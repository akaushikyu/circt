// RUN: hls-est %s --symbol-privatize=exclude=_Z6ap_topPA64_K6ap_intILi32EEPS_ILi40EEPKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6ap_topPA64_K6ap_intILi32EEPS_ILi40EEPKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 review fixes (2026-10-20): VITIS_NOTES N61 control: extent 64 (32-bit elements) is still partitioned: 64 banks of 16 words, LUTRAM.
// Kernel w9r7fix_ap_e64w32 (~/hls-est-work/exp-src/w9r7fix/ap_e64w32.cpp); MLIR from cgeist c3b (Polygeist branch w9r7-cgeist, W9r7 review fixes) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 0 BRAM_18K.

// CHECK: Total BRAM: 0{{$}}

module {
  func.func @_Z6ap_topPA64_K6ap_intILi32EEPS_ILi40EEPKi(%arg0: memref<16x64xi32>, %arg1: memref<16xi40>, %arg2: memref<16xi32>) attributes {hls.orig_name = "ap_top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i40 = arith.constant 0 : i40
    %c15_i32 = arith.constant 15 : i32
    %alloca = memref.alloca() : memref<i40>
    %0 = llvm.mlir.undef : i40
    affine.store %0, %alloca[] : memref<i40>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<16x64xi32>
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 64 {
        %1 = affine.load %arg0[%arg3, %arg4] : memref<16x64xi32>
        affine.store %1, %alloca_0[%arg3, %arg4] : memref<16x64xi32>
      }
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 16 {
      affine.store %c0_i40, %alloca[] : memref<i40>
      %1 = affine.load %arg2[%arg3] : memref<16xi32>
      %2 = arith.andi %1, %c15_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      affine.for %arg4 = 0 to 64 {
        %5 = memref.load %alloca_0[%3, %arg4] : memref<16x64xi32>
        %6 = arith.extsi %5 : i32 to i40
        %7 = affine.load %alloca[] : memref<i40>
        %8 = arith.addi %7, %6 : i40
        affine.store %8, %alloca[] : memref<i40>
      }
      %4 = affine.load %alloca[] : memref<i40>
      affine.store %4, %arg1[%arg3] : memref<16xi40>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
