// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=SCHED

// Memory replication, RAM_1WNR (VITIS_NOTES.md N4; replication.md rep_inv_R16,
// Vitis: buff_A 120 BRAM, tmp 8, total 128, lp1_lp2 II 1).
//
// The compute nest is perfect and rectangular, so the scheduler flattens it:
// the 16 loads buff_A[i][0..15] (the unrolled k loop) depend on the flattened
// induction variable and are NOT hoisted. No loop body stores to buff_A more
// than once (the copy-in nest is flattened too: one store per iteration), so
// the bank is replicable: the scheduler grants it 17 read-or-write slots per
// cycle and the loop runs at II 1 with 16 reads per iteration. Vitis then needs
// ceil(16 / 1) = 16 port-cycles: one 2-port RAM gives 2, so 15 copies, each a
// true-dual-port 4096 x 32 RAM (x18 columns: 2 x 4 = 8 BRAM) -> 120.
// `tmp` is written once per iteration here and read once per iteration of the
// copy-out loop (one live port -> x36 wide: 1 x 8 = 8).

module {
  func.func @kernel(%A: memref<64x64xf32>, %alpha: f32, %out: memref<64x64xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    %buff_A = memref.alloca() {hls.preserve, polygeist.varname = "buff_A"} : memref<64x64xf32>
    %tmp = memref.alloca() {hls.preserve, polygeist.varname = "tmp"} : memref<64x64xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %A[%i, %j] : memref<64x64xf32>
      affine.store %0, %buff_A[%i, %j] : memref<64x64xf32>
    }
  }
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to 64 {
      %l0 = affine.load %buff_A[%i, 0] : memref<64x64xf32>
      %l1 = affine.load %buff_A[%i, 1] : memref<64x64xf32>
      %l2 = affine.load %buff_A[%i, 2] : memref<64x64xf32>
      %l3 = affine.load %buff_A[%i, 3] : memref<64x64xf32>
      %l4 = affine.load %buff_A[%i, 4] : memref<64x64xf32>
      %l5 = affine.load %buff_A[%i, 5] : memref<64x64xf32>
      %l6 = affine.load %buff_A[%i, 6] : memref<64x64xf32>
      %l7 = affine.load %buff_A[%i, 7] : memref<64x64xf32>
      %l8 = affine.load %buff_A[%i, 8] : memref<64x64xf32>
      %l9 = affine.load %buff_A[%i, 9] : memref<64x64xf32>
      %l10 = affine.load %buff_A[%i, 10] : memref<64x64xf32>
      %l11 = affine.load %buff_A[%i, 11] : memref<64x64xf32>
      %l12 = affine.load %buff_A[%i, 12] : memref<64x64xf32>
      %l13 = affine.load %buff_A[%i, 13] : memref<64x64xf32>
      %l14 = affine.load %buff_A[%i, 14] : memref<64x64xf32>
      %l15 = affine.load %buff_A[%i, 15] : memref<64x64xf32>
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
      %m8 = arith.mulf %alpha, %l8 : f32
      %a8 = arith.addf %a7, %m8 : f32
      %m9 = arith.mulf %alpha, %l9 : f32
      %a9 = arith.addf %a8, %m9 : f32
      %m10 = arith.mulf %alpha, %l10 : f32
      %a10 = arith.addf %a9, %m10 : f32
      %m11 = arith.mulf %alpha, %l11 : f32
      %a11 = arith.addf %a10, %m11 : f32
      %m12 = arith.mulf %alpha, %l12 : f32
      %a12 = arith.addf %a11, %m12 : f32
      %m13 = arith.mulf %alpha, %l13 : f32
      %a13 = arith.addf %a12, %m13 : f32
      %m14 = arith.mulf %alpha, %l14 : f32
      %a14 = arith.addf %a13, %m14 : f32
      %m15 = arith.mulf %alpha, %l15 : f32
      %a15 = arith.addf %a14, %m15 : f32
        affine.store %a15, %tmp[%i, %j] : memref<64x64xf32>
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

// SCHED: loopschedule.pipeline II = {{ *}}1
// SCHED: loopschedule.pipeline II = {{ *}}1
// SCHED: loopschedule.pipeline II = {{ *}}1

// CHECK:      buff_A (alloca)
// CHECK:        replication: replicable (max 1 store(s) per loop body), copies 15 set by pipeline @
// CHECK:          ii=1: 16R+0W per iteration -> ceil(16/1)=16 port-cycles -> copies 15
// CHECK:        ram type: RAM_1WNR -- replicable (no loop body stores to it more than once); pipeline @ {{.*}}: 16R+0W per iteration at II 1 needs ceil(16/1)=16 port-cycles -> RAM_1WNR with 15 copies
// (4096 words: the 2049-4096 band, min(ceil(32/4), 2*ceil(32/9)) = 8 per copy as
// 4Kx4 columns; N6 printed the same 8 as 2 x18 columns of 4 blocks)
// CHECK:        bank math: 18432 bits/BRAM_18K (incl. parity), two live ports -> x18 max at RAM_1WNR, element 32b -> mode x4: columns ceil(32/4)=8, depth/block 4096, address depth 2^ceil(log2 4096)=4096, blocks/column max(1,4096/4096)=1 -> 8 per copy, replication 15 -> 120 block(s)
// CHECK-NEXT:   bram: 120
// CHECK:      tmp (alloca)
// CHECK:        replication: replicable (max 1 store(s) per loop body), copies 1
// CHECK:        ram type: RAM_1P
// CHECK:        bank math: {{.*}} one live port -> x36 allowed at RAM_1P, element 32b -> mode x4: columns ceil(32/4)=8, depth/block 4096, address depth 2^ceil(log2 4096)=4096, blocks/column max(1,4096/4096)=1 -> 8 per copy, replication 1 -> 8 block(s)
// CHECK-NEXT:   bram: 8
// CHECK:      Total BRAM: 128

// REPORT: Total BRAM: 128
