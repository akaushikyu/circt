#!/usr/bin/env python3
"""Accesses per state of every array in a Vitis run, from db/*.verbose.sched.rpt.

For each module report the scheduler lists every operation with its state
(`ST_<n> : Operation <id> [<k>/<K>] ...`); a load issues its address in the
state where k == K and returns data later, a store occupies one state. This
counts, per (module, array), how many loads and stores ISSUE in each state and
prints the histogram and the peak - the number of ports the binder needs
(1 -> ram_1p, 2 -> ram_2p / ram_t2p). The bind reports' MemPortTyVec
(bind_portvec.py) only covers arrays a module receives as an argument, not the
module that allocates them (polybench atax `buff_x` in `atax`), so this is the
evidence for sequential regions (VITIS_NOTES.md N12).

    python3 sched_ports.py <run dir with db/> [--arrays a,b] [--json out.json]

<run dir>: a `cache_dir` of results/vitis.json or an
~/hls-est-work/experiments/<name>/<hash>/ directory. Python 3 stdlib only.
"""
import argparse
import glob
import json
import os
import re
import sys

GEP_RE = re.compile(r'"%(\S+) = getelementptr \S+ %([\w.]+),')
ACC_RE = re.compile(r'^ST_(\d+) : Operation \d+ \[(\d+)/(\d+)\][^"]*"(?:%\S+ = )?(load|store) '
                    r'(?:\S+ %\S+, )?\S+ %(\S+?)"')


def scan_report(path):
    """{array: {state: [reads, writes]}} for the accesses issued in each state."""
    with open(path, errors="replace") as f:
        lines = f.readlines()
    base = {}
    for line in lines:
        m = GEP_RE.search(line)
        if m:
            base[m.group(1)] = m.group(2)
    out = {}
    for line in lines:
        m = ACC_RE.search(line)
        if not m:
            continue
        state, k, total, kind, ptr = m.groups()
        if k != total:
            continue  # a later cycle of a multi-cycle access: no new port use
        arr = base.get(ptr, ptr)
        cell = out.setdefault(arr, {}).setdefault(int(state), [0, 0])
        cell[0 if kind == "load" else 1] += 1
    return out


def scan_run(run_dir, arrays=None):
    res = {}
    for f in sorted(glob.glob(os.path.join(run_dir, "db", "*.verbose.sched.rpt"))):
        module = os.path.basename(f)[: -len(".verbose.sched.rpt")]
        for arr, states in scan_report(f).items():
            if arrays and arr not in arrays:
                continue
            hist = {}
            peak = (0, 0)
            for r, w in states.values():
                hist[f"{r}R{w}W"] = hist.get(f"{r}R{w}W", 0) + 1
                if r + w > sum(peak):
                    peak = (r, w)
            res.setdefault(module, {})[arr] = {"states": len(states), "peak_reads": peak[0],
                                               "peak_writes": peak[1], "peak": sum(peak),
                                               "hist": hist}
    return res


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("run_dir")
    ap.add_argument("--arrays", default="", help="comma-separated array names (default: all)")
    ap.add_argument("--json", default=None)
    args = ap.parse_args()
    if not glob.glob(os.path.join(args.run_dir, "db", "*.verbose.sched.rpt")):
        sys.exit(f"no db/*.verbose.sched.rpt under {args.run_dir}")
    arrays = set(a for a in args.arrays.split(",") if a) or None
    res = scan_run(args.run_dir, arrays)
    for module in sorted(res):
        for arr, o in sorted(res[module].items()):
            print(f"{module:48s} {arr:24s} peak {o['peak_reads']}R{o['peak_writes']}W "
                  f"in {o['states']} state(s) with an access  {o['hist']}")
    if args.json:
        with open(args.json, "w") as f:
            json.dump(res, f, indent=1, sort_keys=True)


if __name__ == "__main__":
    main()
