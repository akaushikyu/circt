// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA116_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA116_dPdS1_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA116_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA116_dPdS1_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set scheduling.dependences.promoted_element_register_cycle=false --config-set scheduling.dependences.f64_register_cycle=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N160: an iter_arg that carries a promoted array
// element through two or more multi-cycle operations bounds the II by the chain
// latency + 1. Kernel w9r21p_b2_s (`sb[j] += rb[i] * Ab[i][j]`, i pipelined and
// unrolled by 2, j unrolled 116: two chained 7-state dadds on each sb[j]):
// Vitis II 15, Ab RAM_1WNR 3712 x 64, 15 copies, 240; rb 4, sb 4: total 248.
// Without the rule (and without N160 (b), f64_register_cycle) the loop runs at the chain's II 14 (16 copies, 256). MLIR
// from the installed cgeist 5523df29 with the real headers.
// CHECK: kind=RAM_1WNR  bram=240
// CHECK: 15 copies
// CHECK: Total BRAM: 248
// OFF: kind=RAM_1WNR  bram=256
// OFF: Total BRAM: 264
module {
  func.func @_Z3topPA116_dPdS1_(%arg0: memref<32x116xf64>, %arg1: memref<32xf64>, %arg2: memref<116xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "sb"} : memref<116xf64>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "rb"} : memref<32xf64>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Ab"} : memref<32x116xf64>
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 116 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<32x116xf64>
        affine.store %0, %alloca_1[%arg3, %arg4] : memref<32x116xf64>
      }
    }
    affine.for %arg3 = 0 to 116 {
      affine.store %cst, %alloca[%arg3] : memref<116xf64>
    }
    affine.for %arg3 = 0 to 32 {
      %0 = affine.load %arg1[%arg3] : memref<32xf64>
      affine.store %0, %alloca_0[%arg3] : memref<32xf64>
    }
    affine.for %arg3 = 0 to 32 {
      %0 = affine.load %alloca_0[%arg3] : memref<32xf64>
      affine.for %arg4 = 0 to 116 {
        %1 = affine.load %alloca_1[%arg3, %arg4] : memref<32x116xf64>
        %2 = arith.mulf %0, %1 : f64
        %3 = affine.load %alloca[%arg4] : memref<116xf64>
        %4 = arith.addf %3, %2 : f64
        affine.store %4, %alloca[%arg4] : memref<116xf64>
      }
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
    affine.for %arg3 = 0 to 116 {
      %0 = affine.load %alloca[%arg3] : memref<116xf64>
      affine.store %0, %arg2[%arg3] : memref<116xf64>
    }
    return
  }
}
