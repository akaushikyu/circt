// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPsS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPsS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.implicit_buffers[0].write_buffer.min_bram_bits=0' --config-set 'tool.hls.implicit_buffers[0].write_buffer.element_width=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N158: an m_axi write buffer is a FIFO of
// max_write_burst_length words of the element width, LUTRAM below 1024 bits.
// Kernel w9r21p_i1_wb32s (write-only bundle mem2 of short, burst 32: 32 x 16 =
// 512 bits): Vitis mem2_m_axi 0 BRAM. Kernel w9r21p_i2_wb32i (int: 1024 bits)
// is 2, as before. OFF also turns write_buffer.element_width (N158 (b)) off. MLIR from the installed cgeist 5523df29 with the real headers.
// CHECK: m_axi.adapter bundle=mem2{{.*}} bram=0 ({{.*}}write burst 32 -> 0)
// OFF: m_axi.adapter bundle=mem2{{.*}} bram=2 ({{.*}}write burst 32 -> 2)
module {
  func.func @_Z3topPsS_(%arg0: memref<4096xi16>, %arg1: memref<4096xi16> {hls.interface = [{bundle = "mem2", max_read_burst_length = 32 : i32, max_write_burst_length = 32 : i32, mode = "m_axi", offset = "slave", port = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
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
