// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.streams.element_depth_pragmas=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N177. Kernel w9r23p_k1_stream_elem_depth (~/hls-est-work/exp-src/w9r23p/k1_stream_elem_depth.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 2 BRAM (one 1024 x 32 FIFO).
// hls::stream<int> s[4] with `stream variable=s[0] depth=1024`: only s[0] is deep, the others depth 2 (SRL).
// Off: all four 1024 deep, 8.
// CHECK: Total BRAM: 2{{$}}
// OFF: Total BRAM: 8{{$}}
module {
  func.func @_Z3topPKiPi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "s"}], hls.preserve, hls.stream = [{depth = 1024 : i32, type = "fifo", variable = "s[0]"}], polygeist.varname = "s"} : memref<4xi32>
    affine.for %arg2 = 0 to 4 {
      %0 = "polygeist.subindex"(%alloca, %arg2) : (memref<4xi32>, index) -> memref<?xi32>
      func.call @_ZN3hls6streamIiLi0EEC1Ev(%0) : (memref<?xi32>) -> ()
    }
    %cast = memref.cast %arg0 : memref<1024xi32> to memref<?xi32>
    call @_ZL4prodPKiPN3hls6streamIiLi0EEE(%cast, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 26 : i64}} : (memref<?xi32>, memref<4xi32>) -> ()
    %cast_0 = memref.cast %arg1 : memref<1024xi32> to memref<?xi32>
    call @_ZL4consPN3hls6streamIiLi0EEEPi(%alloca, %cast_0) {hls.inline_auto_off = {calls = 1 : i64, size = 23 : i64}} : (memref<4xi32>, memref<?xi32>) -> ()
    return
  }
  func.func private @_ZN3hls6streamIiLi0EEC1Ev(memref<?xi32>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL4prodPKiPN3hls6streamIiLi0EEE(%arg0: memref<?xi32>, %arg1: memref<4xi32>) attributes {hls.inline_auto_off = {size = 26 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    %alloca = memref.alloca() : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    affine.for %arg2 = 0 to 1024 {
      affine.for %arg3 = 0 to 4 {
        %1 = arith.index_cast %arg3 : index to i32
        %2 = "polygeist.subindex"(%arg1, %arg3) : (memref<4xi32>, index) -> memref<?xi32>
        %3 = affine.load %arg0[%arg2] : memref<?xi32>
        %4 = arith.addi %3, %1 : i32
        affine.store %4, %alloca[0] : memref<1xi32>
        func.call @_ZN3hls6streamIiLi0EE5writeERKi(%2, %cast) : (memref<?xi32>, memref<?xi32>) -> ()
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL4consPN3hls6streamIiLi0EEEPi(%arg0: memref<4xi32>, %arg1: memref<?xi32>) attributes {hls.inline_auto_off = {size = 23 : i64}, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c0_i32 = arith.constant 0 : i32
    affine.for %arg2 = 0 to 1024 {
      %0 = affine.for %arg3 = 0 to 4 iter_args(%arg4 = %c0_i32) -> (i32) {
        %1 = "polygeist.subindex"(%arg0, %arg3) : (memref<4xi32>, index) -> memref<?xi32>
        %2 = func.call @_ZN3hls6streamIiLi0EE4readEv(%1) : (memref<?xi32>) -> i32
        %3 = arith.addi %arg4, %2 : i32
        affine.yield %3 : i32
      }
      affine.store %0, %arg1[%arg2] : memref<?xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamIiLi0EE5writeERKi(memref<?xi32>, memref<?xi32>) attributes {hls.orig_name = "write", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamIiLi0EE4readEv(memref<?xi32>) -> i32 attributes {hls.orig_name = "read", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
}
