// RUN: hls-est %s --symbol-privatize=exclude=_Z6mc_topPKSt7complexIfEPS0_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mc_topPKSt7complexIfEPS0_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r7 (2026-10-20): VITIS_NOTES N60: a local complex<float> table filled from cos / sin of the loop index is computed at run time: one sin_or_cos core (16) + the table (2).
// Kernel w9r7i_mc_cplx_loc (~/hls-est-work/exp-src/w9r7i/mc_cplx_loc.cpp); MLIR from cgeist f02e8776 (Polygeist branch w9r7-cgeist) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 18 BRAM_18K.

// RUN: hls-est %s --symbol-privatize=exclude=_Z6mc_topPKSt7complexIfEPS0_PKi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6mc_topPKSt7complexIfEPS0_PKi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.math_library.local_struct_tables_at_run_time=false' -o /dev/null | FileCheck %s --check-prefix=N60OFF

// With tool.hls.math_library.local_struct_tables_at_run_time=false (N60OFF) the rule is off; the other W9r7 rules stay on.
// N60OFF: Total BRAM: 2{{$}}

// CHECK: Total BRAM: 18{{$}}

module {
  func.func @_Z6mc_topPKSt7complexIfEPS0_PKi(%arg0: memref<256x!llvm.struct<(struct<(f32, f32)>)>>, %arg1: memref<256x!llvm.struct<(struct<(f32, f32)>)>>, %arg2: memref<256xi32>) attributes {hls.orig_name = "mc_top", llvm.linkage = #llvm.linkage<external>} {
    %c8 = arith.constant 8 : index
    %cst = arith.constant -6.2831853071795862 : f64
    %c127_i32 = arith.constant 127 : i32
    %cst_0 = arith.constant 2.560000e+02 : f64
    %cst_1 = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %alloca_2 = memref.alloca() : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %alloca_3 = memref.alloca() : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %alloca_4 = memref.alloca() {polygeist.varname = "t"} : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %alloca_5 = memref.alloca() {hls.preserve, polygeist.varname = "tw"} : memref<128x!llvm.struct<(struct<(f32, f32)>)>>
    %0 = "polygeist.memref2pointer"(%alloca_5) : (memref<128x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 128 {
      %17 = arith.muli %arg3, %c8 : index
      %18 = arith.index_cast %17 : index to i64
      %19 = llvm.getelementptr %0[%18] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      llvm.store %cst_1, %19 : f32, !llvm.ptr
      %20 = llvm.getelementptr %19[1] : (!llvm.ptr) -> !llvm.ptr, f32
      llvm.store %cst_1, %20 : f32, !llvm.ptr
    }
    %1 = "polygeist.memref2pointer"(%alloca_4) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %2 = llvm.getelementptr %1[1] : (!llvm.ptr) -> !llvm.ptr, f32
    %3 = "polygeist.memref2pointer"(%alloca_3) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %4 = llvm.getelementptr %3[1] : (!llvm.ptr) -> !llvm.ptr, f32
    %5 = "polygeist.memref2pointer"(%alloca_5) : (memref<128x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %6 = "polygeist.memref2pointer"(%alloca_2) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %7 = llvm.getelementptr %6[1] : (!llvm.ptr) -> !llvm.ptr, f32
    affine.for %arg3 = 0 to 128 {
      %17 = arith.index_cast %arg3 : index to i32
      %18 = arith.sitofp %17 : i32 to f64
      %19 = arith.mulf %18, %cst : f64
      %20 = arith.divf %19, %cst_0 : f64
      %21 = math.cos %20 : f64
      %22 = arith.truncf %21 : f64 to f32
      %23 = math.sin %20 : f64
      %24 = arith.truncf %23 : f64 to f32
      llvm.store %22, %1 : f32, !llvm.ptr
      llvm.store %24, %2 : f32, !llvm.ptr
      %25 = llvm.load %1 : !llvm.ptr -> f32
      llvm.store %25, %3 : f32, !llvm.ptr
      %26 = llvm.load %2 : !llvm.ptr -> f32
      llvm.store %26, %4 : f32, !llvm.ptr
      %27 = affine.load %alloca_3[0] : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
      affine.store %27, %alloca_2[0] : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
      %28 = arith.muli %arg3, %c8 : index
      %29 = arith.index_cast %28 : index to i64
      %30 = llvm.getelementptr %5[%29] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %31 = llvm.load %6 : !llvm.ptr -> f32
      %32 = llvm.load %7 : !llvm.ptr -> f32
      llvm.store %31, %30 : f32, !llvm.ptr
      %33 = llvm.getelementptr %30[1] : (!llvm.ptr) -> !llvm.ptr, f32
      llvm.store %32, %33 : f32, !llvm.ptr
    }
    %alloca_6 = memref.alloca() : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %alloca_7 = memref.alloca() {polygeist.varname = "__r"} : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
    %8 = "polygeist.memref2pointer"(%arg0) : (memref<256x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %9 = "polygeist.memref2pointer"(%alloca_7) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %10 = llvm.getelementptr %9[1] : (!llvm.ptr) -> !llvm.ptr, f32
    %11 = "polygeist.memref2pointer"(%alloca_5) : (memref<128x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %12 = "polygeist.memref2pointer"(%alloca_6) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %13 = llvm.getelementptr %12[1] : (!llvm.ptr) -> !llvm.ptr, f32
    %14 = "polygeist.memref2pointer"(%arg1) : (memref<256x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %15 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(struct<(f32, f32)>)>>) -> !llvm.ptr
    %16 = llvm.getelementptr %15[1] : (!llvm.ptr) -> !llvm.ptr, f32
    affine.for %arg3 = 0 to 256 {
      %17 = affine.load %arg2[%arg3] : memref<256xi32>
      %18 = arith.andi %17, %c127_i32 : i32
      %19 = arith.index_cast %18 : i32 to index
      %20 = arith.muli %arg3, %c8 : index
      %21 = arith.index_cast %20 : index to i64
      %22 = llvm.getelementptr %8[%21] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %23 = llvm.load %22 : !llvm.ptr -> f32
      llvm.store %23, %9 : f32, !llvm.ptr
      %24 = llvm.getelementptr %22[1] : (!llvm.ptr) -> !llvm.ptr, f32
      %25 = llvm.load %24 : !llvm.ptr -> f32
      llvm.store %25, %10 : f32, !llvm.ptr
      %26 = arith.muli %19, %c8 : index
      %27 = arith.index_cast %26 : index to i64
      %28 = llvm.getelementptr %11[%27] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %29 = llvm.load %28 : !llvm.ptr -> f32
      %30 = llvm.getelementptr %28[1] : (!llvm.ptr) -> !llvm.ptr, f32
      %31 = llvm.load %30 : !llvm.ptr -> f32
      %32 = llvm.load %9 : !llvm.ptr -> f32
      %33 = llvm.load %10 : !llvm.ptr -> f32
      %34 = arith.mulf %32, %29 : f32
      %35 = arith.mulf %33, %31 : f32
      %36 = arith.subf %34, %35 : f32
      %37 = arith.mulf %32, %31 : f32
      %38 = arith.mulf %33, %29 : f32
      %39 = arith.addf %37, %38 : f32
      llvm.store %36, %9 : f32, !llvm.ptr
      llvm.store %39, %10 : f32, !llvm.ptr
      %40 = llvm.load %9 : !llvm.ptr -> f32
      llvm.store %40, %12 : f32, !llvm.ptr
      %41 = llvm.load %10 : !llvm.ptr -> f32
      llvm.store %41, %13 : f32, !llvm.ptr
      %42 = affine.load %alloca_6[0] : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
      affine.store %42, %alloca[0] : memref<1x!llvm.struct<(struct<(f32, f32)>)>>
      %43 = llvm.getelementptr %14[%21] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %44 = llvm.load %15 : !llvm.ptr -> f32
      %45 = llvm.load %16 : !llvm.ptr -> f32
      llvm.store %44, %43 : f32, !llvm.ptr
      %46 = llvm.getelementptr %43[1] : (!llvm.ptr) -> !llvm.ptr, f32
      llvm.store %45, %46 : f32, !llvm.ptr
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
