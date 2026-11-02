// RUN: hls-est %s --symbol-privatize=exclude=_Z6sb_topPfPKf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sb_topPfPKf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N58: a stream of struct {float; bool} is 33 bits wide (bool 1 bit; cgeist records it as hls.stream_element_bits): fifo_w33_d64, 2 BRAM (the IR type {f32, i8} is 40 bits: 3).
// Kernel w9r7_sb_f_none (~/hls-est-work/exp-src/w9r7p/sb_f_none.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 2 BRAM_18K.

// RUN: hls-est %s --symbol-privatize=exclude=_Z6sb_topPfPKf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sb_topPfPKf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.streams.declared_element_bits=false' -o /dev/null | FileCheck %s --check-prefix=BITSOFF

// With tool.hls.streams.declared_element_bits=false (BITSOFF) the rule is off; the other W9r7 rules stay on.
// BITSOFF: Total BRAM: 3{{$}}

// CHECK: Total BRAM: 2{{$}}

module {
  llvm.mlir.global internal constant @str0("s\00") {addr_space = 0 : i32}
  func.func @_Z6sb_topPfPKf(%arg0: memref<1024xf32>, %arg1: memref<1024xf32>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "sb_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.stream = [{depth = 64 : i32, type = "fifo", variable = "s"}], polygeist.varname = "s"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr
    %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamI4DataIfELi0EEC1EPKc(%cast, %2) : (memref<?xi32>, memref<?xi8>) -> ()
    %cast_0 = memref.cast %arg1 : memref<1024xf32> to memref<?xf32>
    call @_ZL4prodRN3hls6streamI4DataIfELi0EEEPKf(%cast, %cast_0) {hls.inline_auto_off = {calls = 1 : i64, size = 15 : i64}} : (memref<?xi32>, memref<?xf32>) -> ()
    %cast_1 = memref.cast %arg0 : memref<1024xf32> to memref<?xf32>
    call @_ZL4consPfRN3hls6streamI4DataIfELi0EEE(%cast_1, %cast) {hls.inline_auto_off = {calls = 1 : i64, size = 17 : i64}} : (memref<?xf32>, memref<?xi32>) -> ()
    return
  }
  func.func private @_ZN3hls6streamI4DataIfELi0EEC1EPKc(memref<?xi32>, memref<?xi8>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 33 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL4prodRN3hls6streamI4DataIfELi0EEEPKf(%arg0: memref<?xi32>, %arg1: memref<?xf32>) attributes {hls.inline_auto_off = {size = 15 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    %c1023_i32 = arith.constant 1023 : i32
    %alloca = memref.alloca() {polygeist.varname = "d"} : memref<1x!llvm.struct<(f32, i8)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(f32, i8)>> to memref<?x!llvm.struct<(f32, i8)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(f32, i8)>>) -> !llvm.ptr
    %1 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(f32, i8)>
    affine.for %arg2 = 0 to 1024 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = affine.load %arg1[%arg2] : memref<?xf32>
      llvm.store %3, %0 : f32, !llvm.ptr
      %4 = arith.cmpi eq, %2, %c1023_i32 : i32
      %5 = arith.extui %4 : i1 to i8
      llvm.store %5, %1 : i8, !llvm.ptr
      func.call @_ZN3hls6streamI4DataIfELi0EE5writeERKS2_(%arg0, %cast) : (memref<?xi32>, memref<?x!llvm.struct<(f32, i8)>>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL4consPfRN3hls6streamI4DataIfELi0EEE(%arg0: memref<?xf32>, %arg1: memref<?xi32>) attributes {hls.inline_auto_off = {size = 17 : i64}, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 0.000000e+00 : f32
    %c0_i8 = arith.constant 0 : i8
    %alloca = memref.alloca() {polygeist.varname = "d"} : memref<1x!llvm.struct<(f32, i8)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(f32, i8)>>) -> !llvm.ptr
    %1 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(f32, i8)>
    affine.for %arg2 = 0 to 1024 {
      %2 = func.call @_ZN3hls6streamI4DataIfELi0EE4readEv(%arg1) : (memref<?xi32>) -> !llvm.struct<(f32, i8)>
      affine.store %2, %alloca[0] : memref<1x!llvm.struct<(f32, i8)>>
      %3 = llvm.load %1 : !llvm.ptr -> i8
      %4 = arith.cmpi ne, %3, %c0_i8 : i8
      %5 = scf.if %4 -> (f32) {
        scf.yield %cst : f32
      } else {
        %6 = llvm.load %0 : !llvm.ptr -> f32
        scf.yield %6 : f32
      }
      affine.store %5, %arg0[%arg2] : memref<?xf32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamI4DataIfELi0EE5writeERKS2_(memref<?xi32>, memref<?x!llvm.struct<(f32, i8)>>) attributes {hls.orig_name = "write", hls.stream_element_bits = 33 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamI4DataIfELi0EE4readEv(memref<?xi32>) -> !llvm.struct<(f32, i8)> attributes {hls.orig_name = "read", hls.stream_element_bits = 33 : i64, llvm.linkage = #llvm.linkage<external>}
}
