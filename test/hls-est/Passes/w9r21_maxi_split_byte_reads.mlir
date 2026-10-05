// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi128EEPS_ILi3EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topP7ap_uintILi128EEPS_ILi3EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r21 (2026-10-24): VITIS_NOTES N152 counter-cases. Kernel w9r21p_c5_oddslice
// (`out[i].range(5, 3) = in[i]`: byte 0 partly kept) reads the word: Vitis
// mem2_m_axi 8 (read FIFO 256 x 128). MLIR from the installed cgeist 5523df29.
// CHECK: m_axi.adapter bundle=mem2{{.*}} bram=8 (read FIFO
// CHECK: Total BRAM: 10
module {
  func.func @_Z3topP7ap_uintILi128EEPS_ILi3EE(%arg0: memref<64xi128> {hls.interface = [{bundle = "mem2", mode = "m_axi", offset = "slave", port = "out"}]}, %arg1: memref<64xi3> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "in"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-57_i128 = arith.constant -57 : i128
    %c7_i128 = arith.constant 7 : i128
    %c3_i128 = arith.constant 3 : i128
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %arg1[%arg2] : memref<64xi3>
      %1 = arith.extui %0 : i3 to i128
      %2 = affine.load %arg0[%arg2] : memref<64xi128>
      %3 = arith.andi %1, %c7_i128 : i128
      %4 = arith.andi %2, %c-57_i128 : i128
      %5 = arith.shli %3, %c3_i128 : i128
      %6 = arith.ori %4, %5 : i128
      affine.store %6, %arg0[%arg2] : memref<64xi128>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
