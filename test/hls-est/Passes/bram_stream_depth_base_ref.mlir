// RUN: hls-est %s --bram-analysis=top=top -o /dev/null | FileCheck %s

// The depth of a stream reached through a callee parameter of the base type
// `hls::stream<T>&` (VITIS_NOTES N49, OPEN_ISSUES O66 (a)). In the real
// headers `hls::stream<T, D>` derives from `hls::stream<T>`: a call through
// the reference names `stream<T, 0>` (`Li0E`), whatever the object's D. The
// object's depth is its constructor's (`Li256E`), else the largest D any
// call names; the reference's 0 never wins. Corpus: barry_walker lab_3
// `hls::stream<Batch, 256> accum_buffers[16]`, Vitis 16 FIFOs of depth 256
// (24 BRAM each at 432 bits); kernels w9r6p sd_d{16,256,2048,8192}.

module {
  func.func private @_ZN3hls6streamIiLi256EEC1Ev(memref<?xi32>)
  func.func private @_ZN3hls6streamIiLi0EE5writeERKi(memref<?xi32>, memref<?xi32>)
  func.func private @_ZN3hls6streamIiLi0EE4readEv(memref<?xi32>) -> i32
  func.func private @_ZN3hls6streamIiLi512EE4readEv(memref<?xi32>) -> i32

  func.func private @prod(%s: memref<?xi32>, %v: memref<?xi32>) {
    func.call @_ZN3hls6streamIiLi0EE5writeERKi(%s, %v) : (memref<?xi32>, memref<?xi32>) -> ()
    return
  }
  func.func private @cons(%s: memref<?xi32>) -> i32 {
    %r = func.call @_ZN3hls6streamIiLi0EE4readEv(%s) : (memref<?xi32>) -> i32
    return %r : i32
  }

  func.func @top(%v: memref<?xi32>) -> i32 attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    // hls::stream<int, 256> s[2]: the producer call (base reference, Li0E)
    // comes before the constructor in the walk; depth 256 from the
    // constructor: 2 x 256x32 = 2 x 2.
    // CHECK: kind=FIFO  bram=4
    // CHECK-NEXT: 2 FIFO(s) = 4 BRAM [2 x 256x32 (depth template
    %s = memref.alloca() {hls.preserve, polygeist.varname = "s"} : memref<2xi32>
    %sc = memref.cast %s : memref<2xi32> to memref<?xi32>
    %c1 = arith.constant 1 : index
    %s1 = "polygeist.subindex"(%s, %c1) : (memref<2xi32>, index) -> memref<?xi32>
    func.call @prod(%sc, %v) : (memref<?xi32>, memref<?xi32>) -> ()
    func.call @prod(%s1, %v) : (memref<?xi32>, memref<?xi32>) -> ()
    affine.for %i = 0 to 2 {
      %e = "polygeist.subindex"(%s, %i) : (memref<2xi32>, index) -> memref<?xi32>
      func.call @_ZN3hls6streamIiLi256EEC1Ev(%e) : (memref<?xi32>) -> ()
    }
    %a = func.call @cons(%sc) : (memref<?xi32>) -> i32
    %b = func.call @cons(%s1) : (memref<?xi32>) -> i32

    // No constructor reached: the largest depth a call names (512), not the
    // base reference's 0: 512x32 -> 2.
    // CHECK: kind=FIFO  bram=2
    // CHECK-NEXT: 1 FIFO(s) = 2 BRAM [1 x 512x32 (depth template
    %t = memref.alloca() {polygeist.varname = "t"} : memref<1xi32>
    %tc = memref.cast %t : memref<1xi32> to memref<?xi32>
    func.call @prod(%tc, %v) : (memref<?xi32>, memref<?xi32>) -> ()
    %c = func.call @_ZN3hls6streamIiLi512EE4readEv(%tc) : (memref<?xi32>) -> i32

    // Only base references: depth 2 (default), shift registers.
    // CHECK: kind=FIFO  bram=0
    // CHECK-NEXT: (depth default
    %u = memref.alloca() {polygeist.varname = "u"} : memref<1xi32>
    %uc = memref.cast %u : memref<1xi32> to memref<?xi32>
    func.call @prod(%uc, %v) : (memref<?xi32>, memref<?xi32>) -> ()
    %d = func.call @cons(%uc) : (memref<?xi32>) -> i32
    %x = arith.addi %a, %b : i32
    %y = arith.addi %c, %d : i32
    %z = arith.addi %x, %y : i32
    return %z : i32
  }
}

// CHECK: Total BRAM: 6
