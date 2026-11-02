// RUN: hls-est %s --lower-polygeist-subindex --memory-banking-bram | FileCheck %s

// A row argument shifts the parameter's partition dimension by one (N17 (b):
// cyclic 4 on dim 1 of the parameter -> dim 2 of A[4][1024]), except when the
// whole array has a single row: Vitis then keeps one bank of A[1][1024]
// ("Complete partitioning on dimension 1", w7_prop_row1; forgebench
// mult_op_module_dot BRAM_C1 / BRAM_C2, VITIS_NOTES.md N24).

func.func private @f(%a: memref<1024xi32> {hls.array_partition = [{dim = 1 : i32, factor = 4 : i32, kind = "cyclic"}]}, %o: memref<1024xi32>) attributes {hls.inline_off} {
  affine.for %i = 0 to 1024 {
    %0 = affine.load %a[%i] : memref<1024xi32>
    affine.store %0, %o[%i] : memref<1024xi32>
  }
  return
}

// Four rows: split on dimension 2 into 4 banks of 4x256.
// CHECK-LABEL: func.func @four_rows
// CHECK-COUNT-4: memref.alloca() {{.*}}hls.bank_of = "A4"{{.*}}hls.partition = {dim = 2 : i32, factor = 4 : i32{{.*}} : memref<4x256xi32>
func.func @four_rows(%in: memref<4x1024xi32>, %out: memref<1024xi32>) {
  %a = memref.alloca() {polygeist.varname = "A4"} : memref<4x1024xi32>
  affine.for %k = 0 to 4 {
    affine.for %i = 0 to 1024 {
      %0 = affine.load %in[%k, %i] : memref<4x1024xi32>
      affine.store %0, %a[%k, %i] : memref<4x1024xi32>
    }
  }
  %c1 = arith.constant 1 : index
  %row = "polygeist.subindex"(%a, %c1) : (memref<4x1024xi32>, index) -> memref<1024xi32>
  call @f(%row, %out) : (memref<1024xi32>, memref<1024xi32>) -> ()
  return
}

// One row: one array, not split.
// CHECK-LABEL: func.func @one_row
// CHECK: memref.alloca() {polygeist.varname = "A1"} : memref<1x1024xi32>
// CHECK-NOT: hls.bank_of = "A1"
// CHECK: return
func.func @one_row(%in: memref<1024xi32>, %out: memref<1024xi32>) {
  %a = memref.alloca() {polygeist.varname = "A1"} : memref<1x1024xi32>
  affine.for %i = 0 to 1024 {
    %0 = affine.load %in[%i] : memref<1024xi32>
    affine.store %0, %a[0, %i] : memref<1x1024xi32>
  }
  %c0 = arith.constant 0 : index
  %row = "polygeist.subindex"(%a, %c0) : (memref<1x1024xi32>, index) -> memref<1024xi32>
  call @f(%row, %out) : (memref<1024xi32>, memref<1024xi32>) -> ()
  return
}
