// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_S_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_S_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.call_depth.outlined_loops_own_allocation=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N14 R5, kernel w9r17i_ol_lim (Vitis 2025.1 td=off: 8): `work` (a
// 1024-word buffer read three times per pipelined iteration, 4 BRAM) is called
// in a loop of top and directly after it, under `allocation function
// instances=work limit=1`. Vitis outlines the loop into top_Outline_VITIS_LOOP_11_1
// because top also calls a function outside every loop, and the limit does not
// reach the call inside the outlined module: two instances, 8 BRAM.
// Off run: scheduling.call_depth.outlined_loops_own_allocation off (one cap over
// the whole function: 1 instance, 4).
// CHECK: allocation limit 1 caps the function's own body only: 1 loop(s) holding calls are outlined (N14 R5)
// CHECK: Total BRAM: 8
// OFF: Total BRAM: 4

module {
  func.func @_Z3topPiS_S_S_i(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi32>, %arg3: memref<1024xi32>, %arg4: i32) attributes {hls.allocation = [{instances = ["work"], limit = 1 : i32, type = "function"}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %0 = arith.index_cast %arg4 : i32 to index
    affine.for %arg5 = 0 to %0 {
      func.call @_ZL4workPiS_(%arg0, %arg1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    }
    call @_ZL4workPiS_(%arg2, %arg3) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
  func.func private @_ZL4workPiS_(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.inline_off, hls.orig_name = "work", llvm.linkage = #llvm.linkage<internal>} {
    %c7_i32 = arith.constant 7 : i32
    %c1023_i32 = arith.constant 1023 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<1024xi32>
    affine.for %arg2 = 0 to 1024 {
      %0 = affine.load %arg0[%arg2] : memref<1024xi32>
      %1 = arith.muli %0, %c3_i32 : i32
      affine.store %1, %alloca[%arg2] : memref<1024xi32>
    }
    affine.for %arg2 = 0 to 1024 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = affine.load %alloca[%arg2] : memref<1024xi32>
      %2 = affine.load %alloca[-%arg2 + 1023] : memref<1024xi32>
      %3 = arith.addi %1, %2 : i32
      %4 = arith.muli %0, %c7_i32 : i32
      %5 = arith.andi %4, %c1023_i32 : i32
      %6 = arith.index_cast %5 : i32 to index
      %7 = memref.load %alloca[%6] : memref<1024xi32>
      %8 = arith.addi %3, %7 : i32
      %9 = affine.load %arg1[%arg2] : memref<1024xi32>
      %10 = arith.addi %9, %8 : i32
      affine.store %10, %arg1[%arg2] : memref<1024xi32>
    }
    return
  }
}
