// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsPA32_sPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsPA32_sPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.fold_nested_constant_guards=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// OPEN_ISSUES O151, kernel w9r15i_ag_nest (Vitis 2025.1 td=off: 84): if (k + kk < N)
// guards of a k loop and a kk loop, both unrolled in a pipelined j loop; V cyclic
// 16 on dim 1 (N = 100). The guards whose operands are nested applies of
// constants fold (tool.hls.pipeline_decision.fold_nested_constant_guards): banks
// 0..3 are read 7 times (6 copies), banks 4..15 6 times (5 copies): 84.
// Off run: every bank read 7 times (96).
// CHECK: Total BRAM: 84
// OFF: Total BRAM: 96

#set = affine_set<(d0, d1) : (-d0 - d1 + 99 >= 0)>
module {
  func.func @_Z3topPsPA32_sPi(%arg0: memref<100xi16>, %arg1: memref<100x32xi16>, %arg2: memref<32xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 16 : i32, kind = "cyclic", variable = "V"}], hls.preserve, polygeist.varname = "V"} : memref<100x32xi16>
    affine.for %arg3 = 0 to 100 {
      affine.for %arg4 = 0 to 32 {
        %0 = affine.load %arg1[%arg3, %arg4] : memref<100x32xi16>
        affine.store %0, %alloca[%arg3, %arg4] : memref<100x32xi16>
      }
    }
    affine.for %arg3 = 0 to 32 {
      %0 = affine.for %arg4 = 0 to 100 step 16 iter_args(%arg5 = %c0_i32) -> (i32) {
        %1 = affine.for %arg6 = 0 to 16 iter_args(%arg7 = %arg5) -> (i32) {
          %2 = affine.if #set(%arg6, %arg4) -> i32 {
            %3 = affine.load %arg0[%arg4 + %arg6] : memref<100xi16>
            %4 = arith.extsi %3 : i16 to i32
            %5 = affine.load %alloca[%arg4 + %arg6, %arg3] : memref<100x32xi16>
            %6 = arith.extsi %5 : i16 to i32
            %7 = arith.muli %4, %6 : i32
            %8 = arith.addi %arg7, %7 : i32
            affine.yield %8 : i32
          } else {
            affine.yield %arg7 : i32
          }
          affine.yield %2 : i32
        }
        affine.yield %1 : i32
      }
      affine.store %0, %arg2[%arg3] : memref<32xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
