// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPfS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPfS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPfS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPfS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.narrowing.copies_close_ranges=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N167. idx[i] = i for i < 1024, then a
// bubble sort swaps idx[j] and idx[j + 1] (std::swap: the stored values are
// plain copies of loaded elements). Vitis closes the range over the copies:
// 1024 x 10, 1 BRAM (kernel w9r22p_c5_idx_swap). With the key off a copy of
// the array's own loads is full range: 32 bits, 2.
// CHECK: 1024x10b
// CHECK: Total BRAM: 1
// OFF: 1024x32b
// OFF: Total BRAM: 2
#map = affine_map<(d0) -> (-d0 + 1023)>
module {
  func.func @_Z3topPfS_(%arg0: memref<1024xf32>, %arg1: memref<1024xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 1.024000e+03 : f32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "idx"} : memref<1024xi32>
    affine.for %arg2 = 0 to 1024 {
      %0 = arith.index_cast %arg2 : index to i32
      affine.store %0, %alloca[%arg2] : memref<1024xi32>
    }
    affine.for %arg2 = 0 to 1023 {
      affine.for %arg3 = 0 to #map(%arg2) {
        %0 = affine.load %arg0[%arg3] : memref<1024xf32>
        %1 = affine.load %arg0[%arg3 + 1] : memref<1024xf32>
        %2 = arith.cmpf ogt, %0, %1 : f32
        scf.if %2 {
          %3 = affine.load %arg0[%arg3] : memref<1024xf32>
          %4 = affine.load %arg0[%arg3 + 1] : memref<1024xf32>
          affine.store %4, %arg0[%arg3] : memref<1024xf32>
          affine.store %3, %arg0[%arg3 + 1] : memref<1024xf32>
          %5 = affine.load %alloca[%arg3] : memref<1024xi32>
          %6 = affine.load %alloca[%arg3 + 1] : memref<1024xi32>
          affine.store %6, %alloca[%arg3] : memref<1024xi32>
          affine.store %5, %alloca[%arg3 + 1] : memref<1024xi32>
        }
      }
    }
    affine.for %arg2 = 0 to 1024 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = affine.load %alloca[%arg2] : memref<1024xi32>
      %2 = arith.index_cast %1 : i32 to index
      %3 = affine.load %arg0[%arg2] : memref<1024xf32>
      %4 = arith.mulf %3, %cst : f32
      %5 = arith.addi %0, %c1_i32 : i32
      %6 = arith.sitofp %5 : i32 to f32
      %7 = arith.divf %4, %6 : f32
      memref.store %7, %arg1[%2] : memref<1024xf32>
    }
    return
  }
}
