// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.memory_architecture.replication.select_of_loads_reload=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N163. A running maximum over three
// reads of t (`m = t[..]; m = std::max(m, t[..]); m = std::max(m, t[..])`, a
// flattened II-1 loop) is 3 element reads and 2 selects whose arms the
// compares also use: Vitis loads the selected address once per select, 5 read
// slots, RAM_1WNR with 4 copies, 8 BRAM (kernel w9r22p_a1_max2; a1_max4 7
// slots, 6 copies; held-out unet_block relu_output). MLIR from the installed
// cgeist 65aa635a (--shim real).
// CHECK: 1024x32b -> RAM_1WNR, 4 copies
// CHECK: Total BRAM: 8
// OFF: 1024x32b -> RAM_1WNR, 2 copies
// OFF: Total BRAM: 4
module {
  func.func @_Z3topPKfPf(%arg0: memref<1024xf32>, %arg1: memref<1024xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 2.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "t"} : memref<1024xf32>
    affine.for %arg2 = 0 to 1024 {
      %0 = affine.load %arg0[%arg2] : memref<1024xf32>
      %1 = arith.mulf %0, %cst : f32
      affine.store %1, %alloca[%arg2] : memref<1024xf32>
    }
    affine.for %arg2 = 0 to 1022 {
      %0 = affine.load %alloca[%arg2] : memref<1024xf32>
      %1 = affine.load %alloca[%arg2 + 1] : memref<1024xf32>
      %2 = arith.cmpf olt, %0, %1 : f32
      %3 = arith.select %2, %1, %0 : f32
      %4 = affine.load %alloca[%arg2 + 2] : memref<1024xf32>
      %5 = arith.cmpf olt, %3, %4 : f32
      %6 = arith.select %5, %4, %3 : f32
      affine.store %6, %arg1[%arg2] : memref<1024xf32>
    }
    return
  }
}
