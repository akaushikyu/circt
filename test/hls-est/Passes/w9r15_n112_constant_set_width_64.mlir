// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPtiPh --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N112, kernel w9r15p_wc_64 (Vitis 2025.1 td=off: 4): the set {0, 64}
// keeps 7 bits (64 in 7 bits is -64 signed): 8192 x 7 = 4 BRAM.
// CHECK: Total BRAM: 4

module {
  func.func @_Z3topPtiPh(%arg0: memref<1024xi16>, %arg1: i32, %arg2: memref<8192xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c64_i8 = arith.constant 64 : i8
    %c8191_i32 = arith.constant 8191 : i32
    %c0_i8 = arith.constant 0 : i8
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "fb"} : memref<8192xi8>
    affine.for %arg3 = 0 to 8192 {
      affine.store %c0_i8, %alloca[%arg3] : memref<8192xi8>
    }
    %0 = arith.index_cast %arg1 : i32 to index
    affine.for %arg3 = 0 to %0 {
      %1 = affine.load %arg0[%arg3] : memref<1024xi16>
      %2 = arith.extui %1 : i16 to i32
      %3 = arith.andi %2, %c8191_i32 : i32
      %4 = arith.index_cast %3 : i32 to index
      memref.store %c64_i8, %alloca[%4] : memref<8192xi8>
    } {hls.loop_tripcount = [{avg = 512 : i32, max = 1024 : i32, min = 0 : i32}]}
    affine.for %arg3 = 0 to 8192 {
      %1 = affine.load %alloca[%arg3] : memref<8192xi8>
      affine.store %1, %arg2[%arg3] : memref<8192xi8>
    }
    return
  }
}
