// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT

// --bram-debug prints the human-readable derivation to stderr, after the normal
// report, which stays on stdout and unchanged (REPORT).
//
// Covers one memref of each kind the explanation distinguishes: the banks of a
// pragma-partitioned array (`buf`, cyclic 2), a plain counted array (`acc`), an
// array below the BRAM promotion threshold (`small`, 8 x i32 = 256 bits), and a
// global whose accesses cannot be attributed (`coef`).

module {
  memref.global "private" constant @coef : memref<64xi32> = dense<1>
  func.func @kernel(%arg0: memref<1024xi32>, %arg1: memref<256xi32>) {
    %c1_i32 = arith.constant 1 : i32
    %buf = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "buf"}], hls.preserve, polygeist.varname = "buf"} : memref<1024xi32> loc("kernel.cpp":12:5)
    %acc = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<256xi32> loc("kernel.cpp":13:5)
    %small = memref.alloca() {hls.preserve, polygeist.varname = "small"} : memref<8xi32> loc("kernel.cpp":14:5)
    %coef = memref.get_global @coef : memref<64xi32>
    affine.for %i = 0 to 1024 {
      %0 = affine.load %arg0[%i] : memref<1024xi32>
      affine.store %0, %buf[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 8 {
      %0 = affine.load %coef[%i] : memref<64xi32>
      affine.store %0, %small[%i] : memref<8xi32>
    }
    affine.for %i = 0 to 256 {
      %0 = affine.load %buf[%i * 2] : memref<1024xi32>
      %1 = affine.load %buf[%i * 2 + 1] : memref<1024xi32>
      %2 = affine.load %small[%i mod 8] : memref<8xi32>
      %3 = arith.addi %0, %1 : i32
      %4 = arith.addi %3, %2 : i32
      affine.store %4, %acc[%i] : memref<256xi32>
    }
    affine.for %i = 0 to 256 {
      %0 = affine.load %acc[%i] : memref<256xi32>
      %1 = arith.addi %0, %c1_i32 : i32
      affine.store %1, %arg1[%i] : memref<256xi32>
    }
    return
  }
}

// CHECK:      === bram-debug: how each BRAM number was derived ===

// The global comes first in module walk order; its accesses go through
// memref.get_global and are not attributed to the declaration.
// CHECK:      [global#0] coef (global) @
// CHECK-NEXT:   shape [64] x i32 (32 bits) = 64 words
// CHECK-NEXT:   status: counted
// CHECK-NEXT:   partition: none
// CHECK-NEXT:   accesses: not attributed (memref.global has no SSA result)
// CHECK-NEXT:   ram type: RAM_1P -- global: accesses not attributed, default RAM_1P
// CHECK-NEXT:   bank math: 16384 bits/BRAM_18K, max width 32 at RAM_1P, element 32b -> config width 32, width tiles 1, depth/block 512, depth tiles ceil(64/512)=1, replication 1 -> 1 block(s)
// CHECK-NEXT:   bram: 1

// CHECK:      [kernel#1] buf[bank 0/2] (alloca) @ kernel.cpp:12:5
// CHECK-NEXT:   shape [512] x i32 (32 bits) = 512 words
// CHECK-NEXT:   status: counted
// CHECK-NEXT:   partition: cyclic factor=2 dim=1 source=pragma (bank 0 of 2)
// CHECK-NEXT:   accesses (2):
// CHECK:          port demand: reads=1 writes=1 total=1 (max over scopes; segregated R/W)
// CHECK:          ram type: RAM_1P -- peak port demand 1/cycle (1R+1W, max over scopes): at most one live port -> RAM_1P (x32 wide, no TDP constraint)
// CHECK:          bank math: 16384 bits/BRAM_18K, max width 32 at RAM_1P, element 32b -> config width 32, width tiles 1, depth/block 512, depth tiles ceil(512/512)=1, replication 1 -> 1 block(s)
// CHECK-NEXT:   bram: 1

// CHECK:      [kernel#2] buf[bank 1/2] (alloca) @ kernel.cpp:12:5
// CHECK:        partition: cyclic factor=2 dim=1 source=pragma (bank 1 of 2)
// CHECK:        bram: 1

// CHECK:      [kernel#3] acc (alloca) @ kernel.cpp:13:5
// CHECK-NEXT:   shape [256] x i32 (32 bits) = 256 words
// CHECK-NEXT:   status: counted
// CHECK-NEXT:   partition: none
// CHECK:        bank math: 16384 bits/BRAM_18K, max width 32 at RAM_1P, element 32b -> config width 32, width tiles 1, depth/block 512, depth tiles ceil(256/512)=1, replication 1 -> 1 block(s)
// CHECK-NEXT:   bram: 1

// CHECK:      [kernel#4] small (alloca) @ kernel.cpp:14:5
// CHECK-NEXT:   shape [8] x i32 (32 bits) = 8 words
// CHECK-NEXT:   status: excluded_small -- size 256 bits <= 1024-bit BRAM promotion threshold; kept in LUTRAM/FFs
// CHECK:        ram type: RAM_1P -- not selected: excluded from BRAM accounting (LUTRAM / stream / zero-size)
// CHECK-NEXT:   bram: 0

// CHECK:      --- summary (sorted by BRAM) ---
// CHECK-NEXT:        1  global#0  coef
// CHECK-NEXT:        1  kernel#1  buf[bank 0/2]
// CHECK-NEXT:        1  kernel#2  buf[bank 1/2]
// CHECK-NEXT:        1  kernel#3  acc
// CHECK-NEXT:        0  kernel#4  small
// CHECK-NEXT: Total BRAM: 4

// REPORT:      memref.global
// REPORT:      kind=RAM_1P  bram=1
// REPORT:      Total BRAM: 4
// REPORT-NOT:  bram-debug
