// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKfPKiPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKfPKiPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 22 review fix (D7), control: one arm value is also used elsewhere,
// both loads stay: 4 reads, 3 copies, 96 (kernel w9r22fx_f6_condsel_used,
// Vitis 96).
// CHECK: Total BRAM: 96
module {
  func.func @_Z3topPKfPKiPf(%arg0: memref<16384xf32>, %arg1: memref<4096xi32>, %arg2: memref<4096xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c64 = arith.constant 64 : index
    %c-1 = arith.constant -1 : index
    %c2 = arith.constant 2 : index
    %c0 = arith.constant 0 : index
    %c1_i32 = arith.constant 1 : i32
    %cst = arith.constant 5.000000e-01 : f32
    %c0_i32 = arith.constant 0 : i32
    %0 = llvm.mlir.undef : f32
    %alloca = memref.alloca() {polygeist.varname = "x"} : memref<1xf32>
    %cast = memref.cast %alloca : memref<1xf32> to memref<?xf32>
    affine.store %0, %alloca[0] : memref<1xf32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "t"} : memref<128x128xf32>
    affine.for %arg3 = 0 to 128 {
      affine.for %arg4 = 0 to 128 {
        %1 = affine.load %arg0[%arg4 + %arg3 * 128] : memref<16384xf32>
        %2 = arith.mulf %1, %cst : f32
        affine.store %2, %alloca_0[%arg3, %arg4] : memref<128x128xf32>
      }
    }
    affine.for %arg3 = 0 to 128 step 2 {
      %1 = arith.index_cast %arg3 : index to i32
      %2 = arith.addi %1, %c1_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      %4 = "polygeist.subindex"(%alloca_0, %3) : (memref<128x128xf32>, index) -> memref<128xf32>
      %5 = arith.cmpi slt, %arg3, %c0 : index
      %6 = arith.subi %c-1, %arg3 : index
      %7 = arith.select %5, %6, %arg3 : index
      %8 = arith.divsi %7, %c2 : index
      %9 = arith.subi %c-1, %8 : index
      %10 = arith.select %5, %9, %8 : index
      %11 = arith.muli %10, %c64 : index
      affine.for %arg4 = 0 to 128 step 2 {
        %12 = affine.load %alloca_0[%arg3, %arg4] : memref<128x128xf32>
        affine.store %12, %alloca[0] : memref<1xf32>
        %13 = arith.cmpi slt, %arg4, %c0 : index
        %14 = arith.subi %c-1, %arg4 : index
        %15 = arith.select %13, %14, %arg4 : index
        %16 = arith.divsi %15, %c2 : index
        %17 = arith.subi %c-1, %16 : index
        %18 = arith.select %13, %17, %16 : index
        %19 = arith.addi %18, %11 : index
        %20 = memref.load %arg1[%19] : memref<4096xi32>
        %21 = arith.cmpi sgt, %20, %c0_i32 : i32
        %22 = scf.if %21 -> (memref<?xf32>) {
          scf.yield %cast : memref<?xf32>
        } else {
          %29 = "polygeist.subindex"(%4, %arg4) : (memref<128xf32>, index) -> memref<?xf32>
          scf.yield %29 : memref<?xf32>
        }
        %23 = affine.load %22[0] : memref<?xf32>
        %24 = affine.load %alloca_0[%arg3, %arg4 + 1] : memref<128x128xf32>
        %25 = arith.mulf %24, %12 : f32
        %26 = arith.addf %23, %25 : f32
        %27 = affine.load %alloca_0[%arg3 + 1, %arg4 + 1] : memref<128x128xf32>
        %28 = arith.addf %26, %27 : f32
        memref.store %28, %arg2[%19] : memref<4096xf32>
      }
    }
    return
  }
}
