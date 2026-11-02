// A kernel for the scheduling plugin tests: a pipelined loop with a
// floating-point multiply, a pipelined accumulation (an iter_arg recurrence
// through a floating-point add, II 5 with the builtin latencies), and three
// loads of `a` in the function body (a sequential scope).
module {
  func.func @top(%in: memref<64xf32>, %out: memref<64xf32>, %acc: memref<1xf32>) {
    %a = memref.alloca() {polygeist.varname = "a"} : memref<64xf32>
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xf32>
      %m = arith.mulf %v, %v : f32
      affine.store %m, %a[%i] : memref<64xf32>
    }
    %z = arith.constant 0.0 : f32
    %r = affine.for %i = 0 to 64 iter_args(%s = %z) -> f32 {
      %v = affine.load %a[%i] : memref<64xf32>
      %n = arith.addf %s, %v : f32
      affine.yield %n : f32
    }
    affine.store %r, %acc[0] : memref<1xf32>
    %x = affine.load %a[0] : memref<64xf32>
    %y = affine.load %a[1] : memref<64xf32>
    %w = affine.load %a[2] : memref<64xf32>
    %s1 = arith.addf %x, %y : f32
    %s2 = arith.addf %s1, %w : f32
    affine.store %s2, %out[0] : memref<64xf32>
    return
  }
}
