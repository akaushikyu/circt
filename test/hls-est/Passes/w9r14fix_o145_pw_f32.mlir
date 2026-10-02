// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s

// W9r14 review fixes, kernel w9r14rv_pw_f32 (Vitis 2025.1 td=off):
// `std::pow(float, 2)` is the C++11 promoted double overload; Vitis builds
// pow_generic<double> (30). This MLIR is from the cgeist before the fix,
// llvm.intr.powi(f32, i32) -> f64: the core is priced from its result type
// (double), not the operand (float, 7).
// CHECK: math.core function=pow type=double
// CHECK: Total BRAM: 30

module {
  func.func @_Z3topPKfPf(%arg0: memref<64xf32>, %arg1: memref<64xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c2_i32 = arith.constant 2 : i32
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %arg0[%arg2] : memref<64xf32>
      %1 = llvm.intr.powi(%0, %c2_i32)  : (f32, i32) -> f64
      %2 = arith.truncf %1 : f64 to f32
      affine.store %2, %arg1[%arg2] : memref<64xf32>
    } {hls.pipeline_off}
    return
  }
}
