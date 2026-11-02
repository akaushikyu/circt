// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPK7ap_uintILi64EEPKS_ILi6EEPS0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPK7ap_uintILi64EEPKS_ILi6EEPS0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPK7ap_uintILi64EEPKS_ILi6EEPS0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPK7ap_uintILi64EEPKS_ILi6EEPS0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.backend.storage_selector.distributed_impl= -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N171. `#pragma HLS bind_storage
// variable=t type=ram_2p impl=lutram` on a 64 x 64-bit array (4096 bits):
// Vitis RAM_2P_LUTRAM_1R1W, 0 BRAM (kernel w9r22p_g2_bind_lutram; the legacy
// `RESOURCE core=RAM_2P_LUTRAM` is the same attribute, g1; without the pragma
// 4, g3). With the key off the impl is ignored, 4 BRAM. MLIR from the installed cgeist
// 65aa635a (--shim real).
// CHECK: excluded from BRAM accounting
// CHECK: Total BRAM: 0
// OFF: Total BRAM: 4
module {
  func.func @_Z3topPK7ap_uintILi64EEPKS_ILi6EEPS0_(%arg0: memref<64xi64>, %arg1: memref<64xi6>, %arg2: memref<64xi64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i64 = arith.constant 3 : i64
    %alloca = memref.alloca() {hls.bind_storage = [{impl = "lutram", type = "ram_2p", variable = "t"}], hls.preserve, polygeist.varname = "t"} : memref<64xi64>
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %arg0[%arg3] : memref<64xi64>
      %1 = arith.shrui %0, %c3_i64 : i64
      %2 = arith.xori %0, %1 : i64
      affine.store %2, %alloca[%arg3] : memref<64xi64>
    }
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %arg1[%arg3] : memref<64xi6>
      %1 = arith.index_castui %0 : i6 to index
      %2 = memref.load %alloca[%1] : memref<64xi64>
      %3 = arith.extui %2 : i64 to i65
      %4 = affine.load %alloca[%arg3] : memref<64xi64>
      %5 = arith.extui %4 : i64 to i65
      %6 = arith.addi %3, %5 : i65
      %7 = arith.trunci %6 : i65 to i64
      affine.store %7, %arg2[%arg3] : memref<64xi64>
    }
    return
  }
}
