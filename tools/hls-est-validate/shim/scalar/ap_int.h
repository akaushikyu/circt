// hls-est "scalar" stand-in for ap_int.h: ap_[u]int<W> is a builtin integer.
#ifndef HLSEST_SCALAR_AP_INT_H
#define HLSEST_SCALAR_AP_INT_H
#ifdef __cplusplus
template <int W, bool S> struct __hlsest_int_sel { typedef long long type; };
template <int W> struct __hlsest_int_sel<W, false> { typedef unsigned long long type; };
#define HLSEST_INT_SEL(LO, HI, ST, UT)                                          \
  template <int W> struct __hlsest_int_sel_rng_##LO {                          \
    typedef ST stype; typedef UT utype; };
template <int W, bool S, int B = (W <= 8 ? 8 : W <= 16 ? 16 : W <= 32 ? 32 : 64)>
struct __hlsest_int { typedef long long type; };
template <int W> struct __hlsest_int<W, true, 8> { typedef signed char type; };
template <int W> struct __hlsest_int<W, false, 8> { typedef unsigned char type; };
template <int W> struct __hlsest_int<W, true, 16> { typedef short type; };
template <int W> struct __hlsest_int<W, false, 16> { typedef unsigned short type; };
template <int W> struct __hlsest_int<W, true, 32> { typedef int type; };
template <int W> struct __hlsest_int<W, false, 32> { typedef unsigned int type; };
template <int W> struct __hlsest_int<W, true, 64> { typedef long long type; };
template <int W> struct __hlsest_int<W, false, 64> { typedef unsigned long long type; };
template <int W> using ap_int = typename __hlsest_int<W, true>::type;
template <int W> using ap_uint = typename __hlsest_int<W, false>::type;
#include "ap_fixed.h"
#endif // __cplusplus
#endif
