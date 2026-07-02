// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=REPORT
// RUN: FileCheck %s --input-file=%t.err

// BRAM vs. distributed RAM (VITIS_NOTES.md N5, 23 kernels): Words * exact
// element Bits >= 1024 -> BRAM_18K, < 1024 -> distributed RAM (0 BRAM). The
// threshold is inclusive and uses the exact width, not a power-of-two one:
//   64 x 16 = 1024 -> 1 BRAM    (lutram_d64_w16)
//   93 x 11 = 1023 -> 0         (lutram_chk_d93_w11; a pow2 width would say 1488)
//   64 x 15 =  960 -> 0         (lutram_chk_d64_w15; pow2 width would say 1024)
//   16 x 64 = 1024 -> 2 BRAM    (lutram_d16_w64; one live port, x36: 2 columns)
//   1024 x 1 = 1024 -> 1 BRAM   (aspect_1p_w1_d1024)
//   32 x 32 = 1024 -> 1 BRAM    (lutram_d32_w32)
// Every array is written in one loop and read in another: one live port.
// The i11 / i15 memrefs are what cgeist emits with the width-exact shim
// (`--shim exact`, `_BitInt(W)`); the harness's default scalar shim widens
// ap_int<11> / ap_int<15> to i16, so through it both arrays are 1 BRAM
// (VITIS_NOTES.md N5, OPEN_ISSUES.md O6).

module {
  func.func @kernel(%in_b64x16: memref<64xi16>, %out_b64x16: memref<64xi16>, %in_b93x11: memref<93xi11>, %out_b93x11: memref<93xi11>, %in_b64x15: memref<64xi15>, %out_b64x15: memref<64xi15>, %in_b16x64: memref<16xi64>, %out_b16x64: memref<16xi64>, %in_b1024x1: memref<1024xi1>, %out_b1024x1: memref<1024xi1>, %in_b32x32: memref<32xi32>, %out_b32x32: memref<32xi32>) {
    %b64x16 = memref.alloca() {hls.preserve, polygeist.varname = "b64x16"} : memref<64xi16>
    %b93x11 = memref.alloca() {hls.preserve, polygeist.varname = "b93x11"} : memref<93xi11>
    %b64x15 = memref.alloca() {hls.preserve, polygeist.varname = "b64x15"} : memref<64xi15>
    %b16x64 = memref.alloca() {hls.preserve, polygeist.varname = "b16x64"} : memref<16xi64>
    %b1024x1 = memref.alloca() {hls.preserve, polygeist.varname = "b1024x1"} : memref<1024xi1>
    %b32x32 = memref.alloca() {hls.preserve, polygeist.varname = "b32x32"} : memref<32xi32>
    affine.for %i = 0 to 64 {
      %0 = affine.load %in_b64x16[%i] : memref<64xi16>
      affine.store %0, %b64x16[%i] : memref<64xi16>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %b64x16[63 - %i] : memref<64xi16>
      affine.store %0, %out_b64x16[%i] : memref<64xi16>
    }
    affine.for %i = 0 to 93 {
      %0 = affine.load %in_b93x11[%i] : memref<93xi11>
      affine.store %0, %b93x11[%i] : memref<93xi11>
    }
    affine.for %i = 0 to 93 {
      %0 = affine.load %b93x11[92 - %i] : memref<93xi11>
      affine.store %0, %out_b93x11[%i] : memref<93xi11>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %in_b64x15[%i] : memref<64xi15>
      affine.store %0, %b64x15[%i] : memref<64xi15>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %b64x15[63 - %i] : memref<64xi15>
      affine.store %0, %out_b64x15[%i] : memref<64xi15>
    }
    affine.for %i = 0 to 16 {
      %0 = affine.load %in_b16x64[%i] : memref<16xi64>
      affine.store %0, %b16x64[%i] : memref<16xi64>
    }
    affine.for %i = 0 to 16 {
      %0 = affine.load %b16x64[15 - %i] : memref<16xi64>
      affine.store %0, %out_b16x64[%i] : memref<16xi64>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in_b1024x1[%i] : memref<1024xi1>
      affine.store %0, %b1024x1[%i] : memref<1024xi1>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %b1024x1[1023 - %i] : memref<1024xi1>
      affine.store %0, %out_b1024x1[%i] : memref<1024xi1>
    }
    affine.for %i = 0 to 32 {
      %0 = affine.load %in_b32x32[%i] : memref<32xi32>
      affine.store %0, %b32x32[%i] : memref<32xi32>
    }
    affine.for %i = 0 to 32 {
      %0 = affine.load %b32x32[31 - %i] : memref<32xi32>
      affine.store %0, %out_b32x32[%i] : memref<32xi32>
    }
    return
  }
}

// CHECK:      b64x16 (alloca)
// CHECK:        status: counted
// CHECK:        bram: 1
// CHECK:      b93x11 (alloca)
// CHECK:        status: excluded_small -- size 1023 bits < 1024-bit BRAM promotion threshold (Words*Bits >= 1024 -> BRAM); distributed RAM, 0 BRAM
// CHECK:        bram: 0
// CHECK:      b64x15 (alloca)
// CHECK:        status: excluded_small -- size 960 bits < 1024-bit BRAM promotion threshold (Words*Bits >= 1024 -> BRAM); distributed RAM, 0 BRAM
// CHECK:        bram: 0
// CHECK:      b16x64 (alloca)
// CHECK:        status: counted
// CHECK:        bram: 2
// CHECK:      b1024x1 (alloca)
// CHECK:        status: counted
// CHECK:        bram: 1
// CHECK:      b32x32 (alloca)
// CHECK:        status: counted
// CHECK:        bram: 1
// CHECK:      Total BRAM: 5

// REPORT: Total BRAM: 5
