#!/usr/bin/env python3
"""Build hls-est-results.xlsx: one workbook with the Vitis ground truth and the hls-est predictions.

    python3 make_sheet.py [--vitis results/vitis.json] [--hlsest <default-pipeline run .json>]
                          [--second <second run .json> [--second-label <name>]]
                          [--experiments experiments/results.csv]
                          [--diagnoses diagnoses.json] [--out hls-est-results.xlsx]

Sheets, in order:
  results               exactly the CLAUDE.md columns: dataset | benchmark | BRAM | DSP | FF | LUT |
                        BRAM_util_pct | DSP_util_pct | FF_util_pct | LUT_util_pct | BRAM (prediction, shim)
  pipeline comparison   Vitis BRAM next to the totals of the --hlsest run and of a second run (--second;
                        e.g. the previous default: split pipeline, scalar shim, no math costs). Each run's
                        column is labelled from that run's recorded configuration (_meta: pipeline, shim,
                        math costs, run id; run_label), unless --second-label names the second one
  per-array             one row per array: Vitis BRAM vs hls-est BRAM (default pipeline)
  mismatches            designs whose default prediction differs, largest |diff| first, with cause / O-number
  failures              designs where Vitis or hls-est produced no number, with the reason
  excluded designs      designs without Vitis ground truth, excluded from comparison, with the reason
  vitis designs         the ground truth for every design: totals, status, error text, top, cache dir
  vitis memories        the Vitis "* Memory:" rows (one per physical memory / bank row)
  vitis loops           the Vitis loop tables (pipelined, II, trip count, latency)
  vitis td=auto         secondary ground truth with syn.array_partition.throughput_driven=auto
  formula reconciliation  summary and miss rows of formula_reconcile.py (VITIS_NOTES N8)
  pipeline experiments  experiments/results.csv
  run config            Vitis version, part, clock, td, shim, pipelines, hls-est / cgeist / hls-llvm-project commits
Every number is copied from a parsed tool output; a missing number is written as the failure text.
"""
import argparse
import re
import csv
import hashlib
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402
from compare import compare_one, summarize  # noqa: E402

from openpyxl import Workbook  # noqa: E402
from openpyxl.styles import Font, PatternFill  # noqa: E402
from openpyxl.utils import get_column_letter  # noqa: E402

COLS = ["dataset", "benchmark", "BRAM", "DSP", "FF", "LUT", "BRAM_util_pct", "DSP_util_pct",
        "FF_util_pct", "LUT_util_pct", "BRAM (prediction, shim)"]
GREEN = PatternFill("solid", fgColor="C6EFCE")
RED = PatternFill("solid", fgColor="FFC7CE")


def table(ws, header, rows):
    ws.append(header)
    for c in ws[1]:
        c.font = Font(bold=True)
    for r in rows:
        ws.append(r)
    ws.freeze_panes = "A2"
    if rows:
        ws.auto_filter.ref = ws.dimensions
    for i, h in enumerate(header, 1):
        vals = [len(str(r[i - 1])) for r in rows[:400] if i - 1 < len(r) and r[i - 1] is not None]
        w = max([len(str(h))] + vals) + 2
        ws.column_dimensions[get_column_letter(i)].width = min(max(w, 8), 60)


def num(x):
    try:
        return int(x)
    except (ValueError, TypeError):
        try:
            return float(x)
        except (ValueError, TypeError):
            return x


def prediction(h):
    if not h:
        return "hls-est: not run"
    if h.get("status") == "ok" and h.get("total_bram") is not None:
        return h["total_bram"]
    return h.get("status") or "hls-est: no result"


def vitis_ok(v):
    return bool(v) and v.get("status") == "ok"


def exclusion(v):
    """Why a design has no Vitis ground truth: (category, reason), derived from the Vitis
    status and error text only (no design names). Peter, 2026-10-10: exclude these designs
    for now and record why in the spreadsheet."""
    if not v:
        return "not run", "Vitis was not run on this design"
    note = (v.get("note") or "").strip()
    st = v.get("status") or ""
    m = re.search(r"\[HLS 207-812\] '([^']+)' file not found", note)
    if m:
        return ("missing header", f"Vitis cannot compile the source: it includes '{m.group(1)}', "
                "which is not part of the dataset (vendor/host header)")
    if re.search(r"Impl=uram\w*.*not supported", note) or "[HLS 214-370]" in note:
        return ("URAM on Zynq-7000", "the source binds arrays to UltraRAM (bind_storage impl=uram); "
                "the xc7z020 part has no UltraRAM, so Vitis stops")
    if "timeout" in st:
        return ("Vitis timeout", f"Vitis csynth did not finish within the harness limit ({st})")
    first = note.splitlines()[0][:160] if note else ""
    return ("other Vitis failure", f"{st}" + (f": {first}" if first else ""))


def vitis_fail_text(v):
    cat, why = exclusion(v)
    return f"excluded ({cat}): {why}"


def git(repo, *a):
    try:
        return subprocess.run(["git", "-C", str(repo), *a], capture_output=True, text=True, timeout=30).stdout.strip()
    except Exception:
        return ""


def md5(path):
    try:
        h = hashlib.md5()
        with open(path, "rb") as f:
            for b in iter(lambda: f.read(1 << 20), b""):
                h.update(b)
        return h.hexdigest()
    except OSError:
        return ""


def color(ws, rows, vcol, pcol):
    for i, r in enumerate(rows, 2):
        v, p = r[vcol - 1], r[pcol - 1]
        if isinstance(v, (int, float)) and isinstance(p, (int, float)):
            ws.cell(row=i, column=pcol).fill = GREEN if v == p else RED


def pipeline_name(pipe):
    """A short name for a recorded pipeline string: the current default, the default before the split
    pass left it (common.SPLIT_PIPELINE), or the passes it has, with every option the string sets
    spelled out (a run that resets option defaults says which)."""
    if pipe == C.DEFAULT_PIPELINE:
        return "default pipeline"
    if pipe == C.SPLIT_PIPELINE:
        return "split pipeline"
    toks = pipe.split()
    base = "split pipeline" if any(t.startswith("--infer-vitis-split-array") for t in toks) else "pipeline"
    if " ".join(t.split("=", 1)[0] for t in toks) == C.DEFAULT_PIPELINE:
        base = "default pipeline"
    # "--pass=opt=v" contributes "opt=v"; a global flag "--flag=v" contributes "flag=v".
    opts = [t.split("=", 1)[1] if t.count("=") > 1 else t[2:] for t in toks if "=" in t]
    return base + (f" [{', '.join(opts)}]" if opts else "")


def run_label(meta, fallback):
    """Name of one run in the workbook, from its recorded configuration (_meta): pipeline name, shim
    (directory name), whether the math-core cost table was applied, and the run id when the meta has one."""
    meta = meta or {}
    pipe = meta.get("pipeline")
    if not pipe:
        return fallback
    parts = [pipeline_name(pipe)]
    if meta.get("shim"):
        parts.append(f"shim {Path(str(meta['shim'])).name}")
    if "math_costs_applied" in meta or "math_costs" in meta:
        parts.append("math costs" if meta.get("math_costs_applied", bool(meta.get("math_costs")))
                     else "no math costs")
    if meta.get("vitis_frontend") is False:
        parts.append("no Vitis front-end flags")
    label = ", ".join(parts)
    return label + (f" (run {meta['run_id']})" if meta.get("run_id") else "")


def second_label(meta, given=None):
    """Name of the second run in the workbook: --second-label, else run_label of its _meta."""
    return given or run_label(meta, "second run")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--vitis", default=str(C.RESULTS_DIR / "vitis.json"))
    ap.add_argument("--hlsest", default=str(C.RESULTS_DIR / "hlsest.json"), help="default-pipeline run")
    ap.add_argument("--second", "--nosplit", dest="second", default=None,
                    help="a second run for the 'pipeline comparison' sheet, e.g. the split pipeline "
                         "(common.SPLIT_PIPELINE, the default before MEMOS M1). --nosplit is the old name, "
                         "from when the default had the split and this run was the one without it")
    ap.add_argument("--second-label", default=None,
                    help="name of the second run in the workbook (default: from its recorded pipeline)")
    ap.add_argument("--experiments", default=str(C.HERE / "experiments" / "results.csv"))
    ap.add_argument("--diagnoses", default=str(C.HERE / "diagnoses.json"))
    ap.add_argument("--out", default=str(C.HERE / "hls-est-results.xlsx"))
    a = ap.parse_args()

    V = C.load_json(a.vitis, {}) or {}
    H = C.load_json(a.hlsest, {}) or {}
    hmeta = H.pop("_meta", {})
    N = (C.load_json(a.second, {}) if a.second else {}) or {}
    nmeta = N.pop("_meta", {})
    nlabel = second_label(nmeta, a.second_label)
    hlabel = run_label(hmeta, "default run")
    if nlabel == hlabel:
        nlabel += " (second run)"
    diags = C.load_json(a.diagnoses, {}) or {}
    keys = sorted(set(V) | set(H) | set(N))
    cmp_rows = {k: compare_one(k, V.get(k), H.get(k)) for k in keys}
    summ = summarize(list(cmp_rows.values()))
    nsumm = summarize([compare_one(k, V.get(k), N.get(k)) for k in keys]) if N else {}

    wb = Workbook()
    # ---- results (CLAUDE.md columns, exactly) ----
    ws = wb.active
    ws.title = "results"
    rows = []
    for k in keys:
        ds, bm = k.split("/", 1)
        v = V.get(k)
        if vitis_ok(v):
            t = v.get("totals") or {}
            rows.append([ds, bm, t.get("BRAM"), t.get("DSP"), t.get("FF"), t.get("LUT"), t.get("BRAM_util_pct"),
                         t.get("DSP_util_pct"), t.get("FF_util_pct"), t.get("LUT_util_pct"), prediction(H.get(k))])
        else:
            rows.append([ds, bm] + [None] * 8 + [vitis_fail_text(v)])
    table(ws, COLS, rows)
    color(ws, rows, 3, 11)

    # ---- pipeline comparison ----
    wn = wb.create_sheet("pipeline comparison")
    nrows = []
    for k in keys:
        ds, bm = k.split("/", 1)
        v = V.get(k)
        vb = (v.get("totals") or {}).get("BRAM") if vitis_ok(v) else vitis_fail_text(v)
        d = prediction(H.get(k))
        n = prediction(N.get(k)) if N else "second run not given (--second)"
        nrows.append([ds, bm, vb, d, (d - vb) if isinstance(d, int) and isinstance(vb, int) else None,
                      n, (n - vb) if isinstance(n, int) and isinstance(vb, int) else None])
    table(wn, ["dataset", "benchmark", "Vitis BRAM", hlabel, "diff (first run - Vitis)",
               nlabel, "diff (second run - Vitis)"], nrows)
    color(wn, nrows, 3, 4)
    color(wn, nrows, 3, 6)

    # ---- per-array (default pipeline) ----
    wa = wb.create_sheet("per-array")
    arows = []
    for k in keys:
        r = cmp_rows[k]
        for x in r.get("arrays", []):
            arows.append([r["dataset"], r["benchmark"], x["name"], x["vitis_bram"], x["hlsest_bram"], x["diff"],
                          x["vitis_words"], x["vitis_bits"], x["vitis_banks"], x["vitis_core"], x["hlsest_kind"],
                          x["hlsest_status"], x["vitis_modules"]])
    table(wa, ["dataset", "benchmark", "array", "Vitis BRAM_18K", "hls-est BRAM", "diff (hls-est - Vitis)",
               "Vitis words", "Vitis bits", "Vitis banks", "Vitis core", "hls-est RAM type", "hls-est status",
               "Vitis modules"], arows)

    # ---- mismatches ----
    wm = wb.create_sheet("mismatches")
    mrows = []
    for r in sorted(cmp_rows.values(), key=lambda r: -abs(r.get("diff") or 0)):
        if r.get("status") != "compared" or r.get("exact"):
            continue
        d = diags.get(r["key"], {})
        worst = sorted(r.get("arrays", []), key=lambda x: -abs(x.get("diff") or 0))[:4]
        mrows.append([r["dataset"], r["benchmark"], r["vitis_bram"], r["hlsest_bram"], r["diff"],
                      "; ".join(f"{x['name']}: {x['hlsest_bram']} vs {x['vitis_bram']}" for x in worst if x.get("diff")),
                      d.get("cause", "not yet diagnosed"), d.get("issue", ""), d.get("evidence", "")])
    table(wm, ["dataset", "benchmark", "Vitis BRAM", "hls-est BRAM", "diff", "largest array differences",
               "diagnosed cause", "open issue", "evidence"], mrows)

    # ---- failures ----
    wf = wb.create_sheet("failures")
    frows = []
    for k in keys:
        v, h = V.get(k), H.get(k)
        vs, hs = (v or {}).get("status", "not run"), (h or {}).get("status", "not run")
        if vs != "ok" or hs != "ok":
            frows.append([*k.split("/", 1), vs, ((v or {}).get("note") or "")[:300], hs,
                          ((h or {}).get("note") or (h or {}).get("error") or "")[:300]])
    table(wf, ["dataset", "benchmark", "Vitis status", "Vitis error", "hls-est status", "hls-est note"], frows)

    # ---- excluded designs (no Vitis ground truth) ----
    wx = wb.create_sheet("excluded designs")
    xrows = []
    for k in sorted(V):
        v = V[k]
        if vitis_ok(v):
            continue
        cat, why = exclusion(v)
        h = H.get(k)
        xrows.append([*k.split("/", 1), cat, why, ((v.get("note") or "").strip().splitlines() or [""])[0][:300],
                      prediction(h) if h else "hls-est: not run"])
    table(wx, ["dataset", "benchmark", "exclusion category", "why it is excluded", "Vitis error (first line)",
               "hls-est result (not compared)"], xrows)

    # ---- vitis designs / memories / loops ----
    wd = wb.create_sheet("vitis designs")
    drows, vmrows, lrows = [], [], []
    for k in sorted(V):
        v = V[k]
        t = v.get("totals") or {}
        ok = vitis_ok(v)
        mems = v.get("memories") or []
        drows.append([v.get("dataset"), v.get("benchmark"), v.get("status"), v.get("top"),
                      *[(t.get(x) if ok else None) for x in ("BRAM", "DSP", "FF", "LUT", "BRAM_util_pct",
                                                             "DSP_util_pct", "FF_util_pct", "LUT_util_pct")],
                      sum((m.get("bram") or 0) for m in mems) if ok else None, len(mems), v.get("elapsed_s"),
                      (v.get("note") or "")[:300], v.get("cache_dir")])
        for m in mems:
            vmrows.append([v.get("dataset"), v.get("benchmark"), m.get("module"), m.get("variable") or m.get("array"),
                           m.get("Memory"), m.get("core"), m.get("optype"), m.get("Words"), m.get("Bits"),
                           m.get("Banks"), m.get("BRAM_18K"), m.get("LUT"), m.get("URAM"), m.get("source")])
        for lp in v.get("loops") or []:
            lrows.append([v.get("dataset"), v.get("benchmark"), lp.get("module"), lp.get("name"), lp.get("pipelined"),
                          lp.get("ii_target"), lp.get("ii_achieved"), lp.get("trip_count"), lp.get("depth"),
                          lp.get("iter_latency"), lp.get("latency_min"), lp.get("latency_max")])
    table(wd, ["dataset", "benchmark", "Vitis status", "top", "BRAM_18K", "DSP", "FF", "LUT", "BRAM_util_pct",
               "DSP_util_pct", "FF_util_pct", "LUT_util_pct", "sum of memory-table BRAM", "memory rows",
               "csynth time (s)", "note / error", "cache dir"], drows)
    table(wb.create_sheet("vitis memories"), ["dataset", "benchmark", "module", "array", "memory instance", "core",
                                              "bound port type", "words", "bits", "banks", "BRAM_18K", "LUT", "URAM",
                                              "source"], vmrows)
    table(wb.create_sheet("vitis loops"), ["dataset", "benchmark", "module", "loop", "pipelined", "II target",
                                           "II achieved", "trip count", "depth", "iteration latency", "latency min",
                                           "latency max"], lrows)

    # ---- td=auto ----
    TDA = C.load_json(Path(a.vitis).with_name("vitis-tdauto.json"), {}) or {}
    if TDA:
        trows = []
        for k in sorted(set(V) | set(TDA)):
            o, x = V.get(k) or {}, TDA.get(k) or {}
            ob = (o.get("totals") or {}).get("BRAM") if vitis_ok(o) else None
            xb = (x.get("totals") or {}).get("BRAM") if vitis_ok(x) else None
            trows.append([*k.split("/", 1), ob, xb, (xb - ob) if ob is not None and xb is not None else None,
                          o.get("status", "not run"), x.get("status", "not run")])
        table(wb.create_sheet("vitis td=auto"), ["dataset", "benchmark", "BRAM (td=off, ground truth)",
                                                 "BRAM (td=auto)", "diff (auto - off)", "status td=off",
                                                 "status td=auto"], trows)

    # ---- formula reconciliation ----
    wr = wb.create_sheet("formula reconciliation")
    srows = []
    for name in ("formula_reconcile_summary.csv", "formula_reconcile.csv"):
        p = C.RESULTS_DIR / name
        if p.exists():
            with open(p) as f:
                rd = list(csv.reader(f))
            srows.append([f"== {name} ({len(rd) - 1} rows)"])
            srows.extend([[num(x) for x in r] for r in rd])
            srows.append([])
    table(wr, ["formula_reconcile.py output (VITIS_NOTES.md N8; MEMOS.md M4)"], srows or [["not generated"]])

    # ---- pipeline experiments ----
    we = wb.create_sheet("pipeline experiments")
    erows, hdr = [], ["(no experiments/results.csv yet)"]
    if Path(a.experiments).exists():
        with open(a.experiments) as f:
            rd = csv.reader(f)
            hdr = next(rd)
            erows = [[num(x) for x in r] for r in rd]
    table(we, hdr, erows)

    # ---- run config ----
    poly = Path(C.CGEIST).resolve().parents[2]
    vers = sorted({str(v.get("vitis_version")) for v in V.values() if v.get("vitis_version")})
    cfg = [
        ["generated", time.strftime("%Y-%m-%d %H:%M")],
        ["Vitis version", ", ".join(vers) + " (Windows install A:\\Vitis\\2025.1, run from WSL)"],
        ["part", C.PART], ["clock", C.CLOCK], ["flow_target", C.FLOW_TARGET],
        ["td (syn.array_partition.throughput_driven)", "off (ground truth); td=auto only on its own sheet"],
        ["extra hls config", "; ".join(C.EXTRA_HLS_CFG)],
        ["Vitis designs / with a result", f"{len(V)} / {sum(1 for v in V.values() if vitis_ok(v))}"],
        ["excluded designs (no Vitis ground truth; see 'excluded designs')",
         f"{sum(1 for v in V.values() if not vitis_ok(v))} - excluded from every comparison (Peter, 2026-10-10)"],
        ["shim", hmeta.get("shim", "")],
        [f"prediction column ({hlabel}): pipeline", hmeta.get("pipeline", "")],
        [f"second run ({nlabel}): pipeline", nmeta.get("pipeline", "")],
        ["top selection prefix", hmeta.get("top_passes", "--symbol-privatize=exclude=<top> --symbol-dce per design")],
        ["hls-est git hash (run)", hmeta.get("hls_est_git", "")],
        ["hls-est binary sha256 (run)", hmeta.get("hls_est_sha256", "")],
        ["hls-est timeout (s)", hmeta.get("timeout", "")],
        ["cgeist that produced the run's MLIR",
         (f"{hmeta.get('cgeist')} md5 {hmeta.get('cgeist_md5')} (Polygeist {hmeta.get('polygeist_head')})"
          if hmeta.get("cgeist_md5") else
          "not recorded by this run" + (f"; MLIR reused from {hmeta.get('mlir_from')}" if hmeta.get("mlir_from") else ""))],
        ["Polygeist HEAD when this sheet was generated", git(poly, "log", "-1", "--format=%h %s")],
        ["installed cgeist md5 when this sheet was generated", md5(C.CGEIST)],
        ["hls-llvm-project commit (formula source, N8)", "tag 2025.1 = 6ad94cf7d252 (worktree ~/hls-llvm-project-2025); "
         "~/hls-llvm-project main = " + git(Path.home() / "hls-llvm-project", "log", "-1", "--format=%h")],
        [f"prediction column ({hlabel}): compared / exact / total |err|",
         f"{summ.get('compared')} / {summ.get('exact')} / {summ.get('total_abs_error')}"],
        [f"second run ({nlabel}): compared / exact / total |err|",
         f"{nsumm.get('compared')} / {nsumm.get('exact')} / {nsumm.get('total_abs_error')}" if nsumm else ""],
    ]
    table(wb.create_sheet("run config"), ["setting", "value"], cfg)

    wb.save(a.out)
    print(f"wrote {a.out}: {len(rows)} designs, {len(arows)} array rows, {len(mrows)} mismatches, "
          f"{len(frows)} failures, {len(vmrows)} Vitis memory rows, {len(lrows)} Vitis loop rows; "
          f"default exact {summ.get('exact')}/{summ.get('compared')}"
          + (f", {nlabel} exact {nsumm.get('exact')}/{nsumm.get('compared')}" if nsumm else ""))


if __name__ == "__main__":
    main()
