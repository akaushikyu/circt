// RUN: split-file %s %t
// RUN: hls-est %t/k.mlir --auto-pipeline-unroll -o - | FileCheck %s --check-prefix=IR
// RUN: hls-est %t/k.mlir --auto-pipeline-unroll "--bram-analysis=top=top math-costs=%t/costs.json" --bram-debug-json=%t/dbg.json -o /dev/null | FileCheck %s
// RUN: FileCheck %s --input-file=%t/dbg.json --check-prefix=JSON

// `#pragma HLS unroll factor=16` on a 100-trip loop: Vitis keeps the 4
// remainder iterations in the exit-checked copies of the unrolled body (no
// epilogue loop), so the loop's 16 calls of a math core are all its call
// sites. --auto-pipeline-unroll unrolls MLIR's cleanup loop into
// straight-line code after the main loop and marks its calls
// hls.unroll_remainder; the math-cost model does not count them again: one
// instance of the core for the pipelined loop (16 calls at II 16), not a
// second one for the 4 copies after it (corpus: class_ece8893_spring_2025
// adithi_upadhya lab2 softmax, exp_33_9_s 7 BRAM in Vitis).

// IR: affine.for %{{.*}} = 0 to 96 step 16 {
// IR-COUNT-16: call @exp_core({{.*}}) {hls.math_core
// IR: } {{{.*}}hls.unroll_partial = 16 : i64}
// IR-COUNT-4: call @exp_core({{.*}}) {hls.math_core = {function = "exp", type = "ap_fixed<33,9>"}, hls.unroll_remainder, hls.user_unroll_copy}

// CHECK: math.core function=exp type=ap_fixed<33,9> func=@top instances=1 bram=7 (exp_33_9_test, per_concurrent_call)
// CHECK: Total BRAM: 7

// JSON-COUNT-4: "status": "remainder"

//--- k.mlir
module {
  func.func private @exp_core(i33) -> i33 attributes {hls.math_core = {function = "exp", type = "ap_fixed<33,9>"}}
  func.func @top(%m: memref<100xi33>) {
    affine.for %j = 0 to 100 {
      %v = affine.load %m[%j] : memref<100xi33>
      %e = func.call @exp_core(%v) {hls.math_core = {function = "exp", type = "ap_fixed<33,9>"}} : (i33) -> i33
      affine.store %e, %m[%j] : memref<100xi33>
    } {hls.unroll = [{factor = 16 : i32, skip_exit_check = false}]}
    return
  }
}

//--- costs.json
{
 "version": 1,
 "entries": [
  {"function": "exp", "type": "ap_fixed<33,9>", "arguments": "any", "core": ["exp_33_9_test"],
   "core_kind": "library_module", "bram_18k": 7, "instancing": "per_concurrent_call"}
 ]
}
