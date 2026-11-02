// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPKbPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPKbPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPKbPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPKbPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set scheduling.timing.operator_latencies.stream_read=2 --config-set scheduling.timing.operator_latencies.stream_write=1 -o /dev/null | FileCheck %s --check-prefix=STRM
// W9r10 review fix D1 (2026-10-21): VITIS_NOTES N82: two reads of one hls::stream in the two exclusive arms of an if, 16 reads of K[j][*] per iteration.
// Only one arm runs per iteration, so the stream's one port is used once: Vitis II 1, K RAM_1WNR 15. With the stream classes (STRM; in the default
// profile since W9r11-impl, MEMOS #78, so CHECK = STRM; before: loop sequential, 1) the accesses hoisted out of the arms (hls.if_arms) count as the larger arm, not the sum (before the fix: II 2, 7).
// Kernel w9r10rv_rv_sc_cond (~/hls-est-work/exp-src/w9r10rv/rv_sc_cond.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: 15 BRAM_18K.
// CHECK: Total BRAM: 15{{$}}
// STRM: Total BRAM: 15{{$}}

module {
  func.func @_Z6sc_topPKsS0_RN3hls6streamIsLi0EEEPKbPs(%arg0: memref<1024xi16>, %arg1: memref<16xi16>, %arg2: memref<?xi32>, %arg3: memref<64xi8>, %arg4: memref<64xi16>) attributes {hls.orig_name = "sc_top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i8 = arith.constant 0 : i8
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "Q"}], hls.preserve, polygeist.varname = "Q"} : memref<16xi16>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "K"} : memref<64x16xi16>
    affine.for %arg5 = 0 to 64 {
      affine.for %arg6 = 0 to 16 {
        %0 = affine.load %arg0[%arg6 + %arg5 * 16] : memref<1024xi16>
        affine.store %0, %alloca_0[%arg5, %arg6] : memref<64x16xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg5 = 0 to 16 {
      %0 = affine.load %arg1[%arg5] : memref<16xi16>
      affine.store %0, %alloca[%arg5] : memref<16xi16>
    }
    affine.for %arg5 = 0 to 64 {
      %0 = affine.load %arg3[%arg5] : memref<64xi8>
      %1 = arith.cmpi ne, %0, %c0_i8 : i8
      %2 = scf.if %1 -> (i16) {
        %6 = func.call @_ZN3hls6streamIsLi0EE4readEv(%arg2) : (memref<?xi32>) -> i16
        scf.yield %6 : i16
      } else {
        %6 = func.call @_ZN3hls6streamIsLi0EE4readEv(%arg2) : (memref<?xi32>) -> i16
        %7 = arith.extsi %6 : i16 to i32
        %8 = arith.addi %7, %c1_i32 : i32
        %9 = arith.trunci %8 : i32 to i16
        scf.yield %9 : i16
      }
      %3 = arith.extsi %2 : i16 to i32
      %4 = affine.for %arg6 = 0 to 16 iter_args(%arg7 = %c0_i32) -> (i32) {
        %6 = affine.load %alloca[%arg6] : memref<16xi16>
        %7 = arith.extsi %6 : i16 to i32
        %8 = affine.load %alloca_0[%arg5, %arg6] : memref<64x16xi16>
        %9 = arith.extsi %8 : i16 to i32
        %10 = arith.muli %7, %9 : i32
        %11 = arith.muli %10, %3 : i32
        %12 = arith.addi %arg7, %11 : i32
        affine.yield %12 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %5 = arith.trunci %4 : i32 to i16
      affine.store %5, %arg4[%arg5] : memref<64xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamIsLi0EE4readEv(memref<?xi32>) -> i16 attributes {hls.orig_name = "read", hls.stream_element_bits = 16 : i64, llvm.linkage = #llvm.linkage<external>}
}
