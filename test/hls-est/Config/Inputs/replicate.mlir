// A 1024 x 32 array read eight times per iteration of a pipelined loop
// (Vitis: RAM_1WNR with ceil(8 / II) - 1 copies).
module {
  func.func @top(%in: memref<1024xi32>, %out: memref<1024xi32>) {
    %a = memref.alloca() {polygeist.varname = "a"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.store %v, %a[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 1016 {
      %x0 = affine.load %a[%i] : memref<1024xi32>
      %x1 = affine.load %a[%i + 1] : memref<1024xi32>
      %x2 = affine.load %a[%i + 2] : memref<1024xi32>
      %x3 = affine.load %a[%i + 3] : memref<1024xi32>
      %x4 = affine.load %a[%i + 4] : memref<1024xi32>
      %x5 = affine.load %a[%i + 5] : memref<1024xi32>
      %x6 = affine.load %a[%i + 6] : memref<1024xi32>
      %x7 = affine.load %a[%i + 7] : memref<1024xi32>
      %s0 = arith.addi %x0, %x1 : i32
      %s1 = arith.addi %x2, %x3 : i32
      %s2 = arith.addi %x4, %x5 : i32
      %s3 = arith.addi %x6, %x7 : i32
      %t0 = arith.addi %s0, %s1 : i32
      %t1 = arith.addi %s2, %s3 : i32
      %u = arith.addi %t0, %t1 : i32
      affine.store %u, %out[%i] : memref<1024xi32>
    }
    return
  }
}
