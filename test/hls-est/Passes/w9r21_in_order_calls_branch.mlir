// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsS_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPsS_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsS_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPsS_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=scheduling.call_depth.in_order_call_starts=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N156: the three calls of w9r21_in_order_calls
// in one arm of an if chain inside a loop (kernel w9r21p_f1_branch): Vitis one
// work instance; the rule applies in a nested block outside pipelined loops.
// MLIR from the installed cgeist 5523df29.
// CHECK: 512x16b -> RAM_1P (x36/port) = 1 BRAM_18K{{$}}
// CHECK: Total BRAM: 8
// OFF: 512x16b -> RAM_1P (x36/port) = 1 BRAM_18K x 2 instance(s) of @_Z4workPsS_S_
// OFF: Total BRAM: 9
#set = affine_set<(d0)[s0] : (d0 - s0 + 1 == 0)>
module {
  func.func @_Z4workPsS_S_(%arg0: memref<512xi16>, %arg1: memref<512xi16>, %arg2: memref<512xi16>) attributes {hls.inline_off, hls.orig_name = "work", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<512xi16>
    affine.for %arg3 = 0 to 512 {
      %0 = affine.load %arg0[%arg3] : memref<512xi16>
      %1 = arith.extsi %0 : i16 to i32
      %2 = affine.load %arg1[-%arg3 + 511] : memref<512xi16>
      %3 = arith.extsi %2 : i16 to i32
      %4 = arith.addi %1, %3 : i32
      %5 = arith.trunci %4 : i32 to i16
      affine.store %5, %alloca[%arg3] : memref<512xi16>
    }
    affine.for %arg3 = 0 to 512 {
      %0 = affine.load %alloca[-%arg3 + 511] : memref<512xi16>
      %1 = arith.extsi %0 : i16 to i32
      %2 = arith.muli %1, %c3_i32 : i32
      %3 = arith.trunci %2 : i32 to i16
      affine.store %3, %arg2[%arg3] : memref<512xi16>
    }
    return
  }
  func.func @_Z3midPsS_(%arg0: memref<512xi16>, %arg1: memref<512xi16>) attributes {hls.inline_off, hls.orig_name = "mid", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %arg0[%arg2] : memref<512xi16>
      %1 = arith.extsi %0 : i16 to i32
      %2 = arith.addi %1, %c1_i32 : i32
      %3 = arith.trunci %2 : i32 to i16
      affine.store %3, %arg1[%arg2] : memref<512xi16>
    }
    return
  }
  func.func @_Z3topPsS_i(%arg0: memref<512xi16>, %arg1: memref<512xi16>, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %c5_i32 = arith.constant 5 : i32
    %c1_i32 = arith.constant 1 : i32
    %c3_i32 = arith.constant 3 : i32
    %c2_i32 = arith.constant 2 : i32
    %0 = arith.index_cast %arg2 : i32 to index
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "P"} : memref<512xi16>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "F"} : memref<512xi16>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "E"} : memref<512xi16>
    %alloca_2 = memref.alloca() {hls.preserve, polygeist.varname = "D"} : memref<512xi16>
    %alloca_3 = memref.alloca() {hls.preserve, polygeist.varname = "C"} : memref<512xi16>
    %alloca_4 = memref.alloca() {hls.preserve, polygeist.varname = "B"} : memref<512xi16>
    %alloca_5 = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<512xi16>
    affine.for %arg3 = 0 to 512 {
      %1 = affine.load %arg0[%arg3] : memref<512xi16>
      affine.store %1, %alloca_5[%arg3] : memref<512xi16>
      %2 = affine.load %arg0[-%arg3 + 511] : memref<512xi16>
      affine.store %2, %alloca_4[%arg3] : memref<512xi16>
      %3 = affine.load %arg0[%arg3] : memref<512xi16>
      %4 = arith.extsi %3 : i16 to i32
      %5 = arith.xori %4, %c5_i32 : i32
      %6 = arith.trunci %5 : i32 to i16
      affine.store %6, %alloca_2[%arg3] : memref<512xi16>
      %7 = affine.load %arg0[%arg3] : memref<512xi16>
      %8 = arith.extsi %7 : i16 to i32
      %9 = arith.shrsi %8, %c1_i32 : i32
      %10 = arith.trunci %9 : i32 to i16
      affine.store %10, %alloca_1[%arg3] : memref<512xi16>
      %11 = affine.load %arg0[%arg3] : memref<512xi16>
      %12 = arith.extsi %11 : i16 to i32
      %13 = arith.andi %12, %c3_i32 : i32
      %14 = arith.trunci %13 : i32 to i16
      affine.store %14, %alloca[%arg3] : memref<512xi16>
    }
    affine.for %arg3 = 0 to %0 {
      %1 = arith.index_cast %arg3 : index to i32
      affine.if #set(%arg3)[%0] {
        func.call @_Z4workPsS_S_(%alloca_5, %alloca_4, %alloca_3) : (memref<512xi16>, memref<512xi16>, memref<512xi16>) -> ()
        func.call @_Z3midPsS_(%alloca, %alloca_5) : (memref<512xi16>, memref<512xi16>) -> ()
        func.call @_Z4workPsS_S_(%alloca_2, %alloca_1, %alloca_0) : (memref<512xi16>, memref<512xi16>, memref<512xi16>) -> ()
      } else {
        %2 = arith.remsi %1, %c2_i32 : i32
        %3 = arith.cmpi ne, %2, %c0_i32 : i32
        scf.if %3 {
          func.call @_Z4workPsS_S_(%alloca_5, %alloca_4, %alloca_3) : (memref<512xi16>, memref<512xi16>, memref<512xi16>) -> ()
        } else {
          func.call @_Z4workPsS_S_(%alloca_2, %alloca_1, %alloca_0) : (memref<512xi16>, memref<512xi16>, memref<512xi16>) -> ()
        }
      }
    }
    affine.for %arg3 = 0 to 512 {
      %1 = affine.load %alloca_3[%arg3] : memref<512xi16>
      %2 = arith.extsi %1 : i16 to i32
      %3 = affine.load %alloca_0[%arg3] : memref<512xi16>
      %4 = arith.extsi %3 : i16 to i32
      %5 = arith.addi %2, %4 : i32
      %6 = affine.load %alloca_5[%arg3] : memref<512xi16>
      %7 = arith.extsi %6 : i16 to i32
      %8 = arith.addi %5, %7 : i32
      %9 = arith.trunci %8 : i32 to i16
      affine.store %9, %arg1[%arg3] : memref<512xi16>
    }
    return
  }
}
