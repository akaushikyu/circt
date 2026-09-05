// RUN: hls-est %s --symbol-privatize=exclude=_Z6ap_topPA32_K8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6ap_topPA32_K8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N57: rule (b) also for an array none of whose accesses is affine (memref.load with a constant column after the unroll).
// Kernel w9r7_ap_none (~/hls-est-work/exp-src/w9r7p/ap_none.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 32 BRAM_18K.


// CHECK: Total BRAM: 32{{$}}

module {
  func.func @_Z6ap_topPA32_K8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPS2_(%arg0: memref<128x32xi16>, %arg1: memref<128xi16>) attributes {hls.orig_name = "ap_top", llvm.linkage = #llvm.linkage<external>} {
    %c13_i32 = arith.constant 13 : i32
    %c2_i35 = arith.constant 2 : i35
    %c127_i32 = arith.constant 127 : i32
    %c5_i32 = arith.constant 5 : i32
    %c0_i32 = arith.constant 0 : i32
    %0 = llvm.mlir.undef : i16
    %1 = llvm.mlir.undef : i32
    %alloca = memref.alloca() : memref<i32>
    affine.store %1, %alloca[] : memref<i32>
    %alloca_0 = memref.alloca() : memref<i16>
    affine.store %0, %alloca_0[] : memref<i16>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<128x32xi16>
    affine.for %arg2 = 0 to 128 {
      %2 = affine.load %arg0[%arg2, 0] : memref<128x32xi16>
      affine.store %2, %alloca_0[] : memref<i16>
      affine.for %arg3 = 1 to 32 {
        %5 = affine.load %arg0[%arg2, %arg3] : memref<128x32xi16>
        %6 = arith.extsi %5 : i16 to i32
        %7 = affine.load %alloca_0[] : memref<i16>
        %8 = arith.extsi %7 : i16 to i32
        %9 = arith.cmpi sgt, %6, %8 : i32
        scf.if %9 {
          %10 = affine.load %arg0[%arg2, %arg3] : memref<128x32xi16>
          affine.store %10, %alloca_0[] : memref<i16>
        }
      }
      %3 = affine.load %alloca_0[] : memref<i16>
      %4 = arith.extsi %3 : i16 to i32
      affine.for %arg3 = 0 to 32 {
        %5 = affine.load %arg0[%arg2, %arg3] : memref<128x32xi16>
        %6 = arith.extsi %5 : i16 to i32
        %7 = arith.subi %6, %4 : i32
        %8 = arith.trunci %7 : i32 to i16
        affine.store %8, %alloca_1[%arg2, %arg3] : memref<128x32xi16>
      }
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 128 {
      %2 = arith.index_cast %arg2 : index to i32
      affine.store %c0_i32, %alloca[] : memref<i32>
      %3 = arith.muli %2, %c5_i32 : i32
      %4 = arith.andi %3, %c127_i32 : i32
      %5 = arith.index_cast %4 : i32 to index
      affine.for %arg3 = 0 to 32 {
        %9 = memref.load %alloca_1[%5, %arg3] : memref<128x32xi16>
        %10 = arith.extsi %9 : i16 to i32
        %11 = affine.load %alloca_1[%arg2, -%arg3 + 31] : memref<128x32xi16>
        %12 = arith.extsi %11 : i16 to i32
        %13 = arith.muli %10, %12 : i32
        %14 = affine.load %alloca[] : memref<i32>
        %15 = arith.extsi %14 : i32 to i35
        %16 = arith.extsi %13 : i32 to i35
        %17 = arith.shli %16, %c2_i35 : i35
        %18 = arith.addi %15, %17 : i35
        %19 = arith.trunci %18 : i35 to i32
        affine.store %19, %alloca[] {hls.ap_compound_assign} : memref<i32>
      } {hls.unroll = [{factor = 8 : i32, skip_exit_check = false}]}
      %6 = affine.load %alloca[] : memref<i32>
      %7 = arith.shrsi %6, %c13_i32 : i32
      %8 = arith.trunci %7 : i32 to i16
      affine.store %8, %arg1[%arg2] : memref<128xi16>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
