// A small kernel for the configuration tests: a 1024 x 32 array filled from
// the input in one loop and read twice per iteration in another (two reads
// per cycle of a pipelined loop), and a 16 x 32 array (512 bits).
module {
  func.func @top(%in: memref<1024xi32>, %out: memref<1024xi32>) {
    %a = memref.alloca() {polygeist.varname = "a"} : memref<1024xi32>
    %s = memref.alloca() {polygeist.varname = "s"} : memref<16xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.store %v, %a[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 16 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.store %v, %s[%i] : memref<16xi32>
    }
    affine.for %i = 0 to 1023 {
      %x = affine.load %a[%i] : memref<1024xi32>
      %y = affine.load %a[%i + 1] : memref<1024xi32>
      %k = affine.load %s[%i mod 16] : memref<16xi32>
      %z = arith.addi %x, %y : i32
      %w = arith.addi %z, %k : i32
      affine.store %w, %out[%i] : memref<1024xi32>
    }
    return
  }
}
