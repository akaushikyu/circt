// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-seq-dual-port --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=ARMS

// Two accesses of one array in one state of a NON-pipelined region
// (--bram-seq-dual-port, VITIS_NOTES.md N12, OPEN_ISSUES.md O3). Vitis
// schedules a sequential region with the same 2-port RAM core as a pipeline
// and puts two accesses in one state when they lie in one straight-line
// stretch and neither depends on the other; one such state makes a 64x32 array
// ram_2p (two reads, or a read and a write: RAM_2P) / ram_t2p (two writes:
// RAM_T2P) = 2 BRAM (x18 columns) instead of ram_1p = 1 (x36).
// Each function below mirrors a Vitis kernel of ~/hls-est-work/exp-src/
// seqports3 (`sp_o_*`: the body of an outer loop that a variable-trip inner
// loop keeps from being pipelined), seqports (`sp_*`) or t6rev (`rv_*`); the
// Vitis BRAM of `a` is in the comment. Without the option (OFF) every array
// here is 1.
//
// @two_loads (sp_o_8ld / sp_2ld_outer, Vitis 2): a[i] and a[i+32] feed one add.
// @dependent_loads (sp_o_dd, Vitis 1): the second address is the first value.
// @rmw (sp_o_rmw, Vitis 1): the store needs the loaded value.
// @load_store_disjoint (sp_o_ldst, Vitis 2): a[i] and a[i+32] cannot alias.
// @store_load_may_alias (sp_o_stld_alias, Vitis 1): a[(5i) mod 64] then a[i]:
//   the load is ordered after the store.
// @split_by_loop (sp_split_loop, Vitis 1): the inner loop separates them; the
//   second load feeds the add after the loop.
// @straight_line (sp_straight, Vitis 2; the hoisted buff_x[0..63] loads of
//   polybench atax, Vitis buff_x ram_2p 2): constant-index loads in the
//   function body.
// @if_arms (sp_o_ifarms, Vitis 1; sp_o_ifst, the same with a store in each
//   arm, Vitis 1): one load in each arm of an if. Vitis predicates the arms and
//   binds the two to one port. --convert-affine-to-loopschedule hoists every if
//   body in front of its if (hoistIfBodies) and records the arm on each moved
//   access (`hls.if_arms = [if id, arm]`, ARMS lines), so the two loads are
//   still exclusive -> 1.
// @if_speculated (sp_if, Vitis 2): a load in an if arm and one before it.
// @two_stores (sp_2st 2 / sp_o_2st 1): two independent stores. The model says
//   2; Vitis gives 1 when the stretch has slack (it moved one store past the
//   inner-loop call), a known over-estimate (N12, O21).
// @mem_order (rv_memdep, Vitis 1): x = a[i]; b[idx[i] & 63] = x;
//   y = b[3i & 63]; a[(y + i) & 63]: the load of b may read x, so the second a
//   load is ordered after the first through b.
// @mem_order_straight (rv_memdep2, Vitis a 1, b 1): the same in the function
//   body.
// @sibling_loops (rv_sib2, Vitis 2): t = a[i]; loop over t; u = a[i+32];
//   loop over u. Vitis outlines both pipelined loops as calls, starts them
//   together and loads both values in one state; the model ends the stretch
//   at the first loop and says 1, a known under-estimate (N12, O21).

module {
  func.func @two_loads(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_two_loads")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %x = affine.load %a[%i] : memref<64xi32>
      %y = affine.load %a[%i + 32] : memref<64xi32>
      %s = arith.addi %x, %y : i32
      %t = affine.for %j = 0 to %n iter_args(%acc = %s) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %m = arith.muli %jj, %acc : i32
        %r = arith.addi %acc, %m : i32
        affine.yield %r : i32
      }
      affine.store %t, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @dependent_loads(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %c31 = arith.constant 31 : i32
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_dependent_loads")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %x = affine.load %a[%i] : memref<64xi32>
      %m = arith.andi %x, %c31 : i32
      %idx = arith.index_cast %m : i32 to index
      %y = memref.load %a[%idx] : memref<64xi32>
      %t = affine.for %j = 0 to %n iter_args(%acc = %y) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %r = arith.addi %acc, %jj : i32
        affine.yield %r : i32
      }
      affine.store %t, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @rmw(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %c3 = arith.constant 3 : i32
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_rmw")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %x = affine.load %a[%i] : memref<64xi32>
      %y = arith.muli %x, %c3 : i32
      affine.store %y, %a[%i] : memref<64xi32>
      %ii = arith.index_cast %i : index to i32
      %t = affine.for %j = 0 to %n iter_args(%acc = %ii) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %r = arith.addi %acc, %jj : i32
        affine.yield %r : i32
      }
      affine.store %t, %out[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %a[%i] : memref<64xi32>
      affine.store %v, %in[%i] : memref<64xi32>
    }
    return
  }

  func.func @load_store_disjoint(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %c3 = arith.constant 3 : i32
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_load_store_disjoint")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %x = affine.load %a[%i] : memref<64xi32>
      %ii = arith.index_cast %i : index to i32
      %c = arith.muli %ii, %c3 : i32
      affine.store %c, %a[%i + 32] : memref<64xi32>
      %t = affine.for %j = 0 to %n iter_args(%acc = %x) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %r = arith.addi %acc, %jj : i32
        affine.yield %r : i32
      }
      affine.store %t, %out[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %a[%i] : memref<64xi32>
      affine.store %v, %in[%i] : memref<64xi32>
    }
    return
  }

  func.func @store_load_may_alias(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_store_load_may_alias")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %ii = arith.index_cast %i : index to i32
      affine.store %ii, %a[(%i * 5) mod 64] : memref<64xi32>
      %x = affine.load %a[%i] : memref<64xi32>
      %t = affine.for %j = 0 to %n iter_args(%acc = %x) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %r = arith.addi %acc, %jj : i32
        affine.yield %r : i32
      }
      affine.store %t, %out[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %a[%i] : memref<64xi32>
      affine.store %v, %in[%i] : memref<64xi32>
    }
    return
  }

  func.func @split_by_loop(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_split_by_loop")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %x = affine.load %a[%i] : memref<64xi32>
      %t = affine.for %j = 0 to %n iter_args(%acc = %x) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %m = arith.muli %jj, %acc : i32
        %r = arith.addi %acc, %m : i32
        affine.yield %r : i32
      }
      %y = affine.load %a[%i + 32] : memref<64xi32>
      %s = arith.addi %t, %y : i32
      affine.store %s, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @straight_line(%in: memref<64xi32>, %out: memref<64xi32>) {
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_straight_line")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    %x = affine.load %a[0] : memref<64xi32>
    %y = affine.load %a[1] : memref<64xi32>
    %s = arith.addi %x, %y : i32
    affine.store %s, %out[0] : memref<64xi32>
    return
  }

  func.func @if_arms(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %c0 = arith.constant 0 : i32
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_if_arms")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %c = affine.load %in[%i] : memref<64xi32>
      %p = arith.cmpi sgt, %c, %c0 : i32
      %x = scf.if %p -> (i32) {
        %l = affine.load %a[%i] : memref<64xi32>
        scf.yield %l : i32
      } else {
        %l = affine.load %a[%i + 32] : memref<64xi32>
        scf.yield %l : i32
      }
      %t = affine.for %j = 0 to %n iter_args(%acc = %x) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %r = arith.addi %acc, %jj : i32
        affine.yield %r : i32
      }
      affine.store %t, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @if_speculated(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %c0 = arith.constant 0 : i32
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_if_speculated")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %x = affine.load %a[%i] : memref<64xi32>
      %c = affine.load %in[%i] : memref<64xi32>
      %p = arith.cmpi sgt, %c, %c0 : i32
      %y = scf.if %p -> (i32) {
        %l = affine.load %a[%i + 32] : memref<64xi32>
        %s = arith.addi %x, %l : i32
        scf.yield %s : i32
      } else {
        scf.yield %x : i32
      }
      %t = affine.for %j = 0 to %n iter_args(%acc = %y) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %r = arith.addi %acc, %jj : i32
        affine.yield %r : i32
      }
      affine.store %t, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @two_stores(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %c7 = arith.constant 7 : i32
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_two_stores")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %ii = arith.index_cast %i : index to i32
      affine.store %ii, %a[%i] : memref<64xi32>
      %s = arith.muli %ii, %c7 : i32
      affine.store %s, %a[%i + 32] : memref<64xi32>
      %t = affine.for %j = 0 to %n iter_args(%acc = %ii) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %r = arith.addi %acc, %jj : i32
        affine.yield %r : i32
      }
      affine.store %t, %out[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %a[%i] : memref<64xi32>
      affine.store %v, %in[%i] : memref<64xi32>
    }
    return
  }

  func.func @mem_order(%in: memref<64xi32>, %out: memref<64xi32>, %idx: memref<64xi32>, %n: index) {
    %c3 = arith.constant 3 : i32
    %c5 = arith.constant 5 : i32
    %c63 = arith.constant 63 : i32
    %b = memref.alloca() {hls.preserve, polygeist.varname = "b"} : memref<64xi32> loc("b_mem_order")
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_mem_order")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
      %w = arith.xori %v, %c5 : i32
      affine.store %w, %b[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %ii = arith.index_cast %i : index to i32
      %x = affine.load %a[%i] : memref<64xi32>
      %t = affine.load %idx[%i] : memref<64xi32>
      %tm = arith.andi %t, %c63 : i32
      %tx = arith.index_cast %tm : i32 to index
      memref.store %x, %b[%tx] : memref<64xi32>
      %k3 = arith.muli %ii, %c3 : i32
      %km = arith.andi %k3, %c63 : i32
      %kx = arith.index_cast %km : i32 to index
      %y = memref.load %b[%kx] : memref<64xi32>
      %ya = arith.addi %y, %ii : i32
      %ym = arith.andi %ya, %c63 : i32
      %yx = arith.index_cast %ym : i32 to index
      %z = memref.load %a[%yx] : memref<64xi32>
      %s = arith.addi %z, %x : i32
      %r = affine.for %j = 0 to %n iter_args(%acc = %s) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %m = arith.muli %jj, %acc : i32
        %q = arith.addi %acc, %m : i32
        affine.yield %q : i32
      }
      affine.store %r, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @mem_order_straight(%in: memref<64xi32>, %out: memref<64xi32>, %out2: memref<64xi32>, %idx: i32, %j: i32) {
    %c3 = arith.constant 3 : i32
    %c7 = arith.constant 7 : i32
    %c63 = arith.constant 63 : i32
    %c0 = arith.constant 0 : index
    %b = memref.alloca() {hls.preserve, polygeist.varname = "b"} : memref<64xi32> loc("b_mem_order_straight")
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_mem_order_straight")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
      %w = arith.muli %v, %c7 : i32
      affine.store %w, %b[%i] : memref<64xi32>
    }
    %im = arith.andi %idx, %c63 : i32
    %ix = arith.index_cast %im : i32 to index
    %x = memref.load %a[%ix] : memref<64xi32>
    %jm = arith.andi %j, %c63 : i32
    %jx = arith.index_cast %jm : i32 to index
    memref.store %x, %b[%jx] : memref<64xi32>
    %k3 = arith.muli %j, %c3 : i32
    %km = arith.andi %k3, %c63 : i32
    %kx = arith.index_cast %km : i32 to index
    %y = memref.load %b[%kx] : memref<64xi32>
    %ym = arith.andi %y, %c63 : i32
    %yx = arith.index_cast %ym : i32 to index
    %z = memref.load %a[%yx] : memref<64xi32>
    %s1 = arith.addi %z, %y : i32
    %s2 = arith.addi %s1, %x : i32
    memref.store %s2, %out2[%c0] : memref<64xi32>
    affine.for %i = 0 to 64 {
      %v = affine.load %b[%i] : memref<64xi32>
      affine.store %v, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @sibling_loops(%in: memref<64xi32>, %out: memref<64xi32>, %n: index) {
    %a = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<64xi32> loc("a_sibling_loops")
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      affine.store %v, %a[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 32 {
      %x = affine.load %a[%i] : memref<64xi32>
      %t = affine.for %j = 0 to %n iter_args(%acc = %x) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %m = arith.muli %jj, %acc : i32
        %r = arith.addi %acc, %m : i32
        affine.yield %r : i32
      }
      %y = affine.load %a[%i + 32] : memref<64xi32>
      %u = affine.for %j = 0 to %n iter_args(%acc = %y) -> (i32) {
        %jj = arith.index_cast %j : index to i32
        %m = arith.muli %jj, %acc : i32
        %r = arith.addi %acc, %m : i32
        affine.yield %r : i32
      }
      %s = arith.addi %t, %u : i32
      affine.store %s, %out[%i] : memref<64xi32>
    }
    return
  }
}

// REPORT: memref.alloca @ loc("a_two_loads")
// REPORT-NEXT: kind=RAM_2P  bram=2
// REPORT: memref.alloca @ loc("a_dependent_loads")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("a_rmw")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("a_load_store_disjoint")
// REPORT-NEXT: kind=RAM_2P  bram=2
// REPORT: memref.alloca @ loc("a_store_load_may_alias")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("a_split_by_loop")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("a_straight_line")
// REPORT-NEXT: kind=RAM_2P  bram=2
// REPORT: memref.alloca @ loc("a_if_arms")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("a_if_speculated")
// REPORT-NEXT: kind=RAM_2P  bram=2
// REPORT: memref.alloca @ loc("a_two_stores")
// REPORT-NEXT: kind=RAM_T2P  bram=2
// REPORT: memref.alloca @ loc("b_mem_order")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("a_mem_order")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("b_mem_order_straight")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("a_mem_order_straight")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: memref.alloca @ loc("a_sibling_loops")
// REPORT-NEXT: kind=RAM_1P  bram=1
// REPORT: Total BRAM: 20

// The debug text names the pair that shares a state.
// CHECK-LABEL: [two_loads#0] a (alloca)
// CHECK: scope loop @ {{.*}} ii=0: reads=2 writes=0 total=2 [same state (independent, one straight-line stretch): memref.load @ {{.*}} + memref.load @
// CHECK-LABEL: [dependent_loads#1] a (alloca)
// CHECK: scope loop @ {{.*}} ii=0: reads=1 writes=0 total=1
// CHECK-NOT: same state
// CHECK-LABEL: [load_store_disjoint#3] a (alloca)
// CHECK: scope loop @ {{.*}} ii=0: reads=1 writes=1 total=2 [same state (independent, one straight-line stretch): memref.load @ {{.*}} + memref.store @
// CHECK-LABEL: [straight_line#6] a (alloca)
// CHECK: scope func @ {{.*}} ii=0: reads=2 writes=0 total=2 [same state
// CHECK-LABEL: [two_stores#9] a (alloca)
// CHECK: scope loop @ {{.*}} ii=0: reads=0 writes=2 total=2 [same state (independent, one straight-line stretch): memref.store @ {{.*}} + memref.store @
// CHECK-LABEL: [mem_order#11] a (alloca)
// CHECK: scope loop @ {{.*}} ii=0: reads=1 writes=0 total=1
// CHECK-NOT: same state
// CHECK-LABEL: [mem_order_straight#13] a (alloca)
// CHECK: scope func @ {{.*}} ii=0: reads=1 writes=0 total=1
// CHECK-NOT: same state
// CHECK-LABEL: [sibling_loops#14] a (alloca)

// OFF: memref.alloca @ loc("a_two_loads")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_load_store_disjoint")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_straight_line")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_if_speculated")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_two_stores")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_mem_order")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_mem_order_straight")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: Total BRAM: 15

// ARMS-LABEL: func.func @if_arms
// ARMS: affine.for
// ARMS: memref.load %{{.*}}[%{{.*}}] {hls.if_arms = array<i64: [[IF:[0-9]+]], 0>}
// ARMS: memref.load %{{.*}}[%{{.*}}] {hls.if_arms = array<i64: [[IF]], 1>}
// ARMS: scf.if
