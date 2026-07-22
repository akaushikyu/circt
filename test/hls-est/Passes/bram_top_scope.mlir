// RUN: hls-est %s --bram-analysis=top=topA --bram-attribute-globals --bram-debug --bram-debug-json=%t.a.json -o /dev/null > %t.a.out 2> %t.a.err
// RUN: FileCheck %s --input-file=%t.a.out --check-prefix=TOPA
// RUN: FileCheck %s --input-file=%t.a.err --check-prefix=TOPADBG
// RUN: FileCheck %s --input-file=%t.a.json --check-prefix=TOPAJSON
// RUN: hls-est %s --symbol-privatize=exclude=topA --symbol-dce --bram-analysis --bram-attribute-globals -o /dev/null 2>&1 | FileCheck %s --check-prefix=TOPA --implicit-check-not=warning:
// RUN: hls-est %s --bram-analysis=top=topB --bram-attribute-globals -o /dev/null 2>&1 | FileCheck %s --check-prefix=TOPB
// RUN: hls-est %s --symbol-privatize=exclude=topB --symbol-dce --bram-analysis --bram-attribute-globals -o /dev/null 2>&1 | FileCheck %s --check-prefix=TOPB --implicit-check-not=warning:

// What top= reaches, beyond bram_top.mlir (W1a review D1, D4, D5): top=<f>
// must cost exactly what --symbol-privatize=exclude=<f> --symbol-dce leaves.
//
//   @tbl:    a constant 512xi64 table. @topA reads it twice per cycle, @topB
//            four times per cycle; @topA never calls @topB.
//   @topA:   also reaches @viaptr, only through func.constant +
//            func.call_indirect (an indirect call); @viaptr holds a 64xi32
//            alloca (1 BRAM).
//
// D1: the table's ports, copies and ROM test count only the get_global sites
// of the reachable functions: top=topA -> ROM_2P (two read-only ports, SDP,
// 512x64 = 2), not the ROM_NP of @topB's four reads (2 copies x 4 = 8).
// D5: @viaptr is reachable (func.constant references it), so its alloca is
// costed, as --symbol-dce keeps it. top=topA = 2 + 1 = 3.
// D4: the debug pipelines are those of the reachable functions only.

// TOPA:      memref.global
// TOPA-NEXT:   kind=ROM_2P  bram=2
// TOPA:      memref.alloca
// TOPA-NEXT:   kind=RAM_1P  bram=1
// TOPA-NOT:  kind=
// TOPA:      Total BRAM: 3

// TOPADBG: top: @topA (2 function(s) reachable through calls; 0 memref(s) outside them not costed)
// TOPADBG: ram type: ROM_2P -- {{.*}}peak 2 read(s) per cycle
// TOPADBG: --- pipelines
// TOPADBG-NEXT: pipeline @ {{.*}} in @topA: ii=1
// TOPADBG-NOT: in @topB
// TOPADBG: --- summary

// TOPAJSON-NOT:  "func": "topB"
// TOPAJSON:      "pipelines": [
// TOPAJSON-NEXT:   {
// TOPAJSON:          "func": "topA",
// TOPAJSON-NOT:  "func": "topB"
// TOPAJSON:      "top": {
// TOPAJSON-NEXT:   "functions": [
// TOPAJSON-NEXT:     "topA",
// TOPAJSON-NEXT:     "viaptr"
// TOPAJSON-NEXT:   ],

// TOPB:      memref.global
// TOPB-NEXT:   kind=ROM_NP  bram=8
// TOPB-NOT:  kind=
// TOPB:      Total BRAM: 8

module {
  memref.global "private" constant @tbl : memref<512xi64> = dense<3>
  func.func private @viaptr() {
    %buf = memref.alloca() {hls.preserve, polygeist.varname = "via_buf"} : memref<64xi32>
    return
  }
  func.func @topA(%out: memref<512xi64>) {
    %f = func.constant @viaptr : () -> ()
    func.call_indirect %f() : () -> ()
    %t = memref.get_global @tbl : memref<512xi64>
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c512 = arith.constant 512 : index
    loopschedule.pipeline II = 1 trip_count = 512 iter_args(%i = %c0) : (index) -> () {
      %cond = arith.cmpi ult, %i, %c512 : index
      loopschedule.register %cond : i1
    } do {
      %s:2 = loopschedule.pipeline.stage start = 0 {
        %a0 = memref.load %t[%i] : memref<512xi64>
        %k1 = arith.constant 1 : index
        %x1 = arith.xori %i, %k1 : index
        %a1 = memref.load %t[%x1] : memref<512xi64>
        %sum = arith.addi %a0, %a1 : i64
        %next = arith.addi %i, %c1 : index
        loopschedule.register %sum, %next : i64, index
      } : i64, index
      loopschedule.pipeline.stage start = 1 {
        memref.store %s#0, %out[%i] : memref<512xi64>
        loopschedule.register
      }
      loopschedule.terminator iter_args(%s#1), results() : (index) -> ()
    }
    return
  }
  func.func @topB(%out: memref<512xi64>) {
    %t = memref.get_global @tbl : memref<512xi64>
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c512 = arith.constant 512 : index
    loopschedule.pipeline II = 1 trip_count = 512 iter_args(%i = %c0) : (index) -> () {
      %cond = arith.cmpi ult, %i, %c512 : index
      loopschedule.register %cond : i1
    } do {
      %s:2 = loopschedule.pipeline.stage start = 0 {
        %a0 = memref.load %t[%i] : memref<512xi64>
        %k1 = arith.constant 1 : index
        %x1 = arith.xori %i, %k1 : index
        %a1 = memref.load %t[%x1] : memref<512xi64>
        %k2 = arith.constant 2 : index
        %x2 = arith.xori %i, %k2 : index
        %a2 = memref.load %t[%x2] : memref<512xi64>
        %k3 = arith.constant 3 : index
        %x3 = arith.xori %i, %k3 : index
        %a3 = memref.load %t[%x3] : memref<512xi64>
        %s01 = arith.addi %a0, %a1 : i64
        %s23 = arith.addi %a2, %a3 : i64
        %sum = arith.addi %s01, %s23 : i64
        %next = arith.addi %i, %c1 : index
        loopschedule.register %sum, %next : i64, index
      } : i64, index
      loopschedule.pipeline.stage start = 1 {
        memref.store %s#0, %out[%i] : memref<512xi64>
        loopschedule.register
      }
      loopschedule.terminator iter_args(%s#1), results() : (index) -> ()
    }
    return
  }
}
