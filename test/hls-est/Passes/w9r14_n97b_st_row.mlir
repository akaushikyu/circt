// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.sink_parent_trailing_code=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N97 (b), OPEN_ISSUES O137, kernel w9r13p_st_row (Vitis 2025.1
// td=off): prod builds row_t t in a pipelined k loop and writes it to a stream
// after the loop, inside for r: Vitis flattens r x k and runs the 64 reads that
// pack t into the stream word in that pipeline (II 4): t RAM_1WNR 16 copies, 32.
// hls-est: the code after the child loop moves into the flattened pipeline
// under a last-iteration guard
// (tool.hls.pipeline_decision.sink_parent_trailing_code); off: RAM_2P, 2.
// CHECK: Total BRAM: 32
// OFF: Total BRAM: 2

module {
  llvm.mlir.global internal constant @str0("s\00") {addr_space = 0 : i32}
  func.func @_Z3topPKiPi(%arg0: memref<1024xi32>, %arg1: memref<256xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {polygeist.varname = "s"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr
    %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI5row_tLi0EEC1EPKc(%cast, %2) : (memref<?xi32>, memref<?xi8>) -> ()
    call @_ZL4prodPKiRN3hls6streamI5row_tLi0EEE(%arg0, %cast) {hls.inline_auto_off = {calls = 1 : i64, size = 20 : i64}} : (memref<1024xi32>, memref<?xi32>) -> ()
    call @_ZL4consRN3hls6streamI5row_tLi0EEEPi(%cast, %arg1) {hls.inline_auto_off = {calls = 1 : i64, size = 333 : i64}} : (memref<?xi32>, memref<256xi32>) -> ()
    return
  }
  func.func private @_ZN3hls6streamI5row_tLi0EEC1EPKc(memref<?xi32>, memref<?xi8>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 2048 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL4prodPKiRN3hls6streamI5row_tLi0EEE(%arg0: memref<1024xi32>, %arg1: memref<?xi32>) attributes {hls.inline_auto_off = {size = 20 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    %alloca = memref.alloca() {polygeist.varname = "t"} : memref<1x!llvm.struct<(array<64 x i32>)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(array<64 x i32>)>> to memref<?x!llvm.struct<(array<64 x i32>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 16 {
      affine.for %arg3 = 0 to 64 {
        %1 = arith.index_cast %arg3 : index to i32
        %2 = affine.load %arg0[%arg3 + %arg2 * 64] : memref<1024xi32>
        %3 = llvm.getelementptr %0[%1] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        llvm.store %2, %3 : i32, !llvm.ptr
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      func.call @_ZN3hls6streamI5row_tLi0EE5writeERKS1_(%arg1, %cast) : (memref<?xi32>, memref<?x!llvm.struct<(array<64 x i32>)>>) -> ()
    }
    return
  }
  func.func private @_ZL4consRN3hls6streamI5row_tLi0EEEPi(%arg0: memref<?xi32>, %arg1: memref<256xi32>) attributes {hls.inline_auto_off = {size = 333 : i64}, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {polygeist.varname = "t"} : memref<1x!llvm.struct<(array<64 x i32>)>>
    %alloca_0 = memref.alloca() : memref<1x!llvm.struct<(array<64 x i32>)>>
    %alloca_1 = memref.alloca() : memref<1x!llvm.struct<(array<64 x i32>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%alloca_1) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    %2 = "polygeist.memref2pointer"(%alloca_0) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 16 {
      %3 = func.call @_ZN3hls6streamI5row_tLi0EE4readEv(%arg0) : (memref<?xi32>) -> !llvm.struct<(array<64 x i32>)>
      affine.store %3, %alloca_0[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      affine.for %arg3 = 0 to 64 {
        %5 = arith.index_cast %arg3 : index to i32
        %6 = llvm.getelementptr %2[%5] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        %7 = llvm.load %6 : !llvm.ptr -> i32
        %8 = llvm.getelementptr %1[%5] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        llvm.store %7, %8 : i32, !llvm.ptr
      }
      %4 = affine.load %alloca_1[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      affine.store %4, %alloca[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      affine.for %arg3 = 0 to 16 {
        %5 = arith.index_cast %arg3 : index to i32
        %6 = affine.for %arg4 = 0 to 64 iter_args(%arg5 = %c0_i32) -> (i32) {
          %7 = arith.index_cast %arg4 : index to i32
          %8 = llvm.getelementptr %0[%7] : (!llvm.ptr, i32) -> !llvm.ptr, i32
          %9 = llvm.load %8 : !llvm.ptr -> i32
          %10 = arith.addi %7, %5 : i32
          %11 = arith.muli %9, %10 : i32
          %12 = arith.addi %arg5, %11 : i32
          affine.yield %12 : i32
        }
        affine.store %6, %arg1[%arg3 + %arg2 * 16] : memref<256xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func private @_ZN3hls6streamI5row_tLi0EE5writeERKS1_(memref<?xi32>, memref<?x!llvm.struct<(array<64 x i32>)>>) attributes {hls.orig_name = "write", hls.stream_element_bits = 2048 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamI5row_tLi0EE4readEv(memref<?xi32>) -> !llvm.struct<(array<64 x i32>)> attributes {hls.orig_name = "read", hls.stream_element_bits = 2048 : i64, llvm.linkage = #llvm.linkage<external>}
}
