// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.sink_parent_trailing_stores=true --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// W9r14 review fixes, kernel w9r14rv_st_arr (Vitis 2025.1 td=off): the code
// after the pipelined child loop stores to an output array (out[r*4+c] =
// t[a] + t[b]); Vitis disables the flatten ([HLS 214-437]) and pipelines the
// child alone: t 2 BRAM. hls-est no longer sinks trailing code that writes
// memory into the flattened pipeline (N97 (b) is measured only for a stream
// write); tool.hls.pipeline_decision.sink_parent_trailing_stores=true (the
// W9r14-impl behaviour): the 8 reads join the pipeline, 8.
// CHECK-NOT: sunk_trailing_ops
// CHECK: Total BRAM: 2
// OFF: sunk_trailing_ops=
// OFF: Total BRAM: 8

module {
  func.func @_Z3topPKiPi(%arg0: memref<1024xi32>, %arg1: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "t"} : memref<64xi32>
    affine.for %arg2 = 0 to 16 {
      affine.for %arg3 = 0 to 64 {
        %12 = affine.load %arg0[%arg3 + %arg2 * 64] : memref<1024xi32>
        %13 = arith.muli %12, %c3_i32 : i32
        affine.store %13, %alloca[%arg3] : memref<64xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      %0 = affine.load %alloca[1] : memref<64xi32>
      %1 = affine.load %alloca[7] : memref<64xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %arg1[%arg2 * 4] : memref<64xi32>
      %3 = affine.load %alloca[13] : memref<64xi32>
      %4 = affine.load %alloca[21] : memref<64xi32>
      %5 = arith.addi %3, %4 : i32
      affine.store %5, %arg1[%arg2 * 4 + 1] : memref<64xi32>
      %6 = affine.load %alloca[33] : memref<64xi32>
      %7 = affine.load %alloca[41] : memref<64xi32>
      %8 = arith.addi %6, %7 : i32
      affine.store %8, %arg1[%arg2 * 4 + 2] : memref<64xi32>
      %9 = affine.load %alloca[50] : memref<64xi32>
      %10 = affine.load %alloca[63] : memref<64xi32>
      %11 = arith.addi %9, %10 : i32
      affine.store %11, %arg1[%arg2 * 4 + 3] : memref<64xi32>
    }
    return
  }
}
