#!/usr/bin/env python3
"""Freeze the held-out eval / locked split (hls-doc/heldout.md).

    python3 -I make_split.py [--root /mnt/d/HLS_heldout] [--seed 20261025] [--force]
    python3 -I make_split.py --set heldout2              (the second set, hls-doc/heldout2.md: root
                                                          /mnt/d/HLS_heldout2, seed 20261027, committed copy
                                                          tools/hls-est-validate/heldout2/split.json)

Reads <root>/catalog/manifest.json (written by build_heldout.py) and assigns every kept design's FAMILY
(near-duplicate content in either direction, variant-suffix-stripped names, shared sources:
build_heldout.assign_families) as a whole to 'eval' or
'locked', per suite: the families of a suite are sorted by name, shuffled with random.Random(seed), and
each family in that order goes to the split that holds fewer designs so far (ties: 'eval').  So both
splits get about half the designs and no family straddles them.

Writes <root>/split.json and the committed copy tools/hls-est-validate/heldout/split.json.  It refuses to
overwrite an existing split unless --force: the split is decided once, before any result exists.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import random
import sys
from collections import defaultdict
from pathlib import Path

SEED = 20261025
HERE = Path(__file__).resolve().parent
# per held-out set: default root, seed, the directory of the committed copy, and the 'frozen' note
SETS = {
    "heldout": {"root": "/mnt/d/HLS_heldout", "seed": SEED, "copy_dir": HERE, "doc": "hls-doc/heldout.md",
                "frozen": None},
    "heldout2": {"root": "/mnt/d/HLS_heldout2", "seed": 20261027, "copy_dir": HERE.parent / "heldout2",
                 "doc": "hls-doc/heldout2.md",
                 "frozen": "2026-10-27, before any ground truth or estimate of the second held-out set existed "
                           "(no cgeist, hls-est or Vitis run on any of its designs)"},
}


def make_split(manifest: dict, seed: int, set_name: str = "heldout") -> dict:
    fams: dict[str, dict[str, list[str]]] = defaultdict(lambda: defaultdict(list))
    for d in manifest["designs"]:
        if d["status"] == "kept":
            fams[d["dataset"]][d["family"]].append(f"{d['dataset']}/{d['design']}")
    designs, suites = {}, {}
    for ds in sorted(fams):
        order = sorted(fams[ds])
        random.Random(f"{seed}:{ds}").shuffle(order)
        count = {"eval": 0, "locked": 0}
        fam_split = {}
        for f in order:
            s = "eval" if count["eval"] <= count["locked"] else "locked"
            fam_split[f] = s
            count[s] += len(fams[ds][f])
            for k in sorted(fams[ds][f]):
                designs[k] = {"split": s, "family": f}
        suites[ds] = {"designs": count, "families": {s: sum(1 for v in fam_split.values() if v == s)
                                                    for s in ("eval", "locked")}}
    out = {"generator": "circt tools/hls-est-validate/heldout/make_split.py",
            "seed": seed, "rule": "per suite: families sorted, shuffled with random.Random(f'{seed}:{dataset}'), "
                                  "each assigned to the split with fewer designs so far (ties: eval)",
            "frozen": "2026-10-25, before any held-out ground truth or estimate existed; re-split the same day "
                      "(content families, review of circt 126f478c5) before any estimate existed and without "
                      "reading any held-out Vitis result",
            "locked_release": "locked designs are not scored or inspected until Peter releases them "
                              "(hls-doc/heldout.md)",
            "suites": suites, "designs": dict(sorted(designs.items()))}
    s = SETS[set_name]
    if s["frozen"]:
        out.update(set=set_name, frozen=s["frozen"],
                   locked_release=f"locked designs are not scored or inspected until Peter releases them ({s['doc']})")
    return out


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--set", choices=sorted(SETS), default="heldout", help="the held-out set (default heldout)")
    ap.add_argument("--root", default=None, help="default: the set's root")
    ap.add_argument("--seed", type=int, default=None, help="default: the set's seed")
    ap.add_argument("--force", action="store_true")
    a = ap.parse_args(argv)
    s = SETS[a.set]
    root = Path(a.root or s["root"])
    a.seed = s["seed"] if a.seed is None else a.seed
    mpath = root / "catalog" / "manifest.json"
    manifest = json.loads(mpath.read_text(encoding="utf-8"))
    split = make_split(manifest, a.seed, a.set)
    split["manifest_sha256"] = hashlib.sha256(mpath.read_bytes()).hexdigest()
    text = json.dumps(split, indent=1) + "\n"
    outs = [root / "split.json", Path(s["copy_dir"]) / "split.json"]
    if not a.force and any(p.exists() for p in outs):
        print("split.json exists: the split is frozen (use --force only before any result exists)",
              file=sys.stderr)
        return 1
    for p in outs:
        p.write_text(text, encoding="utf-8", newline="\n")
    for ds, v in split["suites"].items():
        print(f"{ds}: designs eval {v['designs']['eval']} locked {v['designs']['locked']}; "
              f"families eval {v['families']['eval']} locked {v['families']['locked']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
