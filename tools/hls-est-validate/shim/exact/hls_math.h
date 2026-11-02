// hls-est "exact" stand-in for the Vitis HLS hls_math.h (scalar shim plus
// _Float16 overloads; the generic templates evaluate in double).
#ifndef HLSEST_EXACT_HLS_MATH_H
#define HLSEST_EXACT_HLS_MATH_H

#include <math.h>

#ifdef __cplusplus
#include "ap_fixed.h"
#include "hls_half.h"

namespace hls {
// Generic forms: evaluated in double (the stand-in types convert to it).
template <typename T> T exp(T x) { return (T)::exp((double)x); }
template <typename T> T log(T x) { return (T)::log((double)x); }
template <typename T> T log2(T x) { return (T)::log2((double)x); }
template <typename T> T log10(T x) { return (T)::log10((double)x); }
template <typename T> T sqrt(T x) { return (T)::sqrt((double)x); }
template <typename T> T rsqrt(T x) { return (T)(1.0 / ::sqrt((double)x)); }
template <typename T> T recip(T x) { return (T)(1.0 / (double)x); }
template <typename T> T sin(T x) { return (T)::sin((double)x); }
template <typename T> T cos(T x) { return (T)::cos((double)x); }
template <typename T> T tan(T x) { return (T)::tan((double)x); }
template <typename T> T atan(T x) { return (T)::atan((double)x); }
template <typename T> T tanh(T x) { return (T)::tanh((double)x); }
template <typename T> T erf(T x) { return (T)::erf((double)x); }
template <typename T> T abs(T x) { return x < 0 ? (T)(-(double)x) : x; }
template <typename T> T fabs(T x) { return abs(x); }
template <typename T> T floor(T x) { return (T)::floor((double)x); }
template <typename T> T ceil(T x) { return (T)::ceil((double)x); }
template <typename T> T round(T x) { return (T)::round((double)x); }
template <typename T> T pow(T x, T y) { return (T)::pow((double)x, (double)y); }
template <typename T> T nextafter(T x, T y) {
  return (T)::nextafter((double)x, (double)y);
}
template <typename T> T max(T a, T b) { return a > b ? a : b; }
template <typename T> T min(T a, T b) { return a < b ? a : b; }
template <typename T> T fmax(T a, T b) { return a > b ? a : b; }
template <typename T> T fmin(T a, T b) { return a < b ? a : b; }
template <typename T> bool signbit(T x) { return (double)x < 0; }
template <typename T> bool isnan(T x) { return (double)x != (double)x; }
// _Float16 overloads (preferred over the templates by overload resolution):
// sqrt uses the f16 builtin so cgeist emits math.sqrt on f16 instead of the
// double round trip; the rest keep the width of the result only.
inline _Float16 sqrt(_Float16 x) { return __builtin_sqrtf16(x); }
inline _Float16 rsqrt(_Float16 x) { return (_Float16)1 / __builtin_sqrtf16(x); }
inline _Float16 fabs(_Float16 x) { return __builtin_fabsf16(x); }
inline _Float16 abs(_Float16 x) { return __builtin_fabsf16(x); }
inline float expf(float x) { return ::expf(x); }
inline float logf(float x) { return ::logf(x); }
inline float sqrtf(float x) { return ::sqrtf(x); }
inline float powf(float x, float y) { return ::powf(x, y); }
inline float fabsf(float x) { return ::fabsf(x); }
} // namespace hls
#endif // __cplusplus
#endif
