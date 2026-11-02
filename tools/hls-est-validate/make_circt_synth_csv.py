#!/usr/bin/env python3
"""hls-doc/circt-synth-vs-vitis.csv: CIRCT's own LUT / FF counts of the RTL back end's netlists next to Vitis.

For every design of an RTL coverage run (tools/rtl-backend/coverage.py on branch rtl-backend) whose
hw/comb/seq netlist (<top>.hw.mlir next to the .sv) exists, runs circt-synth --lower-to-k-lut=6 and counts
  circt-synth LUT6     comb.truth_table ops after the mapping
  circt-synth FF bits  bits of seq.firreg / seq.compreg after the mapping
  comb.mul ops / bits  multipliers of the word-level netlist (DSP candidates: CIRCT maps them to LUTs)
  external instances   instances of external modules (HardFloat float units, RAM blocks), whose LUTs and
                       FFs are not counted
Designs without Verilog get the coverage run's reason. These counts describe hls-est's own RTL, not a
prediction of Vitis' csynth DSP / FF / LUT (Peter, 2026-10-23).

Usage: python3 make_circt_synth_csv.py --coverage <cov_final.json> [--vitis results/vitis.json]
                                       [--circt-synth <bin>] [--sweep <json cache>] [--out <csv>] [-j 3]
Each circt-synth runs under prlimit (data 6 GB, no core dump) with a 600 s timeout.
"""

import argparse
import csv
import json
import os
import re
import subprocess
import tempfile
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
LIMIT = ["prlimit", "--core=1", "--data=6000000000"]
TIMEOUT_S = 600
HEADER = ["dataset", "benchmark", "Vitis DSP", "Vitis FF", "Vitis LUT", "Vitis BRAM_18K",
          "RTL stage reached", "circt-synth status", "circt-synth LUT6", "circt-synth FF bits",
          "comb.mul ops", "comb.mul total bits",
          "external module instances (float units, RAMs; contents not counted)",
          "LUT ratio (circt-synth / Vitis)", "FF ratio (circt-synth / Vitis)", "Note"]


def word_level_counts(text):
    """Multipliers and external-module instances of the hw/comb/seq netlist."""
    muls = [int(w) for w in re.findall(r"comb\.mul [^:]*: i(\d+)", text)]
    externs = set(re.findall(r"hw\.module\.extern @([\w$.]+)", text))
    instances = re.findall(r"hw\.instance \"[^\"]*\" @([\w$.]+)", text)
    return {"muls": len(muls), "mul_bits": sum(muls),
            "extern": sum(1 for name in instances if name in externs)}


def top_module(text):
    """The module no other module instantiates (the last one if several)."""
    modules = re.findall(r"hw\.module @([\w$.]+)", text)
    used = set(re.findall(r"hw\.instance \"[^\"]*\" @([\w$.]+)", text))
    tops = [m for m in modules if m not in used]
    return tops[-1] if tops else (modules[-1] if modules else None)


def synth_one(synth, key, sv):
    """circt-synth one design; returns its counts and status."""
    out = {"key": key}
    hw = sv[:-3] + ".hw.mlir" if sv else None
    if not hw or not os.path.exists(hw):
        out["status"] = "no hw.mlir"
        return out
    text = open(hw, errors="replace").read()
    out.update(word_level_counts(text))
    with tempfile.NamedTemporaryFile(suffix=".mlir") as lut:
        try:
            r = subprocess.run(LIMIT + [synth, hw, "--top", top_module(text), "--lower-to-k-lut=6",
                                        "-o", lut.name],
                               capture_output=True, text=True, timeout=TIMEOUT_S, stdin=subprocess.DEVNULL)
        except subprocess.TimeoutExpired:
            out["status"] = f"timeout {TIMEOUT_S}s"
            return out
        if r.returncode:
            out["status"] = "synth error: " + (r.stderr.strip().splitlines() or ["?"])[0][:200]
            return out
        mapped = open(lut.name, errors="replace").read()
    out["luts"] = len(re.findall(r"= comb\.truth_table ", mapped))
    out["ff"] = sum(int(w) for w in re.findall(r"seq\.(?:firreg|compreg)[^\n]*: i(\d+)\s*$", mapped, re.M))
    out["status"] = "ok"
    return out


def synth_error_note(status):
    if "out of memory" in status:
        return "circt-synth ran out of the 6 GB cap"
    if "CombOps" in status:
        return "circt-synth crashed (upstream CombOps assertion)"
    return "circt-synth rejected the netlist"


def ratio(ours, vitis):
    return f"{ours / vitis:.2f}" if isinstance(ours, int) and vitis else ""


def csv_row(key, record, sweep, vitis):
    rtl = record["rtl"]
    result = vitis.get(key) or {}
    totals = result.get("totals", {}) if result.get("status") == "ok" else {}
    stage = rtl.get("stage_reached", "?")
    notes = []
    if stage != "verilog":
        status = "not run: no Verilog"
        why = rtl.get("cause") or rtl.get("diag") or ""
        notes.append(f"RTL back end stops at {stage}" + (f": {why[:160]}" if why else ""))
        counts = {}
    else:
        counts = sweep.get(key, {"status": "missing"})
        status = counts["status"]
        if status.startswith("synth error"):
            notes.append(synth_error_note(status))
            status = "synth error"
    if counts.get("extern"):
        notes.append("float units / RAMs are external: their LUTs and FFs are not counted")
    if not totals:
        notes.append(f"no Vitis result ({str(result.get('status', 'no run'))[:60]})")
    dataset, benchmark = record.get("dataset"), record.get("benchmark")
    return [dataset, benchmark, totals.get("DSP", ""), totals.get("FF", ""), totals.get("LUT", ""),
            totals.get("BRAM", ""), stage, status, counts.get("luts", ""), counts.get("ff", ""),
            counts.get("muls", ""), counts.get("mul_bits", ""), counts.get("extern", ""),
            ratio(counts.get("luts"), totals.get("LUT")), ratio(counts.get("ff"), totals.get("FF")),
            "; ".join(notes)]


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--coverage", required=True, help="cov_final.json of an RTL coverage run")
    ap.add_argument("--vitis", default=HERE / "results/vitis.json")
    ap.add_argument("--circt-synth", default=os.path.expanduser("~/rtlspike/build/bin/circt-synth"))
    ap.add_argument("--sweep", help="JSON cache of the circt-synth counts: reused if it exists, else written")
    ap.add_argument("--out", default=HERE.parent.parent / "hls-doc/circt-synth-vs-vitis.csv")
    ap.add_argument("-j", type=int, default=3)
    args = ap.parse_args()
    coverage = json.load(open(args.coverage))
    coverage.pop("_meta", None)
    vitis = json.load(open(args.vitis))
    if args.sweep and os.path.exists(args.sweep):
        sweep = {r["key"]: r for r in json.load(open(args.sweep))}
    else:
        todo = [(k, r["rtl"].get("sv")) for k, r in coverage.items()
                if r["rtl"].get("stage_reached") == "verilog"]
        with ThreadPoolExecutor(args.j) as pool:
            results = list(pool.map(lambda kv: synth_one(args.circt_synth, *kv), todo))
        sweep = {r["key"]: r for r in results}
        if args.sweep:
            json.dump(results, open(args.sweep, "w"), indent=1)
    rows = [csv_row(k, r, sweep, vitis) for k, r in sorted(coverage.items())]
    with open(args.out, "w", newline="") as f:
        writer = csv.writer(f, lineterminator="\n")
        writer.writerow(HEADER)
        writer.writerows(rows)
    print(f"{args.out}: {len(rows)} designs, " +
          ", ".join(f"{n} {s}" for s, n in Counter(r[7] for r in rows).most_common()))


if __name__ == "__main__":
    main()
