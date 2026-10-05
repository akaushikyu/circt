// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPh --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPh -o /dev/null | FileCheck %s

// VITIS_NOTES N142 + N144, kernel w9r19p_iu_d (cgeist with
// --hls-auto-inline-callee-unroll output): `mid` (with `sub`'s 16-trip loop
// inlined) is kept and called in a `pipeline` loop: a function pipeline whose
// II is set by its 16 loads and 16 stores of the top's `buf` (II 16), so its
// 16 `tbl` reads need one read port per cycle: 1 BRAM (Vitis 1; as a
// sequential scope the 16 reads would share a state, 8).
// CHECK: Total BRAM: 1

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topPh(%arg0: memref<16xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cast = memref.cast %arg0 : memref<16xi8> to memref<?xi8>
    affine.for %arg1 = 0 to 13 {
      func.call @_ZL1hPh(%cast) {hls.inline_auto_off = {calls = 2 : i64, size = 83 : i64}} : (memref<?xi8>) -> ()
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    call @_ZL1hPh(%cast) {hls.inline_auto_off = {calls = 2 : i64, size = 83 : i64}} : (memref<?xi8>) -> ()
    return
  }
  func.func private @_ZL1hPh(%arg0: memref<?xi8>) attributes {hls.inline_auto_off = {size = 83 : i64}, hls.orig_name = "h", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    %c-1_i8 = arith.constant -1 : i8
    %c0_i8 = arith.constant 0 : i8
    %c16_i8 = arith.constant 16 : i8
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = scf.while (%arg1 = %c16_i8) : (i8) -> i8 {
      %6 = arith.cmpi ne, %arg1, %c0_i8 : i8
      scf.condition(%6) %arg1 : i8
    } do {
    ^bb0(%arg1: i8):
      %6 = arith.addi %arg1, %c-1_i8 : i8
      %7 = arith.index_castui %6 : i8 to index
      %8 = memref.load %arg0[%7] : memref<?xi8>
      %9 = arith.index_castui %8 : i8 to index
      %10 = memref.load %0[%9] : memref<256xi8>
      memref.store %10, %arg0[%7] : memref<?xi8>
      scf.yield %6 : i8
    }
    %2 = affine.load %arg0[0] : memref<?xi8>
    %3 = arith.extui %2 : i8 to i32
    %4 = arith.xori %3, %c1_i32 : i32
    %5 = arith.trunci %4 : i32 to i8
    affine.store %5, %arg0[0] : memref<?xi8>
    return
  }
}
