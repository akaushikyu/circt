// RUN: hls-est %s --symbol-privatize=exclude=top_userii --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top_userii -o /dev/null | FileCheck %s --check-prefix=USERII
// RUN: hls-est %s --symbol-privatize=exclude=top_userii --symbol-dce --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram "--convert-affine-to-loopschedule=user-ii-target=false" --bram-analysis=top=top_userii -o /dev/null | FileCheck %s --check-prefix=USERII-OFF

// A user `pipeline II=N` is the II Vitis schedules for, and the RAM_1WNR
// copies are sized at the final II of the loop that reads the array
// (VITIS_NOTES.md N38 II input (a); kernel w9v_r_iifl: 8 reads at II 2 ->
// 3 copies, 6 BRAM). Scheduled at II 1 the loop would need 7 copies.

// USERII: 1024x32b -> RAM_1WNR, 3 copies x 2 (x18/port) = 6 BRAM_18K
// USERII: Total BRAM: 6
// USERII-OFF: 7 copies
// USERII-OFF: Total BRAM: 14

module {
  // 8 unrolled reads of A under a user pipeline II=2.
  func.func @top_userii(%in: memref<1024xi32>, %out: memref<128xi32>) {
    %c0 = arith.constant 0 : i32
    %A = memref.alloca() {hls.preserve, polygeist.varname = "A_userii"} : memref<1024xi32>
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.store %v, %A[%i] : memref<1024xi32>
    }
    affine.for %i = 0 to 128 {
      %s = affine.for %r = 0 to 8 iter_args(%acc = %c0) -> (i32) {
        %x = affine.load %A[%i * 8 + %r] : memref<1024xi32>
        %n = arith.addi %acc, %x : i32
        affine.yield %n : i32
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      affine.store %s, %out[%i] : memref<128xi32>
    } {hls.pipeline = [{II = 2 : i32, rewind = false, style = "stp"}]}
    return
  }
}
