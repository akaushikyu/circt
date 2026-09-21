#!/usr/bin/env python3
"""Generate hls-doc/done-exclusions.md: the lists of MEMOS decision #70 (Peter, 2026-10-20).

(1) DoD 1 / 2: designs whose source Vitis 2025.1 itself rejects (its log has the error line): done,
    listed with that line (MEMOS #70 includes a catalogue top that no source defines, [HLS 214-157]).
    Failures that are not the source's (a Vitis crash, a path Vitis split at a space, a missing file
    that exists now) are listed apart and are not exclusions.
(2) DoD 1: designs whose native reference build is defective (uninitialised reads, AddressSanitizer
    reports, a native build or testbench that fails; not TAPA's host runtime, W9r9 review D6): they
    cannot be verified by check_semantics and count as done when cgeist compiles them; the reason is
    recorded per design.
(3) DoD 5: the short list of designs that may stay out of band (curated in done_exclusions_dod5.json,
    each entry with the per-array cause, the Vitis evidence and why it is out of scope), checked against
    the run; every other out-of-band design is listed as open work.

Inputs (all named on the generated page): a run_hlsest.py result (--run), its compare.py output (--cmp),
the Vitis ground truth (--vitis, default results/vitis.json), check_semantics.py records (--sem, several;
a later file wins for a design), and the curated DoD-5 list (--dod5).

Usage:
  python3 make_done_exclusions.py --run R.json --cmp R.cmp.json --sem a.json b.json ... \\
      [--dod5 done_exclusions_dod5.json] [--out ../../hls-doc/done-exclusions.md]
"""
import argparse
import datetime
import json
import os
import re
from pathlib import Path

HERE = Path(__file__).resolve().parent

# Vitis front-end / elaboration errors that reject the source itself (MEMOS #70 (1)).
VITIS_REJECT = re.compile(r"ERROR: \[HLS (207-\d+|200-70|214-139|214-157)\][^\n]*")

# check_semantics.py "n/a" reasons that mean the native reference is defective (MEMOS #70 (2)),
# in the order they are tried: (class, regex).
NATIVE_DEFECT = [
    ("reads uninitialised memory", re.compile(r"reads uninitialised memory")),
    ("divides by zero (AddressSanitizer FPE)", re.compile(r"AddressSanitizer: FPE")),
    ("AddressSanitizer memory error", re.compile(r"AddressSanitizer: (heap|stack|global)-buffer-overflow|AddressSanitizer: SEGV")),
    ("native build fails", re.compile(r"native build (of .* fails|does not link)")),
    ("native reference aborts", re.compile(r"reference exit -\d+")),
]


def load(path):
    with open(path) as f:
        return json.load(f)


def rows_of(run):
    return {k: v for k, v in run.items() if not k.startswith("_") and isinstance(v, dict)}


def md_escape(s):
    return str(s).replace("|", "\\|").replace("\n", " ")


VITIS_CRASH = re.compile(r"EXCEPTION_ACCESS_VIOLATION|Abnormal program termination|Stack dump")
SPLIT_PATH = re.compile(r"\[HLS 200-40\] Cannot find design file")
MISSING_FILE = re.compile(r"\[HLS 207-812\] '([^']+)' file not found \(([A-Za-z]):/([^:]+):\d+:\d+\)")


TB_FILE = re.compile(r"^[ \t]*add_files[ \t]+-tb[ \t]+([^\s;\[\]$]+)[ \t]*$", re.M)
ERROR_FILE = re.compile(r"\(([A-Za-z]:/[^:()]+):\d+:\d+\)")
REL_ERROR_FILE = re.compile(r"\(([^:()]+):\d+:\d+\)")
TOP_NOT_FOUND = re.compile(r"no function named '([^']+)'")
_CATALOG = None


def catalog_record(key):
    """The HLSFactory v2 catalogue record of `key` (designs.load_hlsfactory_v2), or None."""
    global _CATALOG
    if _CATALOG is None:
        import designs
        _CATALOG = {"%s/%s" % (d["dataset"], d["benchmark"]): d for d in designs.load_hlsfactory_v2()}
    return _CATALOG.get(key)


def stale_catalogue_script(line, key):
    """Why a reject-looking line comes from the catalogue's synthesis script rather than the source
    (W9r9 review D5), or ''.  (a) [HLS 214-157] (top not found) when the script's own testbench files are
    not in the design tree: the script was copied from another project (class_ece8893 lab3 scripts that
    name lab2's compute_attention_HLS and its Q/K/V tensors), and any other [HLS 214-157]: a top the
    script sets but no compiled source defines is a defect of the script (W9r10 review D3, Dehazing
    debayer_csynth).  (b) any error of a design none of whose script design files exists (the harness's
    fallback compiled every C/C++ file of the tree, e.g. a generate_matrices.cpp helper next to a script
    that adds a missing top_dense.cpp, or Monte-Carlo's genRandNums.cpp next to a script that adds an
    absent mersenneTwister.cpp)."""
    rec = catalog_record(key)
    if not rec:
        return ""
    v2 = rec.get("v2") or {}
    script = (v2.get("tcl") or {}).get("script")
    tree = rec.get("v2_dir") or rec.get("dir")
    if not script or not tree:
        return ""
    try:
        text = (Path(tree) / script).read_text(errors="replace")
    except OSError:
        return ""
    if "214-157" in line:
        absent = [f for f in TB_FILE.findall(text) if not (Path(tree) / f).exists()]
        if absent:
            return ("stale catalogue script: %s names a top no source defines and adds testbench files the "
                    "design tree does not hold (%s); it belongs to another project, the design needs its own "
                    "top and a Vitis re-run" % (script, ", ".join(absent[:3])))
        # W9r10 review D3: "Top function not found" is a property of the script (its set_top), never a
        # rejection of the source (Dehazing debayer_csynth sets top 'pipeline'; the source's top is
        # img_pipeline).
        top = TOP_NOT_FOUND.search(line)
        return ("stale catalogue script: %s sets top '%s', which no compiled source defines; a defect of "
                "the script, not a rejection of the source; the design needs its own top and a Vitis "
                "re-run" % (script, top.group(1) if top else "?"))
    if v2.get("source_rule") == "fallback":
        # W9r10 review D3: none of the script's design files exists, so Vitis compiled the harness's choice
        # of files, not the author's design (also when the error is in a file the script names, e.g. a
        # header that the absent design files would have provided).
        m = ERROR_FILE.search(line) or REL_ERROR_FILE.search(line)
        where = (", the error is in %s" % Path(m.group(1)).name) if m else ""
        return ("harness fallback: %s adds no existing design file (%s), so every C/C++ file was compiled%s; "
                "the design needs its own file list and a Vitis re-run"
                % (script, "; ".join(v2.get("source_notes", [])[:1]), where))
    return ""


def not_a_rejection(line, log_text, v, key=""):
    """Why a Vitis failure with a reject-looking error line is not a rejection of the source, or ''."""
    if VITIS_CRASH.search(log_text):
        return "Vitis crashed (EXCEPTION_ACCESS_VIOLATION after the error line): not a rejection"
    if SPLIT_PATH.search(log_text):
        return ("harness path bug: a source path with whitespace was split ([HLS 200-40]); fixed in "
                "run_vitis.py (stage_spaced_design), needs a Vitis re-run")
    m = MISSING_FILE.search(line)
    if m:
        inc, drive, src = m.groups()
        src = Path("/mnt/%s/%s" % (drive.lower(), src))
        if not inc.startswith("/") and (src.parent / inc).exists():
            return ("stale: '%s' exists now (next to %s); the Vitis result predates it and needs a "
                    "re-run" % (inc, src.name))
    return stale_catalogue_script(line, key) if key else ""


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--run", required=True, help="run_hlsest.py result json")
    ap.add_argument("--cmp", required=True, help="compare.py output json of that run")
    ap.add_argument("--vitis", default=str(HERE / "results" / "vitis.json"))
    ap.add_argument("--sem", nargs="*", default=[], help="check_semantics.py records (later wins)")
    ap.add_argument("--dod5", default=str(HERE / "done_exclusions_dod5.json"))
    ap.add_argument("--out", default=str(HERE.parent.parent / "hls-doc" / "done-exclusions.md"))
    args = ap.parse_args()

    run = rows_of(load(args.run))
    cmp_rows = {r["key"]: r for r in load(args.cmp)["rows"]}
    vitis = load(args.vitis)
    sem = {}
    for f in args.sem:
        for k, v in rows_of(load(f)).items():
            sem[k] = v
    dod5 = load(args.dod5)["entries"]

    # (1) Vitis rejects the source: an error line of VITIS_REJECT in the record or its log, unless the
    # log shows that the failure is not the source's (W9 round 8 review defect 2): a Vitis crash, a
    # harness path that Vitis split at a space, or a missing file that exists now (a stale run).  Those
    # are listed apart and are not exclusions.
    rejects, not_rejects = [], []
    for k in sorted(run):
        r = run[k]
        v = vitis.get(k) or {}
        if v.get("status") in (None, "ok"):
            continue
        log_text = ""
        log = Path(v.get("cache_dir") or "/nonexistent") / "log" / "hls_compile.log"
        if log.exists():
            log_text = log.read_text(errors="replace")
        m = VITIS_REJECT.search(v.get("note") or "") or VITIS_REJECT.search(log_text)
        if not m:
            # A run stopped by the harness (memory cap, time limit) rejected nothing: listed with
            # the failures that are not rejections (W9r11-impl: kaihong_lin lab3, 8 GB cap).
            status = str(v.get("status") or "")
            if "memory limit" in status or "timeout" in status:
                not_rejects.append((k, status + (f" ({v.get('note')})" if v.get("note") else ""),
                                    r.get("cgeist_status"), r.get("status"),
                                    "the harness stopped the Vitis run (resource limit), not a rejection"))
            continue
        line = m.group(0)
        why = not_a_rejection(line, log_text, v, k)
        row = (k, line, r.get("cgeist_status"), r.get("status"))
        if why:
            not_rejects.append(row + (why,))
        else:
            rejects.append(row)

    # (2) Defective native reference.
    defects = []
    for k in sorted(run):
        s = sem.get(k)
        if not s or s.get("status") != "n/a":
            continue
        reason = str(s.get("reason") or "")
        for cls, rx in NATIVE_DEFECT:
            if rx.search(reason):
                defects.append((k, cls, reason, run[k].get("cgeist_status")))
                break

    # (3) DoD 5.
    def band(row):
        if row.get("status") != "compared":
            return None
        h, v = row.get("hlsest_bram"), row.get("vitis_bram")
        if h is None or v is None:
            return None
        if h == v:
            return "exact"
        if h > v and h <= v * 1.15:
            return "over <= 15 %"
        return "out of band"
    compared = [r for r in cmp_rows.values() if r.get("status") == "compared"]
    bands = {r["key"]: band(r) for r in compared}
    out_of_band = sorted(k for k, b in bands.items() if b == "out of band")
    listed = {e["key"]: e for e in dod5}
    open_work = [k for k in out_of_band if k not in listed]

    now = datetime.date.today().isoformat()
    L = []
    L.append("# Exclusions in the definition of done (MEMOS #70)")
    L.append("")
    L.append("<!-- Generated by tools/hls-est-validate/make_done_exclusions.py on %s. Do not edit: change the"
             " inputs and re-run the script. -->" % now)
    L.append("")
    L.append("Peter, 2026-10-20 (MEMOS decision #70, \"I agree with the exclusion\"): (1) for DoD 1 and 2 a design"
             " whose source Vitis 2025.1 itself rejects counts as done and is listed with its Vitis log line; (2) for"
             " DoD 1 a design whose native reference build is defective cannot be verified by check_semantics and"
             " counts as done when cgeist compiles it, with the reason per design; (3) for DoD 5 a design may stay out"
             " of band only on a short documented list. The goal is met when every design is in band, done, or on a"
             " list.")
    L.append("")
    L.append("Inputs:")
    L.append("")
    L.append("- run: `%s` (%d designs)" % (args.run, len(run)))
    L.append("- compare: `%s` (%d compared)" % (args.cmp, len(compared)))
    L.append("- Vitis ground truth: `%s`" % args.vitis)
    for f in args.sem:
        L.append("- semantics: `%s`" % f)
    L.append("- DoD-5 list: `%s`" % args.dod5)
    L.append("")
    L.append("## (1) Designs Vitis 2025.1 rejects (%d)" % len(rejects))
    L.append("")
    L.append("| design | Vitis log line | cgeist | hls-est |")
    L.append("|---|---|---|---|")
    for k, line, cg, st in rejects:
        L.append("| %s | %s | %s | %s |" % (md_escape(k), md_escape(line[:200]), md_escape((cg or "-")[:60]),
                                          md_escape(st or "-")))
    L.append("")
    L.append("### Vitis failures that are not rejections of the source (%d, not excluded)" % len(not_rejects))
    L.append("")
    L.append("| design | Vitis log line | why it is not a rejection | cgeist | hls-est |")
    L.append("|---|---|---|---|---|")
    for k, line, cg, st, why in not_rejects:
        L.append("| %s | %s | %s | %s | %s |" % (md_escape(k), md_escape(line[:160]), md_escape(why),
                                               md_escape((cg or "-")[:60]), md_escape(st or "-")))
    L.append("")
    L.append("## (2) Designs whose native reference is defective (%d)" % len(defects))
    L.append("")
    byclass = {}
    for d in defects:
        byclass.setdefault(d[1], []).append(d)
    for cls, _ in NATIVE_DEFECT:
        ds = byclass.get(cls, [])
        if not ds:
            continue
        L.append("### %s (%d)" % (cls, len(ds)))
        L.append("")
        L.append("| design | check_semantics reason | cgeist |")
        L.append("|---|---|---|")
        for k, _, reason, cg in ds:
            L.append("| %s | %s | %s |" % (md_escape(k), md_escape(reason[:200]), md_escape(cg or "-")))
        L.append("")
    L.append("## (3) DoD 5: designs that may stay out of band (%d listed)" % len(dod5))
    L.append("")
    L.append("Band: hls-est equals Vitis or over-counts by at most 15 %% (under-counts are out of band). Of %d"
             " compared designs, %d are exact, %d over by at most 15 %%, %d out of band; %d of these are on the"
             " list below and %d are open work." % (
                 len(compared), sum(1 for b in bands.values() if b == "exact"),
                 sum(1 for b in bands.values() if b == "over <= 15 %"), len(out_of_band),
                 sum(1 for k in out_of_band if k in listed), len(open_work)))
    L.append("")
    L.append("| design | hls-est | Vitis | band in this run | per-array cause | Vitis evidence | why out of scope | status |")
    L.append("|---|---:|---:|---|---|---|---|---|")
    for e in dod5:
        r = cmp_rows.get(e["key"], {})
        L.append("| %s | %s | %s | %s | %s | %s | %s | %s |" % (
            md_escape(e["key"]), r.get("hlsest_bram", "-"), r.get("vitis_bram", "-"),
            bands.get(e["key"]) or r.get("status", "not in run"), md_escape(e["cause"]),
            md_escape(e["vitis_evidence"]), md_escape(e["why_out_of_scope"]), md_escape(e["status"])))
    L.append("")
    L.append("### Out of band and not on the list (open work, %d)" % len(open_work))
    L.append("")
    L.append("| design | hls-est | Vitis | difference |")
    L.append("|---|---:|---:|---:|")
    for k in sorted(open_work, key=lambda k: -abs(cmp_rows[k]["hlsest_bram"] - cmp_rows[k]["vitis_bram"])):
        r = cmp_rows[k]
        L.append("| %s | %d | %d | %+d |" % (md_escape(k), r["hlsest_bram"], r["vitis_bram"],
                                            r["hlsest_bram"] - r["vitis_bram"]))
    L.append("")
    Path(args.out).write_text("\n".join(L) + "\n")
    print("wrote %s: %d rejects, %d not rejections, %d defective references, %d listed, %d open" % (
        args.out, len(rejects), len(not_rejects), len(defects), len(dod5), len(open_work)))


if __name__ == "__main__":
    main()
