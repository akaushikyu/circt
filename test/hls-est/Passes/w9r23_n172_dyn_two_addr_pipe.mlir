// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA1024_KhPA1024_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA1024_KhPA1024_h math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA1024_KhPA1024_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA1024_KhPA1024_h math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.partitioning.shared_address_bank_reads=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N172. Kernel w9r23p_a6_dyn_two_addr_pipe (~/hls-est-work/exp-src/w9r23p/a6_dyn_two_addr_pipe.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 14 BRAM (7 x RAM_1WNR 2).
// As a1 with reads at [c] and [c+1]: two addresses per bank, 2 copies. Off: 98.
// CHECK: Total BRAM: 14{{$}}
// OFF: Total BRAM: 98{{$}}
module {
  func.func @_Z3topPA1024_KhPA1024_h(%arg0: memref<64x1024xi8>, %arg1: memref<64x1024xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c1023_i32 = arith.constant 1023 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "ri"}], hls.preserve, polygeist.varname = "ri"} : memref<7xi32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "buf"}], hls.preserve, polygeist.varname = "buf"} : memref<7x1024xi8>
    affine.for %arg2 = 0 to 7 {
      %0 = arith.index_cast %arg2 : index to i32
      affine.store %0, %alloca[%arg2] : memref<7xi32>
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %alloca[6] : memref<7xi32>
      %1 = arith.index_cast %0 : i32 to index
      affine.for %arg3 = 0 to 1024 {
        %3 = arith.index_cast %arg3 : index to i32
        %4 = affine.load %arg0[%arg2, %arg3] : memref<64x1024xi8>
        memref.store %4, %alloca_0[%1, %arg3] : memref<7x1024xi8>
        %5 = arith.addi %3, %c1_i32 : i32
        %6 = arith.andi %5, %c1023_i32 : i32
        %7 = arith.index_cast %6 : i32 to index
        %8 = affine.for %arg4 = 0 to 7 iter_args(%arg5 = %c0_i32) -> (i32) {
          %11 = affine.load %alloca[%arg4] : memref<7xi32>
          %12 = arith.index_cast %11 : i32 to index
          %13 = memref.load %alloca_0[%12, %arg3] : memref<7x1024xi8>
          %14 = arith.extui %13 : i8 to i32
          %15 = memref.load %alloca_0[%12, %7] : memref<7x1024xi8>
          %16 = arith.extui %15 : i8 to i32
          %17 = arith.addi %14, %16 : i32
          %18 = arith.addi %arg5, %17 : i32
          affine.yield %18 : i32
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
        %9 = arith.shrui %8, %c3_i32 : i32
        %10 = arith.trunci %9 : i32 to i8
        affine.store %10, %arg1[%arg2, %arg3] : memref<64x1024xi8>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      %2 = affine.load %alloca[0] : memref<7xi32>
      affine.for %arg3 = 0 to 6 {
        %3 = affine.load %alloca[%arg3 + 1] : memref<7xi32>
        affine.store %3, %alloca[%arg3] : memref<7xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %2, %alloca[6] : memref<7xi32>
    }
    return
  }
}
