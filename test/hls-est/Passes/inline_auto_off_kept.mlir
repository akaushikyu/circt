// RUN: hls-est %s --inline | FileCheck %s
// RUN: hls-est %s --inline --bram-analysis=top=top --bram-debug --bram-debug-json=%t.json -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=BRAM
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON

// cgeist keeps the calls Vitis does not inline automatically (VITIS_NOTES.md
// N18, MEMOS decision #34, Polygeist W10 `--hls-auto-inline`) and marks them
// `hls.inline_auto_off` ({calls, size} on the call, {size} on the callee).
// hls-est treats such a callee exactly like an `inline off` one: --inline
// keeps its calls (a plain callee is still inlined) and --bram-analysis
// charges its memories once per instance (N14 R1-R3): two calls on disjoint
// arrays are two instances of @work's 512x32 buffer (1 BRAM each).

// CHECK-LABEL: func.func private @work
// CHECK-LABEL: func.func @top
// CHECK-COUNT-2: call @work
// CHECK-NOT:     call @plain
// CHECK:         return

// BRAM: 512x32b -> RAM_1P (x36/port) = 1 BRAM_18K x 2 instance(s) of @work = 2 (non-inlined callee, N14)
// BRAM: Total BRAM: 2
// DBG:      --- instances (non-inlined callees, VITIS_NOTES.md N14 R2/R3) ---
// DBG-NEXT:   @work: 2 instance(s) (not inlined automatically)
// JSON:      "func": "work",
// JSON-NEXT: "inline_auto_off": true,
// JSON-NEXT: "inline_off": false,

module {
  func.func private @plain(%x: i32) -> i32 {
    %c2 = arith.constant 2 : i32
    %y = arith.muli %x, %c2 : i32
    return %y : i32
  }
  func.func private @work(%in: memref<512xi32>, %out: memref<512xi32>) attributes {hls.inline_auto_off = {size = 120 : i64}, hls.orig_name = "work"} {
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
    }
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @top(%a: memref<512xi32>, %b: memref<512xi32>, %c: memref<512xi32>, %d: memref<512xi32>, %x: i32) -> i32 {
    func.call @work(%a, %b) {hls.inline_auto_off = {calls = 2 : i64, size = 120 : i64}} : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @work(%c, %d) {hls.inline_auto_off = {calls = 2 : i64, size = 120 : i64}} : (memref<512xi32>, memref<512xi32>) -> ()
    %y = func.call @plain(%x) : (i32) -> i32
    return %y : i32
  }
}
