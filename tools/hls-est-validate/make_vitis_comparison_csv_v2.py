#!/usr/bin/env python3
"""hls-doc/hls-est-vs-vitis-v2.csv: hls-est-vs-vitis.csv plus our side of DSP / FF / LUT.

Joins, on (dataset, benchmark), the two generated tables
  hls-doc/hls-est-vs-vitis.csv      (make_vitis_comparison_csv.py: Vitis totals, hls-est BRAM prediction)
  hls-doc/circt-synth-vs-vitis.csv  (make_circt_synth_csv.py: circt-synth counts of the RTL back end's netlist)
and appends after the v1 columns:
  DSP (prediction)          empty: hls-est has no DSP model yet (Phase 6, hls-doc/design/phase6-plan.md)
  Multipliers (our RTL)     comb.mul ops of the word-level netlist: the DSP candidates (CIRCT maps them to LUTs)
  LUT (our RTL)             circt-synth --lower-to-k-lut=6 LUT6 count
  FF (our RTL)              circt-synth register bits
  LUT ratio, FF ratio       ours / Vitis
  RTL status                the RTL stage reached and the circt-synth status, or why there is no netlist
The LUT / FF columns count hls-est's own generated hardware, not a prediction of Vitis (float units and RAMs
are external modules and not counted). Regenerate both inputs first to refresh them.

Usage: python3 make_vitis_comparison_csv_v2.py [--v1 <csv>] [--rtl <csv>] [--out <csv>]
"""

import argparse
import csv
from pathlib import Path

HLS_DOC = Path(__file__).resolve().parent.parent.parent / "hls-doc"
EXTRA = ["DSP (prediction)", "Multipliers (our RTL)", "LUT (our RTL)", "FF (our RTL)",
         "LUT ratio (ours / Vitis)", "FF ratio (ours / Vitis)", "RTL status"]


def rtl_status(row):
    if not row:
        return "no RTL coverage record"
    if row["circt-synth status"] == "ok":
        return "ok"
    note = row.get("Note", "")
    return f'{row["circt-synth status"]} (stage {row["RTL stage reached"]})' + (f": {note}" if note else "")


def extra_columns(row):
    if not row:
        return ["", "", "", "", "", "", rtl_status(row)]
    return ["", row["comb.mul ops"], row["circt-synth LUT6"], row["circt-synth FF bits"],
            row["LUT ratio (circt-synth / Vitis)"], row["FF ratio (circt-synth / Vitis)"], rtl_status(row)]


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--v1", default=HLS_DOC / "hls-est-vs-vitis.csv")
    ap.add_argument("--rtl", default=HLS_DOC / "circt-synth-vs-vitis.csv")
    ap.add_argument("--out", default=HLS_DOC / "hls-est-vs-vitis-v2.csv")
    args = ap.parse_args()
    with open(args.v1, newline="") as f:
        reader = csv.reader(f)
        header = next(reader)
        v1 = list(reader)
    with open(args.rtl, newline="") as f:
        rtl = {(r["dataset"], r["benchmark"]): r for r in csv.DictReader(f)}
    with open(args.out, "w", newline="") as f:
        writer = csv.writer(f, lineterminator="\n")
        writer.writerow(header + EXTRA)
        for row in v1:
            writer.writerow(row + extra_columns(rtl.get((row[0], row[1]))))
    print(f"{args.out}: {len(v1)} designs, {sum(1 for r in v1 if (r[0], r[1]) in rtl)} with an RTL record")


if __name__ == "__main__":
    main()
