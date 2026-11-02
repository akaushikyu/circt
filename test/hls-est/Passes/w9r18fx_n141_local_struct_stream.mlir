// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS4_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPKiPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS4_ --bram-debug -o /dev/null 2>&1 | FileCheck %s

// W9 round 18 review fixes, VITIS_NOTES N141 / N58: the stream of lit w9r18fx_n141_static_struct_stream
// declared without `static` (kernel w9r18fx_k9loc, Vitis 2025.1 td=off): s_U 64 x 81 bits = 5 BRAM, the
// packed members (bool 1 bit), not the 96-bit C storage. MLIR from cgeist 2b5e2add (installed), --shim real.
// CHECK: fifo: 1 x depth 64 (pragma) x 81 bits (cgeist hls.stream_element_bits) -> 5 each
// CHECK: Total BRAM: 5{{$}}

module {
  llvm.mlir.global internal constant @str0("s\00") {addr_space = 0 : i32}
  func.func @_Z3topPKiPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS4_(%arg0: memref<256xi32>, %arg1: memref<256xi16>, %arg2: memref<256xi16>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.stream = [{depth = 64 : i32, type = "fifo", variable = "s"}], polygeist.varname = "s"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr
    %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI3PktLi0EEC1EPKc(%cast, %2) : (memref<?xi32>, memref<?xi8>) -> ()
    call @_ZL4prodPKiPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EERN3hls6streamI3PktLi0EEE(%arg0, %arg1, %cast) {hls.inline_auto_off = {calls = 1 : i64, size = 21 : i64}} : (memref<256xi32>, memref<256xi16>, memref<?xi32>) -> ()
    call @_ZL4consRN3hls6streamI3PktLi0EEEP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EE(%cast, %arg2) {hls.inline_auto_off = {calls = 1 : i64, size = 42 : i64}} : (memref<?xi32>, memref<256xi16>) -> ()
    return
  }
  func.func private @_ZN3hls6streamI3PktLi0EEC1EPKc(memref<?xi32>, memref<?xi8>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 81 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL4prodPKiPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EERN3hls6streamI3PktLi0EEE(%arg0: memref<256xi32>, %arg1: memref<256xi16>, %arg2: memref<?xi32>) attributes {hls.inline_auto_off = {size = 21 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    %c15_i32 = arith.constant 15 : i32
    %alloca = memref.alloca() {polygeist.varname = "p"} : memref<1x!llvm.struct<(i32, i32, i16, i8)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(i32, i32, i16, i8)>> to memref<?x!llvm.struct<(i32, i32, i16, i8)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(i32, i32, i16, i8)>>) -> !llvm.ptr
    %1 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i32, i16, i8)>
    %2 = llvm.getelementptr %0[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i32, i16, i8)>
    %3 = llvm.getelementptr %0[0, 3] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i32, i16, i8)>
    affine.for %arg3 = 0 to 256 {
      %4 = arith.index_cast %arg3 : index to i32
      %5 = affine.load %arg0[%arg3] : memref<256xi32>
      llvm.store %5, %0 : i32, !llvm.ptr
      llvm.store %4, %1 : i32, !llvm.ptr
      %6 = affine.load %arg1[%arg3] : memref<256xi16>
      llvm.store %6, %2 : i16, !llvm.ptr
      %7 = arith.andi %4, %c15_i32 : i32
      %8 = arith.cmpi eq, %7, %c15_i32 : i32
      %9 = arith.extui %8 : i1 to i8
      llvm.store %9, %3 : i8, !llvm.ptr
      func.call @_ZN3hls6streamI3PktLi0EE5writeERKS1_(%arg2, %cast) : (memref<?xi32>, memref<?x!llvm.struct<(i32, i32, i16, i8)>>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL4consRN3hls6streamI3PktLi0EEEP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EE(%arg0: memref<?xi32>, %arg1: memref<256xi16>) attributes {hls.inline_auto_off = {size = 42 : i64}, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c11_i32 = arith.constant 11 : i32
    %c0_i8 = arith.constant 0 : i8
    %alloca = memref.alloca() : memref<1x!llvm.struct<(i32, i32, i16, i8)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(i32, i32, i16, i8)>>) -> !llvm.ptr
    %1 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i32, i16, i8)>
    %2 = llvm.getelementptr %0[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i32, i16, i8)>
    %3 = llvm.getelementptr %0[0, 3] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i32, i16, i8)>
    affine.for %arg2 = 0 to 256 {
      %4 = func.call @_ZN3hls6streamI3PktLi0EE4readEv(%arg0) : (memref<?xi32>) -> !llvm.struct<(i32, i32, i16, i8)>
      affine.store %4, %alloca[0] : memref<1x!llvm.struct<(i32, i32, i16, i8)>>
      %5 = llvm.load %0 : !llvm.ptr -> i32
      %6 = llvm.load %1 : !llvm.ptr -> i32
      %7 = llvm.load %2 : !llvm.ptr -> i16
      %8 = llvm.load %3 : !llvm.ptr -> i8
      %9 = arith.cmpi ne, %8, %c0_i8 : i8
      %10 = scf.if %9 -> (i16) {
        %11 = arith.shli %5, %c11_i32 : i32
        %12 = arith.trunci %11 : i32 to i16
        %13 = arith.extsi %7 : i16 to i32
        %14 = arith.extsi %12 : i16 to i32
        %15 = arith.addi %13, %14 : i32
        %16 = arith.trunci %15 : i32 to i16
        scf.yield %16 : i16
      } else {
        %11 = arith.shli %6, %c11_i32 : i32
        %12 = arith.trunci %11 : i32 to i16
        %13 = arith.extsi %7 : i16 to i32
        %14 = arith.extsi %12 : i16 to i32
        %15 = arith.addi %13, %14 : i32
        %16 = arith.trunci %15 : i32 to i16
        scf.yield %16 : i16
      }
      affine.store %10, %arg1[%arg2] : memref<256xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamI3PktLi0EE5writeERKS1_(memref<?xi32>, memref<?x!llvm.struct<(i32, i32, i16, i8)>>) attributes {hls.orig_name = "write", hls.stream_element_bits = 81 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamI3PktLi0EE4readEv(memref<?xi32>) -> !llvm.struct<(i32, i32, i16, i8)> attributes {hls.orig_name = "read", hls.stream_element_bits = 81 : i64, llvm.linkage = #llvm.linkage<external>}
}
