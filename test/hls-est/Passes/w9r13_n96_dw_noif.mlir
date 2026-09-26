// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s

// VITIS_NOTES N64 / N96, kernel w9r8p_dw_noif (Vitis 2025.1 td=off, 80): the
// ECG conv1d_2 nest x / l / c / k; l is not flattened into c, so the X loads
// invariant in c are hoisted out of the pipeline (Xb RAM_2P 8, not 32 as
// RAM_1WNR). The perfect nest x / l / c is not coalesced past l
// (--convert-affine-to-loopschedule reads hls.flatten_refused).
// CHECK: Total BRAM: 80

module {
  func.func @_Z6ie_topPA92_fPA32_A5_fS0_(%arg0: memref<32x92xf32>, %arg1: memref<32x32x5xf32>, %arg2: memref<32x92xf32>) attributes {hls.orig_name = "ie_top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "Yb"} : memref<32x92xf32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "Wb"} : memref<32x32x5xf32>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Xb"} : memref<32x96xf32>
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 92 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<32x92xf32>
        affine.store %0, %alloca_1[%arg3, %arg4] : memref<32x96xf32>
        affine.store %cst, %alloca[%arg3, %arg4] : memref<32x92xf32>
      }
    }
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 32 {
        affine.for %arg5 = 0 to 5 {
          %0 = affine.load %arg1[%arg3, %arg4, %arg5] : memref<32x32x5xf32>
          affine.store %0, %alloca_0[%arg3, %arg4, %arg5] : memref<32x32x5xf32>
        }
      }
    }
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 92 {
        affine.for %arg5 = 0 to 32 {
          affine.for %arg6 = 0 to 5 {
            %0 = affine.load %alloca_1[%arg3, %arg4 + %arg6] : memref<32x96xf32>
            %1 = affine.load %alloca_0[%arg5, %arg3, %arg6] : memref<32x32x5xf32>
            %2 = arith.mulf %0, %1 : f32
            %3 = affine.load %alloca[%arg5, %arg4] : memref<32x92xf32>
            %4 = arith.addf %3, %2 : f32
            affine.store %4, %alloca[%arg5, %arg4] : memref<32x92xf32>
          }
        }
      }
    }
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 92 {
        %0 = affine.load %alloca[%arg3, %arg4] : memref<32x92xf32>
        affine.store %0, %arg2[%arg3, %arg4] : memref<32x92xf32>
      }
    }
    return
  }
}
