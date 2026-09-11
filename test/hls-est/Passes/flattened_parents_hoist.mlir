// RUN: hls-est %s --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=SCHED
// RUN: hls-est %s --infer-vitis-split-array=td=auto -o - | FileCheck %s --check-prefix=SPLIT
//
// `hls.flattened_parents` says Vitis folds the enclosing loops into the
// tagged loop's pipeline. Their induction variables are therefore loop-variant
// for that pipeline:
//  - the invariant-load hoist of --convert-affine-to-loopschedule must keep
//    `lb[i]` inside the pipeline of j (it is re-read every iteration of the
//    flattened 8x65 loop);
//  - --infer-vitis-split-array must count it as a read of lb per iteration.
// @untagged is the same nest without the attribute: the load is hoisted out
// of the pipeline and does not count.

// The parent's code (`lo2[i] = 7`) is sunk into the pipeline under the
// first-iteration guard (VITIS_NOTES N65), so the nest is perfect and is
// coalesced into one 520-trip pipeline.
// SCHED-LABEL: func.func @tagged
// SCHED:       %[[LO2:.*]] = memref.alloca() {{.*}}"lo2"
// SCHED:       %[[LB:.*]] = memref.alloca() {{.*}}"lb"
// SCHED-NOT:   affine.for
// SCHED-NOT:   memref.load %[[LB]]
// SCHED:       loopschedule.pipeline II = {{.*}} trip_count = 520
// SCHED:         memref.store %{{.*}}, %[[LO2]]
// SCHED:         memref.load %[[LB]]
// SCHED:       return

// SPLIT-LABEL: func.func @tagged
// SPLIT:       memref.alloca() {hls.port_pressure = [{ii = 1 : i32, reads = 1 : i32, writes = 0 : i32}], hls.preserve, polygeist.varname = "lb"}
func.func @tagged(%a: memref<8x65xi32>, %b: memref<8xi32>, %out: memref<8x65xi32>) {
  %c7_i32 = arith.constant 7 : i32
  %lo2 = memref.alloca() {hls.preserve, polygeist.varname = "lo2"} : memref<8xi32>
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x65xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x65xi32>
  affine.for %i = 0 to 8 {
    affine.store %c7_i32, %lo2[%i] : memref<8xi32>
    affine.for %j = 0 to 65 {
      %0 = affine.load %la[%i, %j] : memref<8x65xi32>
      %1 = affine.load %lb[%i] : memref<8xi32>
      %2 = arith.muli %0, %1 : i32
      affine.store %2, %lo[%i, %j] : memref<8x65xi32>
    } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
  }
  return
}

// SCHED-LABEL: func.func @untagged
// SCHED:       %[[LB2:.*]] = memref.alloca() {{.*}}"lb"
// SCHED:       affine.for
// SCHED:         memref.load %[[LB2]]
// SCHED:         loopschedule.pipeline
// SCHED-NOT:       memref.load %[[LB2]]
// SCHED:       return

// SPLIT-LABEL: func.func @untagged
// SPLIT:       memref.alloca() {hls.preserve, polygeist.varname = "lb"}
func.func @untagged(%a: memref<8x65xi32>, %b: memref<8xi32>, %out: memref<8x65xi32>) {
  %c7_i32 = arith.constant 7 : i32
  %lo2 = memref.alloca() {hls.preserve, polygeist.varname = "lo2"} : memref<8xi32>
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x65xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x65xi32>
  affine.for %i = 0 to 8 {
    affine.store %c7_i32, %lo2[%i] : memref<8xi32>
    affine.for %j = 0 to 65 {
      %0 = affine.load %la[%i, %j] : memref<8x65xi32>
      %1 = affine.load %lb[%i] : memref<8xi32>
      %2 = arith.muli %0, %1 : i32
      affine.store %2, %lo[%i, %j] : memref<8x65xi32>
    } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
  }
  return
}
