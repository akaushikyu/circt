// RUN: hls-est %s --symbol-privatize=exclude=_Z6fg_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6fg_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6fg_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6fg_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null --config-set tool.hls.pipeline_decision.fold_unrolled_guards=false 2>&1 | FileCheck %s --check-prefix=OFF
// W9r11 review fixes (2026-10-22), D2: VITIS_NOTES N89 for a guard cgeist emits as arith + scf.if.
// `for k (unrolled 4) if ((j * 4 + k) % 8 == 0) s += buf[j * 4 + k];` plus `buf[j * 4 + 1]` in a pipelined j loop: C's `%`
// becomes remsi + the non-negative select, so the guard is an scf.if. Copies k = 1..3 can never run; copy 0 runs for even j.
// Vitis: 2 reads per cycle, RAM_AUTO_1R1W 64x32 = 2 BRAM_18K, II 1. hls-est before the fix: RAM_1WNR 3 copies = 6 (4 reads).
// Kernel w9r11rev_fg_mod (~/hls-est-work/exp-src/w9r11rev/fg_mod.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 1 / 1, 2 BRAM_18K.
// CHECK: ram type: RAM_2P
// CHECK: pipeline @ {{.*}} ii=1 trip=16 {{.*}} folded_guards=3 pinned_guard_operands=0 (N89)
// CHECK: Total BRAM: 2{{$}}
// OFF: ram type: RAM_1WNR
// OFF: Total BRAM: 6{{$}}

module {
  func.func @_Z6fg_topPKiPi(%arg0: memref<64xi32>, %arg1: memref<16xi32>) attributes {hls.orig_name = "fg_top", llvm.linkage = #llvm.linkage<external>} {
    %c8 = arith.constant 8 : index
    %c4 = arith.constant 4 : index
    %c0 = arith.constant 0 : index
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64xi32>
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %arg0[%arg2] : memref<64xi32>
      %1 = arith.addi %0, %c1_i32 : i32
      affine.store %1, %alloca[%arg2] : memref<64xi32>
    }
    affine.for %arg2 = 0 to 16 {
      %0 = arith.muli %arg2, %c4 : index
      %1 = affine.load %alloca[%arg2 * 4 + 1] : memref<64xi32>
      %2 = affine.for %arg3 = 0 to 4 iter_args(%arg4 = %1) -> (i32) {
        %3 = arith.addi %arg3, %0 : index
        %4 = arith.remsi %3, %c8 : index
        %5 = arith.cmpi slt, %4, %c0 : index
        %6 = arith.addi %4, %c8 : index
        %7 = arith.select %5, %6, %4 : index
        %8 = arith.cmpi eq, %7, %c0 : index
        %9 = scf.if %8 -> (i32) {
          %10 = affine.load %alloca[%arg3 + %arg2 * 4] : memref<64xi32>
          %11 = arith.addi %arg4, %10 : i32
          scf.yield %11 : i32
        } else {
          scf.yield %arg4 : i32
        }
        affine.yield %9 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %2, %arg1[%arg2] : memref<16xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
