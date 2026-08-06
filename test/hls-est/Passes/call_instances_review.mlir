// RUN: hls-est %s --bram-analysis=top=war_after --bram-debug -o /dev/null > %t.war.out 2> %t.war.err
// RUN: FileCheck %s --input-file=%t.war.out --check-prefix=WAR
// RUN: FileCheck %s --input-file=%t.war.err --check-prefix=WARDBG
// RUN: hls-est %s --bram-analysis=top=raw_between --bram-debug -o /dev/null > %t.raw.out 2> %t.raw.err
// RUN: FileCheck %s --input-file=%t.raw.out --check-prefix=RAW
// RUN: FileCheck %s --input-file=%t.raw.err --check-prefix=RAWDBG
// RUN: hls-est %s --bram-analysis=top=static_same_parent --bram-attribute-globals --bram-debug -o /dev/null > %t.sp.out 2> %t.sp.err
// RUN: FileCheck %s --input-file=%t.sp.out --check-prefix=SAMEPAR
// RUN: FileCheck %s --input-file=%t.sp.err --check-prefix=SAMEPARDBG
// RUN: hls-est %s --bram-analysis=top=static_two_parents --bram-attribute-globals -o /dev/null | FileCheck %s --check-prefix=TWOPAR

// W3 review fixes of the instance model (VITIS_NOTES.md N14; Vitis 2025.1
// td=off kernels ~/hls-est-work/exp-src/w3rev/ and exp-src/w3fx/):
//
//   @war_after   (w3rev_k6) `work(a, ra); work(b, rb);` and then a loop that
//                reads ra and overwrites b: the write to b follows the second
//                call, so it is no dependence of it. Vitis: 2 instances, 8
//                BRAM. hls-est charged one instance before the fix (D1(a)).
//   @raw_between the same loop between the calls: the second call reads what
//                the loop wrote from the first call's output, 1 instance.
//   @static_same_parent (w3fx_d3_samepar) `u2(a, b); u2(c, d)` with a written
//                `static` array inside u2: both calls write it, so they are
//                ordered and share one instance (Vitis: u2 x1, loc 2 + t 2).
//   @static_two_parents (w3rev_k5, w3fx_d3_mix) u2 called from two parents:
//                2 instances, its local array twice, the written static once
//                (Vitis keeps one memory, in the top; D3).
//
// @work6 holds a 512x32 array (1 BRAM); @u2 a local 512x32 array and the
// written 512x32 global @st.

// WAR:     memref.alloca
// WAR-NEXT:  kind={{.*}}  bram=2
// WAR:     Total BRAM: 2
// WARDBG:  in @war_after (x1): 2 call site(s) -> 2 instance(s) (ordered pairs: 0 by a common array, 0 by a value dependence)

// RAW:     memref.alloca
// RAW-NEXT:  kind={{.*}}  bram=1
// RAW:     Total BRAM: 1
// RAWDBG:  in @raw_between (x1): 2 call site(s) -> 1 instance(s) (ordered pairs: 0 by a common array, 1 by a value dependence)

// SAMEPAR:     memref.global
// SAMEPAR-NEXT:  kind={{.*}}  bram=1
// SAMEPAR:     memref.alloca
// SAMEPAR-NEXT:  kind={{.*}}  bram=1
// SAMEPAR:     Total BRAM: 2
// SAMEPARDBG:  in @static_same_parent (x1): 2 call site(s) -> 1 instance(s) (ordered pairs: 1 by a common array, 0 by a value dependence)

// TWOPAR:      memref.global
// TWOPAR-NEXT:   kind={{.*}}  bram=1
// TWOPAR-NEXT:   {{.*}}written static shared by every instance of its functions: one memory in @static_two_parents, N14 R9)
// TWOPAR:      memref.alloca
// TWOPAR-NEXT:   kind={{.*}}  bram=2
// TWOPAR-NEXT:   {{.*}} x 2 instance(s) of @u2 = 2 (non-inlined callee, N14)
// TWOPAR:      Total BRAM: 3

module {
  memref.global "private" @st : memref<512xi32> = uninitialized

  func.func private @work6(%in: memref<512xi32>, %out: memref<512xi32>) attributes {hls.inline_off, hls.orig_name = "work"} {
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
  func.func @war_after(%a: memref<512xi32>, %b: memref<512xi32>, %ra: memref<512xi32>, %rb: memref<512xi32>) {
    %c1 = arith.constant 1 : i32
    func.call @work6(%a, %ra) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @work6(%b, %rb) : (memref<512xi32>, memref<512xi32>) -> ()
    affine.for %i = 0 to 512 {
      %v = affine.load %ra[%i] : memref<512xi32>
      %w = arith.addi %v, %c1 : i32
      affine.store %w, %b[%i] : memref<512xi32>
    }
    return
  }
  func.func @raw_between(%a: memref<512xi32>, %b: memref<512xi32>, %ra: memref<512xi32>, %rb: memref<512xi32>) {
    %c1 = arith.constant 1 : i32
    func.call @work6(%a, %ra) : (memref<512xi32>, memref<512xi32>) -> ()
    affine.for %i = 0 to 512 {
      %v = affine.load %ra[%i] : memref<512xi32>
      %w = arith.addi %v, %c1 : i32
      affine.store %w, %b[%i] : memref<512xi32>
    }
    func.call @work6(%b, %rb) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }

  func.func private @u2(%in: memref<512xi32>, %out: memref<512xi32>) attributes {hls.inline_off, hls.orig_name = "u2"} {
    %t = memref.get_global @st : memref<512xi32>
    %loc = memref.alloca() {polygeist.varname = "loc"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %loc[%i] : memref<512xi32>
      %s = affine.load %t[%i] : memref<512xi32>
      %u = arith.addi %v, %s : i32
      affine.store %u, %t[%i] : memref<512xi32>
    }
    affine.for %i = 0 to 512 {
      %x = affine.load %loc[511 - %i] : memref<512xi32>
      %y = affine.load %t[%i] : memref<512xi32>
      %z = arith.addi %x, %y : i32
      affine.store %z, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @static_same_parent(%a: memref<512xi32>, %b: memref<512xi32>, %c: memref<512xi32>, %d: memref<512xi32>) {
    func.call @u2(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @u2(%c, %d) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  func.func private @q1(%a: memref<512xi32>, %b: memref<512xi32>) attributes {hls.inline_off} {
    func.call @u2(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  func.func private @q2(%a: memref<512xi32>, %b: memref<512xi32>) attributes {hls.inline_off} {
    func.call @u2(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  func.func @static_two_parents(%a: memref<512xi32>, %b: memref<512xi32>, %c: memref<512xi32>, %d: memref<512xi32>) {
    func.call @q1(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @q2(%c, %d) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
}
