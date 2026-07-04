// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll=pipeline-loops=0 | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll=pipeline-loops=16 | FileCheck %s --check-prefix=PL16
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll=pipeline-loops=15 | FileCheck %s --check-prefix=PL15
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s --check-prefix=PL64
//
// VITIS_NOTES.md N3 / pipeline_unroll.md R1: the threshold is
// syn.compile.pipeline_loops (default 64), compared with the trip count
// inclusively (pu_cfg_pl16_red_m8_n16: 16 <= 16 unrolled;
// pu_cfg_pl15_red3b_l4_m4_n4: 16 > 15 pipelined and flattened;
// pu_cfg_pl0_red_m8_n16: nothing pipelined, unrolled or flattened).

// OFF-LABEL: func.func @reduce16
// OFF:       affine.for %{{.*}} = 0 to 8 {
// OFF-NEXT:    affine.for %{{.*}} = 0 to 16 iter_args
// OFF-NOT:   hls.pipeline
// OFF-NOT:   hls.flattened_parents

// PL16-LABEL: func.func @reduce16
// PL16:       affine.for %{{.*}} = 0 to 8 {
// PL16-NOT:     affine.for
// PL16:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}

// PL15-LABEL: func.func @reduce16
// PL15:       affine.for %{{.*}} = 0 to 8 {
// PL15-NEXT:    affine.for %{{.*}} = 0 to 16 iter_args
// PL15:         } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// PL15-NEXT:    affine.store
// PL15-NEXT:  {{^ *}$}}

// PL64-LABEL: func.func @reduce16
// PL64:       affine.for %{{.*}} = 0 to 8 {
// PL64-NOT:     affine.for
// PL64:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @reduce16(%a: memref<8x16xi32>, %b: memref<16xi32>, %out: memref<8xi32>) {
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
    }
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  return
}

// 64 trips exactly is still unrolled (pu_red_m8_n64), 65 is not.
// PL64-LABEL: func.func @reduce64
// PL64:       affine.for %{{.*}} = 0 to 8 {
// PL64-NOT:     affine.for
// PL64:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// OFF-LABEL: func.func @reduce64
// OFF-NOT:   hls.pipeline
func.func @reduce64(%a: memref<8x64xi32>, %b: memref<64xi32>, %out: memref<8xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<64xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x64xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.for %j = 0 to 64 iter_args(%s = %c0_i32) -> (i32) {
      %1 = affine.load %la[%i, %j] : memref<8x64xi32>
      %2 = affine.load %lb[%j] : memref<64xi32>
      %3 = arith.muli %1, %2 : i32
      %4 = arith.addi %s, %3 : i32
      affine.yield %4 : i32
    }
    affine.store %0, %lo[%i] : memref<8xi32>
  }
  return
}
