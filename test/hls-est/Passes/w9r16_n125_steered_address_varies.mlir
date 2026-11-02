// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.replication.rotating_reads_full_copies=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N125, kernel w9r16p_rs_s4 (Vitis 2025.1 td=off: 272): pa cyclic 8 read at
// 4n + k (k < 128 unrolled) in a pipelined loop at II 2: a read can hit two banks and the
// residue carries into the in-bank address, so Vitis issues one predicated load per bank
// and gives every bank 16 copies (N115's ceil(R / II)). Off
// (rotating_reads_full_copies=false): N4's 15 copies (256).
// CHECK: Total BRAM: 272
// OFF: Total BRAM: 256

module {
  func.func @_Z3topPiS_S_(%arg0: memref<256xi32>, %arg1: memref<256xi32>, %arg2: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1 = arith.constant -1 : index
    %c256 = arith.constant 256 : index
    %c0 = arith.constant 0 : index
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "ker"}], hls.preserve, polygeist.varname = "ker"} : memref<256xi32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "pa"}], hls.preserve, polygeist.varname = "pa"} : memref<508xi32>
    affine.for %arg3 = 0 to 508 {
      %0 = arith.remsi %arg3, %c256 : index
      %1 = arith.cmpi slt, %0, %c0 : index
      %2 = arith.addi %0, %c256 : index
      %3 = arith.select %1, %2, %0 : index
      %4 = memref.load %arg0[%3] : memref<256xi32>
      affine.store %4, %alloca_0[%arg3] : memref<508xi32>
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
    affine.for %arg3 = 0 to 64 {
      %0 = affine.for %arg4 = 0 to 256 iter_args(%arg5 = %c0_i32) -> (i32) {
        %1 = affine.load %alloca_0[%arg4 + %arg3 * 4] : memref<508xi32>
        %2 = affine.load %alloca[%arg4] : memref<256xi32>
        %3 = arith.muli %1, %2 : i32
        %4 = arith.addi %arg5, %3 : i32
        affine.yield %4 : i32
      }
      affine.store %0, %arg2[%arg3] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
