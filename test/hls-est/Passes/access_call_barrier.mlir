// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s

// Load CSE and store forwarding around a call that takes the memref
// (OPEN_ISSUES.md O47). A callee may read and write an array it is passed,
// but only while it runs: the call is a barrier at its own position, not a
// reason to give up on the array in the whole function. Vitis forwards the
// accumulator of a loop whose array is passed to a kept callee after the loop
// (machsuite backprop: get_oracle_activations' accumulator stays RAM_1P 2
// although update_weights, a kept call, takes the array later).
//
// @after_loop: `acc[i] = 0; acc[i] += A[i][0]; acc[i] += A[i][1]` in the
// loop, `use(acc)` after it. The two loads read the store just before them
// and the first two stores are overwritten: one store remains per iteration,
// with 2 forwarded loads and 2 removed stores, as without the call.
// @spans: in one loop body, `x = b[i]; b[i] = v; touch(b); y = b[i];
// b[i] = w; touch((cast) b); z = b[i]`: no access is merged with or forwarded
// to one on the other side of a call. The load after the first call is a
// real read (the callee may have written b[i]); the store before it is not
// dead (the callee may read it); the call through a view is a barrier too.

module {
  func.func private @use(memref<64xf32>)
  func.func private @touch(memref<64xi32>)
  func.func private @touch_dyn(memref<?xi32>)

  func.func @after_loop(%A: memref<64x2xf32>, %out: memref<64xf32>) {
    %cst = arith.constant 0.000000e+00 : f32
    %acc = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<64xf32>
    affine.for %i = 0 to 64 {
      affine.store %cst, %acc[%i] : memref<64xf32>
      %l0 = affine.load %acc[%i] : memref<64xf32>
      %b0 = affine.load %A[%i, 0] : memref<64x2xf32>
      %a0 = arith.addf %l0, %b0 : f32
      affine.store %a0, %acc[%i] : memref<64xf32>
      %l1 = affine.load %acc[%i] : memref<64xf32>
      %b1 = affine.load %A[%i, 1] : memref<64x2xf32>
      %a1 = arith.addf %l1, %b1 : f32
      affine.store %a1, %acc[%i] : memref<64xf32>
    }
    func.call @use(%acc) : (memref<64xf32>) -> ()
    return
  }

  func.func @spans(%in: memref<64xi32>, %out: memref<64x3xi32>) {
    %b = memref.alloca() {hls.preserve, polygeist.varname = "b_spans"} : memref<64xi32>
    affine.for %i = 0 to 64 {
      %x = affine.load %b[%i] : memref<64xi32>
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %b[%i] : memref<64xi32>
      func.call @touch(%b) : (memref<64xi32>) -> ()
      %y = affine.load %b[%i] : memref<64xi32>
      %w = arith.addi %x, %y : i32
      affine.store %w, %b[%i] : memref<64xi32>
      %c = memref.cast %b : memref<64xi32> to memref<?xi32>
      func.call @touch_dyn(%c) : (memref<?xi32>) -> ()
      %z = affine.load %b[%i] : memref<64xi32>
      affine.store %x, %out[%i, 0] : memref<64x3xi32>
      affine.store %y, %out[%i, 1] : memref<64x3xi32>
      affine.store %z, %out[%i, 2] : memref<64x3xi32>
    }
    return
  }
}

// CHECK-LABEL: func.func @after_loop
// CHECK-NOT:   memref.load %alloca
// CHECK:       memref.store %{{.*}}, %alloca[%{{.*}}] {hls.forwarded_loads = 2 : i64, hls.removed_stores = 2 : i64} : memref<64xf32>
// CHECK-NOT:   memref.store %{{.*}}, %alloca
// CHECK:       call @use(%alloca)

// CHECK-LABEL: func.func @spans
// CHECK-NOT:   hls.forwarded_loads
// CHECK-NOT:   hls.removed_stores
// CHECK-NOT:   hls.merged_loads
// CHECK:       memref.load %alloca
// CHECK:       memref.store %{{.*}}, %alloca
// CHECK:       call @touch(%alloca)
// CHECK:       memref.load %alloca
// CHECK:       memref.store %{{.*}}, %alloca
// CHECK:       call @touch_dyn
// CHECK:       memref.load %alloca
// CHECK-NOT:   hls.forwarded_loads
// CHECK-NOT:   hls.removed_stores
// CHECK-NOT:   hls.merged_loads
// CHECK:       return
