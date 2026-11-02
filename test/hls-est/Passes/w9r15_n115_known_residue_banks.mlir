// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.replication.rotating_reads_full_copies=true --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF1
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.replication.rotating_reads_full_copies=true --config-set tool.hls.partitioning.known_residue_banks=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF2

// VITIS_NOTES N115 control, kernel w9r15p_rc_fix (Vitis 2025.1 td=off: 256): int pa[511]
// cyclic 8 read at (n & ~7) + k, k unrolled 256 in a pipelined n loop: the low
// bits of n & ~7 are known zero, so each read's bank is the constant k % 8
// (tool.hls.partitioning.known_residue_banks): 32 reads per bank at II 2, 15
// copies, also with N115's full copies for steered reads on
// (tool.hls.memory_architecture.replication.rotating_reads_full_copies, OFF1).
// Off2 run: both keys flipped: the bank is chosen at run time, but the in-bank address
// is the same on every candidate bank (the base n & ~7 is a multiple of 8, residuesOf),
// so N125 gives the steered reads no extra copy (256; 272 before the W9r16 review fixes,
// when an unknown residue counted as a varying address).
// CHECK: Total BRAM: 256
// OFF1: Total BRAM: 256
// OFF2: Total BRAM: 256

module {
  func.func @_Z3topPiS_S_(%arg0: memref<256xi32>, %arg1: memref<256xi32>, %arg2: memref<256xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1 = arith.constant -1 : index
    %c256 = arith.constant 256 : index
    %c0 = arith.constant 0 : index
    %c-8_i32 = arith.constant -8 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "ker"}], hls.preserve, polygeist.varname = "ker"} : memref<256xi32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "pa"}], hls.preserve, polygeist.varname = "pa"} : memref<511xi32>
    affine.for %arg3 = 0 to 511 {
      %0 = arith.remsi %arg3, %c256 : index
      %1 = arith.cmpi slt, %0, %c0 : index
      %2 = arith.addi %0, %c256 : index
      %3 = arith.select %1, %2, %0 : index
      %4 = memref.load %arg0[%3] : memref<256xi32>
      affine.store %4, %alloca_0[%arg3] : memref<511xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 256 {
      %0 = arith.muli %arg3, %c-1 : index
      %1 = arith.remsi %0, %c256 : index
      %2 = arith.cmpi slt, %1, %c0 : index
      %3 = arith.addi %1, %c256 : index
      %4 = arith.select %2, %3, %1 : index
      %5 = memref.load %arg1[%4] : memref<256xi32>
      affine.store %5, %alloca[%arg3] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 256 {
      %0 = arith.index_cast %arg3 : index to i32
      %1 = arith.andi %0, %c-8_i32 : i32
      %2 = affine.for %arg4 = 0 to 256 iter_args(%arg5 = %c0_i32) -> (i32) {
        %3 = arith.index_cast %arg4 : index to i32
        %4 = arith.addi %1, %3 : i32
        %5 = arith.index_cast %4 : i32 to index
        %6 = memref.load %alloca_0[%5] : memref<511xi32>
        %7 = affine.load %alloca[%arg4] : memref<256xi32>
        %8 = arith.muli %6, %7 : i32
        %9 = arith.addi %arg5, %8 : i32
        affine.yield %9 : i32
      }
      affine.store %2, %arg2[%arg3] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
