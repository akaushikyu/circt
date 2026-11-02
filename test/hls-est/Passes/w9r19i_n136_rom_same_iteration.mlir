// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPhS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPhS_S_ -o /dev/null | FileCheck %s
// RUN: hls-est %s --config-set tool.hls.memory_architecture.rom.module_copies=false --symbol-privatize=exclude=_Z3topPhS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPhS_S_ -o /dev/null | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N136 (c), kernel w9r17p_rom_pl (cgeist output): two different
// inline-off readers `g1`, `g2` of `tbl` called in the same iteration of one
// pipelined loop each keep their own ROM copy (Vitis 2 BRAM, one per module).
// CHECK: one copy per reading module (N136): 1 x 1 ({{.*}}) + 1 x 1 ({{.*}}) = 2
// CHECK: Total BRAM: 2
// OFF: Total BRAM: 1

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topPhS_S_(%arg0: memref<64xi8>, %arg1: memref<64xi8>, %arg2: memref<64xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %arg0[%arg3] : memref<64xi8>
      %1 = func.call @_ZL2g1h(%0) : (i8) -> i8
      affine.store %1, %arg1[%arg3] : memref<64xi8>
      %2 = affine.load %arg0[%arg3] : memref<64xi8>
      %3 = func.call @_ZL2g2h(%2) : (i8) -> i8
      affine.store %3, %arg2[%arg3] : memref<64xi8>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL2g1h(%arg0: i8) -> i8 attributes {hls.inline_off, hls.orig_name = "g1", llvm.linkage = #llvm.linkage<internal>} {
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
  func.func private @_ZL2g2h(%arg0: i8) -> i8 attributes {hls.inline_off, hls.orig_name = "g2", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    %c7_i32 = arith.constant 7 : i32
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = arith.extui %arg0 : i8 to i32
    %2 = arith.addi %1, %c7_i32 : i32
    %3 = arith.trunci %2 : i32 to i8
    %4 = arith.index_castui %3 : i8 to index
    %5 = affine.load %0[symbol(%4)] : memref<256xi8>
    %6 = arith.extui %5 : i8 to i32
    %7 = arith.addi %6, %c3_i32 : i32
    %8 = arith.trunci %7 : i32 to i8
    return %8 : i8
  }
}
