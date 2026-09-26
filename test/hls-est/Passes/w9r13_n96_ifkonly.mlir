// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll=emit-remarks -o /dev/null 2>&1 | FileCheck %s --check-prefix=REM

// VITIS_NOTES N76 / N96, kernel w9r9p_n64_ifkonly (Vitis 2025.1 td=off): the
// guard `if (k & 1)` is false for the copy that makes `l + 1`: flattened.
// REM-NOT: not flattened

module {
  func.func @_Z6ie_topPA92_fPA32_A5_fS0_(%arg0: memref<32x92xf32>, %arg1: memref<32x32x5xf32>, %arg2: memref<32x92xf32>) attributes {hls.orig_name = "ie_top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %cst = arith.constant 0.000000e+00 : f32
    %c0_i32 = arith.constant 0 : i32
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
            %0 = arith.index_cast %arg6 : index to i32
            %1 = arith.andi %0, %c1_i32 : i32
            %2 = arith.cmpi ne, %1, %c0_i32 : i32
            scf.if %2 {
              %3 = affine.load %alloca[%arg5, %arg4] : memref<32x92xf32>
              %4 = arith.addf %3, %cst : f32
              affine.store %4, %alloca[%arg5, %arg4] : memref<32x92xf32>
            } else {
              %3 = affine.load %alloca_1[%arg3, %arg4 + %arg6] : memref<32x96xf32>
              %4 = affine.load %alloca_0[%arg5, %arg3, %arg6] : memref<32x32x5xf32>
              %5 = arith.mulf %3, %4 : f32
              %6 = affine.load %alloca[%arg5, %arg4] : memref<32x92xf32>
              %7 = arith.addf %6, %5 : f32
              affine.store %7, %alloca[%arg5, %arg4] : memref<32x92xf32>
            }
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
