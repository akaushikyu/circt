// RUN: hls-est %s --symbol-privatize=exclude=_Z3topi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>/dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topi -o /dev/null 2>/dev/null | FileCheck %s --check-prefix=BRAM

// Vitis 2025.1 td=off kernel p_two: one callee `fill(E p[N], int k)` (inline off,
// `aggregate variable=p`, E = {int, short}) called with a local L, a global G
// (through `mid`) and `M + N` (M[2N]). The offset view goes to a clone of fill
// that takes the whole M and the offset (--lower-polygeist-subindex), so the
// three variables no longer share one parameter with a view and are all
// aggregated at 48 bits ([HLS 214-241]); before, none was split or priced.
// G 2 (Vitis 2), M 3 (Vitis 3), L 2 (Vitis 1: Vitis narrows L to the 32 bits
// its loads use, which hls-est does not do across the kept call).

// CHECK: memref.global "private" @G : memref<256xi48>
// CHECK: polygeist.varname = "M"} : memref<512xi48>
// CHECK: polygeist.varname = "L"} : memref<256xi48>
// CHECK: call @_ZL4fillP1Ei_off_0(%{{.*}}, %{{.*}}, %{{.*}}) : (memref<512xi48>, index, i32) -> ()
// BRAM: Total BRAM: 7

module {
  memref.global @G : memref<256x!llvm.struct<(i32, i16)>> = uninitialized {hls.aggregate = [{compact = "auto", from = "_ZL3midP1E", variable = "p"}]}
  func.func @_Z3topi(%arg0: i32) -> i32 attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c256 = arith.constant 256 : index
    %c8 = arith.constant 8 : index
    %c256_i32 = arith.constant 256 : i32
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZL4fillP1Ei", variable = "p"}], hls.preserve, polygeist.varname = "M"} : memref<512x!llvm.struct<(i32, i16)>>
    %alloca_0 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZL4fillP1Ei", variable = "p"}], hls.preserve, polygeist.varname = "L"} : memref<256x!llvm.struct<(i32, i16)>>
    call @_ZL4fillP1Ei(%alloca_0, %arg0) : (memref<256x!llvm.struct<(i32, i16)>>, i32) -> ()
    %0 = memref.get_global @G : memref<256x!llvm.struct<(i32, i16)>>
    call @_ZL3midP1E(%0) : (memref<256x!llvm.struct<(i32, i16)>>) -> ()
    %1 = "polygeist.subindex"(%alloca, %c256) : (memref<512x!llvm.struct<(i32, i16)>>, index) -> memref<256x!llvm.struct<(i32, i16)>>
    %2 = arith.addi %arg0, %c1_i32 : i32
    call @_ZL4fillP1Ei(%1, %2) : (memref<256x!llvm.struct<(i32, i16)>>, i32) -> ()
    %3 = "polygeist.memref2pointer"(%alloca_0) : (memref<256x!llvm.struct<(i32, i16)>>) -> !llvm.ptr
    %4 = "polygeist.memref2pointer"(%0) : (memref<256x!llvm.struct<(i32, i16)>>) -> !llvm.ptr
    %5 = "polygeist.memref2pointer"(%alloca) : (memref<512x!llvm.struct<(i32, i16)>>) -> !llvm.ptr
    %6 = affine.for %arg1 = 0 to 256 iter_args(%arg2 = %c0_i32) -> (i32) {
      %7 = arith.index_cast %arg1 : index to i32
      %8 = arith.muli %arg1, %c8 : index
      %9 = arith.index_cast %8 : index to i64
      %10 = llvm.getelementptr %3[%9] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %11 = llvm.load %10 : !llvm.ptr -> i32
      %12 = llvm.getelementptr %4[%9] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %13 = llvm.getelementptr %12[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16)>
      %14 = llvm.load %13 : !llvm.ptr -> i16
      %15 = arith.extsi %14 : i16 to i32
      %16 = arith.addi %11, %15 : i32
      %17 = arith.addi %7, %c256_i32 : i32
      %18 = arith.index_cast %17 : i32 to index
      %19 = arith.muli %18, %c8 : index
      %20 = arith.index_cast %19 : index to i64
      %21 = llvm.getelementptr %5[%20] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %22 = llvm.load %21 : !llvm.ptr -> i32
      %23 = arith.addi %16, %22 : i32
      %24 = llvm.getelementptr %5[%9] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %25 = llvm.getelementptr %24[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16)>
      %26 = llvm.load %25 : !llvm.ptr -> i16
      %27 = arith.extsi %26 : i16 to i32
      %28 = arith.addi %23, %27 : i32
      %29 = arith.addi %arg2, %28 : i32
      affine.yield %29 : i32
    }
    return %6 : i32
  }
  func.func private @_ZL4fillP1Ei(%arg0: memref<256x!llvm.struct<(i32, i16)>> {hls.aggregate = [{compact = "auto", variable = "p"}]}, %arg1: i32) attributes {hls.inline_off, hls.orig_name = "fill", llvm.linkage = #llvm.linkage<internal>} {
    %c8 = arith.constant 8 : index
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<256x!llvm.struct<(i32, i16)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 256 {
      %1 = arith.index_cast %arg2 : index to i32
      %2 = arith.muli %arg2, %c8 : index
      %3 = arith.index_cast %2 : index to i64
      %4 = llvm.getelementptr %0[%3] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %5 = arith.muli %1, %arg1 : i32
      llvm.store %5, %4 : i32, !llvm.ptr
      %6 = llvm.getelementptr %4[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16)>
      %7 = arith.addi %1, %arg1 : i32
      %8 = arith.trunci %7 : i32 to i16
      llvm.store %8, %6 : i16, !llvm.ptr
    }
    return
  }
  func.func private @_ZL3midP1E(%arg0: memref<256x!llvm.struct<(i32, i16)>> {hls.aggregate = [{compact = "auto", from = "_ZL4fillP1Ei", variable = "p"}]}) attributes {hls.inline_off, hls.orig_name = "mid", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    call @_ZL4fillP1Ei(%arg0, %c3_i32) : (memref<256x!llvm.struct<(i32, i16)>>, i32) -> ()
    return
  }
}
