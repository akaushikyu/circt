"""Naive baseline estimators for the thesis evaluation (chapter 6, "What does a naive model score?").

An examiner's first question about an accuracy number is what a model *without* the inferred decisions
would score on the same designs.  This module prices every design from the very MLIR the evaluated run
used (the `mlir` field of each record of the run file), with no loop, partition, replication, schedule or
dead-code decision at all:

  B0  every local or global array (a `memref.alloca` / `memref.alloc` / `memref.global` with at least two
      elements) of the functions reachable from the top function is one memory of its declared depth and
      element width, priced once (no per-call instances) by the 7-series RAMB18 formula with two ports
      (`formula_reconcile.open_old_bram_impl_num`, the transcription of the open resource formula, N8) in
      true-dual-port mode, i.e. never the x36 aspect;
  B1  B0 plus the storage threshold of VITIS_NOTES N5: an array of fewer than 1024 bits is LUT RAM and
      costs no BRAM.

Top-level array arguments are interface ports and cost nothing in either baseline, as in hls-est.  Element
types the parser does not understand (LLVM structs, opaque types) are skipped and counted.  The parser is a
line-level reading of cgeist's MLIR, not an MLIR parser; it is a baseline, not a model.

The result is cached in $SCRATCH/thesis/cache, keyed by the run file's path, size and mtime.
"""
import hashlib
import json
import re
import sys
from pathlib import Path

import thesis_data as T

sys.path.insert(0, str(T.VALIDATE))
from formula_reconcile import LUTRAM_BITS, open_old_bram_impl_num  # noqa: E402
from run_hlsest import find_top  # noqa: E402  (the harness's own resolution of the top function)

FUNC = re.compile(r"^  func\.func (?:private |public )?@([\w$.]+)\(", re.M)
CALL = re.compile(r"(?:func\.call|\bcall|llvm\.call) @([\w$.]+)\(")
ALLOC = re.compile(r"memref\.alloca?\(\)[^\n]*?: memref<([^>]*(?:<[^>]*>[^>]*)*)>")
GLOBAL = re.compile(r"^  memref\.global (?:\"\w+\" )?(?:constant )?@([\w$.]+) : memref<([^>]*(?:<[^>]*>[^>]*)*)>", re.M)
GET_GLOBAL = re.compile(r"memref\.get_global @([\w$.]+)")


def element_bits(t):
    t = t.strip()
    m = re.fullmatch(r"[iu]i?(\d+)|si(\d+)", t)
    if m:
        return int(m.group(1) or m.group(2))
    widths = {"f16": 16, "bf16": 16, "f32": 32, "f64": 64, "index": 64}
    if t in widths:
        return widths[t]
    m = re.fullmatch(r"complex<(\w+)>", t)
    if m and m.group(1) in widths:
        return 2 * widths[m.group(1)]
    m = re.fullmatch(r"vector<([\dx]+)x(\w+)>", t)
    if m and element_bits(m.group(2)):
        n = 1
        for d in m.group(1).split("x"):
            n *= int(d)
        return n * element_bits(m.group(2))
    return None


def shape_of(spec):
    """(words, bits) of a memref type body such as '64x64xf32', or None (dynamic or unknown element)."""
    spec = spec.split(",")[0].strip()          # drop a layout / memory space
    parts = re.split(r"x(?![^<]*>)", spec)
    dims, elem = parts[:-1], parts[-1]
    if any(not d.isdigit() for d in dims):
        return None
    words = 1
    for d in dims:
        words *= int(d)
    bits = element_bits(elem)
    return (words, bits) if bits else None


def functions(text):
    """{name: body text} of the module's functions."""
    marks = [(m.start(), m.group(1)) for m in FUNC.finditer(text)]
    out = {}
    for i, (pos, name) in enumerate(marks):
        end = marks[i + 1][0] if i + 1 < len(marks) else len(text)
        out[name] = text[pos:end]
    return out


def price(words, bits, lutram):
    if lutram and words * bits < LUTRAM_BITS:
        return 0
    return open_old_bram_impl_num(bits, words, sdp=False)


def design_baseline(path, top):
    text = Path(path).read_text(errors="replace")
    funcs = functions(text)
    top, _how = find_top(path, top)
    if top not in funcs:
        return None
    seen, todo = set(), [top]
    while todo:
        f = todo.pop()
        if f in seen or f not in funcs:
            continue
        seen.add(f)
        todo += CALL.findall(funcs[f])
    arrays, skipped, used_globals = [], 0, set()
    for f in seen:
        body = funcs[f]
        used_globals |= set(GET_GLOBAL.findall(body))
        for spec in ALLOC.findall(body):
            s = shape_of(spec)
            if s is None:
                skipped += 1
            elif s[0] >= 2:
                arrays.append(s)
    for name, spec in GLOBAL.findall(text):
        if name in used_globals:
            s = shape_of(spec)
            if s is None:
                skipped += 1
            elif s[0] >= 2:
                arrays.append(s)
    return {"b0": sum(price(w, b, False) for w, b in arrays), "b1": sum(price(w, b, True) for w, b in arrays),
            "arrays": len(arrays), "skipped": skipped}


def baselines(run_path, runs):
    """{design key: {"b0", "b1", "arrays", "skipped"}} for every design of the run with MLIR and a top."""
    p = T.expand(run_path)
    st = p.stat()
    tag = hashlib.sha1(f"{p}|{st.st_size}|{st.st_mtime_ns}|baseline-v2".encode()).hexdigest()[:16]
    cache = T.CACHE / f"{p.stem}.{tag}.baseline.json"
    if cache.exists():
        return json.loads(cache.read_text())
    out = {}
    for key, r in runs.items():
        if r.get("mlir") and r.get("top") and Path(r["mlir"]).exists():
            b = design_baseline(r["mlir"], r["top"])
            if b is not None:
                out[key] = b
    T.CACHE.mkdir(parents=True, exist_ok=True)
    cache.write_text(json.dumps(out))
    return out
