// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPhS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPhS_S_ -o /dev/null | FileCheck %s

// VITIS_NOTES N136 (c) / N143, kernel w9r17p_rom_fp (cgeist output): the loop
// calling the function pipeline `g` is not outlined (the top's only other
// statement is the call `f2(y, z)`; calls do not count), and `g` and `f2` are
// not called in one pipelined iteration: they share one ROM in the top, 1 BRAM
// (Vitis 1).
// CHECK-NOT: one copy per reading module
// CHECK: Total BRAM: 1

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topPhS_S_(%arg0: memref<64xi8>, %arg1: memref<64xi8>, %arg2: memref<64xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %arg0[%arg3] : memref<64xi8>
      %1 = func.call @_ZL1gh(%0) : (i8) -> i8
      affine.store %1, %arg1[%arg3] : memref<64xi8>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    call @_ZL2f2PhS_(%arg1, %arg2) : (memref<64xi8>, memref<64xi8>) -> ()
    return
  }
  func.func private @_ZL1gh(%arg0: i8) -> i8 attributes {hls.inline_off, hls.orig_name = "g", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = arith.index_castui %arg0 : i8 to index
    %2 = affine.load %0[symbol(%1)] : memref<256xi8>
    %3 = arith.extui %arg0 : i8 to i32
    %4 = arith.addi %3, %c1_i32 : i32
    %5 = arith.trunci %4 : i32 to i8
    %6 = arith.index_castui %5 : i8 to index
    %7 = affine.load %0[symbol(%6)] : memref<256xi8>
    %8 = arith.xori %2, %7 : i8
    return %8 : i8
  }
  func.func private @_ZL2f2PhS_(%arg0: memref<64xi8>, %arg1: memref<64xi8>) attributes {hls.inline_off, hls.orig_name = "f2", llvm.linkage = #llvm.linkage<internal>} {
    %c90_i32 = arith.constant 90 : i32
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    affine.for %arg2 = 0 to 64 {
      %1 = affine.load %arg0[%arg2] : memref<64xi8>
      %2 = arith.index_castui %1 : i8 to index
      %3 = memref.load %0[%2] : memref<256xi8>
      %4 = arith.extui %3 : i8 to i32
      %5 = arith.xori %4, %c90_i32 : i32
      %6 = arith.trunci %5 : i32 to i8
      affine.store %6, %arg1[%arg2] : memref<64xi8>
    }
    return
  }
}
