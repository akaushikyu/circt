// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_fS0_S0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA10_fS0_S0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.flatten_nest_invariant_bounds=true --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=true --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=ON

// VITIS_NOTES N129 (W9r16 review fixes), kernel w9r16fx_gp_ff (Vitis 2025.1 td=off: 1, II 4):
// gp_flat with float M. With the N129 keys on (OPEN_ISSUES O170) the flattened nest keeps
// M[i][j] in memory and the fadd recurrence through it (N87 R1) sets II 4, so one port is
// live per cycle: M 1 BRAM. Default (keys off): promoted, 1.
// CHECK: Total BRAM: 1
// ON: Total BRAM: 1

module {
  func.func @_Z3topPA10_fS0_S0_i(%arg0: memref<10x10xf32>, %arg1: memref<10x10xf32>, %arg2: memref<10x10xf32>, %arg3: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "M"} : memref<10x10xf32>
    %0 = arith.index_cast %arg3 : i32 to index
    affine.for %arg4 = 0 to %0 {
      affine.for %arg5 = 0 to %0 {
        affine.store %cst, %alloca[%arg4, %arg5] : memref<10x10xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg4 = 0 to %0 {
      affine.for %arg5 = 0 to %0 {
        affine.for %arg6 = 0 to %0 {
          %1 = affine.load %arg0[%arg4, %arg6] : memref<10x10xf32>
          %2 = affine.load %arg1[%arg6, %arg5] : memref<10x10xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = affine.load %alloca[%arg4, %arg5] : memref<10x10xf32>
          %5 = arith.addf %4, %3 : f32
          affine.store %5, %alloca[%arg4, %arg5] : memref<10x10xf32>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    }
    affine.for %arg4 = 0 to %0 {
      affine.for %arg5 = 0 to %0 {
        %1 = affine.load %alloca[%arg4, %arg5] : memref<10x10xf32>
        affine.store %1, %arg2[%arg4, %arg5] : memref<10x10xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
