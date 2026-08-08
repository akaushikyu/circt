// RUN: hls-est %s --mark-constant-fills | FileCheck %s

// --mark-constant-fills (VITIS_NOTES.md N26), W7 review D1 / D2:
//   @cond      `if (in[i] > 0) buf[i] = 0`: a conditional store leaves a RAM
//              (kernel w7rv_cond0: `buf 4096x1 RAM_AUTO_1R1W`, 1 BRAM), so
//              no mark.
//   @cond_call the same through a filler that is called under an `if`.
//   @local_if  an array declared inside the `if` that fills it is filled
//              unconditionally relative to itself: marked.
//   @twoconst  one `inline off` filler called with 1 for A and 300 for B:
//              Vitis specialises the constant per call (kernel w7rv_twoconst:
//              A 4096x1 ROM, B 4096x9 ROM), so each array gets its own width.

// CHECK-LABEL: func.func @cond
// CHECK: memref.alloca()
// CHECK-NOT: hls.const_fill
// CHECK-SAME: polygeist.varname = "cbuf"
func.func @cond(%in: memref<4096xi32>, %idx: memref<1024xi32>, %out: memref<1024xi32>) {
  %buf = memref.alloca() {polygeist.varname = "cbuf"} : memref<4096xi32>
  %c0 = arith.constant 0 : i32
  %c4095 = arith.constant 4095 : i32
  affine.for %i = 0 to 4096 {
    %x = affine.load %in[%i] : memref<4096xi32>
    %p = arith.cmpi sgt, %x, %c0 : i32
    scf.if %p {
      affine.store %c0, %buf[%i] : memref<4096xi32>
    }
  }
  affine.for %i = 0 to 1024 {
    %x = affine.load %idx[%i] : memref<1024xi32>
    %m = arith.andi %x, %c4095 : i32
    %j = arith.index_cast %m : i32 to index
    %v = memref.load %buf[%j] : memref<4096xi32>
    affine.store %v, %out[%i] : memref<1024xi32>
  }
  return
}

func.func private @fill(%b: memref<4096xi32>, %v: i32) {
  affine.for %i = 0 to 4096 {
    affine.store %v, %b[%i] : memref<4096xi32>
  }
  return
}

// CHECK-LABEL: func.func @cond_call
// CHECK: memref.alloca()
// CHECK-NOT: hls.const_fill
// CHECK-SAME: polygeist.varname = "ccbuf"
func.func @cond_call(%p: i1, %idx: memref<1024xi32>, %out: memref<1024xi32>) {
  %buf = memref.alloca() {polygeist.varname = "ccbuf"} : memref<4096xi32>
  %c5 = arith.constant 5 : i32
  %c4095 = arith.constant 4095 : i32
  scf.if %p {
    func.call @fill(%buf, %c5) : (memref<4096xi32>, i32) -> ()
  }
  affine.for %i = 0 to 1024 {
    %x = affine.load %idx[%i] : memref<1024xi32>
    %m = arith.andi %x, %c4095 : i32
    %j = arith.index_cast %m : i32 to index
    %v = memref.load %buf[%j] : memref<4096xi32>
    affine.store %v, %out[%i] : memref<1024xi32>
  }
  return
}

// CHECK-LABEL: func.func @local_if
// CHECK: memref.alloca() {hls.const_fill = 3 : i32, polygeist.varname = "lbuf"}
func.func @local_if(%p: i1, %idx: memref<1024xi32>, %out: memref<1024xi32>) {
  %c5 = arith.constant 5 : i32
  %c4095 = arith.constant 4095 : i32
  scf.if %p {
    %buf = memref.alloca() {polygeist.varname = "lbuf"} : memref<4096xi32>
    affine.for %i = 0 to 4096 {
      affine.store %c5, %buf[%i] : memref<4096xi32>
    }
    affine.for %i = 0 to 1024 {
      %x = affine.load %idx[%i] : memref<1024xi32>
      %m = arith.andi %x, %c4095 : i32
      %j = arith.index_cast %m : i32 to index
      %v = memref.load %buf[%j] : memref<4096xi32>
      affine.store %v, %out[%i] : memref<1024xi32>
    }
  }
  return
}

func.func private @set_value(%b: memref<4096xi32>, %v: i32) {
  affine.for %i = 0 to 4096 {
    affine.store %v, %b[%i] : memref<4096xi32>
  }
  return
}

// CHECK-LABEL: func.func @twoconst
// CHECK-DAG: memref.alloca() {hls.const_fill = 1 : i32, polygeist.varname = "A"}
// CHECK-DAG: memref.alloca() {hls.const_fill = 9 : i32, polygeist.varname = "B"}
func.func @twoconst(%idx: memref<1024xi32>, %out: memref<1024xi32>) {
  %a = memref.alloca() {polygeist.varname = "A"} : memref<4096xi32>
  %b = memref.alloca() {polygeist.varname = "B"} : memref<4096xi32>
  %c1 = arith.constant 1 : i32
  %c300 = arith.constant 300 : i32
  %c4095 = arith.constant 4095 : i32
  func.call @set_value(%a, %c1) : (memref<4096xi32>, i32) -> ()
  func.call @set_value(%b, %c300) : (memref<4096xi32>, i32) -> ()
  affine.for %i = 0 to 1024 {
    %x = affine.load %idx[%i] : memref<1024xi32>
    %m = arith.andi %x, %c4095 : i32
    %j = arith.index_cast %m : i32 to index
    %v = memref.load %a[%j] : memref<4096xi32>
    %w = memref.load %b[%j] : memref<4096xi32>
    %s = arith.addi %v, %w : i32
    affine.store %s, %out[%i] : memref<1024xi32>
  }
  return
}
