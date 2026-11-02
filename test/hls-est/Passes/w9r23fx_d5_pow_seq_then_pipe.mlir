// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPddS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPddS1_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 23 review fixes (2026-10-28). Kernel w9r23fx/f4_pow_seq_then_pipe (~/hls-est-work/exp-src/w9r23fx/f4_pow_seq_then_pipe.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 30 BRAM.
// W9 round 23 review D5: a straight-line pow before a pipelined loop with pow: one instance, 30.
// CHECK: Total BRAM: 30{{$}}
module {
  func.func @_Z3topPKdPddS1_(%arg0: memref<1024xf64>, %arg1: memref<1024xf64>, %arg2: f64, %arg3: memref<?xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 1.000000e+00 : f64
    %cst_0 = arith.constant 3.000000e+00 : f64
    %0 = affine.load %arg0[0] : memref<1024xf64>
    %1 = arith.addf %0, %cst_0 : f64
    %2 = math.powf %1, %arg2 : f64
    affine.store %2, %arg3[0] : memref<?xf64>
    affine.for %arg4 = 0 to 1024 {
      %3 = affine.load %arg0[%arg4] : memref<1024xf64>
      %4 = arith.addf %3, %cst : f64
      %5 = math.powf %4, %2 : f64
      affine.store %5, %arg1[%arg4] : memref<1024xf64>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
