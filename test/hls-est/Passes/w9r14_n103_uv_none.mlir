// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi512EEPiS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N103, kernel w9r14p_uv_none (Vitis 2025.1 td=off): uv_var
// without the unroll pragma: one read per cycle, PIPO single (200-741): 58.
// CHECK: Total BRAM: 58

module {
  func.func @_Z3topP7ap_uintILi512EEPiS1_(%arg0: memref<256xi512>, %arg1: memref<17xi32>, %arg2: memref<16xi512>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i512 = arith.constant 0 : i512
    %c1 = arith.constant 1 : index
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
        %6 = memref.load %alloca_0[%arg4] : memref<256xi512>
        %7 = affine.load %alloca[] : memref<i512>
        %8 = arith.xori %7, %6 : i512
        affine.store %8, %alloca[] : memref<i512>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      %5 = affine.load %alloca[] : memref<i512>
      affine.store %5, %arg2[%arg3] : memref<16xi512>
    }
    return
  }
}
