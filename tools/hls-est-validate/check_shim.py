#!/usr/bin/env python3
"""Bit-exactness check of a cgeist header shim against the real Vitis headers.

    python3 check_shim.py [--shim shim/exactclass] [--vitis-include /mnt/a/Vitis/2025.1/Vitis/include]
                          [--seed 1] [--n 40] [--out-dir ~/hls-est-work/shim-check] [--keep]

One C++ program is generated (the design-table expressions of
hls-doc/notes/REPORT.md / feas/A/design.md 1.1 plus `--n` seeded
random constants or operations per category), compiled twice - with clang++
against the shim and with g++ -std=c++14 against the Vitis include directory -
and the raw bit patterns printed by the two binaries are compared line by
line.  Every category must match exactly except `exp`, where the Vitis table
algorithm is allowed to differ from floor(exp(x)*2^F) by one LSB (counted and
reported, not failed).  Exit status 1 when any other category mismatches.

This compiles the shim with the HOST clang++ only: it validates the shim's C++,
not what cgeist makes of it (a frontend bug on wide integers is invisible here).
check_shim_cgeist.py runs expressions through cgeist as well.
"""
import argparse
import math
import os
import random
import subprocess
import sys
from pathlib import Path

CLANGXX = "/mnt/d/HLS/Polygeist/llvm-project/build/bin/clang++"
GXX = "g++"

# (W, I, signed, Q, O)
FIXED_TYPES = [
    (16, 5, True, "AP_TRN", "AP_WRAP"), (16, 8, True, "AP_TRN", "AP_WRAP"), (32, 8, True, "AP_TRN", "AP_WRAP"),
    (32, 16, True, "AP_TRN", "AP_WRAP"), (24, 8, True, "AP_TRN", "AP_WRAP"), (28, 10, True, "AP_TRN", "AP_WRAP"),
    (9, 3, True, "AP_TRN", "AP_WRAP"), (12, 4, True, "AP_TRN", "AP_WRAP"), (8, 4, True, "AP_TRN", "AP_WRAP"),
    (8, -2, True, "AP_TRN", "AP_WRAP"), (8, 10, True, "AP_TRN", "AP_WRAP"), (18, 6, True, "AP_TRN", "AP_WRAP"),
    (16, 6, False, "AP_TRN", "AP_WRAP"), (12, 4, False, "AP_TRN", "AP_WRAP"), (8, 8, False, "AP_TRN", "AP_WRAP"),
    (16, 5, True, "AP_RND", "AP_WRAP"), (16, 5, True, "AP_RND", "AP_SAT"), (12, 4, True, "AP_TRN", "AP_SAT"),
    (10, 3, True, "AP_RND_CONV", "AP_SAT_SYM"), (14, 6, True, "AP_TRN_ZERO", "AP_SAT_ZERO"),
    (12, 4, True, "AP_RND_ZERO", "AP_WRAP"), (12, 4, True, "AP_RND_INF", "AP_WRAP"),
    (12, 4, True, "AP_RND_MIN_INF", "AP_SAT"), (12, 4, False, "AP_RND", "AP_SAT"),
    (32, 16, False, "AP_TRN", "AP_WRAP"), (40, 8, False, "AP_TRN", "AP_WRAP"), (34, 20, True, "AP_TRN", "AP_WRAP"),
    (1, 1, True, "AP_TRN", "AP_WRAP"), (1, 0, True, "AP_TRN", "AP_WRAP"), (2, 1, True, "AP_RND", "AP_SAT"),
]
INT_TYPES = [(1, True), (2, True), (4, True), (8, True), (13, True), (16, True), (32, True), (48, True), (64, True),
             (1, False), (4, False), (8, False), (12, False), (16, False), (32, False), (40, False), (64, False)]


def ftype(t):
    W, I, S, Q, O = t
    return f"ap_{'' if S else 'u'}fixed<{W},{I},{Q},{O}>"


def itype(t):
    W, S = t
    return f"ap_{'' if S else 'u'}int<{W}>"


def frand(t, rng, small=False):
    """A random value of fixed type t as a C++ expression (exactly representable)."""
    W, I, S, Q, O = t
    F = W - I
    lo, hi = (-(1 << (W - 1)), (1 << (W - 1)) - 1) if S else (0, (1 << W) - 1)
    if small:
        lo, hi = max(lo, -(1 << min(W - 1, 12))), min(hi, (1 << min(W - 1, 12)))
    raw = rng.randint(lo, hi)
    return f"{ftype(t)}(ldexp((double){raw}, {-F}))", raw


def wrap_raw(v, t):
    """The raw value v wrapped into the W-bit raw of fixed type t."""
    W, S = t[0], t[2]
    v &= (1 << W) - 1
    return v - (1 << W) if S and v >> (W - 1) else v


def div_csim_overflow(a, ra, b, rb):
    """True when Vitis' C-simulation division (etc/ap_fixed_base.h operator/, not
    __SYNTHESIS__) overflows: it divides in _W1 = max(W + max(F2,0) + (S2 && !S),
    W2 + (S && !S2)) bits, so (min << F2) / -1 wraps. csynth computes the quotient
    exactly (kernel rfx_divk_overflow: a.o.3.ll stores 128 for ap_fixed<8,8>(-128) /
    ap_fixed<8,8>(-1), g++ prints -128); the shim follows csynth."""
    W, I, S = a[0], a[1], a[2]
    W2, I2, S2 = b[0], b[1], b[2]
    F2 = W2 - I2
    w1 = max(W + max(F2, 0) + (1 if S2 and not S else 0), W2 + (1 if S and not S2 else 0))
    if rb == 0:
        return False
    num = ra << max(F2, 0)
    q = abs(num) // abs(rb) * (1 if (num >= 0) == (rb > 0) else -1)
    if S or S2:
        return not (-(1 << (w1 - 1)) <= q < (1 << (w1 - 1)))
    return not (0 <= q < (1 << w1))


def sqrt_table_branch(t):
    """hls::sqrt's lookup-table branches (etc/hls_sqrt_apfixed.h: F == 0 && I <= 13,
    F <= 4 && I <= 5): their threshold and result constants wrap in small types, which
    the shim does not reproduce (the header is not ported: All Rights Reserved)."""
    W, I = t[0], t[1]
    F = W - I
    return (F == 0 and I <= 13) or (F <= 4 and I <= 5)


# Categories whose mismatches are known, explained deviations: reported, not failed.
KNOWN = {
    "divcsim": "Vitis C simulation wraps the quotient of min / -1LSB in _W1 bits; csynth and the shim do not",
    "sqrttbl": "hls::sqrt table branch: Vitis' constants wrap in small types (not ported)",
}


def irand(t, rng, nonzero=False):
    W, S = t
    lo, hi = (-(1 << (W - 1)), (1 << (W - 1)) - 1) if S else (0, (1 << W) - 1)
    if W == 1 and S:
        lo, hi = 0, 1
    v = rng.randint(lo, hi)
    while nonzero and v == 0:
        v = rng.randint(lo, hi)
    if W > 62:
        return f"{itype(t)}(ldexp((double){v >> 10}, 10))", v  # exact double
    return f"{itype(t)}({v}{'LL' if S else 'ULL'})", v


HEADER = r'''
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>

template <int W, int I, ap_q_mode Q, ap_o_mode O, int N>
static void P(const char *n, const ap_fixed<W, I, Q, O, N> &x) {
  if constexpr (W <= 64) { ap_uint<W> b = x.range(W - 1, 0); printf("%s <%d,%d> 0x%llx\n", n, W, I, (unsigned long long)b.to_uint64()); }
  else { ap_uint<64> lo = x.range(63, 0); ap_uint<W - 64> hi = x.range(W - 1, 64);
         printf("%s <%d,%d> 0x%llx:0x%llx\n", n, W, I, (unsigned long long)hi.to_uint64(), (unsigned long long)lo.to_uint64()); }
}
template <int W, int I, ap_q_mode Q, ap_o_mode O, int N>
static void P(const char *n, const ap_ufixed<W, I, Q, O, N> &x) {
  if constexpr (W <= 64) { ap_uint<W> b = x.range(W - 1, 0); printf("%s u<%d,%d> 0x%llx\n", n, W, I, (unsigned long long)b.to_uint64()); }
  else { ap_uint<64> lo = x.range(63, 0); ap_uint<W - 64> hi = x.range(W - 1, 64);
         printf("%s u<%d,%d> 0x%llx:0x%llx\n", n, W, I, (unsigned long long)hi.to_uint64(), (unsigned long long)lo.to_uint64()); }
}
template <int W, int I, bool S, ap_q_mode Q, ap_o_mode O, int N>
static void P(const char *n, const ap_fixed_base<W, I, S, Q, O, N> &x) {
  if constexpr (W <= 64) { ap_uint<W> b = x.range(W - 1, 0); printf("%s b<%d,%d,%d> 0x%llx\n", n, W, I, (int)S, (unsigned long long)b.to_uint64()); }
  else { ap_uint<64> lo = x.range(63, 0); ap_uint<W - 64> hi = x.range(W - 1, 64);
         printf("%s b<%d,%d,%d> 0x%llx:0x%llx\n", n, W, I, (int)S, (unsigned long long)hi.to_uint64(), (unsigned long long)lo.to_uint64()); }
}
template <int W> static void P(const char *n, const ap_int<W> &x) {
  if constexpr (W <= 64) { ap_uint<W> b = x.range(W - 1, 0); printf("%s i<%d> 0x%llx\n", n, W, (unsigned long long)b.to_uint64()); }
  else { ap_uint<64> lo = x.range(63, 0); ap_uint<W - 64> hi = x.range(W - 1, 64);
         printf("%s i<%d> 0x%llx:0x%llx\n", n, W, (unsigned long long)hi.to_uint64(), (unsigned long long)lo.to_uint64()); }
}
template <int W> static void P(const char *n, const ap_uint<W> &x) {
  if constexpr (W <= 64) { ap_uint<W> b = x.range(W - 1, 0); printf("%s u<%d> 0x%llx\n", n, W, (unsigned long long)b.to_uint64()); }
  else { ap_uint<64> lo = x.range(63, 0); ap_uint<W - 64> hi = x.range(W - 1, 64);
         printf("%s u<%d> 0x%llx:0x%llx\n", n, W, (unsigned long long)hi.to_uint64(), (unsigned long long)lo.to_uint64()); }
}
static void PB(const char *n, bool b) { printf("%s bool %d\n", n, (int)b); }
static void PI(const char *n, long long v) { printf("%s ll %lld\n", n, v); }
static void PD(const char *n, double d) { printf("%s double %a\n", n, d); }

int main() {
'''


def gen(seed, n):
    rng = random.Random(seed)
    out = [HEADER]
    L = out.append
    k = [0]

    def nm(cat):
        k[0] += 1
        return f"{cat}#{k[0]}"

    # ---- the design-table expressions (feas/A/design.md 1.1, REPORT.md) ----
    L('  { typedef ap_fixed<16, 5> data_t;')
    L('    data_t a = 16; P("tbl_(data_t)16", a);')
    L('    data_t b = 1.0; P("tbl_(data_t)1.0", b);')
    L('    data_t s = hls::sqrt(a); P("tbl_sqrt16", s);')
    L('    data_t c = 4; data_t s4 = hls::sqrt(c); P("tbl_sqrt4", s4);')
    L('    data_t sc4 = b / s4; P("tbl_1/sqrt4", sc4);')
    L('    data_t m = (data_t)3.5 * (data_t)0; P("tbl_3.5*0", m);')
    L('    data_t d = (data_t)1.0 / (data_t)0.5; P("tbl_1/0.5", d);')
    L('    data_t e = (data_t)15.5 + (data_t)1.0; P("tbl_15.5+1", e);')
    L('    data_t q = (data_t)(-1) / (data_t)3; P("tbl_-1/3", q);')
    L('    data_t two = hls::sqrt((data_t)2); P("tbl_sqrt2", two);')
    L('    data_t x = (data_t)0.1 + (data_t)0.2; P("tbl_0.1+0.2", x);')
    L('    data_t t3 = (data_t)(1.0/3) * (data_t)3; P("tbl_1/3*3", t3);')
    L('    data_t e0 = hls::exp((data_t)0); P("tbl_exp0", e0);')
    L('    data_t e1 = hls::exp((data_t)1); P("tbl_exp1", e1);')
    L('    data_t em1 = hls::exp((data_t)-1); P("tbl_exp-1", em1);')
    L('    data_t e3 = hls::exp((data_t)3); P("tbl_exp3_sat", e3);')
    L('    data_t e15 = hls::exp((data_t)15); P("tbl_exp15_sat", e15);')
    L('    data_t e278 = hls::exp((data_t)2.78); P("tbl_exp2.78_sat", e278);')
    L('    data_t em11 = hls::exp((data_t)-11.5); P("tbl_exp-11.5", em11);')
    L('    data_t in = (data_t)2.75; data_t m16 = in * (data_t)16; P("tbl_in*16", m16);')
    L('    data_t sq = (data_t)16 * (data_t)16; P("tbl_16*16", sq);')
    L('    PB("tbl_16>0", a > 0); PB("tbl_16==-16", a == (data_t)-16); PB("tbl_1.0<2", b < 2);')
    L('    PI("tbl_to_int(-1.5)", ((data_t)-1.5).to_int()); PI("tbl_(int)(-1.5)", (int)(data_t)-1.5);')
    L('    PD("tbl_(double)-1.5", (double)(data_t)-1.5);')
    L('    ap_fixed<32,8> w = (data_t)3.25; P("tbl_widen", w); data_t nw = (ap_fixed<32,8>)1.123456; P("tbl_narrow", nw);')
    L('    ap_fixed<16,5,AP_RND> r1 = (ap_fixed<32,8>)1.000244140625; P("tbl_rnd", r1);')
    L('    ap_fixed<16,5,AP_RND,AP_SAT> s1 = 100; P("tbl_sat100", s1); ap_fixed<16,5,AP_RND,AP_SAT> s2 = -100.5; P("tbl_sat-100", s2);')
    L('    ap_ufixed<16,6,AP_TRN,AP_SAT> u1 = -3; P("tbl_usat-3", u1); ap_ufixed<16,6,AP_TRN,AP_SAT> u2 = 70.5; P("tbl_usat70", u2);')
    L('    ap_uint<8> ui = 300; P("tbl_ap_uint8_300", ui); ap_int<8> si = 200; P("tbl_ap_int8_200", si);')
    L('    ap_int<8> sd = -3.75; P("tbl_ap_int8_-3.75", sd); ap_uint<8> ud = 3.75; P("tbl_ap_uint8_3.75", ud);')
    L('    ap_uint<8> aa = 200, bb = 100; auto ss = aa + bb; P("tbl_uint8+uint8", ss); auto mm = aa * bb; P("tbl_uint8*uint8", mm);')
    L('    ap_int<8> ia = -100; auto ds = ia / bb; P("tbl_int8/uint8", ds); auto md = ia % bb; P("tbl_int8%uint8", md);')
    L('    ap_uint<16> cc = (aa, bb); P("tbl_concat", cc); ap_uint<8> rr = aa.range(5, 2); P("tbl_range", rr); PB("tbl_bit7", aa[7]);')
    L('    ap_uint<8> sh = aa << 3; P("tbl_shl", sh); ap_int<8> sr = ia >> 2; P("tbl_shr", sr);')
    L('    ap_fixed<16,5> fs = (data_t)2.5 << 2; P("tbl_fshl", fs); ap_fixed<16,5> fr = (data_t)-2.5 >> 1; P("tbl_fshr", fr);')
    L('    ap_uint<128> big = 1; big = (big << 100) + 5; auto bm = big * ap_uint<128>(3); P("tbl_u128*3", bm);')
    L('    ap_fixed<16,5> fi = aa; P("tbl_fixed_from_uint8", fi); ap_int<8> ifx = (data_t)-2.5; P("tbl_int8_from_fixed", ifx);')
    L('    auto mix = (data_t)1.5 * ap_int<8>(-3); P("tbl_fixed*ap_int", mix); auto mix2 = (data_t)1.5 + 2; P("tbl_fixed+int", mix2);')
    L('    data_t neg = -(data_t)16; P("tbl_neg16", neg); auto negw = -(data_t)-16; P("tbl_negwide", negw);')
    L('    data_t inc = 15.5; inc++; P("tbl_inc_wrap", inc);')
    # ap_int_base(double): the shifted mantissa passes through ap_int_base<25, true> (Vitis
    # etc/ap_int_base.h; confirmed by csynth); the float constructor is exact
    L('    ap_int<32> q30 = 1073741824.0; P("tbl_dbl2int32_2^30", q30); ap_int<32> q24 = 16777219.0; P("tbl_dbl2int32_2^24+3", q24);')
    L('    ap_uint<40> q32 = 4294967295.0; P("tbl_dbl2uint40_2^32-1", q32); ap_int<32> f30 = 1073741824.0f; P("tbl_flt2int32_2^30", f30);')
    L('    ap_int<64> q52 = 4503599627370497.0; P("tbl_dbl2int64_2^52+1", q52); ap_int<32> qn = -33554431.0; P("tbl_dbl2int32_-(2^25-1)", qn);')
    # signed 1-bit types: one stored bit, value 0 or -1
    L('    ap_int<1> m1 = 1; ap_int<8> m1w = m1; P("tbl_int1_widen", m1w); auto m1s = m1 + m1; P("tbl_int1_add", m1s);')
    L('    auto m1m = m1 * m1; P("tbl_int1_mul", m1m); auto m1n = -m1; P("tbl_int1_neg", m1n); PB("tbl_int1_lt0", m1 < 0);')
    L('    PI("tbl_int1_to_int", m1.to_int()); PI("tbl_int1_ll", (long long)m1); ap_int<1> m1r = m1 >> 4; P("tbl_int1_shr", m1r);')
    L('    ap_fixed<1,1> f1 = -1; ap_fixed<8,4> f1w = f1; P("tbl_fixed1_widen", f1w); PD("tbl_fixed1_double", f1.to_double());')
    L('    PI("tbl_fixed1_to_int", f1.to_int()); auto f1a = f1 + (data_t)2.5; P("tbl_fixed1_add", f1a);')
    L('  }')

    # ---- random categories ----
    for _ in range(n):  # from int
        t = rng.choice(FIXED_TYPES)
        v = rng.choice([rng.randint(-40, 40), rng.randint(-70000, 70000), rng.randint(0, 3)])
        L(f'  {{ {ftype(t)} a = {v}; P("{nm("from_int")}", a); }}')
    for _ in range(n):  # from double
        t = rng.choice(FIXED_TYPES)
        d = rng.choice([rng.uniform(-20, 20), rng.uniform(-0.01, 0.01), rng.uniform(-3000, 3000), rng.randint(-5, 5) + 0.5,
                        rng.randint(-5, 5) + 2.0 ** -(t[0] - t[1] + 1)])
        L(f'  {{ {ftype(t)} a = {d!r}; P("{nm("from_double")}", a); }}')
    for _ in range(n):  # fixed -> fixed
        a, b = rng.choice(FIXED_TYPES), rng.choice(FIXED_TYPES)
        ea, _ = frand(a, rng)
        L(f'  {{ {ftype(a)} a = {ea}; {ftype(b)} b = a; P("{nm("convert")}", b); }}')
    for _ in range(2 * n):  # binary
        a, b = rng.choice(FIXED_TYPES), rng.choice(FIXED_TYPES)
        op = rng.choice(["+", "-", "*", "/", "&", "|", "^"])
        ea, ra = frand(a, rng)
        eb, rb = frand(b, rng)
        if op == "/" and rb == 0:
            eb = f"{ftype(b)}(ldexp((double)1, {-(b[0] - b[1])}))"
            rb = wrap_raw(1, b)
        cat = "divcsim" if op == "/" and div_csim_overflow(a, ra, b, rb) else "binop_" + op
        L(f'  {{ {ftype(a)} a = {ea}; {ftype(b)} b = {eb}; auto r = a {op} b; P("{nm(cat)}", r); }}')
    for _ in range(n):  # compound
        a, b = rng.choice(FIXED_TYPES), rng.choice(FIXED_TYPES)
        op = rng.choice(["+=", "-=", "*=", "/="])
        ea, ra = frand(a, rng)
        eb, rb = frand(b, rng, small=True)
        if op == "/=" and rb == 0:
            eb = f"{ftype(b)}(ldexp((double)3, {-(b[0] - b[1])}))"
            rb = wrap_raw(3, b)
        cat = "divcsim" if op == "/=" and div_csim_overflow(a, ra, b, rb) else "compound"
        L(f'  {{ {ftype(a)} a = {ea}; {ftype(b)} b = {eb}; a {op} b; P("{nm(cat)}", a); }}')
    for _ in range(n):  # compare
        a, b = rng.choice(FIXED_TYPES), rng.choice(FIXED_TYPES)
        op = rng.choice(["<", ">", "<=", ">=", "==", "!="])
        ea, _ = frand(a, rng, small=True)
        eb, _ = frand(b, rng, small=True)
        L(f'  {{ {ftype(a)} a = {ea}; {ftype(b)} b = {eb}; PB("{nm("cmp")}", a {op} b); PB("{nm("cmpd")}", a {op} 1.5); PB("{nm("cmpi")}", a {op} -1); }}')
    for _ in range(n):  # shifts, unary, conversions
        a = rng.choice(FIXED_TYPES)
        ea, _ = frand(a, rng)
        s = rng.randint(-3, 10)
        L(f'  {{ {ftype(a)} a = {ea}; auto l = a << {s}; P("{nm("shl")}", l); auto r = a >> {s}; P("{nm("shr")}", r);'
          f' auto m = -a; P("{nm("neg")}", m); PI("{nm("to_int")}", a.to_int()); PI("{nm("cast_int")}", (long long)(int)a); PD("{nm("to_double")}", (double)a); PB("{nm("not")}", !a); }}')
    for _ in range(2 * n):  # ap_int
        a, b = rng.choice(INT_TYPES), rng.choice(INT_TYPES)
        op = rng.choice(["+", "-", "*", "/", "%", "&", "|", "^", "<<", ">>"])
        ea, _ = irand(a, rng)
        eb, _ = irand(b, rng, nonzero=op in "/%")
        if op in ("<<", ">>"):
            eb = str(rng.randint(0, min(a[0], 20)))
        L(f'  {{ {itype(a)} a = {ea}; {itype(b)} b = {eb}; auto r = a {op} b; P("{nm("int_" + op)}", r); }}')
    for _ in range(n):  # ap_int mixed with C int and from double
        a = rng.choice(INT_TYPES)
        op = rng.choice(["+", "-", "*", "/", "%"])
        ea, _ = irand(a, rng, nonzero=True)
        c = rng.randint(-100, 100) or 7
        # small values and the 2^24 <= |d| < 2^52 range of ap_int_base(double)'s 25-bit path
        d = rng.choice([rng.uniform(-300, 300), rng.uniform(-2.0 ** 40, 2.0 ** 40),
                        rng.choice([-1, 1]) * (2.0 ** rng.randint(20, 60) + rng.randint(0, 1 << 20))])
        L(f'  {{ {itype(a)} a = {ea}; auto r = a {op} {c}; P("{nm("int_mix")}", r); auto r2 = {c} {op} a; P("{nm("int_mix2")}", r2);'
          f' {itype(a)} fd = {d!r}; P("{nm("int_from_double")}", fd); PB("{nm("int_cmp")}", a < {c}); auto m = -a; P("{nm("int_neg")}", m); auto t = ~a; P("{nm("int_not")}", t); }}')
    for _ in range(n):  # bit selects / concat on ap_int and ap_fixed
        a = rng.choice([t for t in INT_TYPES if t[0] >= 4])
        f = rng.choice([t for t in FIXED_TYPES if t[0] >= 8])
        ea, _ = irand(a, rng)
        ef, _ = frand(f, rng)
        hi = rng.randint(1, a[0] - 1)
        lo = rng.randint(0, hi)
        fhi = rng.randint(1, f[0] - 1)
        flo = rng.randint(0, fhi)
        L(f'  {{ {itype(a)} a = {ea}; {ftype(f)} f = {ef}; auto r = a.range({hi}, {lo}); P("{nm("range")}", {itype((a[0], False))}(r));'
          f' auto r2 = f({fhi}, {flo}); P("{nm("frange")}", ap_uint<{f[0]}>(r2)); PB("{nm("bit")}", a[{lo}]); PB("{nm("fbit")}", f[{flo}]);'
          f' {itype(a)} a2 = {irand(a, rng)[0]}; auto cc = (a, a2); P("{nm("concat")}", ap_uint<{2 * a[0]}>(cc)); }}')
    for _ in range(n):  # fixed OP C int
        a = rng.choice(FIXED_TYPES)
        ea, _ = frand(a, rng, small=True)
        c = rng.randint(-20, 20) or 3
        op = rng.choice(["+", "-", "*", "/"])
        if op == "/" and ea.endswith("(ldexp((double)0, " + str(-(a[0] - a[1])) + "))"):
            ea = f"{ftype(a)}(ldexp((double)5, {-(a[0] - a[1])}))"
        L(f'  {{ {ftype(a)} a = {ea}; auto r = a {op} {c}; P("{nm("fixed_cint")}", r); auto r2 = {c} {op} a; P("{nm("cint_fixed")}", r2); }}')
    # sqrt: exhaustive for ap_fixed<16,5>, random elsewhere
    L('  for (int v = -32768; v < 32768; v += 1) { ap_fixed<16,5> x = ldexp((double)v, -11); ap_fixed<16,5> r = hls::sqrt(x);'
      ' char nb[32]; snprintf(nb, sizeof nb, "sqrt16_5#%d", v); P(nb, r); }')
    for _ in range(n):
        t = rng.choice([t for t in FIXED_TYPES if t[3] == "AP_TRN" and t[4] == "AP_WRAP" and 2 <= t[0] <= 32 and t[1] >= 1 and t[1] <= t[0]])
        et, _ = frand(t, rng)
        L(f'  {{ {ftype(t)} a = {et}; auto r = hls::sqrt(a); P("{nm("sqrttbl" if sqrt_table_branch(t) else "sqrt")}", r); }}')
    for _ in range(6 * n):  # exp (tolerance 1 LSB)
        t = rng.choice([(16, 5, True, "AP_TRN", "AP_WRAP"), (32, 8, True, "AP_TRN", "AP_WRAP"), (16, 8, True, "AP_TRN", "AP_WRAP"), (12, 4, True, "AP_TRN", "AP_WRAP")])
        et, _ = frand(t, rng, small=True)
        L(f'  {{ {ftype(t)} a = {et}; auto r = hls::exp(a); P("{nm("exp")}", r); }}')
    L('  return 0;\n}\n')
    return "\n".join(out)


def parse(txt):
    d = {}
    for line in txt.splitlines():
        parts = line.split(" ", 1)
        if len(parts) == 2:
            d[parts[0]] = parts[1]
    return d


def raw_of(v):
    try:
        return int(v.split()[-1].split(":")[-1], 16)
    except ValueError:
        return None


def main():
    ap = argparse.ArgumentParser()
    here = Path(__file__).resolve().parent
    ap.add_argument("--shim", default=str(here / "shim" / "exactclass"))
    ap.add_argument("--vitis-include", default="/mnt/a/Vitis/2025.1/Vitis/include")
    ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--n", type=int, default=40)
    ap.add_argument("--out-dir", default=str(Path.home() / "hls-est-work" / "shim-check"))
    ap.add_argument("--clangxx", default=CLANGXX)
    ap.add_argument("--gxx", default=GXX)
    args = ap.parse_args()
    out = Path(args.out_dir)
    out.mkdir(parents=True, exist_ok=True)
    src = out / "probe_gen.cpp"
    src.write_text(gen(args.seed, args.n))
    runs = {}
    for name, cxx, flags in (("shim", args.clangxx, ["-std=c++17", "-fwrapv", "-O0", "-I", args.shim]),
                             ("vitis", args.gxx, ["-std=c++17", "-O0", "-w", "-I", args.vitis_include])):
        exe = out / f"probe_{name}"
        p = subprocess.run([cxx, *flags, str(src), "-o", str(exe)], capture_output=True, text=True)
        if p.returncode != 0:
            print(f"[{name}] compile failed:\n{p.stderr[:4000]}")
            sys.exit(2)
        r = subprocess.run([str(exe)], capture_output=True, text=True, timeout=600)
        (out / f"probe_{name}.out").write_text(r.stdout)
        if r.returncode != 0:
            print(f"[{name}] run failed rc={r.returncode}: {r.stderr[:2000]}")
        runs[name] = parse(r.stdout)
    s, v = runs["shim"], runs["vitis"]
    cats = {}
    for key in v:
        cat = key.split("#")[0] if "#" in key else key.split("_")[0]
        c = cats.setdefault(cat, {"n": 0, "mismatch": 0, "lsb1": 0, "known": 0, "missing": 0, "examples": []})
        c["n"] += 1
        if key not in s:
            c["missing"] += 1
            continue
        if s[key] == v[key]:
            continue
        rs, rv = raw_of(s[key]), raw_of(v[key])
        if cat == "exp" and rs is not None and rv is not None and abs(rs - rv) == 1:
            c["lsb1"] += 1
            if len(c["examples"]) < 3:
                c["examples"].append(f"{key}: shim {s[key]} vitis {v[key]} (1 LSB)")
            continue
        if cat in KNOWN:
            c["known"] += 1
            if len(c["examples"]) < 5:
                c["examples"].append(f"{key}: shim {s[key]} vitis {v[key]} (known: {KNOWN[cat]})")
            continue
        c["mismatch"] += 1
        if len(c["examples"]) < 5:
            c["examples"].append(f"{key}: shim {s[key]} vitis {v[key]}")
    total = sum(c["n"] for c in cats.values())
    bad = sum(c["mismatch"] + c["missing"] for c in cats.values())
    known = sum(c["known"] for c in cats.values())
    print(f"shim={args.shim}\nvitis={args.vitis_include}\nseed={args.seed} n={args.n}: {total} values compared, {bad} mismatches"
          f" ({known} known deviations: {', '.join(f'{k} = {v}' for k, v in KNOWN.items())})")
    print(f"{'category':14} {'values':>7} {'mismatch':>8} {'1-LSB(exp)':>10} {'known':>6}")
    for cat in sorted(cats):
        c = cats[cat]
        print(f"{cat:14} {c['n']:7d} {c['mismatch'] + c['missing']:8d} {c['lsb1']:10d} {c['known']:6d}")
        for e in c["examples"]:
            print(f"    {e}")
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
