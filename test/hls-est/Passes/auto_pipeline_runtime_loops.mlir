// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s

// Loops whose trip count is unknown at the decision (OPEN_ISSUES O72,
// VITIS_NOTES.md N53): an scf.for whose bound is loaded inside an enclosing
// loop (cgeist cannot raise it to an affine.for) and an scf.while. Vitis
// pipelines them like any other loop when every loop inside them (callee
// loops included) has a constant trip count with products <= 64:
//   @runtime_for   kernel shafix_v4 / o72_xio: `while (count >= 16)` inside
//                  `for (j < 2)` with `count = n[j]`, a 16-trip copy loop and
//                  a kept SHA transform: the while pipelined (trip
//                  `1 ~ 268435456`), the copy loop and the callee's loops
//                  unrolled (`W` registers, 0 BRAM); j not pipelined.
//   @runtime_while kernel o72_wa: a data-dependent `while` around a 16-trip
//                  loop: pipelined, the 16-trip loop unrolled.
//   @runtime_deep  kernel o72_fb: the inner loop has 128 trips (> 64): the
//                  inner loop is pipelined, the runtime loop is not.
//   @runtime_nested kernel o72_fd: two nested runtime loops: only the
//                  innermost is pipelined.
//   @runtime_off   `#pragma HLS pipeline off` on the runtime loop (kernel
//                  o72_fpo): its inner loop is pipelined instead.
//   @runtime_perfect kernel o72r_pf3 (O72 review D2): the runtime loop's
//                  body is a perfect nest over a 16-trip loop: Vitis
//                  flattens the runtime loop into the inner loop's pipeline
//                  (inner loop not unrolled), so the inner loop is tagged
//                  with hls.flattened_parents = 1 and the scf.for is not
//                  pipelined.

// CHECK-LABEL: func.func @runtime_for(
// CHECK:         affine.for
// CHECK:           scf.for
// CHECK-NOT:         affine.for
// CHECK:           } {hls.auto_unrolled = [{factor = 16 : i64{{.*}}}, {factor = 16 : i64{{.*}}}, {factor = 64 : i64{{.*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NOT:     hls.pipeline
// CHECK:         return

// CHECK-LABEL: func.func @runtime_while(
// CHECK:         scf.while
// CHECK-NOT:       affine.for
// CHECK:         } attributes {hls.auto_unrolled = [{factor = 16 : i64{{.*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}

// CHECK-LABEL: func.func @runtime_deep(
// CHECK:         scf.for
// CHECK:           affine.for %{{.*}} = 0 to 128
// CHECK:           } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK:         }{{$}}

// CHECK-LABEL: func.func @runtime_nested(
// CHECK:         scf.for
// CHECK:           scf.for
// CHECK:           } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK:         }{{$}}

// CHECK-LABEL: func.func @runtime_off(
// CHECK:         scf.for
// CHECK:           affine.for %{{.*}} = 0 to 16
// CHECK:           } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK:         } {hls.pipeline_off}

// CHECK-LABEL: func.func @runtime_perfect(
// CHECK:         scf.for
// CHECK:           affine.for %{{.*}} = 0 to 16
// CHECK:           } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:    }{{$}}

module {
  memref.global @dat : memref<16xi32> = uninitialized
  func.func private @xf() attributes {hls.inline_auto_off = {size = 139 : i64}} {
    %alloca = memref.alloca() : memref<80xi32>
    %0 = memref.get_global @dat : memref<16xi32>
    affine.for %i = 0 to 16 {
      %v = affine.load %0[%i] : memref<16xi32>
      affine.store %v, %alloca[%i] : memref<80xi32>
    }
    affine.for %i = 16 to 80 {
      %a = affine.load %alloca[%i - 3] : memref<80xi32>
      %b = affine.load %alloca[%i - 16] : memref<80xi32>
      %c = arith.xori %a, %b : i32
      affine.store %c, %alloca[%i] : memref<80xi32>
    }
    return
  }
  func.func @runtime_for(%in: memref<2x4096xi32>, %n: memref<2xi32>) {
    %c1 = arith.constant 1 : index
    %c16 = arith.constant 16 : index
    %d = memref.get_global @dat : memref<16xi32>
    affine.for %j = 0 to 2 {
      %b = affine.load %n[%j] : memref<2xi32>
      %bi = arith.index_cast %b : i32 to index
      %ub = arith.addi %bi, %c1 : index
      scf.for %p = %c16 to %ub step %c16 {
        affine.for %k = 0 to 16 {
          %v = memref.load %in[%j, %k] : memref<2x4096xi32>
          affine.store %v, %d[%k] : memref<16xi32>
        }
        func.call @xf() : () -> ()
      }
    }
    return
  }
  func.func @runtime_while(%a: memref<1024xi32>, %out: memref<64xi32>, %key: i32) {
    %c0_i32 = arith.constant 0 : i32
    %c1_i32 = arith.constant 1 : i32
    %c64_i32 = arith.constant 64 : i32
    %buf = memref.alloca() : memref<64x16xi32>
    %r = scf.while (%i = %c0_i32) : (i32) -> i32 {
      %ii = arith.index_cast %i : i32 to index
      %x = memref.load %a[%ii] : memref<1024xi32>
      %lt = arith.cmpi slt, %i, %c64_i32 : i32
      %ne = arith.cmpi ne, %x, %key : i32
      %go = arith.andi %lt, %ne : i1
      scf.condition(%go) %i : i32
    } do {
    ^bb0(%i: i32):
      %ii = arith.index_cast %i : i32 to index
      %s = affine.for %k = 0 to 16 iter_args(%acc = %c0_i32) -> (i32) {
        %v = memref.load %buf[%ii, %k] : memref<64x16xi32>
        %t = arith.addi %acc, %v : i32
        affine.yield %t : i32
      }
      memref.store %s, %out[%ii] : memref<64xi32>
      %n = arith.addi %i, %c1_i32 : i32
      scf.yield %n : i32
    }
    return
  }
  func.func @runtime_deep(%buf: memref<8x128xi32>, %out: memref<64xi32>, %n: memref<2xi32>) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c0_i32 = arith.constant 0 : i32
    affine.for %j = 0 to 2 {
      %b = affine.load %n[%j] : memref<2xi32>
      %ub = arith.index_cast %b : i32 to index
      scf.for %i = %c0 to %ub step %c1 {
        %s = affine.for %k = 0 to 128 iter_args(%acc = %c0_i32) -> (i32) {
          %v = memref.load %buf[%i, %k] : memref<8x128xi32>
          %t = arith.addi %acc, %v : i32
          affine.yield %t : i32
        }
        memref.store %s, %out[%i] : memref<64xi32>
      }
    }
    return
  }
  func.func @runtime_nested(%buf: memref<64x16xi32>, %out: memref<64xi32>, %n: memref<2xi32>, %e: memref<64xi32>) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    affine.for %j = 0 to 2 {
      %b = affine.load %n[%j] : memref<2xi32>
      %ub = arith.index_cast %b : i32 to index
      scf.for %i = %c0 to %ub step %c1 {
        %eb = memref.load %e[%i] : memref<64xi32>
        %eub = arith.index_cast %eb : i32 to index
        scf.for %k = %c0 to %eub step %c1 {
          %v = memref.load %buf[%i, %k] : memref<64x16xi32>
          memref.store %v, %out[%i] : memref<64xi32>
        }
      }
    }
    return
  }
  func.func @runtime_off(%buf: memref<64x16xi32>, %out: memref<64xi32>, %n: memref<2xi32>) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c0_i32 = arith.constant 0 : i32
    affine.for %j = 0 to 2 {
      %b = affine.load %n[%j] : memref<2xi32>
      %ub = arith.index_cast %b : i32 to index
      scf.for %i = %c0 to %ub step %c1 {
        %s = affine.for %k = 0 to 16 iter_args(%acc = %c0_i32) -> (i32) {
          %v = memref.load %buf[%i, %k] : memref<64x16xi32>
          %t = arith.addi %acc, %v : i32
          affine.yield %t : i32
        }
        memref.store %s, %out[%i] : memref<64xi32>
      } {hls.pipeline_off}
    }
    return
  }
  func.func @runtime_perfect(%buf: memref<64x16xi32>, %res: memref<64x16xi32>, %n: memref<2xi32>) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c63 = arith.constant 63 : index
    %c3_i32 = arith.constant 3 : i32
    affine.for %j = 0 to 2 {
      %b = affine.load %n[%j] : memref<2xi32>
      %ub = arith.index_cast %b : i32 to index
      scf.for %i = %c0 to %ub step %c1 {
        %r = arith.andi %i, %c63 : index
        affine.for %k = 0 to 16 {
          %v = memref.load %buf[%r, %k] : memref<64x16xi32>
          %w = arith.muli %v, %c3_i32 : i32
          memref.store %w, %res[%r, %k] : memref<64x16xi32>
        }
      }
    }
    return
  }
}
