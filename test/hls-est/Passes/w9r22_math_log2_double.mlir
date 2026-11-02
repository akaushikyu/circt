// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r22-impl (2026-10-26): VITIS_NOTES N170. Library math functions the cost
// table did not list: log2(double) is log_generic_double_s, 21 BRAM per
// instance (kernel w9r22p_d7_log2; before: "no entry ... 0 assumed").
// CHECK: Total BRAM: 21
module {
  func.func @_Z3topPKdPd(%arg0: memref<256xf64>, %arg1: memref<?xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f64
    %0 = affine.for %arg2 = 0 to 256 iter_args(%arg3 = %cst) -> (f64) {
      %1 = affine.load %arg0[%arg2] : memref<256xf64>
      %2 = func.call @log2(%1) : (f64) -> f64
      %3 = arith.mulf %1, %2 : f64
      %4 = arith.subf %arg3, %3 : f64
      affine.yield %4 : f64
    }
    affine.store %0, %arg1[0] : memref<?xf64>
    return
  }
  func.func private @log2(f64) -> f64 attributes {hls.orig_name = "log2", llvm.linkage = #llvm.linkage<external>}
}
