// RUN: hls-est %s --symbol-privatize=exclude=_Z6ap_topPA65_K8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6ap_topPA65_K8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6ap_topPA65_K8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6ap_topPA65_K8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.partitioning.constant_index.max_extent=0' -o /dev/null | FileCheck %s --check-prefix=NOLIMIT
// W9r7 review fixes (2026-10-20): VITIS_NOTES N61: rule (b) leaves a constant-indexed dimension of more than 64 elements whole (A[16][65], the reader unrolled over dim 2 with a non-affine row): one RAM of 1040 x 16, 2 BRAM.
// Kernel w9r7fix_ap_e65 (~/hls-est-work/exp-src/w9r7fix/ap_e65.cpp); MLIR from cgeist c3b (Polygeist branch w9r7-cgeist, W9r7 review fixes) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 2 BRAM_18K.
// With tool.hls.partitioning.constant_index.max_extent=0 (NOLIMIT) the rule is off.
// NOLIMIT: Total BRAM: 0{{$}}

// CHECK: Total BRAM: 2{{$}}

module {
  func.func @_Z6ap_topPA65_K8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_PKi(%arg0: memref<16x65xi16>, %arg1: memref<16xi16>, %arg2: memref<16xi32>) attributes {hls.orig_name = "ap_top", llvm.linkage = #llvm.linkage<external>} {
    %c13_i32 = arith.constant 13 : i32
    %c13_i33 = arith.constant 13 : i33
    %c15_i32 = arith.constant 15 : i32
    %c0_i32 = arith.constant 0 : i32
    %0 = llvm.mlir.undef : i32
    %alloca = memref.alloca() : memref<i32>
    affine.store %0, %alloca[] : memref<i32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<16x65xi16>
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 65 {
        %1 = affine.load %arg0[%arg3, %arg4] : memref<16x65xi16>
        affine.store %1, %alloca_0[%arg3, %arg4] : memref<16x65xi16>
      }
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 16 {
      affine.store %c0_i32, %alloca[] : memref<i32>
      %1 = affine.load %arg2[%arg3] : memref<16xi32>
      %2 = arith.andi %1, %c15_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      affine.for %arg4 = 0 to 65 {
        %7 = affine.load %alloca[] : memref<i32>
        %8 = arith.extsi %7 : i32 to i33
        %9 = memref.load %alloca_0[%3, %arg4] : memref<16x65xi16>
        %10 = arith.extsi %9 : i16 to i33
        %11 = arith.shli %10, %c13_i33 : i33
        %12 = arith.addi %8, %11 : i33
        %13 = arith.trunci %12 : i33 to i32
        affine.store %13, %alloca[] {hls.ap_compound_assign} : memref<i32>
      }
      %4 = affine.load %alloca[] : memref<i32>
      %5 = arith.shrsi %4, %c13_i32 : i32
      %6 = arith.trunci %5 : i32 to i16
      affine.store %6, %arg1[%arg3] : memref<16xi16>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
