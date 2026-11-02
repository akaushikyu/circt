// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfS0_Pf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfS0_Pf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r22-impl (2026-10-26): VITIS_NOTES N163 control. The maximum steps mix
// loads of two arrays (`m = max(t[..], u[..]); m = max(m, t[..]); ...`): no
// select has both arms from one array, so no extra read; t and u stay plain
// 2-port RAMs (Vitis t_U / u_U RAM_AUTO_1R1W 8 each, kernel w9r22i_a1_two).
// CHECK-COUNT-2: 4096x32b -> RAM_2P
// CHECK: Total BRAM: 16
module {
  func.func @_Z3topPKfS0_Pf(%arg0: memref<4096xf32>, %arg1: memref<4096xf32>, %arg2: memref<2048xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1 = arith.constant -1 : index
    %c2 = arith.constant 2 : index
    %c64 = arith.constant 64 : index
    %c0 = arith.constant 0 : index
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "u"} : memref<64x64xf32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "t"} : memref<64x64xf32>
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 64 {
        %0 = affine.load %arg0[%arg4 + %arg3 * 64] : memref<4096xf32>
        %1 = arith.cmpf ogt, %0, %cst : f32
        %2 = arith.select %1, %0, %cst : f32
        affine.store %2, %alloca_0[%arg3, %arg4] : memref<64x64xf32>
        %3 = affine.load %arg1[%arg4 + %arg3 * 64] : memref<4096xf32>
        %4 = arith.cmpf ogt, %3, %cst : f32
        %5 = arith.select %4, %3, %cst : f32
        affine.store %5, %alloca[%arg3, %arg4] : memref<64x64xf32>
      }
    }
    affine.for %arg3 = 0 to 64 step 2 {
      %0 = arith.cmpi slt, %arg3, %c0 : index
      %1 = arith.subi %c-1, %arg3 : index
      %2 = arith.select %0, %1, %arg3 : index
      %3 = arith.divsi %2, %c2 : index
      %4 = arith.subi %c-1, %3 : index
      %5 = arith.select %0, %4, %3 : index
      %6 = arith.muli %5, %c64 : index
      affine.for %arg4 = 0 to 64 {
        %7 = affine.load %alloca_0[%arg3, %arg4] : memref<64x64xf32>
        %8 = affine.load %alloca[%arg3, %arg4] : memref<64x64xf32>
        %9 = arith.cmpf olt, %7, %8 : f32
        %10 = arith.select %9, %8, %7 : f32
        %11 = affine.load %alloca_0[%arg3 + 1, %arg4] : memref<64x64xf32>
        %12 = arith.cmpf olt, %10, %11 : f32
        %13 = arith.select %12, %11, %10 : f32
        %14 = affine.load %alloca[%arg3 + 1, %arg4] : memref<64x64xf32>
        %15 = arith.cmpf olt, %13, %14 : f32
        %16 = arith.select %15, %14, %13 : f32
        %17 = arith.addi %arg4, %6 : index
        memref.store %16, %arg2[%17] : memref<2048xf32>
      }
    }
    return
  }
}
