// RUN: hls-est %s --memory-banking-bram | FileCheck %s

// A parameter's pragma partitions the arrays that reach it, transitively, and
// only those (VITIS_NOTES.md N17 (b), N24): @ld fills SA, which reaches @g's
// partitioned parameter, and SC, which does not. SA is split in two, SC stays
// one array, and @ld gets one form per argument partition, as Vitis clones a
// callee per argument form (N14 R4; forgebench diff_orders_module: the call
// that fills the unpartitioned BRAM_C3 is a function of its own).

// CHECK-LABEL: func.func private @g(
// CHECK-SAME: memref<128xi32> {{{.*}}hls.bank_index = 0
// CHECK-SAME: memref<128xi32> {{{.*}}hls.bank_index = 1
func.func private @g(%a: memref<256xi32> {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}]}, %o: memref<256xi32>) attributes {hls.inline_off} {
  affine.for %i = 0 to 256 {
    %0 = affine.load %a[%i] : memref<256xi32>
    affine.store %0, %o[%i] : memref<256xi32>
  }
  return
}

func.func private @ld(%src: memref<256xi32>, %dst: memref<256xi32>) attributes {hls.inline_off} {
  affine.for %i = 0 to 256 {
    %0 = affine.load %src[%i] : memref<256xi32>
    affine.store %0, %dst[%i] : memref<256xi32>
  }
  return
}

// The form of @ld for SA: the destination split like SA.
// CHECK-LABEL: func.func private @ld(%{{.*}}: memref<256xi32>, %{{.*}}: memref<128xi32> {{.*}}, %{{.*}}: memref<128xi32> {{.*}})

// The form of @ld for SC (a clone, after the original): one unsplit parameter.
// CHECK-LABEL: func.func private @ld_form1(%{{.*}}: memref<256xi32>, %{{.*}}: memref<256xi32>)

// CHECK-LABEL: func.func @sideways
// CHECK: %[[A0:.*]] = memref.alloca() {{.*}}hls.bank_of = "SA"{{.*}} : memref<128xi32>
// CHECK: %[[A1:.*]] = memref.alloca() {{.*}}hls.bank_of = "SA"{{.*}} : memref<128xi32>
// CHECK: %[[C:.*]] = memref.alloca() {polygeist.varname = "SC"} : memref<256xi32>
// CHECK: call @ld(%arg0, %[[A0]], %[[A1]])
// CHECK: call @ld_form1(%arg0, %[[C]])
// CHECK: call @g(%[[A0]], %[[A1]], %arg1)
// CHECK: call @g(%[[A0]], %[[A1]], %arg1)
func.func @sideways(%in: memref<256xi32>, %out: memref<256xi32>) {
  %a = memref.alloca() {polygeist.varname = "SA"} : memref<256xi32>
  %c = memref.alloca() {polygeist.varname = "SC"} : memref<256xi32>
  call @ld(%in, %a) : (memref<256xi32>, memref<256xi32>) -> ()
  call @ld(%in, %c) : (memref<256xi32>, memref<256xi32>) -> ()
  call @g(%a, %out) : (memref<256xi32>, memref<256xi32>) -> ()
  affine.for %i = 0 to 256 {
    %0 = affine.load %c[%i] : memref<256xi32>
    affine.store %0, %out[%i] : memref<256xi32>
  }
  call @g(%a, %out) : (memref<256xi32>, memref<256xi32>) -> ()
  return
}
