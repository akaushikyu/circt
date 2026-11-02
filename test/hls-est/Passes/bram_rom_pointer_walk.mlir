// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG

// An initialised global that nothing writes is a ROM of its values' width
// (N26) also when it is read through a pointer walk: `p = &tab[j][0];
// walk(p, n)` with `while (n-- > 0) acc ^= *p++;` passes a row view to a
// callee that carries the position as a loop iter_arg (polygeist.subindex
// of the iter_arg, yielded). Vitis 2025.1, kernels shafix_v2a / shafix_v2b
// (`const unsigned char tab[2][8192]`, ASCII values <= 126 / one value 200):
// `tab 16384x7 ROM_AUTO_1R` = 7 BRAM_18K / `16384x8` = 8; chstone/sha's
// `indata` likewise 16384x7 = 7 (VITIS_NOTES.md N52). The table here holds
// 64 (7 bits by the N26 rule). The same walk that stores through the pointer
// leaves a RAM.

// CHECK: memref.global @ loc({{.*}}:[[#L:]]:3)
// CHECK-NEXT: kind=ROM_1P  bram=7
// CHECK-NEXT: 16384x7b initialised global, never written -> ROM_1P
// CHECK: memref.global @ loc({{.*}}:[[#L+1]]:3)
// CHECK-NEXT: kind=RAM_1P  bram=8

// DBG: ram type: ROM_1P -- initialised global that no get_global site writes (ROM); element width 7 of 8 bits from its values (N26)

module {
  memref.global "private" @tab : memref<2x8192xi8> = dense<64>
  memref.global "private" @tabw : memref<2x8192xi8> = dense<100>

  func.func private @walk(%p: memref<?xi8>, %n: index) -> i32 {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c0_i32 = arith.constant 0 : i32
    %true = arith.constant true
    %r:2 = affine.for %i = 0 to %n iter_args(%acc = %c0_i32, %q = %p) -> (i32, memref<?xi8>) {
      %v = memref.load %q[%c0] : memref<?xi8>
      %e = arith.extui %v : i8 to i32
      %s = arith.xori %acc, %e : i32
      %nq = "polygeist.subindex"(%q, %c1) : (memref<?xi8>, index) -> memref<?xi8>
      %sel = arith.select %true, %nq, %nq : memref<?xi8>
      affine.yield %s, %sel : i32, memref<?xi8>
    }
    return %r#0 : i32
  }

  func.func private @fill(%p: memref<?xi8>, %n: index) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c7 = arith.constant 7 : i8
    %r = affine.for %i = 0 to %n iter_args(%q = %p) -> (memref<?xi8>) {
      memref.store %c7, %q[%c0] : memref<?xi8>
      %nq = "polygeist.subindex"(%q, %c1) : (memref<?xi8>, index) -> memref<?xi8>
      affine.yield %nq : memref<?xi8>
    }
    return
  }

  func.func @top(%n: index, %out: memref<2xi32>) {
    %t = memref.get_global @tab : memref<2x8192xi8>
    %w = memref.get_global @tabw : memref<2x8192xi8>
    affine.for %j = 0 to 2 {
      %row = "polygeist.subindex"(%t, %j) : (memref<2x8192xi8>, index) -> memref<?xi8>
      %r = func.call @walk(%row, %n) : (memref<?xi8>, index) -> i32
      memref.store %r, %out[%j] : memref<2xi32>
      %roww = "polygeist.subindex"(%w, %j) : (memref<2x8192xi8>, index) -> memref<?xi8>
      func.call @fill(%roww, %n) : (memref<?xi8>, index) -> ()
      %r2 = func.call @walk(%roww, %n) : (memref<?xi8>, index) -> i32
      memref.store %r2, %out[%j] : memref<2xi32>
    }
    return
  }
}
