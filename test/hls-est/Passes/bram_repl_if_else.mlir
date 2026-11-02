// RUN: hls-est %s --symbol-privatize=exclude=top_ifelse --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_ifelse -o /dev/null | FileCheck %s --check-prefix=IFELSE
// RUN: hls-est %s --symbol-privatize=exclude=top_ifelse --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram "--convert-affine-to-loopschedule=merge-if-else-accesses=false" --bram-analysis=top=top_ifelse -o /dev/null | FileCheck %s --check-prefix=IFELSE-OFF
// RUN: hls-est %s --symbol-privatize=exclude=top_ifelse --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_ifelse --bram-debug-json=%t.json -o /dev/null
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --symbol-privatize=exclude=top_affif --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_affif -o /dev/null | FileCheck %s --check-prefix=AFFIF
// RUN: hls-est %s --symbol-privatize=exclude=top_rmw --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_rmw -o /dev/null | FileCheck %s --check-prefix=RMW
// RUN: hls-est %s --symbol-privatize=exclude=top_rmw --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram "--convert-affine-to-loopschedule=merge-if-else-accesses=false" --bram-analysis=top=top_rmw -o /dev/null | FileCheck %s --check-prefix=RMW-OFF

// Same-address accesses in the two arms of an if/else (VITIS_NOTES.md N38
// R-ifelse). Vitis' formula for RAM_1WNR copies, min(16, ceil((R + W) / II)
// - 1) for the loop that reads the array and none when a loop body stores it
// twice, counts the stores the two arms make to one address as one store,
// and a read-modify-write made in both arms as one load and one store.
// - top_ifelse: `if (c) A[i] = x; else A[i] = 0;` is one store (the arms'
//   stores are sunk below the if), so A stays replicable: 8 reads at II 1 ->
//   7 copies, 14 BRAM (Vitis 14, kernel w9r_e1ifelse). With the merge off
//   the two stores stay, but stores in the two arms of one if count once for
//   replicability whatever their addresses (bram_repl_exclusive_stores.mlir),
//   so A is still replicated. top_affif: the same through an affine.if.
// - top_rmw: a read-modify-write of Y[c] in both arms of an if/else,
//   unrolled 4 times: the arms' load is hoisted and their store sunk, so
//   store forwarding leaves one load and one store: Y is a 1-port RAM.

// IFELSE: kind=RAM_1WNR  bram=14
// IFELSE: Total BRAM: 14
// IFELSE-OFF: kind=RAM_1WNR  bram=14
// IFELSE-OFF: Total BRAM: 14
// JSON: "merged_if_else_stores": 1
// AFFIF: kind=RAM_1WNR  bram=14
// AFFIF: Total BRAM: 14
// RMW: kind=RAM_T2P  bram=2
// RMW: kind=RAM_1P  bram=1
// RMW: Total BRAM: 3
// RMW-OFF: kind=RAM_T2P  bram=2
// RMW-OFF: kind=RAM_T2P  bram=2
// RMW-OFF: Total BRAM: 4

module {
  // if (in[i] > 0) A[i] = in[i]; else A[i] = 0;  then 8 unrolled reads at II 1.
  func.func @top_ifelse(%in: memref<1024xi32>, %out: memref<128xi32>) {
    %c0 = arith.constant 0 : i32
    %A = memref.alloca() {hls.preserve, polygeist.varname = "A_ifelse"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      %p = arith.cmpi sgt, %v, %c0 : i32
      scf.if %p {
        affine.store %v, %A[%i] : memref<1024xi32>
      } else {
        affine.store %c0, %A[%i] : memref<1024xi32>
      }
    }
    affine.for %i = 0 to 128 {
      %s = affine.for %r = 0 to 8 iter_args(%acc = %c0) -> (i32) {
        %x = affine.load %A[%i * 8 + %r] : memref<1024xi32>
        %n = arith.addi %acc, %x : i32
        affine.yield %n : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %s, %out[%i] : memref<128xi32>
    }
    return
  }

  func.func @top_affif(%in: memref<1024xi32>, %out: memref<128xi32>) {
    %c0 = arith.constant 0 : i32
    %A = memref.alloca() {hls.preserve, polygeist.varname = "A_affif"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.if affine_set<(d0) : (511 - d0 >= 0)>(%i) {
        affine.store %v, %A[%i] : memref<1024xi32>
      } else {
        affine.store %c0, %A[%i] : memref<1024xi32>
      }
    }
    affine.for %i = 0 to 128 {
      %s = affine.for %r = 0 to 8 iter_args(%acc = %c0) -> (i32) {
        %x = affine.load %A[%i * 8 + %r] : memref<1024xi32>
        %n = arith.addi %acc, %x : i32
        affine.yield %n : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %s, %out[%i] : memref<128xi32>
    }
    return
  }

  // Y[c] updated 4 times per iteration, each time under an if/else that
  // read-modify-writes Y[c] in both arms; W read 4 times.
  func.func @top_rmw(%X: memref<4xi32>, %Win: memref<64x4xi32>, %out: memref<64xi32>) {
    %c0 = arith.constant 0 : i32
    %W = memref.alloca() {hls.preserve, polygeist.varname = "W_rmw"} : memref<64x4xi32>
    %Y = memref.alloca() {hls.preserve, polygeist.varname = "Y_rmw"} : memref<64xi32>
    affine.for %c = 0 to 64 {
      affine.for %k = 0 to 4 {
        %w = affine.load %Win[%c, %k] : memref<64x4xi32>
        affine.store %w, %W[%c, %k] : memref<64x4xi32>
      }
      affine.store %c0, %Y[%c] : memref<64xi32>
    }
    affine.for %c = 0 to 64 {
      affine.for %k = 0 to 4 {
        %x = affine.load %X[%k] : memref<4xi32>
        %p = arith.cmpi slt, %x, %c0 : i32
        scf.if %p {
          %y = affine.load %Y[%c] : memref<64xi32>
          affine.store %y, %Y[%c] : memref<64xi32>
        } else {
          %y = affine.load %Y[%c] : memref<64xi32>
          %w = affine.load %W[%c, %k] : memref<64x4xi32>
          %m = arith.muli %x, %w : i32
          %a = arith.addi %y, %m : i32
          affine.store %a, %Y[%c] : memref<64xi32>
        }
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
    }
    affine.for %c = 0 to 64 {
      %y = affine.load %Y[%c] : memref<64xi32>
      affine.store %y, %out[%c] : memref<64xi32>
    }
    return
  }
}
