// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s

// VITIS_NOTES N92, kernel w9r12p_rp_base (Vitis 2025.1 td=off): `short X[64][64]`
// completely partitioned on dim 2; every access of a bank X_j lies in the i
// body at address [i] (init store first, a pipelined read-modify-write,
// a pipelined copy-out). Vitis keeps no X: each bank is promoted to a
// scalar per i iteration. hls-est: the 64 banks are hls.registers.
// CHECK-COUNT-64: hls.registers: iteration-private element (VITIS_NOTES N92)
// CHECK: Total BRAM: 0

module {
  func.func @_Z3topPiS_PsPA64_s(%arg0: memref<65xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi16>, %arg3: memref<64x64xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1 = arith.constant 1 : index
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "X"}], hls.preserve, polygeist.varname = "X"} : memref<64x64xi16>
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 64 {
        affine.store %c0_i16, %alloca[%arg4, %arg5] : memref<64x64xi16>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %0 = affine.load %arg0[%arg4] : memref<65xi32>
      %1 = affine.load %arg0[%arg4 + 1] : memref<65xi32>
      %2 = arith.index_cast %1 : i32 to index
      %3 = arith.index_cast %0 : i32 to index
      scf.for %arg5 = %3 to %2 step %c1 {
        %4 = memref.load %arg1[%arg5] : memref<1024xi32>
        %5 = arith.index_cast %4 : i32 to index
        %6 = memref.load %arg2[%arg5] : memref<1024xi16>
        %7 = memref.load %alloca[%arg4, %5] : memref<64x64xi16>
        %8 = arith.addi %7, %6 : i16
        memref.store %8, %alloca[%arg4, %5] : memref<64x64xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.for %arg5 = 0 to 64 {
        %4 = affine.load %alloca[%arg4, %arg5] : memref<64x64xi16>
        affine.store %4, %arg3[%arg4, %arg5] : memref<64x64xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
