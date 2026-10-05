// RUN: hls-est %s --memory-banking-bram --config-set tool.hls.middle_end.forward_before_banking=true | FileCheck %s
// RUN: hls-est %s --memory-banking-bram --config-set tool.hls.middle_end.forward_before_banking=false | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N138: within a pipelined body, a partitioned local array's load of
// the address stored before is forwarded and the overwritten store removed
// (@fwd); a read of another element in between keeps both stores (@kept).

// CHECK-LABEL: func.func @fwd
// CHECK-COUNT-2: hls.affine.store_enable
// CHECK-NOT: hls.affine.store_enable
// CHECK: return
// OFF-LABEL: func.func @fwd
// OFF-COUNT-4: hls.affine.store_enable
func.func @fwd(%x: memref<8xf32>, %n: index) {
  %acc = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "acc"}]} : memref<8x8xf32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 8 {
      affine.for %k = 0 to 8 step 2 {
        %v0 = affine.load %acc[%i, %j] : memref<8x8xf32>
        %a = affine.load %x[%k] : memref<8xf32>
        %s0 = arith.addf %v0, %a : f32
        affine.store %s0, %acc[%i, %j] : memref<8x8xf32>
        %v1 = affine.load %acc[%i, %j] : memref<8x8xf32>
        %b = affine.load %x[%k + 1] : memref<8xf32>
        %s1 = arith.addf %v1, %b : f32
        affine.store %s1, %acc[%i, %j] : memref<8x8xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
  }
  return
}

// CHECK-LABEL: func.func @kept
// CHECK-COUNT-4: hls.affine.store_enable
func.func @kept(%x: memref<8xf32>) {
  %acc = memref.alloca() {hls.array_partition = [{dim = 2 : i32, factor = 2 : i32, kind = "cyclic", variable = "acc"}]} : memref<8x8xf32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 7 {
      affine.for %k = 0 to 8 step 2 {
        %v0 = affine.load %acc[%i, %j] : memref<8x8xf32>
        %a = affine.load %x[%k] : memref<8xf32>
        %s0 = arith.addf %v0, %a : f32
        affine.store %s0, %acc[%i, %j] : memref<8x8xf32>
        %w = affine.load %acc[%i, %j + 1] : memref<8x8xf32>
        %s1 = arith.addf %s0, %w : f32
        affine.store %s1, %acc[%i, %j] : memref<8x8xf32>
      } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    }
  }
  return
}
