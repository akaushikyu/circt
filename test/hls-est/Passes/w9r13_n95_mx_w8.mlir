// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.implicit_buffers[0].bus_requests.write_per_cycle=0 --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N95, kernel w9r13p_mx_w8 (Vitis 2025.1 td=off: II 8, 4 BRAM): eight
// writes `out[i*8 + u]` per iteration to one m_axi bundle: one write request per
// cycle and bundle.
// CHECK: pipeline @ {{.*}}:19:5 in @{{.*}}: ii=8
// CHECK: Total BRAM: 4
// OFF: pipeline @ {{.*}}:19:5 in @{{.*}}: ii=4

module {
  func.func @_Z3topPKiPi(%arg0: memref<512xi32> {hls.interface = [{bundle = "gmem0", mode = "m_axi", offset = "slave", port = "in"}]}, %arg1: memref<512xi32> {hls.interface = [{bundle = "gmem1", mode = "m_axi", offset = "slave", port = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "loc"} : memref<512xi32>
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %arg0[%arg2] : memref<512xi32>
      affine.store %0, %alloca[%arg2] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 8 {
        %0 = affine.load %alloca[%arg3 + %arg2 * 8] : memref<512xi32>
        %1 = arith.muli %0, %c3_i32 : i32
        affine.store %1, %arg1[%arg3 + %arg2 * 8] : memref<512xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
