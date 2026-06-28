#!/usr/bin/env python3
"""Build hls-est-results.xlsx from the harness results (openpyxl).

    python3 make_sheet.py [--vitis results/vitis.json] [--hlsest results/hlsest.json]
                          [--compare results/compare.json] [--experiments experiments/results.csv]
                          [--diagnoses diagnoses.json] [--out hls-est-results.xlsx]

Sheet 'results' has exactly the columns required by CLAUDE.md:
  dataset | benchmark | BRAM | DSP | FF | LUT | BRAM_util_pct | DSP_util_pct | FF_util_pct |
  LUT_util_pct | BRAM (prediction, shim)
Every number is copied from a parsed tool output; failures are written as text.
"""
import argparse
import csv
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

try:
    from openpyxl import Workbook
    from openpyxl.styles import Font, PatternFill
    from openpyxl.utils import get_column_letter
except ImportError:  # pragma: no cover
    print("pip install --user openpyxl", file=sys.stderr)
    raise

COLS = ["dataset", "benchmark", "BRAM", "DSP", "FF", "LUT", "BRAM_util_pct", "DSP_util_pct",
        "FF_util_pct", "LUT_util_pct", "BRAM (prediction, shim)"]


def prediction_cell(h):
    if not h:
        return "hls-est: not run"
    st = h.get("status", "")
    if st == "ok" and h.get("total_bram") is not None:
        return h["total_bram"]
    return st


def write_table(ws, header, rows, widths=None):
    ws.append(header)
    for c in ws[1]:
        c.font = Font(bold=True)
    for r in rows:
        ws.append(r)
    ws.freeze_panes = "A2"
    for i, h in enumerate(header, 1):
        w = max([len(str(h))] + [len(str(r[i - 1])) for r in rows if i - 1 < len(r)][:500]) + 2
        ws.column_dimensions[get_column_letter(i)].width = min(max(w, 8), 60)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--vitis", default=str(C.RESULTS_DIR / "vitis.json"))
    ap.add_argument("--hlsest", default=str(C.RESULTS_DIR / "hlsest.json"))
    ap.add_argument("--compare", default=str(C.RESULTS_DIR / "compare.json"))
    ap.add_argument("--experiments", default=str(C.HERE / "experiments" / "results.csv"))
    ap.add_argument("--diagnoses", default=str(C.HERE / "diagnoses.json"))
    ap.add_argument("--out", default=str(C.HERE / "hls-est-results.xlsx"))
    args = ap.parse_args()

    V = C.load_json(args.vitis, {}) or {}
    H = C.load_json(args.hlsest, {}) or {}
    meta = H.get("_meta", {})
    CMP = C.load_json(args.compare, {}) or {}
    diags = C.load_json(args.diagnoses, {}) or {}
    keys = sorted(set(V) | set(k for k in H if k != "_meta"))

    wb = Workbook()
    ws = wb.active
    ws.title = "results"
    rows = []
    for k in keys:
        ds, bm = k.split("/", 1)
        v, h = V.get(k), H.get(k)
        if v and v.get("status") == "ok":
            t = v.get("totals", {})
            vit = [t.get("BRAM"), t.get("DSP"), t.get("FF"), t.get("LUT"), t.get("BRAM_util_pct"),
                   t.get("DSP_util_pct"), t.get("FF_util_pct"), t.get("LUT_util_pct")]
            pred = prediction_cell(h)
        else:
            vit = [None] * 8
            why = (v or {}).get("status", "not run")
            note = (v or {}).get("note", "")
            pred = f"vitis failed: {why}" + (f" ({note})" if note else "")
        rows.append([ds, bm, *vit, pred])
    write_table(ws, COLS, rows)
    red = PatternFill("solid", fgColor="FFC7CE")
    green = PatternFill("solid", fgColor="C6EFCE")
    for i, r in enumerate(rows, 2):
        if isinstance(r[2], (int, float)) and isinstance(r[10], (int, float)):
            ws.cell(row=i, column=11).fill = green if r[2] == r[10] else red

    # ---- per-array comparison ----
    wa = wb.create_sheet("arrays")
    arows = []
    for r in CMP.get("rows", []):
        for a in r.get("arrays", []):
            arows.append([r["dataset"], r["benchmark"], a["name"], a["vitis_bram"], a["hlsest_bram"], a["diff"],
                          a["vitis_words"], a["vitis_bits"], a["vitis_banks"], a["vitis_core"],
                          a["hlsest_kind"], a["hlsest_status"], a["vitis_modules"]])
    write_table(wa, ["dataset", "benchmark", "array", "vitis BRAM_18K", "hls-est BRAM", "diff (hls-est - vitis)",
                     "vitis words", "vitis bits", "vitis banks", "vitis core", "hls-est RAM type",
                     "hls-est status", "vitis modules"], arows)

    # ---- mismatches with diagnosed cause ----
    wm = wb.create_sheet("mismatches")
    mrows = []
    for r in sorted(CMP.get("rows", []), key=lambda r: -abs(r.get("diff") or 0)):
        if r.get("status") != "compared" or r.get("exact"):
            continue
        key = r["key"]
        d = diags.get(key, {})
        worst = sorted(r.get("arrays", []), key=lambda a: -abs(a.get("diff") or 0))[:3]
        mrows.append([r["dataset"], r["benchmark"], r["vitis_bram"], r["hlsest_bram"], r["diff"],
                      "; ".join(f"{a['name']}:{a['hlsest_bram']} vs {a['vitis_bram']}" for a in worst if a.get("diff")),
                      d.get("cause", "unexplained"), d.get("evidence", ""), d.get("status", "")])
    write_table(wm, ["dataset", "benchmark", "vitis BRAM", "hls-est BRAM", "diff", "largest array diffs",
                     "diagnosed cause", "evidence", "fix status"], mrows)

    # ---- failures ----
    wf = wb.create_sheet("failures")
    frows = []
    for k in keys:
        v, h = V.get(k), H.get(k)
        vs, hs = (v or {}).get("status", "not run"), (h or {}).get("status", "not run")
        if vs != "ok" or hs != "ok":
            frows.append([*k.split("/", 1), vs, (v or {}).get("note", ""), hs, (h or {}).get("note", ""),
                          (h or {}).get("cgeist_status", "")])
    write_table(wf, ["dataset", "benchmark", "vitis status", "vitis note", "hls-est status", "hls-est note",
                     "cgeist status"], frows)

    # ---- run configuration ----
    wc = wb.create_sheet("run config")
    vers = sorted({(v or {}).get("vitis_version") for v in V.values() if v and v.get("vitis_version")})
    cfg = [["part", C.PART], ["clock", C.CLOCK], ["flow_target", C.FLOW_TARGET],
           ["extra hls config", "; ".join(C.EXTRA_HLS_CFG)], ["Vitis version(s)", ", ".join(map(str, vers)) or C.VITIS_VERSION],
           ["hls-est git hash", meta.get("hls_est_git", "")], ["hls-est pipeline", meta.get("pipeline", "")],
           ["hls-est timeout (s)", meta.get("timeout", "")], ["shim include dir", meta.get("shim", "")],
           ["hls-est binary", meta.get("hls_est", "")], ["designs", len(keys)],
           ["exact matches", CMP.get("summary", {}).get("exact", "")],
           ["compared", CMP.get("summary", {}).get("compared", "")],
           ["total |BRAM error|", CMP.get("summary", {}).get("total_abs_error", "")]]
    write_table(wc, ["setting", "value"], cfg)

    # ---- pipeline experiments ----
    we = wb.create_sheet("pipeline experiments")
    erows, hdr = [], ["(no experiments/results.csv yet)"]
    if Path(args.experiments).exists():
        with open(args.experiments) as f:
            rd = csv.reader(f)
            hdr = next(rd)
            for row in rd:
                erows.append([try_num(x) for x in row])
    write_table(we, hdr, erows)

    wb.save(args.out)
    print(f"wrote {args.out}: {len(rows)} result rows, {len(arows)} array rows, {len(mrows)} mismatches, "
          f"{len(frows)} failures, {len(erows)} experiment rows")


def try_num(x):
    try:
        return int(x)
    except (ValueError, TypeError):
        try:
            return float(x)
        except (ValueError, TypeError):
            return x


if __name__ == "__main__":
    main()
