// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPA32_KfPS_fPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPA32_KfPS_fPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6rr_topPA32_KfPS_fPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6rr_topPA32_KfPS_fPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 --config-set scheduling.dependences.memory_recurrences=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N87 (R1), OPEN_ISSUES O1: a flattened i, j nest, `if (j == 0) acc[i] = b0; acc[i] = acc[i] + A[i][j] * x[j]`, float (stream_hls bicg opt1 v12 shape).
// acc[i] does not change in the inner loop: Vitis keeps it in a register (one load in the first iteration, one store in the last) and the II is the fadd's
// recurrence latency 4 (scheduling.dependences.recurrence_latencies fpaddsub_f32); the init store uses no port (hls.register_promoted_accesses on the load), so acc is RAM_1P x36, 1 BRAM.
// Off (scheduling.dependences.memory_recurrences=false): II 2 (three accesses on two ports), RAM_T2P 2.
// Kernel w9r11p_rr_fi (~/hls-est-work/exp-src/w9r11p/rr_fi.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 4, acc ram_1p 1 BRAM_18K.
// CHECK: pipeline @ {{.*}}:{{[0-9]+}}:5 in @{{.*}}: ii=4 {{.*}} memory_recurrence=R1 ii>=4 (distance 1, chain 4,
// CHECK: Total BRAM: 1{{$}}
// OFF: pipeline @ {{.*}}:{{[0-9]+}}:5 in @{{.*}}: ii=2 
// OFF-NOT: memory_recurrence=
// OFF: Total BRAM: 2{{$}}

#set = affine_set<(d0) : (d0 == 0)>
module {
  func.func @_Z6rr_topPA32_KfPS_fPf(%arg0: memref<64x32xf32>, %arg1: memref<32xf32>, %arg2: f32, %arg3: memref<64xf32>) attributes {hls.orig_name = "rr_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<64xf32>
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 32 {
        affine.if #set(%arg5) {
          affine.store %arg2, %alloca[%arg4] : memref<64xf32>
        }
        %0 = affine.load %alloca[%arg4] : memref<64xf32>
        %1 = affine.load %arg0[%arg4, %arg5] : memref<64x32xf32>
        %2 = affine.load %arg1[%arg5] : memref<32xf32>
        %3 = arith.mulf %1, %2 : f32
        %4 = arith.addf %0, %3 : f32
        affine.store %4, %alloca[%arg4] : memref<64xf32>
      } {hls.loop_flatten = [{}], hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg4 = 0 to 64 {
      %0 = affine.load %alloca[%arg4] : memref<64xf32>
      affine.store %0, %arg3[%arg4] : memref<64xf32>
    }
    return
  }
}
