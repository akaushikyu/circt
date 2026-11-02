// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_i --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.folding.drop_asserts=true --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=ON

// VITIS_NOTES N126, kernel w9r16p_as (Vitis 2025.1 td=off: 2, the same as w9r16p_as_no):
// an assert in a pipeline II=5 loop changes nothing in Vitis. tool.hls.folding.drop_asserts
// erases the __assert_fail call (with it the loop is scheduled at II 5 as without the assert,
// 1 BRAM; Vitis 2 at II 3, OPEN_ISSUES O164). Off by default: on pp4fpgas huffman the
// scheduled create_tree loop puts two reads in one state at II 5 where Vitis spreads them
// (OPEN_ISSUES O166). Default: the loop with the call is not scheduled (2).
// CHECK: Total BRAM: 2
// ON: Total BRAM: 1

#map = affine_map<()[s0] -> (s0 - 1)>
#set = affine_set<(d0) : (d0 == 0)>
module {
  llvm.mlir.global internal constant @str2("void top(int *, int *, int)\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str1("as.cpp\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str0("i == 0 || f[i] >= f[i-1]\00") {addr_space = 0 : i32}
  func.func @_Z3topPiS_i(%arg0: memref<256xi32>, %arg1: memref<256xi32>, %arg2: i32) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i32 = arith.constant 0 : i32
    %c255_i32 = arith.constant 255 : i32
    %c1_i32 = arith.constant 1 : i32
    %c13_i32 = arith.constant 13 : i32
    %c127_i32 = arith.constant 127 : i32
    %true = arith.constant true
    %0 = arith.index_cast %arg2 : i32 to index
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "f"} : memref<255xi32>
    affine.for %arg3 = 0 to 255 {
      %8 = affine.load %arg0[%arg3] : memref<256xi32>
      affine.store %8, %alloca[%arg3] : memref<255xi32>
    }
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr
    %2 = llvm.mlir.addressof @str1 : !llvm.ptr
    %3 = llvm.mlir.addressof @str2 : !llvm.ptr
    %4 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<?xi8>
    %5 = "polygeist.pointer2memref"(%2) : (!llvm.ptr) -> memref<?xi8>
    %6 = "polygeist.pointer2memref"(%3) : (!llvm.ptr) -> memref<?xi8>
    %7 = affine.for %arg3 = 0 to #map()[%0] iter_args(%arg4 = %c0_i32) -> (i32) {
      %8 = arith.index_cast %arg4 : i32 to index
      %9 = memref.load %alloca[%8] : memref<255xi32>
      %10 = arith.addi %arg4, %c1_i32 : i32
      %11 = arith.remsi %10, %c255_i32 : i32
      %12 = arith.index_cast %11 : i32 to index
      %13 = memref.load %alloca[%12] : memref<255xi32>
      %14 = arith.addi %9, %13 : i32
      affine.store %14, %alloca[%arg3] : memref<255xi32>
      %15 = affine.if #set(%arg3) -> i1 {
        affine.yield %true : i1
      } else {
        %18 = affine.load %alloca[%arg3 - 1] : memref<255xi32>
        %19 = arith.cmpi sge, %14, %18 : i32
        affine.yield %19 : i1
      }
      scf.if %15 {
      } else {
        func.call @__assert_fail(%4, %5, %c13_i32, %6) : (memref<?xi8>, memref<?xi8>, i32, memref<?xi8>) -> ()
      }
      %16 = arith.addi %arg4, %9 : i32
      %17 = arith.andi %16, %c127_i32 : i32
      affine.yield %17 : i32
    } {hls.pipeline = [{II = 5 : i32, rewind = false, style = "stp"}]}
    affine.for %arg3 = 0 to 255 {
      %8 = affine.load %alloca[%arg3] : memref<255xi32>
      affine.store %8, %arg1[%arg3] : memref<256xi32>
    }
    return
  }
  func.func private @__assert_fail(memref<?xi8>, memref<?xi8>, i32, memref<?xi8>) attributes {hls.orig_name = "__assert_fail", llvm.linkage = #llvm.linkage<external>}
}
