// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA8_A4_hPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA8_A4_hPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA8_A4_hPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA8_A4_hPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.narrowing.accumulation_ranges=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N159: acc[i] = 0, then 8 pipelined
// iterations of acc[i] += s with s in [0, 1000]: the element ranges over
// 8 x 1020 (the clamp's select range): 13 bits (Vitis 512 x 13, kernel
// w9r21p_j1_accT8; Analog-CIM optimized output_buf, memory form). MLIR from the
// installed cgeist 5523df29.
// Since W9r22-impl (VITIS_NOTES N166 (a)) the init store dies and acc[i] is
// stored once after the promoted loop: one port, RAM_1P (was RAM_T2P, and
// 2 BRAM at 32 bits with the key off).
// CHECK: 512x13b -> RAM_1P
// CHECK: Total BRAM: 1
// OFF: 512x32b -> RAM_1P
// OFF: Total BRAM: 1
module {
  func.func @_Z3topPA8_A4_hPi(%arg0: memref<512x8x4xi8>, %arg1: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-6_i8 = arith.constant -6 : i8
    %c250_i32 = arith.constant 250 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<512xi32>
    affine.for %arg2 = 0 to 512 {
      affine.store %c0_i32, %alloca[%arg2] : memref<512xi32>
      %0 = affine.for %arg3 = 0 to 8 iter_args(%arg4 = %c0_i32) -> (i32) {
        %1 = affine.for %arg5 = 0 to 4 iter_args(%arg6 = %c0_i32) -> (i32) {
          %3 = affine.load %arg0[%arg2, %arg3, %arg5] : memref<512x8x4xi8>
          %4 = arith.extui %3 : i8 to i32
          %5 = arith.cmpi sgt, %4, %c250_i32 : i32
          %6 = arith.select %5, %c-6_i8, %3 : i8
          %7 = arith.extui %6 : i8 to i32
          %8 = arith.addi %arg6, %7 : i32
          affine.yield %8 : i32
        }
        %2 = arith.addi %arg4, %1 : i32
        affine.store %2, %alloca[%arg2] : memref<512xi32>
        affine.yield %2 : i32
      } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %alloca[-%arg2 + 511] : memref<512xi32>
      affine.store %0, %arg1[%arg2] : memref<512xi32>
    }
    return
  }
}
