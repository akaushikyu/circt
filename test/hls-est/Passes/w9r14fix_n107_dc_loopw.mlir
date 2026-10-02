// RUN: hls-est %s --symbol-privatize=exclude=_Z3topiPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topiPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topiPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topiPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.middle_end.dead_memory.overwritten_by_loops=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// W9r14 review fixes, kernel w9r14rv_dc_loopw (Vitis 2025.1 td=off): the
// scalar outputs of the kept call f(n, x, y) are overwritten by a 4-trip
// loop after the call (x = in[k]; y = 2 * in[k]): Vitis deletes the call and
// its sin / cos cores, 0. hls-est (N107): an overwrite that is the first
// access inside a loop that runs at least once counts; off: 16.
// CHECK: Total BRAM: 0
// OFF: Total BRAM: 16

module {
  func.func @_Z3topiPKdPd(%arg0: i32, %arg1: memref<4xf64>, %arg2: memref<2xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 2.000000e+00 : f64
    %cst_0 = arith.constant 5.000000e-01 : f64
    %alloca = memref.alloca() {polygeist.varname = "y"} : memref<1xf64>
    %cast = memref.cast %alloca : memref<1xf64> to memref<?xf64>
    %alloca_1 = memref.alloca() {polygeist.varname = "x"} : memref<1xf64>
    %cast_2 = memref.cast %alloca_1 : memref<1xf64> to memref<?xf64>
    affine.store %cst_0, %alloca_1[0] : memref<1xf64>
    affine.store %cst_0, %alloca[0] : memref<1xf64>
    call @_ZL1fiRdS_(%arg0, %cast_2, %cast) : (i32, memref<?xf64>, memref<?xf64>) -> ()
    affine.for %arg3 = 0 to 4 {
      %2 = affine.load %arg1[%arg3] : memref<4xf64>
      affine.store %2, %alloca_1[0] : memref<1xf64>
      %3 = affine.load %arg1[%arg3] : memref<4xf64>
      %4 = arith.mulf %3, %cst : f64
      affine.store %4, %alloca[0] : memref<1xf64>
    }
    %0 = affine.load %alloca_1[0] : memref<1xf64>
    affine.store %0, %arg2[0] : memref<2xf64>
    %1 = affine.load %alloca[0] : memref<1xf64>
    affine.store %1, %arg2[1] : memref<2xf64>
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
