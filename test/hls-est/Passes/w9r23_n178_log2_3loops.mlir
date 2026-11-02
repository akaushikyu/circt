// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiS0_S0_iPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKiS0_S0_iPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKiS0_S0_iPf --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKiS0_S0_iPf math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.math_library.sequential_core_sharing=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r23-impl (2026-10-28): VITIS_NOTES N178. Kernel w9r23p_m4_log2_3loops (~/hls-est-work/exp-src/w9r23p/m4_log2_3loops.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 21 BRAM (one log2 core).
// log2(double) in three sequential pipelined loops of one function: one shared core. Off: 63.
// CHECK: Total BRAM: 21{{$}}
// OFF: Total BRAM: 63{{$}}
module {
  func.func @_Z3topPKiS0_S0_iPf(%arg0: memref<1024xi32>, %arg1: memref<1024xi32>, %arg2: memref<1024xi32>, %arg3: i32, %arg4: memref<3xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant 0.000000e+00 : f32
    %0 = arith.sitofp %arg3 : i32 to f32
    %1 = affine.for %arg5 = 0 to 1024 iter_args(%arg6 = %cst) -> (f32) {
      %4 = affine.load %arg0[%arg5] : memref<1024xi32>
      %5 = arith.cmpi sgt, %4, %c0_i32 : i32
      %6 = scf.if %5 -> (f32) {
        %7 = affine.load %arg0[%arg5] : memref<1024xi32>
        %8 = arith.sitofp %7 : i32 to f32
        %9 = arith.divf %8, %0 : f32
        %10 = arith.extf %9 : f32 to f64
        %11 = func.call @log2(%10) : (f64) -> f64
        %12 = arith.mulf %10, %11 : f64
        %13 = arith.extf %arg6 : f32 to f64
        %14 = arith.subf %13, %12 : f64
        %15 = arith.truncf %14 : f64 to f32
        scf.yield %15 : f32
      } else {
        scf.yield %arg6 : f32
      }
      affine.yield %6 : f32
    }
    %2 = affine.for %arg5 = 0 to 1024 iter_args(%arg6 = %cst) -> (f32) {
      %4 = affine.load %arg1[%arg5] : memref<1024xi32>
      %5 = arith.cmpi sgt, %4, %c0_i32 : i32
      %6 = scf.if %5 -> (f32) {
        %7 = affine.load %arg1[%arg5] : memref<1024xi32>
        %8 = arith.sitofp %7 : i32 to f32
        %9 = arith.divf %8, %0 : f32
        %10 = arith.extf %9 : f32 to f64
        %11 = func.call @log2(%10) : (f64) -> f64
        %12 = arith.mulf %10, %11 : f64
        %13 = arith.extf %arg6 : f32 to f64
        %14 = arith.subf %13, %12 : f64
        %15 = arith.truncf %14 : f64 to f32
        scf.yield %15 : f32
      } else {
        scf.yield %arg6 : f32
      }
      affine.yield %6 : f32
    }
    %3 = affine.for %arg5 = 0 to 1024 iter_args(%arg6 = %cst) -> (f32) {
      %4 = affine.load %arg2[%arg5] : memref<1024xi32>
      %5 = arith.cmpi sgt, %4, %c0_i32 : i32
      %6 = scf.if %5 -> (f32) {
        %7 = affine.load %arg2[%arg5] : memref<1024xi32>
        %8 = arith.sitofp %7 : i32 to f32
        %9 = arith.divf %8, %0 : f32
        %10 = arith.extf %9 : f32 to f64
        %11 = func.call @log2(%10) : (f64) -> f64
        %12 = arith.mulf %10, %11 : f64
        %13 = arith.extf %arg6 : f32 to f64
        %14 = arith.subf %13, %12 : f64
        %15 = arith.truncf %14 : f64 to f32
        scf.yield %15 : f32
      } else {
        scf.yield %arg6 : f32
      }
      affine.yield %6 : f32
    }
    affine.store %1, %arg4[0] : memref<3xf32>
    affine.store %2, %arg4[1] : memref<3xf32>
    affine.store %3, %arg4[2] : memref<3xf32>
    return
  }
  func.func private @log2(f64) -> f64 attributes {hls.orig_name = "log2", llvm.linkage = #llvm.linkage<external>}
}
