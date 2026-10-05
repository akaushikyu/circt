#!/usr/bin/env python3
"""Static check of the held-out catalogue (hls-doc/heldout.md).  Runs no tool: no cgeist, no hls-est, no
Vitis, so it cannot leak an estimate.

    python3 -I check_heldout.py [--json /mnt/d/HLS_heldout/static_check.json]
    python3 -I check_heldout.py --catalog heldout2      (the second set, hls-doc/heldout2.md; JSON in its root)

For every held-out design (designs.load_designs(catalog='heldout'), both splits):
  - the catalogue loads (hlsfactory.toml valid, dataset_hls.tcl reaches set_top, sources and include
    directories exist: designs.verify_design);
  - the synthesis script is normalised (part xc7z020clg400-1, 10 ns, flow_target vivado,
    throughput_driven off);
  - the top function is defined: in a design source (hlsfactory_v2's definition test, then a looser one that
    allows parentheses in the parameter list), else in a header of the design's directories;
  - the split: every design has one, no family straddles eval and locked.
Exit status 1 when a design fails one of the checks (listed).
"""
from __future__ import annotations

import argparse
import json
import os
import posixpath
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
sys.path.insert(0, str(HERE))
import designs as D                       # noqa: E402  (harness modules)
import hlsfactory_v2 as V2                # noqa: E402
import build_heldout as B                 # noqa: E402

HDR = (".h", ".hpp", ".hh", ".hxx", ".inc", ".tcc", ".ipp")


def top_location(d: dict) -> tuple[str, str | None]:
    """('source' | 'source-loose' | 'header' | 'missing', file)."""
    ddir = d["dir"]
    srcs = [posixpath.normpath(posixpath.join(ddir, s)) for s in d["sources"]]
    for s in srcs:
        if V2._defines_function(s, d["top"]):
            return "source", s
    for s in srcs:
        if B.loose_defines(s, d["top"]):
            return "source-loose", s
    dirs = {posixpath.dirname(s) for s in srcs} | {ddir}
    for inc in d.get("includes", []):
        p = inc if posixpath.isabs(inc) else posixpath.normpath(posixpath.join(ddir, inc))
        dirs.add(p)
    word = re.compile(r"\b" + re.escape(d["top"]) + r"\s*\(")
    for dd in sorted(dirs):
        try:
            names = sorted(os.listdir(dd))
        except OSError:
            continue
        for f in names:
            p = posixpath.join(dd, f)
            if f.lower().endswith(HDR) and os.path.isfile(p):
                try:
                    text = B.read_text(p)
                except OSError:
                    continue
                if word.search(text) and (V2._text_defines_function(text, d["top"]) or B.loose_defines(p, d["top"])):
                    return "header", p
    return "missing", None


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--catalog", choices=D.HELDOUT_CATALOGS, default="heldout")
    ap.add_argument("--json", default=None, help="default: <the set's root>/static_check.json")
    a = ap.parse_args(argv)
    a.json = a.json or posixpath.join(D.heldout_root(a.catalog), "static_check.json")
    problems: list[str] = []
    designs = D.load_designs(catalog=a.catalog, problems=problems)
    fails: dict[str, list[str]] = defaultdict(list)
    for p in problems:
        fails[p.split(":", 1)[0]].append(p)
    where = Counter()
    report = {}
    for d in designs:
        key = f"{d['dataset']}/{d['benchmark']}"
        tcl = d["v2"]["tcl"]
        if (tcl["part"], V2.clock_ns(tcl["clock"]), tcl["flow_target"]) != (B.PART, float(B.CLOCK_NS), B.FLOW_TARGET):
            fails[key].append(f"{key}: not normalised: part {tcl['part']} clock {tcl['clock']} "
                              f"flow_target {tcl['flow_target']}")
        if not any("throughput_driven off" in c for c in tcl["configs"]):
            fails[key].append(f"{key}: no config_array_partition -throughput_driven off")
        loc, f = top_location(d)
        where[(d["dataset"], loc)] += 1
        if loc == "missing":
            fails[key].append(f"{key}: top {d['top']} not defined in its sources or headers")
        report[key] = {"top": d["top"], "top_defined": loc, "top_file": f, "split": d["heldout"]["split"],
                       "family": d["heldout"]["family"], "sources": d["sources"]}
    fam_split = defaultdict(set)
    for d in designs:
        fam_split[(d["dataset"], d["heldout"]["family"])].add(d["heldout"]["split"])
    for fam, s in fam_split.items():
        if len(s) > 1:
            fails[f"family {fam}"].append(f"family {fam} is in both splits")
    out = {"generator": "circt tools/hls-est-validate/heldout/check_heldout.py", "designs": len(designs),
           **({"catalog": a.catalog} if a.catalog != "heldout" else {}),
           "top_defined": {f"{ds}:{loc}": n for (ds, loc), n in sorted(where.items())},
           "failures": {k: v for k, v in sorted(fails.items())}, "per_design": report}
    Path(a.json).write_text(json.dumps(out, indent=1) + "\n", encoding="utf-8")
    print(f"{len(designs)} held-out designs ({a.catalog})")
    for (ds, loc), n in sorted(where.items()):
        print(f"  {ds:20s} top defined in {loc:13s} {n}")
    per = Counter((d["dataset"], d["heldout"]["split"]) for d in designs)
    for (ds, sp), n in sorted(per.items()):
        print(f"  {ds:20s} {sp:7s} {n}")
    print(f"failures: {len(fails)} -> {a.json}")
    for k, v in sorted(fails.items())[:40]:
        print("  " + v[0])
    return 1 if fails else 0


if __name__ == "__main__":
    sys.exit(main())
