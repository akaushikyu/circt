// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.replication.user_ram_1wnr_replicable=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N113, kernel w9r15p_bw_1wnr (Vitis 2025.1 td=off: 12): R[2048] with
// bind_storage type=ram_1wnr is swapped in one loop (two stores per iteration) and
// read 4x per iteration in a pipeline II=1 loop. Vitis replicates it anyway (3
// copies, 12; the swap loop's II rises to 3).
// tool.hls.memory_architecture.replication.user_ram_1wnr_replicable gives that
// (on by default since W9r16-impl, with N124 for FocusedACO). Off: not
// replicable (4).
// CHECK: Total BRAM: 12
// OFF: Total BRAM: 4

module {
  func.func @_Z3topPiS_S_S_(%arg0: memref<2048xi32>, %arg1: memref<512xi32>, %arg2: memref<512xi32>, %arg3: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c2_i32 = arith.constant 2 : i32
    %c11_i32 = arith.constant 11 : i32
    %c2047_i32 = arith.constant 2047 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.bind_storage = [{type = "ram_1wnr", variable = "R"}], hls.preserve, polygeist.varname = "R"} : memref<2048xi32>
    affine.for %arg4 = 0 to 2048 {
      %0 = affine.load %arg0[%arg4] : memref<2048xi32>
      affine.store %0, %alloca[%arg4] : memref<2048xi32>
    }
    affine.for %arg4 = 0 to 512 {
      %0 = affine.load %arg2[%arg4] : memref<512xi32>
      %1 = arith.andi %0, %c2047_i32 : i32
      %2 = arith.shrsi %0, %c11_i32 : i32
      %3 = arith.andi %2, %c2047_i32 : i32
      %4 = arith.index_cast %1 : i32 to index
      %5 = memref.load %alloca[%4] : memref<2048xi32>
      %6 = arith.index_cast %3 : i32 to index
      %7 = memref.load %alloca[%6] : memref<2048xi32>
      memref.store %7, %alloca[%4] : memref<2048xi32>
      memref.store %5, %alloca[%6] : memref<2048xi32>
    }
    affine.for %arg4 = 0 to 512 {
      %0 = affine.load %arg1[%arg4] : memref<512xi32>
      %1 = arith.andi %0, %c2047_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %3 = memref.load %alloca[%2] : memref<2048xi32>
      %4 = arith.addi %1, %c1_i32 : i32
      %5 = arith.andi %4, %c2047_i32 : i32
      %6 = arith.index_cast %5 : i32 to index
      %7 = memref.load %alloca[%6] : memref<2048xi32>
      %8 = arith.addi %3, %7 : i32
      %9 = arith.addi %1, %c2_i32 : i32
      %10 = arith.andi %9, %c2047_i32 : i32
      %11 = arith.index_cast %10 : i32 to index
      %12 = memref.load %alloca[%11] : memref<2048xi32>
      %13 = arith.addi %8, %12 : i32
      %14 = arith.addi %1, %c3_i32 : i32
      %15 = arith.andi %14, %c2047_i32 : i32
      %16 = arith.index_cast %15 : i32 to index
      %17 = memref.load %alloca[%16] : memref<2048xi32>
      %18 = arith.addi %13, %17 : i32
      affine.store %18, %arg3[%arg4] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
