// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll -o - | FileCheck %s --check-prefix=ATTR
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=SCHED
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule --bram-analysis=top=k2 --bram-debug -o /dev/null > %t.k2.out 2> %t.k2.err
// RUN: FileCheck %s --input-file=%t.k2.out --check-prefix=K2
// RUN: FileCheck %s --input-file=%t.k2.err --check-prefix=K2DBG
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule --bram-analysis=top=k4 -o /dev/null | FileCheck %s --check-prefix=K4
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule --bram-analysis=top=two_places --bram-debug -o /dev/null > %t.tp.out 2> %t.tp.err
// RUN: FileCheck %s --input-file=%t.tp.out --check-prefix=TWOPLACES
// RUN: FileCheck %s --input-file=%t.tp.err --check-prefix=TWOPLACESDBG
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule --bram-analysis=top=one_place -o /dev/null | FileCheck %s --check-prefix=ONEPLACE
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll=clock-period-ns=20 -o - | FileCheck %s --check-prefix=SLOW

// Calls inside pipelined loops and arrays passed to callees, as Vitis 2025.1
// builds them (VITIS_NOTES.md N14 R2 / R6; W3 review D1(b), D2, D4; kernels
// ~/hls-est-work/exp-src/w3rev/ and exp-src/w3fx/, td=off):
//
//   D4  Calls of one iteration that share an instance run one after the
//       other, each for its whole depth (latency + 1): II = the sum of the
//       depths. @get2s (two loads, one add; depth 2) twice -> II 4 (inl_e3,
//       w3rev_k4), three times -> II 6 (w3fx_d4_three); @get2 (two loads of
//       the argument, one of a ROM, two adds: the second add does not fit the
//       7.3 ns left after the 3.25 ns load, depth 3) twice -> II 6 (w3rev_k2
//       p1). With a 20 ns clock both adds fit: depth 2.
//   D1(b) Two calls of @get2 on disjoint arrays in one pipelined iteration
//       are concurrent: 2 instances, II 1 (w3rev_k2 p2), so @get2 has 3
//       instances and its ROM is charged 3 times (Vitis: 12 BRAM).
//   k4  The II 4 of the serialized calls leaves the 5 reads of `c` per
//       iteration at 2 port-cycles: c is not replicated (Vitis: 4 BRAM).
//   D2  An array passed to a callee instantiated at two places (rd3 under p1
//       and under p2: w3rev_k3b; two calls in one parent: w3fx_d2_conc) is
//       not replicated for the callee's loop, whose II rises to 2; one place
//       under a parent that has 2 instances replicates (w3fx_d2_nested).

// ATTR-LABEL: func.func private @get2(
// ATTR-LABEL: func.func private @get2s(
// ATTR-LABEL: func.func private @k2_p1(
// ATTR:         func.call @get2({{.*}}) {hls.call_depth = 3 : i64, hls.call_occupancy = 1 : i64}
// ATTR:         func.call @get2({{.*}}) {hls.call_depth = 3 : i64, hls.call_occupancy = 1 : i64}
// ATTR-LABEL: func.func @shared3(
// ATTR:         func.call @get2s({{.*}}) {hls.call_depth = 2 : i64, hls.call_occupancy = 1 : i64}
// rd3a is instantiated under pa1 and under pa2: both arguments are
// port-bound. rd3b is instantiated once (under pn): its `t` (pn's own array)
// is not; its output is pn's argument, and pn is instantiated twice.
// ATTR-LABEL: func.func private @rd3a(
// ATTR-SAME:    hls.port_bound_args = [0, 1]
// ATTR-LABEL: func.func private @rd3b(
// ATTR-SAME:    hls.port_bound_args = [1]

// SLOW-LABEL: func.func private @k2_p1(
// SLOW:         func.call @get2({{.*}}) {hls.call_depth = 2 : i64, hls.call_occupancy = 1 : i64}

// SCHED-LABEL: func.func private @k2_p1(
// SCHED:         loopschedule.pipeline II = 6 trip_count = 1024
// SCHED-LABEL: func.func private @k2_p2(
// SCHED:         loopschedule.pipeline II = 1 trip_count = 1024
// SCHED-LABEL: func.func @k4(
// SCHED:         loopschedule.pipeline II = 4 trip_count = 1024
// SCHED-LABEL: func.func @shared3(
// SCHED:         loopschedule.pipeline II = 6 trip_count = 1024
// SCHED-LABEL: func.func private @rd3a(
// SCHED:         loopschedule.pipeline II = 2 trip_count = 1024
// SCHED-LABEL: func.func private @rd3b(
// SCHED:         loopschedule.pipeline II = 1 trip_count = 1024

// K2:      memref.global
// K2-NEXT:   kind={{.*}}  bram=6
// K2:      Total BRAM: 12
// K2DBG:   @get2: 3 instance(s) (inline off)
// K2DBG:     in @k2_p1 (x1): 2 call site(s) -> 1 instance(s) (ordered pairs: 1 by a common array, 0 by a value dependence)
// K2DBG:     in @k2_p2 (x1): 2 call site(s) -> 2 instance(s) (ordered pairs: 0 by a common array, 0 by a value dependence)

// K4:      Total BRAM: 4

// TWOPLACES:     memref.alloca
// TWOPLACES-NEXT:  kind={{RAM_1P|RAM_2P|RAM_S2P|RAM_1R1W}}  bram=2
// TWOPLACES:     memref.alloca
// TWOPLACES-NEXT:  kind={{RAM_1P|RAM_2P|RAM_S2P|RAM_1R1W}}  bram=2
// TWOPLACES:     Total BRAM: 4
// TWOPLACESDBG:  (in @rd3a via call @rd3a @ {{.*}}, port-bound)
// TWOPLACESDBG:  -> copies 1 (port-bound: a callee instantiated at more than one place, N14 R6)

// ONEPLACE:      memref.alloca
// ONEPLACE-NEXT:   kind=RAM_1WNR  bram=8
// ONEPLACE:      Total BRAM: 8

module {
  memref.global "private" constant @tbl : memref<1024xi32> = dense<7>

  // a[i] + a[1023 - i] + tbl[(i * 5) & 1023] (w3rev_k2 get2).
  func.func private @get2(%a: memref<1024xi32>, %i: i32) -> i32 attributes {hls.inline_off} {
    %c5 = arith.constant 5 : i32
    %c1023 = arith.constant 1023 : i32
    %t = memref.get_global @tbl : memref<1024xi32>
    %0 = arith.index_cast %i : i32 to index
    %1 = affine.load %a[symbol(%0)] : memref<1024xi32>
    %2 = arith.subi %c1023, %i : i32
    %3 = arith.index_cast %2 : i32 to index
    %4 = affine.load %a[symbol(%3)] : memref<1024xi32>
    %5 = arith.addi %1, %4 : i32
    %6 = arith.muli %i, %c5 : i32
    %7 = arith.andi %6, %c1023 : i32
    %8 = arith.index_cast %7 : i32 to index
    %9 = affine.load %t[symbol(%8)] : memref<1024xi32>
    %10 = arith.addi %5, %9 : i32
    return %10 : i32
  }
  // a[i] + a[1023 - i] (inl_e3 / w3rev_k4 get2).
  func.func private @get2s(%a: memref<1024xi32>, %i: i32) -> i32 attributes {hls.inline_off} {
    %c1023 = arith.constant 1023 : i32
    %0 = arith.index_cast %i : i32 to index
    %1 = affine.load %a[symbol(%0)] : memref<1024xi32>
    %2 = arith.subi %c1023, %i : i32
    %3 = arith.index_cast %2 : i32 to index
    %4 = affine.load %a[symbol(%3)] : memref<1024xi32>
    %5 = arith.addi %1, %4 : i32
    return %5 : i32
  }

  // w3rev_k2: p1 calls get2 twice on one array, p2 on two arrays.
  func.func private @k2_p1(%in: memref<1024xi32>, %out: memref<1024xi32>) attributes {hls.inline_off} {
    %c1023 = arith.constant 1023 : i32
    %c7 = arith.constant 7 : i32
    %c3 = arith.constant 3 : i32
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in[%i] : memref<1024xi32>
      %1 = arith.muli %0, %c3 : i32
      affine.store %1, %buf[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 1024 {
      %0 = arith.index_cast %i : index to i32
      %1 = func.call @get2(%buf, %0) : (memref<1024xi32>, i32) -> i32
      %2 = arith.muli %0, %c7 : i32
      %3 = arith.andi %2, %c1023 : i32
      %4 = func.call @get2(%buf, %3) : (memref<1024xi32>, i32) -> i32
      %5 = arith.addi %1, %4 : i32
      affine.store %5, %out[%i] : memref<1024xi32>
    }
    return
  }
  func.func private @k2_p2(%in: memref<1024xi32>, %out: memref<1024xi32>) attributes {hls.inline_off} {
    %cm1 = arith.constant -1 : i32
    %c1023 = arith.constant 1023 : i32
    %c7 = arith.constant 7 : i32
    %c1 = arith.constant 1 : i32
    %b2 = memref.alloca() {polygeist.varname = "b2"} : memref<1024xi32>
    %b1 = memref.alloca() {polygeist.varname = "b1"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in[%i] : memref<1024xi32>
      %1 = arith.addi %0, %c1 : i32
      affine.store %1, %b1[%i] : memref<1024xi32>
      %2 = arith.addi %0, %cm1 : i32
      affine.store %2, %b2[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 1024 {
      %0 = arith.index_cast %i : index to i32
      %1 = func.call @get2(%b1, %0) : (memref<1024xi32>, i32) -> i32
      %2 = arith.muli %0, %c7 : i32
      %3 = arith.andi %2, %c1023 : i32
      %4 = func.call @get2(%b2, %3) : (memref<1024xi32>, i32) -> i32
      %5 = arith.addi %1, %4 : i32
      affine.store %5, %out[%i] : memref<1024xi32>
    }
    return
  }
  func.func @k2(%in1: memref<1024xi32>, %out1: memref<1024xi32>, %in2: memref<1024xi32>, %out2: memref<1024xi32>) {
    func.call @k2_p1(%in1, %out1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @k2_p2(%in2, %out2) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }

  // w3rev_k4: two get2s calls on buf and five reads of c per iteration.
  func.func @k4(%in: memref<1024xi32>, %out: memref<1024xi32>) {
    %c7i = arith.constant 7 : i32
    %c1023 = arith.constant 1023 : i32
    %c3 = arith.constant 3 : i32
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<1024xi32>
    %c = memref.alloca() {polygeist.varname = "c"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in[%i] : memref<1024xi32>
      %1 = arith.muli %0, %c3 : i32
      affine.store %1, %buf[%i] : memref<1024xi32>
      %2 = arith.addi %0, %c7i : i32
      affine.store %2, %c[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 1024 {
      %0 = arith.index_cast %i : index to i32
      %1 = func.call @get2s(%buf, %0) : (memref<1024xi32>, i32) -> i32
      %2 = arith.muli %0, %c7i : i32
      %3 = arith.andi %2, %c1023 : i32
      %4 = func.call @get2s(%buf, %3) : (memref<1024xi32>, i32) -> i32
      %5 = arith.addi %1, %4 : i32
      %r0 = affine.load %c[%i] : memref<1024xi32>
      %r1 = affine.load %c[(%i * 3) mod 1024] : memref<1024xi32>
      %r2 = affine.load %c[(%i * 5) mod 1024] : memref<1024xi32>
      %r3 = affine.load %c[(%i * 11) mod 1024] : memref<1024xi32>
      %r4 = affine.load %c[(%i * 13) mod 1024] : memref<1024xi32>
      %s0 = arith.addi %5, %r0 : i32
      %s1 = arith.addi %s0, %r1 : i32
      %s2 = arith.addi %s1, %r2 : i32
      %s3 = arith.addi %s2, %r3 : i32
      %s4 = arith.addi %s3, %r4 : i32
      affine.store %s4, %out[%i] : memref<1024xi32>
    }
    return
  }

  // w3fx_d4_three: three get2s calls on one array per iteration.
  func.func @shared3(%buf: memref<1024xi32>, %out: memref<1024xi32>) {
    %c7 = arith.constant 7 : i32
    %c3 = arith.constant 3 : i32
    %c1023 = arith.constant 1023 : i32
    affine.for %i = 0 to 1024 {
      %0 = arith.index_cast %i : index to i32
      %1 = func.call @get2s(%buf, %0) : (memref<1024xi32>, i32) -> i32
      %2 = arith.muli %0, %c7 : i32
      %3 = arith.andi %2, %c1023 : i32
      %4 = func.call @get2s(%buf, %3) : (memref<1024xi32>, i32) -> i32
      %5 = arith.muli %0, %c3 : i32
      %6 = arith.andi %5, %c1023 : i32
      %7 = func.call @get2s(%buf, %6) : (memref<1024xi32>, i32) -> i32
      %8 = arith.addi %1, %4 : i32
      %9 = arith.addi %8, %7 : i32
      affine.store %9, %out[%i] : memref<1024xi32>
    }
    return
  }

  // rd3 reads its argument three times per iteration of its own loop.
  // w3rev_k3b: one call under each of two parents (2 places).
  func.func private @rd3a(%a: memref<1024xi32>, %o: memref<1024xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 1024 {
      %x = affine.load %a[%i] : memref<1024xi32>
      %y = affine.load %a[1023 - %i] : memref<1024xi32>
      %z = affine.load %a[(%i * 7) mod 1024] : memref<1024xi32>
      %s = arith.addi %x, %y : i32
      %t = arith.addi %s, %z : i32
      affine.store %t, %o[%i] : memref<1024xi32>
    }
    return
  }
  func.func private @pa1(%in: memref<1024xi32>, %o: memref<1024xi32>) attributes {hls.inline_off} {
    %c3 = arith.constant 3 : i32
    %t = memref.alloca() {polygeist.varname = "t"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      %w = arith.muli %v, %c3 : i32
      affine.store %w, %t[%i] : memref<1024xi32>
    }
    func.call @rd3a(%t, %o) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
  func.func private @pa2(%in: memref<1024xi32>, %o: memref<1024xi32>) attributes {hls.inline_off} {
    %c5 = arith.constant 5 : i32
    %t = memref.alloca() {polygeist.varname = "t"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      %w = arith.addi %v, %c5 : i32
      affine.store %w, %t[%i] : memref<1024xi32>
    }
    func.call @rd3a(%t, %o) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
  func.func @two_places(%in1: memref<1024xi32>, %o1: memref<1024xi32>, %in2: memref<1024xi32>, %o2: memref<1024xi32>) {
    func.call @pa1(%in1, %o1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @pa2(%in2, %o2) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }

  // w3fx_d2_nested: rd3 at one place (under pn), pn instantiated twice.
  func.func private @rd3b(%a: memref<1024xi32>, %o: memref<1024xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 1024 {
      %x = affine.load %a[%i] : memref<1024xi32>
      %y = affine.load %a[1023 - %i] : memref<1024xi32>
      %z = affine.load %a[(%i * 7) mod 1024] : memref<1024xi32>
      %s = arith.addi %x, %y : i32
      %t = arith.addi %s, %z : i32
      affine.store %t, %o[%i] : memref<1024xi32>
    }
    return
  }
  func.func private @pn(%in: memref<1024xi32>, %o: memref<1024xi32>) attributes {hls.inline_off} {
    %c3 = arith.constant 3 : i32
    %t = memref.alloca() {polygeist.varname = "t"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      %w = arith.muli %v, %c3 : i32
      affine.store %w, %t[%i] : memref<1024xi32>
    }
    func.call @rd3b(%t, %o) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
  func.func @one_place(%in1: memref<1024xi32>, %o1: memref<1024xi32>, %in2: memref<1024xi32>, %o2: memref<1024xi32>) {
    func.call @pn(%in1, %o1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @pn(%in2, %o2) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
}
