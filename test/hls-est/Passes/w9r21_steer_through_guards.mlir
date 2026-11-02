// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiPA5_iPA187_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPiPA5_iPA187_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiPA5_iPA187_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPiPA5_iPA187_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.partitioning.steer_through_guards=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N155: five taps X[l + k - 2] of a cyclic-5
// array, each under its own guard (`if (!(l + k < 2 || l + k > 188))`), still
// read every bank once per load state: Vitis 5 x ram_1p = 5 BRAM (kernel
// w9r21p_g1_rot5; ECG_Classifier Optimized temp_input). Off: each guarded copy
// reads every bank, RAM_1WNR. MLIR from the installed cgeist 5523df29.
// CHECK-COUNT-5: 38x32b -> RAM_1P (x36/port) = 1 BRAM_18K
// CHECK: Total BRAM: 5
// OFF: 38x32b -> RAM_1WNR
// OFF: Total BRAM: 40
#set = affine_set<(d0, d1) : (-d0 - d1 + 1 >= 0)>
module {
  func.func @_Z3topPiPA5_iPA187_i(%arg0: memref<187xi32>, %arg1: memref<32x5xi32> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "W"}]}, %arg2: memref<32x187xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %true = arith.constant true
    %c188_i32 = arith.constant 188 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 5 : i32, kind = "cyclic", variable = "X"}], hls.preserve, polygeist.varname = "X"} : memref<187xi32>
    affine.for %arg3 = 0 to 187 {
      %0 = affine.load %arg0[%arg3] : memref<187xi32>
      affine.store %0, %alloca[%arg3] : memref<187xi32>
    }
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 187 {
        %0 = arith.index_cast %arg4 : index to i32
        %1 = affine.for %arg5 = 0 to 5 iter_args(%arg6 = %c0_i32) -> (i32) {
          %2 = arith.index_cast %arg5 : index to i32
          %3 = arith.addi %0, %2 : i32
          %4 = affine.if #set(%arg5, %arg4) -> i1 {
            affine.yield %true : i1
          } else {
            %6 = arith.cmpi sgt, %3, %c188_i32 : i32
            affine.yield %6 : i1
          }
          %5 = scf.if %4 -> (i32) {
            scf.yield %arg6 : i32
          } else {
            %6 = affine.load %alloca[%arg4 + %arg5 - 2] : memref<187xi32>
            %7 = affine.load %arg1[%arg3, %arg5] : memref<32x5xi32>
            %8 = arith.muli %6, %7 : i32
            %9 = arith.addi %arg6, %8 : i32
            scf.yield %9 : i32
          }
          affine.yield %5 : i32
        }
        affine.store %1, %arg2[%arg3, %arg4] : memref<32x187xi32>
      } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
