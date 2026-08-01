// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis=top=top --bram-debug --bram-debug-json=%t.json -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis=top=top -o /dev/null > %t.plain.out
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis=top=top --bram-debug --bram-debug-json=%t.dbg.json -o /dev/null > %t.debug.out 2> /dev/null
// RUN: diff %t.plain.out %t.debug.out

// An array passed to a non-inlined callee is charged to its owner, the
// function that allocates it, from every access, the callee's included
// (VITIS_NOTES.md N14 R6, kernels inl_e1 .. inl_e4):
//
//   @buf3  read three times per cycle in @rd3's own pipelined loop: the
//          caller's array is replicated like a local one (inl_e1_arg_rd3_off
//          = inlined: RAM_1WNR, 2 copies, 1024x32 -> 4 BRAM).
//   @buf2  read by two calls of @get2 (two reads each) from inside the
//          caller's pipelined loop: the reads go through the one instance's
//          port in the callee's own sequential scope, no replication; the
//          calls share the instance (common array) and are serialized, so
//          the caller loop's II rises (inl_e3: II 4, buf RAM 2 BRAM).
//   The debug record names the call and the function of every such access.

// CHECK:      memref.alloca
// CHECK-NEXT:   kind=RAM_1WNR  bram=4
// CHECK:      memref.alloca
// CHECK-NEXT:   kind=RAM_2P  bram=2
// CHECK:      Total BRAM: 6

// DBG:      buf3 (alloca)
// DBG:        accesses (4):
// DBG:          - memref.store write in pipeline @ {{.*}} ii=1
// DBG-NEXT:     - memref.load read  in pipeline @ {{.*}} ii=1 stage={{[0-9]+}} (in @rd3 via call @rd3 @ {{.*}})
// DBG-NEXT:     - memref.load read  in pipeline @ {{.*}} ii=1 stage={{[0-9]+}} (in @rd3 via call @rd3 @ {{.*}})
// DBG-NEXT:     - memref.load read  in pipeline @ {{.*}} ii=1 stage={{[0-9]+}} (in @rd3 via call @rd3 @ {{.*}})
// DBG:        replication: replicable (max 1 store(s) per loop body), copies 2 set by pipeline @
// DBG:        ram type: RAM_1WNR
// DBG:      buf2 (alloca)
// DBG:        accesses (3):
// DBG-NEXT:     - memref.load read  in func @ {{.*}} (in @get2 via call @get2 @ {{.*}})
// DBG-NEXT:     - memref.load read  in func @ {{.*}} (in @get2 via call @get2 @ {{.*}})
// DBG:        replication: replicable (max 1 store(s) per loop body), copies 1
// DBG:        ram type: RAM_2P
// DBG:      --- instances
// DBG:        @get2: 1 instance(s) (inline off)
// DBG-NEXT:     in @top (x1): 2 call site(s) -> 1 instance(s) (ordered pairs: 1 by a common array, 0 by a value dependence)
// DBG:        @rd3: 1 instance(s) (inline off)
// DBG:      --- pipelines
// DBG-DAG:    pipeline @ {{.*}} in @rd3: ii=1
// DBG-DAG:    pipeline @ {{.*}} in @top: ii=2

// JSON:      "in_func": "rd3",
// JSON:      "via_call": "call @rd3 @ {{.*}}"
// JSON:      "in_func": "get2",
// JSON:      "via_call": "call @get2 @ {{.*}}"

module {
  func.func private @rd3(%a: memref<1024xi32>, %o: memref<1024xi32>) attributes {hls.inline_off} {
    %c7 = arith.constant 7 : index
    %c1023 = arith.constant 1023 : index
    affine.for %i = 0 to 1024 {
      %x = affine.load %a[%i] : memref<1024xi32>
      %y = affine.load %a[1023 - %i] : memref<1024xi32>
      %m = arith.muli %i, %c7 : index
      %j = arith.andi %m, %c1023 : index
      %z = memref.load %a[%j] : memref<1024xi32>
      %s = arith.addi %x, %y : i32
      %t = arith.addi %s, %z : i32
      affine.store %t, %o[%i] : memref<1024xi32>
    }
    return
  }
  func.func private @get2(%a: memref<1024xi32>, %i: index) -> i32 attributes {hls.inline_off} {
    %x = affine.load %a[symbol(%i)] : memref<1024xi32>
    %y = affine.load %a[1023 - symbol(%i)] : memref<1024xi32>
    %s = arith.addi %x, %y : i32
    return %s : i32
  }
  func.func @top(%in: memref<1024xi32>, %out3: memref<1024xi32>, %out2: memref<1024xi32>) {
    %c3 = arith.constant 3 : i32
    %c7 = arith.constant 7 : index
    %c1023 = arith.constant 1023 : index
    %buf3 = memref.alloca() {polygeist.varname = "buf3"} : memref<1024xi32>
    %buf2 = memref.alloca() {polygeist.varname = "buf2"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      %w = arith.muli %v, %c3 : i32
      affine.store %w, %buf3[%i] : memref<1024xi32>
      affine.store %v, %buf2[%i] : memref<1024xi32>
    }
    func.call @rd3(%buf3, %out3) : (memref<1024xi32>, memref<1024xi32>) -> ()
    affine.for %i = 0 to 1024 {
      %x = func.call @get2(%buf2, %i) : (memref<1024xi32>, index) -> i32
      %m = arith.muli %i, %c7 : index
      %j = arith.andi %m, %c1023 : index
      %y = func.call @get2(%buf2, %j) : (memref<1024xi32>, index) -> i32
      %s = arith.addi %x, %y : i32
      affine.store %s, %out2[%i] : memref<1024xi32>
    }
    return
  }
}
