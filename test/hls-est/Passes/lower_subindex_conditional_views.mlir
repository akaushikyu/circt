// RUN: hls-est %s --lower-polygeist-subindex 2>&1 | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex=sink-conditional-views=false 2>&1 | FileCheck %s --check-prefix=OFF

// OPEN_ISSUES O84 (b): the conditional operator on lvalues of a class type,
// `T prev = (j == 0) ? B[i][j] : loc[i][j - 1];` (reproducer sel1.cpp), is an
// if yielding one of two element views (`&B[i][j]` as memref<?xi16>) and a
// load of the yielded view. The load moves into the arms, where it names its
// array; the element views (same rank, dynamic first dimension) are lowered
// like offset views, also through the row view they are taken of.

// CHECK-LABEL: func.func @cond_lvalue
// CHECK-NOT: polygeist.subindex
// CHECK: affine.if #{{.*}}(%[[J:.*]]) -> i16 {
// CHECK:   %[[A:.*]] = affine.load %arg1[%[[I:.*]], %[[J]]] : memref<64x64xi16>
// CHECK:   affine.yield %[[A]] : i16
// CHECK: } else {
// CHECK:   %[[B:.*]] = memref.load %{{.*}}[%[[I]], %{{.*}}] : memref<64x64xi16>
// CHECK:   affine.yield %[[B]] : i16
// CHECK: }
// CHECK-NOT: warning
// OFF: warning: polygeist.subindex not lowered
func.func @cond_lvalue(%arg0: memref<64x64xi16>, %arg1: memref<64x64xi16>) {
  %c-1_i32 = arith.constant -1 : i32
  %loc = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "loc"}], polygeist.varname = "loc"} : memref<64x64xi16>
  affine.for %i = 0 to 64 {
    %0 = "polygeist.subindex"(%arg1, %i) : (memref<64x64xi16>, index) -> memref<64xi16>
    %1 = "polygeist.subindex"(%loc, %i) : (memref<64x64xi16>, index) -> memref<64xi16>
    affine.for %j = 0 to 64 {
      %2 = arith.index_cast %j : index to i32
      %3 = affine.if affine_set<(d0) : (d0 == 0)>(%j) -> memref<?xi16> {
        %10 = "polygeist.subindex"(%0, %j) : (memref<64xi16>, index) -> memref<?xi16>
        affine.yield %10 : memref<?xi16>
      } else {
        %10 = arith.addi %2, %c-1_i32 : i32
        %11 = arith.index_cast %10 : i32 to index
        %12 = "polygeist.subindex"(%1, %11) : (memref<64xi16>, index) -> memref<?xi16>
        affine.yield %12 : memref<?xi16>
      }
      %4 = affine.load %3[0] : memref<?xi16>
      affine.store %4, %loc[%i, %j] : memref<64x64xi16>
    }
  }
  return
}

// A select between two element views (the same operator on scalars of a
// type cgeist selects with arith.select): an scf.if with a load per arm.
// CHECK-LABEL: func.func @select_views
// CHECK: %[[V:.*]] = scf.if %{{.*}} -> (i32) {
// CHECK:   memref.load %arg0[%{{.*}}] : memref<16xi32>
// CHECK: } else {
// CHECK:   memref.load %arg1[%{{.*}}] : memref<16xi32>
// CHECK: }
// CHECK: memref.store %[[V]], %arg2
func.func @select_views(%arg0: memref<16xi32>, %arg1: memref<16xi32>, %arg2: memref<16xi32>, %c: i1, %k: index) {
  %a = "polygeist.subindex"(%arg0, %k) : (memref<16xi32>, index) -> memref<?xi32>
  %b = "polygeist.subindex"(%arg1, %k) : (memref<16xi32>, index) -> memref<?xi32>
  %s = arith.select %c, %a, %b : memref<?xi32>
  %c0 = arith.constant 0 : index
  %v = memref.load %s[%c0] : memref<?xi32>
  memref.store %v, %arg2[%k] : memref<16xi32>
  return
}

// Both operands views of one array (`c ? A[i] : A[i + 1]`, W9 round 8 review
// defect 3, kernel w9r8rev c1_selsame.cpp: Vitis 1 BRAM, RAM_AUTO_1R1W): one
// access at the selected index, not a load per arm (which counted two
// exclusive reads as port demand: RAM_1WNR, 3 BRAM).
// CHECK-LABEL: func.func @same_array_if
// CHECK: %[[IX:.*]] = scf.if %{{.*}} -> (index) {
// CHECK:   scf.yield %{{.*}} : index
// CHECK: } else {
// CHECK:   scf.yield %{{.*}} : index
// CHECK: }
// CHECK: arith.addi %{{.*}}, %[[IX]] : index
// CHECK: %[[V:.*]] = memref.load %{{.*}}[%{{.*}}] : memref<1024xi16>
// CHECK-NEXT: affine.store %[[V]], %arg1
func.func @same_array_if(%arg0: memref<1024xi32>, %arg1: memref<1024xi16>) {
  %c1_i32 = arith.constant 1 : i32
  %A = memref.alloca() {polygeist.varname = "A"} : memref<1024xi16>
  affine.for %i = 0 to 1020 {
    %c = affine.load %arg0[%i] : memref<1024xi32>
    %b = arith.trunci %c : i32 to i1
    %0 = scf.if %b -> (memref<?xi16>) {
      %s = "polygeist.subindex"(%A, %i) : (memref<1024xi16>, index) -> memref<?xi16>
      scf.yield %s : memref<?xi16>
    } else {
      %ii = arith.index_cast %i : index to i32
      %n = arith.addi %ii, %c1_i32 : i32
      %ni = arith.index_cast %n : i32 to index
      %s = "polygeist.subindex"(%A, %ni) : (memref<1024xi16>, index) -> memref<?xi16>
      scf.yield %s : memref<?xi16>
    }
    %v = affine.load %0[0] : memref<?xi16>
    affine.store %v, %arg1[%i] : memref<1024xi16>
  }
  return
}

// The select form on one array: a select of the two indices.
// CHECK-LABEL: func.func @same_array_select
// CHECK: %[[IX:.*]] = arith.select %{{.*}}, %{{.*}}, %{{.*}} : index
// CHECK: %[[O:.*]] = arith.addi %{{.*}}, %[[IX]] : index
// CHECK: %[[V:.*]] = memref.load %arg0[%[[O]]] : memref<16xi32>
// CHECK-NOT: scf.if
// CHECK: memref.store %[[V]], %arg1
func.func @same_array_select(%arg0: memref<16xi32>, %arg1: memref<16xi32>, %c: i1, %k: index, %m: index) {
  %a = "polygeist.subindex"(%arg0, %k) : (memref<16xi32>, index) -> memref<?xi32>
  %b = "polygeist.subindex"(%arg0, %m) : (memref<16xi32>, index) -> memref<?xi32>
  %s = arith.select %c, %a, %b : memref<?xi32>
  %c0 = arith.constant 0 : index
  %v = memref.load %s[%c0] : memref<?xi32>
  memref.store %v, %arg1[%k] : memref<16xi32>
  return
}
