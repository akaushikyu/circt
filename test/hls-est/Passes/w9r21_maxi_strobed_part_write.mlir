// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi128EEPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topP7ap_uintILi128EEPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi128EEPs --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topP7ap_uintILi128EEPs math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.implicit_buffers[0].read_fifo.strobed_part_writes=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9r21 (2026-10-24): VITIS_NOTES N152: a part-select store to an m_axi word is
// a strobed write. Kernel w9r21p_c2_half (ap_uint<128> out[64] on bundle mem2,
// `out[i].range(16k+15, 16k) = in[8i+k]` for k < 4: bytes 0..7 written, 8..15
// kept): Vitis mem2_m_axi 0 BRAM (WRITE_ONLY), mem1 2. MLIR from the installed
// cgeist 5523df29 with the real headers.
// CHECK: m_axi.adapter bundle=mem2{{.*}} bram=0 (read FIFO
// CHECK: m_axi.adapter bundle=mem1{{.*}} bram=2
// CHECK: Total BRAM: 2
// OFF: m_axi.adapter bundle=mem2{{.*}} bram=8 (read FIFO
// OFF: Total BRAM: 10
module {
  func.func @_Z3topP7ap_uintILi128EEPs(%arg0: memref<64xi128> {hls.interface = [{bundle = "mem2", mode = "m_axi", offset = "slave", port = "out"}]}, %arg1: memref<512xi16> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "in"}]}) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
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
    affine.for %arg2 = 0 to 64 {
      affine.for %arg3 = 0 to 4 {
        %0 = arith.index_cast %arg3 : index to i32
        %1 = arith.muli %0, %c16_i32 : i32
        %2 = arith.addi %1, %c15_i32 : i32
        %3 = affine.load %arg1[%arg3 + %arg2 * 8] : memref<512xi16>
        %4 = arith.extsi %3 : i16 to i128
        %5 = affine.load %arg0[%arg2] : memref<64xi128>
        %6 = arith.cmpi ugt, %1, %2 : i32
        %7 = arith.select %6, %2, %1 : i32
        %8 = arith.select %6, %1, %2 : i32
        %9 = arith.subi %8, %7 : i32
        %10 = arith.addi %9, %c1_i32 : i32
        %11 = arith.extui %7 : i32 to i128
        %12 = arith.extui %10 : i32 to i128
        %13 = arith.subi %c128_i128, %12 : i128
        %14 = arith.shrui %c-1_i128, %13 : i128
        %15 = arith.andi %4, %14 : i128
        %16 = arith.shrui %15, %c1_i128 : i128
        %17 = arith.andi %16, %c113427455640312821154458202477256070485_i128 : i128
        %18 = arith.andi %15, %c113427455640312821154458202477256070485_i128 : i128
        %19 = arith.shli %18, %c1_i128 : i128
        %20 = arith.ori %17, %19 : i128
        %21 = arith.shrui %20, %c2_i128 : i128
        %22 = arith.andi %21, %c68056473384187692692674921486353642291_i128 : i128
        %23 = arith.andi %20, %c68056473384187692692674921486353642291_i128 : i128
        %24 = arith.shli %23, %c2_i128 : i128
        %25 = arith.ori %22, %24 : i128
        %26 = arith.shrui %25, %c4_i128 : i128
        %27 = arith.andi %26, %c20016609818878733144904388672456953615_i128 : i128
        %28 = arith.andi %25, %c20016609818878733144904388672456953615_i128 : i128
        %29 = arith.shli %28, %c4_i128 : i128
        %30 = arith.ori %27, %29 : i128
        %31 = arith.shrui %30, %c8_i128 : i128
        %32 = arith.andi %31, %c1324055902416102970674609367438786815_i128 : i128
        %33 = arith.andi %30, %c1324055902416102970674609367438786815_i128 : i128
        %34 = arith.shli %33, %c8_i128 : i128
        %35 = arith.ori %32, %34 : i128
        %36 = arith.shrui %35, %c16_i128 : i128
        %37 = arith.andi %36, %c5192217631581220737344928932233215_i128 : i128
        %38 = arith.andi %35, %c5192217631581220737344928932233215_i128 : i128
        %39 = arith.shli %38, %c16_i128 : i128
        %40 = arith.ori %37, %39 : i128
        %41 = arith.shrui %40, %c32_i128 : i128
        %42 = arith.andi %41, %c79228162495817593524129366015_i128 : i128
        %43 = arith.andi %40, %c79228162495817593524129366015_i128 : i128
        %44 = arith.shli %43, %c32_i128 : i128
        %45 = arith.ori %42, %44 : i128
        %46 = arith.shrui %45, %c64_i128 : i128
        %47 = arith.andi %46, %c18446744073709551615_i128 : i128
        %48 = arith.andi %45, %c18446744073709551615_i128 : i128
        %49 = arith.shli %48, %c64_i128 : i128
        %50 = arith.ori %47, %49 : i128
        %51 = arith.shrui %50, %13 : i128
        %52 = arith.select %6, %51, %15 : i128
        %53 = arith.shli %14, %11 : i128
        %54 = arith.xori %53, %c-1_i128 : i128
        %55 = arith.andi %5, %54 : i128
        %56 = arith.shli %52, %11 : i128
        %57 = arith.ori %55, %56 : i128
        affine.store %57, %arg0[%arg2] : memref<64xi128>
      }
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
