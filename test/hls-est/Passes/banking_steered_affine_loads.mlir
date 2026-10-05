// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=steer --bram-debug-json=%t.json -o /dev/null | FileCheck %s
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll "--memory-banking-bram=steer-affine-loads=false" --convert-affine-to-loopschedule --bram-analysis=top=steer --bram-debug-json=%t.off.json -o /dev/null
// RUN: FileCheck %s --input-file=%t.off.json --check-prefix=OFF

// Unrolled affine.load copies of an array partitioned completely on the
// dimension they index as `j + kw` (j the unrolled constant, kw a runtime
// loop counter) address a different bank each, as the memref.load copies of
// banking_steered_loads.mlir do: each bank is read once per iteration, not
// once per copy (Vitis 2025.1 td=off, DSC_Acceleration optimized:
// conv_in_buf, complete on dim 3, read 16 times per iteration by `X[c][ki][j
// * s + kw]`, 34 banks ram_2p of 2 BRAM_18K = 68). Here X[64][16] complete on
// dim 2 (16 banks of 64 words), 8 copies per iteration of the pipelined loop.
// Each bank: one read at II 1, a 1-port RAM of 1 BRAM_18K (16); with the
// copies rewritten one by one each bank looks read 8 times per iteration and
// is replicated 7 times (14 each, 224).

// W9r21 (VITIS_NOTES N157, tool.hls.partitioning.drop_unread_banks): j + kw
// reaches columns 0 .. 14 only, so bank 15 (written, never read) is removed.
// CHECK-COUNT-15: 64x32b -> RAM_1P (x36/port) = 1 BRAM_18K
// CHECK: Total BRAM: 15
// JSON: "reads": 1,
// JSON-NOT: "reads": 8,
// OFF: "reads": 8,

func.func @steer(%in: memref<64x16xi32>, %out: memref<8x64xi32>) {
  %zero = arith.constant 0 : i32
  %X = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 0 : i32, kind = "complete", variable = "X"}], hls.preserve, polygeist.varname = "X"} : memref<64x16xi32>
  affine.for %c = 0 to 64 {
    affine.for %w = 0 to 16 {
      %v = affine.load %in[%c, %w] : memref<64x16xi32>
      affine.store %v, %X[%c, %w] : memref<64x16xi32>
    }
  }
  affine.for %kw = 0 to 8 {
    affine.for %c = 0 to 64 {
      %s = affine.for %j = 0 to 8 iter_args(%acc = %zero) -> (i32) {
        %v = affine.load %X[%c, %j + %kw] : memref<64x16xi32>
        %n = arith.addi %acc, %v : i32
        affine.yield %n : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %s, %out[%kw, %c] : memref<8x64xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
  }
  return
}
