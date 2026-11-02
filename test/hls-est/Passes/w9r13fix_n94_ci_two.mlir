// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPiS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPiS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.partitioning.constant_index.through_calls=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N94 + N14 R4 (W9r13 review finding 4), kernel w9r13rev_ci_two (Vitis 2025.1 td=off: 76,
// A 16 banks, B RAM_1WNR 60, cons and cons_1 both II 1): cons(A) and cons(B) are two forms of the callee
// (A partitioned by its constant indices), one module each, so neither parameter is port-bound.
// Key off (no constant-index partition through calls): one shared callee, port-bound, II 8.
// CHECK-DAG: scope pipeline @ {{.*}}:31:5 ii=1:
// CHECK-DAG: scope pipeline @ {{.*}}:54:5 ii=1:
// CHECK-DAG: scope pipeline @ {{.*}}:23:5 ii=1:
// CHECK: Total BRAM: 76
// OFF-DAG: scope pipeline @ {{.*}}:31:5 ii=1:
// OFF-DAG: scope pipeline @ {{.*}}:54:5 ii=8:
// OFF-DAG: scope pipeline @ {{.*}}:23:5 ii=8:
// OFF: Total BRAM: 8
module {
  func.func @_Z3topPKiPiS1_(%arg0: memref<128xi32>, %arg1: memref<128xi32>, %arg2: memref<128xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1 = arith.constant -1 : index
    %c16 = arith.constant 16 : index
    %c0 = arith.constant 0 : index
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "B"} : memref<128x16xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<128x16xi32>
    affine.for %arg3 = 0 to 128 {
      affine.for %arg4 = 0 to 16 {
        %0 = arith.index_cast %arg4 : index to i32
        %1 = affine.load %arg0[%arg3] : memref<128xi32>
        %2 = arith.addi %1, %0 : i32
        affine.store %2, %alloca_0[%arg3, %arg4] : memref<128x16xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 2048 {
      %0 = arith.index_cast %arg3 : index to i32
      %1 = arith.cmpi slt, %arg3, %c0 : index
      %2 = arith.subi %c-1, %arg3 : index
      %3 = arith.select %1, %2, %arg3 : index
      %4 = arith.divsi %3, %c16 : index
      %5 = arith.subi %c-1, %4 : index
      %6 = arith.select %1, %5, %4 : index
      %7 = memref.load %arg0[%6] : memref<128xi32>
      %8 = arith.muli %7, %0 : i32
      %9 = arith.remsi %arg3, %c16 : index
      %10 = arith.cmpi slt, %9, %c0 : index
      %11 = arith.addi %9, %c16 : index
      %12 = arith.select %10, %11, %9 : index
      memref.store %8, %alloca[%6, %12] : memref<128x16xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    call @_ZL4consPA16_iPi(%alloca_0, %arg1) : (memref<128x16xi32>, memref<128xi32>) -> ()
    call @_ZL4consPA16_iPi(%alloca, %arg2) : (memref<128x16xi32>, memref<128xi32>) -> ()
    return
  }
  func.func private @_ZL4consPA16_iPi(%arg0: memref<128x16xi32>, %arg1: memref<128xi32>) attributes {hls.inline_off, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    affine.for %arg2 = 0 to 128 {
      %0 = affine.for %arg3 = 0 to 16 iter_args(%arg4 = %c0_i32) -> (i32) {
        %1 = arith.index_cast %arg3 : index to i32
        %2 = affine.load %arg0[%arg2, %arg3] : memref<128x16xi32>
        %3 = arith.addi %1, %c1_i32 : i32
        %4 = arith.muli %2, %3 : i32
        %5 = arith.addi %arg4, %4 : i32
        affine.yield %5 : i32
      }
      affine.store %0, %arg1[%arg2] : memref<128xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
