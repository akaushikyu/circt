#!/usr/bin/env python3
"""Build the SECOND held-out evaluation catalogue for hls-est (hls-doc/heldout2.md).

    python3 -I build_heldout2.py [--root /mnt/d/HLS_heldout2] [--dry-run] [-j 12]

Inputs under <root>/src (provenance in <root>/provenance/README.txt):
  hls4ml_gen/      hls4ml Vitis projects written by gen_hls4ml.py (its manifest.json)
  finn_gen/        FINN-hlslib unit-test designs written by gen_finn.py (its manifest.json)
  finn-hlslib/     Xilinx/finn-hlslib (the library headers the FINN designs include, in place)
  rodinia-hls/     SFU-HiAccel/rodinia-hls (kernels referenced in place)

Output (the first set's machinery, heldout/build_heldout.py, reused):
  catalog/heldout2-hls4ml/<design>/    a copy of the hls4ml project + hlsfactory.toml + dataset_hls.tcl
  catalog/heldout2-finn/<design>/      a copy of the test's files + dataset_hls.tcl (-I <finn-hlslib>) +
                                       heldout_includes.txt (cache-key witness of the library tree)
  catalog/heldout2-rodinia/<design>/   dataset_hls.tcl naming the kernel in src/rodinia-hls by absolute path +
                                       heldout_sources.txt / heldout_includes.txt (cache-key witnesses)
  catalog/manifest.json                every candidate: kept / excluded with the reason, family, provenance
  tools/hls-est-validate/heldout2/exclusions.json   the committed summary of every exclusion

Every dataset_hls.tcl is normalised to the ground-truth configuration exactly as for the first set
(xc7z020clg400-1, 10 ns, flow_target vivado, config_array_partition -throughput_driven off); the suite's own
part, clock and config_* lines are dropped and kept as comments / toml tags; source pragmas are untouched.

Training-set deduplication (heldout.md's rules, binding): the training units are those of the first set
(HLSFactory_v2 tree, Polygeist tools/cgeist/Test/HLS, circt test/hls-est, ~/hls-est-work/exp-src) plus the whole
first held-out set (/mnt/d/HLS_heldout/src: its eval and locked splits have both been looked at).  A design is
excluded when a design source is an exact (normalised) copy of a training file, holds >= 80 % of its 5-token
shingles in one training unit, or holds >= 60 % of one training unit's shingles.  Name collisions with training
designs are listed, not excluded (none of the three suites derives from a training suite).  A design whose files
(sources and local headers, with its top) are identical to an earlier kept one is an internal duplicate.

Validity: every kept design's sources are parsed with g++ -fsyntax-only -std=c++14 against the real Vitis
headers (/mnt/a/Vitis/2025.1/Vitis/include; __SYNTHESIS__ not defined); a design g++ rejects is excluded as not
valid C++.  Results are cached by command and content (~/hls-est-work/heldout2/gxx_cache.json).  No cgeist,
hls-est or Vitis run.

Families (the split's unit): the generator's family (hls4ml: the model architecture; FINN: the library function
the test exercises; Rodinia: the application, every optimisation step and sub-kernel of it), joined with the
content rule of the first set (sources + local code headers near-duplicates in either direction, >= 80 %, every
preprocessor line removed; weight / data headers, which hold numbers only, are left out of the fingerprint).  For
the generated hls4ml projects the content rule needs containment in both directions (MUTUAL_CONTENT_DATASETS),
and near-twin architectures are joined (twin_architectures: >= 70 % of each architecture's generated code in the
other, or one design >= 90 % contained in a design of the other architecture).
"""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import posixpath
import re
import subprocess
import sys
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
HARNESS = HERE.parent
sys.path.insert(0, str(HARNESS))
sys.path.insert(0, str(HARNESS / "heldout"))
import hlsfactory_v2 as V2                    # noqa: E402  (harness module)
import build_heldout as B                     # noqa: E402  (the first set's builder: dedupe, families, writers)

DEFAULT_ROOT = "/mnt/d/HLS_heldout2"
HLS4ML_DS, FINN_DS, RODINIA_DS = "heldout2-hls4ml", "heldout2-finn", "heldout2-rodinia"
FIRST_HELDOUT_SRC = "/mnt/d/HLS_heldout/src"
TRAIN_TREES = B.TRAIN_TREES + [FIRST_HELDOUT_SRC]
VITIS_INCLUDE = "/mnt/a/Vitis/2025.1/Vitis/include"
GXX = ["g++", "-std=c++14", "-fsyntax-only", "-w"]
GXX_TIMEOUT = 600
GXX_CACHE = Path.home() / "hls-est-work" / "heldout2" / "gxx_cache.json"
GENERATOR = "circt tools/hls-est-validate/heldout2/build_heldout2.py"
CODE_EXT = (".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx")
# Generated code (hls4ml): every project shares hls4ml's boilerplate, so the one-way containment test would put
# each small network inside every larger one (the 37 architectures collapse into 5 families).  There the content
# rule joins two designs only when each holds >= 80 % of the other's shingles (the same layer sequence with other
# sizes, e.g. a GRU and an LSTM model, or conv2d_avg and conv2d_leaky).
MUTUAL_CONTENT_DATASETS = {HLS4ML_DS}
# Near-twin architectures (review of circt 54295ecc2): two architectures are one family when each holds >= 70 % of
# the other's generated-code shingles (all designs of an architecture together), or when one design of one holds
# >= 90 % of its shingles in one design of the other (dense2_relu in dense2_relu_softmax, 96 %).  The review's
# one-way 80 % closure would join 32 of the 36 architectures into one family (a 75 / 465 split), so it is not used;
# the cross-split one-way 80-90 % pairs that remain are listed in hls-doc/heldout2.md.
TWIN_ARCH_MUTUAL = 0.70
TWIN_DESIGN_ONEWAY = 0.90
NUMBERS_ONLY = re.compile(r"(^|/)(weights/|memdata)")      # weight / data headers: left out of the family fingerprint

PROVENANCE = {
    HLS4ML_DS: {"suite": "hls4ml-generated projects", "repository": "https://github.com/fastmachinelearning/hls4ml",
                "licence": "Apache-2.0 (LICENSE; the Vitis backend templates and nnet_utils headers hls4ml writes "
                           "into each project)", "spdx": "Apache-2.0",
                "generator": "circt tools/hls-est-validate/heldout2/gen_hls4ml.py (PyTorch front end)"},
    FINN_DS: {"suite": "FINN-hlslib unit tests", "repository": "https://github.com/Xilinx/finn-hlslib",
              "licence": "BSD-3-Clause (LICENSE, Copyright (c) 2019, Xilinx, Inc.)", "spdx": "BSD-3-Clause",
              "generator": "circt tools/hls-est-validate/heldout2/gen_finn.py (variant configuration / weight "
                           "headers written by the generator)"},
    RODINIA_DS: {"suite": "Rodinia-HLS", "repository": "https://github.com/SFU-HiAccel/rodinia-hls",
                 "licence": "BSD-2-Clause (LICENSE, Copyright (c) 2020, SFU-HiAccel)", "spdx": "BSD-2-Clause"},
}

_PART = re.compile(r"^\s*set_part\s+\{?([^\s}]+)", re.M)
_CLOCK = re.compile(r"create_clock\s+-period\s+(\S+)")
_CONFIG = re.compile(r"^\s*(?:catch\s*\{\s*)?(config_\w+[^}\n]*)", re.M)


def git_head(d: str) -> str:
    return B.git_head(d)


def code_files(d: str, skip_dirs=()) -> list[str]:
    out = []
    for dp, dn, fn in os.walk(d):
        dn[:] = sorted(x for x in dn if posixpath.relpath(posixpath.join(dp, x), d) not in skip_dirs)
        out += [posixpath.join(dp, f) for f in sorted(fn) if f.lower().endswith(CODE_EXT)]
    return out


# ------------------------------------------------------------------------------------------ candidates
def hls4ml_candidates(src: str) -> list[dict]:
    gen = posixpath.join(src, "hls4ml_gen")
    man = json.loads(Path(gen, "manifest.json").read_text(encoding="utf-8"))
    PROVENANCE[HLS4ML_DS].update(hls4ml_version=man["hls4ml_version"], torch_version=man["torch_version"],
                                 generator_seed=man["seed"])
    out = []
    for r in man["designs"]:
        d = posixpath.join(gen, r["design"])
        c = {"suite": "hls4ml", "dataset": HLS4ML_DS, "design": V2._safe_name(r["design"]), "name": r["design"],
             "origin_rel": f"hls4ml_gen/{r['design']}", "origin_dir": d, "copy": True, "top": "myproject",
             "hint": r["family"], "status": "kept", "reasons": [], "includes_abs": [], "defines": [],
             "cflags": "-std=c++0x",
             "variant": {k: r.get(k) for k in ("arch", "precision", "reuse_factor", "io_type", "strategy")}}
        out.append(c)
        if r["status"] != "ok":
            c["status"], c["reasons"] = "excluded", [f"hls4ml conversion failed: {r.get('error', '')[:200]}"]
            continue
        c["sources"] = ["firmware/myproject.cpp"]
        c["headers"] = [f for f in code_files(posixpath.join(d, "firmware"), skip_dirs=("nnet_utils",))
                        if not f.endswith(".cpp")]
        tcl = B.read_text(posixpath.join(d, "build_prj.tcl")) + B.read_text(posixpath.join(d, "project.tcl"))
        part = re.search(r'set part "([^"]+)"', tcl)
        clock = re.search(r'set clock_period (\S+)', tcl)
        unc = re.search(r'set clock_uncertainty (\S+)', tcl)
        c.update(orig_part=part and part.group(1), orig_clock=clock and clock.group(1),
                 dropped={"clock_uncertainty": unc and unc.group(1),
                          **{f"config[{i}]": x.strip() for i, x in enumerate(_CONFIG.findall(tcl))}})
    return out


def finn_candidates(src: str) -> list[dict]:
    gen = posixpath.join(src, "finn_gen")
    man = json.loads(Path(gen, "manifest.json").read_text(encoding="utf-8"))
    finn = posixpath.join(src, "finn-hlslib")
    PROVENANCE[FINN_DS].update(repository_commit=man["finn_hlslib_commit"], generator_seed=man["seed"])
    out = []
    for r in man["designs"]:
        d = posixpath.join(gen, r["design"])
        c = {"suite": "finn", "dataset": FINN_DS, "design": V2._safe_name(r["design"]), "name": r["design"],
             "origin_rel": f"finn_gen/{r['design']} (finn-hlslib {r['tcl']})", "origin_dir": d, "copy": True,
             "top": r.get("top"), "hint": r["family"], "status": "kept", "reasons": [],
             "variant": {"test": r["test"], "variant": r.get("variant"), "generated": r.get("generated")}}
        out.append(c)
        if r["status"] != "ok":
            c["status"], c["reasons"] = "excluded", [r["error"]]
            continue
        tcl = B.read_text(posixpath.join(finn, r["tcl"]))
        part, clock = _PART.search(tcl), _CLOCK.search(tcl)
        defs = [f"{k}={v}" for k, v in r["defines"].items()]
        c.update(sources=list(r["sources"]),
                 headers=[posixpath.join(d, f) for f in r["files"] if f not in r["sources"]],
                 includes_abs=[finn], defines=defs,
                 cflags=" ".join(["-std=c++14", f"-I{finn}"] + [f"-D{x}" for x in defs]),
                 orig_part=part and part.group(1), orig_clock=clock and clock.group(1),
                 dropped={f"config[{i}]": x.strip() for i, x in enumerate(_CONFIG.findall(tcl))})
    return out


def rodinia_app_name(m_dir: str) -> str | None:
    """APP of a rodinia-hls kernel directory: its Makefile's APP=, else the APP= of the common.mk of an
    enclosing directory (the kernel is src/$(APP).cpp, the top is $(KERNAL_NAME) = workload)."""
    d = m_dir
    for _ in range(4):
        for f in ("Makefile", "common.mk"):
            p = posixpath.join(d, f)
            if os.path.isfile(p):
                m = re.search(r"^APP\s*[:?]?=\s*(\S+)", B.read_text(p), re.M)
                if m:
                    return m.group(1)
        d = posixpath.dirname(d)
    return None


def rodinia_candidates(src: str) -> list[dict]:
    root = posixpath.join(src, "rodinia-hls")
    bench = posixpath.join(root, "Benchmarks")
    PROVENANCE[RODINIA_DS]["repository_commit"] = git_head(root)
    out = []
    for dp, dn, fn in os.walk(bench):
        dn.sort()
        if "Makefile" not in fn or posixpath.relpath(dp, bench).split("/")[0] == "common":
            continue
        rel = posixpath.relpath(dp, bench)
        app = rodinia_app_name(dp)
        top_m = re.search(r"^KERNAL_NAME\s*[:?]?=\s*(\S+)", B.read_text(posixpath.join(dp, "Makefile")), re.M)
        kernel = posixpath.join(dp, "src", f"{app}.cpp") if app else None
        appdir = posixpath.join(bench, rel.split("/")[0])
        c = {"suite": "rodinia", "dataset": RODINIA_DS, "design": V2._safe_name(rel.replace("/", "__")),
             "name": rel.split("/")[-1], "origin_rel": f"Benchmarks/{rel}", "origin_dir": posixpath.join(dp, "src"),
             "copy": False, "top": top_m.group(1) if top_m else "workload",
             "hint": rel.split("/")[0].lower(), "status": "kept", "reasons": [],
             "orig_part": "xilinx_u200_xdma_201830_2 (README: Alveo U200, v++ kernel flow)",
             "orig_clock": "v++ default kernel clock of the platform", "dropped": {}}
        out.append(c)
        if not kernel or not os.path.isfile(kernel):
            c["status"], c["reasons"] = "excluded", [f"no kernel source src/{app}.cpp"]
            continue
        incs = [posixpath.join(dp, "src"), posixpath.join(bench, "common")]
        if os.path.isdir(posixpath.join(appdir, "common")):
            incs.append(posixpath.join(appdir, "common"))
        c.update(sources=[kernel], headers=B.local_headers(posixpath.join(dp, "src")), includes_abs=incs,
                 defines=[], cflags=" ".join(["-std=c++14"] + [f"-I{i}" for i in incs]))
    return out


# ------------------------------------------------------------------------------------------ checks
def abs_sources(c: dict) -> list[str]:
    return [s if posixpath.isabs(s) else posixpath.join(c["origin_dir"], s) for s in c["sources"]]


def internal_duplicates(cands: list[dict]):
    seen = {}
    for c in cands:
        if c["status"] != "kept":
            continue
        h = hashlib.sha256((c["top"] + "\0" + " ".join(c.get("defines", []))).encode())
        for f in abs_sources(c) + c["headers"]:
            h.update(B.norm_source(B.read_text(f)).encode() + b"\0")
        key = (c["dataset"], h.hexdigest())
        if key in seen:
            c["status"] = "excluded"
            c["reasons"].insert(0, f"same top, -D flags and normalised sources and headers as held-out design "
                                   f"{seen[key]}")
        else:
            seen[key] = c["design"]


def gxx_cmd(c: dict, source: str) -> list[str]:
    return (GXX + [f"-I{VITIS_INCLUDE}"] + [f"-I{i}" for i in c.get("includes_abs", [])]
            + [f"-D{x}" for x in c.get("defines", [])] + [source])


def gxx_key(c: dict) -> str:
    h = hashlib.sha256()
    for s in abs_sources(c):
        h.update(" ".join(gxx_cmd(c, s)).encode() + b"\0")
    for f in sorted(set(code_files(c["origin_dir"]) + abs_sources(c) + c["headers"])):
        h.update(f.encode() + b"\0" + Path(f).read_bytes() + b"\0")
    for d in c.get("includes_abs", []):
        h.update(B.tree_digest(d)[0].encode())
    return h.hexdigest()


def gxx_check(c: dict) -> tuple[bool, str]:
    for s in abs_sources(c):
        try:
            r = subprocess.run(gxx_cmd(c, s), capture_output=True, text=True, timeout=GXX_TIMEOUT,
                               cwd=posixpath.dirname(s))
        except subprocess.TimeoutExpired:
            return False, f"g++ -fsyntax-only timed out after {GXX_TIMEOUT}s on {posixpath.basename(s)}"
        if r.returncode != 0:
            err = next((l for l in r.stderr.splitlines() if "error" in l), r.stderr.strip()[:200])
            return False, f"{posixpath.basename(s)}: {err.strip()[:300]}"
    return True, ""


def validity(cands: list[dict], jobs: int):
    cache = json.loads(GXX_CACHE.read_text()) if GXX_CACHE.is_file() else {}
    todo = [c for c in cands if c["status"] == "kept"]
    keys = {c["design"] + c["dataset"]: gxx_key(c) for c in todo}
    run = [c for c in todo if keys[c["design"] + c["dataset"]] not in cache]
    print(f"g++ -fsyntax-only: {len(todo)} designs, {len(run)} not cached", flush=True)
    with ThreadPoolExecutor(jobs) as ex:
        for c, res in zip(run, ex.map(gxx_check, run)):
            cache[keys[c["design"] + c["dataset"]]] = list(res)
    GXX_CACHE.parent.mkdir(parents=True, exist_ok=True)
    GXX_CACHE.write_text(json.dumps(cache, indent=0, sort_keys=True) + "\n")
    for c in todo:
        ok, why = cache[keys[c["design"] + c["dataset"]]]
        if not ok:
            c["status"] = "excluded"
            c["reasons"].insert(0, f"not valid C++ (g++ -fsyntax-only -std=c++14 with the Vitis 2025.1 headers): {why}")


# ------------------------------------------------------------------------------------------ families
def family_files(c: dict) -> list[str]:
    return [f for f in abs_sources(c) + c["headers"]
            if not NUMBERS_ONLY.search(posixpath.relpath(f, c["origin_dir"]))]


def twin_architectures(cands: list[dict], fps: dict) -> list[tuple]:
    """Union keys ('hint', dataset, architecture) of near-twin architectures (TWIN_ARCH_MUTUAL, TWIN_DESIGN_ONEWAY)
    within each dataset of `cands`; fps[dataset][('d', dataset, design)] are the family fingerprints."""
    out = []
    by_ds = defaultdict(list)
    for c in cands:
        by_ds[c["dataset"]].append(c)
    for ds, lst in sorted(by_ds.items()):
        arch: dict[str, set] = defaultdict(set)
        for c in lst:
            arch[c["hint"]] |= fps[ds][("d", ds, c["design"])]
        names = sorted(arch)
        for i, a in enumerate(names):
            for b in names[i + 1:]:
                inter = len(arch[a] & arch[b])
                if arch[a] and arch[b] and min(inter / len(arch[a]), inter / len(arch[b])) >= TWIN_ARCH_MUTUAL:
                    out.append((("hint", ds, a), ("hint", ds, b)))
        sub = {("d", ds, c["design"]): fps[ds][("d", ds, c["design"])] for c in lst}
        hint = {("d", ds, c["design"]): c["hint"] for c in lst}
        for x, y in B.content_pairs(sub, TWIN_DESIGN_ONEWAY):
            if hint[x] != hint[y]:
                out.append((("hint", ds, hint[x]), ("hint", ds, hint[y])))
    return out


def assign_families(kept: list[dict]):
    uf = B.UF()
    fps: dict[str, dict] = defaultdict(dict)
    for c in kept:
        me = ("d", c["dataset"], c["design"])
        uf.union(me, ("hint", c["dataset"], c["hint"]))
        fp: set[int] = set()
        for f in family_files(c):
            fp |= B.family_shingles(B.read_text(f))
        fps[c["dataset"]][me] = fp
    for a, b in twin_architectures([c for c in kept if c["dataset"] in MUTUAL_CONTENT_DATASETS], fps):
        uf.union(a, b)
    for ds in sorted(fps):
        pairs = B.content_pairs(fps[ds], B.FAMILY_CONTAINMENT)
        if ds in MUTUAL_CONTENT_DATASETS:
            both = set(pairs)
            pairs = [(a, b) for a, b in pairs if (b, a) in both or len(fps[ds][a]) < B.MIN_SHINGLES]
        for a, b in pairs:
            uf.union(a, b)
    groups = defaultdict(list)
    for c in kept:
        groups[uf.find(("d", c["dataset"], c["design"]))].append(c)
    seen = {}
    for root, members in sorted(groups.items(), key=lambda kv: min(c["design"] for c in kv[1])):
        members.sort(key=lambda c: c["design"])
        fam = f"{members[0]['suite']}/{members[0]['hint']}"
        if fam in seen:
            fam += "~" + members[0]["design"]
        seen[fam] = root
        for c in members:
            c["family"] = fam
        merged = sorted({c["hint"] for c in members})
        if len(merged) > 1:
            for c in members:
                c["family_note"] = "content-joined generator families: " + ", ".join(merged)


# ------------------------------------------------------------------------------------------ writing
def write_design(c: dict, cat: str):
    ddir = posixpath.join(cat, c["dataset"], c["design"])
    os.makedirs(ddir, exist_ok=True)
    if c["copy"]:
        for dp, dn, fn in os.walk(c["origin_dir"]):
            dn.sort()
            rel = posixpath.relpath(dp, c["origin_dir"])
            os.makedirs(posixpath.normpath(posixpath.join(ddir, rel)), exist_ok=True)
            for f in sorted(fn):
                B.sync_copy(posixpath.join(dp, f), posixpath.normpath(posixpath.join(ddir, rel, f)))
        files = c["sources"]
    else:
        files = abs_sources(c)
    prov = PROVENANCE[c["dataset"]]
    origin = f"{prov['repository']} @ {prov.get('repository_commit') or prov.get('hls4ml_version')} {c['origin_rel']}"
    dropped = {"part": c.get("orig_part"), "clock": c.get("orig_clock"), **(c.get("dropped") or {})}
    tcl = B.normalised_tcl(origin, c["top"], files, c["cflags"], dropped)
    tcl = tcl.replace("generated by circt tools/hls-est-validate/heldout/build_heldout.py",
                      "generated by " + GENERATOR, 1)
    B.write(posixpath.join(ddir, "dataset_hls.tcl"), tcl.replace("# Held-out design:", "# Held-out design (heldout2):", 1))
    if not c["copy"]:
        lines = [f"# {prov['repository']} {prov.get('repository_commit')}: sha256 of the files this design names "
                 "(cache-key witness)"]
        for p in abs_sources(c) + [h for h in c["headers"] if h not in abs_sources(c)]:
            lines.append(f"{B.sha256_file(p)}  {p}")
        B.write(posixpath.join(ddir, "heldout_sources.txt"), "\n".join(lines) + "\n")
    if c.get("includes_abs"):
        inc = ["# sha256 over the C/C++ files under each -I directory (path and content; cache-key witness)"]
        for d in c["includes_abs"]:
            h, n = B.tree_digest(d)
            inc.append(f"{h}  {d}/  ({n} files)")
        B.write(posixpath.join(ddir, "heldout_includes.txt"), "\n".join(inc) + "\n")
    tags = ["heldout2", f"suite:{c['suite']}", f"family:{c['family']}", f"origin:{c['origin_rel']}",
            f"original_part:{c.get('orig_part')}", f"original_clock:{c.get('orig_clock')}"]
    tags += [f"dropped_config:{v}" for k, v in (c.get("dropped") or {}).items() if k.startswith("config[")]
    tags += [f"{k}:{v}" for k, v in (c.get("variant") or {}).items() if v not in (None, [], "")]
    how = ("files copied from the generated project" if c["copy"] else
           "sources referenced in place in src/, each keeping its own licence header")
    B.write(posixpath.join(ddir, "hlsfactory.toml"),
            B.toml_text(c["design"], c["dataset"], tags,
                        ["Second held-out evaluation design (hls-doc/heldout2.md); generated by build_heldout2.py.",
                         f"Source: {prov['suite']} {c['origin_rel']} (licence: {prov['spdx']}); {how}.",
                         "Synthesis configuration normalised (dataset_hls.tcl)."]))


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--root", default=DEFAULT_ROOT)
    ap.add_argument("--dry-run", action="store_true", help="classify only; write nothing")
    ap.add_argument("-j", type=int, default=12, help="parallel g++ syntax checks")
    a = ap.parse_args(argv)
    root = a.root.rstrip("/")
    src, cat = posixpath.join(root, "src"), posixpath.join(root, "catalog")
    B.TRAIN_TREES[:] = TRAIN_TREES               # B.load_training reads its module list
    print("loading the training set (first set's training trees + the first held-out set) ...", flush=True)
    tr = B.load_training()
    print(f"training: {len(tr.exact)} distinct normalised files, {len(tr.files)} shingled units, "
          f"{len(tr.names)} names", flush=True)
    suites = [(HLS4ML_DS, hls4ml_candidates(src)), (FINN_DS, finn_candidates(src)),
              (RODINIA_DS, rodinia_candidates(src))]
    cands = [c for _, lst in suites for c in lst]
    for c in cands:
        if c["status"] == "kept":
            B.dedupe(c, abs_sources(c) + [h for h in c["headers"] if h not in abs_sources(c)], tr,
                     names=[c["name"], c["top"]] + [posixpath.splitext(posixpath.basename(s))[0] for s in c["sources"]],
                     names_exclude=False)
    internal_duplicates(cands)
    validity(cands, a.j)
    kept = [c for c in cands if c["status"] == "kept"]
    assign_families(kept)
    names = defaultdict(int)
    for c in kept:
        names[(c["dataset"], c["design"])] += 1
    if any(n > 1 for n in names.values()):
        print("design name clashes", file=sys.stderr)
        return 1
    if not a.dry_run:
        keep = {(c["dataset"], c["design"]) for c in kept}
        for ds, _ in suites:
            d = posixpath.join(cat, ds)
            os.makedirs(d, exist_ok=True)
            for name in sorted(os.listdir(d)):
                if (ds, name) not in keep and os.path.isfile(posixpath.join(d, name, "hlsfactory.toml")):
                    print(f"removing {ds}/{name} (no longer kept)")
                    B.shutil.rmtree(posixpath.join(d, name))
        for c in kept:
            write_design(c, cat)
    dedupe_rules = {"training_trees": TRAIN_TREES, "training_units": "files and directories",
                    "near_containment": B.NEAR_CONTAINMENT, "reverse_containment": B.REVERSE_CONTAINMENT,
                    "family_containment": B.FAMILY_CONTAINMENT, "hash": "blake2b-64", "shingle_tokens": B.SHINGLE,
                    "min_shingles": B.MIN_SHINGLES, "name_dedupe": False,
                    "validity": " ".join(GXX) + f" -I{VITIS_INCLUDE} (no -D__SYNTHESIS__)"}
    manifest = {"generator": GENERATOR, "root": root,
                "ground_truth_config": {"part": B.PART, "clock_ns": float(B.CLOCK_NS), "flow_target": B.FLOW_TARGET,
                                        "throughput_driven": "off"},
                "dedupe": dedupe_rules, "suites": PROVENANCE, "designs": []}
    for c in cands:
        e = {k: c.get(k) for k in ("dataset", "design", "suite", "status", "reasons", "family", "family_note",
                                   "hint", "origin_rel", "top", "orig_part", "orig_clock", "variant")
             if c.get(k) is not None}
        if c.get("dup") and (c["dup"]["exact"] or c["dup"]["near"] or c["dup"].get("reverse") or c["dup"]["names"]):
            e["dup"] = c["dup"]
        if c.get("similar_info"):
            e["similar_info"] = c["similar_info"]
        manifest["designs"].append(e)
    if not a.dry_run:
        B.write(posixpath.join(cat, "manifest.json"), json.dumps(manifest, indent=1) + "\n")
        excl = {"generator": GENERATOR, "from": posixpath.join(cat, "manifest.json"), "suites": PROVENANCE,
                "dedupe": dedupe_rules,
                "counts": {ds: {"candidates": len(lst), "kept": sum(1 for c in lst if c["status"] == "kept")}
                           for ds, lst in suites},
                "excluded": [{"key": f"{c['dataset']}/{c['design']}", "origin": c["origin_rel"],
                              "reasons": c["reasons"]} for c in cands if c["status"] != "kept"]}
        B.write(str(HERE / "exclusions.json"), json.dumps(excl, indent=1) + "\n")
    for ds, lst in suites:
        n_kept = sum(1 for c in lst if c["status"] == "kept")
        why = defaultdict(int)
        for c in lst:
            if c["status"] != "kept":
                r = next((x for x in c["reasons"] if not x.startswith("note:")), c["reasons"][0])
                why[r.split(":")[0].split("(")[0].strip()] += 1
        fams = len({c["family"] for c in lst if c["status"] == "kept"})
        print(f"{ds}: candidates {len(lst)}, kept {n_kept}, families {fams}, excluded {len(lst) - n_kept}: "
              + ", ".join(f"{k} {v}" for k, v in sorted(why.items(), key=lambda kv: -kv[1])))
    return 0


if __name__ == "__main__":
    sys.exit(main())
