// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths=remarks=true -o /dev/null 2>&1 | FileCheck %s
// W9 round 21 review (2026-10-25), defect D8: the clamp `x > 100 ? 100 : x`
// of an unsigned char compared as a (zero-extended) int bounds the select's
// arm to [0, 100], so the accumulation `s = base[i]; for (16) s += clamp`
// ranges over 255 + 16 x 100 = 1855: 11 bits (kernel w9r21rev_r1c_iterinit,
// Vitis buf_U 1024 x 11). Before, a signed comparison of a zero-extended
// value bounded nothing: 13 bits ([0, 4335]).
// CHECK: remark: narrow-ram-widths: 11 of 32 bits; stored values [0, 1855]
// MLIR from the private cgeist of the W9 round 21 review fixes (real headers).
module {
  func.func @_Z3topPhPA16_hPi(%arg0: memref<1024xi8>, %arg1: memref<1024x16xi8>, %arg2: memref<1024xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c100_i8 = arith.constant 100 : i8
    %c100_i32 = arith.constant 100 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<1024xi32>
    affine.for %arg3 = 0 to 1024 {
      %0 = affine.load %arg0[%arg3] : memref<1024xi8>
      %1 = arith.extui %0 : i8 to i32
      %2 = affine.for %arg4 = 0 to 16 iter_args(%arg5 = %1) -> (i32) {
        %3 = affine.load %arg1[%arg3, %arg4] : memref<1024x16xi8>
        %4 = arith.extui %3 : i8 to i32
        %5 = arith.cmpi sgt, %4, %c100_i32 : i32
        %6 = arith.select %5, %c100_i8, %3 : i8
        %7 = arith.extui %6 : i8 to i32
        %8 = arith.addi %arg5, %7 : i32
        affine.yield %8 : i32
      } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
      affine.store %2, %alloca[%arg3] : memref<1024xi32>
    }
    affine.for %arg3 = 0 to 1024 {
      %0 = affine.load %alloca[-%arg3 + 1023] : memref<1024xi32>
      affine.store %0, %arg2[%arg3] : memref<1024xi32>
    }
    return
  }
}
