// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll | FileCheck %s --check-prefixes=CHECK,FLT
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll=float-loads-perfect | FileCheck %s --check-prefixes=CHECK,FLT
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll=float-loads-perfect=false | FileCheck %s --check-prefixes=CHECK,OFF
//
// VITIS_NOTES.md N3, exp-src/pipeline_unroll_float: a read-only load at an
// inner-invariant address makes a nest imperfect (inner loop unrolled, outer
// loop pipelined) only when the loaded element is an INTEGER. Vitis converts
// the same nest loading a FLOAT element into a perfect nest and flattens it
// ([HLS 200-2061] + [XFORM 203-541]; rv_st_hoist_f_m64_n64, pf_fmul_m8_n64,
// pf_fadd_m8_n64, pf_fmac_m8_n32, pf_srchoist_m8_n64, pm_floatarr_iop_m8_n64,
// rv_rmw_hoist_f_m8_n64 / _m64_n64; polybench atax lp3/lp4, bicg lp1/lp2),
// while every integer twin is unrolled (pu_st_hoist_m8_n16,
// rv_st_hoist_m64_n64, pi_add_m8_n64, pi_mul3_m8_n64, pl_mul_m8_n64,
// pi_srchoist_m8_n64, pm_intarr_fop_m8_n64; pf_twoload_m8_n64: one float and
// one int invariant load -> unrolled). Register promotion of an accumulator
// makes the nest imperfect whatever the element type (pf_memred_m8_n16).
//
// The rule is option float-loads-perfect (FLT), on by default since W1c
// (MEMOS.md M8, decision #3); =false (OFF) keeps the original T3 rule:
// every hoistable invariant load breaks perfectness.

// CHECK-LABEL: func.func @hoisted_load_f
// FLT:         affine.for %{{.*}} = 0 to 8 {
// FLT-NEXT:      affine.for %{{.*}} = 0 to 16 {
// FLT:           } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// FLT-NEXT:    }
// OFF:         affine.for %{{.*}} = 0 to 8 {
// OFF-NOT:       affine.for
// OFF:         } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @hoisted_load_f(%a: memref<8x16xf32>, %b: memref<8xf32>, %out: memref<8x16xf32>) {
  %cst = arith.constant 1.0 : f32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x16xf32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xf32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xf32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 16 {
      %0 = affine.load %la[%i, %j] : memref<8x16xf32>
      %1 = affine.load %lb[%i] : memref<8xf32>
      %2 = arith.mulf %0, %1 : f32
      %3 = arith.addf %2, %cst : f32
      affine.store %3, %lo[%i, %j] : memref<8x16xf32>
    }
  }
  return
}

// It is the type of the hoisted load, not of the arithmetic: int elements
// converted to float and multiplied are unrolled in both modes
// (pm_intarr_fop_m8_n64) ...
// CHECK-LABEL: func.func @hoisted_load_int_fop
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @hoisted_load_int_fop(%a: memref<8x16xi32>, %b: memref<8xi32>, %out: memref<8x16xi32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x16xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xi32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 16 {
      %0 = affine.load %la[%i, %j] : memref<8x16xi32>
      %1 = affine.load %lb[%i] : memref<8xi32>
      %2 = arith.sitofp %0 : i32 to f32
      %3 = arith.sitofp %1 : i32 to f32
      %4 = arith.mulf %2, %3 : f32
      %5 = arith.fptosi %4 : f32 to i32
      affine.store %5, %lo[%i, %j] : memref<8x16xi32>
    }
  }
  return
}

// ... and float elements combined with integer arithmetic are flattened
// under the rule (pm_floatarr_iop_m8_n64).
// CHECK-LABEL: func.func @hoisted_load_f_iop
// FLT:         affine.for %{{.*}} = 0 to 8 {
// FLT-NEXT:      affine.for %{{.*}} = 0 to 16 {
// FLT:           } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// OFF:         affine.for %{{.*}} = 0 to 8 {
// OFF-NOT:       affine.for
// OFF:         } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @hoisted_load_f_iop(%a: memref<8x16xf32>, %b: memref<8xf32>, %out: memref<8x16xf32>) {
  %c1 = arith.constant 1 : i32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x16xf32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xf32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xf32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 16 {
      %0 = affine.load %la[%i, %j] : memref<8x16xf32>
      %1 = affine.load %lb[%i] : memref<8xf32>
      %2 = arith.bitcast %0 : f32 to i32
      %3 = arith.bitcast %1 : f32 to i32
      %4 = arith.muli %2, %3 : i32
      %5 = arith.addi %4, %c1 : i32
      %6 = arith.bitcast %5 : i32 to f32
      affine.store %6, %lo[%i, %j] : memref<8x16xf32>
    }
  }
  return
}

// One float and one int invariant load: the int load alone makes the nest
// imperfect (pf_twoload_m8_n64) - unrolled in both modes.
// CHECK-LABEL: func.func @twoload
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @twoload(%a: memref<8x16xf32>, %b: memref<8xf32>, %c: memref<8xi32>, %out: memref<8x16xf32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x16xf32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xf32>
  %lc = memref.alloca() {hls.preserve, polygeist.varname = "lc"} : memref<8xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xf32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 16 {
      %0 = affine.load %la[%i, %j] : memref<8x16xf32>
      %1 = affine.load %lb[%i] : memref<8xf32>
      %2 = affine.load %lc[%i] : memref<8xi32>
      %3 = arith.sitofp %2 : i32 to f32
      %4 = arith.mulf %0, %1 : f32
      %5 = arith.addf %4, %3 : f32
      affine.store %5, %lo[%i, %j] : memref<8x16xf32>
    }
  }
  return
}

// A float accumulator promoted across the inner loop makes the nest
// imperfect in both modes: j unrolled, i pipelined (pf_memred_m8_n16; atax
// lp1/lp2, bicg lp3/lp4, gesummv, mvt).
// CHECK-LABEL: func.func @promote_f
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @promote_f(%a: memref<8x16xf32>, %b: memref<16xf32>, %out: memref<8xf32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8xf32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<16xf32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xf32>
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 16 {
      %0 = affine.load %lo[%i] : memref<8xf32>
      %1 = affine.load %la[%i, %j] : memref<8x16xf32>
      %2 = affine.load %lb[%j] : memref<16xf32>
      %3 = arith.mulf %1, %2 : f32
      %4 = arith.addf %0, %3 : f32
      affine.store %4, %lo[%i] : memref<8xf32>
    }
  }
  return
}

// The float load already sits before the inner loop - moved there by
// cgeist's own LICM (the MLIR of rv_st_hoist_f_m64_n64 / pf_fmul_m8_n64) or
// written there in the source (pf_srchoist_m8_n64). Under the rule it is
// judged as if it were in the inner loop: flattened.
// CHECK-LABEL: func.func @cgeist_hoisted_f
// FLT:         affine.for %{{.*}} = 0 to 8 {
// FLT-NEXT:      affine.load
// FLT-NEXT:      affine.for %{{.*}} = 0 to 16 {
// FLT:           } {hls.flattened_parents = 1 : i64, hls.pipeline = [{II = 0 : i32, source = "auto"}]}
// FLT-NEXT:    }
// OFF:         affine.for %{{.*}} = 0 to 8 {
// OFF-NOT:       affine.for
// OFF:         } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @cgeist_hoisted_f(%a: memref<8x16xf32>, %b: memref<8xf32>, %out: memref<8x16xf32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x16xf32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xf32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xf32>
  affine.for %i = 0 to 8 {
    %0 = affine.load %lb[%i] : memref<8xf32>
    affine.for %j = 0 to 16 {
      %1 = affine.load %la[%i, %j] : memref<8x16xf32>
      %2 = arith.mulf %1, %0 : f32
      affine.store %2, %lo[%i, %j] : memref<8x16xf32>
    }
  }
  return
}

// The integer form of the same MLIR stays imperfect in both modes
// (pi_srchoist_m8_n64): j unrolled, i pipelined.
// CHECK-LABEL: func.func @cgeist_hoisted_i
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @cgeist_hoisted_i(%a: memref<8x16xi32>, %b: memref<8xi32>, %out: memref<8x16xi32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x16xi32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xi32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xi32>
  affine.for %i = 0 to 8 {
    %0 = affine.load %lb[%i] : memref<8xi32>
    affine.for %j = 0 to 16 {
      %1 = affine.load %la[%i, %j] : memref<8x16xi32>
      %2 = arith.muli %1, %0 : i32
      affine.store %2, %lo[%i, %j] : memref<8x16xi32>
    }
  }
  return
}

// A float load from a memory the inner loop writes cannot be sunk back:
// imperfect, unrolled in both modes.
// CHECK-LABEL: func.func @cgeist_hoisted_f_written
// CHECK:       affine.for %{{.*}} = 0 to 8 {
// CHECK-NOT:     affine.for
// CHECK:       } {hls.auto_unrolled = [{factor = 16 : i64, loc = #loc{{[0-9]*}}}], hls.pipeline = [{II = 0 : i32, source = "auto"}]}
func.func @cgeist_hoisted_f_written(%a: memref<8x16xf32>, %b: memref<8xf32>, %out: memref<8x16xf32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<8x16xf32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xf32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<8x16xf32>
  affine.for %i = 0 to 8 {
    %0 = affine.load %lb[%i] : memref<8xf32>
    affine.for %j = 0 to 16 {
      %1 = affine.load %la[%i, %j] : memref<8x16xf32>
      %2 = arith.mulf %1, %0 : f32
      affine.store %2, %lo[%i, %j] : memref<8x16xf32>
      affine.store %2, %lb[%j floordiv 2] : memref<8xf32>
    }
  }
  return
}
