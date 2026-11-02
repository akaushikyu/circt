// RUN: hls-est %s --config-set=tool.hls.partitioning.drop_unread_banks=false --memory-banking-bram | FileCheck %s
// W9r21: the RUN lines pin tool.hls.partitioning.drop_unread_banks off (VITIS_NOTES
// N157 would remove the banks these kernels write and never read); this test is
// about the banking of constant indices.
//
// Banking must recognise a constant bank when the banked index is an SSA
// constant (what --auto-pipeline-unroll leaves behind for the first unrolled
// iteration: `%buf[%i, %c0]` and `%buf[%i, affine.apply (d0 + 1)(%c0)]`) and
// when it is the counter of a stepped loop (`%buf[%j + 1]` with step 4), which
// --infer-vitis-split-array already pins to one bank, nor when it is constant
// only through a single-trip loop counter or an index cast (@single_trip_and_
// cast). None may expand into the rotating form (f loads + f-1 arith.select,
// or f hls.affine.store_enable). A genuinely rotating access still does.

// CHECK-LABEL: func.func @unrolled
// CHECK-COUNT-4: memref.alloca() {{.*}} : memref<64x1xf32>
// CHECK-NOT: arith.select
// CHECK-NOT: store_enable
// CHECK: return
func.func @unrolled(%arg0: memref<64x4xf32>) {
  %c0 = arith.constant 0 : index
  %c1 = arith.constant 1 : index
  %buf = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "buf"}], polygeist.varname = "buf"} : memref<64x4xf32>
  affine.for %i = 0 to 64 {
    %0 = affine.load %arg0[%i, %c0] : memref<64x4xf32>
    affine.store %0, %buf[%i, %c0] : memref<64x4xf32>
    %1 = affine.apply affine_map<(d0) -> (d0 + 1)>(%c0)
    %2 = affine.load %arg0[%i, %1] : memref<64x4xf32>
    affine.store %2, %buf[%i, %1] : memref<64x4xf32>
  }
  affine.for %i = 0 to 64 {
    %0 = affine.load %buf[%i, %c0] : memref<64x4xf32>
    %1 = affine.load %buf[%i, %c1] : memref<64x4xf32>
    %2 = arith.addf %0, %1 : f32
    affine.store %2, %arg0[%i, %c0] : memref<64x4xf32>
  }
  return
}

// CHECK-LABEL: func.func @stepped
// CHECK-COUNT-4: memref.alloca() {{.*}} : memref<16xf32>
// CHECK-NOT: arith.select
// CHECK-NOT: store_enable
// CHECK: return
func.func @stepped(%arg0: memref<64xf32>) {
  %buf = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "buf"}], polygeist.varname = "buf"} : memref<64xf32>
  affine.for %j = 0 to 64 step 4 {
    %0 = affine.load %arg0[%j] : memref<64xf32>
    affine.store %0, %buf[%j] : memref<64xf32>
    %1 = affine.load %arg0[%j + 1] : memref<64xf32>
    affine.store %1, %buf[%j + 1] : memref<64xf32>
    %2 = affine.load %buf[%j + 2] : memref<64xf32>
    affine.store %2, %arg0[%j + 3] : memref<64xf32>
  }
  return
}

// CHECK-LABEL: func.func @rotating
// CHECK-COUNT-3: arith.select
// CHECK: return
func.func @rotating(%arg0: memref<64xf32>) {
  %buf = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "buf"}], polygeist.varname = "buf"} : memref<64xf32>
  affine.for %j = 0 to 64 {
    %0 = affine.load %buf[%j] : memref<64xf32>
    affine.store %0, %arg0[%j] : memref<64xf32>
  }
  return
}

// A bank index that is constant only through the counter of a loop that runs
// once or through an index cast (ConstantIndex.h, the definition
// --infer-vitis-split-array td=off uses for rule (b)): one bank, no select
// chain, no store_enable - affine store and load through the single-trip
// counter, affine load with an index-cast symbol, memref load / store with an
// index cast and with the single-trip counter.
// CHECK-LABEL: func.func @single_trip_and_cast
// CHECK-COUNT-4: memref.alloca() {{.*}} : memref<64x1xf32>
// CHECK-NOT: arith.select
// CHECK-NOT: store_enable
// CHECK: return
func.func @single_trip_and_cast(%arg0: memref<64x4xf32>) {
  %c2_i32 = arith.constant 2 : i32
  %c3_i32 = arith.constant 3 : i32
  %s3 = arith.index_cast %c3_i32 : i32 to index
  %buf = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 4 : i32, kind = "cyclic", variable = "buf"}], polygeist.varname = "buf"} : memref<64x4xf32>
  affine.for %k = 1 to 2 {
    affine.for %i = 0 to 64 {
      %0 = affine.load %arg0[%i, %k] : memref<64x4xf32>
      affine.store %0, %buf[%i, %k] : memref<64x4xf32>
      memref.store %0, %buf[%i, %k] : memref<64x4xf32>
      %1 = affine.load %buf[%i, %k] : memref<64x4xf32>
      affine.store %1, %arg0[%i, 0] : memref<64x4xf32>
    }
  }
  affine.for %i = 0 to 64 {
    %0 = affine.load %buf[%i, symbol(%s3)] : memref<64x4xf32>
    %t = arith.index_cast %c2_i32 : i32 to index
    %1 = memref.load %buf[%i, %t] : memref<64x4xf32>
    %2 = arith.addf %0, %1 : f32
    affine.store %2, %arg0[%i, 1] : memref<64x4xf32>
  }
  return
}
