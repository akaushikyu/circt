#!/usr/bin/env python3
"""Build the HELD-OUT evaluation catalogue for hls-est (hls-doc/heldout.md).

    python3 -I build_heldout.py [--root /mnt/d/HLS_heldout] [--dry-run]

Inputs (cloned / downloaded once into <root>/src, never modified; provenance in <root>/provenance):
  src/forgehls_kernels/kernels/<suite>/<kernel>/   ForgeHLS kernels (Hugging Face zedongpeng/forgehls,
                                                   kernels/kernels_data.tar.gz, without project/, logs,
                                                   array_info/, loop_info/)
  src/forgehls/                                    the ForgeHLS GitHub repository (licence, docs)
  src/vitis_libraries/                             Xilinx/Vitis_Libraries, branch 2025.1, sparse (*/L1)

Output:
  catalog/heldout-forgehls/<design>/     hlsfactory.toml + dataset_hls.tcl + a copy of the kernel directory
  catalog/heldout-vitislib/<design>/     hlsfactory.toml + dataset_hls.tcl (sources referenced in src/ by
                                         absolute path) + heldout_sources.txt (sha256 of every file the
                                         design names, so the Vitis cache key changes if a source changes)
  catalog/manifest.json                  every candidate: kept / excluded with the reason, family, provenance

The catalogue has the HLSFactory 1.1 layout (hlsfactory.toml naming a VitisHLSSynthFlow synth_tcl), so
hlsfactory_v2.discover() reads it.  Every dataset_hls.tcl is normalised to the ground-truth configuration
(xc7z020clg400-1, 10 ns, flow_target vivado, throughput_driven off); the suite's own part, clock and config_*
settings are dropped and kept as informational toml tags.  Source pragmas are untouched.

Training-set deduplication (ForgeHLS: content, near-content and name; Vitis_Libraries: content and
near-content, name collisions listed only): the training set is every C/C++ file under the HLSFactory_v2
dataset tree, the Polygeist tools/cgeist/Test/HLS tree, circt test/hls-est and the experiment kernels
(~/hls-est-work/exp-src), each file and each directory (the union of its files: a training design split
into .h/.cpp) being one training unit, and the design names of the v2 catalogue
(designs.load_designs(catalog='v2')).  Near-content is tested in both directions: a held-out design source
whose shingles are >= 80 % in one training unit, or one that holds >= 60 % of a training unit's shingles
(the training code inside a larger or combined held-out file, e.g. an example's header and kernel merged
into one combined.cpp).

Families (the split's unit, assign_families): designs whose sources + local headers are near-duplicates of
each other in either direction (the same containment test, >= 80 %, with every preprocessor line removed so
that designs differing only in pragmas, macros or -D flags compare equal), designs with the same name after
generic variant-suffix stripping (variant_stem), and the per-suite rules (ForgeHLS: kernel name without
widths and numbers; Vitis_Libraries: library component, shared design source).

The catalogue is updated in place: a file is rewritten only when its content changes (atomically), and only
the directories of designs that are no longer kept are removed, so a ground-truth run reading other designs
is not disturbed.

Nothing here runs cgeist, hls-est or Vitis.  Downloaded files are only read (python -I; no code from them
is imported or executed; the Tcl scripts are evaluated by hlsfactory_v2.TclSubset, which only records).
"""
from __future__ import annotations

import argparse
import hashlib
import tempfile
import json
import os
import posixpath
import re
import shutil
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
HARNESS = HERE.parent
sys.path.insert(0, str(HARNESS))
import hlsfactory_v2 as V2                    # noqa: E402  (harness module: Tcl subset, toml rules)

DEFAULT_ROOT = "/mnt/d/HLS_heldout"
PART, CLOCK_NS, FLOW_TARGET = "xc7z020clg400-1", "10", "vivado"
FH_DATASET, VL_DATASET = "heldout-forgehls", "heldout-vitislib"

FH_PROVENANCE = {
    "suite": "ForgeHLS", "paper": "arXiv 2507.03255",
    "repository": "https://github.com/zedong-peng/ForgeHLS", "repository_commit": None,
    "kernels": "https://huggingface.co/datasets/zedongpeng/forgehls (kernels/kernels_data.tar.gz)",
    "kernels_revision": "b9a8cf34542f94bd414c162a18f43992eada6a8f",
    "kernels_sha256": "1c75ccb0b6d2367f76ae2c0375d7c807b9fe4a59834c022bbd31ee18fd8e3070",
    "licence": "MIT (GitHub LICENSE, 'Copyright (c) 2025 PZD-CHINA'; Hugging Face card: license: mit; the "
               "card's closing line also names the arXiv non-exclusive distribution licence)",
    "spdx": "MIT",
}
VL_PROVENANCE = {
    "suite": "AMD Vitis_Libraries L1", "repository": "https://github.com/Xilinx/Vitis_Libraries",
    "branch": "2025.1", "repository_commit": None,
    "licence": "Apache-2.0 (LICENSE.txt and every library's LICENSE.txt) except motor_control "
               "(motor_control/LICENSE.txt: X11)", "spdx": "Apache-2.0 AND X11",
}
FH_SUITE_SHORT = {"CHStone": "chstone", "MachSuite": "machsuite", "PolyBench": "polybench",
                  "rosetta": "rosetta", "Vitis-HLS-Introductory-Examples-flatten": "vitisex",
                  "ai_fpga_hls_algorithms": "aifpga", "hls_algorithms": "hlsalgo",
                  "leetcode_hls_algorithms": "leetcode", "operators": "operators",
                  "rtl_chip": "rtlchip", "rtl_ip": "rtlip", "rtl_module": "rtlmodule"}

TRAIN_TREES = ["/mnt/d/HLSFactory_v2/HLSFactory/hlsfactory/hls_dataset_sources",
               "/mnt/d/HLS/Polygeist/tools/cgeist/Test/HLS",
               str(HARNESS.parent.parent / "test" / "hls-est"),
               str(Path.home() / "hls-est-work" / "exp-src")]      # experiment kernels hls-est was tuned on
CXX_EXT = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx", ".inc"}
# names too generic to identify a design (file stems / tops of many unrelated designs)
GENERIC_NAMES = {"top", "main", "kernel", "kernels", "example", "dut", "krnl", "test", "tb", "testbench",
                 "func", "foo", "compute", "run", "support", "common", "utils", "util", "config", "defines",
                 "host", "header", "types", "src", "hls", "design", "accel", "core", "workload", "harness"}
NEAR_CONTAINMENT = 0.80       # share of a held-out file's 5-token shingles found in one training unit
REVERSE_CONTAINMENT = 0.60    # share of a training unit's shingles found in one held-out design source
FAMILY_CONTAINMENT = 0.80     # share of one held-out design's shingles found in another (either direction)
SHINGLE = 5
MIN_SHINGLES = 30             # files with fewer shingles are compared exactly only


# ------------------------------------------------------------------------------------------ normalising
_COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)
_TOKEN = re.compile(r"[A-Za-z_]\w*|\d[\w.]*|\S")


def read_text(p) -> str:
    return Path(p).read_bytes().decode("utf-8", errors="replace").replace("\r\n", "\n")


def norm_source(text: str) -> str:
    """Comments removed, whitespace collapsed (the exact-content identity)."""
    return " ".join(_COMMENT.sub(" ", text).split())


def stable_hash(s: str) -> int:
    """A 64-bit hash that is the same in every run (Python's hash() of a str is salted per process)."""
    return int.from_bytes(hashlib.blake2b(s.encode("utf-8", "surrogatepass"), digest_size=8).digest(), "little")


_PRAGMA_OR_INCLUDE = re.compile(r"\s*#\s*(pragma|include)\b")
_DIRECTIVE = re.compile(r"\s*#")


def shingles(text: str, directives: re.Pattern = _PRAGMA_OR_INCLUDE) -> set[int]:
    """5-token shingles (stable_hash) of the source with comments and the preprocessor lines matching
    `directives` removed: by default #pragma and #include lines (so a copy that differs only in pragmas or
    includes is a near duplicate); family_shingles removes every preprocessor line."""
    t = _COMMENT.sub(" ", text)
    t = "\n".join(l for l in t.split("\n") if not directives.match(l))
    toks = _TOKEN.findall(t)
    return {stable_hash(" ".join(toks[i:i + SHINGLE])) for i in range(max(0, len(toks) - SHINGLE + 1))}


def family_shingles(text: str) -> set[int]:
    """Shingles for the family test: every preprocessor line removed (#pragma, #include, #define, #if...),
    so two designs that differ only in pragmas, macros or -D flags compare equal."""
    return shingles(text, _DIRECTIVE)


def norm_name(s: str) -> str:
    return re.sub(r"[^a-z0-9]", "", s.lower())


# Generic variant suffixes (a trailing name token): sizes and widths (16KB, 8bit, 1024), versions (v1, V2),
# plain numbers (crc32_2), and the words suites use for a variant of one component (static/dynamic/fixed
# implementations, lower/upper triangular, small/large configurations, optimised/reference versions).
_VARIANT_TOKEN = re.compile(r"(\d+([kmg]?b|bits?|x\d+)?|v\d+|static|dynamic|fixed|lo|up|lower|upper|low|"
                            r"small|medium|large|opt|optimi[sz]ed|naive|ref|reference|baseline|base)$")


def variant_stem(s: str) -> str:
    """The name without its trailing variant tokens (_VARIANT_TOKEN), tokens split at '_', '-', '.' and
    camelCase boundaries: zlibc_16KB, zlibc_static -> zlibc; symvLo, symvUp -> symv; sort_top_k_v1 ->
    sort_top_k; crc32_2 -> crc32.  A name made only of variant tokens is kept whole."""
    toks = [t for t in re.split(r"[_\-.\s]+|(?<=[a-z])(?=[A-Z])", s) if t]
    low = [t.lower() for t in toks]
    while len(low) > 1 and _VARIANT_TOKEN.fullmatch(low[-1]):
        low.pop()
    return "_".join(low) if low else s.lower()


def family_name(s: str) -> str:
    """Kernel name without widths / numbers / version suffixes: adder_8bit, adder_16bit -> adder."""
    s = variant_stem(s)
    s = re.sub(r"\d+\s*bits?", "", s)
    s = re.sub(r"(?<=[a-z])v\d+$", "", s)
    s = re.sub(r"\d+", "", s)
    return re.sub(r"[^a-z]", "", s) or norm_name(s)


def sha256_file(p) -> str:
    return hashlib.sha256(Path(p).read_bytes()).hexdigest()


# ------------------------------------------------------------------------------------------ training set
class Training:
    """Training units: every training file and every training directory (the union of the files directly
    in it, so a design split into .h / .cpp is also compared as a whole)."""

    def __init__(self):
        self.exact: dict[str, str] = {}               # normalised-content sha -> training file
        self.files: list[tuple[str, int]] = []        # (unit: a file, or a directory with a trailing '/', shingles)
        self.index: dict[int, list[int]] = defaultdict(list)
        self.names: dict[str, set[str]] = defaultdict(set)   # normalised name -> training design keys

    def _add_unit(self, name: str, sh: set[int]):
        if len(sh) >= MIN_SHINGLES:
            k = len(self.files)
            self.files.append((name, len(sh)))
            for s in sh:
                self.index[s].append(k)

    def add_file(self, path: str) -> set[int]:
        try:
            text = read_text(path)
        except OSError:
            return set()
        h = hashlib.sha256(norm_source(text).encode()).hexdigest()
        self.exact.setdefault(h, path)
        sh = shingles(text)
        self._add_unit(path, sh)
        return sh

    def add_directory(self, path: str, sh: set[int]):
        self._add_unit(path.rstrip("/") + "/", sh)

    def add_name(self, name: str, key: str):
        n = norm_name(name)
        if len(n) >= 3 and n not in GENERIC_NAMES:
            self.names[n].add(key)

    def match_exact(self, text: str):
        return self.exact.get(hashlib.sha256(norm_source(text).encode()).hexdigest())

    def match_near(self, text: str):
        """((forward containment, unit), (reverse containment, unit)): the best share of the held-out text's
        shingles found in one training unit, and the best share of one training unit's shingles found in
        the held-out text (ties: the first unit)."""
        sh = shingles(text)
        if len(sh) < MIN_SHINGLES:
            return (0.0, None), (0.0, None)
        cnt: dict[int, int] = defaultdict(int)
        for s in sh:
            for k in self.index.get(s, ()):
                cnt[k] += 1
        if not cnt:
            return (0.0, None), (0.0, None)
        kf = max(sorted(cnt), key=lambda k: cnt[k])
        kr = max(sorted(cnt), key=lambda k: cnt[k] / self.files[k][1])
        return ((cnt[kf] / len(sh), self.files[kf][0]),
                (cnt[kr] / self.files[kr][1], self.files[kr][0]))


def load_training() -> Training:
    tr = Training()
    for tree in TRAIN_TREES:
        for dp, dn, fn in os.walk(tree):
            dn[:] = sorted(d for d in dn if not d.startswith(".") and d not in ("Output", "__pycache__"))
            unit: set[int] = set()
            for f in sorted(fn):
                if posixpath.splitext(f)[1].lower() in CXX_EXT:
                    unit |= tr.add_file(posixpath.join(dp, f))
            tr.add_directory(dp, unit)
    import designs as D                                  # noqa: E402  (harness module)
    for d in D.load_designs(catalog="v2", verify=False, problems=[]):
        key = f"{d['dataset']}/{d['benchmark']}"
        for part in d["benchmark"].split("__"):
            tr.add_name(part, key)
        tr.add_name(posixpath.basename(d["dir"].rstrip("/")), key)
        if d.get("top"):
            tr.add_name(d["top"], key)
        for s in d["sources"]:
            tr.add_name(posixpath.splitext(posixpath.basename(s))[0], key)
    return tr


# ------------------------------------------------------------------------------------------ Tcl output
def tcl_word(s: str) -> str:
    return "{" + s + "}" if re.search(r"[\s$\[\]\"\\;]", s) else s


def normalised_tcl(origin: str, top: str, files: list[str], cflags: str, dropped: dict) -> str:
    lines = ["# Held-out design: generated by circt tools/hls-est-validate/heldout/build_heldout.py; do not edit.",
             f"# origin: {origin}",
             "# Normalised to the hls-est ground-truth configuration; the suite's own settings were dropped:"]
    for k, v in dropped.items():
        lines.append(f"#   {k}: {v}")
    lines += ["open_project project_1", f"set_top {top}"]
    for f in files:
        lines.append(f"add_files {tcl_word(f)}" + (f" -cflags {tcl_word(cflags)}" if cflags else ""))
    lines += [f'open_solution "solution1" -flow_target {FLOW_TARGET}', f"set_part {PART}",
              f"create_clock -period {CLOCK_NS} -name default",
              "config_array_partition -throughput_driven off", "csynth_design", "exit", ""]
    return "\n".join(lines)


def toml_text(design: str, dataset: str, tags: list[str], comment: list[str]) -> str:
    def q(s):
        return '"' + s.replace("\\", "\\\\").replace('"', '\\"') + '"'
    out = [f"# {c}" for c in comment]
    out += [f"design_name = {q(design)}", f"dataset_name = {q(dataset)}",
            "tags = [" + ", ".join(q(t) for t in tags) + "]", "",
            "[[flow_configs]]", 'flow_name = "VitisHLSSynthFlow"', 'synth_tcl = "dataset_hls.tcl"', ""]
    return "\n".join(out)


def rebuild_cflags(t, test_dir: str, missing: list[str] | None = None) -> tuple[str, list[str], list[str]]:
    """The union of the design files' -cflags with every -I made absolute (relative to the directory the
    suite's script runs in), and the -D / other flags kept in order.  An -I directory that does not exist
    in the checkout (generated by the suite's Makefile, or a submodule) is left out and appended to
    `missing` (the harness rejects a record naming a missing include directory)."""
    toks_out, incs, defs = [], [], []
    for f in t.files:
        if f["tb"] or not f["cflags"]:
            continue
        toks = V2.list_elements(f["cflags"])
        k = 0
        while k < len(toks):
            x = toks[k]
            if x in ("-I", "-D") and k + 1 < len(toks):
                x, k = x + toks[k + 1], k + 1
            if x.startswith("-I"):
                p = t.resolve(x[2:]) if x[2:] else test_dir
                x = "-I" + p
                if not os.path.isdir(p):
                    if missing is not None and p not in missing:
                        missing.append(p)
                    k += 1
                    continue
                if p not in incs:
                    incs.append(p)
            elif x.startswith("-D") and x[2:] not in defs:
                defs.append(x[2:])
            if x not in toks_out:
                toks_out.append(x)
            k += 1
    return " ".join(toks_out), incs, defs


def evaluate(dirpath: str, script: str, env=None, presets: dict | None = None):
    """The suite's script evaluated by the Tcl subset (records only).  `presets` are Tcl variables set
    before it: the Vitis_Libraries Makefiles write them into settings.tcl (CUR_DIR, XF_PROJ_ROOT, XPART,
    CSIM, CSYNTH, ...), which is not in the repository."""
    if not presets:
        return V2.evaluate_script(dirpath, script, env=env or {})
    text = "".join(f"set {k} {tcl_word(v)}\n" for k, v in presets.items()) + read_text(posixpath.join(dirpath, script))
    return V2.evaluate_script(dirpath, script, env=env or {}, text_override=text)


def loose_defines(path: str, name: str) -> bool:
    """A looser definition test than hlsfactory_v2's (parameters may contain parentheses, e.g.
    template arguments or function-pointer parameters): `name(` ... `)` [const] `{` without a `;` between."""
    try:
        text = _COMMENT.sub(" ", read_text(path))
    except OSError:
        return False
    return re.search(r"[\w>*&]\s*(?:\w+\s*::\s*)*\b" + re.escape(name) + r"\s*\([^;{}]*\)\s*(?:const\s*)?\{",
                     text) is not None


def sources_of(t, d: str) -> tuple[list[str], list[str]]:
    """Design sources (relative to d) and notes: hlsfactory_v2's rule; when it finds none because every
    design file is also added with -tb, the both-ways file that defines the top (loose_defines)."""
    srcs, _, notes = V2._sources_from_tcl(t, d)
    if srcs or not t.top:
        return srcs, notes
    tb = {posixpath.normpath(f["abs"]) for f in t.files if f["tb"]}
    for f in t.files:
        p = posixpath.normpath(f["abs"])
        if (not f["tb"] and p in tb and posixpath.splitext(p)[1].lower() in V2.C_SRC_EXT
                and os.path.isfile(p) and loose_defines(p, t.top)):
            r = posixpath.relpath(p, d)
            if r not in srcs:
                srcs.append(r)
                notes.append(f"add_files {f['path']}: also added with -tb; kept as a design file (it defines "
                             f"the top {t.top}; loose definition match)")
    return srcs, notes


# ------------------------------------------------------------------------------------------ ForgeHLS
def forgehls_candidates(src: str, tr: Training, dedupe_names=True) -> list[dict]:
    base = posixpath.join(src, "forgehls_kernels", "kernels")
    out = []
    for suite in sorted(os.listdir(base)):
        sdir = posixpath.join(base, suite)
        if not os.path.isdir(sdir):
            continue
        for k in sorted(os.listdir(sdir)):
            kdir = posixpath.join(sdir, k)
            if not os.path.isdir(kdir):
                continue
            short = FH_SUITE_SHORT.get(suite, norm_name(suite))
            c = {"suite": "forgehls", "dataset": FH_DATASET, "origin_rel": f"kernels/{suite}/{k}",
                 "origin_dir": kdir, "design": V2._safe_name(f"{short}__{k}"), "name": k,
                 "source_group": suite, "status": "kept", "reasons": []}
            out.append(c)
            if not os.path.isfile(posixpath.join(kdir, "run_hls.tcl")):
                c["status"], c["reasons"] = "excluded", ["no run_hls.tcl in the release"]
                continue
            t = evaluate(kdir, "run_hls.tcl")
            srcs, notes = sources_of(t, kdir)
            ttxt = posixpath.join(kdir, "top_function_name.txt")
            top_file = read_text(ttxt).strip() if os.path.isfile(ttxt) else None
            c.update(top=t.top, sources=srcs, orig_part=t.part, orig_clock=t.clock, tcl_errors=t.errors[:5],
                     source_notes=notes, top_function_name_txt=top_file)
            if not t.top:
                c["status"], c["reasons"] = "excluded", ["run_hls.tcl reaches no set_top"]
                continue
            if top_file and top_file != t.top:
                c["reasons"].append(f"note: top_function_name.txt {top_file!r} != set_top {t.top!r}")
            if not srcs:
                c["status"], c["reasons"] = "excluded", ["no design source file"]
                continue
            dedupe(c, [posixpath.join(kdir, s) for s in srcs] + local_headers(kdir), tr,
                   names=[k, t.top] + [posixpath.splitext(posixpath.basename(s))[0] for s in srcs],
                   names_exclude=dedupe_names)
    return out


def local_headers(d: str) -> list[str]:
    return [posixpath.join(d, f) for f in sorted(os.listdir(d))
            if posixpath.splitext(f)[1].lower() in (".h", ".hpp", ".hh", ".hxx")]


def dedupe(c: dict, files: list[str], tr: Training, names: list[str], names_exclude: bool):
    c["dup"] = {"exact": [], "near": [], "names": {}}
    for f in files:
        try:
            text = read_text(f)
        except OSError as e:
            c["status"], c["reasons"] = "excluded", [f"cannot read {f}: {e}"]
            return
        m = tr.match_exact(text)
        if m and norm_source(text):
            c["dup"]["exact"].append({"file": f, "training": m})
        (ratio, mf), (rev, mr) = tr.match_near(text)
        if ratio >= NEAR_CONTAINMENT:
            c["dup"]["near"].append({"file": f, "training": mf, "containment": round(ratio, 3)})
        elif ratio >= 0.5:
            c.setdefault("similar_info", []).append({"file": f, "training": mf, "containment": round(ratio, 3)})
        if rev >= REVERSE_CONTAINMENT:
            c["dup"].setdefault("reverse", []).append({"file": f, "training": mr, "reverse_containment": round(rev, 3)})
        elif rev >= 0.4:
            c.setdefault("similar_info", []).append({"file": f, "training": mr, "reverse_containment": round(rev, 3)})
    for n in names:
        if n and norm_name(n) in tr.names:
            c["dup"]["names"][n] = sorted(tr.names[norm_name(n)])[:5]
    # A design is a training duplicate when one of its design sources (not only a shared header) matches.
    src_files = set(files[:len(c.get("sources", files))])
    exact_src = [e for e in c["dup"]["exact"] if e["file"] in src_files]
    near_src = [e for e in c["dup"]["near"] if e["file"] in src_files]
    rev_src = [e for e in c["dup"].get("reverse", []) if e["file"] in src_files]
    if exact_src:
        c["status"] = "excluded"
        c["reasons"].append("duplicate of a training file (normalised content): " + exact_src[0]["training"])
    elif near_src:
        c["status"] = "excluded"
        c["reasons"].append(f"near-duplicate of a training file ({near_src[0]['containment']:.0%} of its "
                            f"5-token shingles in one file): {near_src[0]['training']}")
    elif rev_src:
        c["status"] = "excluded"
        c["reasons"].append(f"near-duplicate of a training unit, reverse ({rev_src[0]['reverse_containment']:.0%} "
                            f"of its 5-token shingles in the design source {posixpath.basename(rev_src[0]['file'])}): "
                            f"{rev_src[0]['training']}")
    if c["dup"]["names"]:
        if names_exclude and c["status"] == "kept":
            n, keys = next(iter(c["dup"]["names"].items()))
            c["status"] = "excluded"
            c["reasons"].append(f"name {n!r} matches training design(s) {', '.join(keys)}")
        elif not names_exclude:
            c["reasons"].append("note: name collision with training design(s) (not excluded: library code) "
                                + "; ".join(f"{n}: {', '.join(k)}" for n, k in c["dup"]["names"].items()))


def write_forgehls(c: dict, out_dir: str, commit: str):
    ddir = posixpath.join(out_dir, c["design"])
    os.makedirs(ddir, exist_ok=True)
    for f in sorted(os.listdir(c["origin_dir"])):
        p = posixpath.join(c["origin_dir"], f)
        if os.path.isfile(p):
            sync_copy(p, posixpath.join(ddir, "run_hls.orig.tcl" if f == "run_hls.tcl" else f))
        elif os.path.isdir(p):
            shutil.copytree(p, posixpath.join(ddir, f), dirs_exist_ok=True)
    t = evaluate(c["origin_dir"], "run_hls.tcl")
    missing: list[str] = []
    cflags, _, _ = rebuild_cflags(t, c["origin_dir"], missing)
    dropped = {"part": c.get("orig_part"), "clock": c.get("orig_clock")}
    for i, p in enumerate(missing):
        dropped[f"missing -I[{i}]"] = p
    origin = f"{FH_PROVENANCE['kernels']} @ {FH_PROVENANCE['kernels_revision']} {c['origin_rel']}/run_hls.tcl"
    write(posixpath.join(ddir, "dataset_hls.tcl"), normalised_tcl(origin, c["top"], c["sources"], cflags, dropped))
    tags = ["heldout", "suite:forgehls", f"family:{c['family']}", f"source_group:{c['source_group']}",
            f"origin:{c['origin_rel']}", f"original_part:{c.get('orig_part')}",
            f"original_clock:{c.get('orig_clock')}"]
    write(posixpath.join(ddir, "hlsfactory.toml"),
          toml_text(c["design"], FH_DATASET, tags,
                    ["Held-out evaluation design (hls-doc/heldout.md); generated by build_heldout.py.",
                     f"Source: ForgeHLS kernels {c['origin_rel']} (dataset: MIT); files copied unchanged, "
                     "run_hls.tcl kept as run_hls.orig.tcl.",
                     "Upstream licences are retained per file: a file's own header (e.g. Xilinx/AMD Apache-2.0 in "
                     "the Vitis introductory examples, the CHStone copyright notices) governs that file.",
                     "Synthesis configuration normalised (dataset_hls.tcl)."]))


# ------------------------------------------------------------------------------------------ Vitis_Libraries
VL_ENV = {"OPENCV_INCLUDE": "/nonexistent/opencv/include", "OPENCV_LIB": "/nonexistent/opencv/lib",
          "XILINX_VITIS": "/nonexistent/vitis", "XILINX_HLS": "/nonexistent/vitis_hls"}


def vl_presets(root: str, lib: str, dp: str) -> dict:
    """The settings.tcl variables of a Vitis_Libraries test (L1/tests Makefiles): CSYNTH on, every other
    step off; XPART is a placeholder (the part is normalised anyway)."""
    return {"CUR_DIR": dp, "XF_PROJ_ROOT": posixpath.join(root, lib), "XPART": "settings.tcl-part",
            "CSIM": "0", "CSYNTH": "1", "COSIM": "0", "VIVADO_SYN": "0", "VIVADO_IMPL": "0", "QOR_CHECK": "0"}


def vitislib_candidates(src: str, tr: Training) -> list[dict]:
    root = posixpath.join(src, "vitis_libraries")
    out = []
    scripts = []
    for lib in sorted(os.listdir(root)):
        tdir = posixpath.join(root, lib, "L1", "tests")
        if not os.path.isdir(tdir):
            continue
        for dp, dn, fn in os.walk(tdir):
            dn.sort()
            if "run_hls.tcl" in fn:
                scripts.append((lib, dp))
    for lib, dp in sorted(scripts):
        rel = posixpath.relpath(dp, root)                 # <lib>/L1/tests/...
        sub = rel.split("/")[3:]
        comp = next((x for x in sub if x not in ("hw", "sw", "hls", "kernel", "src")), sub[-1] if sub else lib)
        c = {"suite": "vitislib", "dataset": VL_DATASET, "origin_rel": rel, "origin_dir": dp,
             "design": V2._safe_name("__".join([lib] + sub)), "name": sub[-1] if sub else lib,
             "library": lib, "component": comp, "status": "kept", "reasons": []}
        out.append(c)
        t = evaluate(dp, "run_hls.tcl", env=dict(VL_ENV), presets=vl_presets(root, lib, dp))
        srcs, notes = sources_of(t, dp)
        abs_srcs = [posixpath.normpath(posixpath.join(dp, s)) for s in srcs]
        missing_incs: list[str] = []
        cflags, incs, defs = rebuild_cflags(t, dp, missing_incs)
        c.update(top=t.top, sources_abs=abs_srcs, cflags=cflags, includes_abs=incs, defines=defs,
                 missing_includes=missing_incs,
                 orig_part=t.part, orig_clock=t.clock, configs=t.configs, directives=t.directives,
                 tcl_errors=t.errors[:5], source_notes=notes, unset_env=sorted(t.unset_env))
        if not t.top:
            c["status"], c["reasons"] = "excluded", ["run_hls.tcl reaches no set_top"]
            continue
        if not abs_srcs:
            c["status"], c["reasons"] = "excluded", ["no design source file (" + "; ".join(notes[:2]) + ")"]
            continue
        missing = [s for s in abs_srcs if not os.path.isfile(s)]
        if missing:
            c["status"], c["reasons"] = "excluded", [f"design source missing in the checkout: {missing[0]}"]
            continue
        c["sources"] = abs_srcs
        dedupe(c, abs_srcs + local_headers(dp), tr,
               names=[c["name"], t.top], names_exclude=False)
    return out


def write_vitislib(c: dict, out_dir: str, commit: str, root: str):
    ddir = posixpath.join(out_dir, c["design"])
    os.makedirs(ddir, exist_ok=True)
    dropped = {"part": c.get("orig_part"), "clock": c.get("orig_clock")}
    for i, cfg in enumerate(c.get("configs") or []):
        dropped[f"config[{i}]"] = cfg
    for i, dv in enumerate(c.get("directives") or []):
        dropped[f"directive[{i}]"] = dv
    for i, p in enumerate(c.get("missing_includes") or []):
        dropped[f"missing -I[{i}]"] = p
    origin = f"{VL_PROVENANCE['repository']} @ {commit} {c['origin_rel']}/run_hls.tcl"
    write(posixpath.join(ddir, "dataset_hls.tcl"),
          normalised_tcl(origin, c["top"], c["sources_abs"], c["cflags"], dropped))
    # every file the design names, hashed: run_vitis.py's cache key hashes the design directory's
    # C/C++/.txt files, and the sources live in src/ (outside it)
    named = list(c["sources_abs"]) + local_headers(c["origin_dir"])
    lines = [f"# Vitis_Libraries {commit}: sha256 of the files this design names (cache-key witness)"]
    for p in named:
        lines.append(f"{sha256_file(p)}  {posixpath.relpath(p, root)}")
    write(posixpath.join(ddir, "heldout_sources.txt"), "\n".join(lines) + "\n")
    # the include trees the design's -I flags name (L1/include, per-test config directories, ...), hashed
    # whole: a header the design includes from there is in one of them (heldout_includes.txt is a .txt in the
    # design directory, so run_vitis.py's cache key covers it; training designs are not affected)
    inc_lines = [f"# Vitis_Libraries {commit}: sha256 over the C/C++ files under each -I directory "
                 "(path and content; cache-key witness)"]
    for d in c.get("includes_abs") or []:
        h, n = tree_digest(d)
        inc_lines.append(f"{h}  {posixpath.relpath(d, root)}/  ({n} files)")
    write(posixpath.join(ddir, "heldout_includes.txt"), "\n".join(inc_lines) + "\n")
    tags = ["heldout", "suite:vitislib", f"family:{c['family']}", f"library:{c['library']}",
            f"origin:{c['origin_rel']}", f"original_part:{c.get('orig_part')}",
            f"original_clock:{c.get('orig_clock')}"]
    tags += [f"dropped_config:{x}" for x in c.get("configs") or []]
    write(posixpath.join(ddir, "hlsfactory.toml"),
          toml_text(c["design"], VL_DATASET, tags,
                    ["Held-out evaluation design (hls-doc/heldout.md); generated by build_heldout.py.",
                     f"Source: Vitis_Libraries {c['origin_rel']} @ {commit} (licence: "
                     + ("X11" if c["library"] == "motor_control" else "Apache-2.0")
                     + "); sources referenced in place, each keeping its own licence header (third-party code "
                     "under */ext keeps its own licence).", "Synthesis configuration normalised (dataset_hls.tcl)."]))


_TREE_DIGESTS: dict[str, tuple[str, int]] = {}


def tree_digest(d: str) -> tuple[str, int]:
    """(sha256 over every C/C++ file under d, recursively: relative path and content; the number of files),
    memoised per directory."""
    if d not in _TREE_DIGESTS:
        h, n = hashlib.sha256(), 0
        for dp, dn, fn in os.walk(d):
            dn.sort()
            for f in sorted(fn):
                if posixpath.splitext(f)[1].lower() in CXX_EXT | {".tcc", ".ipp"}:
                    p = posixpath.join(dp, f)
                    h.update(posixpath.relpath(p, d).encode() + b"\0" + Path(p).read_bytes() + b"\0")
                    n += 1
        _TREE_DIGESTS[d] = (h.hexdigest(), n)
    return _TREE_DIGESTS[d]


# ------------------------------------------------------------------------------------------ families
class UF:
    def __init__(self):
        self.p = {}

    def find(self, x):
        self.p.setdefault(x, x)
        while self.p[x] != x:
            self.p[x] = self.p[self.p[x]]
            x = self.p[x]
        return x

    def union(self, a, b):
        ra, rb = self.find(a), self.find(b)
        if ra != rb:
            self.p[max(ra, rb)] = min(ra, rb)


def family_files(c: dict) -> list[str]:
    """The files a design's family fingerprint covers: its design sources and the headers next to them in
    the design's own directory (ForgeHLS: the kernel directory; Vitis_Libraries: the test directory)."""
    if c["suite"] == "forgehls":
        srcs = [posixpath.join(c["origin_dir"], s) for s in c.get("sources", [])]
    else:
        srcs = list(c.get("sources_abs", []))
    return srcs + [h for h in local_headers(c["origin_dir"]) if h not in srcs]


def content_pairs(fps: dict, threshold: float) -> list[tuple]:
    """Pairs (a, b) of keys whose fingerprints are near-duplicates in either direction: >= threshold of a's
    shingles occur in b (or of b's in a; every key is tested as a).  Fingerprints with fewer than
    MIN_SHINGLES shingles take part only through exact equality."""
    index: dict[int, list] = defaultdict(list)
    for k in sorted(fps):
        for x in fps[k]:
            index[x].append(k)
    pairs = []
    for k in sorted(fps):
        sh = fps[k]
        if len(sh) < MIN_SHINGLES:
            continue
        cnt: dict = defaultdict(int)
        for x in sh:
            for o in index[x]:
                if o != k:
                    cnt[o] += 1
        pairs += [(k, o) for o in sorted(cnt) if cnt[o] / len(sh) >= threshold]
    by_value: dict = defaultdict(list)
    for k in sorted(fps):
        if 0 < len(fps[k]) < MIN_SHINGLES:
            by_value[frozenset(fps[k])].append(k)
    for ks in by_value.values():
        pairs += [(ks[0], o) for o in ks[1:]]
    return pairs


def assign_families(cands: list[dict]):
    """Variants of one kernel / one library component share a family (the split's unit):
      - content: the designs' sources + local headers (family_files) are near-duplicates in either direction
        (family_shingles: every preprocessor line removed, so differences only in pragmas, macros or -D
        flags do not separate; >= FAMILY_CONTAINMENT), within a suite;
      - name: ForgeHLS kernels with the same family_name (widths, numbers and variant suffixes removed, any
        source group); Vitis_Libraries tests of one library component after variant_stem
        (<library>/<first directory under L1/tests that is not hw/sw>: symvLo, symvUp -> symv);
      - ForgeHLS: identical normalised main source; Vitis_Libraries: a shared design source file."""
    uf = UF()
    fps: dict[str, dict[tuple, set[int]]] = defaultdict(dict)
    for c in cands:
        me = ("d", c["dataset"], c["design"])
        uf.find(me)
        fp: set[int] = set()
        for f in family_files(c):
            try:
                fp |= family_shingles(read_text(f))
            except OSError:
                pass
        fps[c["dataset"]][me] = fp
        if c["suite"] == "forgehls":
            uf.union(me, ("fh-name", family_name(c["name"])))
            for s in c.get("sources", [])[:1]:
                try:
                    h = hashlib.sha256(norm_source(read_text(posixpath.join(c["origin_dir"], s))).encode()).hexdigest()
                    uf.union(me, ("fh-src", h))
                except OSError:
                    pass
        else:
            uf.union(me, ("vl-comp", c["library"], variant_stem(c["component"])))
            for s in c.get("sources_abs", []):
                uf.union(me, ("vl-src", s))
    for ds in sorted(fps):
        for a, b in content_pairs(fps[ds], FAMILY_CONTAINMENT):
            uf.union(a, b)
    groups = defaultdict(list)
    for c in cands:
        groups[uf.find(("d", c["dataset"], c["design"]))].append(c)
    for members in groups.values():
        members.sort(key=lambda c: c["design"])
        lead = members[0]
        if lead["suite"] == "forgehls":
            fam = "forgehls/" + family_name(lead["name"])
        else:
            fam = f"vitislib/{lead['library']}/{variant_stem(lead['component'])}"
        for c in members:
            c["family"] = fam
    # family names must be unique per group
    seen = {}
    for root, members in groups.items():
        fam = members[0]["family"]
        if fam in seen and seen[fam] != root:
            fam2 = fam + "~" + members[0]["design"]
            for c in members:
                c["family"] = fam2
        else:
            seen[fam] = root


# ------------------------------------------------------------------------------------------ main
def write(path: str, text: str):
    """Write text to path only if its content changes, atomically (a temporary file in the same directory,
    then os.replace): a reader never sees a partial file, and an unchanged file keeps its timestamp."""
    data = text.encode("utf-8")
    try:
        if Path(path).read_bytes() == data:
            return
    except OSError:
        pass
    fd, tmp = tempfile.mkstemp(prefix=posixpath.basename(path) + ".", suffix=".tmp", dir=posixpath.dirname(path))
    try:
        with os.fdopen(fd, "wb") as fh:
            fh.write(data)
        os.chmod(tmp, 0o644)
        os.replace(tmp, path)
    except BaseException:
        if os.path.exists(tmp):
            os.unlink(tmp)
        raise


def sync_copy(src: str, dst: str):
    """Copy the file src to dst unless dst already has the same bytes."""
    try:
        if Path(dst).read_bytes() == Path(src).read_bytes():
            return
    except OSError:
        pass
    shutil.copyfile(src, dst)


def git_head(d: str) -> str:
    r = subprocess.run(["git", "-C", d, "-c", "core.hooksPath=/dev/null", "rev-parse", "HEAD"],
                       capture_output=True, text=True)
    return r.stdout.strip()


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=DEFAULT_ROOT)
    ap.add_argument("--dry-run", action="store_true", help="classify only; write nothing")
    a = ap.parse_args(argv)
    root = a.root.rstrip("/")
    src, cat = posixpath.join(root, "src"), posixpath.join(root, "catalog")
    FH_PROVENANCE["repository_commit"] = git_head(posixpath.join(src, "forgehls"))
    vl_commit = git_head(posixpath.join(src, "vitis_libraries"))
    VL_PROVENANCE["repository_commit"] = vl_commit
    print("loading the training set ...", flush=True)
    tr = load_training()
    print(f"training: {len(tr.exact)} distinct normalised files, {len(tr.files)} shingled, "
          f"{len(tr.names)} names", flush=True)
    fh = forgehls_candidates(src, tr)
    vl = vitislib_candidates(src, tr)
    # held-out internal duplicates: a ForgeHLS kernel whose main source equals an earlier kept one
    seen = {}
    for c in fh:
        if c["status"] != "kept":
            continue
        h = hashlib.sha256(norm_source(read_text(posixpath.join(c["origin_dir"], c["sources"][0]))).encode()).hexdigest()
        if h in seen:
            c["status"] = "excluded"
            c["reasons"].append(f"same normalised main source as held-out design {seen[h]}")
        else:
            seen[h] = c["design"]
    kept = [c for c in fh + vl if c["status"] == "kept"]
    assign_families(kept)
    names = defaultdict(list)
    for c in kept:
        names[(c["dataset"], c["design"])].append(c)
    clash = [k for k, v in names.items() if len(v) > 1]
    if clash:
        print(f"design name clashes: {clash[:5]}", file=sys.stderr)
        return 1
    if not a.dry_run:
        # in place: only the directories of designs that are no longer kept are removed
        keep = {(c["dataset"], c["design"]) for c in kept}
        for ds in (FH_DATASET, VL_DATASET):
            d = posixpath.join(cat, ds)
            os.makedirs(d, exist_ok=True)
            for name in sorted(os.listdir(d)):
                if (ds, name) not in keep and os.path.isfile(posixpath.join(d, name, "hlsfactory.toml")):
                    print(f"removing {ds}/{name} (no longer kept)")
                    shutil.rmtree(posixpath.join(d, name))
        for c in kept:
            if c["suite"] == "forgehls":
                write_forgehls(c, posixpath.join(cat, FH_DATASET), FH_PROVENANCE["repository_commit"])
            else:
                write_vitislib(c, posixpath.join(cat, VL_DATASET), vl_commit, posixpath.join(src, "vitis_libraries"))
    manifest = {"generator": "circt tools/hls-est-validate/heldout/build_heldout.py",
                "root": root, "ground_truth_config": {"part": PART, "clock_ns": float(CLOCK_NS),
                                                       "flow_target": FLOW_TARGET, "throughput_driven": "off"},
                "dedupe": {"training_trees": TRAIN_TREES, "training_units": "files and directories",
                           "near_containment": NEAR_CONTAINMENT, "reverse_containment": REVERSE_CONTAINMENT,
                           "family_containment": FAMILY_CONTAINMENT, "hash": "blake2b-64",
                           "shingle_tokens": SHINGLE, "min_shingles": MIN_SHINGLES,
                           "forgehls_name_dedupe": True, "vitislib_name_dedupe": False},
                "suites": {FH_DATASET: FH_PROVENANCE, VL_DATASET: VL_PROVENANCE},
                "designs": []}
    for c in fh + vl:
        e = {k: c.get(k) for k in ("dataset", "design", "suite", "status", "reasons", "family", "origin_rel",
                                   "top", "orig_part", "orig_clock", "source_group", "library", "component",
                                   "configs", "missing_includes")
             if c.get(k) is not None}
        if c.get("dup") and (c["dup"]["exact"] or c["dup"]["near"] or c["dup"].get("reverse") or c["dup"]["names"]):
            e["dup"] = c["dup"]
        if c.get("similar_info"):
            e["similar_info"] = c["similar_info"]
        manifest["designs"].append(e)
    if not a.dry_run:
        write(posixpath.join(cat, "manifest.json"), json.dumps(manifest, indent=1) + "\n")
        # the committed summary: provenance and every excluded candidate with its reason
        excl = {"generator": manifest["generator"], "from": posixpath.join(cat, "manifest.json"),
                "suites": manifest["suites"], "dedupe": manifest["dedupe"],
                "counts": {ds: {"candidates": len(lst),
                                "kept": sum(1 for c in lst if c["status"] == "kept")}
                           for ds, lst in ((FH_DATASET, fh), (VL_DATASET, vl))},
                "excluded": [{"key": f"{c['dataset']}/{c['design']}", "origin": c["origin_rel"],
                              "reasons": c["reasons"]} for c in fh + vl if c["status"] != "kept"]}
        write(str(HERE / "exclusions.json"), json.dumps(excl, indent=1) + "\n")
    for ds, lst in ((FH_DATASET, fh), (VL_DATASET, vl)):
        n_kept = sum(1 for c in lst if c["status"] == "kept")
        why = defaultdict(int)
        for c in lst:
            if c["status"] != "kept":
                why[c["reasons"][0].split(":")[0].split("(")[0].strip()] += 1
        fams = len({c["family"] for c in lst if c["status"] == "kept"})
        print(f"{ds}: candidates {len(lst)}, kept {n_kept}, families {fams}, excluded {len(lst) - n_kept}: "
              + ", ".join(f"{k} {v}" for k, v in sorted(why.items(), key=lambda kv: -kv[1])))
    return 0


if __name__ == "__main__":
    sys.exit(main())
