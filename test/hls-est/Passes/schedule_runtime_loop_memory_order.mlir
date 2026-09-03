// RUN: hls-est %s --auto-pipeline-unroll --convert-affine-to-loopschedule | FileCheck %s

// O72 review D6: the body of a pipelined runtime-trip scf.for (VITIS_NOTES.md
// N53) gets the intra-iteration memory ordering an affine body gets from the
// dependence analysis: `a[i] = a[i] * 3; b[i] = a[i];` reloads a[i] after the
// store in the same iteration. Before, the reload was scheduled in an earlier
// stage than the store (no dependence between memref ops of an scf.for).

// CHECK:     loopschedule.pipeline II =
// CHECK:       memref.load %arg0
// CHECK:       arith.muli
// CHECK:       memref.store %{{.*}}, %arg0
// CHECK:       loopschedule.pipeline.stage
// CHECK:       memref.load %arg0
// CHECK:       memref.store %{{.*}}, %arg1

module {
  func.func @top(%a: memref<64xi32>, %b: memref<64xi32>, %n: memref<2xi32>) {
    %c0 = arith.constant 0 : index
    %c1 = arith.constant 1 : index
    %c63 = arith.constant 63 : index
    %c3_i32 = arith.constant 3 : i32
    affine.for %j = 0 to 2 {
      %bnd = affine.load %n[%j] : memref<2xi32>
      %ub = arith.index_cast %bnd : i32 to index
      scf.for %i = %c0 to %ub step %c1 {
        %ii = arith.andi %i, %c63 : index
        %v = memref.load %a[%ii] : memref<64xi32>
        %w = arith.muli %v, %c3_i32 : i32
        memref.store %w, %a[%ii] : memref<64xi32>
        %x = memref.load %a[%ii] : memref<64xi32>
        memref.store %x, %b[%ii] : memref<64xi32>
      } {hls.pipeline = [{II = 0 : i32, source = "user"}]}
    }
    return
  }
}
