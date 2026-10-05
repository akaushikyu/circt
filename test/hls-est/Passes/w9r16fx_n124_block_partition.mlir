// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N124 (W9r16 review fixes), kernel w9r16rv_ie_blk (Vitis 2025.1 td=off: 40):
// w9r16p_ie_part with A[4096] block-partitioned (factor 2) instead of cyclic. The bank is
// still chosen at run time, but Vitis speculates the arm loads of a block partition: all 6
// reads count, RAM_1WNR 5 copies per bank. Only cyclic partitions are marked
// hls.runtime_bank, so exclusive_steered_reads_share_slot does not apply (it gave 24).
// CHECK: Total BRAM: 40

module {
  func.func @_Z3topPiS_S_S_(%arg0: memref<4096xi32>, %arg1: memref<512xi32>, %arg2: memref<512xi32>, %arg3: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c401_i32 = arith.constant 401 : i32
    %c300_i32 = arith.constant 300 : i32
    %c-5_i32 = arith.constant -5 : i32
    %c201_i32 = arith.constant 201 : i32
    %c100_i32 = arith.constant 100 : i32
    %c7_i32 = arith.constant 7 : i32
    %c4095_i32 = arith.constant 4095 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "block", variable = "A"}], hls.preserve, polygeist.varname = "A"} : memref<4096xi32>
    affine.for %arg4 = 0 to 4096 {
      %0 = affine.load %arg0[%arg4] : memref<4096xi32>
      affine.store %0, %alloca[%arg4] : memref<4096xi32>
    }
    affine.for %arg4 = 0 to 512 {
      %0 = affine.load %arg1[%arg4] : memref<512xi32>
      %1 = arith.andi %0, %c4095_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %3 = memref.load %alloca[%2] : memref<4096xi32>
      %4 = arith.addi %1, %c7_i32 : i32
      %5 = arith.andi %4, %c4095_i32 : i32
      %6 = arith.index_cast %5 : i32 to index
      %7 = memref.load %alloca[%6] : memref<4096xi32>
      %8 = arith.addi %3, %7 : i32
      %9 = affine.load %arg2[%arg4] : memref<512xi32>
      %10 = arith.cmpi sgt, %9, %c0_i32 : i32
      %11 = scf.if %10 -> (i32) {
        %12 = arith.addi %1, %c100_i32 : i32
        %13 = arith.andi %12, %c4095_i32 : i32
        %14 = arith.index_cast %13 : i32 to index
        %15 = memref.load %alloca[%14] : memref<4096xi32>
        %16 = arith.addi %1, %c201_i32 : i32
        %17 = arith.andi %16, %c4095_i32 : i32
        %18 = arith.index_cast %17 : i32 to index
        %19 = memref.load %alloca[%18] : memref<4096xi32>
        %20 = arith.muli %15, %19 : i32
        %21 = arith.addi %8, %20 : i32
        scf.yield %21 : i32
      } else {
        %12 = arith.cmpi slt, %9, %c-5_i32 : i32
        %13 = scf.if %12 -> (i32) {
          %14 = arith.addi %1, %c300_i32 : i32
          %15 = arith.andi %14, %c4095_i32 : i32
          %16 = arith.index_cast %15 : i32 to index
          %17 = memref.load %alloca[%16] : memref<4096xi32>
          %18 = arith.addi %1, %c401_i32 : i32
          %19 = arith.andi %18, %c4095_i32 : i32
          %20 = arith.index_cast %19 : i32 to index
          %21 = memref.load %alloca[%20] : memref<4096xi32>
          %22 = arith.muli %17, %21 : i32
          %23 = arith.subi %8, %22 : i32
          scf.yield %23 : i32
        } else {
          scf.yield %8 : i32
        }
        scf.yield %13 : i32
      }
      affine.store %11, %arg3[%arg4] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
