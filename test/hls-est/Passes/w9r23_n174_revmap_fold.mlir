// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPA5_S_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKhPA5_S_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPA5_S_Pi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKhPA5_S_Pi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.folding.evaluate_constant_fills=true' -o /dev/null | FileCheck %s --check-prefix=ON
// W9r23-impl (2026-10-28): VITIS_NOTES N174. Kernel w9r23p_c5_revmap_fold (~/hls-est-work/exp-src/w9r23p/c5_revmap_fold.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 4 BRAM (banks 4 and 5 gone, no copies).
// dist[] / rev[] filled by constant-trip loops (data-dependent store index) are evaluated into a constant table;
// lut[rev[c]][x] then has constant banks after the unroll (only 4 of 6 read): 4 with
// tool.hls.folding.evaluate_constant_fills (ON; off by default, no corpus design, OPEN_ISSUES O234). Default: 6 banks x 3 copies = 18.
// CHECK: Total BRAM: 18{{$}}
// ON: Total BRAM: 4{{$}}
#map = affine_map<(d0) -> (d0 + 1)>
module {
  func.func @_Z3topPKhPA5_S_Pi(%arg0: memref<256xi8>, %arg1: memref<256x5xi8> {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "px"}]}, %arg2: memref<256xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c2_i32 = arith.constant 2 : i32
    %c-1_i8 = arith.constant -1 : i8
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %c9_i32 = arith.constant 9 : i32
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "lut"}], hls.preserve, polygeist.varname = "lut"} : memref<6x256xi16>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "rev"}], hls.preserve, polygeist.varname = "rev"} : memref<10xi8>
    %alloca_1 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "dist"}], hls.preserve, polygeist.varname = "dist"} : memref<10xi8>
    %0 = affine.for %arg3 = 0 to 4 iter_args(%arg4 = %c0_i32) -> (i32) {
      %2 = arith.index_cast %arg3 : index to i32
      %3 = arith.muli %2, %2 : i32
      %4 = affine.for %arg5 = 0 to #map(%arg3) iter_args(%arg6 = %arg4) -> (i32) {
        %5 = arith.index_cast %arg5 : index to i32
        %6 = arith.muli %5, %5 : i32
        %7 = arith.addi %3, %6 : i32
        %8 = arith.cmpi sle, %7, %c9_i32 : i32
        %9 = arith.cmpi ne, %7, %c0_i32 : i32
        %10 = arith.andi %8, %9 : i1
        %11 = scf.if %10 -> (i32) {
          %12 = arith.index_cast %arg6 : i32 to index
          %13 = arith.trunci %7 : i32 to i8
          memref.store %13, %alloca_1[%12] : memref<10xi8>
          %14 = arith.addi %arg6, %c1_i32 : i32
          scf.yield %14 : i32
        } else {
          scf.yield %arg6 : i32
        }
        affine.yield %11 : i32
      }
      affine.yield %4 : i32
    }
    %1 = affine.for %arg3 = 0 to 10 iter_args(%arg4 = %c0_i32) -> (i32) {
      %2 = arith.index_cast %arg3 : index to i32
      %3 = arith.index_cast %arg4 : i32 to index
      %4 = memref.load %alloca_1[%3] : memref<10xi8>
      %5 = arith.extui %4 : i8 to i32
      %6 = arith.cmpi eq, %5, %2 : i32
      %7 = scf.if %6 -> (i32) {
        %8 = arith.trunci %arg4 : i32 to i8
        affine.store %8, %alloca_0[%arg3] : memref<10xi8>
        %9 = arith.addi %arg4, %c1_i32 : i32
        scf.yield %9 : i32
      } else {
        affine.store %c-1_i8, %alloca_0[%arg3] : memref<10xi8>
        scf.yield %arg4 : i32
      }
      affine.yield %7 : i32
    }
    affine.for %arg3 = 0 to 256 {
      %2 = affine.load %arg0[%arg3] : memref<256xi8>
      %3 = arith.extui %2 : i8 to i32
      affine.for %arg4 = 0 to 6 {
        %4 = arith.index_cast %arg4 : index to i32
        %5 = arith.addi %4, %c3_i32 : i32
        %6 = arith.muli %3, %5 : i32
        %7 = arith.trunci %6 : i32 to i16
        affine.store %7, %alloca[%arg4, %arg3] : memref<6x256xi16>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 256 {
      %2 = affine.for %arg4 = 1 to 5 iter_args(%arg5 = %c0_i32) -> (i32) {
        %3 = arith.index_cast %arg4 : index to i32
        %4 = arith.cmpi sgt, %3, %c2_i32 : i32
        %5 = arith.extui %4 : i1 to i32
        %6 = arith.addi %3, %5 : i32
        %7 = arith.index_cast %6 : i32 to index
        %8 = memref.load %alloca_0[%7] : memref<10xi8>
        %9 = arith.index_cast %8 : i8 to index
        %10 = affine.load %arg1[%arg3, %arg4] : memref<256x5xi8>
        %11 = arith.index_castui %10 : i8 to index
        %12 = memref.load %alloca[%9, %11] : memref<6x256xi16>
        %13 = arith.extsi %12 : i16 to i32
        %14 = arith.addi %arg5, %13 : i32
        affine.yield %14 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %2, %arg2[%arg3] : memref<256xi32>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
