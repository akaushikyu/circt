// RUN: hls-est %s --symbol-privatize=exclude=_Z6rv_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rv_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r10 review fix D6 (2026-10-21): OPEN_ISSUES O111 (b) with Vitis evidence: an int max recurrence over 16 reads per iteration of a pipelined loop.
// arith.maxsi is combinational, so the loop is pipelined at II 1 and the array is replicated (before O111 (b): sequential loop, 8).
// Kernel w9r10rv_rv_max16 (~/hls-est-work/exp-src/w9r10rv/rv_max16.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: 120 BRAM_18K, II 1.
// CHECK: Total BRAM: 120{{$}}

module {
  func.func @_Z6rv_topPKiPi(%arg0: memref<4096xi32>, %arg1: memref<256xi32>) -> i32 attributes {hls.orig_name = "rv_top", llvm.linkage = #llvm.linkage<external>} {
    %c-2147483647_i32 = arith.constant -2147483647 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<256x16xi32>
    affine.for %arg2 = 0 to 256 {
      affine.for %arg3 = 0 to 16 {
        %1 = affine.load %arg0[%arg3 + %arg2 * 16] : memref<4096xi32>
        affine.store %1, %alloca[%arg2, %arg3] : memref<256x16xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %0 = affine.for %arg2 = 0 to 256 iter_args(%arg3 = %c0_i32) -> (i32) {
      %1 = affine.for %arg4 = 0 to 16 iter_args(%arg5 = %c-2147483647_i32) -> (i32) {
        %4 = affine.load %alloca[%arg2, %arg4] : memref<256x16xi32>
        %5 = arith.cmpi sgt, %4, %arg5 : i32
        %6 = arith.select %5, %4, %arg5 : i32
        affine.yield %6 : i32
      }
      affine.store %1, %arg1[%arg2] : memref<256xi32>
      %2 = arith.cmpi slt, %arg3, %1 : i32
      %3 = arith.select %2, %1, %arg3 : i32
      affine.yield %3 : i32
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return %0 : i32
  }
}
