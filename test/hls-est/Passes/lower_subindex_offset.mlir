// RUN: hls-est %s --lower-polygeist-subindex -o - | FileCheck %s
// RUN: hls-est %s --lower-polygeist-subindex --bram-analysis=top=offsets -o /dev/null | FileCheck %s --check-prefix=BRAM

// `f(M + N)` passes the elements of M from N on as an array: cgeist emits a
// `polygeist.subindex` of the same rank (an offset view). It is lowered like
// a row: an access through the view moves its first index by the offset, a
// call passing it goes to a clone of the callee that takes the whole array
// and the offset (Vitis 2025.1 td=off, kernel p_two: `fill(L, s);
// fill(M + N, s + 1);` with M[2N] builds M as one 512-word memory that both
// halves of the code write).

// CHECK-LABEL: func.func private @fill_off_0(
// CHECK-SAME:    %[[P:.*]]: memref<512xi32>, %[[O:.*]]: index {hls.view_index}, %{{.*}}: i32)
// CHECK:         affine.store %{{.*}}, %[[P]][%{{.*}} + symbol(%[[O]])] : memref<512xi32>
// CHECK-LABEL: func.func @offsets
// CHECK:         call @fill(%{{.*}}, %{{.*}}) : (memref<256xi32>, i32) -> ()
// CHECK:         call @fill_off_0(%[[M:.*]], %{{.*}}, %{{.*}}) : (memref<512xi32>, index, i32) -> ()
// CHECK:         affine.load %[[M]][%{{.*}} + symbol(%{{.*}})] : memref<512xi32>
// CHECK-NOT:     polygeist.subindex

// BRAM: Total BRAM: 3

module {
  func.func private @fill(%p: memref<256xi32>, %k: i32) attributes {hls.inline_off} {
    affine.for %i = 0 to 256 {
      %c = arith.index_cast %i : index to i32
      %v = arith.muli %c, %k : i32
      affine.store %v, %p[%i] : memref<256xi32>
    }
    return
  }
  func.func @offsets(%s: i32, %out: memref<256xi32>) {
    %c256 = arith.constant 256 : index
    %L = memref.alloca() {hls.preserve, polygeist.varname = "L"} : memref<256xi32>
    %M = memref.alloca() {hls.preserve, polygeist.varname = "M"} : memref<512xi32>
    func.call @fill(%L, %s) : (memref<256xi32>, i32) -> ()
    %hi = "polygeist.subindex"(%M, %c256) : (memref<512xi32>, index) -> memref<256xi32>
    func.call @fill(%hi, %s) : (memref<256xi32>, i32) -> ()
    affine.for %i = 0 to 256 {
      %a = affine.load %L[%i] : memref<256xi32>
      %b = affine.load %hi[%i] : memref<256xi32>
      %c = affine.load %M[%i] : memref<512xi32>
      %d = arith.addi %a, %b : i32
      %e = arith.addi %d, %c : i32
      affine.store %e, %out[%i] : memref<256xi32>
    }
    return
  }
}
