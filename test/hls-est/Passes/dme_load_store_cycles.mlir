// RUN: hls-est %s --dead-memory-elimination | FileCheck %s
// RUN: hls-est %s --dead-memory-elimination=load-store-cycles=false | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --config-set=tool.hls.middle_end.dead_memory.load_store_cycles=false --dead-memory-elimination | FileCheck %s --check-prefix=OFF

// VITIS_NOTES.md N66 (kernels w9r8p_dm_* and w9r8i_dm_*, td=off): Vitis
// deletes a store only once its array has no used load, so an array whose
// loads feed stores into itself (directly, through another array, or as the
// condition of the store) is kept although nothing it holds leaves the design;
// an array whose loads reach nothing, and a write-only array, are removed.

// dm_self (Vitis 8): cnt[k] = cnt[k] + 1.
// CHECK-LABEL: func.func @self
// CHECK: memref.alloca() {hls.kept_reason = "kept: its loads feed stores into itself (Vitis
// CHECK-SAME: N66)", polygeist.varname = "cnt"}
// OFF-LABEL: func.func @self
// OFF-NOT: memref.alloca
// OFF: return
func.func @self(%u: memref<1024xi32>, %out: memref<256xi32>) {
  %c1 = arith.constant 1 : i32
  %m = arith.constant 4095 : i32
  %c0 = arith.constant 0 : i32
  %cnt = memref.alloca() {polygeist.varname = "cnt"} : memref<4096xi32>
  affine.for %i = 0 to 4096 {
    affine.store %c0, %cnt[%i] : memref<4096xi32>
  }
  affine.for %i = 0 to 1024 {
    %x = affine.load %u[%i] : memref<1024xi32>
    %a = arith.andi %x, %m : i32
    %k = arith.index_cast %a : i32 to index
    %e = memref.load %cnt[%k] : memref<4096xi32>
    %e1 = arith.addi %e, %c1 : i32
    memref.store %e1, %cnt[%k] : memref<4096xi32>
  }
  return
}

// dm_cyc2 (Vitis 16): b[k] = a[k] + 1; a[k] = b[k] + 2.
// CHECK-LABEL: func.func @cycle_two
// CHECK-DAG: hls.kept_reason = "kept: its loads feed stores into itself through other arrays{{.*}}polygeist.varname = "a"
// CHECK-DAG: hls.kept_reason = "kept: its loads feed stores into itself through other arrays{{.*}}polygeist.varname = "b"
// OFF-LABEL: func.func @cycle_two
// OFF-NOT: memref.alloca
// OFF: return
func.func @cycle_two(%u: memref<1024xi32>) {
  %c1 = arith.constant 1 : i32
  %m = arith.constant 4095 : i32
  %a = memref.alloca() {polygeist.varname = "a"} : memref<4096xi32>
  %b = memref.alloca() {polygeist.varname = "b"} : memref<4096xi32>
  affine.for %i = 0 to 1024 {
    %x = affine.load %u[%i] : memref<1024xi32>
    %y = arith.andi %x, %m : i32
    %k = arith.index_cast %y : i32 to index
    %e = memref.load %a[%k] : memref<4096xi32>
    %f = memref.load %b[%k] : memref<4096xi32>
    %e1 = arith.addi %e, %c1 : i32
    memref.store %e1, %b[%k] : memref<4096xi32>
    memref.store %f, %a[%k] : memref<4096xi32>
  }
  return
}

// dm_ctl (Vitis 8): if (cnt[k] > 7) cnt[k] = i.
// CHECK-LABEL: func.func @control
// CHECK: memref.alloca() {hls.kept_reason
// OFF-LABEL: func.func @control
// OFF-NOT: memref.alloca
// OFF: return
func.func @control(%u: memref<1024xi32>) {
  %c7 = arith.constant 7 : i32
  %m = arith.constant 4095 : i32
  %cnt = memref.alloca() {polygeist.varname = "cnt"} : memref<4096xi32>
  affine.for %i = 0 to 1024 {
    %x = affine.load %u[%i] : memref<1024xi32>
    %y = arith.andi %x, %m : i32
    %k = arith.index_cast %y : i32 to index
    %e = memref.load %cnt[%k] : memref<4096xi32>
    %c = arith.cmpi sgt, %e, %c7 : i32
    scf.if %c {
      memref.store %x, %cnt[%k] : memref<4096xi32>
    }
  }
  return
}

// dm_feed (Vitis 16): cnt[k] = cnt[k] + src[k]: src only feeds the kept cnt.
// CHECK-LABEL: func.func @feed
// CHECK: hls.kept_reason{{.*}}polygeist.varname = "cnt"
// CHECK: memref.alloca() {polygeist.varname = "src"}
func.func @feed(%u: memref<1024xi32>) {
  %m = arith.constant 4095 : i32
  %cnt = memref.alloca() {polygeist.varname = "cnt"} : memref<4096xi32>
  %src = memref.alloca() {polygeist.varname = "src"} : memref<4096xi32>
  affine.for %i = 0 to 1024 {
    %x = affine.load %u[%i] : memref<1024xi32>
    %y = arith.andi %x, %m : i32
    %k = arith.index_cast %y : i32 to index
    memref.store %x, %src[%k] : memref<4096xi32>
    %e = memref.load %cnt[%k] : memref<4096xi32>
    %s = memref.load %src[%k] : memref<4096xi32>
    %e1 = arith.addi %e, %s : i32
    memref.store %e1, %cnt[%k] : memref<4096xi32>
  }
  return
}

// dm_rd / dm_dyn (Vitis 0): a load whose value reaches nothing, and a store
// of a value that does not come from the array, keep nothing.
// CHECK-LABEL: func.func @unused_load
// CHECK-NOT: memref.alloca
// CHECK: return
func.func @unused_load(%u: memref<1024xi32>) {
  %m = arith.constant 4095 : i32
  %cnt = memref.alloca() {polygeist.varname = "cnt"} : memref<4096xi32>
  %s0 = arith.constant 0 : i32
  %r = affine.for %i = 0 to 1024 iter_args(%s = %s0) -> (i32) {
    %x = affine.load %u[%i] : memref<1024xi32>
    %y = arith.andi %x, %m : i32
    %k = arith.index_cast %y : i32 to index
    memref.store %x, %cnt[%k] : memref<4096xi32>
    %e = memref.load %cnt[%k] : memref<4096xi32>
    %s1 = arith.addi %s, %e : i32
    affine.yield %s1 : i32
  }
  return
}

// dm_sroa (Vitis 1: only hist, with its own update): `cnt` (2 elements, at
// most complete_threshold) is registers in Vitis, so the cycle
// `cnt[0] += hist[i]` through it is dead and its loads of hist go with it.
// CHECK-LABEL: func.func @scalarised
// CHECK: memref.alloca() {hls.kept_reason{{.*}}polygeist.varname = "hist"}
// CHECK-NOT: memref.alloca
// CHECK-NOT: affine.load %{{.*}}[%{{.*}}] : memref<256xi32>
// CHECK: return
func.func @scalarised(%u: memref<1024xi32>) {
  %c1 = arith.constant 1 : i32
  %c0 = arith.constant 0 : i32
  %m = arith.constant 255 : i32
  %hist = memref.alloca() {polygeist.varname = "hist"} : memref<256xi32>
  %cnt = memref.alloca() {polygeist.varname = "cnt"} : memref<2xi32>
  affine.for %i = 0 to 1024 {
    %x = affine.load %u[%i] : memref<1024xi32>
    %y = arith.andi %x, %m : i32
    %k = arith.index_cast %y : i32 to index
    %e = memref.load %hist[%k] : memref<256xi32>
    %e1 = arith.addi %e, %c1 : i32
    memref.store %e1, %hist[%k] : memref<256xi32>
  }
  affine.for %i = 0 to 2 {
    affine.store %c0, %cnt[%i] : memref<2xi32>
  }
  affine.for %i = 0 to 256 {
    %a = affine.load %cnt[0] : memref<2xi32>
    %h = affine.load %hist[%i] : memref<256xi32>
    %s = arith.addi %a, %h : i32
    affine.store %s, %cnt[0] : memref<2xi32>
  }
  return
}

// dm_acc0 (Vitis 0): `q[s][o] = 0; for d: q[s][o] += x * w`: LICM keeps the
// accumulator in a register and its value before the loop is the 0 just
// stored, so no load of q remains (forgebench attention Q / K).
// CHECK-LABEL: func.func @accumulator_initialised
// CHECK-NOT: memref.alloca
// CHECK: return
func.func @accumulator_initialised(%u: memref<1024xi32>) {
  %c0 = arith.constant 0 : i32
  %q = memref.alloca() {polygeist.varname = "q"} : memref<16x64xi32>
  affine.for %s = 0 to 16 {
    affine.for %o = 0 to 64 {
      affine.store %c0, %q[%s, %o] : memref<16x64xi32>
      affine.for %d = 0 to 64 {
        %x = affine.load %u[%s * 64 + %d] : memref<1024xi32>
        %a = affine.load %q[%s, %o] : memref<16x64xi32>
        %b = arith.addi %a, %x : i32
        affine.store %b, %q[%s, %o] : memref<16x64xi32>
      }
    }
  }
  return
}

// dm_accn (Vitis 2, q kept): the same accumulation of an element an earlier
// loop nest wrote: the load before the promoted loop stays, a real cycle.
// CHECK-LABEL: func.func @accumulator_filled_earlier
// CHECK: memref.alloca() {hls.kept_reason{{.*}}polygeist.varname = "q"}
func.func @accumulator_filled_earlier(%u: memref<1024xi32>) {
  %q = memref.alloca() {polygeist.varname = "q"} : memref<16x64xi32>
  affine.for %s = 0 to 16 {
    affine.for %o = 0 to 64 {
      %x = affine.load %u[%s + %o] : memref<1024xi32>
      affine.store %x, %q[%s, %o] : memref<16x64xi32>
    }
  }
  affine.for %s = 0 to 16 {
    affine.for %o = 0 to 64 {
      affine.for %d = 0 to 64 {
        %x = affine.load %u[%s * 64 + %d] : memref<1024xi32>
        %a = affine.load %q[%s, %o] : memref<16x64xi32>
        %b = arith.addi %a, %x : i32
        affine.store %b, %q[%s, %o] : memref<16x64xi32>
      }
    }
  }
  return
}
