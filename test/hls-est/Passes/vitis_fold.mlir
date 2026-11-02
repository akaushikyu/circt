// RUN: hls-est %s --vitis-fold=undef=false | FileCheck %s
// RUN: hls-est %s --vitis-fold='undef=false canonicalize=false' | FileCheck %s --check-prefix=NOCANON
// RUN: hls-est %s --vitis-fold | FileCheck %s --check-prefix=UNDEF

// --vitis-fold=undef=false (the T4 rule): integer division / remainder by a
// constant zero -> 0 (VITIS_NOTES.md N1a "Division by a constant 0"). Vitis
// gives 0 for an ap_fixed division (dg_d_fold_steps a.o.1.ll:50 `in + 1.0/0`
// -> `in`; dg_d_fold_divrem0b) and an unsigned remainder (dg_d_fold_divrem0),
// and undef for a C int division / signed remainder, of which 0 is a
// refinement. MLIR keeps x/0 (undefined behaviour), so the chain never folds
// without it. The default (`undef`, N13, vitis_fold_undef.mlir) models the
// undefined value: here the stores of x/0, x/0u, x%0 and of the C int sum
// x + 2048/0 are deleted (dg_d_fold_divrem0), x%0u is 0 and x * (2048/0) is 0.

// UNDEF-LABEL: func.func @int_div_by_zero
// UNDEF-DAG: %[[Z:.*]] = arith.constant 0 : i32
// UNDEF-NOT: arith.divsi
// UNDEF: memref.store %[[Z]], %arg1[%c3]
// UNDEF-NEXT: memref.store %[[Z]], %arg1[%c5]
// UNDEF-NEXT: return

// CHECK-LABEL: func.func @int_div_by_zero
// CHECK-NOT: arith.divsi
// CHECK-NOT: arith.divui
// CHECK-NOT: arith.remsi
// CHECK-NOT: arith.remui
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
  %q = arith.divsi %c2048, %c0 : i32
  %e = arith.addi %x, %q : i32
  memref.store %e, %out[%c4i] : memref<8xi32>
  // in * (1/0) -> 0 (the attention `scores *= scale` step)
  %s = arith.divsi %c2048, %c0 : i32
  %f = arith.muli %x, %s : i32
  memref.store %f, %out[%c5i] : memref<8xi32>
  return
}

// A non-zero divisor and floating point are left alone: IEEE x * 0.0 is not 0
// for NaN / inf, and float x / 0.0 is inf, not 0. ceildivsi / floordivsi by 0
// are not folded either: no C expression produces them (affine maps divide by
// positive constants), so there is no Vitis behaviour to match.
// CHECK-LABEL: func.func @not_folded
// CHECK: arith.divsi %arg0, %{{.*}} : i32
// CHECK: arith.floordivsi
// CHECK: arith.ceildivsi
// CHECK: arith.divf
// CHECK: arith.mulf
// CHECK: return
func.func @not_folded(%x: i32, %y: f32, %out: memref<3xi32>, %fout: memref<2xf32>) {
  %c3 = arith.constant 3 : i32
  %c0 = arith.constant 0 : i32
  %f0 = arith.constant 0.0 : f32
  %c0i = arith.constant 0 : index
  %c1i = arith.constant 1 : index
  %c2i = arith.constant 2 : index
  %a = arith.divsi %x, %c3 : i32
  memref.store %a, %out[%c0i] : memref<3xi32>
  %g = arith.floordivsi %x, %c0 : i32
  memref.store %g, %out[%c1i] : memref<3xi32>
  %h = arith.ceildivsi %x, %c0 : i32
  memref.store %h, %out[%c2i] : memref<3xi32>
  %b = arith.divf %y, %f0 : f32
  memref.store %b, %fout[%c0i] : memref<2xf32>
  %c = arith.mulf %y, %f0 : f32
  memref.store %c, %fout[%c1i] : memref<2xf32>
  return
}
