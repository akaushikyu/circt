// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug --config-set scheduling.dependences.register_recurrence_latencies=true -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug --config-set scheduling.dependences.register_recurrence_latencies=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N83 (kernels w9r10p_rc_*): `s = s op a[i]` in a pipelined loop reaches
// II 4 (fadd), 3 (fmul), 5 (dadd), 6 (dmul): the recurrence latencies, below the
// chained 5 / 4 / 7 / 7 that the operator latencies hold since W9r18-impl (N135).
// scheduling.dependences.register_recurrence_latencies gives the adds and multiplies on
// an iter_arg recurrence their recurrence latency; off, they keep the operator latency.
// Off by default since the W9 round 18 review fixes (VITIS_NOTES N139 corrected): Vitis keeps
// the chained latencies in w9r18rv_k3rec (`s = s*a[i] + b[i]`, II 9), k4recif (II 8) and about
// 30 polybench__reproducible loops, so these bare-shape kernels are the only evidence for it.

// CHECK-DAG: in @fadd: ii=4
// CHECK-DAG: in @fmul: ii=3
// CHECK-DAG: in @dadd: ii=5
// CHECK-DAG: in @dmul: ii=6
// OFF-DAG: in @fadd: ii=5
// OFF-DAG: in @fmul: ii=4
// OFF-DAG: in @dadd: ii=7
// OFF-DAG: in @dmul: ii=7

module {
  func.func @fadd(%a: memref<1024xf32>, %o: memref<1xf32>) {
    %z = arith.constant 0.0 : f32
    %s = affine.for %i = 0 to 1024 iter_args(%acc = %z) -> (f32) {
      %x = affine.load %a[%i] : memref<1024xf32>
      %n = arith.addf %acc, %x : f32
      affine.yield %n : f32
    }
    affine.store %s, %o[0] : memref<1xf32>
    return
  }
  func.func @fmul(%a: memref<1024xf32>, %o: memref<1xf32>) {
    %z = arith.constant 1.0 : f32
    %s = affine.for %i = 0 to 1024 iter_args(%acc = %z) -> (f32) {
      %x = affine.load %a[%i] : memref<1024xf32>
      %n = arith.mulf %acc, %x : f32
      affine.yield %n : f32
    }
    affine.store %s, %o[0] : memref<1xf32>
    return
  }
  func.func @dadd(%a: memref<1024xf64>, %o: memref<1xf64>) {
    %z = arith.constant 0.0 : f64
    %s = affine.for %i = 0 to 1024 iter_args(%acc = %z) -> (f64) {
      %x = affine.load %a[%i] : memref<1024xf64>
      %n = arith.addf %acc, %x : f64
      affine.yield %n : f64
    }
    affine.store %s, %o[0] : memref<1xf64>
    return
  }
  func.func @dmul(%a: memref<1024xf64>, %o: memref<1xf64>) {
    %z = arith.constant 1.0 : f64
    %s = affine.for %i = 0 to 1024 iter_args(%acc = %z) -> (f64) {
      %x = affine.load %a[%i] : memref<1024xf64>
      %n = arith.mulf %acc, %x : f64
      affine.yield %n : f64
    }
    affine.store %s, %o[0] : memref<1xf64>
    return
  }
}
