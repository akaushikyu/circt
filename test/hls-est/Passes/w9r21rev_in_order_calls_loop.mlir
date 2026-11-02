// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPsS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPsS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPsS_ math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'scheduling.call_depth.in_order_call_starts=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 21 review (2026-10-25): VITIS_NOTES N156, a loop between the
// calls. `work(A, B, C); for (..) G[i] = C[511 - i] + 1; work(D, E, F)`
// (kernel w9r21rev_r5a_loopbetween): the loop waits for the first call and
// is issued before the second, so the two calls never overlap: one `work`
// instance in Vitis, 8 BRAM. Off (scheduling.call_depth.in_order_call_starts
// =false): two instances, 9.
// CHECK: Total BRAM: 8
// OFF: Total BRAM: 9
// MLIR from the private cgeist of the W9 round 21 review fixes (real headers).
module {
  func.func @_Z4workPsS_S_(%arg0: memref<512xi16>, %arg1: memref<512xi16>, %arg2: memref<512xi16>) attributes {hls.inline_off, hls.orig_name = "work", llvm.linkage = #llvm.linkage<external>} {
    %c3_i32 = arith.constant 3 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<512xi16>
    affine.for %arg3 = 0 to 512 {
      %0 = affine.load %arg0[%arg3] : memref<512xi16>
      %1 = arith.extsi %0 : i16 to i32
      %2 = affine.load %arg1[-%arg3 + 511] : memref<512xi16>
      %3 = arith.extsi %2 : i16 to i32
      %4 = arith.addi %1, %3 : i32
      %5 = arith.trunci %4 : i32 to i16
      affine.store %5, %alloca[%arg3] : memref<512xi16>
    }
    affine.for %arg3 = 0 to 512 {
      %0 = affine.load %alloca[-%arg3 + 511] : memref<512xi16>
      %1 = arith.extsi %0 : i16 to i32
      %2 = arith.muli %1, %c3_i32 : i32
      %3 = arith.trunci %2 : i32 to i16
      affine.store %3, %arg2[%arg3] : memref<512xi16>
    }
    return
  }
  func.func @_Z3topPsS_(%arg0: memref<512xi16>, %arg1: memref<512xi16>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c5_i32 = arith.constant 5 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "G"} : memref<512xi16>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "F"} : memref<512xi16>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "E"} : memref<512xi16>
    %alloca_2 = memref.alloca() {hls.preserve, polygeist.varname = "D"} : memref<512xi16>
    %alloca_3 = memref.alloca() {hls.preserve, polygeist.varname = "C"} : memref<512xi16>
    %alloca_4 = memref.alloca() {hls.preserve, polygeist.varname = "B"} : memref<512xi16>
    %alloca_5 = memref.alloca() {hls.preserve, polygeist.varname = "A"} : memref<512xi16>
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %arg0[%arg2] : memref<512xi16>
      affine.store %0, %alloca_5[%arg2] : memref<512xi16>
      %1 = affine.load %arg0[-%arg2 + 511] : memref<512xi16>
      affine.store %1, %alloca_4[%arg2] : memref<512xi16>
      %2 = affine.load %arg0[%arg2] : memref<512xi16>
      %3 = arith.extsi %2 : i16 to i32
      %4 = arith.xori %3, %c5_i32 : i32
      %5 = arith.trunci %4 : i32 to i16
      affine.store %5, %alloca_2[%arg2] : memref<512xi16>
      %6 = affine.load %arg0[%arg2] : memref<512xi16>
      %7 = arith.extsi %6 : i16 to i32
      %8 = arith.shrsi %7, %c1_i32 : i32
      %9 = arith.trunci %8 : i32 to i16
      affine.store %9, %alloca_1[%arg2] : memref<512xi16>
    }
    call @_Z4workPsS_S_(%alloca_5, %alloca_4, %alloca_3) : (memref<512xi16>, memref<512xi16>, memref<512xi16>) -> ()
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %alloca_3[-%arg2 + 511] : memref<512xi16>
      %1 = arith.extsi %0 : i16 to i32
      %2 = arith.addi %1, %c1_i32 : i32
      %3 = arith.trunci %2 : i32 to i16
      affine.store %3, %alloca[%arg2] : memref<512xi16>
    }
    call @_Z4workPsS_S_(%alloca_2, %alloca_1, %alloca_0) : (memref<512xi16>, memref<512xi16>, memref<512xi16>) -> ()
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %alloca[%arg2] : memref<512xi16>
      %1 = arith.extsi %0 : i16 to i32
      %2 = affine.load %alloca_0[%arg2] : memref<512xi16>
      %3 = arith.extsi %2 : i16 to i32
      %4 = arith.addi %1, %3 : i32
      %5 = arith.trunci %4 : i32 to i16
      affine.store %5, %arg1[%arg2] : memref<512xi16>
    }
    return
  }
}
