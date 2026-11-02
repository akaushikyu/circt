#!/usr/bin/env python3
"""Rewrite the RUN/CHECK header of every test/hls-est/Estimation/**/*.mlir.

Each Estimation file becomes a regression test of the CURRENT estimator, run exactly as the
harness runs a design (run_hlsest.py): the top selection prefix, the default pipeline,
--bram-analysis with top=<top> and the math-function cost table:

    // RUN: hls-est %s --symbol-privatize=exclude=<top> --symbol-dce <pipeline> \
    //   "--bram-analysis=top=<top> math-costs=%S/.../math_costs.json" -o /dev/null | FileCheck %s
    // CHECK: Total BRAM: <N>{{$}}
    // Vitis 2025.1 td=off: <M>   (or 'no ground truth')   <- for the reader, not checked

so `llvm-lit test/hls-est` passes and catches regressions, while the Vitis comparison stays the job
of the harness (compare.py).  An input hls-est fails on gets no RUN line, only a comment saying
why (lit lists it as unresolved).  Other comments at the top of a file are kept below the new
header; the module and the comments after it are not touched.

    python3 regen_estimation_checks.py [--pipeline "<flags>"] [--no-math-costs] [--dry-run] [--only polybench]

The top function and the ground truth come from the design catalogue (designs.py, default
catalogue) and results/vitis.json, looked up by (dataset, benchmark) from the Estimation
directory and file names (chstone_xilinx -> chstone, ...).  An input with no catalogue design keeps
the old rule: a function named top / kernel, else the last function.
"""
import argparse
import os
import re
import shlex
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402
import designs as D  # noqa: E402
import run_hlsest as RH  # noqa: E402  (the harness's top selection and pass options)

EST = C.CIRCT / "test" / "hls-est" / "Estimation"
DS_MAP = {"chstone_xilinx": "chstone", "flowgnn_xilinx": "flowgnn", "spectorhls": "spector_hls",
          "vitis-examples": "vitis_examples", "basic": "basic"}
# Header lines this script writes (and older versions of it wrote); every other leading comment
# is kept.
GENERATED_RE = re.compile(r"^//\s*(RUN:|CHECK[-A-Z]*:|XFAIL:|UNSUPPORTED:|vitis\(td=off\):|Vitis 2025\.1 td=off:"
                          r"|hls-est currently fails on this input|Not run by lit:)")


def split_header(text):
    """(kept leading comment lines, the rest of the file).  The header is the run of comment and
    blank lines before the first other line."""
    lines = text.splitlines(keepends=True)
    i = 0
    while i < len(lines) and (lines[i].lstrip().startswith("//") or not lines[i].strip()):
        i += 1
    kept = [l for l in lines[:i] if l.strip() and not GENERATED_RE.match(l.strip())]
    return kept, "".join(lines[i:])


def top_by_name(text):
    funcs = re.findall(r"func\.func\s+(?:private\s+)?@([A-Za-z0-9_$.]+)", text)
    for f in funcs:
        if re.match(r"^(_Z\d+)?(top|kernel)\b", f) or f in ("top", "kernel"):
            return f
    return funcs[-1] if funcs else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pipeline", default=C.DEFAULT_PIPELINE)
    RH.add_math_costs_args(ap)
    ap.add_argument("--timeout", type=int, default=300)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--only", default="")
    args = ap.parse_args()
    RH.resolve_math_costs(args)
    V = C.load_json(C.RESULTS_DIR / "vitis.json", {}) or {}
    catalogue = {C.design_key(d): d for d in D.load_designs(verify=False)}
    for f in sorted(EST.glob("**/*.mlir")):
        if args.only and args.only not in str(f):
            continue
        kept, body = split_header(f.read_text(errors="replace"))
        key = f"{DS_MAP.get(f.parent.name, f.parent.name)}/{f.stem}"
        design = catalogue.get(key)
        if design and design.get("top"):
            top, how = RH.find_top(f, design["top"])
        else:
            top, how = top_by_name(body), "by name"
        argv = args.pipeline.split()
        prefix = []
        if top:
            prefix = [f"--symbol-privatize=exclude={top}", "--symbol-dce"]
            argv = RH.with_top(argv, top)
        lit_argv = list(argv)
        if args.math_costs:
            argv = RH.with_bram_option(argv, f"math-costs={args.math_costs}")
            rel = os.path.relpath(args.math_costs, f.parent)
            lit_argv = RH.with_bram_option(lit_argv, f"math-costs=%S/{rel}")
        cmd = [C.HLS_EST, str(f)] + prefix + argv + ["-o", "/dev/null"]
        try:
            p = subprocess.run(cmd, capture_output=True, text=True, errors="replace", timeout=args.timeout)
            m = re.search(r"^Total BRAM:\s*(\d+)\s*$", p.stdout, re.M)
            errs = [l.split("error:", 1)[1].strip() for l in p.stderr.splitlines() if "error:" in l]
            status = f"ok {m.group(1)}" if (p.returncode == 0 and m) else f"fail exit {p.returncode}: " + (
                errs or p.stderr.strip().splitlines() or ["?"])[0][:120]
        except subprocess.TimeoutExpired:
            status = f"timeout {args.timeout}s"
        vit = V.get(key, {})
        vitis = vit.get("totals", {}).get("BRAM") if vit.get("status") == "ok" else None
        truth = (f"{vitis} (results/vitis.json {key}; compared by the harness, not by lit)"
                 if vitis is not None else f"no ground truth ({key}: "
                 + (vit.get("status", "not synthesised") if vit else "no Vitis result") + ")")
        if status.startswith("ok"):
            run = " ".join(shlex.quote(a) if " " in a else a for a in prefix + lit_argv)
            header = (f"// RUN: hls-est %s {run} -o /dev/null | FileCheck %s\n"
                      f"// CHECK: Total BRAM: {status.split()[1]}{{{{$}}}}\n")
        else:
            # UNSUPPORTED, with a RUN line lit never runs: lit reports a test without any RUN
            # line as UNRESOLVED, which fails the check-hls-est target
            header = (f"// Not run by lit: hls-est fails on this input under the default pipeline "
                      f"(top {top}): {status}\n// UNSUPPORTED: true\n// RUN: true\n")
        header += f"// Vitis 2025.1 td=off: {truth}\n"
        header += "".join(kept) + "\n"
        print(f"{str(f.relative_to(EST)):45s} top={top} ({how}) {status:30s} vitis={vitis}")
        if not args.dry_run:
            f.write_text(header + body)


if __name__ == "__main__":
    main()
