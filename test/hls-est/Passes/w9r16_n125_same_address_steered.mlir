// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N125, kernel w9r16p_rs_nc (Vitis 2025.1 td=off: 240): pa cyclic 8 read at
// 4n + 8k + r (r < 4) in a pipelined loop at II 2: each read's bank is r or r + 4 and its
// in-bank address n / 2 + k is the same on both, so Vitis reads the candidate banks
// unpredicated and muxes the data: 15 copies per bank (N4), as polybench_pragmas k3mm tmp2.
// tool.hls.memory_architecture.replication.rotating_reads_full_copies gives the extra
// copy only where the in-bank address differs (hls.bank_address_varies): 240.
// CHECK: Total BRAM: 240

module {
  func.func @_Z3topPiS_S_(%arg0: memref<512xi32>, %arg1: memref<256xi32>, %arg2: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c256 = arith.constant 256 : index
    %c-1 = arith.constant -1 : index
    %c0 = arith.constant 0 : index
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "ker"}], hls.preserve, polygeist.varname = "ker"} : memref<128xi32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "pa"}], hls.preserve, polygeist.varname = "pa"} : memref<504xi32>
    affine.for %arg3 = 0 to 504 {
      %0 = affine.load %arg0[%arg3] : memref<512xi32>
      affine.store %0, %alloca_0[%arg3] : memref<504xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 128 {
      %0 = arith.muli %arg3, %c-1 : index
      %1 = arith.remsi %0, %c256 : index
      %2 = arith.cmpi slt, %1, %c0 : index
      %3 = arith.addi %1, %c256 : index
      %4 = arith.select %2, %3, %1 : index
      %5 = memref.load %arg1[%4] : memref<256xi32>
      affine.store %5, %alloca[%arg3] : memref<128xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 64 {
      %0 = affine.for %arg4 = 0 to 32 iter_args(%arg5 = %c0_i32) -> (i32) {
        %1 = affine.for %arg6 = 0 to 4 iter_args(%arg7 = %arg5) -> (i32) {
          %2 = affine.load %alloca_0[%arg6 + %arg4 * 8 + %arg3 * 4] : memref<504xi32>
          %3 = affine.load %alloca[%arg6 + %arg4 * 4] : memref<128xi32>
          %4 = arith.muli %2, %3 : i32
          %5 = arith.addi %arg7, %4 : i32
          affine.yield %5 : i32
        }
        affine.yield %1 : i32
      }
      affine.store %0, %arg2[%arg3] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
