// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s
// W9 round 12 review, kernel w9r12rv_o121_cyc3 (Vitis 2025.1 td=off: 5 =
// 1 + 2 + 2): `A[1536]` cyclic 3, `A[(j + 3*i + 1) % 1536]`, j unrolled x3,
// II 1; each copy reads one bank (residueBase, as o121_cyc4). Before: 12.
// hls-est 3: Vitis binds two of the three 512 x 32 banks x18 (2 each) and
// one x36 (1); which bank gets SDP is not modelled (OPEN_ISSUES O131,
// unconfirmed). The CHECK records today's output, not Vitis.
// CHECK: Total BRAM: 3

module {
  func.func @_Z3topPiS_(%arg0: memref<1536xi32>, %arg1: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-2 = arith.constant -2 : index
    %c-1536 = arith.constant -1536 : index
    %c-1 = arith.constant -1 : index
    %c3 = arith.constant 3 : index
    %c1 = arith.constant 1 : index
    %c1536 = arith.constant 1536 : index
    %c0 = arith.constant 0 : index
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 3 : i32, kind = "cyclic", variable = "A"}], hls.preserve, polygeist.varname = "A"} : memref<1536xi32>
    affine.for %arg2 = 0 to 1536 {
      %0 = affine.load %arg0[%arg2] : memref<1536xi32>
      affine.store %0, %alloca[%arg2] : memref<1536xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 512 {
      %0 = arith.muli %arg2, %c3 : index
      %1 = affine.for %arg3 = 0 to 3 iter_args(%arg4 = %c0_i32) -> (i32) {
        %2 = arith.addi %arg3, %0 : index
        %3 = arith.addi %2, %c1 : index
        %4 = arith.cmpi slt, %3, %c0 : index
        %5 = arith.subi %c-2, %2 : index
        %6 = arith.select %4, %5, %3 : index
        %7 = arith.divsi %6, %c1536 : index
        %8 = arith.subi %c-1, %7 : index
        %9 = arith.select %4, %8, %7 : index
        %10 = arith.muli %9, %c-1536 : index
        %11 = arith.addi %2, %10 : index
        %12 = arith.addi %11, %c1 : index
        %13 = memref.load %alloca[%12] : memref<1536xi32>
        %14 = arith.addi %arg4, %13 : i32
        affine.yield %14 : i32
      }
      affine.store %1, %arg1[%arg2] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
