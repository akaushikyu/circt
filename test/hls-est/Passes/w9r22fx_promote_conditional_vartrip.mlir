// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_KsS1_iPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA128_KsS1_iPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_KsS1_iPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA128_KsS1_iPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.pipeline_decision.promote_conditional_accesses=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 22 review fix (D5 x D2): the conditional accumulation with a
// run-time inner trip count is promoted before the decision without the
// clean-up, so the initial store and 16 bits stay: 15 copies x 4 = 60 (kernel
// w9r22fx_f7_condacc_vartrip, Vitis 60).
// CHECK: Total BRAM: 60
// OFF: Total BRAM: 4
module {
  func.func @_Z3topPA128_KsS1_iPs(%arg0: memref<64x128xi16>, %arg1: memref<64x128xi16>, %arg2: i32, %arg3: memref<64xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c9_i32 = arith.constant 9 : i32
    %c1_i32 = arith.constant 1 : i32
    %c10_i32 = arith.constant 10 : i32
    %c127_i32 = arith.constant 127 : i32
    %c0_i16 = arith.constant 0 : i16
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "s"} : memref<64x64xi16>
    %0 = arith.index_cast %arg2 : i32 to index
    affine.for %arg4 = 0 to 64 {
      affine.for %arg5 = 0 to 64 {
        affine.store %c0_i16, %alloca[%arg4, %arg5] : memref<64x64xi16>
        %1 = affine.for %arg6 = 0 to %0 iter_args(%arg7 = %c0_i16) -> (i16) {
          %6 = arith.index_cast %arg6 : index to i32
          %7 = arith.andi %6, %c127_i32 : i32
          %8 = arith.index_cast %7 : i32 to index
          %9 = memref.load %arg0[%arg4, %8] : memref<64x128xi16>
          %10 = arith.extsi %9 : i16 to i32
          %11 = arith.cmpi sgt, %10, %c0_i32 : i32
          %12 = scf.if %11 -> (i16) {
            %13 = memref.load %arg0[%arg4, %8] : memref<64x128xi16>
            %14 = arith.extsi %13 : i16 to i32
            %15 = memref.load %arg1[%arg5, %8] : memref<64x128xi16>
            %16 = arith.extsi %15 : i16 to i32
            %17 = arith.muli %14, %16 : i32
            %18 = arith.shrsi %17, %c10_i32 : i32
            %19 = arith.trunci %18 : i32 to i16
            %20 = arith.addi %arg7, %19 : i16
            affine.store %20, %alloca[%arg4, %arg5] : memref<64x64xi16>
            scf.yield %20 : i16
          } else {
            scf.yield %arg7 : i16
          }
          affine.yield %12 : i16
        } {hls.loop_tripcount = [{avg = 64 : i32, max = 128 : i32, min = 0 : i32}]}
        %2 = affine.load %alloca[%arg4, %arg5] : memref<64x64xi16>
        %3 = arith.extsi %2 : i16 to i32
        %4 = arith.shrsi %3, %c9_i32 : i32
        %5 = arith.trunci %4 : i32 to i16
        affine.store %5, %alloca[%arg4, %arg5] : memref<64x64xi16>
      }
    }
    affine.for %arg4 = 0 to 64 {
      %1 = affine.for %arg5 = 0 to 64 iter_args(%arg6 = %c0_i16) -> (i16) {
        %2 = arith.index_cast %arg5 : index to i32
        %3 = affine.load %alloca[%arg4, %arg5] : memref<64x64xi16>
        %4 = arith.extsi %3 : i16 to i32
        %5 = arith.addi %2, %c1_i32 : i32
        %6 = arith.trunci %5 : i32 to i16
        %7 = arith.extsi %6 : i16 to i32
        %8 = arith.muli %4, %7 : i32
        %9 = arith.trunci %8 : i32 to i16
        %10 = arith.addi %arg6, %9 : i16
        affine.yield %10 : i16
      }
      affine.store %1, %arg3[%arg4] : memref<64xi16>
    }
    return
  }
}
