// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdS1_d --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdS1_d math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdS1_d --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdS1_d math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.math_library.sequential_core_sharing=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 23 review fixes (2026-10-28). Kernel w9r23rev/m8_pow_inlineoff2 (~/hls-est-work/exp-src/w9r23rev/m8_pow_inlineoff2.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 30 BRAM.
// W9 round 23 review D5 (VITIS_NOTES N178): pow in the pipelined loops of two inline-off functions called by top:
// Vitis makes one pow_generic_double_s in top, 30. With sequential_core_sharing off, one per function, 60.
// CHECK: Total BRAM: 30{{$}}
// OFF: Total BRAM: 60{{$}}
module {
  func.func @_Z3topPKdPdS1_d(%arg0: memref<1024xf64>, %arg1: memref<1024xf64>, %arg2: memref<1024xf64>, %arg3: f64) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    call @_ZL2faPKdPdd(%arg0, %arg1, %arg3) : (memref<1024xf64>, memref<1024xf64>, f64) -> ()
    call @_ZL2fbPKdPdd(%arg1, %arg2, %arg3) : (memref<1024xf64>, memref<1024xf64>, f64) -> ()
    return
  }
  func.func private @_ZL2faPKdPdd(%arg0: memref<1024xf64>, %arg1: memref<1024xf64>, %arg2: f64) attributes {hls.inline_off, hls.orig_name = "fa", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 1.000000e+00 : f64
    affine.for %arg3 = 0 to 1024 {
      %0 = affine.load %arg0[%arg3] : memref<1024xf64>
      %1 = arith.addf %0, %cst : f64
      %2 = math.powf %1, %arg2 : f64
      affine.store %2, %arg1[%arg3] : memref<1024xf64>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL2fbPKdPdd(%arg0: memref<1024xf64>, %arg1: memref<1024xf64>, %arg2: f64) attributes {hls.inline_off, hls.orig_name = "fb", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 2.000000e+00 : f64
    affine.for %arg3 = 0 to 1024 {
      %0 = affine.load %arg0[%arg3] : memref<1024xf64>
      %1 = arith.addf %0, %cst : f64
      %2 = math.powf %1, %arg2 : f64
      affine.store %2, %arg1[%arg3] : memref<1024xf64>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
