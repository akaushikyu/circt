// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.partitioning.constant_index.through_views=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N94 through element views (OPEN_ISSUES O133), kernel w9r15p_rg_net
// (Vitis 2025.1 td=off: v scalarised): int v[8] (array_partition complete) whose
// elements are passed by reference to cas(int &, int &): cgeist passes
// polygeist.subindex element views. Every access, through the views in cas,
// uses a constant index, so v is registers
// (tool.hls.partitioning.constant_index.through_views). (The total stays at 8:
// cgeist keeps the 19 cas calls, which Vitis inlines; the loop's II is the
// calls' shared instance.)
// Off run: the views stop the analysis; v keeps a memory.
// CHECK: v (alloca)
// CHECK-NEXT: shape [8] x i32
// CHECK-NEXT: status: registers
// OFF: v (alloca)
// OFF-NEXT: shape [8] x i32
// OFF-NEXT: status: excluded_small

module {
  func.func @_Z3topPiS_S_(%arg0: memref<4096xi32>, %arg1: memref<512xi32>, %arg2: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1 = arith.constant 1 : index
    %c4095_i32 = arith.constant 4095 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %c7 = arith.constant 7 : index
    %c6 = arith.constant 6 : index
    %c5 = arith.constant 5 : index
    %c4 = arith.constant 4 : index
    %c3 = arith.constant 3 : index
    %c2 = arith.constant 2 : index
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "v"}], hls.preserve, polygeist.varname = "v"} : memref<8xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "L"} : memref<4096xi32>
    affine.for %arg3 = 0 to 4096 {
      %7 = affine.load %arg0[%arg3] : memref<4096xi32>
      affine.store %7, %alloca_0[%arg3] : memref<4096xi32>
    }
    %cast = memref.cast %alloca : memref<8xi32> to memref<?xi32>
    %0 = "polygeist.subindex"(%alloca, %c1) : (memref<8xi32>, index) -> memref<?xi32>
    %1 = "polygeist.subindex"(%alloca, %c2) : (memref<8xi32>, index) -> memref<?xi32>
    %2 = "polygeist.subindex"(%alloca, %c3) : (memref<8xi32>, index) -> memref<?xi32>
    %3 = "polygeist.subindex"(%alloca, %c4) : (memref<8xi32>, index) -> memref<?xi32>
    %4 = "polygeist.subindex"(%alloca, %c5) : (memref<8xi32>, index) -> memref<?xi32>
    %5 = "polygeist.subindex"(%alloca, %c6) : (memref<8xi32>, index) -> memref<?xi32>
    %6 = "polygeist.subindex"(%alloca, %c7) : (memref<8xi32>, index) -> memref<?xi32>
    affine.for %arg3 = 0 to 512 {
      affine.for %arg4 = 0 to 4 {
        %10 = arith.index_cast %arg4 : index to i32
        %11 = affine.load %arg1[%arg3] : memref<512xi32>
        %12 = arith.muli %10, %c1024_i32 : i32
        %13 = arith.addi %11, %12 : i32
        %14 = arith.andi %13, %c4095_i32 : i32
        %15 = arith.index_cast %14 : i32 to index
        %16 = memref.load %alloca_0[%15] : memref<4096xi32>
        affine.store %16, %alloca[%arg4] : memref<8xi32>
      }
      affine.for %arg4 = 4 to 8 {
        %10 = arith.index_cast %arg4 : index to i32
        %11 = affine.load %arg1[%arg3] : memref<512xi32>
        %12 = arith.addi %11, %10 : i32
        affine.store %12, %alloca[%arg4] : memref<8xi32>
      }
      func.call @_ZL3casRiS_(%cast, %0) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%1, %2) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%3, %4) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%5, %6) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%cast, %1) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%0, %2) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%3, %5) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%4, %6) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%0, %1) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%4, %5) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%cast, %3) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%2, %6) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%0, %4) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%1, %5) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%0, %3) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%2, %5) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%1, %3) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%2, %4) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      func.call @_ZL3casRiS_(%2, %3) {hls.inline_auto_off = {calls = 19 : i64, size = 8 : i64}} : (memref<?xi32>, memref<?xi32>) -> ()
      %7 = affine.load %alloca[3] : memref<8xi32>
      %8 = affine.load %alloca[4] : memref<8xi32>
      %9 = arith.xori %7, %8 : i32
      affine.store %9, %arg2[%arg3] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL3casRiS_(%arg0: memref<?xi32>, %arg1: memref<?xi32>) attributes {hls.inline_auto_off = {size = 8 : i64}, hls.orig_name = "cas", llvm.linkage = #llvm.linkage<internal>} {
    %0 = affine.load %arg0[0] : memref<?xi32>
    %1 = affine.load %arg1[0] : memref<?xi32>
    %2 = arith.cmpi slt, %0, %1 : i32
    scf.if %2 {
      %3 = affine.load %arg0[0] : memref<?xi32>
      %4 = affine.load %arg1[0] : memref<?xi32>
      affine.store %4, %arg0[0] : memref<?xi32>
      affine.store %3, %arg1[0] : memref<?xi32>
    }
    return
  }
}
