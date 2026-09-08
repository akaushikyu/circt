// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.partitioning.compound_assign_two_stores=false' -o /dev/null | FileCheck %s --check-prefix=CMPDOFF
// W9r7 review fixes (2026-10-20): VITIS_NOTES N38 R-cmpd: `A[b][i]++` on ap_fixed goes through operator+= and the cross-format operator= (cgeist marks it hls.ap_compound_assign like +=): two stores per bank, never RAM_1WNR.
// Kernel w9r7rev_rc_inc (~/hls-est-work/exp-src/w9r7rev/rc_inc.cpp); MLIR from cgeist c3b (Polygeist branch w9r7-cgeist, W9r7 review fixes) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 2 BRAM_18K.
// With tool.hls.partitioning.compound_assign_two_stores=false (CMPDOFF) the rule is off.
// CMPDOFF: Total BRAM: 14{{$}}

// CHECK: Total BRAM: 2{{$}}

module {
  func.func @_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_(%arg0: memref<2x1024xi16>, %arg1: memref<2x128xi16>, %arg2: i16) attributes {hls.orig_name = "k", llvm.linkage = #llvm.linkage<external>} {
    %c2048_i32 = arith.constant 2048 : i32
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() : memref<i16>
    %0 = llvm.mlir.undef : i16
    affine.store %0, %alloca[] : memref<i16>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "A"}], hls.preserve, polygeist.varname = "A"} : memref<2x1024xi16>
    affine.for %arg3 = 0 to 2 {
      affine.for %arg4 = 0 to 1024 {
        %1 = affine.load %arg0[%arg3, %arg4] : memref<2x1024xi16>
        affine.store %1, %alloca_0[%arg3, %arg4] : memref<2x1024xi16>
      }
    }
    affine.for %arg3 = 0 to 2 {
      affine.for %arg4 = 0 to 1024 {
        %1 = affine.load %alloca_0[%arg3, %arg4] : memref<2x1024xi16>
        %2 = arith.extsi %1 : i16 to i32
        %3 = arith.addi %2, %c2048_i32 : i32
        %4 = arith.trunci %3 : i32 to i16
        affine.store %4, %alloca_0[%arg3, %arg4] {hls.ap_compound_assign} : memref<2x1024xi16>
      }
    }
    affine.for %arg3 = 0 to 2 {
      affine.for %arg4 = 0 to 128 {
        affine.store %c0_i16, %alloca[] : memref<i16>
        affine.for %arg5 = 0 to 8 {
          %2 = affine.load %alloca[] : memref<i16>
          %3 = affine.load %alloca_0[%arg3, %arg5 + %arg4 * 8] : memref<2x1024xi16>
          %4 = arith.extsi %2 : i16 to i32
          %5 = arith.extsi %3 : i16 to i32
          %6 = arith.addi %4, %5 : i32
          %7 = arith.trunci %6 : i32 to i16
          affine.store %7, %alloca[] {hls.ap_compound_assign} : memref<i16>
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
        %1 = affine.load %alloca[] : memref<i16>
        affine.store %1, %arg1[%arg3, %arg4] : memref<2x128xi16>
      }
    }
    return
  }
}
