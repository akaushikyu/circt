// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll=emit-remarks -o /dev/null 2>&1 | FileCheck %s --check-prefix=REM
// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s

// VITIS_NOTES N96, kernel w9r13p_dv_p2 (Vitis 2025.1 td=off): `T[(i + 2k) & 63][j + l]`
// never subscripts `i + 1`: flattened (200-2061, trip 3844), T 64.
// REM-NOT: not flattened
// REM: remark: automatically set the pipeline for the loop (trip 3844, 1 perfect parent(s) flattened, 1 inner loop(s) to unroll)
// CHECK: Total BRAM: 64

module {
  func.func @_Z3topPKiPi(%arg0: memref<4096xi32>, %arg1: memref<3844xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c63_i32 = arith.constant 63 : i32
    %c2_i32 = arith.constant 2 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "T"} : memref<64x64xi32>
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 64 {
        %0 = affine.load %arg0[%arg3 + %arg2 * 64] : memref<4096xi32>
        affine.store %0, %alloca[%arg2, %arg3] : memref<64x64xi32>
      }
    }
    affine.for %arg2 = 0 to 62 {
      %0 = arith.index_cast %arg2 : index to i32
      affine.for %arg3 = 0 to 62 {
        %1 = arith.index_cast %arg3 : index to i32
        %2 = affine.for %arg4 = 0 to 3 iter_args(%arg5 = %c0_i32) -> (i32) {
          %3 = arith.index_cast %arg4 : index to i32
          %4 = arith.muli %3, %c2_i32 : i32
          %5 = arith.addi %0, %4 : i32
          %6 = arith.andi %5, %c63_i32 : i32
          %7 = arith.index_cast %6 : i32 to index
          %8 = affine.for %arg6 = 0 to 3 iter_args(%arg7 = %arg5) -> (i32) {
            %9 = arith.index_cast %arg6 : index to i32
            %10 = arith.addi %1, %9 : i32
            %11 = arith.index_cast %10 : i32 to index
            %12 = memref.load %alloca[%7, %11] : memref<64x64xi32>
            %13 = arith.addi %3, %9 : i32
            %14 = arith.addi %13, %c1_i32 : i32
            %15 = arith.muli %12, %14 : i32
            %16 = arith.addi %arg7, %15 : i32
            affine.yield %16 : i32
          }
          affine.yield %8 : i32
        }
        affine.store %2, %arg1[%arg3 + %arg2 * 62] : memref<3844xi32>
      }
    }
    return
  }
}
