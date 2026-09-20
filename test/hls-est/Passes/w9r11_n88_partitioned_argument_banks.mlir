// RUN: hls-est %s --symbol-privatize=exclude=_Z6sa_topPA28_N3hls6streamIfLi0EEEPA784_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sa_topPA28_N3hls6streamIfLi0EEEPA784_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug-json=- --config-set scheduling.timing.operator_latencies.stream_read=2 --config-set scheduling.timing.operator_latencies.stream_write=1 -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z6sa_topPA28_N3hls6streamIfLi0EEEPA784_f --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z6sa_topPA28_N3hls6streamIfLi0EEEPA784_f math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --bram-debug-json=- --config-set scheduling.timing.operator_latencies.stream_read=2 --config-set scheduling.timing.operator_latencies.stream_write=1 -o /dev/null --config-set tool.hls.memory_architecture.partitioned_argument_bank_ports=false | FileCheck %s --check-prefix=OFF
// W9r11-impl (2026-10-22): VITIS_NOTES N88 (OPEN_ISSUES O119): an `inline off` callee node0(v0, v1) with `array_partition variable=v1 cyclic dim=2 factor=28`
// writes v1[i][k + j * 28] for k = 0..27 (unrolled) in a pipelined j loop, each value read from its own stream v0[0][k]; the top binds v1 to its output port.
// Vitis applies the parameter's partition to the top port ([HLS 214-248] Applying array_partition to 'out') and gets II 1: the 28 banks have their own ports.
// hls-est keys the port pools of a partitioned argument by the access's constant bank (tool.hls.memory_architecture.partitioned_argument_bank_ports);
// off, the 28 stores share the argument's two ports (II 14). Checked with N82's stream classes, which schedule the stream reads (the default leaves the loop sequential).
// Kernel w9r11p_sa_cpt (~/hls-est-work/exp-src/w9r11p/sa_cpt.cpp); MLIR from cgeist 537d6614 (installed), --shim real flags.
// Vitis 2025.1 td=off: 0 BRAM_18K, the j loop II 1.
// CHECK: "pipelines": [
// CHECK: "ii": 1,
// CHECK: "trip_count": 896
// OFF: "pipelines": [
// OFF: "ii": 14,
// OFF: "trip_count": 896

module {
  func.func @_Z6sa_topPA28_N3hls6streamIfLi0EEEPA784_f(%arg0: memref<1x28xi32>, %arg1: memref<32x784xf32>) attributes {hls.orig_name = "sa_top", llvm.linkage = #llvm.linkage<external>} {
    call @_ZL5node0PA28_N3hls6streamIfLi0EEEPA784_f(%arg0, %arg1) : (memref<1x28xi32>, memref<32x784xf32>) -> ()
    return
  }
  func.func private @_ZL5node0PA28_N3hls6streamIfLi0EEEPA784_f(%arg0: memref<1x28xi32>, %arg1: memref<32x784xf32> {hls.array_partition = [{dim = 2 : i32, factor = 28 : i32, kind = "cyclic", variable = "v1"}]}) attributes {hls.inline_off, hls.orig_name = "node0", llvm.linkage = #llvm.linkage<internal>} {
    %c0 = arith.constant 0 : index
    %0 = "polygeist.subindex"(%arg0, %c0) : (memref<1x28xi32>, index) -> memref<28xi32>
    affine.for %arg2 = 0 to 32 {
      affine.for %arg3 = 0 to 28 {
        affine.for %arg4 = 0 to 28 {
          %1 = "polygeist.subindex"(%0, %arg4) : (memref<28xi32>, index) -> memref<?xi32>
          %2 = func.call @_ZN3hls6streamIfLi0EE4readEv(%1) : (memref<?xi32>) -> f32
          affine.store %2, %arg1[%arg2, %arg4 + %arg3 * 28] : memref<32x784xf32>
        }
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    return
  }
  func.func private @_ZN3hls6streamIfLi0EE4readEv(memref<?xi32>) -> f32 attributes {hls.orig_name = "read", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
}
