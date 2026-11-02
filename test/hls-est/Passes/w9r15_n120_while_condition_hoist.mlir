// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_iS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_iS_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.middle_end.licm_hoist_while_conditions=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N120, kernel w9r15i_rp_strm (Vitis 2025.1 td=off: 2, rp
// RAM_AUTO_1R1W): the davendra lab3 read_csr_row shape, a CSR row loop whose body
// writes two streams (cgeist: scf.while re-reading rp[r + 1] in its condition).
// The invariant bound load moves in front of the loop
// (tool.hls.middle_end.licm_hoist_while_conditions), so rp[r] and rp[r + 1] share
// a state: two ports, 2 BRAM.
// Off run: the bound stays in the condition, one port (1).
// CHECK: Total BRAM: 2
// OFF: Total BRAM: 1

module {
  llvm.mlir.global internal constant @str1("cs\00") {addr_space = 0 : i32}
  llvm.mlir.global internal constant @str0("vs\00") {addr_space = 0 : i32}
  func.func @_Z3topPiS_S_iS_(%arg0: memref<65xi32>, %arg1: memref<4096xi32>, %arg2: memref<4096xi32>, %arg3: i32, %arg4: memref<4096xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {polygeist.varname = "cs"} : memref<1xi32>
    %cast = memref.cast %alloca : memref<1xi32> to memref<?xi32>
    %0 = llvm.mlir.undef : i32
    affine.store %0, %alloca[0] : memref<1xi32>
    %alloca_0 = memref.alloca() {polygeist.varname = "vs"} : memref<1xi32>
    %cast_1 = memref.cast %alloca_0 : memref<1xi32> to memref<?xi32>
    affine.store %0, %alloca_0[0] : memref<1xi32>
    %alloca_2 = memref.alloca() {hls.preserve, polygeist.varname = "rp"} : memref<65xi32>
    affine.for %arg5 = 0 to 65 {
      %5 = affine.load %arg0[%arg5] : memref<65xi32>
      affine.store %5, %alloca_2[%arg5] : memref<65xi32>
    }
    %1 = llvm.mlir.addressof @str0 : !llvm.ptr
    %2 = "polygeist.pointer2memref"(%1) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamIiLi0EEC1EPKc(%cast_1, %2) : (memref<?xi32>, memref<?xi8>) -> ()
    %3 = llvm.mlir.addressof @str1 : !llvm.ptr
    %4 = "polygeist.pointer2memref"(%3) : (!llvm.ptr) -> memref<?xi8>
    call @_ZN3hls6streamIiLi0EEC1EPKc(%cast, %4) : (memref<?xi32>, memref<?xi8>) -> ()
    call @_ZL2rdPiS_S_RN3hls6streamIiLi0EEES3_(%alloca_2, %arg1, %arg2, %cast_1, %cast) : (memref<65xi32>, memref<4096xi32>, memref<4096xi32>, memref<?xi32>, memref<?xi32>) -> ()
    call @_ZL2wrRN3hls6streamIiLi0EEES2_iPi(%cast_1, %cast, %arg3, %arg4) : (memref<?xi32>, memref<?xi32>, i32, memref<4096xi32>) -> ()
    return
  }
  func.func private @_ZN3hls6streamIiLi0EEC1EPKc(memref<?xi32>, memref<?xi8>) attributes {hls.orig_name = "stream", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZL2rdPiS_S_RN3hls6streamIiLi0EEES3_(%arg0: memref<65xi32>, %arg1: memref<4096xi32>, %arg2: memref<4096xi32>, %arg3: memref<?xi32>, %arg4: memref<?xi32>) attributes {hls.inline_off, hls.orig_name = "rd", llvm.linkage = #llvm.linkage<internal>} {
    %c1_i32 = arith.constant 1 : i32
    affine.for %arg5 = 0 to 64 {
      %0 = affine.load %arg0[%arg5] : memref<65xi32>
      %1 = scf.while (%arg6 = %0) : (i32) -> i32 {
        %2 = affine.load %arg0[%arg5 + 1] : memref<65xi32>
        %3 = arith.cmpi slt, %arg6, %2 : i32
        scf.condition(%3) %arg6 : i32
      } do {
      ^bb0(%arg6: i32):
        %2 = arith.index_cast %arg6 : i32 to index
        %3 = "polygeist.subindex"(%arg1, %2) : (memref<4096xi32>, index) -> memref<?xi32>
        func.call @_ZN3hls6streamIiLi0EElsERKi(%arg3, %3) : (memref<?xi32>, memref<?xi32>) -> ()
        %4 = "polygeist.subindex"(%arg2, %2) : (memref<4096xi32>, index) -> memref<?xi32>
        func.call @_ZN3hls6streamIiLi0EElsERKi(%arg4, %4) : (memref<?xi32>, memref<?xi32>) -> ()
        %5 = arith.addi %arg6, %c1_i32 : i32
        scf.yield %5 : i32
      }
    }
    return
  }
  func.func private @_ZL2wrRN3hls6streamIiLi0EEES2_iPi(%arg0: memref<?xi32>, %arg1: memref<?xi32>, %arg2: i32, %arg3: memref<4096xi32>) attributes {hls.inline_off, hls.orig_name = "wr", llvm.linkage = #llvm.linkage<internal>} {
    %0 = arith.index_cast %arg2 : i32 to index
    affine.for %arg4 = 0 to %0 {
      %1 = func.call @_ZN3hls6streamIiLi0EE4readEv(%arg0) : (memref<?xi32>) -> i32
      %2 = func.call @_ZN3hls6streamIiLi0EE4readEv(%arg1) : (memref<?xi32>) -> i32
      %3 = arith.addi %1, %2 : i32
      affine.store %3, %arg3[%arg4] : memref<4096xi32>
    }
    return
  }
  func.func private @_ZN3hls6streamIiLi0EElsERKi(memref<?xi32>, memref<?xi32>) attributes {hls.orig_name = "operator<<", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
  func.func private @_ZN3hls6streamIiLi0EE4readEv(memref<?xi32>) -> i32 attributes {hls.orig_name = "read", hls.stream_element_bits = 32 : i64, llvm.linkage = #llvm.linkage<external>}
}
