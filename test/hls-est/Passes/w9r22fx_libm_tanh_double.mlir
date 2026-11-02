// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKdPd --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKdPd math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set=tool.hls.pipeline_decision.pipelined_library_calls=[] -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 22 review fix (D1): tanh(double) is pipelined like tanhf (kernel
// w9r22fx_f9_tanh_loop: t RAM_2P 4 + generic_tanh_double 5 = 9). With an empty
// pipelined_library_calls list the loop stays sequential (t 1-port, 2 + 5).
// CHECK: Total BRAM: 9
// OFF: Total BRAM: 7
module {
  func.func @_Z3topPKdPd(%arg0: memref<256xf64>, %arg1: memref<256xf64>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "t"} : memref<256xf64>
    affine.for %arg2 = 0 to 256 {
      %0 = affine.load %arg0[%arg2] : memref<256xf64>
      affine.store %0, %alloca[%arg2] : memref<256xf64>
    }
    affine.for %arg2 = 0 to 256 {
      %0 = affine.load %alloca[%arg2] : memref<256xf64>
      %1 = func.call @tanh(%0) : (f64) -> f64
      affine.store %1, %alloca[%arg2] : memref<256xf64>
    }
    affine.for %arg2 = 0 to 256 {
      %0 = affine.load %alloca[%arg2] : memref<256xf64>
      affine.store %0, %arg1[%arg2] : memref<256xf64>
    }
    return
  }
  func.func private @tanh(f64) -> f64 attributes {hls.orig_name = "tanh", llvm.linkage = #llvm.linkage<external>}
}
