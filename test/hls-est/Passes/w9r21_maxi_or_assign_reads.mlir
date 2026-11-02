// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi128EEPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topP7ap_uintILi128EEPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// W9r21 (2026-10-24): VITIS_NOTES N152 counter-case. Kernel w9r21p_c4_or
// (`out[i] |= x`: every bit of the old word is used) reads the word: Vitis
// mem2_m_axi 8 (read FIFO 256 x 128). MLIR from the installed cgeist 5523df29.
// CHECK: m_axi.adapter bundle=mem2{{.*}} bram=8 (read FIFO
// CHECK: Total BRAM: 10
module {
  func.func @_Z3topP7ap_uintILi128EEPs(%arg0: memref<64xi128> {hls.interface = [{bundle = "mem2", mode = "m_axi", offset = "slave", port = "out"}]}, %arg1: memref<512xi16> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "in"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c0_i128 = arith.constant 0 : i128
    %c1_i32 = arith.constant 1 : i32
    %c128_i128 = arith.constant 128 : i128
    %c-1_i128 = arith.constant -1 : i128
    %c113427455640312821154458202477256070485_i128 = arith.constant 113427455640312821154458202477256070485 : i128
    %c1_i128 = arith.constant 1 : i128
    %c68056473384187692692674921486353642291_i128 = arith.constant 68056473384187692692674921486353642291 : i128
    %c2_i128 = arith.constant 2 : i128
    %c20016609818878733144904388672456953615_i128 = arith.constant 20016609818878733144904388672456953615 : i128
    %c4_i128 = arith.constant 4 : i128
    %c1324055902416102970674609367438786815_i128 = arith.constant 1324055902416102970674609367438786815 : i128
    %c8_i128 = arith.constant 8 : i128
    %c5192217631581220737344928932233215_i128 = arith.constant 5192217631581220737344928932233215 : i128
    %c16_i128 = arith.constant 16 : i128
    %c79228162495817593524129366015_i128 = arith.constant 79228162495817593524129366015 : i128
    %c32_i128 = arith.constant 32 : i128
    %c18446744073709551615_i128 = arith.constant 18446744073709551615 : i128
    %c64_i128 = arith.constant 64 : i128
    %c15_i32 = arith.constant 15 : i32
    %c16_i32 = arith.constant 16 : i32
    %0 = llvm.mlir.undef : i128
    %1 = affine.for %arg2 = 0 to 64 iter_args(%arg3 = %0) -> (i128) {
      %2 = affine.for %arg4 = 0 to 8 iter_args(%arg5 = %c0_i128) -> (i128) {
        %5 = arith.index_cast %arg4 : index to i32
        %6 = arith.muli %5, %c16_i32 : i32
        %7 = arith.addi %6, %c15_i32 : i32
        %8 = affine.load %arg1[%arg4 + %arg2 * 8] : memref<512xi16>
        %9 = arith.extsi %8 : i16 to i128
        %10 = arith.cmpi ugt, %6, %7 : i32
        %11 = arith.select %10, %7, %6 : i32
        %12 = arith.select %10, %6, %7 : i32
        %13 = arith.subi %12, %11 : i32
        %14 = arith.addi %13, %c1_i32 : i32
        %15 = arith.extui %11 : i32 to i128
        %16 = arith.extui %14 : i32 to i128
        %17 = arith.subi %c128_i128, %16 : i128
        %18 = arith.shrui %c-1_i128, %17 : i128
        %19 = arith.andi %9, %18 : i128
        %20 = arith.shrui %19, %c1_i128 : i128
        %21 = arith.andi %20, %c113427455640312821154458202477256070485_i128 : i128
        %22 = arith.andi %19, %c113427455640312821154458202477256070485_i128 : i128
        %23 = arith.shli %22, %c1_i128 : i128
        %24 = arith.ori %21, %23 : i128
        %25 = arith.shrui %24, %c2_i128 : i128
        %26 = arith.andi %25, %c68056473384187692692674921486353642291_i128 : i128
        %27 = arith.andi %24, %c68056473384187692692674921486353642291_i128 : i128
        %28 = arith.shli %27, %c2_i128 : i128
        %29 = arith.ori %26, %28 : i128
        %30 = arith.shrui %29, %c4_i128 : i128
        %31 = arith.andi %30, %c20016609818878733144904388672456953615_i128 : i128
        %32 = arith.andi %29, %c20016609818878733144904388672456953615_i128 : i128
        %33 = arith.shli %32, %c4_i128 : i128
        %34 = arith.ori %31, %33 : i128
        %35 = arith.shrui %34, %c8_i128 : i128
        %36 = arith.andi %35, %c1324055902416102970674609367438786815_i128 : i128
        %37 = arith.andi %34, %c1324055902416102970674609367438786815_i128 : i128
        %38 = arith.shli %37, %c8_i128 : i128
        %39 = arith.ori %36, %38 : i128
        %40 = arith.shrui %39, %c16_i128 : i128
        %41 = arith.andi %40, %c5192217631581220737344928932233215_i128 : i128
        %42 = arith.andi %39, %c5192217631581220737344928932233215_i128 : i128
        %43 = arith.shli %42, %c16_i128 : i128
        %44 = arith.ori %41, %43 : i128
        %45 = arith.shrui %44, %c32_i128 : i128
        %46 = arith.andi %45, %c79228162495817593524129366015_i128 : i128
        %47 = arith.andi %44, %c79228162495817593524129366015_i128 : i128
        %48 = arith.shli %47, %c32_i128 : i128
        %49 = arith.ori %46, %48 : i128
        %50 = arith.shrui %49, %c64_i128 : i128
        %51 = arith.andi %50, %c18446744073709551615_i128 : i128
        %52 = arith.andi %49, %c18446744073709551615_i128 : i128
        %53 = arith.shli %52, %c64_i128 : i128
        %54 = arith.ori %51, %53 : i128
        %55 = arith.shrui %54, %17 : i128
        %56 = arith.select %10, %55, %19 : i128
        %57 = arith.shli %18, %15 : i128
        %58 = arith.xori %57, %c-1_i128 : i128
        %59 = arith.andi %arg5, %58 : i128
        %60 = arith.shli %56, %15 : i128
        %61 = arith.ori %59, %60 : i128
        affine.yield %61 : i128
      }
      %3 = affine.load %arg0[%arg2] : memref<64xi128>
      %4 = arith.ori %3, %2 : i128
      affine.store %4, %arg0[%arg2] : memref<64xi128>
      affine.yield %2 : i128
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
