// RUN: hls-est %s --bram-analysis=top=chain_df --bram-debug -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: hls-est %s --bram-analysis=top=chain_seq -o /dev/null | FileCheck %s --check-prefix=SEQ
// RUN: hls-est %s --bram-analysis=top=loop_df -o /dev/null | FileCheck %s --check-prefix=LOOP
// RUN: hls-est %s --bram-analysis=top=mixed_df --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=MIXED
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --bram-analysis=top=unrolled_df --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=UNR

// In a dataflow region every call site is a process of its own: the
// processes overlap, so the ordering that lets sequential calls share one
// instance (N14 R2: a common array, a value dependence) does not apply
// (VITIS_NOTES N48: soda erosion, `Module2Func` called 68 times and
// `Module3Func` 4 times in `erosion_kernel` (dataflow), each with a 120 x 16
// delay buffer: Vitis 72 copies, 1 BRAM each).
//
// @stage holds a 512 x 32 delay buffer (1 BRAM) and passes its input on.

module {
  func.func private @stage(%in: memref<512xi32>, %out: memref<512xi32>) attributes {hls.inline_off, hls.orig_name = "stage"} {
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
    }
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  // A chain of four stages, each feeding the next through a channel: in a
  // dataflow region 4 instances (4 BRAM), plus the three channels, which
  // are ping-pong buffers there (2 each).
  // CHECK: 512x32b -> RAM_1P (x36/port) = 1 BRAM_18K x 4 instance(s) of @stage = 4
  // CHECK: Total BRAM: 10
  // DBG: in @chain_df (x1): 4 call site(s) -> 4 instance(s) (dataflow region: every call site is a process of its own)
  func.func @chain_df(%a: memref<512xi32>, %e: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %b = memref.alloca() : memref<512xi32>
    %c = memref.alloca() : memref<512xi32>
    %d = memref.alloca() : memref<512xi32>
    func.call @stage(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @stage(%b, %c) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @stage(%c, %d) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @stage(%d, %e) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  // The same chain without dataflow: every call is ordered after the one
  // before it (a common array), one shared instance; the three
  // intermediate arrays are 1 BRAM each.
  // SEQ-NOT: instance(s) of @stage
  // SEQ: Total BRAM: 4
  func.func @chain_seq(%a: memref<512xi32>, %e: memref<512xi32>) {
    %b = memref.alloca() : memref<512xi32>
    %c = memref.alloca() : memref<512xi32>
    %d = memref.alloca() : memref<512xi32>
    func.call @stage(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @stage(%b, %c) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @stage(%c, %d) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @stage(%d, %e) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  // A call in a loop of a dataflow function is no process of the region:
  // the sequential rule applies (one call site in a loop: 1 instance).
  // LOOP-NOT: instance(s) of @stage
  // LOOP: Total BRAM: 1
  func.func @loop_df(%a: memref<512xi32>, %e: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    affine.for %i = 0 to 4 {
      func.call @stage(%a, %e) : (memref<512xi32>, memref<512xi32>) -> ()
    }
    return
  }
  // Both kinds for one callee (W9 round 6 review defect 1: one nested call
  // site used to send every call of the region back to the sequential
  // rule). The two processes are an instance each; the two calls of the
  // loop are ordered (a common array) and share one: 3 instances.
  // Unconfirmed against Vitis (no kernel mixes the two kinds yet).
  // MIXED-DAG: in @mixed_df (x1): 4 call site(s) -> 3 instance(s) ({{.*}}2 of them dataflow processes, an instance each
  // MIXED-DAG: 512x32b -> RAM_1P (x36/port) = 1 BRAM_18K x 3 instance(s) of @stage = 3
  func.func @mixed_df(%a: memref<512xi32>, %e: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %b = memref.alloca() : memref<512xi32>
    %c = memref.alloca() : memref<512xi32>
    func.call @stage(%a, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    affine.for %i = 0 to 4 {
      func.call @stage(%b, %c) : (memref<512xi32>, memref<512xi32>) -> ()
      func.call @stage(%c, %b) : (memref<512xi32>, memref<512xi32>) -> ()
    }
    func.call @stage(%b, %e) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  // A completely unrolled loop of the region holds processes: unrolled
  // before the instances are counted, its 4 copies are 4 processes (kernel
  // w9r6rev n48a, four `stage` calls in a `#pragma HLS unroll` loop of a
  // dataflow region: Vitis stage, stage_1..3, 4 BRAM; cgeist keeps such
  // calls, HLSAutoInline).
  // UNR: in @unrolled_df (x1): 4 call site(s) -> 4 instance(s) (dataflow region: every call site is a process of its own)
  // UNR: Total BRAM: 4
  func.func @unrolled_df(%a: memref<512xi32>, %e: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    affine.for %i = 0 to 4 {
      func.call @stage(%a, %e) : (memref<512xi32>, memref<512xi32>) -> ()
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    return
  }
}
