// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --memory-banking-bram | FileCheck %s --check-prefix=IR
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: FileCheck %s --input-file=%t.err --check-prefix=RAM

// td=off rule (b) and memory banking must agree on what a constant index is
// (ConstantIndex.h). Each kernel copies int in[64][8] into A[64][8] with the
// column loop unrolled (8 constant columns), then reads two constant columns
// of every row in a pipelined loop at II 1:
//   @single_trip  column 3 through the counter of `for k = 3 to 4` (a loop
//                 that runs once; --affine-loop-normalize leaves it as
//                 `k = 0 to 1` and the index as `k + 3`), column 0 literal;
//   @index_cast   column 5 through `arith.index_cast` of an i32 constant in a
//                 memref.load, column 0 in an affine.load.
// Rule (b) splits dimension 2 into 8 banks of 64 words, and banking must send
// the "constant through a loop counter / a cast" read to its one bank. Before
// the fix it read all 8 banks and muxed them, so every bank saw two reads per
// cycle and bank 0 became RAM_T2P (2 BRAM): 9 per kernel instead of 8 (review
// reproducers e1_singletrip / e3_indexcast; the literal-index control
// e1b_literal gives 8).
//   @memref_only  the same shape reached only through memref.load /
//                 memref.store: banking never splits an array without an
//                 affine access, so rule (b) must not annotate it either; it
//                 stays one RAM (RAM_T2P, 2 BRAM) with no partition spec.
// Total 8 + 8 + 2 = 18 (20 before the fix).

// IR-LABEL: func.func @single_trip
// IR-COUNT-8: memref.alloca() {{.*}}source = "constant-index"{{.*}} : memref<64x1xi32>
// IR-NOT: arith.select
// IR-LABEL: func.func @index_cast
// IR-COUNT-8: memref.alloca() {{.*}}source = "constant-index"{{.*}} : memref<64x1xi32>
// IR-NOT: arith.select
// IR-LABEL: func.func @memref_only
// IR-NOT: hls.array_partition
// IR: memref.alloca() {{.*}}polygeist.varname = "A"} : memref<64x8xi32>
// IR-NOT: hls.array_partition
// IR: return

// REPORT: Total BRAM: 18

// CHECK:      [single_trip#{{[0-9]+}}] A[bank 0/8] (alloca)
// CHECK-COUNT-8: partition: complete factor=8 dim=2 source=constant-index (bank {{[0-7]}} of 8)
// CHECK:      [index_cast#{{[0-9]+}}] A[bank 0/8] (alloca)
// CHECK-COUNT-8: partition: complete factor=8 dim=2 source=constant-index (bank {{[0-7]}} of 8)
// CHECK:      [memref_only#{{[0-9]+}}] A (alloca) @ {{.*}}
// CHECK-NEXT:   shape [64x8] x i32 (32 bits) = 512 words
// CHECK-NEXT:   status: counted
// CHECK-NEXT:   partition: none
// CHECK:        bram: 2
// CHECK:      Total BRAM: 18

// RAM-NOT: RAM_T2P
// RAM-COUNT-16: ram type: RAM_1P
// RAM-NOT: RAM_T2P
// RAM: [memref_only
// RAM: ram type: RAM_T2P

module {
  func.func @single_trip(%in: memref<64x8xi32>, %out: memref<64xi32>) {
    %A = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<64x8xi32>
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to 8 {
        %0 = affine.load %in[%i, %j] : memref<64x8xi32>
        affine.store %0, %A[%i, %j] : memref<64x8xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %k = 3 to 4 {
      affine.for %i = 0 to 64 {
        %0 = affine.load %A[%i, %k] : memref<64x8xi32>
        %1 = affine.load %A[%i, 0] : memref<64x8xi32>
        %2 = arith.addi %0, %1 : i32
        affine.store %2, %out[%i] : memref<64xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func @index_cast(%in: memref<64x8xi32>, %out: memref<64xi32>) {
    %c5_i32 = arith.constant 5 : i32
    %A = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<64x8xi32>
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to 8 {
        %0 = affine.load %in[%i, %j] : memref<64x8xi32>
        affine.store %0, %A[%i, %j] : memref<64x8xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %i = 0 to 64 {
      %idx = arith.index_cast %c5_i32 : i32 to index
      %a = memref.load %A[%i, %idx] : memref<64x8xi32>
      %b = affine.load %A[%i, 0] : memref<64x8xi32>
      %s = arith.addi %a, %b : i32
      affine.store %s, %out[%i] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func @memref_only(%in: memref<64x8xi32>, %out: memref<64xi32>) {
    %c0 = arith.constant 0 : index
    %c3 = arith.constant 3 : index
    %A = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<64x8xi32>
    affine.for %i = 0 to 64 {
      %v = memref.load %in[%i, %c0] : memref<64x8xi32>
      memref.store %v, %A[%i, %c0] : memref<64x8xi32>
      memref.store %v, %A[%i, %c3] : memref<64x8xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %i = 0 to 64 {
      %a = memref.load %A[%i, %c0] : memref<64x8xi32>
      %b = memref.load %A[%i, %c3] : memref<64x8xi32>
      %s = arith.addi %a, %b : i32
      memref.store %s, %out[%i] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
