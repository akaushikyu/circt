// RUN: hls-est %s --symbol-privatize=exclude=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N51: the left operand of an hls::vector binary operator is taken by value, so that array is disaggregated (its lanes completely partitioned, 64 banks of 200 x 16) while the other stays aggregated (2 x 29); the by-value temporary is registers (temporary-registers).
// Kernel w9r7_vx_swap (~/hls-est-work/exp-src/w9r7p/vx_swap.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 122 BRAM_18K.

// RUN: hls-est %s --symbol-privatize=exclude=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.structs.temporary_registers=false' -o /dev/null | FileCheck %s --check-prefix=TMPOFF

// With tool.hls.structs.temporary_registers=false (TMPOFF) the rule is off; the other W9r7 rules stay on.
// TMPOFF: Total BRAM: 94{{$}}

// CHECK: Total BRAM: 122{{$}}

module {
  func.func @_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE(%arg0: memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, %arg1: memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, %arg2: memref<100x16xi32>) attributes {hls.orig_name = "vx_top", llvm.linkage = #llvm.linkage<external>} {
    %c13_i33 = arith.constant 13 : i33
    %c0_i16 = arith.constant 0 : i16
    %c11_i32 = arith.constant 11 : i32
    %c0_i64 = arith.constant 0 : i64
    %c64 = arith.constant 64 : index
    %c100_i32 = arith.constant 100 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EE10reduce_addEv", variable = "this"}]} : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %alloca_0 = memref.alloca() : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %0 = llvm.mlir.undef : i32
    %alloca_1 = memref.alloca() : memref<i32>
    affine.store %0, %alloca_1[] : memref<i32>
    %alloca_2 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "k"}], hls.preserve, polygeist.varname = "k"} : memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %alloca_3 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZN3hlsmlENS_6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEERKS5_", variable = "this"}], hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "q"}], hls.preserve, polygeist.varname = "q"} : memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>
    affine.for %arg3 = 0 to 100 {
      %6 = "polygeist.subindex"(%alloca_3, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %7 = "polygeist.subindex"(%arg0, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %8 = "polygeist.subindex"(%alloca_2, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %9 = "polygeist.subindex"(%arg1, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %10 = "polygeist.memref2pointer"(%6) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %11 = "polygeist.memref2pointer"(%7) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %12 = "polygeist.memref2pointer"(%8) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      %13 = "polygeist.memref2pointer"(%9) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
      affine.for %arg4 = 0 to 4 {
        %14 = arith.muli %arg4, %c64 : index
        %15 = arith.index_cast %14 : index to i64
        %16 = llvm.getelementptr %10[%15] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %17 = llvm.getelementptr %11[%15] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        affine.for %arg5 = 0 to 64 {
          %20 = arith.index_cast %arg5 : index to i32
          %21 = llvm.getelementptr %17[%20] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          %22 = llvm.load %21 : !llvm.ptr -> i8
          %23 = llvm.getelementptr %16[%20] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          llvm.store %22, %23 : i8, !llvm.ptr
        }
        %18 = llvm.getelementptr %12[%15] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %19 = llvm.getelementptr %13[%15] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        affine.for %arg5 = 0 to 64 {
          %20 = arith.index_cast %arg5 : index to i32
          %21 = llvm.getelementptr %19[%20] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          %22 = llvm.load %21 : !llvm.ptr -> i8
          %23 = llvm.getelementptr %18[%20] : (!llvm.ptr, i32) -> !llvm.ptr, i8
          llvm.store %22, %23 : i8, !llvm.ptr
        }
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %alloca_4 = memref.alloca() : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %alloca_5 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EE6pragmaEv", variable = "this"}], polygeist.varname = "lhs"} : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %alloca_6 = memref.alloca() : memref<i16>
    %1 = "polygeist.memref2pointer"(%alloca_0) : (memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
    %2 = "polygeist.memref2pointer"(%alloca_5) : (memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
    %3 = "polygeist.memref2pointer"(%alloca_4) : (memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
    %4 = llvm.mlir.undef : i16
    %5 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 100 {
      %6 = arith.index_cast %arg3 : index to i32
      affine.for %arg4 = 0 to 16 {
        %7 = arith.index_cast %arg4 : index to i32
        affine.store %c0_i32, %alloca_1[] : memref<i32>
        %8 = arith.addi %6, %7 : i32
        %9 = arith.remsi %8, %c100_i32 : i32
        %10 = arith.index_cast %9 : i32 to index
        %11 = "polygeist.subindex"(%alloca_2, %10) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
        %12 = "polygeist.subindex"(%alloca_3, %10) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
        %13 = "polygeist.memref2pointer"(%11) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
        %14 = "polygeist.memref2pointer"(%12) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
        affine.for %arg5 = 0 to 4 {
          %16 = arith.muli %arg5, %c64 : index
          %17 = arith.index_cast %16 : index to i64
          %18 = llvm.getelementptr %13[%17] : (!llvm.ptr, i64) -> !llvm.ptr, i8
          affine.for %arg6 = 0 to 32 {
            %30 = arith.index_cast %arg6 : index to i32
            %31 = llvm.getelementptr %18[%30] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %32 = llvm.load %31 : !llvm.ptr -> i16
            %33 = llvm.getelementptr %1[%30] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            llvm.store %32, %33 : i16, !llvm.ptr
          }
          %19 = affine.load %alloca_0[0] : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
          affine.store %19, %alloca_5[0] : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
          %20 = llvm.getelementptr %14[%17] : (!llvm.ptr, i64) -> !llvm.ptr, i8
          affine.for %arg6 = 0 to 32 {
            %30 = arith.index_cast %arg6 : index to i32
            %31 = llvm.getelementptr %2[%30] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %32 = llvm.load %31 : !llvm.ptr -> i16
            %33 = arith.extsi %32 : i16 to i32
            %34 = llvm.getelementptr %20[%30] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %35 = llvm.load %34 : !llvm.ptr -> i16
            %36 = arith.extsi %35 : i16 to i32
            %37 = arith.muli %33, %36 : i32
            %38 = arith.extsi %37 : i32 to i64
            %39 = arith.cmpi eq, %38, %c0_i64 : i64
            scf.if %39 {
              llvm.store %c0_i16, %31 {hls.ap_compound_assign} : i16, !llvm.ptr
            }
            %40 = arith.shrsi %37, %c11_i32 : i32
            %41 = arith.trunci %40 : i32 to i16
            llvm.store %41, %31 {hls.ap_compound_assign} : i16, !llvm.ptr
          } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
          affine.for %arg6 = 0 to 32 {
            %30 = arith.index_cast %arg6 : index to i32
            %31 = llvm.getelementptr %2[%30] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %32 = llvm.load %31 : !llvm.ptr -> i16
            %33 = llvm.getelementptr %3[%30] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            llvm.store %32, %33 : i16, !llvm.ptr
          }
          %21 = affine.load %alloca_4[0] : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
          affine.store %21, %alloca[0] : memref<1x!llvm.struct<(struct<(array<32 x i16>)>)>>
          affine.store %4, %alloca_6[] : memref<i16>
          %22 = llvm.load %5 : !llvm.ptr -> i16
          affine.store %22, %alloca_6[] : memref<i16>
          affine.for %arg6 = 1 to 32 {
            %30 = affine.load %alloca_6[] : memref<i16>
            %31 = arith.index_cast %arg6 : index to i32
            %32 = llvm.getelementptr %5[%31] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %33 = llvm.load %32 : !llvm.ptr -> i16
            %34 = arith.extsi %30 : i16 to i32
            %35 = arith.extsi %33 : i16 to i32
            %36 = arith.addi %34, %35 : i32
            %37 = arith.trunci %36 : i32 to i16
            affine.store %37, %alloca_6[] {hls.ap_compound_assign} : memref<i16>
          } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
          %23 = affine.load %alloca_6[] : memref<i16>
          %24 = affine.load %alloca_1[] : memref<i32>
          %25 = arith.extsi %24 : i32 to i33
          %26 = arith.extsi %23 : i16 to i33
          %27 = arith.shli %26, %c13_i33 : i33
          %28 = arith.addi %25, %27 : i33
          %29 = arith.trunci %28 : i33 to i32
          affine.store %29, %alloca_1[] {hls.ap_compound_assign} : memref<i32>
        }
        %15 = affine.load %alloca_1[] : memref<i32>
        affine.store %15, %arg2[%arg3, %arg4] : memref<100x16xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
