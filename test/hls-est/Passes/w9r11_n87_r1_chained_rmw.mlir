// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPA128_KfPS_fPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPA128_KfPS_fPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPA128_KfPS_fPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPA128_KfPS_fPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 --config-set scheduling.dependences.memory_recurrences=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N87 (R1, k chained read-modify-writes): rr_fi with the reduction unrolled 4: four `acc[i]` read-modify-writes of one element per iteration, float.
// The four fadds form one recurrence through the register: II 4 x 4 = 16 (Vitis); one load / one store, ram_1p 1.
// Off: II 2, RAM_T2P 2.
// Kernel w9r11p_rr_u4f (~/hls-est-work/exp-src/w9r11p/rr_u4f.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 16, 1 BRAM_18K.
// CHECK: pipeline @ {{.*}}: ii=16 {{.*}} memory_recurrence=R1 ii>=16 (distance 1, chain 16,
// CHECK: Total BRAM: 1{{$}}
// OFF: pipeline @ {{.*}}: ii=2 
// OFF: Total BRAM: 2{{$}}

#set = affine_set<(d0, d1) : (d0 == 0, d1 == 0)>
module {
  func.func @_Z6rr_topPA128_KfPS_fPf(%arg0: memref<64x128xf32>, %arg1: memref<128xf32>, %arg2: f32, %arg3: memref<64xf32>) attributes {hls.orig_name = "rr_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<64xf32>
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 32 {
        affine.for %arg6 = 0 to 4 {
          affine.if #set(%arg6, %arg5) {
            affine.store %arg2, %alloca[%arg4] : memref<64xf32>
          }
          %0 = affine.load %alloca[%arg4] : memref<64xf32>
          %1 = affine.load %arg0[%arg4, %arg6 + %arg5 * 4] : memref<64x128xf32>
          %2 = affine.load %arg1[%arg6 + %arg5 * 4] : memref<128xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          affine.store %4, %alloca[%arg4] : memref<64xf32>
        }
      } {hls.loop_flatten = [{}], hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg4 = 0 to 64 {
      %0 = affine.load %alloca[%arg4] : memref<64xf32>
      affine.store %0, %arg3[%arg4] : memref<64xf32>
    }
    return
  }
}
