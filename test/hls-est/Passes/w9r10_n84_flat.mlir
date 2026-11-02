// RUN: hls-est %s --symbol-privatize=exclude=_Z6pc_topPA64_A32_KsPA64_A32_s --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6pc_topPA64_A32_KsPA64_A32_s math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6pc_topPA64_A32_KsPA64_A32_s --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6pc_topPA64_A32_KsPA64_A32_s math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.dataflow_channels.through_nested_regions=false -o /dev/null | FileCheck %s --check-prefix=NOFF
// W9r10-impl (2026-10-21): VITIS_NOTES N84 (OPEN_ISSUES O112): the same with a flat producer (control).
// With tool.hls.dataflow_channels.through_nested_regions=false (prefix NOFF) the total is 8.
// Kernel w9r10p_pc_flat (~/hls-est-work/exp-src/w9r10p/pc_flat.cpp); MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 8 BRAM_18K.
// CHECK: Total BRAM: 8{{$}}
// NOFF: Total BRAM: 8{{$}}

module {
  func.func @_Z4rowsPA32_sS0_(%arg0: memref<64x32xi16>, %arg1: memref<64x32xi16>) attributes {hls.orig_name = "rows", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c1_i32 = arith.constant 1 : i32
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 32 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<64x32xi16>
        %1 = arith.extsi %0 : i16 to i32
        %2 = arith.addi %1, %c1_i32 : i32
        %3 = arith.muli %2, %c3_i32 : i32
        %4 = arith.addi %3, %c1_i32 : i32
        %5 = arith.trunci %4 : i32 to i16
        affine.store %5, %arg1[%arg2, %arg3] : memref<64x32xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func @_Z4loadPA64_A32_KsPA32_si(%arg0: memref<4x64x32xi16>, %arg1: memref<64x32xi16>, %arg2: i32) attributes {hls.orig_name = "load", llvm.linkage = #llvm.linkage<external>} {
    %0 = arith.index_cast %arg2 : i32 to index
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 32 {
        %1 = affine.load %arg0[symbol(%0), %arg3, %arg4] : memref<4x64x32xi16>
        affine.store %1, %arg1[%arg3, %arg4] : memref<64x32xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func @_Z5storePA32_sPA64_S_i(%arg0: memref<64x32xi16>, %arg1: memref<4x64x32xi16>, %arg2: i32) attributes {hls.orig_name = "store", llvm.linkage = #llvm.linkage<external>} {
    %0 = arith.index_cast %arg2 : i32 to index
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 32 {
        %1 = affine.load %arg0[%arg3, %arg4] : memref<64x32xi16>
        affine.store %1, %arg1[symbol(%0), %arg3, %arg4] : memref<4x64x32xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func @_Z6pc_topPA64_A32_KsPA64_A32_s(%arg0: memref<4x64x32xi16>, %arg1: memref<4x64x32xi16>) attributes {hls.orig_name = "pc_top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "outl"} : memref<64x32xi16>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "Ql"} : memref<64x32xi16>
    affine.for %arg2 = 0 to 4 {
      affine.for %arg3 = 0 to 64 {
        affine.for %arg4 = 0 to 32 {
          %0 = affine.load %arg0[%arg2, %arg3, %arg4] : memref<4x64x32xi16>
          affine.store %0, %alloca_0[%arg3, %arg4] : memref<64x32xi16>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
      affine.for %arg3 = 0 to 64 {
        affine.for %arg4 = 0 to 32 {
          %0 = affine.load %alloca_0[%arg3, %arg4] : memref<64x32xi16>
          %1 = arith.extsi %0 : i16 to i32
          %2 = arith.addi %1, %c1_i32 : i32
          %3 = arith.muli %2, %c3_i32 : i32
          %4 = arith.addi %3, %c1_i32 : i32
          %5 = arith.trunci %4 : i32 to i16
          affine.store %5, %alloca[%arg3, %arg4] : memref<64x32xi16>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
      affine.for %arg3 = 0 to 64 {
        affine.for %arg4 = 0 to 32 {
          %0 = affine.load %alloca[%arg3, %arg4] : memref<64x32xi16>
          affine.store %0, %arg1[%arg2, %arg3, %arg4] : memref<4x64x32xi16>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      }
    } {hls.dataflow = [{disable_start_propagation = false}]}
    return
  }
}
