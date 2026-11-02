// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule --bram-analysis=top=branches --bram-debug -o /dev/null > %t.br.out 2> %t.br.err
// RUN: FileCheck %s --input-file=%t.br.out --check-prefix=BR
// RUN: FileCheck %s --input-file=%t.br.err --check-prefix=BRDBG
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule --bram-analysis=top=join --bram-debug -o /dev/null > %t.join.out 2> %t.join.err
// RUN: FileCheck %s --input-file=%t.join.out --check-prefix=JOIN
// RUN: FileCheck %s --input-file=%t.join.err --check-prefix=JOINDBG
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll -o - | FileCheck %s --check-prefix=ATTR
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=SCHED

// Instances of a non-inlined callee and the depth of a call, as Vitis 2025.1
// builds them (VITIS_NOTES.md N14 R2; W3 review 2; kernels
// ~/hls-est-work/exp-src/w3r2/, td=off):
//
//   D1  Calls in the two branches of an if never run together: one instance
//       (w3r2_k5_branches: Vitis 4 BRAM = one `work` with its 1024x32 buf).
//       --convert-affine-to-loopschedule moves both calls in front of the if;
//       hls.if_arms keeps their arms.
//   D2  The instance count is the most calls that can run at once: two
//       independent calls joined by a third that reads the output of the
//       first and writes the output of the second keep two instances
//       (w3r2_k6_join: Vitis 12 BRAM = 2 x 4 + t1 2 + t2 2; a union of the
//       ordered pairs gave 1 instance, 8 BRAM).
//   D3  The 4 calls of @get3 (three loads of one array, two adds) per
//       iteration share an instance and run one after the other, each for its
//       depth: Vitis groups the two adds into one three-input adder (4.37 ns)
//       that starts when the third load arrives (3.25 ns into cycle 2), so it
//       ends in cycle 3: latency 3, depth 4, II 16 (w3r2_k8_unrolled_calls;
//       two 2.55 ns adds gave depth 3, II 12).

// BR:      Total BRAM: 4
// BRDBG:   @work: 1 instance(s) (inline off)
// BRDBG:     in @branches (x1): 2 call site(s) -> 1 instance(s) (ordered pairs: 0 by a common array, 0 by a value dependence, 1 by exclusive branches)

// JOIN:    Total BRAM: 12
// JOINDBG: @work: 2 instance(s) (inline off)
// JOINDBG:   in @join (x1): 3 call site(s) -> 2 instance(s)

// ATTR-LABEL: func.func @unrolled_calls(
// ATTR-COUNT-4: func.call @get3({{.*}}) {hls.call_depth = 4 : i64, hls.call_occupancy = 2 : i64}

// SCHED-LABEL: func.func @unrolled_calls(
// SCHED:         loopschedule.pipeline II = 1 trip_count = 1024
// SCHED:         loopschedule.pipeline II = 16 trip_count = 256

module {
  func.func private @work(%in: memref<1024xi32>, %out: memref<1024xi32>) attributes {hls.inline_off} {
    %c7 = arith.constant 7 : i32
    %c1023 = arith.constant 1023 : i32
    %c3 = arith.constant 3 : i32
    %buf = memref.alloca() : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in[%i] : memref<1024xi32>
      %1 = arith.muli %0, %c3 : i32
      affine.store %1, %buf[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 1024 {
      %0 = arith.index_cast %i : index to i32
      %1 = affine.load %buf[%i] : memref<1024xi32>
      %2 = affine.load %buf[-%i + 1023] : memref<1024xi32>
      %3 = arith.addi %1, %2 : i32
      %4 = arith.muli %0, %c7 : i32
      %5 = arith.andi %4, %c1023 : i32
      %6 = arith.index_cast %5 : i32 to index
      %7 = memref.load %buf[%6] : memref<1024xi32>
      %8 = arith.addi %3, %7 : i32
      affine.store %8, %out[%i] : memref<1024xi32>
    }
    return
  }

  // if (sel) work(a, b); else work(c, d);
  func.func @branches(%sel: i32, %a: memref<1024xi32>, %b: memref<1024xi32>, %c: memref<1024xi32>, %d: memref<1024xi32>) {
    %c0 = arith.constant 0 : i32
    %0 = arith.cmpi ne, %sel, %c0 : i32
    scf.if %0 {
      func.call @work(%a, %b) : (memref<1024xi32>, memref<1024xi32>) -> ()
    } else {
      func.call @work(%c, %d) : (memref<1024xi32>, memref<1024xi32>) -> ()
    }
    return
  }

  // work(a, t1); work(b, t2); work(t1, t2);
  func.func @join(%a: memref<1024xi32>, %b: memref<1024xi32>, %o: memref<1024xi32>) {
    %t2 = memref.alloca() : memref<1024xi32>
    %t1 = memref.alloca() : memref<1024xi32>
    func.call @work(%a, %t1) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @work(%b, %t2) : (memref<1024xi32>, memref<1024xi32>) -> ()
    func.call @work(%t1, %t2) : (memref<1024xi32>, memref<1024xi32>) -> ()
    affine.for %i = 0 to 1024 {
      %0 = affine.load %t2[%i] : memref<1024xi32>
      affine.store %0, %o[%i] : memref<1024xi32>
    }
    return
  }

  func.func private @get3(%a: memref<1024xi32>, %i: i32) -> i32 attributes {hls.inline_off} {
    %c7 = arith.constant 7 : i32
    %c1023 = arith.constant 1023 : i32
    %0 = arith.index_cast %i : i32 to index
    %1 = affine.load %a[symbol(%0)] : memref<1024xi32>
    %2 = arith.subi %c1023, %i : i32
    %3 = arith.index_cast %2 : i32 to index
    %4 = affine.load %a[symbol(%3)] : memref<1024xi32>
    %5 = arith.addi %1, %4 : i32
    %6 = arith.muli %i, %c7 : i32
    %7 = arith.andi %6, %c1023 : i32
    %8 = arith.index_cast %7 : i32 to index
    %9 = affine.load %a[symbol(%8)] : memref<1024xi32>
    %10 = arith.addi %5, %9 : i32
    return %10 : i32
  }

  // for (i < 256) { s = 0; for (j < 4) s += get3(b, 4 * i + j); out[i] = s; }
  func.func @unrolled_calls(%in: memref<1024xi32>, %out: memref<256xi32>) {
    %c4 = arith.constant 4 : i32
    %c3 = arith.constant 3 : i32
    %c0 = arith.constant 0 : i32
    %b = memref.alloca() : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in[%i] : memref<1024xi32>
      %1 = arith.muli %0, %c3 : i32
      affine.store %1, %b[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 256 {
      %0 = arith.index_cast %i : index to i32
      %1 = arith.muli %0, %c4 : i32
      %2 = affine.for %j = 0 to 4 iter_args(%acc = %c0) -> (i32) {
        %3 = arith.index_cast %j : index to i32
        %4 = arith.addi %1, %3 : i32
        %5 = func.call @get3(%b, %4) : (memref<1024xi32>, i32) -> i32
        %6 = arith.addi %acc, %5 : i32
        affine.yield %6 : i32
      }
      affine.store %2, %out[%i] : memref<256xi32>
    }
    return
  }
}
