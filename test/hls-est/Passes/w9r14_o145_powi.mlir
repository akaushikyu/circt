// RUN: hls-est %s --symbol-privatize=exclude=_Z6mc_topdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mc_topdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s

// OPEN_ISSUES O145, kernel w2i_powce_f64 (Vitis 2025.1 td=off): C pow(x, 2)
// of a double, which cgeist lowers to llvm.intr.powi: Vitis pow_generic_double_s,
// 30 BRAM (math_costs' pow double constant exponent).
// CHECK: Total BRAM: 30

module {
  func.func @_Z6mc_topdPd(%arg0: f64, %arg1: memref<?xf64>) attributes {hls.orig_name = "mc_top", llvm.linkage = #llvm.linkage<external>} {
    %c2_i32 = arith.constant 2 : i32
    %0 = llvm.intr.powi(%arg0, %c2_i32)  : (f64, i32) -> f64
    affine.store %0, %arg1[0] : memref<?xf64>
    return
  }
}
