#!/usr/bin/env python3
"""hls-est for Compiler Explorer: HLS C/C++ in, a per-array BRAM report (and optionally MLIR) out.

Runs the same two steps as the validation harness (tools/hls-est-validate/run_hlsest.py):
  1. cgeist: C/C++ -> affine MLIR, with the harness's front-end flags (exactclass shim, the
     Vitis synthesis macros, -std=gnu++14 / gnu99);
  2. hls-est: --symbol-privatize/--symbol-dce around the top function, then the default pipeline
     with --bram-analysis=top=<top> and the math cost table, plus --bram-debug-json.
The debug JSON is turned into a table grouped by source variable. Everything is printed as MLIR
'//' comments, so the Compiler Explorer pane can use MLIR highlighting, followed by MLIR when asked.

Usage: hls_est_ce.py <source.cpp|source.c> [options]
  --top=NAME        top function (default: 'top', else the last function cgeist emits)
  --show=WHAT       report (default) | input (cgeist MLIR) | output (MLIR after the pipeline) | all
  --explain         add the per-array reasons (port demand, RAM type, bank math)
  -I<dir>, -D<m>    passed to cgeist
  anything else     passed to hls-est (for example --config-set=tool.hls.options.pipeline_loops=2)

Paths come from the environment, with defaults for this machine:
  HLSEST_CE_CGEIST, HLSEST_CE_HLSEST, HLSEST_CE_SHIM, HLSEST_CE_RESOURCE_DIR, HLSEST_CE_MATH_COSTS
"""

import json
import os
import re
import subprocess
import sys
import tempfile
import time
from pathlib import Path

HOME = Path.home()
DEMO = HOME / "hls-est-demo"      # frozen copies on the Linux disk: fast to load, immune to rebuilds


def _default(env, frozen, fallback):
    if env in os.environ:
        return os.environ[env]
    return str(frozen) if Path(frozen).exists() else fallback


CGEIST = _default("HLSEST_CE_CGEIST", DEMO / "bin/cgeist", "/mnt/d/HLS/Polygeist/build/bin/cgeist")
HLSEST = _default("HLSEST_CE_HLSEST", DEMO / "bin/hls-est", str(HOME / "circt/build/clion/bin/hls-est"))
SHIM = _default("HLSEST_CE_SHIM", DEMO / "shim",
                "/mnt/d/HLS/Polygeist/tools/cgeist/Test/HLS/Inputs/vitis")
RESOURCE_DIR = _default("HLSEST_CE_RESOURCE_DIR", DEMO / "clang/18",
                        "/mnt/d/HLS/Polygeist/llvm-project/build/lib/clang/18")
MATH_COSTS = _default("HLSEST_CE_MATH_COSTS", DEMO / "bin/math_costs.json",
                      str(HOME / "circt/tools/hls-est-validate/math_costs.json"))
# Scratch files on the Linux disk: TMPDIR may point at a Windows folder under WSL.
SCRATCH = os.environ.get("HLSEST_CE_TMP", "/tmp")

# common.DEFAULT_PIPELINE of the harness (MEMOS #61), without --bram-analysis (added with top=).
PIPELINE = ("--lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills "
            "--canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize "
            "--auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths "
            "--memory-banking-bram --convert-affine-to-loopschedule").split()

# The macros Vitis' front end defines (VITIS_NOTES N19); run_hlsest.vitis_frontend_flags.
VITIS_DEFINES = ["-D__SYNTHESIS__", "-D__VITIS_HLS__", "-D__HLS_SYN__", "-DAESL_SYN"]

TARGET_NAME = "xc7z020"
TARGET_BRAM = 280          # BRAM_18K sites on the xc7z020 (the Vitis utilization report's 'Available')
TIMEOUT_S = 120


def shim_flags():
    """The extra cgeist flags of the shim (its cgeist_flags file; '#' starts a comment)."""
    p = Path(SHIM) / "cgeist_flags"
    flags = []
    if p.is_file():
        for line in p.read_text().splitlines():
            flags += line.split("#", 1)[0].split()
    return flags


def version():
    """One line for Compiler Explorer's compiler list."""
    import hashlib
    try:
        md5 = hashlib.md5(Path(HLSEST).read_bytes()).hexdigest()[:8]
    except OSError:
        md5 = "missing"
    return f"hls-est-ce 1.0 (hls-est {md5}, Vitis HLS 2025.1 BRAM model, {TARGET_NAME})"


def parse_args(argv):
    if not argv:
        sys.exit(__doc__)
    if argv[0] in ("--version", "-v"):
        print(version())
        sys.exit(0)
    opts = {"source": None, "top": None, "show": "report", "explain": False,
            "cgeist": [], "hlsest": []}
    for a in argv:
        if a.startswith("--top="):
            opts["top"] = a.split("=", 1)[1]
        elif a.startswith("--show="):
            opts["show"] = a.split("=", 1)[1]
        elif a == "--explain":
            opts["explain"] = True
        elif a.startswith(("-I", "-D", "-std=")):
            opts["cgeist"].append(a)
        elif a.startswith("-"):
            opts["hlsest"].append(a)
        elif opts["source"] is None:
            opts["source"] = a
        else:
            sys.exit(f"hls-est-ce: unexpected argument {a!r}")
    if opts["source"] is None:
        sys.exit("hls-est-ce: no source file")
    if opts["show"] not in ("report", "input", "output", "all"):
        sys.exit(f"hls-est-ce: --show must be report, input, output or all, not {opts['show']!r}")
    return opts


def run(cmd, cwd=None):
    t0 = time.time()
    try:
        p = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, errors="replace",
                           timeout=TIMEOUT_S, stdin=subprocess.DEVNULL)
    except subprocess.TimeoutExpired:
        sys.exit(f"hls-est-ce: {Path(cmd[0]).name} timed out after {TIMEOUT_S} s")
    return p, time.time() - t0


def compile_to_mlir(src, opts, work):
    out = work / "input.mlir"
    std = ["-std=gnu99"] if src.suffix == ".c" else ["-std=gnu++14"]
    if any(a.startswith("-std=") for a in opts["cgeist"]):
        std = []
    cmd = [CGEIST, str(src), "--function=*", "-S", "--hls-annotate", "--raise-scf-to-affine",
           "--memref-fullrank", *shim_flags(), f"-resource-dir={RESOURCE_DIR}", *VITIS_DEFINES,
           *std, "-I", SHIM, "-I", str(src.parent), *opts["cgeist"], "-o", str(out)]
    p, secs = run(cmd, cwd=src.parent)
    text = out.read_text(errors="replace") if out.exists() else ""
    if p.returncode != 0 or not re.search(r"func\.func\s", text):
        sys.stderr.write(p.stderr or "cgeist produced no functions\n")
        sys.exit(1)
    # cgeist (LLVM 18) writes module attributes the LLVM-23 parser of hls-est rejects
    # (run_hlsest.sanitize_mlir); the data layout does not matter for BRAM.
    text = re.sub(r"^module attributes \{.*\} \{$", "module {", text, count=1, flags=re.M)
    out.write_text(text)
    return out, secs


def demangle(names):
    try:
        p = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True,
                           timeout=30)
        return dict(zip(names, p.stdout.splitlines()))
    except (OSError, subprocess.TimeoutExpired):
        return {n: n for n in names}


def find_top(mlir, wanted):
    """The MLIR symbol of the top function (run_hlsest.find_top, with 'top' as the default)."""
    funcs = re.findall(r"func\.func\s+(?:private\s+)?@([A-Za-z0-9_$.]+)", mlir.read_text())
    dm = demangle(funcs)
    plain = {n: dm.get(n, n).split("(")[0].split("::")[-1].strip() for n in funcs}
    for name in ([wanted] if wanted else ["top"]):
        for n in funcs:
            if n == name or plain[n] == name:
                return n, plain[n]
    if wanted:
        sys.exit(f"hls-est-ce: no function named {wanted!r}; cgeist emitted: "
                 + ", ".join(sorted(set(plain.values()))))
    return funcs[-1], plain[funcs[-1]]


def estimate(mlir, top, opts, work):
    debug = work / "debug.json"
    out = work / "output.mlir"
    bram = f"--bram-analysis=top={top}"
    if Path(MATH_COSTS).is_file():
        bram += f" math-costs={MATH_COSTS}"
    cmd = [HLSEST, str(mlir), f"--symbol-privatize=exclude={top}", "--symbol-dce", *PIPELINE,
           bram, *opts["hlsest"], f"--bram-debug-json={debug}", "-o", str(out)]
    p, secs = run(cmd)
    if p.returncode != 0 or not debug.exists():
        sys.stderr.write(p.stderr or p.stdout or f"hls-est failed (exit {p.returncode})\n")
        sys.exit(1)
    return json.loads(debug.read_text()), out, p.stdout, secs


def shape_text(m):
    shape = m.get("shape") or []
    return "x".join(str(s) for s in shape) if shape else "scalar"


def group_arrays(memrefs):
    """One row per source array: partitioned banks of one variable are merged."""
    groups = {}
    for m in memrefs:
        name = m.get("varname") or m.get("name") or "(unnamed)"
        loc = m.get("loc") or {}
        key = (m.get("func"), name, loc.get("line"), loc.get("col"))
        groups.setdefault(key, []).append(m)
    return list(groups.values())


def original_shape(m, banks):
    """The declared shape: a partitioned bank's shape with the partitioned dimension restored."""
    shape = list(m.get("shape") or [])
    part = m.get("partition") or {}
    dim = part.get("dim")
    if banks > 1 and shape and isinstance(dim, int) and 1 <= dim <= len(shape):
        if part.get("kind") == "complete":
            shape[dim - 1] = banks
        else:
            shape[dim - 1] *= banks
    return "x".join(str(s) for s in shape) if shape else "scalar"


def partition_text(m, banks=1):
    part = m.get("partition") or {}
    if not part or not part.get("kind") or banks <= 1:
        return "-"
    txt = part["kind"]
    if part.get("factor"):
        txt += f" {part['factor']}"
    if part.get("dim") is not None:
        txt += f" dim {part['dim']}"
    src = part.get("source")
    if src and src != "pragma":
        txt += f", {src}"
    return txt + f" -> {banks} banks"


LIVE_STATUSES = ("counted", "fifo", "pipo")


def is_live(m):
    return m.get("status") in LIVE_STATUSES or (m.get("bram") or 0) > 0


def display_name(m):
    name = m.get("varname") or m.get("name")
    if not name:
        return "(unnamed)"
    if name.startswith("_Z"):
        plain = demangle([name]).get(name, name)
        return plain.split("::")[-1] if plain else name
    return name


def row_for(group):
    first = group[0]
    counted = [m for m in group if is_live(m)]
    bram = sum(m.get("bram") or 0 for m in group)
    copies = max(((m.get("replication") or {}).get("copies") or 1) for m in group)
    if counted:
        kinds = sorted({m.get("ram_type") or "?" for m in counted})
        storage = "/".join(kinds)
    else:
        storage = "removed"
    banks = len(group)
    elem = first.get("elem_type") or f"i{first.get('elem_bits')}"
    shape = original_shape(first, banks)
    fifo = first.get("fifo") or {}
    if fifo.get("groups"):
        # A stream is a one-element memref of the stream object; show the FIFO's depth instead.
        shape = ", ".join(f"depth {g['depth']}" for g in fifo["groups"])
    return {
        "name": display_name(first),
        "shape": shape,
        "type": elem,
        "partition": partition_text(first, banks),
        "storage": storage,
        "copies": str(copies) if counted else "-",
        "bram": bram,
        "status": "live" if counted else first.get("status"),
        "reason": first.get("exclude_reason"),
        "group": group,
    }


def table(rows, headers):
    widths = [max(len(h), *(len(r[i]) for r in rows)) if rows else len(h)
              for i, h in enumerate(headers)]
    fmt = "  ".join("{:<%d}" % w for w in widths[:-1]) + "  {:>%d}" % widths[-1]
    lines = [fmt.format(*headers), "  ".join("-" * w for w in widths)]
    lines += [fmt.format(*r) for r in rows]
    return lines


def explain_lines(row):
    out = []
    for m in row["group"]:
        if not is_live(m):
            continue
        if m.get("status") != "counted":
            out.append(f"  {row['name']}: {m.get('ram_reason')}")
            continue
        bm = m.get("bank_math") or {}
        pd = m.get("port_demand") or {}
        rep = m.get("replication") or {}
        words, bits = m.get("words"), m.get("elem_bits")
        line = f"  {row['name']}"
        if len(row["group"]) > 1:
            line += f"[bank {(m.get('partition') or {}).get('bank_index', '?')}]"
        line += (f": {words} words x {bits} bits, peak {pd.get('total', '?')} port(s)/cycle "
                 f"-> {m.get('ram_type')}")
        if bm:
            line += f"; {bm.get('band', bm.get('formula', ''))} -> {bm.get('blocks_per_copy', '?')} block(s)"
        if (rep.get("copies") or 1) > 1:
            line += f" x {rep['copies']} copies"
        line += f" = {m.get('bram')} BRAM_18K"
        out.append(line)
        if m.get("ram_reason"):
            out.append("      " + m["ram_reason"])
        if len(row["group"]) > 1:
            out.append(f"      (the other {len(row['group']) - 1} banks are priced the same way)")
            break
    return out


def short_reason(reason):
    """The first clause of a debug reason, without the IR locations that follow it."""
    reason = re.split(r": (?:affine|memref|arith|func)\.|;", reason, maxsplit=1)[0]
    return reason.replace(" (Words*Bits >= 1024 -> BRAM)", "")


def report(dbg, top_plain, src_name, t_cgeist, t_hlsest, explain):
    rows = [row_for(g) for g in group_arrays(dbg.get("memrefs") or [])]
    rows.sort(key=lambda r: (-r["bram"], r["name"]))
    total = dbg.get("total_bram", sum(r["bram"] for r in rows))
    arrays = sum(r["bram"] for r in rows)
    lines = [
        "hls-est: static BRAM estimate (replicates Vitis HLS 2025.1 csynth, td=off)",
        f"source {src_name}  |  top {top_plain}  |  target {TARGET_NAME}, BRAM_18K",
        f"time: cgeist {t_cgeist:.1f} s, hls-est {t_hlsest:.2f} s",
        "",
    ]
    live = [r for r in rows if r["status"] == "live"]
    # Unnamed one-element temporaries (cgeist's scalar spills) are noise in a demo table.
    gone = [r for r in rows if r["status"] != "live"
            and not (r["name"] == "(unnamed)" and r["shape"] in ("scalar", "1"))]
    headers = ["array", "shape", "type", "partition", "storage", "copies", "BRAM_18K"]
    if live:
        lines += table([[r["name"], r["shape"], r["type"], r["partition"], r["storage"],
                         r["copies"], str(r["bram"])] for r in live], headers)
    else:
        lines.append("(no array is stored in memory)")
    if gone:
        lines += ["", "not implemented as memory (0 BRAM_18K):"]
        for r in gone:
            reason = r["reason"] or r["status"]
            if not explain:
                reason = short_reason(reason)
            lines.append(f"  {r['name']} ({r['shape']} {r['type']}): {reason}")
    if total != arrays:
        lines += ["", f"other memories (FIFOs, dataflow channels, math-core tables): "
                      f"{total - arrays} BRAM_18K"]
    pct = 100.0 * total / TARGET_BRAM
    lines += ["", f"Total: {total} BRAM_18K  ({pct:.1f} % of the {TARGET_BRAM} on the {TARGET_NAME})"]
    if explain and live:
        lines += ["", "why:"]
        for r in live:
            lines += explain_lines(r)
    return ["// " + l if l else "//" for l in lines]


def main():
    opts = parse_args(sys.argv[1:])
    src = Path(opts["source"]).resolve()
    with tempfile.TemporaryDirectory(prefix="hls-est-ce-", dir=SCRATCH) as tmp:
        work = Path(tmp)
        mlir, t_cgeist = compile_to_mlir(src, opts, work)
        top, top_plain = find_top(mlir, opts["top"])
        dbg, out_mlir, _, t_hlsest = estimate(mlir, top, opts, work)
        lines = report(dbg, top_plain, src.name, t_cgeist, t_hlsest, opts["explain"])
        if opts["show"] in ("input", "all"):
            lines += ["", "// ---- cgeist output (affine MLIR) ----", mlir.read_text().rstrip()]
        if opts["show"] in ("output", "all"):
            lines += ["", "// ---- after the hls-est pipeline ----", out_mlir.read_text().rstrip()]
        print("\n".join(lines).replace(str(work) + "/", ""))


if __name__ == "__main__":
    main()
