// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.implicit_buffers[0].bus_requests.through_calls=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N95 through calls (W9r13 review finding 1), kernel w9r13rev_mx_callee (Vitis 2025.1 td=off:
// load's loop II 8, loc RAM_AUTO_1R1W 1, total 3): the m_axi port `in` is passed to an inline-off load
// function that reads it 8 times per iteration; the bundle's one read request per cycle holds there too.
// Key off: only the top's own ports are limited (II 4, loc two ports, 4).
// CHECK-DAG: scope pipeline @ {{.*}}:34:5 ii=1:
// CHECK-DAG: scope pipeline @ {{.*}}:24:5 ii=8:
// CHECK: Total BRAM: 3
// OFF-DAG: scope pipeline @ {{.*}}:34:5 ii=1:
// OFF-DAG: scope pipeline @ {{.*}}:24:5 ii=4:
// OFF: Total BRAM: 4
module {
  func.func @_Z3topPKiPi(%arg0: memref<512xi32> {hls.interface = [{bundle = "gmem0", depth = 512 : i32, mode = "m_axi", offset = "slave", port = "in"}]}, %arg1: memref<512xi32> {hls.interface = [{bundle = "gmem1", depth = 512 : i32, mode = "m_axi", offset = "slave", port = "out"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "loc"} : memref<512xi32>
    %cast = memref.cast %arg0 : memref<512xi32> to memref<?xi32>
    call @_ZL4loadPKiPi(%cast, %alloca) : (memref<?xi32>, memref<512xi32>) -> ()
    %cast_0 = memref.cast %arg1 : memref<512xi32> to memref<?xi32>
    call @_ZL4compPiS_(%alloca, %cast_0) : (memref<512xi32>, memref<?xi32>) -> ()
    return
  }
  func.func private @_ZL4loadPKiPi(%arg0: memref<?xi32>, %arg1: memref<512xi32>) attributes {hls.inline_off, hls.orig_name = "load", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 8 {
        %0 = affine.load %arg0[%arg3 + %arg2 * 8] : memref<?xi32>
        affine.store %0, %arg1[%arg3 + %arg2 * 8] : memref<512xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL4compPiS_(%arg0: memref<512xi32>, %arg1: memref<?xi32>) attributes {hls.inline_off, hls.orig_name = "comp", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %arg0[%arg2] : memref<512xi32>
      %1 = arith.muli %0, %c3_i32 : i32
      affine.store %1, %arg1[%arg2] : memref<?xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
