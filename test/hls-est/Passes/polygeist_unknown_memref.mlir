// RUN: not hls-est %s --lower-polygeist-subindex -o /dev/null 2>&1 | FileCheck %s

// A Polygeist op hls-est does not model parses as an unregistered op of the
// polygeist dialect. That is safe for an op without memrefs
// (polygeist.get_func, Passes/polygeist_undef_unknown.mlir); one that takes or
// returns a memref could read, write or view a memory the analyses would not
// count, so --lower-polygeist-subindex (the first pass of the default
// pipeline) rejects it (W8b review).

// CHECK: error: polygeist op not modelled by hls-est takes or returns a memref
func.func @top(%in: memref<1024xi32>) {
  "polygeist.some_unmodelled_store"(%in) : (memref<1024xi32>) -> ()
  return
}
