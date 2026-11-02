// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA12_A12_sPA8_A8_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA12_A12_sPA8_A8_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA12_A12_sPA8_A8_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA12_A12_sPA8_A8_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.partitioning.drop_unread_banks=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N157: buf[32][12][12] complete on dim 2, all
// 12 rows written, a 3 x 3 window over an 8 x 8 tile reads rows 0..9: Vitis 10
// banks, 10 BRAM (kernel w9r21p_k1_deadbank; YOLOv4-Tiny L5 conv_in_buf). Off:
// 12. MLIR from the installed cgeist 5523df29.
// CHECK-COUNT-10: 384x16b -> RAM_1P (x36/port) = 1 BRAM_18K
// CHECK-NOT: 384x16b
// CHECK: Total BRAM: 10
// OFF: Total BRAM: 12
module {
  func.func @_Z3topPA12_A12_sPA8_A8_i(%arg0: memref<32x12x12xi16>, %arg1: memref<32x8x8xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "buf"}], hls.preserve, polygeist.varname = "buf"} : memref<32x12x12xi16>
    affine.for %arg2 = 0 to 32 {
      affine.for %arg3 = 0 to 12 {
        affine.for %arg4 = 0 to 12 {
          %0 = affine.load %arg0[%arg2, %arg3, %arg4] : memref<32x12x12xi16>
          affine.store %0, %alloca[%arg2, %arg3, %arg4] : memref<32x12x12xi16>
        }
      }
    }
    affine.for %arg2 = 0 to 32 {
      affine.for %arg3 = 0 to 3 {
        affine.for %arg4 = 0 to 3 {
          affine.for %arg5 = 0 to 8 {
            affine.for %arg6 = 0 to 8 {
              %0 = affine.load %alloca[%arg2, %arg6 + %arg3, %arg5 + %arg4] : memref<32x12x12xi16>
              %1 = arith.extsi %0 : i16 to i32
              %2 = affine.load %arg1[%arg2, %arg6, %arg5] : memref<32x8x8xi32>
              %3 = arith.addi %2, %1 : i32
              affine.store %3, %arg1[%arg2, %arg6, %arg5] : memref<32x8x8xi32>
            }
          } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
        }
      }
    }
    return
  }
}
