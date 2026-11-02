// RUN: hls-est %s --split-input-file --vitis-fold | FileCheck %s
// RUN: hls-est %s --split-input-file --vitis-fold=undef=false | FileCheck %s --check-prefix=T4
// RUN: hls-est %s --split-input-file --vitis-fold=canonicalize=false | FileCheck %s --check-prefix=NOCANON

// --vitis-fold, option `undef` (default on): what Vitis HLS 2025.1 does with
// the undefined value U of an integer division / signed remainder by a
// constant 0 (VITIS_NOTES.md N13). Each function mirrors output slots of the
// Vitis kernel ~/hls-est-work/exp-src/t8/undef_cint.cpp (run t8_undef_cint,
// stores of a.o.1.ll) or of the ap_fixed probes (result_read_headers.md
// section 2), in SSA form (what mem2reg gives Vitis). `undef=false` is the T4
// rule: x / 0 -> 0.

// Sources: divsi / divui / remsi by a constant 0 are U; a store of U into an
// output is deleted (out[0], uout[0], o_sdiv / o_srem / o_udiv of
// dg_d_fold_divrem0). remui by 0 is 0 (dg_d_fold_divrem0 o_urem, uout[1]).
// CHECK-LABEL: func.func @sources
// CHECK-DAG: %[[Z:.*]] = arith.constant 0 : i32
// CHECK-NOT: arith.divsi
// CHECK-NOT: arith.divui
// CHECK-NOT: arith.remsi
// CHECK-NOT: arith.remui
// CHECK: memref.store %[[Z]], %arg1[%c3]
// CHECK-NEXT: return
// T4-LABEL: func.func @sources
// T4-COUNT-4: memref.store %c0_i32
// NOCANON-LABEL: func.func @sources
// NOCANON-NOT: arith.divsi
// NOCANON: arith.constant 0 : i32
// NOCANON: memref.store
// NOCANON-NOT: memref.store
// NOCANON: return
func.func @sources(%x: i32, %out: memref<4xi32>) {
  %c0 = arith.constant 0 : i32
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %i2 = arith.constant 2 : index
  %i3 = arith.constant 3 : index
  %a = arith.divsi %x, %c0 : i32
  memref.store %a, %out[%i0] : memref<4xi32>
  %b = arith.divui %x, %c0 : i32
  memref.store %b, %out[%i1] : memref<4xi32>
  %c = arith.remsi %x, %c0 : i32
  memref.store %c, %out[%i2] : memref<4xi32>
  %d = arith.remui %x, %c0 : i32
  memref.store %d, %out[%i3] : memref<4xi32>
  return
}

// -----

// add / sub / neg / xor / trunc keep U: out[1] x+U, out[2] x-U, out[3] U-x,
// out[5] -U, out[14] U^x, out16[0] (short)U, out[25] x + y%0: all deleted.
// CHECK-LABEL: func.func @keep_undef
// CHECK-NOT: memref.store
// CHECK: return
// T4-LABEL: func.func @keep_undef
// T4: memref.store %arg0, %arg2[%c0]
func.func @keep_undef(%x: i32, %y: i32, %out: memref<8xi32>, %out16: memref<1xi16>) {
  %c0 = arith.constant 0 : i32
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %i2 = arith.constant 2 : index
  %i3 = arith.constant 3 : index
  %i4 = arith.constant 4 : index
  %i5 = arith.constant 5 : index
  %u = arith.divsi %y, %c0 : i32
  %a = arith.addi %x, %u : i32
  memref.store %a, %out[%i0] : memref<8xi32>
  %s = arith.subi %x, %u : i32
  memref.store %s, %out[%i1] : memref<8xi32>
  %s2 = arith.subi %u, %x : i32
  memref.store %s2, %out[%i2] : memref<8xi32>
  %n = arith.subi %c0, %u : i32
  memref.store %n, %out[%i3] : memref<8xi32>
  %xo = arith.xori %u, %x : i32
  memref.store %xo, %out[%i4] : memref<8xi32>
  %r = arith.remsi %y, %c0 : i32
  %a2 = arith.addi %x, %r : i32
  memref.store %a2, %out[%i5] : memref<8xi32>
  %t = arith.trunci %u : i32 to i16
  memref.store %t, %out16[%i0] : memref<1xi16>
  return
}

// -----

// Extensions of U are 0 (out64[0] sext, out64[2] zext, out64[1] sext(U) + x);
// the ap_fixed sum `in + scale` of the exactclass shim is in + sext(U) -> in
// (probe out[2], dg_d_fold_divrem0b o_fvar), sitofp(U) is 0.
// CHECK-LABEL: func.func @ext_zero
// CHECK-DAG: %[[Z64:.*]] = arith.constant 0 : i64
// CHECK-DAG: %[[ZF:.*]] = arith.constant 0.000000e+00 : f64
// CHECK: memref.store %[[Z64]], %arg2[%c0]
// CHECK: memref.store %[[Z64]], %arg2[%c1]
// CHECK: %[[XE:.*]] = arith.extsi %arg0 : i32 to i64
// CHECK: memref.store %[[XE]], %arg2[%c2]
// CHECK: memref.store %arg1, %arg3[%c0]
// CHECK: memref.store %[[ZF]], %arg4[%c0]
func.func @ext_zero(%x: i32, %in: i16, %out64: memref<4xi64>, %out16: memref<1xi16>, %outf: memref<1xf64>) {
  %c0 = arith.constant 0 : i32
  %c0_29 = arith.constant 0 : i29
  %c4194304 = arith.constant 4194304 : i29
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %i2 = arith.constant 2 : index
  %u = arith.divsi %x, %c0 : i32
  %e = arith.extsi %u : i32 to i64
  memref.store %e, %out64[%i0] : memref<4xi64>
  %z = arith.extui %u : i32 to i64
  memref.store %z, %out64[%i1] : memref<4xi64>
  %xe = arith.extsi %x : i32 to i64
  %s = arith.addi %e, %xe : i64
  memref.store %s, %out64[%i2] : memref<4xi64>
  // scale = (data_t)1.0 / sqrt((data_t)16) in the exactclass shim
  %q = arith.divsi %c4194304, %c0_29 : i29
  %scale = arith.trunci %q : i29 to i16
  %ine = arith.extsi %in : i16 to i18
  %se = arith.extsi %scale : i16 to i18
  %sum = arith.addi %ine, %se : i18
  %st = arith.trunci %sum : i18 to i16
  memref.store %st, %out16[%i0] : memref<1xi16>
  %f = arith.sitofp %scale : i16 to f64
  memref.store %f, %outf[%i0] : memref<1xf64>
  return
}

// -----

// mul: x*U -> 0 (out[4]), U*2 + y -> y (out[23]), U*3 + y -> U, deleted
// (out[24]: an odd factor keeps U), (U+1)*x -> 0 (out[26]); the attention
// step `scores *= scale` (sext / mul / shrsi / trunci) stores 0 (probe out[1]).
// CHECK-LABEL: func.func @mul
// CHECK-DAG: %[[Z:.*]] = arith.constant 0 : i32
// CHECK-DAG: %[[Z16:.*]] = arith.constant 0 : i16
// CHECK: memref.store %[[Z]], %arg2[%c0]
// CHECK: memref.store %arg1, %arg2[%c1]
// CHECK-NOT: memref.store {{.*}}%arg2[%c2]
// CHECK: memref.store %[[Z]], %arg2[%c3]
// CHECK: memref.store %[[Z16]], %arg3[%c0]
func.func @mul(%x: i32, %y: i32, %out: memref<4xi32>, %scores: memref<1xi16>) {
  %c0 = arith.constant 0 : i32
  %c1 = arith.constant 1 : i32
  %c2 = arith.constant 2 : i32
  %c3 = arith.constant 3 : i32
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %i2 = arith.constant 2 : index
  %i3 = arith.constant 3 : index
  %u = arith.divsi %x, %c0 : i32
  %m = arith.muli %x, %u : i32
  memref.store %m, %out[%i0] : memref<4xi32>
  %m2 = arith.muli %u, %c2 : i32
  %a2 = arith.addi %m2, %y : i32
  memref.store %a2, %out[%i1] : memref<4xi32>
  %m3 = arith.muli %u, %c3 : i32
  %a3 = arith.addi %m3, %y : i32
  memref.store %a3, %out[%i2] : memref<4xi32>
  %p = arith.addi %u, %c1 : i32
  %m4 = arith.muli %p, %x : i32
  memref.store %m4, %out[%i3] : memref<4xi32>
  %c0_29 = arith.constant 0 : i29
  %c4194304 = arith.constant 4194304 : i29
  %c11 = arith.constant 11 : i51
  %q = arith.divsi %c4194304, %c0_29 : i29
  %scale = arith.trunci %q : i29 to i16
  %sv = memref.load %scores[%i0] : memref<1xi16>
  %a = arith.extsi %sv : i16 to i32
  %b = arith.extsi %scale : i16 to i32
  %ab = arith.muli %a, %b : i32
  %w = arith.extsi %ab : i32 to i51
  %sh = arith.shrsi %w, %c11 : i51
  %r = arith.trunci %sh : i51 to i16
  memref.store %r, %scores[%i0] : memref<1xi16>
  return
}

// -----

// and -> 0 (out[12]), or -> -1 (out[13]); U << c, U >> c (shrsi, shrui) -> 0
// (out[6..8]); x << U is U: x << U + y deleted (out[27]); U / c -> 0 (out[10]);
// x / U and x % U are U, deleted (out[9], out[11]).
// CHECK-LABEL: func.func @bits_shifts_div
// CHECK-DAG: %[[Z:.*]] = arith.constant 0 : i32
// CHECK-DAG: %[[ONES:.*]] = arith.constant -1 : i32
// CHECK: memref.store %[[Z]], %arg2[%c0]
// CHECK: memref.store %[[ONES]], %arg2[%c1]
// CHECK: memref.store %[[Z]], %arg2[%c2]
// CHECK: memref.store %[[Z]], %arg2[%c3]
// CHECK: memref.store %[[Z]], %arg2[%c4]
// CHECK: memref.store %[[Z]], %arg2[%c6]
// CHECK-NOT: memref.store
// CHECK: return
func.func @bits_shifts_div(%x: i32, %y: i32, %out: memref<9xi32>) {
  %c0 = arith.constant 0 : i32
  %c2 = arith.constant 2 : i32
  %c3 = arith.constant 3 : i32
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %i2 = arith.constant 2 : index
  %i3 = arith.constant 3 : index
  %i4 = arith.constant 4 : index
  %i5 = arith.constant 5 : index
  %i6 = arith.constant 6 : index
  %i7 = arith.constant 7 : index
  %i8 = arith.constant 8 : index
  %u = arith.divsi %x, %c0 : i32
  %and = arith.andi %u, %y : i32
  memref.store %and, %out[%i0] : memref<9xi32>
  %or = arith.ori %u, %y : i32
  memref.store %or, %out[%i1] : memref<9xi32>
  %shl = arith.shli %u, %c2 : i32
  memref.store %shl, %out[%i2] : memref<9xi32>
  %ashr = arith.shrsi %u, %c2 : i32
  memref.store %ashr, %out[%i3] : memref<9xi32>
  %lshr = arith.shrui %u, %c2 : i32
  memref.store %lshr, %out[%i4] : memref<9xi32>
  %shu = arith.shli %y, %u : i32
  %shua = arith.addi %x, %shu : i32
  memref.store %shua, %out[%i5] : memref<9xi32>
  %d3 = arith.divsi %u, %c3 : i32
  memref.store %d3, %out[%i6] : memref<9xi32>
  %du = arith.divsi %y, %u : i32
  memref.store %du, %out[%i7] : memref<9xi32>
  %ru = arith.remsi %y, %u : i32
  memref.store %ru, %out[%i8] : memref<9xi32>
  return
}

// -----

// cmpi pred (U, y) is isTrueWhenEqual(pred) whatever y is: slt / sgt / ne
// false, eq / sle true (out[15..19]); `if (U > 5)` takes the else branch
// (out[22]); through a pair of sign extensions from one type the same
// (ap_fixed `scale < in[6] ? in[6] : in[7]` -> in[7], probe2 out[16]).
// CHECK-LABEL: func.func @compare
// CHECK: memref.store %arg2, %arg3[%c0]
// CHECK: memref.store %arg1, %arg3[%c1]
// CHECK: memref.store %arg2, %arg3[%c2]
// CHECK: memref.store %arg2, %arg3[%c3]
// CHECK: memref.store %arg1, %arg3[%c4]
// CHECK-NOT: scf.if
// CHECK: memref.store %arg2, %arg3[%c5]
// CHECK: memref.store %arg5, %arg6[%c0]
func.func @compare(%x: i32, %a: i32, %b: i32, %out: memref<6xi32>, %h6: i16, %h7: i16, %out16: memref<1xi16>) {
  %c0 = arith.constant 0 : i32
  %c5 = arith.constant 5 : i32
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %i2 = arith.constant 2 : index
  %i3 = arith.constant 3 : index
  %i4 = arith.constant 4 : index
  %i5 = arith.constant 5 : index
  %u = arith.divsi %x, %c0 : i32
  %lt = arith.cmpi slt, %u, %x : i32
  %s0 = arith.select %lt, %a, %b : i32
  memref.store %s0, %out[%i0] : memref<6xi32>
  %eq = arith.cmpi eq, %u, %c0 : i32
  %s1 = arith.select %eq, %a, %b : i32
  memref.store %s1, %out[%i1] : memref<6xi32>
  %gt = arith.cmpi sgt, %u, %x : i32
  %s2 = arith.select %gt, %a, %b : i32
  memref.store %s2, %out[%i2] : memref<6xi32>
  %ne = arith.cmpi ne, %u, %x : i32
  %s3 = arith.select %ne, %a, %b : i32
  memref.store %s3, %out[%i3] : memref<6xi32>
  %le = arith.cmpi sle, %u, %x : i32
  %s4 = arith.select %le, %a, %b : i32
  memref.store %s4, %out[%i4] : memref<6xi32>
  %g5 = arith.cmpi sgt, %u, %c5 : i32
  scf.if %g5 {
    memref.store %a, %out[%i5] : memref<6xi32>
  } else {
    memref.store %b, %out[%i5] : memref<6xi32>
  }
  %c0_29 = arith.constant 0 : i29
  %c4194304 = arith.constant 4194304 : i29
  %q = arith.divsi %c4194304, %c0_29 : i29
  %scale = arith.trunci %q : i29 to i16
  %se = arith.extsi %scale : i16 to i17
  %he = arith.extsi %h6 : i16 to i17
  %c = arith.cmpi slt, %se, %he : i17
  %r = arith.select %c, %h6, %h7 : i16
  memref.store %r, %out16[%i0] : memref<1xi16>
  return
}

// -----

// select c, U, y and select c, y, U give y (out[20], out[21]; Vitis stores
// out[20] only when !c, the same arrays stay live).
// CHECK-LABEL: func.func @select_arm
// CHECK: memref.store %arg2, %arg3[%c0]
// CHECK: memref.store %arg2, %arg3[%c1]
func.func @select_arm(%x: i32, %c: i1, %y: i32, %out: memref<2xi32>) {
  %c0 = arith.constant 0 : i32
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %u = arith.divsi %x, %c0 : i32
  %s0 = arith.select %c, %u, %y : i32
  memref.store %s0, %out[%i0] : memref<2xi32>
  %s1 = arith.select %c, %y, %u : i32
  memref.store %s1, %out[%i1] : memref<2xi32>
  return
}

// -----

// The C int attention kernel's scale `x / 0` kept in a local scalar (a
// memref<1xi32> alloca, as cgeist emits an address-taken local): loads of it
// later in the block, also inside the loop, read U, so `out[i] = in[i] + u`
// is deleted and `in` is no longer read; the store into the local becomes 0.
// A load after an intervening store into the local is not forwarded.
// CHECK-LABEL: func.func @local_scalar
// CHECK: memref.alloca
// CHECK: affine.store %c0_i32, %{{.*}}[0]
// CHECK-NOT: affine.load %arg1
// CHECK: affine.store %arg0, %{{.*}}[0]
// CHECK: %[[L:.*]] = affine.load %{{.*}}[0]
// CHECK: affine.store %[[L]], %arg2[8]
// CHECK-NEXT: return
func.func @local_scalar(%x: i32, %in: memref<8xi32>, %out: memref<9xi32>) {
  %c0 = arith.constant 0 : i32
  %loc = memref.alloca() : memref<1xi32>
  %u = arith.divsi %x, %c0 : i32
  affine.store %u, %loc[0] : memref<1xi32>
  affine.for %i = 0 to 8 {
    %v = affine.load %in[%i] : memref<8xi32>
    %w = affine.load %loc[0] : memref<1xi32>
    %s = arith.addi %v, %w : i32
    affine.store %s, %out[%i] : memref<9xi32>
  }
  affine.store %x, %loc[0] : memref<1xi32>
  %l = affine.load %loc[0] : memref<1xi32>
  affine.store %l, %out[8] : memref<9xi32>
  return
}

// -----

// Uses that were not measured see U := 0 (the T4 refinement): a min / max,
// an index computed from U (index 0). Known difference (N13): a
// --canonicalize before this pass merges `(u >= x) ? u : x` into
// `maxsi U, x`, which no longer says whether the compare was sge (Vitis: U,
// the store is deleted) or sgt (Vitis: x); max(x, 0) is stored.
// CHECK-LABEL: func.func @use_zero
// CHECK: %[[M:.*]] = arith.maxsi %arg1, %{{.*}} : i32
// CHECK: memref.store %[[M]], %arg2[%c0]
// CHECK: %[[V:.*]] = memref.load %arg3[%c0]
// CHECK: memref.store %[[V]], %arg2[%c1]
func.func @use_zero(%x: i32, %y: i32, %out: memref<2xi32>, %tbl: memref<16xi32>) {
  %c0 = arith.constant 0 : i32
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %u = arith.divsi %x, %c0 : i32
  %mx = arith.maxsi %u, %y : i32
  memref.store %mx, %out[%i0] : memref<2xi32>
  %idx = arith.index_cast %u : i32 to index
  %v = memref.load %tbl[%idx] : memref<16xi32>
  memref.store %v, %out[%i1] : memref<2xi32>
  return
}

// -----

// The T8 review kernel ~/hls-est-work/exp-src/t8review/rv_undef2.cpp (run
// t8review_undef2/e731b57e6aee) in SSA form: Vitis keeps only out[7] = 0
// and out[9] = in[8]. x >> U (shrsi, shrui) and x % U unsigned are U
// (out[0], out[1], uout[0]); x << U is U (out[2]); U * U2, U & U2, U | U2
// are U (out[5], out[6], out[8]) and U ^ U2 is 0 (out[7]); the compare of U
// decides the select before it could become a max: `(u >= x) ? u : x` and
// `(u < x) ? x : u` are U (out[3], out[4]); x >> (U & 31) is x (out[9]).
// CHECK-LABEL: func.func @review_undef2
// CHECK: %[[Z:.*]] = arith.constant 0 : i32
// CHECK-NOT: affine.store
// CHECK: affine.store %[[Z]], %arg1[7]
// CHECK-NEXT: %[[L:.*]] = affine.load %arg0[8]
// CHECK-NEXT: affine.store %[[L]], %arg1[9]
// CHECK-NEXT: return
// T4-LABEL: func.func @review_undef2
// T4: affine.store %{{.*}}, %arg1[0]
// NOCANON-LABEL: func.func @review_undef2
// NOCANON-NOT: affine.store
// NOCANON: affine.store %{{.*}}, %arg1[7]
// NOCANON-NOT: affine.store
// NOCANON: affine.store %{{.*}}, %arg1[9]
// NOCANON-NEXT: return
func.func @review_undef2(%in: memref<16xi32>, %out: memref<16xi32>, %uout: memref<4xi32>) {
  %c0 = arith.constant 0 : i32
  %c31 = arith.constant 31 : i32
  %x0 = affine.load %in[0] : memref<16xi32>
  %x1 = affine.load %in[1] : memref<16xi32>
  %u = arith.divsi %x0, %c0 : i32
  %u2 = arith.divsi %x1, %c0 : i32
  %a2 = affine.load %in[2] : memref<16xi32>
  %s0 = arith.shrsi %a2, %u : i32
  affine.store %s0, %out[0] : memref<16xi32>
  %a3 = affine.load %in[3] : memref<16xi32>
  %s1 = arith.shrui %a3, %u : i32
  affine.store %s1, %out[1] : memref<16xi32>
  %a4 = affine.load %in[4] : memref<16xi32>
  %s2 = arith.shli %a4, %u : i32
  affine.store %s2, %out[2] : memref<16xi32>
  %a5 = affine.load %in[5] : memref<16xi32>
  %c3 = arith.cmpi sge, %u, %a5 : i32
  %s3 = arith.select %c3, %u, %a5 : i32
  affine.store %s3, %out[3] : memref<16xi32>
  %a6 = affine.load %in[6] : memref<16xi32>
  %c4 = arith.cmpi slt, %u, %a6 : i32
  %s4 = arith.select %c4, %a6, %u : i32
  affine.store %s4, %out[4] : memref<16xi32>
  %m = arith.muli %u, %u2 : i32
  affine.store %m, %out[5] : memref<16xi32>
  %an = arith.andi %u, %u2 : i32
  affine.store %an, %out[6] : memref<16xi32>
  %xo = arith.xori %u, %u2 : i32
  affine.store %xo, %out[7] : memref<16xi32>
  %o = arith.ori %u, %u2 : i32
  affine.store %o, %out[8] : memref<16xi32>
  %a7 = affine.load %in[7] : memref<16xi32>
  %r = arith.remui %a7, %u : i32
  affine.store %r, %uout[0] : memref<4xi32>
  %a8 = affine.load %in[8] : memref<16xi32>
  %m31 = arith.andi %u, %c31 : i32
  %s9 = arith.shrsi %a8, %m31 : i32
  affine.store %s9, %out[9] : memref<16xi32>
  return
}

// -----

// A select whose condition a compare of U decides takes the arm it picks:
// sgt is false, so `(u > y) ? u : y` stores y (the sge form above is U);
// through a pair of sign extensions the same: `(h >= v) ? v : h` with v = U
// is U, deleted. The pass's own rewrite leaves `select (cmpi a, b), a, b`
// without U a select (a max would lose the predicate); the T4 rule merges
// it into a max.
// CHECK-LABEL: func.func @select_by_compare
// CHECK: memref.store %arg1, %arg3[%c0]
// CHECK: %[[C:.*]] = arith.cmpi sgt, %arg1, %arg2 : i32
// CHECK: %[[S:.*]] = arith.select %[[C]], %arg1, %arg2 : i32
// CHECK: memref.store %[[S]], %arg3[%c1]
// CHECK-NOT: memref.store
// CHECK: return
// T4-LABEL: func.func @select_by_compare
// T4: arith.maxsi %arg1, %arg2 : i32
// NOCANON-LABEL: func.func @select_by_compare
// NOCANON: memref.store %arg1, %arg3[%{{.*}}]
// NOCANON: memref.store %{{.*}}, %arg3[%{{.*}}]
// NOCANON-NOT: memref.store
// NOCANON: return
func.func @select_by_compare(%x: i32, %y: i32, %b: i32, %out: memref<2xi32>, %h: i16, %out16: memref<1xi16>) {
  %c0 = arith.constant 0 : i32
  %c0_16 = arith.constant 0 : i16
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %u = arith.divsi %x, %c0 : i32
  %gt = arith.cmpi sgt, %u, %y : i32
  %s0 = arith.select %gt, %u, %y : i32
  memref.store %s0, %out[%i0] : memref<2xi32>
  %c = arith.cmpi sgt, %y, %b : i32
  %s1 = arith.select %c, %y, %b : i32
  memref.store %s1, %out[%i1] : memref<2xi32>
  %v = arith.divsi %h, %c0_16 : i16
  %ve = arith.extsi %v : i16 to i32
  %he = arith.extsi %h : i16 to i32
  %ge = arith.cmpi sge, %he, %ve : i32
  %s2 = arith.select %ge, %v, %h : i16
  memref.store %s2, %out16[%i0] : memref<1xi16>
  return
}

// -----

// Index and vector divisions by 0 keep the T4 rule (0); the rewrites are
// recorded in the module attribute `hls.vitis_fold` for --bram-debug.
// CHECK-LABEL: module attributes {hls.vitis_fold = {counts = {"store-deleted" = 1 : i64}
// CHECK-LABEL: func.func @index_and_record
// CHECK: memref.store %c0, %arg3[%c0]
// CHECK-NEXT: return
func.func @index_and_record(%x: i32, %n: index, %out: memref<1xi32>, %iout: memref<1xindex>) {
  %c0 = arith.constant 0 : i32
  %i0 = arith.constant 0 : index
  %u = arith.divsi %x, %c0 : i32
  memref.store %u, %out[%i0] : memref<1xi32>
  %d = arith.divui %n, %i0 : index
  memref.store %d, %iout[%i0] : memref<1xindex>
  return
}

// -----

// Unsigned slots: uout[1] x + y % 0u -> x and uout[3] x * (y % 0u) -> 0
// (remui by 0 is 0), uout[2] x + y / 0u -> U, deleted.
// CHECK-LABEL: func.func @unsigned_slots
// CHECK-DAG: %[[Z:.*]] = arith.constant 0 : i32
// CHECK: memref.store %arg0, %arg2[%c0]
// CHECK-NEXT: memref.store %[[Z]], %arg2[%c2]
// CHECK-NEXT: return
func.func @unsigned_slots(%x: i32, %y: i32, %uout: memref<3xi32>) {
  %c0 = arith.constant 0 : i32
  %i0 = arith.constant 0 : index
  %i1 = arith.constant 1 : index
  %i2 = arith.constant 2 : index
  %r = arith.remui %y, %c0 : i32
  %a = arith.addi %x, %r : i32
  memref.store %a, %uout[%i0] : memref<3xi32>
  %d = arith.divui %y, %c0 : i32
  %b = arith.addi %x, %d : i32
  memref.store %b, %uout[%i1] : memref<3xi32>
  %m = arith.muli %x, %r : i32
  memref.store %m, %uout[%i2] : memref<3xi32>
  return
}

// -----

// Known difference (N13): the C short sum `(short)((short)U + (short)x)`
// (out16[1]) is deleted by Vitis, which narrows the add before it folds U;
// here the extension of U is 0 and x is stored.
// CHECK-LABEL: func.func @narrowed_short_sum
// CHECK: %[[T:.*]] = arith.trunci %arg1 : i32 to i16
// CHECK: memref.store %[[T]], %arg2[%c0]
func.func @narrowed_short_sum(%x: i32, %y: i32, %out16: memref<1xi16>) {
  %c0 = arith.constant 0 : i32
  %i0 = arith.constant 0 : index
  %u = arith.divsi %x, %c0 : i32
  %ut = arith.trunci %u : i32 to i16
  %ue = arith.extsi %ut : i16 to i32
  %yt = arith.trunci %y : i32 to i16
  %ye = arith.extsi %yt : i16 to i32
  %s = arith.addi %ue, %ye : i32
  %st = arith.trunci %s : i32 to i16
  memref.store %st, %out16[%i0] : memref<1xi16>
  return
}

// -----

// A write through a memref whose base is not known storage (here an if
// result that may be the local) may write the local: the load after it is
// not forwarded and the output store stays.
// CHECK-LABEL: func.func @local_escape
// CHECK: affine.store %c5_i32, %{{.*}}[0]
// CHECK: %[[L:.*]] = affine.load %alloca[0]
// CHECK: affine.store %[[L]], %arg3[0]
func.func @local_escape(%x: i32, %c: i1, %other: memref<1xi32>, %out: memref<1xi32>) {
  %c0 = arith.constant 0 : i32
  %c5 = arith.constant 5 : i32
  %loc = memref.alloca() : memref<1xi32>
  %u = arith.divsi %x, %c0 : i32
  affine.store %u, %loc[0] : memref<1xi32>
  %v = scf.if %c -> (memref<1xi32>) {
    scf.yield %loc : memref<1xi32>
  } else {
    scf.yield %other : memref<1xi32>
  }
  affine.store %c5, %v[0] : memref<1xi32>
  %l = affine.load %loc[0] : memref<1xi32>
  affine.store %l, %out[0] : memref<1xi32>
  return
}
