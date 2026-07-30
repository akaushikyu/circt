#!/usr/bin/env python3
"""hls-doc/hlsfactory-v2.md from a sweep of the HLSFactory v2 catalogue (sweep_hlsfactory_v2.py).

    python3 make_hlsfactory_report.py [--sweep results/hlsfactory-v2-sweep.json]
                                      [--vitis results/vitis.json] [--out ../../hls-doc/hlsfactory-v2.md]
                                      [--reclassify]

classify(record) gives every failed design a cause class (CLASSES: stage, meaning, fix track) and the
error line it rests on, from the record's status and the cgeist / hls-est logs the record names.
--reclassify re-reads those logs and writes the classes back into the sweep JSON (after a rule change);
otherwise the classes stored by the sweep are used, so the page can be rebuilt without the logs.

The page: run configuration; per dataset designs / cgeist ok / hls-est ok / with Vitis truth / exact;
failures by cause class (count, fix track, one example design and error line); the designs whose sources
differ from their Polygeist copy; catalogue entries that are not designs and Polygeist designs the tree
no longer has; one row per design.  "With Vitis truth" = a results/vitis.json entry with status ok for a
design whose sources are the ones that entry synthesized (source_match identical or identical after the
harvest's transform); "exact" = hls-est's total equals that entry's BRAM_18K.
"""
import argparse
import os
import re
import sys
import time
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                         # noqa: E402

VITIS_INCLUDE = Path(C.VITIS_INCLUDE_WSL)

# cause class -> (stage, meaning, fix track)
CLASSES = {
    "missing-vendor-header": ("cgeist", "a Vitis 2025.1 header the harness shim does not provide",
                              "W8b shim (stand-in header)"),
    "missing-legacy-vendor-header": ("cgeist", "a Xilinx library header Vitis 2025.1 no longer ships "
                                               "(hls_video.h, hls_opencv.h, ...): Vitis cannot compile it either",
                                     "UNSUPPORTED (needs the old Vitis library)"),
    "missing-host-header": ("cgeist", "a host / third-party header (OpenCV, OpenCL/XRT, TAPA, ...)",
                            "UNSUPPORTED unless the include is testbench-only (then harness)"),
    "missing-design-file": ("cgeist", "a file the design needs is not in the tree: an #include target, or a "
                                      "design source its synthesis script adds (the rest does not compile alone)",
                            "UNSUPPORTED (dataset incomplete)"),
    "include-path": ("harness", "the header is in the design tree but not on the include path",
                     "harness (loader include dirs)"),
    "shim-range-select": ("cgeist", "shim gap: assignable range() / bit select (O15)", "W6 / W8b shim"),
    "shim-ap-feature": ("cgeist", "shim gap: an ap_int / ap_fixed member or operator exactclass lacks",
                        "W8b shim"),
    "shim-hls-api": ("cgeist", "shim gap: hls::stream / hls::vector / hls_math / other hls:: API", "W8b shim"),
    "shim-std-include": ("cgeist", "shim gap: the Vitis headers include <stdint.h>, <stdio.h>, <stdlib.h>, "
                                   "<cmath>, <iostream>, <string> (etc/ap_common.h, hls_math.h); the stand-ins do "
                                   "not, so a design that relies on them misses uint32_t, memcpy, stderr, ...",
                         "W8b shim"),
    "needs-synthesis-macro": ("harness", "compiles only with __SYNTHESIS__ defined: Vitis' front-end clang runs "
                                         "with -D__SYNTHESIS__ -D__VITIS_HLS__ -D__HLS_SYN__ -DAESL_SYN "
                                         "(VITIS_NOTES N19), the harness cgeist command defines none of them "
                                         "(shown by re-running cgeist with -D__SYNTHESIS__; OPEN_ISSUES O30)",
                              "W8b harness (a default)"),
    "top-not-in-sources": ("harness", "the synthesis script names a top that no design source defines",
                           "UNSUPPORTED (dataset bug)"),
    "cxx-standard": ("harness", "valid before C++17 only (e.g. `register`): cgeist's clang 18 defaults to "
                                "C++17, Vitis 2025.1 compiles C++ as C++14 (VITIS_NOTES N19, OPEN_ISSUES O31)",
                     "W8b harness flag -std=c++14 (a default)"),
    "cxx-rejected": ("cgeist", "a C++ construct cgeist does not lower (reported as unsupported)", "W8b cgeist"),
    "hls-pragma-error": ("cgeist", "cgeist's pragma checks (--hls-annotate) reject one of the design's pragmas "
                                   "(misplaced unroll, dim out of range, unknown variable, two array_partition "
                                   "pragmas on one dimension). Vitis keeps the larger factor for the last "
                                   "(VITIS_NOTES N17 (c)); its handling of the others is unconfirmed",
                         "W8b cgeist (pragma handling: Peter's call)"),
    "clang-error": ("cgeist", "clang rejects the code (C/C++ error in the design's own sources)",
                    "check per design: design bug, Vitis-only extension, or harness"),
    "cgeist-crash": ("cgeist", "cgeist crash / assertion", "W8b cgeist"),
    "cgeist-timeout": ("cgeist", "cgeist timeout", "W8b cgeist"),
    "cgeist-empty-module": ("cgeist", "cgeist exits 0 but emits no function", "W8b cgeist (W7 empty modules)"),
    "cgeist-invalid-mlir": ("cgeist", "cgeist emits MLIR that fails verification", "W8b cgeist"),
    "cgeist-error": ("cgeist", "other cgeist error", "W8b cgeist"),
    "top-not-found": ("harness", "the design's top function is not in the MLIR", "harness / cgeist"),
    "hlsest-parse": ("hls-est", "hls-est cannot parse cgeist's MLIR", "W8b hls-est"),
    "hlsest-unsupported-op": ("hls-est", "hls-est rejects an op", "W8b hls-est"),
    "hlsest-crash": ("hls-est", "hls-est crash / assertion", "W8b hls-est"),
    "hlsest-timeout": ("hls-est", "hls-est timeout", "W8b hls-est"),
    "hlsest-error": ("hls-est", "other hls-est error", "W8b hls-est"),
    "harness-error": ("harness", "the harness itself failed on the design", "harness"),
}
STD_NAMES = re.compile(r"unknown type name '(u?int(?:8|16|32|64)_t|size_t|uintptr_t|FILE|string)'|"
                       r"use of undeclared identifier '(memcpy|memset|memcmp|memmove|strlen|strcpy|strcmp|"
                       r"strncpy|printf|fprintf|sprintf|snprintf|puts|stderr|stdout|exit|abort|malloc|calloc|"
                       r"free|rand|srand|assert|INT_MAX|INT_MIN|UINT_MAX|RAND_MAX|fabs|sqrt|exp|log|pow|"
                       r"floor|ceil|round|cout|cerr|endl|std)'|no member named '(cout|cerr|endl|string|to_string|"
                       r"min|max|abs|sqrt|exp)' in namespace 'std'|no type named '(string|vector)' in namespace 'std'")
HOST_HEADER = re.compile(r"^(opencv2?/|CL/|xcl2|xrt|experimental/xrt|tapa|gflags|glog|boost/|Eigen/|"
                         r"cuda|omp\.h|mpi\.h|ap_utils|sds_lib|xf_|common/xf_|hlslib/|ff\.h|frt\.h)", re.I)


def _read(p, limit=400000):
    try:
        with open(p, errors="replace") as f:
            return f.read(limit)
    except (OSError, TypeError):
        return ""


def _stderr_of_cgeist_log(text):
    return text.split("\n--- stderr ---\n", 1)[1] if "\n--- stderr ---\n" in text else text


def _first(lines, pat):
    for ln in lines:
        if re.search(pat, ln):
            return ln.strip()
    return ""


_vendor_cache = {}


def _vendor_has(header):
    if header not in _vendor_cache:
        _vendor_cache[header] = (VITIS_INCLUDE / header).is_file() or any(
            (VITIS_INCLUDE / sub / header).is_file() for sub in ("etc", "utils"))
    return _vendor_cache[header]


def _in_tree(r, header):
    root = r.get("v2", {}).get("v2_dir") or r.get("dir")
    if not root or not os.path.isdir(root):
        return False
    base = os.path.basename(header)
    for dp, _, fn in os.walk(root):
        if base in fn:
            return True
    return False


def _top_in_sources(r):
    """Whether some design source names the top function as a call or definition (`top(`)."""
    top = r.get("top") or ""
    for s in r.get("sources", []):
        if re.search(r"\b" + re.escape(top) + r"\s*\(", _read(os.path.join(r.get("dir", ""), s), 4000000)):
            return True
    return False


def classify_cgeist(r, stderr):
    st = r.get("status", "")
    lines = stderr.splitlines()
    exp = r.get("synthesis_macro_experiment") or {}
    if exp.get("cgeist_status") and exp["cgeist_status"] != st:
        then = (f"cgeist ok, {exp.get('status')} (BRAM {exp.get('total_bram')})" if exp["cgeist_status"] == "ok"
                else exp["cgeist_status"])
        return "needs-synthesis-macro", "", f"{st[:100]}; with -D__SYNTHESIS__: {then}"[:300]
    if st == "cgeist timeout":
        return "cgeist-timeout", "", f"no output within {r.get('cgeist_note') or 'the timeout'}"
    if st == "cgeist crash":
        a = _first(lines, r"Assertion .* failed|UNREACHABLE executed|LLVM ERROR|Segmentation|Aborted")
        loc = _first(lines, r"^\s*#\d+ .* in .*(clang-mlir|CGCall|cgeist|polygeist|mlir::)")
        return "cgeist-crash", "", (a or loc or (lines[-1].strip() if lines else ""))[:300]
    if "empty module" in st:
        return "cgeist-empty-module", "", st
    errs =[ln for ln in lines if re.search(r"\b(fatal )?error:", ln)]
    first = errs[0].strip() if errs else ""
    k = next((i for i, ln in enumerate(lines) if re.search(r"\b(fatal )?error:", ln)), None)
    snippet = "\n".join(lines[k + 1:k + 3]) if k is not None else ""
    m = re.search(r"fatal error: '([^']+)' file not found", first)
    if m:
        h = m.group(1)
        if HOST_HEADER.search(h):
            return "missing-host-header", h, first
        if _vendor_has(h):
            return "missing-vendor-header", h, first
        if re.match(r"(hls_|ap_|etc/|utils/x_hls)", h):
            return "missing-legacy-vendor-header", h, first
        if _in_tree(r, h):
            return "include-path", h, first
        return "missing-design-file", h, first
    blob = "\n".join(errs[:6])
    if re.search(r"no viable overloaded '='|expression is not assignable|cannot assign", first) and \
            re.search(r"\.range\s*\(|\.bit\s*\(|\w\s*\(\s*[^()]+,\s*[^()]+\)\s*=|\w\s*\[[^\]]+\]\s*=", snippet):
        return "shim-range-select", "", first
    if re.search(r"#pragma HLS|pragma HLS|conflicts with an earlier pragma|expected a pragma name|"
                 r"expected an option name|option '.*' is specified more than once", first):
        return "hls-pragma-error", "", first
    m = STD_NAMES.search(first)
    if m:
        return "shim-std-include", next(g for g in m.groups() if g), first
    if re.search(r"ISO C\+\+1[7-9] does not allow|C\+\+17 removed|no longer supported in C\+\+17", first):
        return "cxx-standard", "", first
    if "no matching function for call" in first or "no matching constructor" in first:
        notes = "\n".join(lines[k:k + 12]) if k is not None else ""
        if re.search(r"hls::(stream|vector)", notes):
            return "shim-hls-api", "", first
        if re.search(r"ap_(u)?(int|fixed)", notes):
            return "shim-ap-feature", "", first
    if re.search(r"hls::(vector|stream|task|stream_of_blocks)|'hls::|hls_math|half|call to '(exp|log|sqrt|pow|"
                 r"sin|cos|tan|tanh|fabs|abs|floor|ceil|round|fmin|fmax|erf)' is ambiguous", blob + "\n" + snippet):
        return "shim-hls-api", "", first
    if re.search(r"ap_(u)?(int|fixed)|ap_range_ref|ap_bit_ref|af_range|af_bit", blob) or \
            re.search(r"no member named '(range|to_\w+|is_neg|bit|get_bit|set_bit|countLeadingZeros|"
                      r"reverse|and_reduce|or_reduce|xor_reduce|length|width|iszero|sign)'", blob):
        return "shim-ap-feature", "", first
    if re.search(r"'[\w.]+' op |verif|does not dominate|operand type mismatch", blob):
        return "cgeist-invalid-mlir", "", first
    if re.search(r"(unsupported|not supported|unhandled|unimplemented|not implemented|cannot lower|TODO)",
                 blob, re.I):
        return "cxx-rejected", "", first
    if errs:
        return "clang-error", "", first
    return "cgeist-error", "", st[:300]


def classify_hlsest(r, err):
    st = r.get("status", "")
    lines = err.splitlines()
    if st.startswith("hls-est timeout"):
        return "hlsest-timeout", "", st
    if st == "hls-est error: crash":
        a = _first(lines, r"Assertion .* failed|UNREACHABLE executed|LLVM ERROR")
        return "hlsest-crash", "", (a or r.get("note") or "")[:300]
    eline = _first(lines, r"error:")
    if "unregistered dialect" in err:
        # the MLIR line after the message names the op: %2 = "polygeist.pointer2memref"(%1) ...
        k = next((i for i, ln in enumerate(lines) if "unregistered dialect" in ln), None)
        m = re.search(r'"([A-Za-z_]\w*\.[\w.]+)"\(', "\n".join(lines[k + 1:k + 3])) if k is not None else None
        op = m.group(1) if m else ""
        return "hlsest-parse", op, (eline.split("error:", 1)[-1].strip()[:120] + (f" ({op})" if op else ""))
    m = re.search(r"custom op '([^']+)' is unknown|invalid memref element type|expected |unexpected |"
                  r"invalid .*syntax|could not parse", err + "\n" + st)
    if m:
        op = m.group(1) if m.group(1) else ""
        if not op:
            k = next((i for i, ln in enumerate(lines) if "error:" in ln), None)
            ctx = "\n".join(lines[k + 1:k + 2]) if k is not None else ""
            if "invalid memref element type" in err and "!llvm.struct" in ctx:
                op = "memref of !llvm.struct"
            else:
                mm = re.search(r"(![\w.]+|memref<[^>]*>)", ctx)
                op = mm.group(1)[:60] if mm else ""
        return "hlsest-parse", op, (eline.split("error:", 1)[-1].strip() or st)[:200]
    m = re.search(r"'([\w.]+)' op (.*)", st) or re.search(r"error: '([\w.]+)' op (.*)", err)
    if m:
        return "hlsest-unsupported-op", m.group(1), _first(lines, r"error:") or st
    return "hlsest-error", "", (_first(lines, r"error:") or st)[:300]


def classify(r):
    """{'cause', 'cause_detail', 'stage', 'error_line'} for a sweep record (cause None when ok)."""
    st = r.get("status", "")
    out = {"cause": None, "cause_detail": "", "stage": None, "error_line": ""}
    if st == "ok":
        top, fn = r.get("top"), r.get("top_fn") or ""
        if r.get("top_rule") in ("last", "single") and top and top not in fn:
            defined = _top_in_sources(r)
            out.update(cause="top-not-found" if defined else "top-not-in-sources", stage="harness",
                       cause_detail=f"picked {fn[:60]!r} ({r.get('top_rule')})",
                       error_line=f"top {top!r} not among the MLIR functions"
                                  + ("" if defined else " and not defined in any design source")
                                  + f"; hls-est ran on {fn[:60]!r}")
        return out
    if st == "harness error":
        out.update(cause="harness-error", stage="harness", error_line=r.get("note", "")[:300])
        return out
    star = r.get("star_attempt") or {}
    exp = r.get("synthesis_macro_experiment") or {}
    if st.startswith("hls-est") and exp.get("status") == "ok":
        out.update(cause="needs-synthesis-macro", stage="harness",
                   error_line=f"{st[:120]}; with -D__SYNTHESIS__: ok (BRAM {exp.get('total_bram')})")
        return out
    if "empty module" in st and star.get("status", "ok") != "ok" and "empty module" not in star["status"]:
        # run_hlsest keeps only the by-name retry's empty module; the '*' attempt shows the real failure
        cause, detail, line = classify_cgeist(dict(r, status=star["status"]),
                                              _stderr_of_cgeist_log(_read(star.get("log"))))
        line = "--function='*': " + line
    elif st.startswith("cgeist"):
        cause, detail, line = classify_cgeist(r, _stderr_of_cgeist_log(_read(r.get("cgeist_log"))))
        missing = [n for n in (r.get("v2") or {}).get("source_notes", [])
                   if n.endswith(": not found") and n.startswith("add_files ")]
        if cause == "clang-error" and missing:
            # the synthesis script names design files the tree lacks; the rest does not compile alone
            cause, detail = "missing-design-file", missing[0][len("add_files "):-len(": not found")]
    elif st.startswith("hls-est"):
        cause, detail, line = classify_hlsest(r, _read(r.get("hlsest_log")))
    else:
        cause, detail, line = "harness-error", "", st
    out.update(cause=cause, cause_detail=detail, stage=CLASSES.get(cause, ("?",))[0],
               error_line=re.sub(r"^/\S+?/([^/\s]+:\d+:\d+:)", r"\1", line)[:300])
    return out


# ------------------------------------------------------------------------------------------- page
def _md(s):
    return str(s if s is not None else "").replace("|", "\\|").replace("\n", " ")


def truth_of(key, r, vitis):
    v = vitis.get(key)
    if not v or v.get("status") != "ok":
        return None, "no Vitis result" if not v else f"Vitis {v.get('status')}"
    sm = (r.get("v2") or {}).get("source_match")
    if sm not in ("identical", "identical-after-harvest"):
        return None, f"stale: sources {sm}"
    return (v.get("totals") or {}).get("BRAM"), "ok"


def build_page(sweep, vitis, src_name):
    meta = sweep.get("_meta", {})
    recs = {k: v for k, v in sweep.items() if k != "_meta"}
    per = defaultdict(Counter)
    causes = defaultdict(list)
    rows = []
    for k in sorted(recs, key=str.lower):
        r = recs[k]
        ds = r["dataset"]
        c = per[ds]
        c["designs"] += 1
        cg_ok = r.get("cgeist_status") == "ok"
        he_ok = r.get("status") == "ok" and r.get("cause") is None
        c["cgeist ok"] += cg_ok
        c["hls-est ok"] += he_ok
        sm = (r.get("v2") or {}).get("source_match")
        c["same sources"] += sm in ("identical", "identical-after-harvest")
        c["differ"] += sm in ("content-differs", "file-set-differs", "top-differs")
        c["new"] += sm == "new"
        tb, why = truth_of(k, r, vitis)
        if tb is not None:
            c["with Vitis truth"] += 1
            if he_ok and r.get("total_bram") == tb:
                c["exact"] += 1
        if r.get("cause"):
            causes[r["cause"]].append(k)
        rows.append((k, r, tb, why))
    out = [f"generated by tools/hls-est-validate/make_hlsfactory_report.py from {src_name} on "
           f"{time.strftime('%Y-%m-%d %H:%M')}", "",
           "# HLSFactory v2 catalogue: cgeist and hls-est on every design (W8a)", "",
           "Every design of the HLSFactory 1.1.0 tree (`D:\\HLSFactory_v2\\HLSFactory`, decision #28) as the "
           "harness catalogue reads it (`designs.py --catalog v2`, rules in `hlsfactory_v2.py`), run through the "
           "installed cgeist and the current hls-est with the harness defaults (shim, pipeline, per-design top "
           "selection) by `sweep_hlsfactory_v2.py`. A failure is put in one cause class by "
           "`make_hlsfactory_report.classify` from the status and the first error line of the cgeist or hls-est "
           "log; the class names the track that can fix it.", ""]
    out += ["## Run configuration", "", "| item | value |", "|---|---|"]
    items = [("HLSFactory tree", f"{meta.get('hlsfactory_root')} (git {meta.get('hlsfactory_head')})"),
             ("catalogue", f"{len(recs)} HLSFactory designs (polybench_pragmas and basic are not HLSFactory "
                           f"designs and are not swept); load {meta.get('catalogue_load_s')} s"),
             ("cgeist", f"`{meta.get('cgeist')}` md5 {meta.get('cgeist_md5')} (installed build/bin/cgeist, "
                        f"Polygeist c70ba2b0)"),
             ("hls-est", f"`{meta.get('hls_est')}` sha256 {meta.get('hls_est_sha256')}: {meta.get('hls_est_git')}"),
             ("shim", f"`{meta.get('shim')}` (harness default)"),
             ("pipeline", f"`{meta.get('pipeline')}` (common.DEFAULT_PIPELINE; run_hlsest adds the top "
                          f"selection per design)"),
             ("timeouts", f"cgeist {meta.get('cgeist_timeout')} s, hls-est {meta.get('hlsest_timeout')} s; "
                          f"-j {meta.get('jobs')}"),
             ("private HOME (MLIR cache, logs)", f"`{meta.get('home')}`"),
             ("run", f"{meta.get('run_id')}: {meta.get('started')} - {meta.get('finished')}"
                     + (f"; re-sweeps: {', '.join(x['run_id'] + ' (' + str(x['keys']) + ' designs)' for x in meta['resweeps'])}"
                        if meta.get("resweeps") else ""))]
    out += [f"| {a} | {_md(b)} |" for a, b in items]

    cols = ["designs", "cgeist ok", "hls-est ok", "with Vitis truth", "exact", "same sources", "differ", "new"]
    out += ["", "## Per dataset", "",
            "*same sources*: the design's source set equals its Polygeist copy (its key, MLIR and Vitis cache "
            "entries carry over); *differ*: same key, other sources (the ground truth is re-run in W8c); *new*: "
            "no Polygeist copy. *hls-est ok* excludes designs where the top was not found.", "",
            "| dataset | " + " | ".join(cols) + " |", "|---|" + "---:|" * len(cols)]
    tot = Counter()
    for ds in sorted(per, key=str.lower):
        tot.update(per[ds])
        out.append(f"| {ds} | " + " | ".join(str(per[ds][c]) for c in cols) + " |")
    out.append("| **total** | " + " | ".join(f"**{tot[c]}**" for c in cols) + " |")
    in_truth = [(k, r) for k, r in recs.items() if k in vitis]
    same = [k for k, r in in_truth if r.get("vitis_cache_key") == vitis[k].get("key")]
    lost = sorted(k for k in vitis if k not in recs and not k.startswith("polybench_pragmas/"))
    out += ["", f"Key stability: {len(in_truth)} of the {len(vitis)} `results/vitis.json` keys are v2 designs "
                f"(the other {len(vitis) - len(in_truth) - len(lost)} are polybench_pragmas, which is not an "
                f"HLSFactory dataset{'' if not lost else '; missing: ' + ', '.join(lost)}); for {len(same)} of "
                f"them the v2 record reproduces the ground truth's Vitis cache key (`run_vitis.cache_key`, so "
                f"`run_vitis.py --catalog v2` reuses the cached synthesis), the other "
                f"{len(in_truth) - len(same)} have other sources: "
                + (", ".join(sorted(k for k, _ in in_truth if k not in same)) or "none") + "."]

    out += ["", "## Failures by cause class", "",
            "| cause class | stage | designs | meaning | fix track | example design | example error |",
            "|---|---|---:|---|---|---|---|"]
    order = sorted(causes, key=lambda c: (-len(causes[c]), c))
    for cz in order:
        ks = causes[cz]
        stage, meaning, track = CLASSES.get(cz, ("?", "?", "?"))
        ex = ks[0]
        out.append(f"| `{cz}` | {stage} | {len(ks)} | {_md(meaning)} | {_md(track)} | {_md(ex)} | "
                   f"`{_md(recs[ex].get('error_line'))[:160]}` |")
    out.append(f"| **total** | | **{sum(len(v) for v in causes.values())}** | | | | |")
    details = defaultdict(Counter)
    for cz, ks in causes.items():
        for k in ks:
            d = recs[k].get("cause_detail")
            if d:
                details[cz][d] += 1
    if details:
        out += ["", "Detail per class (header, op or assertion: designs):", ""]
        for cz in order:
            if details.get(cz):
                out.append(f"- `{cz}`: " + ", ".join(f"`{_md(d)}` {n}" for d, n in details[cz].most_common(25)))

    exp_rows = [(k, r, r["synthesis_macro_experiment"]) for k, r, _, _ in rows
                if r.get("synthesis_macro_experiment")]
    if exp_rows:
        fixed = sum(1 for _, r, e in exp_rows if r.get("status") != "ok" and e.get("cgeist_status") == "ok"
                    and r.get("cgeist_status") != "ok")
        changed = [(k, r, e) for k, r, e in exp_rows if r.get("status") == "ok"
                   and (e.get("status") != "ok" or e.get("total_bram") != r.get("total_bram"))]
        n_ok = sum(1 for _, r, _ in exp_rows if r.get("status") == "ok")
        out += ["", "## Experiment: cgeist with `-D__SYNTHESIS__`", "",
                "Vitis' front end compiles with `-D__SYNTHESIS__ -D__VITIS_HLS__ -D__HLS_SYN__ -DAESL_SYN` "
                "(`autopilot.flow.log` of any cached run); the harness cgeist command defines none of them. "
                "`sweep_hlsfactory_v2.py --followup synmacro,synmacro-ok` re-ran every design whose sources or "
                "headers name `__SYNTHESIS__` with that one macro added (an experiment; the harness default is "
                f"unchanged). {len(exp_rows)} designs: {fixed} that failed in cgeist get through cgeist; "
                + (f"{len(changed)} of the {n_ok} designs that passed change status or total."
                   if n_ok else
                   "no design that passes names the macro in its sources or headers (the shim's headers do not "
                   "test it either), so defining it cannot change a current estimate of this catalogue."
                   if any("synmacro-ok" in f.get("kinds", []) for f in meta.get("followups", [])) else
                   "the designs that pass were not checked (no synmacro-ok follow-up).")
                + " The designs that still fail with the macro are listed under their own class.", "",
                "| design | status without | cgeist with | hls-est with | BRAM without | BRAM with |",
                "|---|---|---|---|---:|---:|"]
        for k, r, e in exp_rows:
            out.append(f"| {_md(k)} | {_md(r.get('status', '')[:50])} | {_md((e.get('cgeist_status') or '')[:40])} | "
                       f"{_md((e.get('status') or '')[:40])} | {_md(r.get('total_bram'))} | {_md(e.get('total_bram'))} |")

    diff = [(k, r) for k, r, _, _ in rows if (r.get("v2") or {}).get("source_match") in
            ("content-differs", "file-set-differs", "top-differs")]
    out += ["", "## Designs whose sources differ from the Polygeist copy", "",
            f"{len(diff)} designs keep their key but not their sources; their Vitis cache entries (if any) "
            "do not apply and their ground truth is re-run in W8c.", "",
            "| design | difference | files only in v2 | files only in the Polygeist copy | changed files |",
            "|---|---|---|---|---|"]
    for k, r in diff:
        sd = (r.get("v2") or {}).get("source_diff") or {}
        out.append(f"| {_md(k)} | {r['v2']['source_match']} | {_md(', '.join(sd.get('only_v2', [])[:6]))} | "
                   f"{_md(', '.join(sd.get('only_polygeist', [])[:6]))} | {_md(', '.join(sd.get('changed', [])[:6]))} |")

    out += ["", "## Not designs, and Polygeist designs the tree no longer has", ""]
    sk = meta.get("skipped", [])
    out += [f"{len(sk)} catalogue entries are not swept:", "", "| entry | reason |", "|---|---|"]
    out += [f"| {_md(s['rel'])} | {_md(s['reason'])} |" for s in sk]
    va = meta.get("vanished", [])
    out += ["", f"{len(va)} designs of the Polygeist copy have no v2 counterpart:", "",
            "| Polygeist key | top | lit mode |", "|---|---|---|"]
    out += [f"| {_md(v['key'])} | {_md(v['top'])} | {_md(v['mode'])} |" for v in va]

    out += ["", "## Per design", "",
            "| design | sources | cgeist | hls-est | BRAM | Vitis BRAM | time (s) | cause |",
            "|---|---|---|---|---:|---:|---:|---|"]
    for k, r, tb, why in rows:
        cg = r.get("cgeist_status", "")
        he = r.get("status", "") if cg == "ok" else ""
        vb = tb if tb is not None else (why if why != "no Vitis result" else "")
        out.append(f"| {_md(k)} | {_md((r.get('v2') or {}).get('source_match'))} | "
                   f"{'ok' if cg == 'ok' else _md(cg[:40])} | {'ok' if he == 'ok' else _md(he[:40])} | "
                   f"{_md(r.get('total_bram'))} | {_md(vb)} | {_md(r.get('wall_s'))} | {_md(r.get('cause') or '')} |")
    return "\n".join(out) + "\n"


def main():
    here = Path(__file__).resolve().parent
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--sweep", default=str(C.RESULTS_DIR / "hlsfactory-v2-sweep.json"))
    ap.add_argument("--vitis", default=str(C.RESULTS_DIR / "vitis.json"))
    ap.add_argument("--out", default=str(here.parent.parent / "hls-doc" / "hlsfactory-v2.md"))
    ap.add_argument("--csv", default=None, help="per-design CSV (default: --out with .csv)")
    ap.add_argument("--reclassify", action="store_true",
                    help="re-read the logs, classify again and write the classes into --sweep")
    a = ap.parse_args()
    sweep = C.load_json(a.sweep, {}) or {}
    vitis = C.load_json(a.vitis, {}) or {}
    if a.reclassify:
        for k, r in sweep.items():
            if k != "_meta":
                r.update(classify(r))
        C.dump_json(sweep, a.sweep)
    try:
        src = str(Path(a.sweep).resolve().relative_to(here.parent.parent))
    except ValueError:
        src = a.sweep
    page = build_page(sweep, vitis, src)
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(page)
    csv_path = Path(a.csv or str(Path(a.out).with_suffix(".csv")))
    write_csv(sweep, vitis, csv_path)
    n = len(sweep) - ("_meta" in sweep)
    print(f"wrote {a.out} and {csv_path} ({n} designs)")


def write_csv(sweep, vitis, path):
    """One row per design (the page's per-design table plus the error line), for diffing two sweeps."""
    import csv
    cols = ["design", "dataset", "source_match", "config", "cgeist", "hls_est", "bram", "vitis_bram",
            "wall_s", "cgeist_s", "cause", "cause_detail", "error_line"]
    with open(path, "w", newline="") as fh:
        w = csv.writer(fh, lineterminator="\n")
        w.writerow(cols)
        for k in sorted((k for k in sweep if k != "_meta"), key=str.lower):
            r = sweep[k]
            v2 = r.get("v2") or {}
            tb, why = truth_of(k, r, vitis)
            w.writerow([k, r.get("dataset"), v2.get("source_match"), v2.get("config"), r.get("cgeist_status"),
                        r.get("status") if r.get("cgeist_status") == "ok" else "", r.get("total_bram"),
                        tb if tb is not None else ("" if why == "no Vitis result" else why), r.get("wall_s"),
                        r.get("cgeist_s"), r.get("cause") or "", r.get("cause_detail") or "",
                        (r.get("error_line") or "")[:300]])


if __name__ == "__main__":
    main()
