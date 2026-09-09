// RUN: hls-est %s --symbol-privatize=exclude=_Z6st_topPA100_K7ap_uintILi160EEPA100_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6st_topPA100_K7ap_uintILi160EEPA100_S0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: sed -e 's/depth = 256 : i32/depth = 4 : i32/' %s | hls-est --symbol-privatize=exclude=_Z6st_topPA100_K7ap_uintILi160EEPA100_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6st_topPA100_K7ap_uintILi160EEPA100_S0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s --check-prefix=D4
// RUN: hls-est %s --symbol-privatize=exclude=_Z6st_topPA100_K7ap_uintILi160EEPA100_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6st_topPA100_K7ap_uintILi160EEPA100_S0_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.streams.stream_pragma_arrays=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r8 (2026-10-20): VITIS_NOTES N67: a local array of a dataflow region with
// `#pragma HLS stream variable=buf depth=D` is one FIFO of depth D at the
// element width, not a RAM. Kernels w9r8p_st_d256 (Vitis 9 = F(256 x 160):
// `buf_r_U | fifo channel | 160, 256, 1`) and st_d4 (Vitis 0: shift
// registers); control st_pipo (no pragma, a PIPO of 9) is the test of
// dataflow channels. MLIR from the installed cgeist d0e92867 with the real
// headers.
// CHECK: FIFO
// CHECK: Total BRAM: 9
// D4: Total BRAM: 0
// OFF: Total BRAM: 5
module {
  func.func @_Z6st_topPA100_K7ap_uintILi160EEPA100_S0_(%arg0: memref<4x100xi160>, %arg1: memref<4x100xi160>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "st_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, hls.stream = [{depth = 256 : i32, type = "fifo", variable = "buf"}], polygeist.varname = "buf"} : memref<4x100xi160>
    call @_ZL4prodPA100_K7ap_uintILi160EEPA100_S0_(%arg0, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 17 : i64}} : (memref<4x100xi160>, memref<4x100xi160>) -> ()
    call @_ZL4consPA100_K7ap_uintILi160EEPA100_S0_(%alloca, %arg1) {hls.inline_auto_off = {calls = 1 : i64, size = 24 : i64}} : (memref<4x100xi160>, memref<4x100xi160>) -> ()
    return
  }
  func.func private @_ZL4prodPA100_K7ap_uintILi160EEPA100_S0_(%arg0: memref<4x100xi160>, %arg1: memref<4x100xi160>) attributes {hls.inline_auto_off = {size = 17 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i192 = arith.constant 3 : i192
    affine.for %arg2 = 0 to 4 {
      affine.for %arg3 = 0 to 100 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<4x100xi160>
        %1 = arith.extui %0 : i160 to i192
        %2 = arith.muli %1, %c3_i192 : i192
        %3 = arith.trunci %2 : i192 to i160
        affine.store %3, %arg1[%arg2, %arg3] : memref<4x100xi160>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func private @_ZL4consPA100_K7ap_uintILi160EEPA100_S0_(%arg0: memref<4x100xi160>, %arg1: memref<4x100xi160>) attributes {hls.inline_auto_off = {size = 24 : i64}, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i162 = arith.constant 1 : i162
    affine.for %arg2 = 0 to 4 {
      affine.for %arg3 = 0 to 100 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<4x100xi160>
        %1 = arith.extui %0 : i160 to i162
        %2 = arith.addi %1, %c1_i162 : i162
        %3 = arith.trunci %2 : i162 to i160
        affine.store %3, %arg1[%arg2, %arg3] : memref<4x100xi160>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
