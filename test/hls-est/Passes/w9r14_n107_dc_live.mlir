// RUN: hls-est %s --symbol-privatize=exclude=_Z3topiPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topiPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N107, kernel w9r14p_dc_live (Vitis 2025.1 td=off): dc_dead
// without the reassignment: two sin_or_cos_double_s, 16.
// CHECK: Total BRAM: 16

module {
  func.func @_Z3topiPd(%arg0: i32, %arg1: memref<2xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 5.000000e-01 : f64
    %alloca = memref.alloca() {polygeist.varname = "y"} : memref<1xf64>
    %cast = memref.cast %alloca : memref<1xf64> to memref<?xf64>
    %alloca_0 = memref.alloca() {polygeist.varname = "x"} : memref<1xf64>
    %cast_1 = memref.cast %alloca_0 : memref<1xf64> to memref<?xf64>
    affine.store %cst, %alloca_0[0] : memref<1xf64>
    affine.store %cst, %alloca[0] : memref<1xf64>
    call @_ZL1fiRdS_(%arg0, %cast_1, %cast) : (i32, memref<?xf64>, memref<?xf64>) -> ()
    %0 = affine.load %alloca_0[0] : memref<1xf64>
    affine.store %0, %arg1[0] : memref<2xf64>
    %1 = affine.load %alloca[0] : memref<1xf64>
    affine.store %1, %arg1[1] : memref<2xf64>
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
