// RUN: hls-est %s --symbol-privatize=exclude=_Z4maxiP1MPSt5arrayIsLm8EEPsi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z4maxiP1MPSt5arrayIsLm8EEPsi --bram-debug -o /dev/null 2>&1 | FileCheck %s

// m_axi ports of structs are always aggregated at the C storage size
// (compact=none, padding included; VITIS_NOTES.md N37 S5, kernel w9s_b:
// `M {int; short; ap_int<5>[2]}` 64 bits -> read+write adapter 4 BRAM_18K,
// std::array<short, 8> 128 bits read only -> 8). The accesses reach the
// port through cgeist's pointer casts (memref2pointer + getelementptr +
// llvm.load / llvm.store). Source:
// ~/hls-est-work/coord/scratch/n37impl/lit_k/maxi.cpp. Vitis (n37i_maxi):
// m_axi_g1 READ_WRITE 64 -> 64 BRAM=4, m_axi_g2 READ_ONLY 128 -> 128 BRAM=8.

// CHECK-DAG: m_axi.adapter bundle=g1 {{.*}}bram=4 (read FIFO 256x64b -> 4
// CHECK-DAG: m_axi.adapter bundle=g2 {{.*}}bram=8 (read FIFO 256x128b -> 8
// CHECK-DAG: Total BRAM: 12

module {
  func.func @_Z4maxiP1MPSt5arrayIsLm8EEPsi(%arg0: memref<?x!llvm.struct<(i32, i16, array<2 x i5>)>> {hls.interface = [{bundle = "g1", depth = 64 : i32, mode = "m_axi", offset = "slave", port = "pm"}]}, %arg1: memref<?x!llvm.struct<(array<8 x i16>)>> {hls.interface = [{bundle = "g2", depth = 64 : i32, mode = "m_axi", offset = "slave", port = "ps"}]}, %arg2: memref<2xi16>, %arg3: i32) attributes {hls.orig_name = "maxi", llvm.linkage = #llvm.linkage<external>} {
    %c8 = arith.constant 8 : index
    %c7_i32 = arith.constant 7 : i32
    %c0_i32 = arith.constant 0 : i32
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(i32, i16, array<2 x i5>)>>) -> !llvm.ptr
    %1:2 = affine.for %arg4 = 0 to 64 iter_args(%arg5 = %c0_i32, %arg6 = %c0_i32) -> (i32, i32) {
      %4 = arith.index_cast %arg4 : index to i32
      %5 = arith.muli %arg4, %c8 : index
      %6 = arith.index_cast %5 : index to i64
      %7 = llvm.getelementptr %0[%6] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %8 = llvm.load %7 : !llvm.ptr -> i32
      %9 = llvm.getelementptr %7[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, array<2 x i5>)>
      %10 = arith.extsi %8 : i32 to i39
      %11 = llvm.getelementptr %9[1] : (!llvm.ptr) -> !llvm.ptr, i5
      %12 = llvm.load %11 : !llvm.ptr -> i5
      %13 = arith.extsi %12 : i5 to i39
      %14 = arith.addi %10, %13 : i39
      %15 = arith.trunci %14 : i39 to i32
      %16 = arith.addi %arg6, %15 : i32
      %17 = llvm.getelementptr %7[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, array<2 x i5>)>
      %18 = arith.trunci %16 : i32 to i16
      llvm.store %18, %17 : i16, !llvm.ptr
      %19 = "polygeist.subindex"(%arg1, %arg4) : (memref<?x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %20 = arith.muli %4, %arg3 : i32
      %21 = arith.andi %20, %c7_i32 : i32
      %22 = arith.extsi %21 : i32 to i64
      %23 = func.call @_ZNSt5arrayIsLm8EEixEm(%19, %22) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %24 = affine.load %23[0] : memref<?xi16>
      %25 = arith.extsi %24 : i16 to i32
      %26 = arith.addi %arg5, %25 : i32
      affine.yield %26, %16 : i32, i32
    }
    %2 = arith.trunci %1#1 : i32 to i16
    affine.store %2, %arg2[0] : memref<2xi16>
    %3 = arith.trunci %1#0 : i32 to i16
    affine.store %3, %arg2[1] : memref<2xi16>
    return
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
  func.func @_ZNSt5arrayIsLm8EEixEm(%arg0: memref<?x!llvm.struct<(array<8 x i16>)>>, %arg1: i64) -> memref<?xi16> attributes {hls.orig_name = "operator[]", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<8xi16>
    %2 = arith.index_castui %arg1 : i64 to index
    %3 = "polygeist.subindex"(%1, %2) : (memref<8xi16>, index) -> memref<?xi16>
    return %3 : memref<?xi16>
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
