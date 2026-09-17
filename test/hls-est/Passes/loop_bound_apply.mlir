// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --convert-affine-to-loopschedule -o - 2>/dev/null | FileCheck %s --check-prefix=IR

// A loop whose bound reads an affine.apply of the enclosing loops' counters
// (polybench nussinov: `for (k = i + 1; k < j; k++)` with `j` computed from
// the counters). --convert-affine-to-loopschedule expands every affine.apply
// into arith ops; the apply is first folded into the bound map, so the loop
// left in place still verifies. Before: "'affine.for' op operand cannot be
// used as a dimension id" (7 polybench__reproducible nussinov designs, W8b).
// The `math.ctlz` (no timing in the model) keeps the inner loop from being
// pipelined, so it stays an affine.for. (Nussinov's `arith.maxsi` did that
// until W9r10-impl gave integer max / min comb timing, OPEN_ISSUES O111 (b).)

// CHECK-NOT: error:
// CHECK: Total BRAM: 0
// IR-LABEL: func.func @bound_apply(
// IR:       affine.for %[[JJ:.*]] = 0 to #map(%{{.*}}) {
// IR-NOT:   affine.apply
// IR:         affine.for %{{.*}} = 0 to #map(%[[JJ]]) {
func.func @bound_apply(%a: memref<60x60xi32>) {
  affine.for %i = 0 to 60 {
    affine.for %jj = 0 to affine_map<(d0) -> (d0)>(%i) {
      %j = affine.apply affine_map<(d0, d1) -> (-d0 + d1 + 60)>(%i, %jj)
      affine.for %k = 0 to affine_map<(d0, d1) -> (d0 + d1 - 60)>(%j, %i) {
        %x = affine.load %a[-%i + 59, %k] : memref<60x60xi32>
        %y = affine.load %a[%k + 1, %j] : memref<60x60xi32>
        %m = arith.addi %x, %y : i32
        %s = math.ctlz %m : i32
        affine.store %s, %a[-%i + 59, %j] : memref<60x60xi32>
      }
    }
  }
  return
}
