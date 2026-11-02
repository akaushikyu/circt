// RUN: hls-est %s --memory-banking-bram | FileCheck %s
// RUN: hls-est %s --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis | FileCheck %s --check-prefix=BRAM

// --memory-banking-bram (VITIS_NOTES.md N17, N21, N24):
//   @two_dims  entries on two dimensions combine (w7_p2d: cyclic 4 on dim 1
//              and cyclic 8 on dim 2 of int[64][64] = 32 banks of 16x8).
//   @merge     two entries on one dimension: the larger factor wins
//              (fbh6_conf_up / fbh6_conf_down); a factor past the extent is
//              a complete partition (N21).
//   @caller    a callee parameter's pragma partitions the caller's array
//              (fbh1_prop_whole, w7_prop_two: both arrays passed to @f are
//              split 4 ways) and the callee gets one parameter per bank.
//   @G         a global with its own pragma is split into bank globals, every
//              get_global site rewritten (diff_orders_p3 shape).

// CHECK-LABEL: func.func @two_dims
// CHECK-COUNT-32: memref.alloca() {{.*}}hls.bank_count = 32 : i32{{.*}} : memref<16x8xi32>
// CHECK: return
func.func @two_dims(%in: memref<64x64xi32>, %out: memref<64x64xi32>) {
  %a = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic"}, {dim = 2 : i32, factor = 8 : i32, kind = "cyclic"}], polygeist.varname = "A"} : memref<64x64xi32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %in[%i, %j] : memref<64x64xi32>
      affine.store %0, %a[%i, %j] : memref<64x64xi32>
    }
  }
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %a[%i, %j] : memref<64x64xi32>
      affine.store %0, %out[%i, %j] : memref<64x64xi32>
    }
  }
  return
}

// CHECK-LABEL: func.func @merge
// CHECK-COUNT-4: memref.alloca() {{.*}}hls.bank_count = 4 : i32{{.*}} : memref<256xi32>
// CHECK-COUNT-8: memref.alloca() {{.*}}hls.bank_count = 8 : i32{{.*}} : memref<1xi32>
// CHECK: return
func.func @merge(%in: memref<1024xi32>, %in8: memref<8xi32>, %out: memref<1024xi32>) {
  %a = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}, {dim = 1 : i32, factor = 4 : i32, kind = "cyclic"}], polygeist.varname = "M"} : memref<1024xi32>
  %c = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 16 : i32, kind = "cyclic"}], polygeist.varname = "C"} : memref<8xi32>
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %a[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 8 {
    %0 = affine.load %in8[%i] : memref<8xi32>
    affine.store %0, %c[%i] : memref<8xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %a[%i] : memref<1024xi32>
    %1 = affine.load %c[%i mod 8] : memref<8xi32>
    %2 = arith.addi %0, %1 : i32
    affine.store %2, %out[%i] : memref<1024xi32>
  }
  return
}

// The callee: one parameter per bank, the accesses rewritten.
// CHECK-LABEL: func.func private @f(
// CHECK-SAME: %{{.*}}: memref<256xi32> {{{.*}}hls.bank_index = 0 : i32
// CHECK-SAME: %{{.*}}: memref<256xi32> {{{.*}}hls.bank_index = 3 : i32
// CHECK-SAME: %{{.*}}: memref<1024xi32>)
// CHECK-NOT: memref<1024xi32> {hls.array_partition
func.func private @f(%a: memref<1024xi32> {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic"}]}, %o: memref<1024xi32>) attributes {hls.inline_off} {
  affine.for %i = 0 to 1024 {
    %0 = affine.load %a[%i] : memref<1024xi32>
    affine.store %0, %o[%i] : memref<1024xi32>
  }
  return
}

// Both arrays passed to @f are split; the calls pass the banks.
// CHECK-LABEL: func.func @caller
// CHECK-COUNT-4: memref.alloca() {{.*}}hls.partition = {{{.*}}from = "parameter 0 of @f"
// CHECK-COUNT-4: memref.alloca() {{.*}}hls.partition = {{{.*}}from = "parameter 0 of @f"
// CHECK: call @f(%{{.*}}, %{{.*}}, %{{.*}}, %{{.*}}, %arg1) : (memref<256xi32>, memref<256xi32>, memref<256xi32>, memref<256xi32>, memref<1024xi32>) -> ()
// CHECK: call @f(%{{.*}}, %{{.*}}, %{{.*}}, %{{.*}}, %arg1)
func.func @caller(%in: memref<1024xi32>, %out: memref<1024xi32>) {
  %a = memref.alloca() {polygeist.varname = "A"} : memref<1024xi32>
  %b = memref.alloca() {polygeist.varname = "B"} : memref<1024xi32>
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %a[%i] : memref<1024xi32>
    affine.store %0, %b[%i] : memref<1024xi32>
  }
  call @f(%a, %out) : (memref<1024xi32>, memref<1024xi32>) -> ()
  call @f(%b, %out) : (memref<1024xi32>, memref<1024xi32>) -> ()
  return
}

// A global with its own two-dimensional pragma: 2 x 2 bank globals.
// CHECK-DAG: memref.global "private" @G_bank_0 : memref<32x64xi16> = uninitialized {hls.bank_count = 4 : i32, hls.bank_index = 0 : i32, hls.bank_of = "G"
// CHECK-DAG: memref.global "private" @G_bank_3 : memref<32x64xi16> = uninitialized
// CHECK-NOT: memref.global "private" @G :
memref.global "private" @G : memref<64x128xi16> = uninitialized {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}, {dim = 2 : i32, factor = 2 : i32, kind = "cyclic"}]}

// CHECK-LABEL: func.func @use_global
// CHECK-COUNT-4: memref.get_global @G_bank_{{[0-3]}} : memref<32x64xi16>
// CHECK: affine.store %{{.*}}, %{{.*}}[%{{.*}} floordiv 2, %{{.*}} floordiv 2] : memref<32x64xi16>
func.func @use_global(%in: memref<64x128xi16>) {
  %g = memref.get_global @G : memref<64x128xi16>
  affine.for %i = 0 to 64 step 2 {
    affine.for %j = 0 to 128 step 2 {
      %0 = affine.load %in[%i, %j] : memref<64x128xi16>
      affine.store %0, %g[%i, %j] : memref<64x128xi16>
    }
  }
  return
}

// Banks of @two_dims: 32 x (16x8 x i32 = 4096 bits) one BRAM each.
// BRAM-DAG: Total BRAM:
