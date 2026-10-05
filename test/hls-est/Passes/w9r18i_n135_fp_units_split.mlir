// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA13_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA13_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.modulo.fast_threshold=0 -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA13_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.modulo.fp_unit_limits=false --config-set scheduling.modulo.height_priority=false --config-set scheduling.timing.operator_latencies.fpaddsub_f64=5 --config-set scheduling.timing.operator_latencies.fpmul_f64=4 -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N135 (W9r18-prove kernel w9r18p_o181_c13; Vitis 2025.1 td=off: 50,
// tb 32 x 64 ram_1p 2): tb[i] += Ab[i][j] * xb[j] over 13 columns in a pipelined
// loop with unroll factor=2, II 2 (Ab's ports). Vitis gives dadd and dmul
// ceil(26 / 2) = 13 units each and places the body in height order on that modulo
// table: the 26 adds fill both slots, copy 2's last add waits a cycle, and the two
// tb stores land in different states (one port: 2). With unlimited units both
// chains end together (two write ports, ram_t2p: 4, the OFF line). The second RUN
// forces the greedy scheduler; the first goes through the simplex, which the
// greedy scheduler re-places at the simplex's II when unit limits are on.
// CHECK: Total BRAM: 50
// OFF: Total BRAM: 52

module {
  func.func @_Z3topPA13_dPdS1_(%arg0: memref<32x13xf64>, %arg1: memref<13xf64>, %arg2: memref<32xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "tb"} : memref<32xf64>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "xb"} : memref<13xf64>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Ab"} : memref<32x13xf64>
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 13 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<32x13xf64>
        affine.store %0, %alloca_1[%arg3, %arg4] : memref<32x13xf64>
      }
    }
    affine.for %arg3 = 0 to 13 {
      %0 = affine.load %arg1[%arg3] : memref<13xf64>
      affine.store %0, %alloca_0[%arg3] : memref<13xf64>
    }
    affine.for %arg3 = 0 to 32 {
      affine.store %cst, %alloca[%arg3] : memref<32xf64>
      %0 = affine.for %arg4 = 0 to 13 iter_args(%arg5 = %cst) -> (f64) {
        %1 = affine.load %alloca_1[%arg3, %arg4] : memref<32x13xf64>
        %2 = affine.load %alloca_0[%arg4] : memref<13xf64>
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
