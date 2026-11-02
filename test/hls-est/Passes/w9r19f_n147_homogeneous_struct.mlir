// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP5cfg_tPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topP5cfg_tPKiPi -o /dev/null | FileCheck %s
// RUN: hls-est %s --config-set tool.hls.structs.top_pointer_scalar=false --symbol-privatize=exclude=_Z3topP5cfg_tPKiPi --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topP5cfg_tPKiPi -o /dev/null | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N147 / N144, W9 round 19 review defect 2 (kernel w9r19f_fx_h8): a
// pointer to a struct whose members all have one type (`struct cfg_t { int a, ...,
// h; }`) is lowered by cgeist as memref<?x8xi32>, like a pointer to an int[8];
// the top's mangled name (P5cfg_t) declares it a class pointer, so it is the same
// aggregated wide scalar as the heterogeneous form (fx_x8): g2's 8 member reads
// and writes are register accesses, g2 is a function pipeline at II 1 with 8 tbl
// reads per cycle, ROM_NP 4 (Vitis 4). As a 2-port memory (off) g2's II is 8: 1.
// CHECK: ROM_NP (8 read port(s)/cycle) = 4 BRAM_18K
// CHECK: Total BRAM: 4
// OFF: Total BRAM: 1

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topP5cfg_tPKiPi(%arg0: memref<?x8xi32>, %arg1: memref<8xi32>, %arg2: memref<8xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %0 = affine.load %arg1[0] : memref<8xi32>
    affine.store %0, %arg0[0, 0] : memref<?x8xi32>
    affine.for %arg3 = 0 to 7 {
      func.call @_ZL2g2P5cfg_t(%arg0) : (memref<?x8xi32>) -> ()
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    %1 = affine.load %arg0[0, 0] : memref<?x8xi32>
    affine.store %1, %arg2[0] : memref<8xi32>
    return
  }
  func.func private @_ZL2g2P5cfg_t(%arg0: memref<?x8xi32>) attributes {hls.inline_off, hls.orig_name = "g2", llvm.linkage = #llvm.linkage<internal>} {
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = affine.load %arg0[0, 0] : memref<?x8xi32>
    %2 = arith.trunci %1 : i32 to i8
    %3 = arith.index_castui %2 : i8 to index
    %4 = affine.load %0[symbol(%3)] : memref<256xi8>
    %5 = affine.load %arg0[0, 1] : memref<?x8xi32>
    %6 = arith.trunci %5 : i32 to i8
    %7 = arith.index_castui %6 : i8 to index
    %8 = affine.load %0[symbol(%7)] : memref<256xi8>
    %9 = affine.load %arg0[0, 2] : memref<?x8xi32>
    %10 = arith.trunci %9 : i32 to i8
    %11 = arith.index_castui %10 : i8 to index
    %12 = affine.load %0[symbol(%11)] : memref<256xi8>
    %13 = affine.load %arg0[0, 3] : memref<?x8xi32>
    %14 = arith.trunci %13 : i32 to i8
    %15 = arith.index_castui %14 : i8 to index
    %16 = affine.load %0[symbol(%15)] : memref<256xi8>
    %17 = affine.load %arg0[0, 4] : memref<?x8xi32>
    %18 = arith.trunci %17 : i32 to i8
    %19 = arith.index_castui %18 : i8 to index
    %20 = affine.load %0[symbol(%19)] : memref<256xi8>
    %21 = affine.load %arg0[0, 5] : memref<?x8xi32>
    %22 = arith.trunci %21 : i32 to i8
    %23 = arith.index_castui %22 : i8 to index
    %24 = affine.load %0[symbol(%23)] : memref<256xi8>
    %25 = affine.load %arg0[0, 6] : memref<?x8xi32>
    %26 = arith.trunci %25 : i32 to i8
    %27 = arith.index_castui %26 : i8 to index
    %28 = affine.load %0[symbol(%27)] : memref<256xi8>
    %29 = affine.load %arg0[0, 7] : memref<?x8xi32>
    %30 = arith.trunci %29 : i32 to i8
    %31 = arith.index_castui %30 : i8 to index
    %32 = affine.load %0[symbol(%31)] : memref<256xi8>
    %33 = arith.extui %8 : i8 to i32
    affine.store %33, %arg0[0, 0] : memref<?x8xi32>
    %34 = arith.extui %12 : i8 to i32
    affine.store %34, %arg0[0, 1] : memref<?x8xi32>
    %35 = arith.extui %16 : i8 to i32
    affine.store %35, %arg0[0, 2] : memref<?x8xi32>
    %36 = arith.extui %20 : i8 to i32
    affine.store %36, %arg0[0, 3] : memref<?x8xi32>
    %37 = arith.extui %24 : i8 to i32
    affine.store %37, %arg0[0, 4] : memref<?x8xi32>
    %38 = arith.extui %28 : i8 to i32
    affine.store %38, %arg0[0, 5] : memref<?x8xi32>
    %39 = arith.extui %32 : i8 to i32
    affine.store %39, %arg0[0, 6] : memref<?x8xi32>
    %40 = arith.extui %4 : i8 to i32
    affine.store %40, %arg0[0, 7] : memref<?x8xi32>
    return
  }
}
