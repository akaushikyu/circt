// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhS0_PhS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPKhS0_PhS1_ -o /dev/null | FileCheck %s

// VITIS_NOTES N148 (kernel w9r19f_fx_fps_dis): the same loops on disjoint arrays
// (A reads in, B reads in2). Vitis outlines B (`top_Outline_B`) next to
// `top_Pipeline_A`, and both use one g in the top (2 BRAM): a pipelined loop
// and a sequential loop share the instance whatever arrays they access.
// CHECK: Total BRAM: 2

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topPKhS0_PhS1_(%arg0: memref<64xi8>, %arg1: memref<64xi8>, %arg2: memref<64xi8>, %arg3: memref<64xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c7_i32 = arith.constant 7 : i32
    affine.for %arg4 = 0 to 64 {
      %0 = affine.load %arg0[%arg4] : memref<64xi8>
      %1 = func.call @_ZL1gh(%0) : (i8) -> i8
      affine.store %1, %arg2[%arg4] : memref<64xi8>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg4 = 0 to 64 {
      %0 = affine.load %arg1[%arg4] : memref<64xi8>
      %1 = arith.extui %0 : i8 to i32
      %2 = arith.xori %1, %c7_i32 : i32
      %3 = arith.trunci %2 : i32 to i8
      %4 = func.call @_ZL1gh(%3) : (i8) -> i8
      affine.store %4, %arg3[%arg4] : memref<64xi8>
    } {hls.pipeline_off}
    return
  }
  func.func private @_ZL1gh(%arg0: i8) -> i8 attributes {hls.inline_off, hls.orig_name = "g", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    %c1_i32 = arith.constant 1 : i32
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = arith.index_castui %arg0 : i8 to index
    %2 = affine.load %0[symbol(%1)] : memref<256xi8>
    %3 = arith.index_castui %2 : i8 to index
    %4 = affine.load %0[symbol(%3)] : memref<256xi8>
    %5 = arith.extui %4 : i8 to i32
    %6 = arith.addi %5, %c1_i32 : i32
    %7 = arith.trunci %6 : i32 to i8
    %8 = arith.index_castui %7 : i8 to index
    %9 = affine.load %0[symbol(%8)] : memref<256xi8>
    %10 = arith.extui %9 : i8 to i32
    %11 = arith.xori %10, %c3_i32 : i32
    %12 = arith.trunci %11 : i32 to i8
    %13 = arith.index_castui %12 : i8 to index
    %14 = affine.load %0[symbol(%13)] : memref<256xi8>
    return %14 : i8
  }
}
