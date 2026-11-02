// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfPKiPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfPKiPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfPKiPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfPKiPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.memory_architecture.replication.select_of_loads_reload=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 22 review fix (D7): `c[k] > 0 ? t[i][j] : t[i+1][j]` (an if with one
// load per arm, the values used by nothing else) is one load of the selected
// address: 3 reads, 2 copies, 64 (kernel w9r22rv_k02_condsel, Vitis 64; round
// 22: 96).
// CHECK: Total BRAM: 64
// OFF: Total BRAM: 96
module {
  func.func @_Z3topPKfPKiPf(%arg0: memref<16384xf32>, %arg1: memref<4096xi32>, %arg2: memref<4096xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c64 = arith.constant 64 : index
    %c-1 = arith.constant -1 : index
    %c2 = arith.constant 2 : index
    %c0 = arith.constant 0 : index
    %c1_i32 = arith.constant 1 : i32
    %cst = arith.constant 5.000000e-01 : f32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "t"} : memref<128x128xf32>
    affine.for %arg3 = 0 to 128 {
      affine.for %arg4 = 0 to 128 {
        %0 = affine.load %arg0[%arg4 + %arg3 * 128] : memref<16384xf32>
        %1 = arith.mulf %0, %cst : f32
        affine.store %1, %alloca[%arg3, %arg4] : memref<128x128xf32>
      }
    }
    affine.for %arg3 = 0 to 128 step 2 {
      %0 = arith.index_cast %arg3 : index to i32
      %1 = "polygeist.subindex"(%alloca, %arg3) : (memref<128x128xf32>, index) -> memref<128xf32>
      %2 = arith.addi %0, %c1_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      %4 = "polygeist.subindex"(%alloca, %3) : (memref<128x128xf32>, index) -> memref<128xf32>
      %5 = arith.cmpi slt, %arg3, %c0 : index
      %6 = arith.subi %c-1, %arg3 : index
      %7 = arith.select %5, %6, %arg3 : index
      %8 = arith.divsi %7, %c2 : index
      %9 = arith.subi %c-1, %8 : index
      %10 = arith.select %5, %9, %8 : index
      %11 = arith.muli %10, %c64 : index
      affine.for %arg4 = 0 to 128 step 2 {
        %12 = arith.cmpi slt, %arg4, %c0 : index
        %13 = arith.subi %c-1, %arg4 : index
        %14 = arith.select %12, %13, %arg4 : index
        %15 = arith.divsi %14, %c2 : index
        %16 = arith.subi %c-1, %15 : index
        %17 = arith.select %12, %16, %15 : index
        %18 = arith.addi %17, %11 : index
        %19 = memref.load %arg1[%18] : memref<4096xi32>
        %20 = arith.cmpi sgt, %19, %c0_i32 : i32
        %21 = scf.if %20 -> (memref<?xf32>) {
          %27 = "polygeist.subindex"(%1, %arg4) : (memref<128xf32>, index) -> memref<?xf32>
          scf.yield %27 : memref<?xf32>
        } else {
          %27 = "polygeist.subindex"(%4, %arg4) : (memref<128xf32>, index) -> memref<?xf32>
          scf.yield %27 : memref<?xf32>
        }
        %22 = affine.load %21[0] : memref<?xf32>
        %23 = affine.load %alloca[%arg3, %arg4 + 1] : memref<128x128xf32>
        %24 = arith.addf %22, %23 : f32
        %25 = affine.load %alloca[%arg3 + 1, %arg4 + 1] : memref<128x128xf32>
        %26 = arith.addf %24, %25 : f32
        memref.store %26, %arg2[%18] : memref<4096xf32>
      }
    }
    return
  }
}
