// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKff --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKff --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.sequential_scope.loads_before_consumer=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N101, kernel w9r13fix_sq_fadd (Vitis 2025.1 td=off: buf 1): float `buf[3] * b + buf[15]`.
// Key off: 2.
// CHECK-DAG: scope pipeline @ {{.*}}:14:5 ii=1:
// CHECK: Total BRAM: 1
// OFF-DAG: scope pipeline @ {{.*}}:14:5 ii=1:
// OFF: Total BRAM: 2
module {
  func.func @_Z3topPKff(%arg0: memref<64xf32>, %arg1: f32) -> f32 attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 5.000000e-01 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64xf32>
    affine.for %arg2 = 0 to 64 {
      %4 = affine.load %arg0[%arg2] : memref<64xf32>
      %5 = arith.mulf %4, %cst : f32
      affine.store %5, %alloca[%arg2] : memref<64xf32>
    }
    %0 = affine.load %alloca[3] : memref<64xf32>
    %1 = arith.mulf %0, %arg1 : f32
    %2 = affine.load %alloca[15] : memref<64xf32>
    %3 = arith.addf %1, %2 : f32
    return %3 : f32
  }
}
