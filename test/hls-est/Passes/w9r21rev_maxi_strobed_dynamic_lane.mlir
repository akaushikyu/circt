// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi64EEPsPh --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topP7ap_uintILi64EEPsPh math-costs=%S/../../../tools/hls-est-validate/math_costs.json' -o /dev/null | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP7ap_uintILi64EEPsPh --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule '--bram-analysis=top=_Z3topP7ap_uintILi64EEPsPh math-costs=%S/../../../tools/hls-est-validate/math_costs.json' --config-set 'tool.hls.implicit_buffers[0].read_fifo.strobed_part_writes=false' -o /dev/null | FileCheck %s --check-prefix=OFF
// W9 round 21 review (2026-10-25): VITIS_NOTES N152 (b). A part-select at a
// run-time byte lane, `out[i].range(8 * s + 7, 8 * s) = x` on an m_axi
// ap_uint<64> (kernel w9r21rev_r3b_dynbyte): the cleared field ~(0xFF << k)
// and the inserted value (x & 0xFF) << k share the shift k, a multiple of 8,
// so every byte is kept whole or overwritten: Vitis writes with byte strobes
// and mem2_m_axi has no read FIFO (0 BRAM). The bounds 8s and 8s + 7 share
// the base 8s, so cgeist's width / reversal arithmetic folds. Off
// (tool.hls.implicit_buffers[0].read_fifo.strobed_part_writes=false): a read
// FIFO, 4.
// CHECK: m_axi.adapter bundle=mem2{{.*}} bram=0 (read FIFO 256x64b -> 0
// CHECK: m_axi.adapter bundle=mem1{{.*}} bram=2
// CHECK: Total BRAM: 2
// OFF: m_axi.adapter bundle=mem2{{.*}} bram=4
// OFF: Total BRAM: 6
// MLIR from the private cgeist of the W9 round 21 review fixes (real headers).
module {
  func.func @_Z3topP7ap_uintILi64EEPsPh(%arg0: memref<64xi64> {hls.interface = [{bundle = "mem2", mode = "m_axi", offset = "slave", port = "out"}]}, %arg1: memref<512xi16> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "in"}]}, %arg2: memref<64xi8>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c1_i32 = arith.constant 1 : i32
    %c64_i64 = arith.constant 64 : i64
    %c-1_i64 = arith.constant -1 : i64
    %c6148914691236517205_i64 = arith.constant 6148914691236517205 : i64
    %c1_i64 = arith.constant 1 : i64
    %c3689348814741910323_i64 = arith.constant 3689348814741910323 : i64
    %c2_i64 = arith.constant 2 : i64
    %c1085102592571150095_i64 = arith.constant 1085102592571150095 : i64
    %c4_i64 = arith.constant 4 : i64
    %c71777214294589695_i64 = arith.constant 71777214294589695 : i64
    %c8_i64 = arith.constant 8 : i64
    %c281470681808895_i64 = arith.constant 281470681808895 : i64
    %c16_i64 = arith.constant 16 : i64
    %c4294967295_i64 = arith.constant 4294967295 : i64
    %c32_i64 = arith.constant 32 : i64
    %c8_i32 = arith.constant 8 : i32
    %c7_i32 = arith.constant 7 : i32
    affine.for %arg3 = 0 to 64 {
      %0 = affine.load %arg2[%arg3] : memref<64xi8>
      %1 = arith.extui %0 : i8 to i32
      %2 = arith.andi %1, %c7_i32 : i32
      %3 = arith.muli %2, %c8_i32 : i32
      %4 = arith.addi %3, %c7_i32 : i32
      %5 = affine.load %arg1[%arg3 * 8] : memref<512xi16>
      %6 = arith.extsi %5 : i16 to i64
      %7 = affine.load %arg0[%arg3] : memref<64xi64>
      %8 = arith.cmpi ugt, %3, %4 : i32
      %9 = arith.select %8, %4, %3 : i32
      %10 = arith.select %8, %3, %4 : i32
      %11 = arith.subi %10, %9 : i32
      %12 = arith.addi %11, %c1_i32 : i32
      %13 = arith.extui %9 : i32 to i64
      %14 = arith.extui %12 : i32 to i64
      %15 = arith.subi %c64_i64, %14 : i64
      %16 = arith.shrui %c-1_i64, %15 : i64
      %17 = arith.andi %6, %16 : i64
      %18 = arith.shrui %17, %c1_i64 : i64
      %19 = arith.andi %18, %c6148914691236517205_i64 : i64
      %20 = arith.andi %17, %c6148914691236517205_i64 : i64
      %21 = arith.shli %20, %c1_i64 : i64
      %22 = arith.ori %19, %21 : i64
      %23 = arith.shrui %22, %c2_i64 : i64
      %24 = arith.andi %23, %c3689348814741910323_i64 : i64
      %25 = arith.andi %22, %c3689348814741910323_i64 : i64
      %26 = arith.shli %25, %c2_i64 : i64
      %27 = arith.ori %24, %26 : i64
      %28 = arith.shrui %27, %c4_i64 : i64
      %29 = arith.andi %28, %c1085102592571150095_i64 : i64
      %30 = arith.andi %27, %c1085102592571150095_i64 : i64
      %31 = arith.shli %30, %c4_i64 : i64
      %32 = arith.ori %29, %31 : i64
      %33 = arith.shrui %32, %c8_i64 : i64
      %34 = arith.andi %33, %c71777214294589695_i64 : i64
      %35 = arith.andi %32, %c71777214294589695_i64 : i64
      %36 = arith.shli %35, %c8_i64 : i64
      %37 = arith.ori %34, %36 : i64
      %38 = arith.shrui %37, %c16_i64 : i64
      %39 = arith.andi %38, %c281470681808895_i64 : i64
      %40 = arith.andi %37, %c281470681808895_i64 : i64
      %41 = arith.shli %40, %c16_i64 : i64
      %42 = arith.ori %39, %41 : i64
      %43 = arith.shrui %42, %c32_i64 : i64
      %44 = arith.andi %43, %c4294967295_i64 : i64
      %45 = arith.andi %42, %c4294967295_i64 : i64
      %46 = arith.shli %45, %c32_i64 : i64
      %47 = arith.ori %44, %46 : i64
      %48 = arith.shrui %47, %15 : i64
      %49 = arith.select %8, %48, %17 : i64
      %50 = arith.shli %16, %13 : i64
      %51 = arith.xori %50, %c-1_i64 : i64
      %52 = arith.andi %7, %51 : i64
      %53 = arith.shli %49, %13 : i64
      %54 = arith.ori %52, %53 : i64
      affine.store %54, %arg0[%arg3] : memref<64xi64>
    } {hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}]}
    return
  }
}
