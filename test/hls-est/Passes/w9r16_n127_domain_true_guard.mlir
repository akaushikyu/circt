// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP3SymS0_iPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP3SymS0_iPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.hoist_common_arm_loads=false --config-set tool.hls.middle_end.gvn_memref_loads=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP3SymS0_iPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.hoist_common_arm_loads=false --config-set tool.hls.pipeline_decision.fold_domain_true_guards=true --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=FOLD

// VITIS_NOTES N127, kernel w9r16p_sh_guard (Vitis 2025.1 td=off: 4): `(s[j].frequency >>
// shift) & 15` with shift the counter of a loop from 0 lowers (real headers) to an
// affine.if (shift >= 0) whose two arms read s[j], plus the struct copy's read of s[j].
// The guard holds on the loop's whole domain; folding it leaves one read per iteration
// (N121's merge), s_frequency 1 BRAM as in Vitis. W9r16 review fixes: Vitis reads once
// also when the guard can fail (w9r16rv_sh_neg / sh_var), so the default is
// tool.hls.pipeline_decision.hoist_common_arm_loads (the load both arms issue is read
// once before the if; CHECK) and fold_domain_true_guards is off; the FOLD run keeps the
// fold as an option (4). Both off: 3 reads, RAM_1WNR 2 copies (7).
// CHECK: Total BRAM: 4
// (W9 round 23 review fixes: the OFF run also turns off tool.hls.middle_end.gvn_memref_loads, whose
// merging of memref.loads across ifs (review D3) now reads the element once as well.)
// OFF: Total BRAM: 7
// FOLD: Total BRAM: 4

#set = affine_set<(d0) : (d0 >= 0)>
module {
  func.func @_Z3topP3SymS0_iPi(%arg0: memref<256x!llvm.struct<(i10, i32)>>, %arg1: memref<256x!llvm.struct<(i10, i32)>>, %arg2: i32, %arg3: memref<16xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
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
    affine.for %arg4 = 0 to 256 {
      %7 = arith.muli %arg4, %c8 : index
      %8 = arith.index_cast %7 : index to i64
      %9 = llvm.getelementptr %0[%8] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %10 = llvm.getelementptr %1[%8] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %11 = llvm.load %10 : !llvm.ptr -> i10
      llvm.store %11, %9 : i10, !llvm.ptr
      %12 = llvm.getelementptr %9[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
      %13 = llvm.getelementptr %10[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
      %14 = llvm.load %13 : !llvm.ptr -> i32
      llvm.store %14, %12 : i32, !llvm.ptr
    }
    %2 = arith.index_cast %arg2 : i32 to index
    %3 = "polygeist.memref2pointer"(%alloca_1) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    %4 = "polygeist.memref2pointer"(%alloca_0) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    %5 = "polygeist.memref2pointer"(%alloca_0) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    affine.for %arg4 = 0 to 32 step 4 {
      %7 = arith.index_cast %arg4 : index to i32
      affine.for %arg5 = 0 to 16 {
        affine.store %c0_i32, %alloca[%arg5] : memref<16xi32>
      }
      %8 = arith.subi %c0_i32, %7 : i32
      affine.for %arg5 = 0 to %2 {
        %9 = arith.muli %arg5, %c8 : index
        %10 = arith.index_cast %9 : index to i64
        %11 = llvm.getelementptr %3[%10] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %12 = llvm.getelementptr %11[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
        %13 = affine.if #set(%arg4) -> i32 {
          %24 = llvm.load %12 : !llvm.ptr -> i32
          %25 = arith.shrui %24, %7 : i32
          affine.yield %25 : i32
        } else {
          %24 = llvm.load %12 : !llvm.ptr -> i32
          %25 = arith.shli %24, %8 : i32
          affine.yield %25 : i32
        }
        %14 = arith.extui %13 : i32 to i33
        %15 = arith.andi %14, %c15_i33 : i33
        %16 = arith.trunci %15 : i33 to i32
        %17 = arith.index_cast %16 : i32 to index
        %18 = memref.load %alloca[%17] : memref<16xi32>
        %19 = arith.addi %18, %c1_i32 : i32
        memref.store %19, %alloca[%17] : memref<16xi32>
        %20 = llvm.getelementptr %4[%10] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %21 = llvm.load %11 : !llvm.ptr -> i10
        llvm.store %21, %20 : i10, !llvm.ptr
        %22 = llvm.getelementptr %20[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
        %23 = llvm.load %12 : !llvm.ptr -> i32
        llvm.store %23, %22 : i32, !llvm.ptr
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.for %arg5 = 0 to %2 {
        %9 = arith.index_cast %arg5 : index to i32
        %10 = arith.muli %9, %c7_i32 : i32
        %11 = arith.andi %10, %c255_i32 : i32
        %12 = arith.index_cast %11 : i32 to index
        %13 = arith.muli %12, %c8 : index
        %14 = arith.index_cast %13 : index to i64
        %15 = llvm.getelementptr %3[%14] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %16 = arith.muli %arg5, %c8 : index
        %17 = arith.index_cast %16 : index to i64
        %18 = llvm.getelementptr %5[%17] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        %19 = llvm.load %18 : !llvm.ptr -> i10
        llvm.store %19, %15 : i10, !llvm.ptr
        %20 = llvm.getelementptr %15[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
        %21 = llvm.getelementptr %18[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
        %22 = llvm.load %21 : !llvm.ptr -> i32
        llvm.store %22, %20 : i32, !llvm.ptr
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.for %arg5 = 0 to 16 {
        %9 = affine.load %alloca[%arg5] : memref<16xi32>
        %10 = affine.load %arg3[%arg5] : memref<16xi32>
        %11 = arith.addi %10, %9 : i32
        affine.store %11, %arg3[%arg5] : memref<16xi32>
      }
    }
    %6 = "polygeist.memref2pointer"(%arg1) : (memref<256x!llvm.struct<(i10, i32)>>) -> !llvm.ptr
    affine.for %arg4 = 0 to 256 {
      %7 = arith.muli %arg4, %c8 : index
      %8 = arith.index_cast %7 : index to i64
      %9 = llvm.getelementptr %6[%8] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %10 = llvm.getelementptr %3[%8] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %11 = llvm.load %10 : !llvm.ptr -> i10
      llvm.store %11, %9 : i10, !llvm.ptr
      %12 = llvm.getelementptr %9[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
      %13 = llvm.getelementptr %10[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i10, i32)>
      %14 = llvm.load %13 : !llvm.ptr -> i32
      llvm.store %14, %12 : i32, !llvm.ptr
    }
    return
  }
}
