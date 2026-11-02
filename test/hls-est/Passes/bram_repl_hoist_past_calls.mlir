// RUN: hls-est %s --symbol-privatize=exclude=top_callfill --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_callfill -o /dev/null | FileCheck %s --check-prefix=CALLFILL
// RUN: hls-est %s --symbol-privatize=exclude=top_callfill --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram "--convert-affine-to-loopschedule=hoist-past-calls=false" --bram-analysis=top=top_callfill -o /dev/null | FileCheck %s --check-prefix=CALLFILL-OFF

// An array filled by a call before a loop is still hoisted from: a callee
// can write an array it received only while a call runs, so only a call
// inside the loop pins its loads (Analog-CIM on-board `v_ref_buf`, filled by
// `load_v_ref_from_DRAM` and read under a break-guarded compare: Vitis 4
// BRAM, a plain RAM). With hoist-past-calls off, any call taking the array
// anywhere in the function keeps its 32 loads in the II-2 pipeline.

// CALLFILL: kind=RAM_2P  bram=2
// CALLFILL: Total BRAM: 2
// CALLFILL-OFF: kind=RAM_1WNR  bram=30

module {
  func.func private @fill_rb(%rb: memref<32xi32>, %ref: memref<32xi32>) attributes {hls.inline_off} {
    affine.for %l = 0 to 32 {
      %r = affine.load %ref[%l] : memref<32xi32>
      affine.store %r, %rb[%l] : memref<32xi32>
    }
    return
  }

  func.func @top_callfill(%in: memref<1024xi32>, %ref: memref<32xi32>, %out: memref<1024xi32>) {
    %c32 = arith.constant 32 : i32
    %true = arith.constant true
    %false = arith.constant false
    %rb = memref.alloca() {hls.preserve, polygeist.varname = "rb_callfill"} : memref<32xi32>
    func.call @fill_rb(%rb, %ref) : (memref<32xi32>, memref<32xi32>) -> ()
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
