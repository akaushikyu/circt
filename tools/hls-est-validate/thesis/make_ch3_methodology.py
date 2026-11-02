#!/usr/bin/env python3
"""Thesis chapter 3, "Inferring a closed compiler's decisions": the methodology.

    ~/hls-est-work/coord/scratch/thesis/venv/bin/python make_ch3_methodology.py [--newest <run.json>]

Writes hls-doc/thesis/03-methodology.md from templates/ch3_methodology.md.in, the tables
tables/ch3-{stages,config,optin,runs}.{md,tex} and the figures figures/ch3-experiment-runs.{pdf,png}
and figures/ch3-catalogue-progress.{pdf,png}.

Inputs (every number of the chapter is read from these): tools/hls-est-validate/results/vitis.json
(ground truth), results/vitis-tdauto.json (td=auto set), results/formula_reconcile_summary.csv, the
published catalogue runs listed in RUNS (run_hlsest.py result JSONs, re-compared here with
compare.compare_one against the current vitis.json), the ad-hoc kernel cache
~/hls-est-work/experiments/*/*/result.json, hls-doc/notes/{VITIS_NOTES,OPEN_ISSUES,MEMOS,CHANGELOG}.md,
~/hls-est-work/coord/scratch/reports/*.md (round reports, counted by name) and test/hls-est/Mirror/.
"""
import argparse
import collections
import csv
import datetime
import os
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ch34_lib as L  # noqa: E402
import common as C  # noqa: E402
from compare import compare_one  # noqa: E402
from make_compare_csv import band, BAND_PCT, IN_BAND  # noqa: E402

SCRATCH = L.WORK / "coord" / "scratch"
OUT = L.THESIS / "03-methodology.md"
SUBSET = ["polybench", "polybench_pragmas", "forgebench", "machsuite", "spector_hls", "vitis_examples"]
GATES = ["bicg", "gesummv", "mvt", "syrk"]

# The catalogue run each step published (results pages / comparison CSVs), in order. Paths only; every
# number comes from re-comparing the file against today's ground truth.
RUNS = [
    ("first full-catalogue run (baseline)", L.RESULTS / "baseline" / "hlsest-2026-10-13-v2-defaults.json"),
    ("hls::stream FIFOs", SCRATCH / "w9fifo_impl" / "after_merged.json"),
    ("PIPO channels", SCRATCH / "w9pipo_impl" / "after6_merged.json"),
    ("width narrowing (round 2)", SCRATCH / "w9r2i" / "after8.json"),
    ("round 2, review fixes", SCRATCH / "w9r2fix" / "after.json"),
    ("process merges (N36)", SCRATCH / "n36impl" / "after.json"),
    ("copy-count inputs (N38)", SCRATCH / "n38impl" / "t7.json"),
    ("structs (N37)", SCRATCH / "n37impl" / "v10.json"),
    ("round 4, review fixes", SCRATCH / "w9r4fix" / "cg_f7.json"),
    ("round 5", SCRATCH / "w9r5fix" / "final.json"),
    ("real Vitis headers", SCRATCH / "w11adopt" / "C1.json"),
    ("round 6", SCRATCH / "w9r6i" / "F1.json"),
    ("round 6, review fixes", SCRATCH / "w9r6fix" / "G1.json"),
    ("round 7", SCRATCH / "w9r7i" / "F.json"),
    ("round 7, review fixes", SCRATCH / "w9r7fix" / "R4.json"),
    ("round 8", SCRATCH / "w9r8g" / "A.json"),
    ("round 9", SCRATCH / "w9r9i" / "P2.json"),
    ("round 9, review fixes", SCRATCH / "w9r9fix" / "F.json"),
    ("round 10", SCRATCH / "w9r10i" / "R10.json"),
    ("round 10, review fixes (final evaluation run)", SCRATCH / "w9r10fx" / "X2.json"),
]

STAGE_ROWS = [
    ["front end (clang 7 + headers -> LLVM IR)", "open (hls-llvm-project)", "db/a.g.ld.5.gdce.ll; source code"],
    ["reflow (pragmas, partition inference, inlining, dead code, narrowing)", "closed LLVM passes",
     "db/a.o.1.ll .. a.o.3.ll; [HLS 214-*] messages; complexity dumps db/cmplx.*.json"],
    ["schedule and binding (II, ports, RAM kind, copies)", "closed, not LLVM",
     "loop / memory / instance / FIFO tables; [HLS 200-*] messages; *.verbose.sched.rpt, *.verbose.bind.rpt; RTL"],
    ["resource formula (RAMB18 per memory)", "open (CoreQuerier.cpp)", "memory table BRAM_18K; source code"],
]


def recompare(path, V):
    H = C.load_json(str(path), {}) or {}
    meta = H.pop("_meta", {})
    rows = [compare_one(k, V.get(k), H.get(k)) for k in sorted(set(V) | set(H))]
    cmp_ = [r for r in rows if r["status"] == "compared"]
    ex = sum(1 for r in cmp_ if r["exact"])
    inb = sum(1 for r in cmp_ if band(r["vitis_bram"], r["hlsest_bram"]) in IN_BAND)
    err = sum(abs(r["diff"]) for r in cmp_)
    sub = [r for r in cmp_ if r["dataset"] in SUBSET]
    shim = Path(str(meta.get("shim", ""))).name or "?"
    git = str(meta.get("hls_est_git", ""))
    if not re.fullmatch(r"[0-9a-f]{7,12}", git):
        git = "frozen " + Path(str(meta.get("hls_est", "?"))).name
    day = datetime.date.fromtimestamp(os.path.getmtime(path)).isoformat()
    return {"rows": rows, "meta": meta, "designs": len(rows), "compared": len(cmp_), "exact": ex,
            "inband": inb, "err": err, "sub_compared": len(sub), "sub_exact": sum(1 for r in sub if r["exact"]),
            "shim": shim, "git": git, "day": day}


def changelog_counts():
    ents = L.changelog_entries()
    review = [h for h, _ in ents if re.search(r"review", h, re.I)]
    optin = []
    for h, b in ents:
        m = re.search(r"^- \*\*Reverted\?:\*\*(.*)$", b, flags=re.M)
        if not m:
            continue
        txt = m.group(1)
        if re.search(r"opt-in|off by default|kept off|stay out of the default|out of the default", txt, re.I):
            day, _, title = h.partition(" — ")
            title, txt = L.readable(title), L.readable(txt)
            optin.append([day, title[:150] + ("..." if len(title) > 150 else ""), txt.strip()[:160]])
    return ents, review, optin


def latest_regex(pattern):
    for h, b in L.changelog_entries():
        m = re.search(pattern, b)
        if m:
            return h, m
    raise KeyError(pattern)


def figure_experiments(idx, gen):
    import ch34_plot as P
    days = collections.Counter(d for _, _, d in idx)
    xs = sorted(days)
    fig, ax = P.plt.subplots(figsize=(6.4, 2.6))
    ax.bar(range(len(xs)), [days[d] for d in xs], color=P.SERIES[0], width=0.6)
    for i, d in enumerate(xs):
        ax.text(i, days[d] + max(days.values()) * 0.015, str(days[d]), ha="center", fontsize=7, color=P.INK2)
    ax.set_xticks(range(len(xs)))
    ax.set_xticklabels([d[5:] for d in xs], fontsize=7)
    ax.set_ylabel("kernel runs", fontsize=8)
    ax.yaxis.grid(True, color=P.GRID, linewidth=0.6)
    P.style(ax)
    fig.tight_layout()
    P.save(fig, str(L.FIGURES / "ch3-experiment-runs"), gen)


def figure_runs(stats, gen):
    import ch34_plot as P
    fig, axes = P.plt.subplots(1, 2, figsize=(7.2, 3.0))
    xs = list(range(len(stats)))
    ax = axes[0]
    ax.plot(xs, [s["exact"] for s in stats], color=P.SERIES[0], linewidth=2, marker="o", markersize=4,
            label="exact")
    ax.plot(xs, [s["inband"] for s in stats], color=P.SERIES[1], linewidth=2, marker="o", markersize=4,
            label="in goal band")
    ax.plot(xs, [s["compared"] for s in stats], color=P.INK2, linewidth=1, linestyle="--", label="compared")
    ax.set_ylabel("designs", fontsize=8)
    ax.legend(fontsize=7, frameon=False, loc="lower right")
    ax2 = axes[1]
    ax2.plot(xs, [s["err"] for s in stats], color=P.SERIES[0], linewidth=2, marker="o", markersize=4)
    ax2.set_yscale("log")
    ax2.set_ylabel("sum |hls-est - Vitis| (BRAM_18K, log)", fontsize=8)
    for a in axes:
        a.set_xticks(xs)
        a.set_xticklabels([str(i + 1) for i in xs], fontsize=7)
        a.set_xlabel("published run (Table 3.5)", fontsize=8)
        a.yaxis.grid(True, color=P.GRID, linewidth=0.6)
        P.style(a)
    fig.tight_layout()
    P.save(fig, str(L.FIGURES / "ch3-catalogue-progress"), gen)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--newest", help="an additional, newer published run JSON (label 'newest')")
    a = ap.parse_args()
    runs = list(RUNS)
    if a.newest:
        runs.append(("newest", Path(a.newest)))
    inputs = ["tools/hls-est-validate/results/{vitis,vitis-tdauto}.json",
              "results/formula_reconcile_summary.csv",
              "the published runs of Table 3.5 (" + ", ".join(L.rel(p) for _, p in runs[-2:]) + ", ...)",
              "~/hls-est-work/experiments/*/*/result.json", "hls-doc/notes/*.md",
              "~/hls-est-work/coord/scratch/reports/", "test/hls-est/Mirror/"]
    gen = L.header(__file__, inputs)
    import json as _json
    snap = _json.loads((Path(__file__).parent / "ch06_manifest.json").read_text())["snapshot"]
    cutoff = datetime.datetime.fromisoformat(snap["experiments_cutoff"])
    L.FIGURES.mkdir(parents=True, exist_ok=True)
    v = {}

    # ground truth
    V = C.load_json(str(L.RESULTS / "vitis.json"), {})
    st = collections.Counter(e.get("status") for e in V.values())
    ok = [e for e in V.values() if e.get("status") == "ok"]
    v["band_over_pct"] = BAND_PCT   # make_compare_csv.BAND_OVER, the DoD-5 band (MEMOS #95)
    v["gt_designs"], v["gt_ok"] = len(V), st["ok"]
    v["gt_failed"], v["gt_timeout"] = st["vitis failed"], st["vitis timeout"]
    v["gt_mem_rows"] = sum(len(e.get("memories") or []) for e in ok)
    v["gt_loop_rows"] = sum(len(e.get("loops") or []) for e in ok)
    for k in ("part", "clock", "vitis_version"):
        vals = collections.Counter(e.get(k) for e in ok)
        if len(vals) != 1:
            raise SystemExit(f"ground truth not uniform in {k}: {vals}")
    cfg_rows = [["Vitis HLS version (recorded per design)", ok[0]["vitis_version"]],
                ["part (recorded per design)", ok[0]["part"]],
                ["clock (recorded per design)", ok[0]["clock"]],
                ["flow_target (harness constant common.FLOW_TARGET)", C.FLOW_TARGET],
                ["extra configuration (common.EXTRA_HLS_CFG)", "; ".join(C.EXTRA_HLS_CFG)],
                ["designs / with a result / rejected / timeout",
                 f"{len(V)} / {st['ok']} / {st['vitis failed']} / {st['vitis timeout']}"]]
    v["table_config"] = L.write_table("ch3-config", ["setting", "value"], cfg_rows,
                                      "Ground-truth configuration", "tab:ch3-config", gen, colspec="ll")
    v["table_stages"] = L.write_table("ch3-stages", ["stage", "visibility", "observed through"], STAGE_ROWS,
                                      "Stages of Vitis HLS and where each is observed", "tab:ch3-stages", gen,
                                      colspec="p{4.2cm}p{2.8cm}p{6.5cm}")
    VA = C.load_json(str(L.RESULTS / "vitis-tdauto.json"), {})
    v["atax_tdauto"] = VA["polybench/atax"]["totals"]["BRAM"]
    v["atax_tdoff"] = V["polybench/atax"]["totals"]["BRAM"]

    # formula reconciliation
    with open(L.RESULTS / "formula_reconcile_summary.csv") as fh:
        fr = {r["subset"]: r for r in csv.DictReader(fh)}
    a_, e_ = fr["[vitis.json] all rows"], fr["[experiments] all rows"]
    v["fr_rows"], v["fr_open"], v["fr_n6"] = a_["rows"], a_["open"], a_["n6"]
    v["fr_exp_rows"], v["fr_exp_open"], v["fr_exp_n6"] = e_["rows"], e_["open"], e_["n6"]
    v["fr_date"] = datetime.date.fromtimestamp(os.path.getmtime(L.RESULTS / "formula_reconcile_summary.csv")).isoformat()
    full = L.THESIS / "data" / "formula-reconcile-full.csv"
    with open(full) as fh:
        ff = {r["subset"]: r for r in csv.DictReader(fh)}
    fa = ff["[vitis.json] all rows"]
    v["frf_rows"], v["frf_open"], v["frf_n6"] = fa["rows"], fa["open"], fa["n6"]
    v["frf_vec_rows"], v["frf_vec_match"] = fa["vec_rows"], fa["vec_match"]

    # experiments
    idx = L.experiment_index(cutoff)
    v["exp_cutoff"] = snap["experiments_cutoff"].replace("T", " ")
    names = {n for n, _, _ in idx}
    sts = collections.Counter(s for _, s, _ in idx)
    v["exp_runs"], v["exp_names"] = len(idx), len(names)
    v["exp_ok"], v["exp_failed"], v["exp_timeout"] = sts["ok"], sts["vitis failed"], sts["vitis timeout"]
    notes_text = L.read_text(L.NOTES / "VITIS_NOTES.md")
    tokens = set(re.findall(r"[A-Za-z0-9_]+", notes_text))
    v["exp_cited"] = len(names & tokens)
    v["n_aspect"] = len({n for n in names if n.startswith(("aspect_", "fr_"))})
    v["n_lutram"] = len({n for n in names if n.startswith("lutram_")})
    v["n_fifo"] = len({n for n in names if n.startswith(("fifo_", "rvf_"))})
    figure_experiments(idx, gen)

    # notes
    import thesis_data as T
    nc = T.note_status_counts()
    v["n_notes"] = nc["notes"]
    v["n_notes_confirmed"], v["n_notes_partly"] = nc["confirmed"], nc["partly"]
    v["n_notes_confirmed_kernels"], v["n_notes_confirmed_corpus"] = nc["confirmed_kernels"], nc["confirmed_corpus"]
    v["n_notes_unconfirmed"], v["n_notes_method"] = nc["unconfirmed"], nc["method"]
    v["n_notes_corpus_list"], v["n_notes_unconfirmed_list"] = nc["confirmed_corpus_list"], nc["unconfirmed_list"]
    v["n_corrections"] = len(re.findall(r"[Cc]orrected", notes_text))
    v["n_open"] = len(re.findall(r"^## O\d+\.", L.read_text(L.NOTES / "OPEN_ISSUES.md"), flags=re.M))
    memos = L.read_text(L.NOTES / "MEMOS.md")
    v["n_memos"] = len(set(re.findall(r"^\| *(\d+) *\|", memos, flags=re.M)))
    ents, review, optin = changelog_counts()
    v["n_changelog"], v["n_changelog_review"] = len(ents), len(review)
    v["table_optin"] = L.write_table("ch3-optin", ["date", "change-log entry", "Reverted? (verbatim, shortened)"],
                                     optin, "Change-log entries whose mechanism stayed opt-in or off by default",
                                     "tab:ch3-optin", gen, colspec="lp{6cm}p{6cm}")
    reps = sorted(p.name for p in (SCRATCH / "reports").glob("*.md"))
    v["n_round_reports"] = len(reps)
    v["n_round_review"] = sum(1 for r in reps if "review" in r)
    v["n_mirror"] = len(list((L.REPO / "test" / "hls-est" / "Mirror").rglob("*.mlir")))
    _, m = latest_regex(r"debug invariance (\d+) cases, (\d+) pass(?:[^;\n(]|\([^)]*\))*")
    v["invariance"] = f"\"{m.group(0).strip().rstrip('.')}\""
    _, m = latest_regex(r"hls-est \(`[^`]*`\) (\d+) tests: [^(\n]*?(\d+) fail")
    v["lit"] = f"\"{m.group(0)}\""
    src = L.read_text(L.REPO / "lib/Dialect/Resource/Passes/BRAMAnalysis.cpp")
    v["debug_json_version"] = re.search(r'root\["version"\] = (\d+);', src).group(1)

    # runs
    stats = []
    for label, p in runs:
        s = recompare(p, V)
        s["label"], s["path"] = label, p
        stats.append(s)
        print(f"  {label}: compared {s['compared']} exact {s['exact']} in band {s['inband']} |err| {s['err']}")
    run_rows = [[i + 1, s["label"], s["day"], s["git"], s["shim"], s["compared"], s["exact"], s["inband"],
                 s["err"], f"{s['sub_exact']} / {s['sub_compared']}"] for i, s in enumerate(stats)]
    v["table_runs"] = L.write_table(
        "ch3-runs", ["#", "run", "file date", "hls-est binary", "shim", "compared", "exact", "in band", "sum |err|",
                     "subset exact"], run_rows,
        "Published catalogue runs re-compared against the current ground truth", "tab:ch3-runs", gen,
        colspec="rllllrrrrr", md_align=["---:", "---", "---", "---", "---", "---:", "---:", "---:", "---:", "---:"])
    figure_runs(stats, gen)
    newest = stats[-1]
    rows = newest["rows"]
    cmp_ = [r for r in rows if r["status"] == "compared"]
    v["cat_designs"] = newest["designs"]
    v["cat_datasets"] = len({r["dataset"] for r in rows})
    v["cat_compared"] = newest["compared"]
    v["subset_names"] = ", ".join(SUBSET)
    v["non_array_bram"] = sum(r.get("vitis_non_array_bram") or 0 for r in cmp_)
    v["vitis_bram_total"] = sum(r["vitis_bram"] for r in cmp_)
    gate = []
    for g in GATES:
        r = next(r for r in rows if r["dataset"] == "polybench_pragmas" and r["benchmark"] == g)
        if r["vitis_bram"] != r["hlsest_bram"]:
            raise SystemExit(f"gate {g} not exact in the newest run")
        gate.append(f"{g} {r['vitis_bram']}")
    v["gates"] = ", ".join(gate)
    meta = newest["meta"]
    v["run_git"], v["run_cgeist"] = meta.get("hls_est_git"), meta.get("cgeist_md5", "?")[:8]
    v["run_shim"] = Path(str(meta.get("shim"))).name
    v["run_pipeline"] = meta.get("pipeline")
    v["run_mlir_from"] = Path(str(meta.get("mlir_from", ""))).parent.name + "/" + Path(str(meta.get("mlir_from", ""))).name
    v["run_polygeist_recorded"] = meta.get("polygeist_head") or "not recorded"
    v["run_polygeist"], v["run_cgeist_snapshot"] = snap["polygeist_commit"], snap["cgeist_md5"]

    # worked example
    for k in ("dm_wo", "dm_rd", "dm_self"):
        v[f"k_{k}"] = L.kernel_value(f"w9r8p_{k}")
    for k in ("dm_cyc2", "dm_ctl", "dm_acc0"):
        v[f"k_{k}"] = L.kernel_value(f"w9r8i_{k}")
    _, q = L.changelog_effect("W9r8-impl 1-5", "(1) Dehazing")
    v["dm_effect"] = q

    text = L.fill_template(L.read_text(Path(__file__).parent / "templates" / "ch3_methodology.md.in"), v)
    with open(OUT, "w") as fh:
        fh.write(f"<!-- {gen} -->\n\n" + text.rstrip() + "\n")
    print(f"wrote {L.rel(OUT)}")


if __name__ == "__main__":
    main()
