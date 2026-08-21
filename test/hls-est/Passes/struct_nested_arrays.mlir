// RUN: hls-est %s --symbol-privatize=exclude=_Z6nestedPKsPsi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6nestedPKsPsi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z6nestedPKsPsi -o /dev/null 2>&1 | FileCheck %s --check-prefix=BRAM

// std::array<std::array<short, 4>, 3>: an array of one-leaf structs inside
// the struct is one leaf of 3 x 4 scalars (flowgnn node_conv_weights,
// VITIS_NOTES.md N37 S2 (a): std::array<std::array<16b, 4>, 3> is 192 bits
// aggregated, 12 scalars disaggregated). The copy constructor copies the
// inner arrays one sub-struct at a time (a load / store of
// !llvm.struct<(array<4 x i16>)>, rewritten scalar by scalar). Source:
// ~/hls-est-work/coord/scratch/n37impl/lit_k/nested.cpp. Vitis (n37i_nested):
// gw 6144x16, 8 BRAM_18K = hls-est.

// CHECK-NOT: not split
// CHECK: memref.global "private" @gw : memref<64x8x3x4xi16> = uninitialized {hls.struct_member = "gw member 0"}
// CHECK: polygeist.varname = "w"} : memref<1x3x4xi16>
// BRAM: Total BRAM: 8

module {
  memref.global @gw : memref<64x8x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>> = uninitialized
  func.func @_Z6nestedPKsPsi(%arg0: memref<1024xi16>, %arg1: memref<1xi16>, %arg2: i32) attributes {hls.orig_name = "nested", llvm.linkage = #llvm.linkage<external>} {
    %c3_i64 = arith.constant 3 : i64
    %c2_i64 = arith.constant 2 : i64
    %c1_i64 = arith.constant 1 : i64
    %c0_i64 = arith.constant 0 : i64
    %c7_i32 = arith.constant 7 : i32
    %c63_i32 = arith.constant 63 : i32
    %c1023_i32 = arith.constant 1023 : i32
    %c3_i32 = arith.constant 3 : i32
    %c4_i32 = arith.constant 4 : i32
    %c8_i32 = arith.constant 8 : i32
    %c96_i32 = arith.constant 96 : i32
    %c12_i32 = arith.constant 12 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {polygeist.varname = "w"} : memref<1x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>> to memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>
    %0 = memref.get_global @gw : memref<64x8x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>
    affine.for %arg3 = 0 to 6144 {
      %3 = arith.index_cast %arg3 : index to i32
      %4 = arith.divsi %3, %c96_i32 : i32
      %5 = arith.index_cast %4 : i32 to index
      %6 = "polygeist.subindex"(%0, %5) : (memref<64x8x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, index) -> memref<8x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>
      %7 = arith.divsi %3, %c12_i32 : i32
      %8 = arith.remsi %7, %c8_i32 : i32
      %9 = arith.index_cast %8 : i32 to index
      %10 = "polygeist.subindex"(%6, %9) : (memref<8x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, index) -> memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>
      %11 = arith.divsi %3, %c4_i32 : i32
      %12 = arith.remsi %11, %c3_i32 : i32
      %13 = arith.extsi %12 : i32 to i64
      %14 = func.call @_ZNSt5arrayIS_IsLm4EELm3EEixEm(%10, %13) : (memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, i64) -> memref<?x!llvm.struct<(array<4 x i16>)>>
      %15 = arith.remsi %3, %c4_i32 : i32
      %16 = arith.extsi %15 : i32 to i64
      %17 = func.call @_ZNSt5arrayIsLm4EEixEm(%14, %16) : (memref<?x!llvm.struct<(array<4 x i16>)>>, i64) -> memref<?xi16>
      %18 = arith.andi %3, %c1023_i32 : i32
      %19 = arith.index_cast %18 : i32 to index
      %20 = memref.load %arg0[%19] : memref<1024xi16>
      affine.store %20, %17[0] : memref<?xi16>
    }
    %1 = affine.for %arg3 = 0 to 512 iter_args(%arg4 = %c0_i32) -> (i32) {
      %3 = arith.index_cast %arg3 : index to i32
      %4 = arith.muli %3, %arg2 : i32
      %5 = arith.andi %4, %c63_i32 : i32
      %6 = arith.index_cast %5 : i32 to index
      %7 = "polygeist.subindex"(%0, %6) : (memref<64x8x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, index) -> memref<8x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>
      %8 = arith.andi %3, %c7_i32 : i32
      %9 = arith.index_cast %8 : i32 to index
      %10 = "polygeist.subindex"(%7, %9) : (memref<8x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, index) -> memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>
      func.call @_ZNSt5arrayIS_IsLm4EELm3EEC1ERKS1_(%cast, %10) : (memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>) -> ()
      %11 = func.call @_ZNSt5arrayIS_IsLm4EELm3EEixEm(%cast, %c0_i64) : (memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, i64) -> memref<?x!llvm.struct<(array<4 x i16>)>>
      %12 = func.call @_ZNSt5arrayIsLm4EEixEm(%11, %c0_i64) : (memref<?x!llvm.struct<(array<4 x i16>)>>, i64) -> memref<?xi16>
      %13 = affine.load %12[0] : memref<?xi16>
      %14 = arith.extsi %13 : i16 to i32
      %15 = func.call @_ZNSt5arrayIS_IsLm4EELm3EEixEm(%cast, %c1_i64) : (memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, i64) -> memref<?x!llvm.struct<(array<4 x i16>)>>
      %16 = func.call @_ZNSt5arrayIsLm4EEixEm(%15, %c1_i64) : (memref<?x!llvm.struct<(array<4 x i16>)>>, i64) -> memref<?xi16>
      %17 = affine.load %16[0] : memref<?xi16>
      %18 = arith.extsi %17 : i16 to i32
      %19 = arith.addi %14, %18 : i32
      %20 = func.call @_ZNSt5arrayIS_IsLm4EELm3EEixEm(%cast, %c2_i64) : (memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, i64) -> memref<?x!llvm.struct<(array<4 x i16>)>>
      %21 = func.call @_ZNSt5arrayIsLm4EEixEm(%20, %c3_i64) : (memref<?x!llvm.struct<(array<4 x i16>)>>, i64) -> memref<?xi16>
      %22 = affine.load %21[0] : memref<?xi16>
      %23 = arith.extsi %22 : i16 to i32
      %24 = arith.addi %19, %23 : i32
      %25 = arith.addi %arg4, %24 : i32
      affine.yield %25 : i32
    }
    %2 = arith.trunci %1 : i32 to i16
    affine.store %2, %arg1[0] : memref<1xi16>
    return
  }
  func.func @_ZNSt5arrayIsLm4EEixEm(%arg0: memref<?x!llvm.struct<(array<4 x i16>)>>, %arg1: i64) -> memref<?xi16> attributes {hls.orig_name = "operator[]", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<4 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<4xi16>
    %2 = arith.index_castui %arg1 : i64 to index
    %3 = "polygeist.subindex"(%1, %2) : (memref<4xi16>, index) -> memref<?xi16>
    return %3 : memref<?xi16>
  }
  func.func @_ZNSt5arrayIS_IsLm4EELm3EEixEm(%arg0: memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, %arg1: i64) -> memref<?x!llvm.struct<(array<4 x i16>)>> attributes {hls.orig_name = "operator[]", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>) -> !llvm.ptr
    %1 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<3x!llvm.struct<(array<4 x i16>)>>
    %2 = arith.index_castui %arg1 : i64 to index
    %3 = "polygeist.subindex"(%1, %2) : (memref<3x!llvm.struct<(array<4 x i16>)>>, index) -> memref<?x!llvm.struct<(array<4 x i16>)>>
    return %3 : memref<?x!llvm.struct<(array<4 x i16>)>>
  }
  func.func @_ZNSt5arrayIS_IsLm4EELm3EEC1ERKS1_(%arg0: memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>, %arg1: memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>) attributes {hls.orig_name = "array", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %alloca = memref.alloca() : memref<1x!llvm.struct<(array<4 x i16>)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(array<4 x i16>)>> to memref<?x!llvm.struct<(array<4 x i16>)>>
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg1) : (memref<?x!llvm.struct<(array<3 x struct<(array<4 x i16>)>>)>>) -> !llvm.ptr
    %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<3x!llvm.struct<(array<4 x i16>)>>
    affine.for %arg2 = 0 to 3 {
      %3 = "polygeist.subindex"(%2, %arg2) : (memref<3x!llvm.struct<(array<4 x i16>)>>, index) -> memref<?x!llvm.struct<(array<4 x i16>)>>
      func.call @_ZNSt5arrayIsLm4EEC1ERKS0_(%cast, %3) : (memref<?x!llvm.struct<(array<4 x i16>)>>, memref<?x!llvm.struct<(array<4 x i16>)>>) -> ()
      %4 = affine.load %alloca[0] : memref<1x!llvm.struct<(array<4 x i16>)>>
      %5 = arith.index_cast %arg2 : index to i32
      %6 = llvm.getelementptr %0[%5] : (!llvm.ptr, i32) -> !llvm.ptr, !llvm.struct<(array<4 x i16>)>
      llvm.store %4, %6 : !llvm.struct<(array<4 x i16>)>, !llvm.ptr
    }
    return
  }
  func.func @_ZNSt5arrayIsLm4EEC1ERKS0_(%arg0: memref<?x!llvm.struct<(array<4 x i16>)>>, %arg1: memref<?x!llvm.struct<(array<4 x i16>)>>) attributes {hls.orig_name = "array", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<4 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg1) : (memref<?x!llvm.struct<(array<4 x i16>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 4 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = llvm.getelementptr %1[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %4 = llvm.load %3 : !llvm.ptr -> i16
      %5 = llvm.getelementptr %0[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      llvm.store %4, %5 : i16, !llvm.ptr
    }
    return
  }
}
