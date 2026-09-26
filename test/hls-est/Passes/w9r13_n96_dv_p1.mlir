// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll=emit-remarks -o /dev/null 2>&1 | FileCheck %s --check-prefix=REM
// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N96, kernel w9r13p_dv_p1 (Vitis 2025.1 td=off): `T[i + k][j + l]`
// with k, l unrolled by j's automatic pipeline; k = 1 makes `T[i + 1]`, a
// subscript of i's next index: Vitis refuses to flatten i into j (200-960,
// do-while loop) and pipelines j alone (trip 62, II 1); T 64. hls-est:
// --auto-pipeline-unroll leaves i a loop of its own (hls.flatten_refused).
// REM: remark: not flattened into the pipelined loop at {{.*}}: its unrolled sub-loop subscripts the next index of this loop (Vitis 200-960, do-while loop)
// REM: remark: automatically set the pipeline for the loop (trip 62, 0 perfect parent(s) flattened, 1 inner loop(s) to unroll)
// CHECK: pipeline @ {{.*}}:26:7 in @{{.*}}: ii=1 trip=62 source=auto flattened_parents=0
// CHECK: Total BRAM: 64

module {
  func.func @_Z3topPKiPi(%arg0: memref<4096xi32>, %arg1: memref<3844xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
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
      affine.for %arg3 = 0 to 62 {
        %0 = affine.for %arg4 = 0 to 3 iter_args(%arg5 = %c0_i32) -> (i32) {
          %1 = arith.index_cast %arg4 : index to i32
          %2 = affine.for %arg6 = 0 to 3 iter_args(%arg7 = %arg5) -> (i32) {
            %3 = arith.index_cast %arg6 : index to i32
            %4 = affine.load %alloca[%arg2 + %arg4, %arg3 + %arg6] : memref<64x64xi32>
            %5 = arith.addi %1, %3 : i32
            %6 = arith.addi %5, %c1_i32 : i32
            %7 = arith.muli %4, %6 : i32
            %8 = arith.addi %arg7, %7 : i32
            affine.yield %8 : i32
          }
          affine.yield %2 : i32
        }
        affine.store %0, %arg1[%arg3 + %arg2 * 62] : memref<3844xi32>
      }
    }
    return
  }
}
