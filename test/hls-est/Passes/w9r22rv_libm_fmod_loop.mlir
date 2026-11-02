// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 22 review fix (D1): fmod(double)'s core has a loop
// (generic_fmod_double_Pipeline_1), so Vitis does not pipeline the loop that
// calls it: tbl stays a 1-port RAM, 2 BRAM (kernel w9r22rv_k3_fmod_loop, Vitis 2;
// round 22 pipelined it, RAM_2P 4). fmod has no cost-table entry (0).
// CHECK: Total BRAM: 2
module {
  func.func @_Z3topPKdPd(%arg0: memref<512xf64>, %arg1: memref<512xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 3.700000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "tbl"} : memref<512xf64>
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %arg0[%arg2] : memref<512xf64>
      affine.store %0, %alloca[%arg2] : memref<512xf64>
    }
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %alloca[%arg2] : memref<512xf64>
      %1 = func.call @fmod(%0, %cst) : (f64, f64) -> f64
      affine.store %1, %alloca[%arg2] : memref<512xf64>
    }
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %alloca[%arg2] : memref<512xf64>
      affine.store %0, %arg1[%arg2] : memref<512xf64>
    }
    return
  }
  func.func private @fmod(f64, f64) -> f64 attributes {hls.orig_name = "fmod", llvm.linkage = #llvm.linkage<external>}
}
