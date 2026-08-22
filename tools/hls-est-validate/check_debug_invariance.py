#!/usr/bin/env python3
"""Prove that --bram-debug / --bram-debug-json do not change any estimate.

    python3 check_debug_invariance.py [--hls-est <binary>] [--tests <dir>] [--timeout 60]
                                      [--pipeline "<flags>"] [-j 4]

Runs every *.mlir under --tests (default test/hls-est/Estimation) through the pipeline (default
common.DEFAULT_PIPELINE) twice, once plain and once with `--bram-debug --bram-debug-json=<tmp>`,
and compares the stdout (the --bram-analysis report, including "Total BRAM: N") and the exit
codes; the JSON's total_bram must equal the report's total.

    PASS  stdout identical, exit codes identical, JSON total matches
    FAIL  any of the above differs
    ERR   hls-est failed or timed out in both runs with identical outputs (reported, not a mismatch)

Exits 1 when any case FAILs. (This replaces check_debug_invariance.sh, MEMOS decision #47.)
"""
import argparse
import concurrent.futures as cf
import difflib
import json
import subprocess
import sys
import tempfile
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                       # noqa: E402


def run(cmd, timeout):
    try:
        p = subprocess.run(cmd, capture_output=True, text=True, errors="replace", timeout=timeout)
        return p.returncode, p.stdout
    except subprocess.TimeoutExpired:
        return 124, ""


def check(f, a, tmp):
    base = [a.hls_est, str(f), *a.pipeline.split()]
    js = Path(tmp) / (f.name + f".{abs(hash(str(f)))}.json")
    rc1, out1 = run(base, a.timeout)
    rc2, out2 = run(base + ["--bram-debug", f"--bram-debug-json={js}"], a.timeout)
    total = next((l.split()[2] for l in out1.splitlines() if l.startswith("Total BRAM:")), None)
    jtotal = "-"
    if js.exists() and js.stat().st_size:
        try:
            jtotal = str(json.loads(js.read_text())["total_bram"])
        except (ValueError, KeyError):
            jtotal = "?"
    msg = ""
    if out1 != out2:
        status = "FAIL"
        msg = "".join(list(difflib.unified_diff(out1.splitlines(True), out2.splitlines(True)))[:20])
    elif rc1 != rc2:
        status, msg = "FAIL", f"exit code differs: plain={rc1} debug={rc2}"
    elif rc1 != 0:
        status, total = "ERR", ("timeout" if rc1 == 124 else f"rc={rc1}")
    elif total is not None and jtotal != total:
        status, msg = "FAIL", f"JSON total_bram ({jtotal}) != report total ({total})"
    else:
        status = "PASS"
    return status, total, jtotal, msg


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--hls-est", default=C.HLS_EST)
    ap.add_argument("--pipeline", default=C.DEFAULT_PIPELINE)
    ap.add_argument("--tests", default=str(C.CIRCT / "test" / "hls-est" / "Estimation"))
    ap.add_argument("--timeout", type=int, default=60)
    ap.add_argument("-j", type=int, default=4)
    a = ap.parse_args()
    files = sorted(Path(a.tests).rglob("*.mlir"))
    print(f"hls-est : {a.hls_est}\npipeline: {a.pipeline}\ntests   : {a.tests} (timeout {a.timeout}s each)\n")
    print(f"{'STATUS':<6}{'TOTAL':<11}{'JSON':<11}CASE")
    counts = {"PASS": 0, "FAIL": 0, "ERR": 0}
    with tempfile.TemporaryDirectory() as tmp, cf.ThreadPoolExecutor(a.j) as ex:
        for f, (status, total, jtotal, msg) in zip(files, ex.map(lambda f: check(f, a, tmp), files)):
            counts[status] += 1
            if msg:
                print(f"--- {f.relative_to(a.tests)}: {msg}")
            print(f"{status:<6}{str(total):<11}{jtotal:<11}{f.relative_to(a.tests)}")
    print(f"\ncases={len(files)} pass={counts['PASS']} fail={counts['FAIL']} "
          f"err(tool failed/timeout, outputs still identical)={counts['ERR']}")
    sys.exit(1 if counts["FAIL"] else 0)


if __name__ == "__main__":
    main()
