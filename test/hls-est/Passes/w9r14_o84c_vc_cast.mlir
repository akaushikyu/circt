// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKN3hls6vectorIsLm8EEEPKiPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKN3hls6vectorIsLm8EEEPKiPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.structs.specialize_split_casts=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// OPEN_ISSUES O84 (c), kernel w9r14i_vc_cast (Vitis 2025.1 td=off): a static
// hls::vector<short, 8> B[512] (cyclic 8) passed to two inline-off functions
// by pointer (memref.cast to memref<?x...> after --split-struct-memrefs):
// Vitis applies the partition (214-248) and the lanes' constant-index complete
// partition (214-449): 64 banks of 64 x 16, PIPO single, 64 + the g0 adapter 8
// + g1 2 = 74. hls-est: the callees are specialised to the static type after
// the split (tool.hls.structs.specialize_split_casts); off: the pragma is
// dropped (used by memref.cast), 18.
// CHECK: Total BRAM: 74
// OFF: Total BRAM: 18

module {
  memref.global "private" @"_Z3topPKN3hls6vectorIsLm8EEEPKiPs@static@_ZZ3topPKN3hls6vectorIsLm8EEEPKiPsE1B@init" : memref<1xi1> = dense<true>
  memref.global "private" @"_Z3topPKN3hls6vectorIsLm8EEEPKiPs@static@_ZZ3topPKN3hls6vectorIsLm8EEEPKiPsE1B" : memref<512x!llvm.struct<(struct<(array<8 x i16>)>)>> = uninitialized {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "B"}]}
  func.func @_Z3topPKN3hls6vectorIsLm8EEEPKiPs(%arg0: memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>> {hls.interface = [{bundle = "g0", depth = 512 : i32, mode = "m_axi", port = "in"}]}, %arg1: memref<?xi32> {hls.interface = [{bundle = "g1", depth = 64 : i32, mode = "m_axi", port = "idx"}]}, %arg2: memref<?xi16> {hls.interface = [{bundle = "g2", depth = 64 : i32, mode = "m_axi", port = "out"}]}) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %false = arith.constant false
    %0 = memref.get_global @"_Z3topPKN3hls6vectorIsLm8EEEPKiPs@static@_ZZ3topPKN3hls6vectorIsLm8EEEPKiPsE1B" : memref<512x!llvm.struct<(struct<(array<8 x i16>)>)>>
    %1 = memref.get_global @"_Z3topPKN3hls6vectorIsLm8EEEPKiPs@static@_ZZ3topPKN3hls6vectorIsLm8EEEPKiPsE1B@init" : memref<1xi1>
    %2 = affine.load %1[0] : memref<1xi1>
    scf.if %2 {
      affine.store %false, %1[0] : memref<1xi1>
    }
    %cast = memref.cast %0 : memref<512x!llvm.struct<(struct<(array<8 x i16>)>)>> to memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>
    call @_ZL4loadPKN3hls6vectorIsLm8EEEPS1_(%arg0, %cast) : (memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>, memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>) -> ()
    call @_ZL3usePKN3hls6vectorIsLm8EEEPKiPs(%cast, %arg1, %arg2) : (memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>, memref<?xi32>, memref<?xi16>) -> ()
    return
  }
  func.func private @_ZL4loadPKN3hls6vectorIsLm8EEEPS1_(%arg0: memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>, %arg1: memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>) attributes {hls.inline_off, hls.orig_name = "load", llvm.linkage = #llvm.linkage<internal>} {
    %c16 = arith.constant 16 : index
    %0 = "polygeist.memref2pointer"(%arg1) : (memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg2 = 0 to 512 {
      %2 = arith.muli %arg2, %c16 : index
      %3 = arith.index_cast %2 : index to i64
      %4 = llvm.getelementptr %0[%3] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %5 = llvm.getelementptr %1[%3] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      affine.for %arg3 = 0 to 16 {
        %6 = arith.index_cast %arg3 : index to i32
        %7 = llvm.getelementptr %5[%6] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        %8 = llvm.load %7 : !llvm.ptr -> i8
        %9 = llvm.getelementptr %4[%6] : (!llvm.ptr, i32) -> !llvm.ptr, i8
        llvm.store %8, %9 : i8, !llvm.ptr
      }
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL3usePKN3hls6vectorIsLm8EEEPKiPs(%arg0: memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>, %arg1: memref<?xi32>, %arg2: memref<?xi16>) attributes {hls.inline_off, hls.orig_name = "use", llvm.linkage = #llvm.linkage<internal>} {
    %c16 = arith.constant 16 : index
    %c0_i16 = arith.constant 0 : i16
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", from = "_ZN3hls6vectorIsLm8EEixEm", variable = "this"}], polygeist.varname = "v"} : memref<1x!llvm.struct<(struct<(array<8 x i16>)>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(struct<(array<8 x i16>)>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(struct<(array<8 x i16>)>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 64 {
      %2 = affine.for %arg4 = 0 to 8 iter_args(%arg5 = %c0_i16) -> (i16) {
        %3 = arith.index_cast %arg4 : index to i32
        %4 = affine.load %arg1[%arg3] : memref<?xi32>
        %5 = arith.addi %4, %3 : i32
        %6 = arith.index_cast %5 : i32 to index
        %7 = arith.muli %6, %c16 : index
        %8 = arith.index_cast %7 : index to i64
        %9 = llvm.getelementptr %1[%8] : (!llvm.ptr, i64) -> !llvm.ptr, i8
        affine.for %arg6 = 0 to 8 {
          %16 = arith.index_cast %arg6 : index to i32
          %17 = llvm.getelementptr %9[%16] : (!llvm.ptr, i32) -> !llvm.ptr, i16
          %18 = llvm.load %17 : !llvm.ptr -> i16
          %19 = llvm.getelementptr %0[%16] : (!llvm.ptr, i32) -> !llvm.ptr, i16
          llvm.store %18, %19 : i16, !llvm.ptr
        }
        %10 = arith.extsi %3 : i32 to i64
        %11 = arith.index_castui %10 : i64 to index
        %12 = arith.index_cast %11 : index to i32
        %13 = llvm.getelementptr %0[%12] : (!llvm.ptr, i32) -> !llvm.ptr, i16
        %14 = llvm.load %13 : !llvm.ptr -> i16
        %15 = arith.addi %arg5, %14 : i16
        affine.yield %15 : i16
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.store %2, %arg2[%arg3] : memref<?xi16>
    }
    return
  }
}
