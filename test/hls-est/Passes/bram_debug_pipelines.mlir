// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug --bram-debug-json=%t.json 2> %t.debug.err > %t.debug.out
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis > %t.plain.out
// RUN: diff %t.plain.out %t.debug.out
// RUN: FileCheck %s --input-file=%t.json
// RUN: FileCheck %s --check-prefix=TEXT --input-file=%t.debug.err

// --bram-debug reports the pipeline / unroll / flatten decisions of
// --auto-pipeline-unroll per pipelined loop ("pipelines" in the JSON, a
// "--- pipelines" section in the text): which loops were flattened into it
// (hls.flattened_parents) and which were unrolled for it (hls.auto_unrolled),
// so a decision mismatch with Vitis' 214-376 / 214-186 / 203-541 lines can be
// read off the debug output instead of inferred from per-scope II and read
// counts. The `diff` RUN line proves the stdout report is unchanged.
//
// @kernel: the first reduction nest has a 65-trip inner loop (> 64): the
// inner loop is pipelined and the imperfect parent is flattened onto it
// (flattened_parents = 1). The second has a 16-trip inner loop: the parent is
// pipelined and the inner loop unrolled x16.

module {
  func.func @kernel(%a: memref<8x65xi32>, %b: memref<65xi32>, %out: memref<8xi32>, %out2: memref<8xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x65xi32> loc("k.cpp":3:5)
    %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<65xi32> loc("k.cpp":4:5)
    affine.for %i = 0 to 8 {
      affine.for %j = 0 to 65 {
        %0 = affine.load %a[%i, %j] : memref<8x65xi32>
        affine.store %0, %la[%i, %j] : memref<8x65xi32>
      } loc("k.cpp":7:5)
    } loc("k.cpp":6:3)
    affine.for %j = 0 to 65 {
      %0 = affine.load %b[%j] : memref<65xi32>
      affine.store %0, %lb[%j] : memref<65xi32>
    } loc("k.cpp":9:3)
    affine.for %i = 0 to 8 {
      %0 = affine.for %j = 0 to 65 iter_args(%s = %c0_i32) -> (i32) {
        %1 = affine.load %la[%i, %j] : memref<8x65xi32>
        %2 = affine.load %lb[%j] : memref<65xi32>
        %3 = arith.muli %1, %2 : i32
        %4 = arith.addi %s, %3 : i32
        affine.yield %4 : i32
      } loc("k.cpp":13:5)
      affine.store %0, %out[%i] : memref<8xi32>
    } loc("k.cpp":12:3)
    affine.for %i = 0 to 8 {
      %0 = affine.for %j = 0 to 16 iter_args(%s = %c0_i32) -> (i32) {
        %1 = affine.load %la[%i, %j] : memref<8x65xi32>
        %2 = affine.load %lb[%j] : memref<65xi32>
        %3 = arith.muli %1, %2 : i32
        %4 = arith.addi %s, %3 : i32
        affine.yield %4 : i32
      } loc("k.cpp":20:5)
      affine.store %0, %out2[%i] : memref<8xi32>
    } loc("k.cpp":19:3)
    return
  }
}

// llvm::json prints object keys sorted, one per line.
// CHECK:      "pipelines": [
// CHECK:        "flattened_parents": 1,
// CHECK-NEXT:   "func": "kernel",
// CHECK-NEXT:   "ii": {{[0-9]+}},
// CHECK-NEXT:   "scheduler": "simplex",
// CHECK-NEXT:   "scope_loc": "k.cpp:13:5",
// CHECK-NEXT:   "source": "auto",
// CHECK-NEXT:   "trip_count": 65,
// CHECK-NEXT:   "unroll_partial": null,
// CHECK-NEXT:   "unrolled": []
// CHECK:        "flattened_parents": 0,
// CHECK-NEXT:   "func": "kernel",
// CHECK-NEXT:   "ii": {{[0-9]+}},
// CHECK-NEXT:   "scheduler": "simplex",
// CHECK-NEXT:   "scope_loc": "k.cpp:19:3",
// CHECK-NEXT:   "source": "auto",
// CHECK-NEXT:   "trip_count": 8,
// CHECK-NEXT:   "unroll_partial": null,
// CHECK-NEXT:   "unrolled": [
// CHECK-NEXT:     {
// CHECK-NEXT:       "factor": 16,
// CHECK-NEXT:       "loc": "k.cpp:20:5"
// CHECK-NEXT:     }
// CHECK-NEXT:   ]

// TEXT:      --- pipelines (decisions of --auto-pipeline-unroll) ---
// TEXT:      pipeline @ k.cpp:13:5 in @kernel: ii={{[0-9]+}} trip=65 source=auto flattened_parents=1
// TEXT:      pipeline @ k.cpp:19:3 in @kernel: ii={{[0-9]+}} trip=8 source=auto flattened_parents=0
// TEXT-NEXT:   unrolled x16 @ k.cpp:20:5
// TEXT:      --- summary (sorted by BRAM) ---
