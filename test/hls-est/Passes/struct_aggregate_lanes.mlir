// RUN: hls-est %s --symbol-privatize=exclude=_Z5lanesPKsPii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs -o - 2>/dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z5lanesPKsPii --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z5lanesPKsPii -o /dev/null 2>&1 | FileCheck %s --check-prefix=BRAM

// The lanes of one aggregated element read in a loop (`for (l...) s += v[e][l]`)
// are one word read and shifts (VITIS_NOTES.md N37 S3: a lane read is a word
// load + lshr); the word read is placed before the lane loop, so the lanes
// unrolled under the pipelined loop do not count as eight reads. The lane
// writes of the fill loop are read-modify-writes. Source:
// ~/hls-est-work/coord/scratch/n37impl/lit_k/lanes.cpp. Vitis 2025.1 td=off
// (n37i_lanes): v 256x128 8 BRAM_18K, the read loop at II 1 = hls-est.

// CHECK: %[[V:.*]] = memref.alloca() {{.*}}polygeist.varname = "v"} : memref<256xi128>
// CHECK: memref.load %[[V]][%{{.*}}] {hls.dynamic_lane, hls.read_modify_write} : memref<256xi128>
// CHECK: memref.store %{{.*}}, %[[V]][%{{.*}}] : memref<256xi128>
// CHECK: affine.for
// CHECK: %[[W:.*]] = memref.load %[[V]][%{{.*}}] : memref<256xi128>
// CHECK-NEXT: affine.for
// CHECK: arith.shrui %[[W]]
// BRAM: Total BRAM: 8

module {
  func.func @_Z5lanesPKsPii(%arg0: memref<2048xi16>, %arg1: memref<1xi32>, %arg2: i32) attributes {hls.orig_name = "lanes", llvm.linkage = #llvm.linkage<external>} {
    %c255_i32 = arith.constant 255 : i32
    %c7_i32 = arith.constant 7 : i32
    %c3_i32 = arith.constant 3 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.aggregate = [{compact = "auto", variable = "v"}], hls.preserve, polygeist.varname = "v"} : memref<256x!llvm.struct<(array<8 x i16>)>>
    affine.for %arg3 = 0 to 2048 {
      %1 = arith.index_cast %arg3 : index to i32
      %2 = arith.shrsi %1, %c3_i32 : i32
      %3 = arith.index_cast %2 : i32 to index
      %4 = "polygeist.subindex"(%alloca, %3) : (memref<256x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %5 = arith.andi %1, %c7_i32 : i32
      %6 = arith.extsi %5 : i32 to i64
      %7 = func.call @_ZNSt5arrayIsLm8EEixEm(%4, %6) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
      %8 = affine.load %arg0[%arg3] : memref<2048xi16>
      affine.store %8, %7[0] : memref<?xi16>
    }
    %0 = affine.for %arg3 = 0 to 256 iter_args(%arg4 = %c0_i32) -> (i32) {
      %1 = arith.index_cast %arg3 : index to i32
      %2 = arith.muli %1, %arg2 : i32
      %3 = arith.andi %2, %c255_i32 : i32
      %4 = arith.index_cast %3 : i32 to index
      %5 = "polygeist.subindex"(%alloca, %4) : (memref<256x!llvm.struct<(array<8 x i16>)>>, index) -> memref<?x!llvm.struct<(array<8 x i16>)>>
      %6 = affine.for %arg5 = 0 to 8 iter_args(%arg6 = %arg4) -> (i32) {
        %7 = arith.index_cast %arg5 : index to i32
        %8 = arith.extsi %7 : i32 to i64
        %9 = func.call @_ZNSt5arrayIsLm8EEixEm(%5, %8) : (memref<?x!llvm.struct<(array<8 x i16>)>>, i64) -> memref<?xi16>
        %10 = affine.load %9[0] : memref<?xi16>
        %11 = arith.extsi %10 : i16 to i32
        %12 = arith.addi %arg6, %11 : i32
        affine.yield %12 : i32
      }
      affine.yield %6 : i32
    }
    affine.store %0, %arg1[0] : memref<1xi32>
    return
  }
  func.func @_ZNSt5arrayIsLm8EEixEm(%arg0: memref<?x!llvm.struct<(array<8 x i16>)>>, %arg1: i64) -> memref<?xi16> attributes {hls.orig_name = "operator[]", llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<8 x i16>)>>) -> !llvm.ptr
    %1 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<8xi16>
    %2 = arith.index_castui %arg1 : i64 to index
    %3 = "polygeist.subindex"(%1, %2) : (memref<8xi16>, index) -> memref<?xi16>
    return %3 : memref<?xi16>
  }
}
