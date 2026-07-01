# "exact" shim (harness-local, width-exact scalars)

Stand-ins for the Vitis HLS headers that keep the *storage width* of every
arbitrary-precision type, using the two clang scalar types cgeist now lowers
(Polygeist branch `hls-est-vitis-match`):

| Vitis type            | shim type                 | MLIR  |
|-----------------------|---------------------------|-------|
| `ap_int<W>`  (W >= 2) | `_BitInt(W)`              | `iW`  |
| `ap_uint<W>` (W >= 1) | `unsigned _BitInt(W)`     | `iW`  |
| `ap_int<1>`           | `unsigned _BitInt(1)`     | `i1`  (clang rejects a signed 1-bit `_BitInt`; width kept, sign lost) |
| `ap_[u]fixed<W<=16,…>`| `_Float16`                | `f16` |
| `ap_[u]fixed<W<=32,…>`| `float`                   | `f32` |
| `ap_[u]fixed<W>32,…>` | `double`                  | `f64` |

`_BitInt(W)` works for every W clang accepts (up to 8388608 bits), so
`ap_uint<512>` becomes `i512`. `_BitInt` is never promoted to `int`, so
arithmetic stays W bits wide, like `ap_int` (but without ap_int's
width-growing `+`/`*` results; those keep W bits and wrap).

What is still NOT modelled:
- fixed-point arithmetic: `ap_fixed` values are IEEE floats, so there is no
  AP_TRN/AP_WRAP quantisation or overflow, no I/F split, and the dynamic range
  is that of the float type (`ap_fixed<16,5>` really holds [-16,16) with 2^-11
  steps; `_Float16` holds +-65504 with 11 bits of mantissa). Only the width
  (and hence the per-element BRAM cost) is exact for W <= 16 and W = 32;
  17..31-bit ap_fixed is still counted as 32 bits.
- member functions such as `.range()`, `(a, b)` concatenation, `.to_int()`.
- `half` (hls_half.h) is still `float`, as in the scalar shim.

`hls_math.h` is the scalar one plus `_Float16` overloads; `hls::sqrt` on a
`_Float16` uses `__builtin_sqrtf16`, which cgeist lowers to `math.sqrt` on
`f16`. The other math templates evaluate in `double` and cast back.
