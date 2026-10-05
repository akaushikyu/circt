// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdS0_PdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdS0_PdS1_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 22 review fix (D6), control: sin and cos in two loops on disjoint
// arrays run concurrently (Vitis outlines the loops): two modules, 16 (kernel
// w9r22fx_f3_sin_cos_disjoint, Vitis 16).
// CHECK: Total BRAM: 16
module {
  func.func @_Z3topPKdS0_PdS1_(%arg0: memref<256xf64>, %arg1: memref<256xf64>, %arg2: memref<256xf64>, %arg3: memref<256xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 5.000000e-01 : f64
    affine.for %arg4 = 0 to 256 {
      %0 = affine.load %arg0[%arg4] : memref<256xf64>
      %1 = math.sin %0 : f64
      affine.store %1, %arg2[%arg4] : memref<256xf64>
    }
    affine.for %arg4 = 0 to 256 {
      %0 = affine.load %arg1[%arg4] : memref<256xf64>
      %1 = arith.mulf %0, %cst : f64
      %2 = math.cos %1 : f64
      affine.store %2, %arg3[%arg4] : memref<256xf64>
    }
    return
  }
}
