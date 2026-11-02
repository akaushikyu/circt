// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N125 (W9r16 review fixes), kernel w9r16rv_rs_fd (Vitis 2025.1 td=off: 240):
// w9r16p_rs_nc with the base 4 * (n / 2): bank r or r + 4, the in-bank address the same on
// both, read unpredicated and muxed, N4's count. The division lowers to arith.divsi, which
// the residue evaluation (residuesOf) treats as an unknown integer whose multiple by 4 has
// residues {0, 4}; before, an unknown residue was taken as "every residue", the address as
// varying, and rotating_reads_full_copies added the copy (256).
// CHECK: Total BRAM: 240

module {
  func.func @_Z3topPiS_S_(%arg0: memref<512xi32>, %arg1: memref<256xi32>, %arg2: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c2 = arith.constant 2 : index
    %c8 = arith.constant 8 : index
    %c4 = arith.constant 4 : index
    %c256 = arith.constant 256 : index
    %c-1 = arith.constant -1 : index
    %c0 = arith.constant 0 : index
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "ker"}], hls.preserve, polygeist.varname = "ker"} : memref<128xi32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "pa"}], hls.preserve, polygeist.varname = "pa"} : memref<504xi32>
    affine.for %arg3 = 0 to 504 {
      %0 = affine.load %arg0[%arg3] : memref<512xi32>
      affine.store %0, %alloca_0[%arg3] : memref<504xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 128 {
      %0 = arith.muli %arg3, %c-1 : index
      %1 = arith.remsi %0, %c256 : index
      %2 = arith.cmpi slt, %1, %c0 : index
      %3 = arith.addi %1, %c256 : index
      %4 = arith.select %2, %3, %1 : index
      %5 = memref.load %arg1[%4] : memref<256xi32>
      affine.store %5, %alloca[%arg3] : memref<128xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 128 {
      %0 = arith.cmpi slt, %arg3, %c0 : index
      %1 = arith.subi %c-1, %arg3 : index
      %2 = arith.select %0, %1, %arg3 : index
      %3 = arith.divsi %2, %c2 : index
      %4 = arith.subi %c-1, %3 : index
      %5 = arith.select %0, %4, %3 : index
      %6 = arith.muli %5, %c4 : index
      %7 = affine.for %arg4 = 0 to 32 iter_args(%arg5 = %c0_i32) -> (i32) {
        %16 = arith.muli %arg4, %c8 : index
        %17 = affine.for %arg6 = 0 to 4 iter_args(%arg7 = %arg5) -> (i32) {
          %18 = arith.addi %arg6, %16 : index
          %19 = arith.addi %18, %6 : index
          %20 = memref.load %alloca_0[%19] : memref<504xi32>
          %21 = affine.load %alloca[%arg6 + %arg4 * 4] : memref<128xi32>
          %22 = arith.muli %20, %21 : i32
          %23 = arith.addi %arg7, %22 : i32
          affine.yield %23 : i32
        }
        affine.yield %17 : i32
      }
      %8 = arith.cmpi slt, %arg3, %c0 : index
      %9 = arith.subi %c-1, %arg3 : index
      %10 = arith.select %8, %9, %arg3 : index
      %11 = arith.divsi %10, %c2 : index
      %12 = arith.subi %c-1, %11 : index
      %13 = arith.select %8, %12, %11 : index
      %14 = memref.load %arg2[%13] : memref<64xi32>
      %15 = arith.addi %14, %7 : i32
      memref.store %15, %arg2[%13] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
