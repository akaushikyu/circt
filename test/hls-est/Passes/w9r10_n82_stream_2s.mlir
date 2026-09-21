// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEES4_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEES4_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEES4_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topPKsS0_RN3hls6streamIsLi0EEES4_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set scheduling.timing.operator_latencies.stream_read=2 --config-set scheduling.timing.operator_latencies.stream_write=1 -o /dev/null | FileCheck %s --check-prefix=STRM
// W9r10-impl (2026-10-21): VITIS_NOTES N82 (OPEN_ISSUES O54 (c)): one write each to two streams: II 1.
// A blocking hls::stream read / write is an operation of class stream_read (2 cycles) / stream_write (1 cycle) on its stream's one port.
// Since W9r11-impl (2026-10-22, MEMOS #78) the classes are in the default profile (CHECK = STRM); before, the default left such a loop
// sequential (1 BRAM). They waited for the loop-carried memory recurrences (VITIS_NOTES N87, OPEN_ISSUES O1 / O114), which W9r11-impl added.
// Kernel w9r10p_sc_2s (~/hls-est-work/exp-src/w9r10p/sc_2s.cpp); MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 15 BRAM_18K.
// CHECK: Total BRAM: 15{{$}}
// STRM: Total BRAM: 15{{$}}

module {
  func.func @_Z6sc_topPKsS0_RN3hls6streamIsLi0EEES4_(%arg0: memref<1024xi16>, %arg1: memref<16xi16>, %arg2: memref<?xi32>, %arg3: memref<?xi32>) attributes {hls.orig_name = "sc_top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() : memref<1xi16>
    %cast = memref.cast %alloca : memref<1xi16> to memref<?xi16>
    %0 = llvm.mlir.undef : i16
    affine.store %0, %alloca[0] : memref<1xi16>
    %alloca_0 = memref.alloca() : memref<1xi16>
    %cast_1 = memref.cast %alloca_0 : memref<1xi16> to memref<?xi16>
    affine.store %0, %alloca_0[0] : memref<1xi16>
    %alloca_2 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "Q"}], hls.preserve, polygeist.varname = "Q"} : memref<16xi16>
    %alloca_3 = memref.alloca() {hls.preserve, polygeist.varname = "K"} : memref<64x16xi16>
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 16 {
        %1 = affine.load %arg0[%arg5 + %arg4 * 16] : memref<1024xi16>
        affine.store %1, %alloca_3[%arg4, %arg5] : memref<64x16xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg4 = 0 to 16 {
      %1 = affine.load %arg1[%arg4] : memref<16xi16>
      affine.store %1, %alloca_2[%arg4] : memref<16xi16>
    }
    affine.for %arg4 = 0 to 64 {
      %1 = affine.for %arg5 = 0 to 16 iter_args(%arg6 = %c0_i32) -> (i32) {
        %5 = affine.load %alloca_2[%arg5] : memref<16xi16>
        %6 = arith.extsi %5 : i16 to i32
        %7 = affine.load %alloca_3[%arg4, %arg5] : memref<64x16xi16>
        %8 = arith.extsi %7 : i16 to i32
        %9 = arith.muli %6, %8 : i32
        %10 = arith.addi %arg6, %9 : i32
        affine.yield %10 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %2 = arith.trunci %1 : i32 to i16
      affine.store %2, %alloca_0[0] : memref<1xi16>
      func.call @_ZN3hls6streamIsLi0EE5writeERKs(%arg2, %cast_1) : (memref<?xi32>, memref<?xi16>) -> ()
      %3 = arith.addi %1, %c1_i32 : i32
      %4 = arith.trunci %3 : i32 to i16
      affine.store %4, %alloca[0] : memref<1xi16>
      func.call @_ZN3hls6streamIsLi0EE5writeERKs(%arg3, %cast) : (memref<?xi32>, memref<?xi16>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamIsLi0EE5writeERKs(memref<?xi32>, memref<?xi16>) attributes {hls.orig_name = "write", hls.stream_element_bits = 16 : i64, llvm.linkage = #llvm.linkage<external>}
}
