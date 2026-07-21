// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis -o /dev/null > %t.all.out 2> %t.all.err
// RUN: FileCheck %s --input-file=%t.all.out --check-prefix=ALL
// RUN: FileCheck %s --input-file=%t.all.err --check-prefix=WARN
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis=top=a --bram-debug --bram-debug-json=%t.a.json -o /dev/null > %t.a.out 2> %t.a.err
// RUN: FileCheck %s --input-file=%t.a.out --check-prefix=TOPA
// RUN: FileCheck %s --input-file=%t.a.err --check-prefix=TOPADBG
// RUN: FileCheck %s --input-file=%t.a.json --check-prefix=TOPAJSON
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis=top=b -o /dev/null 2>&1 | FileCheck %s --check-prefix=TOPB
// RUN: hls-est %s --symbol-privatize=exclude=a --symbol-dce --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s --check-prefix=TOPA --implicit-check-not=warning:
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis --bram-debug-json=%t.all.json -o /dev/null 2>/dev/null
// RUN: FileCheck %s --input-file=%t.all.json --check-prefix=ALLJSON
// RUN: not hls-est %s --bram-analysis=top=nosuch -o /dev/null 2>&1 | FileCheck %s --check-prefix=BAD
// RUN: not hls-est %s --bram-analysis=top=ext -o /dev/null 2>&1 | FileCheck %s --check-prefix=BADEXT

// --bram-analysis=top=<symbol> (MEMOS.md M7, OPEN_ISSUES.md O12): Vitis
// synthesizes the top function and what it calls, so only the memrefs of the
// func.funcs reachable from the top through calls are costed, plus the
// memref.globals those functions take (memref.get_global). cgeist emits other
// public functions too (uncalled alternative tops, standalone copies of
// inlined callees, O10); without top= every function is costed and a warning
// names the public functions that hold memrefs.
//
//   @a:      alloca 64xi32 (1 BRAM), calls @helper
//   @helper: alloca 1024xi32 (2: 1024 words, ceil(32/18)), reads global @G1
//            (512xi32, 1)
//   @b:      alloca 2048xi32 (4: ceil(32/9)), reads global @G2 (4096xi32, 8)
//   @ext:    a declaration
// top=a -> 1 + 2 + 1 = 4; top=b -> 4 + 8 = 12; no top -> 16 and a warning.
// The --symbol-privatize=exclude=a --symbol-dce prefix (what the harness and the
// Estimation RUN lines do) gives the same 4 without top= and no warning: only
// one public function is left.

// WARN: warning: --bram-analysis: 3 public functions hold memrefs (@a, @helper, @b); all of them are costed. Give the top function with --bram-analysis=top=<symbol> (or --symbol-privatize=exclude=<top> --symbol-dce first) to cost only what it reaches
// ALL: Total BRAM: 16
// ALLJSON: "top": null,

// TOPA:      memref.global
// TOPA-NEXT:   kind=RAM_1P  bram=1
// TOPA:      memref.alloca
// TOPA-NEXT:   kind=RAM_1P  bram=1
// TOPA:      memref.alloca
// TOPA-NEXT:   kind=RAM_1P  bram=2
// TOPA-NOT:  memref.
// TOPA:      Total BRAM: 4

// TOPADBG-NOT: warning:
// TOPADBG: top: @a (2 function(s) reachable through calls; 2 memref(s) outside them not costed)
// TOPADBG: Total BRAM: 4

// TOPAJSON:      "top": {
// TOPAJSON-NEXT:   "functions": [
// TOPAJSON-NEXT:     "a",
// TOPAJSON-NEXT:     "helper"
// TOPAJSON-NEXT:   ],
// TOPAJSON-NEXT:   "skipped_memrefs": 2,
// TOPAJSON-NEXT:   "symbol": "a"
// TOPAJSON-NEXT: },
// TOPAJSON:      "total_bram": 4,

// TOPB-NOT: warning:
// TOPB:     kind=RAM_1P  bram=8
// TOPB:     kind=RAM_1P  bram=4
// TOPB-NOT: kind=
// TOPB:     Total BRAM: 12

// BAD: error: --bram-analysis: top=nosuch: no func.func with a body of that name in the module
// BADEXT: error: --bram-analysis: top=ext: no func.func with a body of that name in the module

module {
  memref.global "private" @G1 : memref<512xi32> = uninitialized
  memref.global "private" @G2 : memref<4096xi32> = uninitialized
  func.func private @ext(memref<64xi32>)
  func.func @a(%in: memref<64xi32>, %out: memref<64xi32>) {
    %buf = memref.alloca() {hls.preserve, polygeist.varname = "a_buf"} : memref<64xi32>
    affine.for %i = 0 to 64 {
      %0 = affine.load %in[%i] : memref<64xi32>
      affine.store %0, %buf[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %buf[63 - %i] : memref<64xi32>
      affine.store %0, %out[%i] : memref<64xi32>
    }
    func.call @helper(%out) : (memref<64xi32>) -> ()
    return
  }
  func.func @helper(%io: memref<64xi32>) {
    %g = memref.get_global @G1 : memref<512xi32>
    %buf = memref.alloca() {hls.preserve, polygeist.varname = "h_buf"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %0 = affine.load %g[%i mod 512] : memref<512xi32>
      affine.store %0, %buf[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %buf[%i * 16] : memref<1024xi32>
      affine.store %0, %io[%i] : memref<64xi32>
    }
    return
  }
  func.func @b(%in: memref<64xi32>, %out: memref<64xi32>) {
    %g = memref.get_global @G2 : memref<4096xi32>
    %buf = memref.alloca() {hls.preserve, polygeist.varname = "b_buf"} : memref<2048xi32>
    affine.for %i = 0 to 2048 {
      %0 = affine.load %g[%i * 2] : memref<4096xi32>
      affine.store %0, %buf[%i] : memref<2048xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %buf[%i * 32] : memref<2048xi32>
      affine.store %0, %out[%i] : memref<64xi32>
    }
    return
  }
}
