// a[64] x 12 bits read and written in one pipelined loop (a read-modify-write).
module {
  func.func @top(%in: memref<64xi12>, %out: memref<64xi12>) {
    %a = memref.alloca() {polygeist.varname = "a"} : memref<64xi12>
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi12>
      affine.store %v, %a[%i] : memref<64xi12>
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %a[%i] : memref<64xi12>
      %w = arith.addi %v, %v : i12
      affine.store %w, %a[%i] : memref<64xi12>
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %a[%i] : memref<64xi12>
      affine.store %v, %out[%i] : memref<64xi12>
    }
    return
  }
}
