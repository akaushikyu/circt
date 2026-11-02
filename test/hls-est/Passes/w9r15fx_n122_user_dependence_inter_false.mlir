// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.dependences.user_inter_independence=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N122, kernel w9r15rev_rmw_dep (Vitis 2025.1 td=off: 2): h[in[i]]++
// in a loop with `#pragma HLS pipeline II=1` and `#pragma HLS dependence
// variable=h inter false`. Vitis drops the carried read-after-write of h:
// VITIS_LOOP_10_3 at II 1, h ram_2p (RAM_AUTO_1R1W) 2 BRAM_18K. The pragma
// (hls.dependence on the loop) removes h's recurrence, N117's II floor
// included (scheduling.dependences.user_inter_independence): II 1, RAM_2P 2.
// Off run: the pragma is ignored, N117 gives II 2 and RAM_1P 1 (the
// W9r15-impl result the review found).
// CHECK: RAM_2P
// CHECK: Total BRAM: 2
// OFF: RAM_1P
// OFF: Total BRAM: 1

module {
  func.func @_Z3topPKhPi(%arg0: memref<4096xi8>, %arg1: memref<256xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "h"} : memref<256xi32>
    affine.for %arg2 = 0 to 256 {
      affine.store %c0_i32, %alloca[%arg2] : memref<256xi32>
    }
    affine.for %arg2 = 0 to 4096 {
      %0 = affine.load %arg0[%arg2] : memref<4096xi8>
      %1 = arith.index_castui %0 : i8 to index
      %2 = memref.load %alloca[%1] : memref<256xi32>
      %3 = arith.addi %2, %c1_i32 : i32
      memref.store %3, %alloca[%1] : memref<256xi32>
    } {hls.dependence = [{dependent = false, type = "inter", variable = "h"}], hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 256 {
      %0 = affine.load %alloca[%arg2] : memref<256xi32>
      affine.store %0, %arg1[%arg2] : memref<256xi32>
    }
    return
  }
}
