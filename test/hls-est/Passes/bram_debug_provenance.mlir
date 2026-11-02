// RUN: hls-est %s --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > /dev/null 2> %t.err
// RUN: FileCheck %s --input-file=%t.err

// The `hls.partition` provenance that memory banking stamps on each bank
// records what banking actually applied, not the pragma text, and every bank
// carries an `hls.bank_of` so the report can add the banks of one array up:
//
//   a  `complete` with no factor/dim  -> factor = dimension extent (4), dim 1
//   d  Vitis `dim = 0` (all dims)     -> every dimension split (VITIS_NOTES
//      N24, w7_dim0c: cyclic 2 dim 0 of int[8][64] = 4 banks): 2 x 2 banks,
//      the first split dimension in kind/factor/dim, all of them in dims=[...]
//   %u no polygeist.varname, has loc  -> bank_of "<unnamed@p.cpp:3:3>"
//   %v no polygeist.varname, no loc   -> bank_of "<unnamed#3>" (its position
//      among the function's storage declarations: a, d, u come before it)

module {
  func.func @kernel(%arg0: memref<4x512xi32>, %arg1: memref<4x512xi32>, %arg2: memref<2048xi32>, %arg3: memref<2048xi32>) {
    %a = memref.alloca() {hls.array_partition = [{kind = "complete"}], polygeist.varname = "a"} : memref<4x512xi32> loc("p.cpp":1:3)
    %d = memref.alloca() {hls.array_partition = [{dim = 0 : i32, factor = 2 : i32, kind = "cyclic"}], polygeist.varname = "d"} : memref<4x512xi32> loc("p.cpp":2:3)
    %u = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}]} : memref<2048xi32> loc("p.cpp":3:3)
    %v = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}]} : memref<2048xi32> loc(unknown)
    affine.for %i = 0 to 4 {
      affine.for %j = 0 to 512 {
        %0 = affine.load %arg0[%i, %j] : memref<4x512xi32>
        affine.store %0, %a[%i, %j] : memref<4x512xi32>
        affine.store %0, %d[%i, %j] : memref<4x512xi32>
      }
    }
    affine.for %i = 0 to 2048 {
      %0 = affine.load %arg2[%i] : memref<2048xi32>
      affine.store %0, %u[%i] : memref<2048xi32>
      affine.store %0, %v[%i] : memref<2048xi32>
    }
    affine.for %i = 0 to 4 {
      affine.for %j = 0 to 512 {
        %0 = affine.load %a[%i, %j] : memref<4x512xi32>
        %1 = affine.load %d[%i, %j] : memref<4x512xi32>
        %2 = arith.addi %0, %1 : i32
        affine.store %2, %arg1[%i, %j] : memref<4x512xi32>
      }
    }
    affine.for %i = 0 to 1024 {
      %0 = affine.load %u[%i * 2] : memref<2048xi32>
      %1 = affine.load %u[%i * 2 + 1] : memref<2048xi32>
      %2 = affine.load %v[%i * 2] : memref<2048xi32>
      %3 = affine.load %v[%i * 2 + 1] : memref<2048xi32>
      %4 = arith.addi %0, %1 : i32
      %5 = arith.addi %2, %3 : i32
      %6 = arith.addi %4, %5 : i32
      affine.store %6, %arg3[%i] : memref<2048xi32>
    }
    return
  }
}

// CHECK: === bram-debug: how each BRAM number was derived ===

// CHECK:      ] a[bank 0/4] (alloca) @ p.cpp:1:3
// CHECK:        partition: complete factor=4 dim=1 source=pragma (bank 0 of 4)
// CHECK:      ] a[bank 3/4] (alloca) @ p.cpp:1:3
// CHECK:        partition: complete factor=4 dim=1 source=pragma (bank 3 of 4)

// CHECK:      ] d[bank 0/4] (alloca) @ p.cpp:2:3
// CHECK:        partition: cyclic factor=2 dim=1 source=pragma dims=[cyclic 2 on dim 1, cyclic 2 on dim 2] (bank 0 of 4)
// CHECK:      ] d[bank 3/4] (alloca) @ p.cpp:2:3
// CHECK:        partition: cyclic factor=2 dim=1 source=pragma dims=[cyclic 2 on dim 1, cyclic 2 on dim 2] (bank 3 of 4)

// CHECK:      ] <unnamed@p.cpp:3:3>[bank 0/2] (alloca) @ p.cpp:3:3
// CHECK:        partition: cyclic factor=2 dim=1 source=pragma (bank 0 of 2)
// CHECK:      ] <unnamed@p.cpp:3:3>[bank 1/2] (alloca) @ p.cpp:3:3

// CHECK:      ] <unnamed#3>[bank 0/2] (alloca) @ <unknown>
// CHECK:        partition: cyclic factor=2 dim=1 source=pragma (bank 0 of 2)
// CHECK:      ] <unnamed#3>[bank 1/2] (alloca) @ <unknown>

// CHECK:      --- summary (sorted by BRAM) ---
