// RUN: hls-est %s --symbol-privatize=exclude=_Z6mc_topPKSt7complexIfEPS0_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mc_topPKSt7complexIfEPS0_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N60: the same fill of a local float table is evaluated at compile time: a ROM, no core.
// Kernel w9r7i_mc_flt_loc (~/hls-est-work/exp-src/w9r7i/mc_flt_loc.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 1 BRAM_18K.


// CHECK: Total BRAM: 1{{$}}

module {
  func.func @_Z6mc_topPKSt7complexIfEPS0_PKi(%arg0: memref<256x!llvm.struct<(struct<(f32, f32)>)>>, %arg1: memref<256x!llvm.struct<(struct<(f32, f32)>)>>, %arg2: memref<256xi32>) attributes {hls.orig_name = "mc_top", llvm.linkage = #llvm.linkage<external>} {
    %c8 = arith.constant 8 : index
    %cst = arith.constant -6.2831853071795862 : f64
    %c127_i32 = arith.constant 127 : i32
    %cst_0 = arith.constant 2.560000e+02 : f64
    %alloca = memref.alloca() : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "tw"} : memref<128xf32>
    affine.for %arg3 = 0 to 128 {
      %8 = arith.index_cast %arg3 : index to i32
      %9 = arith.sitofp %8 : i32 to f64
      %10 = arith.mulf %9, %cst : f64
      %11 = arith.divf %10, %cst_0 : f64
      %12 = math.cos %11 : f64
      %13 = arith.truncf %12 : f64 to f32
      affine.store %13, %alloca_1[%arg3] : memref<128xf32>
    }
    %alloca_2 = memref.alloca() : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %alloca_3 = memref.alloca() {polygeist.varname = "__r"} : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<256x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %1 = "polygeist.memref2pointer"(%alloca_3) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %2 = llvm.getelementptr %1[1] : (!llvm.ptr) -> !llvm.ptr, f32
    %3 = "polygeist.memref2pointer"(%alloca_2) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %4 = llvm.getelementptr %3[1] : (!llvm.ptr) -> !llvm.ptr, f32
    %5 = "polygeist.memref2pointer"(%arg1) : (memref<256x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %6 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %7 = llvm.getelementptr %6[1] : (!llvm.ptr) -> !llvm.ptr, f32
    affine.for %arg3 = 0 to 256 {
      %8 = affine.load %arg2[%arg3] : memref<256xi32>
      %9 = arith.andi %8, %c127_i32 : i32
      %10 = arith.index_cast %9 : i32 to index
      %11 = arith.muli %arg3, %c8 : index
      %12 = arith.index_cast %11 : index to i64
      %13 = llvm.getelementptr %0[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %14 = llvm.load %13 : !llvm.ptr -> f32
      llvm.store %14, %1 : f32, !llvm.ptr
      %15 = llvm.getelementptr %13[1] : (!llvm.ptr) -> !llvm.ptr, f32
      %16 = llvm.load %15 : !llvm.ptr -> f32
      llvm.store %16, %2 : f32, !llvm.ptr
      %17 = memref.load %alloca_1[%10] : memref<128xf32>
      %18 = llvm.load %1 : !llvm.ptr -> f32
      %19 = llvm.load %2 : !llvm.ptr -> f32
      %20 = arith.mulf %18, %17 : f32
      %21 = arith.mulf %19, %17 : f32
      llvm.store %20, %1 : f32, !llvm.ptr
      llvm.store %21, %2 : f32, !llvm.ptr
      %22 = llvm.load %1 : !llvm.ptr -> f32
      llvm.store %22, %3 : f32, !llvm.ptr
      %23 = llvm.load %2 : !llvm.ptr -> f32
      llvm.store %23, %4 : f32, !llvm.ptr
      %24 = affine.load %alloca_2[0] : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
      affine.store %24, %alloca[0] : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
      %25 = llvm.getelementptr %5[%12] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %26 = llvm.load %6 : !llvm.ptr -> f32
      %27 = llvm.load %7 : !llvm.ptr -> f32
      llvm.store %26, %25 : f32, !llvm.ptr
      %28 = llvm.getelementptr %25[1] : (!llvm.ptr) -> !llvm.ptr, f32
      llvm.store %27, %28 : f32, !llvm.ptr
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
