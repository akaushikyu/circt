// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_iS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_iS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=true --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=ON
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_iS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N129 (W9r16 review fixes), kernel w9r16rv_gp_flatc (Vitis 2025.1 td=off: 2):
// gp_flat with constant bounds. hls-est flattens i and j into the k pipeline, but promotes
// M[i][j] to a register before that decision, so the flattened nest keeps one read before
// and one write after the k loop in a sequential scope (one port, 1). With
// promote_nest_invariant_only (on by default since W9r18-impl; OPEN_ISSUES O170) the promotion waits for
// the parents' flatten decisions and keeps M[i][j] in memory: 1R1W at II 1, 2 = Vitis.
// OFF: Total BRAM: 1
// ON: Total BRAM: 2
// CHECK: Total BRAM: 2

module {
  func.func @_Z3topPA10_iS0_S0_(%arg0: memref<10x10xi32>, %arg1: memref<10x10xi32>, %arg2: memref<10x10xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "M"} : memref<10x10xi32>
    affine.for %arg3 = 0 to 10 {
      affine.for %arg4 = 0 to 10 {
        affine.store %c0_i32, %alloca[%arg3, %arg4] : memref<10x10xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg3 = 0 to 10 {
      affine.for %arg4 = 0 to 10 {
        affine.for %arg5 = 0 to 10 {
          %0 = affine.load %arg0[%arg3, %arg5] : memref<10x10xi32>
          %1 = affine.load %arg1[%arg5, %arg4] : memref<10x10xi32>
          %2 = arith.muli %0, %1 : i32
          %3 = affine.load %alloca[%arg3, %arg4] : memref<10x10xi32>
          %4 = arith.addi %3, %2 : i32
          affine.store %4, %alloca[%arg3, %arg4] : memref<10x10xi32>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    }
    affine.for %arg3 = 0 to 10 {
      affine.for %arg4 = 0 to 10 {
        %0 = affine.load %alloca[%arg3, %arg4] : memref<10x10xi32>
        affine.store %0, %arg2[%arg3, %arg4] : memref<10x10xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
