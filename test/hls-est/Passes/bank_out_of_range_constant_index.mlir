// RUN: hls-est %s --memory-banking-bram | FileCheck %s
// A constant index outside the partitioned dimension (the arm of
// `h == 0 ? B[i][h] : loc[i][h - 1]` that never runs for the unrolled h = 0
// copy, class_ece8893 FLAT-acceleration) names no bank: it is resolved at
// run time; before, bank -1 indexed out of the bank list (assertion).
// CHECK-LABEL: func.func @oob
// CHECK: arith.remui %c-1, %c4
// CHECK-COUNT-4: memref.load %alloca{{(_[0-9])?}}[%c0, %{{.*}}] : memref<4x1xi32>
// CHECK: return
func.func @oob(%c: i1, %out: memref<4xi32>) {
  %loc = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "loc"}], polygeist.varname = "loc"} : memref<4x4xi32>
  %cm1 = arith.constant -1 : index
  %c0 = arith.constant 0 : index
  %v = scf.if %c -> (i32) {
    %z = arith.constant 0 : i32
    scf.yield %z : i32
  } else {
    %l = memref.load %loc[%c0, %cm1] : memref<4x4xi32>
    scf.yield %l : i32
  }
  memref.store %v, %out[%c0] : memref<4xi32>
  return
}
