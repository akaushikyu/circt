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
a later file wins for a design), and the curated DoD-5 list (--dod5). Optionally the held-out eval
split (hls-doc/heldout.md; W9r22-impl): its run_hlsest.py results (--heldout-run, one per dataset),
their compare.py outputs (--heldout-cmp), its ground truth (--heldout-vitis, default
results/vitis-heldout.json) and its check_semantics.py records (--heldout-sem) give the same three
lists in a section of their own, as drafts (MEMOS #70 was decided for the training catalogue; no
held-out design is on the DoD-5 list). The locked split never appears.

Usage:
  python3 make_done_exclusions.py --run R.json --cmp R.cmp.json --sem a.json b.json ... \\
      [--dod5 done_exclusions_dod5.json] [--out ../../hls-doc/done-exclusions.md] \\
      [--heldout-run F.json V.json --heldout-cmp F.cmp.json V.cmp.json --heldout-sem s.json ...]
"""
import argparse
import datetime
import json
import os
import re
from pathlib import Path

import make_compare_csv as mcc   # the one definition of the DoD-5 goal band (BAND_OVER)

HERE = Path(__file__).resolve().parent

# Vitis front-end / elaboration errors that reject the source itself (MEMOS #70 (1)). W9r23-impl adds the
# codes the first held-out set showed (W9r23-prove, coord/scratch/w9r23p/vitis_rejects.json): 214-194 (a call
# of an undefined function such as rand), 214-143 (an array of non-constant size), SYNCHK 200-21 (an
# unsupported GCC / LLVM intrinsic such as stacksave).
VITIS_REJECT = re.compile(r"ERROR: \[(?:HLS (?:207-\d+|200-70|214-139|214-157|214-194|214-143)|SYNCHK 200-21)\][^\n]*")
# Errors that come from a device feature the design asks for and the ground-truth part lacks (the held-out
# designs target UltraScale+ parts and were normalised to xc7z020): 214-370 (bind_storage impl=uram), 214-372
# (bind_op impl=primitivedsp). Whether they count as rejections is Peter's decision (W9r22 / W9r23 open
# question); they are listed apart, as pending.
VITIS_DEVICE_FEATURE = re.compile(r"ERROR: \[HLS (?:214-370|214-372)\][^\n]*")

# check_semantics.py "n/a" reasons that mean the native reference is defective (MEMOS #70 (2)),
# in the order they are tried: (class, regex).
NATIVE_DEFECT = [
    ("reads uninitialised memory", re.compile(r"reads uninitialised memory")),
    ("AddressSanitizer memory error", re.compile(r"AddressSanitizer: (heap|stack|global)-buffer-overflow|AddressSanitizer: SEGV")),
    ("native build fails", re.compile(r"native build (of .* fails|does not link)")),
    ("native reference aborts", re.compile(r"reference exit -\d+")),
]

# Designs whose native reference reads uninitialised memory although check_semantics gave a verdict
# (a mismatch against the candidate, whose undefined value differs): valgrind memcheck of the reference
# (C simulation, real headers) names the source line (W9r16-prove / W9r16-impl; the reports are kept
# under ~/hls-est-work/coord/scratch/w9r16i/vg/).
UNINITIALISED_REFERENCE_DESIGNS = {
    "class_ece8893_spring_2025/apurba_prasad_padhy_ece8893_spring25_lab2":
        "valgrind: Conditional jump or move depends on uninitialised value(s) at softmax_stream (top.cpp:22):"
        " `fixed_t max_val = localA[0]` reads localA before any write (4 errors from 2 contexts;"
        " w9r16i/vg/apurba.vg.out)",
    "class_ece8893_spring_2025/mohammad_zain_lab_2":
        "valgrind: Conditional jump or move depends on uninitialised value(s) at softmax_HLS (top.cpp:66):"
        " `ap_fixed<32, 8> max_val;` is compared before any write (210046 errors from 124 contexts;"
        " w9r16i/vg/mohammad_zain.vg.out)",
}

# An undefined symbol of Vitis' C-simulation math library in a native or candidate link.  Linking the library
# from the install at check time is allowed (Peter, 2026-10-24, MEMOS #94; check_semantics.py --vitis-mathlib,
# on by default): a record that still fails on these symbols predates that option and must be re-run.
VITIS_MATH_LIBRARY = re.compile(r"does not link: undefined .*(cordic_apfixed::|log_apfixed_reduce::|hls::powf|hls::)")

# Designs whose source divides by zero whatever the inputs: a constant expression of the source is an
# integer (ap_fixed) division by zero, so the C simulation traps (SIGFPE) on every run and no input can
# give a valid reference run (W9r17-impl; VITIS_NOTES N130, kernel w9r17p_sq_sqrt16, whose C simulation
# with the real headers dies with SIGFPE; Vitis folds the same division by N13's rules). Listed with the
# defective references (MEMOS #70 (2)), not as an input-domain limit (OPEN_ISSUES O142).
CONSTANT_DIVISION_BY_ZERO_DESIGNS = {
    k: "the source divides by zero for every input: `const data_t scale = (data_t)1.0 / "
       "hls::sqrt((data_t)head_dim)` with head_dim = 16 and data_t = ap_fixed<16, 5> (range [-16, 16)): "
       "(data_t)16 wraps to -16, hls::sqrt of it is 0 and 1.0 / 0 is an integer division by zero "
       "(%s top.cpp, `head_dim = 16`; kernel w9r17p_sq_sqrt16, VITIS_NOTES N130)" % k.split("/")[1]
    for k in ("forgebench/attention_op_p1", "forgebench/tiled_attn_module", "forgebench/tiled_attn_p1",
              "forgebench/tiled_attn_p2")
}
# The same class with another constant (W9r21-mathlib, the first build of this design's reference, which needs
# Vitis' math library for hls::powf / the cordic table): rms_norm divides by `(data_t)32`, and 32 does not fit
# ap_fixed<16, 5> (range [-16, 16)): it wraps to 0, so every call divides by zero (the reference's
# AddressSanitizer FPE is in rms_norm_8_32's ap_fixed division in every mode, `diag` included).
CONSTANT_DIVISION_BY_ZERO_DESIGNS["forgebench/llama_transformer_p2"] = (
    "the source divides by zero for every input: `sum_sq / (data_t)32` in rms_norm_8_32_ap_fixed_16_5_ "
    "(llama_transformer_p2 top.cpp:86) with data_t = ap_fixed<16, 5> (range [-16, 16)): (data_t)32 wraps to 0, so "
    "every call is an integer division by zero (AddressSanitizer FPE in rms_norm_8_32's ap_fixed operator/ in "
    "every mode and seed)")

# check_semantics.py "n/a" reasons that are limits of the driver's inputs, not defects of the reference:
# the source divides by zero on every input the driver makes (polybench fixed cholesky divides by a pivot
# that is 0 unless the matrix is positive definite). Not
# excluded: open DoD-1 work (W9 round 12 review defect 5; W9 round 13 review finding 9).
INPUT_DOMAIN = [
    ("divides by zero on the driver's inputs (AddressSanitizer FPE)", re.compile(r"AddressSanitizer: FPE")),
]

# A check_semantics reason in which the reference aborts on an assertion of the source.
SOURCE_ASSERTION = re.compile(r"aborts on an assertion of the source")

# Designs whose reference fails an assertion of the source itself on the driver's inputs: the same class
# (the input is outside the source's domain, the reference is not defective), checked per design because an
# abort can also be a real defect (W9 round 14 review finding 7).
INPUT_DOMAIN_DESIGNS = {
    "vitis_examples/28_vitis_accel_examples_streaming_vadd":
        "the source's own assert(size % NUM_WORDS == 0) (vadd.cpp:134) fails on the driver's random size"
        " (exit -6 in all 6 modes)",
}


# References that never return on any input, so check_semantics can give no verdict (W9r19-prove, OPEN_ISSUES
# O157 / O192): proposed for (2) in W9 round 20, accepted by Peter on 2026-10-24 (MEMOS #94).
# W9 round 20 review defect 2: dual_interface_FIFO_receive was listed here by mistake; it stops at a blocking
# read of a drained input stream on both sides, which check_semantics now compares (exit 88 with the dump at that read).
# dual_interface_FIFO_send has no blocking read: once its one input stream is drained, its loop only polls
# `empty()`; its reference and its candidate both run until the time limit (W9 round 20 review fixes:
# reference timeouts in ~/hls-est-work/coord/scratch/w9r20f/sem/dif.json, candidate `timeout 15` rc 124).
NONTERMINATING_REFERENCE_DESIGNS = {
    "auto_ntt/dual_interface_FIFO_send":
        "free-running TAPA task with no blocking read: `for (;;) { if (!common_inVal.empty()) ... "
        "common_inVal.read() ... }` (cpp/dual_interface_FIFO_send.cpp:484-496); once the driver's tokens are "
        "drained it only polls empty(), so neither the reference nor the candidate returns on any input "
        "(both run until the time limit) and no run can be valid; accepted for (2) by Peter, 2026-10-24 (MEMOS #94)",
}

# Proposed additions to (2) that wait for Peter (none at present): design -> why.
PROPOSED_NONTERMINATING = {}


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
    (W9r9 review D5), or ''.  (a) [HLS 214-157] (top not found) is never such a case: MEMOS #70 (1) counts
    a catalogue top that no source defines as a rejection (W9r20-impl).  (b) any error of a design none of whose script design files exists (the harness's
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
        # MEMOS #70 (1) names this case itself: "the catalogue names a top no source defines" counts as
        # done (W9r20-impl; the W9r10 review D3 reading, which listed Dehazing debayer_csynth's script
        # apart, predates #70's wording and contradicted it).  It holds only when no C/C++ file of the
        # design's catalogue directory defines the top: one that does, and that the script fails to
        # compile, is a script defect, not a rejection (W9 round 20 review defect 3).
        top = TOP_NOT_FOUND.search(line)
        hits = top_definitions(top.group(1), design_root(rec)) if top else []
        if hits:
            return ("the top '%s' is defined in %s, which the catalogue's script does not compile: a "
                    "script defect, not a rejection" % (top.group(1), ", ".join(hits[:3])))
        return ""
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


CXX_SUFFIXES = (".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx")


def design_root(rec):
    """The catalogue directory of a design (<dataset>/<design> of its v2 path), or its source tree."""
    tree = Path(rec.get("v2_dir") or rec.get("dir") or "")
    rel = Path((rec.get("v2") or {}).get("rel") or "")
    if len(rel.parts) > 2 and tree.parts[-len(rel.parts):] == rel.parts:
        return Path(*tree.parts[:len(tree.parts) - len(rel.parts) + 2])
    return tree


def top_definitions(name, root):
    """The C/C++ files under root that define a function `name` (a declarator followed by a body)."""
    rx = re.compile(r"\b%s\s*\([^;{}]*\)\s*(const\s*)?\{" % re.escape(name))
    hits = []
    for dirpath, _, files in os.walk(str(root)):
        for f in files:
            if f.lower().endswith(CXX_SUFFIXES):
                path = Path(dirpath) / f
                try:
                    if rx.search(path.read_text(errors="replace")):
                        hits.append(str(path.relative_to(root)))
                except OSError:
                    pass
    return sorted(hits)


def reject_note(line, key=""):
    """The note list (1) shows for a rejection: the MEMOS #70 clause a [HLS 214-157] falls under, with
    the evidence that no source defines the top (checked by stale_catalogue_script) and the design files
    the script names that do not exist."""
    top = TOP_NOT_FOUND.search(line)
    if "214-157" not in line:
        return ""
    rec = catalog_record(key) if key else None
    where = (" (no C/C++ file under %s defines it)" % design_root(rec)) if rec else ""
    missing = [n for n in ((rec or {}).get("v2") or {}).get("source_notes", []) if n.endswith(": not found")]
    gone = ("; the script also adds design files that do not exist (%s), so Vitis compiled the harness's "
            "choice of files" % "; ".join(missing)) if missing else ""
    return ("the catalogue's script sets top '%s', which no source defines%s (MEMOS #70: counts as a "
            "rejection)%s" % (top.group(1) if top else "?", where, gone))


# Missing-header failures that come from how the catalogue staged a library design, not from its source: the
# header is generated by the library's own build or comes from a library its build adds (W9 round 23 review
# D8; checked per design against the library's build files).
CATALOGUE_INCLUDE_ARTEFACTS = {
    "heldout-vitislib/blas__hw__gemm":
        "catalogue artefact: 'params.hpp' is generated by the library's build (blas/L1/tests/hw/gemm/test.mk), "
        "which the catalogue's csynth run does not execute",
    "heldout-vitislib/data_analytics__text__regex_vm":
        "catalogue artefact: 'oniguruma.h' comes from the external Oniguruma library the test's build links "
        "(description.json / run_hls.tcl: -lonig from re_compile/lib); it is not part of the library's sources",
    "heldout-vitislib/data_compression__lz4_compress_mm32bit_single_engine":
        "catalogue artefact: 'boost/assert.hpp' (Boost) is included by the host-side helper "
        "common/libs/compress/compressBase.hpp that the catalogue staged as a source; Boost is not part of the "
        "library's sources",
    "heldout-vitislib/data_compression__lz4_compress_multistreams":
        "catalogue artefact: 'boost/assert.hpp' (Boost) is included by the host-side helper "
        "common/libs/compress/compressBase.hpp that the catalogue staged as a source; Boost is not part of the "
        "library's sources",
}


def not_a_rejection(line, log_text, v, key=""):
    """Why a Vitis failure with a reject-looking error line is not a rejection of the source, or ''."""
    if key in CATALOGUE_INCLUDE_ARTEFACTS and MISSING_FILE.search(line):
        return CATALOGUE_INCLUDE_ARTEFACTS[key]
    if VITIS_CRASH.search(log_text):
        # MEMOS #70 (1) lists [HLS 200-70] among the rejection lines, but a 200-70 that a Vitis crash
        # follows is Vitis failing on a source it accepted, not a rejection of the source (W9 round 8
        # review defect 2; the W9 round 20 review defect 3 asked for the reason to be stated).
        return ("Vitis crashed (EXCEPTION_ACCESS_VIOLATION after the error line): Vitis failed on a source it "
                "accepted, so the line (MEMOS #70 lists 200-70) is not a rejection of the source")
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


def read_sem_list(path):
    """The record paths a --sem-list file names (one per line; '#' starts a comment)."""
    if not path:
        return []
    out = []
    for ln in Path(path).read_text().splitlines():
        ln = ln.split("#", 1)[0].strip()
        if ln:
            out.append(os.path.expanduser(ln))
    return out


def semantics_records(paths):
    """check_semantics.py records of several files merged (a later file wins for a design)."""
    sem = {}
    for f in paths:
        for k, v in rows_of(load(f)).items():
            sem[k] = v
    return sem


def classify(args):
    """The MEMOS #70 lists for the inputs named by args (run, cmp, vitis, sem, dod5): a dict that
    make_dod_status.py reads too."""
    run = rows_of(load(args.run))
    cmp_rows = {r["key"]: r for r in load(args.cmp)["rows"]}
    vitis = load(args.vitis)
    sem = semantics_records(args.sem)
    dod5 = load(args.dod5)["entries"]

    # (1) Vitis rejects the source: an error line of VITIS_REJECT in the record or its log, unless the
    # log shows that the failure is not the source's (W9 round 8 review defect 2): a Vitis crash, a
    # harness path that Vitis split at a space, or a missing file that exists now (a stale run).  Those
    # are listed apart and are not exclusions.
    rejects, not_rejects, device_pending = [], [], []
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
        dev = None if m else (VITIS_DEVICE_FEATURE.search(v.get("note") or "") or
                              VITIS_DEVICE_FEATURE.search(log_text))
        if dev:
            device_pending.append((k, dev.group(0), r.get("cgeist_status"), r.get("status")))
            continue
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
            note = reject_note(line, k)
            sv = sem.get(k) or {}
            if sv.get("status") in ("equal", "mismatch"):
                # cgeist compiles every function of the files the harness chose (--function='*'), so
                # check_semantics can give a verdict for some other function when the catalogue's top is
                # absent (Dehazing script: update_vmin_vmax).  The design counts under (1), not as a
                # semantic verdict (W9 round 20 review defect 4).
                note = "; ".join(x for x in (note, "check_semantics' '%s' is for %s, not the catalogue top: "
                                             "not counted as a verdict" % (sv["status"], sv.get("top_fn") or "?"))
                                 if x)
            rejects.append(row + (note,))

    # (2) Defective native reference.
    defects, input_limits = [], []
    for k in sorted(run):
        s = sem.get(k)
        if k in UNINITIALISED_REFERENCE_DESIGNS:
            defects.append((k, "reads uninitialised memory", UNINITIALISED_REFERENCE_DESIGNS[k],
                            run[k].get("cgeist_status")))
            continue
        if (k in CONSTANT_DIVISION_BY_ZERO_DESIGNS and s and s.get("status") == "n/a"
                and "FPE" in str(s.get("reason") or "")):
            defects.append((k, "divides by zero whatever the inputs",
                            str(s.get("reason")) + "; " + CONSTANT_DIVISION_BY_ZERO_DESIGNS[k],
                            run[k].get("cgeist_status")))
            continue
        if not s or s.get("status") != "n/a":
            continue
        reason = str(s.get("reason") or "")
        if k in NONTERMINATING_REFERENCE_DESIGNS:
            defects.append((k, "never returns on any input", reason + "; " + NONTERMINATING_REFERENCE_DESIGNS[k],
                            run[k].get("cgeist_status")))
            continue
        if k in INPUT_DOMAIN_DESIGNS:
            input_limits.append((k, "fails an assertion of the source on the driver's inputs",
                                 reason + "; " + INPUT_DOMAIN_DESIGNS[k], run[k].get("cgeist_status")))
            continue
        # A reference that needs Vitis' C-simulation math library (the cordic / log tables and
        # hls::powf live in libhlsmc++) is not defective: its record predates check_semantics'
        # --vitis-mathlib (MEMOS #94) and is left open until it is re-run.
        if VITIS_MATH_LIBRARY.search(reason):
            continue
        # The reference fails an assertion of the source (a library's precondition on its size scalars:
        # blas gemm / sbmv / tbmv, hpc rtm2d, vision sgbm / stereopipeline) on the inputs the driver makes:
        # an input outside the source's domain, not a defective reference, even when AddressSanitizer
        # reports the out-of-bounds access the violated precondition leads to (W9 round 23 review D6).
        if SOURCE_ASSERTION.search(reason):
            input_limits.append((k, "fails an assertion of the source on the driver's inputs", reason,
                                 run[k].get("cgeist_status")))
            continue
        for out, classes in ((defects, NATIVE_DEFECT), (input_limits, INPUT_DOMAIN)):
            hit = next((cls for cls, rx in classes if rx.search(reason)), None)
            if hit:
                out.append((k, hit, reason, run[k].get("cgeist_status")))
                break

    # Designs cgeist compiles that still have no check_semantics verdict and no class above: catalogue
    # entries without a C source (hand-written MLIR, run mode "mlir-only": nothing to compare against),
    # the proposed non-terminating references, and the rest (open DoD-1 work).
    classified = ({d[0] for d in defects} | {d[0] for d in input_limits} | {r[0] for r in rejects})
    mlir_only, proposed, no_verdict = [], [], []
    for k in sorted(run):
        r = run[k]
        if k in classified or r.get("cgeist_status") != "ok":
            continue
        s = sem.get(k)
        if s and s.get("status") in ("equal", "mismatch"):
            continue
        reason = str((s or {}).get("reason") or "no check_semantics record")
        if r.get("mode") == "mlir-only" or r.get("cgeist_note") == "mlir-only":
            mlir_only.append((k, reason))
        elif k in PROPOSED_NONTERMINATING:
            proposed.append((k, reason + "; " + PROPOSED_NONTERMINATING[k]))
        elif not VITIS_MATH_LIBRARY.search(reason):
            no_verdict.append((k, reason))

    # (3) DoD 5.
    def band(row):
        if row.get("status") != "compared":
            return None
        h, v = row.get("hlsest_bram"), row.get("vitis_bram")
        if h is None or v is None:
            return None
        if h == v:
            return "exact"
        if mcc.in_band(v, h):
            return "over <= " + mcc.BAND_TEXT
        return "out of band"
    compared = [r for r in cmp_rows.values() if r.get("status") == "compared"]
    bands = {r["key"]: band(r) for r in compared}
    out_of_band = sorted(k for k, b in bands.items() if b == "out of band")
    listed = {e["key"]: e for e in dod5}
    open_work = [k for k in out_of_band if k not in listed]

    return dict(run=run, cmp_rows=cmp_rows, vitis=vitis, sem=sem, dod5=dod5, rejects=rejects,
                not_rejects=not_rejects, device_pending=device_pending, defects=defects, input_limits=input_limits, mlir_only=mlir_only,
                proposed=proposed, no_verdict=no_verdict, compared=compared, bands=bands,
                out_of_band=out_of_band, listed=listed, open_work=open_work)

def render_lists(L, d, h):
    """The three MEMOS #70 lists of classify()'s result `d`, headings at level `h` ('##')."""
    (run, cmp_rows, dod5, rejects, not_rejects, defects, input_limits, mlir_only, proposed, no_verdict, compared,
     bands, out_of_band, listed, open_work) = (d[k] for k in (
        "run", "cmp_rows", "dod5", "rejects", "not_rejects", "defects", "input_limits", "mlir_only", "proposed",
        "no_verdict", "compared", "bands", "out_of_band", "listed", "open_work"))
    L.append(h + " (1) Designs Vitis 2025.1 rejects (%d)" % len(rejects))
    L.append("")
    L.append("| design | Vitis log line | cgeist | hls-est | note |")
    L.append("|---|---|---|---|---|")
    for k, line, cg, st, note in rejects:
        L.append("| %s | %s | %s | %s | %s |" % (md_escape(k), md_escape(line[:200]), md_escape((cg or "-")[:60]),
                                               md_escape(st or "-"), md_escape(note)))
    L.append("")
    device_pending = d.get("device_pending") or []
    if device_pending:
        L.append(h + "# Vitis failures on a device feature the ground-truth part lacks (%d, pending Peter's"
                 " decision)" % len(device_pending))
        L.append("")
        L.append("The design asks for a resource of its original (UltraScale+) part that xc7z020 does not have"
                 " (URAM, primitive DSP binding); whether these count as rejections under MEMOS #70 (1) is open.")
        L.append("")
        L.append("| design | Vitis log line | cgeist | hls-est |")
        L.append("|---|---|---|---|")
        for k, line, cg, st in device_pending:
            L.append("| %s | %s | %s | %s |" % (md_escape(k), md_escape(line[:200]), md_escape((cg or "-")[:60]),
                                              md_escape(st or "-")))
        L.append("")
    L.append(h + "# Vitis failures that are not rejections of the source (%d, not excluded)" % len(not_rejects))
    L.append("")
    L.append("| design | Vitis log line | why it is not a rejection | cgeist | hls-est |")
    L.append("|---|---|---|---|---|")
    for k, line, cg, st, why in not_rejects:
        L.append("| %s | %s | %s | %s | %s |" % (md_escape(k), md_escape(line[:160]), md_escape(why),
                                               md_escape((cg or "-")[:60]), md_escape(st or "-")))
    L.append("")
    L.append(h + " (2) Designs whose native reference is defective (%d)" % len(defects))
    L.append("")
    byclass = {}
    for d in defects:
        byclass.setdefault(d[1], []).append(d)
    classes = [cls for cls, _ in NATIVE_DEFECT]
    classes += [cls for cls in byclass if cls not in classes]   # per-design classes (division by zero)
    for cls in classes:
        ds = byclass.get(cls, [])
        if not ds:
            continue
        L.append(h + "# %s (%d)" % (cls, len(ds)))
        L.append("")
        L.append("| design | check_semantics reason | cgeist |")
        L.append("|---|---|---|")
        for k, _, reason, cg in ds:
            L.append("| %s | %s | %s |" % (md_escape(k), md_escape(reason[:500]), md_escape(cg or "-")))
        L.append("")
    L.append(h + "# Not excluded: the driver's inputs, not the reference (%d, open)" % len(input_limits))
    L.append("")
    L.append("The source divides by zero, or fails one of its own assertions, on every input check_semantics"
             " makes; the reference is not defective. An input in the source's domain (a positive-definite matrix"
             " for cholesky, nonzero denominators for attention, a size that is a multiple of NUM_WORDS for"
             " streaming_vadd) would make these checkable.")
    L.append("")
    L.append("| design | check_semantics reason | cgeist |")
    L.append("|---|---|---|")
    for k, _, reason, cg in input_limits:
        L.append("| %s | %s | %s |" % (md_escape(k), md_escape(reason[:200]), md_escape(cg or "-")))
    L.append("")
    if proposed:
        L.append(h + "# Proposed for (2), not accepted: references that never return (%d, waiting for Peter)"
                 % len(proposed))
        L.append("")
        L.append("| design | check_semantics reason |")
        L.append("|---|---|")
        for k, reason in proposed:
            L.append("| %s | %s |" % (md_escape(k), md_escape(reason[:400])))
        L.append("")
    L.append(h + "# Catalogue entries without a C source (%d, out of scope for DoD 1)" % len(mlir_only))
    L.append("")
    L.append("The catalogue's `basic` entries are hand-written MLIR (run_hlsest.py's `mlir-only` designs): there is"
             " no C source for cgeist to compile and no native reference to compare with, so DoD 1's semantic check"
             " does not apply; hls-est estimates them.")
    L.append("")
    L.append("| design | check_semantics |")
    L.append("|---|---|")
    for k, reason in mlir_only:
        L.append("| %s | %s |" % (md_escape(k), md_escape(reason[:200])))
    L.append("")
    L.append(h + "# No verdict, not classified (%d, open DoD-1 work)" % len(no_verdict))
    L.append("")
    L.append("Designs cgeist compiles whose check_semantics record has no verdict and fits no class above"
             " (a record that still lacks Vitis' math library predates check_semantics --vitis-mathlib, MEMOS #94,"
             " and is listed by make_dod_status.py as needing a re-run).")
    L.append("")
    L.append("| design | check_semantics reason |")
    L.append("|---|---|")
    for k, reason in no_verdict:
        L.append("| %s | %s |" % (md_escape(k), md_escape(reason[:300])))
    L.append("")
    L.append(h + " (3) DoD 5: designs that may stay out of band (%d listed)" % len(dod5))
    L.append("")
    L.append("Band: hls-est equals Vitis or over-counts by at most %s (under-counts are out of band; MEMOS #95). Of"
             " %d compared designs, %d are exact, %d over by at most %s, %d out of band; %d of these are on the"
             " list below and %d are open work." % (
                 mcc.BAND_TEXT, len(compared), sum(1 for b in bands.values() if b == "exact"),
                 sum(1 for b in bands.values() if b == "over <= " + mcc.BAND_TEXT), mcc.BAND_TEXT, len(out_of_band),
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
    L.append(h + "# Out of band and not on the list (open work, %d)" % len(open_work))
    L.append("")
    L.append("| design | hls-est | Vitis | difference |")
    L.append("|---|---:|---:|---:|")
    for k in sorted(open_work, key=lambda k: -abs(cmp_rows[k]["hlsest_bram"] - cmp_rows[k]["vitis_bram"])):
        r = cmp_rows[k]
        L.append("| %s | %d | %d | %+d |" % (md_escape(k), r["hlsest_bram"], r["vitis_bram"],
                                            r["hlsest_bram"] - r["vitis_bram"]))
    L.append("")


def heldout_classify(args, runs=None, cmps=None, sems=None):
    """classify() over the merged held-out runs (forgehls + vitislib) and their compare files (the eval
    split's by default; the locked split's when runs / cmps / sems are given)."""
    import tempfile
    runs = args.heldout_run if runs is None else runs
    cmps = args.heldout_cmp if cmps is None else cmps
    sems = args.heldout_sem if sems is None else sems
    if len(runs) != len(cmps):
        raise SystemExit("--heldout-run and --heldout-cmp need one compare file per run, in the same order")
    # A compare file lists every held-out design; take from each only the designs of its own run.
    run, rows = {}, []
    for run_file, cmp_file in zip(runs, cmps):
        own = rows_of(load(run_file))
        run.update(own)
        rows += [r for r in load(cmp_file)["rows"] if r["key"] in own]
    with tempfile.TemporaryDirectory(prefix="doneexcl") as d:
        tmp = Path(d)
        (tmp / "run.json").write_text(json.dumps(run))
        (tmp / "cmp.json").write_text(json.dumps({"rows": rows}))
        (tmp / "dod5.json").write_text(json.dumps({"entries": []}))
        ns = argparse.Namespace(run=str(tmp / "run.json"), cmp=str(tmp / "cmp.json"), vitis=args.heldout_vitis,
                                sem=list(sems), dod5=str(tmp / "dod5.json"))
        return classify(ns)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--run", required=True, help="run_hlsest.py result json")
    ap.add_argument("--cmp", required=True, help="compare.py output json of that run")
    ap.add_argument("--vitis", default=str(HERE / "results" / "vitis.json"))
    ap.add_argument("--sem", nargs="*", default=[], help="check_semantics.py records (later wins)")
    ap.add_argument("--sem-list", help="a file naming check_semantics.py records, one per line, read before --sem")
    ap.add_argument("--dod5", default=str(HERE / "done_exclusions_dod5.json"))
    ap.add_argument("--out", default=str(HERE.parent.parent / "hls-doc" / "done-exclusions.md"))
    ap.add_argument("--heldout-run", nargs="*", default=[], help="held-out eval run_hlsest.py results (optional)")
    ap.add_argument("--heldout-cmp", nargs="*", default=[], help="their compare.py outputs")
    ap.add_argument("--heldout-vitis", default=str(HERE / "results" / "vitis-heldout.json"))
    ap.add_argument("--heldout-sem", nargs="*", default=[], help="check_semantics.py records of held-out designs")
    ap.add_argument("--locked-run", nargs="*", default=[],
                    help="held-out LOCKED split run_hlsest.py results (needs the split released, hls-doc/heldout.md)")
    ap.add_argument("--locked-cmp", nargs="*", default=[], help="their compare.py outputs")
    ap.add_argument("--locked-sem", nargs="*", default=[], help="check_semantics.py records of locked designs")
    args = ap.parse_args()
    args.sem = read_sem_list(args.sem_list) + list(args.sem)
    d = classify(args)
    (run, cmp_rows, dod5, rejects, not_rejects, defects, input_limits, mlir_only, proposed, no_verdict, compared,
     bands, out_of_band, listed, open_work) = (d[k] for k in (
        "run", "cmp_rows", "dod5", "rejects", "not_rejects", "defects", "input_limits", "mlir_only", "proposed",
        "no_verdict", "compared", "bands", "out_of_band", "listed", "open_work"))
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
    render_lists(L, d, "##")
    if args.heldout_run:
        hd = heldout_classify(args)
        L.append("## Held-out eval split (hls-doc/heldout.md)")
        L.append("")
        L.append("The same three lists for the held-out evaluation split (development data since W9 round 23)."
                 " MEMOS #70 was decided for the training catalogue; these lists are drafts for Peter.")
        L.append("")
        L.append("Inputs:")
        L.append("")
        for f in args.heldout_run:
            L.append("- run: `%s`" % f)
        for f in args.heldout_cmp:
            L.append("- compare: `%s`" % f)
        L.append("- Vitis ground truth: `%s`" % args.heldout_vitis)
        for f in args.heldout_sem:
            L.append("- semantics: `%s`" % f)
        L.append("- DoD-5 list: none (no held-out design is listed)")
        L.append("")
        render_lists(L, hd, "###")
    if args.locked_run:
        import designs as D
        if not D.heldout_locked_released("heldout"):
            raise SystemExit("--locked-run: the locked split of 'heldout' is not released (hls-doc/heldout.md)")
        ld = heldout_classify(args, args.locked_run, args.locked_cmp, args.locked_sem)
        L.append("## Held-out locked split (hls-doc/heldout.md)")
        L.append("")
        L.append("The same three lists for the held-out locked split, which Peter released on 2026-10-27 and which is"
                 " development data since W9 round 23. Drafts for Peter, as the eval split's.")
        L.append("")
        L.append("Inputs:")
        L.append("")
        for f in args.locked_run:
            L.append("- run: `%s`" % f)
        for f in args.locked_cmp:
            L.append("- compare: `%s`" % f)
        L.append("- Vitis ground truth: `%s`" % args.heldout_vitis)
        for f in args.locked_sem:
            L.append("- semantics: `%s`" % f)
        L.append("- DoD-5 list: none (no held-out design is listed)")
        L.append("")
        render_lists(L, ld, "###")
    Path(args.out).write_text("\n".join(L) + "\n")
    print("wrote %s: %d rejects, %d not rejections, %d defective references, %d input-domain limits,"
          " %d proposed, %d mlir-only, %d without a verdict, %d listed, %d open" % (
              args.out, len(rejects), len(not_rejects), len(defects), len(input_limits), len(proposed),
              len(mlir_only), len(no_verdict), len(dod5), len(open_work)))


if __name__ == "__main__":
    main()
