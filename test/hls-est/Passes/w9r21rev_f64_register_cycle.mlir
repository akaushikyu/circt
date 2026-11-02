// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA116_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA116_dPdS1_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA116_dPdS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA116_dPdS1_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'scheduling.dependences.f64_register_cycle=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 21 review (2026-10-25): VITIS_NOTES N160 (b). A promoted array
// element carried through ONE double-precision add per iteration (kernel
// w9r21rev_r2e_elem1: `sb[j] += r[i] * A[i][j]` in double, no unroll) bounds
// the II by the dadd's 7 cycles + 1: Vitis II 8, Ab RAM_1WNR 14 copies, 224
// BRAM, total 230. Off (scheduling.dependences.f64_register_cycle=false):
// N160 needs two multi-cycle operations, II 7, 16 copies, 262.
// CHECK: kind=RAM_1WNR  bram=224
// CHECK: 14 copies
// CHECK: Total BRAM: 230
// OFF: 16 copies
// OFF: Total BRAM: 262
// MLIR from the private cgeist of the W9 round 21 review fixes (real headers).
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
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 116 {
      %0 = affine.load %alloca[%arg3] : memref<116xf64>
      affine.store %0, %arg2[%arg3] : memref<116xf64>
    }
    return
  }
}
