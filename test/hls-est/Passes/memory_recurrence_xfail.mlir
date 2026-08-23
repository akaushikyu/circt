// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule=fast-threshold=0 -o - | FileCheck %s
// XFAIL: *
//
// Open issue O1 (hls-doc/notes/OPEN_ISSUES.md): a loop-carried
// memory dependence (store a[i], load a[i-1] one iteration later) never
// reaches either modulo scheduler, because the pass lowers the affine accesses
// in a copy of MemoryDependenceAnalysis while CyclicSchedulingAnalysis reads
// the cached instance keyed by the erased affine ops. The model's recurrence
// bound is load 1 + mulf 4 + store 1 = 6; both schedulers currently give II 1.
// When this starts passing (XPASS), drop the XFAIL line and close O1.
//
// CHECK: loopschedule.pipeline II = {{ *}}6

func.func @rec_f32(%a: memref<256xf32>, %k: f32) {
  affine.for %i = 1 to 256 {
    %0 = affine.load %a[%i - 1] : memref<256xf32>
    %1 = arith.mulf %0, %k : f32
    affine.store %1, %a[%i] : memref<256xf32>
  }
  return
}
