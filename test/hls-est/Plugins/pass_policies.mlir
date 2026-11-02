// The decision passes through plugins of the test plugin: a pipeline policy
// that pipelines nothing (test-pipeline-nothing), a partition policy that
// partitions nothing (test-no-partition) and a fold rule set that folds
// nothing (test-no-fold). Each writes (or leaves out) the IR contract the
// passes after it read.

// RUN: hls-est %s --auto-pipeline-unroll | FileCheck %s --check-prefix=VITIS
// RUN: hls-est %s --load-plugin=%hls_est_test_plugin --config-set tool.hls.pipeline_decision.policy=test-pipeline-nothing --auto-pipeline-unroll | FileCheck %s --check-prefix=NOPIPE
// VITIS: hls.pipeline = [{II = 0 : i32, source = "auto"}]
// NOPIPE-NOT: hls.pipeline

// RUN: hls-est %s --infer-vitis-split-array | FileCheck %s --check-prefix=SMALL
// RUN: hls-est %s --load-plugin=%hls_est_test_plugin --config-set tool.hls.partitioning.policy=test-no-partition --infer-vitis-split-array | FileCheck %s --check-prefix=NOSMALL
// SMALL: hls.registers
// NOSMALL-NOT: hls.registers

// RUN: hls-est %s --vitis-fold | FileCheck %s --check-prefix=FOLD
// RUN: hls-est %s --load-plugin=%hls_est_test_plugin --config-set tool.hls.folding.rule_set=test-no-fold --vitis-fold | FileCheck %s --check-prefix=NOFOLD
// FOLD-NOT: arith.divsi
// NOFOLD: arith.divsi
module {
  func.func @top(%in: memref<64xi32>, %out: memref<64xi32>, %x: i32) {
    %t = memref.alloca() {polygeist.varname = "t"} : memref<4xi32>
    %zero = arith.constant 0 : i32
    %q = arith.divsi %x, %zero : i32
    affine.for %i = 0 to 4 {
      affine.store %q, %t[%i] : memref<4xi32>
    }
    affine.for %i = 0 to 64 {
      %v = affine.load %in[%i] : memref<64xi32>
      %w = affine.load %t[%i mod 4] : memref<4xi32>
      %s = arith.addi %v, %w : i32
      affine.store %s, %out[%i] : memref<64xi32>
    }
    return
  }
}
