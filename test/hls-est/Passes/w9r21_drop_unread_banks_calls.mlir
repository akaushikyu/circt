// RUN: hls-est %s --memory-banking-bram | FileCheck %s
// RUN: hls-est %s --memory-banking-bram --config-set=tool.hls.partitioning.drop_unread_banks=false | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-25): VITIS_NOTES N157 across calls: buf[4][8] complete on
// dim 1 is filled by one callee and read by another that reads rows 0..2 only
// (YOLOv4-Tiny L5: conv_in_buf written by load_input_tile_block_from_DRAM,
// read by conv_7x7). Bank 3 is read nowhere: it is removed with its stores,
// the bank parameters of both callees and the call operands.
// CHECK-LABEL: func.func private @fill(
// CHECK-SAME: memref<1x8xi32>{{.*}}memref<1x8xi32>{{.*}}memref<1x8xi32>{{.*}}, %arg3: memref<8xi32>)
// CHECK-LABEL: func.func private @use(
// CHECK-SAME: memref<1x8xi32>{{.*}}memref<1x8xi32>{{.*}}memref<1x8xi32>{{.*}}, %arg3: memref<8xi32>)
// CHECK-LABEL: func.func @top(
// CHECK-COUNT-3: memref.alloca() {{.*}}: memref<1x8xi32>
// CHECK-NOT: memref.alloca() {{.*}}: memref<1x8xi32>
// CHECK: call @fill({{%[a-z0-9_]+}}, {{%[a-z0-9_]+}}, {{%[a-z0-9_]+}}, %arg0)
// CHECK: call @use({{%[a-z0-9_]+}}, {{%[a-z0-9_]+}}, {{%[a-z0-9_]+}}, %arg1)
// OFF-COUNT-4: memref.alloca() {{.*}}: memref<1x8xi32>
module {
  func.func private @fill(%buf: memref<4x8xi32>, %in: memref<8xi32>) attributes {hls.inline_off} {
    affine.for %r = 0 to 4 {
      affine.for %c = 0 to 8 {
        %v = affine.load %in[%c] : memref<8xi32>
        affine.store %v, %buf[%r, %c] : memref<4x8xi32>
      }
    }
    return
  }
  func.func private @use(%buf: memref<4x8xi32>, %out: memref<8xi32>) attributes {hls.inline_off} {
    affine.for %c = 0 to 8 {
      %a = affine.load %buf[0, %c] : memref<4x8xi32>
      %b = affine.load %buf[1, %c] : memref<4x8xi32>
      %d = affine.load %buf[2, %c] : memref<4x8xi32>
      %s = arith.addi %a, %b : i32
      %t = arith.addi %s, %d : i32
      affine.store %t, %out[%c] : memref<8xi32>
    }
    return
  }
  func.func @top(%in: memref<8xi32>, %out: memref<8xi32>) {
    %buf = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "buf"}], polygeist.varname = "buf"} : memref<4x8xi32>
    func.call @fill(%buf, %in) : (memref<4x8xi32>, memref<8xi32>) -> ()
    func.call @use(%buf, %out) : (memref<4x8xi32>, memref<8xi32>) -> ()
    return
  }
}
