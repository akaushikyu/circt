// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --inline --bram-analysis -o /dev/null 2>&1 | FileCheck %s --implicit-check-not=warning:
// RUN: hls-est %s --inline --bram-analysis=top=top -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --inline -o - | FileCheck %s --check-prefix=IR

// The harness prefix `--symbol-privatize=exclude=<top> --symbol-dce` and
// `--bram-analysis=top=<top>` keep and cost every callee the top reaches
// through kept calls, nested ones included, and drop the rest: @leaf is
// reached through @mid (kept, `hls.inline_off`); @unused, a public function
// holding an array, is neither reached nor costed; @plain is inlined into
// the top. With both, the result is the same: @leaf's 512x32 (1 BRAM) plus
// the top's own 512x32 (1 BRAM).

// CHECK:      memref.alloca
// CHECK-NEXT:   kind={{.*}}  bram=1
// CHECK:      memref.alloca
// CHECK-NEXT:   kind={{.*}}  bram=1
// CHECK-NOT:  kind=
// CHECK:      Total BRAM: 2

// IR-NOT:   func.func{{.*}}@unused
// IR-NOT:   func.func{{.*}}@plain
// IR:       func.func private @leaf
// IR:       func.func private @mid
// IR:       func.func @top
// IR:         call @mid

module {
  func.func private @leaf(%in: memref<512xi32>, %out: memref<512xi32>) attributes {hls.inline_off} {
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
  func.func private @mid(%in: memref<512xi32>, %out: memref<512xi32>) attributes {hls.inline_off} {
    func.call @leaf(%in, %out) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  func.func private @plain(%x: i32) -> i32 {
    %c2 = arith.constant 2 : i32
    %y = arith.muli %x, %c2 : i32
    return %y : i32
  }
  func.func @unused(%in: memref<512xi32>, %out: memref<512xi32>) {
    %buf = memref.alloca() {polygeist.varname = "dead"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
      %w = affine.load %buf[%i] : memref<512xi32>
      affine.store %w, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @top(%in: memref<512xi32>, %out: memref<512xi32>) {
    %tmp = memref.alloca() {polygeist.varname = "tmp"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      %w = func.call @plain(%v) : (i32) -> i32
      affine.store %w, %tmp[%i] : memref<512xi32>
    }
    func.call @mid(%tmp, %out) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
}
