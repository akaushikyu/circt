// hls-est "exact" stand-in for ap_int.h: ap_[u]int<W> is a W-bit _BitInt.
#ifndef HLSEST_EXACT_AP_INT_H
#define HLSEST_EXACT_AP_INT_H
#ifdef __cplusplus
// _BitInt(W) is a C23 type that clang also accepts in C++. It is never
// promoted to int, so arithmetic stays W bits wide; cgeist lowers it to a
// signless iW. clang rejects `signed _BitInt(1)`, so ap_int<1> is the
// (unsigned) 1-bit type as well: same storage width, sign lost.
template <int W> struct __hlsest_int {
  typedef _BitInt(W) stype;
  typedef unsigned _BitInt(W) utype;
};
template <> struct __hlsest_int<1> {
  typedef unsigned _BitInt(1) stype;
  typedef unsigned _BitInt(1) utype;
};
template <int W> using ap_int = typename __hlsest_int<W>::stype;
template <int W> using ap_uint = typename __hlsest_int<W>::utype;
#include "ap_fixed.h"
#endif // __cplusplus
#endif
