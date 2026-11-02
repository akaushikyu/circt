// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPKiPi -o /dev/null 2>/dev/null | FileCheck %s --check-prefix=BRAM

// Vitis 2025.1 td=off kernel r4s_part: `struct S { int x; short y[4]; }` arrays
// s1 (cyclic factor 2) and s2, with `s2[i] = s1[N-1-i]`. cgeist emits the
// implicit assignment member by member, the array member as a loop of 8 byte
// copies; the whole copy is still one whole-element copy, so both variables are
// split (they were left whole and priced 0) and the partition applies to s1's
// members. Vitis builds s1_x 2 banks, s1_y 3, s2_x 1, s2_y 1 (7); hls-est gives
// the same total, but s1_y 2 and s2_y 2: Vitis also partitions y's constant-
// index dimension and drops the dead columns (OPEN_ISSUES O53).

// CHECK-NOT: not split into members
// CHECK-DAG: polygeist.varname = "s2_0"} : memref<512xi32>
// CHECK-DAG: polygeist.varname = "s2_1"} : memref<512x4xi16>
// CHECK-DAG: kind = "cyclic", variable = "s1"}], hls.preserve, hls.struct_member = "s1 member 1", polygeist.varname = "s1_1"} : memref<512x4xi16>
// BRAM: Total BRAM: 7

module {
  func.func @_Z3topPKiPi(%arg0: memref<512xi32>, %arg1: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c12 = arith.constant 12 : index
    %c2_i32 = arith.constant 2 : i32
    %c511_i32 = arith.constant 511 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "s2"} : memref<512x!llvm.struct<(i32, array<4 x i16>)>>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "s1"}], hls.preserve, polygeist.varname = "s1"} : memref<512x!llvm.struct<(i32, array<4 x i16>)>>
    %0 = "polygeist.memref2pointer"(%alloca_0) : (memref<512x!llvm.struct<(i32, array<4 x i16>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 512 {
      %2 = arith.muli %arg2, %c12 : index
      %3 = arith.index_cast %2 : index to i64
      %4 = llvm.getelementptr %0[%3] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %5 = affine.load %arg0[%arg2] : memref<512xi32>
      llvm.store %5, %4 : i32, !llvm.ptr
      %6 = llvm.getelementptr %4[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, array<4 x i16>)>
      affine.for %arg3 = 0 to 4 {
        %7 = arith.index_cast %arg3 : index to i32
        %8 = affine.load %arg0[%arg2] : memref<512xi32>
        %9 = arith.shrsi %8, %7 : i32
        %10 = arith.trunci %9 : i32 to i16
        %11 = llvm.getelementptr %6[%7] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        llvm.store %10, %11 : i16, !llvm.ptr
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 512 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = "polygeist.subindex"(%alloca, %arg2) : (memref<512x!llvm.struct<(i32, array<4 x i16>)>>, index) -> memref<?x!llvm.struct<(i32, array<4 x i16>)>>
      %4 = arith.subi %c511_i32, %2 : i32
      %5 = arith.index_cast %4 : i32 to index
      %6 = "polygeist.subindex"(%alloca_0, %5) : (memref<512x!llvm.struct<(i32, array<4 x i16>)>>, index) -> memref<?x!llvm.struct<(i32, array<4 x i16>)>>
      %7 = func.call @_ZN1SaSERKS_(%3, %6) : (memref<?x!llvm.struct<(i32, array<4 x i16>)>>, memref<?x!llvm.struct<(i32, array<4 x i16>)>>) -> memref<?x!llvm.struct<(i32, array<4 x i16>)>>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<512x!llvm.struct<(i32, array<4 x i16>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 256 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = arith.muli %2, %c2_i32 : i32
      %4 = arith.index_cast %3 : i32 to index
      %5 = arith.muli %4, %c12 : index
      %6 = arith.index_cast %5 : index to i64
      %7 = llvm.getelementptr %1[%6] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %8 = llvm.load %7 : !llvm.ptr -> i32
      %9 = arith.addi %3, %c1_i32 : i32
      %10 = arith.index_cast %9 : i32 to index
      %11 = arith.muli %10, %c12 : index
      %12 = arith.index_cast %11 : index to i64
      %13 = llvm.getelementptr %1[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %14 = llvm.getelementptr %13[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, array<4 x i16>)>
      %15 = llvm.getelementptr %14[1] : (!llvm.ptr) -> !llvm.ptr, i16
      %16 = llvm.load %15 : !llvm.ptr -> i16
      %17 = arith.extsi %16 : i16 to i32
      %18 = arith.addi %8, %17 : i32
      %19 = llvm.getelementptr %0[%6] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %20 = llvm.getelementptr %19[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, array<4 x i16>)>
      %21 = llvm.getelementptr %20[3] : (!llvm.ptr) -> !llvm.ptr, i16
      %22 = llvm.load %21 : !llvm.ptr -> i16
      %23 = arith.extsi %22 : i16 to i32
      %24 = arith.addi %18, %23 : i32
      %25 = llvm.getelementptr %0[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %26 = llvm.load %25 : !llvm.ptr -> i32
      %27 = arith.addi %24, %26 : i32
      affine.store %27, %arg1[%arg2] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func @_ZN1SaSERKS_(%arg0: memref<?x!llvm.struct<(i32, array<4 x i16>)>>, %arg1: memref<?x!llvm.struct<(i32, array<4 x i16>)>>) -> memref<?x!llvm.struct<(i32, array<4 x i16>)>> attributes {hls.orig_name = "operator=", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(i32, array<4 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg1) : (memref<?x!llvm.struct<(i32, array<4 x i16>)>>) -> !llvm.ptr
    %2 = llvm.load %1 : !llvm.ptr -> i32
    llvm.store %2, %0 : i32, !llvm.ptr
    %3 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, array<4 x i16>)>
    %4 = llvm.getelementptr %1[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, array<4 x i16>)>
    affine.for %arg2 = 0 to 8 {
      %5 = arith.index_cast %arg2 : index to i32
      %6 = llvm.getelementptr %4[%5] : (!llvm.ptr, i32) -> !llvm.ptr, i8
      %7 = llvm.load %6 : !llvm.ptr -> i8
      %8 = llvm.getelementptr %3[%5] : (!llvm.ptr, i32) -> !llvm.ptr, i8
      llvm.store %7, %8 : i8, !llvm.ptr
    }
    return %arg0 : memref<?x!llvm.struct<(i32, array<4 x i16>)>>
  }
}
