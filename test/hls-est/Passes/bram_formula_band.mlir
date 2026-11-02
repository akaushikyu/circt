// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug --bram-debug-json=%t.json > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out --check-prefix=BAND
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=bram-formula=band | FileCheck %s --check-prefix=BAND
// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=bram-formula=n6 --bram-debug 2>&1 >/dev/null | FileCheck %s --check-prefix=N6

// The default BRAM formula (bram-formula=band, MEMOS.md M4 / decision #6):
// the 7-series depth bands, from our measurements (VITIS_NOTES.md N8 (a)-(d)).
// By the address depth P = 2^ceil(log2 words) and the width W:
//   P <= 512 ceil(W/36) if SDP else ceil(W/18); 1024 ceil(W/18); 2048 ceil(W/9);
//   4096 min(ceil(W/4), 2*ceil(W/9)); 8192 ceil(W/2); >= 16384 (P/16384) * W.
// The old formula (bram-formula=n6, the minimum over the aspect-ratio modes,
// N6) agrees up to 4096 words and stacks 2Kx9 / 1Kx18 / 512x36 blocks deeper,
// which Vitis 2025.1 does not do. Vitis values from the fr_* kernels
// (~/hls-est-work/exp-src/formula, experiments/fr_*; aspect_bs2p_* for 512x72):
//   bank        ports                      Vitis  band  n6
//   p8192x9     one port (fr_1p_w9_d8192)    5     5    4
//   p8192x18    one port (fr_1p_w18_d8192)   9     9    8
//   p6000x27    one port (fr_1p_w27_d6000)  14    14   12  (P = 8192)
//   p16384x18   one port (fr_1p_w18_d16384) 18    18   16
//   p512x72     write-only + read-only port  2     2    2  (written in one loop,
//               read in another: SDP, x36; aspect_bs2p_w72_d512 binds ram_2p
//               and still gets 2, N8 (d); bind_storage is not carried to
//               hls-est, the ports used decide)
//   w512x72     read-write + read port       -     4    4  (in-place update in
//               one pipelined loop: not SDP, x18; N6's w512x36 = 2 analogue)
//   p4096x9     one port                     -     2    2  (the 2049-4096 band:
//               min(ceil(9/4) = 3, 2 * ceil(9/9) = 2) = two 2Kx9 per column)
// "one port": written in one loop, read in another.

// BAND: kind=RAM_1P  bram=5
// BAND: kind=RAM_1P  bram=9
// BAND: kind=RAM_1P  bram=14
// BAND: kind=RAM_1P  bram=18
// BAND: kind=RAM_1P  bram=2
// BAND: kind=RAM_2P  bram=4
// BAND: kind=RAM_1P  bram=2
// BAND: Total BRAM: 54

// DBG: bram formula: band (7-series depth bands, VITIS_NOTES.md N8)
// DBG:      p8192x9 (alloca)
// DBG:        bank math: {{.*}} -> 5 block(s); formula band: depth 4097-8192: ceil(W/2)
// DBG:        bram: 5
// DBG:      p8192x18 (alloca)
// DBG:        bank math: {{.*}} -> 9 block(s); formula band: depth 4097-8192: ceil(W/2)
// DBG:        bram: 9
// DBG:      p6000x27 (alloca)
// DBG:        bank math: {{.*}} -> 14 block(s); formula band: depth 4097-8192: ceil(W/2)
// DBG:        bram: 14
// DBG:      p16384x18 (alloca)
// DBG:        bank math: {{.*}} -> 18 block(s); formula band: depth > 8192: 2^ceil(log2 ceil(D/16384)) * W
// DBG:        bram: 18
// DBG:      p512x72 (alloca)
// DBG:        bank math: {{.*}} -> 2 block(s); formula band: depth <= 512, SDP: ceil(W/36)
// DBG:        bram: 2
// DBG:      w512x72 (alloca)
// DBG:        bank math: {{.*}} -> 4 block(s); formula band: depth <= 512, not SDP: ceil(W/18)
// DBG:        bram: 4
// DBG:      p4096x9 (alloca)
// DBG:        bank math: {{.*}} -> 2 block(s); formula band: depth 2049-4096: min(ceil(W/4), 2*ceil(W/9))
// DBG:        bram: 2

// JSON: "bram_formula": "band",
// JSON: "bank_math": {
// JSON-NEXT:   "addr_depth": 8192,
// JSON-NEXT:   "band": "depth 4097-8192: ceil(W/2)",
// JSON:        "formula": "band",

// N6: bram formula: n6 (min over aspect-ratio modes, VITIS_NOTES.md N6)
// N6:      p8192x9 (alloca)
// N6:        bank math: {{.*}} -> 4 block(s); formula n6: min over the aspect-ratio modes (N6)
// N6:        bram: 4
// N6:      p8192x18 (alloca)
// N6:        bank math: {{.*}} -> 8 block(s); formula n6: min over the aspect-ratio modes (N6)
// N6:        bram: 8
// N6:      p6000x27 (alloca)
// N6:        bank math: {{.*}} -> 12 block(s); formula n6: min over the aspect-ratio modes (N6)
// N6:        bram: 12
// N6:      p16384x18 (alloca)
// N6:        bank math: {{.*}} -> 16 block(s); formula n6: min over the aspect-ratio modes (N6)
// N6:        bram: 16
// N6:      p512x72 (alloca)
// N6:        bank math: {{.*}} -> 2 block(s); formula n6: min over the aspect-ratio modes (N6)
// N6:        bram: 2
// N6:      w512x72 (alloca)
// N6:        bank math: {{.*}} -> 4 block(s); formula n6: min over the aspect-ratio modes (N6)
// N6:        bram: 4
// N6:      p4096x9 (alloca)
// N6:        bank math: {{.*}} -> 2 block(s); formula n6: min over the aspect-ratio modes (N6)
// N6:        bram: 2
// N6: Total BRAM: 48

module {
  func.func @kernel(%in_p8192x9: memref<8192xi9>, %out_p8192x9: memref<8192xi9>, %in_p8192x18: memref<8192xi18>, %out_p8192x18: memref<8192xi18>, %in_p6000x27: memref<6000xi27>, %out_p6000x27: memref<6000xi27>, %in_p16384x18: memref<16384xi18>, %out_p16384x18: memref<16384xi18>, %in_p512x72: memref<512xi72>, %out_p512x72: memref<512xi72>, %in_w512x72: memref<512xi72>, %out_w512x72: memref<512xi72>, %in_p4096x9: memref<4096xi9>, %out_p4096x9: memref<4096xi9>) {
    %p8192x9 = memref.alloca() {hls.preserve, polygeist.varname = "p8192x9"} : memref<8192xi9>
    %p8192x18 = memref.alloca() {hls.preserve, polygeist.varname = "p8192x18"} : memref<8192xi18>
    %p6000x27 = memref.alloca() {hls.preserve, polygeist.varname = "p6000x27"} : memref<6000xi27>
    %p16384x18 = memref.alloca() {hls.preserve, polygeist.varname = "p16384x18"} : memref<16384xi18>
    %p512x72 = memref.alloca() {hls.preserve, polygeist.varname = "p512x72"} : memref<512xi72>
    %w512x72 = memref.alloca() {hls.preserve, polygeist.varname = "w512x72"} : memref<512xi72>
    %p4096x9 = memref.alloca() {hls.preserve, polygeist.varname = "p4096x9"} : memref<4096xi9>
    affine.for %i = 0 to 8192 {
      %0 = affine.load %in_p8192x9[%i] : memref<8192xi9>
      affine.store %0, %p8192x9[%i] : memref<8192xi9>
    }
    affine.for %i = 0 to 8192 {
      %0 = affine.load %p8192x9[8191 - %i] : memref<8192xi9>
      affine.store %0, %out_p8192x9[%i] : memref<8192xi9>
    }
    affine.for %i = 0 to 8192 {
      %0 = affine.load %in_p8192x18[%i] : memref<8192xi18>
      affine.store %0, %p8192x18[%i] : memref<8192xi18>
    }
    affine.for %i = 0 to 8192 {
      %0 = affine.load %p8192x18[8191 - %i] : memref<8192xi18>
      affine.store %0, %out_p8192x18[%i] : memref<8192xi18>
    }
    affine.for %i = 0 to 6000 {
      %0 = affine.load %in_p6000x27[%i] : memref<6000xi27>
      affine.store %0, %p6000x27[%i] : memref<6000xi27>
    }
    affine.for %i = 0 to 6000 {
      %0 = affine.load %p6000x27[5999 - %i] : memref<6000xi27>
      affine.store %0, %out_p6000x27[%i] : memref<6000xi27>
    }
    affine.for %i = 0 to 16384 {
      %0 = affine.load %in_p16384x18[%i] : memref<16384xi18>
      affine.store %0, %p16384x18[%i] : memref<16384xi18>
    }
    affine.for %i = 0 to 16384 {
      %0 = affine.load %p16384x18[16383 - %i] : memref<16384xi18>
      affine.store %0, %out_p16384x18[%i] : memref<16384xi18>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %in_p512x72[%i] : memref<512xi72>
      affine.store %0, %p512x72[%i] : memref<512xi72>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %p512x72[511 - %i] : memref<512xi72>
      affine.store %0, %out_p512x72[%i] : memref<512xi72>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %in_w512x72[%i] : memref<512xi72>
      affine.store %0, %w512x72[%i] : memref<512xi72>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %w512x72[%i] : memref<512xi72>
      %1 = affine.load %in_w512x72[511 - %i] : memref<512xi72>
      %2 = arith.addi %0, %1 : i72
      affine.store %2, %w512x72[%i] : memref<512xi72>
    }
    affine.for %i = 0 to 512 {
      %0 = affine.load %w512x72[511 - %i] : memref<512xi72>
      affine.store %0, %out_w512x72[%i] : memref<512xi72>
    }
    affine.for %i = 0 to 4096 {
      %0 = affine.load %in_p4096x9[%i] : memref<4096xi9>
      affine.store %0, %p4096x9[%i] : memref<4096xi9>
    }
    affine.for %i = 0 to 4096 {
      %0 = affine.load %p4096x9[4095 - %i] : memref<4096xi9>
      affine.store %0, %out_p4096x9[%i] : memref<4096xi9>
    }
    return
  }
}
