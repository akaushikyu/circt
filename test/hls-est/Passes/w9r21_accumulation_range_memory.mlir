// RUN: hls-est %s --narrow-ram-widths=remarks=true -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --narrow-ram-widths=remarks=true --config-set=tool.hls.narrowing.accumulation_ranges=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-25): VITIS_NOTES N159, the memory form: `acc[i] = 0` before
// a loop of 8 trips whose body is `acc[i] = acc[i] + x` (x an unsigned byte,
// the address invariant in the loop) ranges over 8 x 255 = 2040: 11 bits
// (Analog-CIM optimized output_buf: 2509 x 23, Vitis 6 BRAM). Off: the
// read-modify-write makes acc a cycle of arrays, full range.
// CHECK: remark: narrow-ram-widths: 11 of 32 bits; stored values [0, 2040]
// OFF: remark: narrow-ram-widths: 32 of 32 bits{{.*}}on a cycle of arrays
module {
  func.func @top(%in: memref<64x8xi8>, %out: memref<64xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %acc = memref.alloca() {polygeist.varname = "acc"} : memref<64xi32>
    affine.for %i = 0 to 64 {
      affine.store %c0_i32, %acc[%i] : memref<64xi32>
      affine.for %m = 0 to 8 {
        %v = affine.load %acc[%i] : memref<64xi32>
        %b = affine.load %in[%i, %m] : memref<64x8xi8>
        %x = arith.extui %b : i8 to i32
        %s = arith.addi %v, %x : i32
        affine.store %s, %acc[%i] : memref<64xi32>
      }
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %acc[%i] : memref<64xi32>
      affine.store %v, %out[%i] : memref<64xi32>
    }
    return
  }
}
