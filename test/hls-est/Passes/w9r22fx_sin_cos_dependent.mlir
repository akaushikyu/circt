// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.math_library.shared_library_modules=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 22 review fix (D6): `cos(in[1] + sin(in[0]))` in straight-line code:
// one module, 8 (kernel w9r22fx_f4_sin_cos_seq, Vitis 8).
// CHECK: Total BRAM: 8
// OFF: Total BRAM: 16
module {
  func.func @_Z3topPKdPd(%arg0: memref<4xf64>, %arg1: memref<4xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %0 = affine.load %arg0[0] : memref<4xf64>
    %1 = math.sin %0 : f64
    %2 = affine.load %arg0[1] : memref<4xf64>
    %3 = arith.addf %2, %1 : f64
    %4 = math.cos %3 : f64
    affine.store %1, %arg1[0] : memref<4xf64>
    affine.store %4, %arg1[1] : memref<4xf64>
    return
  }
}
