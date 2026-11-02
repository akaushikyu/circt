// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPh --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPKhPh -o /dev/null | FileCheck %s
// RUN: hls-est %s --config-set tool.hls.memory_architecture.rom.module_copies=false --symbol-privatize=exclude=_Z3topPKhPh --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPKhPh -o /dev/null | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N136, W9 round 19 review defect 4 (kernel w9r19r_rv_rm_gc): tbl is
// read by g1, called through the kept f, and by g2, both in one pipelined loop of
// the top: g1 is placed by f (the top's direct child on its call chain) and each
// reader keeps its own copy, 1 + 1 (Vitis 2). Before the fix a reader below a
// direct child disabled N136: 1.
// CHECK: one copy per reading module (N136): 1 x 1 (@_ZL2g2h) + 1 x 1 (@_ZL2g1h) = 2
// CHECK: Total BRAM: 2
// OFF: Total BRAM: 1

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topPKhPh(%arg0: memref<64xi8>, %arg1: memref<64xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %arg0[%arg2] : memref<64xi8>
      %1 = func.call @_ZL1fh(%0) : (i8) -> i8
      %2 = affine.load %arg0[%arg2] : memref<64xi8>
      %3 = func.call @_ZL2g2h(%2) : (i8) -> i8
      %4 = arith.xori %1, %3 : i8
      affine.store %4, %arg1[%arg2] : memref<64xi8>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL1fh(%arg0: i8) -> i8 attributes {hls.inline_off, hls.orig_name = "f", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    %0 = call @_ZL2g1h(%arg0) : (i8) -> i8
    %1 = arith.extui %0 : i8 to i32
    %2 = arith.addi %1, %c3_i32 : i32
    %3 = arith.trunci %2 : i32 to i8
    return %3 : i8
  }
  func.func private @_ZL2g2h(%arg0: i8) -> i8 attributes {hls.inline_off, hls.orig_name = "g2", llvm.linkage = #llvm.linkage<internal>} {
    %c5_i32 = arith.constant 5 : i32
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = arith.extui %arg0 : i8 to i32
    %2 = arith.xori %1, %c5_i32 : i32
    %3 = arith.trunci %2 : i32 to i8
    %4 = arith.index_castui %3 : i8 to index
    %5 = affine.load %0[symbol(%4)] : memref<256xi8>
    return %5 : i8
  }
  func.func private @_ZL2g1h(%arg0: i8) -> i8 attributes {hls.inline_off, hls.orig_name = "g1", llvm.linkage = #llvm.linkage<internal>} {
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = arith.index_castui %arg0 : i8 to index
    %2 = affine.load %0[symbol(%1)] : memref<256xi8>
    return %2 : i8
  }
}
