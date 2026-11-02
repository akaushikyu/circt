// RUN: hls-est %s --symbol-privatize=exclude=_Z6gd_topPA16_KfPA32_S_fPA16_fS5_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6gd_topPA16_KfPA32_S_fPA16_fS5_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6gd_topPA16_KfPA32_S_fPA16_fS5_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6gd_topPA16_KfPA32_S_fPA16_fS5_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 --config-set tool.hls.middle_end.dse_guarded_stores=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N90 (negative): gd_f plus a later loop that reads acc. Vitis keeps the guarded init store: II 2 ([HLS 200-885] limited memory ports on acc), RAM_AUTO_1R1W 2.
// hls-est: the array is accessed outside the loop, so the guarded store keeps its port (same with the key off).
// Kernel w9r11i_gd_g (~/hls-est-work/exp-src/w9r11i/gd_g.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 2, 2 BRAM_18K.
// CHECK: pipeline @ {{.*}}: ii=2 trip=8192
// CHECK: Total BRAM: 2{{$}}
// OFF: pipeline @ {{.*}}: ii=2 trip=8192
// OFF: Total BRAM: 2{{$}}

#set = affine_set<(d0) : (d0 == 0)>
#set1 = affine_set<(d0) : (d0 - 15 == 0)>
module {
  func.func @_Z6gd_topPA16_KfPA32_S_fPA16_fS5_(%arg0: memref<16x16xf32>, %arg1: memref<16x32xf32>, %arg2: f32, %arg3: memref<32x16xf32>, %arg4: memref<32x16xf32>) attributes {hls.orig_name = "gd_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<32x16xf32>
    affine.for %arg5 = 0 to 16 {
      affine.for %arg6 = 0 to 16 {
        affine.for %arg7 = 0 to 32 {
          affine.if #set(%arg6) {
            affine.store %arg2, %alloca[%arg7, %arg5] : memref<32x16xf32>
          }
          %0 = affine.load %alloca[%arg7, %arg5] : memref<32x16xf32>
          %1 = affine.load %arg0[%arg5, %arg6] : memref<16x16xf32>
          %2 = affine.load %arg1[%arg6, %arg7] : memref<16x32xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          affine.store %4, %alloca[%arg7, %arg5] : memref<32x16xf32>
          affine.if #set1(%arg6) {
            affine.store %4, %arg3[%arg7, %arg5] : memref<32x16xf32>
          }
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    }
    affine.for %arg5 = 0 to 32 {
      affine.for %arg6 = 0 to 16 {
        %0 = affine.load %alloca[%arg5, %arg6] : memref<32x16xf32>
        affine.store %0, %arg4[%arg5, %arg6] : memref<32x16xf32>
      }
    }
    return
  }
}
