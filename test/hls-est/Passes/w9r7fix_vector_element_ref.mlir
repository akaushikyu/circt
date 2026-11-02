// RUN: hls-est %s --symbol-privatize=exclude=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 review fixes (2026-10-20): VITIS_NOTES N51: elements of k passed by const reference to a kept function: k stays aggregated (100 x 4 words of 512 bits; Vitis k_0 / k_1, cyclic 2, 2 x 29); q (by value) is disaggregated (64 x 1). hls-est now aggregates k (it was excluded and priced 0), but leaves it one RAM_1P of 15: the element view passed to the kept call stops memory banking, and the reads inside the callee count one port (OPEN_ISSUES O82); 79 against Vitis 122.
// Kernel w9r7rev_vx_fnval (~/hls-est-work/exp-src/w9r7rev/vx_fnval.cpp); MLIR from cgeist c3b (Polygeist branch w9r7-cgeist, W9r7 review fixes) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 122 BRAM_18K.

// CHECK: Total BRAM: 79{{$}}

module {
  func.func @_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE(%arg0: memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, %arg1: memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, %arg2: memref<100x16xi32>) attributes {hls.orig_name = "vx_top", llvm.linkage = #llvm.linkage<external>} {
    %c64 = arith.constant 64 : index
    %c100_i32 = arith.constant 100 : i32
    %c0_i32 = arith.constant 0 : i32
    %0 = llvm.mlir.undef : i32
    %alloca = memref.alloca() : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %alloca_0 = memref.alloca() : memref<i32>
    affine.store %0, %alloca_0[] : memref<i32>
    %alloca_1 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZL4sumrRKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEE", variable = "this"}], hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "k"}], hls.preserve, polygeist.varname = "k"} : memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %alloca_2 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "q"}], hls.preserve, polygeist.varname = "q"} : memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>
    affine.for %arg3 = 0 to 100 {
      %2 = "polygeist.subindex"(%alloca_2, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %3 = "polygeist.subindex"(%arg0, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %4 = "polygeist.subindex"(%alloca_1, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %5 = "polygeist.subindex"(%arg1, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %6 = "polygeist.memref2pointer"(%2) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %7 = "polygeist.memref2pointer"(%3) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %8 = "polygeist.memref2pointer"(%4) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %9 = "polygeist.memref2pointer"(%5) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      affine.for %arg4 = 0 to 4 {
        %10 = arith.muli %arg4, %c64 : index
        %11 = arith.index_cast %10 : index to i64
        %12 = llvm.getelementptr %6[%11] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %13 = llvm.getelementptr %7[%11] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        affine.for %arg5 = 0 to 64 {
          %16 = arith.index_cast %arg5 : index to i32
          %17 = llvm.getelementptr %13[%16] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          %18 = llvm.load %17 : !llvm.ptr -> i8
          %19 = llvm.getelementptr %12[%16] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          llvm.store %18, %19 : i8, !llvm.ptr
        }
        %14 = llvm.getelementptr %8[%11] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %15 = llvm.getelementptr %9[%11] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        affine.for %arg5 = 0 to 64 {
          %16 = arith.index_cast %arg5 : index to i32
          %17 = llvm.getelementptr %15[%16] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          %18 = llvm.load %17 : !llvm.ptr -> i8
          %19 = llvm.getelementptr %14[%16] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          llvm.store %18, %19 : i8, !llvm.ptr
        }
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 100 {
      %2 = arith.index_cast %arg3 : index to i32
      affine.for %arg4 = 0 to 16 {
        %3 = arith.index_cast %arg4 : index to i32
        affine.store %c0_i32, %alloca_0[] : memref<i32>
        %4 = arith.addi %2, %3 : i32
        %5 = arith.remsi %4, %c100_i32 : i32
        %6 = arith.index_cast %5 : i32 to index
        %7 = "polygeist.subindex"(%alloca_2, %6) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
        %8 = "polygeist.subindex"(%alloca_1, %6) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
        %9 = "polygeist.memref2pointer"(%7) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
        affine.for %arg5 = 0 to 4 {
          %11 = arith.muli %arg5, %c64 : index
          %12 = arith.index_cast %11 : index to i64
          %13 = llvm.getelementptr %9[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
          affine.for %arg6 = 0 to 32 {
            %26 = arith.index_cast %arg6 : index to i32
            %27 = llvm.getelementptr %13[%26] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %28 = llvm.load %27 : !llvm.ptr -> i16
            %29 = llvm.getelementptr %1[%26] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            llvm.store %28, %29 : i16, !llvm.ptr
          }
          %14 = affine.load %alloca[0] : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
          %15 = func.call @_ZL4sumvN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEE(%14) {hls.inline_auto_off = {calls = 4 : i64, size = 315 : i64}} : (!llvm.struct<(struct<(array<32 x i16>)>)>) -> i32
          %16 = "polygeist.subindex"(%8, %arg5) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<?x!llvm.struct<(struct<(array<32 x i16>)>)>>
          %17 = func.call @_ZL4sumrRKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEE(%16) {hls.inline_auto_off = {calls = 4 : i64, size = 315 : i64}} : (memref<?x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> i32
          %18 = arith.extsi %15 : i32 to i33
          %19 = arith.extsi %17 : i32 to i33
          %20 = arith.addi %18, %19 : i33
          %21 = affine.load %alloca_0[] : memref<i32>
          %22 = arith.extsi %21 : i32 to i34
          %23 = arith.extsi %20 : i33 to i34
          %24 = arith.addi %22, %23 : i34
          %25 = arith.trunci %24 : i34 to i32
          affine.store %25, %alloca_0[] {hls.ap_compound_assign} : memref<i32>
        }
        %10 = affine.load %alloca_0[] : memref<i32>
        affine.store %10, %arg2[%arg3, %arg4] : memref<100x16xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func private @_ZL4sumvN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEE(%arg0: !llvm.struct<(struct<(array<32 x i16>)>)>) -> i32 attributes {hls.inline_auto_off = {size = 315 : i64}, hls.orig_name = "sumv", llvm.linkage = #llvm.linkage<internal>} {
    %c13_i32 = arith.constant 13 : i32
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EE10reduce_addEv", variable = "this"}], polygeist.varname = "v"} : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
    affine.store %arg0, %alloca[0] : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %0 = llvm.mlir.undef : i16
    %alloca_0 = memref.alloca() : memref<i16>
    affine.store %0, %alloca_0[] : memref<i16>
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
    %2 = llvm.load %1 : !llvm.ptr -> i16
    affine.store %2, %alloca_0[] : memref<i16>
    affine.for %arg1 = 1 to 32 {
      %6 = affine.load %alloca_0[] : memref<i16>
      %7 = arith.index_cast %arg1 : index to i32
      %8 = llvm.getelementptr %1[%7] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %9 = llvm.load %8 : !llvm.ptr -> i16
      %10 = arith.extsi %6 : i16 to i32
      %11 = arith.extsi %9 : i16 to i32
      %12 = arith.addi %10, %11 : i32
      %13 = arith.trunci %12 : i32 to i16
      affine.store %13, %alloca_0[] {hls.ap_compound_assign} : memref<i16>
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    %3 = affine.load %alloca_0[] : memref<i16>
    %4 = arith.extsi %3 : i16 to i32
    %5 = arith.shli %4, %c13_i32 : i32
    return %5 : i32
  }
  func.func private @_ZL4sumrRKN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEE(%arg0: memref<?x!llvm.struct<(struct<(array<32 x i16>)>)>> {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EE10reduce_addEv", variable = "this"}]}) -> i32 attributes {hls.inline_auto_off = {size = 315 : i64}, hls.orig_name = "sumr", llvm.linkage = #llvm.linkage<internal>} {
    %c13_i32 = arith.constant 13 : i32
    %0 = llvm.mlir.undef : i16
    %alloca = memref.alloca() : memref<i16>
    affine.store %0, %alloca[] : memref<i16>
    %1 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
    %2 = llvm.load %1 : !llvm.ptr -> i16
    affine.store %2, %alloca[] : memref<i16>
    affine.for %arg1 = 1 to 32 {
      %6 = affine.load %alloca[] : memref<i16>
      %7 = arith.index_cast %arg1 : index to i32
      %8 = llvm.getelementptr %1[%7] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %9 = llvm.load %8 : !llvm.ptr -> i16
      %10 = arith.extsi %6 : i16 to i32
      %11 = arith.extsi %9 : i16 to i32
      %12 = arith.addi %10, %11 : i32
      %13 = arith.trunci %12 : i32 to i16
      affine.store %13, %alloca[] {hls.ap_compound_assign} : memref<i16>
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    %3 = affine.load %alloca[] : memref<i16>
    %4 = arith.extsi %3 : i16 to i32
    %5 = arith.shli %4, %c13_i32 : i32
    return %5 : i32
  }
}
