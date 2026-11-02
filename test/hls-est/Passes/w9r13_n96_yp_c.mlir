// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll=emit-remarks -o /dev/null 2>&1 | FileCheck %s --check-prefix=REM
// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s

// VITIS_NOTES N96, kernel w9r13i_yp_c (Vitis 2025.1 td=off: 64, 200-960 on i,
// j pipelined alone at II 1): a 3 x 3 max window `T[i + k][j + l]` on int
// T[64][64]; k = 1 makes `T[i + 1]`: refused.
// REM: remark: not flattened into the pipelined loop
// CHECK: Total BRAM: 64

module {
  func.func @_Z3topPKiPi(%arg0: memref<4096xi32>, %arg1: memref<3844xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "T"} : memref<64x64xi32>
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 64 {
        %0 = affine.load %arg0[%arg3 + %arg2 * 64] : memref<4096xi32>
        affine.store %0, %alloca[%arg2, %arg3] : memref<64x64xi32>
      }
    }
    affine.for %arg2 = 0 to 62 {
      affine.for %arg3 = 0 to 62 {
        %0 = affine.load %alloca[%arg2, %arg3] : memref<64x64xi32>
        %1 = affine.for %arg4 = 0 to 3 iter_args(%arg5 = %0) -> (i32) {
          %2 = affine.for %arg6 = 0 to 3 iter_args(%arg7 = %arg5) -> (i32) {
            %3 = affine.load %alloca[%arg2 + %arg4, %arg3 + %arg6] : memref<64x64xi32>
            %4 = arith.cmpi sgt, %3, %arg7 : i32
            %5 = arith.select %4, %3, %arg7 : i32
            affine.yield %5 : i32
          }
          affine.yield %2 : i32
        }
        affine.store %1, %arg1[%arg3 + %arg2 * 62] : memref<3844xi32>
      }
    }
    return
  }
}
