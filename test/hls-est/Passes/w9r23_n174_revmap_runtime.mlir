// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPA5_S_Pii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKhPA5_S_Pii math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPA5_S_Pii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKhPA5_S_Pii math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.folding.evaluate_constant_fills=true' -o /dev/null | FileCheck %s --check-prefix=ON
// W9r23-impl (2026-10-28): VITIS_NOTES N174. Kernel w9r23p_c6_revmap_runtime (~/hls-est-work/exp-src/w9r23p/c6_revmap_runtime.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 18 BRAM.
// Control: the fill loops depend on a run-time argument: nothing folds, 18 with the key on (ON) and off.
// CHECK: Total BRAM: 18{{$}}
// ON: Total BRAM: 18{{$}}
#map = affine_map<(d0) -> (d0 + 1)>
#map1 = affine_map<()[s0] -> (s0 + 1)>
module {
  func.func @_Z3topPKhPA5_S_Pii(%arg0: memref<256xi8>, %arg1: memref<256x5xi8> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "px"}]}, %arg2: memref<256xi32>, %arg3: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c2_i32 = arith.constant 2 : i32
    %c-1_i8 = arith.constant -1 : i8
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "lut"}], hls.preserve, polygeist.varname = "lut"} : memref<6x256xi16>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "rev"}], hls.preserve, polygeist.varname = "rev"} : memref<10xi8>
    %alloca_1 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "dist"}], hls.preserve, polygeist.varname = "dist"} : memref<10xi8>
    %0 = affine.for %arg4 = 0 to 4 iter_args(%arg5 = %c0_i32) -> (i32) {
      %3 = arith.index_cast %arg4 : index to i32
      %4 = arith.muli %3, %3 : i32
      %5 = affine.for %arg6 = 0 to #map(%arg4) iter_args(%arg7 = %arg5) -> (i32) {
        %6 = arith.index_cast %arg6 : index to i32
        %7 = arith.muli %6, %6 : i32
        %8 = arith.addi %4, %7 : i32
        %9 = arith.cmpi sle, %8, %arg3 : i32
        %10 = arith.cmpi ne, %8, %c0_i32 : i32
        %11 = arith.andi %9, %10 : i1
        %12 = scf.if %11 -> (i32) {
          %13 = arith.index_cast %arg7 : i32 to index
          %14 = arith.trunci %8 : i32 to i8
          memref.store %14, %alloca_1[%13] : memref<10xi8>
          %15 = arith.addi %arg7, %c1_i32 : i32
          scf.yield %15 : i32
        } else {
          scf.yield %arg7 : i32
        }
        affine.yield %12 : i32
      }
      affine.yield %5 : i32
    }
    %1 = arith.index_cast %arg3 : i32 to index
    %2 = affine.for %arg4 = 0 to #map1()[%1] iter_args(%arg5 = %c0_i32) -> (i32) {
      %3 = arith.index_cast %arg4 : index to i32
      %4 = arith.index_cast %arg5 : i32 to index
      %5 = memref.load %alloca_1[%4] : memref<10xi8>
      %6 = arith.extui %5 : i8 to i32
      %7 = arith.cmpi eq, %6, %3 : i32
      %8 = scf.if %7 -> (i32) {
        %9 = arith.trunci %arg5 : i32 to i8
        affine.store %9, %alloca_0[%arg4] : memref<10xi8>
        %10 = arith.addi %arg5, %c1_i32 : i32
        scf.yield %10 : i32
      } else {
        affine.store %c-1_i8, %alloca_0[%arg4] : memref<10xi8>
        scf.yield %arg5 : i32
      }
      affine.yield %8 : i32
    }
    affine.for %arg4 = 0 to 256 {
      %3 = affine.load %arg0[%arg4] : memref<256xi8>
      %4 = arith.extui %3 : i8 to i32
      affine.for %arg5 = 0 to 6 {
        %5 = arith.index_cast %arg5 : index to i32
        %6 = arith.addi %5, %c3_i32 : i32
        %7 = arith.muli %4, %6 : i32
        %8 = arith.trunci %7 : i32 to i16
        affine.store %8, %alloca[%arg5, %arg4] : memref<6x256xi16>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    affine.for %arg4 = 0 to 256 {
      %3 = affine.for %arg5 = 1 to 5 iter_args(%arg6 = %c0_i32) -> (i32) {
        %4 = arith.index_cast %arg5 : index to i32
        %5 = arith.cmpi sgt, %4, %c2_i32 : i32
        %6 = arith.extui %5 : i1 to i32
        %7 = arith.addi %4, %6 : i32
        %8 = arith.index_cast %7 : i32 to index
        %9 = memref.load %alloca_0[%8] : memref<10xi8>
        %10 = arith.index_cast %9 : i8 to index
        %11 = affine.load %arg1[%arg4, %arg5] : memref<256x5xi8>
        %12 = arith.index_castui %11 : i8 to index
        %13 = memref.load %alloca[%10, %12] : memref<6x256xi16>
        %14 = arith.extsi %13 : i16 to i32
        %15 = arith.addi %arg6, %14 : i32
        affine.yield %15 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %3, %arg2[%arg4] : memref<256xi32>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
