// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_PsPA64_s --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_PsPA64_s --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.dataflow_channels.promoted_invariant_accesses=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N105, kernel w9r14p_pp_mid (Vitis 2025.1 td=off): X[i][col & 63]
// += v (X complete on dim 2) in a pipelined loop inside a variable-trip loop
// (mid) of each of the 4 unrolled row copies: Vitis promotes the row to
// registers (load before, store after the pipeline); the store-back of one copy
// and the preload of the next are separated by the mid loop, so the PIPO is
// single (200-741): 67. hls-est: tool.hls.dataflow_channels.
// promoted_invariant_accesses; off: separate, 131.
// CHECK: mode: single (every process uses one port of the bank (the loop-invariant accesses of the pipelined loop(s) at {{.*}} are registers: one load before, one store after the loop, VITIS_NOTES N105))
// CHECK: Total BRAM: 67
// OFF-NOT: VITIS_NOTES N105
// OFF: Total BRAM: 131

module {
  func.func @_Z3topPiS_PsPA64_s(%arg0: memref<65xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi16>, %arg3: memref<64x64xi16>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1 = arith.constant 1 : index
    %c63_i32 = arith.constant 63 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "lrp"}], hls.preserve, polygeist.varname = "lrp"} : memref<65xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "lval"} : memref<1024xi16>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "lcol"} : memref<1024xi32>
    %alloca_2 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "X"}], hls.preserve, polygeist.varname = "X"} : memref<64x64xi16>
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 64 {
        affine.store %c0_i16, %alloca_2[%arg4, %arg5] : memref<64x64xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg4 = 0 to 1024 {
      %0 = affine.load %arg1[%arg4] : memref<1024xi32>
      affine.store %0, %alloca_1[%arg4] : memref<1024xi32>
      %1 = affine.load %arg2[%arg4] : memref<1024xi16>
      affine.store %1, %alloca_0[%arg4] : memref<1024xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg4 = 0 to 65 {
      %0 = affine.load %arg0[%arg4] : memref<65xi32>
      affine.store %0, %alloca[%arg4] : memref<65xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg4 = 0 to 64 {
      %0 = affine.load %alloca[%arg4] : memref<65xi32>
      %1 = affine.load %alloca[%arg4 + 1] : memref<65xi32>
      %2 = arith.index_cast %1 : i32 to index
      %3 = arith.index_cast %0 : i32 to index
      scf.for %arg5 = %3 to %2 step %c1 {
        %4 = memref.load %alloca_1[%arg5] : memref<1024xi32>
        %5 = arith.andi %4, %c63_i32 : i32
        %6 = memref.load %alloca_0[%arg5] : memref<1024xi16>
        %7 = arith.index_cast %5 : i32 to index
        %8 = memref.load %alloca[%7] : memref<65xi32>
        %9 = arith.addi %5, %c1_i32 : i32
        %10 = arith.index_cast %9 : i32 to index
        %11 = memref.load %alloca[%10] : memref<65xi32>
        %12 = arith.index_cast %11 : i32 to index
        %13 = arith.index_cast %8 : i32 to index
        scf.for %arg6 = %13 to %12 step %c1 {
          %14 = memref.load %alloca_1[%arg6] : memref<1024xi32>
          %15 = arith.andi %14, %c63_i32 : i32
          %16 = arith.index_cast %15 : i32 to index
          %17 = memref.load %alloca_2[%arg4, %16] : memref<64x64xi16>
          %18 = arith.addi %17, %6 : i16
          memref.store %18, %alloca_2[%arg4, %16] : memref<64x64xi16>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    } {hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 64 {
        %0 = affine.load %alloca_2[%arg4, %arg5] : memref<64x64xi16>
        affine.store %0, %arg3[%arg4, %arg5] : memref<64x64xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
