// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs=scalar-registers=false -o - 2>&1 | FileCheck %s --check-prefix=NOREG
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPKsPs --bram-debug-json=%t.json -o /dev/null 2>/dev/null | FileCheck %s --check-prefix=BRAM
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON

// Vitis 2025.1 td=off kernel r4s_aggb: `struct P { short a[3]; bool f;
// ap_uint<5> c; }`, `P arr[1024]` with `aggregate variable=arr`: Vitis packs
// "compact=bit mode in 54-bits", the bool as 1 bit, RAM_1P 3. cgeist stores the
// bool as an i8 that only holds 0 or 1 (zero-extended i1 stores), which packs
// as 1 bit: 1024 x 54 (it was 61 bits, 4 BRAM). `P e = arr[N-1-i]` copies
// the element member by member (now one whole-element copy: one word read);
// the temporary e is read and written only at constant positions, so its
// members are registers and the reading loop keeps II 1 (Vitis II 1; it was
// II 3 with e as a memory).

// CHECK: hls.registers, hls.struct_member = "e member 0", polygeist.varname = "e_0"} : memref<1x3xi16>
// CHECK: polygeist.varname = "arr"} : memref<1024xi54>
// NOREG-NOT: hls.registers
// BRAM: 1024x54b -> RAM_1P (x18/port) = 3 BRAM_18K
// BRAM: Total BRAM: 3
// JSON: "pipelines": [
// JSON: "ii": 1,
// JSON-NOT: "ii": 3,

module {
  func.func @_Z3topPKsPs(%arg0: memref<1024xi16>, %arg1: memref<1024xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c8 = arith.constant 8 : index
    %c0_i8 = arith.constant 0 : i8
    %c1023_i32 = arith.constant 1023 : i32
    %c3_i32 = arith.constant 3 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {polygeist.varname = "e"} : memref<1x!llvm.struct<(array<3 x i16>, i8, i5)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(array<3 x i16>, i8, i5)>> to memref<?x!llvm.struct<(array<3 x i16>, i8, i5)>>
    %alloca_0 = memref.alloca() {hls.aggregate = [{compact = "auto", variable = "arr"}], hls.preserve, polygeist.varname = "arr"} : memref<1024x!llvm.struct<(array<3 x i16>, i8, i5)>>
    %0 = "polygeist.memref2pointer"(%alloca_0) : (memref<1024x!llvm.struct<(array<3 x i16>, i8, i5)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 1024 {
      %5 = arith.muli %arg2, %c8 : index
      %6 = arith.index_cast %5 : index to i64
      %7 = llvm.getelementptr %0[%6] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %8 = affine.load %arg0[%arg2] : memref<1024xi16>
      llvm.store %8, %7 : i16, !llvm.ptr
      %9 = affine.load %arg0[%arg2] : memref<1024xi16>
      %10 = arith.extsi %9 : i16 to i32
      %11 = arith.addi %10, %c1_i32 : i32
      %12 = arith.trunci %11 : i32 to i16
      %13 = llvm.getelementptr %7[1] : (!llvm.ptr) -> !llvm.ptr, i16
      llvm.store %12, %13 : i16, !llvm.ptr
      %14 = affine.load %arg0[%arg2] : memref<1024xi16>
      %15 = arith.extsi %14 : i16 to i32
      %16 = arith.muli %15, %c3_i32 : i32
      %17 = arith.trunci %16 : i32 to i16
      %18 = llvm.getelementptr %7[2] : (!llvm.ptr) -> !llvm.ptr, i16
      llvm.store %17, %18 : i16, !llvm.ptr
      %19 = llvm.getelementptr %7[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<3 x i16>, i8, i5)>
      %20 = affine.load %arg0[%arg2] : memref<1024xi16>
      %21 = arith.extsi %20 : i16 to i32
      %22 = arith.cmpi sgt, %21, %c0_i32 : i32
      %23 = arith.extui %22 : i1 to i8
      llvm.store %23, %19 : i8, !llvm.ptr
      %24 = llvm.getelementptr %7[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<3 x i16>, i8, i5)>
      %25 = affine.load %arg0[%arg2] : memref<1024xi16>
      %26 = arith.trunci %25 : i16 to i5
      llvm.store %26, %24 : i5, !llvm.ptr
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<3 x i16>, i8, i5)>>) -> !llvm.ptr
    %2 = llvm.getelementptr %1[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<3 x i16>, i8, i5)>
    %3 = llvm.getelementptr %1[2] : (!llvm.ptr) -> !llvm.ptr, i16
    %4 = llvm.getelementptr %1[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<3 x i16>, i8, i5)>
    affine.for %arg2 = 0 to 1024 {
      %5 = arith.index_cast %arg2 : index to i32
      %6 = arith.subi %c1023_i32, %5 : i32
      %7 = arith.index_cast %6 : i32 to index
      %8 = "polygeist.subindex"(%alloca_0, %7) : (memref<1024x!llvm.struct<(array<3 x i16>, i8, i5)>>, index) -> memref<?x!llvm.struct<(array<3 x i16>, i8, i5)>>
      func.call @_ZN1PC1ERKS_(%cast, %8) : (memref<?x!llvm.struct<(array<3 x i16>, i8, i5)>>, memref<?x!llvm.struct<(array<3 x i16>, i8, i5)>>) -> ()
      %9 = llvm.load %2 : !llvm.ptr -> i8
      %10 = arith.cmpi ne, %9, %c0_i8 : i8
      %11 = scf.if %10 -> (i16) {
        %12 = llvm.load %3 : !llvm.ptr -> i16
        scf.yield %12 : i16
      } else {
        %12 = llvm.load %1 : !llvm.ptr -> i16
        %13 = llvm.load %4 : !llvm.ptr -> i5
        %14 = arith.extui %13 : i5 to i23
        %15 = arith.extsi %12 : i16 to i23
        %16 = arith.addi %14, %15 : i23
        %17 = arith.trunci %16 : i23 to i16
        scf.yield %17 : i16
      }
      affine.store %11, %arg1[%arg2] : memref<1024xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func @_ZN7ap_uintILi5EEaSIsEERS0_RKT_(%arg0: memref<?xi5>, %arg1: memref<?xi16>) -> memref<?xi5> attributes {hls.orig_name = "operator=", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg1[0] : memref<?xi16>
    %1 = arith.trunci %0 : i16 to i5
    affine.store %1, %arg0[0] : memref<?xi5>
    return %arg0 : memref<?xi5>
  }
  func.func @_ZN1PC1ERKS_(%arg0: memref<?x!llvm.struct<(array<3 x i16>, i8, i5)>>, %arg1: memref<?x!llvm.struct<(array<3 x i16>, i8, i5)>>) attributes {hls.orig_name = "P", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<3 x i16>, i8, i5)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg1) : (memref<?x!llvm.struct<(array<3 x i16>, i8, i5)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 3 {
      %8 = arith.index_cast %arg2 : index to i32
      %9 = llvm.getelementptr %1[%8] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %10 = llvm.load %9 : !llvm.ptr -> i16
      %11 = llvm.getelementptr %0[%8] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      llvm.store %10, %11 : i16, !llvm.ptr
    }
    %2 = llvm.getelementptr %1[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<3 x i16>, i8, i5)>
    %3 = llvm.load %2 : !llvm.ptr -> i8
    %4 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<3 x i16>, i8, i5)>
    llvm.store %3, %4 : i8, !llvm.ptr
    %5 = llvm.getelementptr %0[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<3 x i16>, i8, i5)>
    %6 = llvm.getelementptr %1[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<3 x i16>, i8, i5)>
    %7 = llvm.load %6 : !llvm.ptr -> i5
    llvm.store %7, %5 : i5, !llvm.ptr
    return
  }
  func.func @_ZNK11ap_int_baseILi17ELb1EEcvxEv(%arg0: memref<?xi17>) -> i64 attributes {hls.orig_name = "operator long long", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi17>
    %1 = arith.extsi %0 : i17 to i64
    return %1 : i64
  }
  func.func @_ZplILi5ELb0EsEN11ap_int_baseIXT_EXT0_EE5RTypeIXsr9ap_detail5ctypeIT1_EE1WEXsr9ap_detail5ctypeIS3_EE1SEE4plusERKS1_S3_(%arg0: memref<?xi5>, %arg1: i16) -> i17 attributes {hls.orig_name = "operator+", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi5>
    %1 = arith.extui %0 : i5 to i23
    %2 = arith.extsi %arg1 : i16 to i23
    %3 = arith.addi %1, %2 : i23
    %4 = arith.trunci %3 : i23 to i17
    return %4 : i17
  }
  func.func @_ZN7ap_uintILi5EEC1IsEERKT_(%arg0: memref<?xi5>, %arg1: memref<?xi16>) attributes {hls.orig_name = "ap_uint", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg1[0] : memref<?xi16>
    %1 = arith.trunci %0 : i16 to i5
    affine.store %1, %arg0[0] : memref<?xi5>
    return
  }
  func.func @_ZNK11ap_int_baseILi17ELb1EE4rvalEv(%arg0: memref<?xi17>) -> i17 attributes {hls.orig_name = "rval", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi17>
    return %0 : i17
  }
  func.func @_ZplILi5ELb0ELi16ELb1EEN11ap_int_baseIXT_EXT0_EE5RTypeIXT1_EXT2_EE4plusERKS1_RKS0_IXT1_EXT2_EE(%arg0: memref<?xi5>, %arg1: memref<?xi16>) -> i17 attributes {hls.orig_name = "operator+", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi5>
    %1 = arith.extui %0 : i5 to i23
    %2 = affine.load %arg1[0] : memref<?xi16>
    %3 = arith.extsi %2 : i16 to i23
    %4 = arith.addi %1, %3 : i23
    %5 = arith.trunci %4 : i23 to i17
    return %5 : i17
  }
  func.func @_ZN11ap_int_baseILi16ELb1EEC1IssEET_(%arg0: memref<?xi16>, %arg1: i16) attributes {hls.orig_name = "ap_int_base", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    affine.store %arg1, %arg0[0] : memref<?xi16>
    return
  }
  func.func @_ZN11ap_int_baseILi5ELb0EEC1IssEET_(%arg0: memref<?xi5>, %arg1: i16) attributes {hls.orig_name = "ap_int_base", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = arith.trunci %arg1 : i16 to i5
    affine.store %0, %arg0[0] : memref<?xi5>
    return
  }
  func.func @_ZN9ap_detail4bitsILi17ELb1EE3valEDB17_(%arg0: i17) -> i17 attributes {hls.orig_name = "val", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    return %arg0 : i17
  }
  func.func @_ZNK11ap_int_baseILi5ELb0EE4rvalEv(%arg0: memref<?xi5>) -> i5 attributes {hls.orig_name = "rval", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi5>
    return %0 : i5
  }
  func.func @_ZNK11ap_int_baseILi16ELb1EE4rvalEv(%arg0: memref<?xi16>) -> i16 attributes {hls.orig_name = "rval", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg0[0] : memref<?xi16>
    return %0 : i16
  }
  func.func @_ZN6ap_intILi17EEC1I11ap_int_baseILi17ELb1EEEERKT_(%arg0: memref<?xi17>, %arg1: memref<?xi17>) attributes {hls.orig_name = "ap_int", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = affine.load %arg1[0] : memref<?xi17>
    affine.store %0, %arg0[0] : memref<?xi17>
    return
  }
  func.func @_ZN9ap_detail4bitsILi5ELb0EE3valEDU5_(%arg0: i5) -> i5 attributes {hls.orig_name = "val", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    return %arg0 : i5
  }
  func.func @_ZN9ap_detail4bitsILi16ELb1EE3valEDB16_(%arg0: i16) -> i16 attributes {hls.orig_name = "val", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    return %arg0 : i16
  }
}
