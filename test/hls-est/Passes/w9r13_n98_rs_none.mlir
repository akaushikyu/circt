// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s

// VITIS_NOTES N98, control kernel w9r13p_rs_none (Vitis 2025.1 td=off:
// RAM_AUTO_1R1W, 0): rs_bind without the pragma is LUTRAM (N5).
// CHECK: Total BRAM: 0

module {
  func.func @_Z3topPK6ap_intILi16EEPS0_(%arg0: memref<64xi16>, %arg1: memref<64xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c15_i32 = arith.constant 15 : i32
    %c5_i32 = arith.constant 5 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<16xi16>
    affine.for %arg2 = 0 to 16 {
      %0 = affine.load %arg0[%arg2] : memref<64xi16>
      affine.store %0, %alloca[%arg2] : memref<16xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 64 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = arith.muli %0, %c5_i32 : i32
      %2 = arith.andi %1, %c15_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      %4 = memref.load %alloca[%3] : memref<16xi16>
      %5 = affine.load %arg0[%arg2] : memref<64xi16>
      %6 = arith.extsi %4 : i16 to i32
      %7 = arith.extsi %5 : i16 to i32
      %8 = arith.addi %6, %7 : i32
      %9 = arith.trunci %8 : i32 to i16
      affine.store %9, %arg1[%arg2] : memref<64xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
