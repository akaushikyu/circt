// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s

// Invariant-load hoisting is alias-aware (T2 storage-model review, finding
// D1; VITIS_NOTES.md N4 / replication.md R4 only hoist a load from an array
// the loop does not store to).
//
// @alias: the second loop writes buf through a memref.cast defined outside
// the loop and reads buf[0] directly. buf[0] is rewritten at i = 0, so the
// load is NOT loop-invariant: it has to stay inside the pipeline (the alias
// set of buf contains the cast, and a store through it is a write of buf).
// The forwarding cleanup must not touch it either: the store goes through a
// view, which forgets what is known about buf. (The lowering folds the cast
// into the store afterwards, which is why the output stores to the alloca.)
// @alias_subview: the same through a memref.subview (kept by the lowering).
// @direct: the control. buf is only read in the second loop, so the load is
// hoisted above the pipeline and runs once in the function body.

module {
  func.func @alias(%in: memref<64xi32>, %out: memref<64xi32>) {
    %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf_alias"} : memref<64xi32>
    %view = memref.cast %buf : memref<64xi32> to memref<?xi32>
    affine.for %i = 0 to 64 {
      %0 = affine.load %in[%i] : memref<64xi32>
      affine.store %0, %buf[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %buf[0] : memref<64xi32>
      %1 = affine.load %in[%i] : memref<64xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %view[%i] : memref<?xi32>
      affine.store %2, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @alias_subview(%in: memref<64xi32>, %out: memref<64xi32>) {
    %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf_subview"} : memref<64xi32>
    %view = memref.subview %buf[0] [32] [1] : memref<64xi32> to memref<32xi32, strided<[1]>>
    affine.for %i = 0 to 64 {
      %0 = affine.load %in[%i] : memref<64xi32>
      affine.store %0, %buf[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %0 = affine.load %buf[0] : memref<64xi32>
      %1 = affine.load %in[%i] : memref<64xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %view[%i] : memref<32xi32, strided<[1]>>
      affine.store %2, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @direct(%in: memref<64xi32>, %out: memref<64xi32>) {
    %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf_direct"} : memref<64xi32>
    affine.for %i = 0 to 64 {
      %0 = affine.load %in[%i] : memref<64xi32>
      affine.store %0, %buf[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %buf[0] : memref<64xi32>
      %1 = affine.load %in[%i] : memref<64xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %out[%i] : memref<64xi32>
    }
    return
  }
}

// @alias: both pipelines come first, the constant-index load of buf is inside
// the second one (nothing is hoisted between them).
// CHECK-LABEL: func.func @alias
// CHECK:       loopschedule.pipeline
// CHECK-NOT:   memref.load %alloca[%c0
// CHECK:       loopschedule.pipeline
// CHECK:       memref.load %alloca[%c0{{[_0-9]*}}] : memref<64xi32>
// CHECK:       memref.store %{{.*}}, %alloca[%{{.*}}] : memref<64xi32>

// CHECK-LABEL: func.func @alias_subview
// CHECK:       loopschedule.pipeline
// CHECK-NOT:   memref.load %alloca[%c0
// CHECK:       loopschedule.pipeline
// CHECK:       memref.load %alloca[%c0{{[_0-9]*}}] : memref<64xi32>
// CHECK:       memref.store %{{.*}}, %subview[%{{.*}}] : memref<32xi32, strided<[1]>>

// @direct: the load of buf[0] sits between the two pipelines.
// CHECK-LABEL: func.func @direct
// CHECK:       loopschedule.pipeline
// CHECK:       memref.load %alloca[%c0{{[_0-9]*}}] : memref<64xi32>
// CHECK:       loopschedule.pipeline
// CHECK-NOT:   memref.load %alloca
