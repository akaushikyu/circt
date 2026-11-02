// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - 2>&1 | FileCheck %s
// W9r10-impl (2026-10-21), OPEN_ISSUES O111 (b): an integer max / min is a compare and a select, both
// combinational in the timing model, so a loop that computes one is pipelined (before: "not pipelined
// (left as a sequential loop): unsupported operation arith.maxsi"). Struct members of an SSA value
// (llvm.insertvalue / llvm.extractvalue) are wires too. No Vitis claim beyond C semantics.
// CHECK-NOT: unsupported operation
// CHECK: loopschedule.pipeline II = {{ *}}1 trip_count = {{ *}}64
func.func @minmax(%a: memref<64xi32>, %b: memref<64xi32>, %c: memref<64xi32>) {
  affine.for %i = 0 to 64 {
    %x = affine.load %a[%i] : memref<64xi32>
    %y = affine.load %b[%i] : memref<64xi32>
    %m = arith.maxsi %x, %y : i32
    %n = arith.minui %m, %y : i32
    %u = llvm.mlir.undef : !llvm.struct<(i32, i32)>
    %s = llvm.insertvalue %n, %u[0] : !llvm.struct<(i32, i32)>
    %v = llvm.extractvalue %s[0] : !llvm.struct<(i32, i32)>
    affine.store %v, %c[%i] : memref<64xi32>
  }
  return
}
