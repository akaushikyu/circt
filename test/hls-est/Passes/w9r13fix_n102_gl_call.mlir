// RUN: hls-est %s --symbol-privatize=exclude=_Z6ie_topPA92_fPA32_A5_fS0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6ie_topPA92_fPA32_A5_fS0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.modulo.callee_global_recurrence=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N102 (W9r13 review finding 6), kernel w9r13rev_gl_call (Vitis 2025.1 td=off: II 2, Wb
// RAM_1WNR 32, total 48): the inline-off callee note() does hist[k & 7] += 1 on a global; the next
// iteration's call waits for this one. Key off: II 1, Wb 64, 80 (= gl_callw, a store only: Vitis II 1, 80).
// CHECK-DAG: scope pipeline @ {{.*}}:74:5 ii=1:
// CHECK-DAG: scope pipeline @ {{.*}}:46:9 ii=2:
// CHECK-DAG: scope pipeline @ {{.*}}:28:5 ii=1:
// CHECK-DAG: scope pipeline @ {{.*}}:35:5 ii=1:
// CHECK: Total BRAM: 48
// OFF-DAG: scope pipeline @ {{.*}}:74:5 ii=1:
// OFF-DAG: scope pipeline @ {{.*}}:46:9 ii=1:
// OFF-DAG: scope pipeline @ {{.*}}:28:5 ii=1:
// OFF-DAG: scope pipeline @ {{.*}}:35:5 ii=1:
// OFF: Total BRAM: 80
#set = affine_set<(d0, d1) : (-d0 - d1 + 1 >= 0)>
module {
  memref.global "private" @_ZL4hist : memref<8xi32> = uninitialized
  memref.global "private" @_ZL2Yb : memref<32x92xf32> = uninitialized
  func.func @_Z6ie_topPA92_fPA32_A5_fS0_(%arg0: memref<32x92xf32>, %arg1: memref<32x32x5xf32>, %arg2: memref<32x92xf32>) attributes {hls.orig_name = "ie_top", llvm.linkage = #llvm.linkage<external>} {
    %true = arith.constant true
    %c93_i32 = arith.constant 93 : i32
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "Wb"} : memref<32x32x5xf32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "Xb"} : memref<32x92xf32>
    %0 = memref.get_global @_ZL2Yb : memref<32x92xf32>
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 92 {
        %1 = affine.load %arg0[%arg3, %arg4] : memref<32x92xf32>
        affine.store %1, %alloca_0[%arg3, %arg4] : memref<32x92xf32>
        affine.store %cst, %0[%arg3, %arg4] : memref<32x92xf32>
      }
    }
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 32 {
        affine.for %arg5 = 0 to 5 {
          %1 = affine.load %arg1[%arg3, %arg4, %arg5] : memref<32x32x5xf32>
          affine.store %1, %alloca[%arg3, %arg4, %arg5] : memref<32x32x5xf32>
        }
      }
    }
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 92 {
        %1 = arith.index_cast %arg4 : index to i32
        affine.for %arg5 = 0 to 32 {
          %2 = arith.index_cast %arg5 : index to i32
          affine.for %arg6 = 0 to 5 {
            %3 = arith.index_cast %arg6 : index to i32
            %4 = arith.addi %1, %3 : i32
            %5 = affine.if #set(%arg6, %arg4) -> i1 {
              affine.yield %true : i1
            } else {
              %6 = arith.cmpi sgt, %4, %c93_i32 : i32
              affine.yield %6 : i1
            }
            scf.if %5 {
              %6 = affine.load %0[%arg5, %arg4] : memref<32x92xf32>
              %7 = arith.addf %6, %cst : f32
              affine.store %7, %0[%arg5, %arg4] : memref<32x92xf32>
            } else {
              %6 = affine.load %alloca_0[%arg3, %arg4 + %arg6 - 2] : memref<32x92xf32>
              %7 = affine.load %alloca[%arg5, %arg3, %arg6] : memref<32x32x5xf32>
              %8 = arith.mulf %6, %7 : f32
              %9 = affine.load %0[%arg5, %arg4] : memref<32x92xf32>
              %10 = arith.addf %9, %8 : f32
              affine.store %10, %0[%arg5, %arg4] : memref<32x92xf32>
            }
          }
          func.call @_ZL4notei(%2) : (i32) -> ()
        }
      }
    }
    affine.for %arg3 = 0 to 32 {
      affine.for %arg4 = 0 to 92 {
        %1 = affine.load %0[%arg3, %arg4] : memref<32x92xf32>
        affine.store %1, %arg2[%arg3, %arg4] : memref<32x92xf32>
      }
    }
    return
  }
  func.func private @_ZL4notei(%arg0: i32) attributes {hls.inline_off, hls.orig_name = "note", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    %c7_i32 = arith.constant 7 : i32
    %0 = memref.get_global @_ZL4hist : memref<8xi32>
    %1 = arith.andi %arg0, %c7_i32 : i32
    %2 = arith.index_cast %1 : i32 to index
    %3 = affine.load %0[symbol(%2)] : memref<8xi32>
    %4 = arith.addi %3, %c1_i32 : i32
    affine.store %4, %0[symbol(%2)] : memref<8xi32>
    return
  }
}
