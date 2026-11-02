// RUN: hls-est %s --split-struct-memrefs -o - 2> %t.err | FileCheck %s
// RUN: FileCheck %s --input-file=%t.err --check-prefix=WARN
// RUN: hls-est %s --symbol-privatize=exclude=st1 --symbol-dce --split-struct-memrefs --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=BRAM
// RUN: hls-est %s --symbol-privatize=exclude=st1 --symbol-dce --split-struct-memrefs --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=DBG

// Vitis disaggregates a local array of structs into one memory per member
// (VITIS_NOTES.md N29, w8b3_st1: `struct P { int a; short b; } s[1024]` is
// s_a 1024x32 = 2 BRAM_18K and s_b 1024x16 = 1 BRAM_18K, 3 in all).
// cgeist keeps one memref<1024 x !llvm.struct<(i32, i16)>> reached through
// polygeist.memref2pointer + llvm.getelementptr + llvm.load / llvm.store;
// --split-struct-memrefs gives each member its own memref and turns the
// pointer accesses into memref accesses.

// CHECK-LABEL: func.func @st1(
// CHECK-DAG:     %[[A:.*]] = memref.alloca() {hls.preserve, hls.struct_member = "s member 0", polygeist.varname = "s_0"} : memref<1024xi32>
// CHECK-DAG:     %[[B:.*]] = memref.alloca() {hls.preserve, hls.struct_member = "s member 1", polygeist.varname = "s_1"} : memref<1024xi16>
// CHECK-NOT:     !llvm.struct
// CHECK:         memref.store %{{.*}}, %[[A]][%{{.*}}] : memref<1024xi32>
// CHECK:         memref.store %{{.*}}, %[[B]][%{{.*}}] : memref<1024xi16>
// CHECK:         memref.load %[[A]][%{{.*}}] : memref<1024xi32>
// CHECK:         memref.load %[[B]][%{{.*}}] : memref<1024xi16>
// BRAM: Total BRAM: 3
// DBG: struct array split: s member 0 (--split-struct-memrefs)
// DBG: struct array split: s member 1 (--split-struct-memrefs)
func.func @st1(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: i32) {
  %c8 = arith.constant 8 : index
  %c5_i32 = arith.constant 5 : i32
  %c1023_i32 = arith.constant 1023 : i32
  %c3_i32 = arith.constant 3 : i32
  %alloca = memref.alloca() {hls.preserve, polygeist.varname = "s"} : memref<1024x!llvm.struct<(i32, i16)>>
  %0 = "polygeist.memref2pointer"(%alloca) : (memref<1024x!llvm.struct<(i32, i16)>>) -> !llvm.ptr
  affine.for %arg3 = 0 to 1024 {
    %1 = arith.muli %arg3, %c8 : index
    %2 = arith.index_cast %1 : index to i64
    %3 = llvm.getelementptr %0[%2] : (!llvm.ptr, i64) -> !llvm.ptr, i8
    %4 = affine.load %arg0[%arg3] : memref<1024xi32>
    llvm.store %4, %3 : i32, !llvm.ptr
    %5 = llvm.getelementptr %3[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16)>
    %6 = arith.shrsi %4, %c3_i32 : i32
    %7 = arith.trunci %6 : i32 to i16
    llvm.store %7, %5 : i16, !llvm.ptr
  }
  affine.for %arg3 = 0 to 1024 {
    %1 = arith.index_cast %arg3 : index to i32
    %2 = arith.muli %1, %arg2 : i32
    %3 = arith.andi %2, %c1023_i32 : i32
    %4 = arith.index_cast %3 : i32 to index
    %5 = arith.muli %4, %c8 : index
    %6 = arith.index_cast %5 : index to i64
    %7 = llvm.getelementptr %0[%6] : (!llvm.ptr, i64) -> !llvm.ptr, i8
    %8 = llvm.load %7 : !llvm.ptr -> i32
    %9 = arith.addi %3, %c5_i32 : i32
    %10 = arith.andi %9, %c1023_i32 : i32
    %11 = arith.index_cast %10 : i32 to index
    %12 = arith.muli %11, %c8 : index
    %13 = arith.index_cast %12 : index to i64
    %14 = llvm.getelementptr %0[%13] : (!llvm.ptr, i64) -> !llvm.ptr, i8
    %15 = llvm.getelementptr %14[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16)>
    %16 = llvm.load %15 : !llvm.ptr -> i16
    %17 = arith.extsi %16 : i16 to i32
    %18 = arith.addi %8, %17 : i32
    affine.store %18, %arg1[%arg3] : memref<1024xi32>
  }
  return
}

// A 2-D array reached through a row subindex, a member function called with
// an element (`operator=` / `upd(P &)`, inlined by the pass, as Vitis
// inlines them), and an array member (`unsigned char win[4][4]`), which adds
// its dimensions after the array's own. A struct copy (`P p = s[j]`) reads
// every member.
// CHECK-LABEL: func.func @rows(
// CHECK-DAG:     %[[W0:.*]] = memref.alloca() {{.*}}polygeist.varname = "w_0"} : memref<8x4x4xi8>
// CHECK-DAG:     %[[W1:.*]] = memref.alloca() {{.*}}polygeist.varname = "w_1"} : memref<8xi32>
// CHECK-DAG:     %[[S0:.*]] = memref.alloca() {{.*}}polygeist.varname = "s_0"} : memref<16x64xi32>
// CHECK-DAG:     %[[S1:.*]] = memref.alloca() {{.*}}polygeist.varname = "s_1"} : memref<16x64xi16>
// CHECK-NOT:     func.call @set
// CHECK:         memref.store %{{.*}}, %[[S0]][%{{.*}}, %{{.*}}] : memref<16x64xi32>
// CHECK:         memref.store %{{.*}}, %[[W0]][%{{.*}}, %{{.*}}, %{{.*}}] : memref<8x4x4xi8>
// CHECK:         memref.store %{{.*}}, %[[W1]][%{{.*}}] : memref<8xi32>
// CHECK:         memref.load %[[W0]][%{{.*}}, %{{.*}}, %{{.*}}] : memref<8x4x4xi8>
func.func @rows(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) {
  %c8 = arith.constant 8 : index
  %c20 = arith.constant 20 : index
  %c4_i32 = arith.constant 4 : i32
  %c3_i32 = arith.constant 3 : i32
  %c7_i32 = arith.constant 7 : i32
  %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "w"} : memref<8x!llvm.struct<(array<4 x array<4 x i8>>, i32)>>
  %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "s"} : memref<16x64x!llvm.struct<(i32, i16)>>
  affine.for %arg3 = 0 to 16 {
    affine.for %arg4 = 0 to 64 {
      %3 = "polygeist.subindex"(%alloca_1, %arg3) : (memref<16x64x!llvm.struct<(i32, i16)>>, index) -> memref<64x!llvm.struct<(i32, i16)>>
      %4 = "polygeist.subindex"(%3, %arg4) : (memref<64x!llvm.struct<(i32, i16)>>, index) -> memref<?x!llvm.struct<(i32, i16)>>
      %9 = affine.load %arg0[%arg4 + %arg3 * 64] : memref<1024xi32>
      func.call @set(%4, %9) : (memref<?x!llvm.struct<(i32, i16)>>, i32) -> ()
    }
  }
  %0 = "polygeist.memref2pointer"(%alloca_0) : (memref<8x!llvm.struct<(array<4 x array<4 x i8>>, i32)>>) -> !llvm.ptr
  affine.for %arg3 = 0 to 8 {
    %3 = arith.index_cast %arg3 : index to i32
    %4 = arith.muli %arg3, %c20 : index
    %5 = arith.index_cast %4 : index to i64
    %6 = llvm.getelementptr %0[%5] : (!llvm.ptr, i64) -> !llvm.ptr, i8
    affine.for %arg4 = 0 to 4 {
      %8 = arith.index_cast %arg4 : index to i32
      %9 = arith.muli %8, %c4_i32 : i32
      affine.for %arg5 = 0 to 4 {
        %10 = arith.index_cast %arg5 : index to i32
        %11 = affine.load %arg0[%arg5 + %arg4 * 4 + %arg3 * 16] : memref<1024xi32>
        %12 = arith.trunci %11 : i32 to i8
        %13 = arith.addi %9, %10 : i32
        %14 = llvm.getelementptr %6[%13] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        llvm.store %12, %14 : i8, !llvm.ptr
      }
    }
    %7 = llvm.getelementptr %6[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<4 x array<4 x i8>>, i32)>
    llvm.store %3, %7 : i32, !llvm.ptr
  }
  affine.for %arg3 = 0 to 1024 {
    %3 = arith.index_cast %arg3 : index to i32
    %27 = arith.andi %3, %c7_i32 : i32
    %28 = arith.index_cast %27 : i32 to index
    %29 = arith.muli %28, %c20 : index
    %30 = arith.index_cast %29 : index to i64
    %31 = llvm.getelementptr %0[%30] : (!llvm.ptr, i64) -> !llvm.ptr, i8
    %32 = arith.shrsi %3, %c3_i32 : i32
    %33 = arith.andi %32, %c3_i32 : i32
    %34 = arith.andi %3, %c3_i32 : i32
    %35 = arith.muli %33, %c4_i32 : i32
    %36 = arith.addi %35, %34 : i32
    %37 = llvm.getelementptr %31[%36] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    %38 = llvm.load %37 : !llvm.ptr -> i8
    %39 = arith.extui %38 : i8 to i32
    affine.store %39, %arg1[%arg3] : memref<1024xi32>
  }
  return
}
func.func private @set(%arg0: memref<?x!llvm.struct<(i32, i16)>>, %arg1: i32) {
  %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(i32, i16)>>) -> !llvm.ptr
  llvm.store %arg1, %0 : i32, !llvm.ptr
  %3 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16)>
  %4 = arith.trunci %arg1 : i32 to i16
  llvm.store %4, %3 : i16, !llvm.ptr
  return
}

// A pointer to the array that escapes into an external call cannot be
// followed: the array stays whole, with a warning.
// WARN: warning: struct array not split into members: struct pointer used by func.call
// CHECK-LABEL: func.func @escapes(
// CHECK:         memref.alloca() {polygeist.varname = "e"} : memref<4x!llvm.struct<(i32, i16)>>
func.func @escapes() {
  %e = memref.alloca() {polygeist.varname = "e"} : memref<4x!llvm.struct<(i32, i16)>>
  %p = "polygeist.memref2pointer"(%e) : (memref<4x!llvm.struct<(i32, i16)>>) -> !llvm.ptr
  func.call @ext(%p) : (!llvm.ptr) -> ()
  return
}
func.func private @ext(!llvm.ptr)
