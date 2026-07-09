// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=DEFAULT
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis --bram-attribute-globals --bram-debug -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=ATTR
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG

// cgeist emits `static const int tbl[512] = {...}` as a private global with a
// dense initial value and *without* `constant`. With --bram-attribute-globals
// an initialised global that none of its get_global sites (or their views)
// writes, and that does not escape, is a ROM like a `constant` one. Vitis
// 2025.1, kernel rom2r_int (a 512x32 table read twice per cycle at II = 1):
// `tbl_ROM_AUTO_1R`, 1 BRAM (as N8 fr_rom2r_w32_d512); priced as a two-port
// RAM it was RAM_T2P at x18 = 2.
//   - @tbl: read twice per cycle, never written            -> ROM_2P, 1
//   - @state: initialised, but written in the loop         -> a RAM
//   - @esc: initialised, passed to a call (may be written) -> a RAM
// Without the flag a global's accesses are not seen (RAM_1P, O4).

// DEFAULT: memref.global @ loc({{.*}}:[[#L:]]:3)
// DEFAULT-NEXT: kind=RAM_1P  bram=1

// ATTR: memref.global @ loc({{.*}}:[[#L:]]:3)
// ATTR-NEXT: kind=ROM_2P  bram=1
// ATTR-NEXT: 512x32b initialised global, never written -> ROM_2P (2 read port(s)/cycle) = 1 BRAM_18K
// ATTR: memref.global @ loc({{.*}}:[[#L+1]]:3)
// ATTR-NEXT: kind=RAM_
// ATTR: memref.global @ loc({{.*}}:[[#L+2]]:3)
// ATTR-NEXT: kind=RAM_

// DBG: tbl (global @tbl) @
// DBG: ram type: ROM_2P -- initialised global that no get_global site writes (ROM): peak 2 read(s) per cycle
// DBG: state (global @state) @
// DBG-NOT: ROM
// DBG: ram type: RAM_
// DBG: esc (global @esc) @
// DBG-NOT: ROM
// DBG: ram type: RAM_

module {
  memref.global "private" @tbl : memref<512xi32> = dense<[0, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8, 0, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8, 0, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8, 0, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8, 0, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8, 0, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8, 0, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8, 0, 37, 74, 10, 47, 84, 20, 57, 94, 30, 67, 3, 40, 77, 13, 50, 87, 23, 60, 97, 33, 70, 6, 43, 80, 16, 53, 90, 26, 63, 100, 36, 73, 9, 46, 83, 19, 56, 93, 29, 66, 2, 39, 76, 12, 49, 86, 22, 59, 96, 32, 69, 5, 42, 79, 15, 52, 89, 25, 62, 99, 35, 72, 8]> {polygeist.varname = "tbl"}
  memref.global "private" @state : memref<512xi32> = dense<1> {polygeist.varname = "state"}
  memref.global "private" @esc : memref<512xi32> = dense<2> {polygeist.varname = "esc"}
  func.func private @touch(memref<512xi32>)
  func.func @rom2r(%in: memref<1024xi32>, %out: memref<1024xi32>) {
    %t = memref.get_global @tbl : memref<512xi32>
    %s = memref.get_global @state : memref<512xi32>
    %e = memref.get_global @esc : memref<512xi32>
    func.call @touch(%e) : (memref<512xi32>) -> ()
    %c511 = arith.constant 511 : i32
    %c1 = arith.constant 1 : i32
    affine.for %i = 0 to 1024 {
      %x = affine.load %in[%i] : memref<1024xi32>
      %x1 = arith.addi %x, %c1 : i32
      %a0 = arith.andi %x, %c511 : i32
      %a1 = arith.andi %x1, %c511 : i32
      %i0 = arith.index_cast %a0 : i32 to index
      %i1 = arith.index_cast %a1 : i32 to index
      %v0 = memref.load %t[%i0] : memref<512xi32>
      %v1 = memref.load %t[%i1] : memref<512xi32>
      %sv = memref.load %s[%i0] : memref<512xi32>
      %ev = memref.load %e[%i1] : memref<512xi32>
      %r0 = arith.addi %v0, %v1 : i32
      %r1 = arith.addi %r0, %sv : i32
      %r = arith.addi %r1, %ev : i32
      memref.store %r, %s[%i1] : memref<512xi32>
      affine.store %r, %out[%i] : memref<1024xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
