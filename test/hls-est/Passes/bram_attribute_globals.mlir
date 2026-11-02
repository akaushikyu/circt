// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis --bram-attribute-globals=false -o /dev/null | FileCheck %s --check-prefix=DEFAULT
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=ATTR
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis --bram-attribute-globals --bram-debug -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=ATTR
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG

// --bram-attribute-globals (on by default since W9r10-impl, tool.hls.globals.attribute_accesses,
// VITIS_NOTES N85; prefix DEFAULT is the earlier default, =false): a memref.global has no SSA result, so without it
// --bram-analysis cannot see its accesses and prices it as RAM_1P (one live
// port, x36): OPEN_ISSUES.md O4. With the flag its accesses are collected
// through its memref.get_global sites, like an alloca's (Vitis treats globals
// exactly like locals, VITIS_NOTES.md N1a):
//   - @ACC is read and written in the same pipelined loop: two live ports ->
//     RAM_2P at x18 -> 512x32 = 2 BRAM (default: 1);
//   - @TBL is a constant-initialised global: a ROM. Two reads per cycle are
//     still simple dual port (read-only ports, N8: a ROM read twice per cycle
//     is 512x32 = 1) -> ROM_2P at x36, 64x32 = 1 BRAM (two x18 columns = 2
//     if it were priced as a two-port RAM). (A splat ROM would not do: the
//     affine.load folder turns its loads into the constant.)

// Without the flag the constant @TBL is still a ROM (W7 item 3, N26: its
// get_global sites give its ports); @ACC's accesses are not seen.
// W7 (N26): a ROM is priced at the width its values need, so the table's first
// word is the 32-bit 0x9adf1b1e of the Vitis kernels' tables (random 32-bit
// words), which keeps it a 32-bit table as in those kernels.
// DEFAULT: memref.global @ loc({{.*}}:[[#TBL:]]:3)
// DEFAULT-NEXT: kind=ROM_2P  bram=1
// DEFAULT: memref.global @ loc({{.*}}:[[#TBL+1]]:3)
// DEFAULT-NEXT: kind=RAM_1P  bram=1
// DEFAULT: Total BRAM: 2

// ATTR: memref.global @ loc({{.*}}:[[#TBL:]]:3)
// ATTR-NEXT: kind=ROM_2P  bram=1
// ATTR: memref.global @ loc({{.*}}:[[#TBL+1]]:3)
// ATTR-NEXT: kind=RAM_2P  bram=2
// ATTR: Total BRAM: 3

// DBG: TBL (global) @
// DBG: accesses (2):
// DBG: ram type: ROM_2P -- constant-initialised global (ROM, never written); element width 32 of 32 bits from its values (N26): peak 2 read(s) per cycle -> ROM_2P: read-only ports are simple dual port, x36 allowed (N8)
// DBG: ACC (global) @
// DBG: accesses (3):
// DBG: ram type: RAM_2P

module {
  memref.global "private" constant @TBL : memref<64xi32> = dense<[-1696654562, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8]>
  memref.global @ACC : memref<512xi32> = uninitialized
  func.func @k(%in: memref<512xi32>, %out: memref<512xi32>) {
    %t = memref.get_global @TBL : memref<64xi32>
    %acc = memref.get_global @ACC : memref<512xi32>
    affine.for %i = 0 to 512 {
      %a = affine.load %t[%i mod 64] : memref<64xi32>
      %b = affine.load %t[63 - %i mod 64] : memref<64xi32>
      %s = arith.addi %a, %b : i32
      %c = affine.load %acc[%i] : memref<512xi32>
      %d = arith.addi %c, %s : i32
      affine.store %d, %acc[%i] : memref<512xi32>
    }
    affine.for %i = 0 to 512 {
      %v = affine.load %acc[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
}
