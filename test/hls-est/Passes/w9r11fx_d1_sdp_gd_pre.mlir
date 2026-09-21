// RUN: hls-est %s --symbol-privatize=exclude=_Z6gd_topPA16_KfPA32_S_fPA16_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6gd_topPA16_KfPA32_S_fPA16_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6gd_topPA16_KfPA32_S_fPA16_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6gd_topPA16_KfPA32_S_fPA16_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null --config-set tool.hls.memory_architecture.one_loop_read_write_sdp=false 2>&1 | FileCheck %s --check-prefix=OFF
// W9r11 review fixes (2026-10-22), D1: VITIS_NOTES N90 (c) with two writes per iteration at II 2 and a loop that only writes acc
// (before the main loop). acc[32][16] float: `if (j == 0) acc[k][i] = b0; acc[k][i] += A[i][j] * B[j][k]; if (j == 15)
// out[k][i] = acc[k][i];` in a pipelined k loop (II 2 in Vitis and hls-est: the guarded store stays, N90 (a) needs no other
// loop). One read per iteration, two writes spread over the II: Vitis RAM_AUTO_1R1W 512x32 = 1 BRAM_18K. hls-est before the
// fix: RAM_T2P x18 = 2 (its schedule puts both writes in one modulo slot).
// Kernel w9r11rev_gd_pre (~/hls-est-work/exp-src/w9r11rev/gd_pre.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: main loop II 2, 1 BRAM_18K.
// CHECK: ram type: RAM_S2P
// CHECK: pipeline @ {{.*}} ii=2 trip=8192
// CHECK: Total BRAM: 1{{$}}
// OFF: ram type: RAM_T2P
// OFF: Total BRAM: 2{{$}}

#set = affine_set<(d0) : (d0 == 0)>
#set1 = affine_set<(d0) : (d0 - 15 == 0)>
module {
  func.func @_Z6gd_topPA16_KfPA32_S_fPA16_f(%arg0: memref<16x16xf32>, %arg1: memref<16x32xf32>, %arg2: f32, %arg3: memref<32x16xf32>) attributes {hls.orig_name = "gd_top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<32x16xf32>
    affine.for %arg4 = 0 to 32 {
      affine.for %arg5 = 0 to 16 {
        affine.store %cst, %alloca[%arg4, %arg5] : memref<32x16xf32>
      }
    }
    affine.for %arg4 = 0 to 16 {
      affine.for %arg5 = 0 to 16 {
        affine.for %arg6 = 0 to 32 {
          affine.if #set(%arg5) {
            affine.store %arg2, %alloca[%arg6, %arg4] : memref<32x16xf32>
          }
          %0 = affine.load %alloca[%arg6, %arg4] : memref<32x16xf32>
          %1 = affine.load %arg0[%arg4, %arg5] : memref<16x16xf32>
          %2 = affine.load %arg1[%arg5, %arg6] : memref<16x32xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = arith.addf %0, %3 : f32
          affine.store %4, %alloca[%arg6, %arg4] : memref<32x16xf32>
          affine.if #set1(%arg5) {
            affine.store %4, %arg3[%arg6, %arg4] : memref<32x16xf32>
          }
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    }
    return
  }
}
