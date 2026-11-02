// RUN: hls-est %s --symbol-privatize=exclude=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N51: an element copied into a local (`V t = q[..][l]`) disaggregates q.
// Kernel w9r7_vx_copy (~/hls-est-work/exp-src/w9r7p/vx_copy.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 122 BRAM_18K.


// CHECK: Total BRAM: 122{{$}}

module {
  func.func @_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE(%arg0: memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, %arg1: memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, %arg2: memref<100x16xi32>) attributes {hls.orig_name = "vx_top", llvm.linkage = #llvm.linkage<external>} {
    %c13_i33 = arith.constant 13 : i33
    %c64 = arith.constant 64 : index
    %c100_i32 = arith.constant 100 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EE10reduce_addEv", variable = "this"}], polygeist.varname = "t"} : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %0 = llvm.mlir.undef : i32
    %alloca_0 = memref.alloca() : memref<i32>
    affine.store %0, %alloca_0[] : memref<i32>
    %alloca_1 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EE10reduce_addEv", variable = "this"}], hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "k"}], hls.preserve, polygeist.varname = "k"} : memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %alloca_2 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "q"}], hls.preserve, polygeist.varname = "q"} : memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>
    affine.for %arg3 = 0 to 100 {
      %3 = "polygeist.subindex"(%alloca_2, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %4 = "polygeist.subindex"(%arg0, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %5 = "polygeist.subindex"(%alloca_1, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %6 = "polygeist.subindex"(%arg1, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %7 = "polygeist.memref2pointer"(%3) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %8 = "polygeist.memref2pointer"(%4) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %9 = "polygeist.memref2pointer"(%5) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %10 = "polygeist.memref2pointer"(%6) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      affine.for %arg4 = 0 to 4 {
        %11 = arith.muli %arg4, %c64 : index
        %12 = arith.index_cast %11 : index to i64
        %13 = llvm.getelementptr %7[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %14 = llvm.getelementptr %8[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        affine.for %arg5 = 0 to 64 {
          %17 = arith.index_cast %arg5 : index to i32
          %18 = llvm.getelementptr %14[%17] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          %19 = llvm.load %18 : !llvm.ptr -> i8
          %20 = llvm.getelementptr %13[%17] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          llvm.store %19, %20 : i8, !llvm.ptr
        }
        %15 = llvm.getelementptr %9[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %16 = llvm.getelementptr %10[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        affine.for %arg5 = 0 to 64 {
          %17 = arith.index_cast %arg5 : index to i32
          %18 = llvm.getelementptr %16[%17] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          %19 = llvm.load %18 : !llvm.ptr -> i8
          %20 = llvm.getelementptr %15[%17] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          llvm.store %19, %20 : i8, !llvm.ptr
        }
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %alloca_3 = memref.alloca() : memref<i16>
    %alloca_4 = memref.alloca() : memref<i16>
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
    %2 = llvm.mlir.undef : i16
    affine.for %arg3 = 0 to 100 {
      %3 = arith.index_cast %arg3 : index to i32
      affine.for %arg4 = 0 to 16 {
        %4 = arith.index_cast %arg4 : index to i32
        affine.store %c0_i32, %alloca_0[] : memref<i32>
        %5 = arith.addi %3, %4 : i32
        %6 = arith.remsi %5, %c100_i32 : i32
        %7 = arith.index_cast %6 : i32 to index
        %8 = "polygeist.subindex"(%alloca_2, %7) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
        %9 = "polygeist.subindex"(%alloca_1, %7) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
        %10 = "polygeist.memref2pointer"(%8) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
        %11 = "polygeist.memref2pointer"(%9) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
        affine.for %arg5 = 0 to 4 {
          %13 = arith.muli %arg5, %c64 : index
          %14 = arith.index_cast %13 : index to i64
          %15 = llvm.getelementptr %10[%14] : (!llvm.ptr, i64) -> !llvm.ptr, i8
          affine.for %arg6 = 0 to 32 {
            %31 = arith.index_cast %arg6 : index to i32
            %32 = llvm.getelementptr %15[%31] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %33 = llvm.load %32 : !llvm.ptr -> i16
            %34 = llvm.getelementptr %1[%31] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            llvm.store %33, %34 : i16, !llvm.ptr
          }
          affine.store %2, %alloca_3[] : memref<i16>
          %16 = llvm.load %1 : !llvm.ptr -> i16
          affine.store %16, %alloca_3[] : memref<i16>
          affine.for %arg6 = 1 to 32 {
            %31 = affine.load %alloca_3[] : memref<i16>
            %32 = arith.index_cast %arg6 : index to i32
            %33 = llvm.getelementptr %1[%32] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %34 = llvm.load %33 : !llvm.ptr -> i16
            %35 = arith.extsi %31 : i16 to i32
            %36 = arith.extsi %34 : i16 to i32
            %37 = arith.addi %35, %36 : i32
            %38 = arith.trunci %37 : i32 to i16
            affine.store %38, %alloca_3[] {hls.ap_compound_assign} : memref<i16>
          } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
          %17 = affine.load %alloca_3[] : memref<i16>
          affine.store %2, %alloca_4[] : memref<i16>
          %18 = llvm.getelementptr %11[%14] : (!llvm.ptr, i64) -> !llvm.ptr, i8
          %19 = llvm.load %18 : !llvm.ptr -> i16
          affine.store %19, %alloca_4[] : memref<i16>
          affine.for %arg6 = 1 to 32 {
            %31 = affine.load %alloca_4[] : memref<i16>
            %32 = arith.index_cast %arg6 : index to i32
            %33 = llvm.getelementptr %18[%32] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %34 = llvm.load %33 : !llvm.ptr -> i16
            %35 = arith.extsi %31 : i16 to i32
            %36 = arith.extsi %34 : i16 to i32
            %37 = arith.addi %35, %36 : i32
            %38 = arith.trunci %37 : i32 to i16
            affine.store %38, %alloca_4[] {hls.ap_compound_assign} : memref<i16>
          } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
          %20 = affine.load %alloca_4[] : memref<i16>
          %21 = arith.extsi %17 : i16 to i32
          %22 = arith.extsi %20 : i16 to i32
          %23 = arith.addi %21, %22 : i32
          %24 = arith.trunci %23 : i32 to i17
          %25 = affine.load %alloca_0[] : memref<i32>
          %26 = arith.extsi %25 : i32 to i33
          %27 = arith.extsi %24 : i17 to i33
          %28 = arith.shli %27, %c13_i33 : i33
          %29 = arith.addi %26, %28 : i33
          %30 = arith.trunci %29 : i33 to i32
          affine.store %30, %alloca_0[] {hls.ap_compound_assign} : memref<i32>
        }
        %12 = affine.load %alloca_0[] : memref<i32>
        affine.store %12, %arg2[%arg3, %arg4] : memref<100x16xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
