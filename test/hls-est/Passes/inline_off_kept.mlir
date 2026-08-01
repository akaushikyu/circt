// RUN: hls-est %s --inline | FileCheck %s
// RUN: hls-est %s --inline --inline-ignore-inline-off | FileCheck %s --check-prefix=IGNORE

// hls-est's --inline keeps a call whose callee carries `hls.inline_off`
// (`#pragma HLS inline off`, as cgeist writes it since Polygeist 62c40544),
// because Vitis keeps such a callee as a module of its own (VITIS_NOTES.md
// N14), and inlines every other call as before. A kept callee that calls a
// plain function still has that call inlined. --inline-ignore-inline-off
// restores the old behaviour (every call inlined).

// CHECK-LABEL: func.func private @kept
// CHECK-NOT:     call @
// CHECK:         arith.muli
// CHECK-LABEL: func.func @top
// CHECK:         call @kept
// CHECK-NOT:     call @plain
// CHECK:         return

// IGNORE-LABEL: func.func @top
// IGNORE-NOT:     call @
// IGNORE:         return

module {
  func.func private @plain(%x: i32) -> i32 {
    %c2 = arith.constant 2 : i32
    %y = arith.muli %x, %c2 : i32
    return %y : i32
  }
  func.func private @kept(%x: i32) -> i32 attributes {hls.inline_off, hls.orig_name = "kept"} {
    %y = func.call @plain(%x) : (i32) -> i32
    %c1 = arith.constant 1 : i32
    %z = arith.addi %y, %c1 : i32
    return %z : i32
  }
  func.func @top(%x: i32) -> i32 {
    %a = func.call @kept(%x) : (i32) -> i32
    %b = func.call @plain(%a) : (i32) -> i32
    return %b : i32
  }
}
