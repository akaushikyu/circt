// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N38 R-cmpd: an ap_fixed `/=` to an element of a completely partitioned dimension indexed by a loop counter writes each bank twice (cgeist marks the store hls.ap_compound_assign; banking emits two store_enable per bank), so A is never RAM_1WNR (2 x 1 BRAM, Vitis RAM_AUTO_1R1W).
// Kernel w9r_d1div (~/hls-est-work/coord/scratch/w9r3/k/w9r_d1div.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 2 BRAM_18K.

// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.partitioning.compound_assign_two_stores=false' -o /dev/null | FileCheck %s --check-prefix=CMPDOFF

// With tool.hls.partitioning.compound_assign_two_stores=false (CMPDOFF) the rule is off; the other W9r7 rules stay on.
// CMPDOFF: Total BRAM: 14{{$}}

// CHECK: Total BRAM: 2{{$}}

module {
  func.func @_Z1kPA1024_8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA128_S2_S2_(%arg0: memref<2x1024xi16>, %arg1: memref<2x128xi16>, %arg2: i16) attributes {hls.orig_name = "k", llvm.linkage = #llvm.linkage<external>} {
    %c11_i32 = arith.constant 11 : i32
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() : memref<i16>
    %0 = llvm.mlir.undef : i16
    affine.store %0, %alloca[] : memref<i16>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "A"}], hls.preserve, polygeist.varname = "A"} : memref<2x1024xi16>
    affine.for %arg3 = 0 to 2 {
      affine.for %arg4 = 0 to 1024 {
        %2 = affine.load %arg0[%arg3, %arg4] : memref<2x1024xi16>
        affine.store %2, %alloca_0[%arg3, %arg4] : memref<2x1024xi16>
      }
    }
    %1 = arith.extsi %arg2 : i16 to i32
    affine.for %arg3 = 0 to 2 {
      affine.for %arg4 = 0 to 1024 {
        %2 = affine.load %alloca_0[%arg3, %arg4] : memref<2x1024xi16>
        %3 = arith.extsi %2 : i16 to i32
        %4 = arith.shli %3, %c11_i32 : i32
        %5 = arith.trunci %4 : i32 to i27
        %6 = arith.extsi %5 : i27 to i32
        %7 = arith.divsi %6, %1 : i32
        %8 = arith.trunci %7 : i32 to i16
        affine.store %8, %alloca_0[%arg3, %arg4] {hls.ap_compound_assign} : memref<2x1024xi16>
      }
    }
    affine.for %arg3 = 0 to 2 {
      affine.for %arg4 = 0 to 128 {
        affine.store %c0_i16, %alloca[] : memref<i16>
        affine.for %arg5 = 0 to 8 {
          %3 = affine.load %alloca[] : memref<i16>
          %4 = affine.load %alloca_0[%arg3, %arg5 + %arg4 * 8] : memref<2x1024xi16>
          %5 = arith.extsi %3 : i16 to i32
          %6 = arith.extsi %4 : i16 to i32
          %7 = arith.addi %5, %6 : i32
          %8 = arith.trunci %7 : i32 to i16
          affine.store %8, %alloca[] {hls.ap_compound_assign} : memref<i16>
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
        %2 = affine.load %alloca[] : memref<i16>
        affine.store %2, %arg1[%arg3, %arg4] : memref<2x128xi16>
      }
    }
    return
  }
}
