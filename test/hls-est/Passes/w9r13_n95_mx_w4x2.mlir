// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N95, kernel w9r13p_mx_w4x2 (Vitis 2025.1 td=off: II 4, 4 BRAM):
// four writes to each of two bundles per iteration: II 4, so the local `loc`
// read 8 times per iteration needs no RAM_1WNR copy (2). Before: II 2, 8.
// CHECK: pipeline @ {{.*}}:18:5 in @{{.*}}: ii=4
// CHECK: Total BRAM: 4

module {
  func.func @_Z3topPKiPiS1_(%arg0: memref<512xi32> {hls.interface = [{bundle = "gmem0", mode = "m_axi", offset = "slave", port = "in"}]}, %arg1: memref<256xi32> {hls.interface = [{bundle = "gmem1", mode = "m_axi", offset = "slave", port = "out0"}]}, %arg2: memref<256xi32> {hls.interface = [{bundle = "gmem2", mode = "m_axi", offset = "slave", port = "out1"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c5_i32 = arith.constant 5 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "loc"} : memref<512xi32>
    affine.for %arg3 = 0 to 512 {
      %0 = affine.load %arg0[%arg3] : memref<512xi32>
      affine.store %0, %alloca[%arg3] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 4 {
        %0 = affine.load %alloca[%arg4 + %arg3 * 8] : memref<512xi32>
        %1 = arith.muli %0, %c3_i32 : i32
        affine.store %1, %arg1[%arg4 + %arg3 * 4] : memref<256xi32>
        %2 = affine.load %alloca[%arg4 + %arg3 * 8 + 4] : memref<512xi32>
        %3 = arith.muli %2, %c5_i32 : i32
        affine.store %3, %arg2[%arg4 + %arg3 * 4] : memref<256xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
