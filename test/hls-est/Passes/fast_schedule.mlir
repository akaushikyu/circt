// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=fast-threshold=0 --bram-analysis | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=fast-threshold=0 -o - | FileCheck %s --check-prefix=SCHED
//
// The greedy resource-bound modulo scheduler (every loop with fast-threshold=0;
// by default only bodies with more than 150 resource-limited ops) must give the
// same BRAM total as the simplex-based scheduler. The kernel exercises a
// port-limited loop (three reads of `tab` per iteration through one read port:
// II 3, the reads spread over the three phases, so `tab` stays single-port), a
// loop-carried accumulation (a recurrence through iter_args), and a
// read-modify-write of `acc` at II 1 (its load and store share the one phase,
// so `acc` needs two ports and the narrower x16 TDP configuration).
//
// CHECK: Total BRAM: 3
//
// SCHED: loopschedule.pipeline II = {{ *}}1
// SCHED: loopschedule.pipeline II = {{ *}}3
// SCHED: loopschedule.pipeline II = {{ *}}1
// SCHED: loopschedule.pipeline II = {{ *}}1

func.func @kernel(%arg0: memref<256xi32>, %out: memref<256xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %c3_i32 = arith.constant 3 : i32
  %tab = memref.alloca() {hls.preserve, polygeist.varname = "tab"} : memref<256xi32>
  %acc = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<256xi32>
  affine.for %i = 0 to 256 {
    %0 = affine.load %arg0[%i] : memref<256xi32>
    affine.store %0, %tab[%i] : memref<256xi32>
    affine.store %0, %acc[%i] : memref<256xi32>
  }
  %sum = affine.for %i = 1 to 255 iter_args(%s = %c0_i32) -> i32 {
    %0 = affine.load %tab[%i - 1] : memref<256xi32>
    %1 = affine.load %tab[%i] : memref<256xi32>
    %2 = affine.load %tab[%i + 1] : memref<256xi32>
    %3 = arith.addi %0, %1 : i32
    %4 = arith.addi %3, %2 : i32
    %5 = arith.addi %s, %4 : i32
    affine.yield %5 : i32
  }
  affine.for %i = 0 to 256 {
    %0 = affine.load %acc[%i] : memref<256xi32>
    %1 = arith.muli %0, %c3_i32 : i32
    affine.store %1, %acc[%i] : memref<256xi32>
  }
  affine.for %i = 0 to 256 {
    %0 = affine.load %acc[%i] : memref<256xi32>
    %1 = arith.addi %0, %sum : i32
    affine.store %1, %out[%i] : memref<256xi32>
  }
  return
}
