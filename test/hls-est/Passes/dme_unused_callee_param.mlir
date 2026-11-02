// RUN: hls-est %s --dead-memory-elimination | FileCheck %s
// RUN: hls-est %s --dead-memory-elimination --bram-analysis=top=top -o /dev/null | FileCheck %s --check-prefix=BRAM

// A kept callee (`#pragma HLS inline off`) reads the caller's array `w` only
// into a dead value. The load dies with the value; the parameter is then not
// accessed at all, so --dead-memory-elimination removes it from the callee and
// its operand from the call, and `w` - written by the caller, read by nobody -
// dies too (VITIS_NOTES.md N17 (a): fbh3_l_callee_rd_dead, no memory row;
// tiled_attn_module `split_wq` / `split_wk`). `x`, which the callee still
// reads, stays; so does the parameter of a public function (@pub), whose
// callers hls-est cannot see.

// CHECK-LABEL: func.func private @use(
// CHECK-SAME:    %{{.*}}: memref<1024xi32>, %{{.*}}: memref<1024xi32>)
// CHECK:         affine.load
// CHECK-NOT:     affine.load
// CHECK:         affine.store
// CHECK-LABEL: func.func @pub(
// CHECK-SAME:    %{{.*}}: memref<4xi32>)
// CHECK-LABEL: func.func @top
// CHECK-NOT:     varname = "w"
// CHECK:         memref.alloca() {polygeist.varname = "x"}
// CHECK-NOT:     varname = "w"
// CHECK:         call @use(%{{.*}}, %{{.*}}) : (memref<1024xi32>, memref<1024xi32>) -> ()

// BRAM:     memref.alloca
// BRAM-NEXT:  kind={{.*}}  bram=2
// BRAM-NOT: kind=
// BRAM:     Total BRAM: 2

module {
  func.func private @use(%w: memref<1024xi32>, %x: memref<1024xi32>, %o: memref<1024xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 1024 {
      %a = affine.load %w[%i] : memref<1024xi32>
      %b = affine.load %x[%i] : memref<1024xi32>
      affine.store %b, %o[%i] : memref<1024xi32>
    }
    return
  }
  func.func @pub(%p: memref<4xi32>) {
    return
  }
  func.func @top(%in: memref<1024xi32>, %out: memref<1024xi32>) {
    %w = memref.alloca() {polygeist.varname = "w"} : memref<1024xi32>
    %x = memref.alloca() {polygeist.varname = "x"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.store %v, %w[%i] : memref<1024xi32>
      affine.store %v, %x[%i] : memref<1024xi32>
    }
    func.call @use(%w, %x, %out) : (memref<1024xi32>, memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
}
