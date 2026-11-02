// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_sS0_PA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA64_sS0_PA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_sS0_PA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA64_sS0_PA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'scheduling.dependences.lane_rmw_one_port=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 21 review (2026-10-25): VITIS_NOTES N154 (b). The lane
// read-modify-write `C_local[w][j] += val` of an hls::vector<ap_fixed<16,5>,
// 64> word with a run-time word AND a run-time lane (kernel
// w9r21rev_r4b_dynword): Vitis II 7, C_local ram_1p 29 (as w9r21p_e1, an
// invariant word, II 3, and w9r21rev_r4a, lane = an unrolled counter, II
// 32). The word's accesses share one port (hls.lane_rmw from
// --split-struct-memrefs). Off (scheduling.dependences.lane_rmw_one_port=
// false): II 3 with a second port, RAM_T2P 57.
// CHECK: 64x1024b -> RAM_1P (x36/port) = 29 BRAM_18K
// CHECK: Total BRAM: 29
// OFF: 64x1024b -> RAM_T2P
// OFF: Total BRAM: 57
// MLIR from the private cgeist of the W9 round 21 review fixes (real headers).
module {
  func.func @_Z3topPA64_sS0_PA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE(%arg0: memref<64x64xi16>, %arg1: memref<64x64xi16>, %arg2: memref<64x64xi16>, %arg3: memref<64xi16>, %arg4: memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>> {hls.interface = [{bundle = "mem3", mode = "m_axi", offset = "slave", port = "C"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c128 = arith.constant 128 : index
    %c0_i64 = arith.constant 0 : i64
    %c0_i16 = arith.constant 0 : i16
    %c1 = arith.constant 1 : index
    %c0 = arith.constant 0 : index
    %c63_i32 = arith.constant 63 : i32
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm64EEixEm", variable = "this"}], hls.preserve, polygeist.varname = "C_local"} : memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg5 = 0 to 64 {
      %3 = affine.load %arg3[%arg5] : memref<64xi16>
      %4 = arith.index_cast %3 : i16 to index
      scf.for %arg6 = %c0 to %4 step %c1 {
        %5 = memref.load %arg0[%arg5, %arg6] : memref<64x64xi16>
        %6 = memref.load %arg1[%arg5, %arg6] : memref<64x64xi16>
        %7 = arith.extsi %6 : i16 to i32
        %8 = arith.andi %7, %c63_i32 : i32
        %9 = arith.index_cast %8 : i32 to index
        %10 = arith.extsi %5 : i16 to i64
        %11 = arith.muli %9, %c128 : index
        %12 = arith.index_cast %11 : index to i64
        %13 = llvm.getelementptr %0[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %14 = arith.index_castui %10 : i64 to index
        %15 = arith.index_cast %14 : index to i32
        %16 = llvm.getelementptr %13[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        %17 = llvm.load %16 : !llvm.ptr -> i16
        %18 = memref.load %arg2[%arg5, %arg6] : memref<64x64xi16>
        %19 = arith.extsi %17 : i16 to i32
        %20 = arith.extsi %18 : i16 to i32
        %21 = arith.addi %19, %20 : i32
        %22 = arith.trunci %21 : i32 to i17
        %23 = arith.extsi %22 : i17 to i64
        %24 = arith.cmpi eq, %23, %c0_i64 : i64
        scf.if %24 {
          llvm.store %c0_i16, %16 {hls.ap_compound_assign} : i16, !llvm.ptr
        }
        %25 = arith.trunci %21 : i32 to i16
        llvm.store %25, %16 {hls.ap_compound_assign} : i16, !llvm.ptr
      }
    }
    %1 = "polygeist.memref2pointer"(%arg4) : (memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>>) -> !llvm.ptr
    %2 = "polygeist.memref2pointer"(%alloca) : (memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg5 = 0 to 64 {
      %3 = arith.muli %arg5, %c128 : index
      %4 = arith.index_cast %3 : index to i64
      %5 = llvm.getelementptr %1[%4] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %6 = llvm.getelementptr %2[%4] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      affine.for %arg6 = 0 to 128 {
        %7 = arith.index_cast %arg6 : index to i32
        %8 = llvm.getelementptr %6[%7] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        %9 = llvm.load %8 : !llvm.ptr -> i8
        %10 = llvm.getelementptr %5[%7] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        llvm.store %9, %10 : i8, !llvm.ptr
      }
    }
    return
  }
}
