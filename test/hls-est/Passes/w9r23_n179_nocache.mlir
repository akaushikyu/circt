// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=top math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=top math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.implicit_buffers[0].read_fifo.cache_bram=0' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N179. Kernel w9r23p_x2_nocache_f64 (~/hls-est-work/exp-src/w9r23p/x2_nocache_f64.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 4 BRAM.
// Control: no cache pragma, 4 either way.
// CHECK: Total BRAM: 4{{$}}
// OFF: Total BRAM: 4{{$}}
module {
  func.func @top(%arg0: memref<?xf64> {hls.interface = [{bundle = "gin", depth = 1025 : i32, mode = "m_axi", port = "in"}]}, %arg1: memref<?xf64> {hls.interface = [{bundle = "gout", depth = 1024 : i32, mode = "m_axi", port = "out"}]}, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %0 = arith.index_cast %arg2 : i32 to index
    affine.for %arg3 = 0 to %0 {
      %1 = affine.load %arg0[%arg3] : memref<?xf64>
      %2 = affine.load %arg0[%arg3 + 1] : memref<?xf64>
      %3 = arith.addf %1, %2 : f64
      affine.store %3, %arg1[%arg3] : memref<?xf64>
    }
    return
  }
}
