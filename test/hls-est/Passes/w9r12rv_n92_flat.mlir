// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s
// W9 round 12 review, kernel w9r12rv_n92_flat (Vitis 2025.1 td=off: 0): an
// unpartitioned `int X[64]`, `X[i] = 0; for a (pipelined) X[i] += val[a];
// C[i] = X[i] * 3;`. N92 holds for a whole array as for a bank: Vitis
// promotes X[i] and deletes X.
// CHECK: hls.registers: iteration-private element (VITIS_NOTES N92)
// CHECK: Total BRAM: 0

module {
  func.func @_Z3topPiS_S_(%arg0: memref<65xi32>, %arg1: memref<1024xi32>, %arg2: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1 = arith.constant 1 : index
    %c3_i32 = arith.constant 3 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "X"} : memref<64xi32>
    affine.for %arg3 = 0 to 64 {
      affine.store %c0_i32, %alloca[%arg3] : memref<64xi32>
      %0 = affine.load %arg0[%arg3] : memref<65xi32>
      %1 = affine.load %arg0[%arg3 + 1] : memref<65xi32>
      %2 = arith.index_cast %1 : i32 to index
      %3 = arith.index_cast %0 : i32 to index
      %4 = scf.for %arg4 = %3 to %2 step %c1 iter_args(%arg5 = %c0_i32) -> (i32) {
        %7 = memref.load %arg1[%arg4] : memref<1024xi32>
        %8 = arith.addi %arg5, %7 : i32
        affine.store %8, %alloca[%arg3] : memref<64xi32>
        scf.yield %8 : i32
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      %5 = affine.load %alloca[%arg3] : memref<64xi32>
      %6 = arith.muli %5, %c3_i32 : i32
      affine.store %6, %arg2[%arg3] : memref<64xi32>
    }
    return
  }
}
