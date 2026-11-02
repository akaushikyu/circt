# "scalar" shim (harness-local, lossy)

Stand-ins for the Vitis HLS headers in which `ap_int<W>` / `ap_uint<W>` are
aliases of the smallest builtin integer that holds W bits and
`ap_fixed<W,I,...>` / `ap_ufixed<...>` are aliases of `float` (W <= 32) or
`double`.  cgeist then emits plain `iN` / `f32` / `f64` memrefs, so hls-est can
analyse kernels that use these types at all (the Polygeist stand-in keeps the
value inside a class, which cgeist cannot lower for 2-D arrays and hls-est
cannot parse).  It is NOT bit-accurate: element widths are rounded up
(ap_fixed<16,5> arrays are counted as 32-bit), fixed-point wrap/quantisation is
lost, and member functions such as `.range()` / `(a, b)` concatenation do not
compile.  See VITIS_NOTES.md for the exact semantics the frontend would need.
