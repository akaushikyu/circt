// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPA4_KhPA4_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKsPA4_KhPA4_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPA4_KhPA4_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKsPA4_KhPA4_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.pipeline_decision.fold_unrolled_zero_products=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 23 review fixes (2026-10-28). Kernel w9r23rev/v5_block_mask_int (~/hls-est-work/exp-src/w9r23rev/v5_block_mask_int.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 4 BRAM.
// W9 round 23 review D12: `out[j][p] = tab[t] * p` unrolled over 4 lanes: lane 0's product is 0 (an unrolled
// counter 0), its read of tab is dead, 3 reads per bank and iteration: RAM_1WNR 2 copies per bank. Vitis 4.
// With fold_unrolled_zero_products off, 4 reads, 3 copies, 6.
// CHECK: Total BRAM: 4{{$}}
// OFF: Total BRAM: 6{{$}}
module {
  func.func @_Z3topPKsPA4_KhPA4_i(%arg0: memref<1024xi16>, %arg1: memref<1024x4xi8> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "in"}]}, %arg2: memref<1024x4xi32> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c255_i32 = arith.constant 255 : i32
    %c200_i32 = arith.constant 200 : i32
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
        %2 = arith.extui %1 : i8 to i32
        %3 = arith.addi %2, %c200_i32 : i32
        %4 = arith.andi %3, %c255_i32 : i32
        %5 = arith.index_cast %4 : i32 to index
        %6 = memref.load %alloca[%5] : memref<1024xi32>
        %7 = arith.muli %6, %0 : i32
        affine.store %7, %arg2[%arg3, %arg4] : memref<1024x4xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
