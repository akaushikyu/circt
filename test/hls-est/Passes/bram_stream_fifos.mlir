// RUN: hls-est %s --bram-analysis=top=top --bram-debug --bram-debug-json=%t.json -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --bram-analysis=top=top --bram-stream-fifos=false -o /dev/null | FileCheck %s --check-prefix=OFF

// hls::stream FIFOs (--bram-stream-fifos, on by default). cgeist lowers a
// stream object to an i32 handle that only reaches the external hls::stream
// methods; Vitis builds one FIFO per stream object (VITIS_NOTES.md N31):
//   depth: the stream pragma (hls.stream), else the template argument
//          (`Li<D>E`; 0 = default), else 2;
//   width: the packed bits of the element (mangled builtin / ap type, else the
//          IR type the reads and writes move: a struct is the sum of its
//          members);
//   price: 0 when depth <= 2 or depth x width <= 1024 bits, else the depth
//          bands at x18 (never x36); bind_storage impl=srl/lutram 0,
//          impl=bram the bands at any size.
// The handle storage is never priced as a RAM, and a stream parameter (a top
// argument, or a callee's) is the caller's FIFO or a port: no FIFO there.

module {
  func.func private @_ZN3hls6streamIiLi0EEC1Ev(memref<?xi32>)
  func.func private @_ZN3hls6streamIiLi0EE5writeERKi(memref<?xi32>, memref<?xi32>)
  func.func private @_ZN3hls6streamIiLi0EE4readEv(memref<?xi32>) -> i32
  func.func private @_ZN3hls6streamIiLi64EE4readEv(memref<?xi32>) -> i32
  func.func private @_ZN3hls6streamIiLi1024EE4readEv(memref<?xi32>) -> i32
  func.func private @_ZN3hls6streamI7ap_uintILi600EELi2EE4readEv(memref<?xi32>) -> i600
  func.func private @_ZN3hls6streamIbLi0EE4readEv(memref<?xi32>) -> i8
  func.func private @_ZN3hls6streamI1PLi0EE5writeERKS1_(memref<?xi32>, memref<?x!llvm.struct<(i32, i16)>>)

  // A dataflow process: reads its stream parameter. The FIFO belongs to the
  // caller's alloca, not to this parameter.
  func.func private @cons(%s: memref<?xi32>) -> i32 {
    %v = func.call @_ZN3hls6streamIiLi0EE4readEv(%s) : (memref<?xi32>) -> i32
    return %v : i32
  }

  // CHECK-LABEL: memref.alloca
  func.func @top(%in: memref<?xi32> {hls.stream = [{depth = 1024 : i32, type = "fifo", variable = "in_s"}]}, %p: memref<?x!llvm.struct<(i32, i16)>>) -> i32 {
    // pragma depth 1024 x 32 bits: 1 bank of ceil(32/18) = 2.
    // CHECK: kind=FIFO  bram=2
    // CHECK-NEXT: 1 FIFO(s) = 2 BRAM [1 x 1024x32 (depth pragma, width mangled i)
    %a = memref.alloca() {hls.stream = [{depth = 1024 : i32, type = "fifo", variable = "a"}], polygeist.varname = "a"} : memref<1xi32>
    %ac = memref.cast %a : memref<1xi32> to memref<?xi32>
    func.call @_ZN3hls6streamIiLi0EEC1Ev(%ac) : (memref<?xi32>) -> ()
    %c0 = arith.constant 0 : i32
    %tmp = memref.alloca() : memref<1xi32>
    %tmpc = memref.cast %tmp : memref<1xi32> to memref<?xi32>
    func.call @_ZN3hls6streamIiLi0EE5writeERKi(%ac, %tmpc) : (memref<?xi32>, memref<?xi32>) -> ()
    %r0 = func.call @cons(%ac) : (memref<?xi32>) -> i32

    // Template depth 64 (hls::stream<int, 64>): 64x32 = 2048 bits -> 2.
    // CHECK: kind=FIFO  bram=2
    // CHECK-NEXT: (depth template, width mangled i): 64x32 = 2048 bits > 1024
    %b = memref.alloca() {polygeist.varname = "b"} : memref<1xi32>
    %bc = memref.cast %b : memref<1xi32> to memref<?xi32>
    %r1 = func.call @_ZN3hls6streamIiLi64EE4readEv(%bc) : (memref<?xi32>) -> i32

    // Default depth (Li0E, no pragma): 2 words, shift registers.
    // CHECK: kind=FIFO  bram=0
    // CHECK-NEXT: 1 x 2x32 (depth default, width mangled i): depth 2 <= 2
    %d = memref.alloca() {polygeist.varname = "d"} : memref<1xi32>
    %dc = memref.cast %d : memref<1xi32> to memref<?xi32>
    %r2 = func.call @_ZN3hls6streamIiLi0EE4readEv(%dc) : (memref<?xi32>) -> i32

    // Depth 2 at 600 bits (template <ap_uint<600>, 2>): shift registers at
    // any width.
    // CHECK: kind=FIFO  bram=0
    // CHECK-NEXT: 2x600 (depth template, width mangled 7ap_uintILi600EE): depth 2 <= 2
    %w = memref.alloca() {polygeist.varname = "w"} : memref<1xi32>
    %wc = memref.cast %w : memref<1xi32> to memref<?xi32>
    %r3 = func.call @_ZN3hls6streamI7ap_uintILi600EELi2EE4readEv(%wc) : (memref<?xi32>) -> i600

    // The threshold is inclusive: 32 x 32 = 1024 bits is shift registers,
    // 33 x 32 a RAM of 2.
    // CHECK: kind=FIFO  bram=0
    // CHECK-NEXT: 32x32 = 1024 bits <= 1024: shift registers
    %t32 = memref.alloca() {hls.stream = [{depth = 32 : i32, type = "fifo", variable = "t32"}]} : memref<1xi32>
    %t32c = memref.cast %t32 : memref<1xi32> to memref<?xi32>
    %r4 = func.call @_ZN3hls6streamIiLi0EE4readEv(%t32c) : (memref<?xi32>) -> i32
    // CHECK: kind=FIFO  bram=2
    // CHECK-NEXT: 33x32 = 1056 bits > 1024: block RAM
    %t33 = memref.alloca() {hls.stream = [{depth = 33 : i32, type = "fifo", variable = "t33"}]} : memref<1xi32>
    %t33c = memref.cast %t33 : memref<1xi32> to memref<?xi32>
    %r5 = func.call @_ZN3hls6streamIiLi0EE4readEv(%t33c) : (memref<?xi32>) -> i32

    // An array of streams: one FIFO per element a read or write reaches,
    // all at the pragma depth (512x32: never x36, so ceil(32/18) = 2 each).
    // A dynamic index may reach every element: 2x2 = 4 FIFOs.
    // CHECK: kind=FIFO  bram=8
    // CHECK-NEXT: 4 FIFO(s) = 8 BRAM [4 x 512x32
    %arr = memref.alloca() {hls.preserve, hls.stream = [{depth = 512 : i32, type = "fifo", variable = "arr"}]} : memref<2x2xi32>
    %i1 = arith.constant 1 : index
    %dyn = arith.index_cast %r1 : i32 to index
    %row = "polygeist.subindex"(%arr, %i1) : (memref<2x2xi32>, index) -> memref<2xi32>
    %el = "polygeist.subindex"(%row, %dyn) : (memref<2xi32>, index) -> memref<?xi32>
    %r6 = func.call @_ZN3hls6streamIiLi0EE4readEv(%el) : (memref<?xi32>) -> i32
    // Constant indices only: Vitis removes the streams nothing reads or
    // writes (hls::stream<int> mid[3] with only mid[1] used: one FIFO), so
    // only arr2[1][1] and arr2[0][1] count; the constructor loop does not.
    // CHECK: kind=FIFO  bram=4
    // CHECK-NEXT: 2 FIFO(s) = 4 BRAM [2 x 512x32
    %arr2 = memref.alloca() {hls.preserve, hls.stream = [{depth = 512 : i32, type = "fifo", variable = "arr2"}]} : memref<2x2xi32>
    %i0 = arith.constant 0 : index
    affine.for %k = 0 to 2 {
      affine.for %l = 0 to 2 {
        %crow = "polygeist.subindex"(%arr2, %k) : (memref<2x2xi32>, index) -> memref<2xi32>
        %cel = "polygeist.subindex"(%crow, %l) : (memref<2xi32>, index) -> memref<?xi32>
        func.call @_ZN3hls6streamIiLi0EEC1Ev(%cel) : (memref<?xi32>) -> ()
      }
    }
    %row2 = "polygeist.subindex"(%arr2, %i1) : (memref<2x2xi32>, index) -> memref<2xi32>
    %el2 = "polygeist.subindex"(%row2, %i1) : (memref<2xi32>, index) -> memref<?xi32>
    %r6b = func.call @_ZN3hls6streamIiLi0EE4readEv(%el2) : (memref<?xi32>) -> i32
    %row3 = "polygeist.subindex"(%arr2, %i0) : (memref<2x2xi32>, index) -> memref<2xi32>
    %el3 = "polygeist.subindex"(%row3, %i1) : (memref<2xi32>, index) -> memref<?xi32>
    %el3c = memref.cast %el3 : memref<?xi32> to memref<?xi32>
    %r6c = func.call @_ZN3hls6streamIiLi0EE4readEv(%el3c) : (memref<?xi32>) -> i32
    %r6d = func.call @_ZN3hls6streamIiLi0EE4readEv(%el2) : (memref<?xi32>) -> i32

    // A struct whose member is an array of streams (struct P {
    // hls::stream<int, 1024> s[4]; }): one FIFO per handle of the member
    // array, 4 x 1024x32 = 4 x 2 (Vitis: p_U .. p_3_U, 8).
    // CHECK: kind=FIFO  bram=8
    // CHECK-NEXT: 4 FIFO(s) = 8 BRAM [4 x 1024x32 (depth template
    %ps = memref.alloca() {polygeist.varname = "ps"} : memref<1x!llvm.struct<(array<4 x i32>)>>
    %psp = "polygeist.memref2pointer"(%ps) : (memref<1x!llvm.struct<(array<4 x i32>)>>) -> !llvm.ptr
    %psm = "polygeist.pointer2memref"(%psp) : (!llvm.ptr) -> memref<4xi32>
    %psel = "polygeist.subindex"(%psm, %dyn) : (memref<4xi32>, index) -> memref<?xi32>
    %r6e = func.call @_ZN3hls6streamIiLi1024EE4readEv(%psel) : (memref<?xi32>) -> i32

    // bool is 1 bit (the IR moves an i8): 2048 x 1 -> 1.
    // CHECK: kind=FIFO  bram=1
    // CHECK-NEXT: 2048x1 (depth pragma, width mangled b)
    %bo = memref.alloca() {hls.stream = [{depth = 2048 : i32, type = "fifo", variable = "bo"}]} : memref<1xi32>
    %boc = memref.cast %bo : memref<1xi32> to memref<?xi32>
    %r7 = func.call @_ZN3hls6streamIbLi0EE4readEv(%boc) : (memref<?xi32>) -> i8

    // A struct element {int, short}: packed 48 bits, 1024 x 48 -> 3.
    // CHECK: kind=FIFO  bram=3
    // CHECK-NEXT: 1024x48 (depth pragma, width ir !llvm.struct<(i32, i16)>)
    %st = memref.alloca() {hls.stream = [{depth = 1024 : i32, type = "fifo", variable = "st"}]} : memref<1xi32>
    %stc = memref.cast %st : memref<1xi32> to memref<?xi32>
    func.call @_ZN3hls6streamI1PLi0EE5writeERKS1_(%stc, %p) : (memref<?xi32>, memref<?x!llvm.struct<(i32, i16)>>) -> ()

    // bind_storage type=fifo: impl=srl is shift registers at 1024 x 32 (0);
    // impl=bram is a block RAM even at 16 x 32 = 512 bits (2).
    // CHECK: kind=FIFO  bram=0
    // CHECK-NEXT: bind_storage impl=srl: shift registers
    %srl = memref.alloca() {hls.bind_storage = [{impl = "srl", type = "fifo", variable = "srl"}], hls.stream = [{depth = 1024 : i32, type = "fifo", variable = "srl"}]} : memref<1xi32>
    %srlc = memref.cast %srl : memref<1xi32> to memref<?xi32>
    %r8 = func.call @_ZN3hls6streamIiLi0EE4readEv(%srlc) : (memref<?xi32>) -> i32
    // CHECK: kind=FIFO  bram=2
    // CHECK-NEXT: bind_storage impl=bram: block RAM at any size, 16x32
    %br = memref.alloca() {hls.bind_storage = [{impl = "bram", type = "fifo", variable = "br"}], hls.stream = [{depth = 16 : i32, type = "fifo", variable = "br"}]} : memref<1xi32>
    %brc = memref.cast %br : memref<1xi32> to memref<?xi32>
    %r9 = func.call @_ZN3hls6streamIiLi0EE4readEv(%brc) : (memref<?xi32>) -> i32

    // Only constructed, never read or written: no FIFO.
    // CHECK: kind=FIFO  bram=0
    // CHECK-NEXT: constructed but never read or written
    %u = memref.alloca() {hls.stream = [{depth = 4096 : i32, type = "fifo", variable = "u"}]} : memref<1xi32>
    %uc = memref.cast %u : memref<1xi32> to memref<?xi32>
    func.call @_ZN3hls6streamIiLi0EEC1Ev(%uc) : (memref<?xi32>) -> ()

    // The top's own stream argument is a port: read here, no FIFO, and an
    // ordinary i32 array next to the streams stays a RAM.
    %r10 = func.call @_ZN3hls6streamIiLi0EE4readEv(%in) : (memref<?xi32>) -> i32
    // CHECK: kind=RAM_1P  bram=2
    %ram = memref.alloca() {polygeist.varname = "ram"} : memref<1024xi32>
    %ix = arith.constant 3 : index
    %x = memref.load %ram[%ix] : memref<1024xi32>
    memref.store %r0, %ram[%ix] : memref<1024xi32>
    %s0 = arith.addi %r1, %r2 : i32
    %s1 = arith.addi %s0, %x : i32
    return %s1 : i32
  }
}

// 2 + 2 + 0 + 0 + 0 + 2 + 8 + 4 + 8 + 1 + 3 + 0 + 2 + 0 + 2 (ram) = 34.
// CHECK: Total BRAM: 34

// DBG: [{{.*}}] a (alloca) @
// DBG: status: fifo
// DBG: hls::stream storage (not a RAM): 1 FIFO(s); methods: 4readEv 5writeERKi C1Ev
// DBG: fifo: 1 x depth 1024 (pragma) x 32 bits (mangled i) -> 2 each:{{.*}}(count: every element)
// DBG: fifo: 2 x depth 512 (pragma) x 32 bits (mangled i) -> 2 each:{{.*}}(count: 2 of 4 elements read or written (constant indices))
// DBG: fifo: 4 x depth 1024 (template) x 32 bits (mangled i) -> 2 each:{{.*}}(count: every element x 4 handles of the member array)

// JSON: "fifo": {
// JSON: "bram": 2,
// JSON: "groups": [
// JSON: "bits": 32,
// JSON: "bits_source": "mangled i",
// JSON: "bram_each": 2,
// JSON: "count": 1,
// JSON: "count_source": "every element",
// JSON: "depth": 1024,
// JSON: "depth_source": "pragma",
// JSON: "ram_type": "FIFO",
// JSON: "status": "fifo",

// The former model: the handle storage is a RAM of i32 words (the 2x2
// array 128 bits, LUTRAM; every 1-word handle 0), only the plain array costs.
// OFF-NOT: kind=FIFO
// OFF: Total BRAM: 2
