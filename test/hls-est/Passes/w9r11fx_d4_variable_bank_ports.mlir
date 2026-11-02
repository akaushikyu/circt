// RUN: hls-est %s --symbol-privatize=exclude=_Z6pa_topPA8_KiPKhPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6pa_topPA8_KiPKhPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6pa_topPA8_KiPKhPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6pa_topPA8_KiPKhPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null --config-set tool.hls.memory_architecture.partitioned_argument_bank_ports=false 2>&1 | FileCheck %s --check-prefix=OFF
// W9r11 review fixes (2026-10-22), D4: VITIS_NOTES N88 for an access whose bank is not a constant. a[16][8] cyclic 4 on dim 2
// (a top argument): the unrolled k loop reads two words of every bank per iteration, and `a[i][idx[i] & 7]` may read any
// bank: it takes a port of every bank's pool, so each bank has 3 reads on 2 ports. Vitis: II 2. hls-est before the fix: II 1
// (the variable read used a memref-wide pool that did not compete with the per-bank pools); per-bank pools off: II 5.
// Kernel w9r11rev_pa_var3 (~/hls-est-work/exp-src/w9r11rev/pa_var3.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: II 2, 0 BRAM_18K.
// CHECK: pipeline @ {{.*}} ii=2 trip=16 {{.*}} argument_bank_ports=[arg0 any of 4: 1, arg0 bank 0: 2, arg0 bank 1: 2, arg0 bank 2: 2, arg0 bank 3: 2] (N88)
// CHECK: Total BRAM: 0{{$}}
// OFF: pipeline @ {{.*}} ii=5 trip=16
// OFF-NOT: argument_bank_ports

module {
  func.func @_Z6pa_topPA8_KiPKhPi(%arg0: memref<16x8xi32> {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "a"}]}, %arg1: memref<16xi8>, %arg2: memref<16xi32>) attributes {hls.orig_name = "pa_top", llvm.linkage = #llvm.linkage<external>} {
    %c7_i32 = arith.constant 7 : i32
    %c0_i32 = arith.constant 0 : i32
    affine.for %arg3 = 0 to 16 {
      %0 = affine.for %arg4 = 0 to 8 iter_args(%arg5 = %c0_i32) -> (i32) {
        %7 = affine.load %arg0[%arg3, %arg4] : memref<16x8xi32>
        %8 = arith.addi %arg5, %7 : i32
        affine.yield %8 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %1 = affine.load %arg1[%arg3] : memref<16xi8>
      %2 = arith.extui %1 : i8 to i32
      %3 = arith.andi %2, %c7_i32 : i32
      %4 = arith.index_cast %3 : i32 to index
      %5 = memref.load %arg0[%arg3, %4] : memref<16x8xi32>
      %6 = arith.addi %0, %5 : i32
      affine.store %6, %arg2[%arg3] : memref<16xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
