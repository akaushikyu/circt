// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_fS0_S0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.flatten_nest_invariant_bounds=true --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=true --config-set scheduling.dependences.enclosing_iv_sample_steps=7 -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_fS0_S0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.flatten_nest_invariant_bounds=true --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=true --config-set scheduling.dependences.enclosing_iv_sample_steps=0 -o /dev/null 2>&1 | FileCheck %s --check-prefix=LB

// OPEN_ISSUES O170 (b), kernel w9r16fx_gp_ffo (Vitis 2025.1 td=off: 1 BRAM, the
// flattened i x j x k loop at II 4 from the fadd recurrence of M[i][j]): the nest
// bounds are the counter `iter` of a loop around it (GP_selection's shape). With
// N129's keys on, the memory-recurrence analysis of the flattened loop evaluates
// `iter` 7 steps past its lower bound (scheduling.dependences.enclosing_iv_sample_steps
// = 7): the recurrence is found, II 4, M one port (1). At the lower bound (1, the
// value 0, the default before W9r18-impl) the nest is one iteration long, the recurrence is missed and M takes
// two ports (the second run: 2).
// CHECK: Total BRAM: 1
// LB: Total BRAM: 2

#map = affine_map<(d0) -> (d0)>
module {
  func.func @_Z3topPA10_fS0_S0_i(%arg0: memref<10x10xf32>, %arg1: memref<10x10xf32>, %arg2: memref<10x10xf32>, %arg3: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "M"} : memref<10x10xf32>
    %0 = arith.index_cast %arg3 : i32 to index
    affine.for %arg4 = 1 to %0 {
      affine.for %arg5 = 0 to #map(%arg4) {
        affine.for %arg6 = 0 to #map(%arg4) {
          affine.store %cst, %alloca[%arg5, %arg6] : memref<10x10xf32>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
      affine.for %arg5 = 0 to #map(%arg4) {
        affine.for %arg6 = 0 to #map(%arg4) {
          affine.for %arg7 = 0 to #map(%arg4) {
            %1 = affine.load %arg0[%arg5, %arg7] : memref<10x10xf32>
            %2 = affine.load %arg1[%arg7, %arg6] : memref<10x10xf32>
            %3 = arith.mulf %1, %2 : f32
            %4 = affine.load %alloca[%arg5, %arg6] : memref<10x10xf32>
            %5 = arith.addf %4, %3 : f32
            affine.store %5, %alloca[%arg5, %arg6] : memref<10x10xf32>
          } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
        }
      }
      affine.for %arg5 = 0 to #map(%arg4) {
        affine.for %arg6 = 0 to #map(%arg4) {
          %1 = affine.load %alloca[%arg5, %arg6] : memref<10x10xf32>
          affine.store %1, %arg2[%arg5, %arg6] : memref<10x10xf32>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    }
    return
  }
}
