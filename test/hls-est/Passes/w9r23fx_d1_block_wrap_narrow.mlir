// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPA4_KhPA4_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKsPA4_KhPA4_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 23 review fixes (2026-10-28). Kernel w9r23rev/v4_block_wrap_narrow (~/hls-est-work/exp-src/w9r23rev/v4_block_wrap_narrow.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 4 BRAM.
// W9 round 23 review D1 (VITIS_NOTES N175): `u8 t = in[j][p] & 15; t += 250; tab[t]` is `addi i8 %t, -6`;
// read unsigned its values are 250..255 and 0..9, so tab[1600] block factor 8 (200 words per block) is read
// on blocks 1 AND 0 (the signed range [-6, 9] gave block 0 only, 3). Vitis 4 (2 blocks x 2 RAM_1WNR copies).
// CHECK: Total BRAM: 4{{$}}
module {
  func.func @_Z3topPKsPA4_KhPA4_i(%arg0: memref<1600xi16>, %arg1: memref<1024x4xi8> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "in"}]}, %arg2: memref<1024x4xi32> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-6_i8 = arith.constant -6 : i8
    %c15_i32 = arith.constant 15 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "block", variable = "tab"}], hls.preserve, polygeist.varname = "tab"} : memref<1600xi32>
    affine.for %arg3 = 0 to 1600 {
      %0 = affine.load %arg0[%arg3] : memref<1600xi16>
      %1 = arith.extsi %0 : i16 to i32
      affine.store %1, %alloca[%arg3] : memref<1600xi32>
    }
    affine.for %arg3 = 0 to 1024 {
      affine.for %arg4 = 0 to 4 {
        %0 = arith.index_cast %arg4 : index to i32
        %1 = affine.load %arg1[%arg3, %arg4] : memref<1024x4xi8>
        %2 = arith.extui %1 : i8 to i32
        %3 = arith.andi %2, %c15_i32 : i32
        %4 = arith.trunci %3 : i32 to i8
        %5 = arith.addi %4, %c-6_i8 : i8
        %6 = arith.index_castui %5 : i8 to index
        %7 = memref.load %alloca[%6] : memref<1600xi32>
        %8 = arith.muli %7, %0 : i32
        affine.store %8, %arg2[%arg3, %arg4] : memref<1024x4xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
