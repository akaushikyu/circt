// RUN: hls-est %s --symbol-privatize=exclude=_Z7lat_topPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7lat_topPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z7lat_topPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7lat_topPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set scheduling.timing.operator_latencies.fpdiv_f64=12 -o /dev/null | FileCheck %s --check-prefix=LOFF
// W9r9-impl (2026-10-21): VITIS_NOTES N78: a pipelined loop with a double divide recurrence (s = s / t) runs at II 58, so 32 reads of A per iteration need one RAM_1WNR copy less than at the old fpdiv latency 12.
// Kernel w9r9p_lat_div64r32; MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: A RAM_1WNR 8 BRAM_18K.
// With scheduling.timing.operator_latencies.fpdiv_f64=12 (LOFF): 16.
// LOFF: Total BRAM: 16{{$}}
// CHECK: Total BRAM: 8{{$}}

module {
  func.func @_Z7lat_topPd(%arg0: memref<2048xf64>) -> f64 attributes {hls.orig_name = "lat_top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f64
    %cst_0 = arith.constant 1.000000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<2048xf64>
    affine.for %arg1 = 0 to 2048 {
      %1 = affine.load %arg0[%arg1] : memref<2048xf64>
      affine.store %1, %alloca[%arg1] : memref<2048xf64>
    }
    %0 = affine.for %arg1 = 0 to 64 iter_args(%arg2 = %cst_0) -> (f64) {
      %1 = affine.for %arg3 = 0 to 32 iter_args(%arg4 = %cst) -> (f64) {
        %3 = affine.load %alloca[%arg3 + %arg1 * 32] : memref<2048xf64>
        %4 = arith.addf %arg4, %3 : f64
        affine.yield %4 : f64
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %2 = arith.divf %arg2, %1 : f64
      affine.yield %2 : f64
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return %0 : f64
  }
}
