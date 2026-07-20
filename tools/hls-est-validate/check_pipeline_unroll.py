#!/usr/bin/env python3
"""Compare --auto-pipeline-unroll's decisions with Vitis HLS on the
pipeline_unroll experiment kernels (VITIS_NOTES.md N3).

For every kernel in ~/hls-est-work/exp-src/pipeline_unroll{,_chk,_float}/*.cpp:
  1. the cgeist MLIR (scalar shim, `<mlir-dir>/<kernel>.mlir`) is run through
       hls-est --affine-loop-normalize --auto-pipeline-unroll=emit-remarks
     and the remarks + output IR give, per loop:
       pipelined (hls.pipeline tag), unrolled (factor), flattened
       (hls.flattened_parents ancestors).
     Loops are identified by source line: the k-th affine.for of a func.func
     (pre-order) is the k-th `for` statement of the C function with the same
     `hls.orig_name` (cgeist keeps the source order).
  2. the Vitis log of the newest experiment run gives the same three sets:
       [HLS 214-376] automatically set the pipeline for Loop< VITIS_LOOP_L_n>
       [HLS 214-186] Unrolling loop 'VITIS_LOOP_L_n' ... with a factor of F
       [XFORM 203-541] Flattening a loop nest 'VITIS_LOOP_L_n'
  3. unless --no-bram, the canonical pipeline (without
     --infer-vitis-split-array, as the default since MEMOS M1) is run and its
     Total BRAM compared with the
     Vitis total of the same run (`<exp-src>/out/<kernel>.json`).

A kernel named `..._pl<N>_...` was synthesized with
syn.compile.pipeline_loops=N; hls-est gets pipeline-loops=N for it.

--apu-opts "a b=c" appends options to --auto-pipeline-unroll in both runs
(e.g. --apu-opts float-loads-perfect).

Usage: check_pipeline_unroll.py [--mlir-dir DIR] [--no-bram] [--md OUT.md]
                                [--only K1,K2] [--apu-opts OPTS]
"""
import argparse
import json
import re
import subprocess
from pathlib import Path

HOME = Path.home()
HLS_EST = HOME / "circt/build/clion/bin/hls-est"
EXP_SRC = [HOME / "hls-est-work/exp-src/pipeline_unroll",
           HOME / "hls-est-work/exp-src/pipeline_unroll_chk",
           HOME / "hls-est-work/exp-src/pipeline_unroll_float"]
EXPERIMENTS = HOME / "hls-est-work/experiments"

RE_PIPE = re.compile(r"\[HLS 214-376\] automatically set the pipeline for Loop< ?VITIS_LOOP_(\d+)_\d+>")
RE_UNROLL = re.compile(r"\[HLS 214-186\] Unrolling loop 'VITIS_LOOP_(\d+)_\d+'.*?with a factor of (\d+)")
RE_FLAT = re.compile(r"\[XFORM 203-541\] Flattening a loop nest 'VITIS_LOOP_(\d+)_\d+'")
RE_REMARK_UNROLL = re.compile(r"^[^:\n]*:(\d+):\d+: remark: unrolling loop completely with a factor of (\d+)", re.M)
RE_LOC = re.compile(r'^#loc(\d+) = loc\("[^"]*":(\d+):\d+\)')
RE_FOR = re.compile(r"^(\s*)(?:%\S+(?::\d+)? = )?affine\.for ")
RE_CLOSE = re.compile(r"^(\s*)\}(?: \{(.*)\})? loc\(#loc(\d+)\)")
RE_FUNC = re.compile(r"^\s*func\.func @(\S+)\(.*hls\.orig_name = \"([^\"]+)\"")
RE_FUNC_PLAIN = re.compile(r"^\s*func\.func @(\S+)\(")
RE_C_FUNC = re.compile(r"^\s*(?:static\s+)?(?:inline\s+)?[A-Za-z_][\w\s\*]*?\b([A-Za-z_]\w*)\s*\(")
RE_C_FOR = re.compile(r"\bfor\s*\(")


def pipeline_loops_of(kernel):
    m = re.search(r"_pl(\d+)_", kernel)
    return int(m.group(1)) if m else None


APU_OPTS = []  # extra --auto-pipeline-unroll options (--apu-opts)


def apu_flag(kernel, extra):
    pl = pipeline_loops_of(kernel)
    opts = list(extra) + ([f"pipeline-loops={pl}"] if pl is not None else []) + APU_OPTS
    return "--auto-pipeline-unroll" + ("=" + " ".join(opts) if opts else "")


def decide_flags(kernel):
    return ["--affine-loop-normalize", apu_flag(kernel, ["emit-remarks"]),
            "--mlir-print-debuginfo"]


def bram_flags(kernel):
    auto = apu_flag(kernel, [])
    return ["--affine-loop-normalize", auto, "--memory-banking-bram",
            "--convert-affine-to-loopschedule", "--bram-analysis"]


def c_loops_by_function(cpp):
    """{function name: [source line of each `for`, in order]}"""
    out, cur, depth = {}, None, 0
    for i, line in enumerate(cpp.read_text(errors="replace").splitlines(), 1):
        stripped = line.split("//")[0]
        if depth == 0:
            m = RE_C_FUNC.match(stripped)
            if m and "{" in stripped or (m and not stripped.rstrip().endswith(";")):
                cur = m.group(1)
                out.setdefault(cur, [])
        if cur is not None:
            for _ in RE_C_FOR.finditer(stripped):
                out[cur].append(i)
        depth += stripped.count("{") - stripped.count("}")
        if depth <= 0:
            depth = 0
            if "}" in stripped:
                cur = None
    return out


def mlir_loop_lines(mlir, c_loops):
    """{line in the .mlir of each affine.for: source line} via per-function order."""
    mapping, func, k = {}, None, 0
    for i, line in enumerate(mlir.read_text().splitlines(), 1):
        m = RE_FUNC.match(line)
        if m:
            func, k = m.group(2), 0
            continue
        m = RE_FUNC_PLAIN.match(line)
        if m:
            func, k = m.group(1).lstrip("@"), 0
            continue
        if RE_FOR.match(line):
            lines = c_loops.get(func, [])
            mapping[i] = lines[k] if k < len(lines) else None
            k += 1
    return mapping


def vitis_sets(kernel):
    """(pipelined, unrolled{line: factor}, flattened, bram, run) of the newest run."""
    d = EXPERIMENTS / kernel
    runs = sorted(d.glob("*/log/hls_compile.log"), key=lambda p: p.stat().st_mtime) if d.exists() else []
    if not runs:
        return None
    log = runs[-1].read_text(errors="replace")
    pipelined = {int(m.group(1)) for m in RE_PIPE.finditer(log)}
    unrolled = {int(m.group(1)): int(m.group(2)) for m in RE_UNROLL.finditer(log)}
    flattened = {int(m.group(1)) for m in RE_FLAT.finditer(log)}
    bram = None
    for d in EXP_SRC:
        j = d / "out" / f"{kernel}.json"
        if j.exists():
            try:
                bram = json.loads(j.read_text()).get("totals", {}).get("BRAM")
            except Exception:
                bram = None
            break
    return pipelined, unrolled, flattened, bram, runs[-1].parent.parent.name


def hlsest_sets(kernel, mlir, line_map):
    """(pipelined, unrolled{line: factor}, flattened) from hls-est, or (None, err)."""
    cmd = [str(HLS_EST), str(mlir)] + decide_flags(kernel)
    try:
        p = subprocess.run(cmd, capture_output=True, text=True, timeout=300)
    except subprocess.TimeoutExpired:
        return None, "timeout"
    if p.returncode != 0:
        return None, p.stderr[-2000:]
    unrolled = {}
    for m in RE_REMARK_UNROLL.finditer(p.stderr):
        src = line_map.get(int(m.group(1)))
        unrolled[src] = int(m.group(2))
    locs = {}
    for line in p.stdout.splitlines():
        m = RE_LOC.match(line)
        if m:
            locs[int(m.group(1))] = int(m.group(2))
    # Loop tree from indentation: every affine.for opens at some indent and
    # closes with `} {attrs} loc(#locN)` at the same indent.
    nodes, open_stack = [], []
    for line in p.stdout.splitlines():
        m = RE_FOR.match(line)
        if m:
            nodes.append({"indent": len(m.group(1)), "line": None, "attrs": "",
                          "parent": open_stack[-1] if open_stack else None})
            open_stack.append(len(nodes) - 1)
            continue
        m = RE_CLOSE.match(line)
        if m and open_stack and nodes[open_stack[-1]]["indent"] == len(m.group(1)):
            idx = open_stack.pop()
            nodes[idx]["attrs"] = m.group(2) or ""
            nodes[idx]["line"] = line_map.get(locs.get(int(m.group(3))))
    pipelined, flattened = set(), set()
    for n in nodes:
        if "hls.pipeline" not in n["attrs"]:
            continue
        pipelined.add(n["line"])
        fm = re.search(r"hls\.flattened_parents = (\d+)", n["attrs"])
        k = int(fm.group(1)) if fm else 0
        p_idx = n["parent"]
        while k > 0 and p_idx is not None:
            flattened.add(nodes[p_idx]["line"])
            p_idx = nodes[p_idx]["parent"]
            k -= 1
    return (pipelined, unrolled, flattened), None


def bram_total(kernel, mlir):
    cmd = [str(HLS_EST), str(mlir)] + bram_flags(kernel)
    try:
        p = subprocess.run(cmd, capture_output=True, text=True, timeout=300)
    except subprocess.TimeoutExpired:
        return "timeout"
    if p.returncode != 0:
        return "error"
    m = re.search(r"Total BRAM:\s*(\d+)", p.stdout)
    return int(m.group(1)) if m else "n/a"


def fmt_set(s):
    return ",".join(str(x) for x in sorted(x for x in s if x is not None)) or "-"


def fmt_unroll(d):
    return ",".join(f"{l}x{f}" for l, f in sorted((k if k is not None else -1, v) for k, v in d.items())) or "-"


def fmt_dec(p, u, f):
    return f"P {fmt_set(p)} / U {fmt_unroll(u)} / F {fmt_set(f)}"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--mlir-dir", default=str(HOME / "hls-est-work/t3/mlir"))
    ap.add_argument("--no-bram", action="store_true")
    ap.add_argument("--md", default=None)
    ap.add_argument("--only", default="")
    ap.add_argument("--apu-opts", default="",
                    help="extra --auto-pipeline-unroll options, space separated")
    args = ap.parse_args()
    APU_OPTS.extend(args.apu_opts.split())
    mlir_dir = Path(args.mlir_dir)
    kernels = [(cpp.stem, cpp) for d in EXP_SRC for cpp in sorted(d.glob("*.cpp"))]
    if args.only:
        kernels = [(k, c) for k, c in kernels if k in args.only.split(",")]
    rows, agree, compared, bram_eq, bram_n = [], 0, 0, 0, 0
    for k, cpp in kernels:
        v = vitis_sets(k)
        mlir = mlir_dir / f"{k}.mlir"
        if not mlir.exists():
            rows.append([k, "", "no mlir", "no", "", "", "", ""])
            continue
        line_map = mlir_loop_lines(mlir, c_loops_by_function(cpp))
        h, err = hlsest_sets(k, mlir, line_map)
        if h is None:
            last = err.strip().splitlines()[-1] if err and err.strip() else err
            rows.append([k, "", f"hls-est error: {last}", "no", "", "", "", ""])
            continue
        hp, hu, hf = h
        if v is None:
            rows.append([k, "no vitis run", fmt_dec(hp, hu, hf), "?", "", "", "", ""])
            continue
        vp, vu, vf, vbram, vhash = v
        ok = (vp == hp) and (vu == hu) and (vf == hf)
        compared += 1
        agree += ok
        hb = ""
        if not args.no_bram:
            hb = bram_total(k, mlir)
            bram_n += 1
            bram_eq += (hb == vbram)
        rows.append([k, fmt_dec(vp, vu, vf), fmt_dec(hp, hu, hf),
                     "yes" if ok else "NO", vbram, hb,
                     ("=" if hb == vbram else "x") if not args.no_bram else "",
                     vhash])
    out = ["| kernel | Vitis (P pipelined / U unrolled xfactor / F flattened; source lines) | hls-est | agree | Vitis BRAM | hls-est BRAM (canonical, no split) | = | Vitis run |",
           "|---|---|---|---|---|---|---|---|"]
    for r in rows:
        out.append("| " + " | ".join(str(x) for x in r) + " |")
    out.append("")
    out.append(f"decision agreement: {agree}/{compared}" +
               (f"; BRAM totals equal: {bram_eq}/{bram_n}" if not args.no_bram else ""))
    text = "\n".join(out)
    print(text)
    if args.md:
        Path(args.md).write_text(text + "\n")


if __name__ == "__main__":
    main()
