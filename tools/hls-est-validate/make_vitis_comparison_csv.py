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
      hls-est - Vitis BRAM_18K, empty when not compared;
  hls-est time (s), Vitis csynth time (s)
      wall-clock seconds of the hls-est run (elapsed_s of the --hlsest result files; a later
      file overrides an earlier one, e.g. a no-timeout re-run of the designs that timed out)
      and of the Vitis csynth run (elapsed_s in results/vitis.json, kept from the original run
      for cached results); empty when there is no such run (Peter, 2026-10-20).

Usage: python3 make_vitis_comparison_csv.py [--comparison results/comparison.csv]
                                             [--vitis results/vitis.json] [--out <csv>]
                                             [--hlsest <run json> ...]
"""

import argparse
import csv
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
VITIS_COLUMNS = ("BRAM", "DSP", "FF", "LUT", "BRAM_util_pct", "DSP_util_pct", "FF_util_pct",
                 "LUT_util_pct")
HEADER = ["dataset", "benchmark", *VITIS_COLUMNS, "BRAM (prediction, shim)", "Diff",
          "hls-est time (s)", "Vitis csynth time (s)"]


def seconds(value):
    """A run's elapsed_s as a CSV cell (one decimal), or empty."""
    return f"{value:.1f}" if isinstance(value, (int, float)) else ""


def hlsest_times(paths):
    """{dataset/benchmark: elapsed_s} from hls-est result files; later files override."""
    times = {}
    for path in paths:
        for key, run in json.load(open(path)).items():
            if isinstance(run, dict) and "elapsed_s" in run:
                times[key] = run["elapsed_s"]
    return times


def prediction_cell(row, vitis_ok, vitis_status):
    """The hls-est number, or the reason there is no comparison."""
    predicted = row["hlsest_bram_18k"]
    if row["hlsest_status"] != "ok" or predicted == "":
        return row["hlsest_status"]
    if not vitis_ok:
        return f"vitis failed: {vitis_status}"
    return predicted


def build_rows(comparison, vitis, times):
    for row in comparison:
        key = f"{row['dataset']}/{row['benchmark']}"
        result = vitis.get(key, {})
        vitis_status = result.get("status", "no run")
        vitis_ok = vitis_status == "ok"
        totals = result.get("totals", {}) if vitis_ok else {}
        compared = vitis_ok and row["hlsest_status"] == "ok" and row["hlsest_bram_18k"] != ""
        yield [row["dataset"], row["benchmark"], *[totals.get(c, "") for c in VITIS_COLUMNS],
               prediction_cell(row, vitis_ok, vitis_status),
               row["diff_hlsest_minus_vitis"] if compared else "",
               seconds(times.get(key)), seconds(result.get("elapsed_s"))]


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--comparison", default=HERE / "results/comparison.csv")
    ap.add_argument("--vitis", default=HERE / "results/vitis.json")
    ap.add_argument("--out", default=HERE.parent.parent / "hls-doc/hls-est-vs-vitis.csv")
    ap.add_argument("--hlsest", nargs="*", default=[],
                    help="hls-est result files for the time column (later ones override)")
    args = ap.parse_args()
    comparison = list(csv.DictReader(open(args.comparison)))
    vitis = json.load(open(args.vitis))
    rows = list(build_rows(comparison, vitis, hlsest_times(args.hlsest)))
    with open(args.out, "w", newline="") as f:
        writer = csv.writer(f, lineterminator="\n")
        writer.writerow(HEADER)
        writer.writerows(rows)
    diff = HEADER.index("Diff")
    diffs = [int(r[diff]) for r in rows if r[diff] != ""]
    vitis_bram = [int(r[2]) for r in rows if r[diff] != ""]
    in_goal = sum(0 <= d <= 0.15 * v for d, v in zip(diffs, vitis_bram))
    print(f"{args.out}: {len(rows)} designs, {len(diffs)} compared, "
          f"{sum(d == 0 for d in diffs)} exact, {in_goal} in goal, |err| {sum(map(abs, diffs))}")


if __name__ == "__main__":
    main()
