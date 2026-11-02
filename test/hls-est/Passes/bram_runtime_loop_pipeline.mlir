// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule | FileCheck %s --check-prefix=SCHED

// Kernel o72_fa (OPEN_ISSUES O72, VITIS_NOTES.md N53): `for (j < 2) { c =
// n[j]; for (i < c) { s = 0; for (k < 16) s += buf[i][k] * (k + 1); out[i]
// = s; } }`. The i loop's bound is loaded inside the j loop, so it stays an
// scf.for. Vitis (td=off): VITIS_LOOP_8_4 (i, trip `?`) pipelined at II 1,
// k unrolled ([HLS 214-291] / [HLS 214-186]), buf RAM_1WNR_AUTO_1R1W with
// 15 copies ([HLS 200-2167]): 30. --auto-pipeline-unroll pipelines the runtime-trip
// loop and unrolls k; --convert-affine-to-loopschedule schedules it (16
// reads of buf per iteration at II 1). Before O72 the i loop was opaque, k
// was pipelined on its own and buf was one 1024 x 32 memory (2).

// CHECK: 1024x32b -> RAM_1WNR, 15 copies x 2 (x18/port) = 30 BRAM_18K
// CHECK: Total BRAM: 30

// SCHED-NOT: scf.for
// SCHED:     loopschedule.pipeline II = 1 iter_args(
// SCHED-NOT: scf.for

module {
  func.func @top(%arg0: memref<1024xi32>, %arg1: memref<64xi32>, %arg2: memref<2xi32>, %arg3: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64x16xi32>
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 16 {
        %0 = affine.load %arg0[%arg5 + %arg4 * 16] : memref<1024xi32>
        affine.store %0, %alloca[%arg4, %arg5] : memref<64x16xi32>
      }
    }
    affine.for %arg4 = 0 to 2 {
      %0 = affine.load %arg2[%arg4] : memref<2xi32>
      %1 = arith.index_cast %0 : i32 to index
      scf.for %arg5 = %c0 to %1 step %c1 {
        %2 = affine.for %arg6 = 0 to 16 iter_args(%arg7 = %c0_i32) -> (i32) {
          %3 = arith.index_cast %arg6 : index to i32
          %4 = memref.load %alloca[%arg5, %arg6] : memref<64x16xi32>
          %5 = arith.addi %3, %c1_i32 : i32
          %6 = arith.muli %4, %5 : i32
          %7 = arith.addi %arg7, %6 : i32
          affine.yield %7 : i32
        }
        memref.store %2, %arg1[%arg5] : memref<64xi32>
      }
    }
    return
  }
}
