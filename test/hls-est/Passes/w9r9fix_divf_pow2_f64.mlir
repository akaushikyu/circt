// RUN: hls-est %s --symbol-privatize=exclude=_Z7lat_topPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7lat_topPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r9 review fix D7 (2026-10-21): a floating-point divide by a power-of-two constant is a multiply (VITIS_NOTES N79,
// FloatOps.h isExactReciprocalDivide). `s = s / 2.0 + t` (double): Vitis multiplies by 0.5 (a.o.3.ll `fmul double %s_load, 5.000000e-01`), II 11, A RAM_1WNR 16. hls-est now prices the divide as fpmul: II 9 (fpmul 4 + fpaddsub 5), 3 copies, 24; the remaining gap is the f64 multiplier latency (VITIS_NOTES N78: dmul 6 + dadd 5 = 11; OPEN_ISSUES O107). Before the fix: II 63, 8.
// Kernel ~/hls-est-work/coord/scratch/w9r9rev/k/e78_div2.cpp; MLIR from cgeist 537d6614 (installed), --shim real.
// Vitis 2025.1 td=off: 16 BRAM_18K.
// CHECK: Total BRAM: 24{{$}}

module {
  func.func @_Z7lat_topPd(%arg0: memref<2048xf64>) -> f64 attributes {hls.orig_name = "lat_top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 2.000000e+00 : f64
    %cst_0 = arith.constant 0.000000e+00 : f64
    %cst_1 = arith.constant 1.000000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<2048xf64>
    affine.for %arg1 = 0 to 2048 {
      %1 = affine.load %arg0[%arg1] : memref<2048xf64>
      affine.store %1, %alloca[%arg1] : memref<2048xf64>
    }
    %0 = affine.for %arg1 = 0 to 64 iter_args(%arg2 = %cst_1) -> (f64) {
      %1 = affine.for %arg3 = 0 to 32 iter_args(%arg4 = %cst_0) -> (f64) {
        %4 = affine.load %alloca[%arg3 + %arg1 * 32] : memref<2048xf64>
        %5 = arith.addf %arg4, %4 : f64
        affine.yield %5 : f64
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %2 = arith.divf %arg2, %cst : f64
      %3 = arith.addf %2, %1 : f64
      affine.yield %3 : f64
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return %0 : f64
  }
}
