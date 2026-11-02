// RUN: hls-est %s --symbol-privatize=exclude=_Z3topdddPdS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topdddPdS_S_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 23 review fixes (2026-10-28). Kernel w9r23fx/f7_pow_inlineoff_two_one (~/hls-est-work/exp-src/w9r23fx/f7_pow_inlineoff_two_one.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real).
// W9 round 23 review D5 control (held-out cubic_spline form): one callee calls pow twice on independent scalars,
// its sibling once: a callee that needs two instances keeps them and the sibling keeps its own, 90.
// CHECK: Total BRAM: 90{{$}}
module {
  func.func @_Z3topdddPdS_S_(%arg0: f64, %arg1: f64, %arg2: f64, %arg3: memref<?xf64>, %arg4: memref<?xf64>, %arg5: memref<?xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    call @_ZL2fadddPdS_(%arg0, %arg1, %arg2, %arg3, %arg4) : (f64, f64, f64, memref<?xf64>, memref<?xf64>) -> ()
    %0 = arith.mulf %arg0, %arg1 : f64
    %1 = call @_ZL2fbdd(%0, %arg2) : (f64, f64) -> f64
    affine.store %1, %arg5[0] : memref<?xf64>
    return
  }
  func.func private @_ZL2fadddPdS_(%arg0: f64, %arg1: f64, %arg2: f64, %arg3: memref<?xf64>, %arg4: memref<?xf64>) attributes {hls.inline_off, hls.orig_name = "fa", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 3.000000e+00 : f64
    %cst_0 = arith.constant 1.000000e+00 : f64
    %0 = arith.addf %arg0, %cst_0 : f64
    %1 = math.powf %0, %arg2 : f64
    affine.store %1, %arg3[0] : memref<?xf64>
    %2 = arith.addf %arg1, %cst : f64
    %3 = math.powf %2, %arg2 : f64
    affine.store %3, %arg4[0] : memref<?xf64>
    return
  }
  func.func private @_ZL2fbdd(%arg0: f64, %arg1: f64) -> f64 attributes {hls.inline_off, hls.orig_name = "fb", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 2.000000e+00 : f64
    %0 = arith.addf %arg0, %cst : f64
    %1 = math.powf %0, %arg1 : f64
    return %1 : f64
  }
}
