// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_KhPA8_A8_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA64_KhPA8_A8_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA64_KhPA8_A8_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA64_KhPA8_A8_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.pipeline_decision.library_calls_with_loops=[] -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N169. The jpeg dct form: dct_1d's
// 8 x 8 nest calls cos(double) (math.cos), dct_2d calls it per row and per
// column. sin_or_cos_double has loops of its own, so Vitis pipelines and
// unrolls none of the loops around the calls; every call is sequential and
// shares one sin_or_cos_double_s (8) with block, temp, dct 1 each: 11 (kernel
// w9r22p_d11_jpeg_dct). With the key empty the nests were unrolled into
// pipelines: 64 instances (512) and block RAM_1WNR 7 copies, 530.
// CHECK: Total BRAM: 11
// OFF: Total BRAM: 530
module {
  func.func @_Z3topPA64_KhPA8_A8_f(%arg0: memref<64x64xi8>, %arg1: memref<64x8x8xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c-1 = arith.constant -1 : index
    %c8 = arith.constant 8 : index
    %c0 = arith.constant 0 : index
    %cst = arith.constant 1.280000e+02 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "dct"} : memref<8x8xf32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "block"} : memref<8x8xf32>
    affine.for %arg2 = 0 to 64 step 8 {
      %0 = arith.cmpi slt, %arg2, %c0 : index
      %1 = arith.subi %c-1, %arg2 : index
      %2 = arith.select %0, %1, %arg2 : index
      %3 = arith.divsi %2, %c8 : index
      %4 = arith.subi %c-1, %3 : index
      %5 = arith.select %0, %4, %3 : index
      %6 = arith.muli %5, %c8 : index
      affine.for %arg3 = 0 to 64 step 8 {
        affine.for %arg4 = 0 to 8 {
          affine.for %arg5 = 0 to 8 {
            %14 = affine.load %arg0[%arg2 + %arg4, %arg3 + %arg5] : memref<64x64xi8>
            %15 = arith.extui %14 : i8 to i32
            %16 = arith.sitofp %15 : i32 to f64
            %17 = arith.subf %16, %cst : f64
            %18 = arith.truncf %17 : f64 to f32
            affine.store %18, %alloca_0[%arg4, %arg5] : memref<8x8xf32>
          }
        }
        func.call @_ZL6dct_2dPA8_fS0_(%alloca_0, %alloca) {hls.inline_auto_off = {calls = 1 : i64, size = 106 : i64}} : (memref<8x8xf32>, memref<8x8xf32>) -> ()
        %7 = arith.cmpi slt, %arg3, %c0 : index
        %8 = arith.subi %c-1, %arg3 : index
        %9 = arith.select %7, %8, %arg3 : index
        %10 = arith.divsi %9, %c8 : index
        %11 = arith.subi %c-1, %10 : index
        %12 = arith.select %7, %11, %10 : index
        %13 = arith.addi %12, %6 : index
        affine.for %arg4 = 0 to 8 {
          affine.for %arg5 = 0 to 8 {
            %14 = affine.load %alloca[%arg4, %arg5] : memref<8x8xf32>
            memref.store %14, %arg1[%13, %arg4, %arg5] : memref<64x8x8xf32>
          }
        }
      }
    }
    return
  }
  func.func private @_ZL6dct_2dPA8_fS0_(%arg0: memref<8x8xf32>, %arg1: memref<8x8xf32>) attributes {hls.inline_auto_off = {size = 106 : i64}, hls.orig_name = "dct_2d", llvm.linkage = #llvm.linkage<internal>} {
    %c0_i32 = arith.constant 0 : i32
    %cst = arith.constant 0.000000e+00 : f32
    %cst_0 = arith.constant 5.000000e-01 : f64
    %cst_1 = arith.constant 0.35355339059327379 : f64
    %cst_2 = arith.constant 0.39269909262657166 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "col_out"} : memref<8xf32>
    %alloca_3 = memref.alloca() {hls.preserve, polygeist.varname = "col"} : memref<8xf32>
    %alloca_4 = memref.alloca() {hls.preserve, polygeist.varname = "temp"} : memref<8x8xf32>
    affine.for %arg2 = 0 to 8 {
      affine.for %arg3 = 0 to 8 {
        %0 = arith.index_cast %arg3 : index to i32
        %1 = arith.sitofp %0 : i32 to f64
        %2 = affine.for %arg4 = 0 to 8 iter_args(%arg5 = %cst) -> (f32) {
          %8 = arith.index_cast %arg4 : index to i32
          %9 = affine.load %arg0[%arg2, %arg4] : memref<8x8xf32>
          %10 = arith.extf %9 : f32 to f64
          %11 = arith.sitofp %8 : i32 to f64
          %12 = arith.addf %11, %cst_0 : f64
          %13 = arith.mulf %12, %cst_2 : f64
          %14 = arith.mulf %13, %1 : f64
          %15 = math.cos %14 : f64
          %16 = arith.mulf %10, %15 : f64
          %17 = arith.extf %arg5 : f32 to f64
          %18 = arith.addf %17, %16 : f64
          %19 = arith.truncf %18 : f64 to f32
          affine.yield %19 : f32
        }
        %3 = arith.extf %2 : f32 to f64
        %4 = arith.cmpi eq, %0, %c0_i32 : i32
        %5 = arith.select %4, %cst_1, %cst_0 : f64
        %6 = arith.mulf %3, %5 : f64
        %7 = arith.truncf %6 : f64 to f32
        affine.store %7, %alloca_4[%arg2, %arg3] : memref<8x8xf32>
      }
    }
    affine.for %arg2 = 0 to 8 {
      affine.for %arg3 = 0 to 8 {
        %0 = affine.load %alloca_4[%arg3, %arg2] : memref<8x8xf32>
        affine.store %0, %alloca_3[%arg3] : memref<8xf32>
      }
      affine.for %arg3 = 0 to 8 {
        %0 = arith.index_cast %arg3 : index to i32
        %1 = arith.sitofp %0 : i32 to f64
        %2 = affine.for %arg4 = 0 to 8 iter_args(%arg5 = %cst) -> (f32) {
          %8 = arith.index_cast %arg4 : index to i32
          %9 = affine.load %alloca_3[%arg4] : memref<8xf32>
          %10 = arith.extf %9 : f32 to f64
          %11 = arith.sitofp %8 : i32 to f64
          %12 = arith.addf %11, %cst_0 : f64
          %13 = arith.mulf %12, %cst_2 : f64
          %14 = arith.mulf %13, %1 : f64
          %15 = math.cos %14 : f64
          %16 = arith.mulf %10, %15 : f64
          %17 = arith.extf %arg5 : f32 to f64
          %18 = arith.addf %17, %16 : f64
          %19 = arith.truncf %18 : f64 to f32
          affine.yield %19 : f32
        }
        %3 = arith.extf %2 : f32 to f64
        %4 = arith.cmpi eq, %0, %c0_i32 : i32
        %5 = arith.select %4, %cst_1, %cst_0 : f64
        %6 = arith.mulf %3, %5 : f64
        %7 = arith.truncf %6 : f64 to f32
        affine.store %7, %alloca[%arg3] : memref<8xf32>
      }
      affine.for %arg3 = 0 to 8 {
        %0 = affine.load %alloca[%arg3] : memref<8xf32>
        affine.store %0, %arg1[%arg3, %arg2] : memref<8x8xf32>
      }
    }
    return
  }
}
