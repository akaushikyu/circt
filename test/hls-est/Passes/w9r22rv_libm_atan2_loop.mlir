// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 22 review fix (D1, D8): atan2(double) has a loop in its core
// (atan2_generic_double_Pipeline_1, cordic_ctab_table_128, 4 BRAM): the loop
// around it is not pipelined, tbl 2 + core 4 = 6 (kernel w9r22rv_k3_atan2_loop,
// Vitis 6; round 22: 4).
// CHECK: Total BRAM: 6
module {
  func.func @_Z3topPKdPd(%arg0: memref<512xf64>, %arg1: memref<512xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 1.500000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "tbl"} : memref<512xf64>
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %arg0[%arg2] : memref<512xf64>
      affine.store %0, %alloca[%arg2] : memref<512xf64>
    }
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %alloca[%arg2] : memref<512xf64>
      %1 = func.call @atan2(%0, %cst) : (f64, f64) -> f64
      affine.store %1, %alloca[%arg2] : memref<512xf64>
    }
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %alloca[%arg2] : memref<512xf64>
      affine.store %0, %arg1[%arg2] : memref<512xf64>
    }
    return
  }
  func.func private @atan2(f64, f64) -> f64 attributes {hls.orig_name = "atan2", llvm.linkage = #llvm.linkage<external>}
}
