// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topP7ap_uintILi64EEPKS0_m --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topP7ap_uintILi64EEPKS0_m math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N54: chain of 2: n_c d4, out_r_c d5, shift registers (depth x 64 < 1024 bits).
// Kernel w9r7_sc_k2 (~/hls-est-work/exp-src/w9r7p/sc_k2.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 4 BRAM_18K.


// CHECK: Total BRAM: 4{{$}}

module {
  llvm.mlir.global internal constant @str2("c2\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str1("c1\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str0("c0\00") {addr_space = 0 : i32}
  func.func @_Z6sc_topP7ap_uintILi64EEPKS0_m(%arg0: memref<?xi64> {hls.interface = [{bundle = "g1", mode = "m_axi", offset = "slave", port = "out"}]}, %arg1: memref<?xi64> {hls.interface = [{bundle = "g0", mode = "m_axi", offset = "slave", port = "in"}]}, %arg2: i64 {hls.interface = [{mode = "s_axilite", port = "n"}]}) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.interface = [{mode = "s_axilite", port = "return"}], hls.orig_name = "sc_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c2"}], polygeist.varname = "c2"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    %alloca_0 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c1"}], polygeist.varname = "c1"} : memref<1xi32>
    %cast_1 = memref.cast %alloca_0 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_0[0] : memref<1xi32>
    %alloca_2 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c0"}], polygeist.varname = "c0"} : memref<1xi32>
    %cast_3 = memref.cast %alloca_2 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_2[0] : memref<1xi32>
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr
    %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_3, %2) : (memref<?xi32>, memref<?xi8>) -> ()
    %3 = llvm.mlir.addressof @str1 : !llvm.ptr
    %4 = "polygeist.pointer2memref"(%3) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_1, %4) : (memref<?xi32>, memref<?xi8>) -> ()
    %5 = llvm.mlir.addressof @str2 : !llvm.ptr
    %6 = "polygeist.pointer2memref"(%5) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast, %6) : (memref<?xi32>, memref<?xi8>) -> ()
    call @_ZL2rdRN3hls6streamI7ap_uintILi64EELi0EEEPKS2_m(%cast_3, %arg1, %arg2) {hls.inline_auto_off = {calls = 1 : i64, size = 9 : i64}} : (memref<?xi32>, memref<?xi64>, i64) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_1, %cast_3) {hls.inline_auto_off = {calls = 2 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast, %cast_1) {hls.inline_auto_off = {calls = 2 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL2wrP7ap_uintILi64EERN3hls6streamIS0_Li0EEEm(%arg0, %cast, %arg2) {hls.inline_auto_off = {calls = 1 : i64, size = 12 : i64}} : (memref<?xi64>, memref<?xi32>, i64) -> ()
    return
  }
  func.func private @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(memref<?xi32>, memref<?xi8>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 64 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL2rdRN3hls6streamI7ap_uintILi64EELi0EEEPKS2_m(%arg0: memref<?xi32>, %arg1: memref<?xi64>, %arg2: i64) attributes {hls.inline_auto_off = {size = 9 : i64}, hls.orig_name = "rd", llvm.linkage = #llvm.linkage<internal>} {
    %0 = arith.index_castui %arg2 : i64 to index
    affine.for %arg3 = 0 to %0 {
      %1 = "polygeist.subindex"(%arg1, %arg3) : (memref<?xi64>, index) -> memref<?xi64>
      func.call @_ZN3hls6streamI7ap_uintILi64EELi0EE5writeERKS2_(%arg0, %1) : (memref<?xi32>, memref<?xi64>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%arg0: memref<?xi32>, %arg1: memref<?xi32>) attributes {hls.inline_auto_off = {size = 24 : i64}, hls.orig_name = "pass", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i66 = arith.constant 1 : i66
    %alloca = memref.alloca() : memref<1xi64>
    %cast = memref.cast %alloca : memref<1xi64> to memref<?xi64>
    %0 = llvm.mlir.undef : i64
    affine.store %0, %alloca[0] : memref<1xi64>
    affine.for %arg2 = 0 to 1024 {
      %1 = func.call @_ZN3hls6streamI7ap_uintILi64EELi0EE4readEv(%arg1) : (memref<?xi32>) -> i64
      %2 = arith.extui %1 : i64 to i66
      %3 = arith.addi %2, %c1_i66 : i66
      %4 = arith.trunci %3 : i66 to i64
      affine.store %4, %alloca[0] : memref<1xi64>
      func.call @_ZN3hls6streamI7ap_uintILi64EELi0EE5writeERKS2_(%arg0, %cast) : (memref<?xi32>, memref<?xi64>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL2wrP7ap_uintILi64EERN3hls6streamIS0_Li0EEEm(%arg0: memref<?xi64>, %arg1: memref<?xi32>, %arg2: i64) attributes {hls.inline_auto_off = {size = 12 : i64}, hls.orig_name = "wr", llvm.linkage = #llvm.linkage<internal>} {
    %0 = arith.index_castui %arg2 : i64 to index
    affine.for %arg3 = 0 to %0 {
      %1 = func.call @_ZN3hls6streamI7ap_uintILi64EELi0EE4readEv(%arg1) : (memref<?xi32>) -> i64
      affine.store %1, %arg0[%arg3] : memref<?xi64>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamI7ap_uintILi64EELi0EE5writeERKS2_(memref<?xi32>, memref<?xi64>) attributes {hls.orig_name = "write", hls.stream_element_bits = 64 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamI7ap_uintILi64EELi0EE4readEv(memref<?xi32>) -> i64 attributes {hls.orig_name = "read", hls.stream_element_bits = 64 : i64, llvm.linkage = #llvm.linkage<external>}
}
