// RUN: hls-est %s --symbol-privatize=exclude=_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.structs.member_partitions=false' -o /dev/null | FileCheck %s --check-prefix=MEMBEROFF
// W9r7 review fixes (2026-10-20): OPEN_ISSUES O78: an array_partition on r.data of a struct with two array members applies to that member (cgeist records member_path): r.data registers, r.aux one RAM (1).
// Kernel w9r7rev_mp_two (~/hls-est-work/exp-src/w9r7rev/mp_two.cpp); MLIR from cgeist c3b (Polygeist branch w9r7-cgeist, W9r7 review fixes) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 1 BRAM_18K.
// With tool.hls.structs.member_partitions=false (MEMBEROFF) the rule is off.
// MEMBEROFF: Total BRAM: 2{{$}}

// CHECK: Total BRAM: 1{{$}}

module {
  func.func @_Z6mp_topPK8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi(%arg0: memref<128xi16>, %arg1: memref<128xi16>, %arg2: memref<128xi32>) attributes {hls.orig_name = "mp_top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c127_i32 = arith.constant 127 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", member_path = [0 : i32], variable = "r.data"}], polygeist.varname = "r"} : memref<1x!llvm.struct<(array<128 x i16>, array<128 x i16>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<128 x i16>, array<128 x i16>)>>) -> !llvm.ptr
    %1 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<128 x i16>, array<128 x i16>)>
    affine.for %arg3 = 0 to 128 {
      %2 = arith.index_cast %arg3 : index to i32
      %3 = affine.load %arg0[%arg3] : memref<128xi16>
      %4 = llvm.getelementptr %0[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      llvm.store %3, %4 : i16, !llvm.ptr
      %5 = arith.muli %2, %c3_i32 : i32
      %6 = arith.andi %5, %c127_i32 : i32
      %7 = arith.index_cast %6 : i32 to index
      %8 = memref.load %arg0[%7] : memref<128xi16>
      %9 = llvm.getelementptr %1[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      llvm.store %8, %9 : i16, !llvm.ptr
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 128 {
      %2 = affine.load %arg2[%arg3] : memref<128xi32>
      %3 = arith.andi %2, %c127_i32 : i32
      %4 = arith.addi %2, %c1_i32 : i32
      %5 = arith.andi %4, %c127_i32 : i32
      %6 = llvm.getelementptr %0[%3] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %7 = llvm.load %6 : !llvm.ptr -> i16
      %8 = llvm.getelementptr %0[%5] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %9 = llvm.load %8 : !llvm.ptr -> i16
      %10 = arith.extsi %7 : i16 to i32
      %11 = arith.extsi %9 : i16 to i32
      %12 = arith.addi %10, %11 : i32
      %13 = arith.trunci %12 : i32 to i17
      %14 = llvm.getelementptr %1[%3] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %15 = llvm.load %14 : !llvm.ptr -> i16
      %16 = arith.extsi %13 : i17 to i32
      %17 = arith.extsi %15 : i16 to i32
      %18 = arith.addi %16, %17 : i32
      %19 = arith.trunci %18 : i32 to i16
      affine.store %19, %arg1[%arg3] : memref<128xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
