// RUN: hls-est %s --memory-banking-bram | FileCheck %s --check-prefix=IR
// RUN: hls-est %s --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s

// C's signed `%` (and affine `mod` after lowering) reaches the banking as
// `r = remsi(x, M); select(r < 0, r + M, r)`. That value differs from x by a
// multiple of M, so modulo a cyclic factor F that divides M it is x: two
// unrolled copies `(2 i + u) % 16`, u = 0, 1, of an array cyclic by 2 read
// different banks, one read per bank per iteration (OPEN_ISSUES O121:
// MultiHeadSelfAttention1 opt3 / opt4 `v341`, Vitis one single memory per
// bank; before, both copies were charged to every bank).
//   @signed_mod   offsets 0 and 1 modulo 16, F = 2: one load per bank.
//   @mod_not_multiple  `% 15` with F = 2 (15 is no multiple of 2): rewritten
//                 one by one as before (each copy reads both banks).

// IR-LABEL: func.func @signed_mod
// IR-COUNT-2: memref.load %alloca{{(_[0-9]+)?}}[
// IR-NOT: memref.load %alloca
// IR: return
// IR-LABEL: func.func @mod_not_multiple
// IR-COUNT-4: memref.load %alloca{{(_[0-9]+)?}}[
// IR-NOT: memref.load %alloca
// IR: return

// CHECK-COUNT-2: 512x32b -> RAM_1P (x36/port) = 1 BRAM_18K
// CHECK-COUNT-2: 512x32b -> RAM_2P (x18/port) = 2 BRAM_18K
// CHECK: Total BRAM: 6

func.func @signed_mod(%in: memref<1024xf32>, %out: memref<64xf32>) {
  %c0 = arith.constant 0 : index
  %c1 = arith.constant 1 : index
  %c2 = arith.constant 2 : index
  %c16 = arith.constant 16 : index
  %A = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "A"}], polygeist.varname = "A"} : memref<64x16xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 16 {
      %x = affine.load %in[%i * 16 + %j] : memref<1024xf32>
      affine.store %x, %A[%i, %j] : memref<64x16xf32>
    }
  }
  affine.for %i = 0 to 64 {
    %b = arith.muli %i, %c2 : index
    %x0 = arith.addi %b, %c0 : index
    %r0 = arith.remsi %x0, %c16 : index
    %n0 = arith.cmpi slt, %r0, %c0 : index
    %p0 = arith.addi %r0, %c16 : index
    %k0 = arith.select %n0, %p0, %r0 : index
    %v0 = memref.load %A[%i, %k0] : memref<64x16xf32>
    %x1 = arith.addi %b, %c1 : index
    %r1 = arith.remsi %x1, %c16 : index
    %n1 = arith.cmpi slt, %r1, %c0 : index
    %p1 = arith.addi %r1, %c16 : index
    %k1 = arith.select %n1, %p1, %r1 : index
    %v1 = memref.load %A[%i, %k1] : memref<64x16xf32>
    %s = arith.addf %v0, %v1 : f32
    affine.store %s, %out[%i] : memref<64xf32>
  } {hls.pipeline = [{II = 1 : i32}]}
  return
}

func.func @mod_not_multiple(%in: memref<960xf32>, %out: memref<64xf32>) {
  %c0 = arith.constant 0 : index
  %c1 = arith.constant 1 : index
  %c2 = arith.constant 2 : index
  %c15 = arith.constant 15 : index
  %A = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "A"}], polygeist.varname = "B"} : memref<64x15xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 15 {
      %x = affine.load %in[%i * 15 + %j] : memref<960xf32>
      affine.store %x, %A[%i, %j] : memref<64x15xf32>
    }
  }
  affine.for %i = 0 to 64 {
    %b = arith.muli %i, %c2 : index
    %x0 = arith.addi %b, %c0 : index
    %r0 = arith.remsi %x0, %c15 : index
    %n0 = arith.cmpi slt, %r0, %c0 : index
    %p0 = arith.addi %r0, %c15 : index
    %k0 = arith.select %n0, %p0, %r0 : index
    %v0 = memref.load %A[%i, %k0] : memref<64x15xf32>
    %x1 = arith.addi %b, %c1 : index
    %r1 = arith.remsi %x1, %c15 : index
    %n1 = arith.cmpi slt, %r1, %c0 : index
    %p1 = arith.addi %r1, %c15 : index
    %k1 = arith.select %n1, %p1, %r1 : index
    %v1 = memref.load %A[%i, %k1] : memref<64x15xf32>
    %s = arith.addf %v0, %v1 : f32
    affine.store %s, %out[%i] : memref<64xf32>
  } {hls.pipeline = [{II = 1 : i32}]}
  return
}
