// RUN: hls-est %s --dead-memory-elimination | FileCheck %s
// RUN: hls-est %s --dead-memory-elimination=overwritten-stores=false | FileCheck %s --check-prefix=NODSE

// --dead-memory-elimination (VITIS_NOTES.md N1a, dead_globals.md R1/R2/R6):
// an array whose loads never reach a side effect that leaves the function is
// removed together with the computation that only fed it; a live array is
// never touched, whatever its attributes.

// (a) dg_a_writeonly: `dead` is only written -> removed; `buf` reaches `out`.
// CHECK-LABEL: func.func @write_only
// CHECK: memref.alloca() {hls.preserve, polygeist.varname = "buf"}
// CHECK-NOT: "dead"
// CHECK: return
func.func @write_only(%in: memref<512xi32>, %out: memref<512xi32>) {
  %buf = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<512xi32>
  %dead = memref.alloca() {hls.preserve, polygeist.varname = "dead"} : memref<512xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %buf[%i] : memref<512xi32>
    affine.store %v, %dead[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %buf[511 - %i] : memref<512xi32>
    affine.store %v, %out[%i] : memref<512xi32>
  }
  return
}

// (b) dg_b_unreached: `t` is read only into `u`, `u` is never read -> both
// removed, with the loop that copies t into u.
// CHECK-LABEL: func.func @unreached
// CHECK-NOT: varname = "t"
// CHECK-NOT: varname = "u"
// CHECK: varname = "buf"
// CHECK-NOT: varname = "t"
// CHECK-NOT: varname = "u"
// CHECK: return
func.func @unreached(%in: memref<512xi32>, %out: memref<512xi32>) {
  %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
  %t = memref.alloca() {polygeist.varname = "t"} : memref<512xi32>
  %u = memref.alloca() {polygeist.varname = "u"} : memref<512xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %buf[%i] : memref<512xi32>
    affine.store %v, %t[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %t[%i] : memref<512xi32>
    affine.store %v, %u[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %buf[%i] : memref<512xi32>
    affine.store %v, %out[%i] : memref<512xi32>
  }
  return
}

// (h) dg_h_deadvalue: `t` is read into a running value that is overwritten
// before it reaches the output (the iter_arg's result is unused) -> removed.
// The loop that also carries a live value keeps that iter_arg only.
// CHECK-LABEL: func.func @dead_value
// CHECK-NOT: varname = "t"
// CHECK: affine.for
// CHECK-NOT: varname = "t"
// CHECK: return
func.func @dead_value(%in: memref<512xi32>, %out: memref<1xi32>) {
  %c0 = arith.constant 0 : i32
  %t = memref.alloca() {polygeist.varname = "t"} : memref<512xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %t[%i] : memref<512xi32>
  }
  %r:2 = affine.for %i = 0 to 512 iter_args(%last = %c0, %sum = %c0) -> (i32, i32) {
    %a = affine.load %t[%i] : memref<512xi32>
    %b = affine.load %in[%i] : memref<512xi32>
    %s = arith.addi %sum, %b : i32
    affine.yield %a, %s : i32, i32
  }
  affine.store %r#1, %out[0] : memref<1xi32>
  return
}

// (c) dg_c_overwrite, R2: no cross-loop dead-store elimination. `buf` is
// written in one loop, overwritten with 0 in a second loop and read in a third:
// all three loops and the array stay (the stores use different induction
// variables, so the accesses are not equal).
// CHECK-LABEL: func.func @overwrite_cross_loop
// CHECK: varname = "buf"
// CHECK: affine.store %{{.*}}, %{{.*}}[%{{.*}}] : memref<512xi32>
// CHECK: affine.store %c0_i32, %{{.*}}[%{{.*}}] : memref<512xi32>
// CHECK: affine.load %{{.*}}[%{{.*}}] : memref<512xi32>
func.func @overwrite_cross_loop(%in: memref<512xi32>, %out: memref<512xi32>) {
  %c0 = arith.constant 0 : i32
  %c1 = arith.constant 1 : i32
  %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    %w = arith.addi %v, %c1 : i32
    affine.store %w, %buf[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 512 {
    affine.store %c0, %buf[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %buf[%i] : memref<512xi32>
    affine.store %v, %out[%i] : memref<512xi32>
  }
  return
}

// A store that is overwritten in the same iteration of the enclosing loop
// before any read (the accumulator stored inside the d loop, then the
// product with a folded zero stored after it - LLVM's LICM promotion + DSE)
// is deleted, and `q` dies with it. Without the option (NODSE) the in-loop
// store keeps `s[i]` fed by `q`, so `q` stays.
// CHECK-LABEL: func.func @overwritten_in_iteration
// CHECK-NOT: varname = "q"
// CHECK: varname = "s"
// CHECK-NOT: varname = "q"
// CHECK: return
// NODSE-LABEL: func.func @overwritten_in_iteration
// NODSE: varname = "q"
func.func @overwritten_in_iteration(%in: memref<512xi32>, %out: memref<64xi32>) {
  %c0 = arith.constant 0 : i32
  %q = memref.alloca() {polygeist.varname = "q"} : memref<512xi32>
  %s = memref.alloca() {polygeist.varname = "s"} : memref<64xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %q[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 64 {
    %acc = affine.for %d = 0 to 8 iter_args(%a = %c0) -> (i32) {
      %x = affine.load %q[%i * 8 + %d] : memref<512xi32>
      %n = arith.addi %a, %x : i32
      affine.store %n, %s[%i] : memref<64xi32>
      affine.yield %n : i32
    }
    affine.store %c0, %s[%i] : memref<64xi32>
  }
  affine.for %i = 0 to 64 {
    %v = affine.load %s[%i] : memref<64xi32>
    affine.store %v, %out[%i] : memref<64xi32>
  }
  return
}

// The same with the accumulator kept in memory (cgeist's form without
// iter_args, e.g. under the exactclass shim): `s2[i] += q2[..]` is a
// load-modify-store of one loop-invariant element inside the d loop, whose
// loaded value only feeds that element's stores. LICM would keep it in a
// register, so the overwrite after the loop still kills it and `q2` dies.
// CHECK-LABEL: func.func @overwritten_rmw
// CHECK-NOT: varname = "q2"
// CHECK: varname = "s2"
// CHECK-NOT: varname = "q2"
// CHECK: return
func.func @overwritten_rmw(%in: memref<512xi32>, %out: memref<64xi32>) {
  %c0 = arith.constant 0 : i32
  %q = memref.alloca() {polygeist.varname = "q2"} : memref<512xi32>
  %s = memref.alloca() {polygeist.varname = "s2"} : memref<64xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %q[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 64 {
    affine.store %c0, %s[%i] : memref<64xi32>
    affine.for %d = 0 to 8 {
      %a = affine.load %s[%i] : memref<64xi32>
      %x = affine.load %q[%i * 8 + %d] : memref<512xi32>
      %n = arith.addi %a, %x : i32
      affine.store %n, %s[%i] : memref<64xi32>
    }
    affine.store %c0, %s[%i] : memref<64xi32>
  }
  affine.for %i = 0 to 64 {
    %v = affine.load %s[%i] : memref<64xi32>
    affine.store %v, %out[%i] : memref<64xi32>
  }
  return
}

// If a read of the accumulator leaves the chain (here it is also copied to
// an output), the in-loop stores are observed: nothing is removed.
// CHECK-LABEL: func.func @rmw_escapes
// CHECK: varname = "q3"
// CHECK: varname = "s3"
func.func @rmw_escapes(%in: memref<512xi32>, %out: memref<64xi32>, %side: memref<64xi32>) {
  %c0 = arith.constant 0 : i32
  %q = memref.alloca() {polygeist.varname = "q3"} : memref<512xi32>
  %s = memref.alloca() {polygeist.varname = "s3"} : memref<64xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %q[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 64 {
    affine.store %c0, %s[%i] : memref<64xi32>
    affine.for %d = 0 to 8 {
      %a = affine.load %s[%i] : memref<64xi32>
      affine.store %a, %side[%i] : memref<64xi32>
      %x = affine.load %q[%i * 8 + %d] : memref<512xi32>
      %n = arith.addi %a, %x : i32
      affine.store %n, %s[%i] : memref<64xi32>
    }
    affine.store %c0, %s[%i] : memref<64xi32>
  }
  affine.for %i = 0 to 64 {
    %v = affine.load %s[%i] : memref<64xi32>
    affine.store %v, %out[%i] : memref<64xi32>
  }
  return
}

// Nor when the loaded value leaves the loop through an iter_arg (it reaches
// %o2): the stores it observes are live.
// CHECK-LABEL: func.func @rmw_yield_escapes
// CHECK: varname = "q4"
// CHECK: varname = "s4"
func.func @rmw_yield_escapes(%in: memref<512xi32>, %out: memref<64xi32>, %o2: memref<64xi32>) {
  %c0 = arith.constant 0 : i32
  %q = memref.alloca() {polygeist.varname = "q4"} : memref<512xi32>
  %s = memref.alloca() {polygeist.varname = "s4"} : memref<64xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %q[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 64 {
    affine.store %c0, %s[%i] : memref<64xi32>
    %r = affine.for %d = 0 to 8 iter_args(%x = %c0) -> (i32) {
      %a = affine.load %s[%i] : memref<64xi32>
      %y = affine.load %q[%i * 8 + %d] : memref<512xi32>
      %n = arith.addi %a, %y : i32
      affine.store %n, %s[%i] : memref<64xi32>
      affine.yield %a : i32
    }
    affine.store %r, %o2[%i] : memref<64xi32>
    affine.store %c0, %s[%i] : memref<64xi32>
  }
  affine.for %i = 0 to 64 {
    %v = affine.load %s[%i] : memref<64xi32>
    affine.store %v, %out[%i] : memref<64xi32>
  }
  return
}

// hls.preserve does not keep a dead array (Vitis removes it as well), and a
// live one is never removed.
// CHECK-LABEL: func.func @preserve
// CHECK: memref.alloca() {hls.preserve, polygeist.varname = "live_p"}
// CHECK-NOT: "dead_p"
// CHECK: return
func.func @preserve(%in: memref<512xi32>, %out: memref<512xi32>) {
  %live = memref.alloca() {hls.preserve, polygeist.varname = "live_p"} : memref<512xi32>
  %dead = memref.alloca() {hls.preserve, polygeist.varname = "dead_p"} : memref<512xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %live[%i] : memref<512xi32>
    affine.store %v, %dead[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %live[%i] : memref<512xi32>
    %w = affine.load %dead[%i] : memref<512xi32>
    affine.store %v, %out[%i] : memref<512xi32>
  }
  return
}

// An array passed to a call escapes: it is live whatever the callee does.
// CHECK-LABEL: func.func @escaping
// CHECK: varname = "e"
// CHECK: call @sink
func.func private @sink(memref<512xi32>)
func.func @escaping(%in: memref<512xi32>) {
  %e = memref.alloca() {polygeist.varname = "e"} : memref<512xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %e[%i] : memref<512xi32>
  }
  call @sink(%e) : (memref<512xi32>) -> ()
  return
}

// Globals (R6): a write-only global is removed with its stores; a global
// read into the output stays; a global used by two functions escapes.
// CHECK-NOT: memref.global @G_DEAD
// CHECK-DAG: memref.global @G_LIVE
// CHECK-DAG: memref.global @G_SHARED
// CHECK-LABEL: func.func @globals
// CHECK-NOT: get_global @G_DEAD
// CHECK: return
memref.global @G_DEAD : memref<512xi32> = uninitialized
memref.global @G_LIVE : memref<512xi32> = uninitialized
memref.global @G_SHARED : memref<512xi32> = uninitialized
func.func @globals(%in: memref<512xi32>, %out: memref<512xi32>) {
  %d = memref.get_global @G_DEAD : memref<512xi32>
  %l = memref.get_global @G_LIVE : memref<512xi32>
  %s = memref.get_global @G_SHARED : memref<512xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %d[%i] : memref<512xi32>
    affine.store %v, %l[%i] : memref<512xi32>
    affine.store %v, %s[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %l[%i] : memref<512xi32>
    affine.store %v, %out[%i] : memref<512xi32>
  }
  return
}
func.func @other_user(%out: memref<512xi32>) {
  %s = memref.get_global @G_SHARED : memref<512xi32>
  return
}
