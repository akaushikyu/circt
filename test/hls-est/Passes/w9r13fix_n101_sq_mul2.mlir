// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.sequential_scope.loads_before_consumer=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N101 control, kernel w9r13fix_sq_mul2 (Vitis 2025.1 td=off: buf 2): `buf[3] * b + buf[15] * c`,
// both consumers start together: one state of two reads either way.
// CHECK-DAG: scope pipeline @ {{.*}}:13:5 ii=1:
// CHECK: Total BRAM: 2
// OFF-DAG: scope pipeline @ {{.*}}:13:5 ii=1:
// OFF: Total BRAM: 2
module {
  func.func @_Z3topPKiii(%arg0: memref<64xi32>, %arg1: i32, %arg2: i32) -> i32 attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64xi32>
    affine.for %arg3 = 0 to 64 {
      %5 = arith.index_cast %arg3 : index to i32
      %6 = affine.load %arg0[%arg3] : memref<64xi32>
      %7 = arith.xori %6, %5 : i32
      affine.store %7, %alloca[%arg3] : memref<64xi32>
    }
    %0 = affine.load %alloca[3] : memref<64xi32>
    %1 = arith.muli %0, %arg1 : i32
    %2 = affine.load %alloca[15] : memref<64xi32>
    %3 = arith.muli %2, %arg2 : i32
    %4 = arith.addi %1, %3 : i32
    return %4 : i32
  }
}
