// RUN: hls-est %s --symbol-privatize=exclude=_Z4aggrPKsPsi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>/dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z4aggrPKsPsi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z4aggrPKsPsi --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=BRAM
// RUN: hls-est %s --symbol-privatize=exclude=_Z4aggrPKsPsi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs=aggregate=false -o - 2>/dev/null | FileCheck %s --check-prefix=OFF

// AGGREGATE (VITIS_NOTES.md N37 S2 / S3, kernels w9s_a `ma`, w9s_c `mc`):
// `struct M { int a; short b; ap_int<5> c[2]; }` with the pragma is one
// memory of 400 x 58 bits (32 + 16 + 2 x 5, no padding). An iteration that
// writes every leaf is one word store (`ma`: store i58, ram_1p, x36, 2
// BRAM_18K); writing some leaves reads the word first (`mc`: ram_2p, x18,
// 4). Two members of one element read in one iteration share one word read.
// Source: ~/hls-est-work/coord/scratch/n37impl/lit_k/aggr.cpp. Vitis
// (n37i_aggr): ma 400x58 2, mc 400x58 4, 6 in all = hls-est per array.
// The word reads / writes are affine where the indices allow it (W9r7-impl
// 2/10: the load CSE and the invariant hoist then see them).

// CHECK-DAG: %[[MC:.*]] = memref.alloca() {hls.aggregate = [{compact = "auto", variable = "mc"}], hls.aggregated = "aggregated (AGGREGATE pragma): 400 words x 58 bits, 3 leaves packed without padding{{.*}}polygeist.varname = "mc"} : memref<400xi58>
// CHECK-DAG: %[[MA:.*]] = memref.alloca() {hls.aggregate = [{compact = "auto", variable = "ma"}], hls.aggregated = {{.*}}polygeist.varname = "ma"} : memref<400xi58>
// CHECK: affine.store %{{.*}}, %[[MA]][%{{.*}}] {hls.merged_member_stores = 4 : i64} : memref<400xi58>
// CHECK: affine.load %[[MC]][%{{.*}}] {hls.read_modify_write} : memref<400xi58>
// CHECK: affine.store %{{.*}}, %[[MC]][%{{.*}}] {hls.merged_member_stores = 2 : i64} : memref<400xi58>
// CHECK: affine.load %[[MC]][%{{.*}}] {hls.dynamic_lane, hls.read_modify_write} : memref<400xi58>
// BRAM-DAG: struct variable aggregated (AGGREGATE pragma): 400 words x 58 bits
// BRAM-DAG: Total BRAM: 6
// OFF-DAG: polygeist.varname = "ma_0"} : memref<400xi32>
// OFF-DAG: polygeist.varname = "ma_2"} : memref<400x2xi5>
// OFF-NOT: memref<400xi58>

module {
  func.func @_Z4aggrPKsPsi(%arg0: memref<1024xi16>, %arg1: memref<2xi16>, %arg2: i32) attributes {hls.orig_name = "aggr", llvm.linkage = #llvm.linkage<external>} {
    %c8 = arith.constant 8 : index
    %c5_i32 = arith.constant 5 : i32
    %c1_i32 = arith.constant 1 : i32
    %c3_i32 = arith.constant 3 : i32
    %c400_i32 = arith.constant 400 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", variable = "mc"}], hls.preserve, polygeist.varname = "mc"} : memref<400x!llvm.struct<(i32, i16, array<2 x i5>)>>
    %alloca_0 = memref.alloca() {hls.aggregate = [{compact = "auto", variable = "ma"}], hls.preserve, polygeist.varname = "ma"} : memref<400x!llvm.struct<(i32, i16, array<2 x i5>)>>
    %0 = "polygeist.memref2pointer"(%alloca_0) : (memref<400x!llvm.struct<(i32, i16, array<2 x i5>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 400 {
      %5 = arith.muli %arg3, %c8 : index
      %6 = arith.index_cast %5 : index to i64
      %7 = llvm.getelementptr %0[%6] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %8 = affine.load %arg0[%arg3] : memref<1024xi16>
      %9 = arith.extsi %8 : i16 to i32
      %10 = arith.muli %9, %c3_i32 : i32
      llvm.store %10, %7 : i32, !llvm.ptr
      %11 = llvm.getelementptr %7[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, array<2 x i5>)>
      %12 = affine.load %arg0[%arg3 + 1] : memref<1024xi16>
      llvm.store %12, %11 : i16, !llvm.ptr
      %13 = llvm.getelementptr %7[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, array<2 x i5>)>
      %14 = affine.load %arg0[%arg3 + 2] : memref<1024xi16>
      %15 = arith.trunci %14 : i16 to i5
      llvm.store %15, %13 : i5, !llvm.ptr
      %16 = affine.load %arg0[%arg3 + 3] : memref<1024xi16>
      %17 = arith.trunci %16 : i16 to i5
      %18 = llvm.getelementptr %13[1] : (!llvm.ptr) -> !llvm.ptr, i5
      llvm.store %17, %18 : i5, !llvm.ptr
    }
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<400x!llvm.struct<(i32, i16, array<2 x i5>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 400 {
      %5 = arith.muli %arg3, %c8 : index
      %6 = arith.index_cast %5 : index to i64
      %7 = llvm.getelementptr %1[%6] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %8 = affine.load %arg0[%arg3] : memref<1024xi16>
      %9 = arith.extsi %8 : i16 to i32
      %10 = arith.muli %9, %c5_i32 : i32
      llvm.store %10, %7 : i32, !llvm.ptr
      %11 = llvm.getelementptr %7[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, array<2 x i5>)>
      %12 = affine.load %arg0[%arg3 + 7] : memref<1024xi16>
      llvm.store %12, %11 : i16, !llvm.ptr
    }
    affine.for %arg3 = 0 to 400 {
      %5 = arith.index_cast %arg3 : index to i32
      %6 = arith.muli %arg3, %c8 : index
      %7 = arith.index_cast %6 : index to i64
      %8 = llvm.getelementptr %1[%7] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %9 = llvm.getelementptr %8[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, array<2 x i5>)>
      %10 = arith.andi %5, %c1_i32 : i32
      %11 = affine.load %arg0[%arg3 + 2] : memref<1024xi16>
      %12 = arith.trunci %11 : i16 to i5
      %13 = llvm.getelementptr %9[%10] : (!llvm.ptr, i32) -> !llvm.ptr, i5
      llvm.store %12, %13 : i5, !llvm.ptr
    }
    %2:2 = affine.for %arg3 = 0 to 1024 iter_args(%arg4 = %c0_i32, %arg5 = %c0_i32) -> (i32, i32) {
      %5 = arith.index_cast %arg3 : index to i32
      %6 = arith.muli %5, %arg2 : i32
      %7 = arith.shrsi %6, %c3_i32 : i32
      %8 = arith.remsi %7, %c400_i32 : i32
      %9 = arith.index_cast %8 : i32 to index
      %10 = arith.muli %9, %c8 : index
      %11 = arith.index_cast %10 : index to i64
      %12 = llvm.getelementptr %0[%11] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %13 = llvm.load %12 : !llvm.ptr -> i32
      %14 = llvm.getelementptr %12[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, array<2 x i5>)>
      %15 = arith.andi %5, %c1_i32 : i32
      %16 = arith.extsi %13 : i32 to i39
      %17 = llvm.getelementptr %14[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i5
      %18 = llvm.load %17 : !llvm.ptr -> i5
      %19 = arith.extsi %18 : i5 to i39
      %20 = arith.addi %16, %19 : i39
      %21 = arith.trunci %20 : i39 to i32
      %22 = arith.addi %arg5, %21 : i32
      %23 = llvm.getelementptr %1[%11] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %24 = llvm.load %23 : !llvm.ptr -> i32
      %25 = llvm.getelementptr %23[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, array<2 x i5>)>
      %26 = arith.extsi %24 : i32 to i39
      %27 = llvm.getelementptr %25[%15] : (!llvm.ptr, i32) -> !llvm.ptr, i5
      %28 = llvm.load %27 : !llvm.ptr -> i5
      %29 = arith.extsi %28 : i5 to i39
      %30 = arith.addi %26, %29 : i39
      %31 = arith.trunci %30 : i39 to i32
      %32 = arith.addi %arg4, %31 : i32
      affine.yield %32, %22 : i32, i32
    }
    %3 = arith.trunci %2#1 : i32 to i16
    affine.store %3, %arg1[0] : memref<2xi16>
    %4 = arith.trunci %2#0 : i32 to i16
    affine.store %4, %arg1[1] : memref<2xi16>
    return
  }
  func.func @_ZN6ap_intILi5EEaSIsEERS0_RKT_(%arg0: memref<?xi5>, %arg1: memref<?xi16>) -> memref<?xi5> attributes {hls.orig_name = "operator=", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg1[0] : memref<?xi16>
    %1 = arith.trunci %0 : i16 to i5
    affine.store %1, %arg0[0] : memref<?xi5>
    return %arg0 : memref<?xi5>
  }
  func.func @_ZNK11ap_int_baseILi33ELb1EEcvxEv(%arg0: memref<?xi33>) -> i64 attributes {hls.orig_name = "operator long long", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi33>
    %1 = arith.extsi %0 : i33 to i64
    return %1 : i64
  }
  func.func @_ZplILi5ELb1EiEN11ap_int_baseIXT_EXT0_EE5RTypeIXsr9ap_detail5ctypeIT1_EE1WEXsr9ap_detail5ctypeIS3_EE1SEE4plusES3_RKS1_(%arg0: i32, %arg1: memref<?xi5>) -> i33 attributes {hls.orig_name = "operator+", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = arith.extsi %arg0 : i32 to i39
    %1 = affine.load %arg1[0] : memref<?xi5>
    %2 = arith.extsi %1 : i5 to i39
    %3 = arith.addi %0, %2 : i39
    %4 = arith.trunci %3 : i39 to i33
    return %4 : i33
  }
  func.func @_ZN6ap_intILi5EEC1IsEERKT_(%arg0: memref<?xi5>, %arg1: memref<?xi16>) attributes {hls.orig_name = "ap_int", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg1[0] : memref<?xi16>
    %1 = arith.trunci %0 : i16 to i5
    affine.store %1, %arg0[0] : memref<?xi5>
    return
  }
  func.func @_ZNK11ap_int_baseILi33ELb1EE4rvalEv(%arg0: memref<?xi33>) -> i33 attributes {hls.orig_name = "rval", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi33>
    return %0 : i33
  }
  func.func @_ZplILi32ELb1ELi5ELb1EEN11ap_int_baseIXT_EXT0_EE5RTypeIXT1_EXT2_EE4plusERKS1_RKS0_IXT1_EXT2_EE(%arg0: memref<?xi32>, %arg1: memref<?xi5>) -> i33 attributes {hls.orig_name = "operator+", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi32>
    %1 = arith.extsi %0 : i32 to i39
    %2 = affine.load %arg1[0] : memref<?xi5>
    %3 = arith.extsi %2 : i5 to i39
    %4 = arith.addi %1, %3 : i39
    %5 = arith.trunci %4 : i39 to i33
    return %5 : i33
  }
  func.func @_ZN11ap_int_baseILi32ELb1EEC1IiiEET_(%arg0: memref<?xi32>, %arg1: i32) attributes {hls.orig_name = "ap_int_base", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    affine.store %arg1, %arg0[0] : memref<?xi32>
    return
  }
  func.func @_ZN11ap_int_baseILi5ELb1EEC1IssEET_(%arg0: memref<?xi5>, %arg1: i16) attributes {hls.orig_name = "ap_int_base", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = arith.trunci %arg1 : i16 to i5
    affine.store %0, %arg0[0] : memref<?xi5>
    return
  }
  func.func @_ZN9ap_detail4bitsILi33ELb1EE3valEDB33_(%arg0: i33) -> i33 attributes {hls.orig_name = "val", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    return %arg0 : i33
  }
  func.func @_ZNK11ap_int_baseILi32ELb1EE4rvalEv(%arg0: memref<?xi32>) -> i32 attributes {hls.orig_name = "rval", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi32>
    return %0 : i32
  }
  func.func @_ZNK11ap_int_baseILi5ELb1EE4rvalEv(%arg0: memref<?xi5>) -> i5 attributes {hls.orig_name = "rval", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi5>
    return %0 : i5
  }
  func.func @_ZN6ap_intILi33EEC1I11ap_int_baseILi33ELb1EEEERKT_(%arg0: memref<?xi33>, %arg1: memref<?xi33>) attributes {hls.orig_name = "ap_int", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg1[0] : memref<?xi33>
    affine.store %0, %arg0[0] : memref<?xi33>
    return
  }
  func.func @_ZN9ap_detail4bitsILi32ELb1EE3valEDB32_(%arg0: i32) -> i32 attributes {hls.orig_name = "val", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    return %arg0 : i32
  }
  func.func @_ZN9ap_detail4bitsILi5ELb1EE3valEDB5_(%arg0: i5) -> i5 attributes {hls.orig_name = "val", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    return %arg0 : i5
  }
}
