// RUN: hls-est %s --inline --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=auto --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=SCHED

// The RUN line with the DME front (--inline ... --dead-memory-elimination) is the
// default pipeline (MEMOS.md M1, M5: decisions #1 and #4); the one with
// --infer-vitis-split-array is the former default (td=auto), kept as a variant.

// forgebench mult_op_p3 (scalar shim) aborted in --convert-affine-to-loopschedule
// (IRMapping::lookup "expected 'from' to be contained within the map", from
// createLoopSchedulePipeline's terminator lookup). Reduced kernel: the
// `*out += a[i] * b[i]` of the source reaches hls-est as a store of
// `a[i] * b[i] + 0.0` (the accumulation is lost in the scalar-shim frontend
// output), unrolled 16 times: --auto-pipeline-unroll promotes the stores of
// `acc` to an iter_arg that yields only the last copy's sum. The other 15
// fmul / fadd results are unused, but the last fmul (start 8, latency 4) still
// holds the loop terminator back to cycle 12, while the yielded value (the
// identity select of materializeYieldedValues) starts at 10. Its register chain
// must run through a forwarding stage at 11; no op starts there, so the stage
// was not created and the chain ended at 11.
// Since W9r9-impl (OPEN_ISSUES O103) a value is registered once, by the stage
// that computes it, and the terminator reads that stage's result: no
// forwarding stage, and the lookup must still find the yielded value.

// CHECK: Total BRAM: 0

// SCHED: loopschedule.pipeline II = {{ *}}8
// SCHED: %[[SEL:.+]] = loopschedule.pipeline.stage start = 10 {
// SCHED-NEXT: %[[V:.+]] = arith.select
// SCHED-NEXT: loopschedule.register %[[V]] : f32
// SCHED-NOT: loopschedule.pipeline.stage start = 11
// SCHED: loopschedule.terminator iter_args({{.*}}, %[[SEL]]), results(%[[SEL]])

func.func @dot(%a: memref<64xf32>, %b: memref<64xf32>, %o: memref<1xf32>) {
  %cst = arith.constant 0.000000e+00 : f32
  %acc = memref.alloca() : memref<1xf32>
  affine.store %cst, %acc[0] : memref<1xf32>
  affine.for %i = 0 to 64 {
    %x = affine.load %a[%i] : memref<64xf32>
    %y = affine.load %b[%i] : memref<64xf32>
    %m = arith.mulf %x, %y : f32
    %s = arith.addf %m, %cst : f32
    affine.store %s, %acc[0] : memref<1xf32>
  } {hls.unroll = [{factor = 16 : i32, skip_exit_check = false}]}
  %r = affine.load %acc[0] : memref<1xf32>
  affine.store %r, %o[0] : memref<1xf32>
  return
}
