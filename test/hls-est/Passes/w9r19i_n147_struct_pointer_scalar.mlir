// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP5ctx_tPhS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topP5ctx_tPhS1_ -o /dev/null | FileCheck %s
// RUN: hls-est %s --config-set tool.hls.structs.top_pointer_scalar=false --symbol-privatize=exclude=_Z3topP5ctx_tPhS1_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topP5ctx_tPhS1_ -o /dev/null | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N144 + N147, kernel w9r19p_ri_s (hlsyn aes' aes_expandEncKey_1
// shape, cgeist output): `g2(ctx->key, &rcon)` reads `tbl` 8 times and is
// called in a pipelined loop. The top's `ctx_t *ctx` is one wide scalar in
// Vitis (no memory port), so g2 is a function pipeline at II 1: 8 reads per
// cycle, ROM_NP 4 BRAM (Vitis 4). Behind two ports the context's accesses
// would raise g2's II and halve the reads per cycle (2 BRAM).
// CHECK: ROM_NP (8 read port(s)/cycle) = 4 BRAM_18K
// CHECK: Total BRAM: 4
// OFF: Total BRAM: 2

module {
  memref.global "private" @_ZL3tbl : memref<256xi8> = dense<"0x0DB45B02A950F79E45EC933AE1882FD67D24CB7219C0670EB55C03AA51F89F46ED943BE28930D77E25CC731AC1680FB65D04AB52F9A047EE953CE38A31D87F26CD741BC26910B75E05AC53FAA148EF963DE48B32D98027CE751CC36A11B85F06AD54FBA249F0973EE58C33DA8128CF761DC46B12B96007AE55FCA34AF1983FE68D34DB8229D0771EC56C13BA6108AF56FDA44BF29940E78E35DC832AD1781FC66D14BB6209B057FEA54CF39A41E88F36DD842BD27920C76E15BC630AB158FFA64DF49B42E99037DE852CD37A21C86F16BD640BB25900A74EF59C43EA9138DF862DD47B22C97017BE650CB35A01A84FF69D44EB9239E0872ED57C23CA7118BF66">
  func.func @_Z3topP5ctx_tPhS1_(%arg0: memref<?x!llvm.struct<(array<32 x i8>)>>, %arg1: memref<32xi8>, %arg2: memref<32xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i8 = arith.constant 1 : i8
    %alloca = memref.alloca() {polygeist.varname = "rcon"} : memref<1xi8>
    affine.store %c1_i8, %alloca[0] : memref<1xi8>
    %0 = "polygeist.memref2pointer"(%arg0) : (memref<?x!llvm.struct<(array<32 x i8>)>>) -> !llvm.ptr
    affine.for %arg3 = 0 to 32 {
      %2 = arith.index_cast %arg3 : index to i32
      %3 = affine.load %arg1[%arg3] : memref<32xi8>
      %4 = llvm.getelementptr %0[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i8
      llvm.store %3, %4 : i8, !llvm.ptr
    }
    %1 = "polygeist.pointer2memref"(%0) : (!llvm.ptr) -> memref<?xi8>
    %cast = memref.cast %alloca : memref<1xi8> to memref<?xi8>
    affine.for %arg3 = 0 to 7 {
      func.call @_ZL2g2PhS_(%1, %cast) {hls.inline_auto_off = {calls = 2 : i64, size = 184 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    call @_ZL2g2PhS_(%1, %cast) {hls.inline_auto_off = {calls = 2 : i64, size = 184 : i64}} : (memref<?xi8>, memref<?xi8>) -> ()
    affine.for %arg3 = 0 to 32 {
      %2 = arith.index_cast %arg3 : index to i32
      %3 = llvm.getelementptr %0[%2] : (!llvm.ptr, i32) -> !llvm.ptr, i8
      %4 = llvm.load %3 : !llvm.ptr -> i8
      affine.store %4, %arg2[%arg3] : memref<32xi8>
    }
    return
  }
  func.func private @_ZL2g2PhS_(%arg0: memref<?xi8>, %arg1: memref<?xi8>) attributes {hls.inline_auto_off = {size = 184 : i64}, hls.orig_name = "g2", llvm.linkage = #llvm.linkage<internal>} {
    %c27_i32 = arith.constant 27 : i32
    %c7_i32 = arith.constant 7 : i32
    %c1_i32 = arith.constant 1 : i32
    %0 = memref.get_global @_ZL3tbl : memref<256xi8>
    %1 = affine.load %arg0[29] : memref<?xi8>
    %2 = arith.index_castui %1 : i8 to index
    %3 = affine.load %0[symbol(%2)] : memref<256xi8>
    %4 = affine.load %arg1[0] : memref<?xi8>
    %5 = arith.xori %3, %4 : i8
    %6 = affine.load %arg0[0] : memref<?xi8>
    %7 = arith.xori %6, %5 : i8
    affine.store %7, %arg0[0] : memref<?xi8>
    %8 = affine.load %arg0[30] : memref<?xi8>
    %9 = arith.index_castui %8 : i8 to index
    %10 = affine.load %0[symbol(%9)] : memref<256xi8>
    %11 = affine.load %arg0[1] : memref<?xi8>
    %12 = arith.xori %11, %10 : i8
    affine.store %12, %arg0[1] : memref<?xi8>
    %13 = affine.load %arg0[31] : memref<?xi8>
    %14 = arith.index_castui %13 : i8 to index
    %15 = affine.load %0[symbol(%14)] : memref<256xi8>
    %16 = affine.load %arg0[2] : memref<?xi8>
    %17 = arith.xori %16, %15 : i8
    affine.store %17, %arg0[2] : memref<?xi8>
    %18 = affine.load %arg0[28] : memref<?xi8>
    %19 = arith.index_castui %18 : i8 to index
    %20 = affine.load %0[symbol(%19)] : memref<256xi8>
    %21 = affine.load %arg0[3] : memref<?xi8>
    %22 = arith.xori %21, %20 : i8
    affine.store %22, %arg0[3] : memref<?xi8>
    %23 = affine.load %arg1[0] : memref<?xi8>
    %24 = arith.extui %23 : i8 to i32
    %25 = arith.shli %24, %c1_i32 : i32
    %26 = arith.shrsi %24, %c7_i32 : i32
    %27 = arith.andi %26, %c1_i32 : i32
    %28 = arith.muli %27, %c27_i32 : i32
    %29 = arith.xori %25, %28 : i32
    %30 = arith.trunci %29 : i32 to i8
    affine.store %30, %arg1[0] : memref<?xi8>
    affine.for %arg2 = 4 to 16 step 4 {
      %51 = affine.load %arg0[%arg2 - 4] : memref<?xi8>
      %52 = affine.load %arg0[%arg2] : memref<?xi8>
      %53 = arith.xori %52, %51 : i8
      affine.store %53, %arg0[%arg2] : memref<?xi8>
      %54 = affine.load %arg0[%arg2 - 3] : memref<?xi8>
      %55 = affine.load %arg0[%arg2 + 1] : memref<?xi8>
      %56 = arith.xori %55, %54 : i8
      affine.store %56, %arg0[%arg2 + 1] : memref<?xi8>
      %57 = affine.load %arg0[%arg2 - 2] : memref<?xi8>
      %58 = affine.load %arg0[%arg2 + 2] : memref<?xi8>
      %59 = arith.xori %58, %57 : i8
      affine.store %59, %arg0[%arg2 + 2] : memref<?xi8>
      %60 = affine.load %arg0[%arg2 - 1] : memref<?xi8>
      %61 = affine.load %arg0[%arg2 + 3] : memref<?xi8>
      %62 = arith.xori %61, %60 : i8
      affine.store %62, %arg0[%arg2 + 3] : memref<?xi8>
    }
    %31 = affine.load %arg0[12] : memref<?xi8>
    %32 = arith.index_castui %31 : i8 to index
    %33 = affine.load %0[symbol(%32)] : memref<256xi8>
    %34 = affine.load %arg0[16] : memref<?xi8>
    %35 = arith.xori %34, %33 : i8
    affine.store %35, %arg0[16] : memref<?xi8>
    %36 = affine.load %arg0[13] : memref<?xi8>
    %37 = arith.index_castui %36 : i8 to index
    %38 = affine.load %0[symbol(%37)] : memref<256xi8>
    %39 = affine.load %arg0[17] : memref<?xi8>
    %40 = arith.xori %39, %38 : i8
    affine.store %40, %arg0[17] : memref<?xi8>
    %41 = affine.load %arg0[14] : memref<?xi8>
    %42 = arith.index_castui %41 : i8 to index
    %43 = affine.load %0[symbol(%42)] : memref<256xi8>
    %44 = affine.load %arg0[18] : memref<?xi8>
    %45 = arith.xori %44, %43 : i8
    affine.store %45, %arg0[18] : memref<?xi8>
    %46 = affine.load %arg0[15] : memref<?xi8>
    %47 = arith.index_castui %46 : i8 to index
    %48 = affine.load %0[symbol(%47)] : memref<256xi8>
    %49 = affine.load %arg0[19] : memref<?xi8>
    %50 = arith.xori %49, %48 : i8
    affine.store %50, %arg0[19] : memref<?xi8>
    affine.for %arg2 = 20 to 32 step 4 {
      %51 = affine.load %arg0[%arg2 - 4] : memref<?xi8>
      %52 = affine.load %arg0[%arg2] : memref<?xi8>
      %53 = arith.xori %52, %51 : i8
      affine.store %53, %arg0[%arg2] : memref<?xi8>
      %54 = affine.load %arg0[%arg2 - 3] : memref<?xi8>
      %55 = affine.load %arg0[%arg2 + 1] : memref<?xi8>
      %56 = arith.xori %55, %54 : i8
      affine.store %56, %arg0[%arg2 + 1] : memref<?xi8>
      %57 = affine.load %arg0[%arg2 - 2] : memref<?xi8>
      %58 = affine.load %arg0[%arg2 + 2] : memref<?xi8>
      %59 = arith.xori %58, %57 : i8
      affine.store %59, %arg0[%arg2 + 2] : memref<?xi8>
      %60 = affine.load %arg0[%arg2 - 1] : memref<?xi8>
      %61 = affine.load %arg0[%arg2 + 3] : memref<?xi8>
      %62 = arith.xori %61, %60 : i8
      affine.store %62, %arg0[%arg2 + 3] : memref<?xi8>
    }
    return
  }
}
