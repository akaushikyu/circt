// RUN: hls-est %s --symbol-privatize=exclude=top --symbol-dce --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top --bram-debug -o /dev/null 2>&1 | FileCheck %s

// O72 review D1, kernel o72r_bank: `for (j < 2) { c = n[j]; for (i < c) { t
// = a[i & 1023]; for (k < 16) res[i & 63][k] = t * (k + 3); } }`, res
// partitioned completely on dim 2. Vitis (td=off): i pipelined at II 1, k
// unrolled, 16 banks x 1 = 16. The unrolled stores of the runtime-trip loop
// are memref.store ops indexed by `affine.apply #map(%cK)`;
// --memory-banking-bram evaluates such an index to its constant (bank K),
// so every store writes one bank and no bank sees a store_enable. Before the
// fix each bank took 16 store_enables (II 8, RAM_T2P 2 each: 32).

// CHECK-NOT: store_enable
// CHECK:     in @top: ii=1 source=auto flattened_parents=0
// CHECK:     Total BRAM: 16
// CHECK-COUNT-16: 64x32b -> RAM_1P (x36/port) = 1 BRAM_18K

module {
  func.func @top(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: memref<2xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c3_i32 = arith.constant 3 : i32
    %c63_i32 = arith.constant 63 : i32
    %c1023_i32 = arith.constant 1023 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "res"}], hls.preserve, polygeist.varname = "res"} : memref<64x16xi32>
    affine.for %arg3 = 0 to 2 {
      %0 = affine.load %arg2[%arg3] : memref<2xi32>
      %1 = arith.index_cast %0 : i32 to index
      scf.for %arg4 = %c0 to %1 step %c1 {
        %2 = arith.index_cast %arg4 : index to i32
        %3 = arith.andi %2, %c1023_i32 : i32
        %4 = arith.index_cast %3 : i32 to index
        %5 = memref.load %arg0[%4] : memref<1024xi32>
        %6 = arith.andi %2, %c63_i32 : i32
        %7 = arith.index_cast %6 : i32 to index
        affine.for %arg5 = 0 to 16 {
          %8 = arith.index_cast %arg5 : index to i32
          %9 = arith.addi %8, %c3_i32 : i32
          %10 = arith.muli %5, %9 : i32
          memref.store %10, %alloca[%7, %arg5] : memref<64x16xi32>
        }
      }
    }
    affine.for %arg3 = 0 to 64 {
      affine.for %arg4 = 0 to 16 {
        %0 = affine.load %alloca[%arg3, %arg4] : memref<64x16xi32>
        affine.store %0, %arg1[%arg4 + %arg3 * 16] : memref<1024xi32>
      }
    }
    return
  }
}
