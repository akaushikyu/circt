// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z1kPiS_S_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram | FileCheck %s --check-prefix=IR
// W9r9 review fix D3 (2026-10-21): the N74 nested-reload forwarding of --memory-banking-bram must not forward a
// reload of a global across a call that may write it. The pipelined loop reads G[0][i], calls upd(i, m)
// (inline off, writes G[0][i] through its own get_global), then re-reads G[0][i] inside an if arm: that reload
// stays a read of the banks inside the arm (it was replaced by the value loaded before the call).
// Kernel ~/hls-est-work/coord/scratch/w9r9rev/k/fwd_call.cpp; MLIR from cgeist 537d6614 (installed), --shim real.
// No Vitis run (an IR soundness test; the total is the current hls-est output).
// CHECK: Total BRAM: 4{{$}}
// IR: call @_ZL3updii
// IR: scf.if
// IR-NEXT: affine.apply
// IR-NEXT: affine.load
// IR-NEXT: affine.load
// IR-NEXT: affine.load
// IR-NEXT: affine.load

module {
  memref.global "private" @_ZL1G : memref<4x1024xi32> = uninitialized {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "G"}]}
  func.func @_Z1kPiS_S_(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi32>) attributes {hls.orig_name = "k", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %0 = memref.get_global @_ZL1G : memref<4x1024xi32>
    affine.for %arg3 = 0 to 1024 {
      %1 = affine.load %arg0[%arg3] : memref<1024xi32>
      affine.store %1, %0[0, %arg3] : memref<4x1024xi32>
    }
    affine.for %arg3 = 0 to 1020 {
      %1 = arith.index_cast %arg3 : index to i32
      %2 = affine.load %0[0, %arg3] : memref<4x1024xi32>
      %3 = affine.load %0[0, %arg3 + 1] : memref<4x1024xi32>
      %4 = arith.addi %2, %3 : i32
      %5 = affine.load %0[0, %arg3 + 2] : memref<4x1024xi32>
      %6 = arith.addi %4, %5 : i32
      func.call @_ZL3updii(%1, %6) : (i32, i32) -> ()
      %7 = affine.load %arg1[%arg3] : memref<1024xi32>
      %8 = arith.cmpi sgt, %7, %c0_i32 : i32
      %9 = scf.if %8 -> (i32) {
        %10 = affine.load %0[0, %arg3] : memref<4x1024xi32>
        %11 = arith.addi %6, %10 : i32
        scf.yield %11 : i32
      } else {
        scf.yield %6 : i32
      }
      affine.store %9, %arg2[%arg3] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL3updii(%arg0: i32, %arg1: i32) attributes {hls.inline_off, hls.orig_name = "upd", llvm.linkage = #llvm.linkage<internal>} {
    %0 = memref.get_global @_ZL1G : memref<4x1024xi32>
    %1 = arith.index_cast %arg0 : i32 to index
    affine.store %arg1, %0[0, symbol(%1)] : memref<4x1024xi32>
    return
  }
}
