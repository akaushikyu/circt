// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.replication.caller_stores_per_loop=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N99, kernel w9r13p_nr_call (Vitis 2025.1 td=off: loc RAM_AUTO_1R1W 2,
// the inline-off reader at II 8): the caller stores loc 16 times per iteration,
// so the callee's parameter is not replicable either (hls.caller_stores_per_loop):
// 16 reads on 2 ports, II 8. Before: II 1 from 17 replicated slots that
// --bram-analysis never priced.
// CHECK: pipeline @ {{.*}}:33:5 in @{{.*}}: ii=8
// CHECK: Total BRAM: 2
// OFF: pipeline @ {{.*}}:33:5 in @{{.*}}: ii=1

module {
  func.func @_Z3topPKiPi(%arg0: memref<64xi32>, %arg1: memref<64xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "loc"} : memref<1024xi32>
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %arg0[%arg2] : memref<64xi32>
      affine.for %arg3 = 0 to 16 {
        %1 = arith.index_cast %arg3 : index to i32
        %2 = arith.addi %0, %1 : i32
        affine.store %2, %alloca[%arg3 + %arg2 * 16] : memref<1024xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    call @_ZL2rdPiS_(%alloca, %arg1) : (memref<1024xi32>, memref<64xi32>) -> ()
    return
  }
  func.func private @_ZL2rdPiS_(%arg0: memref<1024xi32>, %arg1: memref<64xi32>) attributes {hls.inline_off, hls.orig_name = "rd", llvm.linkage = #llvm.linkage<internal>} {
    %c1023_i32 = arith.constant 1023 : i32
    %c1_i32 = arith.constant 1 : i32
    %c17_i32 = arith.constant 17 : i32
    %c16_i32 = arith.constant 16 : i32
    %c0_i32 = arith.constant 0 : i32
    affine.for %arg2 = 0 to 64 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = arith.muli %0, %c16_i32 : i32
      %2 = affine.for %arg3 = 0 to 16 iter_args(%arg4 = %c0_i32) -> (i32) {
        %3 = arith.index_cast %arg3 : index to i32
        %4 = arith.muli %3, %c17_i32 : i32
        %5 = arith.addi %1, %4 : i32
        %6 = arith.andi %5, %c1023_i32 : i32
        %7 = arith.index_cast %6 : i32 to index
        %8 = memref.load %arg0[%7] : memref<1024xi32>
        %9 = arith.addi %3, %c1_i32 : i32
        %10 = arith.muli %8, %9 : i32
        %11 = arith.addi %arg4, %10 : i32
        affine.yield %11 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %2, %arg1[%arg2] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
