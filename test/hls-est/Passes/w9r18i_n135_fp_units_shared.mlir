// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA116_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA116_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.modulo.fast_threshold=0 -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA116_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.modulo.fp_unit_limits=false --config-set scheduling.modulo.height_priority=false --config-set scheduling.timing.operator_latencies.fpaddsub_f64=5 --config-set scheduling.timing.operator_latencies.fpmul_f64=4 -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N135 (W9r18-prove kernel w9r18p_o181_c116; Vitis 2025.1 td=off: 264,
// tb ram_t2p 4): the c13 shape over 116 columns, II 14 (232 Ab loads at 17 per
// slot). ceil(232 / 14) = 17 dadd and dmul units; the slots balance, no chain
// waits, and both copies store tb in one state (two write ports, ram_t2p: 4).
// Without the units and the 7-cycle double latencies (OFF) the copies' stores
// fall in different states (RAM_1P: 262).
// CHECK: Total BRAM: 264
// OFF: Total BRAM: 262

module {
  func.func @_Z3topPA116_dPdS1_(%arg0: memref<32x116xf64>, %arg1: memref<116xf64>, %arg2: memref<32xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "tb"} : memref<32xf64>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "xb"} : memref<116xf64>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Ab"} : memref<32x116xf64>
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 116 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<32x116xf64>
        affine.store %0, %alloca_1[%arg3, %arg4] : memref<32x116xf64>
      }
    }
    affine.for %arg3 = 0 to 116 {
      %0 = affine.load %arg1[%arg3] : memref<116xf64>
      affine.store %0, %alloca_0[%arg3] : memref<116xf64>
    }
    affine.for %arg3 = 0 to 32 {
      affine.store %cst, %alloca[%arg3] : memref<32xf64>
      %0 = affine.for %arg4 = 0 to 116 iter_args(%arg5 = %cst) -> (f64) {
        %1 = affine.load %alloca_1[%arg3, %arg4] : memref<32x116xf64>
        %2 = affine.load %alloca_0[%arg4] : memref<116xf64>
        %3 = arith.mulf %1, %2 : f64
        %4 = arith.addf %arg5, %3 : f64
        affine.store %4, %alloca[%arg3] : memref<32xf64>
        affine.yield %4 : f64
      }
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
    affine.for %arg3 = 0 to 32 {
      %0 = affine.load %alloca[%arg3] : memref<32xf64>
      affine.store %0, %arg2[%arg3] : memref<32xf64>
    }
    return
  }
}
