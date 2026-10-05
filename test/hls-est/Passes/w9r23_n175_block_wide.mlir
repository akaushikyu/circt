// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPA4_KhPA4_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKsPA4_KhPA4_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPA4_KhPA4_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKsPA4_KhPA4_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.partitioning.banks_from_value_range=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N175. Kernel w9r23p_h4_block_wide (~/hls-est-work/exp-src/w9r23p/h4_block_wide.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 8 BRAM.
// As h1 with block factor 16: each lane's range spans two blocks, the only candidates of its bank select. Off: 48.
// CHECK: Total BRAM: 8{{$}}
// OFF: Total BRAM: 48{{$}}
module {
  func.func @_Z3topPKsPA4_KhPA4_i(%arg0: memref<2048xi16>, %arg1: memref<1024x4xi8> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "in"}]}, %arg2: memref<1024x4xi32> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c512_i32 = arith.constant 512 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 16 : i32, kind = "block", variable = "tab"}], hls.preserve, polygeist.varname = "tab"} : memref<2048xi32>
    affine.for %arg3 = 0 to 2048 {
      %0 = affine.load %arg0[%arg3] : memref<2048xi16>
      %1 = arith.extsi %0 : i16 to i32
      affine.store %1, %alloca[%arg3] : memref<2048xi32>
    }
    affine.for %arg3 = 0 to 1024 {
      affine.for %arg4 = 0 to 4 {
        %0 = arith.index_cast %arg4 : index to i32
        %1 = affine.load %arg1[%arg3, %arg4] : memref<1024x4xi8>
        %2 = arith.muli %0, %c512_i32 : i32
        %3 = arith.extui %1 : i8 to i32
        %4 = arith.addi %2, %3 : i32
        %5 = arith.index_cast %4 : i32 to index
        %6 = memref.load %alloca[%5] : memref<2048xi32>
        %7 = arith.muli %6, %3 : i32
        affine.store %7, %arg2[%arg3, %arg4] : memref<1024x4xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
