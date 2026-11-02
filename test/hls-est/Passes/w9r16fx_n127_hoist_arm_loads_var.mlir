// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP3SymS0_iiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP3SymS0_iiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.hoist_common_arm_loads=false --config-set tool.hls.middle_end.gvn_memref_loads=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N127 (W9r16 review fixes), kernel w9r16rv_sh_var (Vitis 2025.1 td=off: 4):
// w9r16p_sh_guard with the shift loop bounded by a run-time value, so no range analysis can
// fold the guard. Vitis reads s_frequency once per iteration (the load common to both arms
// is hoisted). Key tool.hls.pipeline_decision.hoist_common_arm_loads; off: 7.
// CHECK: Total BRAM: 4
// (W9 round 23 review fixes: the OFF run also turns off tool.hls.middle_end.gvn_memref_loads, whose
// merging of memref.loads across ifs (review D3) now reads the element once as well.)
// OFF: Total BRAM: 7

#set = affine_set<(d0) : (d0 >= 0)>
module {
  func.func @_Z3topP3SymS0_iiPi(%arg0: memref<256x!llvm.struct<(i10, i32)>>, %arg1: memref<256x!llvm.struct<(i10, i32)>>, %arg2: i32, %arg3: i32, %arg4: memref<16xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c15_i33 = arith.constant 15 : i33
    %c8 = arith.constant 8 : index
    %c255_i32 = arith.constant 255 : i32
    %c7_i32 = arith.constant 7 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "h"}], hls.preserve, polygeist.varname = "h"} : memref<16xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "prev"} : memref<256x!llvm.struct<(i10, i32)>>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "s"} : memref<256x!llvm.struct<(i10, i32)>>
    %0 = "polygeist.memref2pointer"(%alloca_1) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg0) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    affine.for %arg5 = 0 to 256 {
      %8 = arith.muli %arg5, %c8 : index
      %9 = arith.index_cast %8 : index to i64
      %10 = llvm.getelementptr %0[%9] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %11 = llvm.getelementptr %1[%9] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %12 = llvm.load %11 : !llvm.ptr -> i10
      llvm.store %12, %10 : i10, !llvm.ptr
      %13 = llvm.getelementptr %10[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
      %14 = llvm.getelementptr %11[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
      %15 = llvm.load %14 : !llvm.ptr -> i32
      llvm.store %15, %13 : i32, !llvm.ptr
    }
    %2 = arith.index_cast %arg3 : i32 to index
    %3 = arith.index_cast %arg2 : i32 to index
    %4 = "polygeist.memref2pointer"(%alloca_1) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    %5 = "polygeist.memref2pointer"(%alloca_0) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    %6 = "polygeist.memref2pointer"(%alloca_0) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    affine.for %arg5 = 0 to %2 step 4 {
      %8 = arith.index_cast %arg5 : index to i32
      affine.for %arg6 = 0 to 16 {
        affine.store %c0_i32, %alloca[%arg6] : memref<16xi32>
      }
      %9 = arith.subi %c0_i32, %8 : i32
      affine.for %arg6 = 0 to %3 {
        %10 = arith.muli %arg6, %c8 : index
        %11 = arith.index_cast %10 : index to i64
        %12 = llvm.getelementptr %4[%11] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %13 = llvm.getelementptr %12[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
        %14 = affine.if #set(%arg5) -> i32 {
          %25 = llvm.load %13 : !llvm.ptr -> i32
          %26 = arith.shrui %25, %8 : i32
          affine.yield %26 : i32
        } else {
          %25 = llvm.load %13 : !llvm.ptr -> i32
          %26 = arith.shli %25, %9 : i32
          affine.yield %26 : i32
        }
        %15 = arith.extui %14 : i32 to i33
        %16 = arith.andi %15, %c15_i33 : i33
        %17 = arith.trunci %16 : i33 to i32
        %18 = arith.index_cast %17 : i32 to index
        %19 = memref.load %alloca[%18] : memref<16xi32>
        %20 = arith.addi %19, %c1_i32 : i32
        memref.store %20, %alloca[%18] : memref<16xi32>
        %21 = llvm.getelementptr %5[%11] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %22 = llvm.load %12 : !llvm.ptr -> i10
        llvm.store %22, %21 : i10, !llvm.ptr
        %23 = llvm.getelementptr %21[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
        %24 = llvm.load %13 : !llvm.ptr -> i32
        llvm.store %24, %23 : i32, !llvm.ptr
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.for %arg6 = 0 to %3 {
        %10 = arith.index_cast %arg6 : index to i32
        %11 = arith.muli %10, %c7_i32 : i32
        %12 = arith.andi %11, %c255_i32 : i32
        %13 = arith.index_cast %12 : i32 to index
        %14 = arith.muli %13, %c8 : index
        %15 = arith.index_cast %14 : index to i64
        %16 = llvm.getelementptr %4[%15] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %17 = arith.muli %arg6, %c8 : index
        %18 = arith.index_cast %17 : index to i64
        %19 = llvm.getelementptr %6[%18] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %20 = llvm.load %19 : !llvm.ptr -> i10
        llvm.store %20, %16 : i10, !llvm.ptr
        %21 = llvm.getelementptr %16[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
        %22 = llvm.getelementptr %19[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
        %23 = llvm.load %22 : !llvm.ptr -> i32
        llvm.store %23, %21 : i32, !llvm.ptr
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.for %arg6 = 0 to 16 {
        %10 = affine.load %alloca[%arg6] : memref<16xi32>
        %11 = affine.load %arg4[%arg6] : memref<16xi32>
        %12 = arith.addi %11, %10 : i32
        affine.store %12, %arg4[%arg6] : memref<16xi32>
      }
    }
    %7 = "polygeist.memref2pointer"(%arg1) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    affine.for %arg5 = 0 to 256 {
      %8 = arith.muli %arg5, %c8 : index
      %9 = arith.index_cast %8 : index to i64
      %10 = llvm.getelementptr %7[%9] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %11 = llvm.getelementptr %4[%9] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %12 = llvm.load %11 : !llvm.ptr -> i10
      llvm.store %12, %10 : i10, !llvm.ptr
      %13 = llvm.getelementptr %10[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
      %14 = llvm.getelementptr %11[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
      %15 = llvm.load %14 : !llvm.ptr -> i32
      llvm.store %15, %13 : i32, !llvm.ptr
    }
    return
  }
}
