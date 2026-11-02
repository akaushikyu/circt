// RUN: hls-est %s --auto-pipeline-unroll=emit-remarks 2>&1 | FileCheck %s
// RUN: hls-est %s --auto-pipeline-unroll --config-set tool.hls.pipeline_decision.partial_unroll_runtime_loops=false | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N103: a user `unroll factor=F` on an scf.for with a run-time
// trip count becomes a loop of step F * step holding F copies of the body;
// copy u > 0 runs under iv + u * step < ub and passes the loop-carried
// values on unchanged when skipped. Inside a user-pipelined loop the loop
// stays rolled (Vitis [HLS 214-187], class_ece8893 shibao_su lab3).

// CHECK: remark: user unroll: run-time trip count, by factor 3 with guarded copies (VITIS_NOTES N103)
// CHECK: remark: user unroll: run-time trip count inside a pipelined loop, left rolled
// CHECK-LABEL: func.func @sum
// CHECK: scf.for %[[IV:.*]] = %{{.*}} to %[[UB:.*]] step %c3{{.*}} iter_args(%[[A:.*]] = %{{.*}}) -> (i32)
// CHECK: memref.load %{{.*}}[%[[IV]]]
// CHECK: %[[S0:.*]] = arith.addi %[[A]]
// CHECK: %[[IV1:.*]] = arith.addi %[[IV]], %{{.*}} : index
// CHECK: %[[IN1:.*]] = arith.cmpi slt, %[[IV1]], %[[UB]] : index
// CHECK: %[[R1:.*]] = scf.if %[[IN1]] -> (i32)
// CHECK: memref.load %{{.*}}[%[[IV1]]]
// CHECK: } else {
// CHECK-NEXT: scf.yield %[[S0]] : i32
// CHECK: %[[IN2:.*]] = arith.cmpi slt
// CHECK: %[[R2:.*]] = scf.if %[[IN2]] -> (i32)
// CHECK: scf.yield %[[R2]] : i32
// CHECK: hls.unroll_partial = 3 : i64
// CHECK-LABEL: func.func @nested
// CHECK: scf.for
// CHECK-SAME: step %c1

// OFF-LABEL: func.func @sum
// OFF: scf.for
// OFF-SAME: step %c1
// OFF-NOT: scf.if
// OFF: hls.unroll = [{factor = 3 : i32

module {
  func.func @sum(%a: memref<256xi32>, %lo: index, %hi: index) -> i32 {
    %c1 = arith.constant 1 : index
    %c0_i32 = arith.constant 0 : i32
    %r = scf.for %i = %lo to %hi step %c1 iter_args(%s = %c0_i32) -> (i32) {
      %v = memref.load %a[%i] : memref<256xi32>
      %n = arith.addi %s, %v : i32
      scf.yield %n : i32
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 3 : i32, skip_exit_check = false}]}
    return %r : i32
  }
  func.func @nested(%a: memref<256xi32>, %p: memref<17xindex>) {
    %c1 = arith.constant 1 : index
    %c7 = arith.constant 7 : i32
    affine.for %k = 0 to 16 {
      %lo = affine.load %p[%k] : memref<17xindex>
      %hi = affine.load %p[%k + 1] : memref<17xindex>
      scf.for %i = %lo to %hi step %c1 {
        memref.store %c7, %a[%i] : memref<256xi32>
      } {hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
