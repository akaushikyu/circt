// RUN: hls-est %s --symbol-privatize=exclude=_Z8pool_topPA8_A8_8ap_fixedILi16ELi2EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA4_A4_S2_PA4_A4_7ap_uintILi2EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z8pool_topPA8_A8_8ap_fixedILi16ELi2EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA4_A4_S2_PA4_A4_7ap_uintILi2EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z8pool_topPA8_A8_8ap_fixedILi16ELi2EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA4_A4_S2_PA4_A4_7ap_uintILi2EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z8pool_topPA8_A8_8ap_fixedILi16ELi2EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA4_A4_S2_PA4_A4_7ap_uintILi2EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.partitioning.steer_window_groups=false -o /dev/null | FileCheck %s --check-prefix=WOFF
// RUN: hls-est %s --symbol-privatize=exclude=_Z8pool_topPA8_A8_8ap_fixedILi16ELi2EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA4_A4_S2_PA4_A4_7ap_uintILi2EE --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z8pool_topPA8_A8_8ap_fixedILi16ELi2EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA4_A4_S2_PA4_A4_7ap_uintILi2EE math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug-json=%t.json -o /dev/null
// RUN: FileCheck %s --check-prefix=JSON < %t.json
// W9r9 review fix D8: the debug JSON shows the steered load groups and the forwarded if-arm reloads of each bank.
// JSON: "forwarded_reloads": 3,
// JSON: "steered_groups": [
// JSON-NEXT: 2,
// JSON-NEXT: 2
// W9r9-impl (2026-10-21): VITIS_NOTES N74 (with the nested-reload forwarding of --memory-banking-bram): Explainable-ML's 2x2 max pool with argmax re-reads the max inside each if arm; the reload repeats the steered load's address and is forwarded, so each of the 8 banks of X (dim 3 complete) is read once per window column.
// Kernel w9r9i_pool_reload (~/hls-est-work/coord/scratch/w9r9i/k2/pool_reload.cpp); MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off (run w9r9i_pool_reload): X 8 banks RAM_AUTO_1R1W x 1 = 8 BRAM_18K.
// With tool.hls.partitioning.steer_window_groups=false (WOFF): 24.
// WOFF: Total BRAM: 24{{$}}
// CHECK: Total BRAM: 8{{$}}

module {
  func.func @_Z8pool_topPA8_A8_8ap_fixedILi16ELi2EL9ap_q_mode5EL9ap_o_mode3ELi0EEPA4_A4_S2_PA4_A4_7ap_uintILi2EE(%arg0: memref<8x8x8xi16>, %arg1: memref<8x4x4xi16>, %arg2: memref<8x4x4xi2>) attributes {hls.orig_name = "pool_top", llvm.linkage = #llvm.linkage<external>} {
    %c-1_i2 = arith.constant -1 : i2
    %c-2_i2 = arith.constant -2 : i2
    %c-1 = arith.constant -1 : index
    %c2 = arith.constant 2 : index
    %c0 = arith.constant 0 : index
    %alloca = memref.alloca() {hls.array_partition = [{dim = 3 : i32, kind = "complete", variable = "X"}], hls.preserve, polygeist.varname = "X"} : memref<8x8x8xi16>
    affine.for %arg3 = 0 to 8 {
      affine.for %arg4 = 0 to 8 {
        affine.for %arg5 = 0 to 8 {
          %0 = affine.load %arg0[%arg3, %arg4, %arg5] : memref<8x8x8xi16>
          affine.store %0, %alloca[%arg3, %arg4, %arg5] : memref<8x8x8xi16>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    }
    affine.for %arg3 = 0 to 8 {
      affine.for %arg4 = 0 to 8 step 2 {
        %0 = arith.cmpi slt, %arg4, %c0 : index
        %1 = arith.subi %c-1, %arg4 : index
        %2 = arith.select %0, %1, %arg4 : index
        %3 = arith.divsi %2, %c2 : index
        %4 = arith.subi %c-1, %3 : index
        %5 = arith.select %0, %4, %3 : index
        affine.for %arg5 = 0 to 8 step 2 {
          %6 = affine.load %alloca[%arg3, %arg4, %arg5] : memref<8x8x8xi16>
          %7 = arith.extsi %6 : i16 to i32
          %8 = affine.load %alloca[%arg3, %arg4, %arg5 + 1] : memref<8x8x8xi16>
          %9 = arith.extsi %8 : i16 to i32
          %10 = arith.cmpi slt, %7, %9 : i32
          %11 = arith.extui %10 : i1 to i2
          %12 = scf.if %10 -> (i16) {
            %31 = affine.load %alloca[%arg3, %arg4, %arg5 + 1] : memref<8x8x8xi16>
            scf.yield %31 : i16
          } else {
            scf.yield %6 : i16
          }
          %13 = arith.extsi %12 : i16 to i32
          %14 = affine.load %alloca[%arg3, %arg4 + 1, %arg5] : memref<8x8x8xi16>
          %15 = arith.extsi %14 : i16 to i32
          %16 = arith.cmpi slt, %13, %15 : i32
          %17 = arith.select %16, %c-2_i2, %11 : i2
          %18 = scf.if %16 -> (i16) {
            %31 = affine.load %alloca[%arg3, %arg4 + 1, %arg5] : memref<8x8x8xi16>
            scf.yield %31 : i16
          } else {
            scf.yield %12 : i16
          }
          %19 = arith.extsi %18 : i16 to i32
          %20 = affine.load %alloca[%arg3, %arg4 + 1, %arg5 + 1] : memref<8x8x8xi16>
          %21 = arith.extsi %20 : i16 to i32
          %22 = arith.cmpi slt, %19, %21 : i32
          %23 = arith.select %22, %c-1_i2, %17 : i2
          %24 = scf.if %22 -> (i16) {
            %31 = affine.load %alloca[%arg3, %arg4 + 1, %arg5 + 1] : memref<8x8x8xi16>
            scf.yield %31 : i16
          } else {
            scf.yield %18 : i16
          }
          %25 = arith.cmpi slt, %arg5, %c0 : index
          %26 = arith.subi %c-1, %arg5 : index
          %27 = arith.select %25, %26, %arg5 : index
          %28 = arith.divsi %27, %c2 : index
          %29 = arith.subi %c-1, %28 : index
          %30 = arith.select %25, %29, %28 : index
          memref.store %24, %arg1[%arg3, %5, %30] : memref<8x4x4xi16>
          memref.store %23, %arg2[%arg3, %5, %30] : memref<8x4x4xi2>
        }
      }
    }
    return
  }
}
