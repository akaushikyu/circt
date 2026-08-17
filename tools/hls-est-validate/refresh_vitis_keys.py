#!/usr/bin/env python3
"""Recompute the `vitis_keys` of every record of an hls-est run JSON (run_hlsest.py --out) in place.

    python3 refresh_vitis_keys.py <run .json> [...] [--catalog v2|polygeist]

A record's `vitis_keys` (run_vitis.cache_keys) say which ground-truth entries were synthesised from the
record's sources; compare.py, make_compare_csv.py, make_sheet.py and make_hlsfactory_report.py compare a
design only with such an entry.  The keys depend on the design record alone, never on hls-est's output,
so when the rule that computes them changes (for example run_vitis.equivalent_records) an earlier run
is brought up to date by recomputing them, without running cgeist or hls-est again.  Only records that
already carry `vitis_keys` are touched; a record whose design is no longer in the catalogue keeps its
keys and is listed.  `_meta.vitis_keys_refreshed` records the date and how many records changed.
"""
import argparse
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                        # noqa: E402
import designs as D                       # noqa: E402
import run_vitis as RV                    # noqa: E402


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("runs", nargs="+", help="hls-est run JSON files, rewritten in place")
    ap.add_argument("--catalog", default=None, help="design catalogue (default: designs.default_catalog())")
    a = ap.parse_args()
    by_key = {f"{d['dataset']}/{d['benchmark']}": d for d in D.load_designs(catalog=a.catalog or D.default_catalog())}
    keys_of = {}
    for path in a.runs:
        H = C.load_json(path, None)
        if not isinstance(H, dict):
            sys.exit(f"{path}: not a run JSON")
        changed, missing = 0, []
        for k, r in H.items():
            if k == "_meta" or not isinstance(r, dict) or "vitis_keys" not in r:
                continue
            d = by_key.get(k)
            if d is None:
                missing.append(k)
                continue
            if k not in keys_of:
                keys_of[k] = RV.cache_keys(d)
            if r["vitis_keys"] != keys_of[k]:
                r["vitis_keys"] = keys_of[k]
                changed += 1
        H.setdefault("_meta", {})["vitis_keys_refreshed"] = {"date": time.strftime("%Y-%m-%d %H:%M"),
                                                              "records_changed": changed,
                                                              "generator": "refresh_vitis_keys.py"}
        C.dump_json(H, path)
        print(f"{path}: {changed} records changed" + (f"; not in the catalogue: {', '.join(missing)}" if missing else ""))


if __name__ == "__main__":
    main()
