// RUN: hls-est %s --convert-affine-to-loopschedule --bram-analysis --mlir-pass-statistics -o /dev/null 2> %t.1 | FileCheck %s
// RUN: FileCheck %s --check-prefix=STATS --input-file=%t.1
// RUN: hls-est %s --inline --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --mlir-pass-statistics -o /dev/null 2> %t.2 | FileCheck %s
// RUN: FileCheck %s --check-prefix=STATS --input-file=%t.2
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=auto --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --mlir-pass-statistics -o /dev/null 2> %t.3 | FileCheck %s
// RUN: FileCheck %s --check-prefix=STATS --input-file=%t.3

// The RUN line with the DME front (--inline ... --dead-memory-elimination) is the
// default pipeline (MEMOS.md M1, M5: decisions #1 and #4); the one with
// --infer-vitis-split-array is the former default (td=auto), kept as a variant.

// --convert-affine-to-loopschedule's memory dependence analysis
// (InnermostLoopDependenceAnalysis) only examines pairs of accesses inside one
// innermost loop, at that loop's depth: the only dependences a modulo
// schedule of an innermost loop can use. The function-wide analysis paired
// every access with every other access to the same memref at every loop depth
// they share; with user-unrolled copies of a pipelined loop inside one outer
// loop (forgebench conv_B / conv_C / mult_op_p1 / mlp / diff_orders_* /
// diff_dims_module_large) that was 99% of the run time (conv_B: 1.45M pairs
// per depth, 637 of 641 s) and those designs timed out at 120 s.
//
// Below: three sibling innermost loops in one outer loop; %a has 4 accesses
// (a store in the first loop, a load and a store in the second, a load in the
// third). Function scope: 4 x 3 = 12 ordered pairs of %a accesses at each of
// the 2 loop depths = 24. Innermost scope: the 2 ordered pairs of the second
// loop's load and store (every other loop has one access per memref) = 2, two
// dependence tests; the one dependence (the load before the store of the same
// element, within an iteration) is recorded either way. The estimate is the
// same with both scopes: every inner loop is pipelined at II 1, and %a, read
// and written every cycle by the second loop, is a RAM_2P of 4096x32 bits.

// CHECK: memref.alloca
// CHECK-NEXT: kind=RAM_2P bram=8
// CHECK: Total BRAM: 8

// STATS: AffineToLoopSchedule
// STATS-NEXT: (S) 0 dependence-pairs
// STATS-NEXT: (S) 0 dependence-tests
// STATS-NEXT: (S) 0 dependences

func.func @siblings(%in: memref<4x1024xi32>, %out: memref<4x1024xi32>) {
  %c1 = arith.constant 1 : i32
  %a = memref.alloca() {hls.preserve} : memref<4x1024xi32>
  affine.for %i = 0 to 4 {
    affine.for %j = 0 to 1024 {
      %v = affine.load %in[%i, %j] : memref<4x1024xi32>
      %w = arith.addi %v, %c1 : i32
      affine.store %w, %a[%i, %j] : memref<4x1024xi32>
    }
    affine.for %j = 0 to 1024 {
      %v = affine.load %a[%i, %j] : memref<4x1024xi32>
      %w = arith.addi %v, %c1 : i32
      affine.store %w, %a[%i, %j] : memref<4x1024xi32>
    }
    affine.for %j = 0 to 1024 {
      %v = affine.load %a[%i, %j] : memref<4x1024xi32>
      affine.store %v, %out[%i, %j] : memref<4x1024xi32>
    }
  }
  return
}
