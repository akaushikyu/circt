// RUN: hls-est %s --symbol-privatize=exclude=_Z6kernelPii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6kernelPii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.memory_architecture.sequential_scope.loads_before_consumer=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N101 (W9r13 review finding 3), kernel w9r13rev_rs_c32 = the cgeist regression test
// hlsfactory-latency-minus-one.c (Vitis 2025.1 td=off: buf RAM_2P_BRAM_1R1W 1, total 3 with the m_axi
// adapter; verbose.sched.rpt: buf[3] in states 12-13, buf[15] in 15-16 before the add): the second read
// waits for the multiplier its consumer needs, one port. Key off: both reads in one state, RAM_2P 2.
// CHECK-DAG: scope pipeline @ {{.*}}:15:5 ii=1:
// CHECK: Total BRAM: 3
// OFF-DAG: scope pipeline @ {{.*}}:15:5 ii=1:
// OFF: Total BRAM: 4
module {
  func.func @_Z6kernelPii(%arg0: memref<?xi32> {hls.interface = [{depth = 16 : i32, mode = "m_axi", port = "a"}]}, %arg1: i32) -> i32 attributes {hls.orig_name = "kernel", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.bind_storage = [{impl = "bram", latency = -1 : i32, type = "ram_2p", variable = "buf"}], hls.preserve, polygeist.varname = "buf"} : memref<16xi32>
    affine.for %arg2 = 0 to 16 {
      %4 = affine.load %arg0[%arg2] : memref<?xi32>
      affine.store %4, %alloca[%arg2] : memref<16xi32>
    }
    %0 = affine.load %alloca[3] : memref<16xi32>
    %1 = arith.muli %0, %arg1 {hls.bind_op = [{impl = "dsp", latency = -1 : i32, op = "mul", variable = "val"}]} : i32
    %2 = affine.load %alloca[15] : memref<16xi32>
    %3 = arith.addi %1, %2 : i32
    return %3 : i32
  }
}
