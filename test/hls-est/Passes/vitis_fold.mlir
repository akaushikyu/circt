// RUN: hls-est %s --vitis-fold | FileCheck %s
// RUN: hls-est %s --vitis-fold=canonicalize=false | FileCheck %s --check-prefix=NOCANON

// --vitis-fold: Vitis HLS folds an integer (or ap_fixed, an integer in its IR)
// division or remainder by a constant zero to 0 in every arithmetic use
// (VITIS_NOTES.md N1a, dg_d_fold_steps a.o.1.ll:50: `in + 1.0/0` -> `in`).
// MLIR keeps x/0 (undefined behaviour), so the chain never folds without it.

// CHECK-LABEL: func.func @int_div_by_zero
// CHECK-NOT: arith.divsi
// CHECK-NOT: arith.divui
// CHECK-NOT: arith.remsi
// CHECK-NOT: arith.remui
// CHECK-NOT: arith.floordivsi
// CHECK-NOT: arith.ceildivsi
// CHECK-NOT: arith.muli
// CHECK: %[[Z:.*]] = arith.constant 0 : i32
// CHECK: memref.store %[[Z]]
// CHECK: memref.store %[[Z]]
// CHECK: memref.store %[[Z]]
// CHECK: memref.store %[[Z]]
// CHECK: memref.store %arg0
// CHECK: memref.store %[[Z]]
// CHECK: return
// NOCANON-LABEL: func.func @int_div_by_zero
// NOCANON-NOT: arith.divsi
// NOCANON: arith.addi %arg0, %{{.*}} : i32
// NOCANON: arith.muli %arg0, %{{.*}} : i32
func.func @int_div_by_zero(%x: i32, %out: memref<8xi32>) {
  %c0 = arith.constant 0 : i32
  %c2048 = arith.constant 2048 : i32
  %c0i = arith.constant 0 : index
  %c1i = arith.constant 1 : index
  %c2i = arith.constant 2 : index
  %c3i = arith.constant 3 : index
  %c4i = arith.constant 4 : index
  %c5i = arith.constant 5 : index
  %a = arith.divsi %c2048, %c0 : i32
  memref.store %a, %out[%c0i] : memref<8xi32>
  %b = arith.divui %x, %c0 : i32
  memref.store %b, %out[%c1i] : memref<8xi32>
  %c = arith.remsi %x, %c0 : i32
  memref.store %c, %out[%c2i] : memref<8xi32>
  %d = arith.remui %x, %c0 : i32
  memref.store %d, %out[%c3i] : memref<8xi32>
  // in + 1/0 -> in
  %q = arith.floordivsi %c2048, %c0 : i32
  %e = arith.addi %x, %q : i32
  memref.store %e, %out[%c4i] : memref<8xi32>
  // in * (1/0) -> 0 (the attention `scores *= scale` step)
  %s = arith.ceildivsi %c2048, %c0 : i32
  %f = arith.muli %x, %s : i32
  memref.store %f, %out[%c5i] : memref<8xi32>
  return
}

// A non-zero divisor and floating point are left alone: IEEE x * 0.0 is not 0
// for NaN / inf, and float x / 0.0 is inf, not 0.
// CHECK-LABEL: func.func @not_folded
// CHECK: arith.divsi %arg0, %{{.*}} : i32
// CHECK: arith.divf
// CHECK: arith.mulf
// CHECK: return
func.func @not_folded(%x: i32, %y: f32, %out: memref<3xi32>, %fout: memref<2xf32>) {
  %c3 = arith.constant 3 : i32
  %f0 = arith.constant 0.0 : f32
  %c0i = arith.constant 0 : index
  %c1i = arith.constant 1 : index
  %a = arith.divsi %x, %c3 : i32
  memref.store %a, %out[%c0i] : memref<3xi32>
  %b = arith.divf %y, %f0 : f32
  memref.store %b, %fout[%c0i] : memref<2xf32>
  %c = arith.mulf %y, %f0 : f32
  memref.store %c, %fout[%c1i] : memref<2xf32>
  return
}
