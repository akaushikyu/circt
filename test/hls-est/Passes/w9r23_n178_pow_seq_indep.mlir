// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.math_library.sequential_core_sharing=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N178. Kernel w9r23p_m6_pow_seq_indep (~/hls-est-work/exp-src/w9r23p/m6_pow_seq_indep.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 30 BRAM.
// Two independent pow in straight-line code (inputs loaded from in[0] / in[1]): Vitis one core, hls-est two
// (the readiness grouping of N116, which held-out adam_optimizer / cubic_spline confirm for scalar inputs):
// 60 with the key on and off, open (OPEN_ISSUES O247).
// CHECK: Total BRAM: 60{{$}}
// OFF: Total BRAM: 60{{$}}
module {
  func.func @_Z3topPKdPdd(%arg0: memref<4xf64>, %arg1: memref<2xf64>, %arg2: f64) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 2.000000e+00 : f64
    %0 = affine.load %arg0[0] : memref<4xf64>
    %1 = math.powf %0, %arg2 : f64
    affine.store %1, %arg1[0] : memref<2xf64>
    %2 = affine.load %arg0[1] : memref<4xf64>
    %3 = arith.subf %cst, %arg2 : f64
    %4 = math.powf %2, %3 : f64
    affine.store %4, %arg1[1] : memref<2xf64>
    return
  }
}
