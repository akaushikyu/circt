// RUN: hls-est %s --symbol-privatize=exclude=_Z6fx_topPKiS0_S0_S0_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6fx_topPKiS0_S0_S0_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6fx_topPKiS0_S0_S0_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6fx_topPKiS0_S0_S0_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.partitioning.block_bank_from_loop_range=false --config-set tool.hls.partitioning.banks_from_value_range=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r10 review fix D2 (2026-10-21): VITIS_NOTES N86 residual: as w9r10fx_n86_block_bank_range.mlir, but the read loop indexes buf[sel[i] & 127] and buf[128 + (sel[i] & 63)].
// The stores now have constant banks. Vitis bounds the masked reads by the masks (banks 0-1 and bank 2): 3 x RAM_AUTO_1R1W, 1 BRAM_18K each.
// Since W9r23-impl tool.hls.partitioning.banks_from_value_range (VITIS_NOTES N175) bounds them too: 3 (OPEN_ISSUES O116 closed).
// OFF (both range keys off): the masked reads reach every bank, 2 reads each (RAM_2P x18, 2 each) = 6.
// Kernel w9r10fx_fx_blkl (~/hls-est-work/exp-src/w9r10fx/fx_blkl.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: 3 BRAM_18K.
// CHECK: Total BRAM: 3{{$}}
// OFF: Total BRAM: 6{{$}}

module {
  func.func @_Z6fx_topPKiS0_S0_S0_Pi(%arg0: memref<64xi32>, %arg1: memref<64xi32>, %arg2: memref<64xi32>, %arg3: memref<64xi32>, %arg4: memref<64xi32>) attributes {hls.orig_name = "fx_top", llvm.linkage = #llvm.linkage<external>} {
    %c63_i32 = arith.constant 63 : i32
    %c127_i32 = arith.constant 127 : i32
    %c128_i32 = arith.constant 128 : i32
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
      %0 = affine.load %arg3[%arg5] : memref<64xi32>
      %1 = arith.andi %0, %c127_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %3 = memref.load %alloca[%2] : memref<192xi32>
      %4 = arith.andi %0, %c63_i32 : i32
      %5 = arith.addi %4, %c128_i32 : i32
      %6 = arith.index_cast %5 : i32 to index
      %7 = memref.load %alloca[%6] : memref<192xi32>
      %8 = arith.addi %3, %7 : i32
      affine.store %8, %arg4[%arg5] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
