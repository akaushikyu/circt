// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA1024_KhPA1024_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA1024_KhPA1024_h math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA1024_KhPA1024_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA1024_KhPA1024_h math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.partitioning.shared_address_bank_reads=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N172. Kernel w9r23p_a1_dyn_same_pipe (~/hls-est-work/exp-src/w9r23p/a1_dyn_same_pipe.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 7 BRAM (7 x RAM_AUTO_1R1W).
// buf[7][1024] complete dim=1 read at buf[ri[k]][c] (run-time rows, one in-bank address) 7 times per II-1
// iteration: each bank is read once, at offset c. Off: every read loads every bank, 7 copies each, 49.
// CHECK: Total BRAM: 7{{$}}
// OFF: Total BRAM: 49{{$}}
module {
  func.func @_Z3topPA1024_KhPA1024_h(%arg0: memref<64x1024xi8>, %arg1: memref<64x1024xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
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
        %3 = affine.load %arg0[%arg2, %arg3] : memref<64x1024xi8>
        memref.store %3, %alloca_0[%1, %arg3] : memref<7x1024xi8>
        %4 = affine.for %arg4 = 0 to 7 iter_args(%arg5 = %c0_i32) -> (i32) {
          %7 = affine.load %alloca[%arg4] : memref<7xi32>
          %8 = arith.index_cast %7 : i32 to index
          %9 = memref.load %alloca_0[%8, %arg3] : memref<7x1024xi8>
          %10 = arith.extui %9 : i8 to i32
          %11 = arith.addi %arg5, %10 : i32
          affine.yield %11 : i32
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
        %5 = arith.shrui %4, %c3_i32 : i32
        %6 = arith.trunci %5 : i32 to i8
        affine.store %6, %arg1[%arg2, %arg3] : memref<64x1024xi8>
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
