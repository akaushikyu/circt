// RUN: hls-est %s --symbol-privatize=exclude=_Z6ci_topPK1PPS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6ci_topPK1PPS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 review fixes (2026-10-20): VITIS_NOTES N59: worker(s[id], s[id + 4]) unrolled over id on one array of 8 streams: the element indices are integer arithmetic on constants after the unroll (ConstantIndex.h folds addi / subi / muli), so the 4 calls are distinct instances.
// Kernel w9r7rev_ci_one (~/hls-est-work/exp-src/w9r7rev/ci_one.cpp); MLIR from cgeist c3b (Polygeist branch w9r7-cgeist, W9r7 review fixes) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 236 BRAM_18K.

// CHECK: Total BRAM: 236{{$}}

module {
  func.func @_Z6ci_topPK1PPS_(%arg0: memref<128x!llvm.struct<(array<16 x f32>)>>, %arg1: memref<128x!llvm.struct<(array<16 x f32>)>>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "ci_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "s"} : memref<8xi32>
    affine.for %arg2 = 0 to 8 {
      %0 = "polygeist.subindex"(%alloca, %arg2) : (memref<8xi32>, index) -> memref<?xi32>
      func.call @_ZN3hls6streamI1PLi4EEC1Ev(%0) : (memref<?xi32>) -> ()
    }
    %cast = memref.cast %arg0 : memref<128x!llvm.struct<(array<16 x f32>)>> to memref<?x!llvm.struct<(array<16 x f32>)>>
    call @_ZL2rdPK1PPN3hls6streamIS_Li0EEE(%cast, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 11 : i64}} : (memref<?x!llvm.struct<(array<16 x f32>)>>, memref<8xi32>) -> ()
    call @_ZL6fanoutPN3hls6streamI1PLi0EEE(%alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 12 : i64}} : (memref<8xi32>) -> ()
    %cast_0 = memref.cast %arg1 : memref<128x!llvm.struct<(array<16 x f32>)>> to memref<?x!llvm.struct<(array<16 x f32>)>>
    call @_ZL2wrP1PPN3hls6streamIS_Li0EEE(%cast_0, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 14 : i64}} : (memref<?x!llvm.struct<(array<16 x f32>)>>, memref<8xi32>) -> ()
    return
  }
  func.func private @_ZN3hls6streamI1PLi4EEC1Ev(memref<?xi32>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 512 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL2rdPK1PPN3hls6streamIS_Li0EEE(%arg0: memref<?x!llvm.struct<(array<16 x f32>)>>, %arg1: memref<8xi32>) attributes {hls.inline_auto_off = {size = 11 : i64}, hls.orig_name = "rd", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 128 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = arith.andi %0, %c3_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %3 = "polygeist.subindex"(%arg1, %2) : (memref<8xi32>, index) -> memref<?xi32>
      %4 = "polygeist.subindex"(%arg0, %arg2) : (memref<?x!llvm.struct<(array<16 x f32>)>>, index) -> memref<?x!llvm.struct<(array<16 x f32>)>>
      func.call @_ZN3hls6streamI1PLi0EE5writeERKS1_(%3, %4) : (memref<?xi32>, memref<?x!llvm.struct<(array<16 x f32>)>>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL6fanoutPN3hls6streamI1PLi0EEE(%arg0: memref<8xi32>) attributes {hls.inline_auto_off = {size = 12 : i64}, hls.orig_name = "fanout", llvm.linkage = #llvm.linkage<internal>} {
    %c4_i32 = arith.constant 4 : i32
    affine.for %arg1 = 0 to 4 {
      %0 = arith.index_cast %arg1 : index to i32
      %1 = "polygeist.subindex"(%arg0, %arg1) : (memref<8xi32>, index) -> memref<?xi32>
      %2 = arith.addi %0, %c4_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      %4 = "polygeist.subindex"(%arg0, %3) : (memref<8xi32>, index) -> memref<?xi32>
      func.call @_ZL6workerRN3hls6streamI1PLi0EEES3_(%1, %4) : (memref<?xi32>, memref<?xi32>) -> ()
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    return
  }
  func.func private @_ZL2wrP1PPN3hls6streamIS_Li0EEE(%arg0: memref<?x!llvm.struct<(array<16 x f32>)>>, %arg1: memref<8xi32>) attributes {hls.inline_auto_off = {size = 14 : i64}, hls.orig_name = "wr", llvm.linkage = #llvm.linkage<internal>} {
    %c64 = arith.constant 64 : index
    %c3_i32 = arith.constant 3 : i32
    %c4_i32 = arith.constant 4 : i32
    %alloca = memref.alloca() : memref<1x!llvm.struct<(array<16 x f32>)>>
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<16 x f32>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<16 x f32>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 128 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = arith.andi %2, %c3_i32 : i32
      %4 = arith.addi %3, %c4_i32 : i32
      %5 = arith.index_cast %4 : i32 to index
      %6 = "polygeist.subindex"(%arg1, %5) : (memref<8xi32>, index) -> memref<?xi32>
      %7 = func.call @_ZN3hls6streamI1PLi0EE4readEv(%6) : (memref<?xi32>) -> !llvm.struct<(array<16 x f32>)>
      affine.store %7, %alloca[0] : memref<1x!llvm.struct<(array<16 x f32>)>>
      %8 = arith.muli %arg2, %c64 : index
      %9 = arith.index_cast %8 : index to i64
      %10 = llvm.getelementptr %0[%9] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      affine.for %arg3 = 0 to 64 {
        %11 = arith.index_cast %arg3 : index to i32
        %12 = llvm.getelementptr %1[%11] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        %13 = llvm.load %12 : !llvm.ptr -> i8
        %14 = llvm.getelementptr %10[%11] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        llvm.store %13, %14 : i8, !llvm.ptr
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamI1PLi0EE5writeERKS1_(memref<?xi32>, memref<?x!llvm.struct<(array<16 x f32>)>>) attributes {hls.orig_name = "write", hls.stream_element_bits = 512 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL6workerRN3hls6streamI1PLi0EEES3_(%arg0: memref<?xi32>, %arg1: memref<?xi32>) attributes {hls.inline_off, hls.orig_name = "worker", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 2.000000e+00 : f32
    %c511_i32 = arith.constant 511 : i32
    %c7_i32 = arith.constant 7 : i32
    %c16_i32 = arith.constant 16 : i32
    %alloca = memref.alloca() {polygeist.varname = "q"} : memref<1x!llvm.struct<(array<16 x f32>)>>
    %cast = memref.cast %alloca : memref<1x!llvm.struct<(array<16 x f32>)>> to memref<?x!llvm.struct<(array<16 x f32>)>>
    %alloca_0 = memref.alloca() {polygeist.varname = "p"} : memref<1x!llvm.struct<(array<16 x f32>)>>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<512xf32>
    %0 = "polygeist.memref2pointer"(%alloca_0) : (memref<1x!llvm.struct<(array<16 x f32>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 32 {
      %2 = func.call @_ZN3hls6streamI1PLi0EE4readEv(%arg0) : (memref<?xi32>) -> !llvm.struct<(array<16 x f32>)>
      affine.store %2, %alloca_0[0] : memref<1x!llvm.struct<(array<16 x f32>)>>
      affine.for %arg3 = 0 to 16 {
        %3 = arith.index_cast %arg3 : index to i32
        %4 = llvm.getelementptr %0[%3] : (!llvm.ptr, i32) -> !llvm.ptr, f32
        %5 = llvm.load %4 : !llvm.ptr -> f32
        affine.store %5, %alloca_1[%arg3 + %arg2 * 16] : memref<512xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<16 x f32>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 32 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = arith.muli %2, %c16_i32 : i32
      affine.for %arg3 = 0 to 16 {
        %4 = arith.index_cast %arg3 : index to i32
        %5 = arith.muli %4, %c7_i32 : i32
        %6 = arith.addi %3, %5 : i32
        %7 = arith.andi %6, %c511_i32 : i32
        %8 = arith.index_cast %7 : i32 to index
        %9 = memref.load %alloca_1[%8] : memref<512xf32>
        %10 = arith.mulf %9, %cst : f32
        %11 = llvm.getelementptr %1[%4] : (!llvm.ptr, i32) -> !llvm.ptr, f32
        llvm.store %10, %11 : f32, !llvm.ptr
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      func.call @_ZN3hls6streamI1PLi0EE5writeERKS1_(%arg1, %cast) : (memref<?xi32>, memref<?x!llvm.struct<(array<16 x f32>)>>) -> ()
    }
    return
  }
  func.func private @_ZN3hls6streamI1PLi0EE4readEv(memref<?xi32>) -> !llvm.struct<(array<16 x f32>)> attributes {hls.orig_name = "read", hls.stream_element_bits = 512 : i64, llvm.linkage = #llvm.linkage<external>}
}
