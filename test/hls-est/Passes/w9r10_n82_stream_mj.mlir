// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topRN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EEES6_S6_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topRN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EEES6_S6_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6sc_topRN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EEES6_S6_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sc_topRN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EEES6_S6_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set scheduling.timing.operator_latencies.stream_read=2 --config-set scheduling.timing.operator_latencies.stream_write=1 -o /dev/null | FileCheck %s --check-prefix=STRM
// W9r10-impl (2026-10-21): VITIS_NOTES N82 (OPEN_ISSUES O54 (c)): minjun lab2 compute_qk_product_stream shape: K_buffer cyclic 4, 4 x RAM_1WNR 3.
// A blocking hls::stream read / write is an operation of class stream_read (2 cycles) / stream_write (1 cycle) on its stream's one port.
// Since W9r11-impl (2026-10-22, MEMOS #78) the classes are in the default profile (CHECK = STRM); before, the default left such a loop
// sequential (4 BRAM). They waited for the loop-carried memory recurrences (VITIS_NOTES N87, OPEN_ISSUES O1 / O114), which W9r11-impl added.
// Kernel w9r10p_sc_mj (~/hls-est-work/exp-src/w9r10p/sc_mj.cpp); MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 12 BRAM_18K.
// CHECK: Total BRAM: 12{{$}}
// STRM: Total BRAM: 12{{$}}

module {
  func.func @_Z6sc_topRN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EEES6_S6_(%arg0: memref<?xi32>, %arg1: memref<?xi32>, %arg2: memref<?xi32>) attributes {hls.orig_name = "sc_top", llvm.linkage = #llvm.linkage<external>} {
    %c11_i33 = arith.constant 11 : i33
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() {polygeist.varname = "sum"} : memref<1xi16>
    %cast = memref.cast %alloca : memref<1xi16> to memref<?xi16>
    %0 = llvm.mlir.undef : i16
    affine.store %0, %alloca[0] : memref<1xi16>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "Q_row"}], hls.preserve, polygeist.varname = "Q_row"} : memref<16xi16>
    %alloca_1 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "K_buffer"}], hls.preserve, polygeist.varname = "K_buffer"} : memref<64x16xi16>
    affine.for %arg3 = 0 to 2 {
      affine.for %arg4 = 0 to 64 {
        affine.for %arg5 = 0 to 16 {
          %1 = func.call @_ZN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EE4readEv(%arg1) : (memref<?xi32>) -> i16
          affine.store %1, %alloca_1[%arg4, %arg5] : memref<64x16xi16>
        } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
      }
      affine.for %arg4 = 0 to 64 {
        affine.for %arg5 = 0 to 16 {
          %1 = func.call @_ZN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EE4readEv(%arg0) : (memref<?xi32>) -> i16
          affine.store %1, %alloca_0[%arg5] : memref<16xi16>
        } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
        affine.for %arg5 = 0 to 64 {
          affine.store %c0_i16, %alloca[0] : memref<1xi16>
          affine.for %arg6 = 0 to 16 {
            %1 = affine.load %alloca_0[%arg6] : memref<16xi16>
            %2 = arith.extsi %1 : i16 to i32
            %3 = affine.load %alloca_1[%arg5, %arg6] : memref<64x16xi16>
            %4 = arith.extsi %3 : i16 to i32
            %5 = arith.muli %2, %4 : i32
            %6 = affine.load %alloca[0] : memref<1xi16>
            %7 = arith.extsi %6 : i16 to i33
            %8 = arith.shli %7, %c11_i33 : i33
            %9 = arith.extsi %5 : i32 to i33
            %10 = arith.addi %8, %9 : i33
            %11 = arith.shrsi %10, %c11_i33 : i33
            %12 = arith.trunci %11 : i33 to i16
            affine.store %12, %alloca[0] {hls.ap_compound_assign} : memref<1xi16>
          } {hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
          func.call @_ZN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EE5writeERKS4_(%arg2, %cast) : (memref<?xi32>, memref<?xi16>) -> ()
        } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
      }
    }
    return
  }
  func.func private @_ZN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EE4readEv(memref<?xi32>) -> i16 attributes {hls.orig_name = "read", hls.stream_element_bits = 16 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamI8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EELi0EE5writeERKS4_(memref<?xi32>, memref<?xi16>) attributes {hls.orig_name = "write", hls.stream_element_bits = 16 : i64, llvm.linkage = #llvm.linkage<external>}
}
