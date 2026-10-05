// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.middle_end.globals=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// tool.hls.middle_end.globals: kernel w9r8p_ie_acc (Vitis 2025.1 td=off: 80,
// c pipelined at II 1) with the accumulator Yb a global (as in ECG_Classifier
// baseline conv1d_2, Vitis II 1). The guarded read-modify-writes of Yb[c][l]
// merge to one load and one store per iteration only when the global is a
// root memref: II 1, Wb RAM_1WNR 64. Before: II 9 (7 with hoist_common_arm_loads), 32.
// CHECK: pipeline @ {{.*}}:42:9 in @{{.*}}: ii=1
// CHECK: Total BRAM: 80
// OFF: pipeline @ {{.*}}:42:9 in @{{.*}}: ii=7
// OFF: Total BRAM: 32

#set = affine_set<(d0, d1) : (-d0 - d1 + 1 >= 0)>
module {
  memref.global "private" @Ybg : memref<32x92xf32> = uninitialized
  func.func @_Z6ie_topPA92_fPA32_A5_fS0_(%arg0: memref<32x92xf32>, %arg1: memref<32x32x5xf32>, %arg2: memref<32x92xf32>) attributes {hls.orig_name = "ie_top", llvm.linkage = #llvm.linkage<external>} {
    %true = arith.constant true
    %c93_i32 = arith.constant 93 : i32
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.get_global @Ybg : memref<32x92xf32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "Wb"} : memref<32x32x5xf32>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Xb"} : memref<32x92xf32>
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 92 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<32x92xf32>
        affine.store %0, %alloca_1[%arg3, %arg4] : memref<32x92xf32>
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
        %0 = arith.index_cast %arg4 : index to i32
        affine.for %arg5 = 0 to 32 {
          affine.for %arg6 = 0 to 5 {
            %1 = arith.index_cast %arg6 : index to i32
            %2 = arith.addi %0, %1 : i32
            %3 = affine.if #set(%arg6, %arg4) -> i1 {
              affine.yield %true : i1
            } else {
              %4 = arith.cmpi sgt, %2, %c93_i32 : i32
              affine.yield %4 : i1
            }
            scf.if %3 {
              %4 = affine.load %alloca[%arg5, %arg4] : memref<32x92xf32>
              %5 = arith.addf %4, %cst : f32
              affine.store %5, %alloca[%arg5, %arg4] : memref<32x92xf32>
            } else {
              %4 = affine.load %alloca_1[%arg3, %arg4 + %arg6 - 2] : memref<32x92xf32>
              %5 = affine.load %alloca_0[%arg5, %arg3, %arg6] : memref<32x32x5xf32>
              %6 = arith.mulf %4, %5 : f32
              %7 = affine.load %alloca[%arg5, %arg4] : memref<32x92xf32>
              %8 = arith.addf %7, %6 : f32
              affine.store %8, %alloca[%arg5, %arg4] : memref<32x92xf32>
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
