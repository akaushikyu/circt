// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=SCHED

// No replication when a loop body stores to the bank twice (VITIS_NOTES.md N4,
// replication.md R3: rep_wr2_R08, Vitis: buff_A 8 BRAM plain RAM_AUTO_1R1W,
// lp1_lp2 II 4, total 16; the same kernel with a one-store copy-in gets 7 copies
// and 56 BRAM, see replication_1wnr.mlir).
//
// The copy-in stores buff_A[i][2j] and buff_A[i][2j+1] in one iteration, which
// needs two write ports; a RAM_1WNR has one shared write port, so Vitis keeps a
// plain true-dual-port RAM. The scheduler therefore grants buff_A 2 slots per
// cycle: the copy-in runs at II 1 (2 stores) and the compute loop with its 8
// reads at II ceil(8 / 2) = 4. Two ports are live in the same cycle -> x18
// columns: 2 x 4 = 8 BRAM, no copies.

module {
  func.func @kernel(%A: memref<64x64xf32>, %alpha: f32, %out: memref<64x64xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    %buff_A = memref.alloca() {hls.preserve, polygeist.varname = "buff_A"} : memref<64x64xf32>
    %tmp = memref.alloca() {hls.preserve, polygeist.varname = "tmp"} : memref<64x64xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 32 {
      %0 = affine.load %A[%i, %j * 2] : memref<64x64xf32>
      affine.store %0, %buff_A[%i, %j * 2] : memref<64x64xf32>
      %1 = affine.load %A[%i, %j * 2 + 1] : memref<64x64xf32>
      affine.store %1, %buff_A[%i, %j * 2 + 1] : memref<64x64xf32>
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

// SCHED: loopschedule.pipeline II = {{ *}}1
// SCHED: loopschedule.pipeline II = {{ *}}4
// SCHED: loopschedule.pipeline II = {{ *}}1

// CHECK:      buff_A (alloca)
// CHECK:        replication: not replicable (max 2 store(s) per loop body), copies 1
// CHECK-DAG:      ii=1: 0R+2W per iteration -> ceil(2/1)=2 port-cycles -> copies 1
// CHECK-DAG:      ii=4: 8R+0W per iteration -> ceil(8/4)=2 port-cycles -> copies 1
// CHECK:        ram type: RAM_T2P -- peak port demand 2/cycle (2R+2W, max over scopes): two ports live in the same cycle -> RAM_T2P (x18/port, true dual port); not replicable: a loop body stores to it 2 times (Vitis keeps one 2-port RAM and raises that loop's II)
// CHECK:        bank math: {{.*}} two live ports -> x18 max at RAM_T2P, element 32b -> mode x18: columns ceil(32/18)=2, depth/block 1024, address depth 2^ceil(log2 4096)=4096, blocks/column max(1,4096/1024)=4 -> 8 per copy, replication 1 -> 8 block(s)
// CHECK-NEXT:   bram: 8
// CHECK:      tmp (alloca)
// CHECK:        bram: 8
// CHECK:      Total BRAM: 16

// REPORT: Total BRAM: 16
