// hls-est "scalar" stand-in for ap_fixed.h: ap_[u]fixed<W,I,...> is float/double.
#ifndef HLSEST_SCALAR_AP_FIXED_H
#define HLSEST_SCALAR_AP_FIXED_H
#ifdef __cplusplus
#include "ap_int.h"
enum ap_q_mode { AP_RND, AP_RND_ZERO, AP_RND_MIN_INF, AP_RND_INF, AP_RND_CONV, AP_TRN, AP_TRN_ZERO };
enum ap_o_mode { AP_SAT, AP_SAT_ZERO, AP_SAT_SYM, AP_WRAP, AP_WRAP_SM };
template <int W> struct __hlsest_fix { typedef double type; };
template <int W> struct __hlsest_fix_sel { typedef typename __hlsest_fix<(W <= 32 ? 32 : 64)>::type type; };
template <> struct __hlsest_fix<32> { typedef float type; };
template <> struct __hlsest_fix<64> { typedef double type; };
template <int W, int I, int Q = AP_TRN, int O = AP_WRAP, int N = 0>
using ap_fixed = typename __hlsest_fix_sel<W>::type;
template <int W, int I, int Q = AP_TRN, int O = AP_WRAP, int N = 0>
using ap_ufixed = typename __hlsest_fix_sel<W>::type;
#endif // __cplusplus
#endif
