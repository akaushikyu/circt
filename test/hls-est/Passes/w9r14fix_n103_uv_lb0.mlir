// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi512EEPiS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi512EEPiS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.partitioning.induction_residue_banks=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// W9r14 review fixes, kernel w9r14rv_uv_lb0 (Vitis 2025.1 td=off): N103's
// run-time-trip loop `for (idx = 0; idx < ptr[k]; idx++)` with `unroll
// factor=2` reading a cyclic-2 channel A: the lower bound is a constant, so
// copy u of the guarded copies always reads bank u (A[2n + u]): Vitis keeps
// one PIPO memory (single, 58). hls-est: the bank of an scf.for induction
// variable plus a constant is known when lb and step are constants and the
// step is a multiple of the factor (tool.hls.partitioning.
// induction_residue_banks); off: both copies reach both banks, 116.
// CHECK: pipeline @ {{.*}} unroll_partial=2 (run-time trip: guarded copies, N103)
// CHECK: Total BRAM: 58
// OFF: Total BRAM: 116

module {
  func.func @_Z3topP7ap_uintILi512EEPiS1_(%arg0: memref<256xi512>, %arg1: memref<17xi32>, %arg2: memref<16xi512>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i512 = arith.constant 0 : i512
    %c1 = arith.constant 1 : index
    %c0 = arith.constant 0 : index
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
      %2 = arith.index_cast %1 : i32 to index
      scf.for %arg4 = %c0 to %2 step %c1 {
        %4 = memref.load %alloca_0[%arg4] : memref<256xi512>
        %5 = affine.load %alloca[] : memref<i512>
        %6 = arith.xori %5, %4 : i512
        affine.store %6, %alloca[] : memref<i512>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
      %3 = affine.load %alloca[] : memref<i512>
      affine.store %3, %arg2[%arg3] : memref<16xi512>
    }
    return
  }
}
