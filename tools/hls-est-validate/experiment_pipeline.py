#!/usr/bin/env python3
"""Pass-pipeline experiments: run several hls-est pipeline configurations over
the whole design set, score each against the cached Vitis results and record
every configuration in experiments/results.csv (+ one JSON per run).

    python3 experiment_pipeline.py --configs configs.txt [--datasets ...] [-j 8] [--timeout 120]
                                   [--tag ablation] [--vitis results/vitis.json]
    python3 experiment_pipeline.py --ablation            # built-in ablation + reorder set
    python3 experiment_pipeline.py --config "<flags>"    # one configuration

configs.txt: one pipeline per line ('# ...' comments allowed); an optional
'name | flags' form gives the row a name.

Score per configuration: exact matches, total |BRAM error|, failed/crashed
runs, timeouts, per-dataset exact counts; the full pass string and the hls-est
git hash are recorded on every row.  The same global pipeline is applied to
every benchmark (never per benchmark).
"""
import argparse
import csv
import hashlib
import json
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C      # noqa: E402

EXP_DIR = C.HERE / "experiments"
CSV = EXP_DIR / "results.csv"

CORE = "--memory-banking-bram --convert-affine-to-loopschedule --bram-analysis"

ABLATION = [
    ("canonical", C.DEFAULT_PIPELINE),
    ("no-normalize", "--auto-pipeline-unroll --infer-vitis-split-array " + CORE),
    ("no-auto-unroll", "--affine-loop-normalize --infer-vitis-split-array " + CORE),
    ("no-split-infer", "--affine-loop-normalize --auto-pipeline-unroll " + CORE),
    ("base", "--affine-loop-normalize " + CORE),
    ("base+merge-cond", "--affine-loop-normalize --merge-conditional-stores " + CORE),
    ("canonical+merge-cond", "--affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array --merge-conditional-stores " + CORE),
    ("normalize-after-unroll", "--auto-pipeline-unroll --affine-loop-normalize --infer-vitis-split-array " + CORE),
    ("split-after-banking?", "--affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --infer-vitis-split-array --convert-affine-to-loopschedule --bram-analysis"),
    ("+canonicalize+cse", "--affine-loop-normalize --canonicalize --cse --auto-pipeline-unroll --infer-vitis-split-array " + CORE),
    ("+scalrep", "--affine-loop-normalize --auto-pipeline-unroll --canonicalize --affine-scalrep --infer-vitis-split-array " + CORE),
    ("+sccp", "--affine-loop-normalize --canonicalize --sccp --auto-pipeline-unroll --infer-vitis-split-array " + CORE),
    ("+inline", "--inline --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array " + CORE),
    ("+loop-fusion", "--affine-loop-normalize --affine-loop-fusion --auto-pipeline-unroll --infer-vitis-split-array " + CORE),
    ("vis-default", "--auto-pipeline-unroll --canonicalize --affine-scalrep --affine-loop-normalize " + CORE),
    ("pipeline-loops-64", "--affine-loop-normalize --auto-pipeline-unroll=pipeline-loops=64 --infer-vitis-split-array " + CORE),
    ("pipeline-loops-16", "--affine-loop-normalize --auto-pipeline-unroll=pipeline-loops=16 --infer-vitis-split-array " + CORE),
]


def run_config(name, flags, args):
    cid = hashlib.sha1((flags + C.git_hash()).encode()).hexdigest()[:10]
    out = EXP_DIR / "runs" / f"{cid}.json"
    out.parent.mkdir(parents=True, exist_ok=True)
    cmd = [sys.executable, str(C.HERE / "run_hlsest.py"), "--pipeline", flags, "-j", str(args.j),
           "--timeout", str(args.timeout), "--out", str(out), "--run-id", f"exp-{cid}", "--quiet",
           "--shim", args.shim]
    if args.datasets:
        cmd += ["--datasets", args.datasets]
    t0 = time.time()
    if not (out.exists() and not args.force):
        subprocess.run(cmd, check=False)
    cmp_out = EXP_DIR / "runs" / f"{cid}.compare.json"
    subprocess.run([sys.executable, str(C.HERE / "compare.py"), "--vitis", args.vitis, "--hlsest", str(out),
                    "--out", str(cmp_out), "--csv", str(EXP_DIR / "runs" / f"{cid}.compare.csv"), "--quiet"], check=False)
    cmpj = C.load_json(cmp_out, {}) or {}
    s = cmpj.get("summary", {})
    H = C.load_json(out, {}) or {}
    rows = [v for k, v in H.items() if k != "_meta"]
    n_timeout = sum(1 for r in rows if str(r.get("status", "")).startswith("hls-est timeout"))
    n_crash = sum(1 for r in rows if "crash" in str(r.get("status", "")))
    n_err = sum(1 for r in rows if str(r.get("status", "")).startswith("hls-est error"))
    n_cgeist = sum(1 for r in rows if str(r.get("status", "")).startswith("cgeist"))
    per_ds = s.get("per_dataset", {})
    row = {
        "run_id": cid, "name": name, "tag": args.tag, "date": time.strftime("%Y-%m-%d %H:%M"),
        "hls_est_git": H.get("_meta", {}).get("hls_est_git", ""), "pipeline": flags,
        "designs": s.get("designs"), "compared": s.get("compared"), "exact": s.get("exact"),
        "total_abs_error": s.get("total_abs_error"), "hlsest_failed": s.get("hlsest_missing"),
        "timeouts": n_timeout, "crashes": n_crash, "errors": n_err, "cgeist_failed": n_cgeist,
        "wall_s": round(time.time() - t0, 1),
        "per_dataset_exact": " ".join(f"{d}={v['exact']}/{v['compared']}" for d, v in sorted(per_ds.items())),
    }
    return row


def append_csv(row):
    EXP_DIR.mkdir(parents=True, exist_ok=True)
    new = not CSV.exists()
    with open(CSV, "a", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(row.keys()))
        if new:
            w.writeheader()
        w.writerow(row)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--configs")
    ap.add_argument("--config")
    ap.add_argument("--ablation", action="store_true")
    ap.add_argument("--datasets", default="")
    ap.add_argument("--vitis", default=str(C.RESULTS_DIR / "vitis.json"))
    ap.add_argument("--shim", default="scalar")
    ap.add_argument("-j", type=int, default=8)
    ap.add_argument("--timeout", type=int, default=C.HLSEST_TIMEOUT)
    ap.add_argument("--tag", default="")
    ap.add_argument("--force", action="store_true")
    args = ap.parse_args()

    configs = []
    if args.ablation:
        configs += ABLATION
    if args.config:
        configs.append(("cli", args.config))
    if args.configs:
        for line in Path(args.configs).read_text().splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            if "|" in line:
                n, f = line.split("|", 1)
                configs.append((n.strip(), f.strip()))
            else:
                configs.append((line[:40], line))
    if not configs:
        sys.exit("nothing to run (use --ablation, --config or --configs)")
    print(f"{len(configs)} configurations; git {C.git_hash()}")
    for name, flags in configs:
        print(f"=== {name}: {flags}", flush=True)
        row = run_config(name, flags, args)
        append_csv(row)
        print(json.dumps({k: row[k] for k in ("exact", "compared", "total_abs_error", "timeouts", "crashes", "errors")}))
    print(f"appended to {CSV}")


if __name__ == "__main__":
    main()
