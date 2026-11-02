// RUN: hls-est %s --symbol-privatize=exclude=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N44 / N51: an array of hls::vector used only through references (reduce_add on the element) is one memory of N x W-bit words; cgeist copies the element byte by byte (an inlined copy assignment), which --split-struct-memrefs reads as one element copy (element-copy-loops), and the unrolled word reads of one element are one read.
// Kernel w9r7_vx_ref (~/hls-est-work/exp-src/w9r7p/vx_ref.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 116 BRAM_18K.

// RUN: hls-est %s --symbol-privatize=exclude=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.structs.element_copy_loops=false' -o /dev/null | FileCheck %s --check-prefix=COPYOFF

// With tool.hls.structs.element_copy_loops=false (COPYOFF) the rule is off; the other W9r7 rules stay on.
// COPYOFF: Total BRAM: 0{{$}}

// CHECK: Total BRAM: 116{{$}}

module {
  func.func @_Z6vx_topPA4_KN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EEES8_PA16_S1_ILi32ELi8ELS2_5ELS3_3ELi0EE(%arg0: memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, %arg1: memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, %arg2: memref<100x16xi32>) attributes {hls.orig_name = "vx_top", llvm.linkage = #llvm.linkage<external>} {
    %c13_i33 = arith.constant 13 : i33
    %c64 = arith.constant 64 : index
    %c100_i32 = arith.constant 100 : i32
    %c0_i32 = arith.constant 0 : i32
    %0 = llvm.mlir.undef : i32
    %alloca = memref.alloca() : memref<i32>
    affine.store %0, %alloca[] : memref<i32>
    %alloca_0 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EE10reduce_addEv", variable = "this"}], hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "k"}], hls.preserve, polygeist.varname = "k"} : memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>
    %alloca_1 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZNK3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm32EE10reduce_addEv", variable = "this"}], hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "q"}], hls.preserve, polygeist.varname = "q"} : memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>
    affine.for %arg3 = 0 to 100 {
      %2 = "polygeist.subindex"(%alloca_1, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %3 = "polygeist.subindex"(%arg0, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
      %4 = "polygeist.subindex"(%alloca_0, %arg3) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
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
    %alloca_2 = memref.alloca() : memref<i16>
    %alloca_3 = memref.alloca() : memref<i16>
    %1 = llvm.mlir.undef : i16
    affine.for %arg3 = 0 to 100 {
      %2 = arith.index_cast %arg3 : index to i32
      affine.for %arg4 = 0 to 16 {
        %3 = arith.index_cast %arg4 : index to i32
        affine.store %c0_i32, %alloca[] : memref<i32>
        %4 = arith.addi %2, %3 : i32
        %5 = arith.remsi %4, %c100_i32 : i32
        %6 = arith.index_cast %5 : i32 to index
        %7 = "polygeist.subindex"(%alloca_1, %6) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
        %8 = "polygeist.subindex"(%alloca_0, %6) : (memref<100x4x!llvm.struct<(struct<(array<32 x i16>)>)>>, index) -> memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>
        %9 = "polygeist.memref2pointer"(%7) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
        %10 = "polygeist.memref2pointer"(%8) : (memref<4x!llvm.struct<(struct<(array<32 x i16>)>)>>) -> !llvm.ptr
        affine.for %arg5 = 0 to 4 {
          affine.store %1, %alloca_2[] : memref<i16>
          %12 = arith.muli %arg5, %c64 : index
          %13 = arith.index_cast %12 : index to i64
          %14 = llvm.getelementptr %9[%13] : (!llvm.ptr, i64) -> !llvm.ptr, i8
          %15 = llvm.load %14 : !llvm.ptr -> i16
          affine.store %15, %alloca_2[] : memref<i16>
          affine.for %arg6 = 1 to 32 {
            %30 = affine.load %alloca_2[] : memref<i16>
            %31 = arith.index_cast %arg6 : index to i32
            %32 = llvm.getelementptr %14[%31] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %33 = llvm.load %32 : !llvm.ptr -> i16
            %34 = arith.extsi %30 : i16 to i32
            %35 = arith.extsi %33 : i16 to i32
            %36 = arith.addi %34, %35 : i32
            %37 = arith.trunci %36 : i32 to i16
            affine.store %37, %alloca_2[] {hls.ap_compound_assign} : memref<i16>
          } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
          %16 = affine.load %alloca_2[] : memref<i16>
          affine.store %1, %alloca_3[] : memref<i16>
          %17 = llvm.getelementptr %10[%13] : (!llvm.ptr, i64) -> !llvm.ptr, i8
          %18 = llvm.load %17 : !llvm.ptr -> i16
          affine.store %18, %alloca_3[] : memref<i16>
          affine.for %arg6 = 1 to 32 {
            %30 = affine.load %alloca_3[] : memref<i16>
            %31 = arith.index_cast %arg6 : index to i32
            %32 = llvm.getelementptr %17[%31] : (!llvm.ptr, i32) -> !llvm.ptr, i16
            %33 = llvm.load %32 : !llvm.ptr -> i16
            %34 = arith.extsi %30 : i16 to i32
            %35 = arith.extsi %33 : i16 to i32
            %36 = arith.addi %34, %35 : i32
            %37 = arith.trunci %36 : i32 to i16
            affine.store %37, %alloca_3[] {hls.ap_compound_assign} : memref<i16>
          } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
          %19 = affine.load %alloca_3[] : memref<i16>
          %20 = arith.extsi %16 : i16 to i32
          %21 = arith.extsi %19 : i16 to i32
          %22 = arith.addi %20, %21 : i32
          %23 = arith.trunci %22 : i32 to i17
          %24 = affine.load %alloca[] : memref<i32>
          %25 = arith.extsi %24 : i32 to i33
          %26 = arith.extsi %23 : i17 to i33
          %27 = arith.shli %26, %c13_i33 : i33
          %28 = arith.addi %25, %27 : i33
          %29 = arith.trunci %28 : i33 to i32
          affine.store %29, %alloca[] {hls.ap_compound_assign} : memref<i32>
        }
        %11 = affine.load %alloca[] : memref<i32>
        affine.store %11, %arg2[%arg3, %arg4] : memref<100x16xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
