// RUN: hls-est %s --symbol-privatize=exclude=_Z7sdp_topPA32_KfPA32_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7sdp_topPA32_KfPA32_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z7sdp_topPA32_KfPA32_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7sdp_topPA32_KfPA32_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null --config-set tool.hls.memory_architecture.one_loop_read_write_sdp=false 2>&1 | FileCheck %s --check-prefix=OFF
// W9r11 review fixes (2026-10-22), D1: VITIS_NOTES N90 (c) also holds when another loop only writes the array.
// acc[512] float: an init loop writes it, then one pipelined loop reads and writes it once per iteration (distance 32, no
// recurrence) and emits the result in the loop; nothing reads acc after it. Vitis: RAM_AUTO_1R1W 512x32 = 1 BRAM_18K (x36,
// a read-only and a write-only port). hls-est before the fix: RAM_2P x18 = 2 (N90 (c) wanted every access in one loop).
// Kernel w9r11rev_sdp_w (~/hls-est-work/exp-src/w9r11rev/sdp_w.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 1 / 1, 1 BRAM_18K.
// CHECK: ram type: RAM_S2P
// CHECK: Total BRAM: 1{{$}}
// OFF: ram type: RAM_2P
// OFF: Total BRAM: 2{{$}}

module {
  func.func @_Z7sdp_topPA32_KfPA32_f(%arg0: memref<16x32xf32>, %arg1: memref<16x32xf32>) attributes {hls.orig_name = "sdp_top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<512xf32>
    affine.for %arg2 = 0 to 512 {
      affine.store %cst, %alloca[%arg2] : memref<512xf32>
    }
    affine.for %arg2 = 0 to 16 {
      affine.for %arg3 = 0 to 32 {
        %0 = affine.load %alloca[%arg2 + %arg3 * 16] : memref<512xf32>
        %1 = affine.load %arg0[%arg2, %arg3] : memref<16x32xf32>
        %2 = arith.addf %0, %1 : f32
        affine.store %2, %alloca[%arg2 + %arg3 * 16] : memref<512xf32>
        affine.store %2, %arg1[%arg2, %arg3] : memref<16x32xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
