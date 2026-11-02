// RUN: hls-est %s --promote-globals-to-allocas | FileCheck %s

// --promote-globals-to-allocas: Vitis treats a file-scope array exactly like a
// local one (VITIS_NOTES.md N1a, dg_e_globals_static = dg_e_globals_extern =
// dg_e_locals = 4 BRAM). A non-constant global without a (non-zero) initial
// value whose get_global sites are all in one function becomes an alloca at
// that function's entry, so banking, the scheduler's storage model and
// --bram-analysis treat it like a local array.

// Promoted: uninitialised, and dense zero (C's zero-initialised globals).
// CHECK-NOT: memref.global @A
// CHECK-NOT: memref.global @Z
// Kept: used by two functions, constant (a ROM table), non-zero initial value.
// CHECK-DAG: memref.global @SHARED : memref<512xi32> = uninitialized
// CHECK-DAG: memref.global "private" constant @ROM : memref<4xi32> = dense<[1, 2, 3, 4]>
// CHECK-DAG: memref.global @INIT : memref<4xi32> = dense<[5, 6, 7, 8]>
memref.global @A : memref<512xi32> = uninitialized {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}]}
memref.global @Z : memref<64xf32> = dense<0.000000e+00>
memref.global @SHARED : memref<512xi32> = uninitialized
memref.global "private" constant @ROM : memref<4xi32> = dense<[1, 2, 3, 4]>
memref.global @INIT : memref<4xi32> = dense<[5, 6, 7, 8]>

// CHECK-LABEL: func.func @top
// CHECK-DAG: %[[Z:.*]] = memref.alloca() {hls.from_global = "Z", hls.preserve, polygeist.varname = "Z"} : memref<64xf32>
// CHECK-DAG: %[[A:.*]] = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 2 : i32, kind = "cyclic"}], hls.from_global = "A", hls.preserve, polygeist.varname = "A"} : memref<512xi32>
// CHECK-NOT: get_global @A
// CHECK-NOT: get_global @Z
// CHECK: affine.store %{{.*}}, %[[A]][%{{.*}}]
// CHECK: affine.load %[[A]][%{{.*}}]
// CHECK: get_global @SHARED
func.func @top(%in: memref<512xi32>, %out: memref<512xi32>) {
  %a = memref.get_global @A : memref<512xi32>
  %z = memref.get_global @Z : memref<64xf32>
  %rom = memref.get_global @ROM : memref<4xi32>
  %init = memref.get_global @INIT : memref<4xi32>
  affine.for %i = 0 to 512 {
    %v = affine.load %in[%i] : memref<512xi32>
    affine.store %v, %a[%i] : memref<512xi32>
  }
  affine.for %i = 0 to 512 {
    %a2 = memref.get_global @A : memref<512xi32>
    %v = affine.load %a2[%i] : memref<512xi32>
    %r = affine.load %rom[%i mod 4] : memref<4xi32>
    %t = affine.load %init[%i mod 4] : memref<4xi32>
    %s = arith.addi %v, %r : i32
    %u = arith.addi %s, %t : i32
    affine.store %u, %out[%i] : memref<512xi32>
  }
  %sh = memref.get_global @SHARED : memref<512xi32>
  return
}

func.func @helper() {
  %sh = memref.get_global @SHARED : memref<512xi32>
  return
}
