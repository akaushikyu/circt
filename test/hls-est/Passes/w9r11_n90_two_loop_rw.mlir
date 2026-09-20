// RUN: hls-est %s --symbol-privatize=exclude=_Z6gd_topPA16_KfPA32_S_fPA16_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6gd_topPA16_KfPA32_S_fPA16_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6gd_topPA16_KfPA32_S_fPA16_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6gd_topPA16_KfPA32_S_fPA16_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 --config-set tool.hls.memory_architecture.one_loop_read_write_sdp=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N90 (negative): acc[32][16] float, initialised by one loop, read and written once per iteration by a pipelined loop (II 1), read by a third loop.
// Vitis: RAM_AUTO_1R1W 512x32 = 2 BRAM_18K (x18). hls-est: RAM_2P 2 (other loops access the array; the key changes nothing).
// Kernel w9r11i_gd_b (~/hls-est-work/exp-src/w9r11i/gd_b.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: 2 BRAM_18K.
// CHECK: RAM_2P
// CHECK: Total BRAM: 2{{$}}
// OFF: RAM_2P
// OFF: Total BRAM: 2{{$}}

module {
  func.func @_Z6gd_topPA16_KfPA32_S_fPA16_f(%arg0: memref<16x16xf32>, %arg1: memref<16x32xf32>, %arg2: f32, %arg3: memref<32x16xf32>) attributes {hls.orig_name = "gd_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<32x16xf32>
    affine.for %arg4 = 0 to 32 {
      affine.for %arg5 = 0 to 16 {
        affine.store %arg2, %alloca[%arg4, %arg5] : memref<32x16xf32>
      }
    }
    affine.for %arg4 = 0 to 16 {
      affine.for %arg5 = 0 to 16 {
        %0 = affine.load %arg0[%arg4, %arg5] : memref<16x16xf32>
        affine.for %arg6 = 0 to 32 {
          %1 = affine.load %alloca[%arg6, %arg4] : memref<32x16xf32>
          %2 = affine.load %arg1[%arg5, %arg6] : memref<16x32xf32>
          %3 = arith.mulf %0, %2 : f32
          %4 = arith.addf %1, %3 : f32
          affine.store %4, %alloca[%arg6, %arg4] : memref<32x16xf32>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    }
    affine.for %arg4 = 0 to 32 {
      affine.for %arg5 = 0 to 16 {
        %0 = affine.load %alloca[%arg4, %arg5] : memref<32x16xf32>
        affine.store %0, %arg3[%arg4, %arg5] : memref<32x16xf32>
      }
    }
    return
  }
}
