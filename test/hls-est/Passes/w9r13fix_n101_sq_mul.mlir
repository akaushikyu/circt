// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.sequential_scope.loads_before_consumer=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N101, kernel w9r13fix_sq_mul (Vitis 2025.1 td=off: buf RAM_AUTO_1R1W 1):
// `buf[3] * b + buf[15]`: buf[15] issues in the state before the add, after the multiplier.
// Key off: one state of two reads, 2.
// CHECK-DAG: scope pipeline @ {{.*}}:14:5 ii=1:
// CHECK: Total BRAM: 1
// OFF-DAG: scope pipeline @ {{.*}}:14:5 ii=1:
// OFF: Total BRAM: 2
module {
  func.func @_Z3topPKii(%arg0: memref<64xi32>, %arg1: i32) -> i32 attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64xi32>
    affine.for %arg2 = 0 to 64 {
      %4 = arith.index_cast %arg2 : index to i32
      %5 = affine.load %arg0[%arg2] : memref<64xi32>
      %6 = arith.xori %5, %4 : i32
      affine.store %6, %alloca[%arg2] : memref<64xi32>
    }
    %0 = affine.load %alloca[3] : memref<64xi32>
    %1 = arith.muli %0, %arg1 : i32
    %2 = affine.load %alloca[15] : memref<64xi32>
    %3 = arith.addi %1, %2 : i32
    return %3 : i32
  }
}
