// RUN: hls-est %s --symbol-privatize=exclude=_Z6pr_topPKiS0_S0_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6pr_topPKiS0_S0_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// Control for the GVN load PRE rule (W9 round 8 review defect 6): kernel
// w9r8f_pr3, a store of H between the two ifs that read H[i]: both reads
// stay (Vitis 4 BRAM, RAM_1WNR_AUTO_1R1W, II 1).
// CHECK: kind=RAM_1WNR
// CHECK: Total BRAM: 4
module {
  func.func @_Z6pr_topPKiS0_S0_Pi(%arg0: memref<256xi32>, %arg1: memref<256xi32>, %arg2: memref<256xi32>, %arg3: memref<2xi32>) attributes {hls.orig_name = "pr_top", llvm.linkage = #llvm.linkage<external>} {
    %c5_i32 = arith.constant 5 : i32
    %c255_i32 = arith.constant 255 : i32
    %c3_i32 = arith.constant 3 : i32
    %c7_i32 = arith.constant 7 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "H"} : memref<256xi32>
    affine.for %arg4 = 0 to 256 {
      %1 = affine.load %arg0[%arg4] : memref<256xi32>
      %2 = arith.muli %1, %c7_i32 : i32
      affine.store %2, %alloca[%arg4] : memref<256xi32>
    }
    %0:2 = affine.for %arg4 = 0 to 256 iter_args(%arg5 = %c0_i32, %arg6 = %c0_i32) -> (i32, i32) {
      %1 = affine.load %arg1[%arg4] : memref<256xi32>
      %2 = arith.cmpi sgt, %1, %c3_i32 : i32
      %3 = scf.if %2 -> (i32) {
        %9 = affine.load %alloca[%arg4] : memref<256xi32>
        %10 = arith.addi %arg6, %9 : i32
        scf.yield %10 : i32
      } else {
        scf.yield %arg6 : i32
      }
      %4 = arith.andi %1, %c255_i32 : i32
      %5 = arith.index_cast %4 : i32 to index
      memref.store %3, %alloca[%5] : memref<256xi32>
      %6 = affine.load %arg2[%arg4] : memref<256xi32>
      %7 = arith.cmpi sgt, %6, %c5_i32 : i32
      %8 = scf.if %7 -> (i32) {
        %9 = affine.load %alloca[%arg4] : memref<256xi32>
        %10 = arith.addi %arg5, %9 : i32
        scf.yield %10 : i32
      } else {
        scf.yield %arg5 : i32
      }
      affine.yield %8, %3 : i32, i32
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.store %0#1, %arg3[0] : memref<2xi32>
    affine.store %0#0, %arg3[1] : memref<2xi32>
    return
  }
}
