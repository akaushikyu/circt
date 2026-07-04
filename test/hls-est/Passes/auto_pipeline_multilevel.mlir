// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// VITIS_NOTES.md N3 / pipeline_unroll.md R2 step 2 (pu_red3c_l4_m4_n4): the
// product of the trip counts is taken along every nesting path inside the
// candidate; 4 x 4 = 16 <= 64 under i, so i is pipelined and BOTH j and k are
// completely unrolled (two levels; pipeline_unroll_chk_4lvl: three).

// CHECK-LABEL: func.func @nest4x4x4
// CHECK:       affine.for %{{.*}} = 0 to 4 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @nest4x4x4(%a: memref<4x4x4xi32>, %b: memref<4xi32>, %c: memref<4xi32>) {
  %c5_i32 = arith.constant 5 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<4x4xi32>
  %lo2 = memref.alloca() {hls.preserve, polygeist.varname = "lo2"} : memref<4xi32>
  %lc = memref.alloca() {hls.preserve, polygeist.varname = "lc"} : memref<4xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<4xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<4x4x4xi32>
  affine.for %i = 0 to 4 {
    %0 = affine.load %lc[%i] : memref<4xi32>
    %1 = arith.muli %0, %c5_i32 : i32
    affine.store %1, %lo2[%i] : memref<4xi32>
    affine.for %j = 0 to 4 {
      %2 = affine.load %lc[%j] : memref<4xi32>
      %3 = affine.for %k = 0 to 4 iter_args(%s = %2) -> (i32) {
        %4 = affine.load %la[%i, %j, %k] : memref<4x4x4xi32>
        %5 = affine.load %lb[%k] : memref<4xi32>
        %6 = arith.muli %4, %5 : i32
        %7 = arith.addi %s, %6 : i32
        affine.yield %7 : i32
      }
      affine.store %3, %lo[%i, %j] : memref<4x4xi32>
    }
  }
  return
}

// An imperfect i over a perfect (j, k) sub-nest: the sub-nest counts as its
// product. 4 x 16 = 64 -> both unrolled, i pipelined (pu_red3b_l4_m4_n16);
// 4 x 17 = 68 -> nothing unrolled, k pipelined, j and i flattened onto it
// (pu_red3b_l4_m4_n17).
// CHECK-LABEL: func.func @red3b_64
// CHECK:       affine.for %{{.*}} = 0 to 4 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @red3b_64(%a: memref<4x4x16xi32>, %b: memref<16xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<4xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<16xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<4x4x16xi32>
  affine.for %i = 0 to 4 {
    %0 = affine.for %j = 0 to 4 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.for %k = 0 to 16 iter_args(%t = %s) -> (i32) {
        %2 = affine.load %la[%i, %j, %k] : memref<4x4x16xi32>
        %3 = affine.load %lb[%k] : memref<16xi32>
        %4 = arith.muli %2, %3 : i32
        %5 = arith.addi %t, %4 : i32
        affine.yield %5 : i32
      }
      affine.yield %1 : i32
    }
    affine.store %0, %lo[%i] : memref<4xi32>
  }
  return
}

// CHECK-LABEL: func.func @red3b_68
// CHECK:       affine.for %{{.*}} = 0 to 4 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 4 iter_args
// CHECK-NEXT:      affine.for %{{.*}} = 0 to 17 iter_args
// CHECK:           } {hls.flattened_parents = 2 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:      affine.yield
// CHECK-NEXT:    {{^ *}$}}
// CHECK-NEXT:    affine.store
// CHECK-NEXT:  {{^ *}$}}
func.func @red3b_68(%a: memref<4x4x17xi32>, %b: memref<17xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<4xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<17xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<4x4x17xi32>
  affine.for %i = 0 to 4 {
    %0 = affine.for %j = 0 to 4 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.for %k = 0 to 17 iter_args(%t = %s) -> (i32) {
        %2 = affine.load %la[%i, %j, %k] : memref<4x4x17xi32>
        %3 = affine.load %lb[%k] : memref<17xi32>
        %4 = arith.muli %2, %3 : i32
        %5 = arith.addi %t, %4 : i32
        affine.yield %5 : i32
      }
      affine.yield %1 : i32
    }
    affine.store %0, %lo[%i] : memref<4xi32>
  }
  return
}
