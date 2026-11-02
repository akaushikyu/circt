// RUN: hls-est %s --symbol-privatize=exclude=_Z6s1_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6s1_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: sed -e "s/depth = 2 : i32, depth_defaulted,/depth = 2 : i32,/" %s | hls-est --symbol-privatize=exclude=_Z6s1_topPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6s1_topPKiPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s --check-prefix=EXPL
// W9 round 8 review defect 4 (kernel w9r8rev s1_nodepth.cpp): `#pragma HLS
// stream variable=buf` without a depth on int buf[1024] of a dataflow region:
// Vitis makes a FIFO as deep as the array (fifo_w32_d1024, 2 BRAM). cgeist
// writes the default depth 2 with depth_defaulted; hls-est sizes the FIFO by
// the array. An explicit depth 2 (EXPL) stays a 2-deep FIFO (shift
// registers, 0). MLIR from the private W9r8-fix cgeist.
// CHECK: depth the array's size
// CHECK: Total BRAM: 2
// EXPL: Total BRAM: 0
module {
  func.func @_Z6s1_topPKiPi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.orig_name = "s1_top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, hls.stream = [{depth = 2 : i32, depth_defaulted, type = "fifo", variable = "buf"}], polygeist.varname = "buf"} : memref<1024xi32>
    call @_ZL4prodPKiPi(%arg0, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 12 : i64}} : (memref<1024xi32>, memref<1024xi32>) -> ()
    call @_ZL4consPKiPi(%alloca, %arg1) {hls.inline_auto_off = {calls = 1 : i64, size = 12 : i64}} : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
  func.func private @_ZL4prodPKiPi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.inline_auto_off = {size = 12 : i64}, hls.orig_name = "prod", llvm.linkage = #llvm.linkage<internal>} {
    %c3_i32 = arith.constant 3 : i32
    affine.for %arg2 = 0 to 1024 {
      %0 = affine.load %arg0[%arg2] : memref<1024xi32>
      %1 = arith.muli %0, %c3_i32 : i32
      affine.store %1, %arg1[%arg2] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL4consPKiPi(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>) attributes {hls.inline_auto_off = {size = 12 : i64}, hls.orig_name = "cons", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    affine.for %arg2 = 0 to 1024 {
      %0 = affine.load %arg0[%arg2] : memref<1024xi32>
      %1 = arith.addi %0, %c1_i32 : i32
      affine.store %1, %arg1[%arg2] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
