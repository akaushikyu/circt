# "real" shim: the Vitis HLS 2025.1 headers themselves (track W11; the harness default since W11-adopt, MEMOS #67)

This directory holds no headers. Its `cgeist_flags` make cgeist compile a design against
the headers of the Vitis install, the way the Vitis front end does, instead of a stand-in:

| Vitis front end (`db/autopilot.flow.log:331` of every cached run)   | `cgeist_flags` |
|----------------------------------------------------------------------|----------------|
| `-I <Vitis>/common/technology/autopilot` (the synthesis tree, not `Vitis/include`) | the same |
| `-D__SYNTHESIS__ -D__VITIS_HLS__ -DAESL_SYN -D__HLS_SYN__ -D__DSP48E1__` | the same |
| `-include etc/autopilot_ssdm_op.h`                                    | the same |
| `__attribute__((bitwidth(N)))` is an N-bit integer (`ap_common.h:529-542`) | `-Xclang -fxlx-bitwidth` (patched clang: `_BitInt(N)`) |
| integer promotion of an N <= 32 bit integer to `int` (hls-llvm-project `SemaExpr.cpp:704`) | `-Xclang -fxlx-apint-promote` |
| the `__builtin_bit_*` builtins and `__fpga_ctlz` (`Builtins.def:1464-1475`) | `--xlx-prelude` (declarations compiled into cgeist; lowered to `arith` by `CGXlxBuiltin.cc`) |
| the proxy objects of `x.range(h, l)`, `x[i]`, `(a, b)` (`ap_range_ref`, `ap_bit_ref`, `ap_concat_ref`, ...; a reference plus indices) | `--xlx-headers` (inlined and scalarised to shift / mask arithmetic; also namespace-qualified tables and two-reference structs) |
| `-fhls` makes `__fp16` a native type with half arguments and returns | `-Xclang -fnative-half-type -Xclang -fnative-half-arguments-and-returns` |
| `no_ctor`, `hls_preserve` attributes                                  | ignored (`-Xclang -Wno-unknown-attributes`); they only matter for streams and the FFT IP |
| C++: `-fno-threadsafe-statics -fno-use-cxa-atexit`                    | `-Xclang -fno-threadsafe-statics -Xclang -fno-use-cxa-atexit` (cc1 accepts them for C too, without effect; cgeist emits its own static-initialisation guards, so the MLIR of the harness subset does not change) |

plus `--scalar-wrapper-abi`, so that `ap_int` / `ap_fixed` objects reach hls-est as `iN`
like with `shim/exactclass`. The language standard (C++: gnu++14, C: gnu99) comes from
`VITIS_FRONTEND=1` (run_hlsest.py), as for every other shim; without it cgeist uses clang's
default (gnu++17 / gnu17), which already accepts the headers' `typeof`.

Requirements: the Vitis install at `/mnt/a/Vitis/2025.1` and a cgeist with the W11 Xilinx
extensions, built against the patched clang (llvm-project branch `w11-xlx-bitwidth`; see
Polygeist `patches/llvm-project/README.md`): the installed `/mnt/d/HLS/Polygeist/build/bin/cgeist`
since Polygeist `hls-est-vitis-match` 483ef69c (MEMOS #66), or a private build given as
`CGEIST_BIN`. `common.DEFAULT_SHIM` is `real` since W11-adopt (MEMOS #67); `exactclass` stays
selectable with `--shim exactclass`. run_hlsest.py stops before the first design when the cgeist lacks
`--xlx-headers` (the installed one does) or the Vitis install is missing.

`ap_int` / `ap_fixed` constructed from a string literal (`_ssdm_string2bits`, which the
closed Vitis front end folds; the fixed-point math headers' lookup tables) are folded by
cgeist too (`--xlx-headers`, Polygeist `Lib/XlxStringBits.cc`, the C simulation's
conversion), so those tables are dense ROM globals.

`hls::stream` (`hls_stream_39.h`, and its AXI-Stream specialisation in `ap_axi_sdata.h`)
reaches hls-est in the form of the stand-in headers that its FIFO model reads (VITIS_NOTES
N31): under `--xlx-headers` cgeist makes every `hls::stream<T, D>` object an `i32` handle
and every member an external call named as a member of the object's own class (so the
name keeps D although the members are inherited from `hls::stream<T, 0>`); the
`__fpga_fifo_*` / `__fpga_axis_*` builtins are declared by the prelude only so that the
headers parse (Polygeist `clang-mlir.cc` `isXlxStreamClass`, OPEN_ISSUES O64 (a)).

The `hls::` math functions of `hls_math.h` (fixed-point overloads with their bodies, and the
float / double / half declarations of the closed library) are cores of the Vitis math
library: cgeist marks each call `hls.math_core = {function, type}` and keeps the callee as a
function (inlined only when every argument is a constant, which Vitis folds), hls-est's
`--lower-polygeist-subindex` drops its body and the math-cost model prices it per instance
(N16), as for the stand-in headers' `__hlsest_math_<fn>` markers (Polygeist
`Lib/XlxMathCore.cc`, OPEN_ISSUES O64 (c)). A global of an ap type initialised from a number
(`static const ap_uint<10> X = -1;`, `const ap_fixed<..> lut[] = {0.5, ...}`) gets the
constant the headers' numeric constructor computes (Polygeist `XlxStringBits.cc`
`foldNumericConstruct`, O63); the real constructors are not `constexpr`.

Not covered (separate modelling tracks): `hls::task`, `hls::stream_of_blocks`, `ap_float`,
the DSP builtins, the FFT IP, and the extern `cordic_apfixed` / `hotbm_apfixed` tables of the
closed library (declared `extern` in the headers; only reachable inside a math core). Known
gap (O64 (b)): an array of `hls::vector` / `std::array` elements whose trivial copy cgeist
emits in place as a byte loop is not split by `--split-struct-memrefs`.

`autopilot.sha256` lists the sha256 of the Vitis headers this shim compiles against, so
that every file in this directory (README and flags included) keys the MLIR cache as for
the other shims, and a changed install changes the key. Regenerate it with
`(cd /mnt/a/Vitis/2025.1/Vitis/common/technology/autopilot && sha256sum *.h etc/*.h) > autopilot.sha256`.
