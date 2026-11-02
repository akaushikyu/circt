// RUN: hls-est %s --bram-analysis --bram-debug-json=%t.json > /dev/null
// RUN: FileCheck %s --input-file=%t.json
// RUN: not hls-est %s --bram-analysis --bram-debug-json=%t.no-such-dir/x.json > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err --check-prefix=ERR

// Exclusion statuses the JSON distinguishes, and the failure mode of the JSON
// option itself:
//   dynbuf  dynamic extent -> status "dynamic_shape" (not "zero_size")
//   zero    0 x i32        -> status "zero_size"
//   small   8 x i32        -> status "excluded_small", quoting the threshold
// A JSON path that cannot be opened is an error: the report is still printed
// in full (REPORT) but hls-est exits non-zero (`not`) and says why (ERR), so a
// harness never mistakes a missing file for an empty result.

module {
  func.func @dyn(%n: index, %arg0: memref<256xi32>, %arg1: memref<256xi32>) {
    %a = memref.alloca(%n) {polygeist.varname = "dynbuf"} : memref<?xi32>
    %z = memref.alloca() {polygeist.varname = "zero"} : memref<0xi32>
    %s = memref.alloca() {polygeist.varname = "small"} : memref<8xi32>
    affine.for %i = 0 to 256 {
      %0 = affine.load %arg0[%i] : memref<256xi32>
      affine.store %0, %a[%i] : memref<?xi32>
      affine.store %0, %s[%i mod 8] : memref<8xi32>
    }
    affine.for %i = 0 to 256 {
      %0 = affine.load %a[%i] : memref<?xi32>
      %1 = affine.load %s[%i mod 8] : memref<8xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %arg1[%i] : memref<256xi32>
    }
    return
  }
}

// CHECK:      "exclude_reason": "dynamic shape; static size unknown; not estimated",
// CHECK:      "status": "dynamic_shape",
// CHECK-NEXT: "varname": "dynbuf",
// CHECK-NEXT: "words": null

// CHECK:      "exclude_reason": "zero-size array (0 bits)",
// CHECK:      "status": "zero_size",
// CHECK-NEXT: "varname": "zero",
// CHECK-NEXT: "words": 0

// CHECK:      "exclude_reason": "size 256 bits < 1024-bit BRAM promotion threshold (Words*Bits >= 1024 -> BRAM); distributed RAM, 0 BRAM",
// CHECK:      "status": "excluded_small",
// CHECK-NEXT: "varname": "small",
// CHECK-NEXT: "words": 8

// CHECK:      "total_bram": 0,

// REPORT:     memref.alloca
// REPORT:     Total BRAM: 0

// ERR:        error: bram-debug-json: cannot write '{{.*}}no-such-dir{{.*}}x.json': {{.*}}
