// RUN: hls-est %s --symbol-privatize=exclude=viterbi --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=viterbi --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug --bram-debug-json=%t.json -o /dev/null 2> %t.err | FileCheck %s
// RUN: FileCheck %s --check-prefix=TEXT --input-file=%t.err
// RUN: FileCheck %s --check-prefix=JSON --input-file=%t.json

// OPEN_ISSUES.md O9: the simplex modulo scheduler asserted (`succeeded(solved)`)
// when an II bump left an infeasible tableau. It now reports the failure and
// --convert-affine-to-loopschedule falls back to the greedy resource-bound
// scheduler. Input: machsuite viterbi, cgeist with the width-exact shim
// (`--shim exact`), unchanged; Vitis td=off gives 128 BRAM (results/vitis.json).

// CHECK: Total BRAM: 128

// T7: --bram-debug names the scheduler of each pipeline. The two loops whose
// simplex II bump failed are the II-32 ones: the 64-trip inner loop flattened
// into its parent and the 139-trip outer loop.
// TEXT: pipeline @ {{.*}} in @viterbi: ii=1 trip=64 {{.*}} scheduler=simplex{{$}}
// TEXT: pipeline @ {{.*}} in @viterbi: ii=32 trip=64 {{.*}} scheduler=greedy (simplex failed){{$}}
// TEXT: pipeline @ {{.*}} in @viterbi: ii=1 trip=63 {{.*}} scheduler=simplex{{$}}
// TEXT: pipeline @ {{.*}} in @viterbi: ii=32 trip=139 {{.*}} scheduler=greedy (simplex failed){{$}}
// JSON: "pipelines": [
// JSON: "scheduler": "simplex",
// JSON: "scheduler": "greedy (simplex failed)",
// JSON: "scheduler": "simplex",
// JSON: "scheduler": "greedy (simplex failed)",

module {
  func.func @viterbi(%arg0: memref<140xi8>, %arg1: memref<64xf64>, %arg2: memref<4096xf64>, %arg3: memref<4096xf64>, %arg4: memref<140xi8>) -> i32 attributes {hls.orig_name = "viterbi", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %c64_i32 = arith.constant 64 : i32
    %c0_i8 = arith.constant 0 : i8
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "llike"} : memref<140x64xf64>
    %0 = affine.load %arg0[0] : memref<140xi8>
    %1 = arith.extui %0 : i8 to i32
    %2 = arith.index_cast %1 : i32 to index
    affine.for %arg5 = 0 to 64 {
      %5 = affine.load %arg1[%arg5] : memref<64xf64>
      %6 = affine.load %arg3[%arg5 * 64 + symbol(%2)] : memref<4096xf64>
      %7 = arith.addf %5, %6 : f64
      affine.store %7, %alloca[0, %arg5] : memref<140x64xf64>
    }
    affine.for %arg5 = 1 to 140 {
      %5 = affine.load %arg0[%arg5] : memref<140xi8>
      %6 = arith.extui %5 : i8 to i32
      %7 = affine.load %arg0[%arg5] : memref<140xi8>
      %8 = arith.extui %7 : i8 to i32
      affine.for %arg6 = 0 to 64 {
        %9 = arith.index_cast %arg6 : index to i8
        %10 = arith.extui %9 : i8 to i32
        %11 = affine.load %alloca[%arg5 - 1, 0] : memref<140x64xf64>
        %12 = affine.load %arg2[%arg6] : memref<4096xf64>
        %13 = arith.addf %11, %12 : f64
        %14 = arith.muli %10, %c64_i32 : i32
        %15 = arith.addi %14, %6 : i32
        %16 = arith.index_cast %15 : i32 to index
        %17 = memref.load %arg3[%16] : memref<4096xf64>
        %18 = arith.addf %13, %17 : f64
        %19 = arith.addi %14, %8 : i32
        %20 = arith.index_cast %19 : i32 to index
        %21 = memref.load %arg3[%20] : memref<4096xf64>
        %22 = affine.for %arg7 = 1 to 64 iter_args(%arg8 = %18) -> (f64) {
          %23 = affine.load %alloca[%arg5 - 1, %arg7] : memref<140x64xf64>
          %24 = affine.load %arg2[%arg6 + %arg7 * 64] : memref<4096xf64>
          %25 = arith.addf %23, %24 : f64
          %26 = arith.addf %25, %21 : f64
          %27 = arith.cmpf olt, %26, %arg8 : f64
          %28 = arith.select %27, %26, %arg8 : f64
          affine.yield %28 : f64
        }
        affine.store %22, %alloca[%arg5, %arg6] : memref<140x64xf64>
      }
    }
    %3 = affine.load %alloca[139, 0] : memref<140x64xf64>
    %4:2 = affine.for %arg5 = 1 to 64 iter_args(%arg6 = %c0_i8, %arg7 = %3) -> (i8, f64) {
      %5 = arith.index_cast %arg5 : index to i8
      %6 = affine.load %alloca[139, %arg5] : memref<140x64xf64>
      %7 = arith.cmpf olt, %6, %arg7 : f64
      %8 = arith.select %7, %5, %arg6 : i8
      %9 = arith.select %7, %6, %arg7 : f64
      affine.yield %8, %9 : i8, f64
    }
    affine.store %4#0, %arg4[139] : memref<140xi8>
    affine.for %arg5 = 0 to 139 {
      %5 = affine.load %alloca[-%arg5 + 138, 0] : memref<140x64xf64>
      %6 = affine.load %arg4[-%arg5 + 139] : memref<140xi8>
      %7 = arith.extui %6 : i8 to i32
      %8 = arith.index_cast %7 : i32 to index
      %9 = memref.load %arg2[%8] : memref<4096xf64>
      %10 = arith.addf %5, %9 : f64
      %11:2 = affine.for %arg6 = 1 to 64 iter_args(%arg7 = %c0_i8, %arg8 = %10) -> (i8, f64) {
        %12 = arith.index_cast %arg6 : index to i8
        %13 = arith.extui %12 : i8 to i32
        %14 = affine.load %alloca[-%arg5 + 138, %arg6] : memref<140x64xf64>
        %15 = arith.muli %13, %c64_i32 : i32
        %16 = arith.addi %15, %7 : i32
        %17 = arith.index_cast %16 : i32 to index
        %18 = memref.load %arg2[%17] : memref<4096xf64>
        %19 = arith.addf %14, %18 : f64
        %20 = arith.cmpf olt, %19, %arg8 : f64
        %21 = arith.select %20, %12, %arg7 : i8
        %22 = arith.select %20, %19, %arg8 : f64
        affine.yield %21, %22 : i8, f64
      }
      affine.store %11#0, %arg4[-%arg5 + 138] : memref<140xi8>
    }
    return %c0_i32 : i32
  }
}
