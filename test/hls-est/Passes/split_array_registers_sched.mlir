// RUN: hls-est %s --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=RAM
// RUN: hls-est %s --infer-vitis-split-array=td=off --memory-banking-bram --convert-affine-to-loopschedule -o - | FileCheck %s --check-prefix=REGS
// RUN: hls-est %s --infer-vitis-split-array=td=off --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug 2>&1 >/dev/null | FileCheck %s --check-prefix=DEBUG

// An array marked hls.registers (here: int A[4], td=off rule (a), Vitis
// [HLS 214-421]) has no memory ports, so the scheduler links no port resource
// to its accesses. As a RAM the copy-in, which stores to A twice per
// iteration, makes it a true-dual-port bank (2 slots per cycle, VITIS_NOTES.md
// N4), and the compute loop's four reads of A need II = ceil(4 / 2) = 2. As
// registers the compute loop runs at II = 1.

// RAM:  loopschedule.pipeline II = {{ *}}1
// RAM:  loopschedule.pipeline II = {{ *}}2
// REGS: loopschedule.pipeline II = {{ *}}1
// REGS: loopschedule.pipeline II = {{ *}}1

// DEBUG:      A (alloca) @ {{.*}}
// DEBUG-NEXT:   shape [4] x i32 (32 bits) = 4 words
// DEBUG-NEXT:   status: registers -- registers (hls.registers): 4 element(s) <= complete-threshold 4
// DEBUG:        bram: 0
// DEBUG:      Total BRAM: 0

module {
  func.func @regs(%in: memref<64xi32>, %out: memref<64xi32>) {
    %A = memref.alloca() {polygeist.varname = "A"} : memref<4xi32>
    affine.for %i = 0 to 2 {
      %v = affine.load %in[%i * 2] : memref<64xi32>
      affine.store %v, %A[%i * 2] : memref<4xi32>
      %w = affine.load %in[%i * 2 + 1] : memref<64xi32>
      affine.store %w, %A[%i * 2 + 1] : memref<4xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    affine.for %i = 0 to 64 {
      %a = affine.load %A[%i mod 4] : memref<4xi32>
      %b = affine.load %A[(%i + 1) mod 4] : memref<4xi32>
      %c = affine.load %A[(%i + 2) mod 4] : memref<4xi32>
      %d = affine.load %A[(%i + 3) mod 4] : memref<4xi32>
      %s0 = arith.addi %a, %b : i32
      %s1 = arith.addi %c, %d : i32
      %s2 = arith.addi %s0, %s1 : i32
      affine.store %s2, %out[%i] : memref<64xi32>
    } {hls.pipeline = [{II = 1 : i32}]}
    return
  }
}
