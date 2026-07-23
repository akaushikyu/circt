// RUN: hls-est %s --inline --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis 2>&1 | FileCheck %s --implicit-check-not="not pipelined"
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis 2>&1 | FileCheck %s --implicit-check-not="not pipelined"
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=SCHED

// The RUN line with the DME front (--inline ... --dead-memory-elimination) is the
// default pipeline (MEMOS.md M1, M5: decisions #1 and #4); the one with
// --infer-vitis-split-array is the former default (td=auto), kept as a variant.

// `arith.index_castui` is the same wire as `arith.index_cast`. cgeist casts an
// unsigned C index (`unsigned char`, `ap_uint<W>`, `size_t`) with it since its
// unsigned-index fix, and --convert-affine-to-loopschedule only knew
// index_cast: spector_hls/histogram's `hist_loop` stayed a sequential loop
// ("not pipelined ... unsupported operation arith.index_castui"). Reduced
// histogram (4 bins arrays instead of 8): the 4 byte reads of `data` per
// iteration need 2 cycles on its two ports, so the loop pipelines at II 2
// (the full histogram: 8 reads, II 4 = Vitis `hist_loop` II 4). Each bins
// array is 256 x 32 = one RAM_1P BRAM.

// CHECK: Total BRAM: 4
// SCHED: loopschedule.pipeline II = {{ *}}1
// SCHED: loopschedule.pipeline II = {{ *}}2
// SCHED: loopschedule.pipeline II = {{ *}}1

func.func @hist(%data: memref<1024xi8>, %out: memref<256xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %c1_i32 = arith.constant 1 : i32
  %h0 = memref.alloca() {hls.preserve, polygeist.varname = "h0"} : memref<256xi32>
  %h1 = memref.alloca() {hls.preserve, polygeist.varname = "h1"} : memref<256xi32>
  %h2 = memref.alloca() {hls.preserve, polygeist.varname = "h2"} : memref<256xi32>
  %h3 = memref.alloca() {hls.preserve, polygeist.varname = "h3"} : memref<256xi32>
  affine.for %i = 0 to 256 {
    affine.store %c0_i32, %h0[%i] : memref<256xi32>
    affine.store %c0_i32, %h1[%i] : memref<256xi32>
    affine.store %c0_i32, %h2[%i] : memref<256xi32>
    affine.store %c0_i32, %h3[%i] : memref<256xi32>
  }
  affine.for %i = 0 to 1024 step 4 {
    %b0 = affine.load %data[%i] : memref<1024xi8>
    %x0 = arith.index_castui %b0 : i8 to index
    %v0 = memref.load %h0[%x0] : memref<256xi32>
    %n0 = arith.addi %v0, %c1_i32 : i32
    memref.store %n0, %h0[%x0] : memref<256xi32>
    %b1 = affine.load %data[%i + 1] : memref<1024xi8>
    %x1 = arith.index_castui %b1 : i8 to index
    %v1 = memref.load %h1[%x1] : memref<256xi32>
    %n1 = arith.addi %v1, %c1_i32 : i32
    memref.store %n1, %h1[%x1] : memref<256xi32>
    %b2 = affine.load %data[%i + 2] : memref<1024xi8>
    %x2 = arith.index_castui %b2 : i8 to index
    %v2 = memref.load %h2[%x2] : memref<256xi32>
    %n2 = arith.addi %v2, %c1_i32 : i32
    memref.store %n2, %h2[%x2] : memref<256xi32>
    %b3 = affine.load %data[%i + 3] : memref<1024xi8>
    %x3 = arith.index_castui %b3 : i8 to index
    %v3 = memref.load %h3[%x3] : memref<256xi32>
    %n3 = arith.addi %v3, %c1_i32 : i32
    memref.store %n3, %h3[%x3] : memref<256xi32>
  }
  affine.for %i = 0 to 256 {
    %a = affine.load %h0[%i] : memref<256xi32>
    %b = affine.load %h1[%i] : memref<256xi32>
    %c = affine.load %h2[%i] : memref<256xi32>
    %d = affine.load %h3[%i] : memref<256xi32>
    %s0 = arith.addi %a, %b : i32
    %s1 = arith.addi %c, %d : i32
    %s = arith.addi %s0, %s1 : i32
    affine.store %s, %out[%i] : memref<256xi32>
  }
  return
}
