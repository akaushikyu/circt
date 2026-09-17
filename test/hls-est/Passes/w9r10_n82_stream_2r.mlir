// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set scheduling.timing.operator_latencies.stream_read=2 --config-set scheduling.timing.operator_latencies.stream_write=1 -o /dev/null | FileCheck %s --check-prefix=STRM
// W9r10-impl (2026-10-21): VITIS_NOTES N82 (OPEN_ISSUES O54 (c)): two reads of one stream per iteration: II 2, K needs 7 copies.
// A blocking hls::stream read / write is an operation of class stream_read (2 cycles) / stream_write (1 cycle) on its stream's one port.
// The classes are opt-in (prefix STRM, set by --config-set of both latencies); the default leaves such a loop sequential (CHECK), because adopting them
// needs loop-carried memory recurrences (OPEN_ISSUES O1): run S1 of W9r10-impl lost 115 exact designs through x36 -> x18 accumulators.
// Kernel w9r10p_sc_2r (~/hls-est-work/exp-src/w9r10p/sc_2r.cpp); MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 7 BRAM_18K.
// CHECK: Total BRAM: 1{{$}}
// STRM: Total BRAM: 7{{$}}

module {
  func.func @_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPs(%arg0: memref<1024xi16>, %arg1: memref<16xi16>, %arg2: memref<?xi32>, %arg3: memref<64xi16>) attributes {hls.orig_name = "sc_top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "Q"}], hls.preserve, polygeist.varname = "Q"} : memref<16xi16>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "K"} : memref<64x16xi16>
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 16 {
        %0 = affine.load %arg0[%arg5 + %arg4 * 16] : memref<1024xi16>
        affine.store %0, %alloca_0[%arg4, %arg5] : memref<64x16xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg4 = 0 to 16 {
      %0 = affine.load %arg1[%arg4] : memref<16xi16>
      affine.store %0, %alloca[%arg4] : memref<16xi16>
    }
    affine.for %arg4 = 0 to 64 {
      %0 = func.call @_ZN3hls6streamIsLi0EE4readEv(%arg2) : (memref<?xi32>) -> i16
      %1 = func.call @_ZN3hls6streamIsLi0EE4readEv(%arg2) : (memref<?xi32>) -> i16
      %2 = arith.extsi %0 : i16 to i32
      %3 = arith.extsi %1 : i16 to i32
      %4 = affine.for %arg5 = 0 to 16 iter_args(%arg6 = %c0_i32) -> (i32) {
        %6 = affine.load %alloca[%arg5] : memref<16xi16>
        %7 = arith.extsi %6 : i16 to i32
        %8 = affine.load %alloca_0[%arg4, %arg5] : memref<64x16xi16>
        %9 = arith.extsi %8 : i16 to i32
        %10 = arith.muli %7, %9 : i32
        %11 = arith.muli %10, %2 : i32
        %12 = arith.addi %11, %3 : i32
        %13 = arith.addi %arg6, %12 : i32
        affine.yield %13 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %5 = arith.trunci %4 : i32 to i16
      affine.store %5, %arg3[%arg4] : memref<64xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamIsLi0EE4readEv(memref<?xi32>) -> i16 attributes {hls.orig_name = "read", hls.stream_element_bits = 16 : i64, llvm.linkage = #llvm.linkage<external>}
}
