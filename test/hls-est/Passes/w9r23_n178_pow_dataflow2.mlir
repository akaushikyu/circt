// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPdd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPdd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.math_library.sequential_core_sharing=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N178. Kernel w9r23p_m7_pow_dataflow2 (~/hls-est-work/exp-src/w9r23p/m7_pow_dataflow2.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 60 BRAM.
// Control: pow in two dataflow processes: a core each, 60 either way.
// CHECK: Total BRAM: 60{{$}}
// OFF: Total BRAM: 60{{$}}
module {
  func.func @_Z3topPKdPdd(%arg0: memref<1024xf64>, %arg1: memref<1024xf64>, %arg2: f64) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {polygeist.varname = "s"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    call @_ZN3hls6streamIdLi0EEC1Ev(%cast) : (memref<?xi32>) -> ()
    %cast_0 = memref.cast %arg0 : memref<1024xf64> to memref<?xf64>
    call @_ZL2p1PKdRN3hls6streamIdLi0EEEd(%cast_0, %cast, %arg2) {hls.inline_auto_off = {calls = 1 : i64, size = 12 : i64}} : (memref<?xf64>, memref<?xi32>, f64) -> ()
    %cast_1 = memref.cast %arg1 : memref<1024xf64> to memref<?xf64>
    call @_ZL2p2RN3hls6streamIdLi0EEEPdd(%cast, %cast_1, %arg2) {hls.inline_auto_off = {calls = 1 : i64, size = 13 : i64}} : (memref<?xi32>, memref<?xf64>, f64) -> ()
    return
  }
  func.func private @_ZN3hls6streamIdLi0EEC1Ev(memref<?xi32>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 64 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL2p1PKdRN3hls6streamIdLi0EEEd(%arg0: memref<?xf64>, %arg1: memref<?xi32>, %arg2: f64) attributes {hls.inline_auto_off = {size = 12 : i64}, hls.orig_name = "p1", llvm.linkage = #llvm.linkage<internal>} {
    %alloca = memref.alloca() : memref<1xf64>
    %cast = memref.cast %alloca : memref<1xf64> to memref<?xf64>
    %0 = llvm.mlir.undef : f64
    affine.store %0, %alloca[0] : memref<1xf64>
    affine.for %arg3 = 0 to 1024 {
      %1 = affine.load %arg0[%arg3] : memref<?xf64>
      %2 = math.powf %1, %arg2 : f64
      affine.store %2, %alloca[0] : memref<1xf64>
      func.call @_ZN3hls6streamIdLi0EE5writeERKd(%arg1, %cast) : (memref<?xi32>, memref<?xf64>) -> ()
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL2p2RN3hls6streamIdLi0EEEPdd(%arg0: memref<?xi32>, %arg1: memref<?xf64>, %arg2: f64) attributes {hls.inline_auto_off = {size = 13 : i64}, hls.orig_name = "p2", llvm.linkage = #llvm.linkage<internal>} {
    %cst = arith.constant 2.000000e+00 : f64
    %0 = arith.subf %cst, %arg2 : f64
    affine.for %arg3 = 0 to 1024 {
      %1 = func.call @_ZN3hls6streamIdLi0EE4readEv(%arg0) : (memref<?xi32>) -> f64
      %2 = math.powf %1, %0 : f64
      affine.store %2, %arg1[%arg3] : memref<?xf64>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZN3hls6streamIdLi0EE5writeERKd(memref<?xi32>, memref<?xf64>) attributes {hls.orig_name = "write", hls.stream_element_bits = 64 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamIdLi0EE4readEv(memref<?xi32>) -> f64 attributes {hls.orig_name = "read", hls.stream_element_bits = 64 : i64, llvm.linkage = #llvm.linkage<external>}
}
