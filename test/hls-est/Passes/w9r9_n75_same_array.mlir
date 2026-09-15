// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z1kPiS_S_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r9-impl (2026-10-21): VITIS_NOTES N75 counter-case: rdf(A, out) twice with the same array keeps RAM_1WNR replication.
// Kernel w9r9p_rs_same_arr; MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: A RAM_1WNR 14 BRAM_18K.
// CHECK: Total BRAM: 14{{$}}

module {
  func.func @_Z1kPiS_S_(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: memref<128xi32>) attributes {hls.orig_name = "k", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<1024xi32>
    affine.for %arg3 = 0 to 1024 {
      %0 = affine.load %arg0[%arg3] : memref<1024xi32>
      affine.store %0, %alloca[%arg3] : memref<1024xi32>
    }
    call @_ZL3rdfPiS_(%alloca, %arg2) : (memref<1024xi32>, memref<128xi32>) -> ()
    affine.for %arg3 = 0 to 1024 {
      %0 = affine.load %arg1[%arg3] : memref<1024xi32>
      %1 = affine.load %alloca[%arg3] : memref<1024xi32>
      %2 = arith.addi %1, %0 : i32
      affine.store %2, %alloca[%arg3] : memref<1024xi32>
    }
    call @_ZL3rdfPiS_(%alloca, %arg2) : (memref<1024xi32>, memref<128xi32>) -> ()
    return
  }
  func.func private @_ZL3rdfPiS_(%arg0: memref<1024xi32>, %arg1: memref<128xi32>) attributes {hls.inline_off, hls.orig_name = "rdf", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg2 = 0 to 128 {
      %0 = affine.load %arg1[%arg2] : memref<128xi32>
      %1 = affine.for %arg3 = 0 to 8 iter_args(%arg4 = %0) -> (i32) {
        %2 = affine.load %arg0[%arg3 + %arg2 * 8] : memref<1024xi32>
        %3 = arith.addi %arg4, %2 : i32
        affine.yield %3 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %1, %arg1[%arg2] : memref<128xi32>
    }
    return
  }
}
