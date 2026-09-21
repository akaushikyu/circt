#!/usr/bin/env python3
"""Mirror every cgeist HLS lit test as an hls-est lit test (phase P1a, MEMOS decision #47).

    python3 mirror_cgeist_tests.py [-j 4] [--timeout 120] [--long-timeout 600]
                                   [--only <substring>] [--dry-run] [--recheck]
                                   [--shim <name> --mirror-dir <dir>]

Inventory: every cgeist test under Polygeist's tools/cgeist/Test/HLS -- the one .test file per
HLSFactory_v2 design under hlsfactory/ (W8), and every other .c / .cpp file with a RUN line.

Per test:
  1. cgeist, the installed binary (common.CGEIST), with the harness's command for the default
     shim (common.DEFAULT_SHIM: its include directory and cgeist_flags, the Vitis front-end
     macros and -std=, --hls-annotate --raise-scf-to-affine --memref-fullrank) plus the test's own
     include and define flags. A design of the harness catalogue (the HLSFactory .test files and
     the polybench_pragmas tests) is compiled exactly as run_hlsest.py compiles it
     (run_hlsest.run_cgeist, the same MLIR cache), so the checked-in MLIR is the harness's input.
     Any other test is compiled from the first RUN line that runs cgeist and expects it to
     succeed (no `not`, no -DERRORS): its -I / -D flags and its --function= top.
  2. The MLIR, with the module attribute line stripped (run_hlsest.sanitize_mlir), is written to
     test/hls-est/Mirror/<path of the cgeist test relative to Test/HLS, suffix .mlir> under a
     header that names the cgeist test, the cgeist binary (md5, Polygeist commit), the shim, the
     Vitis td=off ground truth (a comment from results/vitis.json, never a CHECK) and a RUN line
     running common.DEFAULT_PIPELINE with the harness's top selection
     (--symbol-privatize=exclude=<top> --symbol-dce and top=<top> on --bram-analysis) and the
     harness's math-core cost table (lit substitution %hls_est_math_costs).
  3. hls-est runs that RUN line; its report becomes the CHECK lines at the end of the file (one
     CHECK / CHECK-NEXT pair per memref: the report line and its kind / BRAM, both anchored with
     {{$}}; a CHECK-NOT of any further report line before, between and after them, which pins the
     number of memrefs; then the total).
     The current hls-est output is the expectation: a regression pin, not Vitis.
     hls-est failing gives an XFAIL test; hls-est still running after --long-timeout seconds
     gives an XFAIL test whose RUN line stops hls-est after --timeout seconds. A test that passes
     only in the --long-timeout retry stays a passing test, and its header records the seconds
     hls-est took at generation (a slow lit test whose verdict may change at regeneration when it
     comes close to --long-timeout; W11-adopt review D5). That note is the file's last line, after
     the CHECK lines, so that it shifts no source location the CHECK lines pin.

A test cgeist cannot compile with this command gets no test file (decision #47: listed, with the
cgeist error, in the manifest and in hls-doc/tests.md). Every test, mirrored or not, is in
test/hls-est/Mirror/manifest.json (the inventory with tops and flags, the outcome, the Vitis
number), which make_test_results.py and the generated section of hls-doc/tests.md read.

Re-run after any cgeist install, any change of common.DEFAULT_PIPELINE / DEFAULT_SHIM, and any
hls-est change that is meant to change an estimate (then review the diff of the CHECK lines).
The script deletes Mirror files whose cgeist test no longer exists or no longer compiles.

--shim compiles under another shim (run_hlsest.py's names: real, exactclass, exact, scalar, or a
directory; `real`, the default since W11-adopt (MEMOS #67), is the real Vitis 2025.1 headers
through cgeist --xlx-headers, which the installed cgeist has since Polygeist 483ef69c). A shim other than
common.DEFAULT_SHIM writes a separate tree: --mirror-dir is then required and must not be the
checked-in test/hls-est/Mirror, and hls-doc/tests.md is left alone.
"""
import argparse
import concurrent.futures as cf
import datetime
import json
import os
import re
import shlex
import subprocess
import sys
import threading
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                       # noqa: E402
import designs as D                      # noqa: E402
import run_hlsest as RH                  # noqa: E402
import run_vitis as RV                   # noqa: E402

TEST_HLS = Path(C.POLYGEIST_TEST_HLS)
# The repository the tests come from: the Polygeist commit the Mirror headers name is its HEAD
# (W9 round 6 review defect 9: the hp_fft headers named the installed checkout's 13c303fa while
# their cgeist tests and binary came from a private branch).
POLYGEIST_REPO = TEST_HLS.parents[3]
DEFAULT_MIRROR = C.CIRCT / "test" / "hls-est" / "Mirror"
MIRROR = DEFAULT_MIRROR                  # --mirror-dir replaces both
MANIFEST = MIRROR / "manifest.json"


def shown(p):
    """A path relative to the CIRCT tree when it is inside it, else absolute (a --mirror-dir)."""
    p = Path(p)
    try:
        return str(p.relative_to(C.CIRCT))
    except ValueError:
        return str(p)
TESTS_DOC = C.CIRCT / "hls-doc" / "tests.md"
SCRATCH = Path.home() / "hls-est-work" / "mirror-cgeist"   # MLIR of the non-catalogue tests
MATH_COSTS_SUBST = "%hls_est_math_costs"
GEN_BEGIN = "<!-- BEGIN GENERATED by tools/hls-est-validate/mirror_cgeist_tests.py -->"
GEN_END = "<!-- END GENERATED -->"
# Words lit or FileCheck would read as directives if they appeared in the checked-in MLIR body.
DIRECTIVE_RE = re.compile(r"\b(RUN|CHECK[A-Z-]*|XFAIL|UNSUPPORTED|REQUIRES|ALLOW_RETRIES|END)\s*:")
PRINT_LOCK = threading.Lock()


def log(msg):
    with PRINT_LOCK:
        print(msg, flush=True)


# ------------------------------------------------------------------------------ inventory ----

def run_lines(path):
    """The RUN commands of a lit test, continuation lines joined."""
    cmds, cur = [], None
    for line in Path(path).read_text(errors="replace").splitlines():
        m = re.search(r"RUN:\s?(.*)$", line)
        if not m:
            continue
        part = m.group(1).rstrip()
        cur = part if cur is None else cur + " " + part
        if cur.endswith("\\"):
            cur = cur[:-1]
            continue
        cmds.append(cur.strip())
        cur = None
    return cmds


def first_cgeist_segment(cmd):
    """The `cgeist ...` part of one RUN command (up to the first pipe / &&), and whether the command
    expects cgeist to fail (`not cgeist`)."""
    for seg in re.split(r"\|\||&&|\|", cmd):
        toks = shlex.split(seg.strip(), posix=True) if seg.strip() else []
        if "cgeist" in toks:
            i = toks.index("cgeist")
            return toks[i + 1:], (i > 0 and toks[i - 1] == "not"), seg.strip()
    return None, False, None


def flags_of(tokens, test_dir):
    """(includes, defines, function, sources, extra) of a cgeist token list, with the cgeist lit
    substitutions the HLS tests use expanded: %stdinclude (polybench utilities), %hls_inputs,
    %vitis_frontend_* (the harness adds the front-end flags itself) and %vitis_include (the
    harness's shim replaces it)."""
    includes, defines, sources, func = [], [], [], None
    i = 0
    while i < len(tokens):
        t = tokens[i]
        if t == "%stdinclude":
            includes.append(str(TEST_HLS.parent / "polybench" / "utilities"))
        elif t in ("-I", "-D") and i + 1 < len(tokens):
            v = tokens[i + 1].replace("%S", str(test_dir)).replace("%hls_inputs", str(TEST_HLS / "Inputs"))
            (includes if t == "-I" else defines).append(v)
            i += 1
        elif t.startswith("-I") and len(t) > 2:
            includes.append(t[2:].replace("%S", str(test_dir)).replace("%hls_inputs", str(TEST_HLS / "Inputs")))
        elif t.startswith("-D") and len(t) > 2:
            defines.append(t[2:])
        elif t.startswith("--function="):
            func = t.split("=", 1)[1].strip("'\"")
        elif t == "%s":
            sources.append("%s")
        elif t.startswith("%S/"):
            sources.append(t[3:])
        elif not t.startswith("-") and not t.startswith("%") and re.search(r"\.(c|cc|cpp|cxx)$", t):
            sources.append(t)
        i += 1
    return includes, defines, func, sources


def hlsfactory_tests():
    return sorted((TEST_HLS / "hlsfactory").rglob("*.test"))


def other_tests():
    out = []
    for p in sorted(TEST_HLS.rglob("*")):
        rel = p.relative_to(TEST_HLS)
        if p.suffix not in (".c", ".cpp") or not p.is_file():
            continue
        if rel.parts[0] == "hlsfactory" or "Inputs" in rel.parts:
            continue
        if run_lines(p):
            out.append(p)
    return out


def mirror_path(test):
    """The Mirror file of a cgeist test given relative to Test/HLS."""
    rel = Path(test)
    return MIRROR / rel.with_suffix(".mlir")


def inventory(designs):
    """One entry per cgeist test. A catalogue design (a record of designs.py with this test file, or
    an HLSFactory_v2-only record whose slug names it) is compiled through its record."""
    by_test = {d["test_file"]: d for d in designs if d.get("test_file")}
    # The same tests by their path below Test/HLS: the catalogue names the installed Polygeist tree,
    # POLYGEIST_TEST_HLS may name a private checkout of it.
    by_rel = {d["test_file"].split("/Test/HLS/", 1)[1]: d
              for d in designs if "/Test/HLS/" in (d.get("test_file") or "")}
    by_slug = {}
    for d in designs:
        if d.get("origin") == "hlsfactory_v2" and not d.get("test_file"):
            by_slug[f"{d['dataset']}/{d['dataset']}__{d['slug']}.test"] = d
    entries = []
    for t in hlsfactory_tests():
        rel = str(t.relative_to(TEST_HLS))
        head = t.read_text(errors="replace").splitlines()[:3]
        mtop = re.search(r"\(top: ([^)]*)\)", head[0] if head else "")
        mmode = re.search(r"Mode: (\w+)", "\n".join(head))
        cmds = run_lines(t)
        toks, _, seg = first_cgeist_segment(cmds[0]) if cmds else (None, False, None)
        cd = re.search(r'cd "%S/([^"]*)"', cmds[0]) if cmds else None
        inc, dfn, func, srcs = flags_of(toks or [], t.parent)
        fe = [x for x in (toks or []) if x.startswith("%vitis_frontend")]
        rec = (by_test.get(str(t)) or by_rel.get(rel)
               or by_slug.get(str(t.relative_to(TEST_HLS / "hlsfactory"))))
        entries.append({
            "test": rel, "kind": "hlsfactory", "top": mtop.group(1) if mtop else None,
            "test_mode": mmode.group(1) if mmode else None,
            "run_line": {"dir": cd.group(1) if cd else None, "sources": srcs, "includes": inc,
                         "defines": dfn, "function": func, "frontend": fe[0] if fe else None},
            "design": C.design_key(rec) if rec else None, "_rec": rec,
        })
    for t in other_tests():
        rel = str(t.relative_to(TEST_HLS))
        rec = by_test.get(str(t)) or by_rel.get(rel)
        cmds = run_lines(t)
        chosen = None
        for c in cmds:
            toks, negated, seg = first_cgeist_segment(c)
            if toks is None or negated or "ERRORS" in " ".join(toks):
                continue
            chosen = (toks, seg)
            break
        if chosen:
            inc, dfn, func, srcs = flags_of(chosen[0], t.parent)
            rl = {"dir": ".", "sources": srcs or ["%s"], "includes": inc, "defines": dfn, "function": func}
        else:
            rl = None
        top = rec["top"] if rec else (rl["function"] if rl and rl["function"] not in (None, "*") else None)
        entries.append({"test": rel, "kind": "catalogue" if rec else "feature", "top": top,
                        "run_line": rl, "design": C.design_key(rec) if rec else None, "_rec": rec})
    return entries


# -------------------------------------------------------------------------------- cgeist ----

def compile_feature(e, shim):
    """cgeist on a non-catalogue test: the harness's command for the default shim plus the RUN
    line's -I / -D flags. Returns (status, mlir path or None, command)."""
    test = TEST_HLS / e["test"]
    rl = e["run_line"]
    if rl is None:
        return "cgeist test expects cgeist to fail (no RUN line runs cgeist without `not` / -DERRORS)", None, ""
    out = SCRATCH / (e["test"].replace("/", "__") + ".mlir")
    out.parent.mkdir(parents=True, exist_ok=True)
    sources = [test.name if s == "%s" else s for s in rl["sources"]]
    pseudo = {"sources": sources, "includes": rl["includes"], "defines": rl["defines"],
              "dataset": "cgeist-test"}
    status, cmdtxt = "", ""
    funcs = ["*"] + ([rl["function"]] if rl["function"] not in (None, "*") else [])
    for func in funcs:
        cmd = RH.cgeist_cmd(pseudo, shim, out, func)
        cmdtxt = shlex.join(cmd)
        if out.exists():
            out.unlink()
        try:
            p = subprocess.run(C.mem_limited(cmd), cwd=str(test.parent), capture_output=True, text=True,
                               errors="replace", timeout=RH.CGEIST_TIMEOUT)
        except subprocess.TimeoutExpired:
            status = f"cgeist timeout {RH.CGEIST_TIMEOUT}s"
            break
        if p.returncode == 0 and out.exists() and re.search(r"func\.func\s", out.read_text(errors="replace")):
            RH.sanitize_mlir(out)
            return "ok", out, cmdtxt
        if p.returncode == 0:
            status = "cgeist error: empty module (no functions emitted)"
        elif p.returncode < 0 or "Stack dump" in p.stderr:
            status = "cgeist crash"
        else:
            errs = [l for l in p.stderr.splitlines() if "error:" in l]
            status = "cgeist error: " + (errs[0].strip()[:200] if errs else f"exit {p.returncode}")
    return status, None, cmdtxt


MLIR_FROM = {}     # design key -> record of the --mlir-from run


def reused_mlir(rec, shim):
    """(status, mlir) of an earlier harness run (--mlir-from) when it compiled this design with the
    same inputs: its MLIR file name carries the cache key run_hlsest.source_hash gives now (sources,
    headers, shim, flags, cgeist md5), so it is the file run_cgeist would write. None otherwise."""
    prev = MLIR_FROM.get(C.design_key(rec))
    if not prev or not prev.get("mlir"):
        return None
    p = Path(prev["mlir"])
    if p.is_file() and p.name == f"{rec['benchmark']}.{RH.source_hash(rec, shim)}.mlir":
        return "ok", p
    return None


def compile_entry(e, shim):
    rec = e["_rec"]
    if rec is not None:
        reused = reused_mlir(rec, shim)
        if reused:
            st, mlir, note = reused[0], reused[1], "--function=*"
        else:
            st, mlir, note = RH.run_cgeist(rec, shim)
        cmd = shlex.join(RH.cgeist_cmd(rec, shim, "<mlir>", "*" if "function=*" in note or not note else rec["top"]))
        return st, mlir, cmd
    return compile_feature(e, shim)


# ------------------------------------------------------------------------------- hls-est ----

def defined_public_functions(text):
    return re.findall(r"^\s*func\.func\s+@([A-Za-z0-9_$.]+)\(", text, flags=re.M)


def hlsest_args(top):
    """The pipeline arguments after the input file, as the harness passes them (run_hlsest.run_hlsest):
    the top-selection prefix, common.DEFAULT_PIPELINE with top= and math-costs= on --bram-analysis."""
    args = C.DEFAULT_PIPELINE.split()
    pre = []
    if top:
        pre = [f"--symbol-privatize=exclude={top}", "--symbol-dce"]
        args = RH.with_top(args, top)
    args = RH.with_bram_option(args, f"math-costs={MATH_COSTS_SUBST}")
    return pre + args


def lit_quote(a):
    return shlex.quote(a)


def run_line(top, timeout=None, capped=False, spaced=False):
    """The RUN line. A test that is XFAIL because hls-est failed (capped) runs hls-est under the memory
    cap it failed under at generation (C.MEM_LIMIT_GB, prlimit --data, as run_hlsest), so that lit
    reproduces the failure instead of an unbounded run that can exhaust WSL's memory (MEMOS #65):
    hlsyn-vitis seidel-2d grows past 12 GB and is killed there. Every XFAIL test is also bounded by a
    timeout: a capped one gets --timeout as well, so that lit does not spend minutes growing hls-est to
    the cap again (seidel-2d: 303 s to 12 GB; W11-adopt review D5)."""
    cmd = " ".join(lit_quote(a) for a in hlsest_args(top))
    lead = "hls-est"
    if capped and C.MEM_LIMIT_GB > 0:
        lead = f"prlimit --data={int(C.MEM_LIMIT_GB * 2**30)} -- {lead}"
    if timeout:
        lead = f"timeout {timeout} {lead}"
    # %s of a test whose path has whitespace (Monte-Carlo "Random 100 Paths") is quoted for the shell.
    s = '"%s"' if spaced else "%s"
    return f"{lead} {s} {cmd} -o /dev/null | FileCheck {s}"


def run_hlsest(path, top, timeout):
    """hls-est on a Mirror file exactly as its RUN line does. Returns (status, stdout, seconds)."""
    args = [a.replace(MATH_COSTS_SUBST, str(RH.DEFAULT_MATH_COSTS)) for a in hlsest_args(top)]
    cmd = [C.HLS_EST, str(path), *args, "-o", "/dev/null"]
    t0 = time.time()
    try:
        p = subprocess.run(C.mem_limited(cmd), capture_output=True, text=True, errors="replace",
                           timeout=timeout)
    except subprocess.TimeoutExpired:
        return f"hls-est timeout {timeout}s", "", time.time() - t0
    el = time.time() - t0
    total, _ = RH.parse_hlsest_output(p.stdout)
    if p.returncode != 0:
        a = re.search(r"Assertion `([^']*)' failed", p.stderr)
        errs = [l for l in p.stderr.splitlines() if "error:" in l]
        why = a.group(0) if a else (errs[0].strip() if errs else f"exit {p.returncode}")
        return f"hls-est error: {why[:200]}", p.stdout, el
    if total is None:
        return "hls-est error: no total", p.stdout, el
    return "ok", p.stdout, el


def check_lines(stdout):
    """CHECK lines pinning the report: per memref its report line (the input path replaced by a
    regex) and the kind / BRAM line after it, each anchored at the end of the line, then the total.
    A CHECK-NOT for a report line before the first memref, between two memrefs and before the total
    pins the number of memrefs: a memref the report gains or loses fails the test."""
    no_memref = "// CHECK-NOT: {{^memref\\.}}"
    out = [no_memref]
    lines = stdout.splitlines()
    for i, line in enumerate(lines):
        if re.match(r"^memref\.\w+", line):
            pat = line.rstrip().replace("{{", "{{[{][{]}}").replace("[[", "{{[[][[]}}")
            pat = re.sub(r'loc\("[^"]*"', 'loc("{{[^"]*}}"', pat)
            out.append(f"// CHECK: {pat}{{{{$}}}}")
            if i + 1 < len(lines) and re.match(r"^\s+kind=", lines[i + 1]):
                out.append(f"// CHECK-NEXT: {lines[i + 1].strip()}{{{{$}}}}")
            out.append(no_memref)
    total, _ = RH.parse_hlsest_output(stdout)
    out.append(f"// CHECK: Total BRAM: {total}{{{{$}}}}")
    return out


def recheck_existing(path, timeout):
    """--recheck: re-runs hls-est on a checked-in Mirror file (its RUN line's arguments) and rewrites
    only its CHECK block; the header, the RUN line and the MLIR body stay byte for byte. Returns
    (path, outcome). An XFAIL test is left as it is."""
    text = path.read_text()
    if "// XFAIL:" in text:
        return path, "xfail (unchanged)"
    run = re.search(r'^// RUN: (?:timeout \d+ )?hls-est "?%s"? (.*) -o /dev/null \| FileCheck "?%s"?$', text, re.M)
    if not run:
        return path, "no RUN line"
    args = [a.replace(MATH_COSTS_SUBST, str(RH.DEFAULT_MATH_COSTS)) for a in shlex.split(run.group(1))]
    p = subprocess.run(C.mem_limited([C.HLS_EST, str(path), *args, "-o", "/dev/null"]),
                       capture_output=True, text=True, errors="replace", timeout=timeout)
    if p.returncode != 0:
        return path, f"hls-est exit {p.returncode}"
    body = text[:text.index("\n// CHECK")] if "\n// CHECK" in text else text.rstrip("\n")
    trailer = re.findall(r"^// slow: .*$", text, re.M)  # write_mirror's note after the CHECK lines
    new_text = body.rstrip("\n") + "\n\n" + "\n".join([*check_lines(p.stdout), *trailer]) + "\n"
    old_total = re.search(r"^// CHECK: Total BRAM: (\S+?)\{\{\$\}\}$", text, re.M)
    total, _ = RH.parse_hlsest_output(p.stdout)
    if not old_total or old_total.group(1) != str(total):
        return path, f"total changed {old_total and old_total.group(1)} -> {total}: not rewritten"
    path.write_text(new_text)
    return path, "rewritten"


# --------------------------------------------------------------------------- ground truth ----

def vitis_info(e, V):
    """{'bram', 'status', 'note', 'key'} of the design's Vitis td=off entry when it was synthesised
    from the sources this test compiles (run_vitis.cache_keys), else a reason; None for tests that
    are no catalogue design."""
    rec = e["_rec"]
    if rec is None:
        return None
    v = V.get(C.design_key(rec))
    if not v:
        return {"status": "no ground truth (not synthesised)"}
    try:
        keys = RV.cache_keys(rec)
    except OSError as ex:
        keys = {"error": repr(ex)}
    if v.get("key") not in keys.values():
        return {"status": "no ground truth for these sources (the Vitis entry was synthesised from other sources)",
                "key": v.get("key")}
    if v.get("status") != "ok":
        return {"status": f"{v.get('status')}: {str(v.get('note', ''))[:160]}", "key": v.get("key")}
    return {"status": "ok", "bram": v["totals"]["BRAM"], "key": v.get("key")}


# ------------------------------------------------------------------------------- writing ----

def header(e, meta, top, vit, note_lines):
    h = [f"// hls-est mirror of the cgeist lit test Polygeist tools/cgeist/Test/HLS/{e['test']}",
         "// generated by tools/hls-est-validate/mirror_cgeist_tests.py; do not edit by hand.",
         f"// cgeist: {meta['cgeist']} (md5 {meta['cgeist_md5']}, Polygeist {meta['polygeist_commit']}),"
         f" shim {meta['shim']} ({' '.join(meta['shim_flags'])})"]
    if e["design"]:
        h.append(f"// design: {e['design']} (harness catalogue record; compiled as run_hlsest.py does)")
    h.append(f"// top: {top}" if top else
             "// top: none (the test names no top function and defines several; every public function is estimated)")
    if vit is None:
        h.append("// Vitis 2025.1 td=off: none (not a catalogue design)")
    elif vit["status"] == "ok":
        h.append(f"// Vitis 2025.1 td=off: BRAM_18K {vit['bram']} (results/vitis.json, key {vit['key']}); "
                 "a comment only, the CHECK lines pin hls-est's current output")
    else:
        h.append(f"// Vitis 2025.1 td=off: {vit['status']}")
    h += [f"// {l}" for l in note_lines]
    return h


def write_mirror(e, mlir_path, meta, args, V):
    """Writes the Mirror file of one compiled test; returns the manifest fields of the outcome."""
    body = Path(mlir_path).read_text(errors="replace")
    bad = DIRECTIVE_RE.search(body)
    if bad:
        return {"outcome": "not written", "reason": f"the MLIR contains the lit directive word {bad.group(0)!r}"}
    funcs = defined_public_functions(body)
    top, top_note = None, []
    if e["_rec"] is not None:
        top, rule = RH.find_top(mlir_path, e["_rec"]["top"])
        if rule in ("single", "last") and e["_rec"]["top"] not in (top or ""):
            top_note = [f"the design's top {e['_rec']['top']!r} is not among the MLIR functions "
                        "(run_hlsest.py reports 'top not found'); every public function is estimated"]
            top = None
    elif e["top"] and e["top"] in funcs:
        top = e["top"]
    elif len(funcs) == 1:
        top = funcs[0]
    vit = vitis_info(e, V)
    out = mirror_path(e["test"])
    out.parent.mkdir(parents=True, exist_ok=True)

    spaced = re.search(r"\s", str(out)) is not None

    def emit(run, extra, checks, trailer=()):
        lines = header(e, meta, top, vit, top_note + extra) + [f"// RUN: {run}"] + extra_directives
        text = "\n".join(lines) + "\n\n" + body.rstrip("\n") + "\n\n" + "\n".join([*checks, *trailer]) + "\n"
        out.write_text(text)

    extra_directives = []
    emit(run_line(top, spaced=spaced), [], ["// CHECK: Total BRAM:"])
    st, stdout, el = run_hlsest(out, top, args.timeout)
    slow = st.startswith("hls-est timeout")
    if slow:
        st, stdout, el = run_hlsest(out, top, args.long_timeout)
    res = {"top": top, "vitis": vit, "mirror": shown(out)}
    if st == "ok":
        checks = check_lines(stdout)
        # The slow note goes after the CHECK lines: the CHECK lines pin source locations (line:column)
        # of the file hls-est just read, so the header must not grow by a line.
        note = []
        if slow:
            note = [f"// slow: hls-est took {el:.0f} s at generation (over the {args.timeout} s timeout, inside the "
                    f"{args.long_timeout} s retry); this test costs about as long in every lit run"]
            res["hlsest_s"] = round(el)
        emit(run_line(top, spaced=spaced), [], checks, note)
        total, mems = RH.parse_hlsest_output(stdout)
        res.update({"outcome": "pass", "hlsest_bram": total, "memrefs": len(mems)})
    elif st.startswith("hls-est timeout"):
        # (no "XFAIL:" in these notes: lit would read the word as the directive)
        reason = (f"expected to fail: hls-est did not finish within {args.long_timeout} s at generation; the RUN line "
                  f"stops it after {args.timeout} s")
        extra_directives = ["// XFAIL: *"]
        emit(run_line(top, args.timeout, spaced=spaced), [reason], ["// CHECK: Total BRAM:"])
        res.update({"outcome": "xfail", "reason": f"hls-est timeout (> {args.long_timeout} s)"})
    else:
        extra_directives = ["// XFAIL: *"]
        emit(run_line(top, args.timeout, capped=True, spaced=spaced),
             [f"expected to fail: {st} (under a {C.MEM_LIMIT_GB:g} GB memory cap, as the RUN line; "
              f"the RUN line also stops it after {args.timeout} s)"],
             ["// CHECK: Total BRAM:"])
        res.update({"outcome": "xfail", "reason": st})
    return res


def process(e, meta, args, V, shim):
    t0 = time.time()
    st, mlir, cmd = compile_entry(e, shim)
    r = {k: v for k, v in e.items() if not k.startswith("_")}
    r["cgeist_cmd"], r["cgeist_status"] = cmd, st
    if st != "ok":
        r.update({"outcome": "cgeist failure", "reason": st, "vitis": vitis_info(e, V)})
        log(f"[cgeist] {e['test']}: {st[:120]}")
        return r
    if args.dry_run:
        r["outcome"] = "dry-run"
        return r
    r.update(write_mirror(e, mlir, meta, args, V))
    log(f"[{r['outcome']}] {e['test']} ({time.time() - t0:.0f}s) {r.get('hlsest_bram', r.get('reason', ''))}")
    return r


# ------------------------------------------------------------------------------- reports ----

def group_of(test):
    p = Path(test).parts
    return f"hlsfactory/{p[1]}" if p[0] == "hlsfactory" else p[0] if len(p) > 1 else "(top level)"


def tests_doc_section(manifest):
    rows = manifest["tests"]
    from collections import Counter, OrderedDict
    per = OrderedDict()
    for r in sorted(rows, key=lambda r: r["test"]):
        per.setdefault(group_of(r["test"]), Counter())[r["outcome"]] += 1
    m = manifest["_meta"]
    out = [GEN_BEGIN,
           f"generated by tools/hls-est-validate/mirror_cgeist_tests.py from Polygeist tools/cgeist/Test/HLS "
           f"(cgeist md5 {m['cgeist_md5']}, Polygeist {m['polygeist_commit']}), hls-est {m['hls_est_git']} "
           f"(md5 {m['hls_est_md5']}) and tools/hls-est-validate/results/vitis.json on {m['date']}",
           "",
           f"Pipeline of every RUN line (common.DEFAULT_PIPELINE): `{m['pipeline']}`; shim `{m['shim']}`.",
           "",
           "### Counts per source directory",
           "",
           "`cgeist tests` counts the cgeist lit tests in that directory of Polygeist `tools/cgeist/Test/HLS`; "
           "every one is either a Mirror test (pass or XFAIL) or a cgeist failure (no test file, listed below).",
           "",
           "| source directory | cgeist tests | Mirror tests | pass | XFAIL | cgeist failure (no test) |",
           "|---|--:|--:|--:|--:|--:|"]
    tot = Counter()
    for g, c in per.items():
        n = sum(c.values())
        tot.update(c)
        out.append(f"| {g} | {n} | {c['pass'] + c['xfail']} | {c['pass']} | {c['xfail']} | {c['cgeist failure']} |")
    n = sum(tot.values())
    out.append(f"| **total** | **{n}** | **{tot['pass'] + tot['xfail']}** | **{tot['pass']}** | "
               f"**{tot['xfail']}** | **{tot['cgeist failure']}** |")
    other = {k: v for k, v in tot.items() if k not in ("pass", "xfail", "cgeist failure")}
    if other:
        out.append("")
        out.append("Other outcomes: " + ", ".join(f"{k} {v}" for k, v in sorted(other.items())))
    out += ["", "### XFAIL tests", "", "| test | reason |", "|---|---|"]
    for r in sorted(rows, key=lambda r: r["test"]):
        if r["outcome"] == "xfail":
            out.append(f"| `{r['mirror']}` | {md_cell(r['reason'])} |")
    out += ["", "### cgeist tests without a Mirror test (cgeist cannot compile them with the harness's command)",
            "", "| cgeist test | design | reason |", "|---|---|---|"]
    for r in sorted(rows, key=lambda r: r["test"]):
        if r["outcome"] not in ("pass", "xfail"):
            out.append(f"| `{r['test']}` | {r.get('design') or ''} | {md_cell(r.get('reason', ''))} |")
    out.append(GEN_END)
    return "\n".join(out)


def md_cell(s):
    return str(s or "").replace("|", "\\|").replace("\n", " ")


def update_tests_doc(section):
    txt = TESTS_DOC.read_text() if TESTS_DOC.exists() else ""
    if GEN_BEGIN in txt and GEN_END in txt:
        a = txt.index(GEN_BEGIN)
        b = txt.index(GEN_END) + len(GEN_END)
        txt = txt[:a] + section + txt[b:]
    else:
        txt = txt.rstrip("\n") + "\n\n## Mirror suite baseline (generated)\n\n" + section + "\n"
    TESTS_DOC.write_text(txt)


def git_head(repo):
    try:
        return subprocess.run(["git", "-C", str(repo), "rev-parse", "--short=8", "HEAD"],
                              capture_output=True, text=True, timeout=60).stdout.strip()
    except (OSError, subprocess.SubprocessError):
        return "unknown"


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("-j", type=int, default=4)
    ap.add_argument("--timeout", type=int, default=C.HLSEST_TIMEOUT,
                    help="hls-est seconds before the long retry (the harness's timeout)")
    ap.add_argument("--long-timeout", type=int, default=600,
                    help="hls-est seconds of the retry; slower designs become XFAIL tests")
    ap.add_argument("--only", default="", help="only the tests whose path contains this text "
                    "(the manifest and tests.md are then not rewritten)")
    ap.add_argument("--dry-run", action="store_true", help="inventory and cgeist only")
    ap.add_argument("--recheck", action="store_true",
                    help="no cgeist: re-run hls-est on every checked-in Mirror test (its own RUN line) and "
                         "rewrite only the CHECK block in the current format; the manifest is not rewritten")
    ap.add_argument("--mlir-from", default=None,
                    help="an earlier run_hlsest.py result JSON: reuse its MLIR files where they carry "
                         "the cache key of the current inputs (same cgeist md5, shim and flags)")
    ap.add_argument("--shim", default=C.DEFAULT_SHIM,
                    help=f"header shim, as run_hlsest.py --shim (default {C.DEFAULT_SHIM}); another shim "
                         "needs --mirror-dir")
    ap.add_argument("--mirror-dir", default=None,
                    help="output tree instead of test/hls-est/Mirror (required with a non-default --shim)")
    args = ap.parse_args()
    global MIRROR, MANIFEST
    if args.mirror_dir:
        MIRROR = Path(args.mirror_dir).resolve()
        MANIFEST = MIRROR / "manifest.json"
    if Path(RH.resolve_shim(args.shim)) != Path(RH.resolve_shim(C.DEFAULT_SHIM)) and MIRROR == DEFAULT_MIRROR:
        sys.exit(f"--shim {args.shim} is not the default shim ({C.DEFAULT_SHIM}): give --mirror-dir "
                 "(the checked-in Mirror suite pins the default shim's output)")
    if args.recheck:
        files = sorted(p for p in MIRROR.rglob("*.mlir") if args.only in str(p))
        from collections import Counter
        with cf.ThreadPoolExecutor(args.j) as ex:
            res = list(ex.map(lambda p: recheck_existing(p, args.long_timeout), files))
        for p, o in res:
            if o not in ("rewritten", "xfail (unchanged)"):
                log(f"[recheck] {shown(p)}: {o}")
        log(f"recheck: {dict(Counter(o.split(' ')[0] for _, o in res))}")
        return

    shim = RH.resolve_shim(args.shim)
    designs = D.load_designs(catalog="v2", problems=[])
    entries = inventory(designs)
    if args.only:
        entries = [e for e in entries if args.only in e["test"]]
    collide = {}
    for e in entries:
        collide.setdefault(str(mirror_path(e["test"])), []).append(e["test"])
    dup = {k: v for k, v in collide.items() if len(v) > 1}
    if dup:
        sys.exit(f"two cgeist tests map to one Mirror file: {dup}")
    if args.mlir_from:
        prev = C.load_json(args.mlir_from, {}) or {}
        MLIR_FROM.update({k: v for k, v in prev.items() if k != "_meta"})
    V = C.load_json(C.RESULTS_DIR / "vitis.json", {}) or {}
    meta = {
        "cgeist": C.CGEIST, "cgeist_md5": RH.cgeist_md5_or_raise(),
        "polygeist_commit": git_head(POLYGEIST_REPO),
        "shim": str(Path(shim).relative_to(C.CIRCT)) if str(shim).startswith(str(C.CIRCT)) else str(shim),
        "shim_flags": RH.shim_cgeist_flags(shim),
        "hls_est": C.HLS_EST, "hls_est_md5": C.md5_of_file(C.HLS_EST), "hls_est_git": git_head(C.CIRCT),
        "pipeline": C.DEFAULT_PIPELINE, "date": datetime.date.today().isoformat(),
        "timeout": args.timeout, "long_timeout": args.long_timeout,
    }
    log(f"{len(entries)} cgeist tests; cgeist md5 {meta['cgeist_md5']}, hls-est md5 {meta['hls_est_md5']}")
    t0 = time.time()
    with cf.ThreadPoolExecutor(args.j) as ex:
        results = list(ex.map(lambda e: process(e, meta, args, V, shim), entries))
    meta["elapsed_s"] = round(time.time() - t0)
    if args.only or args.dry_run:
        print(json.dumps([{k: r.get(k) for k in ("test", "outcome", "reason", "hlsest_bram")} for r in results],
                         indent=1)[:4000])
        return
    keep = {r["mirror"] for r in results if r.get("mirror") and r["outcome"] in ("pass", "xfail")}
    for p in MIRROR.rglob("*.mlir"):
        if shown(p) not in keep:
            p.unlink()
    for r in results:
        if r.get("mirror") and r["outcome"] not in ("pass", "xfail"):
            r.pop("mirror")
    manifest = {"_meta": meta, "tests": sorted(results, key=lambda r: r["test"])}
    MIRROR.mkdir(parents=True, exist_ok=True)
    MANIFEST.write_text(json.dumps(manifest, indent=1, sort_keys=True) + "\n")
    if MIRROR == DEFAULT_MIRROR:
        update_tests_doc(tests_doc_section(manifest))
    from collections import Counter
    log(f"done in {meta['elapsed_s']} s: {dict(Counter(r['outcome'] for r in results))}")


if __name__ == "__main__":
    main()
