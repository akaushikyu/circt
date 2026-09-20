// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPKfPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPKfPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPKfPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPKfPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 --config-set scheduling.dependences.memory_recurrences=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N87 (R2): `a[i] = a[i-2] + x[i]`, float: II = ceil((2 + 4) / 2) = 3 = Vitis.
// Not modelled (residual): Vitis has ram_1p 1 (its load and store fall in different states modulo 3: load state 1, store state 6); hls-est times the chain one cycle longer
// (load 1 + fadd 5 against Vitis' 5 states), the two accesses share a modulo slot and a is RAM_2P 2.
// Kernel w9r11p_rr_d2f (~/hls-est-work/exp-src/w9r11p/rr_d2f.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 3, 1 BRAM_18K.
// CHECK: pipeline @ {{.*}}: ii=3 {{.*}} memory_recurrence=R2 ii>=3 (distance 2, chain 4,
// CHECK: Total BRAM: 2{{$}}
// OFF: pipeline @ {{.*}}: ii=1 trip=254 
// OFF: Total BRAM: 2{{$}}

module {
  func.func @_Z6rr_topPKfPf(%arg0: memref<256xf32>, %arg1: memref<256xf32>) attributes {hls.orig_name = "rr_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<256xf32>
    affine.for %arg2 = 0 to 2 {
      %0 = affine.load %arg0[%arg2] : memref<256xf32>
      affine.store %0, %alloca[%arg2] : memref<256xf32>
    }
    affine.for %arg2 = 2 to 256 {
      %0 = affine.load %alloca[%arg2 - 2] : memref<256xf32>
      %1 = affine.load %arg0[%arg2] : memref<256xf32>
      %2 = arith.addf %0, %1 : f32
      affine.store %2, %alloca[%arg2] : memref<256xf32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 256 {
      %0 = affine.load %alloca[%arg2] : memref<256xf32>
      affine.store %0, %arg1[%arg2] : memref<256xf32>
    }
    return
  }
}
