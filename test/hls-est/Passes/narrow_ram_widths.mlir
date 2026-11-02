// RUN: hls-est %s --narrow-ram-widths | FileCheck %s
// RUN: hls-est %s --narrow-ram-widths=stored-ranges=false | FileCheck %s --check-prefix=NORANGE
// RUN: hls-est %s --narrow-ram-widths=load-demand=false | FileCheck %s --check-prefix=NODEMAND

// --narrow-ram-widths marks the element width Vitis stores per word:
// min(bits the stored values need, low bits the loads' users demand). Each
// function below is one td=off kernel of the w9n_* set (Vitis 2025.1, the
// `Bits` of the memory row); the expected width is in the CHECK line.

// `tbl[a[i]]` over a 64-word table: the index needs 6 bits (w9n_h1_t64);
// `tbl` itself feeds an interface store and stays 32 bits.
// CHECK-LABEL: func.func @index_use
// CHECK:  memref.alloca() {polygeist.varname = "tbl"}
// CHECK:  memref.alloca() {hls.narrow_bits = 6 : i32, hls.narrow_reason = "6 of 32 bits: {{.*}}loads demand 6 bits: affine.load {{.*}} -> arith.index_cast -> subscript of 'tbl'{{.*}}", polygeist.varname = "a"}
// NORANGE-LABEL: func.func @index_use
// NORANGE:  hls.narrow_bits = 6 : i32
// NODEMAND-LABEL: func.func @index_use
// NODEMAND-NOT:  hls.narrow_bits
// NODEMAND:  return
func.func @index_use(%in: memref<1024xi32>, %v: memref<64xi32>, %out: memref<1024xi32>) {
  %tbl = memref.alloca() {polygeist.varname = "tbl"} : memref<64xi32>
  %a = memref.alloca() {polygeist.varname = "a"} : memref<1024xi32>
  affine.for %i = 0 to 64 {
    %0 = affine.load %v[%i] : memref<64xi32>
    affine.store %0, %tbl[%i] : memref<64xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %a[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %a[%i] : memref<1024xi32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %tbl[%1] : memref<64xi32>
    affine.store %2, %out[%i] : memref<1024xi32>
  }
  return
}

// A 2-D table `t[64][64]`: an index on the last dimension needs the 12 bits
// of the flattened address (w9n_h1_2dlast), one on the first dimension 6
// (w9n_h1_2dfirst); `a + 1` passes the low bits through (w9n_h1_plus1).
// CHECK-LABEL: func.func @index_2d
// CHECK:  hls.narrow_bits = 12 : i32{{.*}}polygeist.varname = "last"
// CHECK:  hls.narrow_bits = 6 : i32{{.*}}polygeist.varname = "first"
func.func @index_2d(%in: memref<1024xi32>, %t: memref<64x64xi32>, %out: memref<1024xi32>) {
  %c1 = arith.constant 1 : i32
  %t2 = memref.alloca() {polygeist.varname = "t2"} : memref<64x64xi32>
  %last = memref.alloca() {polygeist.varname = "last"} : memref<1024xi32>
  %first = memref.alloca() {polygeist.varname = "first"} : memref<1024xi32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %t[%i, %j] : memref<64x64xi32>
      affine.store %0, %t2[%i, %j] : memref<64x64xi32>
    }
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %last[%i] : memref<1024xi32>
    affine.store %0, %first[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %r = affine.apply affine_map<(d0) -> (d0 mod 64)>(%i)
    %0 = affine.load %last[%i] : memref<1024xi32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %t2[%r, %1] : memref<64x64xi32>
    %3 = affine.load %first[%i] : memref<1024xi32>
    %4 = arith.addi %3, %c1 : i32
    %5 = arith.index_cast %4 : i32 to index
    %6 = memref.load %t2[%5, %r] : memref<64x64xi32>
    %7 = arith.addi %2, %6 : i32
    affine.store %7, %out[%i] : memref<1024xi32>
  }
  return
}

// A comparison needs every bit (w9n_h1_cmp: 32); a mask keeps up to its
// highest set bit, low bits included (w9n_h2_f0, `& 0xF0`: 8); a shift right
// by 4 then `& 0xF` needs bits 4..7 (w9n_h2_shr: 8).
// CHECK-LABEL: func.func @uses
// CHECK:  memref.alloca() {polygeist.varname = "cmp"}
// CHECK:  hls.narrow_bits = 8 : i32{{.*}}polygeist.varname = "mask"
// CHECK:  hls.narrow_bits = 8 : i32{{.*}}polygeist.varname = "shr"
func.func @uses(%in: memref<1024xi32>, %out: memref<1024xi32>, %flag: memref<1024xi1>) {
  %c4 = arith.constant 4 : i32
  %c5 = arith.constant 5 : i32
  %c15 = arith.constant 15 : i32
  %c240 = arith.constant 240 : i32
  %cmp = memref.alloca() {polygeist.varname = "cmp"} : memref<1024xi32>
  %mask = memref.alloca() {polygeist.varname = "mask"} : memref<1024xi32>
  %shr = memref.alloca() {polygeist.varname = "shr"} : memref<1024xi32>
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %cmp[%i] : memref<1024xi32>
    affine.store %0, %mask[%i] : memref<1024xi32>
    affine.store %0, %shr[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %cmp[%i] : memref<1024xi32>
    %1 = arith.cmpi slt, %0, %c5 : i32
    affine.store %1, %flag[%i] : memref<1024xi1>
    %2 = affine.load %mask[%i] : memref<1024xi32>
    %3 = arith.andi %2, %c240 : i32
    %4 = affine.load %shr[%i] : memref<1024xi32>
    %5 = arith.shrsi %4, %c4 : i32
    %6 = arith.andi %5, %c15 : i32
    %7 = arith.addi %3, %6 : i32
    affine.store %7, %out[%i] : memref<1024xi32>
  }
  return
}

// Stored ranges: ReLU (`maxsi` or a select on the sign) is 31 bits and so is
// a copy of it (w9n_h3_relu, w9n_h3_api, w9n_h3_relucopy); a clamp through
// an scf.if to [-128, 127] is 8 (w9n_h3_clamps); a loop counter below 1024
// is 10 (w9n_h3_ctr).
// CHECK-LABEL: func.func @ranges
// CHECK:  hls.narrow_bits = 31 : i32{{.*}}stored values [0, 2147483647] need 31 bits{{.*}}polygeist.varname = "relu"
// CHECK:  hls.narrow_bits = 31 : i32{{.*}}polygeist.varname = "copy"
// CHECK:  hls.narrow_bits = 31 : i32{{.*}}polygeist.varname = "sel"
// CHECK:  hls.narrow_bits = 8 : i32{{.*}}stored values [-128, 127]{{.*}}polygeist.varname = "clamp"
// CHECK:  hls.narrow_bits = 10 : i32{{.*}}polygeist.varname = "ctr"
// NODEMAND-LABEL: func.func @ranges
// NODEMAND:  hls.narrow_bits = 31 : i32
// NORANGE-LABEL: func.func @ranges
// NORANGE-NOT:  hls.narrow_bits
// NORANGE:  return
func.func @ranges(%in: memref<1024xi32>, %o1: memref<1024xi32>, %o2: memref<1024xi32>, %o3: memref<1024xi32>, %o4: memref<1024xi32>) {
  %c0 = arith.constant 0 : i32
  %c0_33 = arith.constant 0 : i33
  %c127 = arith.constant 127 : i32
  %cm128 = arith.constant -128 : i32
  %c1000 = arith.constant 1000 : i32
  %relu = memref.alloca() {polygeist.varname = "relu"} : memref<1024xi32>
  %copy = memref.alloca() {polygeist.varname = "copy"} : memref<1024xi32>
  %sel = memref.alloca() {polygeist.varname = "sel"} : memref<1024xi32>
  %clamp = memref.alloca() {polygeist.varname = "clamp"} : memref<1024xi32>
  %ctr = memref.alloca() {polygeist.varname = "ctr"} : memref<1024xi32>
  affine.for %i = 0 to 1024 {
    %x = affine.load %in[%i] : memref<1024xi32>
    %0 = arith.maxsi %x, %c0 : i32
    affine.store %0, %relu[%i] : memref<1024xi32>
    %w = arith.extsi %x : i32 to i33
    %p = arith.cmpi sgt, %w, %c0_33 : i33
    %1 = arith.select %p, %x, %c0 : i32
    affine.store %1, %sel[%i] : memref<1024xi32>
    %lt = arith.cmpi slt, %x, %cm128 : i32
    %2 = scf.if %lt -> (i32) {
      scf.yield %cm128 : i32
    } else {
      %m = arith.minsi %x, %c127 : i32
      scf.yield %m : i32
    }
    affine.store %2, %clamp[%i] : memref<1024xi32>
    %ii = arith.index_cast %i : index to i32
    %3 = arith.select %p, %ii, %c1000 : i32
    affine.store %3, %ctr[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %relu[%i] : memref<1024xi32>
    affine.store %0, %copy[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %copy[%i] : memref<1024xi32>
    affine.store %0, %o1[%i] : memref<1024xi32>
    %1 = affine.load %sel[%i] : memref<1024xi32>
    affine.store %1, %o2[%i] : memref<1024xi32>
    %2 = affine.load %clamp[%i] : memref<1024xi32>
    affine.store %2, %o3[%i] : memref<1024xi32>
    %3 = affine.load %ctr[%i] : memref<1024xi32>
    affine.store %3, %o4[%i] : memref<1024xi32>
  }
  return
}

// Across a kept callee: the scalar parameter has what its call site passes
// (`s & 0xF`: 4 bits, w9n_h3_calleearg), and the arrays that reach one
// memref parameter share one width (the larger: 4 for both).
// CHECK-LABEL: func.func private @fill
// CHECK-LABEL: func.func @callee_param
// CHECK:  hls.narrow_bits = 4 : i32{{.*}}polygeist.varname = "x"
// CHECK:  hls.narrow_bits = 4 : i32{{.*}}polygeist.varname = "y"
func.func private @fill(%a: memref<1024xi32>, %v: i32) {
  affine.for %i = 0 to 1024 {
    affine.store %v, %a[%i] : memref<1024xi32>
  }
  return
}
func.func @callee_param(%s: i32, %out: memref<1024xi32>) {
  %c15 = arith.constant 15 : i32
  %c3 = arith.constant 3 : i32
  %x = memref.alloca() {polygeist.varname = "x"} : memref<1024xi32>
  %y = memref.alloca() {polygeist.varname = "y"} : memref<1024xi32>
  %m = arith.andi %s, %c15 : i32
  %n = arith.andi %s, %c3 : i32
  func.call @fill(%x, %m) : (memref<1024xi32>, i32) -> ()
  func.call @fill(%y, %n) : (memref<1024xi32>, i32) -> ()
  affine.for %i = 0 to 1024 {
    %0 = affine.load %x[%i] : memref<1024xi32>
    %1 = affine.load %y[%i] : memref<1024xi32>
    %2 = arith.addi %0, %1 : i32
    affine.store %2, %out[%i] : memref<1024xi32>
  }
  return
}

// Not narrowed: a recurrence through the array (its stores depend on its
// own loads, which Vitis takes at full range: see @self_cycle), an
// initialised global never written (a
// ROM: --bram-analysis applies the ROM width rule), and an array passed to
// an unknown function.
// CHECK-LABEL: memref.global "private" constant @rom
// CHECK-NOT:   hls.narrow_bits
// CHECK-LABEL: func.func @not_narrowed
// CHECK-NOT:   hls.narrow_bits
// CHECK:       return
func.func private @ext(memref<1024xi32>)
memref.global "private" constant @rom : memref<4xi32> = dense<[1, 2, 3, 4]>
func.func @not_narrowed(%out: memref<1024xi32>) {
  %c1 = arith.constant 1 : i32
  %c0 = arith.constant 0 : i32
  %rec = memref.alloca() {polygeist.varname = "rec"} : memref<1024xi32>
  %esc = memref.alloca() {polygeist.varname = "esc"} : memref<1024xi32>
  %g = memref.get_global @rom : memref<4xi32>
  affine.store %c0, %rec[0] : memref<1024xi32>
  affine.for %i = 1 to 1024 {
    %0 = affine.load %rec[%i - 1] : memref<1024xi32>
    %1 = arith.addi %0, %c1 : i32
    affine.store %1, %rec[%i] : memref<1024xi32>
  }
  func.call @ext(%esc) : (memref<1024xi32>) -> ()
  affine.for %i = 0 to 1024 {
    %0 = affine.load %rec[%i] : memref<1024xi32>
    %1 = affine.load %esc[%i] : memref<1024xi32>
    %r = affine.apply affine_map<(d0) -> (d0 mod 4)>(%i)
    %2 = affine.load %g[%r] : memref<4xi32>
    %3 = arith.addi %0, %1 : i32
    %4 = arith.addi %3, %2 : i32
    affine.store %4, %out[%i] : memref<1024xi32>
  }
  return
}

// Partitions: a cyclic or block partition keeps the whole address (a
// 4096-word table cyclic factor 8: 12 bits, w9n_h1_cyc8); a complete
// partition removes its dimension (`t[8][64]` complete on the first
// dimension: a 64-word bank, 6 bits; a corpus design gives 9 for a 512-word
// bank).
// CHECK-LABEL: func.func @partitions
// CHECK:  hls.narrow_bits = 12 : i32{{.*}}polygeist.varname = "ic"
// CHECK:  hls.narrow_bits = 6 : i32{{.*}}polygeist.varname = "ip"
func.func @partitions(%in: memref<1024xi32>, %v: memref<4096xi32>, %out: memref<1024xi32>) {
  %c3 = arith.constant 3 : index
  %cyc = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 8 : i32, kind = "cyclic", variable = "cyc"}], polygeist.varname = "cyc"} : memref<4096xi32>
  %cp = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 0 : i32, kind = "complete", variable = "cp"}], polygeist.varname = "cp"} : memref<8x64xi32>
  %ic = memref.alloca() {polygeist.varname = "ic"} : memref<1024xi32>
  %ip = memref.alloca() {polygeist.varname = "ip"} : memref<1024xi32>
  affine.for %i = 0 to 4096 {
    %0 = affine.load %v[%i] : memref<4096xi32>
    affine.store %0, %cyc[%i] : memref<4096xi32>
  }
  affine.for %i = 0 to 8 {
    affine.for %j = 0 to 64 {
      %0 = affine.load %v[%i * 64 + %j] : memref<4096xi32>
      affine.store %0, %cp[%i, %j] : memref<8x64xi32>
    }
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %ic[%i] : memref<1024xi32>
    affine.store %0, %ip[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %ic[%i] : memref<1024xi32>
    %1 = arith.index_cast %0 : i32 to index
    %2 = memref.load %cyc[%1] : memref<4096xi32>
    %3 = affine.load %ip[%i] : memref<1024xi32>
    %4 = arith.index_cast %3 : i32 to index
    %5 = memref.load %cp[%c3, %4] : memref<8x64xi32>
    %6 = arith.addi %2, %5 : i32
    affine.store %6, %out[%i] : memref<1024xi32>
  }
  return
}

// Vitis does not iterate around a cycle of arrays: a store whose value is
// computed from loads of the same array sees those loads at full range
// (w9i_self: `a[i] = a[i + 1] ^ (a[i] >> 1)` after `a[i] = in[i] &
// 0xffffffff` keeps 64 bits), but a mask after such a load still bounds
// the value (w9i_selfadd: `(a[i + 1] & 0xf) + (a[i] & 0xf)` after `& 0xff`:
// 8 bits).
// CHECK-LABEL: func.func @self_cycle
// CHECK:  memref.alloca() {polygeist.varname = "self"}
// CHECK:  hls.narrow_bits = 8 : i32{{.*}}polygeist.varname = "selfadd"
func.func @self_cycle(%in: memref<1024xi64>, %o1: memref<1024xi64>, %in2: memref<1024xi32>, %o2: memref<1024xi32>) {
  %m32 = arith.constant 4294967295 : i64
  %c1 = arith.constant 1 : i64
  %cff = arith.constant 255 : i32
  %cf = arith.constant 15 : i32
  %self = memref.alloca() {polygeist.varname = "self"} : memref<1024xi64>
  %selfadd = memref.alloca() {polygeist.varname = "selfadd"} : memref<1024xi32>
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi64>
    %1 = arith.andi %0, %m32 : i64
    affine.store %1, %self[%i] : memref<1024xi64>
    %2 = affine.load %in2[%i] : memref<1024xi32>
    %3 = arith.andi %2, %cff : i32
    affine.store %3, %selfadd[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1023 {
    %0 = affine.load %self[%i + 1] : memref<1024xi64>
    %1 = affine.load %self[%i] : memref<1024xi64>
    %2 = arith.shrui %1, %c1 : i64
    %3 = arith.xori %0, %2 : i64
    affine.store %3, %self[%i] : memref<1024xi64>
    %4 = affine.load %selfadd[%i + 1] : memref<1024xi32>
    %5 = affine.load %selfadd[%i] : memref<1024xi32>
    %6 = arith.andi %4, %cf : i32
    %7 = arith.andi %5, %cf : i32
    %8 = arith.addi %6, %7 : i32
    affine.store %8, %selfadd[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %self[%i] : memref<1024xi64>
    affine.store %0, %o1[%i] : memref<1024xi64>
    %1 = affine.load %selfadd[%i] : memref<1024xi32>
    affine.store %1, %o2[%i] : memref<1024xi32>
  }
  return
}

// The same holds for the demanded bits: a value stored back into its own
// array keeps every bit, whatever its other uses demand (w9i_hist: a
// histogram `t[x] = t[x] + 1` read as `tbl[t[i] & 63]` stays 32 bits; the
// `& 63` alone would make it 6).
// CHECK-LABEL: func.func @histogram
// CHECK-NOT:   hls.narrow_bits
// CHECK:       return
func.func @histogram(%in: memref<1024xi32>, %v: memref<64xi32>, %out: memref<1024xi32>) {
  %c0 = arith.constant 0 : i32
  %c1 = arith.constant 1 : i32
  %c63 = arith.constant 63 : i32
  %c1023 = arith.constant 1023 : i32
  %t = memref.alloca() {polygeist.varname = "t"} : memref<1024xi32>
  %tbl = memref.alloca() {polygeist.varname = "tbl"} : memref<64xi32>
  affine.for %i = 0 to 64 {
    %0 = affine.load %v[%i] : memref<64xi32>
    affine.store %0, %tbl[%i] : memref<64xi32>
  }
  affine.for %i = 0 to 1024 {
    affine.store %c0, %t[%i] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    %1 = arith.andi %0, %c1023 : i32
    %2 = arith.index_cast %1 : i32 to index
    %3 = memref.load %t[%2] : memref<1024xi32>
    %4 = arith.addi %3, %c1 : i32
    memref.store %4, %t[%2] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %t[%i] : memref<1024xi32>
    %1 = arith.andi %0, %c63 : i32
    %2 = arith.index_cast %1 : i32 to index
    %3 = memref.load %tbl[%2] : memref<64xi32>
    affine.store %3, %out[%i] : memref<1024xi32>
  }
  return
}

// A copy between two memories of a complete partition is not a cycle: Vitis
// partitions before it narrows, so `t[i][k] = t[0][k]` (i in [1, 7], first
// dimension completely partitioned) copies one array into others (corpus
// class_ece8893_spring_2025 vishnu_varma_venkata lab3 `row_indices_B_local`,
// 8 x 4096 x 12 bits in Vitis). Used as an index of a 64-word table: 6 bits.
// CHECK-LABEL: func.func @bank_copy
// CHECK:  hls.narrow_bits = 6 : i32{{.*}}polygeist.varname = "rows"
func.func @bank_copy(%in: memref<64xi32>, %v: memref<64xi32>, %out: memref<8x64xi32>) {
  %c0 = arith.constant 0 : index
  %tbl = memref.alloca() {polygeist.varname = "tbl"} : memref<64xi32>
  %rows = memref.alloca() {hls.array_partition = [{dim = 1 : i32, factor = 0 : i32, kind = "complete", variable = "rows"}], polygeist.varname = "rows"} : memref<8x64xi32>
  affine.for %k = 0 to 64 {
    %0 = affine.load %v[%k] : memref<64xi32>
    affine.store %0, %tbl[%k] : memref<64xi32>
    %1 = affine.load %in[%k] : memref<64xi32>
    affine.store %1, %rows[0, %k] : memref<8x64xi32>
  }
  affine.for %i = 1 to 8 {
    affine.for %k = 0 to 64 {
      %0 = affine.load %rows[0, %k] : memref<8x64xi32>
      affine.store %0, %rows[%i, %k] : memref<8x64xi32>
    }
  }
  affine.for %i = 0 to 8 {
    affine.for %k = 0 to 64 {
      %0 = affine.load %rows[%i, %k] : memref<8x64xi32>
      %1 = arith.index_cast %0 : i32 to index
      %2 = memref.load %tbl[%1] : memref<64xi32>
      affine.store %2, %out[%i, %k] : memref<8x64xi32>
    }
  }
  return
}

// Bounds from `&&` / `||` guards. The front end lowers `x >= 0 && x < 300`
// to an scf.if yielding the second comparison or false: under it the stored
// x is [0, 299], 9 bits (Vitis td=off, w9rv_ifg: `b` 1024 x 9). The else arm
// of `x < 0 || x >= 300` (an scf.if yielding true or the second comparison)
// and an `arith.andi` of two comparisons bound the same way.
// CHECK-LABEL: func.func @guards
// CHECK:  hls.narrow_bits = 9 : i32{{.*}}stored values [0, 299]{{.*}}polygeist.varname = "b"
// CHECK:  hls.narrow_bits = 9 : i32{{.*}}stored values [0, 299]{{.*}}polygeist.varname = "c"
// CHECK:  hls.narrow_bits = 10 : i32{{.*}}stored values [0, 1023]{{.*}}polygeist.varname = "d"
func.func @guards(%in: memref<1024xi32>, %o1: memref<1024xi32>, %o2: memref<1024xi32>, %o3: memref<1024xi32>) {
  %c0 = arith.constant 0 : i32
  %c7 = arith.constant 7 : i32
  %c300 = arith.constant 300 : i32
  %c1024 = arith.constant 1024 : i32
  %false = arith.constant false
  %true = arith.constant true
  %b = memref.alloca() {polygeist.varname = "b"} : memref<1024xi32>
  %c = memref.alloca() {polygeist.varname = "c"} : memref<1024xi32>
  %d = memref.alloca() {polygeist.varname = "d"} : memref<1024xi32>
  affine.for %i = 0 to 1024 {
    %x = affine.load %in[%i] : memref<1024xi32>
    %ge = arith.cmpi sge, %x, %c0 : i32
    %and = scf.if %ge -> (i1) {
      %lt = arith.cmpi slt, %x, %c300 : i32
      scf.yield %lt : i1
    } else {
      scf.yield %false : i1
    }
    scf.if %and {
      affine.store %x, %b[%i] : memref<1024xi32>
    } else {
      affine.store %c7, %b[%i] : memref<1024xi32>
    }
    %neg = arith.cmpi slt, %x, %c0 : i32
    %or = scf.if %neg -> (i1) {
      scf.yield %true : i1
    } else {
      %big = arith.cmpi sge, %x, %c300 : i32
      scf.yield %big : i1
    }
    scf.if %or {
      affine.store %c7, %c[%i] : memref<1024xi32>
    } else {
      affine.store %x, %c[%i] : memref<1024xi32>
    }
    %lt2 = arith.cmpi slt, %x, %c1024 : i32
    %both = arith.andi %ge, %lt2 : i1
    scf.if %both {
      affine.store %x, %d[%i] : memref<1024xi32>
    }
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %b[%i] : memref<1024xi32>
    affine.store %0, %o1[%i] : memref<1024xi32>
    %1 = affine.load %c[%i] : memref<1024xi32>
    affine.store %1, %o2[%i] : memref<1024xi32>
    %2 = affine.load %d[%i] : memref<1024xi32>
    affine.store %2, %o3[%i] : memref<1024xi32>
  }
  return
}

// Sixteen unrolled stores `a[16i + k] = (x & 15) + 16k`: each one widens the
// range, but they are one pass over straight-line code, not a recurrence;
// [0, 255] is 8 bits (Vitis td=off, w9rv_wid: 1024 x 8).
// CHECK-LABEL: func.func @unrolled_stores
// CHECK:  hls.narrow_bits = 8 : i32{{.*}}stored values [0, 255]{{.*}}polygeist.varname = "a"
func.func @unrolled_stores(%in: memref<1024xi32>, %out: memref<1024xi32>) {
  %c0 = arith.constant 0 : i32
  %c15 = arith.constant 15 : i32
  %c16 = arith.constant 16 : i32
  %c32 = arith.constant 32 : i32
  %c48 = arith.constant 48 : i32
  %c64 = arith.constant 64 : i32
  %c80 = arith.constant 80 : i32
  %c96 = arith.constant 96 : i32
  %c112 = arith.constant 112 : i32
  %c128 = arith.constant 128 : i32
  %c144 = arith.constant 144 : i32
  %c160 = arith.constant 160 : i32
  %c176 = arith.constant 176 : i32
  %c192 = arith.constant 192 : i32
  %c208 = arith.constant 208 : i32
  %c224 = arith.constant 224 : i32
  %c240 = arith.constant 240 : i32
  %a = memref.alloca() {polygeist.varname = "a"} : memref<1024xi32>
  affine.for %i = 0 to 64 {
    %l = affine.load %in[%i] : memref<1024xi32>
    %x = arith.andi %l, %c15 : i32
    %v0 = arith.addi %x, %c0 : i32
    affine.store %v0, %a[%i * 16 + 0] : memref<1024xi32>
    %v1 = arith.addi %x, %c16 : i32
    affine.store %v1, %a[%i * 16 + 1] : memref<1024xi32>
    %v2 = arith.addi %x, %c32 : i32
    affine.store %v2, %a[%i * 16 + 2] : memref<1024xi32>
    %v3 = arith.addi %x, %c48 : i32
    affine.store %v3, %a[%i * 16 + 3] : memref<1024xi32>
    %v4 = arith.addi %x, %c64 : i32
    affine.store %v4, %a[%i * 16 + 4] : memref<1024xi32>
    %v5 = arith.addi %x, %c80 : i32
    affine.store %v5, %a[%i * 16 + 5] : memref<1024xi32>
    %v6 = arith.addi %x, %c96 : i32
    affine.store %v6, %a[%i * 16 + 6] : memref<1024xi32>
    %v7 = arith.addi %x, %c112 : i32
    affine.store %v7, %a[%i * 16 + 7] : memref<1024xi32>
    %v8 = arith.addi %x, %c128 : i32
    affine.store %v8, %a[%i * 16 + 8] : memref<1024xi32>
    %v9 = arith.addi %x, %c144 : i32
    affine.store %v9, %a[%i * 16 + 9] : memref<1024xi32>
    %v10 = arith.addi %x, %c160 : i32
    affine.store %v10, %a[%i * 16 + 10] : memref<1024xi32>
    %v11 = arith.addi %x, %c176 : i32
    affine.store %v11, %a[%i * 16 + 11] : memref<1024xi32>
    %v12 = arith.addi %x, %c192 : i32
    affine.store %v12, %a[%i * 16 + 12] : memref<1024xi32>
    %v13 = arith.addi %x, %c208 : i32
    affine.store %v13, %a[%i * 16 + 13] : memref<1024xi32>
    %v14 = arith.addi %x, %c224 : i32
    affine.store %v14, %a[%i * 16 + 14] : memref<1024xi32>
    %v15 = arith.addi %x, %c240 : i32
    affine.store %v15, %a[%i * 16 + 15] : memref<1024xi32>
  }
  affine.for %i = 0 to 1024 {
    %0 = affine.load %a[%i] : memref<1024xi32>
    affine.store %0, %out[%i] : memref<1024xi32>
  }
  return
}
