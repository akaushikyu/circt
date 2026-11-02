// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// VITIS_NOTES.md N3 / pipeline_unroll.md R2 step 3 (pu_red_m8_n65): an
// imperfect nest whose inner loop has 65 > 64 trips. The inner loop is
// pipelined itself (nothing is unrolled) and Vitis converts the parent into a
// perfect nest and flattens it into the pipeline ("[HLS 200-2061] converted
// nested loops ... into perfectly nested loops", "[XFORM 203-541] Flattening a
// loop nest 'i'"): one 520-trip pipelined loop. The parent is NOT tagged; the
// inner loop carries hls.flattened_parents = 1 so that later passes treat i
// as loop-variant for that pipeline.

// CHECK-LABEL: func.func @reduce65
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 65 iter_args
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:    affine.store
// CHECK-NEXT:  {{^ *}$}}
func.func @reduce65(%a: memref<8x65xi32>, %b: memref<65xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<65xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x65xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 65 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x65xi32>
      %2 = affine.load %lb[%j] : memref<65xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    }
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  return
}

// Three levels, product under j = 4 x 17 = 68 > 64 (pu_red3c_l4_m4_n17):
// k is unrolled (17), j is pipelined, i is converted + flattened onto j.
// CHECK-LABEL: func.func @red3c
// CHECK:       affine.for %{{.*}} = 0 to 4 {
// CHECK:         affine.for %{{.*}} = 0 to 4 {
// CHECK-NOT:       affine.for
// CHECK:         } {hls.auto_unrolled = [{factor = 17 : i64, loc = #loc{{[0-9]*}}}], hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:  {{^ *}$}}
func.func @red3c(%a: memref<4x4x17xi32>, %b: memref<17xi32>, %c: memref<4xi32>) {
  %c5_i32 = arith.constant 5 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<4x4xi32>
  %lo2 = memref.alloca() {hls.preserve, polygeist.varname = "lo2"} : memref<4xi32>
  %lc = memref.alloca() {hls.preserve, polygeist.varname = "lc"} : memref<4xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<17xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<4x4x17xi32>
  affine.for %i = 0 to 4 {
    %0 = affine.load %lc[%i] : memref<4xi32>
    %1 = arith.muli %0, %c5_i32 : i32
    affine.store %1, %lo2[%i] : memref<4xi32>
    affine.for %j = 0 to 4 {
      %2 = affine.load %lc[%j] : memref<4xi32>
      %3 = affine.for %k = 0 to 17 iter_args(%s = %2) -> (i32) {
        %4 = affine.load %la[%i, %j, %k] : memref<4x4x17xi32>
        %5 = affine.load %lb[%k] : memref<17xi32>
        %6 = arith.muli %4, %5 : i32
        %7 = arith.addi %s, %6 : i32
        affine.yield %7 : i32
      }
      affine.store %3, %lo[%i, %j] : memref<4x4xi32>
    }
  }
  return
}
