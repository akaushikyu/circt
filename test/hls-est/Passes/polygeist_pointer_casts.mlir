// RUN: hls-est %s --symbol-privatize=exclude=named_stream --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s -o - | FileCheck %s --check-prefix=ROUND

// cgeist emits polygeist.pointer2memref for a string literal argument (the
// name of `hls::stream<float> s("fifo_0")`) and polygeist.memref2pointer for
// member accesses; hls-est used to stop at the parser on both ("operation
// being parsed with an unregistered dialect", 145 HLSFactory_v2 designs in
// the W8a sweep, OPEN_ISSUES.md O25). They are pure casts: they parse, print
// back unchanged, and own no storage.

// ROUND: "polygeist.pointer2memref"(%{{.*}}) : (!llvm.ptr) -> memref<?xi8>
// ROUND: "polygeist.memref2pointer"(%{{.*}}) : (memref<?xi32>) -> !llvm.ptr
// CHECK: Total BRAM: 2
llvm.mlir.global internal constant @str0("fifo_0\00") {addr_space = 0 : i32}
func.func private @_ZN3hls6streamIfLi0EEC1EPKc(memref<?xi32>, memref<?xi8>)
func.func private @use_ptr(!llvm.ptr)
func.func @named_stream(%in: memref<1024xi32>, %out: memref<1024xi32>) {
  %c0_i32 = arith.constant 0 : i32
  %s = memref.alloca() {hls.stream = [{depth = 2 : i32, type = "fifo", variable = "s"}], polygeist.varname = "s"} : memref<1xi32>
  %cast = memref.cast %s : memref<1xi32> to memref<?xi32>
  affine.store %c0_i32, %s[0] : memref<1xi32>
  %name = llvm.mlir.addressof @str0 : !llvm.ptr
  %m = "polygeist.pointer2memref"(%name) : (!llvm.ptr) -> memref<?xi8>
  func.call @_ZN3hls6streamIfLi0EEC1EPKc(%cast, %m) : (memref<?xi32>, memref<?xi8>) -> ()
  %p = "polygeist.memref2pointer"(%cast) : (memref<?xi32>) -> !llvm.ptr
  func.call @use_ptr(%p) : (!llvm.ptr) -> ()
  %buf = memref.alloca() {polygeist.varname = "buf"} : memref<1024xi32>
  affine.for %i = 0 to 1024 {
    %v = affine.load %in[%i] : memref<1024xi32>
    affine.store %v, %buf[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %v = affine.load %buf[1023 - %i] : memref<1024xi32>
    affine.store %v, %out[%i] : memref<1024xi32>
  }
  return
}
