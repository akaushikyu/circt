// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s

// VITIS_NOTES N93, kernel w9r12p_rom_s3: three independent reads of a 256 x 8
// ROM in one state of the (non-pipelined) top: Vitis ROM_NP, 2 copies.
// CHECK: ROM_NP
// CHECK: Total BRAM: 2

module {
  memref.global "private" @_ZL1T : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3tophhhPh(%arg0: i8, %arg1: i8, %arg2: i8, %arg3: memref<?xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %0 = memref.get_global @_ZL1T : memref<256xi8>
    %1 = arith.index_castui %arg0 : i8 to index
    %2 = affine.load %0[symbol(%1)] : memref<256xi8>
    %3 = arith.index_castui %arg1 : i8 to index
    %4 = affine.load %0[symbol(%3)] : memref<256xi8>
    %5 = arith.xori %2, %4 : i8
    %6 = arith.index_castui %arg2 : i8 to index
    %7 = affine.load %0[symbol(%6)] : memref<256xi8>
    %8 = arith.xori %5, %7 : i8
    affine.store %8, %arg3[0] : memref<?xi8>
    return
  }
}
