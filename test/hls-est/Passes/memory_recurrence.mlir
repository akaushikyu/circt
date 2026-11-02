// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=fast-threshold=0 -o - | FileCheck %s
//
// O1 (hls-doc/notes/OPEN_ISSUES.md), closed by W9r11-impl (2026-10-22): a
// loop-carried memory dependence (store a[i], load a[i-1] one iteration
// later) never reached either modulo scheduler (this test was XFAIL with the
// old model's bound load 1 + mulf 4 + store 1 = 6). VITIS_NOTES N87 R3: Vitis
// forwards the value of the previous iteration (no load of a is left in the
// loop) and the II is the multiply's recurrence latency, fmul f32 3 (N83,
// scheduling.dependences.recurrence_latencies); both schedulers take it as the
// loop's minimum II (hls.memory_recurrence, R3).
//
// CHECK: loopschedule.pipeline II = {{ *}}3

func.func @rec_f32(%a: memref<256xf32>, %k: f32) {
  affine.for %i = 1 to 256 {
    %0 = affine.load %a[%i - 1] : memref<256xf32>
    %1 = arith.mulf %0, %k : f32
    affine.store %1, %a[%i] : memref<256xf32>
  }
  return
}
