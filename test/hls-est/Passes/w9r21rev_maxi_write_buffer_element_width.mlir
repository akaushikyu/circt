// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPsS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPsS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.implicit_buffers[0].write_buffer.element_width=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 21 review (2026-10-25): VITIS_NOTES N158 (b). A write buffer at
// 1024 bits or more is ceil(W / 18) with W the element width, not the bus
// width padded to 32: kernel w9r21rev_r7a_wb64s (short, max_write_burst_length
// 64: 64 x 16 = 1024 bits) is mem2_m_axi 1 BRAM in Vitis (r7b_wb128c, 128 x
// char, 1; w9r21p_i2_wb32i, 32 x int, 2). Off
// (tool.hls.implicit_buffers[0].write_buffer.element_width=false): 2.
// CHECK: m_axi.adapter bundle=mem2{{.*}} bram=1
// CHECK: Total BRAM: 1
// OFF: m_axi.adapter bundle=mem2{{.*}} bram=2
// OFF: Total BRAM: 2
// MLIR from the private cgeist of the W9 round 21 review fixes (real headers).
module {
  func.func @_Z3topPsS_(%arg0: memref<4096xi16>, %arg1: memref<4096xi16> {hls.interface = [{bundle = "mem2", max_read_burst_length = 32 : i32, max_write_burst_length = 64 : i32, mode = "m_axi", offset = "slave", port = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 4096 {
      %0 = affine.load %arg0[%arg2] : memref<4096xi16>
      %1 = arith.extsi %0 : i16 to i32
      %2 = arith.muli %1, %c3_i32 : i32
      %3 = arith.trunci %2 : i32 to i16
      affine.store %3, %arg1[%arg2] : memref<4096xi16>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
