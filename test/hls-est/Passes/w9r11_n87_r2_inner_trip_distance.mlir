// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPA2_KfPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPA2_KfPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPA2_KfPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPA2_KfPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 --config-set scheduling.dependences.memory_recurrences=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N87 (R2): `acc[j] += A[i][j]` in a flattened nest whose inner trip is 2 (dependence distance 2), float.
// Vitis: [HLS 200-880] carried dependence (distance = 2): II = ceil((2 + 4) / 2) = 3; acc ram_2p 2 (the output loop reads two elements per cycle).
// Kernel w9r11p_rr_j2 (~/hls-est-work/exp-src/w9r11p/rr_j2.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 3, 2 BRAM_18K.
// CHECK: pipeline @ {{.*}}: ii=3 {{.*}} memory_recurrence=R2 ii>=3 (distance 2, chain 4,
// CHECK: Total BRAM: 2{{$}}
// OFF: pipeline @ {{.*}}: ii=1 trip=1024 
// OFF: Total BRAM: 2{{$}}

module {
  func.func @_Z6rr_topPA2_KfPf(%arg0: memref<512x2xf32>, %arg1: memref<2xf32>) attributes {hls.orig_name = "rr_top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<128xf32>
    affine.for %arg2 = 0 to 128 {
      affine.store %cst, %alloca[%arg2] : memref<128xf32>
    }
    affine.for %arg2 = 0 to 512 {
      affine.for %arg3 = 0 to 2 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<512x2xf32>
        %1 = affine.load %alloca[%arg3] : memref<128xf32>
        %2 = arith.addf %1, %0 : f32
        affine.store %2, %alloca[%arg3] : memref<128xf32>
      } {hls.loop_flatten = [{}], hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg2 = 0 to 2 {
      %0 = affine.load %alloca[%arg2] : memref<128xf32>
      %1 = affine.load %alloca[%arg2 + 2] : memref<128xf32>
      %2 = arith.addf %0, %1 : f32
      affine.store %2, %arg1[%arg2] : memref<2xf32>
    }
    return
  }
}
