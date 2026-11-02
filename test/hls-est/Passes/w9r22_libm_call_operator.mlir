// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA2048_KfPfPA512_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA2048_KfPfPA512_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA2048_KfPfPA512_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA2048_KfPfPA512_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=scheduling.timing.operator_latencies.libm_call=-1 -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r22-impl (2026-10-26): VITIS_NOTES N169. An LSTM gate loop with 3 expf and
// 2 tanhf calls and 4 reads of gates[2048] per iteration: Vitis pipelines it
// at II 1 (gates RAM_1WNR 3 copies, 12; one generic_tanh_float per call,
// 2 x 5; hid / cell 1 each: 24, kernel w9r22p_d10_lstm_gates). The libm calls
// are scheduled as operators (scheduling.timing.operator_latencies.libm_call);
// at -1 the loop stays sequential: gates 4, one tanh core, 11.
// CHECK: Total BRAM: 24
// OFF: Total BRAM: 11
module {
  func.func @_Z3topPA2048_KfPfPA512_f(%arg0: memref<8x2048xf32>, %arg1: memref<512xf32>, %arg2: memref<8x512xf32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 1.000000e+00 : f32
    %cst_0 = arith.constant 5.000000e-01 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "hid"} : memref<512xf32>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "cell"} : memref<512xf32>
    %alloca_2 = memref.alloca() {hls.preserve, polygeist.varname = "gates"} : memref<2048xf32>
    affine.for %arg3 = 0 to 8 {
      affine.for %arg4 = 0 to 2048 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<8x2048xf32>
        %1 = arith.mulf %0, %cst_0 : f32
        affine.store %1, %alloca_2[%arg4] : memref<2048xf32>
      }
      affine.for %arg4 = 0 to 512 {
        %0 = affine.load %alloca_2[%arg4] : memref<2048xf32>
        %1 = arith.negf %0 : f32
        %2 = math.exp %1 : f32
        %3 = arith.addf %2, %cst : f32
        %4 = arith.divf %cst, %3 : f32
        %5 = affine.load %alloca_2[%arg4 + 512] : memref<2048xf32>
        %6 = arith.negf %5 : f32
        %7 = math.exp %6 : f32
        %8 = arith.addf %7, %cst : f32
        %9 = arith.divf %cst, %8 : f32
        %10 = affine.load %alloca_2[%arg4 + 1024] : memref<2048xf32>
        %11 = arith.negf %10 : f32
        %12 = math.exp %11 : f32
        %13 = arith.addf %12, %cst : f32
        %14 = arith.divf %cst, %13 : f32
        %15 = affine.load %alloca_2[%arg4 + 1536] : memref<2048xf32>
        %16 = func.call @tanhf(%15) : (f32) -> f32
        %17 = affine.load %arg1[%arg4] : memref<512xf32>
        %18 = arith.mulf %9, %17 : f32
        %19 = arith.mulf %4, %16 : f32
        %20 = arith.addf %18, %19 : f32
        affine.store %20, %alloca_1[%arg4] : memref<512xf32>
        %21 = func.call @tanhf(%20) : (f32) -> f32
        %22 = arith.mulf %14, %21 : f32
        affine.store %22, %alloca[%arg4] : memref<512xf32>
      }
      affine.for %arg4 = 0 to 512 {
        %0 = affine.load %alloca_1[%arg4] : memref<512xf32>
        affine.store %0, %arg1[%arg4] : memref<512xf32>
        %1 = affine.load %alloca[%arg4] : memref<512xf32>
        affine.store %1, %arg2[%arg3, %arg4] : memref<8x512xf32>
      }
    }
    return
  }
  func.func private @tanhf(f32) -> f32 attributes {hls.orig_name = "tanhf", llvm.linkage = #llvm.linkage<external>}
}
