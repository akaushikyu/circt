// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=bram-formula=n6 | FileCheck %s --check-prefix=REPORT

// BRAM_18K count per bank: RAMB18 aspect-ratio modes with parity bits
// (VITIS_NOTES.md N6, aspect.md R1/R2 + aspect_chk.md depth rounding):
//   BRAM = min over modes m in {1,2,4,9,18,36} of ceil(W/m) * max(1, P/depth(m)),
//   P = 2^ceil(log2 Words), depth(m) = 16384, 8192, 4096, 2048, 1024, 512
//   (the x9/x18/x36 modes carry the parity bits); x36 only when at most one
//   port is live per cycle.
//   p1024x18   1024x 18 one port    -> 1  (x18 mode: 1 column x 1024/1024)
//   p2048x9    2048x  9 one port    -> 1  (x9 mode: 1 x 2048/2048)
//   p512x36    512x 36 one port    -> 1  (x36 mode (one live port): 1 x 512/512)
//   p2500x18   2500x 18 one port    -> 4  (address depth 4096: x18 1 x 4096/1024 = 4, not ceil(2500/1024) = 3)
//   p1024x40   1024x 40 one port    -> 3  (x18: 3 columns x 1 (x36 would be 2 x 2 = 4))
//   p3072x20   3072x 20 one port    -> 5  (x4: 5 columns x 4096/4096 (x9 = 3 x 2 = 6, x18 = 2 x 4 = 8))
//   p64x32     64x 32 one port    -> 1  (x36 wide: 1 column)
//   w512x36    512x 36 1R+1W/cycle -> 2  (two live ports (1R+1W same cycle): x18 max -> 2 columns)
//   w1024x18   1024x 18 1R+1W/cycle -> 1  (x18: 1 column x 1)
//   w64x32     64x 32 1R+1W/cycle -> 2  (x18: 2 columns (same 64x32 one-port is 1))
// "one port": written in one loop, read in another. "1R+1W/cycle": an
// in-place update inside one pipelined loop (both ports live in the same
// cycle, Vitis ram_2p).
// Every value is the same under the default bram-formula=band (the 7-series
// depth bands of VITIS_NOTES.md N8) and under bram-formula=n6 (RUN line 4): the
// two formulas differ only deeper than 4096 words (bram_formula_band.mlir).

module {
  func.func @kernel(%in_p1024x18: memref<1024xi18>, %out_p1024x18: memref<1024xi18>, %in_p2048x9: memref<2048xi9>, %out_p2048x9: memref<2048xi9>, %in_p512x36: memref<512xi36>, %out_p512x36: memref<512xi36>, %in_p2500x18: memref<2500xi18>, %out_p2500x18: memref<2500xi18>, %in_p1024x40: memref<1024xi40>, %out_p1024x40: memref<1024xi40>, %in_p3072x20: memref<3072xi20>, %out_p3072x20: memref<3072xi20>, %in_p64x32: memref<64xi32>, %out_p64x32: memref<64xi32>, %in_w512x36: memref<512xi36>, %out_w512x36: memref<512xi36>, %in_w1024x18: memref<1024xi18>, %out_w1024x18: memref<1024xi18>, %in_w64x32: memref<64xi32>, %out_w64x32: memref<64xi32>) {
    %p1024x18 = memref.alloca() {hls.preserve, polygeist.varname = "p1024x18"} : memref<1024xi18>
    %p2048x9 = memref.alloca() {hls.preserve, polygeist.varname = "p2048x9"} : memref<2048xi9>
    %p512x36 = memref.alloca() {hls.preserve, polygeist.varname = "p512x36"} : memref<512xi36>
    %p2500x18 = memref.alloca() {hls.preserve, polygeist.varname = "p2500x18"} : memref<2500xi18>
    %p1024x40 = memref.alloca() {hls.preserve, polygeist.varname = "p1024x40"} : memref<1024xi40>
    %p3072x20 = memref.alloca() {hls.preserve, polygeist.varname = "p3072x20"} : memref<3072xi20>
    %p64x32 = memref.alloca() {hls.preserve, polygeist.varname = "p64x32"} : memref<64xi32>
    %w512x36 = memref.alloca() {hls.preserve, polygeist.varname = "w512x36"} : memref<512xi36>
    %w1024x18 = memref.alloca() {hls.preserve, polygeist.varname = "w1024x18"} : memref<1024xi18>
    %w64x32 = memref.alloca() {hls.preserve, polygeist.varname = "w64x32"} : memref<64xi32>
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in_p1024x18[%i] : memref<1024xi18>
      affine.store %0, %p1024x18[%i] : memref<1024xi18>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %p1024x18[1023 - %i] : memref<1024xi18>
      affine.store %0, %out_p1024x18[%i] : memref<1024xi18>
    }
    affine.for %i = 0 to 2048 {
      %0 = affine.load %in_p2048x9[%i] : memref<2048xi9>
      affine.store %0, %p2048x9[%i] : memref<2048xi9>
    }
    affine.for %i = 0 to 2048 {
      %0 = affine.load %p2048x9[2047 - %i] : memref<2048xi9>
      affine.store %0, %out_p2048x9[%i] : memref<2048xi9>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %in_p512x36[%i] : memref<512xi36>
      affine.store %0, %p512x36[%i] : memref<512xi36>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %p512x36[511 - %i] : memref<512xi36>
      affine.store %0, %out_p512x36[%i] : memref<512xi36>
    }
    affine.for %i = 0 to 2500 {
      %0 = affine.load %in_p2500x18[%i] : memref<2500xi18>
      affine.store %0, %p2500x18[%i] : memref<2500xi18>
    }
    affine.for %i = 0 to 2500 {
      %0 = affine.load %p2500x18[2499 - %i] : memref<2500xi18>
      affine.store %0, %out_p2500x18[%i] : memref<2500xi18>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in_p1024x40[%i] : memref<1024xi40>
      affine.store %0, %p1024x40[%i] : memref<1024xi40>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %p1024x40[1023 - %i] : memref<1024xi40>
      affine.store %0, %out_p1024x40[%i] : memref<1024xi40>
    }
    affine.for %i = 0 to 3072 {
      %0 = affine.load %in_p3072x20[%i] : memref<3072xi20>
      affine.store %0, %p3072x20[%i] : memref<3072xi20>
    }
    affine.for %i = 0 to 3072 {
      %0 = affine.load %p3072x20[3071 - %i] : memref<3072xi20>
      affine.store %0, %out_p3072x20[%i] : memref<3072xi20>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %in_p64x32[%i] : memref<64xi32>
      affine.store %0, %p64x32[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %p64x32[63 - %i] : memref<64xi32>
      affine.store %0, %out_p64x32[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %in_w512x36[%i] : memref<512xi36>
      affine.store %0, %w512x36[%i] : memref<512xi36>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %w512x36[%i] : memref<512xi36>
      %1 = affine.load %in_w512x36[511 - %i] : memref<512xi36>
      %2 = arith.addi %0, %1 : i36
      affine.store %2, %w512x36[%i] : memref<512xi36>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %w512x36[511 - %i] : memref<512xi36>
      affine.store %0, %out_w512x36[%i] : memref<512xi36>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in_w1024x18[%i] : memref<1024xi18>
      affine.store %0, %w1024x18[%i] : memref<1024xi18>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %w1024x18[%i] : memref<1024xi18>
      %1 = affine.load %in_w1024x18[1023 - %i] : memref<1024xi18>
      %2 = arith.addi %0, %1 : i18
      affine.store %2, %w1024x18[%i] : memref<1024xi18>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %w1024x18[1023 - %i] : memref<1024xi18>
      affine.store %0, %out_w1024x18[%i] : memref<1024xi18>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %in_w64x32[%i] : memref<64xi32>
      affine.store %0, %w64x32[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %w64x32[%i] : memref<64xi32>
      %1 = affine.load %in_w64x32[63 - %i] : memref<64xi32>
      %2 = arith.addi %0, %1 : i32
      affine.store %2, %w64x32[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %w64x32[63 - %i] : memref<64xi32>
      affine.store %0, %out_w64x32[%i] : memref<64xi32>
    }
    return
  }
}

// CHECK:      p1024x18 (alloca)
// CHECK:        ram type: RAM_1P
// CHECK:        bram: 1
// CHECK:      p2048x9 (alloca)
// CHECK:        ram type: RAM_1P
// CHECK:        bram: 1
// CHECK:      p512x36 (alloca)
// CHECK:        ram type: RAM_1P
// CHECK:        bram: 1
// CHECK:      p2500x18 (alloca)
// CHECK:        ram type: RAM_1P
// CHECK:        bram: 4
// CHECK:      p1024x40 (alloca)
// CHECK:        ram type: RAM_1P
// CHECK:        bram: 3
// CHECK:      p3072x20 (alloca)
// CHECK:        ram type: RAM_1P
// CHECK:        bram: 5
// CHECK:      p64x32 (alloca)
// CHECK:        ram type: RAM_1P
// CHECK:        bram: 1
// CHECK:      w512x36 (alloca)
// CHECK:        ram type: RAM_2P
// CHECK:        bram: 2
// CHECK:      w1024x18 (alloca)
// CHECK:        ram type: RAM_2P
// CHECK:        bram: 1
// CHECK:      w64x32 (alloca)
// CHECK:        ram type: RAM_2P
// CHECK:        bram: 2
// CHECK:      Total BRAM: 21

// REPORT: Total BRAM: 21
