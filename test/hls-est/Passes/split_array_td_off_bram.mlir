// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s --check-prefix=AUTO

// End to end with td=off, on the cgeist output of four Vitis kernels
// (~/hls-est-work/exp-src/partition, Vitis 2025.1 td=off totals in brackets,
// exp-notes/partition.md section 7):
//   @small  small_w32_n4  int A[4]                          -> registers [0]
//   @both   ci_both_n64   int B[64], both loops unrolled    -> registers [0]
//   @cc     ci2d_cc_64x8  int A[64][8], j unrolled in both  -> 8 x [64x32] @ 1 [8]
//   @varj   ci2d_64x8     int A[64][8], copy-in j pipelined -> one RAM_1WNR,
//                         7 copies of 512x32 at x18 = 14 [14]
// Total 22 = Vitis. The default (td=auto) pipeline splits @varj by port
// pressure instead (8 banks = 8) and keeps @both as one RAM (1): 17.

// REPORT: Total BRAM: 22
// AUTO: Total BRAM: 17

// CHECK:      A (alloca) @ {{.*}}
// CHECK-NEXT:   shape [4] x i32 (32 bits) = 4 words
// CHECK-NEXT:   status: registers -- registers (hls.registers): 4 element(s) <= complete-threshold 4: completely partitioned into registers {{.*}}
// CHECK:        ram type: none -- not selected: registers, no memory (no port limit in the schedule)
// CHECK:        bram: 0
// CHECK:      B (alloca) @ {{.*}}
// CHECK-NEXT:   shape [64] x i32 (32 bits) = 64 words
// CHECK-NEXT:   status: registers -- registers (hls.registers): every one of the 128 access(es) uses a constant index in every dimension: scalarised into registers {{.*}}
// CHECK:        bram: 0
// CHECK-COUNT-8: partition: complete factor=8 dim=2 source=constant-index (bank {{[0-7]}} of 8)
// CHECK:      A (alloca) @ {{.*}}
// CHECK-NEXT:   shape [64x8] x i32 (32 bits) = 512 words
// CHECK-NEXT:   status: counted
// CHECK-NEXT:   partition: none
// CHECK:        ram type: RAM_1WNR
// CHECK:        bram: 14
// CHECK:      Total BRAM: 22

module {
  func.func @small(%arg0: memref<4xi32>, %arg1: memref<4xi32>) {
    %c3_i32 = arith.constant 3 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<4xi32>
    affine.for %arg2 = 0 to 4 {
      %0 = affine.load %arg0[%arg2] : memref<4xi32>
      %1 = arith.addi %0, %c1_i32 : i32
      affine.store %1, %alloca[%arg2] : memref<4xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 4 {
      %0 = affine.load %alloca[%arg2] : memref<4xi32>
      %1 = arith.muli %0, %c3_i32 : i32
      affine.store %1, %arg1[%arg2] : memref<4xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func @both(%arg0: memref<64xi32>, %arg1: memref<64xi32>) {
    %c3_i32 = arith.constant 3 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "B"} : memref<64xi32>
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %arg0[%arg2] : memref<64xi32>
      %1 = arith.addi %0, %c1_i32 : i32
      affine.store %1, %alloca[%arg2] : memref<64xi32>
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %alloca[-%arg2 + 63] : memref<64xi32>
      %1 = arith.muli %0, %c3_i32 : i32
      affine.store %1, %arg1[%arg2] : memref<64xi32>
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    return
  }
  func.func @cc(%arg0: memref<64x8xi32>, %arg1: memref<64x8xi32>) {
    %c3_i32 = arith.constant 3 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<64x8xi32>
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 8 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<64x8xi32>
        %1 = arith.addi %0, %c1_i32 : i32
        affine.store %1, %alloca[%arg2, %arg3] : memref<64x8xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 8 {
        %0 = affine.load %alloca[%arg2, -%arg3 + 7] : memref<64x8xi32>
        %1 = arith.muli %0, %c3_i32 : i32
        affine.store %1, %arg1[%arg2, %arg3] : memref<64x8xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func @varj(%arg0: memref<64x8xi32>, %arg1: memref<64xi32>) {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<64x8xi32>
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 8 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<64x8xi32>
        %1 = arith.addi %0, %c1_i32 : i32
        affine.store %1, %alloca[%arg2, %arg3] : memref<64x8xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg2 = 0 to 64 {
      %0 = affine.for %arg3 = 0 to 8 iter_args(%arg4 = %c0_i32) -> (i32) {
        %1 = affine.load %alloca[%arg2, %arg3] : memref<64x8xi32>
        %2 = arith.addi %arg4, %1 : i32
        affine.yield %2 : i32
      }
      affine.store %0, %arg1[%arg2] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
