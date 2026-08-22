// RUN: hls-est %s --symbol-privatize=exclude=top_ifn --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_ifn --bram-debug-json=%t.json -o /dev/null | FileCheck %s --check-prefix=IFN
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --symbol-privatize=exclude=top_nest --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_nest -o /dev/null | FileCheck %s --check-prefix=NEST
// RUN: hls-est %s --symbol-privatize=exclude=top_two --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_two -o /dev/null | FileCheck %s --check-prefix=TWO

// Stores in the two arms of one if never run in the same iteration: they
// share the one write port of a RAM_1WNR and count once for replicability,
// whatever their addresses (Vitis 2025.1 td=off, kernel r4r_ifn:
// `if (s > 0) B[i] = v; else B[N-1-i] = v + 1;`, B read 8 times per
// iteration at II 1 -> RAM_1WNR with 7 copies, 14 BRAM_18K, although
// a.o.3.ll keeps both stores).
// - top_ifn: the two arms store different addresses: one store, 14 (Vitis 14).
// - top_nest: if / else if / else, three different addresses: one store, 14.
// - top_two: two independent ifs store B in one iteration: two stores, B is
//   a 2-port RAM and the reading loop's II rises.

// IFN: kind=RAM_1WNR  bram=14
// IFN: Total BRAM: 14
// JSON: "max_stores_per_loop": 1
// JSON-NEXT: "replicable": true
// NEST: kind=RAM_1WNR  bram=14
// NEST: Total BRAM: 14
// TWO: kind=RAM_T2P  bram=2
// TWO: Total BRAM: 2

module {
  func.func @top_ifn(%in: memref<256xi32>, %sel: memref<256xi32>, %out: memref<32xi32>) {
    %c0 = arith.constant 0 : i32
    %c1 = arith.constant 1 : i32
    %B = memref.alloca() {hls.preserve, polygeist.varname = "B"} : memref<256xi32>
    affine.for %i = 0 to 256 {
      %v = affine.load %in[%i] : memref<256xi32>
      %s = affine.load %sel[%i] : memref<256xi32>
      %p = arith.cmpi sgt, %s, %c0 : i32
      scf.if %p {
        affine.store %v, %B[%i] : memref<256xi32>
      } else {
        %w = arith.addi %v, %c1 : i32
        affine.store %w, %B[255 - %i] : memref<256xi32>
      }
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %j = 0 to 32 {
      %s = affine.for %k = 0 to 8 iter_args(%acc = %c0) -> (i32) {
        %x = affine.load %B[%j * 8 + %k] : memref<256xi32>
        %n = arith.addi %acc, %x : i32
        affine.yield %n : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %s, %out[%j] : memref<32xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  func.func @top_nest(%in: memref<256xi32>, %sel: memref<256xi32>, %out: memref<32xi32>) {
    %c0 = arith.constant 0 : i32
    %c1 = arith.constant 1 : i32
    %B = memref.alloca() {hls.preserve, polygeist.varname = "B"} : memref<256xi32>
    affine.for %i = 0 to 256 {
      %v = affine.load %in[%i] : memref<256xi32>
      %s = affine.load %sel[%i] : memref<256xi32>
      %p = arith.cmpi eq, %s, %c0 : i32
      %q = arith.cmpi eq, %s, %c1 : i32
      scf.if %p {
        affine.store %v, %B[%i] : memref<256xi32>
      } else {
        scf.if %q {
          affine.store %v, %B[255 - %i] : memref<256xi32>
        } else {
          affine.store %c0, %B[(%i + 7) mod 256] : memref<256xi32>
        }
      }
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %j = 0 to 32 {
      %s = affine.for %k = 0 to 8 iter_args(%acc = %c0) -> (i32) {
        %x = affine.load %B[%j * 8 + %k] : memref<256xi32>
        %n = arith.addi %acc, %x : i32
        affine.yield %n : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %s, %out[%j] : memref<32xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }

  func.func @top_two(%in: memref<256xi32>, %sel: memref<256xi32>, %out: memref<32xi32>) {
    %c0 = arith.constant 0 : i32
    %c1 = arith.constant 1 : i32
    %B = memref.alloca() {hls.preserve, polygeist.varname = "B"} : memref<256xi32>
    affine.for %i = 0 to 128 {
      %v = affine.load %in[%i] : memref<256xi32>
      %s = affine.load %sel[%i] : memref<256xi32>
      %p = arith.cmpi sgt, %s, %c0 : i32
      %q = arith.cmpi sgt, %v, %c0 : i32
      scf.if %p {
        affine.store %v, %B[%i] : memref<256xi32>
      }
      scf.if %q {
        affine.store %s, %B[%i + 128] : memref<256xi32>
      }
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %j = 0 to 32 {
      %s = affine.for %k = 0 to 8 iter_args(%acc = %c0) -> (i32) {
        %x = affine.load %B[%j * 8 + %k] : memref<256xi32>
        %n = arith.addi %acc, %x : i32
        affine.yield %n : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %s, %out[%j] : memref<32xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
}
