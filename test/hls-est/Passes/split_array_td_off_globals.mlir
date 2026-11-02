// RUN: hls-est %s '--infer-vitis-split-array=td=off annotate-pressure=false' | FileCheck %s
// RUN: hls-est %s '--infer-vitis-split-array=td=off annotate-pressure=false' --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis 2>&1 | FileCheck %s --check-prefix=BRAM

// --infer-vitis-split-array rule (a) (VITIS_NOTES N7 (a)) holds for globals
// and function statics as for locals: Vitis 2025.1 td=off logs [HLS 214-421]
// 'Automatically partitioning small array' for a global `ap_uint<512> g[4]`
// and a function-static `s[4]` and builds no memory for either (kernel
// w9rv_r1_glob4, Vitis total 0). A global of 5 elements stays a memory.

// CHECK: memref.global @g : memref<4xi512> = uninitialized {hls.registers, hls.registers_reason = "4 element(s) <= complete-threshold 4: {{.*}}214-421{{.*}}"}
// CHECK: memref.global "private" @s_static : memref<4xi512> = uninitialized {hls.registers, {{.*}}}
// CHECK: memref.global @g5 : memref<5xi512> = uninitialized{{$}}
// CHECK-LABEL: func.func @k

// BRAM: Total BRAM: 15
memref.global @g : memref<4xi512> = uninitialized
memref.global "private" @s_static : memref<4xi512> = uninitialized
memref.global @g5 : memref<5xi512> = uninitialized
func.func @k(%in: memref<64xi512>, %sel: memref<64xindex>, %out: memref<64xi512>) {
  %g = memref.get_global @g : memref<4xi512>
  %s = memref.get_global @s_static : memref<4xi512>
  %g5 = memref.get_global @g5 : memref<5xi512>
  affine.for %i = 0 to 4 {
    %a = affine.load %in[%i] : memref<64xi512>
    affine.store %a, %g[%i] : memref<4xi512>
    %b = affine.load %in[%i + 4] : memref<64xi512>
    affine.store %b, %s[%i] : memref<4xi512>
    affine.store %b, %g5[%i] : memref<5xi512>
  }
  affine.for %i = 0 to 64 {
    %x = affine.load %sel[%i] : memref<64xindex>
    %v = memref.load %g[%x] : memref<4xi512>
    %w = memref.load %s[%x] : memref<4xi512>
    %u = memref.load %g5[%x] : memref<5xi512>
    %r = arith.xori %v, %w : i512
    %q = arith.xori %r, %u : i512
    affine.store %q, %out[%i] : memref<64xi512>
  }
  return
}
