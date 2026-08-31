// RUN: hls-est %s --lower-polygeist-subindex -o - | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex --memory-banking-bram -o - 2>&1 | FileCheck %s --check-prefix=BANK

// `s >> Q[i][j]` and `s << Q[i][j]`: cgeist passes the element by reference
// to the bodiless hls::stream method as a `polygeist.subindex` view down to
// a pointer to the element. --lower-polygeist-subindex turns that view into
// a one-element temporary (cgeist's own idiom for a scalar by reference)
// plus an access of the element: a stream read stores the element after the
// call, a stream write loads it before. The array is then an ordinary
// banked memory: its partition pragma applies (VITIS_NOTES N47:
// karthikeya_sharma lab_2 `static Q_BRAM[100][128]`, `complete dim=2`,
// Vitis 128 banks; before, "array_partition not applied: ... used by
// polygeist.subindex").

module {
  func.func private @_ZN3hls6streamIsLi0EErsERS_(memref<?xi32>, memref<?xi16>)
  func.func private @_ZN3hls6streamIsLi0EElsERKs(memref<?xi32>, memref<?xi16>)
  memref.global "private" @Q : memref<8x4xi16> = dense<0> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "Q"}]}

  // CHECK-LABEL: func.func @top
  // CHECK-DAG: %[[WTMP:.*]] = memref.alloca() : memref<1xi16>
  // CHECK-DAG: %[[WVIEW:.*]] = memref.cast %[[WTMP]] : memref<1xi16> to memref<?xi16>
  // CHECK-DAG: %[[RTMP:.*]] = memref.alloca() : memref<1xi16>
  // CHECK-DAG: %[[RVIEW:.*]] = memref.cast %[[RTMP]] : memref<1xi16> to memref<?xi16>
  // CHECK: affine.for %[[I:.*]] = 0 to 8 {
  // CHECK: affine.for %[[J:.*]] = 0 to 4 {
  // CHECK: call @_ZN3hls6streamIsLi0EErsERS_(%arg0, %[[RVIEW]])
  // CHECK-NEXT: %[[V:.*]] = affine.load %[[RTMP]][%{{.*}}] : memref<1xi16>
  // CHECK-NEXT: affine.store %[[V]], %{{.*}}[%[[I]], %[[J]]] : memref<8x4xi16>
  // CHECK: %[[W:.*]] = affine.load %{{.*}}[%[[I]], %[[J]]] : memref<8x4xi16>
  // CHECK-NEXT: affine.store %[[W]], %[[WTMP]][%{{.*}}] : memref<1xi16>
  // CHECK-NEXT: call @_ZN3hls6streamIsLi0EElsERKs(%arg1, %[[WVIEW]])
  // CHECK-NOT: polygeist.subindex
  func.func @top(%in: memref<?xi32>, %out: memref<?xi32>) {
    %q = memref.get_global @Q : memref<8x4xi16>
    affine.for %i = 0 to 8 {
      %row = "polygeist.subindex"(%q, %i) : (memref<8x4xi16>, index) -> memref<4xi16>
      affine.for %j = 0 to 4 {
        %e = "polygeist.subindex"(%row, %j) : (memref<4xi16>, index) -> memref<?xi16>
        func.call @_ZN3hls6streamIsLi0EErsERS_(%in, %e) : (memref<?xi32>, memref<?xi16>) -> ()
        func.call @_ZN3hls6streamIsLi0EElsERKs(%out, %e) : (memref<?xi32>, memref<?xi16>) -> ()
      }
    }
    return
  }
}

// Four banks, no warning.
// BANK-NOT: array_partition not applied
// BANK-COUNT-4: memref.global "private" @Q_bank_{{[0-3]}} : memref<8x1xi16>
// BANK-NOT: array_partition not applied
