// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_KsS1_Ps --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA128_KsS1_Ps math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_KsS1_Ps --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA128_KsS1_Ps math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.pipeline_decision.promote_conditional_accesses=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 22 review fix (D5): a conditional accumulation `if (c) s[i][j] +=
// x` is promoted too (LLVM LICM, a non-escaping local): only the quotient's
// store is left, 7 bits, 15 copies, 30 (kernel w9r22rv_k09_condacc, Vitis 30).
// Off: the store in the if stays, two stores per loop body, RAM_T2P 4.
// CHECK: Total BRAM: 30
// OFF: Total BRAM: 4
module {
  func.func @_Z3topPA128_KsS1_Ps(%arg0: memref<64x128xi16>, %arg1: memref<64x128xi16>, %arg2: memref<64xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c9_i32 = arith.constant 9 : i32
    %c1_i32 = arith.constant 1 : i32
    %c10_i32 = arith.constant 10 : i32
    %c0_i16 = arith.constant 0 : i16
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "s"} : memref<64x64xi16>
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 64 {
        affine.store %c0_i16, %alloca[%arg3, %arg4] : memref<64x64xi16>
        %0 = affine.for %arg5 = 0 to 128 iter_args(%arg6 = %c0_i16) -> (i16) {
          %5 = affine.load %arg0[%arg3, %arg5] : memref<64x128xi16>
          %6 = arith.extsi %5 : i16 to i32
          %7 = arith.cmpi sgt, %6, %c0_i32 : i32
          %8 = scf.if %7 -> (i16) {
            %9 = affine.load %arg0[%arg3, %arg5] : memref<64x128xi16>
            %10 = arith.extsi %9 : i16 to i32
            %11 = affine.load %arg1[%arg4, %arg5] : memref<64x128xi16>
            %12 = arith.extsi %11 : i16 to i32
            %13 = arith.muli %10, %12 : i32
            %14 = arith.shrsi %13, %c10_i32 : i32
            %15 = arith.trunci %14 : i32 to i16
            %16 = arith.addi %arg6, %15 : i16
            affine.store %16, %alloca[%arg3, %arg4] : memref<64x64xi16>
            scf.yield %16 : i16
          } else {
            scf.yield %arg6 : i16
          }
          affine.yield %8 : i16
        }
        %1 = affine.load %alloca[%arg3, %arg4] : memref<64x64xi16>
        %2 = arith.extsi %1 : i16 to i32
        %3 = arith.shrsi %2, %c9_i32 : i32
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
