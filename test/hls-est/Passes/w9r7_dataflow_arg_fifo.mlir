// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topP7ap_uintILi64EEPKS0_m --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topP7ap_uintILi64EEPKS0_m math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N54: a dataflow top forwards each scalar / m_axi pointer argument a later process reads through a FIFO <arg>_c, depth = processes on the longest channel path to the reader (+1 when the first process does not read it): n_c d18, out_r_c d19, 64 bits, 4 BRAM each.
// Kernel w9r7_sc_k16 (~/hls-est-work/exp-src/w9r7p/sc_k16.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 12 BRAM_18K.

// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topP7ap_uintILi64EEPKS0_m --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topP7ap_uintILi64EEPKS0_m math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.streams.dataflow_argument_fifos=false' -o /dev/null | FileCheck %s --check-prefix=ARGOFF

// With tool.hls.streams.dataflow_argument_fifos=false (ARGOFF) the rule is off; the other W9r7 rules stay on.
// ARGOFF: Total BRAM: 4{{$}}

// CHECK: Total BRAM: 12{{$}}

module {
  llvm.mlir.global internal constant @str16("c16\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str15("c15\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str14("c14\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str13("c13\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str12("c12\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str11("c11\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str10("c10\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str9("c9\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str8("c8\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str7("c7\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str6("c6\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str5("c5\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str4("c4\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str3("c3\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str2("c2\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str1("c1\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str0("c0\00") {addr_space = 0 : i32}
  func.func @_Z6sc_topP7ap_uintILi64EEPKS0_m(%arg0: memref<?xi64> {hls.interface = [{bundle = "g1", mode = "m_axi", offset = "slave", port = "out"}]}, %arg1: memref<?xi64> {hls.interface = [{bundle = "g0", mode = "m_axi", offset = "slave", port = "in"}]}, %arg2: i64 {hls.interface = [{mode = "s_axilite", port = "n"}]}) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.interface = [{mode = "s_axilite", port = "return"}], hls.orig_name = "sc_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c16"}], polygeist.varname = "c16"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    %alloca_0 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c15"}], polygeist.varname = "c15"} : memref<1xi32>
    %cast_1 = memref.cast %alloca_0 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_0[0] : memref<1xi32>
    %alloca_2 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c14"}], polygeist.varname = "c14"} : memref<1xi32>
    %cast_3 = memref.cast %alloca_2 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_2[0] : memref<1xi32>
    %alloca_4 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c13"}], polygeist.varname = "c13"} : memref<1xi32>
    %cast_5 = memref.cast %alloca_4 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_4[0] : memref<1xi32>
    %alloca_6 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c12"}], polygeist.varname = "c12"} : memref<1xi32>
    %cast_7 = memref.cast %alloca_6 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_6[0] : memref<1xi32>
    %alloca_8 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c11"}], polygeist.varname = "c11"} : memref<1xi32>
    %cast_9 = memref.cast %alloca_8 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_8[0] : memref<1xi32>
    %alloca_10 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c10"}], polygeist.varname = "c10"} : memref<1xi32>
    %cast_11 = memref.cast %alloca_10 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_10[0] : memref<1xi32>
    %alloca_12 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c9"}], polygeist.varname = "c9"} : memref<1xi32>
    %cast_13 = memref.cast %alloca_12 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_12[0] : memref<1xi32>
    %alloca_14 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c8"}], polygeist.varname = "c8"} : memref<1xi32>
    %cast_15 = memref.cast %alloca_14 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_14[0] : memref<1xi32>
    %alloca_16 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c7"}], polygeist.varname = "c7"} : memref<1xi32>
    %cast_17 = memref.cast %alloca_16 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_16[0] : memref<1xi32>
    %alloca_18 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c6"}], polygeist.varname = "c6"} : memref<1xi32>
    %cast_19 = memref.cast %alloca_18 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_18[0] : memref<1xi32>
    %alloca_20 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c5"}], polygeist.varname = "c5"} : memref<1xi32>
    %cast_21 = memref.cast %alloca_20 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_20[0] : memref<1xi32>
    %alloca_22 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c4"}], polygeist.varname = "c4"} : memref<1xi32>
    %cast_23 = memref.cast %alloca_22 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_22[0] : memref<1xi32>
    %alloca_24 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c3"}], polygeist.varname = "c3"} : memref<1xi32>
    %cast_25 = memref.cast %alloca_24 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_24[0] : memref<1xi32>
    %alloca_26 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c2"}], polygeist.varname = "c2"} : memref<1xi32>
    %cast_27 = memref.cast %alloca_26 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_26[0] : memref<1xi32>
    %alloca_28 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c1"}], polygeist.varname = "c1"} : memref<1xi32>
    %cast_29 = memref.cast %alloca_28 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_28[0] : memref<1xi32>
    %alloca_30 = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "c0"}], polygeist.varname = "c0"} : memref<1xi32>
    %cast_31 = memref.cast %alloca_30 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_30[0] : memref<1xi32>
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr
    %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_31, %2) : (memref<?xi32>, memref<?xi8>) -> ()
    %3 = llvm.mlir.addressof @str1 : !llvm.ptr
    %4 = "polygeist.pointer2memref"(%3) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_29, %4) : (memref<?xi32>, memref<?xi8>) -> ()
    %5 = llvm.mlir.addressof @str2 : !llvm.ptr
    %6 = "polygeist.pointer2memref"(%5) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_27, %6) : (memref<?xi32>, memref<?xi8>) -> ()
    %7 = llvm.mlir.addressof @str3 : !llvm.ptr
    %8 = "polygeist.pointer2memref"(%7) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_25, %8) : (memref<?xi32>, memref<?xi8>) -> ()
    %9 = llvm.mlir.addressof @str4 : !llvm.ptr
    %10 = "polygeist.pointer2memref"(%9) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_23, %10) : (memref<?xi32>, memref<?xi8>) -> ()
    %11 = llvm.mlir.addressof @str5 : !llvm.ptr
    %12 = "polygeist.pointer2memref"(%11) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_21, %12) : (memref<?xi32>, memref<?xi8>) -> ()
    %13 = llvm.mlir.addressof @str6 : !llvm.ptr
    %14 = "polygeist.pointer2memref"(%13) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_19, %14) : (memref<?xi32>, memref<?xi8>) -> ()
    %15 = llvm.mlir.addressof @str7 : !llvm.ptr
    %16 = "polygeist.pointer2memref"(%15) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_17, %16) : (memref<?xi32>, memref<?xi8>) -> ()
    %17 = llvm.mlir.addressof @str8 : !llvm.ptr
    %18 = "polygeist.pointer2memref"(%17) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_15, %18) : (memref<?xi32>, memref<?xi8>) -> ()
    %19 = llvm.mlir.addressof @str9 : !llvm.ptr
    %20 = "polygeist.pointer2memref"(%19) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_13, %20) : (memref<?xi32>, memref<?xi8>) -> ()
    %21 = llvm.mlir.addressof @str10 : !llvm.ptr
    %22 = "polygeist.pointer2memref"(%21) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_11, %22) : (memref<?xi32>, memref<?xi8>) -> ()
    %23 = llvm.mlir.addressof @str11 : !llvm.ptr
    %24 = "polygeist.pointer2memref"(%23) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_9, %24) : (memref<?xi32>, memref<?xi8>) -> ()
    %25 = llvm.mlir.addressof @str12 : !llvm.ptr
    %26 = "polygeist.pointer2memref"(%25) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_7, %26) : (memref<?xi32>, memref<?xi8>) -> ()
    %27 = llvm.mlir.addressof @str13 : !llvm.ptr
    %28 = "polygeist.pointer2memref"(%27) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_5, %28) : (memref<?xi32>, memref<?xi8>) -> ()
    %29 = llvm.mlir.addressof @str14 : !llvm.ptr
    %30 = "polygeist.pointer2memref"(%29) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_3, %30) : (memref<?xi32>, memref<?xi8>) -> ()
    %31 = llvm.mlir.addressof @str15 : !llvm.ptr
    %32 = "polygeist.pointer2memref"(%31) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast_1, %32) : (memref<?xi32>, memref<?xi8>) -> ()
    %33 = llvm.mlir.addressof @str16 : !llvm.ptr
    %34 = "polygeist.pointer2memref"(%33) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI7ap_uintILi64EELi0EEC1EPKc(%cast, %34) : (memref<?xi32>, memref<?xi8>) -> ()
    call @_ZL2rdRN3hls6streamI7ap_uintILi64EELi0EEEPKS2_m(%cast_31, %arg1, %arg2) {hls.inline_auto_off = {calls = 1 : i64, size = 9 : i64}} : (memref<?xi32>, memref<?xi64>, i64) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_29, %cast_31) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_27, %cast_29) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_25, %cast_27) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_23, %cast_25) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_21, %cast_23) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_19, %cast_21) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_17, %cast_19) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_15, %cast_17) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_13, %cast_15) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_11, %cast_13) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_9, %cast_11) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_7, %cast_9) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_5, %cast_7) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_3, %cast_5) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast_1, %cast_3) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4passRN3hls6streamI7ap_uintILi64EELi0EEES4_(%cast, %cast_1) {hls.inline_auto_off = {calls = 16 : i64, size = 24 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
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
