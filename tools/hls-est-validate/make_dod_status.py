#!/usr/bin/env python3
"""Generate hls-doc/dod-status.md: the five items of the definition of done (CLAUDE.md, Peter's /goal of
2026-10-10) checked against the current data, with the MEMOS #70 exclusion list each design falls under.

  (1) cgeist compiles every design into semantically correct MLIR: cgeist status per design (run json) and
      the check_semantics verdict per design (the records of --sem-list / --sem, a later file wins), each
      design without a verdict placed in the list it falls under (make_done_exclusions.classify).
  (2) every design has a cgeist lit test and a mirrored hls-est lit test (the Mirror manifest, the files
      themselves, and a lit result file when given), and hls-est runs every compiled design without an
      error or a timeout (run json).
  (3) the configuration file, the plugin interface and hls-doc/new-architecture.md exist and their lit tests
      (test/hls-est/Config, test/hls-est/Plugins) pass in the lit result file.
  (4) every pass hls-est registers that this project wrote (hls-est --list-passes minus the passes MLIR's own
      Passes.td files define) and every pass of the default pipeline has a page in hls-doc/passes/, the page
      names each of the pass's options (hls-est --help), the pages' index lists it, and
      hls-doc/architecture.md names it.
  (5) goal_band per design (exact, or an over-count of at most make_compare_csv.BAND_OVER, 5 % since
      2026-10-24, MEMOS #95) from results/comparison.csv (DoD 5 names
      hls-doc/comparison.csv; the file moved to tools/hls-est-validate/results/ in P1a, MEMOS #47), with the
      DoD-5 list of done_exclusions_dod5.json.

Every input is named on the page. Anything that does not hold is listed under "Does not hold"; items that
wait for a decision of Peter's are listed under "Waiting for Peter".

Usage:
  python3 make_dod_status.py --run R.json --cmp R.cmp.json --sem-list results/semantics-records.txt \\
      --lit-json lit.json [--cgeist-lit-json cg.json] [--hls-est build/clion/bin/hls-est] \\
      [--out ../../hls-doc/dod-status.md]
"""
import argparse
import csv
import datetime
import json
import re
import subprocess
from pathlib import Path

import make_compare_csv as mcc
import make_done_exclusions as mde

HERE = Path(__file__).resolve().parent
CIRCT = HERE.parent.parent
HLSDOC = CIRCT / "hls-doc"
POLYGEIST_HLS_TESTS = Path("/mnt/d/HLS/Polygeist/tools/cgeist/Test/HLS")
MLIR_PASS_TD_ROOT = CIRCT / "llvm" / "mlir" / "include" / "mlir"
LIT_PASS = ("PASS", "XFAIL", "UNSUPPORTED")
IN_BAND = mcc.IN_BAND   # make_compare_csv.py's goal_band values that are in the DoD-5 band


def md(s):
    return mde.md_escape(s)


# ----------------------------------------------------------------------------------------------- lit --

def load_lit(path):
    """{test path relative to the suite root: result code} of an llvm-lit `-o` JSON file, or None."""
    if not path:
        return None
    data = json.loads(Path(path).read_text())
    out = {}
    for t in data.get("tests", []):
        name = t.get("name", "")
        rel = name.split(" :: ", 1)[1] if " :: " in name else name
        # CIRCT's suite names a test by its path under test/ ("hls-est/Config/x.mlir"); keys here are
        # relative to test/hls-est, Polygeist's by its path under its suite root
        rel = rel[len("hls-est/"):] if rel.startswith("hls-est/") else rel
        out[rel] = t.get("code", "?")
    return out


def lit_summary(lit):
    counts = {}
    for code in lit.values():
        counts[code] = counts.get(code, 0) + 1
    return ", ".join("%s %d" % (k, v) for k, v in sorted(counts.items()))


# ---------------------------------------------------------------------------------------------- DoD 1 --

def dod1(d):
    """Per design: cgeist status, semantic verdict and the list it falls under."""
    run, sem = d["run"], d["sem"]
    rejects = {r[0] for r in d["rejects"]}
    defects = {r[0]: r[1] for r in d["defects"]}
    limits = {r[0]: r[1] for r in d["input_limits"]}
    proposed = {r[0] for r in d["proposed"]}
    mlir_only = {r[0] for r in d["mlir_only"]}
    no_verdict = {r[0] for r in d["no_verdict"]}
    rows, fails = [], []
    for k in sorted(run):
        r = run[k]
        s = sem.get(k) or {}
        verdict = s.get("status") or "no record"
        cg = r.get("cgeist_status") or "?"
        if k in rejects:
            cls = "done: (1) Vitis rejects the source"
        elif cg != "ok":
            cls = "DOES NOT HOLD: cgeist fails and Vitis does not reject the source"
        elif k in defects:
            cls = "done: (2) defective reference (%s)" % defects[k]
        elif verdict == "equal":
            cls = "done: bit-exact"
        elif verdict == "mismatch":
            cls = "DOES NOT HOLD: mismatch with no defective-reference class"
        elif k in mlir_only:
            cls = "out of scope: hand-written MLIR, no C source"
        elif k in proposed:
            cls = "waiting for Peter: proposed for (2), the reference never returns"
        elif k in limits:
            cls = "DOES NOT HOLD: the driver's inputs are outside the source's domain (%s)" % limits[k]
        elif mde.VITIS_MATH_LIBRARY.search(str(s.get("reason") or "")):
            cls = ("DOES NOT HOLD: needs Vitis' C-simulation math library, allowed by MEMOS #94: re-run "
                   "check_semantics (the record predates --vitis-mathlib)")
        elif k in no_verdict:
            cls = "DOES NOT HOLD: no verdict, not classified"
        else:
            cls = "DOES NOT HOLD: no verdict, not classified"
        rows.append((k, cg, verdict, cls))
        if cls.startswith("DOES NOT HOLD"):
            fails.append((k, cls + "; " + str(s.get("reason") or "")[:200]))
    return rows, fails


# ---------------------------------------------------------------------------------------------- DoD 2 --

def has_run_line(path):
    try:
        return "RUN:" in Path(path).read_text(errors="replace")
    except OSError:
        return False


def dod2(d, manifest, lit, cglit=None):
    """Per design: its cgeist lit test, its hls-est lit test (Mirror, or the hand-written MLIR itself for an
    mlir-only design) with its lit result, and hls-est's status in the run."""
    run = d["run"]
    rejects = {r[0] for r in d["rejects"]}
    by_design = {}
    for t in manifest["tests"]:
        if t.get("design"):
            by_design.setdefault(t["design"], []).append(t)
    rows, fails = [], []
    for k in sorted(run):
        r = run[k]
        tests = by_design.get(k, [])
        mlir_only = r.get("mode") == "mlir-only"
        if mlir_only:
            cg_test = "n/a (hand-written MLIR)"
            hl_path = Path(r.get("mlir") or "")
            hl_rel = str(hl_path.relative_to(CIRCT / "test" / "hls-est")) if str(hl_path).startswith(
                str(CIRCT / "test" / "hls-est")) else str(hl_path)
            cg_ok = True
            hl_ok = hl_path.is_file() and has_run_line(hl_path)
        else:
            t = tests[0] if tests else None
            cg_file = POLYGEIST_HLS_TESTS / t["test"] if t else None
            cg_test = t["test"] if t else "missing"
            cg_ok = bool(cg_file and cg_file.is_file())
            hl_rel = t.get("mirror") if t else None
            hl_rel = str(Path(hl_rel).relative_to("test/hls-est")) if hl_rel else None
            hl_ok = bool(hl_rel and (CIRCT / "test" / "hls-est" / hl_rel).is_file())
        lit_code = (lit.get(hl_rel, "not run") if (lit is not None and hl_rel) else "-")
        cg_code = ("-" if mlir_only or cglit is None or not tests else
                   cglit.get("HLS/" + tests[0]["test"], "not run"))
        status = r.get("status") or "?"
        elapsed = r.get("elapsed_s")
        problems = []
        if k in rejects:
            cls = "done: (1) Vitis rejects the source"
        else:
            if not cg_ok:
                problems.append("no cgeist lit test")
            if not hl_ok:
                problems.append("no hls-est lit test")
            if lit is not None and hl_ok and lit_code not in LIT_PASS:
                problems.append("hls-est lit test %s" % lit_code)
            if cglit is not None and not mlir_only and cg_ok and cg_code not in LIT_PASS:
                problems.append("cgeist lit test %s" % cg_code)
            if status != "ok":
                problems.append("hls-est: %s" % status)
            cls = "DOES NOT HOLD: " + "; ".join(problems) if problems else "holds"
        rows.append((k, cg_test, cg_code, hl_rel or "-", lit_code, status, elapsed, cls))
        if problems and k not in rejects:
            fails.append((k, "; ".join(problems)))
    return rows, fails


# ---------------------------------------------------------------------------------------------- DoD 3 --

def dod3(lit):
    checks, fails = [], []
    for f in ("configuration.md", "plugins.md", "new-architecture.md"):
        ok = (HLSDOC / f).is_file()
        checks.append(("hls-doc/%s exists" % f, "yes" if ok else "no"))
        if not ok:
            fails.append(("hls-doc/%s" % f, "missing"))
    for sub in ("Config", "Plugins"):
        files = sorted(p for p in (CIRCT / "test" / "hls-est" / sub).glob("*.mlir"))
        if lit is None:
            checks.append(("test/hls-est/%s: %d lit tests" % (sub, len(files)), "no lit result given"))
            fails.append(("test/hls-est/%s" % sub, "no lit result given"))
            continue
        bad = [(p.name, lit.get("%s/%s" % (sub, p.name), "not run")) for p in files]
        bad = [(n, c) for n, c in bad if c not in LIT_PASS]
        checks.append(("test/hls-est/%s: %d lit tests" % (sub, len(files)),
                       "all pass" if not bad else "; ".join("%s %s" % b for b in bad)))
        fails += [("test/hls-est/%s/%s" % (sub, n), c) for n, c in bad]
    na = (HLSDOC / "new-architecture.md").read_text() if (HLSDOC / "new-architecture.md").is_file() else ""
    # the lit tests the page names (an Inputs/ file is a test's input, not a test)
    for ref in sorted(set(r for r in re.findall(r"`(test/hls-est/[^`]+\.mlir)`", na) if "/Inputs/" not in r)):
        rel = ref[len("test/hls-est/"):]
        code = lit.get(rel, "not run") if lit is not None else "-"
        checks.append(("new-architecture.md's worked example %s" % ref, code))
        if lit is not None and code not in LIT_PASS:
            fails.append((ref, code))
    return checks, fails


# ---------------------------------------------------------------------------------------------- DoD 4 --

def help_passes(hls_est):
    """{pass: [option names]} from `hls-est --help` (a pass at six spaces, its options at eight)."""
    out = subprocess.run([hls_est, "--help"], capture_output=True, text=True, check=True).stdout
    passes, cur = {}, None
    for ln in out.splitlines():
        m = re.match(r"^      --([a-z0-9-]+)", ln)
        if m:
            cur = m.group(1)
            passes[cur] = []
            continue
        m = re.match(r"^        --([a-z0-9-]+)", ln)
        if m and cur:
            passes[cur].append(m.group(1))
            continue
        if not ln.startswith("    "):
            cur = None
    return passes


def upstream_passes():
    names = set()
    for td in MLIR_PASS_TD_ROOT.rglob("*.td"):
        names |= set(re.findall(r'Pass<"([a-z0-9-]+)"', td.read_text(errors="replace")))
    return names


def dod4(hls_est, pipeline):
    helped = help_passes(hls_est)
    listed = subprocess.run([hls_est, "--list-passes"], capture_output=True, text=True, check=True).stdout
    registered = re.findall(r"^  --([a-z0-9-]+)", listed, re.M)
    upstream = upstream_passes()
    own = [p for p in registered if p not in upstream]
    in_pipeline = [re.sub(r"=.*", "", tok.lstrip("-")) for tok in pipeline.split()]
    wanted = own + [p for p in in_pipeline if p not in own]
    arch = (HLSDOC / "architecture.md").read_text()
    index = (HLSDOC / "passes" / "README.md").read_text()
    rows, fails = [], []
    for p in wanted:
        page = HLSDOC / "passes" / ("%s.md" % p)
        text = page.read_text() if page.is_file() else ""
        opts = helped.get(p, []) if p in own else []
        missing_opts = [o for o in opts if not re.search(r"(--|\b)%s\b" % re.escape(o), text)]
        in_arch = bool(re.search(r"(--|`)%s\b" % re.escape(p), arch))
        in_index = "(%s.md)" % p in index
        problems = []
        if not text:
            problems.append("no page")
        if missing_opts:
            problems.append("page does not name option(s) %s" % ", ".join("`%s`" % o for o in missing_opts))
        if not in_index:
            problems.append("not in hls-doc/passes/README.md")
        if not in_arch:
            problems.append("not named in hls-doc/architecture.md")
        origin = "hls-est" if p in own else "MLIR (default pipeline)"
        rows.append((p, origin, "yes" if text else "no", len(opts), "yes" if in_index else "no",
                     "yes" if in_arch else "no", "; ".join(problems) or "holds"))
        if problems:
            fails.append(("--" + p, "; ".join(problems)))
    return rows, fails, len(registered), len(own)


# ---------------------------------------------------------------------------------------------- DoD 5 --

def dod5(comparison_csv, d):
    with open(comparison_csv, newline="") as f:
        rows = list(csv.DictReader(f))
    listed = {e["key"]: e for e in d["dod5"]}
    counts, out, fails = {}, [], []
    for r in rows:
        key = "%s/%s" % (r["dataset"], r["benchmark"])
        band = r.get("goal_band") or ""
        if r.get("comparison_status") != "compared":
            continue
        counts[band] = counts.get(band, 0) + 1
        if band not in IN_BAND:
            entry = listed.get(key)
            state = ("on the DoD-5 list (%s)" % entry["status"]) if entry else "DOES NOT HOLD: out of band, not listed"
            out.append((key, r["hlsest_bram_18k"], r["vitis_bram_18k"], r["diff_hlsest_minus_vitis"], band, state))
            if not entry:
                fails.append((key, "out of band (%s), not on the DoD-5 list" % band))
    # the CSV must be the run's: the compare json's compared count and bands agree with it
    cmp_compared = len(d["compared"])
    csv_compared = sum(counts.values())
    if cmp_compared != csv_compared:
        fails.append((str(comparison_csv), "has %d compared rows, the compare json %d: regenerate it" %
                      (csv_compared, cmp_compared)))
    return counts, out, fails


# ----------------------------------------------------------------------------------------------- page --

def verdict_word(fails, waiting):
    """The 'holds' cell of an item: no (with the count) when a check fails, else yes, naming the designs
    that hold only through an entry still waiting for Peter."""
    if fails:
        return "no (%d)" % len(fails)
    if waiting:
        return "yes with the MEMOS #70 lists, except %d design(s) waiting for Peter" % waiting
    return "yes with the MEMOS #70 lists"


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--run", required=True)
    ap.add_argument("--cmp", required=True)
    ap.add_argument("--vitis", default=str(HERE / "results" / "vitis.json"))
    ap.add_argument("--sem", nargs="*", default=[])
    ap.add_argument("--sem-list", default=str(HERE / "results" / "semantics-records.txt"))
    ap.add_argument("--dod5", default=str(HERE / "done_exclusions_dod5.json"))
    ap.add_argument("--manifest", default=str(CIRCT / "test" / "hls-est" / "Mirror" / "manifest.json"))
    ap.add_argument("--comparison", default=str(HERE / "results" / "comparison.csv"))
    ap.add_argument("--lit-json", help="llvm-lit -o JSON of a full test/hls-est run")
    ap.add_argument("--cgeist-lit-json", help="llvm-lit -o JSON of Polygeist's cgeist lit run (summary only)")
    ap.add_argument("--hls-est", default=str(CIRCT / "build" / "clion" / "bin" / "hls-est"))
    ap.add_argument("--out", default=str(HLSDOC / "dod-status.md"))
    args = ap.parse_args()
    args.sem = mde.read_sem_list(args.sem_list) + list(args.sem)

    import common
    d = mde.classify(args)
    manifest = json.loads(Path(args.manifest).read_text())
    lit = load_lit(args.lit_json)
    cglit = load_lit(args.cgeist_lit_json)

    r1, f1 = dod1(d)
    r2, f2 = dod2(d, manifest, lit, cglit)
    c3, f3 = dod3(lit)
    r4, f4, n_reg, n_own = dod4(args.hls_est, common.DEFAULT_PIPELINE)
    counts5, r5, f5 = dod5(args.comparison, d)

    run = d["run"]
    n = len(run)
    cg_ok = sum(1 for r in run.values() if r.get("cgeist_status") == "ok")
    verdicts = {}
    for k, cg, v, cls in r1:
        verdicts[cls] = verdicts.get(cls, 0) + 1
    hl_ok = sum(1 for r in run.values() if r.get("status") == "ok")
    slowest = max((r.get("elapsed_s") or 0, k) for k, r in run.items())
    waiting1 = [(k, cls) for k, cg, v, cls in r1 if cls.startswith("waiting")]

    L = []
    L.append("# Definition of done: status")
    L.append("")
    L.append("<!-- Generated by tools/hls-est-validate/make_dod_status.py on %s. Do not edit: change the inputs and"
             " re-run the script. -->" % datetime.date.today().isoformat())
    L.append("")
    L.append("The five items of the definition of done (CLAUDE.md, Peter, 2026-10-10), each checked against the"
             " data below. Exclusions follow MEMOS decision #70 and are listed with their evidence in"
             " [done-exclusions.md](done-exclusions.md).")
    L.append("")
    L.append("Inputs:")
    L.append("")
    L.append("- run: `%s` (%d designs); compare: `%s`" % (args.run, n, args.cmp))
    L.append("- Vitis ground truth: `%s`; DoD-5 list: `%s`" % (args.vitis, args.dod5))
    L.append("- semantics: %d check_semantics records (`%s`, then --sem; a later file wins for a design)" % (
        len(args.sem), args.sem_list))
    L.append("- lit tests: Mirror manifest `%s`; hls-est lit result `%s`%s" % (
        args.manifest, args.lit_json or "(none)", ("; cgeist lit result `%s`" % args.cgeist_lit_json)
        if args.cgeist_lit_json else ""))
    L.append("- passes: `%s --list-passes` and `--help`; MLIR's own pass definitions under `%s`" % (
        args.hls_est, MLIR_PASS_TD_ROOT))
    L.append("- goal band: `%s` (DoD 5 names hls-doc/comparison.csv; it moved to tools/hls-est-validate/results/"
             " in P1a, MEMOS #47)" % args.comparison)
    L.append("")
    allfails = [("1", k, w) for k, w in f1] + [("2", k, w) for k, w in f2] + [("3", k, w) for k, w in f3] + \
               [("4", k, w) for k, w in f4] + [("5", k, w) for k, w in f5]
    L.append("## Summary")
    L.append("")
    L.append("| item | holds | numbers |")
    L.append("|---|---|---|")
    L.append("| 1. cgeist compiles every design into semantically correct MLIR | %s | %d designs, cgeist ok %d;"
             " %s |" % (verdict_word(f1, len(waiting1)), n, cg_ok,
                        "; ".join("%s %d" % (k, v) for k, v in sorted(verdicts.items()))))
    L.append("| 2. every design has a cgeist and a Mirror hls-est lit test; hls-est runs every compiled design |"
             " %s | hls-est ok %d of %d; slowest %.0f s (%s); hls-est lit: %s%s |" % (
                 "yes, with the listed exclusions" if not f2 else "no (%d)" % len(f2), hl_ok, n, slowest[0],
                 slowest[1], lit_summary(lit) if lit is not None else "not given",
                 ("; cgeist lit: %s" % lit_summary(cglit)) if cglit is not None else ""))
    L.append("| 3. configuration file, plugins, new-architecture.md and their lit tests | %s | %s |" % (
        "yes" if not f3 else "no (%d)" % len(f3), "; ".join("%s: %s" % c for c in c3)))
    L.append("| 4. a page per pass in hls-doc/passes/, architecture.md names every pass | %s | %d passes registered,"
             " %d written by this project, %d checked (with the default pipeline's MLIR passes) |" % (
                 "yes" if not f4 else "no (%d)" % len(f4), n_reg, n_own, len(r4)))
    L.append("| 5. BRAM equal to Vitis or at most %s over | %s | %d compared: %s; out of band: %d (%d on the"
             " DoD-5 list) |" % (
                 mcc.BAND_TEXT, verdict_word(f5, sum(1 for r in r5 if "proposed" in r[5])), sum(counts5.values()),
                 "; ".join("%s %d" % (k, v) for k, v in sorted(counts5.items())), len(r5),
                 sum(1 for r in r5 if r[5].startswith("on the"))))
    L.append("")
    L.append("## Does not hold (%d)" % len(allfails))
    L.append("")
    if allfails:
        L.append("| item | what | why |")
        L.append("|---|---|---|")
        for it, k, w in allfails:
            L.append("| %s | %s | %s |" % (it, md(k), md(w)))
    else:
        L.append("Nothing: every check below holds or falls under a MEMOS #70 exclusion.")
    L.append("")
    waiting = waiting1 + [(r[0], "DoD-5 list entry: %s" % r[5]) for r in r5 if "proposed" in r[5]]
    L.append("## Waiting for Peter (%d)" % len(waiting))
    L.append("")
    L.append("| design | decision |")
    L.append("|---|---|")
    for k, w in waiting:
        L.append("| %s | %s |" % (md(k), md(w)))
    L.append("")
    L.append("## 1. Semantics per design")
    L.append("")
    L.append("A design counts when check_semantics finds its MLIR bit-exact against the native build, or when it is"
             " on a MEMOS #70 list; a design Vitis rejects counts under (1) whatever check_semantics said (a verdict"
             " for another function of the files does not count).")
    L.append("")
    L.append("| design | cgeist | check_semantics | counts as |")
    L.append("|---|---|---|---|")
    for k, cg, v, cls in r1:
        if cls == "done: bit-exact":
            continue
        L.append("| %s | %s | %s | %s |" % (md(k), md(cg[:60]), md(v), md(cls)))
    L.append("")
    L.append("Designs not shown above are bit-exact (%d)." % verdicts.get("done: bit-exact", 0))
    L.append("")
    L.append("## 2. Lit tests and hls-est runs per design (only rows that are not plain passes)")
    L.append("")
    L.append("| design | cgeist lit test | its lit result | hls-est lit test | its lit result | hls-est | s |"
             " counts as |")
    L.append("|---|---|---|---|---|---|---:|---|")
    plain = 0
    for k, cg, cgc, hl, code, st, el, cls in r2:
        if cls == "holds" and not cg.startswith("n/a"):
            plain += 1
            continue
        L.append("| %s | %s | %s | %s | %s | %s | %s | %s |" % (md(k), md(cg), cgc, md(hl), code, md(st[:60]),
                                                                "%.0f" % el if el else "-", md(cls)))
    L.append("")
    L.append("%d other designs have both lit tests, passing%s, and an hls-est run without error or timeout." % (
        plain, "" if (lit is not None and cglit is not None) else " (a lit result file was not given: not checked)"))
    L.append("")
    L.append("## 3. Configuration and plugins")
    L.append("")
    L.append("| check | result |")
    L.append("|---|---|")
    for c in c3:
        L.append("| %s | %s |" % (md(c[0]), md(c[1])))
    L.append("")
    L.append("## 4. Pass pages")
    L.append("")
    L.append("| pass | origin | page | options | in passes/README.md | in architecture.md | result |")
    L.append("|---|---|---|---:|---|---|---|")
    for row in r4:
        L.append("| `--%s` | %s | %s | %d | %s | %s | %s |" % (row[0], row[1], row[2], row[3], row[4], row[5],
                                                               md(row[6])))
    L.append("")
    L.append("## 5. Out of band")
    L.append("")
    L.append("| design | hls-est | Vitis | difference | band | state |")
    L.append("|---|---:|---:|---:|---|---|")
    for row in r5:
        L.append("| %s | %s | %s | %s | %s | %s |" % tuple(md(x) for x in row))
    L.append("")
    Path(args.out).write_text("\n".join(L) + "\n")
    print("wrote %s: %d checks do not hold (1: %d, 2: %d, 3: %d, 4: %d, 5: %d), %d waiting for Peter" % (
        args.out, len(allfails), len(f1), len(f2), len(f3), len(f4), len(f5), len(waiting)))


if __name__ == "__main__":
    main()
