// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPiS_S_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.partitioning.complete_partition_registers=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N111, kernel w9r15i_rg_mac (Vitis 2025.1 td=off: 24, the w9r15p_rg_net
// network with the compare-and-swap as a macro): a 19-step compare-and-swap network
// on int v[8] (array_partition complete) in a pipeline II=1 loop; L (4096 x 32) is
// read 4x per iteration. The one-element banks of v are registers (no port pool):
// II 1, L RAM_1WNR 3 copies (24).
// Off run: tool.hls.partitioning.complete_partition_registers off (two ports per
// element: II 32, L 8).
// CHECK: Total BRAM: 24
// OFF: Total BRAM: 8

module {
  func.func @_Z3topPiS_S_(%arg0: memref<4096xi32>, %arg1: memref<512xi32>, %arg2: memref<512xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c4095_i32 = arith.constant 4095 : i32
    %c1024_i32 = arith.constant 1024 : i32
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "v"}], hls.preserve, polygeist.varname = "v"} : memref<8xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "L"} : memref<4096xi32>
    affine.for %arg3 = 0 to 4096 {
      %0 = affine.load %arg0[%arg3] : memref<4096xi32>
      affine.store %0, %alloca_0[%arg3] : memref<4096xi32>
    }
    affine.for %arg3 = 0 to 512 {
      %0 = affine.load %arg1[%arg3] : memref<512xi32>
      affine.for %arg4 = 0 to 4 {
        %62 = arith.index_cast %arg4 : index to i32
        %63 = arith.muli %62, %c1024_i32 : i32
        %64 = arith.addi %0, %63 : i32
        %65 = arith.andi %64, %c4095_i32 : i32
        %66 = arith.index_cast %65 : i32 to index
        %67 = memref.load %alloca_0[%66] : memref<4096xi32>
        affine.store %67, %alloca[%arg4] : memref<8xi32>
      }
      %1 = affine.load %arg1[%arg3] : memref<512xi32>
      affine.for %arg4 = 4 to 8 {
        %62 = arith.index_cast %arg4 : index to i32
        %63 = arith.addi %1, %62 : i32
        affine.store %63, %alloca[%arg4] : memref<8xi32>
      }
      %2 = affine.load %alloca[0] : memref<8xi32>
      %3 = affine.load %alloca[1] : memref<8xi32>
      %4 = arith.cmpi slt, %2, %3 : i32
      %5 = arith.select %4, %3, %2 : i32
      %6 = arith.select %4, %2, %3 : i32
      scf.if %4 {
        affine.store %3, %alloca[0] : memref<8xi32>
        affine.store %2, %alloca[1] : memref<8xi32>
      }
      %7 = affine.load %alloca[2] : memref<8xi32>
      %8 = affine.load %alloca[3] : memref<8xi32>
      %9 = arith.cmpi slt, %7, %8 : i32
      %10 = arith.select %9, %8, %7 : i32
      %11 = arith.select %9, %7, %8 : i32
      scf.if %9 {
        affine.store %8, %alloca[2] : memref<8xi32>
        affine.store %7, %alloca[3] : memref<8xi32>
      }
      %12 = affine.load %alloca[4] : memref<8xi32>
      %13 = affine.load %alloca[5] : memref<8xi32>
      %14 = arith.cmpi slt, %12, %13 : i32
      %15 = arith.select %14, %13, %12 : i32
      %16 = arith.select %14, %12, %13 : i32
      scf.if %14 {
        affine.store %13, %alloca[4] : memref<8xi32>
        affine.store %12, %alloca[5] : memref<8xi32>
      }
      %17 = affine.load %alloca[6] : memref<8xi32>
      %18 = affine.load %alloca[7] : memref<8xi32>
      %19 = arith.cmpi slt, %17, %18 : i32
      %20 = arith.select %19, %18, %17 : i32
      %21 = arith.select %19, %17, %18 : i32
      scf.if %19 {
        affine.store %18, %alloca[6] : memref<8xi32>
        affine.store %17, %alloca[7] : memref<8xi32>
      }
      %22 = arith.cmpi slt, %5, %10 : i32
      %23 = arith.select %22, %10, %5 : i32
      %24 = arith.select %22, %5, %10 : i32
      scf.if %22 {
        affine.store %10, %alloca[0] : memref<8xi32>
        affine.store %5, %alloca[2] : memref<8xi32>
      }
      %25 = arith.cmpi slt, %6, %11 : i32
      %26 = arith.select %25, %11, %6 : i32
      %27 = arith.select %25, %6, %11 : i32
      scf.if %25 {
        affine.store %11, %alloca[1] : memref<8xi32>
        affine.store %6, %alloca[3] : memref<8xi32>
      }
      %28 = arith.cmpi slt, %15, %20 : i32
      %29 = arith.select %28, %20, %15 : i32
      %30 = arith.select %28, %15, %20 : i32
      scf.if %28 {
        affine.store %20, %alloca[4] : memref<8xi32>
        affine.store %15, %alloca[6] : memref<8xi32>
      }
      %31 = arith.cmpi slt, %16, %21 : i32
      %32 = arith.select %31, %21, %16 : i32
      %33 = arith.select %31, %16, %21 : i32
      scf.if %31 {
        affine.store %21, %alloca[5] : memref<8xi32>
        affine.store %16, %alloca[7] : memref<8xi32>
      }
      %34 = arith.cmpi slt, %26, %24 : i32
      %35 = arith.select %34, %24, %26 : i32
      %36 = arith.select %34, %26, %24 : i32
      scf.if %34 {
        affine.store %24, %alloca[1] : memref<8xi32>
        affine.store %26, %alloca[2] : memref<8xi32>
      }
      %37 = arith.cmpi slt, %32, %30 : i32
      %38 = arith.select %37, %30, %32 : i32
      %39 = arith.select %37, %32, %30 : i32
      scf.if %37 {
        affine.store %30, %alloca[5] : memref<8xi32>
        affine.store %32, %alloca[6] : memref<8xi32>
      }
      %40 = arith.cmpi slt, %23, %29 : i32
      %41 = arith.select %40, %23, %29 : i32
      scf.if %40 {
        affine.store %29, %alloca[0] : memref<8xi32>
        affine.store %23, %alloca[4] : memref<8xi32>
      }
      %42 = arith.cmpi slt, %27, %33 : i32
      %43 = arith.select %42, %33, %27 : i32
      scf.if %42 {
        affine.store %33, %alloca[3] : memref<8xi32>
        affine.store %27, %alloca[7] : memref<8xi32>
      }
      %44 = arith.cmpi slt, %35, %38 : i32
      %45 = arith.select %44, %38, %35 : i32
      %46 = arith.select %44, %35, %38 : i32
      scf.if %44 {
        affine.store %38, %alloca[1] : memref<8xi32>
        affine.store %35, %alloca[5] : memref<8xi32>
      }
      %47 = arith.cmpi slt, %36, %39 : i32
      %48 = arith.select %47, %39, %36 : i32
      %49 = arith.select %47, %36, %39 : i32
      scf.if %47 {
        affine.store %39, %alloca[2] : memref<8xi32>
        affine.store %36, %alloca[6] : memref<8xi32>
      }
      %50 = arith.cmpi slt, %45, %41 : i32
      %51 = arith.select %50, %45, %41 : i32
      scf.if %50 {
        affine.store %41, %alloca[1] : memref<8xi32>
        affine.store %45, %alloca[4] : memref<8xi32>
      }
      %52 = arith.cmpi slt, %43, %49 : i32
      %53 = arith.select %52, %49, %43 : i32
      scf.if %52 {
        affine.store %49, %alloca[3] : memref<8xi32>
        affine.store %43, %alloca[6] : memref<8xi32>
      }
      %54 = arith.cmpi slt, %48, %51 : i32
      %55 = arith.select %54, %48, %51 : i32
      scf.if %54 {
        affine.store %51, %alloca[2] : memref<8xi32>
        affine.store %48, %alloca[4] : memref<8xi32>
      }
      %56 = arith.cmpi slt, %53, %46 : i32
      %57 = arith.select %56, %46, %53 : i32
      scf.if %56 {
        affine.store %46, %alloca[3] : memref<8xi32>
        affine.store %53, %alloca[5] : memref<8xi32>
      }
      %58 = arith.cmpi slt, %57, %55 : i32
      %59 = arith.select %58, %55, %57 : i32
      %60 = arith.select %58, %57, %55 : i32
      scf.if %58 {
        affine.store %55, %alloca[3] : memref<8xi32>
        affine.store %57, %alloca[4] : memref<8xi32>
      }
      %61 = arith.xori %59, %60 : i32
      affine.store %61, %arg2[%arg3] : memref<512xi32>
    } {hls.pipeline = [{II = 1 : i32, rewind = false, style = "stp"}]}
    return
  }
}
