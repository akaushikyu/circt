// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPhS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPhS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.middle_end.dead_memory.unread_register_elements=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF1
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPhS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.call_occupancy_after_partition=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF2

// VITIS_NOTES N110, kernel w9r15p_dw_dead (Vitis 2025.1 td=off: 24): a 7 x 7 window
// w[49] filled from a local tile in a pipelined j loop and passed to an inline-off
// calc(w) that reads only w[7*i + 6]. The window is scalarised (214-449); the
// stores into the 42 elements calc never reads are deleted with the tile loads
// that fed them, so tile is read 7 times per iteration (RAM_1WNR 6 copies).
// Off1 run: tool.hls.middle_end.dead_memory.unread_register_elements off (49 reads).
// Off2 run: tool.hls.pipeline_decision.call_occupancy_after_partition off (the call's
// occupancy counts the 49 window reads at two per cycle: OPEN_ISSUES O144).
// CHECK: Total BRAM: 24
// OFF1: Total BRAM: 64
// OFF2: Total BRAM: 4

module {
  func.func @_Z4calcPh(%arg0: memref<49xi8>) -> i8 attributes {hls.inline_off, hls.orig_name = "calc", llvm.linkage = #llvm.linkage<external>} {
    %c4 = arith.constant 4 : index
    %c5 = arith.constant 5 : index
    %c2 = arith.constant 2 : index
    %c3 = arith.constant 3 : index
    %c6 = arith.constant 6 : index
    %c1 = arith.constant 1 : index
    %c0 = arith.constant 0 : index
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "v"} : memref<7xi8>
    affine.for %arg1 = 0 to 7 {
      %8 = affine.load %arg0[%arg1 * 7 + 6] : memref<49xi8>
      affine.store %8, %alloca[%arg1] : memref<7xi8>
    }
    %0 = "polygeist.subindex"(%alloca, %c4) : (memref<7xi8>, index) -> memref<?xi8>
    %1 = "polygeist.subindex"(%alloca, %c0) : (memref<7xi8>, index) -> memref<?xi8>
    call @_ZL3casRhS_(%0, %1) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    %2 = "polygeist.subindex"(%alloca, %c5) : (memref<7xi8>, index) -> memref<?xi8>
    %3 = "polygeist.subindex"(%alloca, %c1) : (memref<7xi8>, index) -> memref<?xi8>
    call @_ZL3casRhS_(%2, %3) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    %4 = "polygeist.subindex"(%alloca, %c6) : (memref<7xi8>, index) -> memref<?xi8>
    %5 = "polygeist.subindex"(%alloca, %c2) : (memref<7xi8>, index) -> memref<?xi8>
    call @_ZL3casRhS_(%4, %5) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%5, %1) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    %6 = "polygeist.subindex"(%alloca, %c3) : (memref<7xi8>, index) -> memref<?xi8>
    call @_ZL3casRhS_(%6, %3) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%4, %0) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%0, %5) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%2, %6) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%3, %1) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%2, %0) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%6, %5) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%4, %6) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%0, %3) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    call @_ZL3casRhS_(%0, %6) {hls.inline_auto_off = {calls = 14 : i64, size = 8 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    %7 = affine.load %alloca[3] : memref<7xi8>
    return %7 : i8
  }
  func.func @_Z3topPhS_(%arg0: memref<4900xi8>, %arg1: memref<4096xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "w"} : memref<49xi8>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "tile"} : memref<70x70xi8>
    affine.for %arg2 = 0 to 70 {
      affine.for %arg3 = 0 to 70 {
        %0 = affine.load %arg0[%arg3 + %arg2 * 70] : memref<4900xi8>
        affine.store %0, %alloca_0[%arg2, %arg3] : memref<70x70xi8>
      }
    }
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 64 {
        affine.for %arg4 = 0 to 7 {
          affine.for %arg5 = 0 to 7 {
            %1 = affine.load %alloca_0[%arg2 + %arg4, %arg3 + %arg5] : memref<70x70xi8>
            affine.store %1, %alloca[%arg5 + %arg4 * 7] : memref<49xi8>
          }
        }
        %0 = func.call @_Z4calcPh(%alloca) : (memref<49xi8>) -> i8
        affine.store %0, %arg1[%arg3 + %arg2 * 64] : memref<4096xi8>
      }
    }
    return
  }
  func.func private @_ZL3casRhS_(%arg0: memref<?xi8>, %arg1: memref<?xi8>) attributes {hls.inline_auto_off = {size = 8 : i64}, hls.orig_name = "cas", llvm.linkage = #llvm.linkage<internal>} {
    %0 = affine.load %arg0[0] : memref<?xi8>
    %1 = arith.extui %0 : i8 to i32
    %2 = affine.load %arg1[0] : memref<?xi8>
    %3 = arith.extui %2 : i8 to i32
    %4 = arith.cmpi slt, %1, %3 : i32
    scf.if %4 {
      %5 = affine.load %arg0[0] : memref<?xi8>
      %6 = affine.load %arg1[0] : memref<?xi8>
      affine.store %6, %arg0[0] : memref<?xi8>
      affine.store %5, %arg1[0] : memref<?xi8>
    }
    return
  }
}
