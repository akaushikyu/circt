// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA1024_KhPA1024_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA1024_KhPA1024_h math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA1024_KhPA1024_h --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPA1024_KhPA1024_h math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.middle_end.gvn_memref_loads=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 23 review fixes (2026-10-28). Kernel w9r23rev/d1_dyn_same_pred (~/hls-est-work/exp-src/w9r23rev/d1_dyn_same_pred.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 7 BRAM.
// W9 round 23 review D3 (VITIS_NOTES N172): the seven reads of buf[ri[k]][c] (a run-time bank of a complete
// partition, one in-bank address) each under `if (x > 16 * k)`: the per-bank loads of the separate ifs merge
// (memref.loads in mergeConditionalLoads), one read per bank and iteration. Vitis 7. With gvn_memref_loads off, 49.
// CHECK: Total BRAM: 7{{$}}
// OFF: Total BRAM: 49{{$}}
module {
  func.func @_Z3topPA1024_KhPA1024_h(%arg0: memref<64x1024xi8>, %arg1: memref<64x1024xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %c16_i32 = arith.constant 16 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "ri"}], hls.preserve, polygeist.varname = "ri"} : memref<7xi32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "buf"}], hls.preserve, polygeist.varname = "buf"} : memref<7x1024xi8>
    affine.for %arg2 = 0 to 7 {
      %0 = arith.index_cast %arg2 : index to i32
      affine.store %0, %alloca[%arg2] : memref<7xi32>
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %alloca[6] : memref<7xi32>
      %1 = arith.index_cast %0 : i32 to index
      affine.for %arg3 = 0 to 1024 {
        %3 = affine.load %arg0[%arg2, %arg3] : memref<64x1024xi8>
        memref.store %3, %alloca_0[%1, %arg3] : memref<7x1024xi8>
        %4 = arith.extui %3 : i8 to i32
        %5 = affine.for %arg4 = 0 to 7 iter_args(%arg5 = %c0_i32) -> (i32) {
          %8 = arith.index_cast %arg4 : index to i32
          %9 = arith.muli %8, %c16_i32 : i32
          %10 = arith.cmpi sgt, %4, %9 : i32
          %11 = scf.if %10 -> (i32) {
            %12 = affine.load %alloca[%arg4] : memref<7xi32>
            %13 = arith.index_cast %12 : i32 to index
            %14 = memref.load %alloca_0[%13, %arg3] : memref<7x1024xi8>
            %15 = arith.extui %14 : i8 to i32
            %16 = arith.addi %arg5, %15 : i32
            scf.yield %16 : i32
          } else {
            scf.yield %arg5 : i32
          }
          affine.yield %11 : i32
        } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
        %6 = arith.shrui %5, %c3_i32 : i32
        %7 = arith.trunci %6 : i32 to i8
        affine.store %7, %arg1[%arg2, %arg3] : memref<64x1024xi8>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      %2 = affine.load %alloca[0] : memref<7xi32>
      affine.for %arg3 = 0 to 6 {
        %3 = affine.load %alloca[%arg3 + 1] : memref<7xi32>
        affine.store %3, %alloca[%arg3] : memref<7xi32>
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %2, %alloca[6] : memref<7xi32>
    }
    return
  }
}
