// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP12upstream_cfgPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topP12upstream_cfgPKiPi -o /dev/null | FileCheck %s

// VITIS_NOTES N147 / N145, W9 round 19 review defect 2 (kernel w9r19f_fx_n145s,
// the struct made identified as cgeist names a class): a user struct whose name
// contains "stream" (`upstream_cfg`) is an aggregated struct pointer like any
// other; only library classes (hls::, tapa::, std::) are excluded. g(c) is
// called in the outlined pipelined loop L and after it with a scalar argument:
// one shared instance, tbl 1 (Vitis 1). The old substring test gave 2.
// CHECK: Total BRAM: 1

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topP12upstream_cfgPKiPi(%arg0: memref<?x!llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>>, %arg1: memref<8xi32>, %arg2: memref<8xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>>) -> !llvm.ptr
    %1 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>
    %2 = affine.load %arg1[1] : memref<8xi32>
    llvm.store %2, %1 : i32, !llvm.ptr
    affine.for %arg3 = 0 to 7 {
      func.call @_ZL1gP12upstream_cfg(%arg0) : (memref<?x!llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>>) -> ()
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    call @_ZL1gP12upstream_cfg(%arg0) : (memref<?x!llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>>) -> ()
    %3 = llvm.load %0 : !llvm.ptr -> i32
    affine.store %3, %arg2[0] : memref<8xi32>
    return
  }
  func.func private @_ZL1gP12upstream_cfg(%arg0: memref<?x!llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>>) attributes {hls.inline_off, hls.orig_name = "g", llvm.linkage = #llvm.linkage<internal>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>>) -> !llvm.ptr
    %1 = memref.get_global @_ZL3tbl : memref<256xi8>
    %2 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>
    %3 = llvm.load %2 : !llvm.ptr -> i32
    %4 = arith.trunci %3 : i32 to i8
    %5 = arith.index_castui %4 : i8 to index
    %6 = affine.load %1[symbol(%5)] : memref<256xi8>
    %7 = llvm.getelementptr %0[0, 2] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<"struct.upstream_cfg", (i32, i32, i16)>
    %8 = llvm.load %7 : !llvm.ptr -> i16
    %9 = arith.trunci %8 : i16 to i8
    %10 = arith.index_castui %9 : i8 to index
    %11 = affine.load %1[symbol(%10)] : memref<256xi8>
    %12 = arith.xori %6, %11 : i8
    %13 = arith.extui %12 : i8 to i32
    llvm.store %13, %0 : i32, !llvm.ptr
    return
  }
}
