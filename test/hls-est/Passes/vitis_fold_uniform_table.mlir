// RUN: hls-est %s --vitis-fold | FileCheck %s
// RUN: hls-est %s --vitis-fold='uniform-tables=false' | FileCheck %s --check-prefix=NOFOLD
// RUN: hls-est %s --vitis-fold='raise-counted-loops=false' | FileCheck %s --check-prefix=NORAISE

// --vitis-fold, options uniform-tables and raise-counted-loops (VITIS_NOTES.md
// N52). A never-written one-element global (a scalar global) is its initial
// value: Vitis folds it before its automatic pipeline decision (rvsf_g1 /
// rvsf_g2: `int ksz = 16` as an inner bound, outer loop pipelined, 30). A
// multi-element table of one value folds in Vitis only after the pipeline
// decision has partitioned it into registers (rvsf_rc16 / rc4 / rc2nc:
// `cnt[2|4]` all 16 as the inner bound, inner loop pipelined, 2), so it is
// not folded here. cgeist leaves a loop bounded by such a load an scf.for;
// once the bound folds to a constant, the loop becomes the normalised
// affine.for over its trip count and its accesses become affine (rvsf_g3:
// constant-index partitioning of buf's dimension 2, 16 = Vitis).

// CHECK-LABEL: func.func @scalar
// CHECK-NOT: memref.load
// CHECK-NOT: scf.for
// CHECK: affine.for %{{.*}} = 0 to 2 {
// CHECK: affine.for %[[K:.*]] = 0 to 64 iter_args(%{{.*}} = %{{.*}}) -> (i32) {
// CHECK: affine.load %arg0[%[[K]] * 4 + 4]
// CHECK: } {hls.keep_me}

// NOFOLD-LABEL: func.func @scalar
// NOFOLD: memref.load %{{.*}}[%{{.*}}] : memref<1xi32>
// NOFOLD: scf.for

// NORAISE-LABEL: func.func @scalar
// NORAISE-NOT: memref.load %{{.*}} : memref<1xi32>
// NORAISE: scf.for %{{.*}} = %c4 to %c260 step %c4
// NORAISE: memref.load %arg0

// A two-element table of one value stays a load (rvsf_rc16: Vitis folds it
// only after the pipeline decision).
// CHECK-LABEL: func.func @uniform2
// CHECK: memref.load %{{.*}}[%{{.*}}] : memref<2xi32>
// CHECK: scf.for

// Elements that differ: the load stays (shafix_v3b).
// CHECK-LABEL: func.func @mixed
// CHECK: memref.load %{{.*}}[%{{.*}}] : memref<2xi32>
// CHECK: scf.for

// A scalar global that is written somewhere is not a constant.
// CHECK-LABEL: func.func @written
// CHECK: memref.load %{{.*}}[%{{.*}}] : memref<1xi32>
// CHECK: scf.for

// An access indexed by a value of an enclosing non-affine loop stays a
// memref access after the raise.
// CHECK-LABEL: func.func @outer_scf
// CHECK: scf.for %[[J:.*]] =
// CHECK: affine.for %[[I:.*]] = 0 to 16 {
// CHECK: memref.load %arg0[%[[J]], %[[I]]]
// CHECK: affine.store %{{.*}}, %arg1[%[[I]]]

module {
  memref.global "private" @ksz : memref<1xi32> = dense<256>
  memref.global "private" @cnt : memref<2xi32> = dense<256>
  memref.global "private" @cnt_mixed : memref<2xi32> = dense<[256, 128]>
  memref.global "private" @ksz_written : memref<1xi32> = dense<256>
  memref.global "private" @k16 : memref<1xi32> = dense<16>

  func.func @scalar(%a: memref<512xi32>, %out: memref<2xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %c0 = arith.constant 0 : index
    %c4 = arith.constant 4 : index
    %t = memref.get_global @ksz : memref<1xi32>
    affine.for %j = 0 to 2 {
      %n = memref.load %t[%c0] : memref<1xi32>
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

  func.func @uniform2(%a: memref<512xi32>, %out: memref<2xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %t = memref.get_global @cnt : memref<2xi32>
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

  func.func @written(%a: memref<512xi32>, %out: memref<2xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %t = memref.get_global @ksz_written : memref<1xi32>
    affine.for %j = 0 to 2 {
      %n = memref.load %t[%c0] : memref<1xi32>
      %ub = arith.index_cast %n : i32 to index
      %s = scf.for %i = %c0 to %ub step %c1 iter_args(%acc = %c0_i32) -> (i32) {
        %x = memref.load %a[%i] : memref<512xi32>
        %y = arith.addi %acc, %x : i32
        scf.yield %y : i32
      }
      %si = arith.addi %s, %n : i32
      memref.store %si, %t[%c0] : memref<1xi32>
    }
    return
  }

  func.func @outer_scf(%a: memref<16x16xi32>, %out: memref<16xi32>, %m: index) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %t = memref.get_global @k16 : memref<1xi32>
    scf.for %j = %c0 to %m step %c1 {
      %n = memref.load %t[%c0] : memref<1xi32>
      %ub = arith.index_cast %n : i32 to index
      scf.for %i = %c0 to %ub step %c1 {
        %x = memref.load %a[%j, %i] : memref<16x16xi32>
        memref.store %x, %out[%i] : memref<16xi32>
      }
    }
    return
  }
}
