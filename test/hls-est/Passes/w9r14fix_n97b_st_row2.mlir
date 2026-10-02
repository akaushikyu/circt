// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.sink_parent_trailing_code=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// W9r14 review kernel w9r14rv_st_row2 (Vitis 2025.1 td=off): two stream
// writes of the struct t after the pipelined child loop (each through a
// one-struct temporary that only the write reads): still sunk into the
// flattened pipeline (N97 (b)), t RAM_1WNR 32 = Vitis; the debug output
// counts the moved accesses (sunk_trailing_ops).
// CHECK: sunk_trailing_ops=
// CHECK: Total BRAM: 32
// OFF-NOT: sunk_trailing_ops
// OFF: Total BRAM: 2

module {
  llvm.mlir.global internal constant @str1("s2\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str0("s\00") {addr_space = 0 : i32}
  func.func @_Z3topPKiPi(%arg0: memref<1024xi32>, %arg1: memref<256xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {polygeist.varname = "s2"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    %alloca_0 = memref.alloca() {polygeist.varname = "s"} : memref<1xi32>
    %cast_1 = memref.cast %alloca_0 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_0[0] : memref<1xi32>
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr
    %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI5row_tLi0EEC1EPKc(%cast_1, %2) : (memref<?xi32>, memref<?xi8>) -> ()
    %3 = llvm.mlir.addressof @str1 : !llvm.ptr
    %4 = "polygeist.pointer2memref"(%3) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI5row_tLi0EEC1EPKc(%cast, %4) : (memref<?xi32>, memref<?xi8>) -> ()
    call @_ZL4prodPKiRN3hls6streamI5row_tLi0EEES5_(%arg0, %cast_1, %cast) {hls.inline_auto_off = {calls = 1 : i64, size = 21 : i64}} : (memref<1024xi32>, memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL4consRN3hls6streamI5row_tLi0EEES3_Pi(%cast_1, %cast, %arg1) {hls.inline_auto_off = {calls = 1 : i64, size = 526 : i64}} : (memref<?xi32>, memref<?xi32>, memref<256xi32>) -> ()
    return
  }
  func.func private @_ZN3hls6streamI5row_tLi0EEC1EPKc(memref<?xi32>, memref<?xi8>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 2048 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL4prodPKiRN3hls6streamI5row_tLi0EEES5_(%arg0: memref<1024xi32>, %arg1: memref<?xi32>, %arg2: memref<?xi32>) attributes {hls.inline_auto_off = {size = 21 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    %alloca = memref.alloca() {polygeist.varname = "t"} : memref<1x!llvm.struct<(array<64 x i32>)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(array<64 x i32>)>> to memref<?x!llvm.struct<(array<64 x i32>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 64 {
        %1 = arith.index_cast %arg4 : index to i32
        %2 = affine.load %arg0[%arg4 + %arg3 * 64] : memref<1024xi32>
        %3 = llvm.getelementptr %0[%1] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        llvm.store %2, %3 : i32, !llvm.ptr
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      func.call @_ZN3hls6streamI5row_tLi0EE5writeERKS1_(%arg1, %cast) : (memref<?xi32>, memref<?x!llvm.struct<(array<64 x i32>)>>) -> ()
      func.call @_ZN3hls6streamI5row_tLi0EE5writeERKS1_(%arg2, %cast) : (memref<?xi32>, memref<?x!llvm.struct<(array<64 x i32>)>>) -> ()
    }
    return
  }
  func.func private @_ZL4consRN3hls6streamI5row_tLi0EEES3_Pi(%arg0: memref<?xi32>, %arg1: memref<?xi32>, %arg2: memref<256xi32>) attributes {hls.inline_auto_off = {size = 526 : i64}, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {polygeist.varname = "t2"} : memref<1x!llvm.struct<(array<64 x i32>)>>
    %alloca_0 = memref.alloca() : memref<1x!llvm.struct<(array<64 x i32>)>>
    %alloca_1 = memref.alloca() : memref<1x!llvm.struct<(array<64 x i32>)>>
    %alloca_2 = memref.alloca() {polygeist.varname = "t"} : memref<1x!llvm.struct<(array<64 x i32>)>>
    %alloca_3 = memref.alloca() : memref<1x!llvm.struct<(array<64 x i32>)>>
    %alloca_4 = memref.alloca() : memref<1x!llvm.struct<(array<64 x i32>)>>
    %0 = "polygeist.memref2pointer"(%alloca_2) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    %2 = "polygeist.memref2pointer"(%alloca_4) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    %3 = "polygeist.memref2pointer"(%alloca_3) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    %4 = "polygeist.memref2pointer"(%alloca_1) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    %5 = "polygeist.memref2pointer"(%alloca_0) : (memref<1x!llvm.struct<(array<64 x i32>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 16 {
      %6 = func.call @_ZN3hls6streamI5row_tLi0EE4readEv(%arg0) : (memref<?xi32>) -> !llvm.struct<(array<64 x i32>)>
      affine.store %6, %alloca_3[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      affine.for %arg4 = 0 to 64 {
        %10 = arith.index_cast %arg4 : index to i32
        %11 = llvm.getelementptr %3[%10] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        %12 = llvm.load %11 : !llvm.ptr -> i32
        %13 = llvm.getelementptr %2[%10] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        llvm.store %12, %13 : i32, !llvm.ptr
      }
      %7 = affine.load %alloca_4[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      affine.store %7, %alloca_2[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      %8 = func.call @_ZN3hls6streamI5row_tLi0EE4readEv(%arg1) : (memref<?xi32>) -> !llvm.struct<(array<64 x i32>)>
      affine.store %8, %alloca_0[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      affine.for %arg4 = 0 to 64 {
        %10 = arith.index_cast %arg4 : index to i32
        %11 = llvm.getelementptr %5[%10] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        %12 = llvm.load %11 : !llvm.ptr -> i32
        %13 = llvm.getelementptr %4[%10] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        llvm.store %12, %13 : i32, !llvm.ptr
      }
      %9 = affine.load %alloca_1[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      affine.store %9, %alloca[0] : memref<1x!llvm.struct<(array<64 x i32>)>>
      affine.for %arg4 = 0 to 16 {
        %10 = arith.index_cast %arg4 : index to i32
        %11 = affine.for %arg5 = 0 to 64 iter_args(%arg6 = %c0_i32) -> (i32) {
          %12 = arith.index_cast %arg5 : index to i32
          %13 = llvm.getelementptr %0[%12] : (!llvm.ptr, i32) -> !llvm.ptr, i32
          %14 = llvm.load %13 : !llvm.ptr -> i32
          %15 = arith.addi %12, %10 : i32
          %16 = arith.muli %14, %15 : i32
          %17 = llvm.getelementptr %1[%12] : (!llvm.ptr, i32) -> !llvm.ptr, i32
          %18 = llvm.load %17 : !llvm.ptr -> i32
          %19 = arith.addi %16, %18 : i32
          %20 = arith.addi %arg6, %19 : i32
          affine.yield %20 : i32
        }
        affine.store %11, %arg2[%arg4 + %arg3 * 16] : memref<256xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func private @_ZN3hls6streamI5row_tLi0EE5writeERKS1_(memref<?xi32>, memref<?x!llvm.struct<(array<64 x i32>)>>) attributes {hls.orig_name = "write", hls.stream_element_bits = 2048 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamI5row_tLi0EE4readEv(memref<?xi32>) -> !llvm.struct<(array<64 x i32>)> attributes {hls.orig_name = "read", hls.stream_element_bits = 2048 : i64, llvm.linkage = #llvm.linkage<external>}
}
