// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKyPyi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKyPyi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKyPyi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKyPyi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.memory_architecture.replication.user_plain_ram_pins_kind=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 23 review fixes (2026-10-28). Kernel w9r23rev/r5_bind2p_2w1r (~/hls-est-work/exp-src/w9r23rev/r5_bind2p_2w1r.cpp);
// MLIR from the private cgeist d64b520a (Polygeist 28cad708, --shim real). Vitis 2025.1 td=off: 2 BRAM.
// W9 round 23 review D4 (VITIS_NOTES N173): a user RAM_2P on 64 x 64 bits written twice and read once per
// iteration: one write per cycle (the read / write port), the II rises, and with one read per cycle the bank
// is a simple-dual-port pair, x36: Vitis 2 at II 3 (before: RAM_T2P x18, 4). With the key off the binding is ignored (4).
// CHECK: Total BRAM: 2{{$}}
// OFF: Total BRAM: 4{{$}}
module {
  func.func @_Z3topPKyPyi(%arg0: memref<128xi64>, %arg1: memref<64xi64>, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c63_i32 = arith.constant 63 : i32
    %alloca = memref.alloca() {hls.bind_storage = [{impl = "bram", type = "ram_2p", variable = "b"}], hls.preserve, polygeist.varname = "b"} : memref<64xi64>
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %arg0[%arg3] : memref<128xi64>
      affine.store %0, %alloca[%arg3] : memref<64xi64>
    }
    affine.for %arg3 = 0 to 32 {
      %0 = arith.index_cast %arg3 : index to i32
      %1 = arith.addi %0, %arg2 : i32
      %2 = arith.andi %1, %c63_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      %4 = memref.load %alloca[%3] : memref<64xi64>
      %5 = affine.load %arg0[%arg3 * 2 + 64] : memref<128xi64>
      %6 = arith.addi %4, %5 : i64
      affine.store %6, %alloca[%arg3 * 2] : memref<64xi64>
      %7 = affine.load %arg0[%arg3 * 2 + 65] : memref<128xi64>
      %8 = arith.xori %4, %7 : i64
      affine.store %8, %alloca[%arg3 * 2 + 1] : memref<64xi64>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %alloca[%arg3] : memref<64xi64>
      affine.store %0, %arg1[%arg3] : memref<64xi64>
    }
    return
  }
}
