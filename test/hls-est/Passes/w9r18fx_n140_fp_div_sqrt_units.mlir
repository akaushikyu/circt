// RUN: hls-est %s --symbol-privatize=exclude=kdiv --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=kdiv math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=DIV
// RUN: hls-est %s --symbol-privatize=exclude=kfdiv --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=kfdiv math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=FDIV
// RUN: hls-est %s --symbol-privatize=exclude=ksqrt --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=ksqrt math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=SQRT
// RUN: hls-est %s --symbol-privatize=exclude=kdiv --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=kdiv math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set scheduling.modulo.fp_unit_limits=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=NOLIM

// W9 round 18 review fixes, VITIS_NOTES N140: the divide and square-root cores are floating-point
// unit classes like the adds and multiplies of N135. Kernels (Vitis 2025.1 td=off): an `unroll
// factor=2` pipelined loop whose two copies each end in `tb[i] = s / d` (w9r18rv_k7div, double: 46,
// one ddiv instance, the divisions start one state apart, stores in ST_153 / ST_154, tb ram_1p 2),
// the float version (w9r18fx_k7fdiv: 23, one fdiv instance, tb ram_1p 1) and `tb[i] = sqrt(s)`
// (w9r18fx_k7sqrt: 46, one dsqrt instance, tb ram_1p 2). At II 2 each class gets ceil(2 / 2) = 1
// unit, so the second copy's divide waits a cycle and the two stores land in different stages: tb
// stays one port. Without the unit limit (or before this fix, divide and sqrt had none) both
// stores share a stage and tb becomes a 2-port RAM (48 / 24 / 48). MLIR from cgeist 2b5e2add
// (installed), --shim real; functions renamed.
// DIV: ] tb (alloca)
// DIV: ram type: RAM_1P
// DIV: Total BRAM: 46{{$}}
// FDIV: ] tb (alloca)
// FDIV: ram type: RAM_1P
// FDIV: Total BRAM: 23{{$}}
// SQRT: ] tb (alloca)
// SQRT: ram type: RAM_1P
// SQRT: Total BRAM: 46{{$}}
// NOLIM: ] tb (alloca)
// NOLIM: ram type: RAM_T2P
// NOLIM: Total BRAM: 48{{$}}

module {
  func.func @kdiv(%arg0: memref<32x12xf64>, %arg1: memref<12xf64>, %arg2: memref<32xf64>, %arg3: f64) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "tb"} : memref<32xf64>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "xb"} : memref<12xf64>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Ab"} : memref<32x12xf64>
    affine.for %arg4 = 0 to 32 {
      affine.for %arg5 = 0 to 12 {
        %0 = affine.load %arg0[%arg4, %arg5] : memref<32x12xf64>
        affine.store %0, %alloca_1[%arg4, %arg5] : memref<32x12xf64>
      }
    }
    affine.for %arg4 = 0 to 12 {
      %0 = affine.load %arg1[%arg4] : memref<12xf64>
      affine.store %0, %alloca_0[%arg4] : memref<12xf64>
    }
    affine.for %arg4 = 0 to 32 {
      %0 = affine.for %arg5 = 0 to 12 iter_args(%arg6 = %cst) -> (f64) {
        %2 = affine.load %alloca_1[%arg4, %arg5] : memref<32x12xf64>
        %3 = affine.load %alloca_0[%arg5] : memref<12xf64>
        %4 = arith.mulf %2, %3 : f64
        %5 = arith.addf %arg6, %4 : f64
        affine.yield %5 : f64
      }
      %1 = arith.divf %0, %arg3 : f64
      affine.store %1, %alloca[%arg4] : memref<32xf64>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
    affine.for %arg4 = 0 to 32 {
      %0 = affine.load %alloca[%arg4] : memref<32xf64>
      affine.store %0, %arg2[%arg4] : memref<32xf64>
    }
    return
  }

  func.func @kfdiv(%arg0: memref<32x12xf32>, %arg1: memref<12xf32>, %arg2: memref<32xf32>, %arg3: f32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "tb"} : memref<32xf32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "xb"} : memref<12xf32>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Ab"} : memref<32x12xf32>
    affine.for %arg4 = 0 to 32 {
      affine.for %arg5 = 0 to 12 {
        %0 = affine.load %arg0[%arg4, %arg5] : memref<32x12xf32>
        affine.store %0, %alloca_1[%arg4, %arg5] : memref<32x12xf32>
      }
    }
    affine.for %arg4 = 0 to 12 {
      %0 = affine.load %arg1[%arg4] : memref<12xf32>
      affine.store %0, %alloca_0[%arg4] : memref<12xf32>
    }
    affine.for %arg4 = 0 to 32 {
      %0 = affine.for %arg5 = 0 to 12 iter_args(%arg6 = %cst) -> (f32) {
        %2 = affine.load %alloca_1[%arg4, %arg5] : memref<32x12xf32>
        %3 = affine.load %alloca_0[%arg5] : memref<12xf32>
        %4 = arith.mulf %2, %3 : f32
        %5 = arith.addf %arg6, %4 : f32
        affine.yield %5 : f32
      }
      %1 = arith.divf %0, %arg3 : f32
      affine.store %1, %alloca[%arg4] : memref<32xf32>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
    affine.for %arg4 = 0 to 32 {
      %0 = affine.load %alloca[%arg4] : memref<32xf32>
      affine.store %0, %arg2[%arg4] : memref<32xf32>
    }
    return
  }

  func.func @ksqrt(%arg0: memref<32x12xf64>, %arg1: memref<12xf64>, %arg2: memref<32xf64>, %arg3: f64) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f64
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "tb"} : memref<32xf64>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "xb"} : memref<12xf64>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "Ab"} : memref<32x12xf64>
    affine.for %arg4 = 0 to 32 {
      affine.for %arg5 = 0 to 12 {
        %0 = affine.load %arg0[%arg4, %arg5] : memref<32x12xf64>
        affine.store %0, %alloca_1[%arg4, %arg5] : memref<32x12xf64>
      }
    }
    affine.for %arg4 = 0 to 12 {
      %0 = affine.load %arg1[%arg4] : memref<12xf64>
      affine.store %0, %alloca_0[%arg4] : memref<12xf64>
    }
    affine.for %arg4 = 0 to 32 {
      %0 = affine.for %arg5 = 0 to 12 iter_args(%arg6 = %cst) -> (f64) {
        %2 = affine.load %alloca_1[%arg4, %arg5] : memref<32x12xf64>
        %3 = affine.load %alloca_0[%arg5] : memref<12xf64>
        %4 = arith.mulf %2, %3 : f64
        %5 = arith.addf %arg6, %4 : f64
        affine.yield %5 : f64
      }
      %1 = math.sqrt %0 : f64
      affine.store %1, %alloca[%arg4] : memref<32xf64>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
    affine.for %arg4 = 0 to 32 {
      %0 = affine.load %alloca[%arg4] : memref<32xf64>
      affine.store %0, %arg2[%arg4] : memref<32xf64>
    }
    return
  }
}
