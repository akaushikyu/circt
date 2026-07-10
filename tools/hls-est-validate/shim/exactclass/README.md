# "exactclass" shim (harness-local, opt-in; bit-exact ap_fixed / ap_int)

Stand-ins for the Vitis HLS headers in which `ap_int<W>` / `ap_uint<W>` /
`ap_fixed<W,I,Q,O,N>` / `ap_ufixed<...>` are *classes* whose only data member
is the raw `_BitInt(W)` / `unsigned _BitInt(W)` value, as in the real headers
in `__SYNTHESIS__` mode (`ap_int_base<W,S>::V`, `ap_fixed_base<W,I,S,Q,O,N>::V`).
They need the opt-in cgeist option `--scalar-wrapper-abi` (Polygeist branch
`hls-est-vitis-match`), which lowers such a "scalar wrapper" class to its
scalar. `run_hlsest.py` passes it because this directory has a
`cgeist_flags` file (its flags are appended to the cgeist command and are part
of the MLIR cache key). hls-est then sees

| Vitis type                 | MLIR                                  |
|----------------------------|---------------------------------------|
| `ap_fixed<16,5>` value     | `i16` (raw bits, value * 2^11)        |
| `ap_fixed<16,5> a[8][256]` | `memref<8x256xi16>`                   |
| `ap_fixed<16,5>&`, `this`  | `memref<?xi16>`                       |
| `ap_uint<512>`             | `i512`                                |
| `half`                     | `f16` (`_Float16`)                    |

and every operation is the integer arithmetic of the Vitis headers
(`etc/ap_fixed_base.h`, `etc/ap_int_base.h` of 2025.1), so the constants the
frontend folds are the ones Vitis folds: `(ap_fixed<16,5>)16` is `-32768`
(wrap), and `1.0 / hls::sqrt((ap_fixed<16,5>)16)` is a division by zero that
stays in the IR as `arith.divsi 4194304, 0` (Vitis: `undef`; folding it is
hls-est-side work, track T8, not done yet).

Use: `python3 run_hlsest.py --shim exactclass ...`. Without
`--scalar-wrapper-abi` (e.g. a cgeist binary that predates it) these classes
are LLVM structs that hls-est cannot parse.

This directory is used by the harness only. It does **not** replace
`tools/cgeist/Test/HLS/Inputs/vitis` in Polygeist (the double-backed class
stand-in the lit tests use) nor `shim/exact`; whether to switch either over is
Peter's decision.

## What is modelled (validated by `../../check_shim.py` and `../../check_shim_cgeist.py`)

`check_shim.py` generates one C++ program (the design-table expressions plus
seeded random constants and operations per category), compiles it with the
HOST clang++ against this shim and with g++ against the real
`/mnt/a/Vitis/2025.1/Vitis/include`, and compares every raw bit pattern
(65 536 of the values are the exhaustive `ap_fixed<16,5>` sqrt). That checks
the shim's C++ only. `check_shim_cgeist.py` compiles a targeted + random list
of expressions through **cgeist** (harness flags + `cgeist_flags`,
`-emit-llvm`), with the inputs both as run-time arguments and as constants
cgeist folds, and compares those bits, the host clang++ bits and the Vitis
bits: that is what hls-est receives. The first round of this shim was only
checked with the host compiler and missed a cgeist bug (Polygeist's `x - C`
canonicalisation on integers wider than 64 bits, fixed in Polygeist) and the
two shim errors listed under "Fixed" below. Results are in CHANGELOG.md.

- int -> fixed, double -> fixed (exact IEEE mantissa shift), fixed -> fixed
  with all quantization modes (`AP_TRN`, `AP_RND`, `AP_RND_ZERO`,
  `AP_RND_MIN_INF`, `AP_RND_INF`, `AP_RND_CONV`, `AP_TRN_ZERO`) and overflow
  modes (`AP_WRAP`, `AP_SAT`, `AP_SAT_ZERO`, `AP_SAT_SYM`);
- `+ - * / & | ^` with the Vitis result types (`RType`), compound assignment,
  comparisons (exact), shifts, unary `- ~ !`, `++`/`--`;
- mixed operands: fixed OP C-integer, fixed OP ap_int, ap_int OP C-integer,
  comparisons with double; `(int)x` / `to_int()` (truncation toward zero, and
  the Vitis quirk that a negative fraction in a type with I <= 0 gives -1),
  `to_double()`;
- `ap_int` arithmetic (`+ - * / % & | ^ << >>`), implicit conversion to
  `long long` / `unsigned long long` (Vitis `operator RetType()`); from float
  (truncation toward zero, then wrap); from double the same, except that
  Vitis' `ap_int_base(double)` keeps the shifted mantissa of a value with
  1 <= |d| < 2^52 in an `ap_int_base<FLOAT_MAN + 2, true>` (25 bits, signed)
  before assigning it: `ap_int<32>(1073741824.0)` is 0,
  `ap_int<32>(16777219.0)` is -16777213, `ap_uint<40>(4294967295.0)` is
  0xFFFFFFFFFF (g++ with the Vitis headers and csynth agree: the a.o.3.ll of
  a csynth run stores these constants; `ap_fixed` from double has no such
  step);
- the signed 1-bit types `ap_int<1>`, `ap_fixed<1,I>`: one stored bit (`i1`
  in the MLIR, as in Vitis), read as 0 or -1;
- value-returning `range()`, `operator()`, `operator[]`, `bit()`, `(a, b)`;
- `hls::sqrt` (exhaustively for `ap_fixed<16,5>`: negative -> 0, round-half-up),
  `hls::exp` (floor of the exact value, saturating like the Vitis tables;
  1-LSB differences against the table algorithm are counted separately).

## Not modelled / deviations

- `hls::exp` is NOT the Vitis algorithm: `etc/hls_exp_apfixed.h` (3 ROM
  tables) is "All Rights Reserved" in the Vitis install and is not part of
  the Apache-2.0 `HLS_arbitrary_Precision_Types` repository (which has only
  the ap_int / ap_fixed headers), so it was not ported. The shim returns
  floor(exp(x) * 2^F) with the same saturation; the Vitis tables differ from
  that by one LSB, in either direction, on about 1% of the inputs (909 of
  38 447 in-range `ap_fixed<16,5>` inputs; 10 of 900 random inputs over the
  checked types with `check_shim.py --seed 12 --n 150`, 1 of 240 with
  `--seed 11 --n 40`). `log/tanh/sin/cos/atan/pow/rsqrt/...` are
  evaluated in double and floored to the Vitis result type (Vitis uses
  CORDIC / table algorithms: last-bit differences possible, unconfirmed).
- `hls::sqrt` lookup-table branches (`F == 0 && I <= 13`, `F <= 4 && I <= 5`):
  Vitis compares against hand-written constants of type `ap_ufixed<W-1,I-1>`
  and returns constants of the result type; they wrap when `I` is small
  (`ap_fixed<8,4>(7.9375)`: Vitis 0, shim 2.8125). The shim returns the
  round-half-up root there; `etc/hls_sqrt_apfixed.h` is "All Rights Reserved",
  so the tables are not ported. `check_shim.py` reports these inputs in the
  known category `sqrttbl`.
- Fixed-point division follows **csynth**: the exact quotient. Vitis' C
  simulation path (what g++ with the headers runs) divides in
  `_W1 = max(W + max(F2,0) + (S2 && !S), W2 + (S && !S2))` bits, so the
  minimum divided by a raw -1 wraps there; csynth does not
  (`ap_fixed<8,8>(-128) / ap_fixed<8,8>(-1)` is 128 in csynth, -128 in g++;
  VITIS_NOTES.md N11). `check_shim.py` / `check_shim_cgeist.py` report these
  inputs in the known category `divcsim`.
- `N != 0` saturation bits and `AP_WRAP_SM` (0 corpus uses): plain wrap.
- (fixed) `ap_int<1>` / `ap_fixed<1,I>`: clang rejects a signed `_BitInt(1)`;
  the first round stored them as `_BitInt(2)`, which made arrays of them 2
  bits wide and gave `ap_int<1> x = 1` the value 1 instead of -1. They are now
  stored in an `unsigned _BitInt(1)` and every read goes through `rval()`,
  which sign-extends the bit.
- (fixed) the 25-bit step of `ap_int_base(double)` described above was
  missing (the conversion was exact).
- Assignable bit / range selects and concatenations (`x.range(7,0) = v`,
  `x(7,0) = v`, `x[i] = b`, `(a, b) = v`): Vitis uses reference-proxy classes
  there; here the selects return `const` values, so those lines are compile
  errors (loud, not silently wrong). See OPEN_ISSUES.md.
- `x * 0.5` (fixed OP double) is ambiguous here, as with the real headers
  (the class converts to every built-in type); the corpus therefore does not
  use it.
- String constructors (`ap_fixed<8,4>("0x1.8p0")`) are not provided.
- Division by zero is `undef` in Vitis synthesis; the real simulation headers
  trap; this shim leaves `divsi x, 0` in the IR.
- `hls::stream`, `hls::vector`, `ap_axis`, `ap_cint.h` are the declare-only
  stand-ins of `shim/exact` (a stream or vector containing an `ap_fixed` now
  has an `iW` field).
