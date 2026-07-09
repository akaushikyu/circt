// RUN: hls-est %s --dead-memory-elimination | FileCheck %s
// RUN: hls-est %s --dead-memory-elimination | FileCheck %s --check-prefix=NOKEEP
// RUN: hls-est %s --symbol-privatize=exclude=inl_top --symbol-dce --inline --symbol-dce --dead-memory-elimination | FileCheck %s --check-prefix=INL
// RUN: hls-est %s --symbol-privatize=exclude=inl_top --symbol-dce --inline --symbol-dce --dead-memory-elimination --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=INLBRAM

// --dead-memory-elimination on function bodies with several blocks (an
// inlined callee with an early return, or cf branches): the function's
// control flow is kept, so a value that decides a cf.cond_br, or reaches a
// later block through a block argument, is live, and so is the array it was
// loaded from. A dead array in the same function is still removed. (Before
// the fix: `error: null operand found`, and keep_* treated as dead.)

// CHECK: hls.dead_memrefs = [{{.*}}, name = "dead_c"{{.*}}, name = "dead_b"
// NOKEEP-NOT: , name = "keep_

// CHECK-LABEL: func.func @cfg_cond
// CHECK-NOT: dead_c
// CHECK: polygeist.varname = "keep_c"
// CHECK: arith.cmpi sgt
// CHECK: cf.cond_br
// CHECK: affine.store %{{.*}}, %arg1[0]
// CHECK: return
func.func @cfg_cond(%in: memref<64xi32>, %out: memref<64xi32>) {
  %c0 = arith.constant 0 : i32
  %c1 = arith.constant 1 : i32
  %b = memref.alloca() {polygeist.varname = "keep_c"} : memref<64xi32>
  %d = memref.alloca() {polygeist.varname = "dead_c"} : memref<64xi32>
  affine.for %i = 0 to 64 {
    %v = affine.load %in[%i] : memref<64xi32>
    affine.store %v, %b[%i] : memref<64xi32>
    affine.store %v, %d[%i] : memref<64xi32>
  }
  %v = affine.load %b[5] : memref<64xi32>
  %w = affine.load %d[5] : memref<64xi32>
  %c = arith.cmpi sgt, %v, %c0 : i32
  cf.cond_br %c, ^bb1, ^bb2
^bb1:
  affine.store %c1, %out[0] : memref<64xi32>
  cf.br ^bb2
^bb2:
  return
}

// CHECK-LABEL: func.func @cfg_blockarg
// CHECK-NOT: dead_b
// CHECK: polygeist.varname = "keep_b"
// CHECK: cf.cond_br %arg2, ^bb1(%{{.*}} : i32), ^bb1(%{{.*}} : i32)
// CHECK: ^bb1(%[[X:.*]]: i32):
// CHECK: affine.store %[[X]], %arg1[0]
func.func @cfg_blockarg(%in: memref<64xi32>, %out: memref<64xi32>, %sel: i1) {
  %c0 = arith.constant 0 : i32
  %b = memref.alloca() {polygeist.varname = "keep_b"} : memref<64xi32>
  %d = memref.alloca() {polygeist.varname = "dead_b"} : memref<64xi32>
  affine.for %i = 0 to 64 {
    %v = affine.load %in[%i] : memref<64xi32>
    affine.store %v, %b[%i] : memref<64xi32>
    affine.store %v, %d[%i] : memref<64xi32>
  }
  %v = affine.load %b[5] : memref<64xi32>
  %w = affine.load %d[5] : memref<64xi32>
  cf.cond_br %sel, ^bb1(%v : i32), ^bb1(%c0 : i32)
^bb1(%x: i32):
  affine.store %x, %out[0] : memref<64xi32>
  return
}

// The realistic path: a callee with an early return, inlined by --inline
// into the top as function-level cf.cond_br / cf.br; the array value decides
// which output element is written.
// INL-NOT: , name = "inl_buf"
// INL-LABEL: func.func @inl_top
// INL: polygeist.varname = "inl_buf"
// INL: cf.cond_br
// INLBRAM: Total BRAM: 1
func.func private @put(%o: memref<64xi32>, %x: i32) {
  %c0 = arith.constant 0 : i32
  %neg = arith.cmpi slt, %x, %c0 : i32
  cf.cond_br %neg, ^bb1, ^bb2
^bb1:
  affine.store %c0, %o[0] : memref<64xi32>
  return
^bb2:
  %c1 = arith.constant 1 : i32
  affine.store %c1, %o[1] : memref<64xi32>
  return
}
func.func @inl_top(%in: memref<64xi32>, %out: memref<64xi32>) {
  %b = memref.alloca() {polygeist.varname = "inl_buf"} : memref<64xi32>
  affine.for %i = 0 to 64 {
    %v = affine.load %in[%i] : memref<64xi32>
    affine.store %v, %b[%i] : memref<64xi32>
  }
  %v = affine.load %b[7] : memref<64xi32>
  func.call @put(%out, %v) : (memref<64xi32>, i32) -> ()
  return
}
