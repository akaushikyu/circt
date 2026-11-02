// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top --bram-debug -o /dev/null 2>&1 | FileCheck %s

// O72 review D3, kernel o72r_cdw: `for (j < 64) { unsigned char i = 16; s =
// 0; while (i--) s += buf[j][i] * (i + 1); out[j] = s; }`. cgeist emits the
// countdown as an scf.while; --vitis-fold raises it to an affine.for of 16
// trips (its exit test folds), so j is pipelined with the loop unrolled, as
// in Vitis (td=off: j at II 1, buf RAM_1WNR 15 copies = 30). Before, the
// while counted as a runtime-trip loop and was pipelined on its own (2).

// CHECK:     in @top: ii=1 trip=64 source=auto flattened_parents=0
// CHECK:     Total BRAM: 30
// CHECK:     1024x32b -> RAM_1WNR, 15 copies x 2 (x18/port) = 30 BRAM_18K

module {
  func.func @top(%arg0: memref<1024xi32>, %arg1: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1_i8 = arith.constant -1 : i8
    %c0_i8 = arith.constant 0 : i8
    %c16_i8 = arith.constant 16 : i8
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64x16xi32>
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 16 {
        %0 = affine.load %arg0[%arg3 + %arg2 * 16] : memref<1024xi32>
        affine.store %0, %alloca[%arg2, %arg3] : memref<64x16xi32>
      }
    }
    affine.for %arg2 = 0 to 64 {
      %0:2 = scf.while (%arg3 = %c0_i32, %arg4 = %c16_i8) : (i32, i8) -> (i32, i8) {
        %1 = arith.cmpi ne, %arg4, %c0_i8 : i8
        scf.condition(%1) %arg3, %arg4 : i32, i8
      } do {
      ^bb0(%arg3: i32, %arg4: i8):
        %1 = arith.addi %arg4, %c-1_i8 : i8
        %2 = arith.index_castui %1 : i8 to index
        %3 = memref.load %alloca[%arg2, %2] : memref<64x16xi32>
        %4 = arith.extui %1 : i8 to i32
        %5 = arith.addi %4, %c1_i32 : i32
        %6 = arith.muli %3, %5 : i32
        %7 = arith.addi %arg3, %6 : i32
        scf.yield %7, %1 : i32, i8
      }
      affine.store %0#0, %arg1[%arg2] : memref<64xi32>
    }
    return
  }
}
