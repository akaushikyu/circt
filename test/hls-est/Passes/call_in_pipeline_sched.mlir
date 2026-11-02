// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule -o - 2> %t.err | FileCheck %s
// RUN: FileCheck %s --input-file=%t.err --check-prefix=WARN --allow-empty
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --loopschedule-kept-call-latency=-1 -o - 2>&1 | FileCheck %s --check-prefix=OFF

// A call to a function defined in the module inside a loop is an operation
// of the pipelined loop (VITIS_NOTES.md N14 R2 in a pipelined loop; W3):
//   @indep  two calls of @h with scalar arguments: two instances, II 1
//           (inl_c4_rom_two: 1/2/3 calls per II-1 iteration, 1/2/3
//           instances).
//   @shared two calls of @get2 on the same array: one instance, the calls are
//           serialized (Vitis: a carried dependence between the call
//           operations), each for its whole depth: without hls.call_depth
//           the call latency (default 1) + 1 = 2, so II 4 (inl_e3: II 4,
//           get2 depth 2; W3 review D4, before it II 2).
//   @extern a call without a body in the module (a math function) still
//           leaves the loop sequential unless --loopschedule-call-latency
//           is set, as before.
// --loopschedule-kept-call-latency=-1 leaves every loop with such a call
// sequential (the behaviour before W3), with the "not pipelined" warning.

// CHECK-LABEL: func.func @indep
// CHECK:       loopschedule.pipeline II = 1 trip_count = 1024
// CHECK:         func.call @h
// CHECK:         func.call @h
// CHECK-LABEL: func.func @shared
// CHECK:       loopschedule.pipeline II = 4 trip_count = 1024
// CHECK:         func.call @get2
// CHECK:         func.call @get2
// CHECK-LABEL: func.func @occupied
// CHECK:       loopschedule.pipeline II = 8 trip_count = 128
// CHECK:         func.call @row16
// CHECK-LABEL: func.func @boundary
// CHECK:         affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:      func.call @row16
// CHECK-NEXT:    } {hls.call_boundary = "row16"}
// CHECK-LABEL: func.func @extern
// CHECK:       affine.for
// CHECK:         func.call @sinf
// WARN-NOT: func.call @h
// WARN-NOT: func.call @get2
// WARN-NOT: func.call @row16
// WARN:     warning: not pipelined (left as a sequential loop): unsupported operation {{.*}} func.call @sinf

// OFF: warning: not pipelined (left as a sequential loop): unsupported operation {{.*}} func.call @h
// OFF: warning: not pipelined (left as a sequential loop): unsupported operation {{.*}} func.call @get2

module {
  func.func private @sinf(f32) -> f32
  func.func private @h(%x: i32) -> i32 attributes {hls.inline_off} {
    %t = memref.get_global @tbl : memref<1024xi32>
    %c1023 = arith.constant 1023 : i32
    %i = arith.andi %x, %c1023 : i32
    %idx = arith.index_cast %i : i32 to index
    %v = memref.load %t[%idx] : memref<1024xi32>
    return %v : i32
  }
  memref.global "private" constant @tbl : memref<1024xi32> = dense<1>
  func.func private @get2(%a: memref<1024xi32>, %i: index) -> i32 attributes {hls.inline_off} {
    %x = affine.load %a[symbol(%i)] : memref<1024xi32>
    %y = affine.load %a[1023 - symbol(%i)] : memref<1024xi32>
    %s = arith.addi %x, %y : i32
    return %s : i32
  }
  func.func @indep(%in: memref<1024xi32>, %out: memref<1024xi32>) {
    %c10 = arith.constant 10 : i32
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      %a = func.call @h(%v) : (i32) -> i32
      %w = arith.shrsi %v, %c10 : i32
      %b = func.call @h(%w) : (i32) -> i32
      %s = arith.addi %a, %b : i32
      affine.store %s, %out[%i] : memref<1024xi32>
    }
    return
  }
  func.func @shared(%buf: memref<1024xi32>, %out: memref<1024xi32>) {
    %c7 = arith.constant 7 : index
    %c1023 = arith.constant 1023 : index
    affine.for %i = 0 to 1024 {
      %x = func.call @get2(%buf, %i) : (memref<1024xi32>, index) -> i32
      %m = arith.muli %i, %c7 : index
      %j = arith.andi %m, %c1023 : index
      %y = func.call @get2(%buf, %j) : (memref<1024xi32>, index) -> i32
      %s = arith.addi %x, %y : i32
      affine.store %s, %out[%i] : memref<1024xi32>
    }
    return
  }
  // One call per iteration that holds its instance 8 cycles (the
  // hls.call_occupancy --auto-pipeline-unroll writes; inl_f2_unroll_off: 16
  // accesses of each row per call, II 8): the next iteration's call waits.
  func.func private @row16(%a: memref<16xi32>, %o: memref<16xi32>) attributes {hls.inline_off} {
    %v = affine.load %a[0] : memref<16xi32>
    affine.store %v, %o[0] : memref<16xi32>
    return
  }
  func.func @occupied(%a: memref<16xi32>, %o: memref<16xi32>) {
    affine.for %i = 0 to 128 {
      func.call @row16(%a, %o) {hls.call_occupancy = 8 : i64} : (memref<16xi32>, memref<16xi32>) -> ()
    }
    return
  }
  // A loop marked hls.call_boundary (its callee still has loops) is left a
  // sequential affine.for, without a warning.
  func.func @boundary(%a: memref<16xi32>, %o: memref<16xi32>) {
    affine.for %i = 0 to 8 {
      func.call @row16(%a, %o) : (memref<16xi32>, memref<16xi32>) -> ()
    } {hls.call_boundary = "row16"}
    return
  }
  func.func @extern(%in: memref<1024xf32>, %out: memref<1024xf32>) {
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xf32>
      %s = func.call @sinf(%v) : (f32) -> f32
      affine.store %s, %out[%i] : memref<1024xf32>
    }
    return
  }
}
