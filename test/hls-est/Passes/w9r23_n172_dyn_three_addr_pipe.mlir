// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA1024_KhPA1024_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA1024_KhPA1024_h math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA1024_KhPA1024_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA1024_KhPA1024_h math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.partitioning.shared_address_bank_reads=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N172. Kernel w9r23p_a7_dyn_three_addr_pipe (~/hls-est-work/exp-src/w9r23p/a7_dyn_three_addr_pipe.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 21 BRAM.
// Three addresses: 3 copies per bank. Off: 70.
// CHECK: Total BRAM: 21{{$}}
// OFF: Total BRAM: 70{{$}}
module {
  func.func @_Z3topPA1024_KhPA1024_h(%arg0: memref<64x1024xi8>, %arg1: memref<64x1024xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c2_i32 = arith.constant 2 : i32
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
        %8 = arith.addi %3, %c2_i32 : i32
        %9 = arith.andi %8, %c1023_i32 : i32
        %10 = arith.index_cast %9 : i32 to index
        %11 = affine.for %arg4 = 0 to 7 iter_args(%arg5 = %c0_i32) -> (i32) {
          %14 = affine.load %alloca[%arg4] : memref<7xi32>
          %15 = arith.index_cast %14 : i32 to index
          %16 = memref.load %alloca_0[%15, %arg3] : memref<7x1024xi8>
          %17 = arith.extui %16 : i8 to i32
          %18 = memref.load %alloca_0[%15, %7] : memref<7x1024xi8>
          %19 = arith.extui %18 : i8 to i32
          %20 = arith.addi %17, %19 : i32
          %21 = memref.load %alloca_0[%15, %10] : memref<7x1024xi8>
          %22 = arith.extui %21 : i8 to i32
          %23 = arith.addi %20, %22 : i32
          %24 = arith.addi %arg5, %23 : i32
          affine.yield %24 : i32
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
        %12 = arith.shrui %11, %c3_i32 : i32
        %13 = arith.trunci %12 : i32 to i8
        affine.store %13, %arg1[%arg2, %arg3] : memref<64x1024xi8>
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
