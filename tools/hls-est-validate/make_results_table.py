#!/usr/bin/env python3
"""Write the hls-est vs Vitis results table in Peter's format.

    python3 make_results_table.py --hlsest <run .json> [--out-dir results]

One row per design that has a Vitis td=off result AND an hls-est total; columns:
  dataset | benchmark | BRAM | DSP | FF | LUT | BRAM_util_pct | DSP_util_pct | FF_util_pct | LUT_util_pct |
  BRAM (prediction, shim) | Diff
Diff = (Vitis BRAM - predicted BRAM) / Vitis BRAM (negative = over-count). With Vitis BRAM 0 it is 0 when the
prediction is 0 and empty otherwise. Dataset names follow the earlier sheet: '<dataset>_xilinx', spector_hls as
spectorhls_xilinx. Writes results-table.tsv and results-table.xlsx; every number comes from results/vitis.json and
the hls-est run JSON.
"""
import argparse
import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

COLS = ["dataset", "benchmark", "BRAM", "DSP", "FF", "LUT", "BRAM_util_pct", "DSP_util_pct", "FF_util_pct",
        "LUT_util_pct", "BRAM (prediction, shim)", "Diff"]


def sheet_dataset(ds):
    return ds.replace("spector_hls", "spectorhls") + "_xilinx"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--vitis", default=str(C.RESULTS_DIR / "vitis.json"))
    ap.add_argument("--hlsest", required=True)
    # results/, not hls-doc/: hls-doc holds no CSV / TSV files (MEMOS decision #47)
    ap.add_argument("--out-dir", default=str(C.RESULTS_DIR))
    a = ap.parse_args()
    V = C.load_json(a.vitis, {}) or {}
    H = C.load_json(a.hlsest, {}) or {}
    meta = H.pop("_meta", {})
    rows = []
    for k in sorted(V):
        v, h = V[k], H.get(k)
        if v.get("status") != "ok" or not h or h.get("status") != "ok" or h.get("total_bram") is None:
            continue
        t = v.get("totals") or {}
        vb, pb = t.get("BRAM"), h["total_bram"]
        diff = (0 if pb == 0 else None) if not vb else (vb - pb) / vb
        ds, bm = k.split("/", 1)
        rows.append([sheet_dataset(ds), bm, vb, t.get("DSP"), t.get("FF"), t.get("LUT"), t.get("BRAM_util_pct"),
                     t.get("DSP_util_pct"), t.get("FF_util_pct"), t.get("LUT_util_pct"), pb, diff])
    out = Path(a.out_dir)
    with open(out / "results-table.tsv", "w", newline="") as f:
        w = csv.writer(f, delimiter="\t")
        w.writerow(COLS)
        for r in rows:
            w.writerow(["" if x is None else x for x in r])
    try:
        from openpyxl import Workbook
        from openpyxl.styles import Font
        wb = Workbook()
        ws = wb.active
        ws.title = "results"
        ws.append(COLS)
        for c in ws[1]:
            c.font = Font(bold=True)
        for r in rows:
            ws.append(r)
        for row in ws.iter_rows(min_row=2, min_col=12, max_col=12):
            for c in row:
                c.number_format = "0.0000"
        info = wb.create_sheet("run")
        for kv in [("hls-est run json", a.hlsest), ("hls-est git", meta.get("hls_est_git")), ("pipeline", meta.get("pipeline")),
                   ("shim", meta.get("shim")), ("cgeist md5", meta.get("cgeist_md5")),
                   ("Vitis", "2025.1 csynth, " + C.PART + ", " + C.CLOCK + ", " + "; ".join(C.EXTRA_HLS_CFG)),
                   ("rows", f"{len(rows)} designs with a Vitis result and an hls-est total"),
                   ("Diff", "(Vitis BRAM - predicted BRAM) / Vitis BRAM; negative = over-count")]:
            info.append(list(kv))
        wb.save(out / "results-table.xlsx")
    except ImportError:
        pass
    print(f"wrote {out/'results-table.tsv'} and .xlsx: {len(rows)} rows")


if __name__ == "__main__":
    main()
