#!/usr/bin/env python3
"""Rewrite the RUN/CHECK header of every test/hls-est/Estimation/**/*.mlir.

Each Estimation file becomes a regression test of the CURRENT estimator:

    // RUN: hls-est %s <pipeline> -o /dev/null | FileCheck %s
    // CHECK: Total BRAM: <N>
    // vitis(td=off): <M>   (or 'unknown')   <- for the reader, not checked

so `check-circt` / `llvm-lit test/hls-est` passes and catches regressions,
while the Vitis comparison stays the job of the harness (compare.py).

    python3 regen_estimation_checks.py [--pipeline "<flags>"] [--dry-run] [--only polybench]

The pipeline defaults to common.DEFAULT_PIPELINE.  Files whose run fails or
times out get `// XFAIL: *` plus the failure in a comment instead of a CHECK.
The Vitis number is looked up in results/vitis.json by (dataset, benchmark)
using the Estimation directory names (chstone_xilinx -> chstone, ...).
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

EST = C.CIRCT / "test" / "hls-est" / "Estimation"
DS_MAP = {"chstone_xilinx": "chstone", "flowgnn_xilinx": "flowgnn", "spectorhls": "spector_hls",
          "vitis-examples": "vitis_examples", "basic": "basic"}
HEADER_RE = re.compile(r"^(//.*\n|\s*\n)*", re.M)


def top_of(text):
    funcs = re.findall(r"func\.func\s+(?:private\s+)?@([A-Za-z0-9_$.]+)", text)
    for f in funcs:
        if re.match(r"^(_Z\d+)?(top|kernel)\b", f) or f in ("top", "kernel"):
            return f
    return funcs[-1] if funcs else None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--pipeline", default=C.DEFAULT_PIPELINE)
    ap.add_argument("--timeout", type=int, default=300)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--only", default="")
    args = ap.parse_args()
    V = C.load_json(C.RESULTS_DIR / "vitis.json", {}) or {}
    files = sorted(EST.glob("**/*.mlir"))
    for f in files:
        ds_dir = f.parent.name
        if args.only and args.only not in str(f):
            continue
        text = f.read_text(errors="replace")
        body = text[HEADER_RE.match(text).end():] if text.lstrip().startswith("//") else text
        top = top_of(body)
        priv = f"--symbol-privatize=exclude={top} --symbol-dce " if top and body.count("func.func") > 1 else ""
        cmd = [C.HLS_EST, str(f)] + priv.split() + args.pipeline.split() + ["-o", "/dev/null"]
        try:
            p = subprocess.run(cmd, capture_output=True, text=True, errors="replace", timeout=args.timeout)
            m = re.search(r"Total BRAM:\s*(\d+)", p.stdout)
            status = f"ok {m.group(1)}" if (p.returncode == 0 and m) else f"fail rc={p.returncode}: " + (
                (p.stderr.strip().splitlines() or ["?"])[-1][:120])
        except subprocess.TimeoutExpired:
            status = f"timeout {args.timeout}s"
        ds = DS_MAP.get(ds_dir, ds_dir)
        vit = V.get(f"{ds}/{f.stem}", {})
        vitis = vit.get("totals", {}).get("BRAM") if vit.get("status") == "ok" else None
        run = f"// RUN: hls-est %s {priv}{args.pipeline} -o /dev/null | FileCheck %s\n"
        if status.startswith("ok"):
            header = run + f"// CHECK: Total BRAM: {status.split()[1]}\n"
        else:
            header = "// XFAIL: *\n" + run + f"// CHECK: Total BRAM:\n// hls-est currently fails on this input: {status}\n"
        header += f"// vitis(td=off): {vitis if vitis is not None else 'unknown'}  (ground truth from results/vitis.json; compared by the harness, not by lit)\n\n"
        print(f"{str(f.relative_to(EST)):45s} {status:40s} vitis={vitis}")
        if not args.dry_run:
            f.write_text(header + body)


if __name__ == "__main__":
    main()
