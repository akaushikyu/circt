// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdS1_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdS1_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.math_library.shared_library_modules=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 22 review fix (D6): sin in one loop and cos in the next loop
// (both read in) share one sin_or_cos_double_s: 8 (kernel
// w9r22rv_k12_sin_then_cos, Vitis 8; round 22: 16).
// CHECK: Total BRAM: 8
// OFF: Total BRAM: 16
module {
  func.func @_Z3topPKdPdS1_(%arg0: memref<256xf64>, %arg1: memref<256xf64>, %arg2: memref<256xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 5.000000e-01 : f64
    affine.for %arg3 = 0 to 256 {
      %0 = affine.load %arg0[%arg3] : memref<256xf64>
      %1 = math.sin %0 : f64
      affine.store %1, %arg1[%arg3] : memref<256xf64>
    }
    affine.for %arg3 = 0 to 256 {
      %0 = affine.load %arg0[%arg3] : memref<256xf64>
      %1 = arith.mulf %0, %cst : f64
      %2 = math.cos %1 : f64
      affine.store %2, %arg2[%arg3] : memref<256xf64>
    }
    return
  }
}
