// RUN: hls-est %s --vitis-fold --bram-analysis=top=fa --bram-debug --bram-debug-json=%t.a.json -o /dev/null > %t.a.out 2> %t.a.err
// RUN: FileCheck %s --input-file=%t.a.err --check-prefix=TOPADBG
// RUN: FileCheck %s --input-file=%t.a.json --check-prefix=TOPAJSON
// RUN: hls-est %s --symbol-privatize=exclude=fa --symbol-dce --vitis-fold --bram-analysis --bram-debug -o /dev/null 2>&1 >/dev/null | FileCheck %s --check-prefix=TOPADBG
// RUN: hls-est %s --vitis-fold --bram-analysis --bram-debug --bram-debug-json=%t.all.json -o /dev/null > %t.all.out 2> %t.all.err
// RUN: FileCheck %s --input-file=%t.all.err --check-prefix=ALLDBG
// RUN: FileCheck %s --input-file=%t.all.json --check-prefix=ALLJSON
// RUN: hls-est %s --vitis-fold -o - | FileCheck %s --check-prefix=IR

// The --vitis-fold summary under top= (W1a review D4): --vitis-fold records
// the function of every rewrite and the counts per function in
// `hls.vitis_fold`, and --bram-debug / --bram-debug-json with top=<f> report
// only the rewrites of the functions <f> reaches, as the --symbol-privatize /
// --symbol-dce prefix leaves them. @fa's x / 0 feeds a multiply (mul-zero);
// @fb's, which @fa never calls, a sign extension (ext-zero).

// IR: hls.vitis_fold = {counts = {"ext-zero" = 1 : i64, "mul-zero" = 1 : i64}, func_counts = {fa = {"mul-zero" = 1 : i64}, fb = {"ext-zero" = 1 : i64}}, rewrites = [{func = "fa", loc = {{[^,]*}}, rule = "mul-zero", source = {{[^,]*}}, {func = "fb", loc = {{[^,]*}}, rule = "ext-zero"

// TOPADBG: --- vitis-fold: 1 rewrites of the undefined value
// TOPADBG-NEXT: counts: mul-zero=1
// TOPADBG-NEXT: mul-zero @
// TOPADBG-NOT: ext-zero
// TOPADBG: --- summary

// TOPAJSON:      "vitis_fold": {
// TOPAJSON-NEXT:   "counts": {
// TOPAJSON-NEXT:     "mul-zero": 1
// TOPAJSON-NEXT:   },
// TOPAJSON-NEXT:   "rewrites": [
// TOPAJSON-NEXT:     {
// TOPAJSON-NEXT:       "detail": null,
// TOPAJSON-NEXT:       "func": "fa",
// TOPAJSON:            "rule": "mul-zero",
// TOPAJSON:          }
// TOPAJSON-NEXT:   ],
// TOPAJSON-NEXT:   "scope": "top"

// ALLDBG: --- vitis-fold: 2 rewrites of the undefined value
// ALLDBG-NEXT: counts: ext-zero=1 mul-zero=1

// ALLJSON:      "vitis_fold": {
// ALLJSON:        "scope": "module"

module {
  func.func @fa(%x: i32, %out: memref<1xi32>) {
    %c0 = arith.constant 0 : i32
    %d = arith.divsi %x, %c0 : i32
    %m = arith.muli %d, %x : i32
    %i0 = arith.constant 0 : index
    memref.store %m, %out[%i0] : memref<1xi32>
    return
  }
  func.func @fb(%x: i32, %out: memref<1xi64>) {
    %c0 = arith.constant 0 : i32
    %d = arith.divsi %x, %c0 : i32
    %e = arith.extsi %d : i32 to i64
    %i0 = arith.constant 0 : index
    memref.store %e, %out[%i0] : memref<1xi64>
    return
  }
}
