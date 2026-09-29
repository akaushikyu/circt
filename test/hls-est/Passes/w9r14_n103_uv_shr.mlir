// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi512EEPiS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N103, kernel w9r14p_uv_shr (Vitis 2025.1 td=off): uv_var with
// the index (idx >> 3) & 255 (both copies read one bank): still separate, 116.
// CHECK: Total BRAM: 116

module {
  func.func @_Z3topP7ap_uintILi512EEPiS1_(%arg0: memref<256xi512>, %arg1: memref<17xi32>, %arg2: memref<16xi512>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i512 = arith.constant 0 : i512
    %c1 = arith.constant 1 : index
    %c255_i32 = arith.constant 255 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() : memref<i512>
    %0 = llvm.mlir.undef : i512
    affine.store %0, %alloca[] : memref<i512>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "A"}], hls.preserve, polygeist.varname = "A"} : memref<256xi512>
    affine.for %arg3 = 0 to 256 {
      %1 = affine.load %arg0[%arg3] : memref<256xi512>
      affine.store %1, %alloca_0[%arg3] : memref<256xi512>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 16 {
      affine.store %c0_i512, %alloca[] : memref<i512>
      %1 = affine.load %arg1[%arg3] : memref<17xi32>
      %2 = affine.load %arg1[%arg3 + 1] : memref<17xi32>
      %3 = arith.index_cast %2 : i32 to index
      %4 = arith.index_cast %1 : i32 to index
      scf.for %arg4 = %4 to %3 step %c1 {
        %6 = arith.index_cast %arg4 : index to i32
        %7 = arith.shrsi %6, %c3_i32 : i32
        %8 = arith.andi %7, %c255_i32 : i32
        %9 = arith.index_cast %8 : i32 to index
        %10 = memref.load %alloca_0[%9] : memref<256xi512>
        %11 = affine.load %alloca[] : memref<i512>
        %12 = arith.xori %11, %10 : i512
        affine.store %12, %alloca[] : memref<i512>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
      %5 = affine.load %alloca[] : memref<i512>
      affine.store %5, %arg2[%arg3] : memref<16xi512>
    }
    return
  }
}
