// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=fast-threshold=0 -o - | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=fast-ops-threshold=1 -o - | FileCheck %s
//
// Recurrences through iter_args whose latency sum is far above ResMinII (one
// read per iteration through one port: ResMinII 1). The greedy scheduler
// (fast-threshold=0) finds the recurrence-feasible II by galloping plus
// bisection over the positive-cycle test instead of trying every II from
// ResMinII upwards; it must land exactly on the recurrence bound, the same II
// the simplex scheduler (second RUN line) produces. Latencies: mulf 4, addf 5,
// divf 15 (f32, VITIS_NOTES N78). The third RUN line sends every problem to the greedy scheduler by
// its operation count (fast-ops-threshold=1, the rule for fully unrolled
// bodies whose dense simplex tableau would not fit in memory). Each
// infeasible II is rejected as soon as the relaxing predecessors close a
// cycle, which must not change the II found.
//
// CHECK: loopschedule.pipeline II = {{ *}}4
// CHECK: loopschedule.pipeline II = {{ *}}9
// CHECK: loopschedule.pipeline II = {{ *}}12
// CHECK: loopschedule.pipeline II = {{ *}}29

func.func @rec(%a: memref<256xf32>, %k: f32) -> f32 {
  // mulf: 4
  %r0 = affine.for %i = 0 to 256 iter_args(%s = %k) -> f32 {
    %0 = affine.load %a[%i] : memref<256xf32>
    %1 = arith.mulf %s, %0 : f32
    affine.yield %1 : f32
  }
  // mulf + addf: 9
  %r1 = affine.for %i = 0 to 256 iter_args(%s = %r0) -> f32 {
    %0 = affine.load %a[%i] : memref<256xf32>
    %1 = arith.mulf %s, %0 : f32
    %2 = arith.addf %1, %0 : f32
    affine.yield %2 : f32
  }
  // 3 mulf: 12
  %r2 = affine.for %i = 0 to 256 iter_args(%s = %r1) -> f32 {
    %0 = affine.load %a[%i] : memref<256xf32>
    %1 = arith.mulf %s, %0 : f32
    %2 = arith.mulf %1, %0 : f32
    %3 = arith.mulf %2, %0 : f32
    affine.yield %3 : f32
  }
  // addf + addf + mulf + divf: 5 + 5 + 4 + 15 = 29
  %r3 = affine.for %i = 0 to 256 iter_args(%s = %r2) -> f32 {
    %0 = affine.load %a[%i] : memref<256xf32>
    %1 = arith.addf %s, %0 : f32
    %2 = arith.addf %1, %0 : f32
    %3 = arith.mulf %2, %0 : f32
    %4 = arith.divf %3, %0 : f32
    affine.yield %4 : f32
  }
  return %r3 : f32
}
