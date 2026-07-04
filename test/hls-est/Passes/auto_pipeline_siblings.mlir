// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// VITIS_NOTES.md N3 / pipeline_unroll.md (pu_sib_m8_n16_n65, pu_sib_m8_n16_n16):
// feasibility is all-or-nothing per parent. With sibling inner loops of 16
// and 65 trips the parent cannot be pipelined (65 > 64), so BOTH siblings are
// pipelined individually - the 16-trip one is not unrolled - and the parent
// is neither pipelined nor flattened (two child loops). With 16 and 16 both
// are unrolled and the parent is pipelined.

// CHECK-LABEL: func.func @sib16_65
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 16 iter_args
// CHECK:         } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 65 iter_args
// CHECK:         } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:    arith.subi
// CHECK-NEXT:    affine.store
// CHECK-NEXT:  {{^ *}$}}
func.func @sib16_65(%a: memref<8x65xi32>, %b: memref<65xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<65xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x65xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 16 iter_args(%s = %c0_i32) -> (i32) {
      %3 = affine.load %la[%i, %j] : memref<8x65xi32>
      %4 = affine.load %lb[%j] : memref<65xi32>
      %5 = arith.muli %3, %4 : i32
      %6 = arith.addi %s, %5 : i32
      affine.yield %6 : i32
    }
    %1 = affine.for %j = 0 to 65 iter_args(%t = %c0_i32) -> (i32) {
      %3 = affine.load %la[%i, %j] : memref<8x65xi32>
      %4 = affine.load %lb[%j] : memref<65xi32>
      %5 = arith.xori %3, %4 : i32
      %6 = arith.addi %t, %5 : i32
      affine.yield %6 : i32
    }
    %2 = arith.subi %0, %1 : i32
    affine.store %2, %lo[%i] : memref<8xi32>
  }
  return
}

// CHECK-LABEL: func.func @sib16_16
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @sib16_16(%a: memref<8x16xi32>, %b: memref<16xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<16xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 16 iter_args(%s = %c0_i32) -> (i32) {
      %3 = affine.load %la[%i, %j] : memref<8x16xi32>
      %4 = affine.load %lb[%j] : memref<16xi32>
      %5 = arith.muli %3, %4 : i32
      %6 = arith.addi %s, %5 : i32
      affine.yield %6 : i32
    }
    %1 = affine.for %j = 0 to 16 iter_args(%t = %c0_i32) -> (i32) {
      %3 = affine.load %la[%i, %j] : memref<8x16xi32>
      %4 = affine.load %lb[%j] : memref<16xi32>
      %5 = arith.xori %3, %4 : i32
      %6 = arith.addi %t, %5 : i32
      affine.yield %6 : i32
    }
    %2 = arith.subi %0, %1 : i32
    affine.store %2, %lo[%i] : memref<8xi32>
  }
  return
}

// A dynamic trip count anywhere inside blocks the parent; the dynamic loop
// itself is pipelined (Vitis: "trip ?", pipe yes) and the parent is not
// flattened onto it ("[HLS 200-960] Cannot flatten").
// CHECK-LABEL: func.func @dynamic_inner
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to %{{.*}} iter_args
// CHECK:         } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:    affine.store
// CHECK-NEXT:  {{^ *}$}}
func.func @dynamic_inner(%a: memref<8x64xi32>, %b: memref<64xi32>, %out: memref<8xi32>, %n: index) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<64xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x64xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to %n iter_args(%s = %c0_i32) -> (i32) {
      %3 = affine.load %la[%i, %j] : memref<8x64xi32>
      %4 = affine.load %lb[%j] : memref<64xi32>
      %5 = arith.muli %3, %4 : i32
      %6 = arith.addi %s, %5 : i32
      affine.yield %6 : i32
    }
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  return
}
