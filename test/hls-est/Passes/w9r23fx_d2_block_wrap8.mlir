// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPA4_KhPA4_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKsPA4_KhPA4_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPA4_KhPA4_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKsPA4_KhPA4_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.partitioning.banks_from_value_range=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 23 review fixes (2026-10-28). Kernel w9r23rev/v3_block_wrap8 (~/hls-est-work/exp-src/w9r23rev/v3_block_wrap8.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 4 BRAM.
// W9 round 23 review D2 (VITIS_NOTES N175): `u8 t = in[j][p]; t += 200; tab[t]`: an index_castui of an i8 whose
// range is unknown is in [0, 255], blocks 0 and 1 of tab[1024] block factor 8 (before: unknown, all 8 blocks, 24).
// Vitis 4. With the key off every block is a candidate: 8 blocks x 2 copies, 16.
// CHECK: Total BRAM: 4{{$}}
// OFF: Total BRAM: 16{{$}}
module {
  func.func @_Z3topPKsPA4_KhPA4_i(%arg0: memref<1024xi16>, %arg1: memref<1024x4xi8> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "in"}]}, %arg2: memref<1024x4xi32> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-56_i8 = arith.constant -56 : i8
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "block", variable = "tab"}], hls.preserve, polygeist.varname = "tab"} : memref<1024xi32>
    affine.for %arg3 = 0 to 1024 {
      %0 = affine.load %arg0[%arg3] : memref<1024xi16>
      %1 = arith.extsi %0 : i16 to i32
      affine.store %1, %alloca[%arg3] : memref<1024xi32>
    }
    affine.for %arg3 = 0 to 1024 {
      affine.for %arg4 = 0 to 4 {
        %0 = arith.index_cast %arg4 : index to i32
        %1 = affine.load %arg1[%arg3, %arg4] : memref<1024x4xi8>
        %2 = arith.addi %1, %c-56_i8 : i8
        %3 = arith.index_castui %2 : i8 to index
        %4 = memref.load %alloca[%3] : memref<1024xi32>
        %5 = arith.muli %4, %0 : i32
        affine.store %5, %arg2[%arg3, %arg4] : memref<1024x4xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
