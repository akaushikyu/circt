// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s

// VITIS_NOTES N94, kernel w9r13p_ci_df (Vitis 2025.1 td=off: 32): ci_io with a
// dataflow top; buf is a PIPO channel of 16 banks, 2 x 1 each.
// CHECK: Total BRAM: 32

module {
  func.func @_Z3topPKiPi(%arg0: memref<128xi32>, %arg1: memref<128xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<128x16xi32>
    call @_ZL4prodPKiPA16_i(%arg0, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 70 : i64}} : (memref<128xi32>, memref<128x16xi32>) -> ()
    call @_ZL4consPA16_iPi(%alloca, %arg1) {hls.inline_auto_off = {calls = 1 : i64, size = 70 : i64}} : (memref<128x16xi32>, memref<128xi32>) -> ()
    return
  }
  func.func private @_ZL4prodPKiPA16_i(%arg0: memref<128xi32>, %arg1: memref<128x16xi32>) attributes {hls.inline_auto_off = {size = 70 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg2 = 0 to 128 {
      affine.for %arg3 = 0 to 16 {
        %0 = arith.index_cast %arg3 : index to i32
        %1 = affine.load %arg0[%arg2] : memref<128xi32>
        %2 = arith.addi %1, %0 : i32
        affine.store %2, %arg1[%arg2, %arg3] : memref<128x16xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL4consPA16_iPi(%arg0: memref<128x16xi32>, %arg1: memref<128xi32>) attributes {hls.inline_auto_off = {size = 70 : i64}, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    affine.for %arg2 = 0 to 128 {
      %0 = affine.for %arg3 = 0 to 16 iter_args(%arg4 = %c0_i32) -> (i32) {
        %1 = arith.index_cast %arg3 : index to i32
        %2 = affine.load %arg0[%arg2, %arg3] : memref<128x16xi32>
        %3 = arith.addi %1, %c1_i32 : i32
        %4 = arith.muli %2, %3 : i32
        %5 = arith.addi %arg4, %4 : i32
        affine.yield %5 : i32
      }
      affine.store %0, %arg1[%arg2] : memref<128xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
