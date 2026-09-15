// RUN: hls-est %s --symbol-privatize=exclude=_Z7o79_topRN3hls6streamIiLi0EEES2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7o79_topRN3hls6streamIiLi0EEES2_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z7o79_topRN3hls6streamIiLi0EEES2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z7o79_topRN3hls6streamIiLi0EEES2_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.partitioning.constant_index.globals=false -o /dev/null | FileCheck %s --check-prefix=GOFF
// W9r9-impl (2026-10-21): VITIS_NOTES N77: a function static int buf[4][64] whose rows are written with constant indices is completely partitioned on dim 1 (214-449), as a local array is.
// Kernel w9r9p_o79_static; MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 4 x 1 = 4 BRAM_18K.
// With tool.hls.partitioning.constant_index.globals=false (GOFF): 2.
// GOFF: Total BRAM: 2{{$}}
// CHECK: Total BRAM: 4{{$}}

module {
  memref.global "private" @"_ZL4prodRN3hls6streamIiLi0EEES2_@static@_ZZL4prodRN3hls6streamIiLi0EEES2_E3buf" : memref<4x64xi32> = uninitialized
  func.func @_Z7o79_topRN3hls6streamIiLi0EEES2_(%arg0: memref<?xi32>, %arg1: memref<?xi32>) attributes {hls.orig_name = "o79_top", llvm.linkage = #llvm.linkage<external>} {
    call @_ZL4prodRN3hls6streamIiLi0EEES2_(%arg0, %arg1) {hls.inline_auto_off = {calls = 1 : i64, size = 60 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
    return
  }
  func.func private @_ZL4prodRN3hls6streamIiLi0EEES2_(%arg0: memref<?xi32>, %arg1: memref<?xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.inline_auto_off = {size = 60 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    %c3 = arith.constant 3 : index
    %c7 = arith.constant 7 : index
    %c2 = arith.constant 2 : index
    %c5 = arith.constant 5 : index
    %c1 = arith.constant 1 : index
    %c64 = arith.constant 64 : index
    %c0 = arith.constant 0 : index
    %c0_i32 = arith.constant 0 : i32
    %0 = llvm.mlir.undef : i32
    %alloca = memref.alloca() {polygeist.varname = "s"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca[0] : memref<1xi32>
    %1 = memref.get_global @"_ZL4prodRN3hls6streamIiLi0EEES2_@static@_ZZL4prodRN3hls6streamIiLi0EEES2_E3buf" : memref<4x64xi32>
    affine.for %arg2 = 0 to 64 {
      %2 = func.call @_ZN3hls6streamIiLi0EE4readEv(%arg0) : (memref<?xi32>) -> i32
      %3 = func.call @_ZN3hls6streamIiLi0EE4readEv(%arg0) : (memref<?xi32>) -> i32
      %4 = func.call @_ZN3hls6streamIiLi0EE4readEv(%arg0) : (memref<?xi32>) -> i32
      %5 = func.call @_ZN3hls6streamIiLi0EE4readEv(%arg0) : (memref<?xi32>) -> i32
      %6 = arith.muli %arg2, %c5 : index
      %7 = arith.remsi %6, %c64 : index
      %8 = arith.cmpi slt, %7, %c0 : index
      %9 = arith.addi %7, %c64 : index
      %10 = arith.select %8, %9, %7 : index
      memref.store %2, %1[%c0, %10] : memref<4x64xi32>
      %11 = arith.muli %arg2, %c7 : index
      %12 = arith.remsi %11, %c64 : index
      %13 = arith.cmpi slt, %12, %c0 : index
      %14 = arith.addi %12, %c64 : index
      %15 = arith.select %13, %14, %12 : index
      memref.store %3, %1[%c2, %15] : memref<4x64xi32>
      %16 = arith.muli %arg2, %c3 : index
      %17 = arith.remsi %16, %c64 : index
      %18 = arith.cmpi slt, %17, %c0 : index
      %19 = arith.addi %17, %c64 : index
      %20 = arith.select %18, %19, %17 : index
      memref.store %4, %1[%c1, %20] : memref<4x64xi32>
      affine.store %5, %1[3, %arg2] : memref<4x64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg2 = 0 to 64 {
      affine.store %c0_i32, %alloca[0] : memref<1xi32>
      %2 = affine.for %arg3 = 0 to 4 iter_args(%arg4 = %c0_i32) -> (i32) {
        %3 = arith.addi %arg3, %arg2 : index
        %4 = arith.remsi %3, %c64 : index
        %5 = arith.cmpi slt, %4, %c0 : index
        %6 = arith.addi %4, %c64 : index
        %7 = arith.select %5, %6, %4 : index
        %8 = memref.load %1[%arg3, %7] : memref<4x64xi32>
        %9 = arith.addi %arg4, %8 : i32
        affine.store %9, %alloca[0] : memref<1xi32>
        affine.yield %9 : i32
      }
      func.call @_ZN3hls6streamIiLi0EE5writeERKi(%arg1, %cast) : (memref<?xi32>, memref<?xi32>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamIiLi0EE4readEv(memref<?xi32>) -> i32 attributes {hls.orig_name = "read", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamIiLi0EE5writeERKi(memref<?xi32>, memref<?xi32>) attributes {hls.orig_name = "write", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
}
