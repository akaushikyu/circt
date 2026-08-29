// RUN: split-file %s %t
// RUN: hls-est %t/k.mlir --auto-pipeline-unroll -o - | FileCheck %s --check-prefix=IR
// RUN: hls-est %t/k9.mlir --auto-pipeline-unroll -o - | FileCheck %s --check-prefix=IR9
// RUN: hls-est %t/k.mlir --auto-pipeline-unroll --convert-affine-to-loopschedule "--bram-analysis=top=top math-costs=%t/costs.json" -o /dev/null | FileCheck %s
// RUN: hls-est %t/two.mlir --auto-pipeline-unroll --convert-affine-to-loopschedule "--bram-analysis=top=top math-costs=%t/costs.json" -o /dev/null | FileCheck %s --check-prefix=TWO
// RUN: hls-est %t/part.mlir --auto-pipeline-unroll --convert-affine-to-loopschedule "--bram-analysis=top=top math-costs=%t/costs.json" -o /dev/null | FileCheck %s --check-prefix=PART

// k unrolled copies of `y[i] = hls::exp(x[i])` in a `pipeline off` loop
// read their arguments from one memory with two read ports (x_address0 /
// x_address1): Vitis 2025.1 builds min(k, 2) exp cores (w11rv_r8: trip 10,
// `unroll factor=8`, 2 exp_32_16_s, 10 BRAM; w11rf_exp4, w11rf_sin4 the
// same with k = 4). Two such calls per iteration on x and w get 2 + 2
// (w11rf_exp2a, 20 BRAM); cyclic-partitioned ports keep k (N16 v4n, 4
// instances).

// Trip 10, factor 8: the main loop has one iteration and is promoted, the
// two remainder iterations follow as straight-line code; their calls are
// still marked as copies of the unrolled body's.
// IR-NOT: affine.for
// IR-COUNT-8: call @exp_core({{.*}}) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}} :
// IR-COUNT-2: call @exp_core({{.*}}) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}, hls.unroll_remainder}

// Trip 9, factor 8: both the main loop and the one-iteration cleanup are
// promoted; the last copy is the remainder's.
// IR9-NOT: affine.for
// IR9-COUNT-8: call @exp_core({{.*}}) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}} :
// IR9-NEXT: affine.store
// IR9-NEXT: affine.load
// IR9-NEXT: call @exp_core({{.*}}) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}, hls.unroll_remainder}

// CHECK: math.core function=exp type=ap_fixed<32,16> func=@top instances=2 bram=10
// TWO: math.core function=exp type=ap_fixed<32,16> func=@top instances=4 bram=20
// PART: math.core function=exp type=ap_fixed<32,16> func=@top instances=4 bram=20

//--- k.mlir
module {
  func.func private @exp_core(i32) -> i32 attributes {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}}
  func.func @top(%x: memref<10xi32>, %y: memref<10xi32>) {
    affine.for %i = 0 to 10 {
      %v = affine.load %x[%i] : memref<10xi32>
      %e = func.call @exp_core(%v) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}} : (i32) -> i32
      affine.store %e, %y[%i] : memref<10xi32>
    } {hls.pipeline_off, hls.unroll = [{factor = 8 : i32, skip_exit_check = false}]}
    return
  }
}

//--- k9.mlir
module {
  func.func private @exp_core(i32) -> i32 attributes {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}}
  func.func @top(%x: memref<9xi32>, %y: memref<9xi32>) {
    affine.for %i = 0 to 9 {
      %v = affine.load %x[%i] : memref<9xi32>
      %e = func.call @exp_core(%v) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}} : (i32) -> i32
      affine.store %e, %y[%i] : memref<9xi32>
    } {hls.pipeline_off, hls.unroll = [{factor = 8 : i32, skip_exit_check = false}]}
    return
  }
}

//--- two.mlir
module {
  func.func private @exp_core(i32) -> i32 attributes {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}}
  func.func @top(%x: memref<16xi32>, %w: memref<16xi32>, %y: memref<16xi32>, %z: memref<16xi32>) {
    affine.for %i = 0 to 16 {
      %v = affine.load %x[%i] : memref<16xi32>
      %e = func.call @exp_core(%v) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}} : (i32) -> i32
      affine.store %e, %y[%i] : memref<16xi32>
      %u = affine.load %w[%i] : memref<16xi32>
      %f = func.call @exp_core(%u) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}} : (i32) -> i32
      affine.store %f, %z[%i] : memref<16xi32>
    } {hls.pipeline_off, hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
    return
  }
}

//--- part.mlir
module {
  func.func private @exp_core(i32) -> i32 attributes {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}}
  func.func @top(%x: memref<64xi32> {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "in"}]}, %y: memref<64xi32> {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic", variable = "out"}]}) {
    affine.for %i = 0 to 64 {
      %v = affine.load %x[%i] : memref<64xi32>
      %e = func.call @exp_core(%v) {hls.math_core = {function = "exp", type = "ap_fixed<32,16>"}} : (i32) -> i32
      affine.store %e, %y[%i] : memref<64xi32>
    } {hls.pipeline_off, hls.unroll = [{factor = 4 : i32, skip_exit_check = false}]}
    return
  }
}

//--- costs.json
{
 "version": 1,
 "entries": [
  {"function": "exp", "type": "ap_fixed<32,16>", "arguments": "any", "core": ["exp_32_16_s"],
   "core_kind": "library_module", "bram_18k": 5, "instancing": "per_concurrent_call"}
 ]
}
