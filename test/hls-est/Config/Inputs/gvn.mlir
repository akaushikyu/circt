// The same address of a 1024 x 32 array loaded twice per iteration: one
// load after Vitis' GVN (one port: RAM_1P), two without (RAM_2P).
module {
  func.func @top(%in: memref<1024xi32>, %out: memref<1024xi32>) {
    %a = memref.alloca() {polygeist.varname = "a"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.store %v, %a[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 1024 {
      %x = affine.load %a[%i] : memref<1024xi32>
      %y = affine.load %a[%i] : memref<1024xi32>
      %z = arith.muli %x, %y : i32
      affine.store %z, %out[%i] : memref<1024xi32>
    }
    return
  }
}
