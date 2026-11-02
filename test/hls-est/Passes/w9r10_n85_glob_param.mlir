// RUN: hls-est %s --symbol-privatize=exclude=_Z6gp_topPKsS0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6gp_topPKsS0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6gp_topPKsS0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6gp_topPKsS0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.memory_architecture.replication.port_bound_writable_globals=false -o /dev/null | FileCheck %s --check-prefix=POFF
// W9r10-impl (2026-10-21): VITIS_NOTES N85 (OPEN_ISSUES O4 / O17): a written global read 16 times per iteration by an inline-off callee through a parameter: one 2-port RAM, II 8.
// Global accesses are attributed (tool.hls.globals.attribute_accesses, now on) and a written global or static is never replicated
// (tool.hls.memory_architecture.replication.port_bound_writable_globals; off, prefix POFF, gives 60).
// Kernel w9r10p_gp_glob_param (~/hls-est-work/exp-src/w9r10p/gp_glob_param.cpp); MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 4 BRAM_18K.
// CHECK: Total BRAM: 4{{$}}
// POFF: Total BRAM: 60{{$}}

module {
  memref.global @G : memref<256x16xi16> = uninitialized
  func.func @_Z2rdPA16_sPKs(%arg0: memref<256x16xi16>, %arg1: memref<16xi16>) -> i32 attributes {hls.inline_off, hls.orig_name = "rd", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %0 = affine.for %arg2 = 0 to 256 iter_args(%arg3 = %c0_i32) -> (i32) {
      %1 = affine.for %arg4 = 0 to 16 iter_args(%arg5 = %c0_i32) -> (i32) {
        %3 = affine.load %arg0[%arg2, %arg4] : memref<256x16xi16>
        %4 = arith.extsi %3 : i16 to i32
        %5 = affine.load %arg1[%arg4] : memref<16xi16>
        %6 = arith.extsi %5 : i16 to i32
        %7 = arith.muli %4, %6 : i32
        %8 = arith.addi %arg5, %7 : i32
        affine.yield %8 : i32
      }
      %2 = arith.xori %arg3, %1 : i32
      affine.yield %2 : i32
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return %0 : i32
  }
  func.func @_Z6gp_topPKsS0_(%arg0: memref<4096xi16>, %arg1: memref<16xi16>) -> i32 attributes {hls.orig_name = "gp_top", llvm.linkage = #llvm.linkage<external>} {
    %0 = memref.get_global @G : memref<256x16xi16>
    affine.for %arg2 = 0 to 256 {
      affine.for %arg3 = 0 to 16 {
        %2 = affine.load %arg0[%arg3 + %arg2 * 16] : memref<4096xi16>
        affine.store %2, %0[%arg2, %arg3] : memref<256x16xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %1 = call @_Z2rdPA16_sPKs(%0, %arg1) : (memref<256x16xi16>, memref<16xi16>) -> i32
    return %1 : i32
  }
}
