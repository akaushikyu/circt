// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.memory_architecture.replication.sequential_state_reads=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N164. t[1024] is read three times per
// iteration of an II-1 loop (RAM_1WNR, 2 copies) and four times after it in
// the owner's sequential code (`t[0] + t[1]`, `t[N-2] + t[N-1]`): Vitis starts
// the four independent loads in one state, so the bank needs 3 copies, 6 BRAM
// (kernel w9r22p_a2_r3_tail; one tail read keeps 2, a2_r3_tail1). With the
// key off the sequential reads do not count: 2 copies, 4.
// CHECK: RAM_1WNR, 3 copies
// CHECK: Total BRAM: 6
// OFF: RAM_1WNR, 2 copies
// OFF: Total BRAM: 4
module {
  func.func @_Z3topPKiPi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c2_i32 = arith.constant 2 : i32
    %c1_i32 = arith.constant 1 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "t"} : memref<1024xi32>
    affine.for %arg2 = 0 to 1024 {
      %8 = affine.load %arg0[%arg2] : memref<1024xi32>
      %9 = arith.muli %8, %c3_i32 : i32
      %10 = arith.addi %9, %c1_i32 : i32
      affine.store %10, %alloca[%arg2] : memref<1024xi32>
    }
    affine.for %arg2 = 1 to 1023 {
      %8 = affine.load %alloca[%arg2 - 1] : memref<1024xi32>
      %9 = affine.load %alloca[%arg2] : memref<1024xi32>
      %10 = arith.addi %8, %9 : i32
      %11 = affine.load %alloca[%arg2 + 1] : memref<1024xi32>
      %12 = arith.addi %10, %11 : i32
      %13 = arith.divsi %12, %c3_i32 : i32
      affine.store %13, %arg1[%arg2] : memref<1024xi32>
    }
    %0 = affine.load %alloca[0] : memref<1024xi32>
    %1 = affine.load %alloca[1] : memref<1024xi32>
    %2 = arith.addi %0, %1 : i32
    %3 = arith.divsi %2, %c2_i32 : i32
    affine.store %3, %arg1[0] : memref<1024xi32>
    %4 = affine.load %alloca[1022] : memref<1024xi32>
    %5 = affine.load %alloca[1023] : memref<1024xi32>
    %6 = arith.addi %4, %5 : i32
    %7 = arith.divsi %6, %c2_i32 : i32
    affine.store %7, %arg1[1023] : memref<1024xi32>
    return
  }
}
