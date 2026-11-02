// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 22 review fix (D8): log2f costs log_generic_float_s, 6 BRAM, and the
// loop around it is pipelined (kernel w9r22rv_k19_log2f, Vitis 6; round 22: 0).
// CHECK: Total BRAM: 6
module {
  func.func @_Z3topPKfPf(%arg0: memref<256xf32>, %arg1: memref<?xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %0 = affine.for %arg2 = 0 to 256 iter_args(%arg3 = %cst) -> (f32) {
      %1 = affine.load %arg0[%arg2] : memref<256xf32>
      %2 = func.call @log2f(%1) : (f32) -> f32
      %3 = arith.mulf %1, %2 : f32
      %4 = arith.subf %arg3, %3 : f32
      affine.yield %4 : f32
    }
    affine.store %0, %arg1[0] : memref<?xf32>
    return
  }
  func.func private @log2f(f32) -> f32 attributes {hls.orig_name = "log2f", llvm.linkage = #llvm.linkage<external>}
}
