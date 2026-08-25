// RUN: hls-est %s --narrow-ram-widths | FileCheck %s

// --narrow-ram-widths and top-level array arguments (VITIS_NOTES N41,
// Vitis 2025.1 td=off, kernels w9p5_idx_*): a subscript of an array argument
// without an interface pragma (an ap_memory port under flow_target=vivado)
// demands the bits of that array's address, as for a local; a subscript of
// an m_axi argument (tool.hls.narrowing.full_address_interface_modes)
// demands every bit. A memcpy into a local array, which cgeist lowers to a
// byte-copy loop through polygeist.memref2pointer, stores values nothing is
// known about: the array is not an escape, its width is what its loads'
// users demand.

// `int NL_buf[4096]; memcpy(NL_buf, NL, ...); ... pos[NL_buf[..]]` with
// `double pos[256]` an ap_memory argument: 8 bits (w9p5_idx_mem256, Vitis
// NL_buf 4096x8).
// CHECK-LABEL: func.func @memcpy_apmem
// CHECK: memref.alloca() {hls.narrow_bits = 8 : i32, hls.narrow_reason = "8 of 32 bits: stored values: full range (filled by a memcpy copy-in); loads demand 8 bits: {{.*}}subscript of 'argument 1 of @memcpy_apmem'{{.*}}", polygeist.varname = "NL_buf"}
func.func @memcpy_apmem(%nl: memref<4096xi32>, %pos: memref<256xf64>, %out: memref<256xf64>) {
  %buf = memref.alloca() {polygeist.varname = "NL_buf"} : memref<4096xi32>
  %d = "polygeist.memref2pointer"(%buf) : (memref<4096xi32>) -> !llvm.ptr
  %s = "polygeist.memref2pointer"(%nl) : (memref<4096xi32>) -> !llvm.ptr
  affine.for %b = 0 to 16384 {
    %i = arith.index_cast %b : index to i32
    %p = llvm.getelementptr %s[%i] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    %v = llvm.load %p : !llvm.ptr -> i8
    %q = llvm.getelementptr %d[%i] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    llvm.store %v, %q : i8, !llvm.ptr
  }
  affine.for %i = 0 to 256 {
    %0 = affine.load %buf[%i * 16] : memref<4096xi32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %pos[%1] : memref<256xf64>
    affine.store %2, %out[%i] : memref<256xf64>
  }
  return
}

// The same with a 1000-word argument: 10 bits (w9p5_idx_mem1000).
// CHECK-LABEL: func.func @memcpy_apmem1000
// CHECK: hls.narrow_bits = 10 : i32
func.func @memcpy_apmem1000(%nl: memref<4096xi32>, %pos: memref<1000xf64>, %out: memref<256xf64>) {
  %buf = memref.alloca() {polygeist.varname = "NL_buf"} : memref<4096xi32>
  %d = "polygeist.memref2pointer"(%buf) : (memref<4096xi32>) -> !llvm.ptr
  %s = "polygeist.memref2pointer"(%nl) : (memref<4096xi32>) -> !llvm.ptr
  affine.for %b = 0 to 16384 {
    %i = arith.index_cast %b : index to i32
    %p = llvm.getelementptr %s[%i] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    %v = llvm.load %p : !llvm.ptr -> i8
    %q = llvm.getelementptr %d[%i] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    llvm.store %v, %q : i8, !llvm.ptr
  }
  affine.for %i = 0 to 256 {
    %0 = affine.load %buf[%i * 16] : memref<4096xi32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %pos[%1] : memref<1000xf64>
    affine.store %2, %out[%i] : memref<256xf64>
  }
  return
}

// `pos` an m_axi argument: the subscript is part of a bus address and
// demands every bit, NL_buf stays 32 bits (w9p5_idx_maxi256).
// CHECK-LABEL: func.func @copy_maxi
// CHECK: memref.alloca() {polygeist.varname = "NL_buf"}
func.func @copy_maxi(%nl: memref<4096xi32>, %pos: memref<256xf64> {hls.interface = [{bundle = "g1", mode = "m_axi", offset = "slave", port = "pos"}]}, %out: memref<256xf64>) {
  %buf = memref.alloca() {polygeist.varname = "NL_buf"} : memref<4096xi32>
  affine.for %i = 0 to 4096 {
    %0 = affine.load %nl[%i] : memref<4096xi32>
    affine.store %0, %buf[%i] : memref<4096xi32>
  }
  affine.for %i = 0 to 256 {
    %0 = affine.load %buf[%i * 16] : memref<4096xi32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %pos[%1] : memref<256xf64>
    affine.store %2, %out[%i] : memref<256xf64>
  }
  return
}

// A pointer use that is not a byte-copy destination (here the array is
// read through the pointer) is still an escape: not narrowed.
// CHECK-LABEL: func.func @memcpy_out
// CHECK: memref.alloca() {polygeist.varname = "NL_buf"}
func.func @memcpy_out(%nl: memref<4096xi32>, %pos: memref<256xf64>, %out: memref<256xf64>, %o2: memref<4096xi32>) {
  %buf = memref.alloca() {polygeist.varname = "NL_buf"} : memref<4096xi32>
  affine.for %i = 0 to 4096 {
    %0 = affine.load %nl[%i] : memref<4096xi32>
    affine.store %0, %buf[%i] : memref<4096xi32>
  }
  %s = "polygeist.memref2pointer"(%buf) : (memref<4096xi32>) -> !llvm.ptr
  %d = "polygeist.memref2pointer"(%o2) : (memref<4096xi32>) -> !llvm.ptr
  affine.for %b = 0 to 16384 {
    %i = arith.index_cast %b : index to i32
    %p = llvm.getelementptr %s[%i] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    %v = llvm.load %p : !llvm.ptr -> i8
    %q = llvm.getelementptr %d[%i] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    llvm.store %v, %q : i8, !llvm.ptr
  }
  affine.for %i = 0 to 256 {
    %0 = affine.load %buf[%i * 16] : memref<4096xi32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %pos[%1] : memref<256xf64>
    affine.store %2, %out[%i] : memref<256xf64>
  }
  return
}
