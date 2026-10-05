// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_iS0_S0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.flatten_nest_invariant_bounds=false --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_iS0_S0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.flatten_nest_invariant_bounds=true --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=true --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=ON
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_iS0_S0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N129 (W9r16 review fixes), kernel w9r16rv_gp_flat (Vitis 2025.1 td=off: 2):
// `M[i][j] += inv[i][k] * B[k][j]` in a pipelined k loop, all three loops bounded by the
// top argument `iter`. Vitis flattens the whole nest (VITIS_LOOP_10_3_VITIS_LOOP_11_4_
// VITIS_LOOP_12_5, II 1) and reads and writes M every iteration: M 1R1W, two live ports, 2.
// Keys tool.hls.pipeline_decision.flatten_nest_invariant_bounds (variable inner bounds that
// are the same in every iteration of the nest flatten) and promote_nest_invariant_only
// (M[i][j] changes over the flattened loop and stays in memory), on by default since W9r18-impl
// (OPEN_ISSUES O170: on, polybench_pragmas k2mm / k3mm lose their match because the N87 R1
// recurrence is not found through a partitioned accumulator). With the keys off
// (first RUN) k alone is pipelined, M[i][j] promoted, one port, 1; on (the default) 2 = Vitis.
// OFF: Total BRAM: 1
// ON: Total BRAM: 2
// CHECK: Total BRAM: 2

module {
  func.func @_Z3topPA10_iS0_S0_i(%arg0: memref<10x10xi32>, %arg1: memref<10x10xi32>, %arg2: memref<10x10xi32>, %arg3: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "M"} : memref<10x10xi32>
    %0 = arith.index_cast %arg3 : i32 to index
    affine.for %arg4 = 0 to %0 {
      affine.for %arg5 = 0 to %0 {
        affine.store %c0_i32, %alloca[%arg4, %arg5] : memref<10x10xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg4 = 0 to %0 {
      affine.for %arg5 = 0 to %0 {
        affine.for %arg6 = 0 to %0 {
          %1 = affine.load %arg0[%arg4, %arg6] : memref<10x10xi32>
          %2 = affine.load %arg1[%arg6, %arg5] : memref<10x10xi32>
          %3 = arith.muli %1, %2 : i32
          %4 = affine.load %alloca[%arg4, %arg5] : memref<10x10xi32>
          %5 = arith.addi %4, %3 : i32
          affine.store %5, %alloca[%arg4, %arg5] : memref<10x10xi32>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    }
    affine.for %arg4 = 0 to %0 {
      affine.for %arg5 = 0 to %0 {
        %1 = affine.load %alloca[%arg4, %arg5] : memref<10x10xi32>
        affine.store %1, %arg2[%arg4, %arg5] : memref<10x10xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
