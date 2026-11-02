// RUN: hls-est %s --symbol-privatize=exclude=_Z7fls_topPA16_sS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7fls_topPA16_sS0_S0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z7fls_topPA16_sS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7fls_topPA16_sS0_S0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.pipeline_decision.sink_parent_code=false' --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// W9r8 (2026-10-20): VITIS_NOTES N65: the straight-line code of a loop that
// is flattened into a pipelined child (hls.flattened_parents) runs in the
// pipeline, so its accesses count in the pipeline's port demand. A 16 x 16
// version of kernel w9r8p_fl_pre (Vitis, 64 x 64: Bl RAM_1WNR 60, II 2): the
// 16 reads of Bl[k][j] in the k body are charged to the flattened jj
// pipeline (RAM_1WNR); without the rule they are a sequential scope (RAM_2P).
// The II was 5 (every Cl store a store_enable on all 16 banks); with
// tool.hls.partitioning.reachable_store_banks (OPEN_ISSUES O150, W9r15) copy u
// writes bank u only and the 16 Bl reads bound it: II 1, Bl 15 copies (16;
// Vitis at 64 x 64: II 2, Bl 15 copies x 4 = 60).
// MLIR from the installed cgeist d0e92867 with the real headers.
// CHECK: Bl (alloca)
// CHECK: ram type: RAM_1WNR -- {{.*}}: 16R+0W per iteration
// CHECK: Total BRAM: 16
// OFF: Bl (alloca)
// OFF: ram type: RAM_2P
// OFF: Total BRAM: 2
module {
  func.func @_Z7fls_topPA16_sS0_S0_(%arg0: memref<16x16xi16>, %arg1: memref<16x16xi16>, %arg2: memref<16x16xi16>) attributes {hls.orig_name = "fls_top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "t"}], hls.preserve, polygeist.varname = "t"} : memref<16xi16>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "Cl"}], hls.preserve, polygeist.varname = "Cl"} : memref<16x16xi16>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Bl"} : memref<16x16xi16>
    %alloca_2 = memref.alloca() {hls.preserve, polygeist.varname = "Al"} : memref<16x16xi16>
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 16 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<16x16xi16>
        affine.store %0, %alloca_2[%arg3, %arg4] : memref<16x16xi16>
        %1 = affine.load %arg1[%arg3, %arg4] : memref<16x16xi16>
        affine.store %1, %alloca_1[%arg3, %arg4] : memref<16x16xi16>
        affine.store %c0_i16, %alloca_0[%arg3, %arg4] : memref<16x16xi16>
      }
    }
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 16 {
        %0 = affine.load %alloca_2[%arg3, %arg4] : memref<16x16xi16>
        %1 = arith.extsi %0 : i16 to i32
        affine.for %arg5 = 0 to 16 {
          %2 = affine.load %alloca_1[%arg4, %arg5] : memref<16x16xi16>
          %3 = arith.extsi %2 : i16 to i32
          %4 = arith.muli %1, %3 : i32
          %5 = arith.trunci %4 : i32 to i16
          affine.store %5, %alloca[%arg5] : memref<16xi16>
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
        affine.for %arg5 = 0 to 16 {
          %2 = affine.load %alloca[%arg5] : memref<16xi16>
          %3 = affine.load %alloca_0[%arg3, %arg5] : memref<16x16xi16>
          %4 = arith.addi %3, %2 : i16
          affine.store %4, %alloca_0[%arg3, %arg5] : memref<16x16xi16>
        } {hls.unroll = [{factor = 8 : i32, skip_exit_check = false}]}
      }
    }
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 16 {
        %0 = affine.load %alloca_0[%arg3, %arg4] : memref<16x16xi16>
        affine.store %0, %arg2[%arg3, %arg4] : memref<16x16xi16>
      }
    }
    return
  }
}
