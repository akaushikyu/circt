#!/usr/bin/env python3
"""Collect the per-module memory port-usage vectors (`MemPortTyVec`) from the Vitis
`db/*.verbose.bind.rpt` files of cached runs.

For every run directory (a `cache_dir` of results/vitis.json or an
~/hls-est-work/experiments/<name>/<hash>/ directory) the bind reports list each
memory the module touches as `<comp ... class="1000" name="X">` followed by
`<MemPortTyVec>a b ...</MemPortTyVec>`: one entry per port slot, with
0 = write-only, 1 = read-only, 2 = read/write, 3 = unused (the enum order of
MemoryQuerier::PORT_TYPE in hls-llvm-project CoreQuerier.h plus the "unused"
value that MemoryQuerier::isSDPMode treats as `> READ_WRITE`).

Output: a JSON map {run_dir: {comp_name: [[module, "a b c"], ...]}} used by
formula_reconcile.py (`--portvec`). Python 3 stdlib only.

    python3 bind_portvec.py --vitis results/vitis.json \
        --experiments ~/hls-est-work/experiments -o ~/hls-est-work/exp-notes/bind_portvec.json
"""
import argparse
import glob
import json
import os
import re
import sys
import time

COMP_RE = re.compile(r'<comp id="\d+" class="(\d+)" name="([^"]*)"')
VEC_RE = re.compile(r"<MemPortTyVec>([^<]*)</MemPortTyVec>")


def scan_report(path):
    """Line-oriented state machine: the vector belongs to the last `<comp>` seen."""
    out = []
    name, cls = None, None
    with open(path, errors="replace") as f:
        for line in f:
            m = COMP_RE.search(line)
            if m:
                cls, name = m.group(1), m.group(2)
                continue
            m = VEC_RE.search(line)
            if m and name is not None and cls == "1000":
                out.append((name, m.group(1).strip()))
                name = None
    return out


def scan_run(run_dir):
    res = {}
    for f in sorted(glob.glob(os.path.join(run_dir, "db", "*.verbose.bind.rpt"))):
        module = os.path.basename(f)[: -len(".verbose.bind.rpt")]
        for name, vec in scan_report(f):
            res.setdefault(name, []).append([module, vec])
    return res


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--vitis", action="append", default=[], help="results JSON whose cache_dir entries are scanned (repeatable)")
    ap.add_argument("--experiments", default=None, help="experiments root: every <name>/<hash>/ with db/ is scanned")
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("--update", action="store_true", help="keep entries already in --out, scan only new run dirs")
    args = ap.parse_args()

    runs = []
    for p in args.vitis:
        d = json.load(open(p))
        for v in d.values():
            cd = v.get("cache_dir") if isinstance(v, dict) else None
            if cd and os.path.isdir(os.path.join(cd, "db")):
                runs.append(cd)
    if args.experiments:
        for h in sorted(glob.glob(os.path.join(os.path.expanduser(args.experiments), "*", "*"))):
            if os.path.isdir(os.path.join(h, "db")):
                runs.append(h)
    runs = sorted(set(runs))

    result = {}
    if args.update and os.path.exists(args.out):
        result = json.load(open(args.out))
    t0 = time.time()
    for i, r in enumerate(runs):
        if r in result:
            continue
        result[r] = scan_run(r)
        if (i + 1) % 50 == 0:
            print(f"[{i + 1}/{len(runs)}] {time.time() - t0:.0f}s", file=sys.stderr)
    with open(args.out, "w") as f:
        json.dump(result, f)
    nvec = sum(len(v) for r in result.values() for v in r.values())
    print(f"scanned {len(runs)} run dirs, {sum(len(r) for r in result.values())} memories, {nvec} vectors -> {args.out} ({time.time() - t0:.0f}s)")


if __name__ == "__main__":
    main()
