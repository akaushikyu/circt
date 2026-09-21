// RUN: hls-est %s --symbol-privatize=exclude=_Z6fg_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6fg_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6fg_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6fg_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null --config-set tool.hls.pipeline_decision.fold_unrolled_guards=false 2>&1 | FileCheck %s --check-prefix=OFF
// W9r11 review fixes (2026-10-22), D3: VITIS_NOTES N89 (b). `for k (unrolled 4) if (k + j == 18) s += buf[k * 16 + j];` plus
// `buf[j * 4]` in a pipelined j loop (j < 16). After the fold only copy k = 3 is left, `if (j == 15) buf[j + 48]`: inside the
// guarded arm j is 15 (an equality of the set fixes it), so the address is the constant 63 and the invariant load is hoisted
// out of the loop (LLVM GVN propagates the equality, LICM speculates the load). Vitis: one read per cycle, RAM_AUTO_1R1W 64x32
// = 1 BRAM_18K. hls-est before the fix: 2 reads per cycle, RAM_2P = 2 (fold off: RAM_1WNR, 8).
// Kernel w9r11rev_fg_unr (~/hls-est-work/exp-src/w9r11rev/fg_unr.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 1 / 1, 1 BRAM_18K.
// CHECK: ram type: RAM_1P
// CHECK: pipeline @ {{.*}} ii=1 trip=16 {{.*}} folded_guards=3 pinned_guard_operands=1 (N89)
// CHECK: Total BRAM: 1{{$}}
// OFF: ram type: RAM_1WNR
// OFF: Total BRAM: 8{{$}}

#set = affine_set<(d0, d1) : (d0 + d1 - 18 == 0)>
module {
  func.func @_Z6fg_topPKiPi(%arg0: memref<64xi32>, %arg1: memref<16xi32>) attributes {hls.orig_name = "fg_top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64xi32>
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %arg0[%arg2] : memref<64xi32>
      %1 = arith.addi %0, %c1_i32 : i32
      affine.store %1, %alloca[%arg2] : memref<64xi32>
    }
    affine.for %arg2 = 0 to 16 {
      %0 = affine.for %arg3 = 0 to 4 iter_args(%arg4 = %c0_i32) -> (i32) {
        %3 = affine.if #set(%arg3, %arg2) -> i32 {
          %4 = affine.load %alloca[%arg2 + %arg3 * 16] : memref<64xi32>
          %5 = arith.addi %arg4, %4 : i32
          affine.yield %5 : i32
        } else {
          affine.yield %arg4 : i32
        }
        affine.yield %3 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %1 = affine.load %alloca[%arg2 * 4] : memref<64xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %arg1[%arg2] : memref<16xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
