// The worked kernel of hls-doc/new-architecture.md: a[64] x 12 bits read once
// per cycle, b[1024] x 20 bits accessed once per cycle, c[512] x 40 bits read
// and written in each iteration of one pipelined loop.
module {
  func.func @top(%ia: memref<64xi12>, %ib: memref<1024xi20>, %ic: memref<512xi40>,
                 %oa: memref<64xi12>, %ob: memref<1024xi20>, %oc: memref<512xi40>) {
    %a = memref.alloca() {polygeist.varname = "a"} : memref<64xi12>
    %b = memref.alloca() {polygeist.varname = "b"} : memref<1024xi20>
    %c = memref.alloca() {polygeist.varname = "c"} : memref<512xi40>
    affine.for %i = 0 to 64 {
      %v = affine.load %ia[%i] : memref<64xi12>
      affine.store %v, %a[%i] : memref<64xi12>
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %a[%i] : memref<64xi12>
      affine.store %v, %oa[%i] : memref<64xi12>
    }
    affine.for %i = 0 to 1024 {
      %v = affine.load %ib[%i] : memref<1024xi20>
      affine.store %v, %b[%i] : memref<1024xi20>
    }
    affine.for %i = 0 to 1024 {
      %v = affine.load %b[%i] : memref<1024xi20>
      affine.store %v, %ob[%i] : memref<1024xi20>
    }
    affine.for %i = 0 to 512 {
      %v = affine.load %ic[%i] : memref<512xi40>
      affine.store %v, %c[%i] : memref<512xi40>
    }
    affine.for %i = 0 to 512 {
      %v = affine.load %c[%i] : memref<512xi40>
      %w = affine.load %ic[%i] : memref<512xi40>
      %s = arith.addi %v, %w : i40
      affine.store %s, %c[%i] : memref<512xi40>
    }
    affine.for %i = 0 to 512 {
      %v = affine.load %c[%i] : memref<512xi40>
      affine.store %v, %oc[%i] : memref<512xi40>
    }
    return
  }
}
