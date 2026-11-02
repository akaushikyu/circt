// RUN: hls-est %s --symbol-privatize=exclude=_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): OPEN_ISSUES O78: an array_partition on a member path (`variable=r.data complete`, cgeist records the member's own dim) applies to the member memory of a struct with one array member, its dim after the variable's one-element dimension: 128 registers, 0 BRAM (barry_walker lab_2 Q_row_local.data).
// Kernel w9r7i_mp (~/hls-est-work/exp-src/w9r7i/mp.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 0 BRAM_18K.

// RUN: hls-est %s --symbol-privatize=exclude=_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.structs.member_partitions=false' -o /dev/null | FileCheck %s --check-prefix=MEMBEROFF

// With tool.hls.structs.member_partitions=false (MEMBEROFF) the rule is off; the other W9r7 rules stay on.
// MEMBEROFF: Total BRAM: 1{{$}}

// CHECK: Total BRAM: 0{{$}}

module {
  func.func @_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi(%arg0: memref<128xi16>, %arg1: memref<128xi16>, %arg2: memref<128xi32>) attributes {hls.orig_name = "mp_top", llvm.linkage = #llvm.linkage<external>} {
    %c127_i32 = arith.constant 127 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "r.data"}], polygeist.varname = "r"} : memref<1x!llvm.struct<(array<128 x i16>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<128 x i16>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 128 {
      %1 = arith.index_cast %arg3 : index to i32
      %2 = affine.load %arg0[%arg3] : memref<128xi16>
      %3 = llvm.getelementptr %0[%1] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      llvm.store %2, %3 : i16, !llvm.ptr
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 128 {
      %1 = affine.load %arg2[%arg3] : memref<128xi32>
      %2 = arith.andi %1, %c127_i32 : i32
      %3 = arith.addi %1, %c1_i32 : i32
      %4 = arith.andi %3, %c127_i32 : i32
      %5 = llvm.getelementptr %0[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %6 = llvm.load %5 : !llvm.ptr -> i16
      %7 = llvm.getelementptr %0[%4] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %8 = llvm.load %7 : !llvm.ptr -> i16
      %9 = arith.extsi %6 : i16 to i32
      %10 = arith.extsi %8 : i16 to i32
      %11 = arith.addi %9, %10 : i32
      %12 = arith.trunci %11 : i32 to i16
      affine.store %12, %arg1[%arg3] : memref<128xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
