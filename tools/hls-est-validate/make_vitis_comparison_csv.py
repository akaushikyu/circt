#!/usr/bin/env python3
"""hls-doc/hls-est-vs-vitis.csv: Vitis 2025.1 csynth totals next to the hls-est BRAM prediction.

One row per design of results/comparison.csv (the newest catalogue comparison), joined with
results/vitis.json. Columns (Peter, 2026-10-15; the first eleven are CLAUDE.md's first-sheet
columns):
  dataset, benchmark, BRAM, DSP, FF, LUT, BRAM_util_pct, DSP_util_pct, FF_util_pct, LUT_util_pct
      the Vitis td=off csynth totals (empty when Vitis has no result);
  BRAM (prediction, shim)
      the hls-est BRAM_18K of the default pipeline, or why there is none
      ('vitis failed: ...', 'cgeist error: ...', 'hls-est timeout 120s', ...);
  Diff
      hls-est - Vitis BRAM_18K, empty when not compared.

Usage: python3 make_vitis_comparison_csv.py [--comparison results/comparison.csv]
                                             [--vitis results/vitis.json] [--out <csv>]
"""

import argparse
import csv
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
VITIS_COLUMNS = ("BRAM", "DSP", "FF", "LUT", "BRAM_util_pct", "DSP_util_pct", "FF_util_pct",
                 "LUT_util_pct")
HEADER = ["dataset", "benchmark", *VITIS_COLUMNS, "BRAM (prediction, shim)", "Diff"]


def prediction_cell(row, vitis_ok, vitis_status):
    """The hls-est number, or the reason there is no comparison."""
    predicted = row["hlsest_bram_18k"]
    if row["hlsest_status"] != "ok" or predicted == "":
        return row["hlsest_status"]
    if not vitis_ok:
        return f"vitis failed: {vitis_status}"
    return predicted


def build_rows(comparison, vitis):
    for row in comparison:
        result = vitis.get(f"{row['dataset']}/{row['benchmark']}", {})
        vitis_status = result.get("status", "no run")
        vitis_ok = vitis_status == "ok"
        totals = result.get("totals", {}) if vitis_ok else {}
        compared = vitis_ok and row["hlsest_status"] == "ok" and row["hlsest_bram_18k"] != ""
        yield [row["dataset"], row["benchmark"], *[totals.get(c, "") for c in VITIS_COLUMNS],
               prediction_cell(row, vitis_ok, vitis_status),
               row["diff_hlsest_minus_vitis"] if compared else ""]


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--comparison", default=HERE / "results/comparison.csv")
    ap.add_argument("--vitis", default=HERE / "results/vitis.json")
    ap.add_argument("--out", default=HERE.parent.parent / "hls-doc/hls-est-vs-vitis.csv")
    args = ap.parse_args()
    comparison = list(csv.DictReader(open(args.comparison)))
    vitis = json.load(open(args.vitis))
    rows = list(build_rows(comparison, vitis))
    with open(args.out, "w", newline="") as f:
        writer = csv.writer(f, lineterminator="\n")
        writer.writerow(HEADER)
        writer.writerows(rows)
    diffs = [int(r[-1]) for r in rows if r[-1] != ""]
    vitis_bram = [int(r[2]) for r in rows if r[-1] != ""]
    in_goal = sum(0 <= d <= 0.15 * v for d, v in zip(diffs, vitis_bram))
    print(f"{args.out}: {len(rows)} designs, {len(diffs)} compared, "
          f"{sum(d == 0 for d in diffs)} exact, {in_goal} in goal, |err| {sum(map(abs, diffs))}")


if __name__ == "__main__":
    main()
