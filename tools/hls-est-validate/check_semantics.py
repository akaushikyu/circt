#!/usr/bin/env python3
"""Differential execution of cgeist's MLIR against the native build of the same C/C++ (W8b).

Peter's definition of done asks for MLIR that is *semantically correct*; this script checks it instead
of assuming it.  For every design of a run_hlsest.py / sweep_hlsfactory_v2.py result file whose cgeist
step produced MLIR:

  candidate  the MLIR file hls-est reads (the record's `mlir`), with a small wrapper function added
             (`cs_entry`: every argument a memref, scalars and the return value in memref<1xT>),
             lowered to LLVM (CIRCT's mlir-opt: lower-affine, scf/cf/arith/math/memref/func to llvm;
             files with polygeist ops through polygeist-opt when that binary exists), translated and
             compiled with llc -O0; the hls::stream methods the shim only declares are generated on
             the driver's token FIFOs (cand_stream_runtime);
  reference  the design's sources compiled natively (see --ref below) with the include directories,
             macros and language standard of the record's cgeist command (first line of its cgeist
             log), AddressSanitizer on.  The source that defines the top is #included into the call
             thunk, the others are compiled as usual.

Both are linked with one generated driver.  It fills every argument buffer (each memref argument with
guard zones before and after it, each scalar argument, the return value) with the same seeded values,
calls the top function --calls times (static state carries over, as in a test bench), and after every
call writes a canonical dump of every buffer: each scalar leaf (struct members, array elements) in
little-endian, masked to its bit width; padding and pointer members are left out.  The dumps are
compared byte for byte (a NaN counts as the one quiet NaN of its format: its sign and payload are
unspecified), for every value mode (`small`: integers 0..7 in arrays, 0..8 as scalars, floats in
[-1, 1); `wide`: integers over their full width in arrays, 0..1023 as scalars, floats in
[-1000, 1000); `pos`: integers 1..8, floats in [0.5, 2), for designs that divide by an input) and every
seed.  A design with no verdict is retried once in an input-domain mode (INPUT_RETRIES: `diag`, `align`,
`index`) and, when its top takes a graph (an edge list and a count), in the `graph-*` modes, which write
valid graphs (GRAPH_INDEX_BITS, graph_retry).

The reference (--ref, default `real`): `real` builds the sources with g++ / gcc against the real Vitis
2025.1 headers (an ext4 mirror of C.VITIS_INCLUDE_WSL) in C-simulation mode, which is Vitis' own C
simulation: no __SYNTHESIS__, ap_int / ap_fixed as ap_private.  Its thunk converts every argument
between the MLIR layout and the native objects (REF_THUNK_REAL).  `shim` builds them with clang 18
against the headers cgeist read (the record's shim), where the layouts agree and no conversion is made.
`real,shim` runs both; the first is the design's status, the other is recorded next to it (a mismatch
under `real` only is a shim-semantics difference, track W11; one under both is a frontend bug).

A run is valid when the reference exits 0 within the timeout and AddressSanitizer reports nothing.  A
design is `equal` when it has a valid run and every valid run matches, `mismatch` when a valid run
differs; then the reference is rebuilt with -ftrivial-auto-var-init=pattern and =zero, at its own -O
and at -O0 (a design whose outputs depend on that reads uninitialised memory: `n/a: reads uninitialised
memory`) and with UBSan (its first report is attached to the record).  Everything else is `n/a: <reason>` (no MLIR, the top has
an argument type the driver cannot fill, the native build does not compile, no valid run, ...).

    python3 check_semantics.py --from <run json> [--datasets a,b] [--benchmarks x,y] [-j 8]
                               [--ref real,shim] [--all-refs] [--seeds 1,2] [--modes small,wide,pos]
                               [--calls 2] [--timeout 120] [--out results/semantics.json] [--work DIR]
                               [--keep] [--top-fn MLIR_NAME] [--md ../../hls-doc/semantics.md]
    python3 check_semantics.py --probe a.cpp[,b.cpp] [--probe-top top] [--probe-shim exactclass] ...
    python3 check_semantics.py --page-from <result json> --md <page>
    python3 check_semantics.py --self-test

Vitis' math library (MEMOS #94, --vitis-mathlib auto|off, default auto): a build whose link lacks symbols of
libhlsmc++ (the cordic / log tables, hls::powf, hls::atan(double), ...) gets them compiled from the install's
bitcode at check time (vitis_mathlib.py); nothing of the install is copied into the repositories, and the
temporary files and the executables that hold library code are deleted after the run.

hls::stream: every stream argument of the top gets STREAM_TOKENS tokens per call (filled like an array
element); the dump holds the tokens left in it after the call.  A blocking read of an empty stream ends the run
at that read (Vitis' C simulation blocks there; its deadlock detector aborts): the driver writes the dump of
the call in progress and exits 88 (the real reference's C-simulation hls::stream is watched by a thread
that applies the detector's test).  A run in which both sides stop at a blocking read compares those
dumps; a run in which only the reference stops there does not count.

Layouts: one element layout serves both sides; it was measured with this clang / LLVM (iN and
_BitInt(N): 1/2/4/8 bytes up to 64 bits, then ceil(N/64) * 8 bytes with alignment 8 on both sides).
Not compared: global variables (only the arguments and the return value are outputs), pointer members.
"""
import argparse
import concurrent.futures as cf
import hashlib
import json
import os
import pwd
import re
import resource
import shlex
import shutil
import subprocess
import sys
import threading
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                         # noqa: E402
import vitis_mathlib                       # noqa: E402

# Executing the candidate: the MLIR of cgeist (LLVM 18 syntax) is read, lowered and translated by
# CIRCT's MLIR build (the parser hls-est reads it with; RelWithDebInfo on ext4) and compiled by its llc.
# Polygeist's own build is a Debug build on /mnt/d whose 1-3 GB binaries page in over 9P for tens of
# seconds per process under load.
# The tools are found from this file's tree and the account's own home directory, not $HOME: the
# harness runs with a private HOME for uninstalled cgeist builds (W11 review defect 6).
_REPO_ROOT = Path(__file__).resolve().parents[2]
_ACCOUNT_HOME = Path(pwd.getpwuid(os.getuid()).pw_dir)
MLIR_BIN = os.environ.get("CS_MLIR_BIN", str(_REPO_ROOT / "llvm" / "build" / "bin"))
MLIR_OPT = MLIR_BIN + "/mlir-opt"
MLIR_TRANSLATE = MLIR_BIN + "/mlir-translate"
LLC = MLIR_BIN + "/llc"
# clang 18 (the clang cgeist embeds) for the shim reference: a stripped ext4 copy when one exists
_CLANG18_DIR = os.environ.get("CS_CLANG18_DIR") or next(
    (d for d in (str(_ACCOUNT_HOME / "hls-est-work" / "llvm18-stripped"),)
     if os.path.exists(d + "/clang-18")), "/mnt/d/HLS/Polygeist/llvm-project/build/bin")
CLANG = _CLANG18_DIR + "/clang"
CLANGXX = _CLANG18_DIR + "/clang++"
# The macros Vitis' front end adds in synthesis (run_hlsest.VITIS_FRONTEND_DEFINES; that module loads
# the design catalogue on import, so the tuple is repeated here).
VITIS_FRONTEND_DEFINES = ("__SYNTHESIS__", "__VITIS_HLS__", "__HLS_SYN__", "AESL_SYN")
POLYGEIST_OPT = os.environ.get("POLYGEIST_OPT", "/mnt/d/HLS/Polygeist/build/bin/polygeist-opt")
# polygeist-opt's LLVM dialect has typed pointers, which this tree's mlir-opt / mlir-translate do not
# parse: its output is finished with Polygeist's own (reconcile-unrealized-casts, translation; the LLVM IR
# they write uses opaque pointers, which this tree's llc reads).
POLYGEIST_MLIR_OPT = os.environ.get("POLYGEIST_MLIR_OPT", "/mnt/d/HLS/Polygeist/llvm-project/build/bin/mlir-opt")
POLYGEIST_MLIR_TRANSLATE = os.environ.get("POLYGEIST_MLIR_TRANSLATE",
                                          "/mnt/d/HLS/Polygeist/llvm-project/build/bin/mlir-translate")
SAN_LINKER = os.environ.get("CS_SAN_LINKER", "/usr/bin/clang++-14")
# the real-header reference: Vitis' C simulation compiles with GCC; Polygeist's clang is a Debug build
# that needs more than 10 minutes for hls_math.h, the system g++ 15 s.  GCC 13: -ftrivial-auto-var-init
# (GCC 12+) and _Float16 in C++ (GCC 13)
GCC = os.environ.get("CS_GCC", "/usr/bin/gcc-13")
GXX = os.environ.get("CS_GXX", "/usr/bin/g++-13")
VITIS_INCLUDE_SRC = os.environ.get("CS_VITIS_INCLUDE", C.VITIS_INCLUDE_WSL)
VITIS_INCLUDE_MIRROR = _ACCOUNT_HOME / "hls-est-work" / "vitis-include-mirror" / "2025.1"
WORK_DEFAULT = Path.home() / "hls-est-work" / "semantics"
REF_KINDS = ("real", "shim")
REF_CACHE = Path(os.environ.get("CS_REF_CACHE", str(Path.home() / "hls-est-work" / "semantics-ref-cache")))
REF_CACHE_VERSION = "1"     # bump when the way a reference is built changes outside the hashed texts
SOURCE_EXT = re.compile(r"\.(c|cc|cpp|cxx|C|h|hh|hpp|hxx|H|inc|def|tcc|ipp|inl)$")


def vitis_include_dir():
    """An ext4 mirror of the real Vitis headers (reading /mnt/a for every compile is slow under load).
    Refreshed when a file of the source is newer or missing; returns (dir, md5 of the file list)."""
    src, dst = Path(VITIS_INCLUDE_SRC), VITIS_INCLUDE_MIRROR
    if not src.is_dir():
        raise RuntimeError(f"no Vitis include dir {src}")
    listing = []
    stale = not dst.is_dir()
    for dp, dn, fn in os.walk(src):
        dn.sort()
        for f in sorted(fn):
            p = Path(dp) / f
            st = p.stat()
            rel = p.relative_to(src)
            listing.append(f"{rel}|{st.st_size}|{int(st.st_mtime)}")
            q = dst / rel
            if not stale and (not q.exists() or q.stat().st_size != st.st_size
                              or int(q.stat().st_mtime) != int(st.st_mtime)):
                stale = True
    if stale:
        tmp = dst.with_name(dst.name + f".tmp{os.getpid()}")
        if tmp.exists():
            shutil.rmtree(tmp)
        shutil.copytree(src, tmp, copy_function=shutil.copy2)
        if dst.exists():
            shutil.rmtree(dst)
        tmp.rename(dst)
    return str(dst), hashlib.md5("\n".join(listing).encode()).hexdigest()

UPSTREAM_LOWERING = ["--lower-affine", "--convert-scf-to-cf", "--arith-expand", "--convert-math-to-llvm",
                     "--convert-math-to-libm", "--expand-strided-metadata", "--finalize-memref-to-llvm",
                     "--convert-arith-to-llvm", "--convert-index-to-llvm", "--convert-cf-to-llvm",
                     "--convert-func-to-llvm", "--reconcile-unrealized-casts"]
STD_DIALECTS = {"arith", "affine", "memref", "func", "scf", "math", "cf", "llvm", "index", "builtin"}
GUARD_BYTES = 4096          # guard zone before and after each memref argument
DYN_LEADING = 1 << 16       # elements of a leading '?' dimension (rank 1): a top's pointer argument; 4096 was
                            # too small for feature maps (GradCAM conv_ds read past it: an ASan report, no run)
DYN_LEADING_ND = 256        # ... of a leading '?' dimension of a rank > 1 memref
DYN_INNER = 64              # ... of any other '?' dimension
DYN_RETRY_SCALE = 16        # the leading '?' sizes of the one retry after a heap-buffer-overflow
MAX_BUFFER_BYTES = 1 << 30


# ------------------------------------------------------------------------------------------- types --

class Ty:
    """An MLIR type the driver can fill: int (bits), float (name), ptr, struct (fields, packed),
    array (n, elem), memref (dims, elem, layout)."""

    def __init__(self, k, **kw):
        self.k = k
        self.bits = kw.get("bits", 0)
        self.name = kw.get("name", "")
        self.fields = kw.get("fields", [])
        self.packed = kw.get("packed", False)
        self.n = kw.get("n", 0)
        self.elem = kw.get("elem")
        self.dims = kw.get("dims", [])
        self.layout = kw.get("layout", "")
        self.text = kw.get("text", "")

    def __repr__(self):
        return self.text or self.k


FLOATS = {"bf16": 16, "f16": 16, "f32": 32, "f64": 64, "f80": 80, "f128": 128}


class _Parser:
    def __init__(self, s):
        self.s, self.i = s, 0

    def ws(self):
        while self.i < len(self.s) and self.s[self.i] in " \t\n":
            self.i += 1

    def peek(self, lit):
        self.ws()
        return self.s.startswith(lit, self.i)

    def eat(self, lit):
        if not self.peek(lit):
            raise ValueError(f"expected {lit!r} at {self.i} in {self.s!r}")
        self.i += len(lit)

    def num(self):
        self.ws()
        m = re.compile(r"\d+").match(self.s, self.i)
        if not m:
            raise ValueError(f"expected a number at {self.i} in {self.s!r}")
        self.i = m.end()
        return int(m.group())

    def balanced_until(self, stop):
        """Text up to (not including) the `stop` character at nesting depth 0."""
        depth, j = 0, self.i
        while j < len(self.s):
            ch = self.s[j]
            if ch in "<([{":
                depth += 1
            elif ch in ">)]}":
                if depth == 0 and ch == stop:
                    break
                depth -= 1
            j += 1
        out = self.s[self.i:j]
        self.i = j
        return out

    def type(self, llvm_ctx=False):
        self.ws()
        start = self.i
        m = re.compile(r"i(\d+)(?![\w])").match(self.s, self.i)
        if m:
            self.i = m.end()
            return Ty("int", bits=int(m.group(1)), text=m.group())
        for f in ("bf16", "f16", "f32", "f64", "f80", "f128"):
            if re.compile(re.escape(f) + r"(?![\w])").match(self.s, self.i):
                self.i += len(f)
                return Ty("float", name=f, bits=FLOATS[f], text=f)
        if re.compile(r"index(?![\w])").match(self.s, self.i):
            self.i += 5
            return Ty("int", bits=64, text="index", name="index")
        if self.s.startswith("!llvm.", self.i):
            self.i += len("!llvm.")
            return self.llvm(start)
        if llvm_ctx and re.compile(r"(struct|array|ptr|void)\b").match(self.s, self.i):
            return self.llvm(start)
        if self.s.startswith("memref<", self.i):
            self.i += len("memref<")
            dims = []
            while True:
                self.ws()
                m = re.compile(r"(\?|\d+)x").match(self.s, self.i)
                if not m:
                    break
                dims.append(None if m.group(1) == "?" else int(m.group(1)))
                self.i = m.end()
            elem = self.type()
            layout = ""
            if self.peek(","):
                self.eat(",")
                layout = self.balanced_until(">").strip()
            self.eat(">")
            return Ty("memref", dims=dims, elem=elem, layout=layout, text=self.s[start:self.i])
        raise ValueError(f"unsupported type at {self.i} in {self.s!r}")

    def llvm(self, start):
        if self.s.startswith("ptr", self.i):
            self.i += 3
            if self.peek("<"):
                self.eat("<")
                self.balanced_until(">")
                self.eat(">")
            return Ty("ptr", text=self.s[start:self.i])
        if self.s.startswith("array<", self.i):
            self.i += len("array<")
            n = self.num()
            self.eat("x")
            elem = self.type(llvm_ctx=True)
            self.eat(">")
            return Ty("array", n=n, elem=elem, text=self.s[start:self.i])
        if self.s.startswith("struct<", self.i):
            self.i += len("struct<")
            if self.peek('"'):
                j = self.s.index('"', self.i + 1)
                self.i = j + 1
                if self.peek(">"):
                    raise ValueError("identified struct without a body")
                self.eat(",")
            packed = False
            if self.peek("packed"):
                self.eat("packed")
                packed = True
            self.eat("(")
            fields = []
            while not self.peek(")"):
                fields.append(self.type(llvm_ctx=True))
                if self.peek(","):
                    self.eat(",")
            self.eat(")")
            self.eat(">")
            return Ty("struct", fields=fields, packed=packed, text=self.s[start:self.i])
        raise ValueError(f"unsupported llvm type at {self.i} in {self.s!r}")


def parse_type(s):
    p = _Parser(s.strip())
    t = p.type()
    p.ws()
    if p.i != len(p.s):
        raise ValueError(f"trailing text in type {s!r}")
    return t


def size_align(t):
    """(size, alignment) in bytes; the same on both sides for this clang / LLVM (module docstring)."""
    if t.k == "int":
        b = t.bits
        for lim, sz in ((8, 1), (16, 2), (32, 4), (64, 8)):
            if b <= lim:
                return sz, sz
        return (b + 63) // 64 * 8, 8
    if t.k == "float":
        return {"bf16": (2, 2), "f16": (2, 2), "f32": (4, 4), "f64": (8, 8), "f80": (16, 16),
                "f128": (16, 16)}[t.name]
    if t.k == "ptr":
        return 8, 8
    if t.k == "array":
        s, a = size_align(t.elem)
        return s * t.n, a
    if t.k == "struct":
        off, al = 0, 1
        for f in t.fields:
            s, a = size_align(f)
            if not t.packed:
                off = (off + a - 1) // a * a
                al = max(al, a)
            off += s
        return ((off + al - 1) // al * al if not t.packed else off), (1 if t.packed else al)
    raise ValueError(f"no layout for {t}")


# leaf kinds of the driver: 0 int, 1 f16, 2 f32, 3 f64, 4 bf16, 5 pointer (zero, not compared), 6 f80
KIND = {"f16": 1, "f32": 2, "f64": 3, "bf16": 4, "f80": 6}


def leaf_runs(t, base=0, out=None):
    """Runs (offset, bits, kind, count, stride) of the scalar leaves of t, in canonical order."""
    out = [] if out is None else out
    if t.k == "int":
        out.append([base, t.bits, 0, 1, 0])
    elif t.k == "float":
        if t.name not in KIND:
            raise ValueError(f"cannot fill {t.name}")
        out.append([base, t.bits, KIND[t.name], 1, 0])
    elif t.k == "ptr":
        out.append([base, 64, 5, 1, 0])
    elif t.k == "array":
        es, _ = size_align(t.elem)
        if t.elem.k in ("int", "float", "ptr"):
            r = leaf_runs(t.elem, base)[0]
            r[3], r[4] = t.n, es
            out.append(r)
        else:
            for i in range(t.n):
                leaf_runs(t.elem, base + i * es, out)
    elif t.k == "struct":
        off = 0
        for f in t.fields:
            s, a = size_align(f)
            if not t.packed:
                off = (off + a - 1) // a * a
            leaf_runs(f, base + off, out)
            off += s
    else:
        raise ValueError(f"cannot fill {t}")
    return out


# --------------------------------------------------------------------------------- MLIR reading --

def split_top_level(s, sep=","):
    out, depth, cur = [], 0, []
    for ch in s:
        if ch in "<([{":
            depth += 1
        elif ch in ">)]}":
            depth -= 1
        if ch == sep and depth == 0:
            out.append("".join(cur))
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur))
    return out


def top_signature(text, fn):
    """([arg type text], [result type text]) of func.func @fn, or None."""
    m = re.search(r"func\.func\s+(?:private\s+)?@" + re.escape(fn) + r"\(", text)
    if not m:
        return None
    i, depth = m.end(), 1
    j = i
    while j < len(text) and depth:
        if text[j] in "<([{":
            depth += 1
        elif text[j] in ">)]}":
            depth -= 1
        j += 1
    args_txt = text[i:j - 1]
    rest = text[j:j + 2000]
    res = []
    mr = re.match(r"\s*->\s*", rest)
    if mr:
        r = rest[mr.end():]
        if r.startswith("("):
            k = _Parser(r)
            k.i = 1
            inner = k.balanced_until(")")
            res = [x.strip() for x in split_top_level(inner)]
        else:
            k = _Parser(r)
            k.type()
            res = [r[:k.i].strip()]
    args = []
    for a in split_top_level(args_txt):
        a = a.strip()
        if not a:
            continue
        ty = a.split(":", 1)[1].strip() if ":" in a else a
        # drop an argument attribute dictionary `{llvm.noalias}` / `loc(...)`
        p = _Parser(ty)
        p.type()
        args.append(ty[:p.i].strip())
    return args, res


OP_RE = re.compile(r'^\s*(?:%[^=]+=\s*)?"?([a-z_][a-z_0-9]*)\.([a-z_0-9.]+)"?', re.M)


def dialects_used(text):
    return {m.group(1) for m in OP_RE.finditer(text)}


def demangle(name):
    try:
        p = subprocess.run(["c++filt", name], capture_output=True, text=True, timeout=30)
        return p.stdout.strip() or name
    except Exception:          # noqa: BLE001
        return name


def cxx_name_of(top_fn, top):
    """The C++ expression naming the top function (qualified, with template arguments), or None
    when the top is a member function or an operator."""
    if not top_fn.startswith("_Z"):
        return top_fn
    dm = demangle(top_fn)
    if dm == top_fn:
        return None
    depth, cut = 0, None
    for k, ch in enumerate(dm):
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == "(" and depth == 0:
            cut = k
            break
    name = dm[:cut] if cut is not None else dm
    # a templated function's demangled name starts with its return type: `void foo<5>`
    if " " in name.split("<")[0]:
        name = name.split("<")[0].rsplit(" ", 1)[1] + ("<" + name.split("<", 1)[1] if "<" in name else "")
    if "operator" in name:
        return None
    return name


# ------------------------------------------------------------------------------- cgeist command --

_CATALOGUE = None
CATALOG = None          # designs.load_designs catalogue for complete_record (None = the default; --catalog)


def complete_record(key, rec):
    """Fill in what a run_hlsest.py record lacks and a sweep record has (W11 review defect 6): the
    design's directory and sources from the catalogue, and the cgeist log next to the record's MLIR
    (same cache key: <name>.<key>.mlir -> <name>.<key>.cgeist.log)."""
    global _CATALOGUE
    if not isinstance(rec, dict):
        return
    if "dir" not in rec:
        if _CATALOGUE is None:
            import designs as D
            _CATALOGUE = {f"{d['dataset']}/{d['benchmark']}": d for d in D.load_designs(catalog=CATALOG)}
        d = _CATALOGUE.get(key)
        if d:
            rec.setdefault("dir", d["dir"])
            rec.setdefault("sources", d.get("sources"))
    if not rec.get("cgeist_log") and rec.get("mlir"):
        log = Path(rec["mlir"]).with_suffix(".cgeist.log")
        if log.exists():
            rec["cgeist_log"] = str(log)


def cgeist_command(rec):
    """The cgeist argv of the record (first line of its log), or None."""
    log = rec.get("cgeist_log")
    if not log or not os.path.exists(log):
        return None
    with open(log, errors="replace") as f:
        first = f.readline().strip()
    try:
        return shlex.split(first)
    except ValueError:
        return first.split()


def native_flags(argv):
    """(-I/-D/-std/-U/-include flags in order, sources) of a cgeist argv."""
    flags, srcs, k = [], [], 1
    while k < len(argv):
        x = argv[k]
        if x in ("-I", "-D", "-U", "-include", "-isystem") and k + 1 < len(argv):
            flags += [x, argv[k + 1]]
            k += 2
            continue
        if x == "-o" and k + 1 < len(argv):
            k += 2
            continue
        if re.match(r"-(I|D|U|std=)", x):
            flags.append(x)
        elif not x.startswith("-") and re.search(r"\.(c|cc|cpp|cxx|C)$", x):
            srcs.append(x)
        k += 1
    return flags, srcs


C_COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)


def defines_function(path, name):
    try:
        text = Path(path).read_text(errors="replace")
    except OSError:
        return False
    pat = r"[\w>*&]\s*(?:\w+\s*::\s*)*\b" + re.escape(name) + r"\s*\([^;{}]*\)\s*(?:const\s*)?\{"
    return re.search(pat, C_COMMENT.sub(" ", text)) is not None


def has_main(path):
    try:
        text = C_COMMENT.sub(" ", Path(path).read_text(errors="replace"))
    except OSError:
        return False
    return re.search(r"\bint\s+main\s*\(", text) is not None


# ------------------------------------------------------------------------------- driver sources --

DRIVER_MAIN = r'''
// generated by check_semantics.py: common driver of the reference and the candidate
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <map>
#include <vector>
#include "cs_spec.h"
extern "C" void cs_call(void **p);
static inline uint64_t cs_mix(uint64_t x) {
  x += 0x9e3779b97f4a7c15ULL;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
  x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
  return x ^ (x >> 31);
}
static unsigned char *cs_base[CS_NARGS + 1];
static unsigned char *cs_obj[CS_NARGS + 1];   // the storage a top-level hls::stream argument points to
static FILE *cs_out;
static int cs_cur_call;   // the call in progress (the dump written at a blocking read names it)
// Set by the real reference's thunk while the top runs: copies the arguments' state back into the
// driver's buffers and FIFOs (cs_back), so a dump written at a blocking read sees it.
extern "C" { void (*cs_block_hook)(void) = 0; }
// The FIFO key of stream i of stream entry a: object i of the argument's storage, or for a member
// stream of an aggregate of streams (a TAPA async_mmap, OPEN_ISSUES O157) the member's offset in its
// parent argument's object.
static unsigned char *cs_stream_key(int a, uint32_t i) {
  const CsArg &A = cs_args[a];
  if (A.parent >= 0) return cs_obj[A.parent] + A.key_off;
  return cs_obj[a] + (uint64_t)i * A.stream_stride;
}

// ---- token FIFOs of hls::stream objects, keyed by the object's address.  The candidate's stream
// methods (generated from cgeist's declarations), the shim reference's and the real reference's
// argument conversion all use them; the driver fills the top's stream arguments with tokens before
// each call and dumps what is left in them after it.
struct CsFifo { std::deque<std::vector<unsigned char> > q; uint64_t underflow = 0; };
static std::map<const void *, CsFifo> cs_fifos;
extern "C" void cs_fifo_reset(const void *k) { CsFifo &f = cs_fifos[k]; f.q.clear(); f.underflow = 0; }
extern "C" void cs_fifo_push(const void *k, const void *d, uint32_t n) {
  const unsigned char *b = (const unsigned char *)d;
  cs_fifos[k].q.emplace_back(b, b + n);
}
extern "C" int cs_fifo_try_pop(const void *k, void *d, uint32_t n) {
  CsFifo &f = cs_fifos[k];
  if (f.q.empty()) return 0;
  std::vector<unsigned char> &t = f.q.front();
  memset(d, 0, n);
  memcpy(d, t.data(), t.size() < n ? t.size() : n);
  f.q.pop_front();
  return 1;
}
extern "C" void cs_dump_and_exit(int code);
extern "C" void cs_fifo_pop(const void *k, void *d, uint32_t n) {
  if (cs_fifo_try_pop(k, d, n)) return;
  // a blocking read of an empty stream: Vitis' C simulation blocks and its deadlock detector aborts
  // (hls_stream.h); here the run ends at that read with the call's dump and a distinct exit code
  cs_stop_at_blocking_read();
}
extern "C" uint64_t cs_fifo_size(const void *k) {
  std::map<const void *, CsFifo>::iterator it = cs_fifos.find(k);
  return it == cs_fifos.end() ? 0 : it->second.q.size();
}

static void cs_put_int(unsigned char *p, int bits, const uint64_t *limb) {
  int nb = (bits + 7) / 8;
  for (int b = 0; b < nb; ++b) p[b] = (unsigned char)(limb[b / 8] >> (8 * (b % 8)));
}
// ---- mode `graph-*` (GRAPH_MODES): valid graphs in the argument shapes graph_role recognises.  Graph g
// has cs_gc(g) nodes, an even number in 2..8, and as many edges: a random perfect matching listed by source
// (j, partner(j)), j = 0 .. cs_gc(g) - 1, so the edge list is symmetric, every node has one out-edge and one
// in-edge (no degree is 0) and every endpoint is below its graph's node count.  Graphs are concatenated in
// every edge list (graph g's edges start after the cs_gc(0) + ... + cs_gc(g - 1) edges of the graphs before
// it); a count array holds cs_gc(i) at position i (nodes, edges and the per-graph counts of a batch), a
// count scalar holds cs_gc(0) (the node and edge count of a single graph, and the number of graphs of a
// batch).
static uint64_t cs_gseed;
static std::vector<uint32_t> cs_gedge;     // cs_gedge[2q], cs_gedge[2q + 1]: endpoints of edge q
static uint32_t cs_gc(uint64_t g) { return 2 * (1 + (uint32_t)(cs_mix(cs_gseed + 1 + g) % 4)); }
static void cs_graph_edges(uint64_t need) {
  cs_gedge.clear();
  for (uint64_t g = 0; cs_gedge.size() / 2 < need; ++g) {
    uint32_t n = cs_gc(g), perm[8], partner[8];
    for (uint32_t j = 0; j < n; ++j) perm[j] = j;
    for (uint32_t j = n - 1; j > 0; --j) {
      uint32_t k = (uint32_t)(cs_mix(cs_gseed * 31ULL + g * 8ULL + j) % (j + 1));
      uint32_t t = perm[j]; perm[j] = perm[k]; perm[k] = t;
    }
    for (uint32_t j = 0; j < n; j += 2) { partner[perm[j]] = perm[j + 1]; partner[perm[j + 1]] = perm[j]; }
    for (uint32_t j = 0; j < n; ++j) { cs_gedge.push_back(j); cs_gedge.push_back(partner[j]); }
  }
}
// The value of graph lane `lane` (0 or 1 for an edge endpoint) of element `idx` of argument A, or -1 when
// the lane keeps its mode's fill.
static int64_t cs_graph_value(const CsArg &A, uint64_t idx, int lane, uint64_t v) {
  switch (A.graph_role) {
  case 1: return A.is_scalar ? cs_gc(0) : cs_gc(idx);                       // a count
  case 2: return cs_gedge[2 * (idx / 2) + idx % 2];                          // edge list: last dimension 2
  case 3: return lane < 2 ? (int64_t)cs_gedge[2 * idx + lane] : -1;          // edge list: two lanes an element
  case 4: return (int64_t)(v % 2);                                           // another index lane: 0 or 1
  }
  return -1;
}
static void cs_fill(int mode, uint64_t seed, int call) {
  // modes 6, 7, 8: `graph-small`, `graph-wide`, `graph-pos`: the graph lanes above, every other lane as in
  // mode 0, 1, 2
  bool graph = mode >= 6;
  if (graph) {
    mode -= 6;
    cs_gseed = cs_mix(seed * 1000003ULL + (uint64_t)call * 7919ULL + 0x6772617068ULL);
    uint64_t need = 0;
    for (int a = 0; a < CS_NARGS; ++a)
      if (cs_args[a].graph_role == 2 || cs_args[a].graph_role == 3) {
        uint64_t q = cs_args[a].graph_role == 2 ? cs_args[a].elems / 2 : cs_args[a].elems;
        if (q > need) need = q;
      }
    cs_graph_edges(need);
  }
  for (int a = 0; a < CS_NARGS; ++a) {
    const CsArg &A = cs_args[a];
    unsigned char *base = cs_base[a];
    uint64_t total = A.elems + 2 * A.guard;
    memset(base, 0, total * A.esize);
    if (A.is_ret) continue;
    uint64_t st = cs_mix(seed * 1000003ULL + (uint64_t)call * 7919ULL + (uint64_t)a * 104729ULL + 1);
    for (uint64_t e = 0; e < total; ++e) {
      unsigned char *el = base + e * A.esize;
      int lane = 0;                 // the element's integer lanes of at least GRAPH_INDEX_BITS, in order
      for (int r = 0; r < A.nruns; ++r) {
        const CsRun &R = A.runs[r];
        for (uint32_t c = 0; c < R.count; ++c) {
          unsigned char *p = el + R.off + (uint64_t)c * R.stride;
          uint64_t v = cs_mix(st++);
          if (graph && A.graph_role && R.kind == 0 && R.bits >= CS_GRAPH_INDEX_BITS && e >= A.guard &&
              e < A.guard + A.elems) {
            int64_t g = cs_graph_value(A, e - A.guard, lane++, v);
            if (g >= 0) {
              uint64_t limb[64] = {(uint64_t)g};
              int sz = R.bits <= 32 ? 4 : R.bits <= 64 ? 8 : (R.bits + 63) / 64 * 8;
              unsigned char tmp[512] = {0};
              cs_put_int(tmp, R.bits, limb);
              memcpy(p, tmp, sz);
              continue;
            }
          }
          // mode 3 (`diag`): as `pos`, but the diagonal of a square matrix argument is large (an
          // integer or fixed-point element: a quarter of its range, whatever its fraction width; a
          // float: cols + 1), so the matrix is diagonally dominant (pivots of a decomposition are not
          // 0); mode 4 (`align`): as `pos`, but a scalar integer is a multiple of 64 in 64..256;
          // mode 5 (`index`): as `pos`, but an integer lane of an array or aggregate argument is its
          // own position in the argument (0, 1, 2, ...): every index array is monotone and in range
          // (a CSR row pointer, its column indices, the `end = ptr[n]` count they imply)
          bool diag = false;
          if (mode == 3 && A.sq_rows && e >= A.guard && e < A.guard + A.elems) {
            uint64_t idx = e - A.guard;
            diag = (idx / A.sq_cols) % A.sq_rows == idx % A.sq_cols;
          }
          if (R.kind == 0) {
            uint64_t limb[64] = {0};
            int nl = (R.bits + 63) / 64;
            if (mode == 0) limb[0] = A.is_scalar ? v % 9 : v % 8;
            else if (diag && R.bits >= 3) limb[(R.bits - 2) / 64] = 1ULL << ((R.bits - 2) % 64);
            else if (mode == 4 && A.is_scalar) limb[0] = 64 * (1 + v % 4);
            else if (mode == 5 && (A.elems > 1 || R.count > 1))  // an array, or an aggregate by value
              limb[0] = e >= A.guard && e < A.guard + A.elems ? (e - A.guard) * R.count + c : 0;
            else if (mode >= 2) limb[0] = 1 + v % 8;
            else if (A.is_scalar) limb[0] = v % 1024;
            else { limb[0] = v; for (int l = 1; l < nl && l < 64; ++l) limb[l] = cs_mix(st++); }
            if (R.bits < 64 * nl) limb[nl - 1] &= (~0ULL) >> (64 * nl - R.bits);
            int sz = R.bits <= 8 ? 1 : R.bits <= 16 ? 2 : R.bits <= 32 ? 4 : R.bits <= 64 ? 8 : nl * 8;
            unsigned char tmp[512] = {0};
            cs_put_int(tmp, R.bits, limb);
            memcpy(p, tmp, sz);
          } else if (R.kind == 5) {
            memset(p, 0, 8);
          } else {
            double d = (double)(v >> 11) * (1.0 / 9007199254740992.0) * 2.0 - 1.0;
            if (mode == 1) d *= 1000.0;
            else if (diag) d = (double)A.sq_cols + 1.0;
            else if (mode >= 2) d = 1.25 + 0.75 * d;
            if (R.kind == 1) { _Float16 h = (_Float16)d; memcpy(p, &h, 2); }
            else if (R.kind == 2) { float f = (float)d; memcpy(p, &f, 4); }
            else if (R.kind == 3) { memcpy(p, &d, 8); }
            else if (R.kind == 4) { float f = (float)d; uint32_t u; memcpy(&u, &f, 4); uint16_t h = (uint16_t)(u >> 16); memcpy(p, &h, 2); }
            else if (R.kind == 6) { long double x = d; memcpy(p, &x, 10); }
          }
        }
      }
    }
  }
}
// A NaN is written as the one quiet NaN of its format: C and IEEE 754 leave the sign and payload of a
// NaN made by an invalid operation unspecified (glibc's sqrt(-1) gives +NaN, x86 sqrtsd gives -NaN).
static void cs_canonical_nan(int kind, unsigned char *p) {
  if (kind == 2) { float f; memcpy(&f, p, 4); if (f != f) { uint32_t q = 0x7fc00000u; memcpy(p, &q, 4); } }
  else if (kind == 3) { double d; memcpy(&d, p, 8); if (d != d) { uint64_t q = 0x7ff8000000000000ULL; memcpy(p, &q, 8); } }
  else if (kind == 1) { uint16_t h; memcpy(&h, p, 2); if ((h & 0x7c00) == 0x7c00 && (h & 0x3ff)) { h = 0x7e00; memcpy(p, &h, 2); } }
  else if (kind == 4) { uint16_t h; memcpy(&h, p, 2); if ((h & 0x7f80) == 0x7f80 && (h & 0x7f)) { h = 0x7fc0; memcpy(p, &h, 2); } }
  else if (kind == 6) { long double x = 0; memcpy(&x, p, 10); if (x != x) { long double q = __builtin_nanl(""); memcpy(p, &q, 10); } }
}
static void cs_dump_elem(const CsArg &A, const unsigned char *el) {
  for (int r = 0; r < A.nruns; ++r) {
    const CsRun &R = A.runs[r];
    if (R.kind == 5) continue;
    int nb = R.kind == 6 ? 10 : (R.bits + 7) / 8;
    for (uint32_t c = 0; c < R.count; ++c) {
      unsigned char tmp[512];
      memcpy(tmp, el + R.off + (uint64_t)c * R.stride, nb);
      if (R.kind == 0 && (R.bits % 8)) tmp[nb - 1] &= (unsigned char)((1u << (R.bits % 8)) - 1);
      cs_canonical_nan(R.kind, tmp);
      fwrite(tmp, 1, nb, cs_out);
    }
  }
}
// One call's dump: the call number, every fixed-size argument (guard zones included) in order, then
// for every stream argument the number of tokens left in it and those tokens.
static void cs_dump(int call) {
  fwrite(&call, sizeof call, 1, cs_out);
  for (int a = 0; a < CS_NARGS; ++a) {
    const CsArg &A = cs_args[a];
    if (A.is_stream) continue;
    uint64_t total = A.elems + 2 * A.guard;
    for (uint64_t e = 0; e < total; ++e) cs_dump_elem(A, cs_base[a] + e * A.esize);
  }
  for (int a = 0; a < CS_NARGS; ++a) {
    const CsArg &A = cs_args[a];
    if (!A.is_stream) continue;
    for (uint32_t i = 0; i < A.stream_count; ++i) {
      CsFifo &f = cs_fifos[cs_stream_key(a, i)];
      uint64_t n = f.q.size();
      fwrite(&n, sizeof n, 1, cs_out);
      std::vector<unsigned char> tok(A.esize + 64);
      for (size_t t = 0; t < f.q.size(); ++t) {
        memset(tok.data(), 0, tok.size());
        memcpy(tok.data(), f.q[t].data(), f.q[t].size() < A.esize ? f.q[t].size() : A.esize);
        cs_dump_elem(A, tok.data());
      }
    }
  }
  fflush(cs_out);
}
extern "C" void cs_dump_and_exit(int code) {   // for runtime hooks that must stop the design
  fflush(stderr);
  if (cs_out) { fflush(cs_out); fclose(cs_out); }
  _Exit(code);
}
// A blocking read of an empty stream (the candidate's or the shim reference's token FIFO, or the real
// reference's C-simulation hls::stream, seen by its watcher): no input can arrive any more, so the run
// ends here with the dump of the call in progress and exit 88; a run in which both sides stop this way
// compares those dumps (W9 round 20 review defect 2: dual_interface_FIFO_receive).
extern "C" void cs_stop_at_blocking_read(void) {
  fprintf(stderr, "cs-stream: read of an empty hls::stream\n");
  if (cs_block_hook) cs_block_hook();
  if (cs_out) cs_dump(cs_cur_call);
  cs_dump_and_exit(88);
}
int main(int argc, char **argv) {
  if (argc < 5) { fprintf(stderr, "usage: %s mode seed calls out\n", argv[0]); return 2; }
  int mode = atoi(argv[1]);
  uint64_t seed = strtoull(argv[2], 0, 10);
  int calls = atoi(argv[3]);
  cs_out = fopen(argv[4], "wb");
  if (!cs_out) return 3;
  for (int a = 0; a < CS_NARGS; ++a) {
    uint64_t bytes = (cs_args[a].elems + 2 * cs_args[a].guard) * cs_args[a].esize;
    cs_base[a] = (unsigned char *)aligned_alloc(64, (bytes + 63) / 64 * 64 + 64);
    if (!cs_base[a]) return 4;
    if (cs_args[a].is_stream) {
      uint64_t ob = ((uint64_t)cs_args[a].stream_count * cs_args[a].stream_stride + 256 + 63) / 64 * 64;
      cs_obj[a] = (unsigned char *)aligned_alloc(64, ob);
      memset(cs_obj[a], 0, ob);
    }
  }
  for (int c = 0; c < calls; ++c) {
    cs_fill(mode, seed, c);
    void *p[CS_NARGS + 1];
    for (int a = 0; a < CS_NARGS; ++a) {
      const CsArg &A = cs_args[a];
      if (A.is_stream) {
        // the tokens of this call: every element of the token buffer, in order (an array of N
        // streams: the i-th N-th of them to stream i)
        // (an aggregate of member streams has stream_count 0: its members are entries of their own)
        p[a] = cs_obj[a];
        uint64_t per = A.stream_count ? A.elems / A.stream_count : 0;
        for (uint32_t i = 0; i < A.stream_count; ++i) {
          unsigned char *k = cs_stream_key(a, i);
          cs_fifo_reset(k);
          for (uint64_t e = i * per; e < (i + 1) * per; ++e) cs_fifo_push(k, cs_base[a] + e * A.esize, A.esize);
        }
      } else {
        p[a] = cs_base[a] + A.guard * A.esize;
      }
    }
    p[CS_NARGS] = 0;
    cs_cur_call = c;
    cs_call(p);
    cs_dump(c);
  }
  fclose(cs_out);
  cs_out = 0;
  return 0;
}
'''

SPEC_HEAD = r'''
// generated by check_semantics.py
#pragma once
#include <cstdint>
struct CsRun { uint32_t off; int bits; int kind; uint32_t count; uint32_t stride; };
struct CsArg { uint64_t elems; uint32_t esize; uint32_t guard; int is_scalar; int is_ret; int nruns; const CsRun *runs;
               int is_stream; uint32_t stream_count; uint32_t stream_stride; uint64_t sq_rows; uint64_t sq_cols;
               int parent; uint32_t key_off; int first_member; int nmembers; int graph_role; };
extern "C" void cs_fifo_reset(const void *k);
extern "C" void cs_fifo_push(const void *k, const void *d, uint32_t n);
extern "C" int cs_fifo_try_pop(const void *k, void *d, uint32_t n);
extern "C" void cs_fifo_pop(const void *k, void *d, uint32_t n);
extern "C" uint64_t cs_fifo_size(const void *k);
extern "C" void (*cs_block_hook)(void);
extern "C" void cs_stop_at_blocking_read(void);
'''

# The thunks share a translation unit with the design's top source, included at THUNK_MARK: their
# standard headers come before it, and every identifier after it carries a Cs / cs_ prefix, so that the
# designs' macros (`#define N 32`, `#define I 8`) reach neither.
THUNK_MARK = "// --- cs: the design's sources go here ---\n"
# library names used after THUNK_MARK that a design may #define (a design's `size`, `data`, `V`, `type`)
THUNK_SHIELDED = ("V", "size", "data", "resize", "type", "value", "get", "width", "range", "to_uint64",
                  "read", "write", "empty", "first", "second", "tuple")
REF_THUNK_CXX = r'''
#include <cstddef>
#include <cstring>
#include <type_traits>
#include "cs_spec.h"
// --- cs: the design's sources go here ---
#ifdef CGEIST_TEST_HLS_STREAM_H
// the shim declares the hls::stream methods without defining them (cgeist emits calls); natively they
// are the driver's token FIFOs, keyed by the object's address like the candidate's generated ones
namespace hls {
template <typename CsT, int CsD> stream<CsT, CsD>::stream() { cs_fifo_reset(this); }
template <typename CsT, int CsD> stream<CsT, CsD>::stream(const char *) { cs_fifo_reset(this); }
template <typename CsT, int CsD> CsT stream<CsT, CsD>::read() {
  CsT cs_v;
  cs_fifo_pop(this, (void *)&cs_v, sizeof(CsT));
  return cs_v;
}
template <typename CsT, int CsD> void stream<CsT, CsD>::read(CsT &cs_v) { cs_fifo_pop(this, (void *)&cs_v, sizeof(CsT)); }
template <typename CsT, int CsD> bool stream<CsT, CsD>::read_nb(CsT &cs_v) {
  return cs_fifo_try_pop(this, (void *)&cs_v, sizeof(CsT)) != 0;
}
template <typename CsT, int CsD> void stream<CsT, CsD>::write(const CsT &cs_v) {
  cs_fifo_push(this, (const void *)&cs_v, sizeof(CsT));
}
template <typename CsT, int CsD> bool stream<CsT, CsD>::write_nb(const CsT &cs_v) {
  cs_fifo_push(this, (const void *)&cs_v, sizeof(CsT));
  return true;
}
template <typename CsT, int CsD> bool stream<CsT, CsD>::empty() const { return cs_fifo_size(this) == 0; }
template <typename CsT, int CsD> bool stream<CsT, CsD>::full() const { return false; }
template <typename CsT, int CsD> int stream<CsT, CsD>::size() const { return (int)cs_fifo_size(this); }
template <typename CsT, int CsD> void stream<CsT, CsD>::operator>>(CsT &cs_v) { read(cs_v); }
template <typename CsT, int CsD> void stream<CsT, CsD>::operator<<(const CsT &cs_v) { write(cs_v); }
}  // namespace hls
#endif
namespace cs_detail {
template <class CsA> struct CsConv {
  typedef typename std::remove_cv<CsA>::type CsV;
  static CsA cs_get(void *cs_p) { return *static_cast<CsV *>(cs_p); }
};
template <class CsA> struct CsConv<CsA *> { static CsA *cs_get(void *cs_p) { return static_cast<CsA *>(cs_p); } };
template <class CsA> struct CsConv<CsA *const> { static CsA *cs_get(void *cs_p) { return static_cast<CsA *>(cs_p); } };
template <class CsA> struct CsConv<CsA &> {
  static CsA &cs_get(void *cs_p) { return *static_cast<typename std::remove_cv<CsA>::type *>(cs_p); }
};
template <class CsA> struct CsConv<CsA &&> {
  static CsA &&cs_get(void *cs_p) { return static_cast<CsA &&>(*static_cast<CsA *>(cs_p)); }
};
template <std::size_t... CsI> struct CsSeq {};
template <std::size_t CsN, std::size_t... CsI> struct CsGen : CsGen<CsN - 1, CsN - 1, CsI...> {};
template <std::size_t... CsI> struct CsGen<0, CsI...> { typedef CsSeq<CsI...> cs_type; };
template <class CsR> struct CsRet {
  template <class CsF, class... CsX> static void cs_run(void *cs_rp, CsF cs_f, CsX &&...cs_x) {
    CsR cs_r = cs_f(static_cast<CsX &&>(cs_x)...);
    std::memcpy(cs_rp, (const void *)&cs_r, sizeof(cs_r));
  }
};
template <> struct CsRet<void> {
  template <class CsF, class... CsX> static void cs_run(void *, CsF cs_f, CsX &&...cs_x) {
    cs_f(static_cast<CsX &&>(cs_x)...);
  }
};
template <class CsR, class... CsA, std::size_t... CsI>
void cs_call_seq(CsR (*cs_f)(CsA...), void **cs_p, CsSeq<CsI...>) {
  CsRet<CsR>::cs_run(cs_p[sizeof...(CsA)], cs_f, CsConv<CsA>::cs_get(cs_p[CsI])...);
}
template <class CsR, class... CsA> void cs_invoke(CsR (*cs_f)(CsA...), void **cs_p) {
  static_assert(sizeof...(CsA) == CS_NPARAMS, "cs: the C++ top and the MLIR top have different arity");
  static_assert(std::is_void<CsR>::value == (CS_HAS_RET == 0),
                "cs: the C++ top and the MLIR top differ in their result");
  cs_call_seq(cs_f, cs_p, typename CsGen<sizeof...(CsA)>::cs_type());
}
// an overloaded top: the overload with the parameter types of the MLIR top's mangled name
template <class... CsP> struct CsPick {
  template <class CsR> static CsR (*cs_get(CsR (*cs_f)(CsP...)))(CsP...) { return cs_f; }
};
// a value of type T in an unevaluated call (the result type of the top, by overload resolution)
template <class CsT> CsT cs_val();
}  // namespace cs_detail
#ifndef CS_TOP_FN
#define CS_TOP_FN &CS_TOP
#endif
extern "C" void cs_call(void **cs_p) { cs_detail::cs_invoke(CS_TOP_FN, cs_p); }
'''

# Reference thunk for the real Vitis headers in C-simulation mode (no __SYNTHESIS__).  There an
# ap_int / ap_fixed is an ssdm_int_sim<W, S> holding an ap_private<W, S> V (etc/ap_common.h): the value
# sign-extended over its container, and from 65 bits on a different size than the MLIR iN
# (ap_int<129> is 32 bytes, i129 24).  So every argument is copied into native objects before the call
# and back after it: an ap element from the MLIR bits through ap_int_base<W, false> (which makes the
# container canonical), any other element byte for byte when its size equals the MLIR element's.  The
# guard zones travel with the buffer, so out-of-bounds writes still show up in the dump.
REF_THUNK_REAL = r'''
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tuple>
#include <type_traits>
#include <memory>
#include <vector>
#include "cs_spec.h"
// --- cs: the design's sources go here ---
namespace cs_detail {
[[noreturn]] inline void cs_layout_fail(int cs_a, const char *cs_what) {
  std::fprintf(stderr, "cs-layout: argument %d: %s\n", cs_a, cs_what);
  std::fflush(stderr);
  std::_Exit(87);
}
#ifdef __AP_COMMON_H__
template <int CsW, bool CsS> std::integral_constant<int, CsW> cs_apw(const ssdm_int_sim<CsW, CsS> *);
template <int CsW, bool CsS> std::integral_constant<bool, CsS> cs_aps(const ssdm_int_sim<CsW, CsS> *);
#endif
std::integral_constant<int, 0> cs_apw(...);
std::integral_constant<bool, false> cs_aps(...);
#ifdef X_HLS_STREAM_SIM_H
template <class CsT, int CsD> std::true_type cs_stream(const hls::stream<CsT, CsD> *);
#endif
std::false_type cs_stream(...);
template <class CsE> struct CsAp {
  enum { cs_w = decltype(cs_apw((CsE *)0))::value, cs_s = decltype(cs_aps((CsE *)0))::value,
         cs_is_stream = decltype(cs_stream((CsE *)0))::value };
};
inline uint32_t cs_limb_bytes(uint32_t cs_es, int cs_l) {
  uint32_t cs_left = cs_es - 8u * (uint32_t)cs_l;
  return cs_left < 8u ? cs_left : 8u;
}
inline void cs_check_int_elem(int cs_a, int cs_w) {
  const CsArg &cs_arg = cs_args[cs_a];
  if (cs_arg.nruns != 1 || cs_arg.runs[0].kind != 0 || cs_arg.runs[0].count != 1 || cs_arg.runs[0].bits != cs_w)
    cs_layout_fail(cs_a, "an ap type whose width differs from the MLIR element");
}
template <class CsE, int CsW = CsAp<CsE>::cs_w> struct CsElem;
#ifdef __AP_COMMON_H__
template <class CsE, int CsW> struct CsElem {   // an ap_int / ap_fixed of CsW bits
  static void cs_in(int cs_a, CsE *cs_d, const unsigned char *cs_s, uint32_t cs_es) {
    cs_check_int_elem(cs_a, CsW);
    const int cs_nl = (CsW + 63) / 64;
    ap_int_base<CsW, false> cs_u = 0;
    for (int cs_l = cs_nl - 1; cs_l >= 0; --cs_l) {
      uint64_t cs_limb = 0;
      std::memcpy(&cs_limb, cs_s + 8 * cs_l, cs_limb_bytes(cs_es, cs_l));
      if (cs_nl == 1) cs_u = ap_int_base<CsW, false>((unsigned long long)cs_limb);
      else cs_u = (cs_u << 64) | ap_int_base<CsW, false>((unsigned long long)cs_limb);
    }
    ap_int_base<CsW, (bool)CsAp<CsE>::cs_s> cs_v = cs_u;
    cs_d->V = cs_v.V;
  }
  static void cs_out(int cs_a, unsigned char *cs_d, const CsE *cs_s, uint32_t cs_es) {
    cs_check_int_elem(cs_a, CsW);
    ap_int_base<CsW, (bool)CsAp<CsE>::cs_s> cs_v;
    cs_v.V = cs_s->V;
    ap_int_base<CsW, false> cs_u = cs_v;
    const int cs_nl = (CsW + 63) / 64;
    for (int cs_l = 0; cs_l < cs_nl; ++cs_l) {
      ap_int_base<CsW, false> cs_t = cs_nl == 1 ? cs_u : (cs_u >> (64 * cs_l));
      uint64_t cs_limb = ap_int_base<64, false>(cs_t).to_uint64();
      std::memcpy(cs_d + 8 * cs_l, &cs_limb, cs_limb_bytes(cs_es, cs_l));
    }
  }
};
#endif
template <class CsE> struct CsElem<CsE, 0> {   // any other element: the same bytes
  static void cs_check(int cs_a, uint32_t cs_es) {
    if (CsAp<CsE>::cs_is_stream) cs_layout_fail(cs_a, "hls::stream argument");
    if (sizeof(CsE) != cs_es) cs_layout_fail(cs_a, "element size differs from the MLIR element");
  }
  static void cs_in(int cs_a, CsE *cs_d, const unsigned char *cs_s, uint32_t cs_es) {
    cs_check(cs_a, cs_es);
    std::memcpy((void *)cs_d, cs_s, sizeof(CsE));
  }
  static void cs_out(int cs_a, unsigned char *cs_d, const CsE *cs_s, uint32_t cs_es) {
    cs_check(cs_a, cs_es);
    std::memcpy(cs_d, (const void *)cs_s, sizeof(CsE));
  }
};
template <class CsB> struct CsBuf {   // the native copy of one memref argument, guard zones included
  // An array new[], not a std::vector: an element type that cannot be moved (TAPA's istream / ostream,
  // auto_ntt) needs only a default constructor this way (W9r14-impl).
  std::unique_ptr<CsB[]> cs_v;
  uint64_t cs_size = 0;
  // MLIR elements per native element: cgeist flattens an array of a struct of m equal scalars into a
  // trailing dimension of m (flowgnn `edge_t *` -> memref<?x2xi32>); the bytes agree element group by
  // element group (W9r15-impl). 1 for every other element.
  static uint32_t cs_group(int cs_a) {
    const CsArg &cs_arg = cs_args[cs_a];
    if (CsAp<CsB>::cs_w != 0 || CsAp<CsB>::cs_is_stream || cs_arg.esize == 0 ||
        sizeof(CsB) <= cs_arg.esize || sizeof(CsB) % cs_arg.esize)
      return 1;
    uint32_t cs_m = (uint32_t)(sizeof(CsB) / cs_arg.esize);
    if (cs_arg.elems % cs_m || cs_arg.guard % cs_m)
      return 1;
    return cs_m;
  }
  void cs_fill(int cs_a, void *cs_p) {
    const CsArg &cs_arg = cs_args[cs_a];
    const uint32_t cs_m = cs_group(cs_a), cs_es = cs_arg.esize * cs_m;
    uint64_t cs_n = (cs_arg.elems + 2 * (uint64_t)cs_arg.guard) / cs_m;
    cs_v.reset(new CsB[cs_n]());
    cs_size = cs_n;
    const unsigned char *cs_base = (const unsigned char *)cs_p - (uint64_t)cs_arg.guard * cs_arg.esize;
    for (uint64_t cs_e = 0; cs_e < cs_n; ++cs_e)
      CsElem<CsB>::cs_in(cs_a, &cs_v[cs_e], cs_base + cs_e * cs_es, cs_es);
  }
  void cs_back(int cs_a, void *cs_p) {
    const CsArg &cs_arg = cs_args[cs_a];
    const uint32_t cs_es = cs_arg.esize * cs_group(cs_a);
    unsigned char *cs_base = (unsigned char *)cs_p - (uint64_t)cs_arg.guard * cs_arg.esize;
    for (uint64_t cs_e = 0; cs_e < cs_size; ++cs_e)
      CsElem<CsB>::cs_out(cs_a, cs_base + cs_e * cs_es, &cs_v[cs_e], cs_es);
  }
  CsB *cs_first(int cs_a) { return cs_v.get() + cs_args[cs_a].guard / cs_group(cs_a); }
};
template <class CsT> struct CsBase {
  typedef typename std::remove_cv<typename std::remove_all_extents<CsT>::type>::type cs_type;
};
template <class CsA> struct CsConv {   // by value
  typedef typename std::remove_cv<CsA>::type CsB;
  int cs_a;
  CsB cs_val;
  explicit CsConv(int a) : cs_a(a) {}
  CsB cs_get(void *cs_p) {
    CsElem<CsB>::cs_in(cs_a, &cs_val, (const unsigned char *)cs_p, cs_args[cs_a].esize);
    return cs_val;
  }
  void cs_back(void *) {}
};
template <class CsP> struct CsConv<CsP *> {   // a pointer (an array parameter decays to one)
  typedef typename CsBase<CsP>::cs_type CsB;
  int cs_a;
  CsBuf<CsB> cs_buf;
  explicit CsConv(int a) : cs_a(a) {}
  CsP *cs_get(void *cs_p) { cs_buf.cs_fill(cs_a, cs_p); return reinterpret_cast<CsP *>(cs_buf.cs_first(cs_a)); }
  void cs_back(void *cs_p) { cs_buf.cs_back(cs_a, cs_p); }
};
template <class CsP> struct CsConv<CsP *const> : CsConv<CsP *> { explicit CsConv(int a) : CsConv<CsP *>(a) {} };
template <class CsT> struct CsConv<CsT &> {
  typedef typename CsBase<CsT>::cs_type CsB;
  int cs_a;
  CsBuf<CsB> cs_buf;
  explicit CsConv(int a) : cs_a(a) {}
  CsT &cs_get(void *cs_p) { cs_buf.cs_fill(cs_a, cs_p); return *reinterpret_cast<CsT *>(cs_buf.cs_first(cs_a)); }
  void cs_back(void *cs_p) { cs_buf.cs_back(cs_a, cs_p); }
};
template <class CsT> struct CsConv<CsT &&> {
  typedef typename CsBase<CsT>::cs_type CsB;
  int cs_a;
  CsBuf<CsB> cs_buf;
  explicit CsConv(int a) : cs_a(a) {}
  CsT &&cs_get(void *cs_p) {
    cs_buf.cs_fill(cs_a, cs_p);
    return static_cast<CsT &&>(*reinterpret_cast<CsT *>(cs_buf.cs_first(cs_a)));
  }
  void cs_back(void *cs_p) { cs_buf.cs_back(cs_a, cs_p); }
};
#ifdef X_HLS_STREAM_SIM_H
// a stream argument: the driver's tokens (keyed by cs_p) go into a real hls::stream before the call,
// whatever is left in it comes back after
template <class CsT, int CsD> struct CsConv<hls::stream<CsT, CsD> &> {
  int cs_a;
  hls::stream<CsT, CsD> cs_s;
  explicit CsConv(int a) : cs_a(a) {}
  hls::stream<CsT, CsD> &cs_get(void *cs_p) {
    const CsArg &cs_arg = cs_args[cs_a];
    std::vector<unsigned char> cs_raw(cs_arg.esize + 64, 0);
    while (cs_fifo_try_pop(cs_p, cs_raw.data(), cs_arg.esize)) {
      CsT cs_v;
      CsElem<CsT>::cs_in(cs_a, &cs_v, cs_raw.data(), cs_arg.esize);
      cs_s.write(cs_v);
    }
    return cs_s;
  }
  void cs_back(void *cs_p) {
    const CsArg &cs_arg = cs_args[cs_a];
    std::vector<unsigned char> cs_raw(cs_arg.esize + 64, 0);
    while (!cs_s.empty()) {
      CsT cs_v = cs_s.read();
      CsElem<CsT>::cs_out(cs_a, cs_raw.data(), &cs_v, cs_arg.esize);
      cs_fifo_push(cs_p, cs_raw.data(), cs_arg.esize);
    }
  }
};
#endif
#ifdef TAPA_XILINX_HLS_STREAM_H_
// TAPA (auto_ntt, OPEN_ISSUES O109): a tapa::istream<T> / ostream<T> holds hls::stream<
// tapa::internal::elem_t<T>> members (`_`, and `_peek` for an istream).  The driver's tokens for such
// an argument are keyed by the object's address (`_`'s in the MLIR) and laid out as the MLIR elem_t
// {iN val; i8 eot} (runs 0 and 1; plan_args fills eot with 0 / 1).
template <class CsT> inline uint64_t cs_tapa_bits(const CsT &cs_v, std::true_type) {
  return (uint64_t)cs_v.to_uint64();
}
template <class CsT> inline uint64_t cs_tapa_bits(const CsT &cs_v, std::false_type) {
  return (uint64_t)cs_v;
}
template <class CsT> inline void cs_tapa_check(int cs_a) {
  const CsArg &cs_arg = cs_args[cs_a];
  // a value wider than 64 bits only as an ap type (an ap_uint<512> data port, auto_ntt's async_mmap)
  // a float / double value is {f32 / f64 val, i8 eot} (W9 round 20 review defect 6)
  const bool cs_fp = std::is_floating_point<CsT>::value;
  const int cs_kind = !cs_fp ? 0 : (sizeof(CsT) == 4 ? 2 : (sizeof(CsT) == 8 ? 3 : -1));
  if (cs_arg.nruns != 2 || cs_arg.runs[0].kind != cs_kind || (cs_arg.runs[0].bits > 64 && CsAp<CsT>::cs_w <= 64) ||
      (CsAp<CsT>::cs_w && CsAp<CsT>::cs_w != cs_arg.runs[0].bits) ||
      (cs_fp && cs_arg.runs[0].bits != (int)(8 * sizeof(CsT))))
    cs_layout_fail(cs_a, "a TAPA token that is not {iN / f32 / f64 val, i8 eot} of the element's width");
}
// The value of a token: up to 64 bits one little-endian limb, wider (an ap type only) limb by limb as
// CsElem does for an array element.
template <class CsT> inline void cs_tapa_val_in(CsT &cs_d, const unsigned char *cs_s, int cs_bits,
                                                std::false_type) {
  if (std::is_floating_point<CsT>::value) {   // the IEEE bits as they are
    std::memcpy((void *)&cs_d, cs_s, sizeof(CsT));
    return;
  }
  uint64_t cs_limb = 0;
  std::memcpy(&cs_limb, cs_s, (cs_bits + 7) / 8);
  cs_d = (CsT)cs_limb;
}
template <class CsT> inline void cs_tapa_val_out(unsigned char *cs_d, const CsT &cs_s, int cs_bits,
                                                 std::false_type) {
  if (std::is_floating_point<CsT>::value) {
    std::memcpy(cs_d, (const void *)&cs_s, sizeof(CsT));
    return;
  }
  uint64_t cs_limb = cs_tapa_bits(cs_s, std::integral_constant<bool, (CsAp<CsT>::cs_w > 0)>());
  std::memcpy(cs_d, &cs_limb, (cs_bits + 7) / 8);
}
#ifdef __AP_COMMON_H__
template <class CsT> inline void cs_tapa_val_in(CsT &cs_d, const unsigned char *cs_s, int cs_bits,
                                                std::true_type) {
  enum { CsW = CsAp<CsT>::cs_w };
  const uint32_t cs_vb = (uint32_t)(cs_bits + 7) / 8;
  ap_int_base<CsW, false> cs_u = 0;
  for (int cs_l = (CsW + 63) / 64 - 1; cs_l >= 0; --cs_l) {
    uint64_t cs_limb = 0;
    std::memcpy(&cs_limb, cs_s + 8 * cs_l, cs_limb_bytes(cs_vb, cs_l));
    cs_u = (cs_u << 64) | ap_int_base<CsW, false>((unsigned long long)cs_limb);
  }
  ap_int_base<CsW, (bool)CsAp<CsT>::cs_s> cs_v = cs_u;
  cs_d.V = cs_v.V;
}
template <class CsT> inline void cs_tapa_val_out(unsigned char *cs_d, const CsT &cs_s, int cs_bits,
                                                 std::true_type) {
  enum { CsW = CsAp<CsT>::cs_w };
  const uint32_t cs_vb = (uint32_t)(cs_bits + 7) / 8;
  ap_int_base<CsW, (bool)CsAp<CsT>::cs_s> cs_v;
  cs_v.V = cs_s.V;
  ap_int_base<CsW, false> cs_u = cs_v;
  for (int cs_l = 0; cs_l < (CsW + 63) / 64; ++cs_l) {
    uint64_t cs_limb = ap_int_base<64, false>(cs_u >> (64 * cs_l)).to_uint64();
    std::memcpy(cs_d + 8 * cs_l, &cs_limb, cs_limb_bytes(cs_vb, cs_l));
  }
}
#endif
template <class CsT> inline void cs_tapa_in(int cs_a, tapa::internal::elem_t<CsT> *cs_d,
                                            const unsigned char *cs_s) {
  cs_tapa_check<CsT>(cs_a);
  const CsArg &cs_arg = cs_args[cs_a];
  cs_tapa_val_in(cs_d->val, cs_s, cs_arg.runs[0].bits, std::integral_constant<bool, (CsAp<CsT>::cs_w > 64)>());
  cs_d->eot = (cs_s[cs_arg.runs[1].off] & 1) != 0;
}
template <class CsT> inline void cs_tapa_out(int cs_a, unsigned char *cs_d,
                                             const tapa::internal::elem_t<CsT> *cs_s) {
  cs_tapa_check<CsT>(cs_a);
  const CsArg &cs_arg = cs_args[cs_a];
  std::memset(cs_d, 0, cs_arg.esize);
  cs_tapa_val_out(cs_d, cs_s->val, cs_arg.runs[0].bits, std::integral_constant<bool, (CsAp<CsT>::cs_w > 64)>());
  cs_d[cs_arg.runs[1].off] = cs_s->eot ? 1 : 0;
}
template <class CsS, class CsT> struct CsTapaConv {
  int cs_a;
  CsS cs_s;
  explicit CsTapaConv(int a) : cs_a(a) {}
  CsS &cs_get(void *cs_p) {
    std::vector<unsigned char> cs_raw(cs_args[cs_a].esize + 64, 0);
    while (cs_fifo_try_pop(cs_p, cs_raw.data(), cs_args[cs_a].esize)) {
      tapa::internal::elem_t<CsT> cs_v;
      cs_tapa_in<CsT>(cs_a, &cs_v, cs_raw.data());
      cs_s._.write(cs_v);
    }
    return cs_s;
  }
  void cs_back(void *cs_p) {
    std::vector<unsigned char> cs_raw(cs_args[cs_a].esize + 64, 0);
    while (!cs_s._.empty()) {
      tapa::internal::elem_t<CsT> cs_v = cs_s._.read();
      cs_tapa_out<CsT>(cs_a, cs_raw.data(), &cs_v);
      cs_fifo_push(cs_p, cs_raw.data(), cs_args[cs_a].esize);
    }
  }
};
// An array of TAPA streams, `tapa::istream<T> (&)[N]` (OPEN_ISSUES O157): stream i's tokens are keyed
// by the address of the MLIR's object i (cs_args' stream_stride apart).
template <class CsS, class CsT, std::size_t CsN> struct CsTapaArrayConv {
  int cs_a;
  CsS cs_s[CsN];
  explicit CsTapaArrayConv(int a) : cs_a(a) {
    if (cs_args[a].stream_count != CsN) cs_layout_fail(a, "an array of TAPA streams of another length");
  }
  void *cs_key(void *cs_p, std::size_t cs_i) {
    return (unsigned char *)cs_p + cs_i * cs_args[cs_a].stream_stride;
  }
  CsS (&cs_get(void *cs_p))[CsN] {
    std::vector<unsigned char> cs_raw(cs_args[cs_a].esize + 64, 0);
    for (std::size_t cs_i = 0; cs_i < CsN; ++cs_i)
      while (cs_fifo_try_pop(cs_key(cs_p, cs_i), cs_raw.data(), cs_args[cs_a].esize)) {
        tapa::internal::elem_t<CsT> cs_v;
        cs_tapa_in<CsT>(cs_a, &cs_v, cs_raw.data());
        cs_s[cs_i]._.write(cs_v);
      }
    return cs_s;
  }
  void cs_back(void *cs_p) {
    std::vector<unsigned char> cs_raw(cs_args[cs_a].esize + 64, 0);
    for (std::size_t cs_i = 0; cs_i < CsN; ++cs_i)
      while (!cs_s[cs_i]._.empty()) {
        tapa::internal::elem_t<CsT> cs_v = cs_s[cs_i]._.read();
        cs_tapa_out<CsT>(cs_a, cs_raw.data(), &cs_v);
        cs_fifo_push(cs_key(cs_p, cs_i), cs_raw.data(), cs_args[cs_a].esize);
      }
  }
};
template <class CsT, std::size_t CsN> struct CsConv<tapa::istream<CsT> (&)[CsN]>
    : CsTapaArrayConv<tapa::istream<CsT>, CsT, CsN> {
  explicit CsConv(int a) : CsTapaArrayConv<tapa::istream<CsT>, CsT, CsN>(a) {}
};
template <class CsT, std::size_t CsN> struct CsConv<tapa::ostream<CsT> (&)[CsN]>
    : CsTapaArrayConv<tapa::ostream<CsT>, CsT, CsN> {
  explicit CsConv(int a) : CsTapaArrayConv<tapa::ostream<CsT>, CsT, CsN>(a) {}
};
#ifdef TAPA_XILINX_HLS_MMAP_H_
// A TAPA memory port, `tapa::async_mmap<T>&` (OPEN_ISSUES O157): five member streams (read_addr,
// read_data, write_addr, write_data, write_resp) with three token types.  Each member is a driver
// entry of its own (cs_args' first_member + i), keyed by the member's offset in the MLIR struct; the
// driver fills every member with tokens like any stream argument (read_data's tokens are the memory's
// responses whatever the request addresses) and dumps what is left in each after the call.
template <class CsT> struct CsConv<tapa::async_mmap<CsT> &> {
  typedef typename tapa::async_mmap<CsT>::addr_t CsAddr;
  typedef typename tapa::async_mmap<CsT>::resp_t CsResp;
  int cs_a;
  tapa::async_mmap<CsT> cs_m;
  explicit CsConv(int a) : cs_a(a) {
    if (cs_args[a].nmembers != 5) cs_layout_fail(a, "a TAPA async_mmap that is not five member streams");
  }
  void *cs_key(void *cs_p, int cs_i) {
    return (unsigned char *)cs_p + cs_args[cs_args[cs_a].first_member + cs_i].key_off;
  }
  template <class CsE, class CsS> void cs_in1(void *cs_p, int cs_i, CsS &cs_s) {
    int cs_m1 = cs_args[cs_a].first_member + cs_i;
    std::vector<unsigned char> cs_raw(cs_args[cs_m1].esize + 64, 0);
    while (cs_fifo_try_pop(cs_key(cs_p, cs_i), cs_raw.data(), cs_args[cs_m1].esize)) {
      tapa::internal::elem_t<CsE> cs_v;
      cs_tapa_in<CsE>(cs_m1, &cs_v, cs_raw.data());
      cs_s._.write(cs_v);
    }
  }
  template <class CsE, class CsS> void cs_out1(void *cs_p, int cs_i, CsS &cs_s) {
    int cs_m1 = cs_args[cs_a].first_member + cs_i;
    std::vector<unsigned char> cs_raw(cs_args[cs_m1].esize + 64, 0);
    while (!cs_s._.empty()) {
      tapa::internal::elem_t<CsE> cs_v = cs_s._.read();
      cs_tapa_out<CsE>(cs_m1, cs_raw.data(), &cs_v);
      cs_fifo_push(cs_key(cs_p, cs_i), cs_raw.data(), cs_args[cs_m1].esize);
    }
  }
  tapa::async_mmap<CsT> &cs_get(void *cs_p) {
    cs_in1<CsAddr>(cs_p, 0, cs_m.read_addr);
    cs_in1<CsT>(cs_p, 1, cs_m.read_data);
    cs_in1<CsAddr>(cs_p, 2, cs_m.write_addr);
    cs_in1<CsT>(cs_p, 3, cs_m.write_data);
    cs_in1<CsResp>(cs_p, 4, cs_m.write_resp);
    return cs_m;
  }
  void cs_back(void *cs_p) {
    cs_out1<CsAddr>(cs_p, 0, cs_m.read_addr);
    cs_out1<CsT>(cs_p, 1, cs_m.read_data);
    cs_out1<CsAddr>(cs_p, 2, cs_m.write_addr);
    cs_out1<CsT>(cs_p, 3, cs_m.write_data);
    cs_out1<CsResp>(cs_p, 4, cs_m.write_resp);
  }
};
#endif
template <class CsT> struct CsConv<tapa::istream<CsT> &> : CsTapaConv<tapa::istream<CsT>, CsT> {
  explicit CsConv(int a) : CsTapaConv<tapa::istream<CsT>, CsT>(a) {}
};
template <class CsT> struct CsConv<tapa::ostream<CsT> &> : CsTapaConv<tapa::ostream<CsT>, CsT> {
  explicit CsConv(int a) : CsTapaConv<tapa::ostream<CsT>, CsT>(a) {}
};
#endif
template <std::size_t... CsI> struct CsSeq {};
template <std::size_t CsN, std::size_t... CsI> struct CsGen : CsGen<CsN - 1, CsN - 1, CsI...> {};
template <std::size_t... CsI> struct CsGen<0, CsI...> { typedef CsSeq<CsI...> cs_type; };
template <class CsR> struct CsRet {
  template <class CsF, class... CsX> static void cs_run(int cs_a, void *cs_rp, CsF cs_f, CsX &&...cs_x) {
    typedef typename std::remove_cv<CsR>::type CsB;
    CsB cs_r = cs_f(static_cast<CsX &&>(cs_x)...);
    CsElem<CsB>::cs_out(cs_a, (unsigned char *)cs_rp, &cs_r, cs_args[cs_a].esize);
  }
};
template <> struct CsRet<void> {
  template <class CsF, class... CsX> static void cs_run(int, void *, CsF cs_f, CsX &&...cs_x) {
    cs_f(static_cast<CsX &&>(cs_x)...);
  }
};
#ifdef X_HLS_STREAM_SIM_H
// A read of an empty C-simulation hls::stream blocks for ever (Vitis' own deadlock detector runs only
// under __HLS_COSIM__).  A watcher thread applies that detector's test, more blocked reads than running
// hls::tasks (hls_stream.h, stream_globals::check_deadlock), held for half a second, and ends the run
// at the read like the candidate's token FIFO does (cs_stop_at_blocking_read).  The counters are
// private: an explicit instantiation may name private members, which yields their addresses.
template <class CsTag, typename CsTag::cs_type CsM> struct CsRob {
  friend typename CsTag::cs_type cs_rob(CsTag) { return CsM; }
};
struct CsBlockedTag { typedef std::atomic<int> &(*cs_type)(); friend cs_type cs_rob(CsBlockedTag); };
struct CsTasksTag { typedef std::atomic<int> &(*cs_type)(); friend cs_type cs_rob(CsTasksTag); };
template struct CsRob<CsBlockedTag, &hls::stream_globals<false>::get_blocked_counter>;
template struct CsRob<CsTasksTag, &hls::stream_globals<false>::get_task_counter>;
inline void cs_block_watch() {
  int cs_n = 0;
  for (;;) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if (cs_rob(CsBlockedTag())().load() > cs_rob(CsTasksTag())().load()) {
      if (++cs_n >= 10) cs_stop_at_blocking_read();
    } else {
      cs_n = 0;
    }
  }
}
inline void cs_start_block_watch() {
  static bool cs_started = false;
  if (cs_started) return;
  cs_started = true;
  std::thread(cs_block_watch).detach();
}
#else
inline void cs_start_block_watch() {}
#endif
template <class CsR, class... CsA, std::size_t... CsI>
void cs_call_seq(CsR (*cs_f)(CsA...), void **cs_p, CsSeq<CsI...>) {
  std::tuple<CsConv<CsA>...> cs_conv(((int)CsI)...);   // in place: a stream cannot be copied
  // a blocking read ends the run inside the call: the dump written there needs every argument's state
  // copied back first (cs_block_hook, called by cs_stop_at_blocking_read)
  static std::tuple<CsConv<CsA>...> *cs_tp;
  static void **cs_pp;
  cs_tp = &cs_conv;
  cs_pp = cs_p;
  struct CsHook {
    static void cs_run() {
      int cs_d[] = {0, (std::get<CsI>(*cs_tp).cs_back(cs_pp[CsI]), 0)...};
      (void)cs_d;
    }
  };
  cs_block_hook = &CsHook::cs_run;
  cs_start_block_watch();
  CsRet<CsR>::cs_run((int)sizeof...(CsA), cs_p[sizeof...(CsA)], cs_f, std::get<CsI>(cs_conv).cs_get(cs_p[CsI])...);
  cs_block_hook = 0;
  int cs_done[] = {0, (std::get<CsI>(cs_conv).cs_back(cs_p[CsI]), 0)...};
  (void)cs_done;
}
template <class CsR, class... CsA> void cs_invoke(CsR (*cs_f)(CsA...), void **cs_p) {
  static_assert(sizeof...(CsA) == CS_NPARAMS, "cs: the C++ top and the MLIR top have different arity");
  static_assert(std::is_void<CsR>::value == (CS_HAS_RET == 0),
                "cs: the C++ top and the MLIR top differ in their result");
  cs_call_seq(cs_f, cs_p, typename CsGen<sizeof...(CsA)>::cs_type());
}
// an overloaded top: the overload with the parameter types of the MLIR top's mangled name
template <class... CsP> struct CsPick {
  template <class CsR> static CsR (*cs_get(CsR (*cs_f)(CsP...)))(CsP...) { return cs_f; }
};
// a value of type T in an unevaluated call (the result type of the top, by overload resolution)
template <class CsT> CsT cs_val();
}  // namespace cs_detail
#ifndef CS_TOP_FN
#define CS_TOP_FN &CS_TOP
#endif
extern "C" void cs_call(void **cs_p) { cs_detail::cs_invoke(CS_TOP_FN, cs_p); }
'''


def c_scalar_type(t):
    if t.k == "int":
        if t.bits == 1:
            return "bool"
        for b in (8, 16, 32, 64):
            if t.bits == b:
                return f"int{b}_t"
        return f"unsigned _BitInt({t.bits})"
    if t.k == "float":
        return {"f16": "_Float16", "f32": "float", "f64": "double", "f80": "long double"}.get(t.name)
    return None


STREAM_TOKENS = 4096        # tokens the driver puts into every hls::stream argument of the top per call


def split_cxx_method(dm):
    """('hls::stream<float, 0>', 'read()') of a demangled member function name, or (None, dm)."""
    depth, cut = 0, None
    for k, ch in enumerate(dm):
        if ch == "<":
            depth += 1
        elif ch == ">":
            depth -= 1
        elif ch == "(" and depth == 0:
            break
        elif dm.startswith("::", k) and depth == 0:
            cut = k
    if cut is None:
        return None, dm
    return dm[:cut], dm[cut + 2:]


def cxx_params(dm):
    """The parameter list of a demangled function name, split at depth 0."""
    depth, start = 0, None
    for k, ch in enumerate(dm):
        if ch in "<":
            depth += 1
        elif ch in ">":
            depth -= 1
        elif ch == "(" and depth == 0:
            start = k
            break
    if start is None:
        return []
    inner = dm[start + 1:dm.rindex(")")]
    return [x.strip() for x in split_top_level(inner)] if inner.strip() and inner.strip() != "void" else []


def stream_methods(text):
    """{mangled name: (class, method, (MLIR arg types, MLIR result types))} of every hls::stream member
    function the MLIR declares without a body (the shim declares them, cgeist emits calls)."""
    out = {}
    for name in sorted(set(re.findall(r"func\.func\s+private\s+@(_ZNK?3hls6stream\w+)\(", text))):
        cls, meth = split_cxx_method(demangle(name))
        sig = top_signature(text, name)
        if cls and sig:
            out[name] = (cls, meth, sig)
    return out


def stream_token_types(methods):
    """{'hls::stream<float, 0>': token MLIR type} from the methods that move a token."""
    tok = {}
    for cls, meth, (args, res) in methods.values():
        t = None
        if re.match(r"read\(\)", meth) and res:
            t = res[0]
        elif re.match(r"(read|write|read_nb|write_nb|operator<<|operator>>)\(.+\)", meth) and len(args) >= 2:
            mt = parse_type(args[1])
            if mt.k == "memref":
                t = mt.elem.text
        if t:
            tok.setdefault(cls, t)
    return tok


TAPA_TOKEN = "tapa:"   # prefix of a TAPA stream's token type in top_stream_args' result


TAPA_MMAP = "tapa_mmap"   # key of a TAPA async_mmap argument's member token types in top_stream_args' result
# The members of TAPA's kernel-side async_mmap<T> (tapa/xilinx/hls/mmap.h), in declaration order, with
# the token MLIR type of the address and response members (elem_t<int64_t> {i64 val; bool eot},
# elem_t<uint8_t> {i8 val; bool eot}); None: a data member, whose token is elem_t<T>.
TAPA_MMAP_MEMBERS = (("read_addr", "!llvm.struct<(i64, i8)>"), ("read_data", None),
                     ("write_addr", "!llvm.struct<(i64, i8)>"), ("write_data", None),
                     ("write_resp", "!llvm.struct<(i8, i8)>"))


def tapa_mmap_tokens(elem, nospace):
    """The token MLIR types of the five member streams of a `tapa::async_mmap<elem>&` argument
    (OPEN_ISSUES O157): an address or response member's fixed type, a data member's from the declared
    methods of hls::stream<tapa::internal::elem_t<elem>, 0> (None when there is none: the design never
    moves data tokens, so the driver gives those members none).  The fixed types are used even when a
    method is declared: cgeist flattens the homogeneous elem_t<uint8_t> {i8, i8} into memref<?x2xi8>,
    whose element (i8) is not the token (auto_ntt fwd_* write_resp.read_nb); the bytes are the same."""
    data = nospace.get(re.sub(r"\s+", "", f"hls::stream<tapa::internal::elem_t<{elem}>,0>"))
    return [fixed or data for _, fixed in TAPA_MMAP_MEMBERS]


def top_stream_args(top_fn, methods):
    """{argument index: token MLIR type} for the top's hls::stream parameters; ValueError when a stream
    parameter's token type is unknown (no declared method moves its tokens) or is an array of streams.
    A TAPA `tapa::istream<T>&` / `tapa::ostream<T>&` (auto_ntt, OPEN_ISSUES O109) is a stream whose
    tokens are the `hls::stream<tapa::internal::elem_t<T>>` member's {T val; bool eot}: its type
    carries the TAPA_TOKEN prefix (plan_args fills eot with 0 / 1)."""
    if not top_fn.startswith("_Z"):
        return {}
    params = cxx_params(demangle(top_fn))
    tok = stream_token_types(methods)
    nospace = {re.sub(r"\s+", "", c): t for c, t in tok.items()}
    out = {}
    for k, prm in enumerate(params):
        base = re.sub(r"\s*(&|\*|const)\s*$", "", prm).strip()
        base = re.sub(r"^const\s+", "", base)
        if base.startswith("tapa::istreams<") or base.startswith("tapa::ostreams<"):
            raise ValueError(f"argument {k}: an array of TAPA streams ({prm})")
        mm = re.fullmatch(r"tapa::async_mmap<(.*)>", base)
        if mm:
            if not prm.rstrip().endswith("&"):
                raise ValueError(f"argument {k}: a TAPA async_mmap not by reference ({prm})")
            out[k] = {TAPA_MMAP: tapa_mmap_tokens(mm.group(1), nospace)}
            continue
        # A reference to an array of TAPA streams, `tapa::istream<T> (&) [N]` (TAPA's kernel-side
        # istreams<T, N>; auto_ntt shuffler_*, OPEN_ISSUES O157): N streams, the MLIR argument a
        # memref of N stream objects; its token type carries the count (TAPA_TOKEN[N]).
        ma = re.fullmatch(r"(tapa::[io]stream<.*>)\s*\(&\)\s*\[(\d+)\]", prm.strip())
        if ma:
            inner = re.fullmatch(r"tapa::[io]stream<(.*)>", ma.group(1).strip())
            cls = re.sub(r"\s+", "", f"hls::stream<tapa::internal::elem_t<{inner.group(1)}>,0>")
            if cls not in nospace:
                raise ValueError(f"argument {k}: {ma.group(1)} with no token-moving method declared")
            out[k] = f"{TAPA_TOKEN[:-1]}[{ma.group(2)}]:" + nospace[cls]
            continue
        m = re.fullmatch(r"tapa::[io]stream<(.*)>", base)
        if m:
            if prm.rstrip().endswith("*") or re.search(r"\[\d*\]|\(\*\)", prm):
                raise ValueError(f"argument {k}: an array of TAPA streams ({prm})")
            cls = re.sub(r"\s+", "", f"hls::stream<tapa::internal::elem_t<{m.group(1)}>,0>")
            if cls not in nospace:
                raise ValueError(f"argument {k}: {base} with no token-moving method declared")
            out[k] = TAPA_TOKEN + nospace[cls]
            continue
        if not base.startswith("hls::stream<"):
            continue
        if prm.rstrip().endswith("*") or re.search(r"\[\d*\]|\(\*\)", prm):
            raise ValueError(f"argument {k}: an array of hls::stream ({prm})")
        if base not in tok:
            raise ValueError(f"argument {k}: {base} with no token-moving method declared")
        out[k] = tok[base]
    return out


def bool_params(top_fn):
    """The indices of the top's `bool` parameters (its mangled name; none for a C name)."""
    if not top_fn.startswith("_Z"):
        return set()
    return {k for k, p in enumerate(cxx_params(demangle(top_fn)))
            if re.sub(r"^const\s+", "", p.strip()) == "bool"}


def tapa_token_runs(k, tt):
    """The runs of a TAPA token {iN val; i8 eot} (or {f32 / f64 val; i8 eot}: a float / double stream,
    W9 round 20 review defect 6); the eot byte holds 0 or 1 (C++'s bool).  N may exceed 64 (the thunk
    accepts that for an ap type only: an ap_uint<512> data port)."""
    runs = leaf_runs(tt)
    if (len(runs) != 2 or runs[0][2] not in (0, KIND["f32"], KIND["f64"]) or runs[1][2] != 0
            or runs[1][1] != 8):
        raise ValueError(f"argument {k}: TAPA token {tt} is not {{iN, i8}} or {{f32 / f64, i8}}")
    runs[1][1] = 1
    return runs


def struct_field_offsets(t):
    """Byte offsets of the fields of an LLVM struct type (the layout of size_align)."""
    off, out = 0, []
    for f in t.fields:
        sz, al = size_align(f)
        if not t.packed:
            off = (off + al - 1) // al * al
        out.append(off)
        off += sz
    return out


def tapa_mmap_entry(k, s, t, toks):
    """The plan entry of a `tapa::async_mmap<T>&` argument (OPEN_ISSUES O157): a stream entry with no
    streams of its own (count 0) whose object is the MLIR struct of five stream objects, and one member
    stream entry per struct field, keyed by the field's offset (spec_entries places them after the
    plan).  A member with no known token type gets no tokens."""
    if t.k != "memref" or t.elem.k != "struct" or len(t.elem.fields) != len(TAPA_MMAP_MEMBERS):
        raise ValueError(f"argument {k}: a TAPA async_mmap as {s}")
    members = []
    for (name, _), off, tok in zip(TAPA_MMAP_MEMBERS, struct_field_offsets(t.elem), toks):
        tt = parse_type(tok or "!llvm.struct<(i8, i8)>")
        esize, _ = size_align(tt)
        members.append(dict(kind="stream", type=f"{s}.{name}", ty=tt, dims=[1], esize=esize,
                            runs=tapa_token_runs(k, tt), elems=STREAM_TOKENS if tok else 0, guard=0,
                            scalar=False, ret=False, count=1, stride=0, key_off=off))
    return dict(kind="stream", type=s, ty=t.elem, dims=[1] * len(t.dims), esize=1, runs=[[0, 8, 0, 1, 0]],
                elems=0, guard=0, scalar=False, ret=False, count=0, stride=size_align(t.elem)[0],
                members=members)


def spec_entries(plan):
    """The driver's argument entries: the plan (one per wrapper argument, the result last), then the
    member streams of every aggregate of streams with their parent's index."""
    out = [dict(p) for p in plan]
    for a, p in enumerate(plan):
        if p.get("members"):
            out[a]["first_member"] = len(out)
            for m in p["members"]:
                out.append(dict(m, parent=a))
    return out


def plan_args(arg_types, res_types, streams=None, dyn_scale=1, bools=()):
    """The driver's view of the top: one entry per wrapper argument.  streams: {argument index: token
    MLIR type} of the top's hls::stream arguments (top_stream_args).  dyn_scale multiplies the leading
    '?' dimension sizes (the retry of a heap-buffer-overflow, Checker._check)."""
    streams = streams or {}
    plan = []
    for k, s in enumerate(arg_types):
        t = parse_type(s)
        if k in streams and isinstance(streams[k], dict):
            plan.append(tapa_mmap_entry(k, s, t, streams[k][TAPA_MMAP]))
        elif k in streams:
            if t.k != "memref":
                raise ValueError(f"argument {k}: hls::stream as {s}")
            mcount = re.match(r"tapa\[(\d+)\]:", streams[k])
            count = int(mcount.group(1)) if mcount else 1
            tapa = streams[k].startswith(TAPA_TOKEN) or bool(mcount)
            tok_s = streams[k][mcount.end():] if mcount else (streams[k][len(TAPA_TOKEN):] if tapa else streams[k])
            tt = parse_type(tok_s)
            esize, _ = size_align(tt)
            runs = leaf_runs(tt)
            if tapa:
                # {T val; bool eot}: the eot byte holds 0 or 1 (C++'s bool, the i1 a load truncates to)
                if (len(runs) != 2 or runs[0][2] not in (0, KIND["f32"], KIND["f64"]) or runs[0][1] > 64
                        or runs[1][2] != 0 or runs[1][1] != 8):
                    raise ValueError(f"argument {k}: TAPA token {tt} is not {{iN, i8}} or {{f32 / f64, i8}}")
                runs[1][1] = 1
            dims, stride = [1] * len(t.dims), 0
            if count > 1:
                # an array of N stream objects: the memref's own shape; stream i is keyed by the address
                # of object i (its first member, `_`), `stride` bytes after object i - 1
                if not t.dims or t.dims[0] != count or any(d is None for d in t.dims):
                    raise ValueError(f"argument {k}: {count} TAPA streams as {s}")
                dims = list(t.dims)
                inner = 1
                for d in dims[1:]:
                    inner *= d
                stride = size_align(t.elem)[0] * inner
            plan.append(dict(kind="stream", type=s, ty=tt, dims=dims, esize=esize, runs=runs,
                             elems=STREAM_TOKENS * count, guard=0, scalar=False, ret=False,
                             count=count, stride=stride))
        elif t.k == "memref":
            if t.layout and not re.fullmatch(r"strided<\[(\?, )*1\](, offset: \?)?>|strided<\[1\]>", t.layout):
                raise ValueError(f"argument {k}: memref layout {t.layout}")
            dims = []
            for i, d in enumerate(t.dims):
                if d is None:
                    d = ((DYN_LEADING if len(t.dims) == 1 else DYN_LEADING_ND) * dyn_scale if i == 0
                         else DYN_INNER)
                dims.append(d)
            esize, _ = size_align(t.elem)
            runs = leaf_runs(t.elem)
            elems = 1
            for d in dims:
                elems *= d
            if not t.dims:
                raise ValueError(f"argument {k}: rank-0 memref")
            guard = max(1, GUARD_BYTES // max(1, esize))
            plan.append(dict(kind="memref", type=s, ty=t, dims=dims, esize=esize, runs=runs, elems=elems,
                             guard=guard, scalar=False, ret=False))
        elif t.k in ("int", "float", "struct", "array"):
            esize, _ = size_align(t)
            runs = leaf_runs(t)
            if k in bools and t.k == "int":
                # a C++ bool passed as i8 holds 0 or 1 (any other byte is not a bool value)
                runs[0][1] = 1
            plan.append(dict(kind="scalar", type=s, ty=t, dims=[1], esize=esize, runs=runs, elems=1,
                             guard=0, scalar=True, ret=False))
        else:
            raise ValueError(f"argument {k}: type {s}")
    if len(res_types) > 1:
        raise ValueError("several results")
    for s in res_types:
        t = parse_type(s)
        if t.k not in ("int", "float", "struct", "array"):
            raise ValueError(f"result type {s}")
        esize, _ = size_align(t)
        plan.append(dict(kind="ret", type=s, ty=t, dims=[1], esize=esize, runs=leaf_runs(t), elems=1, guard=0,
                         scalar=True, ret=True))
    total = sum((p["elems"] + 2 * p["guard"]) * p["esize"] for p in plan)
    if total > MAX_BUFFER_BYTES:
        raise ValueError(f"argument buffers need {total} bytes")
    return plan


def square_dims(p):
    """(rows, cols) of an array argument whose last two dimensions are equal (a square matrix, or a
    batch of them), else (0, 0): the driver's `diag` mode fills its diagonal."""
    dims = p.get("dims") or []
    if p.get("kind") == "stream" or p.get("scalar") or len(dims) < 2:
        return 0, 0
    r, c = dims[-2], dims[-1]
    if not isinstance(r, int) or not isinstance(c, int) or r != c or r < 2:
        return 0, 0
    return r, c


# Valid-graph inputs (mode `graph-*`, the input-domain retry `graph`; W9r21 review finding 1-3).  Graph
# designs (GNN inference over a batch of molecules, message passing, graph analytics) take a graph as a
# COO edge list, an array of (source, destination) integer pairs, together with integer node and edge
# counts: a scalar for one graph, or one count per graph in an array for a batch, with the graphs'
# edges concatenated.  The source requires that every endpoint is below its graph's node count, that the
# counts stay within the arrays, and often that no node has degree 0 (a mean or a log-degree scaler divides
# by it) and that the list is symmetric (an undirected graph).  Random integers break all of these, so the
# reference indexes past its tables or divides by zero on every run, and the design gets no verdict.
# graph_role recognises the shapes from the argument types alone, no names:
#   1  count: an integer scalar, or a rank-1 array of one integer lane per element;
#   2  edge list: an array whose last dimension is 2, of one integer lane per element (`int e[N][2]`);
#   3  edge list: an array whose element holds exactly two integer lanes (`struct {int u, v;}`,
#      `std::array<int, 2>`);
#   4  index: the integer lanes of any other array (a node's categorical features, which index embedding
#      tables): 0 or 1, in range of any table with two or more rows;
# where an integer lane is one of at least GRAPH_INDEX_BITS bits: C's int, long and size_t, the types of
# every count and index argument in the catalogue's graph designs; narrower lanes (ap_fixed<16, 6> weights
# and features, char flags, bools) are data and keep their mode's fill.  The driver then writes graphs
# that satisfy every requirement above at once (cs_graph_edges).  The recognition need not be right for
# every design: the mode is only a retry for a design with no verdict under the random fill, a run counts
# only when the reference is free of sanitizer reports and returns, and any such input is evidence of
# bit-exactness. Not covered: an edge list as two separate arrays of sources and destinations (they look like
# count arrays) and CSR (its monotone row pointer is the `index` mode's domain).
GRAPH_INDEX_BITS = 32
GRAPH_MODES = ("graph-small", "graph-wide", "graph-pos")


def graph_role(p):
    """The argument's role in the `graph-*` modes (see GRAPH_INDEX_BITS): 0 none, 1 count, 2 edge list
    (last dimension 2), 3 edge list (two lanes an element), 4 other index lanes."""
    if p.get("kind") == "stream" or p.get("ret"):
        return 0
    runs = p["runs"]
    lanes = sum(r[3] for r in runs)
    index = [r for r in runs if r[2] == 0 and r[1] >= GRAPH_INDEX_BITS]
    if not index:
        return 0
    only_index = len(index) == len(runs)
    if p.get("scalar"):
        return 1 if only_index and lanes == 1 else 0
    dims = p.get("dims") or []
    if only_index and lanes == 1 and len(dims) == 1:
        return 1
    if only_index and lanes == 1 and len(dims) >= 2 and dims[-1] == 2:
        return 2
    if only_index and lanes == 2:
        return 3
    return 4


def graph_shaped(plan):
    """Whether the plan has an edge list and a count (the `graph` retry applies)."""
    roles = {graph_role(p) for p in plan}
    return 1 in roles and bool(roles & {2, 3})


def spec_header(plan):
    out = [SPEC_HEAD]
    plan = spec_entries(plan)
    for a, p in enumerate(plan):
        runs = ", ".join("{%d, %d, %d, %d, %d}" % tuple(r) for r in p["runs"])
        out.append(f"static const CsRun cs_runs{a}[] = {{{runs}}};")
    out.append(f"#define CS_NARGS {len(plan)}")
    out.append(f"#define CS_GRAPH_INDEX_BITS {GRAPH_INDEX_BITS}")
    rows = ", ".join("{%dULL, %d, %d, %d, %d, %d, cs_runs%d, %d, %d, %d, %dULL, %dULL, %d, %d, %d, %d, %d}" % (
        p["elems"], p["esize"], p["guard"], int(p["scalar"]), int(p["ret"]), len(p["runs"]), a,
        int(p["kind"] == "stream"), p.get("count", 1), p.get("stride", 0), *square_dims(p),
        p.get("parent", -1), p.get("key_off", 0), p.get("first_member", -1), len(p.get("members", ())),
        graph_role(p))
        for a, p in enumerate(plan))
    out.append(f"static const CsArg cs_args[CS_NARGS] = {{{rows}}};")
    return "\n".join(out) + "\n"


GLOBAL_INIT = re.compile(r"func\.func @([\w.$-]+)\(\) attributes \{[^\n]*?hls\.global_init = (-?\d+)")


def global_inits(text):
    """The dynamic-initialization functions cgeist emitted (`hls.global_init`, a global whose initializer
    is not a constant and did not fold), in declaration order: C++ runs them before main."""
    return [f for f, _ in sorted(GLOBAL_INIT.findall(text), key=lambda m: int(m[1]))]


def wrapper_mlir(top_fn, plan, inits=()):
    """func.func @cs_entry: every argument a memref; scalars / the result go through memref<1xT>.  The
    dynamic-initialization functions `inits` run once, before the first call."""
    params, call_args, call_types, body = [], [], [], ["    %cs_c0 = arith.constant 0 : index"]
    pre = ""
    if inits:
        pre = '  memref.global "private" @cs_inited : memref<1xi1> = dense<false>\n'
        body += ["    %cs_ig = memref.get_global @cs_inited : memref<1xi1>",
                 "    %cs_iv = memref.load %cs_ig[%cs_c0] : memref<1xi1>",
                 "    %cs_true = arith.constant true",
                 "    %cs_in = arith.xori %cs_iv, %cs_true : i1",
                 "    scf.if %cs_in {"]
        body += [f"      func.call @{f}() : () -> ()" for f in inits]
        body += ["      memref.store %cs_true, %cs_ig[%cs_c0] : memref<1xi1>", "    }"]
    ret = None
    for a, p in enumerate(plan):
        if p["kind"] in ("memref", "stream"):
            params.append(f"%cs{a}: {p['type']}")
            call_args.append(f"%cs{a}")
            call_types.append(p["type"])
        elif p["kind"] == "scalar":
            params.append(f"%cs{a}: memref<1x{p['type']}>")
            body.append(f"    %cs_v{a} = memref.load %cs{a}[%cs_c0] : memref<1x{p['type']}>")
            call_args.append(f"%cs_v{a}")
            call_types.append(p["type"])
        else:
            params.append(f"%cs{a}: memref<1x{p['type']}>")
            ret = (a, p["type"])
    rt = f" -> {ret[1]}" if ret else " -> ()"
    res = "%cs_r = " if ret else ""
    body.append(f"    {res}func.call @{top_fn}({', '.join(call_args)}) : ({', '.join(call_types)}){rt}")
    if ret:
        body.append(f"    memref.store %cs_r, %cs{ret[0]}[%cs_c0] : memref<1x{ret[1]}>")
    body.append("    return")
    return pre + ("  func.func @cs_entry(" + ", ".join(params) + ") {\n" + "\n".join(body) + "\n  }\n")


def cand_thunk(plan, abi="descriptor"):
    proto, args = [], []
    for a, p in enumerate(plan):
        if abi == "bare":
            proto.append("void *")
            args.append(f"p[{a}]")
            continue
        dims = p["dims"] if p["kind"] in ("memref", "stream") else [1]
        r = len(dims)
        strides, s = [], 1
        for d in reversed(dims):
            strides.insert(0, s)
            s *= d
        proto += ["void *", "void *", "int64_t"] + ["int64_t"] * (2 * r)
        args += [f"p[{a}]", f"p[{a}]", "0"] + [str(d) for d in dims] + [str(x) for x in strides]
    return ("#include <cstdint>\n"
            f"extern \"C\" void cs_entry({', '.join(proto)});\n"
            f"extern \"C\" void cs_call(void **p) {{ cs_entry({', '.join(args)}); }}\n")


# The result type may be a nested struct (`{ { [2 x { { float, float } }] } }`: a read() of an
# hls::vector<std::complex<float>, 2>), hence the greedy brace group on one line.
LL_DECLARE = re.compile(r"^declare\s+(?:[\w.]+\s+)*?(\{.*\}|\S+)\s+@(_ZNK?3hls6stream\w+)\((.*)\)", re.M)


def _llvm_param_groups(mlir_args):
    """How many LLVM parameters each MLIR argument becomes (a rank-r memref: its descriptor, 3 + 2r)."""
    groups = []
    for s in mlir_args:
        t = parse_type(s)
        groups.append(3 + 2 * len(t.dims) if t.k == "memref" else 1)
    return groups


def cand_stream_runtime(text, ll_text):
    """LLVM IR defining every hls::stream method cand.ll declares, on the driver's token FIFOs (keyed by
    the object's address), or raises ValueError naming the method it cannot define."""
    methods = stream_methods(text)
    out = ["declare void @cs_fifo_reset(ptr)", "declare void @cs_fifo_push(ptr, ptr, i32)",
           "declare i32 @cs_fifo_try_pop(ptr, ptr, i32)", "declare void @cs_fifo_pop(ptr, ptr, i32)",
           "declare i64 @cs_fifo_size(ptr)", ""]
    for m in LL_DECLARE.finditer(ll_text):
        ret, name, params = m.group(1), m.group(2), m.group(3)
        if name not in methods:
            raise ValueError(f"no MLIR declaration of {name}")
        cls, meth, (margs, mres) = methods[name]
        ptys = [x.strip() for x in split_top_level(params)] if params.strip() else []
        groups = _llvm_param_groups(margs)
        if sum(groups) != len(ptys):
            raise ValueError(f"{name}: {len(ptys)} LLVM parameters for MLIR {margs}")
        body, k = [], 0
        addrs = []
        for gi, (g, s) in enumerate(zip(groups, margs)):
            t = parse_type(s)
            if t.k == "memref":
                es, _ = size_align(t.elem)
                body.append(f"  %o{gi} = mul i64 %p{k + 2}, {es}")
                body.append(f"  %a{gi} = getelementptr i8, ptr %p{k + 1}, i64 %o{gi}")
                # a token is one row of the memref: cgeist passes a struct token of N equal members as
                # memref<?xNxT> (flowgnn gat's stream<node_t>, node_t = {int nd; int degree;}: memref<?x2xi32>,
                # 8 bytes, not 4; W9r21-graph)
                row = es
                for d in t.dims[1:]:
                    if d is None:
                        raise ValueError(f"{name}: token memref {s} with a dynamic inner dimension")
                    row *= d
                addrs.append((f"%a{gi}", row))
            else:
                addrs.append((f"%p{k}", 0))
            k += g
        this = addrs[0][0] if addrs else None
        mname = meth.split("(")[0]
        data = addrs[1] if len(addrs) > 1 else None
        if mname in ("stream", "~stream"):
            if mname == "stream":
                body.append(f"  call void @cs_fifo_reset(ptr {this})")
            body.append("  ret void")
        elif mname == "read" and not data:
            if not mres:
                raise ValueError(f"{name}: read() without a result")
            n, _ = size_align(parse_type(mres[0]))
            body += [f"  %b = alloca {ret}, align 16", f"  call void @cs_fifo_pop(ptr {this}, ptr %b, i32 {n})",
                     f"  %v = load {ret}, ptr %b", f"  ret {ret} %v"]
        elif mname in ("read", "operator>>") and data:
            body += [f"  call void @cs_fifo_pop(ptr {this}, ptr {data[0]}, i32 {data[1]})", "  ret void"]
        elif mname == "read_nb" and data:
            body += [f"  %r = call i32 @cs_fifo_try_pop(ptr {this}, ptr {data[0]}, i32 {data[1]})",
                     "  %c = icmp ne i32 %r, 0"] + _ret_bool(ret)
        elif mname in ("write", "operator<<", "write_nb") and data:
            body.append(f"  call void @cs_fifo_push(ptr {this}, ptr {data[0]}, i32 {data[1]})")
            body += (["  %c = icmp eq i32 0, 0"] + _ret_bool(ret)) if mname == "write_nb" else ["  ret void"]
        elif mname in ("empty", "full"):
            body += [f"  %s = call i64 @cs_fifo_size(ptr {this})",
                     f"  %c = icmp {'eq' if mname == 'empty' else 'ne'} i64 %s, " +
                     ("0" if mname == "empty" else "-1")] + _ret_bool(ret)
        elif mname == "size":
            body.append(f"  %s = call i64 @cs_fifo_size(ptr {this})")
            if ret == "i64":
                body.append("  ret i64 %s")
            else:
                body += [f"  %t = trunc i64 %s to {ret}", f"  ret {ret} %t"]
        else:
            raise ValueError(f"hls::stream method {meth} has no token-FIFO model")
        sig = ", ".join(f"{ty} %p{i}" for i, ty in enumerate(ptys))
        out.append(f"define {ret} @{name}({sig}) {{\nentry:\n" + "\n".join(body) + "\n}\n")
    return "\n".join(out)


def _ret_bool(ret):
    """Return the i1 %c as the method's LLVM result type (i1, or a wider integer)."""
    if ret == "i1":
        return ["  ret i1 %c"]
    if ret == "void":
        return ["  ret void"]
    return [f"  %z = zext i1 %c to {ret}", f"  ret {ret} %z"]


def ref_thunk_c(top_fn, plan):
    """Thunk for a top defined in C: a prototype from the MLIR types."""
    proto, args, ret = [], [], None
    for a, p in enumerate(plan):
        if p["kind"] == "memref":
            proto.append("void *")
            args.append(f"p[{a}]")
        elif p["kind"] == "scalar":
            ct = c_scalar_type(p["ty"])
            if not ct:
                raise ValueError(f"C top with a {p['type']} argument")
            proto.append(ct)
            args.append(f"*({ct} *)p[{a}]")
        else:
            ct = c_scalar_type(p["ty"])
            if not ct:
                raise ValueError(f"C top returning {p['type']}")
            ret = (a, ct)
    rt = ret[1] if ret else "void"
    call = f"{top_fn}({', '.join(args)})"
    if ret:
        call = f"*({ret[1]} *)p[{ret[0]}] = {call}"
    return ("#include <cstdint>\n"
            f"extern \"C\" {rt} {top_fn}({', '.join(proto)});\n"
            f"extern \"C\" void cs_call(void **p) {{ {call}; }}\n")


# ----------------------------------------------------------------------------------- execution --

def run(cmd, cwd=None, timeout=600, env=None):
    t0 = time.time()
    try:
        # The compile steps get the memory cap; the ASan executables below cannot (their shadow
        # memory is a multi-terabyte private mapping that RLIMIT_DATA counts).
        p = subprocess.run(C.mem_limited(cmd), cwd=cwd, capture_output=True, text=True, errors="replace",
                           timeout=timeout, env=env)
        return p.returncode, p.stdout, p.stderr, time.time() - t0
    except subprocess.TimeoutExpired:
        return "timeout", "", "", time.time() - t0


def _raise_stack():
    try:
        soft, hard = resource.getrlimit(resource.RLIMIT_STACK)
        want = 1 << 30
        if hard != resource.RLIM_INFINITY:
            want = min(want, hard)
        resource.setrlimit(resource.RLIMIT_STACK, (want, hard))
    except (ValueError, OSError):
        pass


def run_exe(exe, mode, seed, calls, out, timeout, env=None):
    t0 = time.time()
    e = dict(os.environ)
    e.update(env or {})
    try:
        # ASLR off: the clang 14 ASan runtime crashes at random under this kernel's mmap randomisation
        # (1 run in 6 of polybench/bicg; 0 in 30 with setarch -R)
        p = subprocess.run(["setarch", "x86_64", "-R", str(exe), str(mode), str(seed), str(calls), str(out)],
                           capture_output=True, timeout=timeout, env=e, preexec_fn=_raise_stack)
        # stderr, then the end of stdout (Vitis' C-simulation hls::stream reports there)
        err = p.stderr.decode(errors="replace") + "\n" + p.stdout[-4000:].decode(errors="replace")
        return p.returncode, err, time.time() - t0
    except subprocess.TimeoutExpired:
        return "timeout", "", time.time() - t0


def first_err(text, n=300):
    """The first error line, without the directory part of its file name."""
    pick = None
    for line in text.splitlines():
        if "error" in line.lower():
            pick = line
            break
    if pick is None:
        lines = [x for x in text.splitlines() if x.strip()]
        pick = lines[-1] if lines else ""
    return re.sub(r"(?<![\w.])/[^\s:]*/([^/\s:]+:)", r"\1", pick.strip())[:n]


def dump_layout(plan):
    """Byte length of one call's dump per fixed-size argument (the driver's cs_dump order; stream
    arguments come after them, with a variable length)."""
    per = []
    for p in plan:
        if p["kind"] == "stream":
            per.append(None)
            continue
        per.append(token_bytes(p) * (p["elems"] + 2 * p["guard"]))
    return per


def token_bytes(p):
    """Dump bytes of one element (or token) of plan entry p."""
    b = 0
    for r in p["runs"]:
        if r[2] == 5:
            continue
        b += (10 if r[2] == 6 else (r[1] + 7) // 8) * r[3]
    return b


def differing_bytes(a, b, chunk=4096):
    """The positions at which two byte strings of one length differ (compared a chunk at a time, so that
    long equal stretches cost one comparison each)."""
    out = []
    for lo in range(0, len(a), chunk):
        if a[lo:lo + chunk] != b[lo:lo + chunk]:
            out.extend(i for i in range(lo, min(lo + chunk, len(a))) if a[i] != b[i])
    return out


def first_diff(a, b, plan):
    """Where two dumps first differ: call, argument, element (negative: in the front guard) and the
    bytes of that element, or for a stream argument the token counts and the first differing token."""
    per = dump_layout(plan)
    pa = pb = 0
    call = 0
    while pa < len(a) and pb < len(b):
        pa += 4
        pb += 4
        for ai, ln in enumerate(per):
            if ln is None:
                continue
            if a[pa:pa + ln] != b[pb:pb + ln]:
                p = plan[ai]
                eb = max(1, token_bytes(p))
                k = next(i for i in range(ln) if pa + i >= len(a) or pb + i >= len(b) or a[pa + i] != b[pb + i])
                e = k // eb - p["guard"]
                where = "front guard" if e < 0 else ("back guard" if e >= p["elems"] else "element")
                s0 = (k // eb) * eb
                return dict(call=call, arg=ai, elem=e, where=where, arg_type=p["type"],
                            ref=a[pa + s0:pa + s0 + eb][:32].hex(), cand=b[pb + s0:pb + s0 + eb][:32].hex(),
                            lengths=[len(a), len(b)])
            pa += ln
            pb += ln
        for ai, p in enumerate(spec_entries(plan)):
            if p["kind"] != "stream":
                continue
            for si in range(p.get("count", 1)):
                na = int.from_bytes(a[pa:pa + 8], "little")
                nb = int.from_bytes(b[pb:pb + 8], "little")
                eb = token_bytes(p)
                ta, tb = a[pa + 8:pa + 8 + na * eb], b[pb + 8:pb + 8 + nb * eb]
                if na != nb or ta != tb:
                    t = next((i // eb for i in range(min(len(ta), len(tb))) if ta[i] != tb[i]), min(na, nb))
                    d = dict(call=call, arg=ai, where="stream", arg_type=p["type"], tokens=[na, nb], token=t,
                             ref=ta[t * eb:(t + 1) * eb].hex(), cand=tb[t * eb:(t + 1) * eb].hex())
                    if p.get("count", 1) > 1:
                        d["stream"] = si
                    return d
                pa += 8 + na * eb
                pb += 8 + nb * eb
        call += 1
    return dict(call=call, lengths=[len(a), len(b)])


def _f32_nan(word):
    return (word & 0x7F800000) == 0x7F800000 and (word & 0x007FFFFF) != 0


def nan_lane_only_diff(a, b, plan):
    """True when two dumps of equal length differ only in 32-bit lanes of wide integer leaves (at least
    64 bits, a multiple of 32) where both lanes are float NaNs.  A design that packs floats into an
    ap_uint<512> stores the NaN its arithmetic made, and C leaves a NaN's sign and payload unspecified
    (W9 round 8 review defect 7: neuro_monarchs symbolic kernel, ref 0xffc00000 against cand 0x7fe87ad9,
    both NaN).  Any other difference, a difference in a stream argument, or dumps of different
    lengths: False."""
    if len(a) != len(b) or a == b:
        return False
    per = dump_layout(plan)
    if any(ln is None for ln in per):
        return False
    pos = 0
    while pos < len(a):
        if a[pos:pos + 4] != b[pos:pos + 4]:
            return False
        pos += 4
        for ai, ln in enumerate(per):
            seg_a, seg_b = a[pos:pos + ln], b[pos:pos + ln]
            if seg_a != seg_b:
                p = plan[ai]
                eb = token_bytes(p)
                for e in range(0, ln, max(1, eb)):
                    if seg_a[e:e + eb] == seg_b[e:e + eb]:
                        continue
                    off = e
                    for r in p["runs"]:
                        if r[2] == 5:
                            continue
                        nb = 10 if r[2] == 6 else (r[1] + 7) // 8
                        for _ in range(r[3]):
                            la, lb = seg_a[off:off + nb], seg_b[off:off + nb]
                            if la != lb:
                                if r[2] != 0 or r[1] < 64 or r[1] % 32:
                                    return False
                                for q in range(0, nb, 4):
                                    wa = int.from_bytes(la[q:q + 4], "little")
                                    wb = int.from_bytes(lb[q:q + 4], "little")
                                    if wa != wb and not (_f32_nan(wa) and _f32_nan(wb)):
                                        return False
                            off += nb
            pos += ln
    return True


def input_retry(runs, valid, done, modes):
    """The input-domain retry mode (INPUT_RETRIES) for a reference with no valid run whose every run
    failed for that retry's reason, or None (one retry per design)."""
    if valid or done is not None or not runs:
        return None
    whys = [r.get("why", "") for r in runs]
    for mode, key in INPUT_RETRIES:
        if mode not in modes.split(",") and all(key in w for w in whys):
            return mode
    return None


STUB_CALLED = re.compile(r"cs-stub: (\S+) called")
ASAN_ENV = {"ASAN_OPTIONS": "detect_leaks=0:exitcode=86:detect_stack_use_after_return=0"}
LAYOUT_EXIT = 87            # REF_THUNK_REAL's exit code when an argument cannot be converted
BLOCKED_READ_EXIT = 88      # the driver's exit code at a blocking read of an empty stream (cs_stop_at_blocking_read)
MODE_INDEX = {"small": 0, "wide": 1, "pos": 2, "diag": 3, "align": 4, "index": 5,
              "graph-small": 6, "graph-wide": 7, "graph-pos": 8}
# Input-domain retries (OPEN_ISSUES O142): when no run of the default modes is valid because the
# reference divides by zero on every input (`diag`: a diagonally dominant square matrix, the domain of
# a decomposition such as polybench cholesky in fixed point) or aborts on an assertion of the source
# (`align`: scalar integers that are multiples of 64, the usual `size % N == 0` precondition), the runs
# are repeated once in that mode; the verdict's reason names the retry. A reference whose every run
# makes an out-of-bounds access, or times out (twice, the limit of one design), is retried in mode
# `index` (integer arrays hold their own positions: monotone, in-range index arrays such as a CSR row
# pointer and its column indices; class_ece8893 connor_talley / max_beaulieu lab 3, whose random row
# pointers index past their rows or loop over unbounded ranges, OPEN_ISSUES O142).
INPUT_RETRIES = (("diag", "AddressSanitizer: FPE"), ("align", "assertion"),
                 ("index", "AddressSanitizer"), ("index", "reference exit timeout"))


# The exactclass shim's math-core markers (shim/exactclass/cgeist_flags): with this macro its
# fixed-point math functions call __hlsest_math_<name>(args..., W, I, S) declarations instead of the
# libm builtins, for hls-est's math-costs; a native build compiles the builtins instead.
MATH_MARKER_DEFINE = "HLSEST_MATH_MARKERS"


def drop_define(flags, name):
    """`flags` without -D<name> / -D <name>."""
    out, k = [], 0
    while k < len(flags):
        if flags[k] == "-D" and k + 1 < len(flags) and flags[k + 1] == name:
            k += 2
            continue
        if flags[k] == "-D" + name:
            k += 1
            continue
        out.append(flags[k])
        k += 1
    return out


# Each marker returns the value of the builtin it stands for (shim/exactclass/hls_math.h HLSEST_M1 /
# HLSEST_M2): the hls:: name, except where the shim computes the function from another builtin.
MATH_MARKER_BUILTIN = {"rsqrt": "sqrt", "sinpi": "sin", "cospi": "cos"}
LL_MATH_MARKER = re.compile(r"^declare\s+double\s+@__hlsest_math_(\w+)\(([^)]*)\)", re.M)


def undefined_symbol_stubs(names, ll_text):
    """(LLVM IR defining the undefined data globals zero-initialised, C defining the undefined functions as
    stubs that abort) for the link of the candidate; None when a name is neither."""
    types = "\n".join(l for l in ll_text.splitlines() if re.match(r"%[\w.\"]+ = type ", l))
    globs, funcs = [], []
    for n in names:
        m = re.search(r"(?m)^@" + re.escape(n) + r" = external (?:dso_local )?global (.+?)(?:, align \d+)?$",
                      ll_text)
        if m:
            globs.append(f"@{n} = weak global {m.group(1)} zeroinitializer")
        elif re.search(r"(?m)^declare [^@]*@" + re.escape(n) + r"\(", ll_text) and re.fullmatch(r"\w+", n):
            funcs.append(n)
        else:
            return None
    ll = (types + "\n" + "\n".join(globs) + "\n") if globs else ""
    # a stub names itself on stderr before it aborts, so a run that reaches it says why (STUB_CALLED)
    c = ("#include <stdio.h>\n#include <stdlib.h>\n" + "".join(
        f'__attribute__((weak)) void {f}(void) {{ fputs("cs-stub: {f} called\\n", stderr); abort(); }}\n'
        for f in funcs)) if funcs else ""
    return ll, c


def design_sources_defining(ddir, srcs, names):
    """Sources under the design directory, other than `srcs` and without a main(), that define one of the
    functions `names` (plain or qualified names: a definition `name(...) {`)."""
    have = {os.path.normpath(str(Path(ddir) / s)) for s in srcs}
    names_have = {Path(s).name for s in srcs}
    roots = [Path(ddir)]
    # The cgeist lit inputs (Polygeist tools/cgeist/Test/HLS/hlsfactory/Inputs/<dataset>/...) hold only the
    # files the cgeist command reads; the rest of the design is in the catalogue.
    parts = Path(ddir).parts
    if "hlsfactory" in parts and "Inputs" in parts:
        i = parts.index("Inputs")
        roots.append(Path(C.DEFAULT_HLSFACTORY_ROOT, "hlsfactory", "hls_dataset_sources", *parts[i + 1:]))
    out = []
    for f in sorted(p for r in roots if r.is_dir() for p in r.rglob("*")):
        if f.suffix not in (".c", ".cc", ".cpp") or os.path.normpath(str(f)) in have or has_main(f) or \
                (f.parent != Path(ddir) and f.name in names_have):
            continue
        try:
            text = f.read_text(errors="replace")
        except OSError:
            continue
        if any(re.search(r"\b" + re.escape(n.split("::")[-1]) + r"\s*\([^;{]*\)\s*(const\s*)?\{", text)
               for n in names):
            out.append(os.path.relpath(str(f), str(ddir)) if Path(ddir) in f.parents else str(f))
    return out


def math_marker_stubs(ll_text):
    """C definitions of the math-core markers the lowered candidate declares (empty when none)."""
    out = []
    for name, params in sorted(set(LL_MATH_MARKER.findall(ll_text))):
        n_double = params.count("double")
        args = ", ".join(f"double x{i}" for i in range(n_double)) + ", int w, int i, int s"
        call = ", ".join(f"x{i}" for i in range(n_double))
        out.append(f"double __hlsest_math_{name}({args}) {{ (void)w; (void)i; (void)s; "
                   f"return {MATH_MARKER_BUILTIN.get(name, name)}({call}); }}")
    return ("#include <math.h>\n" + "\n".join(out) + "\n") if out else ""


def ref_flags(kind, flags, rec, vitis_inc):
    """The native build's -I/-D/-U/-std flags: the cgeist command's, with the shim directory replaced by
    the real Vitis headers for kind `real`; never the shim's math-core marker macro."""
    flags = drop_define(list(flags), MATH_MARKER_DEFINE)
    if kind != "real":
        return list(flags)
    # Vitis' C simulation defines none of the synthesis macros its front end adds (run_hlsest's
    # VITIS_FRONTEND_DEFINES, VITIS_NOTES N19); with __SYNTHESIS__ the real headers take their
    # synthesis-only branches, which g++ does not compile.
    synthesis_only = {"-D" + m for m in VITIS_FRONTEND_DEFINES}
    kept, k = [], 0
    while k < len(flags):
        if flags[k] == "-D" and k + 1 < len(flags) and "-D" + flags[k + 1] in synthesis_only:
            k += 2
            continue
        if flags[k] in synthesis_only:
            k += 1
            continue
        kept.append(flags[k])
        k += 1
    flags = kept
    # A record compiled with --shim real (the synthesis tree C.VITIS_AUTOPILOT_WSL, its forced
    # -include etc/autopilot_ssdm_op.h and -D__DSP48E1__, all from shim/real/cgeist_flags): the
    # C simulation reads Vitis/include instead, with none of these.
    autopilot = os.path.normpath(C.VITIS_AUTOPILOT_WSL)
    kept, k = [], 0
    while k < len(flags):
        x = flags[k]
        if x in ("-I", "-include") and k + 1 < len(flags) and \
                os.path.normpath(flags[k + 1]).startswith(autopilot):
            k += 2
            continue
        if (x.startswith("-I") and os.path.normpath(x[2:]).startswith(autopilot)) or x == "-D__DSP48E1__" or \
                (x == "-D" and k + 1 < len(flags) and flags[k + 1] == "__DSP48E1__"):
            k += 2 if x == "-D" else 1
            continue
        kept.append(x)
        k += 1
    flags = kept
    shim_dirs = {os.path.normpath(p) for p in (rec.get("shim"), C.SHIM_INCLUDE) if p}
    shim_root = os.path.normpath(str(Path(C.__file__).resolve().parent / "shim"))
    out, k, placed = [], 0, False
    while k < len(flags):
        x = flags[k]
        path = None
        if x == "-I" and k + 1 < len(flags):
            path, step = flags[k + 1], 2
        elif x.startswith("-I") and len(x) > 2:
            path, step = x[2:], 1
        if path is not None:
            n = os.path.normpath(path)
            if n in shim_dirs or n == shim_root or n.startswith(shim_root + os.sep) or \
                    n.startswith(os.path.normpath(C.SHIM_INCLUDE) + os.sep):
                if not placed:
                    out += ["-I", vitis_inc]
                    placed = True
                k += step
                continue
            out += ["-I", path]
            k += step
            continue
        out.append(x)
        k += 1
    if not placed:
        out += ["-I", vitis_inc]
    return out


# TAPA kernels (auto_ntt): without __SYNTHESIS__ TAPA's headers take its host runtime (tapa/host: frt,
# glog, boost.coroutine2, none of them part of the design), so the native reference never compiled
# (W9r9 review D6).  The kernel-side headers (tapa/xilinx/hls) only wrap hls::stream, which C simulation
# provides: include them once with __SYNTHESIS__ defined, after the C-simulation ap_int / hls_stream
# headers have set their include guards; the design's own `#include <tapa.h>` is then a no-op.
TAPA_KERNEL_PRELUDE = """// check_semantics.py: TAPA's kernel headers over the C-simulation hls::stream
#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <functional>
#include <ostream>
#include <ap_int.h>
#include <hls_stream.h>
#define __SYNTHESIS__
#include "tapa.h"
#undef __SYNTHESIS__
"""
TAPA_KERNEL_MARK = os.path.join("tapa", "xilinx", "hls", "tapa.h")


def tapa_kernel_flags(flags, work, ddir):
    """-include of TAPA_KERNEL_PRELUDE when an -I directory holds TAPA's tapa.h and its kernel headers."""
    dirs = [flags[k + 1] for k in range(len(flags) - 1) if flags[k] == "-I"]
    dirs += [x[2:] for x in flags if x.startswith("-I") and len(x) > 2]
    dirs = [os.path.join(str(ddir), d) for d in dirs]  # relative -I paths are the design directory's
    if not any(os.path.isfile(os.path.join(d, TAPA_KERNEL_MARK)) and os.path.isfile(os.path.join(d, "tapa.h"))
               for d in dirs):
        return []
    hdr = Path(work) / "cs_tapa_kernel.h"
    if not hdr.exists() or hdr.read_text() != TAPA_KERNEL_PRELUDE:
        hdr.parent.mkdir(parents=True, exist_ok=True)
        hdr.write_text(TAPA_KERNEL_PRELUDE)
    # The kernel headers call hls::stream::empty() / full() from const members; the synthesis
    # hls::stream declares them const, the C-simulation one does not: -fpermissive lets g++ accept it.
    return ["-fpermissive", "-include", str(hdr)]


class Checker:
    def __init__(self, args):
        self.a = args
        self.work = Path(args.work)
        self.lock = threading.Lock()
        self.refs = [k for k in args.ref.split(",") if k]
        for k in self.refs:
            if k not in REF_KINDS:
                raise SystemExit(f"--ref: unknown reference kind {k!r} (known: {', '.join(REF_KINDS)})")
        self.vitis_inc, self.vitis_inc_md5 = (vitis_include_dir() if "real" in self.refs else (None, None))
        # Vitis' math library (MEMOS #94): linked only when a build lacks symbols it defines
        self.vml = None
        if getattr(args, "vitis_mathlib", "auto") != "off":
            self.vml = vitis_mathlib.Mathlib(GXX, self.vitis_inc or vitis_include_dir()[0])
        self.vml_used = {}

    def undefined_mangled(self, link):
        """The undefined symbols (mangled) of a failing link command ending in `-lm -o <exe>`."""
        _, _, se, _ = run(link[:-3] + ["-Wl,--no-demangle"] + link[-3:])
        return sorted(set(re.findall(r"undefined reference to [`']([^'`]+)'", se)))

    def mathlib_objects(self, wd, side, und):
        """Objects of Vitis' math library defining the symbols of `und` it has: None when it has none (or
        --vitis-mathlib off, or the install has no library), a reason string when they cannot be built, else
        vitis_mathlib.Mathlib.build's (objects, {table: private name}, {table: (count, width)})."""
        if self.vml is None or not und or not self.vml.prepare():
            return None
        syms = [u for u in und if self.vml.defines(u)]
        if not syms:
            return None
        try:
            got = self.vml.build(syms)
        except ValueError as e:
            return f"Vitis math library: {e}"[:300]
        with self.lock:
            self.vml_used.setdefault(str(wd), {})[side] = syms
        return got

    def check(self, key, rec):
        out = dict(key=key, mlir=rec.get("mlir"), top_fn=rec.get("top_fn"), status="", reason="")
        try:
            self._check(key, rec, out)
        except Exception as e:      # noqa: BLE001
            out["status"], out["reason"] = "n/a", f"harness exception: {type(e).__name__}: {e}"[:400]
        return out

    @staticmethod
    def _na(out, reason):
        out["status"], out["reason"] = "n/a", reason
        return out

    # ------------------------------------------------------------------------------- candidate --
    def _check(self, key, rec, out):
        if rec.get("cgeist_status") not in (None, "ok") or rec.get("status", "").startswith("cgeist"):
            return self._na(out, "no MLIR: " + (rec.get("cgeist_status") or rec.get("status", ""))[:120])
        mlir = rec.get("mlir")
        if not mlir or not os.path.exists(mlir):
            return self._na(out, "no MLIR file")
        text = Path(mlir).read_text(errors="replace")
        top_fn = rec.get("top_fn") or rec.get("top")
        sig = top_signature(text, top_fn)
        if not sig:
            return self._na(out, f"top {top_fn} not in the MLIR")
        # A top whose pointer argument ('?' leading dimension) is read past the driver's default size
        # (spector matrix_multiplication reads `dtype *A` M*M = 1,048,576 times; GradCAM linear_fc
        # reads weights[][512] up to row 1024) gets a heap-buffer-overflow from the driver's buffer, not
        # from the design (W9 round 12 review, defect 5): such a check is re-run once with the leading
        # '?' dimensions DYN_RETRY_SCALE times larger, within MAX_BUFFER_BYTES.
        for scale in (1, DYN_RETRY_SCALE):
            try:
                plan = plan_args(*sig, top_stream_args(top_fn, stream_methods(text)), dyn_scale=scale,
                                 bools=bool_params(top_fn))
            except ValueError as e:
                return self._na(out, f"driver cannot fill the top: {e}"[:300])
            dyn = any(p["kind"] == "memref" and None in p["ty"].dims for p in plan)
            if scale > 1:
                if sum(p["elems"] * p["esize"] for p in plan) > MAX_BUFFER_BYTES:
                    break
                out.clear()
                out.update(base)
                out["dyn_scale"] = scale
            else:
                base = dict(out)
            self._check_plan(key, rec, out, text, top_fn, plan)
            refs = out.get("refs") or {}
            overflow = any("heap-buffer-overflow" in r.get("reason", "") for r in refs.values())
            if not (dyn and overflow and out.get("status") == "n/a"):
                break
        return out

    def _check_plan(self, key, rec, out, text, top_fn, plan):
        out["args"] = [p["type"] for p in plan]
        if any(p["kind"] == "stream" for p in plan):
            out["stream_args"] = [a for a, p in enumerate(plan) if p["kind"] == "stream"]
        argv = cgeist_command(rec)
        if not argv:
            return self._na(out, "no cgeist command (log missing)")
        flags, srcs = native_flags(argv)
        ddir = Path(rec["dir"])
        if not srcs:
            srcs = list(rec.get("sources", []))
        wd = self.work / key.replace("/", "__")
        if wd.exists():
            shutil.rmtree(wd)
        wd.mkdir(parents=True)
        out["work"] = str(wd)
        why = self.build_candidate(wd, text, top_fn, plan)
        if why:
            return self._na(out, why)
        # the references in order: an `equal` ends the list (unless --all-refs); a mismatch or an n/a
        # goes on to the next, which tells a frontend bug (every reference differs) from a shim-semantics
        # difference (only the real headers differ) and stands in where the first cannot be built
        out["refs"] = {}
        for kind in self.refs:
            out["refs"][kind] = self.compare(kind, wd, ddir, flags, srcs, top_fn, rec, plan)
            if out["refs"][kind]["status"] == "equal" and not self.a.all_refs:
                break
        decided = [k for k in out["refs"] if out["refs"][k]["status"] in ("equal", "mismatch")]
        use = decided[0] if decided else self.refs[0]
        prim = out["refs"][use]
        out["status"], out["reason"], out["ref_used"] = prim["status"], prim["reason"], use
        if use != self.refs[0]:
            out["reason"] = (f"{prim['reason']} [{use} reference; {self.refs[0]}: "
                             f"{out['refs'][self.refs[0]]['reason'][:160]}]")
        # (an n/a of its own: a `graph` retry's verdict quotes the default modes' reason, which may say it)
        uninit = [k for k in out["refs"] if out["refs"][k]["status"] == "n/a"
                  and "uninitialised" in out["refs"][k].get("reason", "")]
        if out["status"] == "mismatch" and uninit:
            # one reference showed that the design's outputs depend on uninitialised memory: the C program
            # has no defined result, so a difference says nothing about the frontend
            out["status"] = "n/a"
            out["reason"] = (f"reads uninitialised memory ({uninit[0]} reference; {use}: "
                             f"{prim['reason'][:120]})")
        if out["status"] == "mismatch":
            other = [k for k in decided if k != use]
            if not other:
                out["mismatch_kind"] = f"{use} reference only (no other reference was compared)"
            elif all(out["refs"][k]["status"] == "equal" for k in other):
                out["mismatch_kind"] = f"{use} only ({', '.join(other)} equal): header semantics"
            else:
                out["mismatch_kind"] = "every reference differs: frontend"
        if not self.a.keep:
            for f in wd.glob("cand.*.bin"):
                f.unlink(missing_ok=True)
        used = self.vml_used.get(str(wd))
        if used:
            # the record names what was linked; the executables hold library code and are not kept (MEMOS #94)
            out["vitis_mathlib"] = {side: syms for side, syms in sorted(used.items())}
            # The scope of a verdict (W9r21 review finding 4): a library function only the reference links was
            # computed by something else on the candidate's side (cgeist lowers hls::cos(double) & co. to LLVM's
            # math intrinsics, glibc at run time), so equal outputs do not show the two agree on it.
            cand = {demangle(x) for x in used.get("cand", [])}
            # every build of the deciding reference kind (`real`, `real_nosan` of the timeout fallback, ...)
            ref_syms = {x for side, syms in used.items() if side == use or side.startswith(use + "_") for x in syms}
            ref_only = sorted({demangle(x) for x in ref_syms} - cand)
            funcs = [d for d in ref_only if re.search(r"\)( const)?$", d)]
            if funcs:
                out["vitis_mathlib_reference_only"] = funcs
                if out["status"] == "equal":
                    out["reason"] += ("; scope: the reference calls " + ", ".join(funcs) + " from Vitis' math "
                                      "library, the candidate computes them with LLVM math intrinsics (glibc), "
                                      "so this does not check those functions")
            for f in wd.glob("*.exe"):
                f.unlink(missing_ok=True)
        return out

    def build_candidate(self, wd, text, top_fn, plan):
        """cand.exe from the MLIR; None, or the reason it cannot be built."""
        dial = dialects_used(text) - STD_DIALECTS
        used_polygeist = "polygeist" in dial
        if dial - {"polygeist"}:
            return "MLIR uses dialects " + ",".join(sorted(dial))
        renamed = re.sub(r"@main\b", "@cs_design_main_", text)
        body = renamed.rstrip()
        if not body.endswith("}"):
            return "MLIR does not end with the module's closing brace"
        wrapped = body[:-1] + wrapper_mlir(top_fn, plan, global_inits(text)) + "}\n"
        (wd / "cand.mlir").write_text(wrapped)
        if used_polygeist:
            if not os.path.exists(POLYGEIST_OPT):
                return "polygeist ops (" + ",".join(sorted(set(re.findall(r"polygeist\.(\w+)", text)))) + \
                       ") need polygeist-opt (not built)"
            # polygeist-opt registers neither --convert-scf-to-cf (its convert-polygeist-to-llvm
            # lowers scf itself) nor --reconcile-unrealized-casts.
            lowers = [[POLYGEIST_OPT, str(wd / "cand.mlir"), "--lower-affine",
                       "--convert-polygeist-to-llvm=use-c-style-memref=0", "-o", str(wd / "cand.pg.mlir")],
                      [POLYGEIST_MLIR_OPT, str(wd / "cand.pg.mlir"), "--reconcile-unrealized-casts",
                       "-o", str(wd / "cand.ll.mlir")]]
            translate = POLYGEIST_MLIR_TRANSLATE
        else:
            lowers = [[MLIR_OPT, str(wd / "cand.mlir"), *UPSTREAM_LOWERING, "-o", str(wd / "cand.ll.mlir")]]
            translate = MLIR_TRANSLATE
        for lower in lowers:
            rc, so, se, _ = run(lower, timeout=600)
            if rc != 0:
                (wd / "lower.err").write_text(se)
                return "lowering failed: " + first_err(se)
        rc, so, se, _ = run([translate, "--mlir-to-llvmir", str(wd / "cand.ll.mlir"), "-o", str(wd / "cand.ll")])
        if rc != 0:
            (wd / "translate.err").write_text(se)
            return "mlir-translate failed: " + first_err(se)
        rc, so, se, _ = run([LLC, "-O0", "-filetype=obj", "-relocation-model=pic", str(wd / "cand.ll"), "-o",
                             str(wd / "cand.o")])
        if rc != 0:
            return "llc on the lowered MLIR failed: " + first_err(se)
        extra_objs = []
        ll_text = (wd / "cand.ll").read_text(errors="replace")
        if LL_DECLARE.search(ll_text):
            # the shim's hls::stream methods are declarations only: define them on the token FIFOs
            try:
                (wd / "cand_streams.ll").write_text(cand_stream_runtime(text, ll_text))
            except ValueError as e:
                return f"hls::stream runtime: {e}"[:300]
            rc, so, se, _ = run([LLC, "-O0", "-filetype=obj", "-relocation-model=pic", str(wd / "cand_streams.ll"),
                                 "-o", str(wd / "cand_streams.o")])
            if rc != 0:
                (wd / "cand_streams.err").write_text(se)
                return "hls::stream runtime does not compile: " + first_err(se)
            extra_objs.append(str(wd / "cand_streams.o"))
        stubs = math_marker_stubs(ll_text)
        if stubs:
            # the exactclass shim's math-core markers are declarations only: call the builtin
            (wd / "cand_math.c").write_text(stubs)
            rc, so, se, _ = run([GCC, "-c", "-O0", "-w",
                                 str(wd / "cand_math.c"), "-o", str(wd / "cand_math.o")])
            if rc != 0:
                return "math-core marker stubs do not compile: " + first_err(se)
            extra_objs.append(str(wd / "cand_math.o"))
        (wd / "cs_spec.h").write_text(spec_header(plan))
        (wd / "cs_main.cpp").write_text(DRIVER_MAIN)
        (wd / "cand_thunk.cpp").write_text(cand_thunk(plan, "descriptor"))
        # the driver and the candidate's thunk are plain C++: the system g++ (fast to start)
        common = [GXX, "-c", "-O0", "-w", "-std=c++17", "-I", str(wd)]
        for src, obj in (("cs_main.cpp", "cs_main.o"), ("cand_thunk.cpp", "cand_thunk.o")):
            rc, so, se, _ = run(common + [str(wd / src), "-o", str(wd / obj)])
            if rc != 0:
                return f"driver {src} does not compile: " + first_err(se)
        link = [GXX, str(wd / "cs_main.o"), str(wd / "cand_thunk.o"), str(wd / "cand.o"), *extra_objs, "-lm",
                "-o", str(wd / "cand.exe")]
        rc, so, se, _ = run(link)
        if rc != 0:
            # Symbols Vitis' math library defines (the cordic / log tables, hls::powf, hls::atan(double),
            # ...): link the library from the install (MEMOS #94; vitis_mathlib.py).  The candidate was
            # compiled with the synthesis headers, so it reads the library's own table layout.
            und = self.undefined_mangled(link)
            got = self.mathlib_objects(wd, "cand", und)
            if isinstance(got, str):
                return got
            if got:
                objs, raw, _ = got
                link = link[:-3] + objs + vitis_mathlib.defsym_flags(raw) + link[-3:]
                rc, so, se, _ = run(link)
        if rc != 0:
            # Symbols the MLIR declares but no file cgeist compiled defines (W9r14-impl, DoD 1): a design
            # global defined in another source of the design without an initialiser (flowgnn gcn / gin
            # `edge_attrs` in globals.cc) is zero-initialised there, so a zero-initialised definition is the
            # same object; a function only an uncalled function of the module references (a testbench
            # helper, gin_vn_base's fetch_one_graph / load_weights) gets a stub that aborts, so a run that
            # does call it fails instead of passing.
            _, _, se_raw, _ = run(link[:-3] + ["-Wl,--no-demangle"] + link[-3:])
            und = sorted(set(re.findall(r"undefined reference to [`']([^'`]+)'", se_raw)))
            stubs = undefined_symbol_stubs(und, ll_text) if und else None
            if stubs:
                ll_stub, c_stub = stubs
                objs = []
                if ll_stub:
                    (wd / "cand_globals.ll").write_text(ll_stub)
                    rc2, _, se2, _ = run([LLC, "-O0", "-filetype=obj", "-relocation-model=pic",
                                          str(wd / "cand_globals.ll"), "-o", str(wd / "cand_globals.o")])
                    if rc2 == 0:
                        objs.append(str(wd / "cand_globals.o"))
                if c_stub:
                    (wd / "cand_stubs.c").write_text(c_stub)
                    rc2, _, se2, _ = run([GCC, "-c", "-O0", "-w", str(wd / "cand_stubs.c"), "-o",
                                          str(wd / "cand_stubs.o")])
                    if rc2 == 0:
                        objs.append(str(wd / "cand_stubs.o"))
                if objs:
                    rc, so, se, _ = run(link[:-3] + objs + link[-3:])
        if rc != 0:
            (wd / "cand.link.err").write_text(se)
            und = re.findall(r"undefined reference to [`']([^'`]+)'", se)
            return "candidate does not link: " + (("undefined " + ", ".join(sorted(set(und))[:4])) if und
                                                  else first_err(se))
        return None

    # ------------------------------------------------------------------------------- reference --
    def compare(self, kind, wd, ddir, flags, srcs, top_fn, rec, plan, sanitize=True, graph=False):
        """Build the `kind` reference and compare it with cand.exe on every mode and seed.  A reference
        that times out under AddressSanitizer on every run is built and run again without it (the
        AddressSanitizer build of class_ece8893 Ray-tracing HLS runs over 1800 s, the plain one in about
        130 s; OPEN_ISSUES O165): its verdict says so in the reason.  graph: run the GRAPH_MODES only (the
        input-domain retry `graph`, graph_retry)."""
        a = self.a
        res = dict(status="", reason="")
        rflags = ref_flags(kind, flags, rec, self.vitis_inc)
        if kind == "real":
            rflags = rflags + tapa_kernel_flags(rflags, self.work, ddir)
        res["flags"] = rflags
        san = ["-fsanitize=address", "-fno-omit-frame-pointer"] if sanitize else []
        refb = self.build_ref(kind, wd, ddir, rflags, srcs, top_fn, rec, plan, res,
                              tag=f"{kind}" if sanitize else f"{kind}_nosan", extra=san)
        if refb is None:
            return res
        runs, valid, bad, timeouts = [], 0, None, 0
        modes = GRAPH_MODES if graph else [m for m in a.modes.split(",") if m]
        plan_runs = [(mode, int(seed)) for mode in modes for seed in a.seeds.split(",") if seed]
        retry, k = ("graph" if graph else None), 0
        while True:
            if k >= len(plan_runs):
                retry = input_retry(runs, valid, retry, a.modes)
                if retry is None:
                    break
                res["input_retry"] = retry
                plan_runs += [(retry, int(seed)) for seed in a.seeds.split(",") if seed]
                continue
            # one mismatch is enough to analyse; a reference that times out twice will not finish later
            # in the same mode (it may in an input-domain retry: `index`)
            if bad is not None:
                break
            if timeouts >= 2:
                retry = input_retry(runs, valid, retry, a.modes)
                if retry is None:
                    break
                res["input_retry"] = retry
                timeouts = 0
                plan_runs = plan_runs[:k] + [(retry, int(seed)) for seed in a.seeds.split(",") if seed]
                continue
            mode, seed = plan_runs[k]
            k += 1
            mi = MODE_INDEX[mode]
            ro, co = wd / f"{kind}.{mode}.{seed}.bin", wd / f"cand.{mode}.{seed}.bin"
            rrc, rerr, rt = run_exe(refb, mi, seed, a.calls, ro, a.timeout, ASAN_ENV)
            r = dict(mode=mode, seed=seed, ref_rc=rrc, ref_s=round(rt, 2))
            if rrc == LAYOUT_EXIT:
                m = re.search(r"cs-layout: (.*)", rerr)
                res["status"], res["reason"] = "n/a", "argument layout: " + (m.group(1) if m else "?")
                return res
            # exit 88: the reference stopped at a blocking read of an empty stream, with the dump of the
            # call in progress; it is compared when the candidate stops at the same read (below)
            ref_blocked = rrc == BLOCKED_READ_EXIT
            if rrc != 0 and not ref_blocked:
                m = re.search(r"ERROR: AddressSanitizer: ([\w-]+)", rerr)
                r["valid"] = False
                if rrc == 86:
                    r["why"] = "AddressSanitizer: " + (m.group(1) if m else "?")
                elif rrc == -6 and "hls::stream is read while empty" in rerr:
                    r["why"] = "reads an empty hls::stream"
                elif rrc == -6 and re.search(r"Assertion .* failed", rerr):
                    r["why"] = "aborts on an assertion of the source"
                else:
                    r["why"] = f"reference exit {rrc}"
                timeouts += rrc == "timeout"
                runs.append(r)
                ro.unlink(missing_ok=True)
                continue
            if not co.exists():
                crc, cerr, ct = run_exe(wd / "cand.exe", mi, seed, a.calls, co, a.timeout)
                (wd / f"cand.{mode}.{seed}.rc").write_text(str(crc))
                stub = re.search(STUB_CALLED, cerr or "")
                (wd / f"cand.{mode}.{seed}.stub").write_text(stub.group(1) if stub else "")
            else:
                crc, ct = (wd / f"cand.{mode}.{seed}.rc").read_text().strip(), 0.0
                sf = wd / f"cand.{mode}.{seed}.stub"
                cerr = f"cs-stub: {sf.read_text()} called" if sf.exists() and sf.read_text() else ""
                crc = int(crc) if crc.lstrip("-").isdigit() else crc
            if crc == -8 and self.reference_divides_by_zero(kind, wd, ddir, rflags, srcs, top_fn, rec, plan,
                                                             res, mi, seed):
                # SIGFPE: an integer division by zero (or INT_MIN / -1) in the candidate, and the source
                # divides by zero on these inputs too (UBSan says so). That is undefined in C and C++, so
                # the native build's result for these inputs means nothing (it need not trap: the
                # reference took its value from whatever its division gave). A candidate that traps where
                # the source does not divide by zero is a mismatch (a trip count computed above its guard,
                # W9r7 review defect 1).
                r.update(cand_rc=crc, cand_s=round(ct, 2), valid=False,
                         why="candidate divides by zero (SIGFPE; the source divides by zero too: undefined "
                             "behaviour in C)")
                runs.append(r)
                ro.unlink(missing_ok=True)
                continue
            if ref_blocked and crc != BLOCKED_READ_EXIT:
                r.update(cand_rc=crc, cand_s=round(ct, 2), valid=False,
                         why="reads an empty hls::stream (the reference blocks; the candidate does not stop there)")
                runs.append(r)
                ro.unlink(missing_ok=True)
                continue
            r.update(cand_rc=crc, cand_s=round(ct, 2), valid=True)
            if ref_blocked:
                r["note"] = "both stop at a blocking read of an empty hls::stream; the dumps there are compared"
            valid += 1
            ra = ro.read_bytes()
            r["ref_sha1"] = hashlib.sha1(ra).hexdigest()[:16]
            cb = co.read_bytes() if co.exists() else b""
            if crc != 0 and not ref_blocked:
                r["equal"] = False
                r["why"] = f"candidate exit {crc}"
                stub = re.search(STUB_CALLED, cerr or "")
                if stub:
                    r["why"] += (f" (it calls {stub.group(1)}, which the MLIR declares and nothing defines: "
                                 "the driver's stub aborts)")
            elif ra == cb:
                r["equal"] = True
            elif nan_lane_only_diff(ra, cb, plan):
                r["equal"] = True
                r["note"] = "equal up to NaN payloads in float lanes of packed integers"
            else:
                r["equal"] = False
                r["diff"] = first_diff(ra, cb, plan)
            runs.append(r)
            if r["equal"] and not a.keep:
                ro.unlink(missing_ok=True)
            elif not r["equal"] and bad is None:
                bad = r
        res["runs"] = runs
        if not valid and sanitize and timeouts and all(r.get("ref_rc") == "timeout" for r in runs):
            plain = self.compare(kind, wd, ddir, flags, srcs, top_fn, rec, plan, sanitize=False, graph=graph)
            plain["reason"] = ("reference without AddressSanitizer (it times out under it): "
                               + str(plain.get("reason") or ""))
            plain["sanitizer_runs"] = runs
            return plain
        retried = (f" (input-domain retry `{res['input_retry']}`: every run of the default modes "
                   "was invalid)") if res.get("input_retry") else ""
        if not valid:
            whys = sorted({r.get("why", "") for r in runs})
            res["status"], res["reason"] = "n/a", "no valid run (" + "; ".join(whys)[:200] + ")" + retried
            return self.graph_retry(kind, wd, ddir, flags, srcs, top_fn, rec, plan, sanitize, graph, res)
        if bad is None:
            # Seeds need not give distinct inputs: mode `index` fills every integer lane with its position,
            # so a design whose arguments are all integer lanes gets one input whatever the seed (W9 round 19
            # review defect 7). Count the distinct reference outputs, so the reason does not claim more
            # independent evidence than the runs gave.
            distinct = len({r["ref_sha1"] for r in runs if r.get("valid")})
            outputs = (f", {distinct} distinct reference output(s)" if distinct < valid else "")
            res["status"], res["reason"] = "equal", f"{valid} valid runs{outputs}" + retried
            return res
        # a mismatch: does the reference read uninitialised memory?  does it run into UB?
        mi = MODE_INDEX[bad["mode"]]
        # two pairs, each =pattern against =zero: at the reference's own optimisation level and at -O0 (an
        # -O0 in `extra` overrides the real reference's -O1, the last -O wins).  At -O1 GCC can fold a read of
        # an uninitialised local to a constant before the auto-var-init lowering, so that pair gives the same
        # output and the read goes unseen (ap_fixed<16,5> local read into an output: -O0 =pattern 0xfefe,
        # -O1 =pattern 0x0000; forgebench mult_op_module_dot, W11-adopt review D3); the -O1 pair stays because
        # it sees reads the -O0 pair does not (kamya_hari lab_3: -O1 pair differs, -O0 pair equal).
        res["mismatch_run"] = bad
        init_exes = {}
        for opt in ([], ["-O0"]):
            dumps = []
            for init in ("pattern", "zero"):
                tag = f"{kind}_{init}" + ("_O0" if opt else "")
                exe = self.build_ref(kind, wd, ddir, rflags, srcs, top_fn, rec, plan, res, tag=tag,
                                     extra=[*opt, f"-ftrivial-auto-var-init={init}"])
                if exe is None:
                    return res
                init_exes[tag] = exe
                o = wd / f"{tag}.bin"
                rc, _, _ = run_exe(exe, mi, bad["seed"], a.calls, o, a.timeout)
                dumps.append(o.read_bytes() if (rc == 0 and o.exists()) else None)
            if dumps[0] is None or dumps[1] is None or dumps[0] != dumps[1]:
                res["status"] = "n/a"
                res["reason"] = ("reads uninitialised memory (native outputs depend on -ftrivial-auto-var-init"
                                 + (" at -O0)" if opt else ")"))
                if dumps[0] is not None and dumps[1] is not None:
                    masked = self.masked_compare(wd, kind, init_exes, runs, opt, a)
                    if masked is not None and masked["status"] == "equal":
                        res.update(masked)
                        return res
                    if masked is not None:
                        res["reason"] = masked["reason"]
                return self.graph_retry(kind, wd, ddir, flags, srcs, top_fn, rec, plan, sanitize, graph, res)
        exe = self.build_ref(kind, wd, ddir, rflags, srcs, top_fn, rec, plan, res, tag=f"{kind}_ubsan",
                             extra=["-fsanitize=undefined"])
        if exe is not None:
            rc, err, _ = run_exe(exe, mi, bad["seed"], a.calls, wd / f"{kind}_ubsan.bin", a.timeout,
                                 {"UBSAN_OPTIONS": "print_stacktrace=0"})
            # the design's own reports first: the headers' (ap_private's shifts of negative values in the
            # Vitis C-simulation headers, for one) say nothing about the design
            hdr_dirs = tuple(d for d in (self.vitis_inc, rec.get("shim"), C.SHIM_INCLUDE) if d)
            ub_all = [ln.strip() for ln in err.splitlines() if "runtime error:" in ln]
            ub_design = [ln for ln in ub_all if not ln.startswith(hdr_dirs) and "/include/" not in ln.split(":")[0]]
            ub = [re.sub(r"^/\S*/([^/:]+:\d+)", r"\1", ln) for ln in (ub_design or ub_all)]
            if ub:
                res["ubsan"] = ub[:3]
        res["status"] = "mismatch"
        res["reason"] = (f"{bad['mode']} seed {bad['seed']}: " + (bad.get("why") or json.dumps(bad.get("diff"))))[:400]
        return res

    def masked_compare(self, wd, kind, init_exes, runs, opt, a):
        """The verdict on the bytes that do not depend on uninitialised memory (W9 round 23 review D7): the
        reference reads uninitialised memory (its outputs differ between -ftrivial-auto-var-init=pattern and
        =zero), but the bytes on which every build of the reference agrees (its own build, =pattern and
        =zero at its optimisation level and at -O0) are defined by the program, and the candidate must give
        them. Every mismatching valid run is checked this way; the result (a status and a reason) is
        "equal" when the candidate agrees on every such byte of every run, an n/a that names the first byte
        where it does not (the uninitialised value may come from storage the auto-var-init does not cover,
        the same in every reference build), or None when a dump has another length or no byte is
        init-independent (the n/a stands)."""
        checked = unstable_total = 0
        for r in runs:
            if not r.get("valid") or r.get("equal", True) or r.get("why"):
                continue
            mode, seed = r["mode"], r["seed"]
            ro, co = wd / f"{kind}.{mode}.{seed}.bin", wd / f"cand.{mode}.{seed}.bin"
            if not ro.exists() or not co.exists():
                return None
            ref, cand = ro.read_bytes(), co.read_bytes()
            dumps = [ref]
            for tag, exe in init_exes.items():
                o = wd / f"{tag}.{mode}.{seed}.bin"
                rc, _, _ = run_exe(exe, MODE_INDEX[mode], seed, a.calls, o, a.timeout)
                if rc != 0 or not o.exists():
                    return None
                dumps.append(o.read_bytes())
            if any(len(d) != len(ref) for d in dumps) or len(cand) != len(ref):
                return None
            unstable = set()
            for d in dumps[1:]:
                unstable.update(differing_bytes(ref, d))
            if len(unstable) == len(ref):
                return None
            unstable_total += len(unstable)
            for i in differing_bytes(ref, cand):
                if i not in unstable:
                    # Not a verdict: an uninitialised value can also come from storage that
                    # -ftrivial-auto-var-init does not cover (heap, statics, reads past a buffer), the
                    # same in every build of the reference and another one in the candidate (soda
                    # contrast / denoise2d / denoise3d: 0x00 in every reference build).
                    return {"status": "n/a", "masked": True,
                            "reason": ("reads uninitialised memory (native outputs depend on "
                                       "-ftrivial-auto-var-init); the masked comparison is not decidable: "
                                       f"{mode} seed {seed}: byte {i} of the output dump differs (candidate "
                                       f"{cand[i]:#04x}, reference {ref[i]:#04x}) where no build of the "
                                       "reference changes")[:400]}
            checked += 1
        if not checked:
            return None
        return {"status": "equal", "masked": True,
                "reason": (f"equal on the init-independent bytes of {checked} mismatching run(s) (the reference "
                           f"reads uninitialised memory: {unstable_total} byte(s) depend on "
                           "-ftrivial-auto-var-init and are not compared)")}

    # why-strings of a run that failed on its input: an out-of-bounds access, a division by zero (FPE) or
    # a loop over an unbounded count (timeout)
    GRAPH_RETRY_WHYS = ("AddressSanitizer", "reference exit timeout", "aborts on an assertion of the source")

    def graph_retry(self, kind, wd, ddir, flags, srcs, top_fn, rec, plan, sanitize, graph, res):
        """The input-domain retry `graph` (GRAPH_INDEX_BITS): for a design with an edge list and a count
        whose verdict under the default modes is n/a (no valid run, or reads uninitialised memory) and
        some of whose runs failed on their input, the runs are repeated in the GRAPH_MODES.  Their result
        decides when they give a verdict (equal, mismatch, or reads uninitialised memory on valid graphs);
        otherwise the default modes' n/a and its reason stand, with the retry's result under `graph_retry`.
        Both are recorded.  (The trigger counts an assertion of the source too: `assert(u < n)` is graph
        code's usual guard.)"""
        if graph or not graph_shaped(plan):
            return res
        if not any(w in r.get("why", "") for r in res.get("runs", []) for w in self.GRAPH_RETRY_WHYS):
            return res
        g = self.compare(kind, wd, ddir, flags, srcs, top_fn, rec, plan, sanitize=sanitize, graph=True)
        g["input_retry"] = "graph"
        g["default_modes"] = {k: res.get(k) for k in ("status", "reason", "runs", "mismatch_run", "ubsan",
                                                      "input_retry") if k in res}
        if g.get("status") in ("equal", "mismatch") or (g.get("status") == "n/a" and "reads uninitialised memory"
                                                         in str(g.get("reason", ""))):
            g["reason"] = (f"{g.get('reason', '')} (input-domain retry `graph`: valid graphs; the default modes "
                           f"gave n/a: {str(res.get('reason', ''))[:160]})")
            return g
        # the default modes' reason stays the record's reason: make_done_exclusions / make_dod_status classify an
        # n/a by it, and the graph runs' failures come from inputs the driver chose (review of b06d1bd51, item 1)
        res["graph_retry"] = {k: g.get(k) for k in ("status", "reason", "runs") if k in g}
        return res

    def reference_divides_by_zero(self, kind, wd, ddir, rflags, srcs, top_fn, rec, plan, res, mi, seed):
        """Whether the source itself divides by zero on this mode and seed: a reference built with
        -fsanitize=integer-divide-by-zero reports it (or traps). Unknown (no build) counts as yes, the
        earlier rule."""
        a = self.a
        tag = f"{kind}_divz"
        scratch = {}                    # a failed build must not set the design's status
        exe = self.build_ref(kind, wd, ddir, rflags, srcs, top_fn, rec, plan, scratch, tag=tag,
                             extra=["-fsanitize=integer-divide-by-zero"])
        res.setdefault("ref_cache_hits", []).extend(scratch.get("ref_cache_hits", []))
        if exe is None:
            return True
        rc, err, _ = run_exe(exe, mi, seed, a.calls, wd / f"{tag}.bin", a.timeout,
                             {"UBSAN_OPTIONS": "print_stacktrace=0"})
        return rc == -8 or "division by zero" in err

    # ---------------------------------------------------------------------- reference build cache --
    # A reference depends on the design's files, its flags, the headers and compilers, and the plan (the
    # MLIR top's signature) only, not on the MLIR's body: re-checks after a frontend change reuse it.
    _dir_digests = {}

    def _files_digest(self, root, recursive=True):
        root = str(root)
        memo_key = (root, recursive)
        with self.lock:
            if memo_key in self._dir_digests:
                return self._dir_digests[memo_key]
        h = hashlib.sha256()
        if os.path.isdir(root):
            walker = os.walk(root) if recursive else [(root, [], os.listdir(root))]
            for dp, dn, fn in walker:
                dn.sort()
                for f in sorted(fn):
                    if not SOURCE_EXT.search(f):
                        continue
                    p = os.path.join(dp, f)
                    try:
                        with open(p, "rb") as fh:
                            h.update(os.path.relpath(p, root).encode() + b"\0" + fh.read() + b"\0")
                    except OSError:
                        continue
        d = h.hexdigest()
        with self.lock:
            self._dir_digests[memo_key] = d
        return d

    def ref_cache_key(self, kind, ddir, flags, mflags_hint, rec, plan, top_fn, tag, extra):
        # The reference's own source files: several probes (or designs) in one directory share the
        # directory digest and can share a top signature, so the digest alone does not tell them apart.
        parts = [REF_CACHE_VERSION, kind, tag, " ".join(flags), " ".join(extra), top_fn, rec.get("top") or "",
                 " ".join(str(s) for s in (rec.get("sources") or [])),
                 spec_header(plan), DRIVER_MAIN, REF_THUNK_REAL if kind == "real" else REF_THUNK_CXX,
                 " ".join(THUNK_SHIELDED),
                 mflags_hint, self._files_digest(ddir)]
        for tool in ((GCC, GXX) if kind == "real" else (CLANG, CLANGXX, SAN_LINKER)) + (GXX,):
            try:
                st = os.stat(os.path.realpath(tool))
                parts.append(f"{tool}|{st.st_size}|{int(st.st_mtime)}")
            except OSError:
                return None
        if kind == "real":
            parts.append(self.vitis_inc_md5 or "")
        else:
            parts.append(self._files_digest(rec.get("shim") or C.SHIM_INCLUDE))
        dd = os.path.realpath(str(ddir))
        k = 0
        while k < len(flags):           # include directories outside the design (polybench utilities, ...)
            if flags[k] == "-I" and k + 1 < len(flags):
                p = flags[k + 1] if os.path.isabs(flags[k + 1]) else os.path.join(dd, flags[k + 1])
                p = os.path.realpath(p)
                if not p.startswith(dd + os.sep) and p != dd and p != (self.vitis_inc or ""):
                    parts.append(p + "|" + self._files_digest(p, recursive=False))
                k += 2
                continue
            k += 1
        return hashlib.sha256("\x1e".join(parts).encode()).hexdigest()[:24]

    def build_ref(self, kind, wd, ddir, flags, srcs, top_fn, rec, plan, res, tag, extra):
        """The reference executable from the cache or from build_ref_uncached, or None (res gets the
        reason). Failures are cached too, unless a step timed out."""
        exe = wd / f"{tag}.exe"
        if exe.exists():
            return exe
        main_hint = "main" if any(has_main(ddir / s) for s in srcs) else ""
        key = None if self.a.no_ref_cache else self.ref_cache_key(kind, ddir, flags, main_hint, rec, plan, top_fn,
                                                                  tag, extra)
        cdir = REF_CACHE / key if key else None
        if cdir is not None:
            if self.vml is not None and (cdir / "failed.json").exists() and \
                    "does not link" in (cdir / "failed.json").read_text():
                cdir = None      # a link failure cached before the math library was linked (MEMOS #94)
        if cdir is not None:
            if (cdir / "ref.exe").exists():
                shutil.copy2(cdir / "ref.exe", exe)
                res.setdefault("ref_cache_hits", []).append(tag)
                return exe
            if (cdir / "failed.json").exists():
                res.update(json.loads((cdir / "failed.json").read_text()))
                res.setdefault("ref_cache_hits", []).append(tag)
                return None
        got = self.build_ref_uncached(kind, wd, ddir, flags, srcs, top_fn, rec, plan, res, tag, extra)
        if tag in self.vml_used.get(str(wd), {}):
            cdir = None          # nothing derived from Vitis' math library is kept after the run (MEMOS #94)
        if cdir is not None:
            tmp = cdir.with_name(cdir.name + f".tmp{os.getpid()}.{threading.get_ident()}")
            tmp.mkdir(parents=True, exist_ok=True)
            if got is not None:
                shutil.copy2(got, tmp / "ref.exe")
            elif "timeout" not in res.get("reason", ""):
                (tmp / "failed.json").write_text(json.dumps({"status": res.get("status"),
                                                              "reason": res.get("reason")}))
            else:
                shutil.rmtree(tmp, ignore_errors=True)
                return got
            try:
                tmp.rename(cdir)
            except OSError:          # another thread stored the same key first
                shutil.rmtree(tmp, ignore_errors=True)
        return got

    def build_ref_uncached(self, kind, wd, ddir, flags, srcs, top_fn, rec, plan, res, tag, extra):
        """Native objects + thunk + driver -> executable, or None (res gets the reason)."""
        exe = wd / f"{tag}.exe"
        if kind == "real":
            # -pthread: the C-simulation hls::stream runs a deadlock detector thread (hls_stream.h).
            # -O1: ap_private's operators at -O0 under AddressSanitizer take minutes per call; GCC keeps
            # IEEE semantics at -O1 (no -ffast-math, no FP contraction without FMA in the base x86-64 ISA)
            cc, cxx, base, opt = GCC, GXX, ["-pthread"], "-O1"
        else:
            cc, cxx, base, opt = CLANG, CLANGXX, [f"-resource-dir={C.CLANG_RESOURCE_DIR}"], "-O0"
        top = rec.get("top") or top_fn
        main_def = [s for s in srcs if has_main(ddir / s)]
        mflags = ["-Dmain=cs_design_main_"] if main_def else []
        top_src = [s for s in srcs if defines_function(ddir / s, top)]
        objs = []

        def compile_one(s):
            o = wd / f"{tag}.{Path(s).name}.o"
            comp = cc if s.endswith(".c") else cxx
            rc, so, se, _ = run([comp, "-c", opt, "-w", *base, *flags, *mflags, *extra, s, "-o", str(o)],
                                cwd=str(ddir))
            if rc != 0:
                (wd / f"{tag}.{Path(s).name}.err").write_text(se)
                self._na(res, f"native build of {s} fails: " + first_err(se))
                return None
            return o

        if top_src and top_src[0].endswith(".c"):
            for s in srcs:
                o = compile_one(s)
                if o is None:
                    return None
                objs.append(o)
            try:
                thunk = ref_thunk_c(top_fn, plan)
            except ValueError as e:
                self._na(res, f"native thunk: {e}")
                return None
        else:
            inc = top_src[:1] if top_src else [s for s in srcs if not s.endswith(".c")]
            for s in srcs:
                if s in inc:
                    continue
                o = compile_one(s)
                if o is None:
                    return None
                objs.append(o)
            name = cxx_name_of(top_fn, top)
            if not name:
                self._na(res, f"top {top_fn} is not a free function")
                return None
            nparams = sum(1 for p in plan if p["kind"] != "ret")
            has_ret = int(any(p["kind"] == "ret" for p in plan))
            # the standard headers and cs_spec.h come first: a design's macros (`#define N 8`, `#define B 4`)
            # must not reach them (spector_hls dct's params.h broke <vector> when it came after)
            prelude, body = (REF_THUNK_REAL if kind == "real" else REF_THUNK_CXX).split(THUNK_MARK)
            thunk = prelude + "".join(f'#include "{(ddir / s).resolve()}"\n' for s in inc)
            thunk += f"#define CS_NPARAMS {nparams}\n#define CS_HAS_RET {has_ret}\n#define CS_TOP {name}\n"
            # ... and the library member names the body uses are shielded from the design's macros
            # (spector_hls dct: `#define size imageW * imageH`)
            thunk += "".join(f'#pragma push_macro("{m}")\n#undef {m}\n' for m in THUNK_SHIELDED)
            thunk += body
            thunk += "".join(f'#pragma pop_macro("{m}")\n' for m in reversed(THUNK_SHIELDED))
        tf = wd / f"{tag}_thunk.cpp"
        tf.write_text(thunk)
        o = wd / f"{tag}_thunk.o"
        compile_thunk = [cxx, "-c", opt, "-w", *base, "-I", str(wd), *flags, *mflags, *extra, str(tf), "-o", str(o)]
        rc, so, se, _ = run(compile_thunk, cwd=str(ddir))
        if rc != 0 and "overloaded function" in se and top_fn.startswith("_Z"):
            # several functions share the top's name: pick the one the MLIR top was compiled from
            params = cxx_params(demangle(top_fn))
            # The result type comes from a call with the MLIR top's parameter types, and the cast picks
            # the overload: deducing it from `&CS_TOP` fails when the name also denotes a function
            # template (a top named `forward` next to `using namespace std;`, whose std::forward joins
            # the overload set; WIP / stream_hls FeedForward).
            args = ", ".join(f"cs_detail::cs_val<{p}>()" for p in params)
            pick = (f"#define CS_TOP_FN static_cast<decltype(CS_TOP({args})) (*)({', '.join(params)})>"
                    f"(&CS_TOP)\n")
            tf.write_text(thunk.replace("#define CS_TOP ", pick + "#define CS_TOP ", 1))
            rc, so, se, _ = run(compile_thunk, cwd=str(ddir))
        if rc != 0:
            (wd / f"{tag}_thunk.err").write_text(se)
            msg = first_err(se)
            if "different arity" in se or "differ in their result" in se:
                msg = "the C++ top and the MLIR top differ in arity / result (" + msg + ")"
            self._na(res, "native thunk does not compile: " + msg)
            return None
        objs.append(o)
        san = [x for x in extra if x.startswith("-fsanitize")]
        if kind == "real":
            link = [cxx, "-pthread", *san, str(wd / "cs_main.o"), *map(str, objs), "-lm", "-o", str(exe)]
        else:
            # Polygeist's LLVM build has no compiler-rt: sanitizer builds link with the system clang 14
            # driver and its runtime (clang 18 objects, same instrumentation ABI; checked on a stack
            # overflow / UBSan probe)
            link = [SAN_LINKER if san else CLANGXX, *san, str(wd / "cs_main.o"), *map(str, objs), "-lm", "-o",
                    str(exe)]
        rc, so, se, _ = run(link)
        added = []
        if rc != 0:
            # A function the design's own sources define in a file the cgeist command does not name (a
            # testbench helper main.cpp calls: GNN-virtual-node gin_vn_base's fetch_one_graph /
            # load_weights in load_weights_graph.cpp; W9r14-impl, DoD 1): compile that file too.
            und = sorted(set(re.findall(r"undefined reference to [`']([^'`(]+)", se)))
            extra_srcs = design_sources_defining(ddir, srcs, und) if und else []
            for s2 in extra_srcs:
                o2 = compile_one(s2)
                if o2 is None:
                    return None
                added.append(str(o2))
            if added:
                rc, so, se, _ = run(link[:-3] + added + link[-3:])
        if rc != 0:
            # Symbols of Vitis' math library (MEMOS #94; vitis_mathlib.py): its functions as they are; its
            # tables, which the real reference reads as C-simulation ap_int / ap_fixed objects, as a C++
            # definition copied element by element from the library's (synthesis-layout) copy.  The shim
            # reference reads the synthesis layout, like the candidate.
            relink = link[:-3] + added + link[-3:]
            got = self.mathlib_objects(wd, tag, self.undefined_mangled(relink))
            if isinstance(got, str):
                self._na(res, got)
                return None
            if got:
                vobjs, raw, info = got
                more = list(vobjs)
                if raw and kind == "real":
                    tsrc = wd / f"{tag}_vml_tables.cpp"
                    try:
                        tsrc.write_text(vitis_mathlib.table_source(info, demangle))
                    except ValueError as e:
                        self._na(res, f"Vitis math library: {e}"[:300])
                        return None
                    to = wd / f"{tag}_vml_tables.o"
                    rc2, _, se2, _ = run([cxx, "-c", opt, "-w", *base, *flags, str(tsrc), "-o", str(to)],
                                         cwd=str(ddir))
                    if rc2 != 0:
                        (wd / f"{tag}_vml_tables.err").write_text(se2)
                        self._na(res, "Vitis math library tables do not compile: " + first_err(se2))
                        return None
                    more.append(str(to))
                elif raw:
                    more += vitis_mathlib.defsym_flags(raw)
                res["vitis_mathlib"] = self.vml_used.get(str(wd), {}).get(tag, [])
                rc, so, se, _ = run(link[:-3] + added + more + link[-3:])
        if rc != 0:
            (wd / f"{tag}.link.err").write_text(se)
            und = re.findall(r"undefined reference to [`']([^'`]+)'", se)
            self._na(res, "native build does not link: " + (("undefined " + ", ".join(sorted(set(und))[:4]))
                                                            if und else first_err(se)))
            return None
        return exe


# ------------------------------------------------------------------------------------- reporting --

def probe_record(src, top, shim, work):
    """A run record for one probe file: cgeist (the harness command, run_hlsest.cgeist_cmd, with C.CGEIST,
    i.e. CGEIST_BIN) into work/probe-mlir/, module attributes stripped like the harness does."""
    import run_hlsest as R                 # noqa: E402  (imports the design catalogue only when probing)
    shim_dir = R.resolve_shim(shim)
    d = dict(dataset="probe", benchmark=src.stem, dir=str(src.parent), sources=[src.name], includes=[],
             defines=[], top=top)
    od = work / "probe-mlir"
    od.mkdir(parents=True, exist_ok=True)
    out = od / f"{src.stem}.mlir"
    cmd = R.cgeist_cmd(d, shim_dir, out, "*")
    rc, so, se, _ = run(cmd, cwd=str(src.parent), timeout=900)
    log = od / f"{src.stem}.cgeist.log"
    log.write_text(" ".join(shlex.quote(x) for x in cmd) + "\n--- stderr ---\n" + se)
    rec = dict(dataset="probe", benchmark=src.stem, dir=str(src.parent), sources=[src.name], top=top,
               cgeist_log=str(log), shim=str(shim_dir), mlir=str(out))
    if rc != 0 or not out.exists():
        rec.update(cgeist_status=f"cgeist error: {first_err(se)}", status="cgeist error")
        return rec
    text = re.sub(r"^module attributes \{.*\} \{$", "module {", out.read_text(), flags=re.M)
    out.write_text(text)
    fns = re.findall(r"func\.func\s+(?:private\s+)?@([\w$.]+)\(", text)
    pick = [f for f in fns if f == top or (f.startswith("_Z") and
                                           (cxx_name_of(f, f) or "").split("<")[0].split("::")[-1] == top)]
    rec.update(cgeist_status="ok", status="ok", top_fn=pick[0] if pick else top)
    return rec


NA_CLASSES = (
    (r"^no MLIR", "no MLIR (cgeist failed)"),
    (r"polygeist ops", "polygeist ops (need polygeist-opt)"),
    (r"argument buffers need", "argument buffers over 1 GiB"),
    (r"driver cannot fill", "top argument type"),
    (r"dialects", "other dialect"),
    (r"lowering failed|mlir-translate failed|clang on the lowered", "MLIR lowering fails"),
    (r"hls::stream argument", "hls::stream argument"),
    (r"argument layout", "argument layout differs"),
    (r"candidate does not link: undefined .*(stream|hls)", "candidate: undefined hls:: functions"),
    (r"candidate does not link", "candidate link"),
    (r"undefined .*(cordic_apfixed|hls::|hotbm|_ZN3hls)", "real headers: needs Vitis' csim math library"),
    (r"native build|native thunk", "native build"),
    (r"uninitialised", "reads uninitialised memory"),
    (r"no valid run.*(FPE|divides by zero)", "no valid run: division by zero"),
    (r"no valid run.*(overflow|SEGV|use-after|AddressSanitizer)", "no valid run: out-of-bounds access"),
    (r"no valid run.*timeout", "no valid run: timeout"),
    (r"no valid run", "no valid run"),
    (r"not a free function", "top not a free function"),
)


def reason_class(r):
    s, why = r.get("status", ""), r.get("reason", "")
    if s in ("equal", "mismatch"):
        return s
    for pat, cls in NA_CLASSES:
        if re.search(pat, why):
            return cls
    return "other: " + why[:60]


def summary(results):
    import collections
    per = collections.OrderedDict()
    via = collections.defaultdict(collections.Counter)
    for k, r in sorted(results.items()):
        if k.startswith("_"):
            continue
        ds = k.split("/", 1)[0]
        cls = reason_class(r)
        per.setdefault(ds, collections.Counter())[cls] += 1
        if cls in ("equal", "mismatch"):
            via[ds][r.get("ref_used", "?")] += 1
            via["**total**"][r.get("ref_used", "?")] += 1
    lines = ["| dataset | designs | checked (reference) | equal | mismatch | n/a (reasons) |",
             "|---|--:|--:|--:|--:|---|"]
    tot = collections.Counter()

    def row(name, c):
        n = sum(c.values())
        eq, mm = c.get("equal", 0), c.get("mismatch", 0)
        na = ", ".join(f"{k} {v}" for k, v in c.most_common() if k not in ("equal", "mismatch"))
        refs = ", ".join(f"{k} {v}" for k, v in sorted(via[name].items()))
        refs = f" ({refs})" if refs else ""
        b = "**" if name.startswith("**") else ""
        return f"| {name} | {b}{n}{b} | {b}{eq + mm}{b}{refs} | {b}{eq}{b} | {b}{mm}{b} | {na} |"

    for ds, c in per.items():
        lines.append(row(ds, c))
        tot.update(c)
    lines.append(row("**total**", tot))
    mism = [(k, r) for k, r in sorted(results.items()) if not k.startswith("_") and r.get("status") == "mismatch"]
    if mism:
        lines += ["", "| mismatch | reference | kind | first difference |", "|---|---|---|---|"]
        for k, r in mism:
            lines.append(f"| {k} | {r.get('ref_used', '')} | {r.get('mismatch_kind', '')} | "
                         f"{r.get('reason', '')[:160].replace('|', '/')} |")
    return "\n".join(lines)


def self_test():
    t = parse_type("memref<?x!llvm.struct<(array<84 x i32>, i17, f32)>>")
    assert t.k == "memref" and t.dims == [None] and t.elem.k == "struct", t
    assert size_align(t.elem) == (84 * 4 + 4 + 4, 4), size_align(t.elem)
    assert leaf_runs(t.elem) == [[0, 32, 0, 84, 4], [336, 17, 0, 1, 0], [340, 32, 2, 1, 0]], leaf_runs(t.elem)
    assert size_align(parse_type("i65")) == (16, 8)
    assert size_align(parse_type("i192")) == (24, 8)
    assert size_align(parse_type("!llvm.struct<(i8, i65)>")) == (24, 8)
    assert size_align(parse_type("!llvm.struct<packed (i8, i32)>")) == (5, 1)
    t = parse_type("memref<4x8xi16>")
    assert t.dims == [4, 8] and t.elem.bits == 16
    t = parse_type("memref<?x10xf32, strided<[?, 1], offset: ?>>")
    assert t.layout == "strided<[?, 1], offset: ?>", t.layout
    sig = top_signature("func.func @f(%arg0: memref<4xi32> {llvm.noalias}, %arg1: i6) -> i20 attributes {x} {",
                        "f")
    assert sig == (["memref<4xi32>", "i6"], ["i20"]), sig
    plan = plan_args(*sig)
    assert [p["kind"] for p in plan] == ["memref", "scalar", "ret"]
    w = wrapper_mlir("f", plan)
    assert "func.call @f(%cs0, %cs_v1) : (memref<4xi32>, i6) -> i20" in w, w
    assert cxx_name_of("_Z7forwardPA784_fPf", "forward") == "forward"
    assert cxx_name_of("cfun", "cfun") == "cfun"
    # streams: a method's class, a function's parameters, the top's stream arguments and their tokens
    assert split_cxx_method("hls::stream<ap_fixed<16, 5>, 0>::read(int&)") == \
        ("hls::stream<ap_fixed<16, 5>, 0>", "read(int&)")
    assert cxx_params("top(hls::stream<int, 0>&, int (*) [8], float)") == \
        ["hls::stream<int, 0>&", "int (*) [8]", "float"]
    methods = {"_ZN3hls6streamIiLi0EE4readEv": ("hls::stream<int, 0>", "read()",
                                                (["memref<?x!llvm.struct<(i32)>>"], ["i32"]))}
    assert stream_token_types(methods) == {"hls::stream<int, 0>": "i32"}
    assert top_stream_args("_Z3topRN3hls6streamIiLi0EEEPi", methods) == {0: "i32"}, \
        top_stream_args("_Z3topRN3hls6streamIiLi0EEEPi", methods)
    plan = plan_args(["memref<?x!llvm.struct<(i32)>>", "memref<4xi32>"], [], {0: "i32"})
    assert plan[0]["kind"] == "stream" and plan[0]["esize"] == 4 and plan[0]["elems"] == STREAM_TOKENS
    # dumps: call header, fixed arguments (memref<4xi32> with its guards), then stream sections
    fixed = (4 + 2 * plan[1]["guard"]) * 4
    a = (0).to_bytes(4, "little") + bytes(fixed) + (2).to_bytes(8, "little") + bytes(8)
    b = (0).to_bytes(4, "little") + bytes(fixed) + (2).to_bytes(8, "little") + bytes(4) + b"\x01\0\0\0"
    d = first_diff(a, b, plan)
    assert d["where"] == "stream" and d["token"] == 1 and d["tokens"] == [2, 2], d
    # an array of TAPA streams (O157): N streams of one memref of N objects, keyed object_stride apart
    plan = plan_args(["memref<3x!llvm.struct<(i32, i32)>>"], [], {0: "tapa[3]:!llvm.struct<(i32, i8)>"})
    assert plan[0]["count"] == 3 and plan[0]["stride"] == 8 and plan[0]["dims"] == [3], plan[0]
    assert plan[0]["elems"] == 3 * STREAM_TOKENS
    tok = (1).to_bytes(8, "little") + bytes(5)
    a = (0).to_bytes(4, "little") + tok + tok + tok
    b = (0).to_bytes(4, "little") + tok + tok + (1).to_bytes(8, "little") + b"\x02" + bytes(4)
    d = first_diff(a, b, plan)
    assert d["where"] == "stream" and d.get("stream") == 2, d
    # a TAPA async_mmap<int>& (O157): no streams of its own, five member streams keyed by field offset
    mm_ty = ("memref<?x!llvm.struct<(struct<(i32)>, struct<(i32, i32)>, struct<(i32)>, struct<(i32)>,"
             " struct<(i32, i32)>)>>")
    nos = {"hls::stream<tapa::internal::elem_t<int>,0>": "!llvm.struct<(i32, i8)>"}
    toks = tapa_mmap_tokens("int", nos)
    assert toks[1] == toks[3] == "!llvm.struct<(i32, i8)>" and toks[4] == "!llvm.struct<(i8, i8)>", toks
    assert tapa_mmap_tokens("float", nos)[1] is None
    plan = plan_args([mm_ty, "memref<4xi32>"], [], {0: {TAPA_MMAP: toks}})
    ents = spec_entries(plan)
    assert len(plan) == 2 and len(ents) == 7 and plan[0]["count"] == 0 and ents[0]["first_member"] == 2, ents
    assert [e["key_off"] for e in ents[2:]] == [0, 4, 12, 16, 20], ents
    assert all(e["parent"] == 0 for e in ents[2:]) and ents[2]["esize"] == 16 and ents[6]["esize"] == 2
    assert "cs_runs6" in spec_header(plan)
    # a struct token passed as a memref row (flowgnn gat's stream<node_t>, memref<?x2xi32>) moves 8 bytes
    nm = "_ZN3hls6streamI6node_tLi0EElsERKS1_"
    srt = cand_stream_runtime(f"func.func private @{nm}(memref<?xi32>, memref<?x2xi32>)\n",
                              f"declare void @{nm}(ptr, ptr, i64, i64, i64, ptr, ptr, i64, i64, i64, i64, i64)\n")
    assert "call void @cs_fifo_push(ptr %a0, ptr %a1, i32 8)" in srt, srt
    # graph_role (the `graph-*` modes): a batch of graphs as flowgnn passes it, and one graph as gnnbuilder does
    gp = plan_args(["i32", "memref<?xi32>", "memref<?x1xi16>", "memref<?x!llvm.struct<(array<9 x i32>)>>",
                    "memref<?x2xi32>", "memref<?x173x80xi16>", "memref<?xi16>", "memref<8x!llvm.struct<(i32, i32)>>",
                    "memref<4x!llvm.struct<(i32, f32)>>", "i8", "memref<600x3xi64>"], [])
    assert [graph_role(x) for x in gp] == [1, 1, 0, 4, 2, 0, 0, 3, 4, 0, 4], [graph_role(x) for x in gp]
    assert graph_shaped(gp) and not graph_shaped(gp[:4]) and not graph_shaped(gp[4:5])
    assert spec_header(gp).count(", 2}") >= 1 and "#define CS_GRAPH_INDEX_BITS 32" in spec_header(gp)
    tk = (1).to_bytes(4, "little") + b"\x01"
    a = (0).to_bytes(4, "little") + bytes((4 + 2 * plan[1]["guard"]) * 4)
    a += b"".join((0).to_bytes(8, "little") for _ in range(5))
    b2 = a[:-16] + (1).to_bytes(8, "little") + tk + (0).to_bytes(8, "little")
    d = first_diff(a + bytes(0), b2, plan)
    assert d["where"] == "stream" and d["arg"] == 5 and d["arg_type"].endswith(".write_data"), d
    # a float TAPA token {f32 val, i8 eot} (W9 round 20 review defect 6): the value is a float run
    assert tapa_token_runs(0, parse_type("!llvm.struct<(f32, i8)>")) == [[0, 32, 2, 1, 0], [4, 1, 0, 1, 0]]
    plan = plan_args(["memref<?x!llvm.struct<(i32, i32)>>"], [], {0: "tapa:!llvm.struct<(f64, i8)>"})
    assert plan[0]["kind"] == "stream" and plan[0]["esize"] == 16, plan[0]
    # a blocking read of an empty stream ends the run with the call's dump (W9 round 20 review defect 2)
    assert "cs_dump(cs_cur_call)" in DRIVER_MAIN and "cs_stop_at_blocking_read();" in DRIVER_MAIN
    assert "cs_block_hook = &CsHook::cs_run;" in REF_THUNK_REAL and BLOCKED_READ_EXIT == 88
    # NaN lanes of a packed integer (ap_uint<64> holding two floats): payloads differ, both NaN
    plan = plan_args(["memref<2xi64>", "memref<2xi32>"], [])
    lay = sum(dump_layout(plan))
    base = bytearray((0).to_bytes(4, "little") + bytes(lay))
    off = 4 + plan[0]["guard"] * 8
    a, b, c = bytearray(base), bytearray(base), bytearray(base)
    a[off:off + 4] = (0xFFC00000).to_bytes(4, "little")
    b[off:off + 4] = (0x7FE87AD9).to_bytes(4, "little")
    c[off:off + 4] = (0x3F800000).to_bytes(4, "little")
    assert nan_lane_only_diff(bytes(a), bytes(b), plan)
    assert not nan_lane_only_diff(bytes(a), bytes(c), plan)
    off32 = 4 + (2 + 2 * plan[0]["guard"]) * 8 + plan[1]["guard"] * 4
    d1, d2 = bytearray(base), bytearray(base)
    d1[off32:off32 + 4] = (0xFFC00000).to_bytes(4, "little")
    d2[off32:off32 + 4] = (0x7FE87AD9).to_bytes(4, "little")
    assert not nan_lane_only_diff(bytes(d1), bytes(d2), plan)   # an i32 leaf is an integer
    assert defines_function.__name__
    # the masked comparison's byte positions (W9 round 23 review D7)
    x = bytes(range(256)) * 40
    y = bytearray(x); y[5] ^= 1; y[9000] ^= 0x80
    assert differing_bytes(x, bytes(y)) == [5, 9000] and differing_bytes(x, x) == []
    # Vitis' math library (MEMOS #94): the intrinsic definitions, and a library build when the install has one
    import tempfile
    with tempfile.TemporaryDirectory(prefix="vml-selftest-", dir=str(WORK_DEFAULT.parent)) as td:
        for note in vitis_mathlib.self_test(GXX, LLC, vitis_include_dir()[0], td):
            print("  " + note)
    print("self-test ok")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--from", dest="src", help="run_hlsest.py / sweep_hlsfactory_v2.py result json")
    ap.add_argument("--datasets", default="")
    ap.add_argument("--benchmarks", default="")
    ap.add_argument("-j", type=int, default=8)
    ap.add_argument("--seeds", default="1,2")
    ap.add_argument("--modes", default="small,wide,pos")
    ap.add_argument("--ref", default="real,shim", help="reference kinds in order, comma separated: real (the "
                    "real Vitis headers, C simulation, g++), shim (the headers cgeist read, clang 18); the first "
                    "that can be built decides, the next ones run after a mismatch or an n/a")
    ap.add_argument("--all-refs", action="store_true", help="run every --ref kind even after an equal one")
    ap.add_argument("--no-ref-cache", action="store_true",
                    help="always rebuild the references (the cache is CS_REF_CACHE, default "
                         "~/hls-est-work/semantics-ref-cache)")
    ap.add_argument("--calls", type=int, default=2)
    ap.add_argument("--timeout", type=int, default=120)
    ap.add_argument("--work", default=str(WORK_DEFAULT))
    ap.add_argument("--out", default=None,
                    help="result JSON (default results/semantics.json; results/semantics-<set>.json for a "
                         "held-out run: semantics-heldout.json, semantics-heldout2.json)")
    ap.add_argument("--catalog", choices=("polygeist", "v2", "heldout", "heldout2"), default=None,
                    help="the catalogue of the --from run (default: from its _meta.catalog, else the harness "
                         "default).  For 'heldout' the locked split's designs are left out until Peter "
                         "releases them (hls-doc/heldout.md; 'heldout2' likewise, hls-doc/heldout2.md)")
    ap.add_argument("--keep", action="store_true", help="keep the dumps of equal runs")
    ap.add_argument("--top-fn", default="", help="check this MLIR function instead of each record's top "
                    "(to bisect a mismatch inside one design)")
    ap.add_argument("--probe", default="", help="check these C/C++ files (comma separated) instead of a run: "
                    "each is compiled with the harness cgeist command (CGEIST_BIN) into --work")
    ap.add_argument("--probe-top", default="top", help="the top function of the --probe files")
    ap.add_argument("--probe-shim", default=C.DEFAULT_SHIM, help="the shim of the --probe cgeist command")
    ap.add_argument("--md", default="", help="also write the hls-doc page (e.g. ../../hls-doc/semantics.md)")
    ap.add_argument("--page-from", default="", help="only write the --md page from this result json")
    ap.add_argument("--self-test", action="store_true")
    ap.add_argument("--vitis-mathlib", choices=("auto", "off"), default="auto",
                    help="link Vitis' installed math library libhlsmc++ (its tables and functions, compiled from "
                         "the install's bitcode at check time; MEMOS #94) into a build whose link lacks symbols "
                         "it defines (auto, the default), or never (off)")
    ap.add_argument("--max-buffer-gib", type=float, default=1.0,
                    help="largest total of argument buffers the driver allocates (GiB; default 1). Each run "
                         "holds them twice in the comparison: raise it only for a few designs at -j 1, "
                         "under the 12 GB cap of the resource rules (MEMOS #65)")
    a = ap.parse_args()
    global MAX_BUFFER_BYTES
    MAX_BUFFER_BYTES = int(a.max_buffer_gib * (1 << 30))
    if a.self_test:
        self_test()
        return
    if a.page_from:
        if not a.md:
            ap.error("--page-from needs --md")
        write_page(json.loads(Path(a.page_from).read_text()), a.md, a.page_from)
        return
    if not a.src and not a.probe:
        ap.error("--from or --probe is required")
    src = json.loads(Path(a.src).read_text()) if a.src else {"_meta": {"probe": a.probe}}
    recs = src.get("designs", src) if isinstance(src.get("designs"), dict) else src
    keys = [k for k in recs if not k.startswith("_")]
    global CATALOG
    # the run's catalogue: the first word of its _meta.catalog ('v2 (<root>)', 'heldout (<root>; split ...)',
    # 'polygeist'); a --catalog that contradicts it is refused (it would load the wrong designs, and a held-out
    # run must keep its locked designs out)
    run_catalog = (str((src.get("_meta") or {}).get("catalog") or "").split() or [None])[0]
    if run_catalog not in (None, "polygeist", "v2", *C.HELDOUT_SETS):
        run_catalog = None
    if a.catalog and run_catalog and a.catalog != run_catalog:
        ap.error(f"--catalog {a.catalog} contradicts the run's _meta.catalog ({run_catalog}) in {a.src}")
    CATALOG = a.catalog or (run_catalog if run_catalog in C.HELDOUT_SETS else None)
    heldout = CATALOG if CATALOG in C.HELDOUT_SETS else None       # the held-out set, or None
    wrong = sorted(k for k in keys if C.heldout_set_of_key(k) != heldout)
    if heldout and wrong:
        ap.error(f"{a.src} holds designs that are not of the held-out set {heldout!r} (e.g. {wrong[0]})")
    if not heldout and wrong:
        ap.error(f"{a.src} holds held-out designs but the catalogue is not a held-out one (hls-doc/heldout.md)")
    if a.out is None:
        a.out = str(C.RESULTS_DIR / (f"semantics-{heldout}.json" if heldout else "semantics.json"))
    elif C.heldout_set_of_name(Path(a.out).name) != heldout:
        ap.error(f"--out {a.out}: held-out results go to a file whose name contains their set ('heldout', "
                 "'heldout2'), others not")
    if heldout:
        import designs as D                  # noqa: E402  (harness module)
        if not D.heldout_locked_released(heldout):
            locked = D.heldout_locked_keys(name=heldout)
            n = len(keys)
            keys = [k for k in keys if k not in locked]
            if n != len(keys):
                print(f"held-out: {n - len(keys)} locked designs left out (hls-doc/heldout.md)")
    if a.datasets:
        ds = set(a.datasets.split(","))
        keys = [k for k in keys if k.split("/", 1)[0] in ds]
    if a.benchmarks:
        bs = set(a.benchmarks.split(","))
        keys = [k for k in keys if k.split("/", 1)[1] in bs or k in bs]
    for k in keys:
        complete_record(k, recs[k])
    if a.probe:
        recs = {}
        for probe_src in a.probe.split(","):
            rec = probe_record(Path(probe_src).resolve(), a.probe_top, a.probe_shim, Path(a.work))
            recs[f"probe/{Path(probe_src).stem}"] = rec
        keys = list(recs)
    if a.top_fn:
        # check another function of the same MLIR (bisecting a mismatch): the MLIR name and its C++ name
        cxx = cxx_name_of(a.top_fn, a.top_fn)
        if not cxx:
            ap.error(f"--top-fn {a.top_fn}: not a free function")
        recs = {k: dict(recs[k], top_fn=a.top_fn, top=cxx.split("<")[0].split("::")[-1]) for k in keys}
    chk = Checker(a)
    results = {}
    t0 = time.time()
    try:
        with cf.ThreadPoolExecutor(max_workers=a.j) as ex:
            futs = {ex.submit(chk.check, k, recs[k]): k for k in keys}
            for n, f in enumerate(cf.as_completed(futs), 1):
                k = futs[f]
                r = f.result()
                results[k] = r
                print(f"[{n}/{len(keys)}] {k}: {r['status']} {r['reason'][:150]}", flush=True)
    finally:
        if chk.vml is not None:
            chk.vml.cleanup()        # the library's temporary files (MEMOS #94)
    meta = dict(source=str(Path(a.src).resolve()) if a.src else None, source_meta=src.get("_meta", {}),
                probe=a.probe or None, cgeist=C.CGEIST if a.probe else None, seeds=a.seeds,
                modes=a.modes, calls=a.calls, timeout=a.timeout, mlir_bin=MLIR_BIN, clang18=CLANG, ref=a.ref,
                gcc=GXX, vitis_include=VITIS_INCLUDE_SRC, vitis_include_md5=chk.vitis_inc_md5,
                polygeist_opt=POLYGEIST_OPT if os.path.exists(POLYGEIST_OPT) else None,
                # the binary matters: a polygeist-opt older than Polygeist 6b7c55d6 lowers a same-rank
                # polygeist.subindex by elements, not rows (flowgnn's &edge_list_in[offset], W9r21-graph)
                polygeist_opt_md5=C.md5_of_file(POLYGEIST_OPT) if os.path.exists(POLYGEIST_OPT) else None,
                vitis_mathlib=dict(mode=a.vitis_mathlib, **(chk.vml.describe() if chk.vml is not None else {}),
                                   used_by=sorted(k for k, r in results.items() if r.get("vitis_mathlib"))),
                circt_head=C.git_hash(), elapsed_s=round(time.time() - t0, 1),
                finished=time.strftime("%Y-%m-%d %H:%M:%S"))
    results["_meta"] = meta
    Path(a.out).parent.mkdir(parents=True, exist_ok=True)
    Path(a.out).write_text(json.dumps(results, indent=1, sort_keys=True))
    print(summary(results))
    if a.md:
        write_page(results, a.md, a.out)


def write_page(results, path, src):
    """hls-doc page: the run configuration, the per-dataset table, the mismatches and the n/a designs."""
    meta = results.get("_meta", {})
    sm = meta.get("source_meta") or {}
    lines = ["# Semantic check of cgeist's MLIR", "",
             f"Generated by `tools/hls-est-validate/check_semantics.py --md` from `{src}` "
             f"({meta.get('finished', '')}). Do not edit by hand.", "",
             "Every design's cgeist MLIR is lowered to LLVM and run against a native build of the same sources "
             "on the same seeded inputs; every output buffer (and every token left in an hls::stream argument) "
             "is compared bit for bit. The reference is the first of `--ref` that builds: `real` = g++ with the "
             "real Vitis 2025.1 headers in C-simulation mode, `shim` = clang 18 with the headers cgeist read. "
             "See the script's docstring for the value modes and the rules.", "",
             "| setting | value |", "|---|---|",
             f"| MLIR from | `{meta.get('source')}` (cgeist md5 `{sm.get('cgeist_md5', '?')}`, shim "
             f"`{sm.get('shim', '?')}`) |",
             f"| references | `{meta.get('ref')}`; Vitis headers `{meta.get('vitis_include')}` (file list md5 "
             f"`{meta.get('vitis_include_md5')}`), `{meta.get('gcc')}` |",
             f"| inputs | modes `{meta.get('modes')}`, seeds `{meta.get('seeds')}`, {meta.get('calls')} calls per run, "
             f"timeout {meta.get('timeout')} s |"]
    sp = meta.get("second_pass")
    if sp:
        lines.append(f"| second pass | {len(sp.get('keys', []))} designs (mismatches, and n/a under the first "
                     f"reference) re-run with `--ref {sp.get('ref')} --all-refs` from `{sp.get('source')}` "
                     f"({sp.get('finished')}) |")
    lines += ["",
             "## Per dataset", "", summary(results), "", "## Designs that are not checked", "",
             "| design | reason |", "|---|---|"]
    for k, r in sorted(results.items()):
        if k.startswith("_") or r.get("status") in ("equal", "mismatch"):
            continue
        lines.append(f"| {k} | {r.get('reason', '')[:200].replace('|', '/')} |")
    Path(path).write_text("\n".join(lines) + "\n")


if __name__ == "__main__":
    main()
