// RUN: hls-est %s --symbol-privatize=exclude=top_callee --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_callee -o /dev/null | FileCheck %s --check-prefix=CALLEE
// RUN: hls-est %s --symbol-privatize=exclude=top_callee --symbol-dce --affine-loop-normalize --auto-pipeline-unroll "--memory-banking-bram=callee-stores-per-loop=false" --convert-affine-to-loopschedule --bram-analysis=top=top_callee -o /dev/null | FileCheck %s --check-prefix=CALLEE-OFF
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram -o - | FileCheck %s --check-prefix=ATTR

// Replicability decided from every loop that stores the array, the loops of
// the callees it is passed to included (OPEN_ISSUES.md O51 (f)): a callee
// loop stores S twice per iteration, so S is never a RAM_1WNR and the
// caller's loop reading S 8 times and B 8 times gets only S's two ports
// (II 4); B then needs no copies. --memory-banking-bram records the callee's
// worst loop body on the caller's bank (hls.callee_stores_per_loop) for the
// per-function scheduler. Without it the scheduler gave S the replicated read
// slots: II 1 and 7 copies of B (class_ece8893_spring_2025 adithi lab2:
// `V_local` 15 copies where Vitis builds 1, because a softmax callee stores
// `attention` 16 times per iteration).

// CALLEE: kind=RAM_T2P  bram=2
// CALLEE: kind=RAM_2P  bram=2
// CALLEE: Total BRAM: 4
// CALLEE-OFF: kind=RAM_1WNR  bram=14
// CALLEE-OFF: Total BRAM: 16
// ATTR: %{{.*}} = memref.alloca() {hls.callee_stores_per_loop = 2 : i64, hls.preserve, polygeist.varname = "S_callee"}

module {
  // A callee loop stores S twice per iteration: S is never a RAM_1WNR, so the
  // caller's loop reading S 8 times and B 8 times gets two ports of S (II 4),
  // and B needs one 2-port RAM, not 7 copies.
  func.func private @fill2(%S: memref<1024xi32>, %in: memref<1024xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 512 {
      %a = affine.load %in[%i * 2] : memref<1024xi32>
      %b = affine.load %in[%i * 2 + 1] : memref<1024xi32>
      affine.store %a, %S[%i * 2] : memref<1024xi32>
      affine.store %b, %S[%i * 2 + 1] : memref<1024xi32>
    }
    return
  }

  func.func @top_callee(%in: memref<1024xi32>, %out: memref<128xi32>) {
    %c0 = arith.constant 0 : i32
    %S = memref.alloca() {hls.preserve, polygeist.varname = "S_callee"} : memref<1024xi32>
    %B = memref.alloca() {hls.preserve, polygeist.varname = "B_callee"} : memref<1024xi32>
    func.call @fill2(%S, %in) : (memref<1024xi32>, memref<1024xi32>) -> ()
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.store %v, %B[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 128 {
      %s = affine.for %r = 0 to 8 iter_args(%acc = %c0) -> (i32) {
        %x = affine.load %S[%i * 8 + %r] : memref<1024xi32>
        %y = affine.load %B[%i * 8 + %r] : memref<1024xi32>
        %m = arith.muli %x, %y : i32
        %n = arith.addi %acc, %m : i32
        affine.yield %n : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %s, %out[%i] : memref<128xi32>
    }
    return
  }
}
