// RUN: hls-est %s --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: hls-est %s --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug-json=%t.json > %t.json.out
// RUN: hls-est %s --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis > %t.plain.out
// RUN: diff %t.plain.out %t.json.out
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s --check-prefix=OFF

// --bram-analysis prices an array with the width --narrow-ram-widths marks,
// before the LUTRAM threshold, on every bank (Vitis 2025.1 td=off):
//   small  int[64] read only as an index of a 64-word table: 64x6 = 384
//          bits < 1024, distributed RAM, 0 BRAM (w9n_h1_lut64; 64x32 would
//          be 1 BRAM)
//   big    int[1024] read only as an index of the same table: 1024x6 = 1
//          BRAM (w9n_h1_t64; 1024x32 = 2)
//   part   int[2048] cyclic factor 2, read only as an index: each 1024-word
//          bank 1024x6 = 1 BRAM (w9n_h1_part2: both banks get the width)
//   tbl    64x32, stored to the output: 1 BRAM, not narrowed

// CHECK: Total BRAM: 4
// OFF:   Total BRAM: 8

// DBG:      small (alloca)
// DBG:        narrowed width: 6 of 32 bits (6 of 32 bits: {{.*}}loads demand 6 bits: {{.*}}subscript of 'tbl'{{.*}})
// DBG:        status: excluded_small -- size 384 bits (narrowed element width) < 1024-bit BRAM promotion threshold
// DBG:      big (alloca)
// DBG:        narrowed width: 6 of 32 bits
// DBG:        bram: 1
// DBG:      part[bank 0/2] (alloca)
// DBG:        narrowed width: 6 of 32 bits
// DBG:        bram: 1
// DBG:      part[bank 1/2] (alloca)
// DBG:        narrowed width: 6 of 32 bits
// DBG:        bram: 1

// JSON:      "narrow": {
// JSON-NEXT:   "bits": 6,
// JSON-NEXT:   "declared_bits": 32,
// JSON-NEXT:   "reason": "6 of 32 bits: {{.*}}"

module {
  func.func @kernel(%in: memref<2048xi32>, %v: memref<64xi32>, %out: memref<2048xi32>) {
    %tbl = memref.alloca() {polygeist.varname = "tbl"} : memref<64xi32>
    %small = memref.alloca() {polygeist.varname = "small"} : memref<64xi32>
    %big = memref.alloca() {polygeist.varname = "big"} : memref<1024xi32>
    %part = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic", variable = "part"}], polygeist.varname = "part"} : memref<2048xi32>
    affine.for %i = 0 to 64 {
      %0 = affine.load %v[%i] : memref<64xi32>
      affine.store %0, %tbl[%i] : memref<64xi32>
      affine.store %0, %small[%i] : memref<64xi32>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in[%i] : memref<2048xi32>
      affine.store %0, %big[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 2048 {
      %0 = affine.load %in[%i] : memref<2048xi32>
      affine.store %0, %part[%i] : memref<2048xi32>
    }
    affine.for %i = 0 to 64 {
      %0 = affine.load %small[%i] : memref<64xi32>
      %1 = arith.index_cast %0 : i32 to index
      %2 = memref.load %tbl[%1] : memref<64xi32>
      affine.store %2, %out[%i] : memref<2048xi32>
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %big[%i] : memref<1024xi32>
      %1 = arith.index_cast %0 : i32 to index
      %2 = memref.load %tbl[%1] : memref<64xi32>
      affine.store %2, %out[%i] : memref<2048xi32>
    }
    affine.for %i = 0 to 2048 {
      %0 = affine.load %part[%i] : memref<2048xi32>
      %1 = arith.index_cast %0 : i32 to index
      %2 = memref.load %tbl[%1] : memref<64xi32>
      affine.store %2, %out[%i] : memref<2048xi32>
    }
    return
  }
}
