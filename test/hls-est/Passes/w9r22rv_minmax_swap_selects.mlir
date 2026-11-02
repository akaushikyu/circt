// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPfS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPfS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 22 review fix (D3): a compare-exchange written with selects is not
// a plain copy, so idx keeps 32 bits: 2 BRAM (kernel w9r22rv_k21_minmax_swap,
// Vitis 2; round 22: 1).
// CHECK: Total BRAM: 2
#map = affine_map<(d0) -> (-d0 + 1023)>
module {
  func.func @_Z3topPfS_(%arg0: memref<1024xf32>, %arg1: memref<1024xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1023_i32 = arith.constant 1023 : i32
    %c7_i32 = arith.constant 7 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "idx"} : memref<1024xi32>
    affine.for %arg2 = 0 to 1024 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = arith.muli %0, %c7_i32 : i32
      %2 = arith.andi %1, %c1023_i32 : i32
      affine.store %2, %alloca[%arg2] : memref<1024xi32>
    }
    affine.for %arg2 = 0 to 1023 {
      affine.for %arg3 = 0 to #map(%arg2) {
        %0 = affine.load %alloca[%arg3] : memref<1024xi32>
        %1 = affine.load %alloca[%arg3 + 1] : memref<1024xi32>
        %2 = arith.index_cast %0 : i32 to index
        %3 = memref.load %arg0[%2] : memref<1024xf32>
        %4 = arith.index_cast %1 : i32 to index
        %5 = memref.load %arg0[%4] : memref<1024xf32>
        %6 = arith.cmpf ogt, %3, %5 : f32
        %7 = arith.select %6, %1, %0 : i32
        affine.store %7, %alloca[%arg3] : memref<1024xi32>
        %8 = arith.select %6, %0, %1 : i32
        affine.store %8, %alloca[%arg3 + 1] : memref<1024xi32>
      }
    }
    affine.for %arg2 = 0 to 1024 {
      %0 = affine.load %alloca[%arg2] : memref<1024xi32>
      %1 = arith.index_cast %0 : i32 to index
      %2 = memref.load %arg0[%1] : memref<1024xf32>
      affine.store %2, %arg1[%arg2] : memref<1024xf32>
    }
    return
  }
}
