// RUN: hls-est %s --memory-banking-bram | FileCheck %s --check-prefix=IR
// RUN: hls-est %s --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s

// Unrolled copies of one runtime-indexed read whose indices differ by
// constants distinct modulo the cyclic factor address a different bank each;
// Vitis reads every bank once per iteration (VITIS_NOTES.md N27, W7 review
// D3; kernel w7rv_rt4: A[4096] cyclic 4, A[(base + 4*i + u) & 4095] for
// u < 4 at II 1: four banks ram_1p, 8 BRAM). Each bank is loaded once.
//   @steered   offsets 0..3: one load per bank, 4 x 2 BRAM = 8.
//   @collide   offsets 0 and 4 meet in one bank: rewritten one by one as
//              before (each copy reads every candidate bank).

// IR-LABEL: func.func @steered
// IR-COUNT-4: memref.load %alloca{{(_[0-9]+)?}}[
// IR-NOT: memref.load %alloca
// IR: return
// IR-LABEL: func.func @collide
// IR-COUNT-8: memref.load %alloca{{(_[0-9]+)?}}[
// IR-NOT: memref.load %alloca
// IR: return

// @steered: one read per bank (Vitis: ram_1p, 8 BRAM); @collide: two.
// CHECK-COUNT-4: 1024x32b -> RAM_1P (x18/port) = 2 BRAM_18K
// CHECK-COUNT-4: 1024x32b -> RAM_2P (x18/port) = 2 BRAM_18K
// CHECK: Total BRAM: 16

func.func @steered(%in: memref<4096xi32>, %base: i32) -> i32 {
  %c4095 = arith.constant 4095 : i32
  %c0 = arith.constant 0 : i32
  %c1 = arith.constant 1 : i32
  %c2 = arith.constant 2 : i32
  %c3 = arith.constant 3 : i32
  %c4 = arith.constant 4 : i32
  %A = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "A"}], polygeist.varname = "A"} : memref<4096xi32>
  affine.for %i = 0 to 4096 {
    %x = affine.load %in[%i] : memref<4096xi32>
    affine.store %x, %A[%i] : memref<4096xi32>
  }
  %r = affine.for %i = 0 to 1024 iter_args(%acc = %c0) -> (i32) {
    %ii = arith.index_cast %i : index to i32
    %m = arith.muli %ii, %c4 : i32
    %b = arith.addi %base, %m : i32
    %a0 = arith.andi %b, %c4095 : i32
    %j0 = arith.index_cast %a0 : i32 to index
    %v0 = memref.load %A[%j0] : memref<4096xi32>
    %s0 = arith.addi %acc, %v0 : i32
    %b1 = arith.addi %b, %c1 : i32
    %a1 = arith.andi %b1, %c4095 : i32
    %j1 = arith.index_cast %a1 : i32 to index
    %v1 = memref.load %A[%j1] : memref<4096xi32>
    %s1 = arith.addi %s0, %v1 : i32
    %b2 = arith.addi %b, %c2 : i32
    %a2 = arith.andi %b2, %c4095 : i32
    %j2 = arith.index_cast %a2 : i32 to index
    %v2 = memref.load %A[%j2] : memref<4096xi32>
    %s2 = arith.addi %s1, %v2 : i32
    %b3 = arith.addi %b, %c3 : i32
    %a3 = arith.andi %b3, %c4095 : i32
    %j3 = arith.index_cast %a3 : i32 to index
    %v3 = memref.load %A[%j3] : memref<4096xi32>
    %s3 = arith.addi %s2, %v3 : i32
    affine.yield %s3 : i32
  } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
  return %r : i32
}

func.func @collide(%in: memref<4096xi32>, %base: i32) -> i32 {
  %c4095 = arith.constant 4095 : i32
  %c0 = arith.constant 0 : i32
  %c4 = arith.constant 4 : i32
  %c8 = arith.constant 8 : i32
  %A = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "A"}], polygeist.varname = "A2"} : memref<4096xi32>
  affine.for %i = 0 to 4096 {
    %x = affine.load %in[%i] : memref<4096xi32>
    affine.store %x, %A[%i] : memref<4096xi32>
  }
  %r = affine.for %i = 0 to 512 iter_args(%acc = %c0) -> (i32) {
    %ii = arith.index_cast %i : index to i32
    %m = arith.muli %ii, %c8 : i32
    %b = arith.addi %base, %m : i32
    %a0 = arith.andi %b, %c4095 : i32
    %j0 = arith.index_cast %a0 : i32 to index
    %v0 = memref.load %A[%j0] : memref<4096xi32>
    %s0 = arith.addi %acc, %v0 : i32
    %b1 = arith.addi %b, %c4 : i32
    %a1 = arith.andi %b1, %c4095 : i32
    %j1 = arith.index_cast %a1 : i32 to index
    %v1 = memref.load %A[%j1] : memref<4096xi32>
    %s1 = arith.addi %s0, %v1 : i32
    affine.yield %s1 : i32
  } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
  return %r : i32
}
