// RUN: hls-est %s --vitis-fold | FileCheck %s
// RUN: hls-est %s --vitis-fold=raise-counted-loops=false | FileCheck %s --check-prefix=OFF

// --vitis-fold (raise-counted-loops) raises an scf.while whose exit test
// folds to a constant trip count to an affine.for over that count (O72
// review D3, VITIS_NOTES.md N53 (c)). cgeist emits `unsigned char i = 16;
// while (i--)` and `for (int k = 8; --k;)` as scf.while; Vitis computes their
// trip counts (o72r_cdw: `while (i--)` unrolled into the pipelined loop
// around it, buf RAM_1WNR 15 copies, 30; o72r_cdw2: collapsed with its
// 4-trip parent into a 64-trip pipeline, 6). A loop whose exit test reads
// memory (`while (a[m] != key && m < 63)`) keeps its runtime trip count.

// CHECK-LABEL: func.func @top(
// CHECK:         affine.for %{{.*}} = 0 to 4 {
// CHECK:           affine.for %{{.*}} = 0 to 16 iter_args(%{{.*}} = %c0_i32, %{{.*}} = %c16_i8) -> (i32, i8) {
// CHECK:             memref.load
// CHECK:             affine.yield
// CHECK:           affine.for %{{.*}} = 0 to 7 iter_args(
// CHECK:             affine.yield
// CHECK:           scf.while
// CHECK:             arith.cmpi ne
// CHECK:             scf.condition

// OFF-COUNT-3: scf.while
// OFF-NOT:     affine.for %{{.*}} = 0 to 16

module {
  func.func @top(%arg0: memref<64xi32>, %arg1: memref<64xi32>, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c16_i32 = arith.constant 16 : i32
    %c7_i32 = arith.constant 7 : i32
    %c-1_i8 = arith.constant -1 : i8
    %c-1_i32 = arith.constant -1 : i32
    %c63_i32 = arith.constant 63 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i8 = arith.constant 0 : i8
    %c16_i8 = arith.constant 16 : i8
    %c0_i32 = arith.constant 0 : i32
    affine.for %arg3 = 0 to 4 {
      %0:2 = scf.while (%arg4 = %c0_i32, %arg5 = %c16_i8) : (i32, i8) -> (i32, i8) {
        %5 = arith.cmpi ne, %arg5, %c0_i8 : i8
        scf.condition(%5) %arg4, %arg5 : i32, i8
      } do {
      ^bb0(%arg4: i32, %arg5: i8):
        %5 = arith.addi %arg5, %c-1_i8 : i8
        %6 = arith.index_castui %5 : i8 to index
        %7 = memref.load %arg0[%6] : memref<64xi32>
        %8 = arith.extui %5 : i8 to i32
        %9 = arith.addi %8, %c1_i32 : i32
        %10 = arith.muli %7, %9 : i32
        %11 = arith.addi %arg4, %10 : i32
        scf.yield %11, %5 : i32, i8
      }
      %1:2 = scf.while (%arg4 = %c7_i32, %arg5 = %c0_i32) : (i32, i32) -> (i32, i32) {
        %5 = arith.cmpi ne, %arg4, %c0_i32 : i32
        scf.condition(%5) %arg5, %arg4 : i32, i32
      } do {
      ^bb0(%arg4: i32, %arg5: i32):
        %5 = arith.addi %arg5, %c16_i32 : i32
        %6 = arith.index_cast %5 : i32 to index
        %7 = memref.load %arg0[%6] : memref<64xi32>
        %8 = arith.addi %arg4, %7 : i32
        %9 = arith.addi %arg5, %c-1_i32 : i32
        scf.yield %9, %8 : i32, i32
      }
      %2:2 = scf.while (%arg4 = %c0_i32, %arg5 = %c0_i32) : (i32, i32) -> (i32, i32) {
        %5 = arith.index_cast %arg4 : i32 to index
        %6 = memref.load %arg0[%5] : memref<64xi32>
        %7 = arith.cmpi ne, %6, %arg2 : i32
        %8 = arith.cmpi slt, %arg4, %c63_i32 : i32
        %9 = arith.andi %7, %8 : i1
        scf.condition(%9) %arg5, %arg4 : i32, i32
      } do {
      ^bb0(%arg4: i32, %arg5: i32):
        %5 = arith.index_cast %arg5 : i32 to index
        %6 = memref.load %arg0[%5] : memref<64xi32>
        %7 = arith.addi %arg4, %6 : i32
        %8 = arith.addi %arg5, %c1_i32 : i32
        scf.yield %8, %7 : i32, i32
      }
      %3 = arith.addi %0#0, %1#0 : i32
      %4 = arith.addi %3, %2#0 : i32
      affine.store %4, %arg1[%arg3] : memref<64xi32>
    }
    return
  }
}
