// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=SCHED
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=hoist-invariant=false --bram-analysis | FileCheck %s --check-prefix=NOHOIST

// Loop-invariant reads are hoisted out of the pipelined loop and use none of
// its ports (VITIS_NOTES.md N4, replication.md R4: rep_tri_R08 vs rep_inv_R08).
//
// @tri: lp2 runs j <= i, so the nest is not rectangular and is not flattened;
// lp2 is pipelined alone and the 8 loads buff_tri[i][0..7] do not depend on j
// (and buff_tri is not written in lp2) -> moved into the lp1 body, where they
// run sequentially on one port: buff_tri is a plain wide RAM (8 BRAM), lp2 II 1.
// Vitis: `define internal void @rep_Pipeline_lp2(...)` takes no buff_A, the 8
// loads sit in @rep; buff_A 8 BRAM, total 16.
// @rect: the same loads in a rectangular nest: the nest is flattened, i is a
// function of the flattened IV, nothing is hoisted, 8 reads per iteration at
// II 1 -> 7 copies x 8 = 56 BRAM (Vitis rep_inv_R08: 56 + 8 = 64).
// acc[i] += ... inside lp2 of @tri is read AND written in lp2, so its load is
// not hoisted: 1R+1W in the same cycle -> x18 -> 64x32 = 2 BRAM.
// With hoist-invariant=false the @tri loads stay in lp2 (8 reads/iteration,
// replicated like @rect): the total rises from 82 to 130.

#tri = affine_map<(d0) -> (d0 + 1)>
module {
  func.func @tri(%A: memref<64x64xf32>, %alpha: f32, %out: memref<64x64xf32>, %y: memref<64xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    %buff_tri = memref.alloca() {hls.preserve, polygeist.varname = "buff_tri"} : memref<64x64xf32>
    %tmp = memref.alloca() {hls.preserve, polygeist.varname = "tmp_tri"} : memref<64x64xf32>
    %acc = memref.alloca() {hls.preserve, polygeist.varname = "acc_tri"} : memref<64xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %A[%i, %j] : memref<64x64xf32>
      affine.store %0, %buff_tri[%i, %j] : memref<64x64xf32>
    }
  }
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to #tri(%i) {
      %l0 = affine.load %buff_tri[%i, 0] : memref<64x64xf32>
      %l1 = affine.load %buff_tri[%i, 1] : memref<64x64xf32>
      %l2 = affine.load %buff_tri[%i, 2] : memref<64x64xf32>
      %l3 = affine.load %buff_tri[%i, 3] : memref<64x64xf32>
      %l4 = affine.load %buff_tri[%i, 4] : memref<64x64xf32>
      %l5 = affine.load %buff_tri[%i, 5] : memref<64x64xf32>
      %l6 = affine.load %buff_tri[%i, 6] : memref<64x64xf32>
      %l7 = affine.load %buff_tri[%i, 7] : memref<64x64xf32>
      %m0 = arith.mulf %alpha, %l0 : f32
      %a0 = arith.addf %cst, %m0 : f32
      %m1 = arith.mulf %alpha, %l1 : f32
      %a1 = arith.addf %a0, %m1 : f32
      %m2 = arith.mulf %alpha, %l2 : f32
      %a2 = arith.addf %a1, %m2 : f32
      %m3 = arith.mulf %alpha, %l3 : f32
      %a3 = arith.addf %a2, %m3 : f32
      %m4 = arith.mulf %alpha, %l4 : f32
      %a4 = arith.addf %a3, %m4 : f32
      %m5 = arith.mulf %alpha, %l5 : f32
      %a5 = arith.addf %a4, %m5 : f32
      %m6 = arith.mulf %alpha, %l6 : f32
      %a6 = arith.addf %a5, %m6 : f32
      %m7 = arith.mulf %alpha, %l7 : f32
      %a7 = arith.addf %a6, %m7 : f32
        affine.store %a7, %tmp[%i, %j] : memref<64x64xf32>
        %p = affine.load %acc[%i] : memref<64xf32>
        %q = arith.addf %p, %a7 : f32
        affine.store %q, %acc[%i] : memref<64xf32>
      }
    }
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %tmp[%i, %j] : memref<64x64xf32>
      affine.store %0, %out[%i, %j] : memref<64x64xf32>
    }
  }
    affine.for %i = 0 to 64 {
      %0 = affine.load %acc[%i] : memref<64xf32>
      affine.store %0, %y[%i] : memref<64xf32>
    }
    return
  }

  func.func @rect(%A: memref<64x64xf32>, %alpha: f32, %out: memref<64x64xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    %buff_rect = memref.alloca() {hls.preserve, polygeist.varname = "buff_rect"} : memref<64x64xf32>
    %tmp = memref.alloca() {hls.preserve, polygeist.varname = "tmp_rect"} : memref<64x64xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %A[%i, %j] : memref<64x64xf32>
      affine.store %0, %buff_rect[%i, %j] : memref<64x64xf32>
    }
  }
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to 64 {
      %l0 = affine.load %buff_rect[%i, 0] : memref<64x64xf32>
      %l1 = affine.load %buff_rect[%i, 1] : memref<64x64xf32>
      %l2 = affine.load %buff_rect[%i, 2] : memref<64x64xf32>
      %l3 = affine.load %buff_rect[%i, 3] : memref<64x64xf32>
      %l4 = affine.load %buff_rect[%i, 4] : memref<64x64xf32>
      %l5 = affine.load %buff_rect[%i, 5] : memref<64x64xf32>
      %l6 = affine.load %buff_rect[%i, 6] : memref<64x64xf32>
      %l7 = affine.load %buff_rect[%i, 7] : memref<64x64xf32>
      %m0 = arith.mulf %alpha, %l0 : f32
      %a0 = arith.addf %cst, %m0 : f32
      %m1 = arith.mulf %alpha, %l1 : f32
      %a1 = arith.addf %a0, %m1 : f32
      %m2 = arith.mulf %alpha, %l2 : f32
      %a2 = arith.addf %a1, %m2 : f32
      %m3 = arith.mulf %alpha, %l3 : f32
      %a3 = arith.addf %a2, %m3 : f32
      %m4 = arith.mulf %alpha, %l4 : f32
      %a4 = arith.addf %a3, %m4 : f32
      %m5 = arith.mulf %alpha, %l5 : f32
      %a5 = arith.addf %a4, %m5 : f32
      %m6 = arith.mulf %alpha, %l6 : f32
      %a6 = arith.addf %a5, %m6 : f32
      %m7 = arith.mulf %alpha, %l7 : f32
      %a7 = arith.addf %a6, %m7 : f32
        affine.store %a7, %tmp[%i, %j] : memref<64x64xf32>
      }
    }
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %tmp[%i, %j] : memref<64x64xf32>
      affine.store %0, %out[%i, %j] : memref<64x64xf32>
    }
  }
    return
  }
}

// In @tri the eight hoisted loads precede the pipeline inside the outer loop;
// in @rect they are inside the flattened pipeline.
// SCHED:       func.func @tri
// SCHED:       affine.for
// SCHED-COUNT-8: memref.load %{{.*}} : memref<64x64xf32>
// SCHED:       loopschedule.pipeline II = {{ *}}1
// SCHED:       func.func @rect
// SCHED:       loopschedule.pipeline II = {{ *}}1
// SCHED:       loopschedule.pipeline II = {{ *}}1
// SCHED-COUNT-8: memref.load %{{.*}} : memref<64x64xf32>

// CHECK:      buff_tri (alloca)
// CHECK:        - memref.load read  in loop @
// CHECK:        replication: replicable (max 1 store(s) per loop body), copies 1
// CHECK:        ram type: RAM_1P -- peak port demand 1/cycle
// CHECK:        bram: 8
// CHECK:      acc_tri (alloca)
// CHECK:        ram type: RAM_2P
// CHECK:        bram: 2
// CHECK:      buff_rect (alloca)
// CHECK:        replication: replicable (max 1 store(s) per loop body), copies 7
// CHECK:        ram type: RAM_1WNR
// CHECK:        bram: 56
// CHECK:      Total BRAM: 82

// REPORT: Total BRAM: 82
// NOHOIST: Total BRAM: 130
