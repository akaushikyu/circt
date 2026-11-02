// RUN: not hls-est %s --symbol-privatize=exclude=_Z8conflictPKsPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o /dev/null 2>&1 | FileCheck %s

// AGGREGATE (here from fill's parameter) and DISAGGREGATE on one variable:
// Vitis stops with [HLS 214-258] "Unsupported conflicting aggregate pragma
// with disaggregate pragma" (VITIS_NOTES.md N37 S4); hls-est reports it as
// unsupported. Source: ~/hls-est-work/coord/scratch/n37impl/lit_k/conflict.cpp.

// CHECK: error: unsupported: conflicting aggregate and disaggregate pragmas on one variable (Vitis [HLS 214-258])

module {
  func.func @_Z8conflictPKsPs(%arg0: memref<512xi16>, %arg1: memref<1xi16>) attributes {hls.orig_name = "conflict", llvm.linkage = #llvm.linkage<external>} {
    %c2_i64 = arith.constant 2 : i64
    %c3 = arith.constant 3 : index
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZL4fillPSt5arrayIsLm8EEPKs", variable = "p"}], hls.disaggregate = [{variable = "d"}], hls.preserve, polygeist.varname = "d"} : memref<64x!llvm.struct<(array<8 x i16>)>>
    %cast = memref.cast %arg0 : memref<512xi16> to memref<?xi16>
    call @_ZL4fillPSt5arrayIsLm8EEPKs(%alloca, %cast) : (memref<64x!llvm.struct<(array<8 x i16>)>>, memref<?xi16>) -> ()
    %0 = "polygeist.subindex"(%alloca, %c3) : (memref<64x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
    %1 = call @_ZNSt5arrayIsLm8EEixEm(%0, %c2_i64) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
    %2 = affine.load %1[0] : memref<?xi16>
    affine.store %2, %arg1[0] : memref<1xi16>
    return
  }
  func.func private @_ZL4fillPSt5arrayIsLm8EEPKs(%arg0: memref<64x!llvm.struct<(array<8 x i16>)>> {hls.aggregate = [{compact = "auto", variable = "p"}]}, %arg1: memref<?xi16>) attributes {hls.inline_off, hls.orig_name = "fill", llvm.linkage = #llvm.linkage<internal>} {
    %c7_i32 = arith.constant 7 : i32
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 512 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = arith.shrsi %0, %c3_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %3 = "polygeist.subindex"(%arg0, %2) : (memref<64x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %4 = arith.andi %0, %c7_i32 : i32
      %5 = arith.extsi %4 : i32 to i64
      %6 = func.call @_ZNSt5arrayIsLm8EEixEm(%3, %5) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %7 = affine.load %arg1[%arg2] : memref<?xi16>
      affine.store %7, %6[0] : memref<?xi16>
    }
    return
  }
  func.func @_ZNSt5arrayIsLm8EEixEm(%arg0: memref<?x!llvm.struct<(array<8 x i16>)>>, %arg1: i64) -> memref<?xi16> attributes {hls.orig_name = "operator[]", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<8xi16>
    %2 = arith.index_castui %arg1 : i64 to index
    %3 = "polygeist.subindex"(%1, %2) : (memref<8xi16>, index) -> memref<?xi16>
    return %3 : memref<?xi16>
  }
}
