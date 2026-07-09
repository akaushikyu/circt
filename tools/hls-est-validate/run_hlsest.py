#!/usr/bin/env python3
"""Run cgeist and then hls-est on every design (the prediction side).

    python3 run_hlsest.py [--datasets a,b] [--benchmarks x,y] [-j 8] [--timeout 120]
                          [--pipeline "<hls-est flags>"] [--shim polygeist|<dir>]
                          [--out results/hlsest.json] [--force-cgeist] [--debug-json]
                          [--mlir-from <earlier result json>]

Per design:
  1. cgeist <sources> --function=<top> -S --hls-annotate --raise-scf-to-affine
     --memref-fullrank [<shim>/cgeist_flags] -I <shim> -I <design includes> -o <mlir>
     (cached by hash of sources, shim files and the shim's cgeist flags)
  2. hls-est <mlir> --symbol-privatize=exclude=<top> --symbol-dce <pipeline>
     (the privatize/dce pair keeps only the top and what it calls, which is how
     the inlining double count was fixed)
--mlir-from reuses the MLIR files (and cgeist outcomes) an earlier result file
recorded instead of running cgeist, so two hls-est builds or pipelines can be
compared on byte-identical inputs even after a shim or cgeist change.
Status strings follow CLAUDE.md: ok | cgeist crash | cgeist error: ... |
hls-est error: <status> | hls-est timeout <N>s.
"""
import argparse
import concurrent.futures as cf
import os
import re
import shutil
import subprocess
import sys
import threading
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                       # noqa: E402
import designs as D                      # noqa: E402

LOCK = threading.Lock()
MLIR_ROOT = Path.home() / "hls-est-work" / "mlir"
LOG_ROOT = Path.home() / "hls-est-work" / "hlsest-logs"
CGEIST_TIMEOUT = 600
HDR_EXT = {".h", ".hh", ".hpp", ".hxx", ".inc", ".tcc", ".ipp"}


def resolve_shim(s):
    if s in ("polygeist", "", None):
        return Path(C.SHIM_INCLUDE)
    p = Path(__file__).resolve().parent / "shim" / s
    if p.is_dir():
        return p
    return Path(s).resolve()


# ---------------------------------------------------------------- cgeist ----

def shim_cgeist_flags(shim):
    """Extra cgeist flags a shim needs, from <shim dir>/cgeist_flags (whitespace-separated,
    '#' starts a comment); e.g. shim/exactclass needs --scalar-wrapper-abi. [] without the file."""
    p = Path(shim) / "cgeist_flags"
    if not p.is_file():
        return []
    flags = []
    for line in p.read_text().splitlines():
        flags += line.split("#", 1)[0].split()
    return flags


def cgeist_cmd(d, shim, out, func):
    cmd = [C.CGEIST, *d["sources"], f"--function={func}", "-S", "--hls-annotate",
           "--raise-scf-to-affine", "--memref-fullrank", *shim_cgeist_flags(shim),
           f"-resource-dir={C.CLANG_RESOURCE_DIR}", "-I", str(shim), "-I", "."]
    for inc in d.get("includes", []):
        if inc != ".":
            cmd += ["-I", inc]
    if d["dataset"] == "polybench_pragmas":
        cmd += ["-I", C.POLYBENCH_UTIL_INCLUDE]
    for df in d.get("defines", []):
        cmd += ["-D" + df]
    cmd += ["-o", str(out)]
    return cmd


def source_hash(d, shim):
    files = [Path(d["dir"]) / s for s in d["sources"]]
    for p in Path(d["dir"]).rglob("*"):
        if p.is_file() and p.suffix.lower() in HDR_EXT:
            files.append(p)
    for p in Path(shim).glob("*"):
        if p.is_file():
            files.append(p)
    extra = "|".join([d["top"], " ".join(d.get("includes", [])), " ".join(d.get("defines", [])),
                      str(shim), "cgeist-v3"])
    flags = shim_cgeist_flags(shim)
    if flags:   # only then, so that the keys of shims without cgeist_flags do not change
        extra += "|cgeist-flags:" + " ".join(flags)
    return C.sha256_of_files(files, extra)[:16]


def run_cgeist(d, shim, force=False):
    """Returns (status, mlir_path_or_None, note)."""
    if d.get("mode") == "mlir-only":
        return "ok", Path(d["mlir"]), "mlir-only"
    if not d.get("sources"):
        return "cgeist error: no sources", None, ""
    key = source_hash(d, shim)
    out = MLIR_ROOT / d["dataset"] / f"{d['benchmark']}.{key}.mlir"
    meta = out.with_suffix(".status")
    if out.exists() and meta.exists() and not force:
        st = meta.read_text().strip()
        return (st, out if st == "ok" else None, "cached")
    out.parent.mkdir(parents=True, exist_ok=True)
    log = out.with_suffix(".cgeist.log")
    status, note = "ok", ""
    # The HLSFactory lit tests were generated with --function='*'; a C++ top
    # given by name can silently produce an empty module.  Try '*' first.
    for func in ("*", d["top"]):
        cmd = cgeist_cmd(d, shim, out, func)
        try:
            p = subprocess.run(cmd, cwd=d["dir"], capture_output=True, text=True, errors="replace",
                               timeout=CGEIST_TIMEOUT)
        except subprocess.TimeoutExpired:
            status, note = "cgeist timeout", f"{CGEIST_TIMEOUT}s"
            break
        log.write_text(" ".join(cmd) + "\n\n" + p.stdout + "\n--- stderr ---\n" + p.stderr)
        if p.returncode == 0 and out.exists() and out.stat().st_size > 0                 and re.search(r"func\.func\s", out.read_text(errors="replace")):
            sanitize_mlir(out)
            status, note = "ok", f"--function={func}"
            break
        if p.returncode == 0:
            status, note = "cgeist error: empty module (no functions emitted)", f"--function={func}"
            continue
        if p.returncode < 0 or "Stack dump" in p.stderr or "PLEASE submit a bug report" in p.stderr:
            status = "cgeist crash"
        else:
            errs = [l for l in p.stderr.splitlines() if "error:" in l]
            status = "cgeist error: " + (errs[0].strip()[:200] if errs else f"exit {p.returncode}")
        note = f"--function={func}"
        if func == "*":
            continue          # retry with the top function by name
        break
    meta.write_text(status)
    if status != "ok" and out.exists():
        out.unlink()
    return status, (out if status == "ok" else None), note


def sanitize_mlir(path):
    """cgeist (LLVM 18) emits `module attributes {dlti.dl_spec = ..., llvm.data_layout = ...}`
    in a syntax the LLVM-23 MLIR parser of hls-est rejects; the data layout is
    irrelevant to BRAM estimation, so drop the module attribute dictionary."""
    p = Path(path)
    txt = p.read_text(errors="replace")
    new = re.sub(r"^module attributes \{.*\} \{$", "module {", txt, count=1, flags=re.M)
    if new != txt:
        p.write_text(new)


# ------------------------------------------------------------- top in MLIR ---

def mlir_functions(mlir_path):
    txt = Path(mlir_path).read_text(errors="replace")
    return re.findall(r"func\.func\s+(?:private\s+)?@([A-Za-z0-9_$.]+)", txt)


def demangle(names):
    try:
        p = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True, timeout=30)
        return dict(zip(names, p.stdout.splitlines()))
    except Exception:
        return {n: n for n in names}


def find_top(mlir_path, top):
    funcs = mlir_functions(mlir_path)
    if top in funcs:
        return top, "exact"
    dm = demangle(funcs)
    for n in funcs:
        base = dm.get(n, n).split("(")[0].split("::")[-1].strip()
        if base == top:
            return n, "demangled"
    m = re.compile(r"^_Z(?:N\d*)?(\d+)(" + re.escape(top) + r")(?![A-Za-z0-9_])")
    for n in funcs:
        mm = m.match(n)
        if mm and int(mm.group(1)) == len(top):
            return n, "mangled"
    if len(funcs) == 1:
        return funcs[0], "single"
    return (funcs[-1] if funcs else None), "last"


# ---------------------------------------------------------------- hls-est ----

BLOCK_RE = re.compile(r"^(memref\.(?:alloca|global|arg)[^\n]*)$", re.M)


def parse_hlsest_output(text):
    """Text report: one block per memref followed by 'Total BRAM: N'."""
    mems = []
    cur = None
    total = None
    for line in text.splitlines():
        m = re.match(r"^(memref\.\w+)\s+(.*)$", line)
        if m and not line.startswith(" "):
            cur = {"op": m.group(1), "head": m.group(2).strip(), "kind": None, "bram": None, "detail": []}
            loc = re.search(r'loc\("([^"]*)":(\d+):(\d+)\)', line)
            if loc:
                cur["loc"] = [loc.group(1), int(loc.group(2)), int(loc.group(3))]
            nm = re.search(r"@(\S+)", m.group(2))
            cur["name"] = nm.group(1) if nm and not m.group(2).startswith("@ loc") else None
            vn = re.search(r'varname\s*=\s*"?([A-Za-z0-9_]+)"?', line)
            if vn:
                cur["varname"] = vn.group(1)
            mems.append(cur)
            continue
        m = re.match(r"^\s+kind=(\S+)\s+bram=(\d+)", line)
        if m and cur is not None:
            cur["kind"], cur["bram"] = m.group(1), int(m.group(2))
            continue
        m = re.match(r"^\s*Total BRAM:\s*(\d+)", line)
        if m:
            total = int(m.group(1))
            continue
        if cur is not None and line.startswith("    "):
            cur["detail"].append(line.strip())
    return total, mems


def run_hlsest(mlir, top_fn, pipeline, timeout, log_prefix, privatize=True, debug_json=None):
    cmd = [C.HLS_EST, str(mlir)]
    if privatize and top_fn:
        cmd += [f"--symbol-privatize=exclude={top_fn}", "--symbol-dce"]
    cmd += pipeline.split()
    if debug_json:
        cmd += [f"--bram-debug-json={debug_json}"]
    cmd += ["-o", "/dev/null"]
    t0 = time.time()
    try:
        p = subprocess.run(cmd, capture_output=True, text=True, errors="replace", timeout=timeout)
    except subprocess.TimeoutExpired:
        return {"status": f"hls-est timeout {timeout}s", "elapsed_s": timeout, "cmd": " ".join(cmd)}
    el = time.time() - t0
    Path(log_prefix + ".out").write_text(p.stdout)
    Path(log_prefix + ".err").write_text(" ".join(cmd) + "\n\n" + p.stderr)
    total, mems = parse_hlsest_output(p.stdout + "\n" + p.stderr)
    # pipeline_full = every pass actually run, incl. the per-design top-selection prefix
    # (--symbol-privatize/--symbol-dce).  Re-run a case from `cmd`/`pipeline_full`, never from
    # `pipeline` alone: without the prefix uncalled public functions are costed too (OPEN_ISSUES O12).
    full = " ".join(a for a in cmd[2:] if a not in ("-o", "/dev/null"))
    r = {"elapsed_s": round(el, 2), "cmd": " ".join(cmd), "pipeline_full": full, "total_bram": total,
         "memrefs": mems, "exit": p.returncode}
    if p.returncode < 0 or p.returncode > 1 and ("Stack dump" in p.stderr or "Aborted" in p.stderr or "Assertion" in p.stderr):
        r["status"] = "hls-est error: crash"
        a = re.search(r"Assertion `([^']*)' failed", p.stderr)
        r["note"] = (a.group(0) if a else p.stderr.strip().splitlines()[-1] if p.stderr.strip() else "")[:200]
    elif p.returncode != 0:
        errs = [l for l in p.stderr.splitlines() if "error:" in l]
        r["status"] = "hls-est error: " + (errs[0].split("error:", 1)[1].strip()[:160] if errs else f"exit {p.returncode}")
    elif total is None:
        r["status"] = "hls-est error: no total"
    else:
        r["status"] = "ok"
    if debug_json and Path(debug_json).exists():
        r["debug_json"] = debug_json
    return r


def process(d, args, shim, run_id):
    key = C.design_key(d)
    r = {"dataset": d["dataset"], "benchmark": d["benchmark"], "top": d["top"], "mode": d.get("mode"),
         "pipeline": args.pipeline, "shim": str(shim)}
    prev = (args.mlir_from_records or {}).get(key)
    if prev and prev.get("mlir") and Path(prev["mlir"]).exists():
        st, mlir, note = "ok", Path(prev["mlir"]), f"from {args.mlir_from}"
    elif prev and str(prev.get("cgeist_status", "ok")) != "ok":
        st, mlir, note = prev["cgeist_status"], None, f"from {args.mlir_from}"
    else:
        st, mlir, note = run_cgeist(d, shim, args.force_cgeist)
    r["cgeist_status"], r["cgeist_note"] = st, note
    if st != "ok":
        r["status"] = st
        return r
    r["mlir"] = str(mlir)
    top_fn, rule = find_top(mlir, d["top"])
    r["top_fn"], r["top_rule"] = top_fn, rule
    log_prefix = str(LOG_ROOT / run_id / f"{d['dataset']}__{d['benchmark']}")
    Path(log_prefix).parent.mkdir(parents=True, exist_ok=True)
    # Always emit the per-memref debug JSON: compare.py needs it to match arrays by name.
    dbg = log_prefix + ".debug.json" if not args.no_debug_json else None
    hr = run_hlsest(mlir, top_fn, args.pipeline, args.timeout, log_prefix,
                    privatize=not args.no_privatize, debug_json=dbg)
    r.update(hr)
    return r


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--datasets", default="")
    ap.add_argument("--benchmarks", default="")
    ap.add_argument("-j", type=int, default=8)
    ap.add_argument("--timeout", type=int, default=C.HLSEST_TIMEOUT)
    ap.add_argument("--pipeline", default=C.DEFAULT_PIPELINE)
    ap.add_argument("--shim", default="scalar")
    ap.add_argument("--out", default=str(C.RESULTS_DIR / "hlsest.json"))
    ap.add_argument("--run-id", default=None)
    ap.add_argument("--force-cgeist", action="store_true")
    ap.add_argument("--mlir-from", default=None,
                    help="earlier run_hlsest result json: reuse its MLIR files instead of running cgeist")
    ap.add_argument("--no-privatize", action="store_true")
    ap.add_argument("--debug-json", action="store_true", help="(default now; kept for compatibility)")
    ap.add_argument("--no-debug-json", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    shim = resolve_shim(args.shim)
    args.mlir_from_records = None
    if args.mlir_from:
        prev = C.load_json(args.mlir_from, {}) or {}
        args.mlir_from_records = {k: v for k, v in prev.items() if k != "_meta"}
    designs = D.load_designs()
    if args.datasets:
        ds = set(args.datasets.split(","))
        designs = [d for d in designs if d["dataset"] in ds]
    if args.benchmarks:
        bs = set(args.benchmarks.split(","))
        designs = [d for d in designs if d["benchmark"] in bs]
    run_id = args.run_id or time.strftime("%Y%m%d-%H%M%S")
    ghash, bsha = C.hls_est_identity()
    results = {"_meta": {"pipeline": args.pipeline, "shim": str(shim), "hls_est_git": ghash,
                         "hls_est_sha256": bsha, "mlir_from": args.mlir_from,
                         "top_passes": ("none" if args.no_privatize else
                                        "--symbol-privatize=exclude=<top> --symbol-dce prepended per design"),
                         "timeout": args.timeout, "run_id": run_id, "hls_est": C.HLS_EST}}
    if not args.quiet:
        print(f"{len(designs)} designs; pipeline: {args.pipeline}; shim: {shim}; git {ghash}", flush=True)
    done = 0
    with cf.ThreadPoolExecutor(max_workers=args.j) as ex:
        futs = {ex.submit(process, d, args, shim, run_id): d for d in designs}
        for f in cf.as_completed(futs):
            d = futs[f]
            try:
                r = f.result()
            except Exception as e:  # noqa: BLE001
                r = {"dataset": d["dataset"], "benchmark": d["benchmark"], "status": "harness error",
                     "note": repr(e)[:300]}
            done += 1
            with LOCK:
                results[C.design_key(d)] = r
            if not args.quiet:
                print(f"[{done}/{len(designs)}] {C.design_key(d):50s} {r.get('status', ''):40.40s} "
                      f"BRAM={r.get('total_bram')} {r.get('elapsed_s', '')}s", flush=True)
    C.dump_json(results, args.out)
    n_ok = sum(1 for k, r in results.items() if k != "_meta" and r.get("status") == "ok")
    print(f"done: {n_ok} ok of {len(results) - 1} -> {args.out}")


if __name__ == "__main__":
    main()
