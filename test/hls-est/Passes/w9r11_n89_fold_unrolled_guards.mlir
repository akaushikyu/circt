// RUN: hls-est %s --symbol-privatize=exclude=_Z6sa_topRN3hls6streamIfLi0EEEPA64_KfPA64_f --symbol-dce --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6sa_topRN3hls6streamIfLi0EEEPA64_KfPA64_f --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --config-set tool.hls.pipeline_decision.fold_unrolled_guards=false | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --symbol-privatize=exclude=_Z6sa_topRN3hls6streamIfLi0EEEPA64_KfPA64_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sa_topRN3hls6streamIfLi0EEEPA64_KfPA64_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug --config-set scheduling.timing.operator_latencies.stream_read=2 --config-set scheduling.timing.operator_latencies.stream_write=1 -o /dev/null 2>&1 | FileCheck %s --check-prefix=STRM
// RUN: hls-est %s --symbol-privatize=exclude=_Z6sa_topRN3hls6streamIfLi0EEEPA64_KfPA64_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sa_topRN3hls6streamIfLi0EEEPA64_KfPA64_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug --config-set scheduling.timing.operator_latencies.stream_read=2 --config-set scheduling.timing.operator_latencies.stream_write=1 --config-set tool.hls.pipeline_decision.fold_unrolled_guards=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=STRMOFF
// W9r11-impl (2026-10-22): VITIS_NOTES N89 (OPEN_ISSUES O120): `for k (unrolled 8) { if (k + j * 8 == 0) w = s.read(); dst[i][k + j * 8] = src[i][k + j * 8] * w; }`
// in a pipelined j loop. After the unroll each copy keeps affine.if #set(%cK, %j) with #set = (d0 == 0, d1 == 0); only copy 0 can ever read.
// --auto-pipeline-unroll now folds the constant operands into the set and drops the arm that never runs (tool.hls.pipeline_decision.fold_unrolled_guards).
// Vitis: one stream read per iteration, j loop II 1. With N82's stream classes hls-est's j loop goes II 8 -> 1 (STRM / STRMOFF).
// Kernel w9r11p_sa_cnd2 (~/hls-est-work/exp-src/w9r11p/sa_cnd2.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: 16 BRAM_18K (II 1 in the j loop).
// CHECK-COUNT-1: affine.if
// CHECK-NOT: affine.if
// OFF-COUNT-8: affine.if
// OFF-NOT: affine.if
// STRM: scope pipeline @ {{.*}}:{{[0-9]+}}:12 ii=1:
// STRM: Total BRAM: 16{{$}}
// STRMOFF: scope pipeline @ {{.*}}:{{[0-9]+}}:12 ii=8:
// STRMOFF: Total BRAM: 16{{$}}

#set = affine_set<(d0, d1) : (d0 == 0, d1 == 0)>
module {
  func.func @_Z6sa_topRN3hls6streamIfLi0EEEPA64_KfPA64_f(%arg0: memref<?xi32>, %arg1: memref<32x64xf32>, %arg2: memref<32x64xf32>) attributes {hls.orig_name = "sa_top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 8 : i32, kind = "cyclic", variable = "dst"}], hls.preserve, polygeist.varname = "dst"} : memref<32x64xf32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 8 : i32, kind = "cyclic", variable = "src"}], hls.preserve, polygeist.varname = "src"} : memref<32x64xf32>
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 64 {
        %1 = affine.load %arg1[%arg3, %arg4] : memref<32x64xf32>
        affine.store %1, %alloca_0[%arg3, %arg4] : memref<32x64xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %0 = affine.for %arg3 = 0 to 32 iter_args(%arg4 = %cst) -> (f32) {
      %1 = affine.for %arg5 = 0 to 8 iter_args(%arg6 = %arg4) -> (f32) {
        %2 = affine.for %arg7 = 0 to 8 iter_args(%arg8 = %arg6) -> (f32) {
          %3 = affine.if #set(%arg7, %arg5) -> f32 {
            %6 = func.call @_ZN3hls6streamIfLi0EE4readEv(%arg0) : (memref<?xi32>) -> f32
            affine.yield %6 : f32
          } else {
            affine.yield %arg8 : f32
          }
          %4 = affine.load %alloca_0[%arg3, %arg7 + %arg5 * 8] : memref<32x64xf32>
          %5 = arith.mulf %4, %3 : f32
          affine.store %5, %alloca[%arg3, %arg7 + %arg5 * 8] : memref<32x64xf32>
          affine.yield %3 : f32
        }
        affine.yield %2 : f32
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.yield %1 : f32
    }
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 64 {
        %1 = affine.load %alloca[%arg3, %arg4] : memref<32x64xf32>
        affine.store %1, %arg2[%arg3, %arg4] : memref<32x64xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func private @_ZN3hls6streamIfLi0EE4readEv(memref<?xi32>) -> f32 attributes {hls.orig_name = "read", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
}
