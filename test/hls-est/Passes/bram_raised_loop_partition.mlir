// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --canonicalize --sccp --vitis-fold=raise-counted-loops=false --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top -o /dev/null 2>&1 | FileCheck %s --check-prefix=NORAISE

// Kernel rvsf_g3 (VITIS_NOTES.md N52): both k loops are bounded by the
// scalar global `int ksz = 16` and imperfect, so cgeist leaves them scf.for
// with memref accesses. Vitis (td=off): 16 - both k loops unrolled,
// [HLS 214-449] partitions buf's dimension 2 (constant indices, N7 (b)) into
// 16 banks of 64 words, 1 BRAM each; the same source with `#define ksz 16`
// (rvsf_g3c) also 16. --vitis-fold folds ksz, raises the loops to affine.for
// and turns their accesses affine, so the unrolled constant indices are seen.
// Without the raise buf stays one 1024 x 32 memory (2).

// CHECK-COUNT-16: 64x32b -> RAM_1P (x36/port) = 1 BRAM_18K
// CHECK: Total BRAM: 16

// NORAISE: Total BRAM: 2

module {
  memref.global @ksz : memref<1xi32> = dense<16>
  func.func @top(%arg0: memref<64xi32>, %arg1: memref<64xi32>, %arg2: memref<64xi32>) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64x16xi32>
    %0 = memref.get_global @ksz : memref<1xi32>
    affine.for %arg3 = 0 to 64 {
      %1 = affine.load %arg0[%arg3] : memref<64xi32>
      %2 = affine.load %0[0] : memref<1xi32>
      %3 = arith.index_cast %2 : i32 to index
      scf.for %arg4 = %c0 to %3 step %c1 {
        %4 = arith.index_cast %arg4 : index to i32
        %5 = arith.addi %1, %4 : i32
        memref.store %5, %alloca[%arg3, %arg4] : memref<64x16xi32>
      }
      affine.store %1, %arg2[%arg3] : memref<64xi32>
    }
    affine.for %arg3 = 0 to 64 {
      %1 = affine.load %0[0] : memref<1xi32>
      %2 = arith.index_cast %1 : i32 to index
      %3 = scf.for %arg4 = %c0 to %2 step %c1 iter_args(%arg5 = %c0_i32) -> (i32) {
        %4 = arith.index_cast %arg4 : index to i32
        %5 = memref.load %alloca[%arg3, %arg4] : memref<64x16xi32>
        %6 = arith.addi %4, %c1_i32 : i32
        %7 = arith.muli %5, %6 : i32
        %8 = arith.addi %arg5, %7 : i32
        scf.yield %8 : i32
      }
      affine.store %3, %arg1[%arg3] : memref<64xi32>
    }
    return
  }
}
