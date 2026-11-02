// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPKfPKhPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPKfPKhPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPKfPKhPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPKfPKhPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 --config-set scheduling.dependences.memory_recurrences=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N87 (R4): `acc[idx[i] & 63] += x[i]` (float, an address Vitis cannot compute), pipelined II 1 requested.
// Vitis adds a reuse register (reuse_reg) and reaches the fadd recurrence: II 4, acc ram_1p 1. hls-est: the load and the store use one index value -> distance 1, chain 4.
// Off: II 1, load + store on two ports, 2 BRAM.
// Kernel w9r11p_rr_ind (~/hls-est-work/exp-src/w9r11p/rr_ind.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 4, 1 BRAM_18K.
// CHECK: pipeline @ {{.*}}: ii=4 {{.*}} memory_recurrence=R4 ii>=4 (distance 1, chain 4,
// CHECK: Total BRAM: 1{{$}}
// OFF-NOT: memory_recurrence=
// OFF: Total BRAM: 2{{$}}

module {
  func.func @_Z6rr_topPKfPKhPf(%arg0: memref<256xf32>, %arg1: memref<256xi8>, %arg2: memref<64xf32>) attributes {hls.orig_name = "rr_top", llvm.linkage = #llvm.linkage<external>} {
    %c63_i32 = arith.constant 63 : i32
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<64xf32>
    affine.for %arg3 = 0 to 64 {
      affine.store %cst, %alloca[%arg3] : memref<64xf32>
    }
    affine.for %arg3 = 0 to 256 {
      %0 = affine.load %arg1[%arg3] : memref<256xi8>
      %1 = arith.extui %0 : i8 to i32
      %2 = arith.andi %1, %c63_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      %4 = affine.load %arg0[%arg3] : memref<256xf32>
      %5 = memref.load %alloca[%3] : memref<64xf32>
      %6 = arith.addf %5, %4 : f32
      memref.store %6, %alloca[%3] : memref<64xf32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %alloca[%arg3] : memref<64xf32>
      affine.store %0, %arg2[%arg3] : memref<64xf32>
    }
    return
  }
}
