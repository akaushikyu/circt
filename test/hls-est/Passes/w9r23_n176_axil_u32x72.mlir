// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPjPK7ap_uintILi16EEPS0_ILi32EEi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPjPK7ap_uintILi16EEPS0_ILi32EEi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPjPK7ap_uintILi16EEPS0_ILi32EEi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPjPK7ap_uintILi16EEPS0_ILi32EEi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.interfaces.axi_lite_array_memories=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N176. Kernel w9r23p_s1_axil_u32x72 (~/hls-est-work/exp-src/w9r23p/s1_axil_u32x72.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 4 BRAM (control_s_axi 2, gmem0 2).
// lut[72] (32 bits) bound to s_axilite: a two-port RAM in the control adapter, 72 x 32 at x18 = 2. Off: 2 (the m_axi adapter only).
// CHECK: Total BRAM: 4{{$}}
// OFF: Total BRAM: 2{{$}}
#set = affine_set<(d0)[s0] : (-d0 + s0 - 1 >= 0)>
module {
  func.func @_Z3topPjPK7ap_uintILi16EEPS0_ILi32EEi(%arg0: memref<72xi32> {hls.interface = [{mode = "s_axilite", port = "lut"}]}, %arg1: memref<?xi16> {hls.interface = [{bundle = "gmem0", depth = 64 : i32, mode = "m_axi", offset = "slave", port = "in"}]}, %arg2: memref<?xi32> {hls.interface = [{bundle = "gmem1", depth = 64 : i32, mode = "m_axi", offset = "slave", port = "out"}]}, %arg3: i32 {hls.interface = [{mode = "s_axilite", port = "n"}]}) attributes {hls.interface = [{mode = "s_axilite", port = "return"}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c72_i32 = arith.constant 72 : i32
    %0 = arith.index_cast %arg3 : i32 to index
    affine.for %arg4 = 0 to 64 {
      affine.if #set(%arg4)[%0] {
        %1 = affine.load %arg1[%arg4] : memref<?xi16>
        %2 = arith.extui %1 : i16 to i32
        %3 = arith.remsi %2, %c72_i32 : i32
        %4 = arith.trunci %3 : i32 to i16
        %5 = arith.index_castui %4 : i16 to index
        %6 = memref.load %arg0[%5] : memref<72xi32>
        affine.store %6, %arg2[%arg4] : memref<?xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
