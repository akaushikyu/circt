// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N116 control, kernel w9r15p_al_two (Vitis 2025.1 td=off: 12): two
// independent producers pa(e, Q); pb(f, K) run together, so work(Q, o1) and
// work(K, o2) get their inputs in the same state: two instances.
// CHECK: Total BRAM: 12

module {
  func.func @_Z3topPiS_S_S_(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi32>, %arg3: memref<1024xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "K"} : memref<1024xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "Q"} : memref<1024xi32>
    call @_ZL2paPKiPi(%arg0, %alloca_0) : (memref<1024xi32>, memref<1024xi32>) -> ()
    call @_ZL2pbPKiPi(%arg1, %alloca) : (memref<1024xi32>, memref<1024xi32>) -> ()
    call @_ZL4workPKiPi(%alloca_0, %arg2) : (memref<1024xi32>, memref<1024xi32>) -> ()
    call @_ZL4workPKiPi(%alloca, %arg3) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
  func.func private @_ZL2paPKiPi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.inline_off, hls.orig_name = "pa", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 1024 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = affine.load %arg0[%arg2] : memref<1024xi32>
      %2 = arith.muli %1, %c3_i32 : i32
      %3 = arith.addi %2, %0 : i32
      affine.store %3, %arg1[%arg2] : memref<1024xi32>
    }
    return
  }
  func.func private @_ZL2pbPKiPi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.inline_off, hls.orig_name = "pb", llvm.linkage = #llvm.linkage<internal>} {
    %c5_i32 = arith.constant 5 : i32
    affine.for %arg2 = 0 to 1024 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = affine.load %arg0[%arg2] : memref<1024xi32>
      %2 = arith.muli %1, %c5_i32 : i32
      %3 = arith.addi %2, %0 : i32
      affine.store %3, %arg1[%arg2] : memref<1024xi32>
    }
    return
  }
  func.func private @_ZL4workPKiPi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.inline_off, hls.orig_name = "work", llvm.linkage = #llvm.linkage<internal>} {
    %c2_i32 = arith.constant 2 : i32
    %c1023_i32 = arith.constant 1023 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<1024xi32>
    affine.for %arg2 = 0 to 1024 {
      %0 = affine.load %arg0[%arg2] : memref<1024xi32>
      affine.store %0, %alloca[%arg2] : memref<1024xi32>
    }
    affine.for %arg2 = 0 to 1024 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = affine.load %alloca[%arg2] : memref<1024xi32>
      %2 = arith.addi %0, %c1_i32 : i32
      %3 = arith.andi %2, %c1023_i32 : i32
      %4 = arith.index_cast %3 : i32 to index
      %5 = memref.load %alloca[%4] : memref<1024xi32>
      %6 = arith.addi %1, %5 : i32
      %7 = arith.addi %0, %c2_i32 : i32
      %8 = arith.andi %7, %c1023_i32 : i32
      %9 = arith.index_cast %8 : i32 to index
      %10 = memref.load %alloca[%9] : memref<1024xi32>
      %11 = arith.addi %6, %10 : i32
      affine.store %11, %arg1[%arg2] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
