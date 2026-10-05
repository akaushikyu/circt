// RUN: hls-est %s --symbol-privatize=exclude=_Z6fx_topPKiS0_S0_S0_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6fx_topPKiS0_S0_S0_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6fx_topPKiS0_S0_S0_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6fx_topPKiS0_S0_S0_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.partitioning.block_bank_from_loop_range=false --config-set tool.hls.partitioning.banks_from_value_range=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r10 review fix D2 (2026-10-21): VITIS_NOTES N86: buf[192] block factor 3 (depth 64), written buf[i], buf[i+64], buf[i+128] and read the same way in two pipelined i < 64 loops.
// Each index stays inside one block over the loop's range, so each access has a constant bank (one store and one load per bank): Vitis 3 x RAM_AUTO_1R1W, 1 BRAM_18K each.
// Before (OFF, tool.hls.partitioning.block_bank_from_loop_range=false and, since W9r23, banks_from_value_range=false, which bounds the same indices): a store_enable per candidate bank, 3 writes per bank, RAM_T2P x18 -> 2 per bank.
// Kernel w9r10fx_fx_blk2 (~/hls-est-work/exp-src/w9r10fx/fx_blk2.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: 3 BRAM_18K.
// CHECK: Total BRAM: 3{{$}}
// OFF: Total BRAM: 6{{$}}

module {
  func.func @_Z6fx_topPKiS0_S0_S0_Pi(%arg0: memref<64xi32>, %arg1: memref<64xi32>, %arg2: memref<64xi32>, %arg3: memref<64xi32>, %arg4: memref<64xi32>) attributes {hls.orig_name = "fx_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 3 : i32, kind = "block", variable = "buf"}], hls.preserve, polygeist.varname = "buf"} : memref<192xi32>
    affine.for %arg5 = 0 to 64 {
      %0 = affine.load %arg0[%arg5] : memref<64xi32>
      affine.store %0, %alloca[%arg5] : memref<192xi32>
      %1 = affine.load %arg1[%arg5] : memref<64xi32>
      affine.store %1, %alloca[%arg5 + 64] : memref<192xi32>
      %2 = affine.load %arg2[%arg5] : memref<64xi32>
      affine.store %2, %alloca[%arg5 + 128] : memref<192xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg5 = 0 to 64 {
      %0 = affine.load %alloca[%arg5] : memref<192xi32>
      %1 = affine.load %alloca[%arg5 + 64] : memref<192xi32>
      %2 = arith.addi %0, %1 : i32
      %3 = affine.load %alloca[%arg5 + 128] : memref<192xi32>
      %4 = arith.addi %2, %3 : i32
      affine.store %4, %arg4[%arg5] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
