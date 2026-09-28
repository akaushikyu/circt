// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.do_while_flatten_refusal=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s --check-prefix=LOOPS
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --config-set tool.hls.pipeline_decision.do_while_flatten_refusal=false | FileCheck %s --check-prefix=LOOPSOFF

// VITIS_NOTES N96 (W9r13 review finding 5), kernel w9r13rev_dv_s2k (Vitis 2025.1 td=off: j pipelined
// alone, 62 trips, i sequential): `i += 2` and rows i + 2k: the subscript i + 2 is the parent's next index;
// --affine-loop-normalize leaves i as affine.apply (d0 * 2) of the normalized index. The refusal shows in
// the loop attributes after --auto-pipeline-unroll.
// LOOPS: hls.flatten_refused
// LOOPSOFF-NOT: hls.flatten_refused
// CHECK-DAG: scope pipeline @ {{.*}}:30:7 ii=1:
// CHECK-DAG: scope pipeline @ {{.*}}:23:5 ii=1:
// CHECK: Total BRAM: 64
// OFF-DAG: scope pipeline @ {{.*}}:30:7 ii=1:
// OFF-DAG: scope pipeline @ {{.*}}:23:5 ii=1:
// OFF: Total BRAM: 64
module {
  func.func @_Z3topPKiPi(%arg0: memref<4096xi32>, %arg1: memref<4096xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "T"} : memref<64x64xi32>
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 64 {
        %0 = affine.load %arg0[%arg3 + %arg2 * 64] : memref<4096xi32>
        affine.store %0, %alloca[%arg2, %arg3] : memref<64x64xi32>
      }
    }
    affine.for %arg2 = 0 to 59 step 2 {
      affine.for %arg3 = 0 to 62 {
        %0 = affine.for %arg4 = 0 to 3 iter_args(%arg5 = %c0_i32) -> (i32) {
          %1 = arith.index_cast %arg4 : index to i32
          %2 = affine.for %arg6 = 0 to 3 iter_args(%arg7 = %arg5) -> (i32) {
            %3 = arith.index_cast %arg6 : index to i32
            %4 = affine.load %alloca[%arg2 + %arg4 * 2, %arg3 + %arg6] : memref<64x64xi32>
            %5 = arith.addi %1, %3 : i32
            %6 = arith.addi %5, %c1_i32 : i32
            %7 = arith.muli %4, %6 : i32
            %8 = arith.addi %arg7, %7 : i32
            affine.yield %8 : i32
          }
          affine.yield %2 : i32
        }
        affine.store %0, %arg1[%arg3 + %arg2 * 64] : memref<4096xi32>
      }
    }
    return
  }
}
