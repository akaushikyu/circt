// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPK7ap_uintILi128EEPS0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPK7ap_uintILi128EEPS0_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPK7ap_uintILi128EEPS0_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPK7ap_uintILi128EEPS0_i math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.memory_architecture.replication.user_plain_ram_pins_kind=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N173. Kernel w9r23p_b5_2p_bind_seq (~/hls-est-work/exp-src/w9r23p/b5_2p_bind_seq.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 4 BRAM.
// Control: bound ram_2p, one access per cycle: priced on the ports used, x36: 4 either way.
// CHECK: Total BRAM: 4{{$}}
// OFF: Total BRAM: 4{{$}}
module {
  func.func @_Z3topPK7ap_uintILi128EEPS0_i(%arg0: memref<512xi128>, %arg1: memref<512xi128>, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i130 = arith.constant 1 : i130
    %c511_i32 = arith.constant 511 : i32
    %c7_i32 = arith.constant 7 : i32
    %alloca = memref.alloca() {hls.bind_storage = [{impl = "bram", type = "ram_2p", variable = "buf"}], hls.preserve, polygeist.varname = "buf"} : memref<512xi128>
    affine.for %arg3 = 0 to 512 {
      %1 = affine.load %arg0[%arg3] : memref<512xi128>
      %2 = arith.extui %1 : i128 to i130
      %3 = arith.addi %2, %c1_i130 : i130
      %4 = arith.trunci %3 : i130 to i128
      affine.store %4, %alloca[%arg3] : memref<512xi128>
    } {hls.pipeline_off}
    %0 = arith.extsi %arg2 : i32 to i128
    affine.for %arg3 = 0 to 512 {
      %1 = arith.index_cast %arg3 : index to i32
      %2 = arith.muli %1, %c7_i32 : i32
      %3 = arith.andi %2, %c511_i32 : i32
      %4 = arith.index_cast %3 : i32 to index
      %5 = memref.load %alloca[%4] : memref<512xi128>
      %6 = arith.xori %5, %0 : i128
      affine.store %6, %arg1[%arg3] : memref<512xi128>
    } {hls.pipeline_off}
    return
  }
}
