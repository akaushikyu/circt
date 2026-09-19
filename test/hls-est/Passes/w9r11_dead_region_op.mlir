// RUN: hls-est %s --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s
// W9r11-impl (2026-10-22): the dead-op sweep of --convert-affine-to-loopschedule collected a dead scf.if and the dead ops
// inside it and erased both (a double free: class_ece8893_2023_spring Eyeriss once --auto-pipeline-unroll folded the unrolled
// copies' guards, VITIS_NOTES N89). A dead region op now takes its body with it.
// CHECK: Total BRAM: 0{{$}}
module {
  func.func @df(%arg0: memref<64xi32>, %arg1: i1) {
    affine.for %i = 0 to 64 {
      %v = affine.load %arg0[%i] : memref<64xi32>
      scf.if %arg1 {
        %x = arith.addi %v, %v : i32
        %y = arith.muli %x, %v : i32
      }
      affine.store %v, %arg0[%i] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
