// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// A partial user unroll whose factor does not divide the trip count. Vitis
// unrolls the body by the factor and keeps the exit checks inside it: there is
// no epilogue loop. So the main loop (10 trips, factor 4 -> 2 iterations of 4
// bodies) keeps `hls.unroll_partial = 4` and is pipelined, and the remainder
// iterations (8, 9) are straight-line code after it - not a second loop that
// would inherit the marker and a pipeline tag of its own.
// CHECK-LABEL: func.func @partial
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 8 step 4 {
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.unroll_partial = 4 : i64}
// CHECK-NOT:     affine.for
// CHECK:         affine.load %{{.*}}[%c8]
// CHECK:         affine.store
// CHECK:         affine.load
// CHECK:         affine.store
// CHECK-NEXT:  }
// CHECK-NEXT:  return
func.func @partial(%a: memref<10xi32>, %out: memref<10xi32>) {
  %c2 = arith.constant 2 : i32
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 10 {
      %0 = affine.load %a[%j] : memref<10xi32>
      %1 = arith.muli %0, %c2 : i32
      affine.store %1, %out[%j] : memref<10xi32>
    } {hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
  }
  return
}

// A factor that divides the trip count: one loop, no remainder code.
// CHECK-LABEL: func.func @divisible
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 8 step 4 {
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.unroll_partial = 4 : i64}
// CHECK-NEXT:  }
// CHECK-NEXT:  return
func.func @divisible(%a: memref<8xi32>, %out: memref<8xi32>) {
  %c2 = arith.constant 2 : i32
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 8 {
      %0 = affine.load %a[%j] : memref<8xi32>
      %1 = arith.muli %0, %c2 : i32
      affine.store %1, %out[%j] : memref<8xi32>
    } {hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
  }
  return
}

// Trip 6, factor 4: MLIR's main loop is left with a single iteration and
// replaced by its body (the op is erased - no marker may be set on it
// afterwards), the cleanup loop (2 iterations) is unrolled completely. No
// loop is left, so nothing blocks the auto-pipelining of the parent, which
// is pipelined with the six bodies in it (their out[] stores promoted out of
// it). Known gap (OPEN_ISSUES O14,
// unconfirmed): Vitis keeps a ceil(6/4) = 2-trip loop of 4 guarded bodies.
// CHECK-LABEL: func.func @single_main
// CHECK:       affine.for %{{.*}} = 0 to 8 iter_args
// CHECK-NOT:     affine.for
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.promoted_element_iter_args = array<i64: {{[0-9, ]+}}>}
// CHECK-COUNT-6: affine.store
// CHECK-NEXT:  return
func.func @single_main(%a: memref<6xi32>, %out: memref<6xi32>) {
  %c2 = arith.constant 2 : i32
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 6 {
      %0 = affine.load %a[%j] : memref<6xi32>
      %1 = arith.muli %0, %c2 : i32
      affine.store %1, %out[%j] : memref<6xi32>
    } {hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
  }
  return
}

// Trip 9, factor 4: the cleanup loop has a single iteration and MLIR
// replaces it by its body, which holds the k loop. That k loop is a loop of
// the remainder iteration, not the cleanup loop: it is not unrolled as a
// remainder and is decided on its own (pipelined). The main loop keeps the
// marker and is pipelined with its four k copies unrolled.
// CHECK-LABEL: func.func @single_cleanup
// CHECK:       affine.for %{{.*}} = 0 to 8 step 4 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 32 : i64, {{.*}}}, {factor = 32 : i64, {{.*}}}, {factor = 32 : i64, {{.*}}}, {factor = 32 : i64, {{.*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.unroll_partial = 4 : i64}
// CHECK-NEXT:  affine.for %{{.*}} = 0 to 32 {
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:  return
func.func @single_cleanup(%a: memref<9x32xi32>, %out: memref<9x32xi32>) {
  %c2 = arith.constant 2 : i32
  affine.for %j = 0 to 9 {
    affine.for %k = 0 to 32 {
      %0 = affine.load %a[%j, %k] : memref<9x32xi32>
      %1 = arith.muli %0, %c2 : i32
      affine.store %1, %out[%j, %k] : memref<9x32xi32>
    }
  } {hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
  return
}
