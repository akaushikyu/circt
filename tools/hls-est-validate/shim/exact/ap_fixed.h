// hls-est "exact" stand-in for ap_fixed.h: ap_[u]fixed<W,I,...> is the
// builtin floating type with the same storage width: _Float16 (W <= 16),
// float (W <= 32), double (W > 32). This keeps the element width that the
// BRAM estimate depends on exact for W <= 16 (and 32), but NOT the
// fixed-point arithmetic semantics: no AP_TRN/AP_WRAP quantisation or
// overflow, no I/F split, and the dynamic range is that of the float type.
#ifndef HLSEST_EXACT_AP_FIXED_H
#define HLSEST_EXACT_AP_FIXED_H
#ifdef __cplusplus
#include "ap_int.h"
enum ap_q_mode { AP_RND, AP_RND_ZERO, AP_RND_MIN_INF, AP_RND_INF, AP_RND_CONV, AP_TRN, AP_TRN_ZERO };
enum ap_o_mode { AP_SAT, AP_SAT_ZERO, AP_SAT_SYM, AP_WRAP, AP_WRAP_SM };
template <int W, bool H = (W <= 16), bool F = (W <= 32)> struct __hlsest_fix { typedef double type; };
template <int W> struct __hlsest_fix<W, true, true> { typedef _Float16 type; };
template <int W> struct __hlsest_fix<W, false, true> { typedef float type; };
template <int W, int I, int Q = AP_TRN, int O = AP_WRAP, int N = 0>
using ap_fixed = typename __hlsest_fix<W>::type;
template <int W, int I, int Q = AP_TRN, int O = AP_WRAP, int N = 0>
using ap_ufixed = typename __hlsest_fix<W>::type;
#endif // __cplusplus
#endif
