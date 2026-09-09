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
