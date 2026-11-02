// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_KsS1_Ps --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA128_KsS1_Ps math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_KsS1_Ps --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA128_KsS1_Ps math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.pipeline_decision.promoted_store_cleanup=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N166 (a). `s[i][j] = 0; for (d < 128)
// s[i][j] += (q * k) >> 10; s[i][j] /= 768;` then a loop reading 64 elements
// of a row per iteration. LLVM's LICM keeps s[i][j] in a register over the d
// loop: the initial store and the accumulator's store die and only the
// quotient (7 bits) is stored, once per j body, so s is replicable: Vitis
// 4096 x 7, 15 copies x 2 = 30 (kernel w9r22p_c1_accdiv; c2 without the
// division 60, c4 `/= 16` 45; c3, whose d loop also reads s, keeps 16 bits).
// With the key off every store stays: 16 bits, not replicable, 4.
// CHECK: 4096x7b -> RAM_1WNR, 15 copies
// CHECK: Total BRAM: 30
// OFF: Total BRAM: 4
module {
  func.func @_Z3topPA128_KsS1_Ps(%arg0: memref<64x128xi16>, %arg1: memref<64x128xi16>, %arg2: memref<64xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c768_i32 = arith.constant 768 : i32
    %c1_i32 = arith.constant 1 : i32
    %c10_i32 = arith.constant 10 : i32
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "s"} : memref<64x64xi16>
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 64 {
        affine.store %c0_i16, %alloca[%arg3, %arg4] : memref<64x64xi16>
        %0 = affine.for %arg5 = 0 to 128 iter_args(%arg6 = %c0_i16) -> (i16) {
          %5 = affine.load %arg0[%arg3, %arg5] : memref<64x128xi16>
          %6 = arith.extsi %5 : i16 to i32
          %7 = affine.load %arg1[%arg4, %arg5] : memref<64x128xi16>
          %8 = arith.extsi %7 : i16 to i32
          %9 = arith.muli %6, %8 : i32
          %10 = arith.shrsi %9, %c10_i32 : i32
          %11 = arith.trunci %10 : i32 to i16
          %12 = arith.addi %arg6, %11 : i16
          affine.store %12, %alloca[%arg3, %arg4] : memref<64x64xi16>
          affine.yield %12 : i16
        }
        %1 = affine.load %alloca[%arg3, %arg4] : memref<64x64xi16>
        %2 = arith.extsi %1 : i16 to i32
        %3 = arith.divsi %2, %c768_i32 : i32
        %4 = arith.trunci %3 : i32 to i16
        affine.store %4, %alloca[%arg3, %arg4] : memref<64x64xi16>
      }
    }
    affine.for %arg3 = 0 to 64 {
      %0 = affine.for %arg4 = 0 to 64 iter_args(%arg5 = %c0_i16) -> (i16) {
        %1 = arith.index_cast %arg4 : index to i32
        %2 = affine.load %alloca[%arg3, %arg4] : memref<64x64xi16>
        %3 = arith.extsi %2 : i16 to i32
        %4 = arith.addi %1, %c1_i32 : i32
        %5 = arith.trunci %4 : i32 to i16
        %6 = arith.extsi %5 : i16 to i32
        %7 = arith.muli %3, %6 : i32
        %8 = arith.trunci %7 : i32 to i16
        %9 = arith.addi %arg5, %8 : i16
        affine.yield %9 : i16
      }
      affine.store %0, %arg2[%arg3] : memref<64xi16>
    }
    return
  }
}
