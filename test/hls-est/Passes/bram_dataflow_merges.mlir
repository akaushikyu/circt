// RUN: hls-est %s --symbol-privatize=exclude=top_ll2 --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_ll2 --bram-debug-json=%t.json -o /dev/null | FileCheck %s --check-prefix=LL2
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --symbol-privatize=exclude=top_rwr --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_rwr -o /dev/null | FileCheck %s --check-prefix=RWR
// RUN: hls-est %s --symbol-privatize=exclude=top_cyc --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_cyc --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=CYC
// RUN: hls-est %s --symbol-privatize=exclude=top_half --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_half --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=HALF
// RUN: hls-est %s --symbol-privatize=exclude=top_trans --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_trans -o /dev/null | FileCheck %s --check-prefix=TRANS
// RUN: hls-est %s --symbol-privatize=exclude=top_inner --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_inner --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=INNER
// RUN: hls-est %s --symbol-privatize=exclude=top_strm --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_strm --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=STRM

// Dataflow process merges (VITIS_NOTES.md N36). Vitis merges every process of
// a dataflow region that writes one local array (or stream) into one process,
// together with every process on a dependence path from one of them to
// another, until nothing changes. The array stays a ping-pong channel (N33,
// the merged group counting as one process) when a process outside the group
// reads it; arrays wholly inside the group are ordinary memories. Every case
// mirrors a Vitis 2025.1 td=off kernel (512 x int, pipelined II 1 loops, the
// reader reads in reverse); the Vitis BRAM is in each comment.

module {
  // w9m_ll2: two loops write buf, a third reads it. One process {A, B}:
  // buf is a single PIPO of 2 x 512 words, F(1024x32) at x18 = 2 (Vitis 2).
  // LL2: kind=PIPO  bram=2
  // LL2: Total BRAM: 2
  // JSON: "merge_group": "loopschedule.pipeline @
  // JSON-NEXT: "merge_reason": "writes on 'buf'",
  func.func @top_ll2(%in: memref<512xi32>, %in2: memref<512xi32>, %out: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 256 {
      %v = affine.load %in2[%i] : memref<512xi32>
      affine.store %v, %buf[2 * %i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  // w9m_rwr: A writes buf, B reads it, C writes it again, D reads it. B lies
  // on the path A -> B -> C: one process {A, B, C}; buf is a single PIPO
  // read by D = 2 (Vitis 2).
  // RWR: kind=PIPO  bram=2
  // RWR: Total BRAM: 2
  func.func @top_rwr(%in: memref<512xi32>, %in2: memref<512xi32>, %out: memref<512xi32>, %out2: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %in2[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out2[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  // w9m_cyc: A writes buf and t, X reads t and writes u, B reads u and writes
  // buf, C reads buf. X lies on the path A -> X -> B through t and u: one
  // process {A, X, B}; t and u are ordinary memories of it, 512x32 = 1 each
  // at x36 (one port per sub-loop), buf a single PIPO = 2 (Vitis 4).
  // CYC: t (alloca)
  // CYC: not a ping-pong channel: every process that accesses it is merged into one process
  // CYC: u (alloca)
  // CYC: not a ping-pong channel: every process that accesses it is merged into one process ({{.*}}: on a dependence path from one process of the merged group to another)
  // CYC: kind=RAM_1P  bram=1
  // CYC: kind=RAM_1P  bram=1
  // CYC: kind=PIPO  bram=2
  // CYC: Total BRAM: 4
  func.func @top_cyc(%in: memref<512xi32>, %in2: memref<512xi32>, %out: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %t = memref.alloca() {polygeist.varname = "t"} : memref<512xi32>
    %u = memref.alloca() {polygeist.varname = "u"} : memref<512xi32>
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
      %w = affine.load %in2[%i] : memref<512xi32>
      affine.store %w, %t[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %t[511 - %i] : memref<512xi32>
      affine.store %v, %u[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 256 {
      %v = affine.load %u[511 - %i] : memref<512xi32>
      affine.store %v, %buf[2 * %i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  // w9v_m_half: X reads t from writer A but has no path to writer B, so it is
  // not merged (the closure follows dependences, not program order): t is a
  // single PIPO from {A, B} to X = 2, buf a single PIPO = 2 (Vitis 4).
  // HALF: dataflow ping-pong channel of function @top_half
  // HALF: merged into the process of
  // HALF-NEXT: process {{[0-9]+}} (reads): loopschedule.pipeline
  // HALF-NEXT: blocks: 2
  // HALF: kind=PIPO  bram=2
  // HALF: kind=PIPO  bram=2
  // HALF: Total BRAM: 4
  func.func @top_half(%in: memref<512xi32>, %in2: memref<512xi32>, %out: memref<512xi32>, %out2: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %t = memref.alloca() {polygeist.varname = "t"} : memref<512xi32>
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
      affine.store %v, %t[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %t[511 - %i] : memref<512xi32>
      affine.store %v, %out2[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 256 {
      %v = affine.load %in2[%i] : memref<512xi32>
      affine.store %v, %buf[2 * %i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  // w9m_trans: A writes p and q, B writes p, C writes q: merges chain across
  // arrays into one process {A, B, C}; p and q are single PIPOs read by D,
  // 2 + 2 (Vitis 4).
  // TRANS: kind=PIPO  bram=2
  // TRANS: kind=PIPO  bram=2
  // TRANS: Total BRAM: 4
  func.func @top_trans(%in: memref<512xi32>, %in2: memref<512xi32>, %out: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %p = memref.alloca() {polygeist.varname = "p"} : memref<512xi32>
    %q = memref.alloca() {polygeist.varname = "q"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %p[%i] : memref<512xi32>
      %w = affine.load %in2[%i] : memref<512xi32>
      affine.store %w, %q[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 256 {
      %v = affine.load %in2[%i] : memref<512xi32>
      affine.store %v, %p[2 * %i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 256 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %q[2 * %i + 1] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %p[511 - %i] : memref<512xi32>
      %w = affine.load %q[511 - %i] : memref<512xi32>
      %s = arith.addi %v, %w : i32
      affine.store %s, %out[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  // w9m_inner: A writes buf and t, B reads t and writes buf, C reads buf: t
  // lies wholly inside the merged process {A, B}, an ordinary memory
  // 512x32 = 1; buf a single PIPO = 2 (Vitis 3).
  // INNER: t (alloca)
  // INNER: every process that accesses it is merged into one process ({{.*}}writes on 'buf'): an ordinary memory
  // INNER: kind=RAM_1P  bram=1
  // INNER: kind=PIPO  bram=2
  // INNER: Total BRAM: 3
  func.func @top_inner(%in: memref<512xi32>, %in2: memref<512xi32>, %out: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %t = memref.alloca() {polygeist.varname = "t"} : memref<512xi32>
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
      %w = affine.load %in2[%i] : memref<512xi32>
      affine.store %w, %t[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 256 {
      %v = affine.load %t[511 - %i] : memref<512xi32>
      affine.store %v, %buf[2 * %i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  // w9m_strm: A writes buf and stream s, X moves s to s2, B reads s2 and
  // writes buf, C reads buf. X lies on the path A -> X -> B through the
  // streams: one process {A, X, B}; the streams stay FIFOs of depth 1024
  // (2 each), buf a single PIPO = 2 (Vitis 6).
  // STRM: merged into the process of {{.*}}(writes on 'buf')
  // STRM: merged into the process of {{.*}}(writes on 'buf')
  // STRM: kind=PIPO  bram=2
  // STRM: Total BRAM: 6
  func.func private @_ZN3hls6streamIiLi0EEC1Ev(memref<?xi32>)
  func.func private @_ZN3hls6streamIiLi0EE5writeERKi(memref<?xi32>, memref<?xi32>)
  func.func private @_ZN3hls6streamIiLi0EE4readEv(memref<?xi32>) -> i32
  func.func @top_strm(%in: memref<512xi32>, %in2: memref<512xi32>, %out: memref<512xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    %tmp = memref.alloca() : memref<1xi32>
    %ctmp = memref.cast %tmp : memref<1xi32> to memref<?xi32>
    %tmp2 = memref.alloca() : memref<1xi32>
    %ctmp2 = memref.cast %tmp2 : memref<1xi32> to memref<?xi32>
    %s = memref.alloca() {hls.stream = [{depth = 1024 : i32, type = "fifo", variable = "s"}], polygeist.varname = "s"} : memref<1xi32>
    %cs = memref.cast %s : memref<1xi32> to memref<?xi32>
    %s2 = memref.alloca() {hls.stream = [{depth = 1024 : i32, type = "fifo", variable = "s2"}], polygeist.varname = "s2"} : memref<1xi32>
    %cs2 = memref.cast %s2 : memref<1xi32> to memref<?xi32>
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    call @_ZN3hls6streamIiLi0EEC1Ev(%cs) : (memref<?xi32>) -> ()
    call @_ZN3hls6streamIiLi0EEC1Ev(%cs2) : (memref<?xi32>) -> ()
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %buf[%i] : memref<512xi32>
      %w = affine.load %in2[%i] : memref<512xi32>
      affine.store %w, %tmp[0] : memref<1xi32>
      func.call @_ZN3hls6streamIiLi0EE5writeERKi(%cs, %ctmp) : (memref<?xi32>, memref<?xi32>) -> ()
    }
    affine.for %i = 0 to 512 {
      %v = func.call @_ZN3hls6streamIiLi0EE4readEv(%cs) : (memref<?xi32>) -> i32
      affine.store %v, %tmp2[0] : memref<1xi32>
      func.call @_ZN3hls6streamIiLi0EE5writeERKi(%cs2, %ctmp2) : (memref<?xi32>, memref<?xi32>) -> ()
    }
    affine.for %i = 0 to 256 {
      %v = func.call @_ZN3hls6streamIiLi0EE4readEv(%cs2) : (memref<?xi32>) -> i32
      affine.store %v, %buf[2 * %i] : memref<512xi32>
    }
    affine.for %i = 0 to 512 {
      %v = affine.load %buf[511 - %i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
}
