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

// A memcpy into an offset destination, `memcpy(&j[1024], in, 4096)`: cgeist
// puts a constant-offset GEP in front of the byte loop's GEP. It is still a
// copy-in, not an escape (w9rv_n41_mc, Vitis j 2048x10).
// CHECK-LABEL: func.func @memcpy_offset
// CHECK: memref.alloca() {hls.narrow_bits = 10 : i32, hls.narrow_reason = "10 of 32 bits: stored values: full range (filled by a memcpy copy-in){{.*}}", polygeist.varname = "j"}
func.func @memcpy_offset(%in: memref<2048xi32>, %tbl: memref<1000xi32>, %out: memref<2048xi32>) {
  %j = memref.alloca() {polygeist.varname = "j"} : memref<2048xi32>
  %d = "polygeist.memref2pointer"(%j) : (memref<2048xi32>) -> !llvm.ptr
  %d1 = llvm.getelementptr %d[4096] : (!llvm.ptr) -> !llvm.ptr, i8
  %s = "polygeist.memref2pointer"(%in) : (memref<2048xi32>) -> !llvm.ptr
  affine.for %b = 0 to 4096 {
    %i = arith.index_cast %b : index to i32
    %p = llvm.getelementptr %s[%i] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    %v = llvm.load %p : !llvm.ptr -> i8
    %q = llvm.getelementptr %d1[%i] : (!llvm.ptr, i32) -> !llvm.ptr, i8
    llvm.store %v, %q : i8, !llvm.ptr
  }
  affine.for %t = 0 to 1024 {
    %v = affine.load %in[%t] : memref<2048xi32>
    affine.store %v, %j[%t] : memref<2048xi32>
  }
  affine.for %t = 0 to 2048 {
    %0 = affine.load %j[%t] : memref<2048xi32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %tbl[%1] : memref<1000xi32>
    affine.store %2, %out[%t] : memref<2048xi32>
  }
  return
}

// The row index of a 2-D array whose rows are not a power of two long
// demands only the row bits: `A[i1[t]][i4[t]]` with A[100][10] gives i1 7
// bits (ceil(log2 100)), i4 the 10 of the linear address (w9rv_n41_2d /
// w9rv_n41_2dloc, Vitis i1 2048x7, i4 2048x10).
// CHECK-LABEL: func.func @row_index_2d
// CHECK: memref.alloca() {hls.narrow_bits = 7 : i32, {{.*}}polygeist.varname = "i1"}
// CHECK: memref.alloca() {hls.narrow_bits = 10 : i32, {{.*}}polygeist.varname = "i4"}
func.func @row_index_2d(%a: memref<100x10xi32>, %in: memref<2048xi32>, %out: memref<2048xi32>) {
  %i1 = memref.alloca() {polygeist.varname = "i1"} : memref<2048xi32>
  %i4 = memref.alloca() {polygeist.varname = "i4"} : memref<2048xi32>
  affine.for %t = 0 to 2048 {
    %v = affine.load %in[%t] : memref<2048xi32>
    affine.store %v, %i1[%t] : memref<2048xi32>
    affine.store %v, %i4[%t] : memref<2048xi32>
  }
  affine.for %t = 0 to 2048 {
    %r = affine.load %i1[%t] : memref<2048xi32>
    %c = affine.load %i4[%t] : memref<2048xi32>
    %ri = arith.index_cast %r : i32 to index
    %ci = arith.index_cast %c : i32 to index
    %x = memref.load %a[%ri, %ci] : memref<100x10xi32>
    affine.store %x, %out[%t] : memref<2048xi32>
  }
  return
}
