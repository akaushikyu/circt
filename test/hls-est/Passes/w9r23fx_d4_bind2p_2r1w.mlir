// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKyPyi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKyPyi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9 round 23 review fixes (2026-10-28). Kernel w9r23fx/f2_bind2p_2r1w (~/hls-est-work/exp-src/w9r23fx/f2_bind2p_2r1w.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 4 BRAM.
// W9 round 23 review D4 control: the same RAM_2P read twice and written once per iteration: two reads in one
// cycle use both ports, not simple dual port: x18, Vitis 4.
// CHECK: Total BRAM: 4{{$}}
module {
  func.func @_Z3topPKyPyi(%arg0: memref<128xi64>, %arg1: memref<64xi64>, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c2_i32 = arith.constant 2 : i32
    %c63_i32 = arith.constant 63 : i32
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.bind_storage = [{impl = "bram", type = "ram_2p", variable = "b"}], hls.preserve, polygeist.varname = "b"} : memref<64xi64>
    affine.for %arg3 = 0 to 64 {
      %1 = affine.load %arg0[%arg3] : memref<128xi64>
      affine.store %1, %alloca[%arg3] : memref<64xi64>
    }
    %0 = arith.muli %arg2, %c2_i32 : i32
    affine.for %arg3 = 0 to 64 {
      %1 = arith.index_cast %arg3 : index to i32
      %2 = arith.addi %1, %arg2 : i32
      %3 = arith.andi %2, %c63_i32 : i32
      %4 = arith.index_cast %3 : i32 to index
      %5 = memref.load %alloca[%4] : memref<64xi64>
      %6 = arith.addi %1, %0 : i32
      %7 = arith.addi %6, %c1_i32 : i32
      %8 = arith.andi %7, %c63_i32 : i32
      %9 = arith.index_cast %8 : i32 to index
      %10 = memref.load %alloca[%9] : memref<64xi64>
      %11 = arith.addi %5, %10 : i64
      %12 = affine.load %arg0[%arg3 + 64] : memref<128xi64>
      %13 = arith.xori %11, %12 : i64
      affine.store %13, %alloca[%arg3] : memref<64xi64>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 64 {
      %1 = affine.load %alloca[%arg3] : memref<64xi64>
      affine.store %1, %arg1[%arg3] : memref<64xi64>
    }
    return
  }
}
