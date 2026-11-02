// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// VITIS_NOTES.md N3 / pipeline_unroll.md R1-R2 (pu_red_m8_n16, pu_memred_m8_n16):
// an imperfect nest whose inner loop has <= 64 trips: the inner loop is
// completely unrolled and the parent is pipelined ("automatically set the
// pipeline for Loop<i>", "complete unroll implied by the pipeline pragma").
//
// @reduce: i(8) { s = 0; j(16) { s += la[i][j] * lb[j] }; lo[i] = s }
// @promote: i(8) { j(16) { lo[i] += la[i][j] * lb[j] } } - Vitis promotes
// lo[i] to a register across the j loop (LLVM LICM scalar promotion), which
// makes the nest imperfect (pu_memred_m8_n16: j unrolled, i pipelined); the
// pipelined body then holds ONE load and ONE store of lo[i], not 16 of each.

// CHECK-LABEL: func.func @reduce
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @reduce(%a: memref<8x16xi32>, %b: memref<16xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<16xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 16 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x16xi32>
      %2 = affine.load %lb[%j] : memref<16xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    }
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  affine.for %i = 0 to 8 {
    %0 = affine.load %lo[%i] : memref<8xi32>
    affine.store %0, %out[%i] : memref<8xi32>
  }
  return
}

// CHECK-LABEL: func.func @promote
// CHECK:       %[[LO:.*]] = memref.alloca() {{.*}}"lo"
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.load %[[LO]][
// CHECK-NOT:     affine.for
// CHECK-NOT:     affine.load %[[LO]][
// CHECK:         affine.store %{{.*}}, %[[LO]][
// CHECK-NEXT:  } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @promote(%a: memref<8x16xi32>, %b: memref<16xi32>, %out: memref<8xi32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<16xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xi32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 16 {
      %0 = affine.load %la[%i, %j] : memref<8x16xi32>
      %1 = affine.load %lb[%j] : memref<16xi32>
      %2 = arith.muli %0, %1 : i32
      %3 = affine.load %lo[%i] : memref<8xi32>
      %4 = arith.addi %3, %2 : i32
      affine.store %4, %lo[%i] : memref<8xi32>
    }
  }
  affine.for %i = 0 to 8 {
    %0 = affine.load %lo[%i] : memref<8xi32>
    affine.store %0, %out[%i] : memref<8xi32>
  }
  return
}
