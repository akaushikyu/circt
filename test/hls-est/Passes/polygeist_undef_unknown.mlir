// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s -o - | FileCheck %s --check-prefix=ROUND

// cgeist emits polygeist.undef for a variable read before any assignment on
// some path (chstone sha: a pointer a loop advances), and other Polygeist ops
// hls-est does not model, such as polygeist.get_func (the address of a
// function passed as a value). hls-est used to stop at the parser on both
// (W8b). polygeist.undef is a pure op without storage; an op hls-est does not
// model parses as an unregistered op of the polygeist dialect and owns no
// memory either.

// ROUND: func.func @fnptr(%{{.*}}: memref<?x!llvm.func<void ()>>)
// ROUND: "polygeist.undef"() : () -> memref<?xi32>
// ROUND: "polygeist.get_func"() <{name = @callee}> : () -> !llvm.ptr
// CHECK: Total BRAM: 2
func.func private @callee()
func.func private @use(memref<?xi32>, !llvm.ptr)
func.func private @takefn(memref<?x!llvm.func<void ()>>)
// A function passed by pointer is a memref of !llvm.func elements.
func.func @fnptr(%p: memref<?x!llvm.func<void ()>>) {
  func.call @takefn(%p) : (memref<?x!llvm.func<void ()>>) -> ()
  return
}
func.func @top(%in: memref<1024xi32>, %out: memref<1024xi32>, %c: i1) {
  %u = "polygeist.undef"() : () -> memref<?xi32>
  %cast = memref.cast %in : memref<1024xi32> to memref<?xi32>
  %sel = arith.select %c, %cast, %u : memref<?xi32>
  %f = "polygeist.get_func"() <{name = @callee}> : () -> !llvm.ptr
  func.call @use(%sel, %f) : (memref<?xi32>, !llvm.ptr) -> ()
  %buf = memref.alloca() : memref<1024xi32>
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
