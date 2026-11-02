// RUN: hls-est %s --symbol-privatize=exclude=_Z2hpPA8_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.modulo.fast_threshold=0 --config-set scheduling.modulo.height_priority=true -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z2hpPA8_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.modulo.fast_threshold=0 --config-set scheduling.modulo.height_priority=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --symbol-privatize=exclude=_Z2hpPA8_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N133 (corrected, W9 round 17 review fixes), kernel w9r17fx_hp
// (Vitis 2025.1 td=off: 4, `t` RAM_AUTO_1R1W / ram_t2p 64 x 64): two 8-term double
// reductions over rows i and i + 1 of an argument A[64][8] (2 ports, 16 loads: II 8),
// t[i] = s0; t[i + 1] = s1. Vitis issues one load of each copy per state and stores
// both t elements in one state (two write ports). The greedy scheduler (forced with
// fast_threshold=0) in program order gives copy 1 the first four states' ports, so
// copy 2's chain and its store end later: one write per state, RAM_1P, 2. With the
// height priority both chains start together: 4 = Vitis. The simplex (third RUN)
// gives 4 as well.
// CHECK: Total BRAM: 4
// OFF: Total BRAM: 2

module {
  func.func @_Z2hpPA8_dPdS1_(%arg0: memref<64x8xf64>, %arg1: memref<8xf64>, %arg2: memref<64xf64>) attributes {hls.orig_name = "hp", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "t"} : memref<64xf64>
    affine.for %arg3 = 0 to 64 step 2 {
      %0 = affine.for %arg4 = 0 to 8 iter_args(%arg5 = %cst) -> (f64) {
        %2 = affine.load %arg0[%arg3, %arg4] : memref<64x8xf64>
        %3 = affine.load %arg1[%arg4] : memref<8xf64>
        %4 = arith.mulf %2, %3 : f64
        %5 = arith.addf %arg5, %4 : f64
        affine.yield %5 : f64
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %1 = affine.for %arg4 = 0 to 8 iter_args(%arg5 = %cst) -> (f64) {
        %2 = affine.load %arg0[%arg3 + 1, %arg4] : memref<64x8xf64>
        %3 = affine.load %arg1[%arg4] : memref<8xf64>
        %4 = arith.mulf %2, %3 : f64
        %5 = arith.addf %arg5, %4 : f64
        affine.yield %5 : f64
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %0, %alloca[%arg3] : memref<64xf64>
      affine.store %1, %alloca[%arg3 + 1] : memref<64xf64>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %alloca[-%arg3 + 63] : memref<64xf64>
      affine.store %0, %arg2[%arg3] : memref<64xf64>
    }
    return
  }
}
