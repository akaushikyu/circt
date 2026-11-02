// RUN: hls-est %s --symbol-privatize=exclude=_Z6ci_topPK1PPS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6ci_topPK1PPS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N59: calls of a kept function from a completely unrolled loop on distinct elements of an array of streams are concurrent: 4 instances of worker, 4 x buf.
// Kernel w9r7_ci_s4 (~/hls-est-work/exp-src/w9r7p/ci_s4.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 236 BRAM_18K.

// RUN: hls-est %s --symbol-privatize=exclude=_Z6ci_topPK1PPS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6ci_topPK1PPS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.streams.distinct_element_instances=false' -o /dev/null | FileCheck %s --check-prefix=INSTOFF

// With tool.hls.streams.distinct_element_instances=false (INSTOFF) the rule is off; the other W9r7 rules stay on.
// INSTOFF: Total BRAM: 233{{$}}

// CHECK: Total BRAM: 236{{$}}

module {
  func.func @_Z6ci_topPK1PPS_(%arg0: memref<128x!llvm.struct<(array<16 x f32>)>>, %arg1: memref<128x!llvm.struct<(array<16 x f32>)>>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "ci_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "b"} : memref<4xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "a"} : memref<4xi32>
    affine.for %arg2 = 0 to 4 {
      %0 = "polygeist.subindex"(%alloca_0, %arg2) : (memref<4xi32>, index) -> memref<?xi32>
      func.call @_ZN3hls6streamI1PLi4EEC1Ev(%0) : (memref<?xi32>) -> ()
    }
    affine.for %arg2 = 0 to 4 {
      %0 = "polygeist.subindex"(%alloca, %arg2) : (memref<4xi32>, index) -> memref<?xi32>
      func.call @_ZN3hls6streamI1PLi4EEC1Ev(%0) : (memref<?xi32>) -> ()
    }
    %cast = memref.cast %arg0 : memref<128x!llvm.struct<(array<16 x f32>)>> to memref<?x!llvm.struct<(array<16 x f32>)>>
    call @_ZL2rdPK1PPN3hls6streamIS_Li0EEE(%cast, %alloca_0) {hls.inline_auto_off = {calls = 1 : i64, size = 11 : i64}} : (memref<?x!llvm.struct<(array<16 x f32>)>>, memref<4xi32>) -> ()
    call @_ZL6fanoutPN3hls6streamI1PLi0EEES3_(%alloca_0, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 11 : i64}} : (memref<4xi32>, memref<4xi32>) -> ()
    %cast_1 = memref.cast %arg1 : memref<128x!llvm.struct<(array<16 x f32>)>> to memref<?x!llvm.struct<(array<16 x f32>)>>
    call @_ZL2wrP1PPN3hls6streamIS_Li0EEE(%cast_1, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 13 : i64}} : (memref<?x!llvm.struct<(array<16 x f32>)>>, memref<4xi32>) -> ()
    return
  }
  func.func private @_ZN3hls6streamI1PLi4EEC1Ev(memref<?xi32>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 512 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL2rdPK1PPN3hls6streamIS_Li0EEE(%arg0: memref<?x!llvm.struct<(array<16 x f32>)>>, %arg1: memref<4xi32>) attributes {hls.inline_auto_off = {size = 11 : i64}, hls.orig_name = "rd", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 128 {
      %0 = arith.index_cast %arg2 : index to i32
      %1 = arith.andi %0, %c3_i32 : i32
      %2 = arith.index_cast %1 : i32 to index
      %3 = "polygeist.subindex"(%arg1, %2) : (memref<4xi32>, index) -> memref<?xi32>
      %4 = "polygeist.subindex"(%arg0, %arg2) : (memref<?x!llvm.struct<(array<16 x f32>)>>, index) -> memref<?x!llvm.struct<(array<16 x f32>)>>
      func.call @_ZN3hls6streamI1PLi0EE5writeERKS1_(%3, %4) : (memref<?xi32>, memref<?x!llvm.struct<(array<16 x f32>)>>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL6fanoutPN3hls6streamI1PLi0EEES3_(%arg0: memref<4xi32>, %arg1: memref<4xi32>) attributes {hls.inline_auto_off = {size = 11 : i64}, hls.orig_name = "fanout", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg2 = 0 to 4 {
      %0 = "polygeist.subindex"(%arg0, %arg2) : (memref<4xi32>, index) -> memref<?xi32>
      %1 = "polygeist.subindex"(%arg1, %arg2) : (memref<4xi32>, index) -> memref<?xi32>
      func.call @_ZL6workerRN3hls6streamI1PLi0EEES3_(%0, %1) : (memref<?xi32>, memref<?xi32>) -> ()
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    return
  }
  func.func private @_ZL2wrP1PPN3hls6streamIS_Li0EEE(%arg0: memref<?x!llvm.struct<(array<16 x f32>)>>, %arg1: memref<4xi32>) attributes {hls.inline_auto_off = {size = 13 : i64}, hls.orig_name = "wr", llvm.linkage = #llvm.linkage<internal>} {
    %c64 = arith.constant 64 : index
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() : memref<1x!llvm.struct<(array<16 x f32>)>>
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<16 x f32>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<16 x f32>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 128 {
      %2 = arith.index_cast %arg2 : index to i32
      %3 = arith.andi %2, %c3_i32 : i32
      %4 = arith.index_cast %3 : i32 to index
      %5 = "polygeist.subindex"(%arg1, %4) : (memref<4xi32>, index) -> memref<?xi32>
      %6 = func.call @_ZN3hls6streamI1PLi0EE4readEv(%5) : (memref<?xi32>) -> !llvm.struct<(array<16 x f32>)>
      affine.store %6, %alloca[0] : memref<1x!llvm.struct<(array<16 x f32>)>>
      %7 = arith.muli %arg2, %c64 : index
      %8 = arith.index_cast %7 : index to i64
      %9 = llvm.getelementptr %0[%8] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      affine.for %arg3 = 0 to 64 {
        %10 = arith.index_cast %arg3 : index to i32
        %11 = llvm.getelementptr %1[%10] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        %12 = llvm.load %11 : !llvm.ptr -> i8
        %13 = llvm.getelementptr %9[%10] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        llvm.store %12, %13 : i8, !llvm.ptr
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
