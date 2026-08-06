#!/usr/bin/env python3
"""Bit-exactness of a cgeist shim THROUGH cgeist (what hls-est actually receives).

    python3 check_shim_cgeist.py [--shim exactclass] [--cgeist /mnt/d/HLS/Polygeist/build/bin/cgeist]
                                 [--seed 1] [--n 30] [--out-dir ~/hls-est-work/shim-check-cgeist]

check_shim.py compiles the shim with the host clang++ only, so it cannot see a
frontend bug (e.g. Polygeist's canonicaliser rewriting `x - C` on integers wider
than 64 bits). Here every expression is compiled three ways and the raw bit
patterns are compared:

  vitis       g++ -std=c++17 against the real Vitis include directory
  host        host clang++ against the shim
  cg-runtime  cgeist (the harness flags + <shim>/cgeist_flags, -emit-llvm) against
              the shim, inputs as function arguments (the arithmetic is executed)
  cg-const    the same with the inputs as constants (what cgeist folds)

Two C entry points per expression and variant return the low / high 64 bits of
the result's raw bits; a C driver prints them. The expressions are a targeted list
(wide-integer constants, rounding-mode ties, the double -> ap_int 25-bit path of
ap_int_base(double), signed 1-bit types) plus `--n` seeded random ones per run.
--shim real (the real Vitis headers through cgeist, track W11) has no headers of its own, so
the host variant is skipped. --bit-ops adds the bit and range operations (select / set, range read
and assignment with constant, runtime and reversed indices, concat, the reductions,
countLeadingZeros), which only shims that implement them can build. --flag-drop / --flag-add
remove / append cgeist flags (e.g. --flag-drop=-fxlx-apint-promote compares the promotion choice).
Exit status 1 when any comparison against Vitis mismatches (hls::exp may differ by
one LSB, and a fixed-point min / -1 LSB division is `divcsim`, where g++ runs Vitis'
C-simulation path and csynth differs (VITIS_NOTES N11): counted, not failed); 2 when
a build step fails.
"""
import argparse
import random
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import common as C          # noqa: E402
import run_hlsest as R      # noqa: E402
from check_shim import div_csim_overflow, wrap_raw  # noqa: E402

CLANG = "/mnt/d/HLS/Polygeist/llvm-project/build/bin/clang"
CLANGXX = "/mnt/d/HLS/Polygeist/llvm-project/build/bin/clang++"

FX = [(16, 5, True, "AP_TRN", "AP_WRAP"), (12, 4, True, "AP_TRN", "AP_WRAP"), (32, 8, True, "AP_TRN", "AP_WRAP"),
      (24, 10, True, "AP_TRN", "AP_WRAP"), (40, 12, True, "AP_TRN", "AP_WRAP"), (10, 3, False, "AP_TRN", "AP_WRAP"),
      (18, 6, True, "AP_RND", "AP_SAT"), (14, 5, True, "AP_RND_ZERO", "AP_WRAP"), (12, 4, True, "AP_RND_INF", "AP_SAT"),
      (12, 6, True, "AP_RND_MIN_INF", "AP_WRAP"), (16, 7, True, "AP_RND_CONV", "AP_SAT_SYM"),
      (10, 4, True, "AP_TRN_ZERO", "AP_SAT"), (72, 20, True, "AP_TRN", "AP_WRAP"), (66, 30, False, "AP_TRN", "AP_WRAP"),
      (1, 1, True, "AP_TRN", "AP_WRAP"), (2, 1, True, "AP_RND", "AP_SAT")]
IN = [(1, True), (1, False), (8, True), (13, True), (32, True), (16, False), (40, False), (48, False), (70, True),
      (80, True), (100, False), (128, False)]


def ft(t):
    W, I, S, Q, O = t
    return f"ap_{'' if S else 'u'}fixed<{W},{I},{Q},{O}>"


def it(t):
    W, S = t
    return f"ap_{'' if S else 'u'}int<{W}>"


def gen_exprs(seed, n):
    rng = random.Random(seed)

    def fval(t, small=False):
        W, I, S, Q, O = t
        F = W - I
        span = min(W - 1, 20 if small else 40)
        lo, hi = (-(1 << span), (1 << span) - 1) if S else (0, (1 << span) - 1)
        return rng.randint(lo, hi) / 2.0 ** F

    def ival(t):
        W, S = t
        span = min(W - 1, 50)
        lo, hi = (-(1 << span), 1 << span) if S else (0, 1 << span)
        return float(rng.randint(lo, hi))

    def tie(t):
        W, I, S, Q, O = t
        F = W - I
        k = rng.randint(1, 1 << min(I + F - 3, 10))
        v = (2 * k + 1) / 2.0 ** (F + 1)
        return -v if S else v

    E = []  # (name, code using inputs a, b and defining r, a, b)
    # -- targeted: rounding-mode ties (negative), exact negatives, wide-integer constants
    for q in ["AP_TRN_ZERO", "AP_RND_ZERO", "AP_RND_MIN_INF", "AP_RND_INF", "AP_RND_CONV", "AP_RND"]:
        t = (10, 4, True, q, "AP_WRAP")
        E.append((f"tie_{q}", f"{ft(t)} r = a;", tie(t), 0.0))
    E.append(("exactneg_TRN_ZERO", "ap_fixed<8,3,AP_TRN_ZERO,AP_WRAP> r = a;", -1.5, 0.0))
    E.append(("fx2fx_negtie_RND_INF", "ap_fixed<40,20> x = a; ap_fixed<16,5,AP_RND_INF> r = x;", -(2 * 77 + 1) / 2.0 ** 12, 0.0))
    E.append(("fx32prod_RND_INF", "ap_fixed<32,8> x = a; ap_fixed<32,8> y = b; ap_fixed<16,5,AP_RND_INF> r = x * y;",
              -0.5, 7 * 2.0 ** -11))
    E.append(("u100_sub1", "ap_uint<100> x = (unsigned long long)a; ap_uint<100> r = (x << 40) - 1;", 2.0 ** 30, 0.0))
    E.append(("i80_sub3", "ap_int<80> x = (long long)a; ap_int<80> r = x - 3;", -5.0, 0.0))
    E.append(("u128_range", "ap_uint<128> x = (unsigned long long)a; x = (x << 64) | ap_uint<128>(7); ap_uint<128> r = x.range(15, 0);", 1.0, 0.0))
    E.append(("i70_dec", "ap_int<70> r = (long long)a; --r;", 0.0, 0.0))
    E.append(("u512_range256", "ap_uint<512> x = (unsigned long long)a; x = (x << 300) | (x << 100) | x; ap_uint<256> h = x.range(255, 0); ap_uint<128> r = h >> 64;", 3.0, 0.0))
    # -- targeted: ap_int_base(double) keeps the shifted mantissa in 25 signed bits
    for d in [1073741824.0, 16777219.0, -33554431.0, 4503599627370497.0, 12345.75, 2.0 ** 24, -(2.0 ** 24) - 5,
              2.0 ** 51 + 3, 9007199254740992.0]:
        E.append(("dbl2int32", "ap_int<32> r = a;", d, 0.0))
    for d in [4294967295.0, 8388607.0, 2.0 ** 39 + 1, 2.0 ** 53]:
        E.append(("dbl2uint40", "ap_uint<40> r = a;", d, 0.0))
    for d in [1073741824.0, 16777219.0, -123456789.0]:
        E.append(("flt2int32", "ap_int<32> r = (float)a;", d, 0.0))
    E.append(("dbl2int80", "ap_int<80> r = a;", -(2.0 ** 40) - 7, 0.0))
    # -- targeted: signed 1-bit types (stored as one bit, read as 0 / -1)
    E.append(("i1_widen", "ap_int<1> x = (int)a; ap_int<8> r = x;", 1.0, 0.0))
    E.append(("i1_add", "ap_int<1> x = (int)a; ap_int<1> y = (int)b; auto r = x + y;", 1.0, 1.0))
    E.append(("i1_mul", "ap_int<1> x = (int)a; ap_int<1> y = (int)b; auto r = x * y;", 1.0, 1.0))
    E.append(("i1_neg", "ap_int<1> x = (int)a; auto r = -x;", 1.0, 0.0))
    E.append(("i1_cmp", "ap_int<1> x = (int)a; bool r = x < 0;", 1.0, 0.0))
    E.append(("i1_shr", "ap_int<1> x = (int)a; ap_int<1> r = x >> 3;", 1.0, 0.0))
    E.append(("i1_div", "ap_int<8> x = (int)a; ap_int<1> y = (int)b; auto r = x / y;", 6.0, 1.0))
    E.append(("i1_toint", "ap_int<1> x = (int)a; ap_int<32> r = x.to_int();", 1.0, 0.0))
    E.append(("f1_widen", "ap_fixed<1,1> x = a; ap_fixed<8,4> r = x;", -1.0, 0.0))
    E.append(("f1_add", "ap_fixed<1,1> x = a; ap_fixed<4,2> y = b; auto r = x + y;", -1.0, 1.5))
    E.append(("f1_toint", "ap_fixed<1,1> x = a; ap_int<8> r = x.to_int();", -1.0, 0.0))
    E.append(("f1_double", "ap_fixed<1,1> x = a; ap_fixed<16,8> r = x.to_double() * 3;", -1.0, 0.0))
    # -- random
    for _ in range(n):
        c = rng.choice(["bin", "bin", "bin", "conv", "sqrt", "exp", "int", "int", "cmp", "compound", "dbl2int"])
        if c == "bin":
            x, y = rng.choice(FX), rng.choice(FX)
            op = rng.choice(["+", "-", "*", "/"])
            a, b = fval(x), fval(y, small=True)
            if op == "/" and b == 0:
                b = 1.0
            nm = f"bin{op}"
            if op == "/" and div_csim_overflow(x, round(a * 2 ** (x[0] - x[1])), y,
                                               wrap_raw(round(b * 2 ** (y[0] - y[1])), y)):
                nm = "divcsim"
            E.append((nm, f"{ft(x)} x = a; {ft(y)} y = b; auto r = x {op} y;", a, b))
        elif c == "conv":
            x, y = rng.choice(FX), rng.choice(FX)
            E.append(("conv", f"{ft(x)} x = a; {ft(y)} r = x;", fval(x), 0.0))
        elif c == "sqrt":
            x = rng.choice([t for t in FX if t[3] == "AP_TRN" and 2 <= t[0] <= 32 and t[1] >= 1])
            E.append(("sqrt", f"{ft(x)} x = a; auto r = hls::sqrt(x);", fval(x), 0.0))
        elif c == "exp":
            x = rng.choice([(16, 5, True, "AP_TRN", "AP_WRAP"), (32, 8, True, "AP_TRN", "AP_WRAP"),
                            (12, 4, True, "AP_TRN", "AP_WRAP")])
            E.append(("exp", f"{ft(x)} x = a; auto r = hls::exp(x);", fval(x, small=True) / 16, 0.0))
        elif c == "int":
            x, y = rng.choice(IN), rng.choice(IN)
            op = rng.choice(["+", "-", "*", "/", "%", "&", "|", "^"])
            a, b = ival(x), ival(y)
            if op in "/%" and b == 0:
                b = 3.0
            cx = "long long" if x[1] else "unsigned long long"
            cy = "long long" if y[1] else "unsigned long long"
            a = a if x[1] else abs(a)
            b = b if y[1] else (abs(b) or 3.0)
            E.append((f"int{op}", f"{it(x)} x = ({cx})a; {it(y)} y = ({cy})b; auto r = x {op} y;", a, b))
        elif c == "cmp":
            x, y = rng.choice(FX), rng.choice(FX)
            op = rng.choice(["<", ">", "<=", ">=", "==", "!="])
            E.append((f"cmp{op}", f"{ft(x)} x = a; {ft(y)} y = b; bool r = x {op} y;", fval(x, small=True),
                      fval(y, small=True)))
        elif c == "compound":
            x, y = rng.choice(FX), rng.choice(FX)
            op = rng.choice(["+=", "-=", "*=", "/="])
            b = fval(y, small=True) or 1.0
            a = fval(x)
            nm = f"cmpd{op}"
            if op == "/=" and div_csim_overflow(x, round(a * 2 ** (x[0] - x[1])), y,
                                                wrap_raw(round(b * 2 ** (y[0] - y[1])), y)):
                nm = "divcsim"
            E.append((nm, f"{ft(x)} r = a; {ft(y)} y = b; r {op} y;", a, b))
        else:
            x = rng.choice(IN)
            e = rng.randint(0, 60)
            d = rng.choice([-1, 1]) * (2.0 ** e + rng.randint(0, 1 << min(e, 20)))
            E.append(("dbl2int", f"{it(x)} r = a;", d if x[1] else abs(d), 0.0))
    return E


def gen_bit_exprs(seed):
    """Bit and range operations (W11): every one goes through the Vitis bit builtins under
    __SYNTHESIS__ (ap_common.h _AP_ROOT_op_*), and through ap_private in the g++ reference."""
    rng = random.Random(seed * 7919 + 1)
    E = []
    U = "unsigned long long"
    for W in (8, 12, 33, 64, 70, 100):
        for _ in range(3):
            hi, lo = sorted(rng.sample(range(W), 2), reverse=True)
            a = float(rng.randint(0, (1 << min(W, 52)) - 1))
            b = float(rng.randint(0, (1 << min(W, 40)) - 1))
            # constant indices, forward and reversed
            E.append((f"rng{W}", f"ap_uint<{W}> x = ({U})a; ap_uint<{W}> r = x.range({hi}, {lo});", a, 0.0))
            E.append((f"rngrev{W}", f"ap_uint<{W}> x = ({U})a; ap_uint<{W}> r = x.range({lo}, {hi});", a, 0.0))
            E.append((f"rngset{W}", f"ap_uint<{W}> r = ({U})a; r.range({hi}, {lo}) = ({U})b;", a, b))
            E.append((f"rngsetrev{W}", f"ap_uint<{W}> r = ({U})a; r.range({lo}, {hi}) = ({U})b;", a, b))
            E.append((f"rngop{W}", f"ap_int<{W}> r = (long long)a; r({hi}, {lo}) = ({U})b;", a, b))
            # runtime indices: hi and lo packed into b
            enc = float(hi * 4096 + lo)
            E.append((f"rngrt{W}", f"ap_uint<{W}> x = ({U})a; int h = (int)b / 4096, l = (int)b % 4096; "
                                   f"ap_uint<{W}> r = x.range(h, l);", a, enc))
            E.append((f"rngrtrev{W}", f"ap_uint<{W}> x = ({U})a; int h = (int)b / 4096, l = (int)b % 4096; "
                                      f"ap_uint<{W}> r = x.range(l, h);", a, enc))
            E.append((f"rngrtset{W}", f"ap_uint<{W}> r = ({U})a; int h = (int)b / 4096, l = (int)b % 4096; "
                                      f"r.range(h, l) = ({U})(a * 3);", a, enc))
            k = rng.randrange(W)
            E.append((f"bit{W}", f"ap_int<{W}> x = (long long)a; bool r = x[{k}];", a, 0.0))
            E.append((f"bitrt{W}", f"ap_int<{W}> x = (long long)a; bool r = x[(int)b];", a, float(k)))
            E.append((f"bitset{W}", f"ap_int<{W}> r = (long long)a; r[{k}] = (int)b & 1;", a, float(rng.randint(0, 1))))
            E.append((f"bitsetrt{W}", f"ap_uint<{W}> r = ({U})a; r.set_bit((int)b, true); r.clear((int)b ^ 1);",
                      a, float(k)))
        for red in ("and_reduce", "or_reduce", "xor_reduce", "nand_reduce", "nor_reduce", "xnor_reduce"):
            v = rng.choice([0.0, float((1 << min(W, 52)) - 1), float(rng.randint(0, (1 << min(W, 52)) - 1))])
            E.append((f"{red}{W}", f"ap_uint<{W}> x = ({U})a; bool r = x.{red}();", v, 0.0))
        E.append((f"clz{W}", f"ap_uint<{W}> x = ({U})a; ap_int<32> r = x.countLeadingZeros();",
                  float(rng.randint(0, (1 << min(W, 52)) - 1) >> rng.randint(0, 20)), 0.0))
        E.append((f"clz0_{W}", f"ap_uint<{W}> x = ({U})a; ap_int<32> r = x.countLeadingZeros();", 0.0, 0.0))
    for A, B in ((5, 7), (12, 20), (33, 31), (64, 8), (3, 100)):
        a = float(rng.randint(0, (1 << min(A, 52)) - 1))
        b = float(rng.randint(0, (1 << min(B, 52)) - 1))
        E.append((f"cat{A}_{B}", f"ap_uint<{A}> x = ({U})a; ap_uint<{B}> y = ({U})b; ap_uint<{A + B}> r = (x, y);", a, b))
        E.append((f"catm{A}_{B}", f"ap_int<{A}> x = (long long)a; ap_uint<{B}> y = ({U})b; "
                                  f"ap_uint<{A + B}> r = x.concat(y);", a, b))
    # ap_fixed bit access
    E.append(("fxrng", "ap_fixed<16,5> x = a; ap_uint<8> r = x.range(11, 4);", -3.40625, 0.0))
    E.append(("fxrngset", "ap_fixed<16,5> r = a; r.range(7, 0) = (unsigned long long)b;", 2.75, 201.0))
    E.append(("fxbit", "ap_fixed<12,4> x = a; bool r = x[10];", -1.25, 0.0))
    E.append(("fxbitset", "ap_ufixed<12,4> r = a; r[3] = 1; r[11] = 0;", 9.5, 0.0))
    # shifts and unary operators on narrow and 32-bit types (the integer promotion question)
    for W, S in ((8, False), (8, True), (17, True), (32, False), (32, True), (31, False)):
        t = f"ap_{'' if S else 'u'}int<{W}>"
        c = "long long" if S else U
        a = float(rng.randint(-(1 << (W - 2)), (1 << (W - 2)) - 1)) if S else float(rng.randint(0, (1 << (W - 1)) - 1))
        E.append((f"shl{W}{'s' if S else 'u'}", f"{t} x = ({c})a; {t} r = x << 5;", a, 0.0))
        E.append((f"shr{W}{'s' if S else 'u'}", f"{t} x = ({c})a; {t} r = x >> 3;", a, 0.0))
        E.append((f"neg{W}{'s' if S else 'u'}", f"{t} x = ({c})a; {t} r = -x;", a, 0.0))
        E.append((f"not{W}{'s' if S else 'u'}", f"{t} x = ({c})a; {t} r = ~x;", a, 0.0))
        E.append((f"shlw{W}{'s' if S else 'u'}", f"{t} x = ({c})a; ap_int<64> r = x << 9;", a, 0.0))
        E.append((f"mulw{W}{'s' if S else 'u'}", f"{t} x = ({c})a; {t} y = ({c})b; auto r = x * y;", a,
                  float(rng.randint(1, 1000))))
    return E


COMMON = "#include <ap_fixed.h>\n#include <ap_int.h>\n#include <hls_math.h>\n"
SHIM_HELPERS = """
template <class T> unsigned long long LO(const T &r) { typedef unsigned _BitInt(T::width) U; return (unsigned long long)(U)r.V; }
template <class T> unsigned long long HI(const T &r) {
  typedef unsigned _BitInt(T::width) U;
  if constexpr (T::width > 64) return (unsigned long long)((U)r.V >> 64); else return 0ull;
}
static unsigned long long LO(bool r) { return r; }
static unsigned long long HI(bool) { return 0ull; }
"""
VITIS_HELPERS = """
#include <stdio.h>
template <class T> void PR(int k, const char *n, const T &r) {
  const int W = T::width;
  ap_uint<W> bits = r.range(W - 1, 0);
  unsigned long long lo, hi = 0;
  if constexpr (W <= 64) lo = bits.to_uint64();
  else { ap_uint<64> l = bits.range(63, 0); ap_uint<(W > 64 ? W - 64 : 1)> h = bits.range(W - 1, 64); lo = l.to_uint64(); hi = h.to_uint64(); }
  printf("bx%d_%s %llx:%llx\\n", k, n, hi, lo);
}
static void PR(int k, const char *n, bool r) { printf("bx%d_%s 0:%llx\\n", k, n, (unsigned long long)r); }
int main() {"""


def write_sources(E, out):
    sh = [COMMON, SHIM_HELPERS]
    for k, (n, code, a, b) in enumerate(E):
        sh.append(f'extern "C" unsigned long long bx{k}_r_lo(double a, double b) {{ {code} return LO(r); }}')
        sh.append(f'extern "C" unsigned long long bx{k}_r_hi(double a, double b) {{ {code} return HI(r); }}')
        sh.append(f'extern "C" unsigned long long bx{k}_c_lo() {{ const double a = {a!r}, b = {b!r}; {code} return LO(r); }}')
        sh.append(f'extern "C" unsigned long long bx{k}_c_hi() {{ const double a = {a!r}, b = {b!r}; {code} return HI(r); }}')
    (out / "bx_shim.cpp").write_text("\n".join(sh) + "\n")
    # The same functions split into bx_shim_<i>.cpp (--chunks): one cgeist run on hundreds of
    # functions over the real headers takes longer than the step timeout.
    for f in out.glob("bx_shim_*.cpp"):
        f.unlink()
    dr = ["#include <stdio.h>"]
    for k in range(len(E)):
        dr.append(f"unsigned long long bx{k}_r_lo(double, double); unsigned long long bx{k}_r_hi(double, double);"
                  f" unsigned long long bx{k}_c_lo(void); unsigned long long bx{k}_c_hi(void);")
    dr.append("int main(void) {")
    for k, (n, code, a, b) in enumerate(E):
        pn = n.replace("%", "%%")  # a printf format: `int%` would eat an argument
        dr.append(f'  printf("bx{k}_{pn} %llx:%llx %llx:%llx\\n", bx{k}_r_hi({a!r}, {b!r}), bx{k}_r_lo({a!r}, {b!r}),'
                  f' bx{k}_c_hi(), bx{k}_c_lo());')
    dr.append("  return 0;\n}")
    (out / "bx_drv.c").write_text("\n".join(dr) + "\n")
    vi = [COMMON, VITIS_HELPERS]
    for k, (n, code, a, b) in enumerate(E):
        vi.append(f'  {{ const double a = {a!r}, b = {b!r}; {code} PR({k}, "{n}", r); }}')
    vi.append("  return 0;\n}")
    (out / "bx_vitis.cpp").write_text("\n".join(vi) + "\n")
    with open(out / "bx_list.txt", "w") as f:
        for k, (n, code, a, b) in enumerate(E):
            f.write(f"bx{k}_{n}\t{a!r}\t{b!r}\t{code}\n")


def sh(cmd, out, log, timeout=1800):
    p = subprocess.run(cmd, cwd=out, capture_output=True, text=True, errors="replace", timeout=timeout)
    (out / log).write_text(" ".join(cmd) + "\n\n" + p.stdout + "\n--- stderr ---\n" + p.stderr)
    return p


def parse(text, two):
    d = {}
    for line in text.splitlines():
        f = line.split()
        if two and len(f) == 3:
            d[f[0]] = (f[1], f[2])
        elif not two and len(f) == 2:
            d[f[0]] = f[1]
    return d


def raw(s):
    hi, lo = s.split(":")
    return (int(hi, 16) << 64) | int(lo, 16)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--shim", default="exactclass")
    ap.add_argument("--cgeist", default=C.CGEIST)
    ap.add_argument("--vitis-include", default=C.VITIS_INCLUDE_WSL)
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--n", type=int, default=30)
    ap.add_argument("--out-dir", default=str(Path.home() / "hls-est-work" / "shim-check-cgeist"))
    ap.add_argument("--bit-ops", action="store_true", help="add the bit and range operations (gen_bit_exprs)")
    ap.add_argument("--no-math", action="store_true", help="leave out hls::sqrt / hls::exp")
    ap.add_argument("--flag-drop", action="append", default=[], help="drop this cgeist flag (and a preceding -Xclang)")
    ap.add_argument("--flag-add", action="append", default=[], help="append this cgeist flag")
    ap.add_argument("--chunks", type=int, default=1, help="compile the cgeist variant in this many parts, in parallel")
    args = ap.parse_args()
    shim = R.resolve_shim(args.shim)
    out = Path(args.out_dir) / f"s{args.seed}"
    out.mkdir(parents=True, exist_ok=True)
    E = gen_exprs(args.seed, args.n)
    if args.no_math:
        E = [e for e in E if e[0] not in ("sqrt", "exp")]
    if args.bit_ops:
        E += gen_bit_exprs(args.seed)
    write_sources(E, out)
    chunks = []
    if args.chunks > 1:
        body = (out / "bx_shim.cpp").read_text().split("\n")
        head = [COMMON, SHIM_HELPERS]
        fns = [l for l in body if l.startswith('extern "C" unsigned long long bx')]
        per = (len(fns) + args.chunks - 1) // args.chunks
        per += (-per) % 4          # keep the four functions of an expression together
        for i in range(0, len(fns), per):
            name = f"bx_shim_{i // per}.cpp"
            (out / name).write_text("\n".join(head + fns[i:i + per]) + "\n")
            chunks.append(name)
    # A shim without headers of its own (shim/real: the Vitis install's headers) has no host variant.
    with_host = (Path(shim) / "ap_int.h").is_file()
    shim_flags = []
    for f in R.shim_cgeist_flags(shim):
        if f in args.flag_drop:
            if shim_flags and shim_flags[-1] == "-Xclang":
                shim_flags.pop()
            continue
        shim_flags.append(f)
    flags = ["--function=*", "-S", "-emit-llvm", "--hls-annotate", "--raise-scf-to-affine", "--memref-fullrank",
             *shim_flags, *args.flag_add, f"-resource-dir={C.CLANG_RESOURCE_DIR}", "-I", str(shim)]
    if chunks:
        import concurrent.futures as cf
        lls = [c.replace(".cpp", ".ll") for c in chunks]
        with cf.ThreadPoolExecutor(min(16, len(chunks))) as ex:
            res = list(ex.map(lambda c: sh([args.cgeist, c, *flags, "-o", c.replace(".cpp", ".ll")], out,
                                            f"cgeist-{c}.log"), chunks))
        for c, p in zip(chunks, res):
            if p.returncode != 0:
                print(f"[cgeist {c}] failed rc={p.returncode} (log {out / ('cgeist-' + c + '.log')})")
                print(p.stderr[-3000:])
                sys.exit(2)
        cg_steps = [("cg-link", [CLANG, "-O0", "-w", *lls, "bx_drv.c", "-lm", "-o", "bx_cg"])]
    else:
        cg_steps = [("cgeist", [args.cgeist, "bx_shim.cpp", *flags, "-o", "bx_shim.ll"]),
                    ("cg-link", [CLANG, "-O0", "-w", "bx_shim.ll", "bx_drv.c", "-lm", "-o", "bx_cg"])]
    steps = [
        *cg_steps,
        ("host-cc", [CLANGXX, "-std=c++17", "-O0", "-w", "-fwrapv", "-I", str(shim), "-c", "bx_shim.cpp", "-o", "bx_host.o"]),
        ("host-drv", [CLANG, "-O0", "-w", "-c", "bx_drv.c", "-o", "bx_drv.o"]),
        ("host-link", [CLANGXX, "bx_host.o", "bx_drv.o", "-lm", "-o", "bx_host"]),
        ("vitis-cc", ["g++", "-std=c++17", "-O0", "-w", "-I", args.vitis_include, "bx_vitis.cpp", "-o", "bx_vitis"]),
    ]
    if not with_host:
        steps = [s for s in steps if not s[0].startswith("host-")]
    for name, cmd in steps:
        p = sh(cmd, out, f"{name}.log")
        if p.returncode != 0:
            print(f"[{name}] failed rc={p.returncode} (log {out / (name + '.log')})")
            print(p.stderr[-3000:])
            sys.exit(2)
    res = {}
    for name, exe in (("cg", "./bx_cg"), ("host", "./bx_host"), ("vitis", "./bx_vitis")):
        if name == "host" and not with_host:
            res[name] = ""
            continue
        p = subprocess.run([exe], cwd=out, capture_output=True, text=True, timeout=600)
        (out / f"{name}.out").write_text(p.stdout)
        res[name] = p.stdout
    v = parse(res["vitis"], False)
    h = {k: x[1] for k, x in parse(res["host"], True).items()}
    cg = parse(res["cg"], True)
    names = [f"bx{k}_{n}" for k, (n, *_rest) in enumerate(E)]
    bad = {"host": 0, "cg-runtime": 0, "cg-const": 0}
    lsb = 0
    known = 0
    lines = []
    for k, nm in enumerate(names):
        vv = v.get(nm)
        if vv is None:
            lines.append(f"MISSING-VITIS {nm}")
            bad["host"] += 1
            continue
        got = {"host": h.get(nm, "?"), "cg-runtime": cg.get(nm, ("?", "?"))[0], "cg-const": cg.get(nm, ("?", "?"))[1]}
        if not with_host:
            del got["host"]
        tags = []
        hard = False
        for lab, val in got.items():
            if val == vv:
                continue
            if "_exp" in nm and val != "?" and abs(raw(val) - raw(vv)) == 1:
                tags.append(f"{lab}:1LSB")
                lsb += 1
                continue
            if "_divcsim" in nm and val != "?":
                tags.append(f"{lab}:known(divcsim)={val}")
                known += 1
                continue
            tags.append(f"{lab}={val}")
            bad[lab] += 1
            hard = True
        if tags:
            n, code, a, b = E[k]
            lines.append(f"{'BAD' if hard else 'TOL'} {nm:28s} vitis={vv:24s} {' '.join(tags)}   [a={a!r} b={b!r}] {code}")
    (out / "report.txt").write_text("\n".join(lines) + "\n")
    print(f"shim={shim} cgeist={args.cgeist} flags={' '.join(shim_flags + args.flag_add)}\nseed={args.seed} n={args.n}: {len(E)} expressions x 3 "
          f"(host clang++, cgeist runtime, cgeist constants) vs g++ + Vitis headers")
    print(f"mismatches: host {bad['host']}, cgeist runtime {bad['cg-runtime']}, cgeist constants {bad['cg-const']}"
          f" (hls::exp 1-LSB differences tolerated: {lsb}; known divcsim differences: {known})")
    for line in lines:
        print("  " + line)
    sys.exit(1 if any(bad.values()) else 0)


if __name__ == "__main__":
    main()
