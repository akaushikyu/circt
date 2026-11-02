// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_KsPA64_s --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_KsPA64_s --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.partitioning.constant_index.block_offset=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N104, kernel w9r14p_cb_blk (Vitis 2025.1 td=off): short C[64][64]
// with block factor=16 dim=2 (block size 4), written at constant columns,
// read at j = 8 * jj + u (j unroll factor 8): the offset in the block u % 4 is
// a constant, so Vitis partitions every block completely (214-449 / 214-270):
// 64 banks, PIPO single, 64. hls-est: rule (b) on the block offset
// (tool.hls.partitioning.constant_index.block_offset); off: 16 banks, 32.
// CHECK: Total BRAM: 64
// OFF: Total BRAM: 32

module {
  func.func @_Z3topPA64_KsPA64_s(%arg0: memref<64x64xi16>, %arg1: memref<64x64xi16>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 16 : i32, kind = "block", variable = "C"}], hls.preserve, polygeist.varname = "C"} : memref<64x64xi16>
    call @_ZL2wrPA64_KsPA64_s(%arg0, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 326 : i64}} : (memref<64x64xi16>, memref<64x64xi16>) -> ()
    call @_ZL2rdPA64_KsPA64_s(%alloca, %arg1) {hls.inline_auto_off = {calls = 1 : i64, size = 185 : i64}} : (memref<64x64xi16>, memref<64x64xi16>) -> ()
    return
  }
  func.func private @_ZL2wrPA64_KsPA64_s(%arg0: memref<64x64xi16>, %arg1: memref<64x64xi16>) attributes {hls.inline_auto_off = {size = 326 : i64}, hls.orig_name = "wr", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 64 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<64x64xi16>
        %1 = arith.extsi %0 : i16 to i32
        %2 = arith.addi %1, %c1_i32 : i32
        %3 = arith.trunci %2 : i32 to i16
        affine.store %3, %arg1[%arg2, %arg3] : memref<64x64xi16>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL2rdPA64_KsPA64_s(%arg0: memref<64x64xi16>, %arg1: memref<64x64xi16>) attributes {hls.inline_auto_off = {size = 185 : i64}, hls.orig_name = "rd", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 64 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<64x64xi16>
        affine.store %0, %arg1[%arg2, %arg3] : memref<64x64xi16>
      } {hls.unroll = [{factor = 8 : i32, skip_exit_check = false}]}
    } {hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
    return
  }
}
