// RUN: hls-est %s --lower-polygeist-subindex -o - 2> %t.err | FileCheck %s
// RUN: FileCheck %s --input-file=%t.err --check-prefix=WARN
// RUN: hls-est %s --lower-polygeist-subindex --bram-analysis=top=rows -o /dev/null | FileCheck %s --check-prefix=BRAM

// cgeist passes a row of a 2-D array by reference as `polygeist.subindex`
// (OPEN_ISSUES.md O25). --lower-polygeist-subindex removes the op:
//   - a load / store through the view indexes the whole array (the row as
//     an affine dim when it is a loop counter, a symbol when it is a
//     function argument, otherwise through memref ops);
//   - a call passing the view goes to a clone of the callee that takes the
//     whole array and the row, one clone per argument form, shared by every
//     call of that form (Vitis clones `work` into `work.1` per array
//     argument form, VITIS_NOTES.md N14 R4; inl_c10: two forms, 10 BRAM);
//     a partition pragma of the row parameter moves to the whole array with
//     its dimension shifted;
//   - the original callee is erased when private and no call is left.
// A view that is not a row of a static array stays, with a warning.

// CHECK-LABEL: func.func private @work_row_0(
// CHECK-SAME:    %[[A:.*]]: memref<4x1024xi32> {hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic"}]}, %[[K:.*]]: index, %[[O:.*]]: memref<1024xi32>)
// CHECK-SAME:    attributes {hls.inline_off, hls.orig_name = "work"}
// CHECK:         memref.alloca
// CHECK:         affine.load %[[A]][symbol(%[[K]]), %{{.*}}] : memref<4x1024xi32>
// CHECK:         affine.store %{{.*}}, %[[O]][%{{.*}}] : memref<1024xi32>
// CHECK-LABEL: func.func private @work_row_1(
// CHECK-SAME:    %{{.*}}: memref<1024xi32> {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}]}, %[[B:.*]]: memref<4x1024xi32>, %[[L:.*]]: index)
// CHECK:         affine.store %{{.*}}, %[[B]][symbol(%[[L]]), %{{.*}}] : memref<4x1024xi32>
// CHECK-NOT:   func.func private @work(
// CHECK-LABEL: func.func @rows
// CHECK:         affine.for %[[I:.*]] = 0 to 4 {
// CHECK-NEXT:      call @work_row_0(%{{.*}}, %[[I]], %{{.*}}) : (memref<4x1024xi32>, index, memref<1024xi32>) -> ()
// CHECK-NEXT:      call @work_row_1(%{{.*}}, %{{.*}}, %[[I]]) : (memref<1024xi32>, memref<4x1024xi32>, index) -> ()
// CHECK-NEXT:      call @work_row_0(%{{.*}}, %[[I]], %{{.*}}) : (memref<4x1024xi32>, index, memref<1024xi32>) -> ()
// CHECK-NOT:     polygeist.subindex
// CHECK-LABEL: func.func @direct
// CHECK:         affine.for %[[J:.*]] = 0 to 4 {
// CHECK-NEXT:      affine.for %[[M:.*]] = 0 to 1024 {
// CHECK-NEXT:        %[[V:.*]] = affine.load %{{.*}}[%[[J]], %[[M]]] : memref<4x1024xi32>
// CHECK-NEXT:        affine.store %[[V]], %{{.*}}[%[[J]], -%[[M]] + 1023] : memref<4x1024xi32>
// CHECK-NOT:     polygeist.subindex
// CHECK-LABEL: func.func @nonaffine
// CHECK:         affine.for %[[J2:.*]] = 0 to 4 {
// CHECK-NEXT:      %[[R:.*]] = affine.load %{{.*}}[%[[J2]]] : memref<4xindex>
// CHECK-NEXT:      affine.for %[[N:.*]] = 0 to 1024 {
// CHECK-NEXT:        %[[IDX:.*]] = affine.apply #{{.*}}(%[[N]])
// CHECK-NEXT:        memref.load %{{.*}}[%[[R]], %[[IDX]]] : memref<4x1024xi32>
// CHECK-NOT:     polygeist.subindex
// CHECK-LABEL: func.func @offset
// CHECK:         "polygeist.subindex"
// CHECK-LABEL: func.func @nested_top
// CHECK:           call @mid_row_0(%{{.*}}, %{{.*}}) : (memref<4x1024xi32>, index) -> ()
// CHECK-LABEL: func.func private @mid_row_0(
// CHECK-NOT:     polygeist.subindex
// CHECK:           call @leaf_row_0_1(%{{.*}}, %{{.*}}, %{{.*}}, %{{.*}}) : (memref<4x1024xi32>, index, memref<4x1024xi32>, index) -> ()
// CHECK-NOT:   polygeist.subindex
// CHECK-NOT:   func.func private @mid(
// CHECK-NOT:   func.func private @leaf_row_0(
// CHECK:       func.func private @leaf_row_0_1(
// CHECK-NOT:   func.func private @leaf(
// WARN: warning: polygeist.subindex not lowered: not a row of a static-shape array

// The clones are two modules, each with its own local array (inl_c10: work
// and work.1, 4 + 4), plus the caller's 2 (1024x32).
// BRAM: Total BRAM: 6

module {
  func.func private @work(%in: memref<1024xi32> {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}]}, %out: memref<1024xi32>) attributes {hls.inline_off, hls.orig_name = "work"} {
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
  func.func @rows(%a: memref<4x1024xi32>, %b: memref<4x1024xi32>) {
    %t = memref.alloca() {polygeist.varname = "t"} : memref<1024xi32>
    affine.for %k = 0 to 4 {
      %ra = "polygeist.subindex"(%a, %k) : (memref<4x1024xi32>, index) -> memref<1024xi32>
      %rb = "polygeist.subindex"(%b, %k) : (memref<4x1024xi32>, index) -> memref<1024xi32>
      func.call @work(%ra, %t) : (memref<1024xi32>, memref<1024xi32>) -> ()
      func.call @work(%t, %rb) : (memref<1024xi32>, memref<1024xi32>) -> ()
      func.call @work(%ra, %t) : (memref<1024xi32>, memref<1024xi32>) -> ()
    }
    return
  }
  func.func @direct(%a: memref<4x1024xi32>, %b: memref<4x1024xi32>) {
    affine.for %j = 0 to 4 {
      %ra = "polygeist.subindex"(%a, %j) : (memref<4x1024xi32>, index) -> memref<1024xi32>
      %rb = "polygeist.subindex"(%b, %j) : (memref<4x1024xi32>, index) -> memref<1024xi32>
      affine.for %m = 0 to 1024 {
        %v = affine.load %ra[%m] : memref<1024xi32>
        affine.store %v, %rb[1023 - %m] : memref<1024xi32>
      }
    }
    return
  }
  // The row comes from memory inside a loop: neither an affine dim nor a
  // symbol, so the access goes through memref ops.
  func.func @nonaffine(%a: memref<4x1024xi32>, %o: memref<4x1024xi32>, %rows: memref<4xindex>) {
    affine.for %j = 0 to 4 {
      %r = affine.load %rows[%j] : memref<4xindex>
      %row = "polygeist.subindex"(%a, %r) : (memref<4x1024xi32>, index) -> memref<1024xi32>
      affine.for %n = 0 to 1024 {
        %v = affine.load %row[1023 - %n] : memref<1024xi32>
        affine.store %v, %o[%j, %n] : memref<4x1024xi32>
      }
    }
    return
  }
  func.func @offset(%a: memref<?xi32>, %i: index) -> i32 {
    %p = "polygeist.subindex"(%a, %i) : (memref<?xi32>, index) -> memref<?xi32>
    %v = affine.load %p[0] : memref<?xi32>
    return %v : i32
  }
  // A clone made before the callee's own views were lowered (the caller
  // comes first in the module): the clone's copy of @mid's row argument to
  // @leaf is lowered too. In the clone both arguments of @leaf are rows
  // (@mid's parameter is one now), so it calls @leaf_row_0_1; @mid's own
  // call got @leaf_row_0, which no call reaches once @mid is gone and is
  // erased with it.
  func.func @nested_top(%a: memref<4x1024xi32>) {
    affine.for %k = 0 to 4 {
      %ra = "polygeist.subindex"(%a, %k) : (memref<4x1024xi32>, index) -> memref<1024xi32>
      func.call @mid(%ra) : (memref<1024xi32>) -> ()
    }
    return
  }
  func.func private @mid(%r: memref<1024xi32>) attributes {hls.inline_off} {
    %loc = memref.alloca() : memref<4x1024xi32>
    affine.for %j = 0 to 4 {
      %rl = "polygeist.subindex"(%loc, %j) : (memref<4x1024xi32>, index) -> memref<1024xi32>
      func.call @leaf(%rl, %r) : (memref<1024xi32>, memref<1024xi32>) -> ()
    }
    return
  }
  func.func private @leaf(%x: memref<1024xi32>, %y: memref<1024xi32>) attributes {hls.inline_off} {
    affine.for %n = 0 to 1024 {
      %v = affine.load %y[%n] : memref<1024xi32>
      affine.store %v, %x[%n] : memref<1024xi32>
    }
    return
  }
}
