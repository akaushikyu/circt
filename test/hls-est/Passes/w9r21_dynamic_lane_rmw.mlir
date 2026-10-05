// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_sPA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA64_sPA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_sPA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA64_sPA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=scheduling.dependences.dynamic_lane_rmw=false --config-set=scheduling.dependences.lane_rmw_one_port=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N154: a read-modify-write of a lane chosen at
// run time in an hls::vector word (C[i][j] += x, j loaded, the word address
// invariant in the loop) is a recurrence through the memory: Vitis II 3, one
// port, ram_1p 64 x 1024 = 29 BRAM (kernel w9r21p_e1_vecrmw; mohammad_zain lab3
// C_local). Off (with scheduling.dependences.lane_rmw_one_port off too, N154 (b)): the word is promoted to a register, II 1, RAM_2P 57. MLIR from
// the installed cgeist 5523df29.
// CHECK: 64x1024b -> RAM_1P (x36/port) = 29 BRAM_18K
// CHECK: Total BRAM: 29
// OFF: 64x1024b -> RAM_2P (x18/port) = 57 BRAM_18K
module {
  func.func @_Z3topPA64_sPA64_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPsPN3hls6vectorIS4_Lm64EEE(%arg0: memref<64x64xi16>, %arg1: memref<64x64xi16>, %arg2: memref<64xi16>, %arg3: memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>> {hls.interface = [{bundle = "mem3", mode = "m_axi", offset = "slave", port = "C"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c128 = arith.constant 128 : index
    %c0_i64 = arith.constant 0 : i64
    %c0_i16 = arith.constant 0 : i16
    %c1 = arith.constant 1 : index
    %c0 = arith.constant 0 : index
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZN3hls6vectorI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELm64EEixEm", variable = "this"}], hls.preserve, polygeist.varname = "C_local"} : memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg4 = 0 to 64 {
      %3 = affine.load %arg2[%arg4] : memref<64xi16>
      %4 = arith.muli %arg4, %c128 : index
      %5 = arith.index_cast %4 : index to i64
      %6 = llvm.getelementptr %0[%5] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %7 = arith.index_cast %3 : i16 to index
      scf.for %arg5 = %c0 to %7 step %c1 {
        %8 = memref.load %arg0[%arg4, %arg5] : memref<64x64xi16>
        %9 = arith.extsi %8 : i16 to i64
        %10 = arith.index_castui %9 : i64 to index
        %11 = arith.index_cast %10 : index to i32
        %12 = llvm.getelementptr %6[%11] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        %13 = llvm.load %12 : !llvm.ptr -> i16
        %14 = memref.load %arg1[%arg4, %arg5] : memref<64x64xi16>
        %15 = arith.extsi %13 : i16 to i32
        %16 = arith.extsi %14 : i16 to i32
        %17 = arith.addi %15, %16 : i32
        %18 = arith.trunci %17 : i32 to i17
        %19 = arith.extsi %18 : i17 to i64
        %20 = arith.cmpi eq, %19, %c0_i64 : i64
        scf.if %20 {
          llvm.store %c0_i16, %12 {hls.ap_compound_assign} : i16, !llvm.ptr
        }
        %21 = arith.trunci %17 : i32 to i16
        llvm.store %21, %12 {hls.ap_compound_assign} : i16, !llvm.ptr
      }
    }
    %1 = "polygeist.memref2pointer"(%arg3) : (memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>>) -> !llvm.ptr
    %2 = "polygeist.memref2pointer"(%alloca) : (memref<64x!llvm.struct<(struct<(array<64 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg4 = 0 to 64 {
      %3 = arith.muli %arg4, %c128 : index
      %4 = arith.index_cast %3 : index to i64
      %5 = llvm.getelementptr %1[%4] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %6 = llvm.getelementptr %2[%4] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      affine.for %arg5 = 0 to 128 {
        %7 = arith.index_cast %arg5 : index to i32
        %8 = llvm.getelementptr %6[%7] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        %9 = llvm.load %8 : !llvm.ptr -> i8
        %10 = llvm.getelementptr %5[%7] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        llvm.store %9, %10 : i8, !llvm.ptr
      }
    }
    return
  }
}
