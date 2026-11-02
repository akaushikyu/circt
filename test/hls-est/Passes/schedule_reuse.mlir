// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug --mlir-pass-statistics -o %t.on.mlir > %t.on.out 2> %t.on.err
// RUN: FileCheck %s --input-file=%t.on.out
// RUN: FileCheck %s --check-prefix=REUSE --input-file=%t.on.err
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule=reuse-schedules=false --bram-analysis --bram-debug --mlir-pass-statistics -o %t.off.mlir > %t.off.out 2> %t.off.err
// RUN: FileCheck %s --input-file=%t.off.out
// RUN: FileCheck %s --check-prefix=SOLVE --input-file=%t.off.err
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule=verify-schedule-reuse=true --bram-analysis --mlir-pass-statistics -o /dev/null 2>&1 | FileCheck %s --check-prefix=VERIFY
// RUN: sed -e 's/hls.scheduler = "[^"]*"//' %t.on.mlir > %t.on.stripped
// RUN: sed -e 's/hls.scheduler = "[^"]*"//' %t.off.mlir > %t.off.stripped
// RUN: diff %t.on.stripped %t.off.stripped

// --convert-affine-to-loopschedule gives a loop whose modulo scheduling
// problem is identical to an already scheduled loop's (same operations in the
// same order, operator latencies, resource limits, dependences and distances;
// ScheduleSignature) that loop's II and start times instead of solving it
// again (option reuse-schedules, default on). Both schedulers are
// deterministic functions of the problem, so the IR is the same as with the
// option off apart from the hls.scheduler debug note (the diff above), and the
// estimate is unchanged. User-unrolled copies of a pipelined loop are the
// common case (forgebench diff_orders_*, mlp, mult_op_p1, conv_B / conv_C,
// diff_dims_module_large).
//
// @copies: three reductions over different arrays of the same type (identical
// problems; the second and third reuse the first's schedule) and one over an
// f64 array (other operator types and an II of 8: solved on its own, and placed again by the
// greedy scheduler with its floating-point unit limits, VITIS_NOTES N135, at the II of its
// chained dadd latency 7 + 1: the accumulated value comes from a dmul, N160 (b), kernel
// w9r21rev_r2d_scalar1, Vitis II 8; W9 round 21 review fixes). Each
// array is read once per cycle: RAM_1P, 1024 x 32 bits = 2 BRAM_18K, and
// 1024 x 64 bits = 4.

// CHECK: Total BRAM: 10

// REUSE: pipeline @ {{.*}}:[[L0:[0-9]+]]:{{[0-9]+}} in @copies: ii=1 {{.*}} scheduler=simplex{{$}}
// REUSE: pipeline @ {{.*}} in @copies: ii=1 {{.*}} scheduler=simplex (reused from {{.*}}:[[L0]]:{{[0-9]+}}){{$}}
// REUSE: pipeline @ {{.*}} in @copies: ii=1 {{.*}} scheduler=simplex (reused from {{.*}}:[[L0]]:{{[0-9]+}}){{$}}
// REUSE: pipeline @ {{.*}} in @copies: ii=8 {{.*}} scheduler=greedy (floating-point units at the simplex II) memory_recurrence=N160 ii>=8 {{.*}}
// REUSE: AffineToLoopSchedule
// REUSE: (S) 2 schedules-reused
// REUSE-NEXT: (S) 2 schedules-solved

// SOLVE-NOT: reused from
// SOLVE: (S) 0 schedules-reused
// SOLVE-NEXT: (S) 4 schedules-solved

// With verify-schedule-reuse the reused loops are solved again and compared.
// VERIFY-NOT: schedule reuse mismatch
// VERIFY: (S) 0 schedule-reuse-mismatches
// VERIFY-NEXT: (S) 2 schedules-reused
// VERIFY-NEXT: (S) 4 schedules-solved

func.func @copies(%a: memref<1024xi32>, %b: memref<1024xi32>, %c: memref<1024xi32>, %d: memref<1024xf64>, %o: memref<4xi32>, %of: memref<1xf64>) {
  %c0_i32 = arith.constant 0 : i32
  %f0 = arith.constant 0.0 : f64
  %la = memref.alloca() {hls.preserve} : memref<1024xi32>
  %lb = memref.alloca() {hls.preserve} : memref<1024xi32>
  %lc = memref.alloca() {hls.preserve} : memref<1024xi32>
  %ld = memref.alloca() {hls.preserve} : memref<1024xf64>
  %sa = affine.for %i = 0 to 1024 iter_args(%acc = %c0_i32) -> (i32) {
    %x = affine.load %la[%i] : memref<1024xi32>
    %y = arith.muli %x, %x : i32
    %s = arith.addi %acc, %y : i32
    affine.yield %s : i32
  }
  affine.store %sa, %o[0] : memref<4xi32>
  %sb = affine.for %i = 0 to 1024 iter_args(%acc = %c0_i32) -> (i32) {
    %x = affine.load %lb[%i] : memref<1024xi32>
    %y = arith.muli %x, %x : i32
    %s = arith.addi %acc, %y : i32
    affine.yield %s : i32
  }
  affine.store %sb, %o[1] : memref<4xi32>
  %sc = affine.for %i = 0 to 1024 iter_args(%acc = %c0_i32) -> (i32) {
    %x = affine.load %lc[%i] : memref<1024xi32>
    %y = arith.muli %x, %x : i32
    %s = arith.addi %acc, %y : i32
    affine.yield %s : i32
  }
  affine.store %sc, %o[2] : memref<4xi32>
  %sd = affine.for %i = 0 to 1024 iter_args(%acc = %f0) -> (f64) {
    %x = affine.load %ld[%i] : memref<1024xf64>
    %y = arith.mulf %x, %x : f64
    %s = arith.addf %acc, %y : f64
    affine.yield %s : f64
  }
  affine.store %sd, %of[0] : memref<1xf64>
  return
}
