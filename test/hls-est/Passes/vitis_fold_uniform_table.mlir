// RUN: hls-est %s --vitis-fold | FileCheck %s
// RUN: hls-est %s --vitis-fold='uniform-tables=false' | FileCheck %s --check-prefix=NOFOLD
// RUN: hls-est %s --vitis-fold='raise-counted-loops=false' | FileCheck %s --check-prefix=NORAISE

// --vitis-fold, options uniform-tables and raise-counted-loops (VITIS_NOTES.md
// N52). Vitis makes a table of at most complete_threshold (4) elements
// registers (N7 (a)); when it is never written and all its elements hold one
// value, a load from it is that value, whatever the index: kernels
// shafix_v3a / v3c / v3d (`cnt[2] = {256, 256}`; `for (j < 2) { c = cnt[j];
// for (i < c) ... }`) have one flattened 512-trip pipeline, shafix_v3b
// (`{256, 128}`) a variable 128 ~ 256 trip inner loop, and a large table of
// one value (shafix_v3e, 2913 x -4096) stays a ROM; chstone/sha's
// `in_i = {8192, 8192}` is gone in a.o.1.ll. cgeist leaves such an inner
// loop an scf.for (its bound is loaded inside the j loop, not an affine
// symbol); once the bound folds to a constant, the loop becomes the
// normalised affine.for over its trip count.

// CHECK-LABEL: func.func @uniform
// CHECK-NOT: memref.load
// CHECK-NOT: scf.for
// CHECK: affine.for %{{.*}} = 0 to 2 {
// CHECK: affine.for %[[K:.*]] = 0 to 64 iter_args(%{{.*}} = %{{.*}}) -> (i32) {
// CHECK: %[[I:.*]] = affine.apply #map(%[[K]])
// CHECK: memref.load %arg0[%[[I]]]
// CHECK: } {hls.keep_me}

// NOFOLD-LABEL: func.func @uniform
// NOFOLD: memref.load %{{.*}}[%{{.*}}] : memref<2xi32>
// NOFOLD: scf.for

// NORAISE-LABEL: func.func @uniform
// NORAISE-NOT: memref.load %{{.*}} : memref<2xi32>
// NORAISE: scf.for %{{.*}} = %c4 to %c260 step %c4

// Elements that differ: the load stays (shafix_v3b).
// CHECK-LABEL: func.func @mixed
// CHECK: memref.load %{{.*}}[%{{.*}}] : memref<2xi32>
// CHECK: scf.for

// A uniform table of more than 4 elements is a memory, not registers.
// CHECK-LABEL: func.func @big
// CHECK: memref.load %{{.*}}[%{{.*}}] : memref<64xi32>

// A uniform table that is written somewhere is not a constant.
// CHECK-LABEL: func.func @written
// CHECK: memref.load %{{.*}}[%{{.*}}] : memref<2xi32>
// CHECK: scf.for

#map = affine_map<(d0) -> (d0 * 4 + 4)>
module {
  memref.global "private" @cnt : memref<2xi32> = dense<256>
  memref.global "private" @cnt_mixed : memref<2xi32> = dense<[256, 128]>
  memref.global "private" @cnt_written : memref<2xi32> = dense<256>
  memref.global "private" @cnt_big : memref<64xi32> = dense<256>

  func.func @uniform(%a: memref<512xi32>, %out: memref<2xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %c4 = arith.constant 4 : index
    %t = memref.get_global @cnt : memref<2xi32>
    affine.for %j = 0 to 2 {
      %n = memref.load %t[%j] : memref<2xi32>
      %ni = arith.index_cast %n : i32 to index
      %ub = arith.addi %ni, %c4 : index
      %s = scf.for %i = %c4 to %ub step %c4 iter_args(%acc = %c0_i32) -> (i32) {
        %x = memref.load %a[%i] : memref<512xi32>
        %y = arith.addi %acc, %x : i32
        scf.yield %y : i32
      } {hls.keep_me}
      memref.store %s, %out[%j] : memref<2xi32>
    }
    return
  }

  func.func @mixed(%a: memref<512xi32>, %out: memref<2xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %t = memref.get_global @cnt_mixed : memref<2xi32>
    affine.for %j = 0 to 2 {
      %n = memref.load %t[%j] : memref<2xi32>
      %ub = arith.index_cast %n : i32 to index
      %s = scf.for %i = %c0 to %ub step %c1 iter_args(%acc = %c0_i32) -> (i32) {
        %x = memref.load %a[%i] : memref<512xi32>
        %y = arith.addi %acc, %x : i32
        scf.yield %y : i32
      }
      memref.store %s, %out[%j] : memref<2xi32>
    }
    return
  }

  func.func @big(%k: index, %out: memref<2xi32>) {
    %t = memref.get_global @cnt_big : memref<64xi32>
    %n = memref.load %t[%k] : memref<64xi32>
    %c0 = arith.constant 0 : index
    memref.store %n, %out[%c0] : memref<2xi32>
    return
  }

  func.func @written(%a: memref<512xi32>, %out: memref<2xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %t = memref.get_global @cnt_written : memref<2xi32>
    affine.for %j = 0 to 2 {
      %n = memref.load %t[%j] : memref<2xi32>
      %ub = arith.index_cast %n : i32 to index
      %s = scf.for %i = %c0 to %ub step %c1 iter_args(%acc = %c0_i32) -> (i32) {
        %x = memref.load %a[%i] : memref<512xi32>
        %y = arith.addi %acc, %x : i32
        scf.yield %y : i32
      }
      memref.store %s, %t[%j] : memref<2xi32>
    }
    return
  }
}
