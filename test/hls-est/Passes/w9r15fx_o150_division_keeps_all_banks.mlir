// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_iPA64_i --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --memory-banking-bram | FileCheck %s

// W9 round 15 review, finding 5 (kernel ob_fdiv_aff): reachableCandidates
// (tool.hls.partitioning.reachable_store_banks, OPEN_ISSUES O150) evaluates an
// index over one power-of-two period of its operands, which shows only its
// low bits. a[i][j floordiv 2] with j in [0, 128) and a's dim 2 complete (64
// banks) reaches every bank, but one period of j (64 values) reaches only
// banks 0..31: the first version gave banks 32..63 no store. An index with a
// division (or a mod by a non-power of two) now keeps every candidate: 64
// store_enables, one per bank.
// CHECK-COUNT-64: hls.affine.store_enable
// CHECK-NOT: hls.affine.store_enable

module {
  func.func @_Z3topPA128_iPA64_i(%arg0: memref<64x128xi32>, %arg1: memref<64x64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1 = arith.constant -1 : index
    %c2 = arith.constant 2 : index
    %c0 = arith.constant 0 : index
    %alloca = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "a"}], hls.preserve, polygeist.varname = "a"} : memref<64x64xi32>
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 128 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<64x128xi32>
        %1 = arith.cmpi slt, %arg3, %c0 : index
        %2 = arith.subi %c-1, %arg3 : index
        %3 = arith.select %1, %2, %arg3 : index
        %4 = arith.divsi %3, %c2 : index
        %5 = arith.subi %c-1, %4 : index
        %6 = arith.select %1, %5, %4 : index
        affine.store %0, %alloca[%arg2, %arg3 floordiv 2] : memref<64x64xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 64 {
        %0 = affine.load %alloca[%arg2, %arg3] : memref<64x64xi32>
        affine.store %0, %arg1[%arg2, %arg3] : memref<64x64xi32>
      }
    }
    return
  }
}
