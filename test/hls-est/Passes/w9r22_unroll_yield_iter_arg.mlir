// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule='cse=false' -o /dev/null
// W9r22-impl (2026-10-26): OPEN_ISSUES O207. The inner loop yields one of its
// own iter_args (`x = y`): `for (j < 3) { t = x + y; x = y; y = t; } out = x`.
// Upstream generateUnrolledLoop kept the yielded block argument, so every copy
// after the first read the initial value and the store was `out = in1`; the
// unroll now forwards it: out = in0 + 2 in1 (kernel
// coord/scratch/w9r22p/unrollbug/fib.cpp, installed cgeist 65aa635a).
// CHECK:      %[[A:.*]] = affine.load %arg0
// CHECK-NEXT: %[[B:.*]] = affine.load %arg1
// CHECK-NEXT: %[[S1:.*]] = arith.addi %[[A]], %[[B]]
// CHECK-NEXT: %[[S2:.*]] = arith.addi %[[B]], %[[S1]]
// CHECK:      affine.store %[[S2]], %arg2
// CHECK-NOT:  unrealized_conversion_cast
module {
  func.func @_Z3topPKiS0_Pi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    affine.for %arg3 = 0 to 1024 {
      %0 = affine.load %arg0[%arg3] : memref<1024xi32>
      %1 = affine.load %arg1[%arg3] : memref<1024xi32>
      %2:2 = affine.for %arg4 = 0 to 3 iter_args(%arg5 = %1, %arg6 = %0) -> (i32, i32) {
        %3 = arith.addi %arg6, %arg5 : i32
        affine.yield %3, %arg5 : i32, i32
      }
      affine.store %2#1, %arg2[%arg3] : memref<1024xi32>
    }
    return
  }
}
