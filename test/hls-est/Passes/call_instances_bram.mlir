// RUN: hls-est %s --bram-analysis=top=two_indep --bram-debug --bram-debug-json=%t.json -o /dev/null > %t.indep.out 2> %t.indep.err
// RUN: FileCheck %s --input-file=%t.indep.out --check-prefix=INDEP
// RUN: FileCheck %s --input-file=%t.indep.err --check-prefix=INDEPDBG
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --bram-analysis=top=two_shared -o /dev/null | FileCheck %s --check-prefix=SHARED
// RUN: hls-est %s --bram-analysis=top=chain -o /dev/null | FileCheck %s --check-prefix=CHAIN
// RUN: hls-est %s --bram-analysis=top=via_memory -o /dev/null | FileCheck %s --check-prefix=MEMDEP
// RUN: hls-est %s --bram-analysis=top=limited -o /dev/null | FileCheck %s --check-prefix=LIMIT
// RUN: hls-est %s --bram-analysis=top=two_parents -o /dev/null | FileCheck %s --check-prefix=PARENTS
// RUN: hls-est %s --bram-analysis=top=in_loop -o /dev/null | FileCheck %s --check-prefix=INLOOP
// RUN: hls-est %s --bram-analysis=top=shared_global --bram-attribute-globals -o /dev/null | FileCheck %s --check-prefix=GLOBAL

// Non-inlined callees are charged once per instance (VITIS_NOTES.md N14,
// kernels ~/hls-est-work/exp-src/inline/inl_*.cpp, Vitis 2025.1 td=off):
//
//   R1  a callee's local array is one memory, counted once per instance
//       (inl_a1 off = on = 4; inl_b2 two instances = 8; inl_b4 three = 12).
//   R2  calls of one callee from one parent that can run concurrently get
//       one instance each; ordered calls share one: a common array, read or
//       written (inl_b1, inl_b5: 1 instance), a value of one reaching the
//       other (inl_b9 `g(g(x))`: 1), also through memory, or
//       `#pragma HLS allocation function instances=.. limit=1` (inl_b6: 1).
//       One call site in a loop is one instance (inl_c1).
//   R3  every parent module gets its own instances: a callee called from two
//       parents is instantiated twice (inl_d1: 14, inl_d2: 12).
//
// @work holds a 512x32 array (1 BRAM); @g a 512x32 table (1 BRAM).

// INDEP:      memref.alloca
// INDEP-NEXT:   kind=RAM_1P  bram=2
// INDEP-NEXT:   512x32b -> RAM_1P (x36/port) = 1 BRAM_18K x 2 instance(s) of @work = 2 (non-inlined callee, N14)
// INDEP:      Total BRAM: 2
// INDEPDBG:      instances: 2 of @work (N14: charged once per instance; 1 per instance)
// INDEPDBG-NEXT: bram: 2
// INDEPDBG:      --- instances (non-inlined callees, VITIS_NOTES.md N14 R2/R3) ---
// INDEPDBG-NEXT:   @work: 2 instance(s) (inline off)
// INDEPDBG-NEXT:     in @two_indep (x1): 2 call site(s) -> 2 instance(s) (ordered pairs: 0 by a common array, 0 by a value dependence)
// INDEPDBG-NEXT:       call @ {{.*}} -> instance 0
// INDEPDBG-NEXT:       call @ {{.*}} -> instance 1
// JSON:      "instances": [
// JSON-NEXT:   {
// JSON-NEXT:     "func": "work",
// JSON-NEXT:     "inline_off": true,
// JSON-NEXT:     "instances": 2,
// JSON-NEXT:     "parents": [
// JSON-NEXT:       {
// JSON-NEXT:         "allocation_limit": null,
// JSON-NEXT:         "call_sites": 2,
// JSON-NEXT:         "instances": 2,
// JSON-NEXT:         "parent": "two_indep",
// JSON-NEXT:         "parent_instances": 1,
// JSON-NEXT:         "rule": "2 call site(s) -> 2 instance(s) (ordered pairs: 0 by a common array, 0 by a value dependence)",
// JSON-NEXT:         "sites": [
// JSON-NEXT:           {
// JSON-NEXT:             "instance": 0,
// JSON-NEXT:             "loc": "{{.*}}"
// JSON-NEXT:           },
// JSON-NEXT:           {
// JSON-NEXT:             "instance": 1,
// JSON:      "memrefs": [
// JSON:      "bram": 2,
// JSON-NEXT: "bram_per_instance": 1,
// JSON:      "instances": 2,
// JSON:      "owner_func": null

// SHARED:  kind=RAM_1P  bram=1
// SHARED:  Total BRAM: 1
// CHAIN:   kind={{.*}}  bram=1
// CHAIN:   Total BRAM: 1
// MEMDEP:  kind={{.*}}  bram=1
// MEMDEP:  Total BRAM: 1
// LIMIT:   kind=RAM_1P  bram=1
// LIMIT:   Total BRAM: 1
// PARENTS: kind=RAM_1P  bram=2
// PARENTS: Total BRAM: 2
// INLOOP:  kind=RAM_1P  bram=1
// INLOOP:  Total BRAM: 1
// A static table shared by two callees lives in their deepest common caller
// (here the top, one instance). @own is written by @u2: both calls of @u2
// write it, so they are ordered and share one instance (w3fx_d3_samepar),
// and a written static is one memory anyway (N14 R9, w3rev_k5): charged once.
// GLOBAL:      memref.global @ loc({{.*}}:[[# @LINE + 7]]:3)
// GLOBAL-NEXT:   kind={{.*}}  bram=1
// GLOBAL:      memref.global @ loc({{.*}}:[[# @LINE + 6]]:3)
// GLOBAL-NEXT:   kind={{.*}}  bram=1
// GLOBAL:      Total BRAM: 2

module {
  memref.global "private" @shared : memref<512xi32> = uninitialized
  memref.global "private" @own : memref<512xi32> = uninitialized

  func.func private @work(%in: memref<512xi32>, %out: memref<512xi32>) attributes {hls.inline_off, hls.orig_name = "work"} {
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
  func.func private @g(%x: i32) -> i32 attributes {hls.inline_off, hls.orig_name = "g"} {
    %t = memref.alloca() {polygeist.varname = "t"} : memref<512xi32>
    %c511 = arith.constant 511 : i32
    %i = arith.andi %x, %c511 : i32
    %idx = arith.index_cast %i : i32 to index
    affine.store %x, %t[0] : memref<512xi32>
    %v = memref.load %t[%idx] : memref<512xi32>
    return %v : i32
  }

  // R2: disjoint arrays -> 2 instances.
  func.func @two_indep(%a: memref<512xi32>, %b: memref<512xi32>, %c: memref<512xi32>, %d: memref<512xi32>) {
    func.call @work(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @work(%c, %d) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  // R2: a common array, only read by both -> 1 instance (inl_b5).
  func.func @two_shared(%a: memref<512xi32>, %b: memref<512xi32>, %c: memref<512xi32>) {
    func.call @work(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @work(%a, %c) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  // R2: g(g(x)) -> 1 instance (inl_b9).
  func.func @chain(%x: i32) -> i32 {
    %y = func.call @g(%x) : (i32) -> i32
    %z = func.call @g(%y) : (i32) -> i32
    return %z : i32
  }
  // R2: the value of the first call reaches the second through memory (a
  // store to and a load from a caller array) -> 1 instance.
  func.func @via_memory(%x: i32, %tmp: memref<4xi32>) -> i32 {
    %y = func.call @g(%x) : (i32) -> i32
    affine.store %y, %tmp[0] : memref<4xi32>
    %w = affine.load %tmp[1] : memref<4xi32>
    %z = func.call @g(%w) : (i32) -> i32
    return %z : i32
  }
  // R2: allocation limit 1 on disjoint arrays -> 1 instance (inl_b6).
  func.func @limited(%a: memref<512xi32>, %b: memref<512xi32>, %c: memref<512xi32>, %d: memref<512xi32>) attributes {hls.allocation = [{instances = ["work"], limit = 1 : i32, type = "function"}]} {
    func.call @work(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @work(%c, %d) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  // R3: one instance in each of two parents -> 2.
  func.func private @p1(%a: memref<512xi32>, %b: memref<512xi32>) attributes {hls.inline_off} {
    func.call @work(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  func.func private @p2(%a: memref<512xi32>, %b: memref<512xi32>) attributes {hls.inline_off} {
    func.call @work(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  func.func @two_parents(%a: memref<512xi32>, %b: memref<512xi32>, %c: memref<512xi32>, %d: memref<512xi32>) {
    func.call @p1(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @p2(%c, %d) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  // One call site in a loop: one instance whatever the trip count (inl_c1).
  func.func @in_loop(%a: memref<4x512xi32>, %b: memref<4x512xi32>) {
    affine.for %k = 0 to 4 {
      %ra = memref.subview %a[%k, 0] [1, 512] [1, 1] : memref<4x512xi32> to memref<512xi32, strided<[1], offset: ?>>
      %ca = memref.cast %ra : memref<512xi32, strided<[1], offset: ?>> to memref<512xi32>
      %rb = memref.subview %b[%k, 0] [1, 512] [1, 1] : memref<4x512xi32> to memref<512xi32, strided<[1], offset: ?>>
      %cb = memref.cast %rb : memref<512xi32, strided<[1], offset: ?>> to memref<512xi32>
      func.call @work(%ca, %cb) : (memref<512xi32>, memref<512xi32>) -> ()
    }
    return
  }
  // Globals: @shared is used by @u1 and @u2 (both one instance under the
  // top) -> charged once for the top; @own only by @u2, which the top calls
  // twice on disjoint arrays, but both calls write @own -> 1 instance
  // (before the W3 review fixes: 2 instances, charged twice).
  func.func private @u1(%o: memref<512xi32>) attributes {hls.inline_off} {
    %s = memref.get_global @shared : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %s[%i] : memref<512xi32>
      affine.store %v, %o[%i] : memref<512xi32>
    }
    return
  }
  func.func private @u2(%o: memref<512xi32>) attributes {hls.inline_off} {
    %s = memref.get_global @shared : memref<512xi32>
    %w = memref.get_global @own : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %s[%i] : memref<512xi32>
      affine.store %v, %w[%i] : memref<512xi32>
    }
    affine.for %i = 0 to 512 {
      %v = affine.load %w[511 - %i] : memref<512xi32>
      affine.store %v, %o[%i] : memref<512xi32>
    }
    return
  }
  func.func @shared_global(%a: memref<512xi32>, %b: memref<512xi32>, %c: memref<512xi32>) {
    func.call @u1(%a) : (memref<512xi32>) -> ()
    func.call @u2(%b) : (memref<512xi32>) -> ()
    func.call @u2(%c) : (memref<512xi32>) -> ()
    return
  }
}
