// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r22-impl (2026-10-26): VITIS_NOTES N170. round(double) is generic_round
// inlined into the caller with its two ROMs mask_table (64 x 52) and
// one_half_table (64 x 53): 4 BRAM (kernel w9r22p_d9_round; before: round
// was a pure libm helper, 0).
// CHECK: Total BRAM: 4
module {
  func.func @_Z3topPKfPKiPi(%arg0: memref<64xf32>, %arg1: memref<64xi32>, %arg2: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %arg0[%arg3] : memref<64xf32>
      %1 = affine.load %arg1[%arg3] : memref<64xi32>
      %2 = arith.sitofp %1 : i32 to f32
      %3 = arith.divf %0, %2 : f32
      %4 = arith.extf %3 : f32 to f64
      %5 = func.call @round(%4) : (f64) -> f64
      %6 = arith.fptosi %5 : f64 to i32
      affine.store %6, %arg2[%arg3] : memref<64xi32>
    }
    return
  }
  func.func private @round(f64) -> f64 attributes {hls.orig_name = "round", llvm.linkage = #llvm.linkage<external>}
}
