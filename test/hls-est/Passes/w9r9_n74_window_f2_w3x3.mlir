// RUN: hls-est %s --symbol-privatize=exclude=_Z7win_topPA40_sPA16_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7win_topPA40_sPA16_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z7win_topPA40_sPA16_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7win_topPA40_sPA16_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.partitioning.steer_window_groups=false -o /dev/null | FileCheck %s --check-prefix=WOFF
// W9r9-impl (2026-10-21): VITIS_NOTES N74: a 3x3 window on factor 2 along both dims: offsets {0,1,2} mod 2 put 2 per class per dimension, R = 2 x 2 = 4 reads per bank -> RAM_1WNR with 3 copies.
// Kernel w9r9p_o92_f2_w3x3; MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: RAM_1WNR 4 x 3 = 12 BRAM_18K.
// With tool.hls.partitioning.steer_window_groups=false (WOFF): 32.
// WOFF: Total BRAM: 32{{$}}
// CHECK: Total BRAM: 12{{$}}

module {
  func.func @_Z7win_topPA40_sPA16_i(%arg0: memref<40x40xi16>, %arg1: memref<16x16xi32>) attributes {hls.orig_name = "win_top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "X"}, {dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "X"}], hls.preserve, polygeist.varname = "X"} : memref<40x40xi16>
    affine.for %arg2 = 0 to 40 {
      affine.for %arg3 = 0 to 40 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<40x40xi16>
        affine.store %0, %alloca[%arg2, %arg3] : memref<40x40xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    affine.for %arg2 = 0 to 16 {
      affine.for %arg3 = 0 to 16 {
        %0 = affine.for %arg4 = 0 to 3 iter_args(%arg5 = %c0_i32) -> (i32) {
          %1 = arith.index_cast %arg4 : index to i32
          %2 = arith.muli %1, %c3_i32 : i32
          %3 = affine.for %arg6 = 0 to 3 iter_args(%arg7 = %arg5) -> (i32) {
            %4 = arith.index_cast %arg6 : index to i32
            %5 = affine.load %alloca[%arg2 + %arg4, %arg3 + %arg6] : memref<40x40xi16>
            %6 = arith.extsi %5 : i16 to i32
            %7 = arith.addi %2, %4 : i32
            %8 = arith.addi %7, %c1_i32 : i32
            %9 = arith.muli %6, %8 : i32
            %10 = arith.addi %arg7, %9 : i32
            affine.yield %10 : i32
          }
          affine.yield %3 : i32
        }
        affine.store %0, %arg1[%arg2, %arg3] : memref<16x16xi32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
