// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
//
// VITIS_NOTES.md N15: a loop whose counter is narrower than its runtime bound
// (`for (uint8_t i = 0; i < n; i++)`, int n; cgeist raises it by assuming
// that it terminates and marks it `hls.uncounted`) is not collapsed with its
// perfect inner nest before the pipeline decision. Vitis pipelines it and
// unrolls a <= 64-trip inner loop into it (nc_q_u8, nc_r_u8: `buf` replicated
// for 16 reads per iteration), where the same nest with an `int` counter has
// its inner loop pipelined and the outer loop flattened into it (nc_q_int,
// nc_r_int). Everything else about the loop is the `int` behaviour.

// The `int` counter: one collapsed loop, the inner loop pipelined, the outer
// one flattened into it.
// CHECK-LABEL: func.func @int_counter
// CHECK:       affine.for %{{.*}} = 0 to %{{.*}} {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 16 {
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:  {{^ *}$}}
func.func @int_counter(%n: index, %out: memref<4096xi32>) {
  %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<256x16xi32>
  affine.for %i = 0 to %n {
    affine.for %j = 0 to 16 {
      %0 = affine.load %buf[%i, %j] : memref<256x16xi32>
      %1 = affine.load %buf[%i, -%j + 15] : memref<256x16xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %out[%i * 16 + %j] : memref<4096xi32>
    }
  }
  return
}

// The narrow counter: the marked loop is pipelined, the inner loop unrolled.
// CHECK-LABEL: func.func @uncounted
// CHECK:       affine.for %{{.*}} = 0 to %{{.*}} {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.uncounted}
func.func @uncounted(%n: index, %out: memref<4096xi32>) {
  %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<256x16xi32>
  affine.for %i = 0 to %n {
    affine.for %j = 0 to 16 {
      %0 = affine.load %buf[%i, %j] : memref<256x16xi32>
      %1 = affine.load %buf[%i, -%j + 15] : memref<256x16xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %out[%i * 16 + %j] : memref<4096xi32>
    }
  } {hls.uncounted}
  return
}

// With an inner loop of more than 64 trips the inner loop is pipelined and
// the uncounted loop flattened into it (step 3), as the `int` nest is through
// the collapse (nc_f_u8 = nc_f_int: one flattened loop, trip `?`).
// CHECK-LABEL: func.func @uncounted_inner128
// CHECK:       affine.for %{{.*}} = 0 to %{{.*}} {
// CHECK-NEXT:    affine.for %{{.*}} = 0 to 128 {
// CHECK:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:  } {hls.uncounted}
func.func @uncounted_inner128(%n: index, %out: memref<8192xi32>) {
  %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64x128xi32>
  affine.for %i = 0 to %n {
    affine.for %j = 0 to 128 {
      %0 = affine.load %buf[%i, %j] : memref<64x128xi32>
      affine.store %0, %out[%i * 128 + %j] : memref<8192xi32>
    }
  } {hls.uncounted}
  return
}

// An uncounted loop whose inner loop is not a perfect child (a store in its
// own body) is not flattened into it: a loop around a pipelined loop is
// flattened only through the collapse or with constant bounds.
// CHECK-LABEL: func.func @uncounted_imperfect
// CHECK:       affine.for %{{.*}} = 0 to %{{.*}} {
// CHECK:         affine.for %{{.*}} = 0 to 128 {
// CHECK:         } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// CHECK-NEXT:  } {hls.uncounted}
func.func @uncounted_imperfect(%n: index, %out: memref<8192xi32>, %cnt: memref<64xi32>) {
  %c1 = arith.constant 1 : i32
  %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64x128xi32>
  affine.for %i = 0 to %n {
    affine.store %c1, %cnt[%i] : memref<64xi32>
    affine.for %j = 0 to 128 {
      %0 = affine.load %buf[%i, %j] : memref<64x128xi32>
      affine.store %0, %out[%i * 128 + %j] : memref<8192xi32>
    }
  } {hls.uncounted}
  return
}

// A single uncounted loop is pipelined as any loop without children.
// CHECK-LABEL: func.func @uncounted_single
// CHECK:       affine.for %{{.*}} = 0 to %{{.*}} {
// CHECK:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.uncounted}
func.func @uncounted_single(%n: index, %out: memref<256xi32>) {
  %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<256xi32>
  affine.for %i = 0 to %n {
    %0 = affine.load %buf[%i] : memref<256xi32>
    affine.store %0, %out[%i] : memref<256xi32>
  } {hls.uncounted}
  return
}
