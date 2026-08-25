// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=fast-threshold=0 --config-set scheduling.modulo.recurrence_repair_rounds=64 -o - | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=fast-threshold=0 -o - | FileCheck %s --check-prefix=NOREPAIR
//
// The greedy modulo scheduler (fast-threshold=0) places a loop-carried
// recurrence whose head has no same-iteration predecessor. Eight reads of
// one memory share its two ports (ResMinII 4) and feed an add tree; the
// recurrence is the iter_arg: mulf (4) + addf (5) = 9 cycles, so II 9
// (VITIS_NOTES N39: what Vitis computes for such a reduction, and what the
// simplex scheduler of the second RUN line gives). The list schedule
// places the mulf at time 0 and delays the reads for their ports, so the
// final addf of the iteration comes too late for the mulf of the next one.
// scheduling.modulo.recurrence_repair_rounds (first RUN line: 64) moves the
// mulf later to what the carried edge demands and places the body again:
// II 9. Without the repair (NOREPAIR, the default 0) the II is bumped until
// the late addf fits (OPEN_ISSUES O56: II 8 for Vitis' 2 on class_ece8893
// nayan lab2). The repair is off by default: on the catalogue it only moves
// nayan / sreenidhi / vishnu lab2, whose Q / K become right while attention /
// V over-count until R-cmpd (OPEN_ISSUES O51 (a)) is modelled.
//
// CHECK: loopschedule.pipeline II = {{ *}}9{{ }}
// NOREPAIR: loopschedule.pipeline II = {{ *}}{{1[0-9]|2[0-9]}}{{ }}

func.func @red(%a: memref<512xf32>, %k: f32) -> f32 {
  %r = affine.for %i = 0 to 64 iter_args(%s = %k) -> f32 {
    %0 = affine.load %a[%i * 8] : memref<512xf32>
    %1 = affine.load %a[%i * 8 + 1] : memref<512xf32>
    %2 = affine.load %a[%i * 8 + 2] : memref<512xf32>
    %3 = affine.load %a[%i * 8 + 3] : memref<512xf32>
    %4 = affine.load %a[%i * 8 + 4] : memref<512xf32>
    %5 = affine.load %a[%i * 8 + 5] : memref<512xf32>
    %6 = affine.load %a[%i * 8 + 6] : memref<512xf32>
    %7 = affine.load %a[%i * 8 + 7] : memref<512xf32>
    %t0 = arith.addf %0, %1 : f32
    %t1 = arith.addf %2, %3 : f32
    %t2 = arith.addf %4, %5 : f32
    %t3 = arith.addf %6, %7 : f32
    %u0 = arith.addf %t0, %t1 : f32
    %u1 = arith.addf %t2, %t3 : f32
    %t = arith.addf %u0, %u1 : f32
    %m = arith.mulf %s, %k : f32
    %n = arith.addf %m, %t : f32
    affine.yield %n : f32
  }
  return %r : f32
}
