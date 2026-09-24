// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s
// W9 round 12 review, kernel w9r12rv_n93_loop (Vitis 2025.1 td=off: 2, the
// loop not pipelined, two ROM copies): four independent reads of a ROM per
// iteration of a loop under `#pragma HLS pipeline off`. The loop stays
// sequential in --convert-affine-to-loopschedule
// (tool.hls.pipeline_decision.pipeline_off_sequential), so N93 applies:
// ceil(4 / 2) copies. Before: the loop was scheduled as a pipeline (II 2,
// ROM_2P, 1).
// CHECK: Total BRAM: 2

module {
  memref.global "private" @_ZL1T : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topPhS_(%arg0: memref<64xi8>, %arg1: memref<64xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c2_i32 = arith.constant 2 : i32
    %c1_i32 = arith.constant 1 : i32
    %0 = memref.get_global @_ZL1T : memref<256xi8>
    affine.for %arg2 = 0 to 64 {
      %1 = affine.load %arg0[%arg2] : memref<64xi8>
      %2 = arith.index_castui %1 : i8 to index
      %3 = memref.load %0[%2] : memref<256xi8>
      %4 = arith.extui %1 : i8 to i32
      %5 = arith.addi %4, %c1_i32 : i32
      %6 = arith.trunci %5 : i32 to i8
      %7 = arith.index_castui %6 : i8 to index
      %8 = memref.load %0[%7] : memref<256xi8>
      %9 = arith.xori %3, %8 : i8
      %10 = arith.addi %4, %c2_i32 : i32
      %11 = arith.trunci %10 : i32 to i8
      %12 = arith.index_castui %11 : i8 to index
      %13 = memref.load %0[%12] : memref<256xi8>
      %14 = arith.xori %9, %13 : i8
      %15 = arith.addi %4, %c3_i32 : i32
      %16 = arith.trunci %15 : i32 to i8
      %17 = arith.index_castui %16 : i8 to index
      %18 = memref.load %0[%17] : memref<256xi8>
      %19 = arith.xori %14, %18 : i8
      affine.store %19, %arg1[%arg2] : memref<64xi8>
    } {hls.pipeline_off}
    return
  }
}
