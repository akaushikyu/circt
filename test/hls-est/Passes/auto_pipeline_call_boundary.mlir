// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s

// A kept call is a boundary of the automatic pipeline / flatten decision
// (VITIS_NOTES.md N14 R7; kernels inl_f1_flat_off, inl_f2_unroll_off):
//   @flat_off  a caller loop (8 trips) around @row, whose own loop has 128
//              trips: 8 x 128 > 64, so the caller is not pipelined and
//              nothing is flattened across the call; @row's loop is
//              pipelined in @row (Vitis: `row | VITIS_LOOP` pipelined, the
//              caller loop `pipe no`; inlined, the nest is flattened into
//              one 1024-trip pipeline).
//   @unroll_off a caller loop (128 trips) around @row16, whose loop has 16
//              trips: the caller is pipelined and the callee's loop is
//              unrolled inside the callee (Vitis: `[HLS 214-186] ... in
//              function 'row16' completely with a factor of 16`, II 8; the
//              same for 64 trips under an 8-trip caller, kernels
//              w3h_cb_flat64 and w3h_cb_nest64 with a 4 x 4 x 4 nest). The
//              call holds its instance for 16 accesses of each row, two per
//              cycle: hls.call_occupancy 8, the II bound in
//              --convert-affine-to-loopschedule.
//   A loop that is not pipelined and calls a callee that keeps loops gets
//   hls.call_boundary (--convert-affine-to-loopschedule leaves it a
//   sequential affine.for).

// CHECK-LABEL: func.func private @row(
// CHECK:         affine.for %{{.*}} = 0 to 128 {
// CHECK:         } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-LABEL: func.func private @row16(
// CHECK-NOT:     affine.for
// CHECK:         return
// CHECK-LABEL: func.func @flat_off
// CHECK:         affine.for %{{.*}} = 0 to 8 {
// CHECK:           func.call @row
// CHECK-NEXT:    } {hls.call_boundary = "row"}
// CHECK-NOT:     hls.pipeline
// CHECK-NOT:     hls.flattened_parents
// CHECK:         return
// CHECK-LABEL: func.func @unroll_off
// CHECK:         affine.for %{{.*}} = 0 to 128 {
// CHECK:           func.call @row16(%{{.*}}, %{{.*}}) {hls.call_occupancy = 8 : i64}
// CHECK:         } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
//   @nest_caller a caller loop (8 trips) around @nest, whose nest has
//              8 x 8 x 4 = 256 trips: the caller stays sequential and
//              @nest pipelines its flattened i-j loop with d unrolled
//              (Vitis, corpus attn_breakdown_op1 `matmul_small_1`:
//              `VITIS_LOOP_65_1_VITIS_LOOP_66_2` pipelined, 64 trips, the
//              caller's `VITIS_LOOP_232_1` not pipelined; kernel
//              w3h_cb_nest256).
// CHECK-LABEL: func.func private @nest(
// CHECK:         affine.for %{{.*}} = 0 to 8 {
// CHECK:           affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:         affine.for
// CHECK:           } {hls.auto_unrolled = [{factor = 4 : i64, loc = #loc{{[0-9]*}}}], hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-LABEL: func.func @nest_caller
// CHECK:         affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:      func.call @nest
// CHECK-NEXT:    } {hls.call_boundary = "nest"}
// CHECK-NEXT:    return
// CHECK-LABEL: func.func @acc4_caller
// CHECK:         affine.for %{{.*}} = 0 to 64 {
// CHECK-NEXT:      func.call @acc4(%{{.*}}, %{{.*}}) {hls.call_occupancy = 2 : i64}
// CHECK-NEXT:    } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}

module {
  func.func private @row(%a: memref<128xi32>, %o: memref<128xi32>) attributes {hls.inline_off} {
    %c3 = arith.constant 3 : i32
    affine.for %j = 0 to 128 {
      %v = affine.load %a[%j] : memref<128xi32>
      %w = arith.muli %v, %c3 : i32
      affine.store %w, %o[%j] : memref<128xi32>
    }
    return
  }
  func.func private @row16(%a: memref<16xi32>, %o: memref<16xi32>) attributes {hls.inline_off} {
    %c3 = arith.constant 3 : i32
    affine.for %j = 0 to 16 {
      %v = affine.load %a[%j] : memref<16xi32>
      %w = arith.muli %v, %c3 : i32
      affine.store %w, %o[%j] : memref<16xi32>
    }
    return
  }
  func.func @flat_off(%a: memref<8x128xi32>, %o: memref<8x128xi32>) {
    affine.for %i = 0 to 8 {
      %ra = memref.subview %a[%i, 0] [1, 128] [1, 1] : memref<8x128xi32> to memref<128xi32, strided<[1], offset: ?>>
      %ca = memref.cast %ra : memref<128xi32, strided<[1], offset: ?>> to memref<128xi32>
      %ro = memref.subview %o[%i, 0] [1, 128] [1, 1] : memref<8x128xi32> to memref<128xi32, strided<[1], offset: ?>>
      %co = memref.cast %ro : memref<128xi32, strided<[1], offset: ?>> to memref<128xi32>
      func.call @row(%ca, %co) : (memref<128xi32>, memref<128xi32>) -> ()
    }
    return
  }
  func.func @unroll_off(%a: memref<128x16xi32>, %o: memref<128x16xi32>) {
    affine.for %i = 0 to 128 {
      %ra = memref.subview %a[%i, 0] [1, 16] [1, 1] : memref<128x16xi32> to memref<16xi32, strided<[1], offset: ?>>
      %ca = memref.cast %ra : memref<16xi32, strided<[1], offset: ?>> to memref<16xi32>
      %ro = memref.subview %o[%i, 0] [1, 16] [1, 1] : memref<128x16xi32> to memref<16xi32, strided<[1], offset: ?>>
      %co = memref.cast %ro : memref<16xi32, strided<[1], offset: ?>> to memref<16xi32>
      func.call @row16(%ca, %co) : (memref<16xi32>, memref<16xi32>) -> ()
    }
    return
  }
  // @nest is defined before its caller, as in C, so a decision in module
  // order would pipeline @nest's flattened i-j loop and unroll d first; the
  // caller's test would then see one 64-trip loop and pass. Callers are
  // decided first, against the callee's 8 x 8 x 4 = 256 trips.
  func.func private @nest(%q: memref<8x32xi32>, %k: memref<8x32xi32>, %s: memref<8x8xi32>, %h: index) attributes {hls.inline_off} {
    %c0 = arith.constant 0 : i32
    affine.for %i = 0 to 8 {
      affine.for %j = 0 to 8 {
        affine.store %c0, %s[%i, %j] : memref<8x8xi32>
        affine.for %d = 0 to 4 {
          %a = affine.load %q[%i, %d + symbol(%h) * 4] : memref<8x32xi32>
          %b = affine.load %k[%j, %d + symbol(%h) * 4] : memref<8x32xi32>
          %m = arith.muli %a, %b : i32
          %o = affine.load %s[%i, %j] : memref<8x8xi32>
          %n = arith.addi %o, %m : i32
          affine.store %n, %s[%i, %j] : memref<8x8xi32>
        }
      }
    }
    return
  }
  func.func @nest_caller(%q: memref<8x32xi32>, %k: memref<8x32xi32>, %s: memref<8x8xi32>) {
    affine.for %g = 0 to 8 {
      func.call @nest(%q, %k, %s, %g) : (memref<8x32xi32>, memref<8x32xi32>, memref<8x8xi32>, index) -> ()
    }
    return
  }
  // Occupancy counts distinct addresses, after forwarding: @acc4 reads a[0]
  // twice (one read) and a[1..3] once, and reads back s[0] only after
  // writing it (forwarded): 4 reads of a, 1 write of s -> 2 cycles.
  func.func private @acc4(%a: memref<4xi32>, %s: memref<1xi32>) attributes {hls.inline_off} {
    %c0 = arith.constant 0 : i32
    affine.store %c0, %s[0] : memref<1xi32>
    %a0 = affine.load %a[0] : memref<4xi32>
    %a0b = affine.load %a[0] : memref<4xi32>
    %a1 = affine.load %a[1] : memref<4xi32>
    %a2 = affine.load %a[2] : memref<4xi32>
    %a3 = affine.load %a[3] : memref<4xi32>
    %p = affine.load %s[0] : memref<1xi32>
    %x0 = arith.addi %p, %a0 : i32
    %x1 = arith.addi %x0, %a0b : i32
    %x2 = arith.addi %x1, %a1 : i32
    %x3 = arith.addi %x2, %a2 : i32
    %x4 = arith.addi %x3, %a3 : i32
    affine.store %x4, %s[0] : memref<1xi32>
    return
  }
  func.func @acc4_caller(%a: memref<4xi32>, %s: memref<1xi32>) {
    affine.for %g = 0 to 64 {
      func.call @acc4(%a, %s) : (memref<4xi32>, memref<1xi32>) -> ()
    }
    return
  }
}
