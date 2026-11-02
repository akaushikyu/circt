// RUN: hls-est %s --symbol-privatize=exclude=_Z7msv_topPKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEEPS5_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7msv_topPKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEEPS5_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 review fixes (2026-10-20): VITIS_NOTES N56: an m_axi port written only through `s >> c[i]` (an hls::stream read into the port element, class_ece8893 nikhil_p lab3 `mem3`) has no read FIFO: the stream read writes its data argument (StreamFifos.h streamDataAccess); only the read bundle g0 has one (15).
// Kernel w9r7fix_mx_sreadv (~/hls-est-work/exp-src/w9r7fix/mx_sreadv.cpp); MLIR from cgeist c3b (Polygeist branch w9r7-cgeist, W9r7 review fixes) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 15 BRAM_18K.

// CHECK: Total BRAM: 15{{$}}

module {
  func.func @_Z7msv_topPKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEEPS5_(%arg0: memref<64x!llvm.struct<(struct<(array<16 x i16>)>)>> {hls.aggregate = [{compact = "auto", from = "_ZL7producePKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEERNS_6streamIS5_Li0EEE", variable = "this"}], hls.interface = [{bundle = "g0", mode = "m_axi", offset = "slave", port = "a"}]}, %arg1: memref<64x!llvm.struct<(struct<(array<16 x i16>)>)>> {hls.interface = [{bundle = "g1", mode = "m_axi", offset = "slave", port = "c"}]}) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.interface = [{mode = "s_axilite", port = "return"}], hls.orig_name = "msv_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {polygeist.varname = "s"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    call @_ZN3hls6streamINS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEELi4EEC1Ev(%cast) : (memref<?xi32>) -> ()
    call @_ZL7producePKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEERNS_6streamIS5_Li0EEE(%arg0, %cast) {hls.inline_auto_off = {calls = 1 : i64, size = 274 : i64}} : (memref<64x!llvm.struct<(struct<(array<16 x i16>)>)>>, memref<?xi32>) -> ()
    call @_ZL7consumeRN3hls6streamINS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEELi0EEEPS6_(%cast, %arg1) {hls.inline_auto_off = {calls = 1 : i64, size = 9 : i64}} : (memref<?xi32>, memref<64x!llvm.struct<(struct<(array<16 x i16>)>)>>) -> ()
    return
  }
  func.func private @_ZN3hls6streamINS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEELi4EEC1Ev(memref<?xi32>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 256 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL7producePKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEERNS_6streamIS5_Li0EEE(%arg0: memref<64x!llvm.struct<(struct<(array<16 x i16>)>)>> {hls.aggregate = [{compact = "auto", from = "_ZN3hlsplENS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEERKS5_", variable = "this"}]}, %arg1: memref<?xi32>) attributes {hls.inline_auto_off = {size = 274 : i64}, hls.orig_name = "produce", llvm.linkage = #llvm.linkage<internal>} {
    %c32 = arith.constant 32 : index
    %c0_i64 = arith.constant 0 : i64
    %c0_i16 = arith.constant 0 : i16
    %c63_i32 = arith.constant 63 : i32
    %alloca = memref.alloca() : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>> to memref<?x!llvm.struct<(struct<(array<16 x i16>)>)>>
    %alloca_0 = memref.alloca() : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>
    %alloca_1 = memref.alloca() : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>
    %alloca_2 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EE6pragmaEv", variable = "this"}], polygeist.varname = "lhs"} : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>
    %0 = "polygeist.memref2pointer"(%alloca_0) : (memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg0) : (memref<64x!llvm.struct<(struct<(array<16 x i16>)>)>>) -> !llvm.ptr
    %2 = "polygeist.memref2pointer"(%alloca_2) : (memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>) -> !llvm.ptr
    %3 = "polygeist.memref2pointer"(%alloca_1) : (memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 64 {
      %4 = arith.index_cast %arg2 : index to i32
      %5 = arith.muli %arg2, %c32 : index
      %6 = arith.index_cast %5 : index to i64
      %7 = llvm.getelementptr %1[%6] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      affine.for %arg3 = 0 to 16 {
        %15 = arith.index_cast %arg3 : index to i32
        %16 = llvm.getelementptr %7[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        %17 = llvm.load %16 : !llvm.ptr -> i16
        %18 = llvm.getelementptr %0[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        llvm.store %17, %18 : i16, !llvm.ptr
      }
      %8 = arith.subi %c63_i32, %4 : i32
      %9 = arith.index_cast %8 : i32 to index
      %10 = affine.load %alloca_0[0] : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>
      affine.store %10, %alloca_2[0] : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>
      %11 = arith.muli %9, %c32 : index
      %12 = arith.index_cast %11 : index to i64
      %13 = llvm.getelementptr %1[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      affine.for %arg3 = 0 to 16 {
        %15 = arith.index_cast %arg3 : index to i32
        %16 = llvm.getelementptr %2[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        %17 = llvm.load %16 : !llvm.ptr -> i16
        %18 = llvm.getelementptr %13[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        %19 = llvm.load %18 : !llvm.ptr -> i16
        %20 = arith.extsi %17 : i16 to i32
        %21 = arith.extsi %19 : i16 to i32
        %22 = arith.addi %20, %21 : i32
        %23 = arith.trunci %22 : i32 to i17
        %24 = arith.extsi %23 : i17 to i64
        %25 = arith.cmpi eq, %24, %c0_i64 : i64
        scf.if %25 {
          llvm.store %c0_i16, %16 {hls.ap_compound_assign} : i16, !llvm.ptr
        }
        %26 = arith.trunci %22 : i32 to i16
        llvm.store %26, %16 {hls.ap_compound_assign} : i16, !llvm.ptr
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.for %arg3 = 0 to 16 {
        %15 = arith.index_cast %arg3 : index to i32
        %16 = llvm.getelementptr %2[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        %17 = llvm.load %16 : !llvm.ptr -> i16
        %18 = llvm.getelementptr %3[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        llvm.store %17, %18 : i16, !llvm.ptr
      }
      %14 = affine.load %alloca_1[0] : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>
      affine.store %14, %alloca[0] : memref<1x!llvm.struct<(struct<(array<16 x i16>)>)>>
      func.call @_ZN3hls6streamINS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEELi0EElsERKS6_(%arg1, %cast) : (memref<?xi32>, memref<?x!llvm.struct<(struct<(array<16 x i16>)>)>>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL7consumeRN3hls6streamINS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEELi0EEEPS6_(%arg0: memref<?xi32>, %arg1: memref<64x!llvm.struct<(struct<(array<16 x i16>)>)>>) attributes {hls.inline_auto_off = {size = 9 : i64}, hls.orig_name = "consume", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg2 = 0 to 64 {
      %0 = "polygeist.subindex"(%arg1, %arg2) : (memref<64x!llvm.struct<(struct<(array<16 x i16>)>)>>, index) -> memref<?x!llvm.struct<(struct<(array<16 x i16>)>)>>
      func.call @_ZN3hls6streamINS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEELi0EErsERS6_(%arg0, %0) : (memref<?xi32>, memref<?x!llvm.struct<(struct<(array<16 x i16>)>)>>) -> ()
    }
    return
  }
  func.func private @_ZN3hls6streamINS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEELi0EElsERKS6_(memref<?xi32>, memref<?x!llvm.struct<(struct<(array<16 x i16>)>)>>) attributes {hls.orig_name = "operator<<", hls.stream_element_bits = 256 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamINS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm16EEELi0EErsERS6_(memref<?xi32>, memref<?x!llvm.struct<(struct<(array<16 x i16>)>)>>) attributes {hls.orig_name = "operator>>", hls.stream_element_bits = 256 : i64, llvm.linkage = #llvm.linkage<external>}
}
