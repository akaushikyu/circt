// RUN: hls-est %s --bram-analysis --bram-seq-dual-port | FileCheck %s
// RUN: hls-est %s --bram-analysis --bram-seq-dual-port=false | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --bram-analysis | FileCheck %s

// --bram-seq-dual-port (VITIS_NOTES.md N12) on hand-written lowered IR, to pin
// the parts of the rule that the --convert-affine-to-loopschedule output does
// not reach (it hoists every if body in front of its if, so no access is left
// in an arm there; seq_scope_ports.mlir covers the pipeline end to end).
//
// @arms: a[i] in the then arm, a[i+32] in the else arm of one if: the two never
//   execute together, no state holds both -> 1.
// @arm_and_before: a[i] before the if, a[i+32] in its then arm: one stretch,
//   Vitis predicates the arm (sp_if: ram_2p 2) -> 2.
// @same_address: two loads of a[i] (not merged by CSE here): one load after
//   GVN -> 1.
// @call_barrier: a[0], a call that takes the array, a[1]: the call orders the
//   two loads -> 1.
// @sub_offset: store a[i - 1], load a[i + 1]: provably different addresses,
//   nothing orders them -> 1R+1W in one state, RAM_2P = 2.
// @three_loads: three independent loads still need only two ports (a state
//   holds at most two in a sequential region: sp_8ld, ram_2p 2) -> 2.
// Two reads per state are RAM_2P (Vitis ram_2p); RAM_T2P only for two writes.
//
// Memory order through another array (review of T6, D1):
// @through_other: x = a[i]; b[idx[i]] = x; y = b[3i]; a[y]: the load of b may
//   read the stored x, so the second a load is ordered after the first
//   (rv_memdep: Vitis a ram_1p 1) -> a 1.
// @through_other_disjoint: the same with b[0] stored and b[1] loaded: nothing
//   orders the two a loads -> a 2 (b: 1R+1W in one state, 2).
// @war_chain: x = a[i]; t = b[x]; b[j] = 5; w = b[k]; a[w]: the store is
//   ordered after the load of b that needs x (write after read), the load of
//   w after the store -> a 1.
// @unrelated_store: x = a[i]; b[i] = v; y = a[i+32]: a store that depends on
//   no access of a orders nothing -> a 2.
// @call_between: a[0], a call that takes no array, a[1]: a call may write
//   any storage, so it orders the two loads (conservative, not confirmed by a
//   Vitis kernel) -> 1.

module {
  func.func private @use(memref<64xi32>)
  func.func private @tick()

  func.func @arms(%c: i1, %out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_arms")
    %c32 = arith.constant 32 : index
    affine.for %i = 0 to 32 {
      %x = scf.if %c -> (i32) {
        %l = memref.load %a[%i] : memref<64xi32>
        scf.yield %l : i32
      } else {
        %j = arith.addi %i, %c32 : index
        %l = memref.load %a[%j] : memref<64xi32>
        scf.yield %l : i32
      }
      memref.store %x, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @arm_and_before(%c: i1, %out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_arm_and_before")
    %c32 = arith.constant 32 : index
    affine.for %i = 0 to 32 {
      %x = memref.load %a[%i] : memref<64xi32>
      %y = scf.if %c -> (i32) {
        %j = arith.addi %i, %c32 : index
        %l = memref.load %a[%j] : memref<64xi32>
        %s = arith.addi %x, %l : i32
        scf.yield %s : i32
      } else {
        scf.yield %x : i32
      }
      memref.store %y, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @same_address(%out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_same_address")
    affine.for %i = 0 to 32 {
      %x = memref.load %a[%i] : memref<64xi32>
      %y = memref.load %a[%i] : memref<64xi32>
      %s = arith.addi %x, %y : i32
      memref.store %s, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @call_barrier(%out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_call_barrier")
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %x = memref.load %a[%c0] : memref<64xi32>
    func.call @use(%a) : (memref<64xi32>) -> ()
    %y = memref.load %a[%c1] : memref<64xi32>
    %s = arith.addi %x, %y : i32
    memref.store %s, %out[%c0] : memref<64xi32>
    return
  }

  func.func @sub_offset(%v: i32, %out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_sub_offset")
    %c1 = arith.constant 1 : index
    affine.for %i = 1 to 32 {
      %m = arith.subi %i, %c1 : index
      memref.store %v, %a[%m] : memref<64xi32>
      %p = arith.addi %i, %c1 : index
      %x = memref.load %a[%p] : memref<64xi32>
      memref.store %x, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @three_loads(%out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_three_loads")
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c2 = arith.constant 2 : index
    %x = memref.load %a[%c0] : memref<64xi32>
    %y = memref.load %a[%c1] : memref<64xi32>
    %z = memref.load %a[%c2] : memref<64xi32>
    %s = arith.addi %x, %y : i32
    %t = arith.addi %s, %z : i32
    memref.store %t, %out[%c0] : memref<64xi32>
    return
  }

  func.func @through_other(%idx: memref<64xi32>, %out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_through_other")
    %b = memref.alloca() : memref<64xi32> loc("b_through_other")
    %c3 = arith.constant 3 : i32
    %c63 = arith.constant 63 : i32
    affine.for %i = 0 to 32 {
      %ii = arith.index_cast %i : index to i32
      %x = memref.load %a[%i] : memref<64xi32>
      %t = memref.load %idx[%i] : memref<64xi32>
      %tm = arith.andi %t, %c63 : i32
      %j = arith.index_cast %tm : i32 to index
      memref.store %x, %b[%j] : memref<64xi32>
      %k3 = arith.muli %ii, %c3 : i32
      %km = arith.andi %k3, %c63 : i32
      %k = arith.index_cast %km : i32 to index
      %y = memref.load %b[%k] : memref<64xi32>
      %ym = arith.andi %y, %c63 : i32
      %yi = arith.index_cast %ym : i32 to index
      %z = memref.load %a[%yi] : memref<64xi32>
      %s = arith.addi %z, %x : i32
      memref.store %s, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @through_other_disjoint(%out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_through_other_disjoint")
    %b = memref.alloca() : memref<64xi32> loc("b_through_other_disjoint")
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c63 = arith.constant 63 : i32
    affine.for %i = 0 to 32 {
      %x = memref.load %a[%i] : memref<64xi32>
      memref.store %x, %b[%c0] : memref<64xi32>
      %y = memref.load %b[%c1] : memref<64xi32>
      %ym = arith.andi %y, %c63 : i32
      %yi = arith.index_cast %ym : i32 to index
      %z = memref.load %a[%yi] : memref<64xi32>
      %s = arith.addi %z, %x : i32
      memref.store %s, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @war_chain(%j: index, %k: index, %out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_war_chain")
    %b = memref.alloca() : memref<64xi32> loc("b_war_chain")
    %c5 = arith.constant 5 : i32
    %c63 = arith.constant 63 : i32
    affine.for %i = 0 to 32 {
      %x = memref.load %a[%i] : memref<64xi32>
      %xm = arith.andi %x, %c63 : i32
      %xi = arith.index_cast %xm : i32 to index
      %t = memref.load %b[%xi] : memref<64xi32>
      memref.store %c5, %b[%j] : memref<64xi32>
      %w = memref.load %b[%k] : memref<64xi32>
      %wm = arith.andi %w, %c63 : i32
      %wi = arith.index_cast %wm : i32 to index
      %z = memref.load %a[%wi] : memref<64xi32>
      %s = arith.addi %z, %t : i32
      memref.store %s, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @unrelated_store(%v: i32, %out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_unrelated_store")
    %b = memref.alloca() : memref<64xi32> loc("b_unrelated_store")
    %c32 = arith.constant 32 : index
    affine.for %i = 0 to 32 {
      %x = memref.load %a[%i] : memref<64xi32>
      memref.store %v, %b[%i] : memref<64xi32>
      %j = arith.addi %i, %c32 : index
      %y = memref.load %a[%j] : memref<64xi32>
      %s = arith.addi %x, %y : i32
      memref.store %s, %out[%i] : memref<64xi32>
    }
    return
  }

  func.func @call_between(%out: memref<64xi32>) {
    %a = memref.alloca() : memref<64xi32> loc("a_call_between")
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %x = memref.load %a[%c0] : memref<64xi32>
    func.call @tick() : () -> ()
    %y = memref.load %a[%c1] : memref<64xi32>
    %s = arith.addi %x, %y : i32
    memref.store %s, %out[%c0] : memref<64xi32>
    return
  }
}

// CHECK: memref.alloca @ loc("a_arms")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_arm_and_before")
// CHECK-NEXT: kind=RAM_2P  bram=2
// CHECK: memref.alloca @ loc("a_same_address")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_call_barrier")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_sub_offset")
// CHECK-NEXT: kind=RAM_2P  bram=2
// CHECK: memref.alloca @ loc("a_three_loads")
// CHECK-NEXT: kind=RAM_2P  bram=2
// CHECK: memref.alloca @ loc("a_through_other")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("b_through_other")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_through_other_disjoint")
// CHECK-NEXT: kind=RAM_2P  bram=2
// CHECK: memref.alloca @ loc("b_through_other_disjoint")
// CHECK-NEXT: kind=RAM_2P  bram=2
// CHECK: memref.alloca @ loc("a_war_chain")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("b_war_chain")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_unrelated_store")
// CHECK-NEXT: kind=RAM_2P  bram=2
// CHECK: memref.alloca @ loc("b_unrelated_store")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_call_between")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: Total BRAM: 21

// OFF: memref.alloca @ loc("a_arm_and_before")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_sub_offset")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_three_loads")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_through_other_disjoint")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_unrelated_store")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: Total BRAM: 15
