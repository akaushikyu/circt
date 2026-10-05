// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPhi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKhPhi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKhPhi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topPKhPhi math-costs=%S/../../../tools/hls-est-validate/math_costs.json' '--config-set=tool.hls.partitioning.reshaped_callee_parameters=true' -o /dev/null | FileCheck %s --check-prefix=ON
// W9r23-impl (2026-10-28): VITIS_NOTES N180. Kernel w9r23p_w1_part_callee_shape (~/hls-est-work/exp-src/w9r23p/w1_part_callee_shape.cpp);
// MLIR from the installed cgeist 91128806 (Polygeist 449c7033, --shim real). Vitis 2025.1 td=off: 24 BRAM (24 x 128x8; row 24 unreachable).
// s[25][128] complete dim=1 passed to inline-off callees declared s[24][128]: cgeist reshapes the array with a
// memref.reinterpret_cast, which hides the partition (default: one 3200 x 8 memory, 2). With
// tool.hls.partitioning.reshaped_callee_parameters (off by default: one kernel, no catalogue or held-out design)
// an array used only through casts of one smaller shape becomes an array of that shape: 24 banks = Vitis.
// CHECK: Total BRAM: 2{{$}}
// ON: Total BRAM: 24{{$}}
module {
  func.func @_Z3topPKhPhi(%arg0: memref<128xi8>, %arg1: memref<128xi8>, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "s"}], hls.preserve, polygeist.varname = "s"} : memref<25x128xi8>
    %reinterpret_cast = memref.reinterpret_cast %alloca to offset: [0], sizes: [24, 128], strides: [128, 1] : memref<25x128xi8> to memref<24x128xi8>
    %cast = memref.cast %arg0 : memref<128xi8> to memref<?xi8>
    call @_ZL4fillPA128_hPKhi(%reinterpret_cast, %cast, %arg2) : (memref<24x128xi8>, memref<?xi8>, i32) -> ()
    %0 = arith.addi %arg2, %c1_i32 : i32
    affine.for %arg3 = 0 to 128 {
      %1 = arith.index_cast %arg3 : index to i32
      %2 = func.call @_ZL3getPA128_hii(%reinterpret_cast, %0, %1) : (memref<24x128xi8>, i32, i32) -> i8
      affine.store %2, %arg1[%arg3] : memref<128xi8>
    }
    return
  }
  func.func private @_ZL4fillPA128_hPKhi(%arg0: memref<24x128xi8>, %arg1: memref<?xi8>, %arg2: i32) attributes {hls.inline_off, hls.orig_name = "fill", llvm.linkage = #llvm.linkage<internal>} {
    %c24_i32 = arith.constant 24 : i32
    %0 = arith.remsi %arg2, %c24_i32 : i32
    %1 = arith.index_cast %0 : i32 to index
    affine.for %arg3 = 0 to 128 {
      %2 = affine.load %arg1[%arg3] : memref<?xi8>
      affine.store %2, %arg0[symbol(%1), %arg3] : memref<24x128xi8>
    }
    return
  }
  func.func private @_ZL3getPA128_hii(%arg0: memref<24x128xi8>, %arg1: i32, %arg2: i32) -> i8 attributes {hls.inline_off, hls.orig_name = "get", llvm.linkage = #llvm.linkage<internal>} {
    %c24_i32 = arith.constant 24 : i32
    %0 = arith.remsi %arg1, %c24_i32 : i32
    %1 = arith.index_cast %0 : i32 to index
    %2 = arith.index_cast %arg2 : i32 to index
    %3 = affine.load %arg0[symbol(%1), symbol(%2)] : memref<24x128xi8>
    return %3 : i8
  }
}
