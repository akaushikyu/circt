// RUN: hls-est %s --infer-vitis-split-array=td=off | FileCheck %s

// VITIS_NOTES N110 on a chain of two registers arrays (W9 round 15 review,
// finding 8): w2[1] is never read, so its store is deleted with the load of
// w1[1] that fed it; that leaves w1[1] unread, and its store is deleted with
// the add that fed it in a second round. The first version ran one round, so
// the result depended on the order of the arrays (w1 is visited first here
// and kept its dead store). The rule runs to a fixpoint.
// CHECK: hls.registers_reason = "{{.*}}1 store(s) into element(s) no used load reads deleted{{.*}}", polygeist.varname = "w1"
// CHECK: hls.registers_reason = "{{.*}}1 store(s) into element(s) no used load reads deleted{{.*}}", polygeist.varname = "w2"
// CHECK-NOT: affine.store %{{.*}}, %{{.*}}[1] : memref<2xi8>

module {
  func.func @top(%in: memref<64xi8>, %out: memref<64xi8>) {
    %c1 = arith.constant 1 : i8
    %w1 = memref.alloca() {polygeist.varname = "w1"} : memref<2xi8>
    %w2 = memref.alloca() {polygeist.varname = "w2"} : memref<2xi8>
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi8>
      %v1 = arith.addi %v, %c1 : i8
      affine.store %v, %w1[0] : memref<2xi8>
      affine.store %v1, %w1[1] : memref<2xi8>
      %a = affine.load %w1[0] : memref<2xi8>
      %b = affine.load %w1[1] : memref<2xi8>
      affine.store %a, %w2[0] : memref<2xi8>
      affine.store %b, %w2[1] : memref<2xi8>
      %c = affine.load %w2[0] : memref<2xi8>
      affine.store %c, %out[%i] : memref<64xi8>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
