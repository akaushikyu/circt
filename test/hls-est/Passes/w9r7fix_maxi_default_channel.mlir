// RUN: hls-est %s --symbol-privatize=exclude=_Z6mw_topPK7ap_uintILi256EES2_S2_PS0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mw_topPK7ap_uintILi256EES2_S2_PS0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 review fixes (2026-10-20): VITIS_NOTES N56: a port without channel= is on channel 0, so an explicit channel=0 port and two ports without one share one read FIFO (39, as one channel).
// Kernel w9r7rev_mx_chdef (~/hls-est-work/exp-src/w9r7rev/mx_chdef.cpp); MLIR from cgeist c3b (Polygeist branch w9r7-cgeist, W9r7 review fixes) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 39 BRAM_18K.

// CHECK: Total BRAM: 39{{$}}

module {
  func.func @_Z6mw_topPK7ap_uintILi256EES2_S2_PS0_(%arg0: memref<256xi256> {hls.interface = [{bundle = "g0", channel = 0 : i32, mode = "m_axi", offset = "slave", port = "a"}]}, %arg1: memref<256xi256> {hls.interface = [{bundle = "g0", mode = "m_axi", offset = "slave", port = "b"}]}, %arg2: memref<256xi256> {hls.interface = [{bundle = "g0", mode = "m_axi", offset = "slave", port = "c"}]}, %arg3: memref<256xi256> {hls.interface = [{bundle = "g1", mode = "m_axi", offset = "slave", port = "out"}]}) attributes {hls.interface = [{mode = "s_axilite", port = "return"}], hls.orig_name = "mw_top", llvm.linkage = #llvm.linkage<external>} {
    %c7_i32 = arith.constant 7 : i32
    %c255_i32 = arith.constant 255 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "lc"} : memref<256xi256>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<256xi256>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<256xi256>
    affine.for %arg4 = 0 to 256 {
      %0 = affine.load %arg0[%arg4] : memref<256xi256>
      affine.store %0, %alloca_1[%arg4] : memref<256xi256>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg4 = 0 to 256 {
      %0 = affine.load %arg1[%arg4] : memref<256xi256>
      affine.store %0, %alloca_0[%arg4] : memref<256xi256>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg4 = 0 to 256 {
      %0 = affine.load %arg2[%arg4] : memref<256xi256>
      affine.store %0, %alloca[%arg4] : memref<256xi256>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg4 = 0 to 256 {
      %0 = arith.index_cast %arg4 : index to i32
      %1 = affine.load %alloca_1[%arg4] : memref<256xi256>
      %2 = arith.extui %1 : i256 to i257
      %3 = affine.load %alloca_0[-%arg4 + 255] : memref<256xi256>
      %4 = arith.extui %3 : i256 to i257
      %5 = arith.addi %2, %4 : i257
      %6 = arith.muli %0, %c7_i32 : i32
      %7 = arith.andi %6, %c255_i32 : i32
      %8 = arith.index_cast %7 : i32 to index
      %9 = arith.extui %5 : i257 to i258
      %10 = memref.load %alloca[%8] : memref<256xi256>
      %11 = arith.extui %10 : i256 to i258
      %12 = arith.addi %9, %11 : i258
      %13 = arith.trunci %12 : i258 to i256
      affine.store %13, %arg3[%arg4] : memref<256xi256>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
