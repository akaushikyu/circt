// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// VITIS_NOTES.md N3 / pipeline_unroll.md R2 step 1: a perfect nest is ONE
// loop for the decision (trip = product) and is never unrolled, whatever its
// size (pu_st_m64_n64: 64x64 -> one flattened 4096-trip pipeline, no unroll).
// Perfectness is judged after LICM / scalar promotion: register-only code in
// the outer body keeps the nest perfect (pipeline_unroll_chk_scalarmid), a
// load hoisted out of the inner loop does not (pu_st_hoist_m8_n16: j unrolled
// 16, i pipelined).

// CHECK-LABEL: func.func @perfect64x64
// CHECK:       affine.for %{{.*}} = 0 to 64 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 64 {
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:  {{^ *}$}}
func.func @perfect64x64(%a: memref<64x64xi32>, %out: memref<64x64xi32>) {
  %c2_i32 = arith.constant 2 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<64x64xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<64x64xi32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %la[%i, %j] : memref<64x64xi32>
      %1 = arith.muli %0, %c2_i32 : i32
      affine.store %1, %lo[%i, %j] : memref<64x64xi32>
    }
  }
  return
}

// Register-only code around the inner loop (a second accumulator consuming
// the inner reduction): still perfect -> inner pipelined, outer flattened.
// CHECK-LABEL: func.func @scalarmid
// CHECK:       affine.for %{{.*}} = 0 to 8 iter_args
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 16 iter_args
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @scalarmid(%a: memref<8x16xi32>, %b: memref<16xi32>, %out: memref<1xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %c1_i32 = arith.constant 1 : i32
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<16xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xi32>
  %acc = affine.for %i = 0 to 8 iter_args(%accv = %c0_i32) -> (i32) {
    %0 = affine.for %j = 0 to 16 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x16xi32>
      %2 = affine.load %lb[%j] : memref<16xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    }
    %5 = arith.index_cast %i : index to i32
    %6 = arith.addi %5, %c1_i32 : i32
    %7 = arith.muli %0, %6 : i32
    %8 = arith.addi %accv, %7 : i32
    affine.yield %8 : i32
  }
  affine.store %acc, %out[0] : memref<1xi32>
  return
}

// A j-invariant load inside the inner loop: Vitis' LICM hoists it into the
// outer body, the nest is imperfect, j (16) is unrolled, i pipelined.
// CHECK-LABEL: func.func @hoisted_load
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @hoisted_load(%a: memref<8x16xi32>, %b: memref<8xi32>, %out: memref<8x16xi32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x16xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xi32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 16 {
      %0 = affine.load %la[%i, %j] : memref<8x16xi32>
      %1 = affine.load %lb[%i] : memref<8xi32>
      %2 = arith.muli %0, %1 : i32
      affine.store %2, %lo[%i, %j] : memref<8x16xi32>
    }
  }
  return
}
