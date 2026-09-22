// RUN: hls-est %s --auto-pipeline-unroll | FileCheck %s

// --auto-pipeline-unroll promotes a location that is invariant in a
// pipelined loop to a register (LLVM LICM scalar promotion) only when every
// access of it in the loop is a load or a store. A cast of it passed to a
// call (cgeist's `hls::stream<float>::write(const float &)`: `v = A[..];
// s.write(v)` stores v into a one-element local and passes its cast) reads
// the location: promoting it dropped the stores and with them the loads of
// A that fed them (MultiHeadSelfAttention1 opt4 node14: 15 of the 16 reads
// of `v357`'s banks vanished, the PIPO channel was priced on one bank; Vitis
// 8 banks x 4 = 32, OPEN_ISSUES O121 correction).

// CHECK-LABEL: func.func @stream_write_through_cast
// CHECK: affine.for
// CHECK-NOT: iter_args
// CHECK: affine.load %{{.*}} : memref<64xf32>
// CHECK-NEXT: affine.store %{{.*}}, %[[TMP:.*]][0] : memref<1xf32>
// CHECK: func.call @write
// CHECK: affine.load %{{.*}} : memref<64xf32>
// CHECK-NEXT: affine.store
// CHECK: func.call @write
func.func private @write(memref<?xi32>, memref<?xf32>)
func.func @stream_write_through_cast(%A: memref<64xf32>, %s: memref<1xi32>) {
  %tmp = memref.alloca() {polygeist.varname = "v"} : memref<1xf32>
  %cast = memref.cast %tmp : memref<1xf32> to memref<?xf32>
  %scast = memref.cast %s : memref<1xi32> to memref<?xi32>
  affine.for %i = 0 to 32 {
    %a = affine.load %A[%i * 2] : memref<64xf32>
    affine.store %a, %tmp[0] : memref<1xf32>
    func.call @write(%scast, %cast) : (memref<?xi32>, memref<?xf32>) -> ()
    %b = affine.load %A[%i * 2 + 1] : memref<64xf32>
    affine.store %b, %tmp[0] : memref<1xf32>
    func.call @write(%scast, %cast) : (memref<?xi32>, memref<?xf32>) -> ()
  } {hls.pipeline = [{II = 1 : i32}]}
  return
}
