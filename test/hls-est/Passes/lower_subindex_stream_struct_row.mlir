// RUN: hls-est %s --lower-polygeist-subindex -o - | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex --split-struct-memrefs --memory-banking-bram -o - 2>&1 | FileCheck %s --check-prefix=BANK

// `s >> P[i]` and `s << P[i]` on an array of structs whose members share one
// type (`struct P2 { short a, b; } P[2048]`, cgeist's memref<2048x2xi16>):
// the stream method gets the whole row (memref<?x2xi16>). Like a scalar
// element (lower_subindex_stream_element.mlir), the row becomes a temporary
// (memref<1x2xi16>, cgeist's idiom for a struct by reference) copied member
// by member: a read stores both members after the call, a write loads both
// before it; every member is read before any is written. The array's
// accesses are then visible and its partition pragma applies (W9 round 6
// review defect 4, kernel w9r6rev n47b: before, "accesses not attributed").
// Vitis also splits such an array into one memory per member (P.a, P.b, each
// cyclic 2: four 1024x16 banks); hls-est keeps the members as one more
// dimension of one memory (OPEN_ISSUES O54 (h)), so the banks below are
// 1024x2.

module {
  func.func private @_ZN3hls6streamI2P2Li0EErsERS1_(memref<?xi32>, memref<?x2xi16>)
  func.func private @_ZN3hls6streamI2P2Li0EElsERKS1_(memref<?xi32>, memref<?x2xi16>)
  memref.global "private" @P : memref<2048x2xi16> = uninitialized {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "P"}]}

  // CHECK-LABEL: func.func @top
  // CHECK-COUNT-2: memref.cast %{{.*}} : memref<1x2xi16> to memref<?x2xi16>
  // CHECK: affine.for %[[I:.*]] = 0 to 2048 {
  // CHECK: call @_ZN3hls6streamI2P2Li0EErsERS1_(%arg0, %{{.*}})
  // CHECK: %[[A:.*]] = affine.load %{{.*}} : memref<1x2xi16>
  // CHECK-NEXT: %[[B:.*]] = affine.load %{{.*}} : memref<1x2xi16>
  // CHECK-NEXT: affine.store %[[A]], %{{.*}}[%[[I]], %{{.*}}] : memref<2048x2xi16>
  // CHECK-NEXT: affine.store %[[B]], %{{.*}}[%[[I]], %{{.*}}] : memref<2048x2xi16>
  // CHECK: affine.for
  // CHECK: affine.load %{{.*}} : memref<2048x2xi16>
  // CHECK-NEXT: affine.load %{{.*}} : memref<2048x2xi16>
  // CHECK-NEXT: affine.store %{{.*}} : memref<1x2xi16>
  // CHECK-NEXT: affine.store %{{.*}} : memref<1x2xi16>
  // CHECK-NEXT: call @_ZN3hls6streamI2P2Li0EElsERKS1_
  // CHECK-NOT: polygeist.subindex
  func.func @top(%in: memref<?xi32>, %out: memref<?xi32>) {
    %p = memref.get_global @P : memref<2048x2xi16>
    affine.for %i = 0 to 2048 {
      %e = "polygeist.subindex"(%p, %i) : (memref<2048x2xi16>, index) -> memref<?x2xi16>
      func.call @_ZN3hls6streamI2P2Li0EErsERS1_(%in, %e) : (memref<?xi32>, memref<?x2xi16>) -> ()
    }
    affine.for %i = 0 to 2048 {
      %e = "polygeist.subindex"(%p, %i) : (memref<2048x2xi16>, index) -> memref<?x2xi16>
      func.call @_ZN3hls6streamI2P2Li0EElsERKS1_(%out, %e) : (memref<?xi32>, memref<?x2xi16>) -> ()
    }
    return
  }
}

// Two banks, no warning.
// BANK-NOT: array_partition not applied
// BANK-COUNT-2: memref.global "private" @P_bank_{{[01]}} : memref<1024x2xi16>
// BANK-NOT: array_partition not applied
