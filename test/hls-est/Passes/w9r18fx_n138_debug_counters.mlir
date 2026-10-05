// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA16_iS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPA16_iS0_S0_ --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA16_iS0_S0_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPA16_iS0_S0_ --bram-debug-json=%t.json -o /dev/null && FileCheck %s --check-prefix=JSON < %t.json

// W9 round 18 review fixes (defect 6): the loads and stores N138's forwarding before banking removes
// (tool.hls.middle_end.forward_before_banking) show in the debug output of every bank. Kernel
// w9r18rv_k6fwd (the k2mm lp3 shape on int, tmp1 cyclic 4 on j, `unroll factor=2`; Vitis 2025.1
// td=off 12 = hls-est): each bank's guarded store absorbs the first copy's forwarded load and its dead
// store. Before the fix --memory-banking-bram rebuilt the stores without the counters (0 everywhere).
// MLIR from cgeist 2b5e2add (installed), --shim real.
// CHECK: tmp1[bank 0/4]
// CHECK: hls.store_enable write in pipeline {{.*}}(absorbed 1 forwarded load(s), 1 dead store(s))
// CHECK: tmp1[bank 3/4]
// CHECK: hls.store_enable write in pipeline {{.*}}(absorbed 1 forwarded load(s), 1 dead store(s))
// CHECK: Total BRAM: 12{{$}}
// JSON: "forwarded_loads": 1
// JSON: "removed_stores": 1

module {
  func.func @_Z3topPA16_iS0_S0_(%arg0: memref<16x16xi32>, %arg1: memref<16x16xi32>, %arg2: memref<16x16xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "Bb"} : memref<16x16xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "Ab"} : memref<16x16xi32>
    %alloca_1 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "tmp1"}], hls.preserve, polygeist.varname = "tmp1"} : memref<16x16xi32>
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 16 {
        %0 = affine.load %arg0[%arg3, %arg4] : memref<16x16xi32>
        affine.store %0, %alloca_0[%arg3, %arg4] : memref<16x16xi32>
        %1 = affine.load %arg1[%arg3, %arg4] : memref<16x16xi32>
        affine.store %1, %alloca[%arg3, %arg4] : memref<16x16xi32>
      }
    }
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 16 {
        affine.store %c0_i32, %alloca_1[%arg3, %arg4] : memref<16x16xi32>
      }
    }
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 16 {
        affine.for %arg5 = 0 to 16 {
          %0 = affine.load %alloca_0[%arg3, %arg5] : memref<16x16xi32>
          %1 = affine.load %alloca[%arg5, %arg4] : memref<16x16xi32>
          %2 = arith.muli %0, %1 : i32
          %3 = affine.load %alloca_1[%arg3, %arg4] : memref<16x16xi32>
          %4 = arith.addi %3, %2 : i32
          affine.store %4, %alloca_1[%arg3, %arg4] : memref<16x16xi32>
        } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
      }
    }
    affine.for %arg3 = 0 to 16 {
      affine.for %arg4 = 0 to 16 {
        %0 = affine.load %alloca_1[%arg3, %arg4] : memref<16x16xi32>
        affine.store %0, %arg2[%arg3, %arg4] : memref<16x16xi32>
      }
    }
    return
  }
}
