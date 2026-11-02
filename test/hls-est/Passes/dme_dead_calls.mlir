// RUN: hls-est %s --dead-memory-elimination | FileCheck %s
// RUN: hls-est %s --dead-memory-elimination=dead-calls=false | FileCheck %s --check-prefix=OFF

// Calls of a non-inlined callee whose written arrays nothing reads
// (VITIS_NOTES.md N17 (a) / (d), N25):
//   @single  the only call of @fill1 writes D, never read: Vitis deletes the
//            call and D (fbh3_g_callee_wr; forgebench diff_orders_module
//            BRAM_A3 / BRAM_B3).
//   @shared  @fill2 also fills the live A: the dead call stays and L is kept
//            at its full cost as RAM_AUTO_0R0W (w7_dl_local, w7_dl_global,
//            tiled_attn_module BRAM_A2 / A3).
//   @forms   @fill3 fills P, which reaches @g's partitioned parameter, and the
//            unread U: the two calls are different forms of @fill3 (N14 R4),
//            so the call for U is the only call of its form and goes
//            (diff_orders_module BRAM_C3).

// CHECK: hls.dead_memrefs = [{{.*}}name = "D", reason = "write-only: never read (0 store(s)); its writer, the call of @fill1 at {{.*}} was deleted: no array it writes is read and no call of the same form is live

func.func private @fill1(%in: memref<1024xi32>, %a: memref<1024xi32>) attributes {hls.inline_off} {
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %a[%i] : memref<1024xi32>
  }
  return
}
func.func private @fill2(%in: memref<1024xi32>, %a: memref<1024xi32>) attributes {hls.inline_off} {
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %a[%i] : memref<1024xi32>
  }
  return
}
func.func private @fill3(%in: memref<1024xi32>, %a: memref<1024xi32>) attributes {hls.inline_off} {
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %a[%i] : memref<1024xi32>
  }
  return
}
func.func private @g(%a: memref<1024xi32> {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}]}, %o: memref<1024xi32>) attributes {hls.inline_off} {
  affine.for %i = 0 to 1024 {
    %0 = affine.load %a[%i] : memref<1024xi32>
    affine.store %0, %o[%i] : memref<1024xi32>
  }
  return
}

// CHECK-LABEL: func.func @single
// CHECK-NOT: call @fill1
// CHECK-NOT: polygeist.varname = "D"
// CHECK: return
// OFF-LABEL: func.func @single
// OFF: call @fill1
func.func @single(%in: memref<1024xi32>, %out: memref<1024xi32>) {
  %d = memref.alloca() {polygeist.varname = "D"} : memref<1024xi32>
  call @fill1(%in, %d) : (memref<1024xi32>, memref<1024xi32>) -> ()
  return
}

// CHECK-LABEL: func.func @shared
// CHECK-DAG: memref.alloca() {polygeist.varname = "A"}
// CHECK-DAG: memref.alloca() {hls.kept_reason = "kept: never read, written by a call of @fill2, which has another live call site of the same form; {{.*}}", polygeist.varname = "L"}
// CHECK: call @fill2
// CHECK: call @fill2
func.func @shared(%in: memref<1024xi32>, %out: memref<1024xi32>) {
  %a = memref.alloca() {polygeist.varname = "A"} : memref<1024xi32>
  %l = memref.alloca() {polygeist.varname = "L"} : memref<1024xi32>
  call @fill2(%in, %a) : (memref<1024xi32>, memref<1024xi32>) -> ()
  call @fill2(%in, %l) : (memref<1024xi32>, memref<1024xi32>) -> ()
  affine.for %i = 0 to 1024 {
    %0 = affine.load %a[%i] : memref<1024xi32>
    affine.store %0, %out[%i] : memref<1024xi32>
  }
  return
}

// CHECK-LABEL: func.func @forms
// CHECK: polygeist.varname = "P"
// CHECK-NOT: polygeist.varname = "U"
// CHECK: call @fill3
// CHECK-NOT: call @fill3
// CHECK: call @g
func.func @forms(%in: memref<1024xi32>, %out: memref<1024xi32>) {
  %p = memref.alloca() {polygeist.varname = "P"} : memref<1024xi32>
  %u = memref.alloca() {polygeist.varname = "U"} : memref<1024xi32>
  call @fill3(%in, %p) : (memref<1024xi32>, memref<1024xi32>) -> ()
  call @fill3(%in, %u) : (memref<1024xi32>, memref<1024xi32>) -> ()
  call @g(%p, %out) : (memref<1024xi32>, memref<1024xi32>) -> ()
  return
}
