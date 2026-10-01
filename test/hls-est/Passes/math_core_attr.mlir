// RUN: split-file %s %t
// RUN: hls-est %t/k.mlir --lower-polygeist-subindex -o - | FileCheck %s --check-prefix=IR
// RUN: hls-est %t/k.mlir --lower-polygeist-subindex --inline "--bram-analysis=top=top math-costs=%t/costs.json" -o /dev/null | FileCheck %s
// RUN: hls-est %t/plain.mlir --lower-polygeist-subindex -o - | FileCheck %s --check-prefix=PLAIN

// cgeist --xlx-headers marks a call of an hls:: math function of the real
// hls_math.h, and the callee, with hls.math_core (Polygeist XlxMathCore.h).
// --lower-polygeist-subindex drops the callee's body - the library's code,
// here a CORDIC loop over its arctanh table - and the private symbols only
// it used (@table, @helper); the --bram-analysis math-cost model then prices
// the call as the core of the cost table (VITIS_NOTES N16), as it prices the
// stand-in headers' __hlsest_math_<fn> markers: a call in a sequential loop
// is one instance of tanh ap_fixed<16,5> (4 BRAM), the float overload's type
// is its operand's (@fl: exp float, 0 BRAM). The table is not priced as a
// memory of the design. A module without the attribute is unchanged (PLAIN).

// IR-NOT: @table
// IR-NOT: @helper
// IR-DAG: func.func private @tanh16_5(i16) -> i16 attributes {hls.core_tables = {{\[\[}}128, 128, "table"{{\]\]}}, hls.math_core = {function = "tanh", type = "ap_fixed<16,5>"}}
// IR-DAG: func.func private @expf_core(f32) -> f32 attributes {hls.math_core = {function = "exp"}}
// IR-LABEL: func.func @top
// IR: call @tanh16_5(%{{.*}}) {hls.math_core = {function = "tanh", type = "ap_fixed<16,5>"}}

// CHECK-DAG: math.core function=tanh type=ap_fixed<16,5> func=@top instances=1 bram=4 (cordic_apfixed_hyperb_table_arctanh_128, cordic_loop)
// CHECK-DAG: math.core function=exp type=float func=@top instances=1 bram=0
// CHECK: Total BRAM: 4

// PLAIN: memref.global "private" constant @table
// PLAIN: func.func private @helper
// PLAIN: func.func private @tanh16_5(%arg0: i16) -> i16 {

//--- k.mlir
module {
  memref.global "private" constant @table : memref<128xi128> = dense<1>
  func.func private @helper(%arg0: i128) -> i128 {
    return %arg0 : i128
  }
  func.func private @tanh16_5(%arg0: i16) -> i16 attributes {hls.math_core = {function = "tanh", type = "ap_fixed<16,5>"}} {
    %t = memref.get_global @table : memref<128xi128>
    %acc = memref.alloca() : memref<1xi128>
    affine.for %i = 0 to 19 {
      %v = affine.load %t[%i] : memref<128xi128>
      %w = func.call @helper(%v) : (i128) -> i128
      affine.store %w, %acc[0] : memref<1xi128>
    }
    %r = affine.load %acc[0] : memref<1xi128>
    %x = arith.trunci %r : i128 to i16
    %y = arith.addi %x, %arg0 : i16
    return %y : i16
  }
  func.func private @expf_core(f32) -> f32 attributes {hls.math_core = {function = "exp"}}
  func.func @top(%in: memref<64xi16>, %out: memref<64xi16>, %f: memref<64xf32>) {
    affine.for %i = 0 to 64 {
      %a = affine.load %in[%i] : memref<64xi16>
      %b = func.call @tanh16_5(%a) {hls.math_core = {function = "tanh", type = "ap_fixed<16,5>"}} : (i16) -> i16
      affine.store %b, %out[%i] : memref<64xi16>
      %c = affine.load %f[%i] : memref<64xf32>
      %d = func.call @expf_core(%c) {hls.math_core = {function = "exp"}} : (f32) -> f32
      affine.store %d, %f[%i] : memref<64xf32>
    } {hls.pipeline_off}
    return
  }
}

//--- plain.mlir
module {
  memref.global "private" constant @table : memref<128xi128> = dense<1>
  func.func private @helper(%arg0: i128) -> i128 {
    return %arg0 : i128
  }
  func.func private @tanh16_5(%arg0: i16) -> i16 {
    %t = memref.get_global @table : memref<128xi128>
    %c0 = arith.constant 0 : index
    %v = memref.load %t[%c0] : memref<128xi128>
    %w = func.call @helper(%v) : (i128) -> i128
    %x = arith.trunci %w : i128 to i16
    return %x : i16
  }
  func.func @top(%a: i16) -> i16 {
    %b = func.call @tanh16_5(%a) : (i16) -> i16
    return %b : i16
  }
}

//--- costs.json
{
 "version": 1,
 "entries": [
  {"function": "tanh", "type": "ap_fixed<16,5>", "arguments": "any", "core": "(inlined into the caller)",
   "core_kind": "inline_cordic", "bram_18k": 4, "instancing": "cordic_loop",
   "tables": [{"name": "cordic_apfixed_hyperb_table_arctanh_128", "words": 128, "bits": 124}],
   "cordic_loop_trip_count": 19, "bram_18k_if_cordic_loop_unrolled": 0, "cordic_loop_unrolled_in": "any_pipeline"},
  {"function": "exp", "type": "float", "arguments": "any", "core": ["fexp_test"],
   "core_kind": "fp_operator", "bram_18k": 0, "instancing": "operator"}
 ]
}
