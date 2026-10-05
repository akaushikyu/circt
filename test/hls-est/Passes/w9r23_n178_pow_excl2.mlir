// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.math_library.sequential_core_sharing=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N178. Kernel w9r23p_m1_pow_excl2 (~/hls-est-work/exp-src/w9r23p/m1_pow_excl2.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 30 BRAM.
// pow in the two arms of an if, II 1: one core. Off: 60.
// CHECK: Total BRAM: 30{{$}}
// OFF: Total BRAM: 60{{$}}
module {
  func.func @_Z3topPKdPdd(%arg0: memref<1024xf64>, %arg1: memref<1024xf64>, %arg2: f64) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 2.000000e+00 : f64
    %cst_0 = arith.constant 1.000000e+00 : f64
    %cst_1 = arith.constant 0.000000e+00 : f64
    %0 = arith.subf %cst, %arg2 : f64
    affine.for %arg3 = 0 to 1024 {
      %1 = affine.load %arg0[%arg3] : memref<1024xf64>
      %2 = arith.cmpf oge, %1, %cst_1 : f64
      scf.if %2 {
        %3 = arith.addf %1, %cst_0 : f64
        %4 = math.powf %3, %arg2 : f64
        affine.store %4, %arg1[%arg3] : memref<1024xf64>
      } else {
        %3 = arith.negf %1 : f64
        %4 = arith.addf %3, %cst_0 : f64
        %5 = math.powf %4, %0 : f64
        %6 = arith.negf %5 : f64
        affine.store %6, %arg1[%arg3] : memref<1024xf64>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
