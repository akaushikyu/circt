// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=cse-loads=false --bram-analysis | FileCheck %s --check-prefix=NOCSE

// Same-address loads are merged before R is counted (VITIS_NOTES.md N4: R is
// the number of loads per iteration "after unrolling, CSE, LICM"; T2
// storage-model review, finding D2, reproducer p1_dupload).
//
// The pipelined loop loads buf[i][0] and buf[i][1] four times each: 8 load
// ops, 2 distinct addresses, no store to buf in between. Vitis' GVN keeps one
// load per address, so R = 2 at II 1 -> ceil(2/1) = 2 port-cycles -> a plain
// 2-port RAM (two reads in the same cycle, x18 columns: 4096x32 = 8 BRAM),
// no replication. The surviving load records the 3 it stands for. Without
// the merge (cse-loads=false) R = 8 -> 7 copies x 8 = 56 (total 64).

module {
  func.func @kernel(%A: memref<64x64xf32>, %alpha: f32, %out: memref<64x64xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64x64xf32>
    %tmp = memref.alloca() {hls.preserve, polygeist.varname = "tmp"} : memref<64x64xf32>
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to 64 {
        %0 = affine.load %A[%i, %j] : memref<64x64xf32>
        affine.store %0, %buf[%i, %j] : memref<64x64xf32>
      }
    }
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to 64 {
        %l0 = affine.load %buf[%i, 0] : memref<64x64xf32>
        %l1 = affine.load %buf[%i, 1] : memref<64x64xf32>
        %l2 = affine.load %buf[%i, 0] : memref<64x64xf32>
        %l3 = affine.load %buf[%i, 1] : memref<64x64xf32>
        %l4 = affine.load %buf[%i, 0] : memref<64x64xf32>
        %l5 = affine.load %buf[%i, 1] : memref<64x64xf32>
        %l6 = affine.load %buf[%i, 0] : memref<64x64xf32>
        %l7 = affine.load %buf[%i, 1] : memref<64x64xf32>
        %m0 = arith.mulf %alpha, %l0 : f32
        %a0 = arith.addf %cst, %m0 : f32
        %m1 = arith.mulf %a0, %l1 : f32
        %a1 = arith.addf %a0, %m1 : f32
        %m2 = arith.mulf %a1, %l2 : f32
        %a2 = arith.addf %a1, %m2 : f32
        %m3 = arith.mulf %a2, %l3 : f32
        %a3 = arith.addf %a2, %m3 : f32
        %m4 = arith.mulf %a3, %l4 : f32
        %a4 = arith.addf %a3, %m4 : f32
        %m5 = arith.mulf %a4, %l5 : f32
        %a5 = arith.addf %a4, %m5 : f32
        %m6 = arith.mulf %a5, %l6 : f32
        %a6 = arith.addf %a5, %m6 : f32
        %m7 = arith.mulf %a6, %l7 : f32
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

// CHECK:      buf (alloca)
// CHECK:        - memref.load read  in pipeline @ {{.*}} ii=1 stage={{[0-9]+}} (+3 same-address load(s) merged into it: CSE)
// CHECK:        - memref.load read  in pipeline @ {{.*}} ii=1 stage={{[0-9]+}} (+3 same-address load(s) merged into it: CSE)
// CHECK:        replication: replicable (max 1 store(s) per loop body), copies 1
// CHECK:          ii=1: 2R+0W per iteration -> ceil(2/1)=2 port-cycles -> copies 1
// Two reads per cycle (one write elsewhere) bind ram_2p in Vitis; only two
// writes per cycle need ram_t2p. Both are x18 per port: 8 BRAM either way.
// CHECK:        ram type: RAM_2P
// CHECK:        bram: 8
// CHECK:      Total BRAM: 16

// REPORT: Total BRAM: 16

// NOCSE: Total BRAM: 64
