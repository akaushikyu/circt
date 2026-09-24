// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s
// W9 round 12 review, kernel w9r12rv_n92_varinit (Vitis 2025.1 td=off: 64,
// 64 banks x 1): rp_base with `for (t = 0; t < n; t++) X[i][j] = t;` (j
// unrolled) as the init. The init loop may run zero times, so the reads see
// the value from before the iteration: LLVM LICM loads the old value in the
// preheader (--auto-pipeline-unroll's promotion now does too) and the banks
// are no N92 registers.
// CHECK-NOT: iteration-private element
// CHECK: Total BRAM: 64

module {
  func.func @_Z3topiPiS_PsPA64_s(%arg0: i32, %arg1: memref<65xi32>, %arg2: memref<1024xi32>, %arg3: memref<1024xi16>, %arg4: memref<64x64xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1 = arith.constant 1 : index
    %alloca = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "X"}], hls.preserve, polygeist.varname = "X"} : memref<64x64xi16>
    %0 = arith.index_cast %arg0 : i32 to index
    affine.for %arg5 = 0 to 64 {
      affine.for %arg6 = 0 to %0 {
        %5 = arith.index_cast %arg6 : index to i32
        %6 = arith.trunci %5 : i32 to i16
        affine.for %arg7 = 0 to 64 {
          affine.store %6, %alloca[%arg5, %arg7] : memref<64x64xi16>
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      }
      %1 = affine.load %arg1[%arg5] : memref<65xi32>
      %2 = affine.load %arg1[%arg5 + 1] : memref<65xi32>
      %3 = arith.index_cast %2 : i32 to index
      %4 = arith.index_cast %1 : i32 to index
      scf.for %arg6 = %4 to %3 step %c1 {
        %5 = memref.load %arg2[%arg6] : memref<1024xi32>
        %6 = arith.index_cast %5 : i32 to index
        %7 = memref.load %arg3[%arg6] : memref<1024xi16>
        %8 = memref.load %alloca[%arg5, %6] : memref<64x64xi16>
        %9 = arith.addi %8, %7 : i16
        memref.store %9, %alloca[%arg5, %6] : memref<64x64xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.for %arg6 = 0 to 64 {
        %5 = affine.load %alloca[%arg5, %arg6] : memref<64x64xi16>
        affine.store %5, %arg4[%arg5, %arg6] : memref<64x64xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
}
