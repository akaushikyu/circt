// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_fii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA64_fii math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_fii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA64_fii math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.math_library.shared_library_modules=false -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N169. sin(double) in one arm of an if
// and cos(double) in the other, pow in both (positional_encoding form): Vitis
// leaves the loops sequential (sin / cos have loops), sin and cos are one
// sin_or_cos_double_s module and the two exclusive pow calls one
// pow_generic_double_s: 8 + 5 = 13 (kernel w9r22p_d3_sincos_branch). With
// shared_library_modules off sin and cos are two cores: 21.
// CHECK: Total BRAM: 13
// OFF: Total BRAM: 21
module {
  func.func @_Z3topPA64_fii(%arg0: memref<64x64xf32>, %arg1: i32, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c2 = arith.constant 2 : index
    %c0 = arith.constant 0 : index
    %c-1_i32 = arith.constant -1 : i32
    %cst = arith.constant 1.000000e+04 : f64
    %0 = arith.index_cast %arg1 : i32 to index
    %1 = arith.index_cast %arg2 : i32 to index
    %2 = arith.sitofp %arg2 : i32 to f32
    affine.for %arg3 = 0 to %0 {
      %3 = arith.index_cast %arg3 : index to i32
      %4 = arith.sitofp %3 : i32 to f64
      affine.for %arg4 = 0 to %1 {
        %5 = arith.index_cast %arg4 : index to i32
        %6 = arith.remsi %arg4, %c2 : index
        %7 = arith.cmpi slt, %6, %c0 : index
        %8 = arith.addi %6, %c2 : index
        %9 = arith.select %7, %8, %6 : index
        %10 = arith.cmpi eq, %9, %c0 : index
        scf.if %10 {
          %11 = arith.sitofp %5 : i32 to f32
          %12 = arith.divf %11, %2 : f32
          %13 = arith.extf %12 : f32 to f64
          %14 = math.powf %cst, %13 : f64
          %15 = arith.divf %4, %14 : f64
          %16 = math.sin %15 : f64
          %17 = arith.truncf %16 : f64 to f32
          affine.store %17, %arg0[%arg3, %arg4] : memref<64x64xf32>
        } else {
          %11 = arith.addi %5, %c-1_i32 : i32
          %12 = arith.sitofp %11 : i32 to f32
          %13 = arith.divf %12, %2 : f32
          %14 = arith.extf %13 : f32 to f64
          %15 = math.powf %cst, %14 : f64
          %16 = arith.divf %4, %15 : f64
          %17 = math.cos %16 : f64
          %18 = arith.truncf %17 : f64 to f32
          affine.store %18, %arg0[%arg3, %arg4] : memref<64x64xf32>
        }
      }
    }
    return
  }
}
