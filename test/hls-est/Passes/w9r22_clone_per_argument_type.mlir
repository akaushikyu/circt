// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfS0_S0_Pf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfS0_S0_Pf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfS0_S0_Pf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfS0_S0_Pf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.inlining.clone_per_argument_type=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N165. work(a, b, o) is kept
// (INLINE off) and called three times in sequence with float arrays that are
// top-level ports (p) or caller locals (l): (p, p, l), (l, p, l), (l, l, p).
// Vitis' IR has a float port as [N x i32]* and a local as [N x float]*, so
// the three call sites call three clones (work, work_1, work_2), each a
// module with its own buf: 3 x 2 + t1 2 + t2 2 = 10 (kernel w9r22p_b1_mix);
// one module shared by the sequential calls gives 6 (OFF). MLIR from the
// installed cgeist 65aa635a (--shim real).
// CHECK-COUNT-5: 1024x32b -> RAM_1P
// CHECK: Total BRAM: 10
// OFF: Total BRAM: 6
module {
  func.func @_Z3topPKfS0_S0_Pf(%arg0: memref<1024xf32>, %arg1: memref<1024xf32>, %arg2: memref<1024xf32>, %arg3: memref<1024xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "t2"} : memref<1024xf32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "t1"} : memref<1024xf32>
    call @_ZL4workPKfS0_Pf(%arg0, %arg1, %alloca_0) : (memref<1024xf32>, memref<1024xf32>, memref<1024xf32>) -> ()
    call @_ZL4workPKfS0_Pf(%alloca_0, %arg2, %alloca) : (memref<1024xf32>, memref<1024xf32>, memref<1024xf32>) -> ()
    call @_ZL4workPKfS0_Pf(%alloca, %alloca_0, %arg3) : (memref<1024xf32>, memref<1024xf32>, memref<1024xf32>) -> ()
    return
  }
  func.func private @_ZL4workPKfS0_Pf(%arg0: memref<1024xf32>, %arg1: memref<1024xf32>, %arg2: memref<1024xf32>) attributes {hls.inline_off, hls.orig_name = "work", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<1024xf32>
    affine.for %arg3 = 0 to 1024 {
      %1 = affine.load %arg0[%arg3] : memref<1024xf32>
      %2 = affine.load %arg1[%arg3] : memref<1024xf32>
      %3 = arith.addf %1, %2 : f32
      affine.store %3, %alloca[%arg3] : memref<1024xf32>
    }
    %0 = affine.for %arg3 = 0 to 1024 iter_args(%arg4 = %cst) -> (f32) {
      %1 = affine.load %alloca[%arg3] : memref<1024xf32>
      %2 = arith.addf %arg4, %1 : f32
      affine.yield %2 : f32
    }
    affine.for %arg3 = 0 to 1024 {
      %1 = affine.load %alloca[-%arg3 + 1023] : memref<1024xf32>
      %2 = arith.mulf %1, %0 : f32
      affine.store %2, %arg2[%arg3] : memref<1024xf32>
    }
    return
  }
}
