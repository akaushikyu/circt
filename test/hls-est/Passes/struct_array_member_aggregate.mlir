// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs=aggregate=false -o - 2>&1 | FileCheck %s --check-prefix=NOAGG
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPKsPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topPKsPi -o /dev/null 2>/dev/null | FileCheck %s --check-prefix=BRAM

// Vitis 2025.1 td=off kernel r4s_fld: `struct Outer { In arr[512]; int x[512]; }`
// with `struct In { short a, b; }`, `o.arr` passed to `fill(In p[N])` (inline
// off, `aggregate variable=p`). The member array of structs is a leaf (its
// members have one type: one more dimension, as cgeist lays such an array
// out), the call receives that leaf's memory, and AGGREGATE on the parameter
// packs the last dimension of every memory it reaches into one word: o_arr is
// 512 x 32 (2 BRAM_18K at x18, read twice per iteration), o_x 512 x 19 after
// width narrowing (1): 3 = Vitis 3, per array. Before, the struct was left
// whole ("not a scalar or an array of scalars") and priced 0.

// CHECK: polygeist.varname = "o_0"} : memref<1x512xi32>
// CHECK: polygeist.varname = "o_1"} : memref<1x512xi32>
// CHECK: call @_ZL4fillP2InPKs_row_0(%{{.*}}, %{{.*}}, %{{.*}}) : (memref<1x512xi32>, index, memref<512xi16>)
// CHECK-LABEL: func.func private @_ZL4fillP2InPKs_row_0(
// CHECK-COUNT-1: affine.store %{{.*}}, %arg0[symbol(%arg1), %{{.*}}] : memref<1x512xi32>
// CHECK-NOT: affine.store %{{.*}}, %arg0
// NOAGG: polygeist.varname = "o_0"} : memref<1x512x2xi16>
// BRAM: 512x32b -> RAM_2P (x18/port) = 2 BRAM_18K
// BRAM: 512x19b -> RAM_1P (x36/port) = 1 BRAM_18K
// BRAM: Total BRAM: 3

module {
  func.func @_Z3topPKsPi(%arg0: memref<512xi16>, %arg1: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c2_i32 = arith.constant 2 : i32
    %c511_i32 = arith.constant 511 : i32
    %c1_i32 = arith.constant 1 : i32
    %c7_i32 = arith.constant 7 : i32
    %alloca = memref.alloca() {polygeist.varname = "o"} : memref<1x!llvm.struct<(array<512 x struct<(i16, i16)>>, array<512 x i32>)>>
    %0 = "polygeist.memref2pointer"(%alloca) : (memref<1x!llvm.struct<(array<512 x struct<(i16, i16)>>, array<512 x i32>)>>) -> !llvm.ptr
    %1 = llvm.getelementptr %0[0, 1] : (!llvm.ptr) -> !llvm.ptr, !llvm.struct<(array<512 x struct<(i16, i16)>>, array<512 x i32>)>
    affine.for %arg2 = 0 to 512 {
      %3 = arith.index_cast %arg2 : index to i32
      %4 = affine.load %arg0[%arg2] : memref<512xi16>
      %5 = arith.extsi %4 : i16 to i32
      %6 = arith.muli %5, %c7_i32 : i32
      %7 = llvm.getelementptr %1[%3] : (!llvm.ptr, i32) -> !llvm.ptr, i32
      llvm.store %6, %7 : i32, !llvm.ptr
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    %2 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<512x2xi16>
    call @_ZL4fillP2InPKs(%2, %arg0) : (memref<512x2xi16>, memref<512xi16>) -> ()
    affine.for %arg2 = 0 to 512 {
      %3 = arith.index_cast %arg2 : index to i32
      %4 = arith.subi %c511_i32, %3 : i32
      %5 = arith.muli %4, %c2_i32 : i32
      %6 = llvm.getelementptr %0[%5] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %7 = llvm.load %6 : !llvm.ptr -> i16
      %8 = arith.extsi %7 : i16 to i32
      %9 = arith.muli %3, %c2_i32 : i32
      %10 = arith.addi %9, %c1_i32 : i32
      %11 = llvm.getelementptr %0[%10] : (!llvm.ptr, i32) -> !llvm.ptr, i16
      %12 = llvm.load %11 : !llvm.ptr -> i16
      %13 = arith.extsi %12 : i16 to i32
      %14 = arith.addi %8, %13 : i32
      %15 = llvm.getelementptr %1[%4] : (!llvm.ptr, i32) -> !llvm.ptr, i32
      %16 = llvm.load %15 : !llvm.ptr -> i32
      %17 = arith.addi %14, %16 : i32
      affine.store %17, %arg1[%arg2] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
  func.func private @_ZL4fillP2InPKs(%arg0: memref<512x2xi16> {hls.aggregate = [{compact = "auto", variable = "p"}]}, %arg1: memref<512xi16>) attributes {hls.inline_off, hls.orig_name = "fill", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    affine.for %arg2 = 0 to 512 {
      %0 = affine.load %arg1[%arg2] : memref<512xi16>
      affine.store %0, %arg0[%arg2, 0] : memref<512x2xi16>
      %1 = affine.load %arg1[%arg2] : memref<512xi16>
      %2 = arith.extsi %1 : i16 to i32
      %3 = arith.addi %2, %c1_i32 : i32
      %4 = arith.trunci %3 : i32 to i16
      affine.store %4, %arg0[%arg2, 1] : memref<512x2xi16>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
