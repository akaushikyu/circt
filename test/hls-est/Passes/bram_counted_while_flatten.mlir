// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top --bram-debug -o /dev/null 2>&1 | FileCheck %s

// O72 review D3, kernel o72r_cdw2: a `while (i--)` countdown (i = 16)
// inside `for (j < 4)` around a 4-trip k loop. Raised to a 16-trip
// affine.for by --vitis-fold, it collapses with j (a perfect pair, 64 trips)
// and is pipelined with k unrolled and j flattened, as in Vitis (td=off: j
// and the while flattened, trip 64, buf RAM_1WNR 3 copies = 6). Before, the
// while was auto-pipelined but not scheduled (2).

// CHECK:     in @top: ii=1 trip=16 source=auto flattened_parents=1
// CHECK:     Total BRAM: 6
// CHECK:     1024x32b -> RAM_1WNR, 3 copies x 2 (x18/port) = 6 BRAM_18K

module {
  func.func @top(%arg0: memref<1024xi32>, %arg1: memref<64xi32>, %arg2: memref<2xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1_i8 = arith.constant -1 : i8
    %c63_i32 = arith.constant 63 : i32
    %c0_i8 = arith.constant 0 : i8
    %c16_i8 = arith.constant 16 : i8
    %c4_i32 = arith.constant 4 : i32
    %c1_i32 = arith.constant 1 : i32
    %c16_i32 = arith.constant 16 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64x16xi32>
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 16 {
        %0 = affine.load %arg0[%arg4 + %arg3 * 16] : memref<1024xi32>
        affine.store %0, %alloca[%arg3, %arg4] : memref<64x16xi32>
      }
    }
    affine.for %arg3 = 0 to 4 {
      %0 = arith.index_cast %arg3 : index to i32
      %1 = arith.muli %0, %c16_i32 : i32
      %2 = scf.while (%arg4 = %c16_i8) : (i8) -> i8 {
        %3 = arith.cmpi ne, %arg4, %c0_i8 : i8
        scf.condition(%3) %arg4 : i8
      } do {
      ^bb0(%arg4: i8):
        %3 = arith.addi %arg4, %c-1_i8 : i8
        %4 = arith.extui %3 : i8 to i32
        %5 = arith.addi %1, %4 : i32
        %6 = arith.andi %5, %c63_i32 : i32
        %7 = arith.index_cast %6 : i32 to index
        %8 = affine.for %arg5 = 0 to 4 iter_args(%arg6 = %c0_i32) -> (i32) {
          %9 = arith.index_cast %arg5 : index to i32
          %10 = arith.muli %9, %c4_i32 : i32
          %11 = arith.addi %10, %0 : i32
          %12 = arith.index_cast %11 : i32 to index
          %13 = memref.load %alloca[%7, %12] : memref<64x16xi32>
          %14 = arith.addi %9, %c1_i32 : i32
          %15 = arith.muli %13, %14 : i32
          %16 = arith.addi %arg6, %15 : i32
          affine.yield %16 : i32
        }
        memref.store %8, %arg1[%7] : memref<64xi32>
        scf.yield %3 : i8
      }
    }
    return
  }
}
