// RUN: hls-est %s --symbol-privatize=exclude=_Z3topiPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topiPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topiPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topiPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.middle_end.dead_memory.overwritten_call_outputs=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N107, kernel w9r14p_dc_dead (Vitis 2025.1 td=off): f(n, x, y)
// (inline off, hls::sin / hls::cos of double) whose reference outputs x, y are
// overwritten after the call (x = y = 1.0) before any read: Vitis deletes the
// call and its cores, 0 BRAM. hls-est: --dead-memory-elimination
// (tool.hls.middle_end.dead_memory.overwritten_call_outputs); off: 16.
// CHECK: Total BRAM: 0
// OFF: Total BRAM: 16

module {
  func.func @_Z3topiPd(%arg0: i32, %arg1: memref<2xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 1.000000e+00 : f64
    %cst_0 = arith.constant 5.000000e-01 : f64
    %alloca = memref.alloca() {polygeist.varname = "y"} : memref<1xf64>
    %cast = memref.cast %alloca : memref<1xf64> to memref<?xf64>
    %alloca_1 = memref.alloca() {polygeist.varname = "x"} : memref<1xf64>
    %cast_2 = memref.cast %alloca_1 : memref<1xf64> to memref<?xf64>
    affine.store %cst_0, %alloca_1[0] : memref<1xf64>
    affine.store %cst_0, %alloca[0] : memref<1xf64>
    call @_ZL1fiRdS_(%arg0, %cast_2, %cast) : (i32, memref<?xf64>, memref<?xf64>) -> ()
    affine.store %cst, %alloca[0] : memref<1xf64>
    affine.store %cst, %alloca_1[0] : memref<1xf64>
    affine.store %cst, %arg1[0] : memref<2xf64>
    %0 = affine.load %alloca[0] : memref<1xf64>
    affine.store %0, %arg1[1] : memref<2xf64>
    return
  }
  func.func private @_ZL1fiRdS_(%arg0: i32, %arg1: memref<?xf64>, %arg2: memref<?xf64>) attributes {hls.inline_off, hls.orig_name = "f", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 5.000000e-01 : f64
    %0 = arith.index_cast %arg0 : i32 to index
    affine.for %arg3 = 0 to %0 {
      %1 = affine.load %arg1[0] : memref<?xf64>
      %2 = math.sin %1 : f64
      %3 = affine.load %arg2[0] : memref<?xf64>
      %4 = math.cos %3 : f64
      %5 = arith.mulf %2, %4 : f64
      affine.store %5, %arg1[0] : memref<?xf64>
      %6 = arith.addf %5, %cst : f64
      affine.store %6, %arg2[0] : memref<?xf64>
    }
    return
  }
}
