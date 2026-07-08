// hls-est "exactclass" stand-in for the Vitis HLS ap_int.h.
//
// ap_int<W> / ap_uint<W> are classes whose ONLY data member is a
// `_BitInt(W)` / `unsigned _BitInt(W)` (ap_int_base<W,S>::V), exactly like
// the Vitis headers in __SYNTHESIS__ mode (`int __attribute__((bitwidth(W)))`).
// cgeist (Polygeist branch hls-est-vitis-match, --scalar-wrapper-abi) lowers a
// single-scalar-member class to that scalar, so every ap_int<W> value, array
// element, reference and `this` is a plain `iW` in the MLIR.
//
// Semantics follow etc/ap_int_base.h of Vitis 2025.1:
//   * result widths of + - * / % & | ^ per ap_int_base::RType (the wider
//     Vitis result type), computed exactly; assigning back truncates (wrap);
//   * shifts keep the width of the left operand (bits shifted out are lost);
//   * conversion from double truncates toward zero, then wraps to W bits;
//   * the implicit conversion to a built-in integer is the 64-bit one Vitis
//     provides (`operator RetType()`): long long / unsigned long long;
//   * range() / operator() / operator[] / bit() / (a, b) are VALUE-returning
//     (const): `x.range(7, 0) = v` does not compile (Vitis uses reference
//     proxies there; see tools/hls-est-validate/OPEN_ISSUES.md).
// Known deviations: clang rejects a signed _BitInt(1), so ap_int<1> is stored
// as a _BitInt(2) (2-bit value semantics and storage); string constructors
// are not provided.
#ifndef HLSEST_EXACTCLASS_AP_INT_H
#define HLSEST_EXACTCLASS_AP_INT_H
#ifdef __cplusplus

enum ap_q_mode { AP_RND, AP_RND_ZERO, AP_RND_MIN_INF, AP_RND_INF, AP_RND_CONV, AP_TRN, AP_TRN_ZERO };
enum ap_o_mode { AP_SAT, AP_SAT_ZERO, AP_SAT_SYM, AP_WRAP, AP_WRAP_SM };

typedef long long ap_slong;
typedef unsigned long long ap_ulong;

namespace ap_detail {
constexpr int max(int a, int b) { return a > b ? a : b; }
constexpr int min(int a, int b) { return a < b ? a : b; }

// The raw storage / computation types. A signed _BitInt needs >= 2 bits.
template <int N, bool S> struct bits { typedef _BitInt((N < 2 ? 2 : N)) type; };
template <int N> struct bits<N, false> { typedef unsigned _BitInt((N < 1 ? 1 : N)) type; };
template <int N> using sbits = typename bits<N, true>::type;
template <int N> using ubits = typename bits<N, false>::type;

// Width and signedness Vitis assigns to each C integer type in mixed
// expressions (ap_int_base.h ALL_OP_BIN_WITH_INT, ap_fixed_base.h
// ALL_AF_OP_WITH_INT). The primary template is empty so that
// `typename ctype<T>::...` is a substitution failure for any other T.
template <class T> struct ctype {};
template <> struct ctype<bool> { static constexpr int W = 1; static constexpr bool S = false; typedef bool type; };
template <> struct ctype<char> { static constexpr int W = 8; static constexpr bool S = ((char)-1 < 0); typedef char type; };
template <> struct ctype<signed char> { static constexpr int W = 8; static constexpr bool S = true; typedef signed char type; };
template <> struct ctype<unsigned char> { static constexpr int W = 8; static constexpr bool S = false; typedef unsigned char type; };
template <> struct ctype<short> { static constexpr int W = 16; static constexpr bool S = true; typedef short type; };
template <> struct ctype<unsigned short> { static constexpr int W = 16; static constexpr bool S = false; typedef unsigned short type; };
template <> struct ctype<int> { static constexpr int W = 32; static constexpr bool S = true; typedef int type; };
template <> struct ctype<unsigned> { static constexpr int W = 32; static constexpr bool S = false; typedef unsigned type; };
template <> struct ctype<long> { static constexpr int W = 64; static constexpr bool S = true; typedef long type; };
template <> struct ctype<unsigned long> { static constexpr int W = 64; static constexpr bool S = false; typedef unsigned long type; };
template <> struct ctype<long long> { static constexpr int W = 64; static constexpr bool S = true; typedef long long type; };
template <> struct ctype<unsigned long long> { static constexpr int W = 64; static constexpr bool S = false; typedef unsigned long long type; };

// 2^E as a double, computed at compile time (a static constexpr member, so
// the frontend folds it to a constant; __builtin_ldexp would be a libc call).
constexpr double pow2_eval(int e) {
  double r = 1.0;
  for (int i = 0; i < (e < 0 ? -e : e); i++) r = e < 0 ? r * 0.5 : r * 2.0;
  return r;
}
template <int E> struct pow2 { static constexpr double v = pow2_eval(E); };
template <bool S> struct rettype { typedef long long type; };
template <> struct rettype<false> { typedef unsigned long long type; };

// Truncate-toward-zero conversion of a double to a W-bit integer, as
// ap_int_base(double): decode the IEEE mantissa, shift it by the exponent
// (bits shifted out of W are lost), then negate. NaN/inf: Vitis warns and
// proceeds with the raw bits; we do the same.
template <int W, bool S>
constexpr typename bits<W, S>::type double_to_int(double d) {
  typedef typename bits<W, S>::type raw_t;
  typedef ubits<(W > 64 ? W : 64)> uw;
  unsigned long long b = __builtin_bit_cast(unsigned long long, d);
  bool neg = (b >> 63) != 0;
  int e = (int)((b >> 52) & 0x7ff);
  unsigned long long m = b & ((1ull << 52) - 1);
  if (e == 0 && m == 0) return (raw_t)0;
  m |= 1ull << 52;
  int exp = e - 1023;
  uw mag = 0;
  if (exp < 52) {
    int sh = 52 - exp;
    mag = sh < 54 ? (uw)(m >> sh) : (uw)0;
  } else {
    int sh = exp - 52;
    mag = sh < W ? (uw)((uw)m << sh) : (uw)0;
  }
  raw_t r = (raw_t)mag;
  return neg ? (raw_t)(-r) : r;
}

template <int W, bool S> constexpr sbits<W + 1> smin() { return S ? (sbits<W + 1>)(-((sbits<W + 1>)1 << (W - 1))) : (sbits<W + 1>)0; }
template <int W, bool S> constexpr sbits<W + 1> smax() { return S ? (sbits<W + 1>)(((sbits<W + 1>)1 << (W - 1)) - 1) : (sbits<W + 1>)(((sbits<W + 1>)1 << W) - 1); }
} // namespace ap_detail

namespace ap_detail {
// Vitis compares two bitwidth integers with the C usual arithmetic
// conversions (etc/ap_private.h operator<): both narrower than int -> signed;
// same signedness -> that; mixed -> unsigned when the unsigned operand is at
// least as wide as the signed one, else signed. Operands arrive extended to
// MW bits by their own signedness.
template <int W1, bool S1, int W2, bool S2, int MW>
constexpr bool cmp_lt(sbits<MW> l, sbits<MW> r) {
  const bool sgn = (S1 == S2) ? S1 : ((W1 < 32 && W2 < 32) ? true : (S1 ? !(W2 >= W1) : !(W1 >= W2)));
  return sgn ? (l < r) : ((ubits<MW>)l < (ubits<MW>)r);
}
template <int W1, bool S1, int W2, bool S2, int MW>
constexpr bool cmp_eq(sbits<MW> l, sbits<MW> r) { return l == r; }
} // namespace ap_detail

template <int W, int I, bool S, ap_q_mode Q, ap_o_mode O, int N> struct ap_fixed_base;
template <int W, int I, ap_q_mode Q, ap_o_mode O, int N> struct ap_fixed;
template <int W, int I, ap_q_mode Q, ap_o_mode O, int N> struct ap_ufixed;
template <int W> struct ap_int;
template <int W> struct ap_uint;

template <int W, bool S> struct _ap_int_factory { typedef ap_int<W> type; };
template <int W> struct _ap_int_factory<W, false> { typedef ap_uint<W> type; };

template <int W, bool S> struct ap_int_base {
  static_assert(W > 0, "ap_int_base bitwidth must be positive");
  typedef typename ap_detail::bits<W, S>::type raw_t;
  static const int width = W;
  static const bool sign = S;

  raw_t V; // the only data member (uninitialised by default, like Vitis)

  /// Result types of the binary operators (ap_int_base.h RType).
  template <int W2, bool S2> struct RType {
    enum {
      mult_w = W + W2,
      mult_s = S || S2,
      plus_w = ap_detail::max(W + (S2 && !S), W2 + (S && !S2)) + 1,
      plus_s = S || S2,
      minus_w = ap_detail::max(W + (S2 && !S), W2 + (S && !S2)) + 1,
      minus_s = true,
      div_w = W + S2,
      div_s = S || S2,
      mod_w = ap_detail::min(W, W2 + (!S2 && S)),
      mod_s = S,
      logic_w = ap_detail::max(W + (S2 && !S), W2 + (S && !S2)),
      logic_s = S || S2
    };
    typedef ap_int_base<mult_w, mult_s> mult_base;
    typedef ap_int_base<plus_w, plus_s> plus_base;
    typedef ap_int_base<minus_w, minus_s> minus_base;
    typedef ap_int_base<logic_w, logic_s> logic_base;
    typedef ap_int_base<div_w, div_s> div_base;
    typedef ap_int_base<mod_w, mod_s> mod_base;
    typedef ap_int_base<W, S> arg1_base;
    typedef typename _ap_int_factory<mult_w, mult_s>::type mult;
    typedef typename _ap_int_factory<plus_w, plus_s>::type plus;
    typedef typename _ap_int_factory<minus_w, minus_s>::type minus;
    typedef typename _ap_int_factory<logic_w, logic_s>::type logic;
    typedef typename _ap_int_factory<div_w, div_s>::type div;
    typedef typename _ap_int_factory<mod_w, mod_s>::type mod;
    typedef typename _ap_int_factory<W, S>::type arg1;
    typedef bool reduce;
  };

  // ---- constructors (all trivial or constexpr) ----------------------------
  ap_int_base() = default;
  ap_int_base(const ap_int_base &) = default;
  ap_int_base &operator=(const ap_int_base &) = default;
  // from another width: sign/zero-extend by the SOURCE signedness, then wrap.
  template <int W2, bool S2>
  constexpr ap_int_base(const ap_int_base<W2, S2> &o) : V((raw_t)o.V) {}
  template <class T, class = typename ap_detail::ctype<T>::type>
  constexpr ap_int_base(T v) : V((raw_t)v) {}
  constexpr ap_int_base(double d) : V(ap_detail::double_to_int<W, S>(d)) {}
  constexpr ap_int_base(float d) : V(ap_detail::double_to_int<W, S>((double)d)) {}
  // from a fixed-point value: its integer part (floor); defined in ap_fixed.h.
  template <int W2, int I2, bool S2, ap_q_mode Q2, ap_o_mode O2, int N2>
  constexpr ap_int_base(const ap_fixed_base<W2, I2, S2, Q2, O2, N2> &o);

  template <int W2, bool S2>
  constexpr ap_int_base &operator=(const ap_int_base<W2, S2> &o) { V = (raw_t)o.V; return *this; }
  template <class T, class = typename ap_detail::ctype<T>::type>
  constexpr ap_int_base &operator=(T v) { V = (raw_t)v; return *this; }

  // ---- conversions ---------------------------------------------------------
  // Vitis: `operator RetType()` with RetType the 64-bit C integer of the
  // same signedness (relied on for array subscripts and mixed arithmetic).
  constexpr operator typename ap_detail::rettype<S>::type() const {
    return (typename ap_detail::rettype<S>::type)V;
  }
  constexpr bool to_bool() const { return V != 0; }
  constexpr char to_char() const { return (char)V; }
  constexpr signed char to_schar() const { return (signed char)V; }
  constexpr unsigned char to_uchar() const { return (unsigned char)V; }
  constexpr short to_short() const { return (short)V; }
  constexpr unsigned short to_ushort() const { return (unsigned short)V; }
  constexpr int to_int() const { return (int)V; }
  constexpr unsigned to_uint() const { return (unsigned)V; }
  constexpr long to_long() const { return (long)V; }
  constexpr unsigned long to_ulong() const { return (unsigned long)V; }
  constexpr ap_slong to_int64() const { return (ap_slong)V; }
  constexpr ap_ulong to_uint64() const { return (ap_ulong)V; }
  constexpr float to_float() const { return (float)V; }
  constexpr double to_double() const { return (double)V; }
  constexpr _Float16 to_half() const { return (_Float16)(float)V; }

  constexpr int length() const { return W; }
  constexpr bool iszero() const { return V == 0; }
  constexpr bool is_zero() const { return V == 0; }
  constexpr bool sign_bit() const { return ((ap_detail::ubits<W>)V >> (W - 1)) & 1; }

  // ---- bit and slice selects (value-returning) ----------------------------
  constexpr bool operator[](int i) const { return (((ap_detail::ubits<W>)V >> i) & 1) != 0; }
  constexpr bool bit(int i) const { return (*this)[i]; }
  constexpr bool get_bit(int i) const { return (*this)[i]; }
  constexpr bool test(int i) const { return (*this)[i]; }
  constexpr void set_bit(int i, bool b) {
    ap_detail::ubits<W> m = (ap_detail::ubits<W>)1 << i;
    V = (raw_t)(b ? ((ap_detail::ubits<W>)V | m) : ((ap_detail::ubits<W>)V & (ap_detail::ubits<W>)~m));
  }
  constexpr void set(int i) { set_bit(i, true); }
  constexpr void set(int i, bool b) { set_bit(i, b); }
  constexpr void clear(int i) { set_bit(i, false); }
  constexpr void invert(int i) { set_bit(i, !(*this)[i]); }
  // bits [hi:lo], zero-extended to W bits (what an ap_range_ref converts to).
  constexpr const ap_int_base<W, false> range(int hi, int lo) const {
    ap_int_base<W, false> r;
    int h = hi, l = lo;
    if (h < l) { h = lo; l = hi; }
    int n = h - l + 1;
    ap_detail::ubits<W> v = (ap_detail::ubits<W>)V >> l;
    if (n < W) v &= (ap_detail::ubits<W>)((((ap_detail::ubits<W + 1>)1) << n) - 1);
    if (hi < lo) { // reversed select
      ap_detail::ubits<W> o = 0;
      for (int k = 0; k < n; k++) o |= (ap_detail::ubits<W>)(((v >> k) & 1)) << (n - 1 - k);
      v = o;
    }
    r.V = v;
    return r;
  }
  constexpr const ap_int_base<W, false> range() const { ap_int_base<W, false> r; r.V = (ap_detail::ubits<W>)V; return r; }
  constexpr const ap_int_base<W, false> operator()(int hi, int lo) const { return range(hi, lo); }
  constexpr const ap_int_base<W, false> range(int hi, int lo) { return ((const ap_int_base *)this)->range(hi, lo); }
  constexpr const ap_int_base<W, false> operator()(int hi, int lo) { return range(hi, lo); }

  constexpr bool and_reduce() const { return (ap_detail::ubits<W>)V == (ap_detail::ubits<W>)~(ap_detail::ubits<W>)0; }
  constexpr bool nand_reduce() const { return !and_reduce(); }
  constexpr bool or_reduce() const { return V != 0; }
  constexpr bool nor_reduce() const { return V == 0; }
  constexpr bool xor_reduce() const {
    bool p = false;
    for (int i = 0; i < W; i++) p ^= (*this)[i];
    return p;
  }
  constexpr bool xnor_reduce() const { return !xor_reduce(); }
  constexpr void reverse() {
    ap_detail::ubits<W> o = 0, v = (ap_detail::ubits<W>)V;
    for (int k = 0; k < W; k++) o |= (ap_detail::ubits<W>)((v >> k) & 1) << (W - 1 - k);
    V = (raw_t)o;
  }
  constexpr int countLeadingZeros() const {
    int n = 0;
    for (int i = W - 1; i >= 0 && !(*this)[i]; i--) n++;
    return n;
  }

  // ---- unary ---------------------------------------------------------------
  constexpr typename RType<1, false>::minus operator-() const {
    typename RType<1, false>::minus_base r;
    r.V = (typename RType<1, false>::minus_base::raw_t)(-(ap_detail::sbits<W + 2>)V);
    return typename RType<1, false>::minus(r);
  }
  constexpr typename RType<W, S>::arg1 operator+() const { return typename RType<W, S>::arg1(*this); }
  constexpr typename RType<W, S>::arg1 operator~() const {
    ap_int_base r;
    r.V = (raw_t)~V;
    return typename RType<W, S>::arg1(r);
  }
  constexpr bool operator!() const { return V == 0; }

  constexpr ap_int_base &operator++() { V = (raw_t)((ap_detail::sbits<W + 2>)V + 1); return *this; }
  constexpr ap_int_base &operator--() { V = (raw_t)((ap_detail::sbits<W + 2>)V - 1); return *this; }
  constexpr const ap_int_base operator++(int) { ap_int_base t(*this); ++*this; return t; }
  constexpr const ap_int_base operator--(int) { ap_int_base t(*this); --*this; return t; }

  // ---- shifts: the result keeps W bits ------------------------------------
  constexpr typename RType<W, S>::arg1 operator<<(unsigned sh) const {
    ap_int_base r;
    r.V = sh < (unsigned)W ? (raw_t)((ap_detail::ubits<W>)V << sh) : (raw_t)0;
    return typename RType<W, S>::arg1(r);
  }
  constexpr typename RType<W, S>::arg1 operator>>(unsigned sh) const {
    ap_int_base r;
    if (sh < (unsigned)W) r.V = (raw_t)(V >> sh);
    else r.V = (S && V < 0) ? (raw_t)-1 : (raw_t)0;
    return typename RType<W, S>::arg1(r);
  }
  constexpr typename RType<W, S>::arg1 operator<<(int sh) const { return sh < 0 ? operator>>((unsigned)-sh) : operator<<((unsigned)sh); }
  constexpr typename RType<W, S>::arg1 operator>>(int sh) const { return sh < 0 ? operator<<((unsigned)-sh) : operator>>((unsigned)sh); }
  template <int W2, bool S2>
  constexpr typename RType<W, S>::arg1 operator<<(const ap_int_base<W2, S2> &o) const { return operator<<((int)o.to_int64()); }
  template <int W2, bool S2>
  constexpr typename RType<W, S>::arg1 operator>>(const ap_int_base<W2, S2> &o) const { return operator>>((int)o.to_int64()); }
  template <class T> constexpr ap_int_base &operator<<=(const T &sh) { *this = operator<<(sh); return *this; }
  template <class T> constexpr ap_int_base &operator>>=(const T &sh) { *this = operator>>(sh); return *this; }

  // ---- compound assignment (the binary operator, then wrap) ---------------
  template <class T> constexpr ap_int_base &operator+=(const T &o) { *this = (*this + o); return *this; }
  template <class T> constexpr ap_int_base &operator-=(const T &o) { *this = (*this - o); return *this; }
  template <class T> constexpr ap_int_base &operator*=(const T &o) { *this = (*this * o); return *this; }
  template <class T> constexpr ap_int_base &operator/=(const T &o) { *this = (*this / o); return *this; }
  template <class T> constexpr ap_int_base &operator%=(const T &o) { *this = (*this % o); return *this; }
  template <class T> constexpr ap_int_base &operator&=(const T &o) { *this = (*this & o); return *this; }
  template <class T> constexpr ap_int_base &operator|=(const T &o) { *this = (*this | o); return *this; }
  template <class T> constexpr ap_int_base &operator^=(const T &o) { *this = (*this ^ o); return *this; }
};

// ---- binary operators on two ap_int_base: exact in a wide type, then the
// Vitis result width (ap_int_base.h OP_BIN_AP / OP_BIN_AP2) --------------------
namespace ap_detail {
template <int W1, bool S1, int W2, bool S2> struct wide2 { typedef sbits<W1 + W2 + 2> type; };
}
#define HLSEST_AP_INT_BIN(SYM, RTY)                                                         \
  template <int W1, bool S1, int W2, bool S2>                                               \
  constexpr typename ap_int_base<W1, S1>::template RType<W2, S2>::RTY operator SYM(           \
      const ap_int_base<W1, S1> &a, const ap_int_base<W2, S2> &b) {                         \
    typedef typename ap_detail::wide2<W1, S1, W2, S2>::type wide;                           \
    typename ap_int_base<W1, S1>::template RType<W2, S2>::RTY##_base r;                     \
    r.V = (typename ap_int_base<W1, S1>::template RType<W2, S2>::RTY##_base::raw_t)(        \
        (wide)a.V SYM(wide) b.V);                                                           \
    return typename ap_int_base<W1, S1>::template RType<W2, S2>::RTY(r);                    \
  }
HLSEST_AP_INT_BIN(+, plus)
HLSEST_AP_INT_BIN(-, minus)
HLSEST_AP_INT_BIN(*, mult)
HLSEST_AP_INT_BIN(&, logic)
HLSEST_AP_INT_BIN(|, logic)
HLSEST_AP_INT_BIN(^, logic)
#undef HLSEST_AP_INT_BIN
// Division and modulo (etc/ap_private.h operator/ and operator%): both
// operands are extended by their own signedness to the common type of
// MAX(W1,W2) + (S1||S2) bits whose signedness is that of the wider operand
// (signed if either is, at equal widths); quotient and remainder are signed
// when that common type is.
// A negative value in an unsigned common type is therefore its bit pattern
// (ap_uint<16>(17272) / ap_int<8>(-1) is 0). A zero divisor is undefined
// (Vitis: `undef`; the IR carries `divsi x, 0`).
template <int W1, bool S1, int W2, bool S2>
constexpr typename ap_int_base<W1, S1>::template RType<W2, S2>::div operator/(
    const ap_int_base<W1, S1> &a, const ap_int_base<W2, S2> &b) {
  typedef typename ap_int_base<W1, S1>::template RType<W2, S2>::div_base R;
  const int MW = ap_detail::max(W1, W2) + (S1 || S2);
  const bool CS = W1 > W2 ? S1 : (W2 > W1 ? S2 : (S1 || S2));
  typedef ap_detail::sbits<MW + 1> sw;
  typedef ap_detail::ubits<MW> uw;
  sw l = (sw)a.V, r = (sw)b.V;
  R res;
  if (CS) res.V = (typename R::raw_t)(l / r);
  else res.V = (typename R::raw_t)((uw)l / (uw)r);
  return typename ap_int_base<W1, S1>::template RType<W2, S2>::div(res);
}
template <int W1, bool S1, int W2, bool S2>
constexpr typename ap_int_base<W1, S1>::template RType<W2, S2>::mod operator%(
    const ap_int_base<W1, S1> &a, const ap_int_base<W2, S2> &b) {
  typedef typename ap_int_base<W1, S1>::template RType<W2, S2>::mod_base R;
  const int MW = ap_detail::max(W1, W2) + (S1 || S2);
  const bool CS = W1 > W2 ? S1 : (W2 > W1 ? S2 : (S1 || S2));
  typedef ap_detail::sbits<MW + 1> sw;
  typedef ap_detail::ubits<MW> uw;
  sw l = (sw)a.V, r = (sw)b.V;
  R res;
  if (CS) res.V = (typename R::raw_t)(l % r);
  else res.V = (typename R::raw_t)((uw)l % (uw)r);
  return typename ap_int_base<W1, S1>::template RType<W2, S2>::mod(res);
}
#define HLSEST_AP_INT_REL(SYM, EXPR)                                                        \
  template <int W1, bool S1, int W2, bool S2>                                               \
  constexpr bool operator SYM(const ap_int_base<W1, S1> &a, const ap_int_base<W2, S2> &b) { \
    const int MW = ap_detail::max(W1, W2) + 1;                                              \
    ap_detail::sbits<MW> l = (ap_detail::sbits<MW>)a.V, r = (ap_detail::sbits<MW>)b.V;      \
    return EXPR;                                                                            \
  }
HLSEST_AP_INT_REL(<, (ap_detail::cmp_lt<W1, S1, W2, S2, MW>(l, r)))
HLSEST_AP_INT_REL(>, (ap_detail::cmp_lt<W2, S2, W1, S1, MW>(r, l)))
HLSEST_AP_INT_REL(<=, (!ap_detail::cmp_lt<W2, S2, W1, S1, MW>(r, l)))
HLSEST_AP_INT_REL(>=, (!ap_detail::cmp_lt<W1, S1, W2, S2, MW>(l, r)))
HLSEST_AP_INT_REL(==, (ap_detail::cmp_eq<W1, S1, W2, S2, MW>(l, r)))
HLSEST_AP_INT_REL(!=, (!ap_detail::cmp_eq<W1, S1, W2, S2, MW>(l, r)))
#undef HLSEST_AP_INT_REL

// ---- mixed with C integers: the C value becomes ap_int_base<ctype::W, ctype::S>
// (ap_int_base.h ALL_OP_BIN_WITH_INT / ALL_OP_REL_WITH_INT). ------------------
#define HLSEST_AP_INT_MIX(SYM, RTY)                                                         \
  template <int W, bool S, class T>                                                         \
  constexpr typename ap_int_base<W, S>::template RType<ap_detail::ctype<T>::W,              \
                                                        ap_detail::ctype<T>::S>::RTY        \
  operator SYM(const ap_int_base<W, S> &a, T b) {                                           \
    return a SYM ap_int_base<ap_detail::ctype<T>::W, ap_detail::ctype<T>::S>(b);            \
  }                                                                                         \
  template <int W, bool S, class T>                                                         \
  constexpr typename ap_int_base<W, S>::template RType<ap_detail::ctype<T>::W,              \
                                                        ap_detail::ctype<T>::S>::RTY        \
      operator SYM(T a, const ap_int_base<W, S> &b) {                                       \
    return ap_int_base<ap_detail::ctype<T>::W, ap_detail::ctype<T>::S>(a) SYM b;            \
  }
HLSEST_AP_INT_MIX(+, plus)
HLSEST_AP_INT_MIX(-, minus)
HLSEST_AP_INT_MIX(*, mult)
HLSEST_AP_INT_MIX(/, div)
HLSEST_AP_INT_MIX(%, mod)
HLSEST_AP_INT_MIX(&, logic)
HLSEST_AP_INT_MIX(|, logic)
HLSEST_AP_INT_MIX(^, logic)
#undef HLSEST_AP_INT_MIX
#define HLSEST_AP_INT_MIXREL(SYM)                                                           \
  template <int W, bool S, class T, class = typename ap_detail::ctype<T>::type>             \
  constexpr bool operator SYM(const ap_int_base<W, S> &a, T b) {                            \
    return a SYM ap_int_base<ap_detail::ctype<T>::W, ap_detail::ctype<T>::S>(b);            \
  }                                                                                         \
  template <int W, bool S, class T, class = typename ap_detail::ctype<T>::type>             \
  constexpr bool operator SYM(T a, const ap_int_base<W, S> &b) {                            \
    return ap_int_base<ap_detail::ctype<T>::W, ap_detail::ctype<T>::S>(a) SYM b;            \
  }
HLSEST_AP_INT_MIXREL(<)
HLSEST_AP_INT_MIXREL(>)
HLSEST_AP_INT_MIXREL(<=)
HLSEST_AP_INT_MIXREL(>=)
HLSEST_AP_INT_MIXREL(==)
HLSEST_AP_INT_MIXREL(!=)
#undef HLSEST_AP_INT_MIXREL

// Concatenation (a, b): the W1+W2 raw bits, unsigned.
template <int W1, bool S1, int W2, bool S2>
constexpr const ap_uint<W1 + W2> operator,(const ap_int_base<W1, S1> &a, const ap_int_base<W2, S2> &b) {
  ap_int_base<W1 + W2, false> r;
  r.V = ((ap_detail::ubits<W1 + W2>)(ap_detail::ubits<W1>)a.V << W2) | (ap_detail::ubits<W1 + W2>)(ap_detail::ubits<W2>)b.V;
  return ap_uint<W1 + W2>(r);
}

template <int W> struct ap_int : ap_int_base<W, true> {
  typedef ap_int_base<W, true> Base;
  ap_int() = default;
  ap_int(const ap_int &) = default;
  ap_int &operator=(const ap_int &) = default;
  template <class T> constexpr ap_int(const T &v) : Base(v) {}
  template <class T> constexpr ap_int &operator=(const T &v) { this->V = ap_int(v).V; return *this; }
};
template <int W> struct ap_uint : ap_int_base<W, false> {
  typedef ap_int_base<W, false> Base;
  ap_uint() = default;
  ap_uint(const ap_uint &) = default;
  ap_uint &operator=(const ap_uint &) = default;
  template <class T> constexpr ap_uint(const T &v) : Base(v) {}
  template <class T> constexpr ap_uint &operator=(const T &v) { this->V = ap_uint(v).V; return *this; }
};

#include "ap_fixed.h"

#endif // __cplusplus
#endif
