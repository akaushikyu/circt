// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s
// W9 round 12 review, kernel w9r12rv_o121_cyc4 (Vitis 2025.1 td=off: 4,
// 4 banks x 1, one read per bank): `A[2048]` cyclic 4, `A[(j + 4*i + 2) %
// 2048]`, j unrolled x4, II 1. cgeist lowers the affine-raised C `%` as
// `x + (-2048) * floordiv(x, 2048)`; residueBase peels the multiple of the
// factor, so each copy's bank is known. Before: 24 (4 x RAM_1WNR 6).
// CHECK-COUNT-4: kind=RAM_1P bram=1
// CHECK: Total BRAM: 4

module {
  func.func @_Z3topPiS_(%arg0: memref<2048xi32>, %arg1: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-3 = arith.constant -3 : index
    %c-2048 = arith.constant -2048 : index
    %c-1 = arith.constant -1 : index
    %c2 = arith.constant 2 : index
    %c4 = arith.constant 4 : index
    %c2048 = arith.constant 2048 : index
    %c0 = arith.constant 0 : index
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "A"}], hls.preserve, polygeist.varname = "A"} : memref<2048xi32>
    affine.for %arg2 = 0 to 2048 {
      %0 = affine.load %arg0[%arg2] : memref<2048xi32>
      affine.store %0, %alloca[%arg2] : memref<2048xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 512 {
      %0 = arith.muli %arg2, %c4 : index
      %1 = affine.for %arg3 = 0 to 4 iter_args(%arg4 = %c0_i32) -> (i32) {
        %2 = arith.addi %arg3, %0 : index
        %3 = arith.addi %2, %c2 : index
        %4 = arith.cmpi slt, %3, %c0 : index
        %5 = arith.subi %c-3, %2 : index
        %6 = arith.select %4, %5, %3 : index
        %7 = arith.divsi %6, %c2048 : index
        %8 = arith.subi %c-1, %7 : index
        %9 = arith.select %4, %8, %7 : index
        %10 = arith.muli %9, %c-2048 : index
        %11 = arith.addi %2, %10 : index
        %12 = arith.addi %11, %c2 : index
        %13 = memref.load %alloca[%12] : memref<2048xi32>
        %14 = arith.addi %arg4, %13 : i32
        affine.yield %14 : i32
      }
      affine.store %1, %arg1[%arg2] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
