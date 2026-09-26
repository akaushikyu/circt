// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.modulo.lower_ii_of_both=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// scheduling.modulo.lower_ii_of_both, kernel w9r13p_mx_r8 (Vitis 2025.1 td=off:
// II 8): eight reads of one m_axi bundle per iteration (N95). The simplex
// scheduler fixes the store of the reduction before the last loads and bumps
// the II to 14; the greedy scheduler reaches 8, and the lower II wins.
// CHECK: pipeline @ {{.*}}:15:5 in @{{.*}}: ii=8 {{.*}}scheduler=greedy (lower II than simplex)
// OFF: pipeline @ {{.*}}:15:5 in @{{.*}}: ii=14 {{.*}}scheduler=simplex

module {
  func.func @_Z3topPKiPi(%arg0: memref<512xi32> {hls.interface = [{bundle = "gmem0", mode = "m_axi", offset = "slave", port = "in"}]}, %arg1: memref<64xi32> {hls.interface = [{bundle = "gmem1", mode = "m_axi", offset = "slave", port = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    affine.for %arg2 = 0 to 64 {
      %0 = affine.for %arg3 = 0 to 8 iter_args(%arg4 = %c0_i32) -> (i32) {
        %1 = arith.index_cast %arg3 : index to i32
        %2 = affine.load %arg0[%arg3 + %arg2 * 8] : memref<512xi32>
        %3 = arith.addi %1, %c1_i32 : i32
        %4 = arith.muli %2, %3 : i32
        %5 = arith.addi %arg4, %4 : i32
        affine.yield %5 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %0, %arg1[%arg2] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
