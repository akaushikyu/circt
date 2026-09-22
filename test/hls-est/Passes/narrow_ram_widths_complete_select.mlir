// RUN: hls-est %s --narrow-ram-widths | FileCheck %s
// RUN: hls-est %s --narrow-ram-widths=complete-read-selector=false | FileCheck %s --check-prefix=OFF

// --narrow-ram-widths and the subscript of a completely partitioned
// dimension (VITIS_NOTES N91, Vitis 2025.1 td=off, kernels w9r12p_nw_*): an
// array whose loaded values only select one of the S banks of a completely
// partitioned array in a READ is narrowed to ceil(log2 S) bits (the selector
// of _ssdm_op_SparseMux); add / sub keep the narrowing. The selector of a
// WRITE into completely partitioned banks keeps every bit (a compare chain
// whose out-of-range case writes nothing).

// `int idx[1024]; int P[65]` (complete): `out[i] = P[k] + P[k + 1]` with
// k = idx[i] (w9r12p_nw_p65r2: Vitis idx 1024 x 7).
// CHECK-LABEL: func.func @read_select65
// CHECK: memref.alloca() {hls.narrow_bits = 7 : i32, {{.*}}polygeist.varname = "idx"}
// OFF-LABEL: func.func @read_select65
// OFF-NOT: hls.narrow_bits
func.func @read_select65(%in: memref<1024xi32>, %pin: memref<65xi32>, %out: memref<1024xi32>) {
  %P = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "P"}], polygeist.varname = "P"} : memref<65xi32>
  %idx = memref.alloca() {polygeist.varname = "idx"} : memref<1024xi32>
  %c1 = arith.constant 1 : i32
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %idx[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 65 {
    %0 = affine.load %pin[%i] : memref<65xi32>
    affine.store %0, %P[%i] : memref<65xi32>
  }
  affine.for %i = 0 to 1024 {
    %k = affine.load %idx[%i] : memref<1024xi32>
    %a = arith.index_cast %k : i32 to index
    %x = memref.load %P[%a] : memref<65xi32>
    %k1 = arith.addi %k, %c1 : i32
    %b = arith.index_cast %k1 : i32 to index
    %y = memref.load %P[%b] : memref<65xi32>
    %s = arith.addi %x, %y : i32
    affine.store %s, %out[%i] : memref<1024xi32>
  }
  return
}

// A 16-bank read selector: 4 bits (w9r12p_nw_p16r1).
// CHECK-LABEL: func.func @read_select16
// CHECK: memref.alloca() {hls.narrow_bits = 4 : i32, {{.*}}polygeist.varname = "idx"}
func.func @read_select16(%in: memref<1024xi32>, %pin: memref<16xi32>, %out: memref<1024xi32>) {
  %P = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "P"}], polygeist.varname = "P"} : memref<16xi32>
  %idx = memref.alloca() {polygeist.varname = "idx"} : memref<1024xi32>
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %idx[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 16 {
    %0 = affine.load %pin[%i] : memref<16xi32>
    affine.store %0, %P[%i] : memref<16xi32>
  }
  affine.for %i = 0 to 1024 {
    %k = affine.load %idx[%i] : memref<1024xi32>
    %a = arith.index_cast %k : i32 to index
    %x = memref.load %P[%a] : memref<16xi32>
    affine.store %x, %out[%i] : memref<1024xi32>
  }
  return
}

// The selector of a write into 64 completely partitioned banks keeps all 32
// bits (w9r12p_nw_wrst: Vitis idx 1024 x 32).
// CHECK-LABEL: func.func @write_select64
// CHECK: memref.alloca() {polygeist.varname = "idx"}
func.func @write_select64(%in: memref<1024xi32>, %v: memref<1024xi32>, %out: memref<64xi32>) {
  %C = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "C"}], polygeist.varname = "C"} : memref<64xi32>
  %idx = memref.alloca() {polygeist.varname = "idx"} : memref<1024xi32>
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %idx[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %k = affine.load %idx[%i] : memref<1024xi32>
    %a = arith.index_cast %k : i32 to index
    %x = affine.load %v[%i] : memref<1024xi32>
    memref.store %x, %C[%a] : memref<64xi32>
  }
  affine.for %i = 0 to 64 {
    %0 = affine.load %C[%i] : memref<64xi32>
    affine.store %0, %out[%i] : memref<64xi32>
  }
  return
}
