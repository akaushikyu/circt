// RUN: hls-est %s --bram-analysis --bram-seq-dual-port | FileCheck %s
// RUN: hls-est %s --bram-analysis | FileCheck %s --check-prefix=OFF

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

module {
  func.func private @use(memref<64xi32>)

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
}

// CHECK: memref.alloca @ loc("a_arms")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_arm_and_before")
// CHECK-NEXT: kind=RAM_T2P  bram=2
// CHECK: memref.alloca @ loc("a_same_address")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_call_barrier")
// CHECK-NEXT: kind=RAM_1P  bram=1
// CHECK: memref.alloca @ loc("a_sub_offset")
// CHECK-NEXT: kind=RAM_2P  bram=2
// CHECK: memref.alloca @ loc("a_three_loads")
// CHECK-NEXT: kind=RAM_T2P  bram=2
// CHECK: Total BRAM: 9

// OFF: memref.alloca @ loc("a_arm_and_before")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_sub_offset")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: memref.alloca @ loc("a_three_loads")
// OFF-NEXT: kind=RAM_1P  bram=1
// OFF: Total BRAM: 6
