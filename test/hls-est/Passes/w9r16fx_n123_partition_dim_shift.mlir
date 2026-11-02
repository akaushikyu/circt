// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s

// VITIS_NOTES N123 (W9r16 review fixes), kernel w9r16fx_pm_kept1 (Vitis 2025.1 td=off: 4):
// w9r16i_pm_kept with the pragma `dim=1 cyclic factor=2` on f(int a[50][8]); the kept w
// passes the global g[100][8] on, so cgeist carries the entry to w's parameter with
// rows = 50. The root has more rows: Vitis applies the pragma one dimension deeper
// (cyclic 2 on g's dimension 2: g_0 / g_1 400 x 32, 2 BRAM each), as for a global root
// (w9r16rv_pm_dim1); a dim=2 entry falls past the rank and is dropped (pm_kept: 2).
// CHECK: Total BRAM: 4

module {
  memref.global @g : memref<100x8xi32> = uninitialized
  func.func @_Z1fPA8_iPii(%arg0: memref<50x8xi32> {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "a"}]}, %arg1: memref<8xi32>, %arg2: i32) attributes {hls.inline_off, hls.orig_name = "f", llvm.linkage = #llvm.linkage<external>} {
    %0 = arith.index_cast %arg2 : i32 to index
    affine.for %arg3 = 0 to %0 {
      affine.for %arg4 = 0 to 8 {
        %1 = affine.load %arg0[%arg3 * 2, %arg4] : memref<50x8xi32>
        %2 = affine.load %arg0[%arg3 * 2 + 1, %arg4] : memref<50x8xi32>
        %3 = arith.addi %1, %2 : i32
        %4 = affine.load %arg1[%arg4] : memref<8xi32>
        %5 = arith.addi %4, %3 : i32
        affine.store %5, %arg1[%arg4] : memref<8xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func @_Z1wPA8_iPii(%arg0: memref<100x8xi32> {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", rows = 50 : i64, variable = "a"}]}, %arg1: memref<8xi32>, %arg2: i32) attributes {hls.inline_off, hls.orig_name = "w", llvm.linkage = #llvm.linkage<external>} {
    %0 = arith.index_cast %arg2 : i32 to index
    affine.for %arg3 = 0 to %0 {
      affine.for %arg4 = 0 to 8 {
        %1 = affine.load %arg0[%arg3 * 2, %arg4] : memref<100x8xi32>
        %2 = affine.load %arg0[%arg3 * 2 + 1, %arg4] : memref<100x8xi32>
        %3 = arith.addi %1, %2 : i32
        %4 = affine.load %arg1[%arg4] : memref<8xi32>
        %5 = arith.addi %4, %3 : i32
        affine.store %5, %arg1[%arg4] : memref<8xi32>
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func @_Z3topPiS_i(%arg0: memref<800xi32>, %arg1: memref<8xi32>, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1 = arith.constant -1 : index
    %c8 = arith.constant 8 : index
    %c0 = arith.constant 0 : index
    %0 = memref.get_global @g : memref<100x8xi32>
    affine.for %arg3 = 0 to 800 {
      %1 = affine.load %arg0[%arg3] : memref<800xi32>
      %2 = arith.cmpi slt, %arg3, %c0 : index
      %3 = arith.subi %c-1, %arg3 : index
      %4 = arith.select %2, %3, %arg3 : index
      %5 = arith.divsi %4, %c8 : index
      %6 = arith.subi %c-1, %5 : index
      %7 = arith.select %2, %6, %5 : index
      %8 = arith.remsi %arg3, %c8 : index
      %9 = arith.cmpi slt, %8, %c0 : index
      %10 = arith.addi %8, %c8 : index
      %11 = arith.select %9, %10, %8 : index
      memref.store %1, %0[%7, %11] : memref<100x8xi32>
    }
    call @_Z1wPA8_iPii(%0, %arg1, %arg2) : (memref<100x8xi32>, memref<8xi32>, i32) -> ()
    return
  }
}
