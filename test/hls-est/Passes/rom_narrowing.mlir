// RUN: hls-est %s --mark-constant-fills --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug 2>%t.err | FileCheck %s
// RUN: FileCheck %s --check-prefix=DBG --input-file=%t.err

// ROMs (VITIS_NOTES.md N26): an array written only with constants is a ROM of
// those constants; a ROM's element width comes from its values.
//   @fill300   buf[i] = 300 for 4096 x i32, read through a runtime index:
//              300 needs 9 bits (w7_rf9u: 4096x9 ROM_AUTO_1R, 2 BRAM).
//   @tbl       a constant table of 4096 x i32 holding 6: 2 bits (6 = 110b
//              read as signed in 3 bits is -2; w7_rf6: 4096x2, 1 BRAM).
//   @zeros     every write stores 0: no memory (N1a).

// CHECK-DAG: kind=ROM_1P  bram=2
// CHECK-DAG: kind=ROM_1P  bram=1
// CHECK-DAG: kind=ROM_1P  bram=0
// CHECK: Total BRAM: 3

// DBG-DAG: every write stores a constant (ROM of those values, N26); element width 9 of 32 bits from its values (N26)
// DBG-DAG: element width 2 of 32 bits from its values (N26)
// DBG-DAG: status: zero_rom

memref.global "private" @tbl : memref<4096xi32> = dense<6>

func.func @kernel(%idx: memref<1024xi32>, %out: memref<1024xi32>, %out2: memref<1024xi32>, %out3: memref<1024xi32>) {
  %buf = memref.alloca() {polygeist.varname = "fill300"} : memref<4096xi32>
  %z = memref.alloca() {polygeist.varname = "zeros"} : memref<4096xi32>
  %c300 = arith.constant 300 : i32
  %c0 = arith.constant 0 : i32
  %c4095 = arith.constant 4095 : i32
  affine.for %i = 0 to 4096 {
    affine.store %c300, %buf[%i] : memref<4096xi32>
    affine.store %c0, %z[%i] : memref<4096xi32>
  }
  %t = memref.get_global @tbl : memref<4096xi32>
  affine.for %i = 0 to 1024 {
    %x = affine.load %idx[%i] : memref<1024xi32>
    %m = arith.andi %x, %c4095 : i32
    %j = arith.index_cast %m : i32 to index
    %v = memref.load %buf[%j] : memref<4096xi32>
    affine.store %v, %out[%i] : memref<1024xi32>
    %w = memref.load %z[%j] : memref<4096xi32>
    affine.store %w, %out2[%i] : memref<1024xi32>
    %u = memref.load %t[%j] : memref<4096xi32>
    affine.store %u, %out3[%i] : memref<1024xi32>
  }
  return
}
