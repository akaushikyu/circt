#!/usr/bin/env python3
"""Link Vitis' installed math library (libhlsmc++) into check_semantics.py's two builds (MEMOS #94).

Some designs call math functions or read tables that Vitis' headers only declare: the cordic tables
(`cordic_apfixed::circ_table_arctan_128`, ...), the log tables (`log_apfixed_reduce::log_lut_table<..>::array`,
...), `hls::powf(float, float)`, `hls::atan(double)`, `hls::cos(double)`, ...  Vitis' C simulation links them
from libhlsmc++; check_semantics.py's native reference and candidate do not link, or would read zero tables.
Peter allowed (MEMOS #94, 2026-10-24) linking that library from the install at check time, provided nothing of
it is copied into the repositories; temporary files live under ~/hls-est-work and are deleted after the run.

What the install holds (Vitis 2025.1, Windows): `win64/lib/libhlsmc++_39.bc`, the library as LLVM bitcode for
synthesis (triple fpga64-xilinx-none, Xilinx' LLVM 3.9 producer), and `win64/lib/csim/libhlsmc++-*.dll`, the C
simulation builds as Windows DLLs, which a Linux process cannot load.  So the bitcode is compiled for x86-64 here
with the LLVM 14 tools of the same install (`tps/lnx64/clang-14.0.0/bin`, which read the 3.9 bitcode):

1. `llvm-dis` the bitcode once per run, drop its metadata (its `fpga.*` nodes hold DILocations LLVM 14 rejects)
   and retarget it to x86_64-pc-linux-gnu (prepare()).
2. Per build: `opt -internalize -globaldce` keeps the requested symbols, what they reference and the library's
   static constructors (the tables are filled by them); every other symbol becomes internal, so nothing else
   of the library can clash with the design's own objects.
3. Xilinx' own intrinsics are replaced by IR definitions: `llvm.fpga.legacy.part.select` / `part.set` follow
   hls-llvm-project's constant folder (FoldLegacyPartSelect / FoldLegacyPartSet, ConstantFolding.cpp, reverse
   mode included); `_ssdm_string2bits(dst, str, radix, I, S, Q, O, N, C99)`, the synthesis ap_fixed string
   constructor that Vitis' front end evaluates at compile time, becomes a call of a generated C++ function that
   builds the same ap_fixed_base<W, I, S, Q, O, N> from the string with the C-simulation headers (the width W
   is the destination alloca's).  `llvm.fpga.recip` / `rsqrt` become 1 / x and 1 / sqrt(x).
4. `llc` (the install's LLVM 14) compiles the result; the generated C++ is compiled with g++ against the real
   Vitis headers (C-simulation mode).

The library's static constructors run at init priority 101, before the design's.  A requested table keeps the
library's (synthesis) layout under a private name `__cs_vml_<symbol>`: the candidate, compiled by cgeist with the
synthesis headers, reads the same layout and gets the real name by `--defsym`; the native reference reads the
C-simulation ap_int / ap_fixed objects, so it gets a generated C++ definition of the table whose elements are
built bit by bit from the library's copy (`table_source`).
"""

import atexit
import hashlib
import os
import re
import shutil
import subprocess
import tempfile
import threading
from pathlib import Path

import common as C

# The install root: <root>/Vitis/include is C.VITIS_INCLUDE_WSL.
VITIS_ROOT = Path(os.environ.get("CS_VITIS_ROOT", str(Path(C.VITIS_INCLUDE_WSL).parents[1])))
# libhlsmc++ as bitcode: the Windows install has it under win64, a Linux install under lnx64.
MATHLIB_CANDIDATES = ("win64/lib/libhlsmc++_39.bc", "lnx64/lib/libhlsmc++_39.bc")
LLVM_BIN_CANDIDATES = ("tps/lnx64/clang-14.0.0/bin",)
TMP_ROOT = Path(os.environ.get("CS_VITIS_MATHLIB_TMP", str(Path.home() / "hls-est-work" / "tmp-vitis-mathlib")))

RAW_PREFIX = "__cs_vml_"


def find_mathlib():
    """(bitcode, LLVM bin directory) of the install, or None when either is missing."""
    bc = os.environ.get("CS_VITIS_MATHLIB")
    bcs = [Path(bc)] if bc else [VITIS_ROOT / c for c in MATHLIB_CANDIDATES]
    bins = [Path(os.environ["CS_VITIS_LLVM_BIN"])] if os.environ.get("CS_VITIS_LLVM_BIN") else \
        [VITIS_ROOT / c for c in LLVM_BIN_CANDIDATES]
    bc = next((p for p in bcs if p.is_file()), None)
    llvm = next((p for p in bins if all((p / t).exists() for t in ("llvm-dis", "opt", "llc"))), None)
    return (bc, llvm) if bc and llvm else None


def _run(cmd, timeout=900):
    try:
        p = subprocess.run(C.mem_limited(cmd), capture_output=True, text=True, errors="replace", timeout=timeout)
    except subprocess.TimeoutExpired:
        return "timeout", "", f"timed out after {timeout} s"
    return p.returncode, p.stdout, p.stderr


def _err(se, n=300):
    lines = [l for l in se.splitlines() if l.strip() and not l.startswith("!") and "invalid debug info" not in l]
    return " | ".join(lines)[:n]


# ------------------------------------------------------------------------------------------ IR edits --

_ATTACHMENT = re.compile(r",? ![A-Za-z_.][\w.]* ![0-9]+")


def strip_and_retarget(src, dst):
    """The disassembled library without metadata, debug intrinsics and its fpga64 target."""
    with open(src) as f, open(dst, "w") as g:
        for line in f:
            if line.startswith("!") or line.startswith("target datalayout"):
                continue
            if line.startswith("target triple"):
                line = 'target triple = "x86_64-pc-linux-gnu"\n'
            elif "@llvm.dbg." in line and line.lstrip().startswith("call"):
                continue
            elif "!" in line:
                line = _ATTACHMENT.sub("", line)
            g.write(line)


def _cast_i32(val, n, name):
    """IR lines turning the i32 `val` into iN as %name (n bits)."""
    if n == 32:
        return [f"  %{name} = add i32 {val}, 0"]
    return [f"  %{name} = {'zext' if n > 32 else 'trunc'} i32 {val} to i{n}"]


def part_select_def(n):
    """fpga.legacy.part.select(V, Lo, Hi) on iN: V[Hi:Lo] in the low bits, bit-reversed when Lo > Hi."""
    b = [f"define internal i{n} @__cs_fpga_ps_i{n}(i{n} %v, i32 %lo, i32 %hi) {{", "entry:",
         "  %rev = icmp ugt i32 %lo, %hi",
         "  %l = select i1 %rev, i32 %hi, i32 %lo",
         "  %h = select i1 %rev, i32 %lo, i32 %hi",
         "  %d = sub i32 %h, %l",
         f"  %k = sub i32 {n - 1}, %d"]
    b += _cast_i32("%l", n, "lN") + _cast_i32("%k", n, "kN")
    b += [f"  %s = lshr i{n} %v, %lN",
          f"  %u = shl i{n} %s, %kN",
          f"  %f = lshr i{n} %u, %kN",
          f"  %r = call i{n} @llvm.bitreverse.i{n}(i{n} %f)",
          f"  %rf = lshr i{n} %r, %kN",
          f"  %res = select i1 %rev, i{n} %rf, i{n} %f",
          f"  ret i{n} %res", "}"]
    return "\n".join(b)


def part_set_def(n, m):
    """fpga.legacy.part.set(V, R, Lo, Hi) on iN with an iM R: V with V[Hi:Lo] = R (R's low bits, reversed
    when Lo > Hi)."""
    if m == n:
        ext = f"  %rN = add i{n} %rep, 0"
    else:
        ext = f"  %rN = {'zext' if n > m else 'trunc'} i{m} %rep to i{n}"
    b = [f"define internal i{n} @__cs_fpga_pset_i{n}_i{m}(i{n} %v, i{m} %rep, i32 %lo, i32 %hi) {{", "entry:",
         "  %rev = icmp ugt i32 %lo, %hi",
         "  %l = select i1 %rev, i32 %hi, i32 %lo",
         "  %h = select i1 %rev, i32 %lo, i32 %hi",
         "  %d = sub i32 %h, %l",
         f"  %k = sub i32 {n - 1}, %d"]
    b += _cast_i32("%l", n, "lN") + _cast_i32("%k", n, "kN")
    b += [ext,
          f"  %mask = lshr i{n} -1, %kN",
          f"  %rm = and i{n} %rN, %mask",
          f"  %r = call i{n} @llvm.bitreverse.i{n}(i{n} %rm)",
          f"  %rr = lshr i{n} %r, %kN",
          f"  %rs = select i1 %rev, i{n} %rr, i{n} %rm",
          f"  %rsh = shl i{n} %rs, %lN",
          f"  %msh = shl i{n} %mask, %lN",
          f"  %nm = xor i{n} %msh, -1",
          f"  %keep = and i{n} %v, %nm",
          f"  %res = or i{n} %keep, %rsh",
          f"  ret i{n} %res", "}"]
    return "\n".join(b)


FP_TYPES = {"f16": "half", "f32": "float", "f64": "double"}


def recip_rsqrt_def(op, suffix):
    t = FP_TYPES[suffix]
    one = {"half": "0xH3C00", "float": "1.0", "double": "1.0"}[t]
    if op == "recip":
        body = [f"  %r = fdiv {t} {one}, %x"]
    else:
        body = [f"  %s = call {t} @llvm.sqrt.{suffix}({t} %x)", f"  %r = fdiv {t} {one}, %s"]
    return "\n".join([f"define internal {t} @__cs_fpga_{op}_{suffix}({t} %x) {{", "entry:", *body,
                      f"  ret {t} %r", "}"])


_PS = re.compile(r"@llvm\.fpga\.legacy\.part\.select\.i(\d+)\b")
_PSET = re.compile(r"@llvm\.fpga\.legacy\.part\.set\.i(\d+)\.i(\d+)\b")
_RR = re.compile(r"@llvm\.fpga\.(recip|rsqrt)\.(f16|f32|f64)\b")
_S2B = re.compile(r"call void \(\.\.\.\) @_ssdm_string2bits\(i8\* (%[\w.]+), i8\* ([^,]+), i32 ([^,]+), "
                  r"i32 (-?\d+), i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+), i32 (\d+)\)")
_ALLOCA = re.compile(r"^\s*(%[\w.]+) = alloca i(\d+)\b")
_BITCAST = re.compile(r"^\s*(%[\w.]+) = bitcast i(\d+)\* (%[\w.]+) to i8\*")


def rewrite_module(text):
    """(IR with Xilinx' intrinsics and _ssdm_string2bits replaced, the string2bits tuples (W, I, S, Q, O, N))."""
    tuples = set()
    out = []
    widths = {}
    for line in text.splitlines():
        if line.startswith("define "):
            widths = {}
        m = _ALLOCA.match(line) or _BITCAST.match(line)
        if m:
            widths[m.group(1)] = int(m.group(2))
        if "@_ssdm_string2bits(" in line and not line.startswith("declare"):
            s = _S2B.search(line)
            if not s or s.group(1) not in widths:
                raise ValueError("unrecognised _ssdm_string2bits call: " + line.strip()[:200])
            w = widths[s.group(1)]
            i, sg, q, o, n = (int(s.group(k)) for k in (4, 5, 6, 7, 8))
            tuples.add((w, i, sg, q, o, n))
            line = line[:s.start()] + (f"call void @__cs_string2bits(i8* {s.group(1)}, i8* {s.group(2)}, "
                                       f"i32 {s.group(3)}, i32 {w}, i32 {i}, i32 {sg}, i32 {q}, i32 {o}, "
                                       f"i32 {n})") + line[s.end():]
        out.append(line)
    text = "\n".join(l for l in out if not re.match(r"declare .*@(llvm\.fpga\.|_ssdm_string2bits)", l)) + "\n"
    ps = sorted({int(n) for n in _PS.findall(text)})
    pset = sorted({(int(n), int(m)) for n, m in _PSET.findall(text)})
    rr = sorted(set(_RR.findall(text)))
    text = _PS.sub(lambda m: f"@__cs_fpga_ps_i{m.group(1)}", text)
    text = _PSET.sub(lambda m: f"@__cs_fpga_pset_i{m.group(1)}_i{m.group(2)}", text)
    text = _RR.sub(lambda m: f"@__cs_fpga_{m.group(1)}_{m.group(2)}", text)
    left = sorted(set(re.findall(r"@llvm\.fpga\.[\w.]+", text)))
    if left:
        raise ValueError("unsupported Xilinx intrinsics: " + ", ".join(left[:5]))
    defs = [part_select_def(n) for n in ps] + [part_set_def(n, m) for n, m in pset] + \
        [recip_rsqrt_def(op, sfx) for op, sfx in rr]
    bitrev = sorted({n for n in ps} | {n for n, _ in pset})
    decls = [f"declare i{n} @llvm.bitreverse.i{n}(i{n})" for n in bitrev
             if f"@llvm.bitreverse.i{n}(" not in text]
    decls += [f"declare {FP_TYPES[s]} @llvm.sqrt.{s}({FP_TYPES[s]})" for s in {s for op, s in rr if op == "rsqrt"}
              if f"declare {FP_TYPES[s]} @llvm.sqrt.{s}(" not in text]
    if tuples:
        decls.append("declare void @__cs_string2bits(i8*, i8*, i32, i32, i32, i32, i32, i32, i32)")
    return text + "\n".join(decls + defs) + "\n", tuples


def string2bits_source(tuples):
    """C++ (C-simulation headers) defining __cs_string2bits for the (W, I, S, Q, O, N) tuples."""
    lines = ["// generated by check_semantics.py (vitis_mathlib.py): the synthesis _ssdm_string2bits",
             "#include <ap_fixed.h>", "#include <cstdlib>", "#include <cstring>",
             "template <int W, int I, bool S, int Q, int O, int N>",
             "static void cs_s2b(void *dst, const char *s, int radix) {",
             "  ap_fixed_base<W, I, S, (ap_q_mode)Q, (ap_o_mode)O, N> v(s, (signed char)radix);",
             "  unsigned char *d = (unsigned char *)dst;",
             "  std::memset(d, 0, (W + 7) / 8);",
             "  for (int b = 0; b < W; ++b) if (v[b]) d[b / 8] |= (unsigned char)(1u << (b % 8));",
             "}",
             'extern "C" void __cs_string2bits(void *dst, const char *s, int radix, int w, int i, int sg, '
             'int q, int o, int n) {']
    for w, i, sg, q, o, n in sorted(tuples):
        lines.append(f"  if (w == {w} && i == {i} && sg == {sg} && q == {q} && o == {o} && n == {n}) "
                     f"return cs_s2b<{w}, {i}, {'true' if sg else 'false'}, {q}, {o}, {n}>(dst, s, radix);")
    lines += ["  std::abort();", "}"]
    return "\n".join(lines) + "\n"


def int_width(type_text, types):
    """The integer width an LLVM element type wraps (structs with one member, down to an iN), or None."""
    t = type_text.strip()
    for _ in range(32):
        m = re.fullmatch(r"i(\d+)", t)
        if m:
            return int(m.group(1))
        if t in types:
            t = types[t]
            continue
        m = re.fullmatch(r"\{\s*(.+?)\s*\}", t)
        if m and re.fullmatch(r'%"[^"]*"|%[\w.]+|i\d+', m.group(1)):   # one member
            t = m.group(1)
            continue
        return None
    return None


def alloc_size(w):
    """Bytes per element of an iW array (LLVM's x86-64 layout; C simulation's ap_private gives the same)."""
    store = (w + 7) // 8
    if store <= 8:
        return 1 << (store - 1).bit_length()
    return (store + 7) // 8 * 8


# ----------------------------------------------------------------------------------------- library --

class Mathlib:
    """One run's view of libhlsmc++: prepared once, built per design, removed by cleanup()."""

    def __init__(self, gxx, vitis_include):
        found = find_mathlib()
        self.bc, self.llvm = found if found else (None, None)
        self.gxx, self.vitis_include = gxx, vitis_include
        self.lock = threading.Lock()
        self.tmp = None
        self.ll = None
        self.funcs, self.globs, self.types = set(), {}, {}
        self.built = {}
        self.error = None

    @property
    def available(self):
        return self.bc is not None

    def describe(self):
        return dict(bitcode=str(self.bc) if self.bc else None, llvm_bin=str(self.llvm) if self.llvm else None,
                    bitcode_md5=self._md5() if self.bc else None)

    def _md5(self):
        h = hashlib.md5()
        with open(self.bc, "rb") as f:
            for chunk in iter(lambda: f.read(1 << 20), b""):
                h.update(chunk)
        return h.hexdigest()

    def prepare(self):
        """Disassemble, strip and index the library once (thread safe). False with self.error set on failure."""
        with self.lock:
            if self.ll is not None or self.error:
                return self.error is None
            if not self.available:
                self.error = "Vitis math library not found (looked for %s under %s)" % (
                    " / ".join(MATHLIB_CANDIDATES), VITIS_ROOT)
                return False
            TMP_ROOT.mkdir(parents=True, exist_ok=True)
            self.tmp = Path(tempfile.mkdtemp(prefix="run-", dir=str(TMP_ROOT)))
            atexit.register(self.cleanup)
            raw = self.tmp / "lib.dis.ll"
            rc, _, se = _run([str(self.llvm / "llvm-dis"), str(self.bc), "-o", str(raw)])
            if rc != 0:
                self.error = "llvm-dis of the Vitis math library failed: " + _err(se)
                return False
            self.ll = self.tmp / "lib.ll"
            strip_and_retarget(raw, self.ll)
            raw.unlink()
            for line in open(self.ll):
                if line.startswith("define "):
                    m = re.search(r"@([\w.$]+)\(", line)
                    if m and " internal " not in line[:40] and " private " not in line[:40]:
                        self.funcs.add(m.group(1))
                elif line.startswith("@"):
                    m = re.match(r"@([\w.$]+) = (?:(?:dso_local|local_unnamed_addr|unnamed_addr|hidden) )*"
                                 r"(global|constant) (\[(\d+) x (.+?)\])", line)
                    if m and " internal " not in line and " private " not in line:
                        self.globs[m.group(1)] = (int(m.group(4)), m.group(5))
                elif line.startswith("%"):
                    m = re.match(r'(%[\w."<>, ()\-]+?) = type (.+)$', line.rstrip())
                    if m:
                        self.types[m.group(1)] = m.group(2)
            return True

    def defines(self, sym):
        return sym in self.funcs or sym in self.globs

    def cleanup(self):
        """Remove this run's temporary files (and the temporary root when nothing else is in it)."""
        if self.tmp is not None:
            shutil.rmtree(self.tmp, ignore_errors=True)
            self.tmp = None
            try:
                TMP_ROOT.rmdir()
            except OSError:
                pass

    def build(self, syms):
        """Objects defining `syms` (library symbols): (objects, {table: raw name}, {table: (count, width)}),
        built once per symbol set and run.  Raises ValueError on a failure."""
        if not self.prepare():
            raise ValueError(self.error)
        key = tuple(sorted(set(syms)))
        with self.lock:
            entry = self.built.setdefault(key, {"lock": threading.Lock()})
        with entry["lock"]:
            if "result" not in entry:
                try:
                    entry["result"] = self._build(list(key), "b%d" % len(self.built) + "-" +
                                                  hashlib.md5("\n".join(key).encode()).hexdigest()[:10])
                except ValueError as e:
                    entry["result"] = e
        if isinstance(entry["result"], ValueError):
            raise entry["result"]
        objs, raw, info = entry["result"]
        return list(objs), dict(raw), dict(info)

    def _build(self, syms, tag):
        tables = [s for s in syms if s in self.globs]
        bdir = self.tmp / tag
        if bdir.exists():
            shutil.rmtree(bdir)
        bdir.mkdir(parents=True)
        red = bdir / "red.ll"
        rc, _, se = _run([str(self.llvm / "opt"), "-internalize",
                          "-internalize-public-api-list=" + ",".join(syms), "-globaldce", str(self.ll), "-S",
                          "-o", str(red)])
        if rc != 0:
            raise ValueError("opt on the Vitis math library failed: " + _err(se))
        text, tuples = rewrite_module(red.read_text())
        red.unlink()
        # tables under private names (the candidate gets the real one by --defsym, the reference a C++
        # definition), 16-byte aligned like the candidate's i128 arrays
        info = {}
        for s in tables:
            count, elem = self.globs[s]
            w = int_width(elem, self.types)
            if w is None:
                raise ValueError(f"table {s}: element type {elem} is not an integer")
            info[s] = (count, w)
            text = re.sub(r"@" + re.escape(s) + r"(?![\w.$])", "@" + RAW_PREFIX + s, text)
            text = re.sub(r"(?m)^(@" + re.escape(RAW_PREFIX + s) + r" = .*), align \d+$", r"\1, align 16", text)
        # the library's constructors fill its tables: run them before the design's (and the reference's
        # table copies, which are default priority)
        text = re.sub(r"(@llvm\.global_ctors = .*)", lambda m: m.group(1).replace("{ i32 65535,", "{ i32 101,"),
                      text)
        ll = bdir / "vml.ll"
        ll.write_text(text)
        obj = bdir / "vml.o"
        rc, _, se = _run([str(self.llvm / "llc"), "-O1", "-filetype=obj", "-relocation-model=pic", str(ll),
                          "-o", str(obj)])
        if rc != 0:
            raise ValueError("llc on the Vitis math library failed: " + _err(se))
        ll.unlink()
        objs = [str(obj)]
        if tuples:
            src = bdir / "vml_s2b.cpp"
            src.write_text(string2bits_source(tuples))
            o = bdir / "vml_s2b.o"
            rc, _, se = _run([self.gxx, "-c", "-O1", "-w", "-std=gnu++14", "-I", str(self.vitis_include), str(src),
                              "-o", str(o)])
            if rc != 0:
                raise ValueError("the string2bits runtime does not compile: " + _err(se))
            objs.append(str(o))
        return objs, {s: RAW_PREFIX + s for s in tables}, info


def defsym_flags(raw_names):
    """Linker flags giving each table its real name on the candidate's side."""
    return [f"-Wl,--defsym={s}={r}" for s, r in sorted(raw_names.items())]


def table_source(info, demangle):
    """C++ (C-simulation headers) defining each table from the library's copy, element by element, for the
    native reference."""
    lines = ["// generated by check_semantics.py (vitis_mathlib.py): the math library's tables, C-simulation layout",
             "#include <hls_math.h>", "#include <cstring>", "#include <type_traits>",
             "namespace cs_vml {",
             "template <class T> typename std::enable_if<std::is_arithmetic<T>::value, T>::type",
             "load(const unsigned char *p) { T t; std::memcpy(&t, p, sizeof t); return t; }",
             "template <class T> typename std::enable_if<!std::is_arithmetic<T>::value, T>::type",
             "load(const unsigned char *p) {",
             "  T t = 0;",
             "  for (int b = 0; b < T::width; ++b) t[b] = (p[b / 8] >> (b % 8)) & 1;",
             "  return t;",
             "}",
             "}  // namespace cs_vml"]
    for k, (s, (count, w)) in enumerate(sorted(info.items())):
        name = demangle(s)
        if not name or "(" in name.split("<")[0]:
            raise ValueError(f"table {s}: cannot name it in C++ ({name})")
        stride = alloc_size(w)
        lines.append(f'extern "C" const unsigned char {RAW_PREFIX}{s}[];')
        lines.append(f"typedef std::remove_cv<std::remove_reference<decltype({name}[0])>::type>::type cs_vml_t{k};")
        lines.append(f"static_assert(sizeof(cs_vml_t{k}) == {stride}, \"{s}: C-simulation element size\");")
        elems = ", ".join(f"cs_vml::load<cs_vml_t{k}>({RAW_PREFIX}{s} + {j * stride})" for j in range(count))
        lines.append(f"const cs_vml_t{k} {name}[{count}] = {{{elems}}};")
    return "\n".join(lines) + "\n"


# ---------------------------------------------------------------------------------------- self-test --

def fold_part_select(v, n, lo, hi):
    """hls-llvm-project's FoldLegacyPartSelect on Python integers (the reference of the self-test)."""
    rev = lo > hi
    lo, hi = min(lo, hi), max(lo, hi)
    length = hi - lo + 1
    r = (v >> lo) & ((1 << length) - 1)
    if rev:
        r = int(format(r, f"0{length}b")[::-1], 2)
    return r


def fold_part_set(v, n, rep, lo, hi):
    """hls-llvm-project's FoldLegacyPartSet on Python integers."""
    rev = lo > hi
    lo, hi = min(lo, hi), max(lo, hi)
    length = hi - lo + 1
    r = rep & ((1 << length) - 1)
    if rev:
        r = int(format(r, f"0{length}b")[::-1], 2)
    mask = ((1 << length) - 1) << lo
    return (v & ~mask & ((1 << n) - 1)) | (r << lo)


def self_test(gxx, llc, vitis_include, work):
    """The intrinsic definitions against the constant folder's semantics (always), and, when the install has
    the library, a build of one table and one function checked against their mathematical values on both
    sides' layouts (no library content is part of the test).  Returns a list of notes."""
    import random
    notes = []
    work = Path(work)
    work.mkdir(parents=True, exist_ok=True)
    cases = [(13, 0), (32, 0), (64, 0)]
    ir = ["; vitis_mathlib self-test"]
    ir += [part_select_def(n) for n, _ in cases]
    ir += [part_set_def(13, 5), part_set_def(64, 64), part_set_def(32, 1)]
    ir += [f"declare i{n} @llvm.bitreverse.i{n}(i{n})" for n in (13, 32, 64)]
    text = "\n".join(ir).replace("define internal", "define") + "\n"
    (work / "ps.ll").write_text(text)
    p = subprocess.run([llc, "-O1", "-filetype=obj", "-relocation-model=pic", str(work / "ps.ll"), "-o",
                        str(work / "ps.o")], capture_output=True, text=True)
    assert p.returncode == 0, p.stderr[:500]
    rnd = random.Random(7)
    sel, st = [], []
    for n, _ in cases:
        for _ in range(40):
            v = rnd.getrandbits(n)
            lo, hi = rnd.randrange(n), rnd.randrange(n)
            sel.append((n, v, lo, hi))
    for n, m in ((13, 5), (64, 64), (32, 1)):
        for _ in range(40):
            v, r = rnd.getrandbits(n), rnd.getrandbits(m)
            lo, hi = rnd.randrange(n), rnd.randrange(n)
            st.append((n, m, v, r, lo, hi))
    ctype = {1: "unsigned char", 5: "unsigned char", 13: "unsigned short", 32: "unsigned", 64: "unsigned long long"}
    c = ["#include <stdio.h>"]
    c += [f"{ctype[n]} __cs_fpga_ps_i{n}({ctype[n]}, unsigned, unsigned);" for n, _ in cases]
    c += [f"{ctype[n]} __cs_fpga_pset_i{n}_i{m}({ctype[n]}, {ctype[m]}, unsigned, unsigned);"
          for n, m in ((13, 5), (64, 64), (32, 1))]
    c.append("int main(void) {")
    for n, v, lo, hi in sel:
        c.append(f'  printf("%llu\\n", (unsigned long long)(__cs_fpga_ps_i{n}({v}ULL, {lo}, {hi}) & '
                 f'{(1 << n) - 1}ULL));')
    for n, m, v, r, lo, hi in st:
        c.append(f'  printf("%llu\\n", (unsigned long long)(__cs_fpga_pset_i{n}_i{m}({v}ULL, {r}ULL, {lo}, {hi})'
                 f' & {(1 << n) - 1}ULL));')
    c.append("  return 0;\n}")
    (work / "ps_main.c").write_text("\n".join(c) + "\n")
    p = subprocess.run([gxx, "-x", "c", str(work / "ps_main.c"), "-x", "none", str(work / "ps.o"), "-o",
                        str(work / "ps.exe")], capture_output=True, text=True)
    assert p.returncode == 0, p.stderr[:500]
    got = [int(x) for x in subprocess.run([str(work / "ps.exe")], capture_output=True, text=True).stdout.split()]
    want = [fold_part_select(v, n, lo, hi) for n, v, lo, hi in sel] + \
        [fold_part_set(v, n, r, lo, hi) for n, m, v, r, lo, hi in st]
    assert got == want, [(i, g, w) for i, (g, w) in enumerate(zip(got, want)) if g != w][:5]
    assert int_width('%"a"', {'%"a"': '{ %"b<1, 2>" }', '%"b<1, 2>"': "{ i29 }"}) == 29
    assert [alloc_size(w) for w in (6, 20, 29, 44, 65, 128, 256)] == [1, 4, 4, 8, 16, 16, 32]
    notes.append("intrinsics: %d part.select and %d part.set cases equal the constant folder" % (len(sel), len(st)))

    lib = Mathlib(gxx, vitis_include)
    if not lib.available:
        notes.append("library build skipped: no libhlsmc++ bitcode or LLVM tools under %s" % VITIS_ROOT)
        return notes
    try:
        sym, fn = "_ZN14cordic_apfixed21circ_table_arctan_128E", "_ZN3hls4sqrtEd"
        objs, raw, info = lib.build([sym, fn])
        assert info[sym] == (128, 128), info
        # candidate side: the library's own layout, 128-bit words of ap_ufixed<128, 2>
        cmain = work / "vml_cand.cpp"
        cmain.write_text('#include <cstdio>\nextern "C" const unsigned char %s[];\n'
                         'namespace hls { double sqrt(double); }\nint main() {\n'
                         '  for (int k = 0; k < 24; ++k) { const unsigned char *p = %s + 16 * k; long double v = 0;\n'
                         '    for (int b = 15; b >= 0; --b) v = v * 256 + p[b];\n'
                         '    std::printf("%%.17Lg\\n", v / 85070591730234615865843651857942052864.0L); }\n'
                         '  std::printf("%%.17g\\n", hls::sqrt(2.0));\n}\n' % (raw[sym], raw[sym]))
        # native side: the C-simulation table defined from the library's copy
        (work / "vml_tab.cpp").write_text(table_source(info, lambda s: "cordic_apfixed::circ_table_arctan_128"))
        nmain = work / "vml_native.cpp"
        nmain.write_text('#include <hls_math.h>\n#include <cstdio>\nint main() {\n'
                         '  for (int k = 0; k < 24; ++k) std::printf("%.17g\\n", '
                         'cordic_apfixed::circ_table_arctan_128[k].to_double());\n'
                         '  std::printf("%.17g\\n", hls::sqrt(2.0));\n}\n')
        outs = []
        for name, srcs in (("cand", [cmain]), ("native", [nmain, work / "vml_tab.cpp"])):
            exe = work / f"vml_{name}.exe"
            p = subprocess.run([gxx, "-O1", "-w", "-std=gnu++14", "-I", str(vitis_include), *map(str, srcs), *objs,
                                "-lm", "-o", str(exe)], capture_output=True, text=True)
            assert p.returncode == 0, (name, p.stderr[:800])
            outs.append([float(x) for x in subprocess.run([str(exe)], capture_output=True, text=True).stdout.split()])
            exe.unlink()
        import math
        for name, vals in zip(("candidate", "native"), outs):
            for k in range(24):
                assert abs(vals[k] - math.atan(2.0 ** -k)) <= 1e-15 * max(1.0, abs(vals[k])), (name, k, vals[k])
            assert vals[24] == math.sqrt(2.0), (name, vals[24])
        notes.append("library: arctan table (both layouts) and hls::sqrt(double) built from %s" % lib.bc)
    finally:
        lib.cleanup()
    return notes
