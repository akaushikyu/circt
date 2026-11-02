// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_PsPA64_s --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N105, kernel w9r14p_pp_nomask (Vitis 2025.1 td=off): the RMW
// pipeline directly in the unrolled row body: the store-back of row copy 0 and
// the preload of copy 1 share a state (ST_6): separate, 134.
// CHECK: Total BRAM: 134

module {
  func.func @_Z3topPiS_PsPA64_s(%arg0: memref<65xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi16>, %arg3: memref<64x64xi16>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1 = arith.constant 1 : index
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
        %5 = arith.index_cast %4 : i32 to index
        %6 = memref.load %alloca_0[%arg5] : memref<1024xi16>
        %7 = memref.load %alloca_2[%arg4, %5] : memref<64x64xi16>
        %8 = arith.addi %7, %6 : i16
        memref.store %8, %alloca_2[%arg4, %5] : memref<64x64xi16>
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
