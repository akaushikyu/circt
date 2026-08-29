// RUN: split-file %s %t
// RUN: hls-est %t/kernels.mlir --bram-analysis=math-costs=%t/costs.json -o /dev/null > %t/on.out 2> %t/on.err
// RUN: FileCheck %s --input-file=%t/on.out
// RUN: FileCheck %s --input-file=%t/on.err --check-prefix=WARN
// RUN: hls-est %t/kernels.mlir --bram-analysis -o /dev/null > %t/off.out 2> %t/off.err
// RUN: FileCheck %s --input-file=%t/off.out --check-prefix=OFF
// RUN: hls-est %t/kernels.mlir --bram-analysis=math-costs=%t/costs.json --bram-debug --bram-debug-json=%t/dbg.json -o /dev/null > %t/dbg.out 2> %t/dbg.err
// RUN: diff %t/on.out %t/dbg.out
// RUN: FileCheck %s --input-file=%t/dbg.err --check-prefix=DBG
// RUN: FileCheck %s --input-file=%t/dbg.json --check-prefix=JSON
// RUN: hls-est %t/pipe.mlir --convert-affine-to-loopschedule --bram-analysis=math-costs=%t/pipecosts.json -o /dev/null | FileCheck %s --check-prefix=PIPE

// --bram-analysis=math-costs=<file>: every hls:: math call is priced from
// the cost table, BRAM_18K per core instance, instances by the call
// structure. The table here is made up (exp of double costs 5 so that
// instance counts show); the real one is tools/hls-est-validate/
// math_costs.json (math_costs_config.mlir parses it). One function per rule;
// only @filltab holds a memref (its 16 x f64 table, 2 BRAM), everything else
// in the total is math cores.
//
// Outside pipelines one instance per call that can run concurrently:
// independent calls in one straight-line stretch are concurrent (@indep 2), a
// chain f(f(x)) is one instance (@chain), a call in a sequential loop is one
// (@seqloop), k unrolled copies are k, but at most two of them read their
// arguments from one memory at a time (its two ports: @unrolled, 4 copies on
// A, 2; w11rv_r8, W11 review fixes), calls in the two arms
// of an if share one (@excl 1). Calls in different stretches run one after
// the other and share (@around: before and after a loop, 1), except in two
// loops of the function body that access no common array, which Vitis runs
// concurrently (@twoloops_disjoint 2; @twoloops, both loops read A: 1). In a
// loop that
// keeps its hls.pipeline tag (not scheduled here): ceil(calls / requested II)
// (@tagged 3 calls at II 2 -> 2). Constant arguments fold (@folded), an
// unused result is removed (@dead); pow with a constant base takes the
// "constant base" entry (@powcb 1). The shim marker
// __hlsest_math_<fn>(<double args>, W, I, S) carries the ap_fixed type: sin +
// cos of one argument share one CORDIC (@sincos_same 4), on two arguments they
// do not (@sincos_diff 8); a pragma-pipelined loop unrolls the CORDIC loop and
// its table folds (@cordic_tagged 0); an automatically pipelined one keeps the
// sin / cos CORDIC loop (cordic_loop_unrolled_in = user_pipeline: @cordic_auto
// 4) but unrolls tanh's (any_pipeline: @tanh_auto 0). An operator core
// (@sqrt_op) and a logic-only entry (@abs_op) cost 0; an external libm call is
// recognised by name (@libm_exp 5); floor is not a core (@floorcall: no
// record). A callee kept as a module (hls.inline_off) called twice
// concurrently has two instances, each with its own core (@kept 2 x 5). A
// loop that fills a local array from its index and constants is evaluated at
// compile time (@filltab: folded), unless the value meets data (@filldata 5).
// A core that keeps Vitis from pipelining automatically
// (blocks_automatic_pipelining): in an automatically pipelined loop whose 4
// calls are copies from a 4-fold automatic unroll it is one sequential
// instance (@blocked_auto 8), with a pipeline pragma ceil(4 calls / II 2) = 2
// (@blocked_user 16): a loop left unscheduled here gets the II its ports
// allow, two accesses per array per cycle (4 loads of A -> II 2; @tagged's 3
// loads also give II 2). A pair
// the table does not list is reported with a warning and costs 0 (@unknown
// atan float, @ufixed ap_ufixed sin).

// CHECK-DAG: math.core function=exp type=double func=@indep instances=2 bram=10 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@chain instances=1 bram=5 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@seqloop instances=1 bram=5 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@unrolled instances=2 bram=10 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@twoloops instances=1 bram=5 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@twoloops_disjoint instances=2 bram=10 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@excl instances=1 bram=5 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@around instances=1 bram=5 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@tagged instances=2 bram=10 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@folded instances=0 bram=0 (folded: evaluated at compile time)
// CHECK-DAG: math.core function=exp type=double func=@dead instances=0 bram=0 (dead: no call result reaches an output)
// CHECK-DAG: math.core function=pow type=float arguments=constant_base func=@powcb instances=1 bram=1 (pow_generic_float_s, per_concurrent_call)
// CHECK-DAG: math.core function=pow type=float func=@powany instances=1 bram=7 (pow_generic_float_s, per_concurrent_call)
// CHECK-DAG: math.core function=sin type=ap_fixed<16,5> func=@sincos_same instances=1 bram=4 (cordic_apfixed_circ_table_arctan_128, cordic_loop)
// CHECK-DAG: math.core function=sin type=ap_fixed<16,5> func=@sincos_diff instances=1 bram=4 (cordic_apfixed_circ_table_arctan_128, cordic_loop)
// CHECK-DAG: math.core function=cos type=ap_fixed<16,5> func=@sincos_diff instances=1 bram=4 (cordic_apfixed_circ_table_arctan_128, cordic_loop)
// CHECK-DAG: math.core function=sin type=ap_fixed<16,5> func=@cordic_tagged instances=1 bram=0 (cordic_apfixed_circ_table_arctan_128, cordic_loop)
// CHECK-DAG: math.core function=sin type=ap_fixed<16,5> func=@cordic_auto instances=1 bram=4 (cordic_apfixed_circ_table_arctan_128, cordic_loop)
// CHECK-DAG: math.core function=tanh type=ap_fixed<16,5> func=@tanh_auto instances=1 bram=0 (cordic_apfixed_hyperb_table_arctanh_128, cordic_loop)
// CHECK-DAG: math.core function=sqrt type=double func=@sqrt_op instances=1 bram=0 (dsqrt_64ns_64ns_64_57_no_dsp_1, operator)
// CHECK-DAG: math.core function=abs type=float func=@abs_op instances=1 bram=0 (abs_float, logic_only)
// CHECK-DAG: math.core function=exp type=double func=@libm_exp instances=1 bram=5 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=atan type=float func=@unknown instances=1 bram=0 (unknown cost: no entry)
// CHECK-DAG: math.core function=sin type=ap_ufixed<16,5> func=@ufixed instances=1 bram=0 (unknown cost: no entry)
// CHECK-DAG: math.core function=exp type=double func=@kept instances=2 bram=10 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=exp type=double func=@filltab instances=0 bram=0 (folded: evaluated at compile time)
// CHECK-DAG: math.core function=exp type=double func=@filldata instances=1 bram=5 (exp_test_s, per_concurrent_call)
// CHECK-DAG: math.core function=sin type=double func=@blocked_auto instances=1 bram=8 (sin_or_cos_double_s, per_concurrent_call)
// CHECK-DAG: math.core function=sin type=double func=@blocked_user instances=2 bram=16 (sin_or_cos_double_s, per_concurrent_call)
// CHECK-NOT: func=@floorcall
// CHECK: Total BRAM: 135

// WARN-DAG: warning: --bram-analysis: math-costs: no entry for atan of float in {{.*}}costs.json: unknown cost, 0 assumed
// WARN-DAG: warning: --bram-analysis: math-costs: no entry for sin of ap_ufixed<16,5> in {{.*}}costs.json: unknown cost, 0 assumed

// Without the option nothing changes (no path: no math cost).
// OFF-NOT: math.core
// OFF: Total BRAM: 2

// DBG: math core 'cordic_apfixed_circ_table_arctan_128' (math_core) in @sincos_same
// DBG-NEXT: function: sin of ap_fixed<16,5> (type from the shim marker), arguments any
// DBG-NEXT: config: {{.*}}costs.json entries[3]: core cordic_apfixed_circ_table_arctan_128 (inline_cordic), 4 BRAM per instance, instancing cordic_loop, 0 when a pragma-pipelined loop unrolls the CORDIC loop, shares its instance with cos
// DBG-NEXT: sequential {{.*}} stretch 0: 1 call(s) -> 1 instance(s) x 4
// DBG-NEXT: call func.call @__hlsest_math_sin
// DBG-SAME: counted
// DBG-NEXT: call func.call @__hlsest_math_cos
// DBG-SAME: shared (shares the instance of the sin call
// DBG-NEXT: => 1 instance(s), 4 BRAM

// JSON: "id": "sincos_same#math:sin:ap_fixed<16,5>:any",
// JSON: "kind": "math_core",

// Scheduled pipelines (--convert-affine-to-loopschedule): ceil(calls / the
// scheduled II) per loopschedule.pipeline (@user2 2 calls at II 1: 2; @ports4
// 4 calls, 4 loads of A per iteration schedule at II 2: 2), automatic or user
// source (@auto1 1); a chain f(f(x)) whose second call is in a later stage
// stays live through the stage registers (@chain_pipe 2); the CORDIC entry
// folds its table in a pragma-pipelined loop (@cordic_user 0) and keeps it in
// an automatically pipelined one (@cordic_auto 4); a pipelined fill of a
// local array from the induction variable is evaluated at compile time
// (@fill_pipe: folded).
// PIPE-DAG: math.core function=exp type=double func=@user2 instances=2 bram=10 (exp_test_s, per_concurrent_call)
// PIPE-DAG: math.core function=exp type=double func=@ports4 instances=2 bram=10 (exp_test_s, per_concurrent_call)
// PIPE-DAG: math.core function=exp type=double func=@auto1 instances=1 bram=5 (exp_test_s, per_concurrent_call)
// PIPE-DAG: math.core function=exp type=double func=@chain_pipe instances=2 bram=10 (exp_test_s, per_concurrent_call)
// PIPE-DAG: math.core function=sin type=double func=@cordic_user instances=1 bram=0 (cordic_test_table, cordic_loop)
// PIPE-DAG: math.core function=sin type=double func=@cordic_auto instances=1 bram=4 (cordic_test_table, cordic_loop)
// PIPE-DAG: math.core function=exp type=double func=@fill_pipe instances=0 bram=0 (folded: evaluated at compile time)
// PIPE: Total BRAM:

//--- costs.json
{
 "version": 1,
 "entries": [
  {"function": "exp", "type": "double", "arguments": "any", "core": ["exp_test_s"], "core_kind": "library_module",
   "bram_18k": 5, "instancing": "per_concurrent_call"},
  {"function": "pow", "type": "float", "arguments": "any", "core": ["pow_generic_float_s"],
   "core_kind": "library_module", "bram_18k": 7, "instancing": "per_concurrent_call"},
  {"function": "pow", "type": "float", "arguments": "constant base", "core": ["pow_generic_float_s"],
   "core_kind": "library_module", "bram_18k": 1, "instancing": "per_concurrent_call"},
  {"function": "sin", "type": "ap_fixed<16,5>", "arguments": "any", "core": "(inlined into the caller)",
   "core_kind": "inline_cordic", "bram_18k": 4, "instancing": "cordic_loop",
   "tables": [{"name": "cordic_apfixed_circ_table_arctan_128", "words": 128, "bits": 126}],
   "cordic_loop_trip_count": 18, "bram_18k_if_cordic_loop_unrolled": 0, "cordic_loop_unrolled_in": "user_pipeline",
   "shares_instance_with": ["cos"]},
  {"function": "cos", "type": "ap_fixed<16,5>", "arguments": "any", "core": "(inlined into the caller)",
   "core_kind": "inline_cordic", "bram_18k": 4, "instancing": "cordic_loop",
   "tables": [{"name": "cordic_apfixed_circ_table_arctan_128", "words": 128, "bits": 126}],
   "cordic_loop_trip_count": 18, "bram_18k_if_cordic_loop_unrolled": 0, "shares_instance_with": ["sin"]},
  {"function": "sqrt", "type": "double", "arguments": "any", "core": ["dsqrt_64ns_64ns_64_57_no_dsp_1"],
   "core_kind": "fp_operator", "bram_18k": 0, "instancing": "operator"},
  {"function": "abs", "type": "float", "arguments": "any", "core": "(inlined into the caller)",
   "core_kind": "logic_only", "bram_18k": 0, "instancing": "logic_only"},
  {"function": "tanh", "type": "ap_fixed<16,5>", "arguments": "any", "core": "(inlined into the caller)",
   "core_kind": "inline_cordic", "bram_18k": 4, "instancing": "cordic_loop",
   "tables": [{"name": "cordic_apfixed_hyperb_table_arctanh_128", "words": 128, "bits": 124}],
   "cordic_loop_trip_count": 19, "bram_18k_if_cordic_loop_unrolled": 0, "cordic_loop_unrolled_in": "any_pipeline"},
  {"function": "sin", "type": "double", "arguments": "any", "core": ["sin_or_cos_double_s"],
   "core_kind": "library_module", "bram_18k": 8, "instancing": "per_concurrent_call",
   "blocks_automatic_pipelining": true}
 ]
}

//--- kernels.mlir
module {
  func.func private @__hlsest_math_sin(f64, i32, i32, i32) -> f64
  func.func private @__hlsest_math_cos(f64, i32, i32, i32) -> f64
  func.func private @__hlsest_math_tanh(f64, i32, i32, i32) -> f64
  func.func private @exp(f64) -> f64
  func.func private @floor(f64) -> f64

  func.func @indep(%a: f64, %b: f64, %o: memref<2xf64>) {
    %0 = math.exp %a : f64
    %1 = math.exp %b : f64
    affine.store %0, %o[0] : memref<2xf64>
    affine.store %1, %o[1] : memref<2xf64>
    return
  }
  func.func @chain(%a: f64, %o: memref<1xf64>) {
    %0 = math.exp %a : f64
    %1 = math.exp %0 : f64
    affine.store %1, %o[0] : memref<1xf64>
    return
  }
  func.func @seqloop(%A: memref<16xf64>, %O: memref<16xf64>) {
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i] : memref<16xf64>
      %1 = math.exp %0 : f64
      affine.store %1, %O[%i] : memref<16xf64>
    }
    return
  }
  func.func @unrolled(%A: memref<16xf64>, %O: memref<16xf64>) {
    affine.for %i = 0 to 4 {
      %0 = affine.load %A[%i * 4] : memref<16xf64>
      %1 = affine.load %A[%i * 4 + 1] : memref<16xf64>
      %2 = affine.load %A[%i * 4 + 2] : memref<16xf64>
      %3 = affine.load %A[%i * 4 + 3] : memref<16xf64>
      %4 = math.exp %0 : f64
      %5 = math.exp %1 : f64
      %6 = math.exp %2 : f64
      %7 = math.exp %3 : f64
      affine.store %4, %O[%i * 4] : memref<16xf64>
      affine.store %5, %O[%i * 4 + 1] : memref<16xf64>
      affine.store %6, %O[%i * 4 + 2] : memref<16xf64>
      affine.store %7, %O[%i * 4 + 3] : memref<16xf64>
    }
    return
  }
  func.func @twoloops(%A: memref<16xf64>, %O: memref<16xf64>, %P: memref<16xf64>) {
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i] : memref<16xf64>
      %1 = math.exp %0 : f64
      affine.store %1, %O[%i] : memref<16xf64>
    }
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i] : memref<16xf64>
      %1 = math.exp %0 : f64
      affine.store %1, %P[%i] : memref<16xf64>
    }
    return
  }
  func.func @twoloops_disjoint(%A: memref<16xf64>, %B: memref<16xf64>, %O: memref<16xf64>, %P: memref<16xf64>) {
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i] : memref<16xf64>
      %1 = math.exp %0 : f64
      affine.store %1, %O[%i] : memref<16xf64>
    }
    affine.for %i = 0 to 16 {
      %0 = affine.load %B[%i] : memref<16xf64>
      %1 = math.exp %0 : f64
      affine.store %1, %P[%i] : memref<16xf64>
    }
    return
  }
  func.func @excl(%c: i1, %a: f64, %b: f64, %o: memref<1xf64>) {
    %r = scf.if %c -> f64 {
      %0 = math.exp %a : f64
      scf.yield %0 : f64
    } else {
      %1 = math.exp %b : f64
      scf.yield %1 : f64
    }
    affine.store %r, %o[0] : memref<1xf64>
    return
  }
  func.func @around(%a: f64, %b: f64, %A: memref<16xf64>, %O: memref<16xf64>, %o: memref<2xf64>) {
    %0 = math.exp %a : f64
    affine.store %0, %o[0] : memref<2xf64>
    affine.for %i = 0 to 16 {
      %x = affine.load %A[%i] : memref<16xf64>
      %y = arith.mulf %x, %x : f64
      affine.store %y, %O[%i] : memref<16xf64>
    }
    %1 = math.exp %b : f64
    affine.store %1, %o[1] : memref<2xf64>
    return
  }
  func.func @tagged(%A: memref<48xf64>, %O: memref<48xf64>) {
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i * 3] : memref<48xf64>
      %1 = affine.load %A[%i * 3 + 1] : memref<48xf64>
      %2 = affine.load %A[%i * 3 + 2] : memref<48xf64>
      %3 = math.exp %0 : f64
      %4 = math.exp %1 : f64
      %5 = math.exp %2 : f64
      affine.store %3, %O[%i * 3] : memref<48xf64>
      affine.store %4, %O[%i * 3 + 1] : memref<48xf64>
      affine.store %5, %O[%i * 3 + 2] : memref<48xf64>
    } {hls.pipeline = [{II = 2 : i32}]}
    return
  }
  func.func @folded(%o: memref<1xf64>) {
    %c = arith.constant 1.000000e+00 : f64
    %0 = math.exp %c : f64
    affine.store %0, %o[0] : memref<1xf64>
    return
  }
  func.func @dead(%a: f64, %o: memref<1xf64>) {
    %0 = math.exp %a : f64
    %1 = arith.addf %0, %a : f64
    affine.store %a, %o[0] : memref<1xf64>
    return
  }
  func.func @powcb(%x: f32, %o: memref<1xf32>) {
    %c = arith.constant 1.000000e+04 : f32
    %0 = math.powf %c, %x : f32
    affine.store %0, %o[0] : memref<1xf32>
    return
  }
  func.func @powany(%x: f32, %y: f32, %o: memref<1xf32>) {
    %0 = math.powf %x, %y : f32
    affine.store %0, %o[0] : memref<1xf32>
    return
  }
  func.func @sincos_same(%x: i16, %o: memref<2xi16>) {
    %c16 = arith.constant 16 : i32
    %c5 = arith.constant 5 : i32
    %c1 = arith.constant 1 : i32
    %scale = arith.constant 4.8828125E-4 : f64
    %0 = arith.sitofp %x : i16 to f64
    %1 = arith.mulf %0, %scale : f64
    %2 = func.call @__hlsest_math_sin(%1, %c16, %c5, %c1) : (f64, i32, i32, i32) -> f64
    %3 = arith.sitofp %x : i16 to f64
    %4 = arith.mulf %3, %scale : f64
    %5 = func.call @__hlsest_math_cos(%4, %c16, %c5, %c1) : (f64, i32, i32, i32) -> f64
    %6 = arith.fptosi %2 : f64 to i16
    %7 = arith.fptosi %5 : f64 to i16
    affine.store %6, %o[0] : memref<2xi16>
    affine.store %7, %o[1] : memref<2xi16>
    return
  }
  func.func @sincos_diff(%x: i16, %y: i16, %o: memref<2xi16>) {
    %c16 = arith.constant 16 : i32
    %c5 = arith.constant 5 : i32
    %c1 = arith.constant 1 : i32
    %scale = arith.constant 4.8828125E-4 : f64
    %0 = arith.sitofp %x : i16 to f64
    %1 = arith.mulf %0, %scale : f64
    %2 = func.call @__hlsest_math_sin(%1, %c16, %c5, %c1) : (f64, i32, i32, i32) -> f64
    %3 = arith.sitofp %y : i16 to f64
    %4 = arith.mulf %3, %scale : f64
    %5 = func.call @__hlsest_math_cos(%4, %c16, %c5, %c1) : (f64, i32, i32, i32) -> f64
    %6 = arith.fptosi %2 : f64 to i16
    %7 = arith.fptosi %5 : f64 to i16
    affine.store %6, %o[0] : memref<2xi16>
    affine.store %7, %o[1] : memref<2xi16>
    return
  }
  func.func @cordic_tagged(%A: memref<16xi16>, %O: memref<16xi16>) {
    %c16 = arith.constant 16 : i32
    %c5 = arith.constant 5 : i32
    %c1 = arith.constant 1 : i32
    %scale = arith.constant 4.8828125E-4 : f64
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i] : memref<16xi16>
      %1 = arith.sitofp %0 : i16 to f64
      %2 = arith.mulf %1, %scale : f64
      %3 = func.call @__hlsest_math_sin(%2, %c16, %c5, %c1) : (f64, i32, i32, i32) -> f64
      %4 = arith.fptosi %3 : f64 to i16
      affine.store %4, %O[%i] : memref<16xi16>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func @cordic_auto(%A: memref<16xi16>, %O: memref<16xi16>) {
    %c16 = arith.constant 16 : i32
    %c5 = arith.constant 5 : i32
    %c1 = arith.constant 1 : i32
    %scale = arith.constant 4.8828125E-4 : f64
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i] : memref<16xi16>
      %1 = arith.sitofp %0 : i16 to f64
      %2 = arith.mulf %1, %scale : f64
      %3 = func.call @__hlsest_math_sin(%2, %c16, %c5, %c1) : (f64, i32, i32, i32) -> f64
      %4 = arith.fptosi %3 : f64 to i16
      affine.store %4, %O[%i] : memref<16xi16>
    } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
    return
  }
  func.func @tanh_auto(%A: memref<16xi16>, %O: memref<16xi16>) {
    %c16 = arith.constant 16 : i32
    %c5 = arith.constant 5 : i32
    %c1 = arith.constant 1 : i32
    %scale = arith.constant 4.8828125E-4 : f64
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i] : memref<16xi16>
      %1 = arith.sitofp %0 : i16 to f64
      %2 = arith.mulf %1, %scale : f64
      %3 = func.call @__hlsest_math_tanh(%2, %c16, %c5, %c1) : (f64, i32, i32, i32) -> f64
      %4 = arith.fptosi %3 : f64 to i16
      affine.store %4, %O[%i] : memref<16xi16>
    } {hls.pipeline = [{II = 0 : i32, source = "auto"}]}
    return
  }
  func.func @sqrt_op(%a: f64, %o: memref<1xf64>) {
    %0 = math.sqrt %a : f64
    affine.store %0, %o[0] : memref<1xf64>
    return
  }
  func.func @abs_op(%a: f32, %o: memref<1xf32>) {
    %0 = math.absf %a : f32
    affine.store %0, %o[0] : memref<1xf32>
    return
  }
  func.func @libm_exp(%a: f64, %o: memref<1xf64>) {
    %0 = func.call @exp(%a) : (f64) -> f64
    affine.store %0, %o[0] : memref<1xf64>
    return
  }
  func.func @floorcall(%a: f64, %o: memref<1xf64>) {
    %0 = func.call @floor(%a) : (f64) -> f64
    affine.store %0, %o[0] : memref<1xf64>
    return
  }
  func.func @unknown(%a: f32, %o: memref<1xf32>) {
    %0 = math.atan %a : f32
    affine.store %0, %o[0] : memref<1xf32>
    return
  }
  func.func @kept(%a: f64, %o: memref<1xf64>) attributes {hls.inline_off} {
    %0 = math.exp %a : f64
    affine.store %0, %o[0] : memref<1xf64>
    return
  }
  func.func @twice(%a: f64, %b: f64, %o: memref<1xf64>, %p: memref<1xf64>) {
    func.call @kept(%a, %o) : (f64, memref<1xf64>) -> ()
    func.call @kept(%b, %p) : (f64, memref<1xf64>) -> ()
    return
  }
  func.func @filltab(%A: memref<16xf64>, %O: memref<16xf64>) {
    %tab = memref.alloca() : memref<16xf64>
    %s = arith.constant 0.25 : f64
    affine.for %i = 0 to 16 {
      %0 = arith.index_cast %i : index to i32
      %1 = arith.sitofp %0 : i32 to f64
      %2 = arith.mulf %1, %s : f64
      %3 = math.exp %2 : f64
      affine.store %3, %tab[%i] : memref<16xf64>
    }
    affine.for %i = 0 to 16 {
      %0 = affine.load %tab[%i] : memref<16xf64>
      %1 = affine.load %A[%i] : memref<16xf64>
      %2 = arith.mulf %0, %1 : f64
      affine.store %2, %O[%i] : memref<16xf64>
    }
    return
  }
  func.func @filldata(%A: memref<16xf64>, %O: memref<16xf64>) {
    %s = arith.constant 0.25 : f64
    affine.for %i = 0 to 16 {
      %0 = arith.index_cast %i : index to i32
      %1 = arith.sitofp %0 : i32 to f64
      %2 = arith.mulf %1, %s : f64
      %3 = math.exp %2 : f64
      %4 = affine.load %A[%i] : memref<16xf64>
      %5 = arith.mulf %3, %4 : f64
      affine.store %5, %O[%i] : memref<16xf64>
    }
    return
  }
  func.func @blocked_auto(%A: memref<64xf64>, %O: memref<64xf64>) {
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i * 4] : memref<64xf64>
      %1 = affine.load %A[%i * 4 + 1] : memref<64xf64>
      %2 = affine.load %A[%i * 4 + 2] : memref<64xf64>
      %3 = affine.load %A[%i * 4 + 3] : memref<64xf64>
      %4 = math.sin %0 : f64
      %5 = math.sin %1 : f64
      %6 = math.sin %2 : f64
      %7 = math.sin %3 : f64
      affine.store %4, %O[%i * 4] : memref<64xf64>
      affine.store %5, %O[%i * 4 + 1] : memref<64xf64>
      affine.store %6, %O[%i * 4 + 2] : memref<64xf64>
      affine.store %7, %O[%i * 4 + 3] : memref<64xf64>
    } {hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.auto_unrolled = [{factor = 4 : i64}]}
    return
  }
  func.func @blocked_user(%A: memref<64xf64>, %O: memref<64xf64>) {
    affine.for %i = 0 to 16 {
      %0 = affine.load %A[%i * 4] : memref<64xf64>
      %1 = affine.load %A[%i * 4 + 1] : memref<64xf64>
      %2 = affine.load %A[%i * 4 + 2] : memref<64xf64>
      %3 = affine.load %A[%i * 4 + 3] : memref<64xf64>
      %4 = math.sin %0 : f64
      %5 = math.sin %1 : f64
      %6 = math.sin %2 : f64
      %7 = math.sin %3 : f64
      affine.store %4, %O[%i * 4] : memref<64xf64>
      affine.store %5, %O[%i * 4 + 1] : memref<64xf64>
      affine.store %6, %O[%i * 4 + 2] : memref<64xf64>
      affine.store %7, %O[%i * 4 + 3] : memref<64xf64>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func @ufixed(%x: i16, %o: memref<1xi16>) {
    %c16 = arith.constant 16 : i32
    %c5 = arith.constant 5 : i32
    %c0 = arith.constant 0 : i32
    %0 = arith.uitofp %x : i16 to f64
    %1 = func.call @__hlsest_math_sin(%0, %c16, %c5, %c0) : (f64, i32, i32, i32) -> f64
    %2 = arith.fptoui %1 : f64 to i16
    affine.store %2, %o[0] : memref<1xi16>
    return
  }
}

//--- pipecosts.json
{"version": 1, "entries": [
 {"function": "exp", "type": "double", "instancing": "per_concurrent_call", "bram_18k": 5, "core": "exp_test_s"},
 {"function": "sin", "type": "double", "instancing": "cordic_loop", "bram_18k": 4, "core": "cordic_test_table", "bram_18k_if_cordic_loop_unrolled": 0, "cordic_loop_unrolled_in": "user_pipeline"}]}

//--- pipe.mlir
module {
  func.func @user2(%A: memref<64xf64>, %O: memref<64xf64>) {
    affine.for %i = 0 to 32 {
      %0 = affine.load %A[%i * 2] : memref<64xf64>
      %1 = affine.load %A[%i * 2 + 1] : memref<64xf64>
      %2 = math.exp %0 : f64
      %3 = math.exp %1 : f64
      affine.store %2, %O[%i * 2] : memref<64xf64>
      affine.store %3, %O[%i * 2 + 1] : memref<64xf64>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func @ports4(%A: memref<128xf64>, %O: memref<64xf64>, %P: memref<64xf64>) {
    affine.for %i = 0 to 32 {
      %0 = affine.load %A[%i * 4] : memref<128xf64>
      %1 = affine.load %A[%i * 4 + 1] : memref<128xf64>
      %2 = affine.load %A[%i * 4 + 2] : memref<128xf64>
      %3 = affine.load %A[%i * 4 + 3] : memref<128xf64>
      %4 = math.exp %0 : f64
      %5 = math.exp %1 : f64
      %6 = math.exp %2 : f64
      %7 = math.exp %3 : f64
      affine.store %4, %O[%i * 2] : memref<64xf64>
      affine.store %5, %O[%i * 2 + 1] : memref<64xf64>
      affine.store %6, %P[%i * 2] : memref<64xf64>
      affine.store %7, %P[%i * 2 + 1] : memref<64xf64>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func @auto1(%A: memref<64xf64>, %O: memref<64xf64>) {
    affine.for %i = 0 to 64 {
      %0 = affine.load %A[%i] : memref<64xf64>
      %1 = math.exp %0 : f64
      affine.store %1, %O[%i] : memref<64xf64>
    }
    return
  }
  func.func @chain_pipe(%A: memref<64xf64>, %O: memref<64xf64>) {
    affine.for %i = 0 to 64 {
      %0 = affine.load %A[%i] : memref<64xf64>
      %1 = math.exp %0 : f64
      %2 = arith.mulf %1, %1 : f64
      %3 = math.exp %2 : f64
      %4 = arith.addf %3, %0 : f64
      affine.store %4, %O[%i] : memref<64xf64>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func @cordic_user(%A: memref<64xf64>, %O: memref<64xf64>) {
    affine.for %i = 0 to 64 {
      %0 = affine.load %A[%i] : memref<64xf64>
      %1 = math.sin %0 : f64
      affine.store %1, %O[%i] : memref<64xf64>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
  func.func @cordic_auto(%A: memref<64xf64>, %O: memref<64xf64>) {
    affine.for %i = 0 to 64 {
      %0 = affine.load %A[%i] : memref<64xf64>
      %1 = math.sin %0 : f64
      affine.store %1, %O[%i] : memref<64xf64>
    }
    return
  }
  func.func @fill_pipe(%A: memref<64xf64>, %O: memref<64xf64>) {
    %t = memref.alloca() : memref<64xf64>
    affine.for %i = 0 to 64 {
      %c = arith.index_cast %i : index to i32
      %f = arith.sitofp %c : i32 to f64
      %e = math.exp %f : f64
      affine.store %e, %t[%i] : memref<64xf64>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 64 {
      %0 = affine.load %A[%i] : memref<64xf64>
      %1 = affine.load %t[%i] : memref<64xf64>
      %2 = arith.mulf %0, %1 : f64
      affine.store %2, %O[%i] : memref<64xf64>
    }
    return
  }
}
