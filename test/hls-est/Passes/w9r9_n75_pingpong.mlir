// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPA1024_iPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z1kPA1024_iPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z1kPA1024_iPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z1kPA1024_iPi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set tool.hls.memory_architecture.replication.port_bound_several_arrays=false -o /dev/null | FileCheck %s --check-prefix=POFF
// W9r9-impl (2026-10-21): VITIS_NOTES N75: Yolo-v3-tiny's ping-pong shape, if (t % 2 == 0) rdf(A, out) else rdf(A2, out): one instance, two arrays on its parameter, port-bound.
// Kernel w9r9p_rs_pingpong; MLIR from cgeist 537d6614 (installed) with the harness's --shim real flags.
// Vitis 2025.1 td=off: 4 BRAM_18K.
// With tool.hls.memory_architecture.replication.port_bound_several_arrays=false (POFF): 28.
// POFF: Total BRAM: 28{{$}}
// CHECK: Total BRAM: 4{{$}}

module {
  func.func @_Z1kPA1024_iPi(%arg0: memref<4x1024xi32>, %arg1: memref<128xi32>) attributes {hls.orig_name = "k", llvm.linkage = #llvm.linkage<external>} {
    %c2 = arith.constant 2 : index
    %c0 = arith.constant 0 : index
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "A2"} : memref<1024xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<1024xi32>
    affine.for %arg2 = 0 to 4 {
      %0 = arith.remsi %arg2, %c2 : index
      %1 = arith.cmpi slt, %0, %c0 : index
      %2 = arith.addi %0, %c2 : index
      %3 = arith.select %1, %2, %0 : index
      %4 = arith.cmpi eq, %3, %c0 : index
      scf.if %4 {
        affine.for %arg3 = 0 to 1024 {
          %5 = affine.load %arg0[%arg2, %arg3] : memref<4x1024xi32>
          affine.store %5, %alloca_0[%arg3] : memref<1024xi32>
        }
        func.call @_ZL3rdfPiS_(%alloca_0, %arg1) : (memref<1024xi32>, memref<128xi32>) -> ()
      } else {
        affine.for %arg3 = 0 to 1024 {
          %5 = affine.load %arg0[%arg2, %arg3] : memref<4x1024xi32>
          affine.store %5, %alloca[%arg3] : memref<1024xi32>
        }
        func.call @_ZL3rdfPiS_(%alloca, %arg1) : (memref<1024xi32>, memref<128xi32>) -> ()
      }
    }
    return
  }
  func.func private @_ZL3rdfPiS_(%arg0: memref<1024xi32>, %arg1: memref<128xi32>) attributes {hls.inline_off, hls.orig_name = "rdf", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg2 = 0 to 128 {
      %0 = affine.load %arg1[%arg2] : memref<128xi32>
      %1 = affine.for %arg3 = 0 to 8 iter_args(%arg4 = %0) -> (i32) {
        %2 = affine.load %arg0[%arg3 + %arg2 * 8] : memref<1024xi32>
        %3 = arith.addi %arg4, %2 : i32
        affine.yield %3 : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %1, %arg1[%arg2] : memref<128xi32>
    }
    return
  }
}
