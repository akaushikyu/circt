// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// Calls back into the function that owns a pipelined loop (direct or mutual
// recursion) must neither unroll that loop into itself (use-after-erase) nor
// make the loop forest recurse forever: a function is entered at most once
// per call chain, both when the forest is built and when the loops under a
// pipelined loop are collected for unrolling.

// Self recursion: the call is opaque (no inner loop reachable), the loop is
// pipelined as it is and survives with its call.
// CHECK-LABEL: func.func @rec
// CHECK:       affine.for %{{.*}} = 0 to 16 iter_args
// CHECK:         call @rec
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @rec(%a: memref<8x16xi32>, %i: index) -> i32 {
  %c0 = arith.constant 0 : i32
  %0 = affine.for %j = 0 to 16 iter_args(%s = %c0) -> (i32) {
    %1 = affine.load %a[%i, %j] : memref<8x16xi32>
    %2 = func.call @rec(%a, %j) : (memref<8x16xi32>, index) -> i32
    %3 = arith.addi %1, %2 : i32
    %4 = arith.addi %s, %3 : i32
    affine.yield %4 : i32
  }
  return %0 : i32
}

// Mutual recursion: @fa is decided first; its loop is pipelined and @fb's
// loop (reached through the call) is unrolled for it, recorded in
// hls.auto_unrolled. The call from @fb back to @fa does not re-enter @fa.
// CHECK-LABEL: func.func @fa
// CHECK:       affine.for %{{.*}} = 0 to 16 iter_args
// CHECK:         call @fb
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = {{.*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-LABEL: func.func @fb
// CHECK-NOT:     affine.for
// CHECK-COUNT-16: call @fa
// CHECK:         return
func.func @fa(%a: memref<8x16xi32>, %i: index) -> i32 {
  %c0 = arith.constant 0 : i32
  %0 = affine.for %j = 0 to 16 iter_args(%s = %c0) -> (i32) {
    %1 = affine.load %a[%i, %j] : memref<8x16xi32>
    %2 = func.call @fb(%a, %j) : (memref<8x16xi32>, index) -> i32
    %3 = arith.addi %1, %2 : i32
    %4 = arith.addi %s, %3 : i32
    affine.yield %4 : i32
  }
  return %0 : i32
}
func.func @fb(%a: memref<8x16xi32>, %i: index) -> i32 {
  %c0 = arith.constant 0 : i32
  %0 = affine.for %j = 0 to 16 iter_args(%s = %c0) -> (i32) {
    %1 = affine.load %a[%i, %j] : memref<8x16xi32>
    %2 = func.call @fa(%a, %j) : (memref<8x16xi32>, index) -> i32
    %3 = arith.addi %1, %2 : i32
    %4 = arith.addi %s, %3 : i32
    affine.yield %4 : i32
  }
  return %0 : i32
}

// A pipelined caller unrolls the loops of its callees, a self-recursive
// callee's loop included (once: the recursive call inside it is not followed
// again), and never comes back to its own loop.
// CHECK-LABEL: func.func @rec2
// CHECK-NOT:     affine.for
// CHECK-LABEL: func.func @caller
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = {{.*}}}, {factor = 16 : i64, loc = {{.*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @callee(%a: memref<8x16xi32>, %i: index) -> i32 {
  %c0 = arith.constant 0 : i32
  %0 = affine.for %j = 0 to 16 iter_args(%s = %c0) -> (i32) {
    %1 = affine.load %a[%i, %j] : memref<8x16xi32>
    %2 = arith.addi %s, %1 : i32
    affine.yield %2 : i32
  }
  return %0 : i32
}
func.func @rec2(%a: memref<8x16xi32>, %i: index) -> i32 {
  %c0 = arith.constant 0 : i32
  %0 = affine.for %j = 0 to 16 iter_args(%s = %c0) -> (i32) {
    %1 = affine.load %a[%i, %j] : memref<8x16xi32>
    %2 = func.call @rec2(%a, %j) : (memref<8x16xi32>, index) -> i32
    %3 = arith.addi %1, %2 : i32
    %4 = arith.addi %s, %3 : i32
    affine.yield %4 : i32
  }
  return %0 : i32
}
func.func @caller(%a: memref<8x16xi32>, %out: memref<8xi32>, %out2: memref<8xi32>) {
  affine.for %i = 0 to 8 {
    %0 = func.call @callee(%a, %i) : (memref<8x16xi32>, index) -> i32
    %1 = func.call @rec2(%a, %i) : (memref<8x16xi32>, index) -> i32
    affine.store %0, %out[%i] : memref<8xi32>
    affine.store %1, %out2[%i] : memref<8xi32>
  }
  return
}
