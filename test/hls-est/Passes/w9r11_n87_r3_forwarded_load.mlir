// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 --config-set scheduling.dependences.memory_recurrences=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N87 (R3): `a[i] = a[i-1] + x[i]`, int, pipelined II 1.
// The value a[i-1] is the one stored in the previous iteration: Vitis forwards it and removes the load (no load of a left in the loop), so a is ram_1p 1.
// hls-est marks the load register-promoted (no port): one store per iteration, RAM_1P x36, 1 BRAM; off: load + store at II 1, two ports, 2 BRAM.
// Kernel w9r11p_rr_d1i (~/hls-est-work/exp-src/w9r11p/rr_d1i.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 1, a ram_1p 1 BRAM_18K.
// CHECK: Total BRAM: 1{{$}}
// OFF: Total BRAM: 2{{$}}

module {
  func.func @_Z6rr_topPKiPi(%arg0: memref<256xi32>, %arg1: memref<256xi32>) attributes {hls.orig_name = "rr_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<256xi32>
    %0 = affine.load %arg0[0] : memref<256xi32>
    affine.store %0, %alloca[0] : memref<256xi32>
    affine.for %arg2 = 1 to 256 {
      %1 = affine.load %alloca[%arg2 - 1] : memref<256xi32>
      %2 = affine.load %arg0[%arg2] : memref<256xi32>
      %3 = arith.addi %1, %2 : i32
      affine.store %3, %alloca[%arg2] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 256 {
      %1 = affine.load %alloca[%arg2] : memref<256xi32>
      affine.store %1, %arg1[%arg2] : memref<256xi32>
    }
    return
  }
}
