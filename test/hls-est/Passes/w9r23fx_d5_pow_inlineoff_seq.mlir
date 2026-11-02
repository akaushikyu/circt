// RUN: hls-est %s --symbol-privatize=exclude=_Z3topddPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topddPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 23 review fixes (2026-10-28). Kernel w9r23fx/f5_pow_inlineoff_seq (~/hls-est-work/exp-src/w9r23fx/f5_pow_inlineoff_seq.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 30 BRAM.
// W9 round 23 review D5: one straight-line pow in each of two inline-off functions: one instance in top, 30.
// CHECK: Total BRAM: 30{{$}}
module {
  func.func @_Z3topddPd(%arg0: f64, %arg1: f64, %arg2: memref<?xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %0 = call @_ZL2fadd(%arg0, %arg1) : (f64, f64) -> f64
    %1 = call @_ZL2fbdd(%0, %arg1) : (f64, f64) -> f64
    affine.store %1, %arg2[0] : memref<?xf64>
    return
  }
  func.func private @_ZL2fadd(%arg0: f64, %arg1: f64) -> f64 attributes {hls.inline_off, hls.orig_name = "fa", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 1.000000e+00 : f64
    %0 = arith.addf %arg0, %cst : f64
    %1 = math.powf %0, %arg1 : f64
    return %1 : f64
  }
  func.func private @_ZL2fbdd(%arg0: f64, %arg1: f64) -> f64 attributes {hls.inline_off, hls.orig_name = "fb", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 2.000000e+00 : f64
    %0 = arith.addf %arg0, %cst : f64
    %1 = math.powf %0, %arg1 : f64
    return %1 : f64
  }
}
