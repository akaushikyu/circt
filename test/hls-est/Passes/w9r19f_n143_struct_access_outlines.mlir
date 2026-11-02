// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP9plain_cfgPh --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topP9plain_cfgPh -o /dev/null | FileCheck %s

// VITIS_NOTES N143 / N147, W9 round 19 review defect 1 (kernels w9r19r_rv_s2_plain_cfg,
// w9r19f_fx_s2_rd, w9r19f_fx_s_rd): a read or write of the top's struct pointer
// (`c->a = c->b * 3 + 1`) outside the pipelined loop I outlines I like a memory
// access (`top_Pipeline_I`), so g(buf), called in I and after it, has an instance
// in each module: tbl 1 BRAM x 2 (Vitis 2). Before the fix the aggregated struct
// pointer was exempt and its llvm.load / llvm.store were not seen: 1.
// CHECK: x 2 instance(s) of @_ZL1gPh = 2
// CHECK: Total BRAM: 2

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topP9plain_cfgPh(%arg0: memref<?x!llvm.struct<(i32, i16, i8)>>, %arg1: memref<16xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c1_i32 = arith.constant 1 : i32
    affine.for %arg2 = 0 to 13 {
      func.call @_ZL1gPh(%arg1) : (memref<16xi8>) -> ()
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(i32, i16, i8)>>) -> !llvm.ptr
    %1 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(i32, i16, i8)>
    %2 = llvm.load %1 : !llvm.ptr -> i16
    %3 = arith.extsi %2 : i16 to i32
    %4 = arith.muli %3, %c3_i32 : i32
    %5 = arith.addi %4, %c1_i32 : i32
    llvm.store %5, %0 : i32, !llvm.ptr
    call @_ZL1gPh(%arg1) : (memref<16xi8>) -> ()
    return
  }
  func.func private @_ZL1gPh(%arg0: memref<16xi8>) attributes {hls.inline_off, hls.orig_name = "g", llvm.linkage = #llvm.linkage<internal>} {
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = affine.load %arg0[1] : memref<16xi8>
    %2 = arith.index_castui %1 : i8 to index
    %3 = affine.load %0[symbol(%2)] : memref<256xi8>
    affine.store %3, %arg0[0] : memref<16xi8>
    %4 = affine.load %arg0[3] : memref<16xi8>
    %5 = arith.index_castui %4 : i8 to index
    %6 = affine.load %0[symbol(%5)] : memref<256xi8>
    affine.store %6, %arg0[2] : memref<16xi8>
    return
  }
}
