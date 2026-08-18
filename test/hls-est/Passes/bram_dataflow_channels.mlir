// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top --bram-debug --bram-debug-json=%t.json -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top --bram-dataflow-channels=false -o /dev/null | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --symbol-privatize=exclude=top_seq --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_seq -o /dev/null | FileCheck %s --check-prefix=SEQ
// RUN: hls-est %s --symbol-privatize=exclude=top_df --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_df -o /dev/null | FileCheck %s --check-prefix=DF
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_loop -o /dev/null | FileCheck %s --check-prefix=LOOP
// RUN: hls-est %s --symbol-privatize=exclude=top_merge --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_merge --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=MERGE

// Dataflow ping-pong channels (--bram-dataflow-channels, on by default;
// VITIS_NOTES.md N33). In a dataflow region (hls.dataflow on a function or a
// loop) a local array that one process (a call or a loop of the region) writes
// and a later one reads is a channel of N blocks:
//   N:     the stream type=pipo depth, else 2, else 1 for a non-top region
//          function none of whose direct callers is a dataflow region;
//   mode:  separate memories when some process accesses the bank twice in one
//          cycle (most accesses on one control path: exclusive if arms share
//          a port) or it is bound to ram_2p / ram_s2p, else one memory;
//   price: single F(N x D, W) at x18 (0 below 1024 bits of N x D x W);
//          separate N x F(D, W) at x18, x36 when bound ram_2p / ram_s2p with
//          one port per process (0 below 1024 bits of D x W); N = 1 an
//          ordinary memory; impl=lutram 0; never replicated.

module {
  // Producer: writes buf[i], pipelined.
  func.func private @prod(%buf: memref<1024xi32>, %seed: i32) attributes {hls.inline_off} {
    affine.for %i = 0 to 1024 {
      affine.store %seed, %buf[%i] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  // One read per iteration.
  func.func private @cons1(%buf: memref<1024xi32>, %out: memref<1024xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 1024 {
      %v = affine.load %buf[%i] : memref<1024xi32>
      affine.store %v, %out[%i] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func private @prod256(%buf: memref<256xi32>, %seed: i32) attributes {hls.inline_off} {
    affine.for %i = 0 to 256 {
      affine.store %seed, %buf[%i] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  // Two reads in one iteration of a pipelined loop: a second port.
  func.func private @cons2(%buf: memref<256xi32>, %out: memref<256xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 128 {
      %a = affine.load %buf[2 * %i] : memref<256xi32>
      %b = affine.load %buf[2 * %i + 1] : memref<256xi32>
      %s = arith.addi %a, %b : i32
      affine.store %s, %out[%i] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  // Two reads on mutually exclusive arms: one port.
  func.func private @consx(%buf: memref<256xi32>, %out: memref<256xi32>, %c: i1) attributes {hls.inline_off} {
    affine.for %i = 0 to 256 {
      %v = scf.if %c -> i32 {
        %a = affine.load %buf[%i] : memref<256xi32>
        scf.yield %a : i32
      } else {
        %b = affine.load %buf[255 - %i] : memref<256xi32>
        scf.yield %b : i32
      }
      affine.store %v, %out[%i] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  // One read per iteration.
  func.func private @cons256(%buf: memref<256xi32>, %out: memref<256xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 256 {
      %v = affine.load %buf[%i] : memref<256xi32>
      affine.store %v, %out[%i] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  // Reads and writes the channel: Vitis merges it with the producer.
  func.func private @consrw(%buf: memref<256xi32>, %out: memref<256xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 256 {
      %a = affine.load %buf[%i] : memref<256xi32>
      affine.store %a, %out[%i] : memref<256xi32>
      affine.store %a, %buf[%i] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func private @prodz(%buf: memref<1024xi32>) attributes {hls.inline_off} {
    %z = arith.constant 0 : i32
    affine.for %i = 0 to 1024 {
      affine.store %z, %buf[%i] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func private @prod8(%buf: memref<8xi32>, %seed: i32) attributes {hls.inline_off} {
    affine.for %i = 0 to 8 {
      affine.store %seed, %buf[%i] : memref<8xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func private @cons8(%buf: memref<8xi32>, %out: memref<256xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 8 {
      %a = affine.load %buf[%i] : memref<8xi32>
      affine.store %a, %out[%i] : memref<256xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func private @prod640(%buf: memref<640xi32>, %seed: i32) attributes {hls.inline_off} {
    affine.for %i = 0 to 640 {
      affine.store %seed, %buf[%i] : memref<640xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func private @cons640(%buf: memref<640xi32>, %out: memref<1024xi32>) attributes {hls.inline_off} {
    affine.for %i = 0 to 640 {
      %a = affine.load %buf[%i] : memref<640xi32>
      affine.store %a, %out[%i] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  // CHECK-LABEL: memref.alloca
  func.func @top(%seed: i32, %c: i1, %o1: memref<1024xi32>, %o2: memref<256xi32>, %o3: memref<1024xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    // One read per process: one memory of 2 x 1024 words, F(2048x32) at x18
    // = ceil(32/9) = 4.
    // CHECK: kind=PIPO  bram=4
    // CHECK-NEXT: single (every process uses one port of the bank): single memory of all 2 blocks: F(2048x32) at x18
    %a = memref.alloca() {polygeist.varname = "a"} : memref<1024xi32>
    // Two reads per iteration: separate, 2 x F(256x32) at x18 = 2 x 2.
    // CHECK: kind=PIPO  bram=4
    // CHECK-NEXT: separate (a process drives a second port: pipelined scope (II {{[0-9]+}}), one control path of one iteration
    %b = memref.alloca() {polygeist.varname = "b"} : memref<256xi32>
    // Exclusive reads: single, F(512x32) at x18 = 2.
    // CHECK: kind=PIPO  bram=2
    // CHECK-NEXT: single (every process uses one port of the bank)
    %x = memref.alloca() {polygeist.varname = "x"} : memref<256xi32>
    // The consumer writes it too: not a channel, an ordinary memory.
    // CHECK: kind=RAM_2P  bram=2
    %rw = memref.alloca() {polygeist.varname = "rw"} : memref<256xi32>
    // 2 x 8 x 32 = 512 bits < 1024: distributed RAM.
    // CHECK: kind=PIPO  bram=0
    // CHECK-NEXT: single memory of 16x32 < 1024 bits
    %s8 = memref.alloca() {polygeist.varname = "s8"} : memref<8xi32>
    // stream type=pipo depth=3: F(1920x32) = 4 (not F(2560x32) = 8).
    // CHECK: kind=PIPO  bram=4
    // CHECK-NEXT: blocks 3: stream type=pipo depth pragma; single
    %d3 = memref.alloca() {polygeist.varname = "d3", hls.stream = [{depth = 3 : i32, type = "pipo", variable = "d3"}]} : memref<640xi32>
    // ram_2p with one port per process: separate, x36: 2 x 1.
    // CHECK: kind=PIPO  bram=2
    // CHECK-NEXT: separate (bind_storage type=ram_2p (separate memories even with one port per process)): separate: 2 x F(256x32) at x36 allowed
    %b2p = memref.alloca() {polygeist.varname = "b2p", hls.bind_storage = [{impl = "bram", type = "ram_2p", variable = "b2p"}]} : memref<256xi32>
    // ram_s2p and two reads per iteration: one read port, the II rises;
    // separate x36 = 2.
    // CHECK: kind=PIPO  bram=2
    // CHECK-NEXT: has one port per side, so the second access waits
    %bs2p = memref.alloca() {polygeist.varname = "bs2p", hls.bind_storage = [{impl = "bram", type = "ram_s2p", variable = "bs2p"}]} : memref<256xi32>
    // impl=lutram: distributed RAM.
    // CHECK: kind=PIPO  bram=0
    %lut = memref.alloca() {polygeist.varname = "lut", hls.bind_storage = [{impl = "lutram", type = "ram_2p", variable = "lut"}]} : memref<1024xi32>
    // Two banks of one partitioned array: the consumer reads bank 0 twice per
    // iteration and bank 1 once; both banks come from one RAM module, so
    // both are separate: 2 x (2 x F(256x32)) = 8.
    // CHECK: kind=PIPO  bram=4
    // CHECK-NEXT: separate (a process drives a second port: pipelined scope
    // CHECK: kind=PIPO  bram=4
    // CHECK-NEXT: separate (a process drives a second port: another bank of the array (bank 0) shares its RAM module: pipelined scope
    %pb0 = memref.alloca() {polygeist.varname = "pb", hls.bank_of = "pb", hls.bank_count = 2 : i32, hls.bank_index = 0 : i32} : memref<256xi32>
    %pb1 = memref.alloca() {polygeist.varname = "pb", hls.bank_of = "pb", hls.bank_count = 2 : i32, hls.bank_index = 1 : i32} : memref<256xi32>
    // Filled with a constant (hls.const_fill): a ROM of that constant, here
    // all zero, so no memory; never a channel.
    // CHECK: kind=ROM_1P  bram=0
    // CHECK-NEXT: ROM whose values are all 0
    %zero = memref.alloca() {polygeist.varname = "zero", hls.const_fill = 0 : i32} : memref<1024xi32>
    // Two consumers, one read each: merged into one reader, single = 4.
    // CHECK: kind=PIPO  bram=4
    %two = memref.alloca() {polygeist.varname = "two"} : memref<1024xi32>
    func.call @prod(%a, %seed) : (memref<1024xi32>, i32) -> ()
    func.call @prod256(%b, %seed) : (memref<256xi32>, i32) -> ()
    func.call @prod256(%x, %seed) : (memref<256xi32>, i32) -> ()
    func.call @prod256(%rw, %seed) : (memref<256xi32>, i32) -> ()
    func.call @prod8(%s8, %seed) : (memref<8xi32>, i32) -> ()
    func.call @prod640(%d3, %seed) : (memref<640xi32>, i32) -> ()
    func.call @prod256(%b2p, %seed) : (memref<256xi32>, i32) -> ()
    func.call @prod256(%bs2p, %seed) : (memref<256xi32>, i32) -> ()
    func.call @prod(%lut, %seed) : (memref<1024xi32>, i32) -> ()
    func.call @prod(%two, %seed) : (memref<1024xi32>, i32) -> ()
    func.call @prod256(%pb0, %seed) : (memref<256xi32>, i32) -> ()
    func.call @prod256(%pb1, %seed) : (memref<256xi32>, i32) -> ()
    func.call @prodz(%zero) : (memref<1024xi32>) -> ()
    func.call @cons1(%a, %o1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @cons2(%b, %o2) : (memref<256xi32>, memref<256xi32>) -> ()
    func.call @consx(%x, %o2, %c) : (memref<256xi32>, memref<256xi32>, i1) -> ()
    func.call @consrw(%rw, %o2) : (memref<256xi32>, memref<256xi32>) -> ()
    func.call @cons8(%s8, %o2) : (memref<8xi32>, memref<256xi32>) -> ()
    func.call @cons640(%d3, %o3) : (memref<640xi32>, memref<1024xi32>) -> ()
    func.call @cons256(%b2p, %o2) : (memref<256xi32>, memref<256xi32>) -> ()
    func.call @cons2(%bs2p, %o2) : (memref<256xi32>, memref<256xi32>) -> ()
    func.call @cons1(%lut, %o1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @cons1(%two, %o1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @cons1(%two, %o3) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @cons1(%zero, %o3) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @cons2(%pb0, %o2) : (memref<256xi32>, memref<256xi32>) -> ()
    func.call @cons256(%pb1, %o2) : (memref<256xi32>, memref<256xi32>) -> ()
    return
  }
  // CHECK: Total BRAM: 32

  // OFF: kind=RAM_1P  bram=2
  // OFF: kind=RAM_2P  bram=2
  // OFF: Total BRAM: 20

  // DBG: dataflow ping-pong channel of function @top
  // DBG-NEXT: process {{[0-9]+}} (writes): call @prod @
  // DBG-NEXT: process {{[0-9]+}} (reads): call @cons1 @
  // DBG-NEXT: blocks: 2: the region of the top function
  // DBG-NEXT: mode: single (every process uses one port of the bank)
  // DBG-NEXT: pipo price: single memory of all 2 blocks: F(2048x32) at x18 (true dual port, one port per side) = 4
  // DBG: dataflow region array, not a ping-pong channel: 2 processes write it

  // JSON: "pipo": {
  // JSON-NEXT: "blocks": 2,
  // JSON-NEXT: "blocks_source": "2: the region of the top function",
  // JSON-NEXT: "channel": true,
  // JSON-NEXT: "mode": "single",
  // JSON: "ram_type": "PIPO",
  // JSON: "status": "pipo",
  // JSON: "not_channel_reason": "2 processes write it

  // A dataflow function called once from a sequential top: one block, an
  // ordinary memory (x36 with one port per process: 256x32 = 1).
  func.func private @head(%seed: i32, %o: memref<256xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}], hls.inline_off} {
    %h = memref.alloca() {polygeist.varname = "h"} : memref<256xi32>
    %c = arith.constant true
    func.call @prod256(%h, %seed) : (memref<256xi32>, i32) -> ()
    func.call @consx(%h, %o, %c) : (memref<256xi32>, memref<256xi32>, i1) -> ()
    return
  }
  // SEQ: kind=PIPO  bram=1
  // SEQ-NEXT: blocks 1: the region function is not the top and none of its direct callers is a dataflow region
  // SEQ: Total BRAM: 1
  func.func @top_seq(%seed: i32, %o: memref<256xi32>) {
    func.call @head(%seed, %o) : (i32, memref<256xi32>) -> ()
    return
  }
  // The same function called from a dataflow region: two blocks, single
  // F(512x32) = 2.
  // DF: kind=PIPO  bram=2
  // DF-NEXT: blocks 2: the region function is called from the dataflow region @top_df
  // DF: Total BRAM: 2
  func.func @top_df(%seed: i32, %o: memref<256xi32>) attributes {hls.dataflow = [{disable_start_propagation = false}]} {
    func.call @head(%seed, %o) : (i32, memref<256xi32>) -> ()
    return
  }

  // A dataflow loop body: the two inner loops are its processes; two blocks.
  // LOOP: kind=PIPO  bram=4
  // LOOP-NEXT: dataflow ping-pong channel of loop affine.for
  // LOOP-SAME: blocks 2: dataflow-in-loop body
  // LOOP: Total BRAM: 4
  func.func @top_loop(%seed: i32, %o: memref<1024xi32>) {
    %t = memref.alloca() {polygeist.varname = "t"} : memref<1024xi32>
    affine.for %k = 0 to 4 {
      affine.for %i = 0 to 1024 {
        affine.store %seed, %t[%i] : memref<1024xi32>
      } {hls.pipeline = [{II = 1 : i32}]}
      affine.for %i = 0 to 1024 {
        %v = affine.load %t[%i] : memref<1024xi32>
        affine.store %v, %o[%i] : memref<1024xi32>
      } {hls.pipeline = [{II = 1 : i32}]}
    } {hls.dataflow = [{disable_start_propagation = false}]}
    return
  }

  // Two processes of the dataflow loop of a non-top function read the same
  // parameter: Vitis merges them into one process, so the array between them
  // is an ordinary memory of that process (1024x32 = 2), not a channel.
  // MERGE: dataflow region array, not a ping-pong channel: its producer and a consumer are merged into one process (both access parameter 0 of @conv
  // MERGE: Total BRAM: 2
  func.func private @conv(%p: memref<1024xi32>, %o: memref<1024xi32>) attributes {hls.inline_off} {
    %t = memref.alloca() {polygeist.varname = "t"} : memref<1024xi32>
    affine.for %k = 0 to 4 {
      affine.for %i = 0 to 1024 {
        %v = affine.load %p[%i] : memref<1024xi32>
        affine.store %v, %t[%i] : memref<1024xi32>
      } {hls.pipeline = [{II = 1 : i32}]}
      affine.for %i = 0 to 1024 {
        %v = affine.load %t[%i] : memref<1024xi32>
        %w = affine.load %p[%i] : memref<1024xi32>
        %s = arith.addi %v, %w : i32
        affine.store %s, %o[%i] : memref<1024xi32>
      } {hls.pipeline = [{II = 1 : i32}]}
    } {hls.dataflow = [{disable_start_propagation = false}]}
    return
  }
  func.func @top_merge(%p: memref<1024xi32>, %o: memref<1024xi32>) {
    func.call @conv(%p, %o) : (memref<1024xi32>, memref<1024xi32>) -> ()
    return
  }
}
