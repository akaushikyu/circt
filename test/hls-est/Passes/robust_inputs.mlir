// RUN: hls-est %s --symbol-privatize=exclude=ptr_vars --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null > %t.ptr.out 2> %t.ptr.err
// RUN: FileCheck %s --input-file=%t.ptr.out --check-prefix=PTR
// RUN: FileCheck %s --input-file=%t.ptr.err --check-prefix=PTRDBG
// RUN: hls-est %s --symbol-privatize=exclude=nonaffine --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=NONAFF
// RUN: hls-est %s --symbol-privatize=exclude=math_call --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null 2>&1 | FileCheck %s --check-prefix=CALL
// RUN: hls-est %s --symbol-privatize=exclude=math_call --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --config-set=scheduling.timing.operator_latencies.libm_call=-1 --bram-analysis -o /dev/null 2>&1 | FileCheck %s --check-prefix=CALLSEQ
// RUN: hls-est %s --symbol-privatize=exclude=math_call --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --loopschedule-call-latency=1 --bram-analysis -o /dev/null 2>&1 | FileCheck %s --check-prefix=CALL1
// RUN: hls-est %s --symbol-privatize=exclude=if_results --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=IFRES

// Inputs the harness used to lose to a tool failure (T4 robustness).

// (a) Pointer variables: cgeist emits `memref<memref<?xi32>>` allocas for C
// pointer locals (forgebench conv_*). The scheduler's bank classification
// asserted in getElementTypeBitWidth; --bram-analysis now reports them as
// excluded with the reason, and index-typed arrays are 64-bit words.
// PTR: Total BRAM: 2
// PTRDBG: status: excluded_type -- element type memref<?xi32> is not an integer / float; not estimated
// PTRDBG: idx (alloca) @
// PTRDBG: shape [512] x index (64 bits)
func.func @ptr_vars(%in: memref<?xi32>, %out: memref<512xindex>) {
  %p = memref.alloca() {polygeist.varname = "p"} : memref<memref<?xi32>>
  %idx = memref.alloca() {polygeist.varname = "idx"} : memref<512xindex>
  memref.store %in, %p[] : memref<memref<?xi32>>
  affine.for %i = 0 to 512 {
    affine.store %i, %idx[%i] : memref<512xindex>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %idx[511 - %i] : memref<512xindex>
    affine.store %v, %out[%i] : memref<512xindex>
  }
  return
}

// (b) Loops cgeist could not raise (scf.while / scf.for) are sequential
// scopes: the affine loops inside / around them are still scheduled and
// --bram-analysis runs. `buf` (512x32, written in an scf.for, read in an
// scf.while) is one plain RAM.
// NONAFF: Total BRAM: 1
func.func @nonaffine(%in: memref<512xi32>, %out: memref<512xi32>, %n: index) {
  %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
  %c0 = arith.constant 0 : index
  %c1 = arith.constant 1 : index
  scf.for %i = %c0 to %n step %c1 {
    %v = memref.load %in[%i] : memref<512xi32>
    memref.store %v, %buf[%i] : memref<512xi32>
    affine.for %j = 0 to 4 {
      %w = affine.load %in[%j] : memref<512xi32>
      affine.store %w, %out[%j] : memref<512xi32>
    }
  }
  %r = scf.while (%i = %c0) : (index) -> index {
    %c = arith.cmpi slt, %i, %n : index
    scf.condition(%c) %i : index
  } do {
  ^bb0(%i: index):
    %v = memref.load %buf[%i] : memref<512xi32>
    memref.store %v, %out[%i] : memref<512xi32>
    %nx = arith.addi %i, %c1 : index
    scf.yield %nx : index
  }
  return
}

// (c) A call to a C math library function in a loop body: tanhf is an
// operator of the pipeline (scheduling.timing.operator_latencies.libm_call,
// VITIS_NOTES N169: Vitis pipelines loops around tanhf), so `tbl` is read and
// written in one pipelined loop (2 ports, 512x32 at x18 = 2 BRAM); with
// libm_call = -1 the loop stays a sequential affine.for (warning, no failure,
// 1 BRAM: the behaviour before W9r22-impl), and --loopschedule-call-latency=1
// pipelines it as well.
// CALL-NOT: warning: not pipelined
// CALL: Total BRAM: 2
// CALLSEQ: warning: not pipelined (left as a sequential loop): unsupported operation {{.*}}func.call @tanhf
// CALLSEQ: Total BRAM: 1
// CALL1-NOT: warning: not pipelined
// CALL1: Total BRAM: 2
func.func private @tanhf(f32) -> f32
func.func @math_call(%in: memref<512xf32>, %out: memref<512xf32>) {
  %tbl = memref.alloca() {polygeist.varname = "tbl"} : memref<512xf32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xf32>
    affine.store %v, %tbl[%i] : memref<512xf32>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %tbl[%i] : memref<512xf32>
    %t = func.call @tanhf(%v) : (f32) -> f32
    affine.store %t, %tbl[%i] : memref<512xf32>
  }
  affine.for %i = 0 to 512 {
    %v = affine.load %tbl[%i] : memref<512xf32>
    affine.store %v, %out[%i] : memref<512xf32>
  }
  return
}

// (d) spector_hls sobel_filter_x/y: an affine.if with results whose
// then-branch yields values computed from loads, inside a pipelined loop.
// The scf.if hoisting ran inside the dialect conversion and left an scf.yield
// with a null operand ("null operand found"); it now runs after the conversion.
// IFRES: Total BRAM: 0
#set = affine_set<(d0) : (d0 - 2 >= 0)>
func.func @if_results(%img: memref<64x64xi8>, %out: memref<64x64xi8>) {
  %c0 = arith.constant 0 : i32
  %win = memref.alloca() {polygeist.varname = "win"} : memref<3xi32>
  affine.for %r = 1 to 63 {
    %res:2 = affine.for %c = 0 to 64 iter_args(%a = %c0, %b = %c0) -> (i32, i32) {
      %y:2 = affine.if #set(%c) -> (i32, i32) {
        affine.store %a, %win[0] : memref<3xi32>
        %l0 = affine.load %img[%r - 1, %c] : memref<64x64xi8>
        %e0 = arith.extsi %l0 : i8 to i32
        affine.store %e0, %win[1] : memref<3xi32>
        %l1 = affine.load %img[%r + 1, %c] : memref<64x64xi8>
        %e1 = arith.extsi %l1 : i8 to i32
        affine.store %e1, %win[2] : memref<3xi32>
        affine.yield %e0, %e1 : i32, i32
      } else {
        affine.yield %a, %b : i32, i32
      }
      %s = arith.addi %y#0, %y#1 : i32
      %t = arith.trunci %s : i32 to i8
      affine.store %t, %out[%r, %c] : memref<64x64xi8>
      affine.yield %y#0, %y#1 : i32, i32
    }
  }
  return
}
