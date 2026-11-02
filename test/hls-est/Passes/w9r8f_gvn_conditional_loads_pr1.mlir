// RUN: hls-est %s --symbol-privatize=exclude=_Z6pr_topPKiS0_S0_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6pr_topPKiS0_S0_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6pr_topPKiS0_S0_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6pr_topPKiS0_S0_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.middle_end.gvn_conditional_loads=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 8 review defect 6 (class_ece8893 Dehazing update_vmin_vmax reads
// each histogram twice per pipelined iteration, in two non-exclusive ifs):
// kernel w9r8f_pr1, `if (c1[i] > 3) s1 += H[i]; if (c2[i] > 5) s2 += H[i];`
// at II 1. Vitis: H RAM_AUTO_1R1W, 1 BRAM (GVN load PRE: one read per path,
// so one per iteration). The loads become one load before the first if; with
// the rule off they are two reads (RAM_2P, 2). Control kernels: pr2 (the
// second if reads H[255 - i]: Vitis 2 = hls-est), pr3 (a store of H between
// the ifs keeps both reads: Vitis 4, RAM_1WNR = hls-est). MLIR from the
// private W9r8-fix cgeist.
// CHECK: kind=RAM_1P
// CHECK: Total BRAM: 1
// OFF: kind=RAM_2P
// OFF: Total BRAM: 2
module {
  func.func @_Z6pr_topPKiS0_S0_Pi(%arg0: memref<256xi32>, %arg1: memref<256xi32>, %arg2: memref<256xi32>, %arg3: memref<2xi32>) attributes {hls.orig_name = "pr_top", llvm.linkage = #llvm.linkage<external>} {
    %c5_i32 = arith.constant 5 : i32
    %c3_i32 = arith.constant 3 : i32
    %c7_i32 = arith.constant 7 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "H"} : memref<256xi32>
    affine.for %arg4 = 0 to 256 {
      %1 = affine.load %arg0[%arg4] : memref<256xi32>
      %2 = arith.muli %1, %c7_i32 : i32
      affine.store %2, %alloca[%arg4] : memref<256xi32>
    }
    %0:2 = affine.for %arg4 = 0 to 256 iter_args(%arg5 = %c0_i32, %arg6 = %c0_i32) -> (i32, i32) {
      %1 = affine.load %arg1[%arg4] : memref<256xi32>
      %2 = arith.cmpi sgt, %1, %c3_i32 : i32
      %3 = scf.if %2 -> (i32) {
        %7 = affine.load %alloca[%arg4] : memref<256xi32>
        %8 = arith.addi %arg6, %7 : i32
        scf.yield %8 : i32
      } else {
        scf.yield %arg6 : i32
      }
      %4 = affine.load %arg2[%arg4] : memref<256xi32>
      %5 = arith.cmpi sgt, %4, %c5_i32 : i32
      %6 = scf.if %5 -> (i32) {
        %7 = affine.load %alloca[%arg4] : memref<256xi32>
        %8 = arith.addi %arg5, %7 : i32
        scf.yield %8 : i32
      } else {
        scf.yield %arg5 : i32
      }
      affine.yield %6, %3 : i32, i32
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.store %0#1, %arg3[0] : memref<2xi32>
    affine.store %0#0, %arg3[1] : memref<2xi32>
    return
  }
}
