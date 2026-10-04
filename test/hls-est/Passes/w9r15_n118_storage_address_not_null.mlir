// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_sPsPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA128_sPsPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.folding.storage_address_not_null=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N118, kernel w9r15p_pb_null (Vitis 2025.1 td=off: 0): a local
// K[100][128] filled from the input and used only as K[k] ? 1 : 0 (a row address,
// never null). The comparison folds (tool.hls.folding.storage_address_not_null)
// and dead-memory elimination removes the write-only array.
// Off run: the comparison keeps K (16).
// CHECK: Total BRAM: 0
// OFF: Total BRAM: 16

module {
  func.func @_Z3topPA128_sPsPi(%arg0: memref<100x128xi16>, %arg1: memref<128xi16>, %arg2: memref<100xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "K"} : memref<100x128xi16>
    affine.for %arg3 = 0 to 100 {
      affine.for %arg4 = 0 to 128 {
        %1 = affine.load %arg0[%arg3, %arg4] : memref<100x128xi16>
        affine.store %1, %alloca[%arg3, %arg4] : memref<100x128xi16>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
    %0 = llvm.mlir.zero : !llvm.ptr
    affine.for %arg3 = 0 to 100 {
      %1 = affine.for %arg4 = 0 to 100 iter_args(%arg5 = %c0_i32) -> (i32) {
        %2 = affine.load %arg1[%arg4] : memref<128xi16>
        %3 = arith.extsi %2 : i16 to i32
        %4 = "polygeist.subindex"(%alloca, %arg4) : (memref<100x128xi16>, index) -> memref<128xi16>
        %5 = "polygeist.memref2pointer"(%4) : (memref<128xi16>) -> !llvm.ptr
        %6 = llvm.icmp "ne" %5, %0 : !llvm.ptr
        %7 = arith.extui %6 : i1 to i32
        %8 = arith.muli %3, %7 : i32
        %9 = arith.addi %arg5, %8 : i32
        affine.yield %9 : i32
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
      affine.store %1, %arg2[%arg3] : memref<100xi32>
    }
    return
  }
}
