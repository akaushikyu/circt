# "real" shim: the Vitis HLS 2025.1 headers themselves (track W11, opt-in)

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

plus `--scalar-wrapper-abi`, so that `ap_int` / `ap_fixed` objects reach hls-est as `iN`
like with `shim/exactclass`. The language standard (C++: gnu++14, C: gnu99) comes from
`VITIS_FRONTEND=1` (run_hlsest.py), as for every other shim; without it cgeist uses clang's
default (gnu++17 / gnu17), which already accepts the headers' `typeof`.

Requirements: the Vitis install at `/mnt/a/Vitis/2025.1` and a cgeist built from Polygeist
branch `w11-real-headers` against the patched clang of that branch (`CGEIST_BIN`). The
installed cgeist does not know `--xlx-prelude` / `-Xclang` and fails on the first flag.

Not covered (separate modelling tracks): `hls::stream` (`__fpga_fifo_*`), `hls::task`,
`ap_float`, the float / double `hls_math` functions (closed bitcode), the DSP builtins,
the FFT IP, and `ap_int` / `ap_fixed` constructors from a string (`_ssdm_string2bits`,
folded by the closed Vitis front end).

`autopilot.sha256` lists the sha256 of the Vitis headers this shim compiles against, so
that every file in this directory (README and flags included) keys the MLIR cache as for
the other shims, and a changed install changes the key. Regenerate it with
`(cd /mnt/a/Vitis/2025.1/Vitis/common/technology/autopilot && sha256sum *.h etc/*.h) > autopilot.sha256`.
