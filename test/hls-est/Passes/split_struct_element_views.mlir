// RUN: hls-est %s --symbol-privatize=exclude=_Z5viewsPKsPsi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>/dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z5viewsPKsPsi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z5viewsPKsPsi -o /dev/null 2>&1 | FileCheck %s --check-prefix=BRAM

// Struct-typed variables reached the way cgeist emits C++ (VITIS_NOTES.md
// N37 S1, kernel w9s_a): a one-member struct (`struct R { short d[8]; }`,
// std::array<short, 8>) is one memory named after the variable with the
// member's dimension appended (Vitis `ra` 2400x16, `sa` 2400x16, `gr`
// 2880x16 in w9s_a / w9s_b). The element views `&a[i]` (polygeist.subindex
// of a 1-D struct array, which --lower-polygeist-subindex leaves), the
// operator[] member view (polygeist.pointer2memref), the implicit copy
// assignment (a byte loop, here one whole-element copy) and a global are
// all split. Source: ~/hls-est-work/coord/scratch/n37impl/lit_k/views.cpp
// (cgeist, exactclass shim). Vitis 2025.1 td=off (vitis_adhoc n37i_views,
// ~/hls-est-work/experiments/n37i_views/): gr, ra, sa (RAM_1WNR, 1 copy), sc 2400x16, 4
// BRAM_18K each, 16 in all = hls-est per array.

// CHECK-DAG: memref.global "private" @gr : memref<300x8xi16> = uninitialized {hls.struct_member = "gr member 0"}
// CHECK-DAG: memref.alloca() {hls.preserve, hls.struct_member = "sc member 0", polygeist.varname = "sc"} : memref<300x8xi16>
// CHECK-DAG: memref.alloca() {hls.preserve, hls.struct_member = "sa member 0", polygeist.varname = "sa"} : memref<300x8xi16>
// CHECK-DAG: memref.alloca() {hls.preserve, hls.struct_member = "ra member 0", polygeist.varname = "ra"} : memref<300x8xi16>
// CHECK-NOT: memref<300x!llvm.struct
// BRAM-NOT: not split
// BRAM: Total BRAM: 16

module {
  memref.global @gr : memref<300x!llvm.struct<(array<8 x i16>)>> = uninitialized
  func.func @_Z5viewsPKsPsi(%arg0: memref<2048xi16>, %arg1: memref<4xi16>, %arg2: i32) attributes {hls.orig_name = "views", llvm.linkage = #llvm.linkage<external>} {
    %c16 = arith.constant 16 : index
    %c300_i32 = arith.constant 300 : i32
    %c2_i32 = arith.constant 2 : i32
    %c1_i32 = arith.constant 1 : i32
    %c2047_i32 = arith.constant 2047 : i32
    %c7_i32 = arith.constant 7 : i32
    %c3_i32 = arith.constant 3 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "sc"} : memref<300x!llvm.struct<(array<8 x i16>)>>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "sa"} : memref<300x!llvm.struct<(array<8 x i16>)>>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "ra"} : memref<300x!llvm.struct<(array<8 x i16>)>>
    %0 = "polygeist.memref2pointer"(%alloca_1) : (memref<300x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 2400 {
      %8 = arith.index_cast %arg3 : index to i32
      %9 = arith.shrsi %8, %c3_i32 : i32
      %10 = arith.index_cast %9 : i32 to index
      %11 = arith.muli %10, %c16 : index
      %12 = arith.index_cast %11 : index to i64
      %13 = llvm.getelementptr %0[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %14 = arith.andi %8, %c7_i32 : i32
      %15 = arith.andi %8, %c2047_i32 : i32
      %16 = arith.index_cast %15 : i32 to index
      %17 = memref.load %arg0[%16] : memref<2048xi16>
      %18 = llvm.getelementptr %13[%14] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      llvm.store %17, %18 : i16, !llvm.ptr
    }
    affine.for %arg3 = 0 to 2400 {
      %8 = arith.index_cast %arg3 : index to i32
      %9 = arith.shrsi %8, %c3_i32 : i32
      %10 = arith.index_cast %9 : i32 to index
      %11 = "polygeist.subindex"(%alloca_0, %10) : (memref<300x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %12 = arith.andi %8, %c7_i32 : i32
      %13 = arith.extsi %12 : i32 to i64
      %14 = func.call @_ZNSt5arrayIsLm8EEixEm(%11, %13) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %15 = arith.addi %8, %c1_i32 : i32
      %16 = arith.andi %15, %c2047_i32 : i32
      %17 = arith.index_cast %16 : i32 to index
      %18 = memref.load %arg0[%17] : memref<2048xi16>
      affine.store %18, %14[0] : memref<?xi16>
    }
    %1 = memref.get_global @gr : memref<300x!llvm.struct<(array<8 x i16>)>>
    %2 = "polygeist.memref2pointer"(%1) : (memref<300x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 2400 {
      %8 = arith.index_cast %arg3 : index to i32
      %9 = arith.shrsi %8, %c3_i32 : i32
      %10 = arith.index_cast %9 : i32 to index
      %11 = arith.muli %10, %c16 : index
      %12 = arith.index_cast %11 : index to i64
      %13 = llvm.getelementptr %2[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %14 = arith.andi %8, %c7_i32 : i32
      %15 = arith.addi %8, %c2_i32 : i32
      %16 = arith.andi %15, %c2047_i32 : i32
      %17 = arith.index_cast %16 : i32 to index
      %18 = memref.load %arg0[%17] : memref<2048xi16>
      %19 = llvm.getelementptr %13[%14] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      llvm.store %18, %19 : i16, !llvm.ptr
    }
    affine.for %arg3 = 0 to 300 {
      %8 = arith.index_cast %arg3 : index to i32
      %9 = "polygeist.subindex"(%alloca, %arg3) : (memref<300x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %10 = arith.muli %8, %c7_i32 : i32
      %11 = arith.remsi %10, %c300_i32 : i32
      %12 = arith.index_cast %11 : i32 to index
      %13 = "polygeist.subindex"(%alloca_0, %12) : (memref<300x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %14 = func.call @_ZNSt5arrayIsLm8EEaSERKS0_(%9, %13) : (memref<?x!llvm.struct<(array<8 x i16>)>>, memref<?x!llvm.struct<(array<8 x i16>)>>) -> memref<?x!llvm.struct<(array<8 x i16>)>>
    }
    %3:4 = affine.for %arg3 = 0 to 2048 iter_args(%arg4 = %c0_i32, %arg5 = %c0_i32, %arg6 = %c0_i32, %arg7 = %c0_i32) -> (i32, i32, i32, i32) {
      %8 = arith.index_cast %arg3 : index to i32
      %9 = arith.muli %8, %arg2 : i32
      %10 = arith.andi %9, %c2047_i32 : i32
      %11 = arith.andi %10, %c7_i32 : i32
      %12 = arith.shrsi %10, %c3_i32 : i32
      %13 = arith.remsi %12, %c300_i32 : i32
      %14 = arith.index_cast %13 : i32 to index
      %15 = arith.muli %14, %c16 : index
      %16 = arith.index_cast %15 : index to i64
      %17 = llvm.getelementptr %0[%16] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %18 = llvm.getelementptr %17[%11] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %19 = llvm.load %18 : !llvm.ptr -> i16
      %20 = arith.extsi %19 : i16 to i32
      %21 = arith.addi %arg7, %20 : i32
      %22 = "polygeist.subindex"(%alloca_0, %14) : (memref<300x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %23 = arith.extsi %11 : i32 to i64
      %24 = func.call @_ZNSt5arrayIsLm8EEixEm(%22, %23) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %25 = affine.load %24[0] : memref<?xi16>
      %26 = arith.extsi %25 : i16 to i32
      %27 = arith.addi %arg6, %26 : i32
      %28 = llvm.getelementptr %2[%16] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %29 = llvm.getelementptr %28[%11] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %30 = llvm.load %29 : !llvm.ptr -> i16
      %31 = arith.extsi %30 : i16 to i32
      %32 = arith.addi %arg5, %31 : i32
      %33 = "polygeist.subindex"(%alloca, %14) : (memref<300x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %34 = func.call @_ZNSt5arrayIsLm8EEixEm(%33, %23) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %35 = affine.load %34[0] : memref<?xi16>
      %36 = arith.extsi %35 : i16 to i32
      %37 = arith.addi %arg4, %36 : i32
      affine.yield %37, %32, %27, %21 : i32, i32, i32, i32
    }
    %4 = arith.trunci %3#3 : i32 to i16
    affine.store %4, %arg1[0] : memref<4xi16>
    %5 = arith.trunci %3#2 : i32 to i16
    affine.store %5, %arg1[1] : memref<4xi16>
    %6 = arith.trunci %3#1 : i32 to i16
    affine.store %6, %arg1[2] : memref<4xi16>
    %7 = arith.trunci %3#0 : i32 to i16
    affine.store %7, %arg1[3] : memref<4xi16>
    return
  }
  func.func @_ZNSt5arrayIsLm8EEixEm(%arg0: memref<?x!llvm.struct<(array<8 x i16>)>>, %arg1: i64) -> memref<?xi16> attributes {hls.orig_name = "operator[]", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<8xi16>
    %2 = arith.index_castui %arg1 : i64 to index
    %3 = "polygeist.subindex"(%1, %2) : (memref<8xi16>, index) -> memref<?xi16>
    return %3 : memref<?xi16>
  }
  func.func @_ZNSt5arrayIsLm8EEaSERKS0_(%arg0: memref<?x!llvm.struct<(array<8 x i16>)>>, %arg1: memref<?x!llvm.struct<(array<8 x i16>)>>) -> memref<?x!llvm.struct<(array<8 x i16>)>> attributes {hls.orig_name = "operator=", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg1) : (memref<?x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 16 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = llvm.getelementptr %1[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i8
      %4 = llvm.load %3 : !llvm.ptr -> i8
      %5 = llvm.getelementptr %0[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i8
      llvm.store %4, %5 : i8, !llvm.ptr
    }
    return %arg0 : memref<?x!llvm.struct<(array<8 x i16>)>>
  }
}
