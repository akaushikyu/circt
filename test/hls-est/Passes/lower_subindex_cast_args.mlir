// RUN: hls-est %s --lower-polygeist-subindex -o - | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex --memory-banking-bram -o - 2>&1 | FileCheck %s --check-prefix=BANK

// A static array passed to a pointer parameter (`void load(int *dst)`
// called as `load(buf)`): cgeist casts it to `memref<?xT>`, which the
// banking cannot follow, so a partition pragma on `buf` was dropped ("used
// by memref.cast"). --lower-polygeist-subindex specialises the callee per
// static argument form (Vitis specialises per argument form, N14 R4): the
// clone's parameter has the array's static type, and a use that needs the
// pointer (a further call) gets its own cast, specialised in the next
// round. VITIS_NOTES N47: zijun_wang lab3's statics, `cyclic factor=32`,
// filled through `load_matrix_data16(ap_fixed<16,5> *dst, ...)`, are 32
// banks in Vitis.

module {
  memref.global "private" @buf : memref<64xi32> = dense<0> {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "buf"}]}

  // CHECK-LABEL: func.func private @fill(
  // CHECK-SAME: memref<?xi32>
  func.func private @fill(%dst: memref<?xi32>, %src: memref<?xi32>) attributes {hls.inline_auto_off = {size = 10 : i64}} {
    affine.for %i = 0 to 64 {
      %v = affine.load %src[%i] : memref<?xi32>
      affine.store %v, %dst[%i] : memref<?xi32>
    }
    return
  }
  // CHECK-LABEL: func.func private @fill_static(
  // CHECK-SAME: %[[A:.*]]: memref<64xi32>
  // CHECK: affine.store %{{.*}}, %[[A]][%{{.*}}] : memref<64xi32>

  // A pointer passed on: the inner call gets its own specialisation (the
  // cast the clone needed for it goes once the call is redirected), and the
  // original, now unused, is erased.
  // CHECK-NOT: func.func private @outer(
  func.func private @outer(%dst: memref<?xi32>, %src: memref<?xi32>) attributes {hls.inline_auto_off = {size = 10 : i64}} {
    func.call @fill(%dst, %src) : (memref<?xi32>, memref<?xi32>) -> ()
    return
  }
  // CHECK-LABEL: func.func private @outer_static(
  // CHECK-SAME: %[[D:.*]]: memref<64xi32>
  // CHECK: call @fill_static(%[[D]], %{{.*}}) : (memref<64xi32>, memref<?xi32>) -> ()

  // CHECK-LABEL: func.func @top(
  // CHECK: %[[G:.*]] = memref.get_global @buf : memref<64xi32>
  // CHECK: call @fill_static(%[[G]], %arg0) : (memref<64xi32>, memref<?xi32>) -> ()
  // CHECK: call @outer_static(%[[G]], %arg0) : (memref<64xi32>, memref<?xi32>) -> ()
  // The interface pointer is never specialised: it is no cast of a static
  // array.
  // CHECK: call @fill(%arg1, %arg0) : (memref<?xi32>, memref<?xi32>) -> ()
  func.func @top(%in: memref<?xi32>, %out: memref<?xi32>) {
    %g = memref.get_global @buf : memref<64xi32>
    %c = memref.cast %g : memref<64xi32> to memref<?xi32>
    func.call @fill(%c, %in) : (memref<?xi32>, memref<?xi32>) -> ()
    func.call @outer(%c, %in) : (memref<?xi32>, memref<?xi32>) -> ()
    func.call @fill(%out, %in) : (memref<?xi32>, memref<?xi32>) -> ()
    return
  }
}

// The partition now applies: four banks, the specialised callee takes them.
// BANK-NOT: array_partition not applied
// BANK-COUNT-4: memref.global "private" @buf_bank_{{[0-3]}} : memref<16xi32>
// BANK-NOT: array_partition not applied
