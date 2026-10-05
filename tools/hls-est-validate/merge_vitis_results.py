#!/usr/bin/env python3
"""Merge one Vitis summary JSON (run_vitis.py --out) into another, without overwriting anything.

    python3 merge_vitis_results.py --from ~/hls-est-work/results/vitis-v2.json \
                                   [--into results/vitis.json] [--dry-run] [--no-catalog]

Every dataset/benchmark key the target lacks is copied over unchanged.  A key present in both keeps
the target's entry; when the two entries were synthesised from different sources (their Vitis cache
keys differ) the key is listed as a conflict and the target still wins, so a ground-truth entry is
never replaced silently.  The target is rewritten under the same lock run_vitis.py takes for its
summary, so a concurrent runner's or --reparse's entries are kept.

The report gives, per dataset of the design catalogue: designs with sources, entries with Vitis
'ok', failures grouped by the class of their first error message, timeouts, and the designs with no
entry at all (never synthesised).  --no-catalog skips loading the catalogue (it walks /mnt/d and
takes minutes) and reports over the merged entries only.
"""
import argparse
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                       # noqa: E402

# A Vitis failure is classed by the message id of its first ERROR line; the classes name what went
# wrong in words so that the per-dataset table reads without looking the ids up.
FAILURE_CLASSES = [
    (r"Path length exceeds", "Windows path too long"),
    (r"\[HLS 207-812\]", "header not found"),
    (r"\[HLS 214-370\]", "storage kind not on the part (URAM)"),
    (r"\[HLS 214-157\]", "top function not found"),
    (r"\[HLS 214-139\]", "recursion"),
    (r"\[HLS 200-70\] Cannot find any design unit", "no design unit"),
    (r"\[HLS 207-", "C/C++ front-end error"),
    (r"\[HLS 200-70\]|\[HLS 200-1715\]", "Vitis internal synthesis failure"),
    (r"\[HLS 214-", "unsupported construct"),
]


def failure_class(note: str) -> str:
    for pattern, name in FAILURE_CLASSES:
        if re.search(pattern, note or ""):
            return name
    return "other"


def merge(into: dict, src: dict):
    """Return (merged, added keys, kept keys with equal cache keys, conflicts [(key, into, src)])."""
    merged = dict(into)
    added, same, conflicts = [], [], []
    for k, r in src.items():
        if k not in into:
            merged[k] = r
            added.append(k)
        elif into[k].get("key") == r.get("key"):
            same.append(k)
        else:
            conflicts.append((k, into[k].get("key"), r.get("key")))
    return merged, added, same, conflicts


def dataset_table(entries: dict, catalogue_keys: list[str] | None) -> str:
    per = defaultdict(Counter)
    fail_classes = defaultdict(Counter)
    keys = catalogue_keys if catalogue_keys is not None else list(entries)
    for k in keys:
        ds = k.split("/", 1)[0]
        per[ds]["designs"] += 1
        r = entries.get(k)
        if r is None:
            per[ds]["unsynthesised"] += 1
        elif r.get("status") == "ok":
            per[ds]["ok"] += 1
        elif "timeout" in (r.get("status") or ""):
            per[ds]["timeout"] += 1
        else:
            per[ds]["failed"] += 1
            fail_classes[ds][failure_class(r.get("note", ""))] += 1
    rows = ["| dataset | designs | Vitis ok | failed (by class) | timeout | unsynthesised |",
            "|---|---:|---:|---|---:|---:|"]
    tot = Counter()
    for ds in sorted(per):
        c = per[ds]
        tot.update(c)
        fc = ", ".join(f"{n} {name}" for name, n in fail_classes[ds].most_common())
        rows.append(f"| {ds} | {c['designs']} | {c['ok']} | {c['failed']}{' (' + fc + ')' if fc else ''} "
                    f"| {c['timeout']} | {c['unsynthesised']} |")
    rows.append(f"| TOTAL | {tot['designs']} | {tot['ok']} | {tot['failed']} | {tot['timeout']} "
                f"| {tot['unsynthesised']} |")
    return "\n".join(rows)


def check_heldout_parity(src: str, into: str):
    """Held-out ground truth never shares a file with the training one, nor one held-out set's with another's
    (hls-doc/heldout.md, heldout2.md): both files' names name the same held-out set ('heldout', 'heldout2'), or
    neither names one (the rule of common.heldout_out_path).  Returns that set, or None for training files."""
    hs, hi = C.heldout_set_of_name(Path(src).name), C.heldout_set_of_name(Path(into).name)
    if hs != hi or hs == "?":
        raise SystemExit(f"refusing to merge {repr(hs) + ' held-out' if hs else 'training'} results {src} into "
                         f"{repr(hi) + ' held-out' if hi else 'training'} file {into}: held-out and training "
                         "results, and the results of different held-out sets, are kept in separate files "
                         "(hls-doc/heldout.md)")
    return hs


def check_heldout_keys(entries: dict, path: str, heldout):
    """Every entry of a held-out file is a design of its held-out set (dataset heldout-* / heldout2-*) and no
    entry of a training file is a held-out one; refuses a file that mixes them."""
    wrong = sorted(k for k in entries if not k.startswith("_") and C.heldout_set_of_key(k) != (heldout or None))
    if wrong:
        raise SystemExit(f"{path}: {len(wrong)} entries of another set in a "
                         f"{repr(heldout) + ' held-out' if heldout else 'training'} file (e.g. {wrong[0]}); "
                         "refusing to merge (hls-doc/heldout.md)")


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--from", dest="src", required=True, help="summary JSON to merge in")
    ap.add_argument("--into", default=str(C.RESULTS_DIR / "vitis.json"), help="summary JSON to extend")
    ap.add_argument("--dry-run", action="store_true", help="report only, write nothing")
    ap.add_argument("--no-catalog", action="store_true",
                    help="do not load the design catalogue for the per-dataset table")
    a = ap.parse_args(argv)
    heldout = check_heldout_parity(a.src, a.into)
    import run_vitis as RV               # noqa: E402  (its summary lock)
    with RV.file_lock(a.into + ".lock"):
        into = C.load_json(a.into, {}) or {}
        src = C.load_json(a.src, {}) or {}
        check_heldout_keys(src, a.src, heldout)
        check_heldout_keys(into, a.into, heldout)
        merged, added, same, conflicts = merge(into, src)
        if not a.dry_run:
            C.dump_json(merged, a.into)
    print(f"{a.into}: {len(into)} entries; {a.src}: {len(src)} entries")
    print(f"added {len(added)}, in both with the same cache key {len(same)}, "
          f"in both with different cache keys {len(conflicts)} (target kept)"
          f"{' [dry run, nothing written]' if a.dry_run else f' -> {len(merged)} entries'}")
    for k, ki, ks in conflicts:
        print(f"  conflict {k}: kept {ki}, not merged {ks}")
    catalogue_keys = None
    if not a.no_catalog:
        import designs as D              # noqa: E402
        catalogue_keys = [C.design_key(d) for d in D.load_designs(catalog=heldout or None)
                          if d.get("sources")]
        stale = sorted(k for k in merged if k not in set(catalogue_keys))
        if stale:
            print(f"entries for designs the catalogue does not have ({len(stale)}): {', '.join(stale)}")
    print(dataset_table(merged, catalogue_keys))
    return 0


if __name__ == "__main__":
    sys.exit(main())
