// RUN: hls-est %s --symbol-privatize=exclude=_Z6mx_topPSt5arrayIiLm9EEPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mx_topPSt5arrayIiLm9EEPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6mx_topPSt5arrayIiLm9EEPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mx_topPSt5arrayIiLm9EEPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.implicit_buffers[0].read_fifo.power_of_two_width=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r8 (2026-10-20): VITIS_NOTES N63: the read FIFO of an m_axi adapter is as
// wide as the widest read rounded up to a power of two. Kernel w9r8p_mx_i9
// (an m_axi port of std::array<int, 9> = 288 bits, depth 256): Vitis
// g0_m_axi 29 = F(256 x 512), buf 1, total 30. MLIR from the installed cgeist
// d0e92867 with the real headers.
// CHECK: m_axi.adapter{{.*}}bram=29
// CHECK: Total BRAM: 30
// OFF: m_axi.adapter{{.*}}bram=16
// OFF: Total BRAM: 17
module {
  func.func @_Z6mx_topPSt5arrayIiLm9EEPi(%arg0: memref<?x!llvm.struct<(array<9 x i32>)>> {hls.interface = [{bundle = "g0", depth = 256 : i32, mode = "m_axi", offset = "slave", port = "a"}]}, %arg1: memref<64xi32> {hls.interface = [{bundle = "g1", depth = 64 : i32, mode = "m_axi", offset = "slave", port = "out"}]}) attributes {hls.interface = [{mode = "s_axilite", port = "return"}], hls.orig_name = "mx_top", llvm.linkage = #llvm.linkage<external>} {
    %c36 = arith.constant 36 : index
    %c255_i32 = arith.constant 255 : i32
    %c61_i32 = arith.constant 61 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {polygeist.varname = "t"} : memref<1x!llvm.struct<(array<9 x i32>)>>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<256xi32>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<9 x i32>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<9 x i32>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 256 {
      %2 = arith.muli %arg2, %c36 : index
      %3 = arith.index_cast %2 : index to i64
      %4 = llvm.getelementptr %1[%3] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      affine.for %arg3 = 0 to 9 {
        %6 = arith.index_cast %arg3 : index to i32
        %7 = llvm.getelementptr %4[%6] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        %8 = llvm.load %7 : !llvm.ptr -> i32
        %9 = llvm.getelementptr %0[%6] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        llvm.store %8, %9 : i32, !llvm.ptr
      }
      %5 = affine.for %arg3 = 0 to 9 iter_args(%arg4 = %c0_i32) -> (i32) {
        %6 = arith.index_cast %arg3 : index to i32
        %7 = arith.extsi %6 : i32 to i64
        %8 = arith.index_castui %7 : i64 to index
        %9 = arith.index_cast %8 : index to i32
        %10 = llvm.getelementptr %0[%9] : (!llvm.ptr, i32) -> !llvm.ptr, i32
        %11 = llvm.load %10 : !llvm.ptr -> i32
        %12 = arith.addi %arg4, %11 : i32
        affine.yield %12 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %5, %alloca_0[%arg2] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 64 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = arith.muli %2, %c61_i32 : i32
      %4 = arith.andi %3, %c255_i32 : i32
      %5 = arith.index_cast %4 : i32 to index
      %6 = memref.load %alloca_0[%5] : memref<256xi32>
      %7 = arith.addi %6, %2 : i32
      affine.store %7, %arg1[%arg2] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
