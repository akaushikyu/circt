// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=forward-stores=true --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=forward-stores=true -o - | FileCheck %s --check-prefix=SCHED
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s --check-prefix=REPORT
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=forward-stores=false --bram-analysis | FileCheck %s --check-prefix=NOFWD

// Store-to-load forwarding and dead-store elimination on the unrolled body
// (VITIS_NOTES.md N4: R and W per iteration are counted "after unrolling,
// CSE, LICM"; T2 storage-model review, finding D2).
//
// @acc: `acc[i] = 0; for k (unrolled 8) acc[i] += alpha * A[i][k]` is, after
// unrolling, 9 stores and 8 loads of acc[i] per iteration. Each load reads
// what the store just before it wrote (same address, nothing in between may
// alias), so Vitis forwards the value and every store but the last is
// overwritten before anything reads it: one store per iteration, no load.
// acc then has one live port in each loop -> x36 wide 64x32 = 1 BRAM, and the
// loop is bound by the 8 interface reads (2 ports) at II 4. Without the
// cleanup the body stores to acc 9 times, acc is not replicable, the loop
// runs at II 9 and acc is a true-dual-port 64x32 RAM = 2 BRAM.
// `forward-stores` is ON by default since W1c (MEMOS.md M6, decision #5; the
// fifth RUN line checks the default report, the last one =false = NOFWD): per
// array it is what Vitis does where the array is live (an unrolled accumulator
// becomes one store; attention Q/K become replicable, 3 copies = Vitis); it
// would also replicate arrays Vitis deletes, which the default pipeline's
// --dead-memory-elimination removes first (OPEN_ISSUES.md O7).
// @mayalias: `b[i] = v; x = b[j]; b[i] = w` with i and j both functions of
// the flattened induction variable: the difference of the two addresses is
// not a constant, so the load may read either store's address. Nothing is
// forwarded and the first store is not dead: both stores and the load stay.
// @disjoint: `b[2i] = v; x = b[2i+1]`: the addresses differ by the constant
// 1, so the load is not forwarded (it reads other memory), and nothing is
// dead.

module {
  func.func @acc(%A: memref<64x8xf32>, %alpha: f32, %out: memref<64xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    %acc = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<64xf32>
    affine.for %i = 0 to 64 {
      affine.store %cst, %acc[%i] : memref<64xf32>
      %l0 = affine.load %acc[%i] : memref<64xf32>
      %b0 = affine.load %A[%i, 0] : memref<64x8xf32>
      %m0 = arith.mulf %alpha, %b0 : f32
      %a0 = arith.addf %l0, %m0 : f32
      affine.store %a0, %acc[%i] : memref<64xf32>
      %l1 = affine.load %acc[%i] : memref<64xf32>
      %b1 = affine.load %A[%i, 1] : memref<64x8xf32>
      %m1 = arith.mulf %alpha, %b1 : f32
      %a1 = arith.addf %l1, %m1 : f32
      affine.store %a1, %acc[%i] : memref<64xf32>
      %l2 = affine.load %acc[%i] : memref<64xf32>
      %b2 = affine.load %A[%i, 2] : memref<64x8xf32>
      %m2 = arith.mulf %alpha, %b2 : f32
      %a2 = arith.addf %l2, %m2 : f32
      affine.store %a2, %acc[%i] : memref<64xf32>
      %l3 = affine.load %acc[%i] : memref<64xf32>
      %b3 = affine.load %A[%i, 3] : memref<64x8xf32>
      %m3 = arith.mulf %alpha, %b3 : f32
      %a3 = arith.addf %l3, %m3 : f32
      affine.store %a3, %acc[%i] : memref<64xf32>
      %l4 = affine.load %acc[%i] : memref<64xf32>
      %b4 = affine.load %A[%i, 4] : memref<64x8xf32>
      %m4 = arith.mulf %alpha, %b4 : f32
      %a4 = arith.addf %l4, %m4 : f32
      affine.store %a4, %acc[%i] : memref<64xf32>
      %l5 = affine.load %acc[%i] : memref<64xf32>
      %b5 = affine.load %A[%i, 5] : memref<64x8xf32>
      %m5 = arith.mulf %alpha, %b5 : f32
      %a5 = arith.addf %l5, %m5 : f32
      affine.store %a5, %acc[%i] : memref<64xf32>
      %l6 = affine.load %acc[%i] : memref<64xf32>
      %b6 = affine.load %A[%i, 6] : memref<64x8xf32>
      %m6 = arith.mulf %alpha, %b6 : f32
      %a6 = arith.addf %l6, %m6 : f32
      affine.store %a6, %acc[%i] : memref<64xf32>
      %l7 = affine.load %acc[%i] : memref<64xf32>
      %b7 = affine.load %A[%i, 7] : memref<64x8xf32>
      %m7 = arith.mulf %alpha, %b7 : f32
      %a7 = arith.addf %l7, %m7 : f32
      affine.store %a7, %acc[%i] : memref<64xf32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %acc[%i] : memref<64xf32>
      affine.store %0, %out[%i] : memref<64xf32>
    }
    return
  }

  func.func @mayalias(%in: memref<64xi32>, %out: memref<64x64xi32>) {
    %b = memref.alloca() {hls.preserve, polygeist.varname = "b_mayalias"} : memref<64xi32>
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to 64 {
        %v = affine.load %in[%i] : memref<64xi32>
        affine.store %v, %b[%i] : memref<64xi32>
        %x = affine.load %b[%j] : memref<64xi32>
        %w = arith.addi %x, %v : i32
        affine.store %w, %b[%i] : memref<64xi32>
        affine.store %x, %out[%i, %j] : memref<64x64xi32>
      }
    }
    return
  }

  func.func @disjoint(%in: memref<64xi32>, %out: memref<64xi32>) {
    %b = memref.alloca() {hls.preserve, polygeist.varname = "b_disjoint"} : memref<64xi32>
    affine.for %i = 0 to 32 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %b[%i * 2] : memref<64xi32>
      %x = affine.load %b[%i * 2 + 1] : memref<64xi32>
      affine.store %x, %out[%i] : memref<64xi32>
    }
    return
  }
}

// @acc: one store of acc per iteration that absorbed the 8 forwarded loads and
// the 8 dead stores; II 4 (interface reads); acc 1 BRAM.
// SCHED-LABEL: func.func @acc
// SCHED:       loopschedule.pipeline II = {{ *}}4
// SCHED-NOT:   memref.load %alloca
// SCHED:       memref.store %{{.*}}, %alloca[%{{.*}}] {hls.forwarded_loads = 8 : i64, hls.removed_stores = 8 : i64} : memref<64xf32>
// SCHED-NOT:   memref.store %{{.*}}, %alloca
// SCHED:       loopschedule.pipeline II = {{ *}}1
// SCHED:       memref.load %alloca

// @mayalias: both stores and the load remain (the schedule may order the load
// before the stores, so presence is checked, not order).
// SCHED-LABEL: func.func @mayalias
// SCHED:       loopschedule.pipeline
// SCHED-DAG:   memref.load %alloca[%{{.*}}] : memref<64xi32>
// SCHED-DAG:   memref.store %{{.*}}, %alloca[%{{.*}}] : memref<64xi32>
// SCHED-DAG:   memref.store %{{.*}}, %alloca[%{{.*}}] : memref<64xi32>

// @disjoint: the load remains.
// SCHED-LABEL: func.func @disjoint
// SCHED:       loopschedule.pipeline
// SCHED-DAG:   memref.store %{{.*}}, %alloca[%{{.*}}] : memref<64xi32>
// SCHED-DAG:   memref.load %alloca[%{{.*}}] : memref<64xi32>

// CHECK:      acc (alloca)
// CHECK:        - memref.store write in pipeline @ {{.*}} ii=4 stage={{[0-9]+}} (absorbed 8 forwarded load(s), 8 dead store(s))
// CHECK:        replication: replicable (max 1 store(s) per loop body), copies 1
// CHECK:        ram type: RAM_1P
// CHECK:        bram: 1
// CHECK:      b_mayalias (alloca)
// CHECK:        replication: not replicable (max 2 store(s) per loop body)
// CHECK:          ii=2: 1R+2W per iteration
// CHECK-NEXT:   ram type: RAM_S2P
// CHECK:      b_disjoint (alloca)
// CHECK:          ii=1: 1R+1W per iteration
// CHECK-NEXT:   ram type: RAM_S2P
// CHECK:      Total BRAM: 3

// b_disjoint is read and written once per iteration of the one pipelined loop
// that accesses it: a read-only and a write-only port, x36 (VITIS_NOTES N90,
// W9r11-impl; RAM_2P x18 = 2 before, total 5). b_mayalias, one read and two
// writes per iteration at II 2 in its only loop, is one read and one write
// per cycle once the writes are spread over the II: RAM_S2P x36 = 1 (N90 (c),
// W9r11 review D1, kernels w9r11rev_gd_pre / gd_post; RAM_T2P x18 = 2 before,
// total 4).
// REPORT: Total BRAM: 3

// Default (no forwarding): acc has 8R+9W per iteration, not replicable, II 9,
// a true-dual-port 64x32 RAM = 2 BRAM (total 6; 5 before W9r11 review D1).
// NOFWD: Total BRAM: 4
