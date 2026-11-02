// RUN: split-file %s %t
// RUN: hls-est %t/k.mlir --bram-analysis=math-costs=%S/../../../tools/hls-est-validate/math_costs.json -o /dev/null | FileCheck %s --check-prefix=REAL
// RUN: hls-est %t/k.mlir --bram-analysis=math-costs=%S/../../../tools/hls-est-validate/math_costs.json -o /dev/null 2>&1 >/dev/null | FileCheck %s --check-prefix=REALWARN --allow-empty
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/nosuchfile.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=MISSING
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/badjson.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=BADJSON
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/noentries.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=NOENTRIES
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/version.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=VERSION
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/nobram.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=NOBRAM
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/rule.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=RULE
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/form.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=FORM
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/dup.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=DUP
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/unrolledin.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=UNROLLEDIN
// RUN: not hls-est %t/k.mlir --bram-analysis=math-costs=%t/logiconly.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=LOGICONLY

// The cost table of --bram-analysis=math-costs=: the harness default
// tools/hls-est-validate/math_costs.json parses and prices the corpus cores:
// fft_transpose's double sin
// and cos are two sin_or_cos_double_s instances of 8 (Vitis 16 of its 28),
// the rope pow with a constant base is pow_generic_float_s's 1, the shim
// marker of exp on ap_fixed<32,16> is exp_32_16_s's 5, fabs of double is
// logic only (0). A file that cannot be
// read, is not JSON or breaks the format is an error before any report line.

// REAL-NOT: m_axi
// REAL-DAG: math.core function=sin type=double func=@k instances=1 bram=8 (sin_or_cos_double_s, per_concurrent_call)
// REAL-DAG: math.core function=cos type=double func=@k instances=1 bram=8 (sin_or_cos_double_s, per_concurrent_call)
// REAL-DAG: math.core function=pow type=float arguments=constant_base func=@k instances=1 bram=1 (pow_generic_float_s, per_concurrent_call)
// REAL-DAG: math.core function=exp type=ap_fixed<32,16> func=@k instances=1 bram=5 (exp_32_16_s, per_concurrent_call)
// REAL-DAG: math.core function=abs type=double func=@k instances=1 bram=0 (abs_double, logic_only)
// REAL: Total BRAM: 22
// fabs of double is listed (logic only, 0 BRAM): no unlisted-pair warning.
// REALWARN-NOT: warning

// MISSING: error: --bram-analysis: math-costs: cannot read '{{.*}}nosuchfile.json'
// MISSING-NOT: Total BRAM
// BADJSON: error: --bram-analysis: math-costs: '{{.*}}badjson.json' is not valid JSON
// NOENTRIES: error: --bram-analysis: math-costs: '{{.*}}noentries.json': no "entries" array
// VERSION: error: --bram-analysis: math-costs: '{{.*}}version.json': version 2 is not supported (this hls-est reads version 1)
// NOBRAM: error: --bram-analysis: math-costs: '{{.*}}nobram.json': entries[0]: "bram_18k" is missing or not a non-negative integer
// RULE: error: --bram-analysis: math-costs: '{{.*}}rule.json': entries[0]: unknown instancing rule "per_call"
// FORM: error: --bram-analysis: math-costs: '{{.*}}form.json': entries[0]: "arguments" must be "any", "constant base" or "constant exponent"
// DUP: error: --bram-analysis: math-costs: '{{.*}}dup.json': entries[1]: a second entry for exp of double (arguments "any")
// UNROLLEDIN: error: --bram-analysis: math-costs: '{{.*}}unrolledin.json': entries[0]: "cordic_loop_unrolled_in" must be "any_pipeline" or "user_pipeline"
// LOGICONLY: error: --bram-analysis: math-costs: '{{.*}}logiconly.json': entries[0]: instancing "logic_only" (no memory) needs "bram_18k": 0

//--- badjson.json
{"version": 1, "entries": [ {"function": "exp", }
//--- noentries.json
{"version": 1}
//--- version.json
{"version": 2, "entries": []}
//--- nobram.json
{"version": 1, "entries": [{"function": "exp", "type": "double", "instancing": "operator"}]}
//--- rule.json
{"version": 1, "entries": [{"function": "exp", "type": "double", "bram_18k": 0, "instancing": "per_call"}]}
//--- form.json
{"version": 1, "entries": [{"function": "pow", "type": "float", "bram_18k": 1, "instancing": "operator",
  "arguments": "constant"}]}
//--- dup.json
{"version": 1, "entries": [{"function": "exp", "type": "double", "bram_18k": 0, "instancing": "operator"},
  {"function": "exp", "type": "double", "bram_18k": 1, "instancing": "operator"}]}
//--- unrolledin.json
{"version": 1, "entries": [{"function": "sin", "type": "ap_fixed<16,5>", "bram_18k": 4, "instancing": "cordic_loop",
  "cordic_loop_unrolled_in": "never"}]}
//--- k.mlir
module {
  func.func private @__hlsest_math_exp(f64, i32, i32, i32) -> f64
  func.func @k(%A: memref<512xf64>, %O: memref<512xf64>, %P: memref<512xf64>, %x: f32, %y: i32, %r: memref<2xf32>, %s: memref<1xf64>) {
    affine.for %i = 0 to 512 {
      %0 = affine.load %A[%i] : memref<512xf64>
      %1 = math.sin %0 : f64
      %2 = math.cos %0 : f64
      affine.store %1, %O[%i] : memref<512xf64>
      affine.store %2, %P[%i] : memref<512xf64>
    }
    %base = arith.constant 1.000000e+04 : f32
    %3 = math.powf %base, %x : f32
    affine.store %3, %r[0] : memref<2xf32>
    %c32 = arith.constant 32 : i32
    %c16 = arith.constant 16 : i32
    %c1 = arith.constant 1 : i32
    %4 = arith.sitofp %y : i32 to f64
    %5 = func.call @__hlsest_math_exp(%4, %c32, %c16, %c1) : (f64, i32, i32, i32) -> f64
    %6 = arith.truncf %5 : f64 to f32
    affine.store %6, %r[1] : memref<2xf32>
    %7 = math.absf %4 : f64
    affine.store %7, %s[0] : memref<1xf64>
    return
  }
}
//--- logiconly.json
{"version": 1, "entries": [{"function": "abs", "type": "double", "bram_18k": 1, "instancing": "logic_only"}]}
