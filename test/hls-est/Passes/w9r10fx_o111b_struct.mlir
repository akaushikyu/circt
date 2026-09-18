// RUN: hls-est %s --symbol-privatize=exclude=_Z6rv_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rv_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r10 review fix D6 (2026-10-21): OPEN_ISSUES O111 (b) with Vitis evidence: a struct min/max helper over 8 reads per iteration.
// llvm.insertvalue / extractvalue and integer min / max are combinational, so the loop is pipelined (before O111 (b): sequential, 4).
// Kernel w9r10rv_rv_struct (~/hls-est-work/exp-src/w9r10rv/rv_struct.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: 28 BRAM_18K.
// CHECK: Total BRAM: 28{{$}}

module {
  func.func @_Z6rv_topPKiPi(%arg0: memref<2048xi32>, %arg1: memref<256xi32>) -> i32 attributes {hls.orig_name = "rv_top", llvm.linkage = #llvm.linkage<external>} {
    %c-2147483647_i32 = arith.constant -2147483647 : i32
    %c2147483647_i32 = arith.constant 2147483647 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "p"} : memref<1x2xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<256x8xi32>
    affine.for %arg2 = 0 to 256 {
      affine.for %arg3 = 0 to 8 {
        %1 = affine.load %arg0[%arg3 + %arg2 * 8] : memref<2048xi32>
        affine.store %1, %alloca_0[%arg2, %arg3] : memref<256x8xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %0 = affine.for %arg2 = 0 to 256 iter_args(%arg3 = %c0_i32) -> (i32) {
      affine.store %c2147483647_i32, %alloca[0, 0] : memref<1x2xi32>
      affine.store %c-2147483647_i32, %alloca[0, 1] : memref<1x2xi32>
      affine.for %arg4 = 0 to 8 {
        %5 = affine.load %alloca[0, 0] : memref<1x2xi32>
        %6 = affine.load %alloca[0, 1] : memref<1x2xi32>
        %7 = affine.load %alloca_0[%arg2, %arg4] : memref<256x8xi32>
        %8 = arith.cmpi slt, %7, %5 : i32
        %9 = arith.select %8, %7, %5 : i32
        %10 = arith.cmpi sgt, %7, %6 : i32
        %11 = arith.select %10, %7, %6 : i32
        affine.store %9, %alloca[0, 0] : memref<1x2xi32>
        affine.store %11, %alloca[0, 1] : memref<1x2xi32>
      }
      %1 = affine.load %alloca[0, 1] : memref<1x2xi32>
      %2 = affine.load %alloca[0, 0] : memref<1x2xi32>
      %3 = arith.subi %1, %2 : i32
      affine.store %3, %arg1[%arg2] : memref<256xi32>
      %4 = arith.addi %arg3, %1 : i32
      affine.yield %4 : i32
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return %0 : i32
  }
}
