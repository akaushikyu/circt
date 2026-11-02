// RUN: hls-est %s --narrow-ram-widths=remarks=true -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --narrow-ram-widths=remarks=true --config-set=tool.hls.narrowing.callee_param_stores_full_range=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// W9 round 21 review (2026-10-25): VITIS_NOTES N162. A flag array set to 0
// in the caller and to 1 only inside a function kept as a call, through a
// scalar reference parameter (`int &seen`), keeps its declared width in
// Vitis: kernel w9r21fx_x1_plainref 128 x 32; gnnbuilder pna_qm9
// `min_incremental_data::one_sample_processed` is 32 bits in all five
// 128-deep rows (inlined, the max aggregation's field is 1 bit). The same
// flags passed as a whole array the callee indexes (`int seen[128]`, kernel
// w9r21fx_x2_plainarr) are 1 bit in Vitis. Off: the callee's store of 1 joins
// the range and the reference flag is 1 bit too.
// CHECK-DAG: remark: narrow-ram-widths: 32 of 32 bits{{.*}}written through a scalar reference parameter of a called function
// CHECK-DAG: remark: narrow-ram-widths: 1 of 32 bits; stored values [0, 1]{{.*}}store to 'argument 1 of @top2'
// OFF: remark: narrow-ram-widths: 1 of 32 bits; stored values [0, 1]{{.*}}store to 'argument 1 of @top'
// OFF: remark: narrow-ram-widths: 1 of 32 bits; stored values [0, 1]{{.*}}store to 'argument 1 of @top2'

module {
  func.func private @update(%flag: memref<?xi32>, %v: i32) attributes {hls.inline_off} {
    %c0 = arith.constant 0 : index
    %c1_i32 = arith.constant 1 : i32
    memref.store %c1_i32, %flag[%c0] : memref<?xi32>
    return
  }
  func.func @top(%in: memref<64x128xi32>, %out: memref<128xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %c0 = arith.constant 0 : index
    %seen = memref.alloca() {polygeist.varname = "seen"} : memref<128xi32>
    affine.for %i = 0 to 128 {
      affine.store %c0_i32, %seen[%i] : memref<128xi32>
    }
    affine.for %e = 0 to 64 {
      affine.for %i = 0 to 128 {
        %x = affine.load %in[%e, %i] : memref<64x128xi32>
        %s = "polygeist.subindex"(%seen, %i) : (memref<128xi32>, index) -> memref<?xi32>
        func.call @update(%s, %x) : (memref<?xi32>, i32) -> ()
      }
    }
    affine.for %i = 0 to 128 {
      %f = affine.load %seen[%i] : memref<128xi32>
      %z = arith.cmpi eq, %f, %c0_i32 : i32
      %r = arith.extui %z : i1 to i32
      affine.store %r, %out[%i] : memref<128xi32>
    }
    return
  }
  func.func private @mark(%flags: memref<128xi32>) attributes {hls.inline_off} {
    %c1_i32 = arith.constant 1 : i32
    affine.for %i = 0 to 128 {
      affine.store %c1_i32, %flags[%i] : memref<128xi32>
    }
    return
  }
  func.func @top2(%in: memref<64x128xi32>, %out: memref<128xi32>) {
    %c0_i32 = arith.constant 0 : i32
    %seen = memref.alloca() {polygeist.varname = "seen_whole"} : memref<128xi32>
    affine.for %i = 0 to 128 {
      affine.store %c0_i32, %seen[%i] : memref<128xi32>
    }
    func.call @mark(%seen) : (memref<128xi32>) -> ()
    affine.for %i = 0 to 128 {
      %f = affine.load %seen[%i] : memref<128xi32>
      %z = arith.cmpi eq, %f, %c0_i32 : i32
      %r = arith.extui %z : i1 to i32
      affine.store %r, %out[%i] : memref<128xi32>
    }
    return
  }
}
