// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA16_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA16_7ap_uintILi3EES4_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA16_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA16_7ap_uintILi3EES4_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA16_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA16_7ap_uintILi3EES4_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA16_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA16_7ap_uintILi3EES4_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.narrowing.reaching_store_ranges=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N151 (c): a load from a register array
// (completely partitioned) takes the range of the store that reaches it in its
// block, not the union of every store into the array. Kernel w9r21p_a5_overwrite:
// d[] filled from a full-range input, then overwritten by lut values in the same
// iteration; buf = d[j] x recip(sum): Vitis 1024 x 10 bits (barry_walker lab2
// attention_row_local.data). MLIR from the installed cgeist 5523df29.
// CHECK: 1024x10b -> RAM_T2P
// CHECK: Total BRAM: 1
// OFF: 1024x15b -> RAM_T2P
module {
  func.func @_Z3topPA16_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA16_7ap_uintILi3EES4_(%arg0: memref<64x16xi16>, %arg1: memref<64x16xi3>, %arg2: memref<64x16xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c304_i16 = arith.constant 304 : i16
    %c281474976710656_i56 = arith.constant 281474976710656 : i56
    %c-1_i8 = arith.constant -1 : i8
    %c-52_i8 = arith.constant -52 : i8
    %c-103_i8 = arith.constant -103 : i8
    %c-128_i8 = arith.constant -128 : i8
    %c102_i8 = arith.constant 102 : i8
    %c76_i8 = arith.constant 76 : i8
    %c51_i8 = arith.constant 51 : i8
    %c38_i8 = arith.constant 38 : i8
    %c0_i43 = arith.constant 0 : i43
    %c11_i32 = arith.constant 11 : i32
    %c13_i32 = arith.constant 13 : i32
    %c0_i56 = arith.constant 0 : i56
    %c13_i33 = arith.constant 13 : i33
    %c3_i32 = arith.constant 3 : i32
    %c0_i8 = arith.constant 0 : i8
    %c0_i32 = arith.constant 0 : i32
    %0 = llvm.mlir.undef : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "d"}], hls.preserve, polygeist.varname = "d"} : memref<16xi16>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64x16xi16>
    %alloca_1 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "lut"}], hls.preserve, polygeist.varname = "lut"} : memref<8xi8>
    affine.store %c-1_i8, %alloca_1[0] : memref<8xi8>
    affine.store %c-52_i8, %alloca_1[1] : memref<8xi8>
    affine.store %c-103_i8, %alloca_1[2] : memref<8xi8>
    affine.store %c-128_i8, %alloca_1[3] : memref<8xi8>
    affine.store %c102_i8, %alloca_1[4] : memref<8xi8>
    affine.store %c76_i8, %alloca_1[5] : memref<8xi8>
    affine.store %c51_i8, %alloca_1[6] : memref<8xi8>
    affine.store %c38_i8, %alloca_1[7] : memref<8xi8>
    %1 = affine.for %arg3 = 0 to 64 iter_args(%arg4 = %0) -> (i32) {
      affine.for %arg5 = 0 to 16 {
        %11 = affine.load %arg0[%arg3, %arg5] : memref<64x16xi16>
        affine.store %11, %alloca[%arg5] : memref<16xi16>
      }
      %2 = affine.for %arg5 = 0 to 16 iter_args(%arg6 = %c0_i32) -> (i32) {
        %11 = affine.load %alloca[%arg5] : memref<16xi16>
        %12 = arith.extsi %11 : i16 to i43
        %13 = arith.cmpi sgt, %12, %c0_i43 : i43
        %14 = scf.if %13 -> (i16) {
          %20 = affine.load %arg1[%arg3, %arg5] : memref<64x16xi3>
          %21 = arith.index_castui %20 : i3 to index
          %22 = memref.load %alloca_1[%21] : memref<8xi8>
          %23 = arith.extui %22 : i8 to i32
          %24 = arith.shli %23, %c3_i32 : i32
          %25 = arith.trunci %24 : i32 to i16
          affine.store %25, %alloca[%arg5] : memref<16xi16>
          scf.yield %25 : i16
        } else {
          affine.store %c304_i16, %alloca[%arg5] : memref<16xi16>
          scf.yield %c304_i16 : i16
        }
        %15 = arith.extsi %arg6 : i32 to i33
        %16 = arith.extsi %14 : i16 to i33
        %17 = arith.shli %16, %c13_i33 : i33
        %18 = arith.addi %15, %17 : i33
        %19 = arith.trunci %18 : i33 to i32
        affine.yield %19 : i32
      }
      %3 = arith.extsi %2 : i32 to i56
      %4 = arith.cmpi eq, %3, %c0_i56 : i56
      %5 = arith.extui %4 : i1 to i8
      %6 = arith.cmpi eq, %5, %c0_i8 : i8
      %7 = scf.if %6 -> (i32) {
        %11 = arith.divsi %c281474976710656_i56, %3 : i56
        %12 = arith.trunci %11 : i56 to i32
        scf.yield %12 : i32
      } else {
        %11 = arith.select %4, %c0_i32, %0 : i32
        scf.yield %11 : i32
      }
      %8 = arith.shrsi %7, %c13_i32 : i32
      %9 = arith.trunci %8 : i32 to i16
      %10 = arith.extsi %9 : i16 to i32
      affine.for %arg5 = 0 to 16 {
        %11 = affine.load %alloca[%arg5] : memref<16xi16>
        %12 = arith.extsi %11 : i16 to i32
        %13 = arith.muli %12, %10 : i32
        %14 = arith.shrsi %13, %c11_i32 : i32
        %15 = arith.trunci %14 : i32 to i16
        affine.store %15, %alloca_0[%arg3, %arg5] : memref<64x16xi16>
      }
      affine.yield %2 : i32
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 16 {
        %2 = affine.load %alloca_0[-%arg3 + 63, %arg4] : memref<64x16xi16>
        affine.store %2, %arg2[%arg3, %arg4] : memref<64x16xi16>
      }
    }
    return
  }
}
