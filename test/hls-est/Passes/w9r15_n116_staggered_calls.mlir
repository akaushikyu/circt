// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.call_depth.staggered_calls_share_instance=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N116, kernel w9r15p_al_lim (Vitis 2025.1 td=off: 8): mm(e, 3, Q);
// mm(e, 5, K); work(Q, o1); work(K, o2) with mm limited to one instance: the two
// work calls get their inputs in different states (the second mm runs after the
// first), so they share one instance (4 BRAM: work's 3-read RAM_1WNR buffer).
// Off run: scheduling.call_depth.staggered_calls_share_instance off (N14 R2: two
// concurrent instances, 12).
// CHECK: Total BRAM: 8
// OFF: Total BRAM: 12

module {
  func.func @_Z3topPiS_S_(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi32>) attributes {hls.allocation = [{instances = ["mm"], limit = 1 : i32, type = "function"}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c5_i32 = arith.constant 5 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "K"} : memref<1024xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "Q"} : memref<1024xi32>
    call @_ZL2mmPKiiPi(%arg0, %c3_i32, %alloca_0) : (memref<1024xi32>, i32, memref<1024xi32>) -> ()
    call @_ZL2mmPKiiPi(%arg0, %c5_i32, %alloca) : (memref<1024xi32>, i32, memref<1024xi32>) -> ()
    call @_ZL4workPKiPi(%alloca_0, %arg1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    call @_ZL4workPKiPi(%alloca, %arg2) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
  func.func private @_ZL2mmPKiiPi(%arg0: memref<1024xi32>, %arg1: i32, %arg2: memref<1024xi32>) attributes {hls.inline_off, hls.orig_name = "mm", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg3 = 0 to 1024 {
      %0 = arith.index_cast %arg3 : index to i32
      %1 = affine.load %arg0[%arg3] : memref<1024xi32>
      %2 = arith.muli %1, %arg1 : i32
      %3 = arith.addi %2, %0 : i32
      affine.store %3, %arg2[%arg3] : memref<1024xi32>
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
