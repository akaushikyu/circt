// RUN: hls-est %s --split-struct-memrefs | FileCheck %s

// A global array of structs initialised from constants: memref.global cannot
// hold a value of llvm.struct elements, so cgeist (--scalar-wrapper-abi)
// gives it as `hls.struct_initial_value`, one attribute per scalar in memory
// order (elements, then members); the split per-member globals get it as
// their initial values (kernel w11rv_g3: `static const C ctab[4] =
// {{0.5, 1}, ...}` with C { ap_fixed<16,8> a; ap_int<6> b; }).

// CHECK: memref.global "private" @ctab_0 : memref<4xi16> = dense<[128, -320, 32765, 32640]>
// CHECK: memref.global "private" @ctab_1 : memref<4xi6> = dense<[1, -2, 31, 31]>
// CHECK-NOT: hls.struct_initial_value

module {
  memref.global "private" @ctab : memref<4x!llvm.struct<(i16, i6)>> = uninitialized {hls.struct_initial_value = [128 : i16, 1 : i6, -320 : i16, -2 : i6, 32765 : i16, 31 : i6, 32640 : i16, 31 : i6]}
  func.func @top(%idx: memref<64xi32>, %out: memref<64xi32>) {
    %g = memref.get_global @ctab : memref<4x!llvm.struct<(i16, i6)>>
    affine.for %i = 0 to 64 {
      %k = affine.load %idx[%i] : memref<64xi32>
      %ki = arith.index_cast %k : i32 to index
      %s = memref.load %g[%ki] : memref<4x!llvm.struct<(i16, i6)>>
      %a = llvm.extractvalue %s[0] : !llvm.struct<(i16, i6)>
      %b = llvm.extractvalue %s[1] : !llvm.struct<(i16, i6)>
      %ae = arith.extsi %a : i16 to i32
      %be = arith.extsi %b : i6 to i32
      %r = arith.addi %ae, %be : i32
      affine.store %r, %out[%i] : memref<64xi32>
    }
    return
  }
}
