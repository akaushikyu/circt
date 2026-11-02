// RUN: hls-est %s --symbol-privatize=exclude=_Z6fl_topPA64_sS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6fl_topPA64_sS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.partitioning.reachable_store_banks=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// OPEN_ISSUES O150, kernel w9r8p_fl_pre (Vitis 2025.1 td=off: 128, the ben_hall
// lab3 shape): `Cl[i][jj + u] += t[jj + u]` with Cl complete on dim 2 and the
// jj loop unrolled by 32 (jj in {0, 32}). Copy u can only reach banks u and
// u + 32, so each bank is written once per iteration and Bl's 64 reads bound
// the II (Bl RAM_1WNR); every bank written by every copy gave 33 accesses
// per bank (ResMinII 17): 80.
// (tool.hls.partitioning.reachable_store_banks)
// CHECK: Total BRAM: 128
// OFF: Total BRAM: 80

module {
  func.func @_Z6fl_topPA64_sS0_S0_(%arg0: memref<64x64xi16>, %arg1: memref<64x64xi16>, %arg2: memref<64x64xi16>) attributes {hls.orig_name = "fl_top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "t"}], hls.preserve, polygeist.varname = "t"} : memref<64xi16>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "Cl"}], hls.preserve, polygeist.varname = "Cl"} : memref<64x64xi16>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Bl"} : memref<64x64xi16>
    %alloca_2 = memref.alloca() {hls.preserve, polygeist.varname = "Al"} : memref<64x64xi16>
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 64 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<64x64xi16>
        affine.store %0, %alloca_2[%arg3, %arg4] : memref<64x64xi16>
        %1 = affine.load %arg1[%arg3, %arg4] : memref<64x64xi16>
        affine.store %1, %alloca_1[%arg3, %arg4] : memref<64x64xi16>
        affine.store %c0_i16, %alloca_0[%arg3, %arg4] : memref<64x64xi16>
      }
    }
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 64 {
        %0 = affine.load %alloca_2[%arg3, %arg4] : memref<64x64xi16>
        %1 = arith.extsi %0 : i16 to i32
        affine.for %arg5 = 0 to 64 {
          %2 = affine.load %alloca_1[%arg4, %arg5] : memref<64x64xi16>
          %3 = arith.extsi %2 : i16 to i32
          %4 = arith.muli %1, %3 : i32
          %5 = arith.trunci %4 : i32 to i16
          affine.store %5, %alloca[%arg5] : memref<64xi16>
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
        affine.for %arg5 = 0 to 64 {
          %2 = affine.load %alloca[%arg5] : memref<64xi16>
          %3 = affine.load %alloca_0[%arg3, %arg5] : memref<64x64xi16>
          %4 = arith.addi %3, %2 : i16
          affine.store %4, %alloca_0[%arg3, %arg5] : memref<64x64xi16>
        } {hls.unroll = [{factor = 32 : i32, skip_exit_check = false}]}
      }
    }
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 64 {
        %0 = affine.load %alloca_0[%arg3, %arg4] : memref<64x64xi16>
        affine.store %0, %arg2[%arg3, %arg4] : memref<64x64xi16>
      }
    }
    return
  }
}
