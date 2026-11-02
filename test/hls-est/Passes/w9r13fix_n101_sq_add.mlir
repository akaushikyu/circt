// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.sequential_scope.loads_before_consumer=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N101 control, kernel w9r13fix_sq_add (Vitis 2025.1 td=off: buf 2): `buf[3] + buf[15] + b`,
// one consumer, one state of two reads either way.
// CHECK-DAG: scope pipeline @ {{.*}}:13:5 ii=1:
// CHECK: Total BRAM: 2
// OFF-DAG: scope pipeline @ {{.*}}:13:5 ii=1:
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
    %1 = affine.load %alloca[15] : memref<64xi32>
    %2 = arith.addi %0, %1 : i32
    %3 = arith.addi %2, %arg1 : i32
    return %3 : i32
  }
}
