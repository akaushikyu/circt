#!/usr/bin/env python3
"""Write the hls-est vs Vitis comparison as CSV files into hls-doc/.

    python3 make_compare_csv.py --hlsest <run .json> [--out-dir ../../hls-doc]

Writes comparison.csv (one row per design) and comparison-summary.csv (one row per dataset plus
ALL, followed by key/value rows describing the run). Every number is read from results/vitis.json
(Vitis 2025.1 csynth, td=off) and the hls-est run JSON; nothing is typed in by hand.
"""
import argparse
import csv
import statistics
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402
from compare import compare_one, summarize  # noqa: E402


BAND_OVER = 0.15   # Peter's goal (2026-10-10): exact, or an over-count of at most 15 % of the Vitis value


def band(vitis, est):
    """Classify one design against the goal band: 'exact', 'over<=15%', 'over>15%', 'under', or '' if not compared."""
    if vitis is None or est is None:
        return ""
    if est == vitis:
        return "exact"
    if est > vitis:
        return "over<=15%" if est <= vitis * (1 + BAND_OVER) else "over>15%"
    return "under"


def row_band(r):
    """The goal band of one comparison row, empty unless the row is compared: a row whose Vitis entry was
    synthesised from other sources ('sources differ') carries both totals but is not a comparison, so it
    must not count towards the goal band (the summary counts compared rows only)."""
    return band(r["vitis_bram"], r["hlsest_bram"]) if r["status"] == "compared" else ""


def band_counts(compared):
    b = [band(r["vitis_bram"], r["hlsest_bram"]) for r in compared]
    inb = sum(1 for x in b if x in ("exact", "over<=15%"))
    return [inb, b.count("over<=15%"), b.count("over>15%"), b.count("under"),
            round(100 * inb / len(compared), 1) if compared else ""]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--vitis", default=str(C.RESULTS_DIR / "vitis.json"))
    ap.add_argument("--hlsest", required=True, help="hls-est run JSON (run_hlsest.py --out)")
    ap.add_argument("--out-dir", default=str(C.HERE.parent.parent / "hls-doc"))
    a = ap.parse_args()
    V = C.load_json(a.vitis, {}) or {}
    H = C.load_json(a.hlsest, {}) or {}
    meta = H.pop("_meta", {})
    keys = sorted(set(V) | set(H))
    rows = [compare_one(k, V.get(k), H.get(k)) for k in keys]
    out = Path(a.out_dir)
    out.mkdir(parents=True, exist_ok=True)

    with open(out / "comparison.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["dataset", "benchmark", "vitis_bram_18k", "hlsest_bram_18k", "diff_hlsest_minus_vitis", "abs_diff",
                    "exact", "goal_band", "comparison_status", "vitis_status", "hlsest_status", "largest_array_differences"])
        for r in rows:
            worst = sorted((x for x in r.get("arrays", []) if x.get("diff")), key=lambda x: -abs(x["diff"]))[:3]
            w.writerow([r["dataset"], r["benchmark"], r["vitis_bram"], r["hlsest_bram"], r["diff"],
                        abs(r["diff"]) if r["diff"] is not None else None, r["exact"], row_band(r), r["status"],
                        r["vitis_status"], r["hlsest_status"],
                        "; ".join(f"{x['name']}: hls-est {x['hlsest_bram']} vs Vitis {x['vitis_bram']}" for x in worst)])

    s = summarize(rows)
    with open(out / "comparison-summary.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["dataset", "designs", "with_vitis_result", "compared", "exact", "exact_pct_of_compared",
                    "total_abs_err", "mean_abs_err", "median_abs_err", "hlsest_failed_or_not_run", "vitis_failed",
                    "in_goal_band", "over_le_15pct", "over_gt_15pct", "under", "in_goal_band_pct_of_compared"])
        def line(name, rs):
            c = [r for r in rs if r["status"] == "compared"]
            errs = [abs(r["diff"]) for r in c]
            w.writerow([name, len(rs), sum(1 for r in rs if r["vitis_status"] == "ok"), len(c),
                        sum(1 for r in c if r["exact"]), round(100 * sum(1 for r in c if r["exact"]) / len(c), 1) if c else "",
                        sum(errs), round(statistics.mean(errs), 1) if errs else "", statistics.median(errs) if errs else "",
                        sum(1 for r in rs if r["status"] == "hls-est missing"), sum(1 for r in rs if r["status"] == "vitis missing"),
                        *band_counts(c)])
        for ds in sorted(s["per_dataset"]):
            line(ds, [r for r in rows if r["dataset"] == ds])
        line("ALL", rows)
        w.writerow([])
        w.writerow(["run_setting", "value"])
        for k, v in [("generated", time.strftime("%Y-%m-%d %H:%M")), ("generator", "tools/hls-est-validate/make_compare_csv.py"),
                     ("hls-est run json", a.hlsest), ("hls-est git", meta.get("hls_est_git")), ("hls-est binary", meta.get("hls_est")),
                     ("pipeline", meta.get("pipeline")), ("shim", meta.get("shim")), ("cgeist", meta.get("cgeist")),
                     ("cgeist md5", meta.get("cgeist_md5")), ("mlir reused from", meta.get("mlir_from")),
                     ("vitis", "2025.1 csynth, " + C.PART + ", " + C.CLOCK + ", " + "; ".join(C.EXTRA_HLS_CFG)),
                     ("note", "designs absent from the run are listed with comparison_status 'hls-est missing'; designs without a "
                              "Vitis result are 'vitis missing' (excluded, see hls-est-results.xlsx 'excluded designs')")]:
            w.writerow([k, v])
    print(f"wrote {out/'comparison.csv'} ({len(rows)} rows) and {out/'comparison-summary.csv'}")
    print(f"ALL: compared {s['compared']}, exact {s['exact']}, |err| {s['total_abs_error']}")
    allc = [r for r in rows if r["status"] == "compared"]
    inb, le, gt, un, pct = band_counts(allc)
    print(f"goal band (exact or over-count <= 15%): {inb}/{len(allc)} ({pct}%); over<=15%: {le}, over>15%: {gt}, under: {un}")
    for ds, d in sorted(s["per_dataset"].items()):
        print(f"  {ds:22s} designs {d['designs']:3d} compared {d['compared']:3d} exact {d['exact']:3d} |err| {d['abs_error']:6d}")


if __name__ == "__main__":
    main()
