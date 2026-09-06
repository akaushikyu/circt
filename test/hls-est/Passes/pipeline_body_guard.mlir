// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=big --config-set 'scheduling.modulo.max_pipeline_body_ops=8' -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=big -o /dev/null 2>&1 | FileCheck %s --check-prefix=DEFAULT

// scheduling.modulo.max_pipeline_body_ops: a pipelined loop whose body has
// more operations is left sequential with a warning (a memory guard: the
// pipeline pragma of hlsyn-vitis seidel-2d unrolls 118 x 118 stencil
// iterations into one body of 264,084 operations, which ran out of memory
// in the pipeline construction; OPEN_ISSUES O76). The default (250,000) does
// not touch this loop.

// CHECK: warning: not pipelined (left as a sequential loop): the body has {{[0-9]+}} operations, more than scheduling.modulo.max_pipeline_body_ops = 8
// CHECK: Total BRAM:
// DEFAULT-NOT: max_pipeline_body_ops
// DEFAULT: Total BRAM:

module {
  func.func @big(%a: memref<64xi32>, %b: memref<64xi32>) {
    affine.for %i = 0 to 64 {
      %x = affine.load %a[%i] : memref<64xi32>
      %y = arith.addi %x, %x : i32
      %z = arith.muli %y, %x : i32
      %w = arith.subi %z, %y : i32
      %v = arith.addi %w, %z : i32
      %u = arith.muli %v, %w : i32
      affine.store %u, %b[%i] : memref<64xi32>
    } {hls.pipeline = {ii = 1 : i32}}
    return
  }
}
