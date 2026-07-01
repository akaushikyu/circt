// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug-json=%t.json > %t.debug.out
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis > %t.plain.out
// RUN: diff %t.plain.out %t.debug.out
// RUN: FileCheck %s --input-file=%t.json

// --bram-debug-json explains every memref without changing the estimate.
//
// `buf` carries a cyclic factor-2 pragma: banking turns it into two 512 x i32
// banks that no longer carry the pragma, so the JSON must name them through the
// provenance attributes banking leaves behind (hls.bank_of / hls.bank_index /
// hls.bank_count / hls.partition). `acc` is a plain 256 x i32 array (8192 bits,
// above the 1024-bit BRAM promotion threshold). Each is one BRAM_18K at x32.
// The `diff` RUN line proves the stdout report is byte-identical with the
// option on and off.

module {
  func.func @kernel(%arg0: memref<1024xi32>, %arg1: memref<256xi32>) {
    %c1_i32 = arith.constant 1 : i32
    %buf = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "buf"}], hls.preserve, polygeist.varname = "buf"} : memref<1024xi32> loc("kernel.cpp":12:5)
    %acc = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<256xi32> loc("kernel.cpp":13:5)
    affine.for %i = 0 to 1024 {
      %0 = affine.load %arg0[%i] : memref<1024xi32>
      affine.store %0, %buf[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 256 {
      %0 = affine.load %buf[%i * 2] : memref<1024xi32>
      %1 = affine.load %buf[%i * 2 + 1] : memref<1024xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %acc[%i] : memref<256xi32>
    }
    affine.for %i = 0 to 256 {
      %0 = affine.load %acc[%i] : memref<256xi32>
      %1 = arith.addi %0, %c1_i32 : i32
      affine.store %1, %arg1[%i] : memref<256xi32>
    }
    return
  }
}

// llvm::json prints object keys sorted, one per line.
// CHECK:      "functions": [
// CHECK-NEXT:   "kernel"
// CHECK:      "memrefs": [

// bank 0 of buf: one live port -> the x36 mode, 512 words = one RAMB18.
// CHECK:      "bank_math": {
// CHECK-NEXT:   "addr_depth": 512,
// CHECK-NEXT:   "bits_per_bram": 18432,
// CHECK-NEXT:   "blocks": 1,
// CHECK-NEXT:   "blocks_per_copy": 1,
// CHECK-NEXT:   "config_width": 36,
// CHECK-NEXT:   "depth_per_block": 512,
// CHECK-NEXT:   "depth_tiles": 1,
// CHECK-NEXT:   "max_width": 36,
// CHECK-NEXT:   "replication": 1,
// CHECK-NEXT:   "wide": true,
// CHECK-NEXT:   "width_tiles": 1
// CHECK:      "bram": 1,
// CHECK-NEXT: "elem_bits": 32,
// CHECK-NEXT: "elem_type": "i32",
// CHECK-NEXT: "exclude_reason": null,
// CHECK-NEXT: "func": "kernel",
// CHECK-NEXT: "id": "kernel#0",
// CHECK-NEXT: "kind": "alloca",
// CHECK-NEXT: "loc": {
// CHECK-NEXT:   "col": 5,
// CHECK-NEXT:   "file": "kernel.cpp",
// CHECK-NEXT:   "line": 12
// CHECK:      "name": null,
// CHECK-NEXT: "partition": {
// CHECK-NEXT:   "bank_count": 2,
// CHECK-NEXT:   "bank_index": 0,
// CHECK-NEXT:   "dim": 1,
// CHECK-NEXT:   "factor": 2,
// CHECK-NEXT:   "kind": "cyclic",
// CHECK-NEXT:   "reason": null,
// CHECK-NEXT:   "source": "pragma"
// CHECK:      "ram_type": "RAM_1P",
// CHECK:      "replication": {
// CHECK-NEXT:   "copies": 1,
// CHECK-NEXT:   "limiting_loop": null,
// CHECK-NEXT:   "loops": [
// CHECK:        "max_stores_per_loop": 1,
// CHECK-NEXT:   "replicable": true
// CHECK:      "status": "counted",
// CHECK-NEXT: "varname": "buf",
// CHECK-NEXT: "words": 512

// bank 1 of buf
// CHECK:      "id": "kernel#1",
// CHECK:      "partition": {
// CHECK-NEXT:   "bank_count": 2,
// CHECK-NEXT:   "bank_index": 1,
// CHECK-NEXT:   "dim": 1,
// CHECK-NEXT:   "factor": 2,
// CHECK-NEXT:   "kind": "cyclic",
// CHECK:      "ram_type": "RAM_1P",
// CHECK:      "varname": "buf",

// acc: unpartitioned
// CHECK:      "bram": 1,
// CHECK:      "id": "kernel#2",
// CHECK:      "partition": null,
// CHECK:      "ram_type": "RAM_1P",
// CHECK:      "status": "counted",
// CHECK-NEXT: "varname": "acc",
// CHECK-NEXT: "words": 256

// CHECK:      "summary": [
// CHECK:      "total_bram": 3,
// CHECK-NEXT: "version": 2
