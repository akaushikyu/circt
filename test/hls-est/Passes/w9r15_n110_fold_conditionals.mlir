// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA70_hPA64_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA70_hPA64_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.partitioning.constant_index.fold_conditionals=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N110 corpus shape (Dehazing tile_median), kernel w9r15i_cw_cross
// (Vitis 2025.1 td=off: 36, tile RAM_1WNR 9 copies at II 2): a cross window filled
// through a counter that skips the centre (if (b != 3) cr[n++] = ..): once the
// loop is unrolled the counter's scf.if / select chain folds to constants
// (tool.hls.partitioning.constant_index.fold_conditionals), the windows are
// registers and only the elements the kept callee reads are loaded.
// Off run: the counter stays unknown, cr keeps its memory and the call's port bound.
// CHECK: Total BRAM: 36
// OFF: Total BRAM: 8

module {
  func.func @_Z3topPA70_hPA64_h(%arg0: memref<70x70xi8>, %arg1: memref<64x64xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c7_i32 = arith.constant 7 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "cr"} : memref<13xi8>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "sq"} : memref<49xi8>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "tile"} : memref<70x70xi8>
    affine.for %arg2 = 0 to 70 {
      affine.for %arg3 = 0 to 70 {
        %0 = affine.load %arg0[%arg2, %arg3] : memref<70x70xi8>
        affine.store %0, %alloca_1[%arg2, %arg3] : memref<70x70xi8>
      }
    }
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 64 {
        affine.for %arg4 = 0 to 7 {
          affine.for %arg5 = 0 to 7 {
            %2 = affine.load %alloca_1[%arg2 + %arg4, %arg3 + %arg5] : memref<70x70xi8>
            affine.store %2, %alloca_0[%arg5 + %arg4 * 7] : memref<49xi8>
          }
        }
        affine.for %arg4 = 0 to 7 {
          %2 = affine.load %alloca_1[%arg2 + %arg4, %arg3 + 3] : memref<70x70xi8>
          affine.store %2, %alloca[%arg4] : memref<13xi8>
        }
        %0 = affine.for %arg4 = 0 to 7 iter_args(%arg5 = %c7_i32) -> (i32) {
          %2 = arith.index_cast %arg4 : index to i32
          %3 = arith.cmpi ne, %2, %c3_i32 : i32
          %4 = scf.if %3 -> (i32) {
            %5 = arith.addi %arg5, %c1_i32 : i32
            %6 = arith.index_cast %arg5 : i32 to index
            %7 = affine.load %alloca_1[%arg2 + 3, %arg3 + %arg4] : memref<70x70xi8>
            memref.store %7, %alloca[%6] : memref<13xi8>
            scf.yield %5 : i32
          } else {
            scf.yield %arg5 : i32
          }
          affine.yield %4 : i32
        }
        %1 = func.call @_ZL3medPhS_(%alloca_0, %alloca) : (memref<49xi8>, memref<13xi8>) -> i8
        affine.store %1, %arg1[%arg2, %arg3] : memref<64x64xi8>
      } {hls.pipeline = [{II = 2 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func private @_ZL3medPhS_(%arg0: memref<49xi8>, %arg1: memref<13xi8>) -> i8 attributes {hls.inline_off, hls.orig_name = "med", llvm.linkage = #llvm.linkage<internal>} {
    %c6_i32 = arith.constant 6 : i32
    %c7_i32 = arith.constant 7 : i32
    %c0_i8 = arith.constant 0 : i8
    %alloca = memref.alloca() {polygeist.varname = "m"} : memref<1xi8>
    %cast = memref.cast %alloca : memref<1xi8> to memref<?xi8>
    affine.store %c0_i8, %alloca[0] : memref<1xi8>
    affine.for %arg2 = 0 to 7 {
      %1 = arith.index_cast %arg2 : index to i32
      %2 = affine.load %alloca[0] : memref<1xi8>
      %3 = arith.extui %2 : i8 to i32
      %4 = arith.muli %1, %c7_i32 : i32
      %5 = arith.addi %4, %c6_i32 : i32
      %6 = arith.index_cast %5 : i32 to index
      %7 = affine.load %arg0[%arg2 * 7 + 6] : memref<49xi8>
      %8 = arith.extui %7 : i8 to i32
      %9 = arith.cmpi sgt, %3, %8 : i32
      %10 = scf.if %9 -> (memref<?xi8>) {
        scf.yield %cast : memref<?xi8>
      } else {
        %12 = "polygeist.subindex"(%arg0, %6) : (memref<49xi8>, index) -> memref<?xi8>
        scf.yield %12 : memref<?xi8>
      }
      %11 = affine.load %10[0] : memref<?xi8>
      affine.store %11, %alloca[0] : memref<1xi8>
    }
    affine.for %arg2 = 0 to 13 {
      %1 = affine.load %arg1[%arg2] : memref<13xi8>
      %2 = affine.load %alloca[0] : memref<1xi8>
      %3 = arith.xori %2, %1 : i8
      affine.store %3, %alloca[0] : memref<1xi8>
    }
    %0 = affine.load %alloca[0] : memref<1xi8>
    return %0 : i8
  }
}
