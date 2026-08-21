// RUN: hls-est %s --symbol-privatize=exclude=_Z5callsPKsPsiRN3hls6streamI3RowLi0EEE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>/dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z5callsPKsPsiRN3hls6streamI3RowLi0EEE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z5callsPKsPsiRN3hls6streamI3RowLi0EEE -o /dev/null 2>&1 | FileCheck %s --check-prefix=BRAM
// RUN: hls-est %s --symbol-privatize=exclude=_Z5callsPKsPsiRN3hls6streamI3RowLi0EEE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs=through-calls=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// A struct variable passed whole to kept calls is one variable with the
// callees' parameters (VITIS_NOTES.md N37 S2 (b), S7): `la` reaches fill's
// AGGREGATE parameter (cgeist --hls-annotate carries the pragma to `la`) and
// is one 330 x 128 memory, fill's parameter with it (Vitis w9s_b `la`
// 330x128, 8 BRAM_18K); `ps` is split together with the parameters of prods
// and cons. An element passed to hls::stream::write is read whole through a
// temporary the call receives. Source:
// ~/hls-est-work/coord/scratch/n37impl/lit_k/calls.cpp. Vitis (n37i_calls):
// la 330x128 8 and ps 2400x16 4 = hls-est; rows 1024x16 RAM_1WNR 15 copies
// (15 BRAM_18K) where hls-est has 1: the 64-element stream write sits in a
// loop hls-est leaves unscheduled (a stream call is not schedulable), so its
// 64 reads per iteration are not seen as one pipelined iteration. Vitis 27,
// hls-est 13.

// CHECK-DAG: polygeist.varname = "rows"} : memref<16x64xi16>
// CHECK-DAG: polygeist.varname = "ps"} : memref<300x8xi16>
// CHECK-DAG: %[[LA:.*]] = memref.alloca() {hls.aggregate = [{compact = "auto", from = "{{.*}}fill{{.*}}", variable = "p"}], hls.aggregated = {{.*}} : memref<330xi128>
// CHECK: call @{{.*}}fill{{.*}}(%[[LA]], %{{.*}}) : (memref<330xi128>, memref<?xi16>) -> ()
// CHECK: call @{{.*}}prods{{.*}}(%{{.*}}, %{{.*}}) : (memref<?xi16>, memref<300x8xi16>) -> ()
// CHECK: call @{{.*}}cons{{.*}}(%{{.*}}, %{{.*}}, %{{.*}}) : (memref<300x8xi16>, i32, memref<?xi16>) -> ()
// CHECK: func.call @{{.*}}stream{{.*}}write{{.*}}(%{{.*}}, %{{.*}}) : (memref<?xi32>, memref<?x!llvm.struct<(array<64 x i16>)>>) -> ()
// CHECK: func.func private @{{.*}}fill{{.*}}(%arg0: memref<330xi128> {hls.aggregate
// CHECK: func.func private @{{.*}}prods{{.*}}(%arg0: memref<?xi16>, %arg1: memref<300x8xi16>)
// CHECK: func.func private @{{.*}}cons{{.*}}(%arg0: memref<300x8xi16>, %arg1: i32, %arg2: memref<?xi16>)
// BRAM: Total BRAM: 13
// OFF-DAG: struct array not split into members: struct array passed to the kept call @{{.*}}fill
// OFF-DAG: struct array not split into members: struct array passed to the kept call @{{.*}}prods

module {
  func.func @_Z5callsPKsPsiRN3hls6streamI3RowLi0EEE(%arg0: memref<1024xi16>, %arg1: memref<4xi16>, %arg2: i32, %arg3: memref<?xi32>) attributes {hls.orig_name = "calls", llvm.linkage = #llvm.linkage<external>} {
    %c128 = arith.constant 128 : index
    %c7_i32 = arith.constant 7 : i32
    %c330_i32 = arith.constant 330 : i32
    %c3_i32 = arith.constant 3 : i32
    %c1023_i32 = arith.constant 1023 : i32
    %c15_i32 = arith.constant 15 : i32
    %c63_i32 = arith.constant 63 : i32
    %c6_i32 = arith.constant 6 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "rows"} : memref<16x!llvm.struct<(array<64 x i16>)>>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "ps"} : memref<300x!llvm.struct<(array<8 x i16>)>>
    %alloca_1 = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZL4fillPSt5arrayIsLm8EEPKs", variable = "p"}], hls.preserve, polygeist.varname = "la"} : memref<330x!llvm.struct<(array<8 x i16>)>>
    %cast = memref.cast %arg0 : memref<1024xi16> to memref<?xi16>
    call @_ZL4fillPSt5arrayIsLm8EEPKs(%alloca_1, %cast) : (memref<330x!llvm.struct<(array<8 x i16>)>>, memref<?xi16>) -> ()
    call @_ZL5prodsPKsPSt5arrayIsLm8EE(%cast, %alloca_0) : (memref<?xi16>, memref<300x!llvm.struct<(array<8 x i16>)>>) -> ()
    %cast_2 = memref.cast %arg1 : memref<4xi16> to memref<?xi16>
    call @_ZL4consPSt5arrayIsLm8EEiPs(%alloca_0, %arg2, %cast_2) : (memref<300x!llvm.struct<(array<8 x i16>)>>, i32, memref<?xi16>) -> ()
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<16x!llvm.struct<(array<64 x i16>)>>) -> !llvm.ptr
    affine.for %arg4 = 0 to 1024 {
      %3 = arith.index_cast %arg4 : index to i32
      %4 = arith.shrsi %3, %c6_i32 : i32
      %5 = arith.index_cast %4 : i32 to index
      %6 = arith.muli %5, %c128 : index
      %7 = arith.index_cast %6 : index to i64
      %8 = llvm.getelementptr %0[%7] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %9 = arith.andi %3, %c63_i32 : i32
      %10 = affine.load %arg0[%arg4] : memref<1024xi16>
      %11 = llvm.getelementptr %8[%9] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      llvm.store %10, %11 : i16, !llvm.ptr
    }
    affine.for %arg4 = 0 to 16 {
      %3 = arith.index_cast %arg4 : index to i32
      %4 = arith.muli %3, %arg2 : i32
      %5 = arith.andi %4, %c15_i32 : i32
      %6 = arith.index_cast %5 : i32 to index
      %7 = "polygeist.subindex"(%alloca, %6) : (memref<16x!llvm.struct<(array<64 x i16>)>>, index) -> memref<?x!llvm.struct<(array<64 x i16>)>>
      func.call @_ZN3hls6streamI3RowLi0EE5writeERKS1_(%arg3, %7) : (memref<?xi32>, memref<?x!llvm.struct<(array<64 x i16>)>>) -> ()
    }
    %1 = affine.for %arg4 = 0 to 1024 iter_args(%arg5 = %c0_i32) -> (i32) {
      %3 = arith.index_cast %arg4 : index to i32
      %4 = arith.muli %3, %arg2 : i32
      %5 = arith.andi %4, %c1023_i32 : i32
      %6 = arith.shrsi %5, %c3_i32 : i32
      %7 = arith.remsi %6, %c330_i32 : i32
      %8 = arith.index_cast %7 : i32 to index
      %9 = "polygeist.subindex"(%alloca_1, %8) : (memref<330x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %10 = arith.andi %5, %c7_i32 : i32
      %11 = arith.extsi %10 : i32 to i64
      %12 = func.call @_ZNSt5arrayIsLm8EEixEm(%9, %11) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %13 = affine.load %12[0] : memref<?xi16>
      %14 = arith.extsi %13 : i16 to i32
      %15 = arith.addi %arg5, %14 : i32
      affine.yield %15 : i32
    }
    %2 = arith.trunci %1 : i32 to i16
    affine.store %2, %arg1[1] : memref<4xi16>
    return
  }
  func.func private @_ZL4fillPSt5arrayIsLm8EEPKs(%arg0: memref<330x!llvm.struct<(array<8 x i16>)>> {hls.aggregate = [{compact = "auto", variable = "p"}]}, %arg1: memref<?xi16>) attributes {hls.inline_off, hls.orig_name = "fill", llvm.linkage = #llvm.linkage<internal>} {
    %c1023_i32 = arith.constant 1023 : i32
    %c7_i32 = arith.constant 7 : i32
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 2640 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = arith.shrsi %0, %c3_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %3 = "polygeist.subindex"(%arg0, %2) : (memref<330x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %4 = arith.andi %0, %c7_i32 : i32
      %5 = arith.extsi %4 : i32 to i64
      %6 = func.call @_ZNSt5arrayIsLm8EEixEm(%3, %5) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %7 = arith.andi %0, %c1023_i32 : i32
      %8 = arith.index_cast %7 : i32 to index
      %9 = memref.load %arg1[%8] : memref<?xi16>
      affine.store %9, %6[0] : memref<?xi16>
    }
    return
  }
  func.func private @_ZL5prodsPKsPSt5arrayIsLm8EE(%arg0: memref<?xi16>, %arg1: memref<300x!llvm.struct<(array<8 x i16>)>>) attributes {hls.inline_off, hls.orig_name = "prods", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    %c1023_i32 = arith.constant 1023 : i32
    %c7_i32 = arith.constant 7 : i32
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 2400 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = arith.shrsi %0, %c3_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %3 = "polygeist.subindex"(%arg1, %2) : (memref<300x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %4 = arith.andi %0, %c7_i32 : i32
      %5 = arith.extsi %4 : i32 to i64
      %6 = func.call @_ZNSt5arrayIsLm8EEixEm(%3, %5) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %7 = arith.andi %0, %c1023_i32 : i32
      %8 = arith.index_cast %7 : i32 to index
      %9 = memref.load %arg0[%8] : memref<?xi16>
      %10 = arith.extsi %9 : i16 to i32
      %11 = arith.addi %10, %c1_i32 : i32
      %12 = arith.trunci %11 : i32 to i16
      affine.store %12, %6[0] : memref<?xi16>
    }
    return
  }
  func.func private @_ZL4consPSt5arrayIsLm8EEiPs(%arg0: memref<300x!llvm.struct<(array<8 x i16>)>>, %arg1: i32, %arg2: memref<?xi16>) attributes {hls.inline_off, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c7_i32 = arith.constant 7 : i32
    %c300_i32 = arith.constant 300 : i32
    %c3_i32 = arith.constant 3 : i32
    %c2047_i32 = arith.constant 2047 : i32
    %c0_i32 = arith.constant 0 : i32
    %0 = affine.for %arg3 = 0 to 2048 iter_args(%arg4 = %c0_i32) -> (i32) {
      %2 = arith.index_cast %arg3 : index to i32
      %3 = arith.muli %2, %arg1 : i32
      %4 = arith.andi %3, %c2047_i32 : i32
      %5 = arith.shrsi %4, %c3_i32 : i32
      %6 = arith.remsi %5, %c300_i32 : i32
      %7 = arith.index_cast %6 : i32 to index
      %8 = "polygeist.subindex"(%arg0, %7) : (memref<300x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %9 = arith.andi %4, %c7_i32 : i32
      %10 = arith.extsi %9 : i32 to i64
      %11 = func.call @_ZNSt5arrayIsLm8EEixEm(%8, %10) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %12 = affine.load %11[0] : memref<?xi16>
      %13 = arith.extsi %12 : i16 to i32
      %14 = arith.addi %arg4, %13 : i32
      affine.yield %14 : i32
    }
    %1 = arith.trunci %0 : i32 to i16
    affine.store %1, %arg2[0] : memref<?xi16>
    return
  }
  func.func private @_ZN3hls6streamI3RowLi0EE5writeERKS1_(memref<?xi32>, memref<?x!llvm.struct<(array<64 x i16>)>>) attributes {hls.orig_name = "write", llvm.linkage = #llvm.linkage<external>}
  func.func @_ZNSt5arrayIsLm8EEixEm(%arg0: memref<?x!llvm.struct<(array<8 x i16>)>>, %arg1: i64) -> memref<?xi16> attributes {hls.orig_name = "operator[]", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<8xi16>
    %2 = arith.index_castui %arg1 : i64 to index
    %3 = "polygeist.subindex"(%1, %2) : (memref<8xi16>, index) -> memref<?xi16>
    return %3 : memref<?xi16>
  }
}
