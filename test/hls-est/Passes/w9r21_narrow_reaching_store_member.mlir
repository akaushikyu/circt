// RUN: hls-est %s --narrow-ram-widths=remarks=true -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --narrow-ram-widths=remarks=true --config-set=tool.hls.narrowing.reaching_store_ranges=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-25): VITIS_NOTES N151 (c) on a struct member: cgeist gives
// `row.data[4]` (array_partition complete on .data) a leading dimension of
// extent 1 (memref<1x4xi16>, partition dim 2). That dimension is one register
// too, so a load at constant subscripts takes the range of the store that
// reaches it: the stream value is overwritten by a byte before `out` is
// written (barry_walker lab2 attention_row_local.data -> attention, Vitis 8
// bits). The subscripts are constant expressions (index casts, a multiply and
// a division), as cgeist emits them.
// CHECK: :19:12: remark: narrow-ram-widths: 8 of 16 bits; stored values [0, 255]
// OFF: :19:12: remark: narrow-ram-widths: 16 of 16 bits; stored values [-32768, 32767]
module {
  func.func @top(%in: memref<64x4xi16>, %lut: memref<64x4xi8>, %out: memref<64x4xi16>) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c2 = arith.constant 2 : index
    %row = memref.alloca() {hls.array_partition = [{dim = 2 : i32, kind = "complete", variable = "row.data"}], polygeist.varname = "row"} : memref<1x4xi16>
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<64x4xi16>
    affine.for %i = 0 to 64 {
      %a = affine.load %in[%i, 0] : memref<64x4xi16>
      memref.store %a, %row[%c0, %c0] : memref<1x4xi16>
      %b = affine.load %in[%i, 1] : memref<64x4xi16>
      memref.store %b, %row[%c0, %c1] : memref<1x4xi16>
      %l0 = affine.load %lut[%i, 0] : memref<64x4xi8>
      %e0 = arith.extui %l0 : i8 to i16
      memref.store %e0, %row[%c0, %c0] : memref<1x4xi16>
      %l1 = affine.load %lut[%i, 1] : memref<64x4xi8>
      %e1 = arith.extui %l1 : i8 to i16
      memref.store %e1, %row[%c0, %c1] : memref<1x4xi16>
      %k = arith.index_cast %c1 : index to i32
      %kk = arith.index_cast %k : i32 to index
      %m = arith.muli %kk, %c2 : index
      %j = arith.divui %m, %c2 : index
      %v0 = memref.load %row[%c0, %c0] : memref<1x4xi16>
      affine.store %v0, %buf[%i, 0] : memref<64x4xi16>
      %v1 = memref.load %row[%c0, %j] : memref<1x4xi16>
      affine.store %v1, %buf[%i, 1] : memref<64x4xi16>
    }
    affine.for %i = 0 to 64 {
      affine.for %j = 0 to 4 {
        %v = affine.load %buf[%i, %j] : memref<64x4xi16>
        affine.store %v, %out[%i, %j] : memref<64x4xi16>
      }
    }
    return
  }
}
