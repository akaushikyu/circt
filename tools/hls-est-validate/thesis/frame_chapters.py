#!/usr/bin/env python3
"""Render the frame chapters of the thesis draft (abstract, introduction, background, implementation,
RTL back end, limitations) from templates, with every number taken from a parsed result file.

Templates: tools/hls-est-validate/thesis/templates/*.md.in.  A placeholder {{key}} is replaced by the value
of `key` in the number set this script collects; an unknown key is an error (no number is ever typed by
hand into a chapter).  Outputs (all under hls-doc/thesis/):

  <chapter>.md                          one file per template
  data/frame-numbers.json               every number with the file it came from
  tables/frame-*.{md,tex}               tables (LaTeX: booktabs)
  figures/ch07-rtl-funnel.{pdf,png}     the RTL coverage funnel (needs matplotlib: run with the private
                                        venv ~/hls-est-work/coord/scratch/thesis/venv/bin/python; without
                                        matplotlib the figure is skipped and the chapters still render)

Inputs (paths are recorded in data/frame-numbers.json):
  tools/hls-est-validate/results/comparison-summary.csv, comparison.csv  (make_compare_csv.py, newest run)
  tools/hls-est-validate/results/vitis.json                              (Vitis 2025.1 ground truth)
  hls-doc/hls-est-vs-vitis.csv                                           (time columns)
  hls-doc/thesis/data/ch06-numbers.json                                  (chapter 6's numbers, as ev_*;
                                                                         run make_thesis_tables.py first)
  hls-doc/notes/{VITIS_NOTES,OPEN_ISSUES,MEMOS,CHANGELOG}.md at the snapshot commit (counts of notes and
                                                                         issues; ch06_manifest.json snapshot)
  hls-doc/plugins.md, configuration.md, passes/README.md, tests.md, done-exclusions.md
  the check_semantics records listed in done-exclusions.md (later wins)
  git: the snapshot commits of ~/circt and /mnt/d/HLS (commit counts, co-author trailers, source sizes),
       branch rtl-backend: hls-doc/rtl-coverage.md, hls-doc/design/rtl-backend-float.md, tools/rtl-backend/kernels/
  test/hls-est/ (test files with a RUN line)

Usage: python3 tools/hls-est-validate/thesis/frame_chapters.py [--out hls-doc/thesis]
"""
import argparse
import csv
import datetime
import json
import re
import statistics
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import thesis_data as T  # noqa: E402  (the shared note-status parser)

HERE = Path(__file__).resolve().parent
VALIDATE = HERE.parent
CIRCT = VALIDATE.parent.parent
DOC = CIRCT / "hls-doc"
POLYGEIST = Path("/mnt/d/HLS")
RESULTS = VALIDATE / "results"
FRAME_CHAPTERS = ["00-abstract", "01-introduction", "02-background-related-work", "05-implementation",
                  "07-rtl-backend", "08-limitations-future-work"]
HARNESS_SUBSET = ["polybench", "polybench_pragmas", "forgebench", "machsuite", "spector_hls",
                  "vitis_examples"]
GATES = ["bicg", "gesummv", "mvt", "syrk"]


class Numbers:
    """Key -> value, with the source file of each key."""

    def __init__(self):
        self.values, self.sources = {}, {}

    def put(self, key, value, source):
        if key in self.values:
            raise SystemExit("duplicate key %s" % key)
        self.values[key] = value
        self.sources[key] = str(source)


def fmt_int(n):
    return "{:,}".format(n)


def pct(a, b):
    return "%.1f" % (100.0 * a / b) if b else "n/a"


def git(repo, *args):
    return subprocess.run(["git", "-C", str(repo)] + list(args), check=True, capture_output=True,
                          text=True).stdout


def md_table_rows(text, header_start):
    """Rows (lists of cells) of the first Markdown table whose header line starts with header_start."""
    lines = [l.strip() for l in text.splitlines()]
    for i, line in enumerate(lines):
        if line.startswith(header_start):
            rows = []
            for row in lines[i + 2:]:
                if not row.startswith("|"):
                    break
                rows.append([c.strip() for c in row.strip().strip("|").split("|")])
            return rows
    raise SystemExit("table %r not found" % header_start)


def as_int(cell):
    return int(re.sub(r"[^0-9-]", "", cell))


# ---------------------------------------------------------------------------------------------- collectors

def collect_comparison(N):
    src = RESULTS / "comparison-summary.csv"
    text = src.read_text()
    summary_part, _, settings_part = text.partition("\n\n")
    rows = list(csv.DictReader(summary_part.splitlines()))
    allrow = next(r for r in rows if r["dataset"] == "ALL")
    i = lambda k: int(float(allrow[k]))
    N.put("designs", i("designs"), src)
    N.put("with_vitis", i("with_vitis_result"), src)
    N.put("compared", i("compared"), src)
    N.put("exact", i("exact"), src)
    N.put("exact_pct", allrow["exact_pct_of_compared"], src)
    N.put("in_goal", i("in_goal_band"), src)
    N.put("in_goal_pct", allrow["in_goal_band_pct_of_compared"], src)
    N.put("abs_err", fmt_int(i("total_abs_err")), src)
    N.put("over_le15", i("over_le_15pct"), src)
    N.put("over_gt15", i("over_gt_15pct"), src)
    N.put("under", i("under"), src)
    N.put("out_of_band", i("compared") - i("in_goal_band"), src)
    N.put("hlsest_failed", i("hlsest_failed_or_not_run"), src)
    N.put("vitis_missing", i("vitis_failed"), src)
    N.put("datasets", len([r for r in rows if r["dataset"] != "ALL"]), src)
    full_ds = [r["dataset"] for r in rows if r["dataset"] != "ALL" and r["compared"] not in ("", "0")
               and r["exact"] == r["compared"]]
    N.put("datasets_all_exact", len(full_ds), src)
    ds = sorted((r for r in rows if r["dataset"] != "ALL"), key=lambda r: -int(float(r["total_abs_err"] or 0)))
    tot_err = i("total_abs_err")
    N.put("err_top4", ", ".join("%s %s" % (r["dataset"], fmt_int(int(float(r["total_abs_err"])))) for r in ds[:4]), src)
    N.put("err_top4_share", pct(sum(int(float(r["total_abs_err"])) for r in ds[:4]), tot_err), src)
    settings = dict(r for r in csv.reader(settings_part.splitlines()) if len(r) == 2)
    N.put("run_json", settings["hls-est run json"].replace(str(Path.home()), "~"), src)
    N.put("run_hlsest_git", settings["hls-est git"], src)
    N.put("run_cgeist_md5", settings["cgeist md5"][:8], src)
    N.put("run_generated", settings["generated"], src)
    passes = settings["pipeline"].split()
    N.put("pipeline_passes", len(passes), src)
    N.put("pipeline_text", " ".join(passes), src)

    src2 = RESULTS / "comparison.csv"
    text2 = src2.read_text()
    lines2 = text2.splitlines()
    start = next(i for i, l in enumerate(lines2) if l.startswith("dataset,benchmark,"))
    rows2 = list(csv.DictReader(lines2[start:]))
    compared = [r for r in rows2 if r["comparison_status"] == "compared"]
    sub = [r for r in compared if r["dataset"] in HARNESS_SUBSET]
    N.put("subset_compared", len(sub), src2)
    N.put("subset_exact", sum(r["exact"] == "True" for r in sub), src2)
    N.put("subset_in_goal", sum(r["goal_band"] in ("exact", "over<=15%") for r in sub), src2)
    N.put("subset_abs_err", sum(int(r["abs_diff"]) for r in sub), src2)
    for g in GATES:
        r = next(r for r in rows2 if r["dataset"] == "polybench_pragmas" and r["benchmark"] == g)
        N.put("gate_%s_vitis" % g, int(r["vitis_bram_18k"]), src2)
        N.put("gate_%s_hlsest" % g, int(r["hlsest_bram_18k"]), src2)
    N.put("gates_all_exact", "all four exact" if all(
        N.values["gate_%s_vitis" % g] == N.values["gate_%s_hlsest" % g] for g in GATES)
        else "NOT all exact", src2)
    under = sorted((r for r in compared if int(r["diff_hlsest_minus_vitis"]) < 0),
                   key=lambda r: int(r["diff_hlsest_minus_vitis"]))
    N.put("under_sum", fmt_int(-sum(int(r["diff_hlsest_minus_vitis"]) for r in under)), src2)
    over = [r for r in compared if int(r["diff_hlsest_minus_vitis"]) > 0]
    N.put("over_sum", fmt_int(sum(int(r["diff_hlsest_minus_vitis"]) for r in over)), src2)
    return under, sorted(set(r["goal_band"] for r in compared))


def collect_vitis(N):
    src = RESULTS / "vitis.json"
    d = json.loads(src.read_text())
    ok = [v for v in d.values() if v.get("status") == "ok"]
    N.put("vitis_records", len(d), src)
    N.put("vitis_ok", len(ok), src)
    N.put("vitis_failed", sum(v.get("status") == "vitis failed" for v in d.values()), src)
    N.put("vitis_timeout", sum(v.get("status") == "vitis timeout" for v in d.values()), src)
    N.put("vitis_memory_rows", fmt_int(sum(len(v.get("memories") or []) for v in ok)), src)
    N.put("vitis_loop_rows", fmt_int(sum(len(v.get("loops") or []) for v in ok)), src)
    versions = sorted(set(str(v.get("vitis_version")) for v in ok))
    parts = sorted(set(str(v.get("part")) for v in ok))
    clocks = sorted(set(str(v.get("clock")) for v in ok))
    N.put("vitis_versions", ", ".join(versions), src)
    N.put("vitis_parts", ", ".join(parts), src)
    N.put("vitis_clocks", ", ".join(re.sub(r"(\d)ns$", r"\1 ns", c) for c in clocks), src)
    secs = [float(v["elapsed_s"]) for v in ok if v.get("elapsed_s")]
    N.put("vitis_hours_total", "%.0f" % (sum(secs) / 3600.0), src)


def collect_times(N):
    src = DOC / "hls-est-vs-vitis.csv"
    rows = list(csv.DictReader(src.open()))
    pairs = []
    for r in rows:
        try:
            h, v = float(r["hls-est time (s)"]), float(r["Vitis csynth time (s)"])
        except (ValueError, KeyError):
            continue
        pairs.append((h, v))
    N.put("time_pairs", len(pairs), src)
    util = []
    for r in rows:
        try:
            util.append([float(r[k]) for k in ("BRAM_util_pct", "DSP_util_pct", "FF_util_pct",
                                                 "LUT_util_pct")])
        except (ValueError, KeyError):
            continue
    N.put("util_designs", len(util), src)
    N.put("util_bram_highest", sum(u[0] > 0 and u[0] >= max(u[1:]) for u in util), src)
    N.put("time_hlsest_median", "%.1f" % statistics.median(p[0] for p in pairs), src)
    N.put("time_vitis_median", "%.1f" % statistics.median(p[1] for p in pairs), src)
    N.put("time_hlsest_total_h", "%.1f" % (sum(p[0] for p in pairs) / 3600.0), src)
    N.put("time_vitis_total_h", "%.1f" % (sum(p[1] for p in pairs) / 3600.0), src)


def collect_notes(N):
    notes = DOC / "notes"
    index = T.vitis_notes_index()
    N.put("n_notes", len(index), notes / "VITIS_NOTES.md")
    N.put("n_last", max(int(re.sub(r"\D", "", h)) for h in index), notes / "VITIS_NOTES.md")
    counts = T.note_status_counts(index)
    for k in ("confirmed", "confirmed_kernels", "confirmed_corpus", "partly", "unconfirmed", "method",
              "confirmed_corpus_list", "unconfirmed_list", "partly_list", "method_list"):
        N.put("n_notes_%s" % k, counts[k], "%s (thesis_data.note_status)" % (notes / "VITIS_NOTES.md"))
    per = {}
    for nid, e in index.items():
        m = re.search(r"(\d+)(?: \+ \d+)* (?:v1 )?kernels", e["title"])
        per[nid] = {"status": e["status"], "kernels": int(m.group(1)) if m else None}
    oi = T.notes_text("OPEN_ISSUES.md")
    onums = [int(x) for x in re.findall(r"^## O(\d+)\.", oi, re.M)]
    N.put("o_count", len(onums), notes / "OPEN_ISSUES.md")
    N.put("o_last", max(onums), notes / "OPEN_ISSUES.md")
    memos = T.notes_text("MEMOS.md")
    drows = re.findall(r"^\| (\d+) \|", memos, re.M)
    N.put("memos_decisions", len(set(drows)), notes / "MEMOS.md")
    cl = T.notes_text("CHANGELOG.md")
    dates = re.findall(r"^## (\d{4}-\d{2}-\d{2})", cl, re.M)
    N.put("changelog_entries", len(dates), notes / "CHANGELOG.md")
    N.put("changelog_first", min(dates), notes / "CHANGELOG.md")
    N.put("changelog_last", max(dates), notes / "CHANGELOG.md")
    return per


def collect_docs(N):
    pl = (DOC / "plugins.md").read_text()
    rows = md_table_rows(pl, "| Interface (registry key)")
    N.put("plugin_interfaces", len(rows), DOC / "plugins.md")
    cfg = (DOC / "configuration.md").read_text()
    reg = md_table_rows(cfg, "| Interface | Implementation")
    N.put("plugin_builtins", len(reg), DOC / "configuration.md")
    body = cfg.split("## run:", 1)[1].split("## plugins:", 1)[0]
    keys = [l for l in body.splitlines() if re.match(r"^\| `[a-z_]", l)]
    N.put("config_keys", len(keys), DOC / "configuration.md")
    pr = (DOC / "passes" / "README.md").read_text()
    prow = md_table_rows(pr, "| # | Pass")
    pages = [p for p in (DOC / "passes").glob("*.md") if p.name != "README.md"]
    N.put("pass_pages", len(pages), DOC / "passes")
    own = sum(1 for r in prow if r[2].startswith("hls-est") or "modified" in r[2])
    N.put("pipeline_own_passes", own, DOC / "passes" / "README.md")
    tests = (DOC / "tests.md").read_text()
    trow = md_table_rows(tests, "| source directory | cgeist tests")
    total = next(r for r in trow if "total" in r[0])
    tot = [as_int(total[k]) for k in range(1, 6)]
    N.put("cgeist_hls_tests", tot[0], DOC / "tests.md")
    N.put("mirror_tests", tot[1], DOC / "tests.md")
    N.put("mirror_pass", tot[2], DOC / "tests.md")
    N.put("mirror_xfail", tot[3], DOC / "tests.md")
    N.put("mirror_no_test", tot[4], DOC / "tests.md")
    de = (DOC / "done-exclusions.md").read_text()
    N.put("dod_vitis_rejects", int(re.search(r"^## \(1\).*\((\d+)\)", de, re.M).group(1)),
          DOC / "done-exclusions.md")
    N.put("dod_defective_refs", int(re.search(r"^## \(2\).*\((\d+)\)", de, re.M).group(1)),
          DOC / "done-exclusions.md")
    sems = re.findall(r"^- semantics: `([^`]+)`", de, re.M)
    merged = {}
    for f in sems:
        d = json.loads(Path(f).read_text())
        rows_ = d.get("rows", d) if isinstance(d, dict) else {r["key"]: r for r in d}
        if isinstance(rows_, list):
            rows_ = {r["key"]: r for r in rows_}
        merged.update({k: v for k, v in rows_.items() if not k.startswith("_")})
    st = [v.get("status") for v in merged.values()]
    N.put("sem_records", len(merged), "semantics records listed in hls-doc/done-exclusions.md")
    N.put("sem_equal", st.count("equal"), "semantics records listed in hls-doc/done-exclusions.md")
    N.put("sem_mismatch", st.count("mismatch"), "semantics records listed in hls-doc/done-exclusions.md")
    N.put("sem_na", st.count("n/a"), "semantics records listed in hls-doc/done-exclusions.md")
    N.put("sem_checked", st.count("equal") + st.count("mismatch"),
          "semantics records listed in hls-doc/done-exclusions.md")
    return prow, rows


def collect_invariance(N):
    """The newest change-log record of the debug-invariance check ("debug invariance N cases, ...")."""
    src = DOC / "notes" / "CHANGELOG.md"
    m = re.search(r"debug invariance (\d+) cases, (\d+) pass(?:, \d+ fail)?, (\d+) tool error", T.notes_text("CHANGELOG.md"))
    N.put("inv_cases", int(m.group(1)), src)
    N.put("inv_record", m.group(0), src)


def collect_tests(N):
    root = CIRCT / "test" / "hls-est"
    for sub in ("Passes", "Estimation", "Mirror", "Config", "Plugins"):
        files = [p for p in (root / sub).rglob("*") if p.suffix in (".mlir", ".test", ".json")
                 and p.is_file() and "RUN:" in p.read_text(errors="replace")]
        N.put("lit_%s" % sub.lower(), len(files), root / sub)


def collect_loc(N, snap):
    """Source sizes read from git at the snapshot commits (not the working tree)."""
    def tree(repo, commit, paths, keep):
        names = [n for n in git(repo, "ls-tree", "-r", "--name-only", commit, *paths).splitlines() if keep(n)]
        return names, sum(len(git(repo, "show", "%s:%s" % (commit, n)).splitlines()) for n in names)
    res_paths = ["lib/Dialect/Resource", "include/circt/Dialect/Resource"]
    is_src = lambda n: n.endswith((".cpp", ".h"))
    c = snap["circt_commit"]
    files, lines = tree(CIRCT, c, res_paths, is_src)
    N.put("loc_resource", fmt_int(lines), "git %s: lib/Dialect/Resource/**/*.cpp + include/circt/Dialect/Resource/**/*.h" % c)
    N.put("files_resource", len(files), "git %s: lib/Dialect/Resource, include/circt/Dialect/Resource" % c)
    base = git(CIRCT, "merge-base", "main", c).strip()
    files0, lines0 = tree(CIRCT, base, res_paths, is_src)
    N.put("loc_resource_before", fmt_int(lines0), "git %s (branch point): the same paths" % base[:9])
    N.put("files_resource_before", len(files0), "git %s (branch point): the same paths" % base[:9])
    py, pylines = tree(CIRCT, c, ["tools/hls-est-validate"],
                       lambda n: n.endswith(".py") and n.count("/") == 2)
    N.put("loc_harness", fmt_int(pylines), "git %s: tools/hls-est-validate/*.py" % c)
    N.put("files_harness", len(py), "git %s: tools/hls-est-validate/*.py" % c)
    p = snap["polygeist_commit"]
    hls, hlslines = tree(POLYGEIST, p, ["Polygeist/tools/cgeist/Lib"],
                         lambda n: n.count("/") == 4 and ("HLS" in n.rsplit("/", 1)[1] or "Xlx" in n.rsplit("/", 1)[1]))
    N.put("loc_cgeist_hls", fmt_int(hlslines), "git %s: Polygeist tools/cgeist/Lib/*{HLS,Xlx}*" % p)
    N.put("files_cgeist_hls", len(hls), "git %s: Polygeist tools/cgeist/Lib/*{HLS,Xlx}*" % p)


def collect_git(N, snap):
    """Commit counts at the frozen snapshot commits (ch06_manifest.json `snapshot`), so that they do not
    change when the thesis commits themselves land."""
    c, p = snap["circt_commit"], snap["polygeist_commit"]
    N.put("circt_commits", int(git(CIRCT, "rev-list", "--count", c, "^main")),
          "git rev-list %s ^main (~/circt)" % c)
    N.put("circt_head", c, "ch06_manifest.json snapshot")
    N.put("circt_commits_coauthored", int(git(CIRCT, "log", "--format=%B", c, "^main").lower().count(
        "co-authored-by: claude")), "git log %s ^main trailers (~/circt)" % c)
    N.put("polygeist_commits", int(git(POLYGEIST, "rev-list", "--count", p, "^main")),
          "git rev-list %s ^main (/mnt/d/HLS)" % p)
    N.put("polygeist_head", p, "ch06_manifest.json snapshot")
    N.put("polygeist_commits_coauthored", int(git(POLYGEIST, "log", "--format=%B", p, "^main").lower().count(
        "co-authored-by: claude")), "git log %s ^main trailers (/mnt/d/HLS)" % p)
    base = git(CIRCT, "merge-base", "main", c).strip()
    N.put("circt_branch_point", base[:9], "git merge-base main %s" % c)
    N.put("circt_branch_point_date", git(CIRCT, "log", "-1", "--format=%ad", "--date=short", base).strip(),
          "git log %s" % base)


def collect_rtl(N):
    src = "git show rtl-backend:hls-doc/rtl-coverage.md"
    cov = git(CIRCT, "show", "rtl-backend:hls-doc/rtl-coverage.md")
    head = cov.splitlines()[2]
    m = re.search(r"\(([\d-]+ [\d:]+); hls-est `(\w+)`, cgeist `(\w+)`, timeout (\d+) s per step, "
                  r"co-simulation cap (\d+) cycles\)", head)
    N.put("rtl_date", m.group(1), src)
    N.put("rtl_hlsest", m.group(2), src)
    N.put("rtl_timeout", m.group(4), src)
    N.put("rtl_cycle_cap", fmt_int(int(m.group(5))), src)
    tot = md_table_rows(cov, "| | designs")
    labels = {}
    for r in tot:
        labels[re.sub(r"\*", "", r[0])] = as_int(r[1])
    keymap = {"catalogue designs": "rtl_catalogue", "cgeist MLIR": "rtl_cgeist",
              "hls-est decision pipeline ok": "rtl_hlsest_ok", "Verilog produced": "rtl_verilog",
              "testbench found": "rtl_tb_found", "testbench passes natively": "rtl_tb_native",
              "Verilog and a testbench": "rtl_verilog_tb", "co-simulation pass": "rtl_cosim_pass",
              "of them: the testbench's own check": "rtl_selfcheck",
              "of them: no call changes any output": "rtl_vacuous"}
    funnel = []
    for lab, val in labels.items():
        for prefix, key in keymap.items():
            if lab.startswith(prefix):
                N.put(key, val, src)
                funnel.append((lab, val))
    ver = md_table_rows(cov, "| verdict | designs")
    for r in ver:
        key = "rtl_v_" + re.sub(r"[^a-z]+", "_", r[0].split("(")[0].strip().lower()).strip("_")
        N.put(key, as_int(r[1]), src)
    m = re.search(r"\*\*Wrong-code mismatches \(RTL differs from a well-defined C result\): (\d+)\.\*\*",
                  cov)
    N.put("rtl_wrong_code", int(m.group(1)), src)
    first = md_table_rows(cov, "| cause class | designs")
    N.put("rtl_first_block_top", "%s (%d), %s (%d), %s (%d)" % (
        first[0][0], as_int(first[0][1]), first[1][0], as_int(first[1][1]), first[2][0],
        as_int(first[2][1])), src)
    N.put("rtl_no_verilog_ok", N.values["rtl_hlsest_ok"] - N.values["rtl_verilog"], src)
    fl = git(CIRCT, "show", "rtl-backend:hls-doc/design/rtl-backend-float.md")
    wns = md_table_rows(fl, "| kernel | WNS")
    src2 = "git show rtl-backend:hls-doc/design/rtl-backend-float.md (section 8)"
    for r in wns:
        k = r[0].split()[0]
        N.put("wns_%s" % k, r[1], src2)
    kern = [l for l in git(CIRCT, "ls-tree", "--name-only", "rtl-backend", "tools/rtl-backend/kernels/")
            .splitlines() if l.endswith(".c")]
    N.put("rtl_kernels", len(kern), "git ls-tree rtl-backend tools/rtl-backend/kernels/")
    N.put("rtl_branch_head", git(CIRCT, "rev-parse", "--short=9", "rtl-backend").strip(), "git")
    return funnel, wns


def collect_evaluation(N, out):
    """Every number of chapter 6 (data/ch06-numbers.json, written by make_thesis_tables.py, which must run
    first), as ev_<key>, so that the abstract, the introduction and the limitations quote the same values."""
    src = out / "data" / "ch06-numbers.json"
    nums = json.loads(src.read_text())["numbers"]
    for k, v in nums.items():
        N.put("ev_" + k, v, src)


# ---------------------------------------------------------------------------------------------- tables

def tex_escape(s):
    s = s.replace("\\", r"\textbackslash{}")
    for a, b in (("&", r"\&"), ("%", r"\%"), ("_", r"\_"), ("#", r"\#"), ("$", r"\$"), ("{", r"\{"),
                 ("}", r"\}"), ("~", r"\textasciitilde{}"), ("^", r"\^{}")):
        s = s.replace(a, b)
    s = re.sub(r"`([^`]*)`", r"\\texttt{\1}", s)
    s = s.replace("**", "")
    return s


def write_table(out, name, caption, header, rows, align, source):
    md = ["<!-- generated by tools/hls-est-validate/thesis/frame_chapters.py from %s -->" % source, "",
          "**%s**" % caption, "",
          "| " + " | ".join(header) + " |",
          "|" + "|".join("---:" if a == "r" else "---" for a in align) + "|"]
    md += ["| " + " | ".join(str(c) for c in r) + " |" for r in rows]
    (out / "tables" / (name + ".md")).write_text("\n".join(md) + "\n")
    tex = ["% generated by tools/hls-est-validate/thesis/frame_chapters.py from " + source,
           r"\begin{table}[t]", r"\centering", r"\small",
           r"\caption{%s}" % tex_escape(caption), r"\label{tab:%s}" % name,
           r"\begin{tabular}{%s}" % "".join("r" if a == "r" else ("p{%s}" % a if a.endswith("cm") else "l")
                                            for a in align),
           r"\toprule", " & ".join(tex_escape(h) for h in header) + r" \\", r"\midrule"]
    tex += [" & ".join(tex_escape(str(c)) for c in r) + r" \\" for r in rows]
    tex += [r"\bottomrule", r"\end{tabular}", r"\end{table}"]
    (out / "tables" / (name + ".tex")).write_text("\n".join(tex) + "\n")


RELATED = [
    # (approach, representative work (bib keys), input, what it predicts, ground truth, open model?)
    ("Analytical models", "COMBA [@zhao2017comba], Lin-Analyzer [@zhong2016lin], Aladdin [@shao2014aladdin]",
     "C/C++ or LLVM IR + pragmas", "latency, resources (aggregate)", "the HLS tool's report / RTL",
     "own model of an HLS tool"),
    ("Report-based ML", "Dai et al. [@dai2018fast], Pyramid [@makrani2019pyramid]",
     "HLS reports", "post-implementation resources, timing", "Vivado implementation", "learned"),
    ("Graph neural networks", "GNN-DSE [@sohrabizadeh2022gnndse], Wu et al. [@wu2022hlsgnn], "
     "IronMan [@wu2021ironman], PowerGear [@lin2022powergear], Ustun et al. [@ustun2020delay]",
     "program / IR graph + pragmas", "latency, LUT/FF/DSP/BRAM, power, delay (aggregate)",
     "HLS tool or implementation", "learned, opaque"),
    ("Language models", "ProgSG [@qin2024progsg], Intelligent4DSE [@xu2025intelligent4dse]",
     "source code + program graph", "latency, resources (aggregate)", "HLS tool", "learned, opaque"),
    ("Memory partitioning", "Cong et al. [@cong2011memorypartition], Wang et al. [@wang2014memorypartition]",
     "affine loop nests", "a conflict-free bank layout (designed, not predicted)", "their own schedule",
     "algorithmic"),
    ("HLS tool testing / verification", "Herklotz et al. [@herklotz2021reliability], Vericert [@herklotz2021vericert]",
     "generated or given C programs", "miscompilations; proven-correct RTL", "simulation; a proof",
     "black-box testing; verified compiler"),
    ("Open HLS compilers", "Bambu [@ferrandi2021bambu], LegUp [@canis2011legup], "
     "Dynamatic [@josipovic2018dynamatic], XLS [@xls], ScaleHLS [@ye2022scalehls], Allo [@chen2024allo], "
     "CIRCT/Calyx [@nigam2021calyx]", "C/C++, DSLs, MLIR", "their own schedules and resources",
     "themselves", "open, but a different tool"),
    ("This work (hls-est)", "black-box inference of Vitis HLS 2025.1, MLIR/CIRCT passes",
     "C/C++ + pragmas, real Vitis headers", "per-memory BRAM_18K decisions (kind, banks, copies, blocks)",
     "Vitis csynth totals; per array where names align", "open, rule-based, every rule cited"),
]


# ---------------------------------------------------------------------------------------------- main

def render(template, values, name):
    def sub(m):
        k = m.group(1).strip()
        if k not in values:
            raise SystemExit("%s: unknown placeholder {{%s}}" % (name, k))
        return str(values[k])
    return re.sub(r"\{\{([^}]+)\}\}", sub, template)


def figure_funnel(out, funnel):
    try:
        import matplotlib
        matplotlib.use("Agg")
        import matplotlib.pyplot as plt
    except ImportError:
        print("matplotlib missing: figure skipped", file=sys.stderr)
        return False
    chain = ("catalogue designs", "cgeist MLIR", "hls-est decision pipeline ok", "Verilog produced",
             "Verilog and a testbench", "co-simulation pass")
    funnel = [(l.split(" (")[0], v) for l, v in funnel if l.startswith(chain)]
    labels = [l for l, _ in funnel]
    vals = [v for _, v in funnel]
    fig, ax = plt.subplots(figsize=(7.0, 3.6))
    y = list(range(len(vals)))[::-1]
    ax.barh(y, vals, color="#2a78d6", height=0.62, edgecolor="#fcfcfb", linewidth=2)
    ax.set_yticks(y)
    ax.set_yticklabels(labels, fontsize=8, color="#0b0b0b")
    for yy, v in zip(y, vals):
        ax.text(v + max(vals) * 0.01, yy, str(v), va="center", fontsize=8, color="#52514e")
    ax.set_xlabel("designs of the HLSFactory_v2 catalogue", fontsize=8, color="#52514e")
    for s in ("top", "right"):
        ax.spines[s].set_visible(False)
    ax.spines["left"].set_color("#c3c2b7")
    ax.spines["bottom"].set_color("#c3c2b7")
    ax.tick_params(axis="x", labelsize=8, colors="#52514e")
    ax.grid(axis="x", color="#e6e5e0", linewidth=0.6)
    ax.set_axisbelow(True)
    ax.set_xlim(0, max(vals) * 1.12)
    fig.tight_layout()
    for ext in ("pdf", "png"):
        fig.savefig(out / "figures" / ("ch07-rtl-funnel." + ext), dpi=200,
                    metadata={"CreationDate": None} if ext == "pdf" else None)
    plt.close(fig)
    return True


README_MARK = "<!-- README written by tools/hls-est-validate/thesis/frame_chapters.py"


def chapter_generator(path):
    """(title, generator) of a chapter file from its first heading and its 'Generated by' comment."""
    text = path.read_text(errors="replace")
    title = next((l[2:].strip() for l in text.splitlines() if l.startswith("# ")), path.stem)
    m = re.search(r"[Gg]enerated by (\S+)(?: from (\S+))?", text[:2000])
    gen = ("`%s` from `%s`" % (m.group(1), m.group(2).rstrip(";,.")) if m and m.group(2)
           else ("`%s`" % m.group(1) if m else "hand-written (no generator comment)"))
    return title, gen


def write_readme(out, N):
    target = out / "README.md"
    if target.exists() and not target.read_text().startswith(README_MARK):
        print("README.md belongs to another generator: not touched", file=sys.stderr)
        return
    L = [README_MARK + " on %s; re-run it after any chapter changes. -->" % N.values["generated"], "",
         "# hls-est thesis draft", "",
         "Draft chapters of Peter's master's thesis on hls-est (black-box inference of Vitis HLS 2025.1's "
         "BRAM decisions, replicated as MLIR/CIRCT passes). Every chapter is generated: numbers come only "
         "from parsed result files, never typed by hand. Edit a chapter's template "
         "(`tools/hls-est-validate/thesis/templates/`), then re-run its generator.", "",
         "## Chapters", "", "| file | title | generated by |", "|---|---|---|"]
    for p in sorted(out.glob("[0-9][0-9]-*.md")):
        title, gen = chapter_generator(p)
        L.append("| [%s](%s) | %s | %s |" % (p.name, p.name, title, gen))
    L += ["", "Bibliography: " + ", ".join("[%s](%s)" % (p.name, p.name) for p in sorted(out.glob("*.bib"))) +
          " (entries not checked online carry `unverified` in their note).", "",
          "## Generators and their inputs", "",
          "- **`tools/hls-est-validate/thesis/frame_chapters.py`**: chapters " +
          ", ".join(FRAME_CHAPTERS) + "; tables `tables/frame-*.{md,tex}`; figure "
          "`figures/ch07-rtl-funnel.{pdf,png}`; every number with its source in "
          "`data/frame-numbers.json`. Inputs: " + "; ".join(
              "`%s`" % s for s in sorted(set(v.replace(str(Path.home()), "~") for v in N.sources.values() if v))) + ".",
          "- Other generators in `tools/hls-est-validate/thesis/` (for example `make_thesis_tables.py`) "
          "name their inputs in their chapter's header comment and in their `data/*.json` files.", "",
          "## Rebuild", "", "```",
          "~/hls-est-work/coord/scratch/thesis/venv/bin/python tools/hls-est-validate/thesis/frame_chapters.py",
          "```", "", "The venv is private (matplotlib only); with plain `python3` the chapters and tables "
          "render and the figure is skipped.", "",
          "## Tables and figures", ""]
    for d in ("tables", "figures"):
        files = sorted(p.name for p in (out / d).glob("*") if p.suffix in (".md", ".pdf"))
        L.append("- `%s/`: %s" % (d, ", ".join(files)))
    target.write_text("\n".join(L) + "\n")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--out", default=str(DOC / "thesis"))
    args = ap.parse_args()
    out = Path(args.out)
    for d in ("", "tables", "figures", "data"):
        (out / d).mkdir(parents=True, exist_ok=True)

    N = Numbers()
    snap = json.loads((HERE / "ch06_manifest.json").read_text())["snapshot"]
    collect_evaluation(N, out)
    under, _ = collect_comparison(N)
    collect_vitis(N)
    collect_times(N)
    notes = collect_notes(N)
    prow, plugrows = collect_docs(N)
    collect_tests(N)
    collect_invariance(N)
    collect_git(N, snap)
    collect_loc(N, snap)
    funnel, wns = collect_rtl(N)
    N.put("rtl_verilog_pct", pct(N.values["rtl_verilog"], N.values["rtl_catalogue"]), "rtl_verilog / rtl_catalogue")
    for nid, v in notes.items():
        N.put("%s.status" % nid, v["status"], DOC / "notes" / "VITIS_NOTES.md")
        if v["kernels"] is not None:
            N.put("%s.kernels" % nid, v["kernels"], DOC / "notes" / "VITIS_NOTES.md")
    N.put("generated", datetime.date.today().isoformat(), "date of the run")

    # tables
    write_table(out, "frame-pipeline", "Table 5.1. The default hls-est pass pipeline (hls-doc/passes/README.md)",
                ["#", "pass", "kind", "what it does"],
                [[r[0], r[1].split("](")[0].lstrip("["), r[2], r[3]] for r in prow],
                ["r", "l", "l", "6.5cm"], "hls-doc/passes/README.md")
    write_table(out, "frame-plugins", "Table 5.2. Plugin interfaces of hls-est and their default builtins "
                "(hls-doc/plugins.md)", ["interface", "selected by", "builtins (default first)"],
                [[r[0], r[2], r[3]] for r in plugrows], ["l", "5cm", "4.5cm"], "hls-doc/plugins.md")
    top_under = under[:10]
    write_table(out, "frame-undercounts", "Table 8.1. The %d largest under-counts of the final evaluation run" % len(top_under),
                ["dataset", "design", "Vitis", "hls-est", "diff", "largest per-array differences"],
                [[r["dataset"], r["benchmark"][:60], r["vitis_bram_18k"], r["hlsest_bram_18k"],
                  r["diff_hlsest_minus_vitis"], "; ".join(x[:60] for x in r["largest_array_differences"].split("; ")[:2])]
                 for r in top_under], ["l", "4cm", "r", "r", "r", "5.5cm"],
                "tools/hls-est-validate/results/comparison.csv")
    write_table(out, "frame-rtl-coverage", "Table 7.1. RTL back end: coverage of the catalogue (branch rtl-backend, "
                "hls-doc/rtl-coverage.md, %s)" % N.values["rtl_date"], ["stage", "designs"],
                [[l, v] for l, v in funnel], ["l", "r"], "git show rtl-backend:hls-doc/rtl-coverage.md")
    write_table(out, "frame-rtl-timing", "Table 7.2. Out-of-context Vivado synthesis of floating-point RTL kernels "
                "(xc7z020clg400-1, 10 ns; rtl-backend-float.md section 8)",
                ["kernel", "WNS", "critical path", "LUT / FF / DSP", "Vitis csynth estimate"],
                [r[:5] for r in wns], ["3cm", "r", "3.5cm", "l", "3.5cm"],
                "git show rtl-backend:hls-doc/design/rtl-backend-float.md")
    write_table(out, "frame-related-work", "Table 2.2. How hls-est differs from earlier estimation and HLS work",
                ["approach", "representative work", "input", "predicts", "ground truth", "model"],
                [list(r) for r in RELATED], ["2.2cm", "4cm", "2.2cm", "2.6cm", "2cm", "2cm"],
                "hand-written classification (no numbers)")
    have_fig = figure_funnel(out, funnel)
    N.put("fig_funnel", "figures/ch07-rtl-funnel.pdf" if have_fig else "(figure not generated)", "")

    # chapters
    tdir = HERE / "templates"
    for chap in FRAME_CHAPTERS:
        t = tdir / (chap + ".md.in")
        name = chap + ".md"
        text = render(t.read_text(), N.values, t.name)
        hdr = ("<!-- Generated by tools/hls-est-validate/thesis/frame_chapters.py from "
               "tools/hls-est-validate/thesis/templates/%s on %s; numbers: data/frame-numbers.json. "
               "Edit the template, not this file. -->\n\n" % (t.name, N.values["generated"]))
        (out / name).write_text(hdr + text)
    bib = (HERE / "templates" / "references.bib").read_text()
    (out / "references.bib").write_text(bib)   # the one bibliography of every chapter
    (out / "data" / "frame-numbers.json").write_text(json.dumps(
        {k: {"value": N.values[k], "source": N.sources[k]} for k in sorted(N.values)}, indent=1) + "\n")
    write_readme(out, N)
    print("rendered %d chapters, %d numbers" % (len(FRAME_CHAPTERS), len(N.values)))


if __name__ == "__main__":
    main()
