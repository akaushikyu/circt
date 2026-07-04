// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// User pragmas take precedence over the automatic decision, as in Vitis:
//  - a user `hls.pipeline` loop is pipelined whatever the threshold and
//    everything inside it is completely unrolled ("complete unroll implied by
//    the pipeline pragma"); the attribute is kept as cgeist wrote it;
//  - a loop above a user-pipelined loop is not auto-pipelined (that would
//    unroll the user's pipeline); a perfect parent is flattened onto it;
//  - `hls.pipeline_off` is never auto-pipelined;
//  - `hls.unroll` (complete, or by factor) is applied BEFORE the decision; a
//    loop that keeps a partial user unroll (factor below its trip count, 1
//    included) is never unrolled completely for an enclosing automatic
//    pipeline, so no loop around it is auto-pipelined and the loop itself is
//    (Vitis ground truth: forgebench/diff_dims_p1 - the k/4 loop pipelined in
//    all 96 user-made copies, i and j not; spector_hls/fir - the `factor=1`
//    loops pipelined, the 67-trip parent not).

// CHECK-LABEL: func.func @user_outer
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
func.func @user_outer(%a: memref<8x128xi32>, %b: memref<128xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<128xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x128xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 128 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x128xi32>
      %2 = affine.load %lb[%j] : memref<128xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    }
    affine.store %0, %lo[%i] : memref<8xi32>
  } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
  return
}

// CHECK-LABEL: func.func @user_inner
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 16 iter_args
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
// CHECK-NEXT:    affine.store
// CHECK-NEXT:  {{^ *}$}}
func.func @user_inner(%a: memref<8x16xi32>, %b: memref<16xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<16xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 16 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x16xi32>
      %2 = affine.load %lb[%j] : memref<16xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  return
}

// CHECK-LABEL: func.func @pipeline_off
// CHECK:       affine.for %{{.*}} = 0 to 64 {
// CHECK:       } {hls.pipeline_off}
// CHECK-NOT:   hls.pipeline =
func.func @pipeline_off(%a: memref<64xi32>, %out: memref<64xi32>) {
  %c2_i32 = arith.constant 2 : i32
  affine.for %i = 0 to 64 {
    %0 = affine.load %a[%i] : memref<64xi32>
    %1 = arith.muli %0, %c2_i32 : i32
    affine.store %1, %out[%i] : memref<64xi32>
  } {hls.pipeline_off}
  return
}

// 256 trips unrolled by the user factor 4: the loop keeps a partial unroll
// (64 trips, 4 bodies), is pipelined itself and the parent is flattened onto
// it; the consumed pragma becomes `hls.unroll_partial = 4`.
// CHECK-LABEL: func.func @user_unroll_factor
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 256 step 4 iter_args
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.unroll_partial = 4 : i64}
// CHECK-NEXT:    affine.store
// CHECK-NEXT:  {{^ *}$}}
func.func @user_unroll_factor(%a: memref<8x256xi32>, %b: memref<256xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<256xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x256xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 256 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x256xi32>
      %2 = affine.load %lb[%j] : memref<256xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    } {hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  return
}

// The same nest without the pragma: 256 > 64 -> j pipelined, i flattened.
// CHECK-LABEL: func.func @no_user_unroll
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 256 iter_args
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @no_user_unroll(%a: memref<8x256xi32>, %b: memref<256xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<256xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x256xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 256 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x256xi32>
      %2 = affine.load %lb[%j] : memref<256xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    }
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  return
}

// A complete user unroll (factor 0) of a 128-trip loop (> threshold).
// CHECK-LABEL: func.func @user_unroll_full
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @user_unroll_full(%a: memref<8x128xi32>, %b: memref<128xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<128xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x128xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 128 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x128xi32>
      %2 = affine.load %lb[%j] : memref<128xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  return
}
