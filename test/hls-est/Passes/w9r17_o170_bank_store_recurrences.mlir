// RUN: hls-est %s --symbol-privatize=exclude=k2mm --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.flatten_nest_invariant_bounds=true --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=true --config-set scheduling.dependences.enclosing_iv_sample_steps=7 --config-set scheduling.dependences.bank_store_recurrences=true --bram-debug-json=%t.on.json -o /dev/null && FileCheck %s --input-file=%t.on.json
// RUN: hls-est %s --symbol-privatize=exclude=k2mm --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.pipeline_decision.flatten_nest_invariant_bounds=true --config-set tool.hls.pipeline_decision.promote_nest_invariant_only=true --config-set scheduling.dependences.enclosing_iv_sample_steps=7 --config-set scheduling.dependences.bank_store_recurrences=false --bram-debug-json=%t.off.json -o /dev/null && FileCheck %s --check-prefix=OFF --input-file=%t.off.json

// OPEN_ISSUES O170 (a), polybench_pragmas k2mm (Vitis 2025.1 td=off: the
// `tmp1[i][j] += alpha * A[i][k] * B[k][j]` loop at II 8): tmp1 is partitioned
// cyclic 4 on j, so after --memory-banking-bram its read-modify-write is four
// run-time-bank loads and four enabled stores. With
// scheduling.dependences.bank_store_recurrences the enabled stores count as stores
// of the array (and each bank's load takes the enable of its bank's store), so with
// N129's keys on the R1 recurrence of the flattened k loop is found: II 8 = Vitis.
// The keys are on by default since W9r18-impl, with tool.hls.middle_end.
// forward_before_banking (VITIS_NOTES N138, O170 (c)), which removes the overwritten store of
// the first unroll copy so that tmp1 stays replicable (k2mm 184 = Vitis); the second RUN
// turns bank_store_recurrences off.
// CHECK: "memory_recurrence": {
// CHECK-NEXT: "chain": 8,
// CHECK-NEXT: "distance": 1,
// CHECK-NEXT: "ii": 8,
// CHECK: "rule": "R1",
// CHECK: "scope_loc": "{{.*}}:50:9",
// OFF-NOT: "rule": "R1",

module {
  func.func @k2mm(%arg0: f32, %arg1: f32, %arg2: memref<64x64xf32> {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "A"}], hls.bind_storage = [{type = "ram_1p", variable = "A"}]}, %arg3: memref<64x64xf32> {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "B"}], hls.bind_storage = [{type = "ram_1p", variable = "B"}]}, %arg4: memref<64x64xf32> {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "C"}], hls.bind_storage = [{type = "ram_1p", variable = "C"}]}, %arg5: memref<64x64xf32> {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "D"}], hls.bind_storage = [{type = "ram_1p", variable = "D"}]}, %arg6: memref<64x64xf32> {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "E_out"}], hls.interface = [{mode = "ap_fifo", port = "E_out"}]}) attributes {hls.orig_name = "k2mm", llvm.linkage = #llvm.linkage<external>} {
    %cst = arith.constant 0.000000e+00 : f32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "tmp2"}], hls.preserve, polygeist.varname = "tmp2"} : memref<64x64xf32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "tmp1"}], hls.preserve, polygeist.varname = "tmp1"} : memref<64x64xf32>
    %alloca_1 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "buff_E_out"}], hls.preserve, polygeist.varname = "buff_E_out"} : memref<64x64xf32>
    %alloca_2 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "buff_D"}], hls.preserve, polygeist.varname = "buff_D"} : memref<64x64xf32>
    %alloca_3 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "buff_C"}], hls.preserve, polygeist.varname = "buff_C"} : memref<64x64xf32>
    %alloca_4 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "buff_B"}], hls.preserve, polygeist.varname = "buff_B"} : memref<64x64xf32>
    %alloca_5 = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "buff_A"}], hls.preserve, polygeist.varname = "buff_A"} : memref<64x64xf32>
    affine.for %arg7 = 0 to 64 {
      affine.for %arg8 = 0 to 64 {
        %0 = affine.load %arg2[%arg7, %arg8] : memref<64x64xf32>
        affine.store %0, %alloca_5[%arg7, %arg8] : memref<64x64xf32>
        %1 = affine.load %arg3[%arg7, %arg8] : memref<64x64xf32>
        affine.store %1, %alloca_4[%arg7, %arg8] : memref<64x64xf32>
        %2 = affine.load %arg4[%arg7, %arg8] : memref<64x64xf32>
        affine.store %2, %alloca_3[%arg7, %arg8] : memref<64x64xf32>
        %3 = affine.load %arg5[%arg7, %arg8] : memref<64x64xf32>
        affine.store %3, %alloca_2[%arg7, %arg8] : memref<64x64xf32>
        affine.store %cst, %alloca_1[%arg7, %arg8] : memref<64x64xf32>
        affine.store %cst, %alloca_0[%arg7, %arg8] : memref<64x64xf32>
        affine.store %cst, %alloca[%arg7, %arg8] : memref<64x64xf32>
      } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
    }
    affine.for %arg7 = 0 to 64 {
      affine.for %arg8 = 0 to 64 {
        affine.for %arg9 = 0 to 64 {
          %0 = affine.load %alloca_5[%arg7, %arg9] : memref<64x64xf32>
          %1 = arith.mulf %arg0, %0 : f32
          %2 = affine.load %alloca_4[%arg9, %arg8] : memref<64x64xf32>
          %3 = arith.mulf %1, %2 : f32
          %4 = affine.load %alloca_0[%arg7, %arg8] : memref<64x64xf32>
          %5 = arith.addf %4, %3 : f32
          affine.store %5, %alloca_0[%arg7, %arg8] : memref<64x64xf32>
        } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
      }
    }
    affine.for %arg7 = 0 to 64 {
      affine.for %arg8 = 0 to 64 {
        affine.for %arg9 = 0 to 64 {
          %0 = affine.load %alloca_0[%arg7, %arg9] : memref<64x64xf32>
          %1 = affine.load %alloca_3[%arg9, %arg8] : memref<64x64xf32>
          %2 = arith.mulf %0, %1 : f32
          %3 = affine.load %alloca[%arg7, %arg8] : memref<64x64xf32>
          %4 = arith.addf %3, %2 : f32
          affine.store %4, %alloca[%arg7, %arg8] : memref<64x64xf32>
        }
      }
    }
    affine.for %arg7 = 0 to 64 {
      affine.for %arg8 = 0 to 64 {
        %0 = affine.load %alloca[%arg7, %arg8] : memref<64x64xf32>
        %1 = affine.load %alloca_2[%arg7, %arg8] : memref<64x64xf32>
        %2 = arith.mulf %arg1, %1 : f32
        %3 = arith.addf %0, %2 : f32
        affine.store %3, %alloca_1[%arg7, %arg8] : memref<64x64xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 2 : i32, skip_exit_check = false}]}
    }
    affine.for %arg7 = 0 to 64 {
      affine.for %arg8 = 0 to 64 {
        %0 = affine.load %alloca_1[%arg7, %arg8] : memref<64x64xf32>
        affine.store %0, %arg6[%arg7, %arg8] : memref<64x64xf32>
      } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
    }
    return
  }
}
