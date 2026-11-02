// RUN: hls-est %s --symbol-privatize=exclude=top_condinv --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_condinv -o /dev/null | FileCheck %s --check-prefix=CONDINV
// RUN: hls-est %s --symbol-privatize=exclude=top_condinv --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram "--convert-affine-to-loopschedule=hoist-conditional-invariant=false" --bram-analysis=top=top_condinv -o /dev/null | FileCheck %s --check-prefix=CONDINV-OFF
// RUN: hls-est %s --symbol-privatize=exclude=top_condinv --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_condinv --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=CONDINV-DBG

// Conditional loop-invariant loads (VITIS_NOTES.md N38 R-hoist-cond): 32
// reads of rb under a break-guarded compare, unrolled in a loop pipelined at
// II 2, are hoisted out of the loop, as Vitis' LICM does (kernel
// w9r_b9condinv: the pipeline takes 32 scalar arguments, rb is a plain RAM,
// total 4). With the hoist off they are 32 reads per iteration: 15 copies.

// CONDINV: kind=RAM_2P  bram=2
// CONDINV: Total BRAM: 2
// CONDINV-OFF: kind=RAM_1WNR  bram=30
// CONDINV-OFF: Total BRAM: 30
// CONDINV-DBG: (loop-invariant load hoisted out of an if of the loop body)

module {
  // 32 rb[l] compares under a break flag, pipelined at II 2.
  func.func @top_condinv(%in: memref<1024xi32>, %ref: memref<32xi32>, %out: memref<1024xi32>) {
    %c32 = arith.constant 32 : i32
    %true = arith.constant true
    %false = arith.constant false
    %rb = memref.alloca() {hls.preserve, polygeist.varname = "rb_condinv"} : memref<32xi32>
    affine.for %l = 0 to 32 {
      %r = affine.load %ref[%l] : memref<32xi32>
      affine.store %r, %rb[%l] : memref<32xi32>
    }
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      %res:2 = affine.for %l = 0 to 32 iter_args(%o = %c32, %go = %true) -> (i32, i1) {
        %n:2 = scf.if %go -> (i32, i1) {
          %b = affine.load %rb[%l] : memref<32xi32>
          %ge = arith.cmpi sge, %v, %b : i32
          %li = arith.index_cast %l : index to i32
          %no = arith.select %ge, %li, %o : i32
          %ng = arith.xori %ge, %true : i1
          scf.yield %no, %ng : i32, i1
        } else {
          scf.yield %o, %false : i32, i1
        }
        affine.yield %n#0, %n#1 : i32, i1
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %res#0, %out[%i] : memref<1024xi32>
    } {hls.pipeline = [{II = 2 : i32, rewind = false, style = "stp"}]}
    return
  }
}
