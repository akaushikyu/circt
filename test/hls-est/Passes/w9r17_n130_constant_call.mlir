// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_S2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_S2_ --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_S2_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=_Z3topP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_S2_ --config-set tool.hls.folding.evaluate_constant_calls=false -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_S2_ --symbol-dce --lower-polygeist-subindex --inline --canonicalize --sccp --vitis-fold -o - | FileCheck %s --check-prefix=IR

// VITIS_NOTES N130, kernel w9r17p_sq_sqrt4 (Vitis 2025.1 td=off: 0 BRAM, `buf`
// 64 x 15 LUTRAM): `scale = (data_t)1.0 / hls::sqrt((data_t)4)` with data_t
// ap_fixed<16,5>. Vitis evaluates the sqrt of the literal at compile time (no
// sqrt core); the scale is then the constant 0.5 and `in[i] * scale` needs 15
// bits, so `buf` (64 x 15 = 960 bits < 1024) is LUTRAM. --vitis-fold evaluates
// the sqrt_fixed call of the constant 8192 (4.0) to 4096 (2.0).
// Off run: tool.hls.folding.evaluate_constant_calls off (the call stays, the
// scale is unknown, buf 64 x 16 = 1 BRAM).
// IR: hls.vitis_fold = {counts = {"constant-call" = 1
// IR-SAME: sqrt_fixed of constant arguments evaluated: 4096 : i16
// IR-NOT: call @_Z10sqrt_fixed
// CHECK: Total BRAM: 0
// OFF: Total BRAM: 1

module {
  memref.global @"_Z10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_@static@_ZZ10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_E4msbm" : memref<1xi32> = dense<6>
  memref.global @"_Z10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_@static@_ZZ10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_E4msbx" : memref<1xi32> = dense<8>
  memref.global @"_Z10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_@static@_ZZ10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_E4msbr" : memref<1xi32> = dense<3>
  memref.global @"_Z10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_@static@_ZZ10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_E4prcs" : memref<1xi32> = dense<24>
  memref.global @"_Z10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_@static@_ZZ10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_E4lsbx" : memref<1xi32> = dense<19>
  func.func @_Z3topP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_S2_(%arg0: memref<64xi16>, %arg1: memref<64xi16>, %arg2: i16) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "buf"} : memref<64xi16>
    call @_ZL7scale_fP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_S2_(%arg0, %alloca, %arg2) : (memref<64xi16>, memref<64xi16>, i16) -> ()
    call @_ZL5use_fP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_(%alloca, %arg1) : (memref<64xi16>, memref<64xi16>) -> ()
    return
  }
  func.func private @_ZL7scale_fP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_S2_(%arg0: memref<64xi16>, %arg1: memref<64xi16>, %arg2: i16) attributes {hls.inline_off, hls.orig_name = "scale_f", llvm.linkage = #llvm.linkage<internal>} {
    %c4194304_i32 = arith.constant 4194304 : i32
    %c8192_i16 = arith.constant 8192 : i16
    %c11_i32 = arith.constant 11 : i32
    %0 = call @_Z10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_(%c8192_i16) {hls.inline_auto_off = {calls = 1 : i64, size = 1891 : i64}} : (i16) -> i16
    %1 = arith.extsi %0 : i16 to i32
    %2 = arith.divsi %c4194304_i32, %1 : i32
    %3 = arith.trunci %2 : i32 to i16
    %4 = arith.extsi %3 : i16 to i32
    affine.for %arg3 = 0 to 64 {
      %5 = affine.load %arg0[%arg3] : memref<64xi16>
      %6 = arith.extsi %5 : i16 to i32
      %7 = arith.muli %6, %4 : i32
      %8 = arith.shrsi %7, %c11_i32 : i32
      %9 = arith.trunci %8 : i32 to i16
      affine.store %9, %arg1[%arg3] : memref<64xi16>
    }
    return
  }
  func.func private @_ZL5use_fP8ap_fixedILi16ELi5EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_(%arg0: memref<64xi16>, %arg1: memref<64xi16>) attributes {hls.inline_off, hls.orig_name = "use_f", llvm.linkage = #llvm.linkage<internal>} {
    affine.for %arg2 = 0 to 64 {
      %0 = affine.load %arg0[-%arg2 + 63] : memref<64xi16>
      %1 = affine.load %arg0[%arg2] : memref<64xi16>
      %2 = arith.extsi %0 : i16 to i32
      %3 = arith.extsi %1 : i16 to i32
      %4 = arith.addi %2, %3 : i32
      %5 = arith.trunci %4 : i32 to i16
      affine.store %5, %arg1[%arg2] : memref<64xi16>
    }
    return
  }
  func.func @_Z10sqrt_fixedILi16ELi5EE8ap_fixedIXT_EXT0_EL9ap_q_mode5EL9ap_o_mode3ELi0EES3_(%arg0: i16) -> i16 attributes {hls.inline_auto_off = {size = 1891 : i64}, hls.orig_name = "sqrt_fixed", hls.pipeline = [{II = 0 : i32, rewind = false, style = "stp"}], llvm.linkage = #llvm.linkage<linkonce_odr>} {
    %c-1_i32 = arith.constant -1 : i32
    %true = arith.constant true
    %c15_i16 = arith.constant 15 : i16
    %c-4096_i13 = arith.constant -4096 : i13
    %c4095_i13 = arith.constant 4095 : i13
    %c16777215_i32 = arith.constant 16777215 : i32
    %c255_i32 = arith.constant 255 : i32
    %c-16773121_i32 = arith.constant -16773121 : i32
    %c-4096_i32 = arith.constant -4096 : i32
    %c4095_i32 = arith.constant 4095 : i32
    %c-2048_i12 = arith.constant -2048 : i12
    %c2047_i12 = arith.constant 2047 : i12
    %c12_i13 = arith.constant 12 : i13
    %c7_i27 = arith.constant 7 : i27
    %c24_i27 = arith.constant 24 : i27
    %c-16773121_i27 = arith.constant -16773121 : i27
    %c4095_i27 = arith.constant 4095 : i27
    %c12_i27 = arith.constant 12 : i27
    %c13_i32 = arith.constant 13 : i32
    %c1_i12 = arith.constant 1 : i12
    %c1_i30 = arith.constant 1 : i30
    %c8_i16 = arith.constant 8 : i16
    %c255_i16 = arith.constant 255 : i16
    %c4_i16 = arith.constant 4 : i16
    %c3855_i16 = arith.constant 3855 : i16
    %c2_i16 = arith.constant 2 : i16
    %c13107_i16 = arith.constant 13107 : i16
    %c1_i16 = arith.constant 1 : i16
    %c21845_i16 = arith.constant 21845 : i16
    %c-1_i12 = arith.constant -1 : i12
    %c12_i12 = arith.constant 12 : i12
    %c16_i32 = arith.constant 16 : i32
    %c65535_i32 = arith.constant 65535 : i32
    %c8_i32 = arith.constant 8 : i32
    %c16711935_i32 = arith.constant 16711935 : i32
    %c252645135_i32 = arith.constant 252645135 : i32
    %c858993459_i32 = arith.constant 858993459 : i32
    %c1431655765_i32 = arith.constant 1431655765 : i32
    %c-1_i30 = arith.constant -1 : i30
    %c30_i30 = arith.constant 30 : i30
    %c1_i3 = arith.constant 1 : i3
    %c-1_i8 = arith.constant -1 : i8
    %c8_i8 = arith.constant 8 : i8
    %c1_i6 = arith.constant 1 : i6
    %c2_i4 = arith.constant 2 : i4
    %c3_i4 = arith.constant 3 : i4
    %c1_i4 = arith.constant 1 : i4
    %c5_i4 = arith.constant 5 : i4
    %c-1_i3 = arith.constant -1 : i3
    %c3_i3 = arith.constant 3 : i3
    %c4_i8 = arith.constant 4 : i8
    %c15_i8 = arith.constant 15 : i8
    %c2_i8 = arith.constant 2 : i8
    %c51_i8 = arith.constant 51 : i8
    %c85_i8 = arith.constant 85 : i8
    %c-1_i6 = arith.constant -1 : i6
    %c6_i6 = arith.constant 6 : i6
    %c0_i3 = arith.constant 0 : i3
    %c0_i12 = arith.constant 0 : i12
    %c0_i16 = arith.constant 0 : i16
    %c-13 = arith.constant -13 : index
    %c2 = arith.constant 2 : index
    %c1_i8 = arith.constant 1 : i8
    %c27_i32 = arith.constant 27 : i32
    %c25_i32 = arith.constant 25 : i32
    %c24_i32 = arith.constant 24 : i32
    %c12_i32 = arith.constant 12 : i32
    %c4_i32 = arith.constant 4 : i32
    %c3_i32 = arith.constant 3 : i32
    %c2_i32 = arith.constant 2 : i32
    %c0_i8 = arith.constant 0 : i8
    %c1_i32 = arith.constant 1 : i32
    %false = arith.constant false
    %c11_i32 = arith.constant 11 : i32
    %0 = llvm.mlir.undef : i16
    %1 = llvm.mlir.undef : i12
    %2 = llvm.mlir.undef : i32
    %3 = arith.shrui %arg0, %c15_i16 : i16
    %4 = arith.trunci %3 : i16 to i1
    %5 = arith.extui %4 : i1 to i8
    %6 = arith.cmpi eq, %5, %c0_i8 : i8
    %7 = scf.if %6 -> (i16) {
      %8 = arith.extsi %arg0 : i16 to i32
      %9 = arith.shrsi %8, %c11_i32 : i32
      %10 = arith.trunci %9 : i32 to i8
      %11 = arith.shli %8, %c1_i32 : i32
      %12 = arith.trunci %11 : i32 to i12
      %13:2 = affine.for %arg1 = 0 to 3 iter_args(%arg2 = %c0_i3, %arg3 = %10) -> (i3, i8) {
        %41 = arith.subi %c2, %arg1 : index
        %42 = arith.index_cast %41 : index to i32
        %43 = arith.addi %42, %c3_i32 : i32
        %44 = arith.muli %42, %c2_i32 : i32
        %45 = arith.addi %44, %c1_i32 : i32
        %46 = arith.cmpi ugt, %42, %c2_i32 : i32
        %47 = arith.select %46, %c2_i32, %42 : i32
        %48 = arith.select %46, %42, %c2_i32 : i32
        %49 = arith.subi %48, %47 : i32
        %50 = arith.addi %49, %c1_i32 : i32
        %51 = arith.trunci %47 : i32 to i3
        %52 = arith.trunci %50 : i32 to i3
        %53 = arith.subi %c3_i3, %52 : i3
        %54 = arith.shrui %c-1_i3, %53 : i3
        %55 = arith.shrui %arg2, %51 : i3
        %56 = arith.andi %55, %54 : i3
        %57 = arith.extui %56 : i3 to i4
        %58 = arith.shrui %57, %c1_i4 : i4
        %59 = arith.andi %58, %c5_i4 : i4
        %60 = arith.andi %57, %c5_i4 : i4
        %61 = arith.shli %60, %c1_i4 : i4
        %62 = arith.ori %59, %61 : i4
        %63 = arith.shrui %62, %c2_i4 : i4
        %64 = arith.andi %63, %c3_i4 : i4
        %65 = arith.andi %62, %c3_i4 : i4
        %66 = arith.shli %65, %c2_i4 : i4
        %67 = arith.ori %64, %66 : i4
        %68 = arith.extui %53 : i3 to i4
        %69 = arith.addi %68, %c1_i4 : i4
        %70 = arith.shrui %67, %69 : i4
        %71 = arith.trunci %70 : i4 to i3
        %72 = arith.select %46, %71, %56 : i3
        %73 = arith.cmpi ugt, %45, %43 : i32
        %74 = arith.select %73, %43, %45 : i32
        %75 = arith.select %73, %45, %43 : i32
        %76 = arith.subi %75, %74 : i32
        %77 = arith.addi %76, %c1_i32 : i32
        %78 = arith.trunci %74 : i32 to i6
        %79 = arith.trunci %77 : i32 to i6
        %80 = arith.subi %c6_i6, %79 : i6
        %81 = arith.shrui %c-1_i6, %80 : i6
        %82 = arith.extui %72 : i3 to i6
        %83 = arith.andi %82, %81 : i6
        %84 = arith.extui %83 : i6 to i8
        %85 = arith.shrui %84, %c1_i8 : i8
        %86 = arith.andi %85, %c85_i8 : i8
        %87 = arith.andi %84, %c85_i8 : i8
        %88 = arith.shli %87, %c1_i8 : i8
        %89 = arith.ori %86, %88 : i8
        %90 = arith.shrui %89, %c2_i8 : i8
        %91 = arith.andi %90, %c51_i8 : i8
        %92 = arith.andi %89, %c51_i8 : i8
        %93 = arith.shli %92, %c2_i8 : i8
        %94 = arith.ori %91, %93 : i8
        %95 = arith.shrui %94, %c4_i8 : i8
        %96 = arith.andi %95, %c15_i8 : i8
        %97 = arith.andi %94, %c15_i8 : i8
        %98 = arith.shli %97, %c4_i8 : i8
        %99 = arith.ori %96, %98 : i8
        %100 = arith.extui %80 : i6 to i8
        %101 = arith.addi %100, %c2_i8 : i8
        %102 = arith.shrui %99, %101 : i8
        %103 = arith.trunci %102 : i8 to i6
        %104 = arith.select %73, %103, %83 : i6
        %105 = arith.shli %104, %78 : i6
        %106 = arith.trunci %44 : i32 to i6
        %107 = arith.shli %c1_i6, %106 : i6
        %108 = arith.xori %107, %c-1_i6 : i6
        %109 = arith.andi %105, %108 : i6
        %110 = arith.ori %109, %107 : i6
        %111 = arith.addi %42, %c4_i32 : i32
        %112 = arith.cmpi ugt, %44, %111 : i32
        %113 = arith.select %112, %111, %44 : i32
        %114 = arith.select %112, %44, %111 : i32
        %115 = arith.subi %114, %113 : i32
        %116 = arith.addi %115, %c1_i32 : i32
        %117 = arith.trunci %113 : i32 to i8
        %118 = arith.trunci %116 : i32 to i8
        %119 = arith.subi %c8_i8, %118 : i8
        %120 = arith.shrui %c-1_i8, %119 : i8
        %121 = arith.shrui %arg3, %117 : i8
        %122 = arith.andi %121, %120 : i8
        %123 = arith.shrui %122, %c1_i8 : i8
        %124 = arith.andi %123, %c85_i8 : i8
        %125 = arith.andi %122, %c85_i8 : i8
        %126 = arith.shli %125, %c1_i8 : i8
        %127 = arith.ori %124, %126 : i8
        %128 = arith.shrui %127, %c2_i8 : i8
        %129 = arith.andi %128, %c51_i8 : i8
        %130 = arith.andi %127, %c51_i8 : i8
        %131 = arith.shli %130, %c2_i8 : i8
        %132 = arith.ori %129, %131 : i8
        %133 = arith.shrui %132, %c4_i8 : i8
        %134 = arith.andi %133, %c15_i8 : i8
        %135 = arith.andi %132, %c15_i8 : i8
        %136 = arith.shli %135, %c4_i8 : i8
        %137 = arith.ori %134, %136 : i8
        %138 = arith.shrui %137, %119 : i8
        %139 = arith.select %112, %138, %122 : i8
        %140 = arith.cmpi ugt, %44, %43 : i32
        %141 = arith.select %140, %43, %44 : i32
        %142 = arith.select %140, %44, %43 : i32
        %143 = arith.subi %142, %141 : i32
        %144 = arith.addi %143, %c1_i32 : i32
        %145 = arith.trunci %141 : i32 to i6
        %146 = arith.trunci %144 : i32 to i6
        %147 = arith.subi %c6_i6, %146 : i6
        %148 = arith.shrui %c-1_i6, %147 : i6
        %149 = arith.shrui %110, %145 : i6
        %150 = arith.andi %149, %148 : i6
        %151 = arith.extui %150 : i6 to i8
        %152 = arith.shrui %151, %c1_i8 : i8
        %153 = arith.andi %152, %c85_i8 : i8
        %154 = arith.andi %151, %c85_i8 : i8
        %155 = arith.shli %154, %c1_i8 : i8
        %156 = arith.ori %153, %155 : i8
        %157 = arith.shrui %156, %c2_i8 : i8
        %158 = arith.andi %157, %c51_i8 : i8
        %159 = arith.andi %156, %c51_i8 : i8
        %160 = arith.shli %159, %c2_i8 : i8
        %161 = arith.ori %158, %160 : i8
        %162 = arith.shrui %161, %c4_i8 : i8
        %163 = arith.andi %162, %c15_i8 : i8
        %164 = arith.andi %161, %c15_i8 : i8
        %165 = arith.shli %164, %c4_i8 : i8
        %166 = arith.ori %163, %165 : i8
        %167 = arith.extui %147 : i6 to i8
        %168 = arith.addi %167, %c2_i8 : i8
        %169 = arith.shrui %166, %168 : i8
        %170 = arith.trunci %169 : i8 to i6
        %171 = arith.select %140, %170, %150 : i6
        %172 = arith.extui %139 : i8 to i32
        %173 = arith.extui %171 : i6 to i32
        %174 = arith.cmpi slt, %172, %173 : i32
        %175 = arith.extui %174 : i1 to i8
        %176 = arith.cmpi eq, %175, %c0_i8 : i8
        %177:2 = scf.if %176 -> (i3, i8) {
          %178 = arith.extui %139 : i8 to i64
          %179 = arith.extui %171 : i6 to i64
          %180 = arith.subi %178, %179 : i64
          %181 = arith.trunci %180 : i64 to i8
          %182 = arith.andi %181, %120 : i8
          %183 = arith.shrui %182, %c1_i8 : i8
          %184 = arith.andi %183, %c85_i8 : i8
          %185 = arith.andi %182, %c85_i8 : i8
          %186 = arith.shli %185, %c1_i8 : i8
          %187 = arith.ori %184, %186 : i8
          %188 = arith.shrui %187, %c2_i8 : i8
          %189 = arith.andi %188, %c51_i8 : i8
          %190 = arith.andi %187, %c51_i8 : i8
          %191 = arith.shli %190, %c2_i8 : i8
          %192 = arith.ori %189, %191 : i8
          %193 = arith.shrui %192, %c4_i8 : i8
          %194 = arith.andi %193, %c15_i8 : i8
          %195 = arith.andi %192, %c15_i8 : i8
          %196 = arith.shli %195, %c4_i8 : i8
          %197 = arith.ori %194, %196 : i8
          %198 = arith.shrui %197, %119 : i8
          %199 = arith.select %112, %198, %182 : i8
          %200 = arith.shli %120, %117 : i8
          %201 = arith.xori %200, %c-1_i8 : i8
          %202 = arith.andi %arg3, %201 : i8
          %203 = arith.shli %199, %117 : i8
          %204 = arith.ori %202, %203 : i8
          %205 = arith.trunci %42 : i32 to i3
          %206 = arith.shli %c1_i3, %205 : i3
          %207 = arith.xori %206, %c-1_i3 : i3
          %208 = arith.andi %arg2, %207 : i3
          %209 = arith.ori %208, %206 : i3
          scf.yield %209, %204 : i3, i8
        } else {
          scf.yield %arg2, %arg3 : i3, i8
        }
        affine.yield %177#0, %177#1 : i3, i8
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %14 = arith.extui %13#0 : i3 to i30
      %15:5 = affine.for %arg1 = -12 to 0 iter_args(%arg2 = %2, %arg3 = %c0_i12, %arg4 = %c0_i12, %arg5 = %12, %arg6 = %13#1) -> (i32, i12, i12, i12, i8) {
        %41 = arith.subi %c-13, %arg1 : index
        %42 = arith.index_cast %41 : index to i32
        %43 = arith.addi %42, %c27_i32 : i32
        %44 = arith.addi %42, %c25_i32 : i32
        %45 = arith.cmpi ugt, %44, %43 : i32
        %46 = arith.select %45, %43, %44 : i32
        %47 = arith.select %45, %44, %43 : i32
        %48 = arith.subi %47, %46 : i32
        %49 = arith.addi %48, %c1_i32 : i32
        %50 = arith.trunci %46 : i32 to i30
        %51 = arith.trunci %49 : i32 to i30
        %52 = arith.subi %c30_i30, %51 : i30
        %53 = arith.shrui %c-1_i30, %52 : i30
        %54 = arith.andi %14, %53 : i30
        %55 = arith.extui %54 : i30 to i32
        %56 = arith.shrui %55, %c1_i32 : i32
        %57 = arith.andi %56, %c1431655765_i32 : i32
        %58 = arith.andi %55, %c1431655765_i32 : i32
        %59 = arith.shli %58, %c1_i32 : i32
        %60 = arith.ori %57, %59 : i32
        %61 = arith.shrui %60, %c2_i32 : i32
        %62 = arith.andi %61, %c858993459_i32 : i32
        %63 = arith.andi %60, %c858993459_i32 : i32
        %64 = arith.shli %63, %c2_i32 : i32
        %65 = arith.ori %62, %64 : i32
        %66 = arith.shrui %65, %c4_i32 : i32
        %67 = arith.andi %66, %c252645135_i32 : i32
        %68 = arith.andi %65, %c252645135_i32 : i32
        %69 = arith.shli %68, %c4_i32 : i32
        %70 = arith.ori %67, %69 : i32
        %71 = arith.shrui %70, %c8_i32 : i32
        %72 = arith.andi %71, %c16711935_i32 : i32
        %73 = arith.andi %70, %c16711935_i32 : i32
        %74 = arith.shli %73, %c8_i32 : i32
        %75 = arith.ori %72, %74 : i32
        %76 = arith.shrui %75, %c16_i32 : i32
        %77 = arith.andi %76, %c65535_i32 : i32
        %78 = arith.andi %75, %c65535_i32 : i32
        %79 = arith.shli %78, %c16_i32 : i32
        %80 = arith.ori %77, %79 : i32
        %81 = arith.extui %52 : i30 to i32
        %82 = arith.addi %81, %c2_i32 : i32
        %83 = arith.shrui %80, %82 : i32
        %84 = arith.trunci %83 : i32 to i30
        %85 = arith.select %45, %84, %54 : i30
        %86 = arith.shli %85, %50 : i30
        %87 = arith.addi %42, %c24_i32 : i32
        %88 = arith.muli %42, %c2_i32 : i32
        %89 = arith.addi %88, %c25_i32 : i32
        %90 = arith.addi %42, %c12_i32 : i32
        %91 = arith.cmpi ugt, %90, %c11_i32 : i32
        %92 = arith.select %91, %c11_i32, %90 : i32
        %93 = arith.select %91, %90, %c11_i32 : i32
        %94 = arith.subi %93, %92 : i32
        %95 = arith.addi %94, %c1_i32 : i32
        %96 = arith.trunci %92 : i32 to i12
        %97 = arith.trunci %95 : i32 to i12
        %98 = arith.subi %c12_i12, %97 : i12
        %99 = arith.shrui %c-1_i12, %98 : i12
        %100 = arith.shrui %arg3, %96 : i12
        %101 = arith.andi %100, %99 : i12
        %102 = arith.extui %101 : i12 to i16
        %103 = arith.shrui %102, %c1_i16 : i16
        %104 = arith.andi %103, %c21845_i16 : i16
        %105 = arith.andi %102, %c21845_i16 : i16
        %106 = arith.shli %105, %c1_i16 : i16
        %107 = arith.ori %104, %106 : i16
        %108 = arith.shrui %107, %c2_i16 : i16
        %109 = arith.andi %108, %c13107_i16 : i16
        %110 = arith.andi %107, %c13107_i16 : i16
        %111 = arith.shli %110, %c2_i16 : i16
        %112 = arith.ori %109, %111 : i16
        %113 = arith.shrui %112, %c4_i16 : i16
        %114 = arith.andi %113, %c3855_i16 : i16
        %115 = arith.andi %112, %c3855_i16 : i16
        %116 = arith.shli %115, %c4_i16 : i16
        %117 = arith.ori %114, %116 : i16
        %118 = arith.shrui %117, %c8_i16 : i16
        %119 = arith.andi %118, %c255_i16 : i16
        %120 = arith.andi %117, %c255_i16 : i16
        %121 = arith.shli %120, %c8_i16 : i16
        %122 = arith.ori %119, %121 : i16
        %123 = arith.extui %98 : i12 to i16
        %124 = arith.addi %123, %c4_i16 : i16
        %125 = arith.shrui %122, %124 : i16
        %126 = arith.trunci %125 : i16 to i12
        %127 = arith.select %91, %126, %101 : i12
        %128 = arith.cmpi ugt, %89, %87 : i32
        %129 = arith.select %128, %87, %89 : i32
        %130 = arith.select %128, %89, %87 : i32
        %131 = arith.subi %130, %129 : i32
        %132 = arith.addi %131, %c1_i32 : i32
        %133 = arith.trunci %129 : i32 to i30
        %134 = arith.trunci %132 : i32 to i30
        %135 = arith.subi %c30_i30, %134 : i30
        %136 = arith.shrui %c-1_i30, %135 : i30
        %137 = arith.extui %127 : i12 to i30
        %138 = arith.andi %137, %136 : i30
        %139 = arith.extui %138 : i30 to i32
        %140 = arith.shrui %139, %c1_i32 : i32
        %141 = arith.andi %140, %c1431655765_i32 : i32
        %142 = arith.andi %139, %c1431655765_i32 : i32
        %143 = arith.shli %142, %c1_i32 : i32
        %144 = arith.ori %141, %143 : i32
        %145 = arith.shrui %144, %c2_i32 : i32
        %146 = arith.andi %145, %c858993459_i32 : i32
        %147 = arith.andi %144, %c858993459_i32 : i32
        %148 = arith.shli %147, %c2_i32 : i32
        %149 = arith.ori %146, %148 : i32
        %150 = arith.shrui %149, %c4_i32 : i32
        %151 = arith.andi %150, %c252645135_i32 : i32
        %152 = arith.andi %149, %c252645135_i32 : i32
        %153 = arith.shli %152, %c4_i32 : i32
        %154 = arith.ori %151, %153 : i32
        %155 = arith.shrui %154, %c8_i32 : i32
        %156 = arith.andi %155, %c16711935_i32 : i32
        %157 = arith.andi %154, %c16711935_i32 : i32
        %158 = arith.shli %157, %c8_i32 : i32
        %159 = arith.ori %156, %158 : i32
        %160 = arith.shrui %159, %c16_i32 : i32
        %161 = arith.andi %160, %c65535_i32 : i32
        %162 = arith.andi %159, %c65535_i32 : i32
        %163 = arith.shli %162, %c16_i32 : i32
        %164 = arith.ori %161, %163 : i32
        %165 = arith.extui %135 : i30 to i32
        %166 = arith.addi %165, %c2_i32 : i32
        %167 = arith.shrui %164, %166 : i32
        %168 = arith.trunci %167 : i32 to i30
        %169 = arith.select %128, %168, %138 : i30
        %170 = arith.shli %136, %133 : i30
        %171 = arith.xori %170, %c-1_i30 : i30
        %172 = arith.andi %86, %171 : i30
        %173 = arith.shli %169, %133 : i30
        %174 = arith.ori %172, %173 : i30
        %175 = arith.addi %88, %c24_i32 : i32
        %176 = arith.trunci %175 : i32 to i30
        %177 = arith.shli %c1_i30, %176 : i30
        %178 = arith.xori %177, %c-1_i30 : i30
        %179 = arith.andi %174, %178 : i30
        %180 = arith.ori %179, %177 : i30
        %181 = arith.extui %180 : i30 to i32
        %182 = arith.shrsi %181, %c24_i32 : i32
        %183 = arith.trunci %182 : i32 to i6
        %184 = arith.shrsi %181, %c12_i32 : i32
        %185 = arith.trunci %184 : i32 to i12
        %186 = arith.trunci %180 : i30 to i12
        %187 = arith.extui %arg6 : i8 to i32
        %188 = arith.andi %187, %c255_i32 : i32
        %189 = arith.andi %arg2, %c16777215_i32 : i32
        %190 = arith.shli %188, %c24_i32 : i32
        %191 = arith.ori %189, %190 : i32
        %192 = arith.extui %arg5 : i12 to i32
        %193 = arith.andi %192, %c4095_i32 : i32
        %194 = arith.andi %191, %c-16773121_i32 : i32
        %195 = arith.shli %193, %c12_i32 : i32
        %196 = arith.ori %194, %195 : i32
        %197 = arith.extui %arg4 : i12 to i32
        %198 = arith.andi %197, %c4095_i32 : i32
        %199 = arith.andi %196, %c-4096_i32 : i32
        %200 = arith.ori %199, %198 : i32
        %201 = arith.extui %183 : i6 to i32
        %202 = arith.cmpi sgt, %187, %201 : i32
        %203 = scf.if %202 -> (i1) {
          scf.yield %true : i1
        } else {
          %206 = arith.cmpi eq, %187, %201 : i32
          %207 = scf.if %206 -> (i1) {
            %208 = arith.extui %185 : i12 to i32
            %209 = arith.cmpi sgt, %192, %208 : i32
            scf.yield %209 : i1
          } else {
            scf.yield %false : i1
          }
          scf.yield %207 : i1
        }
        %204 = scf.if %203 -> (i1) {
          scf.yield %true : i1
        } else {
          %206 = arith.cmpi eq, %187, %201 : i32
          %207 = arith.cmpi eq, %arg5, %185 : i12
          %208 = arith.andi %206, %207 : i1
          %209 = scf.if %208 -> (i1) {
            %210 = arith.extui %186 : i12 to i32
            %211 = arith.cmpi sge, %197, %210 : i32
            scf.yield %211 : i1
          } else {
            scf.yield %false : i1
          }
          scf.yield %209 : i1
        }
        %205:5 = scf.if %204 -> (i32, i12, i12, i12, i8) {
          %206 = arith.extui %arg4 : i12 to i13
          %207 = arith.extui %186 : i12 to i32
          %208 = arith.cmpi slt, %197, %207 : i32
          %209 = scf.if %208 -> (i13) {
            %248 = arith.andi %206, %c4095_i13 : i13
            %249 = arith.ori %248, %c-4096_i13 : i13
            scf.yield %249 : i13
          } else {
            scf.yield %206 : i13
          }
          %210 = arith.extui %209 : i13 to i32
          %211 = arith.subi %210, %207 : i32
          %212 = arith.extui %arg5 : i12 to i13
          %213 = arith.extui %185 : i12 to i32
          %214 = arith.cmpi slt, %192, %213 : i32
          %215 = scf.if %214 -> (i1) {
            scf.yield %true : i1
          } else {
            %248 = arith.cmpi eq, %arg5, %185 : i12
            %249 = arith.andi %248, %208 : i1
            scf.yield %249 : i1
          }
          %216 = scf.if %215 -> (i13) {
            %248 = arith.andi %212, %c4095_i13 : i13
            %249 = arith.ori %248, %c-4096_i13 : i13
            scf.yield %249 : i13
          } else {
            scf.yield %212 : i13
          }
          %217 = arith.extui %216 : i13 to i32
          %218 = arith.extui %208 : i1 to i32
          %219 = arith.subi %217, %218 : i32
          %220 = arith.trunci %219 : i32 to i13
          %221 = arith.extui %220 : i13 to i32
          %222 = arith.subi %221, %213 : i32
          %223 = scf.if %215 -> (i8) {
            %248 = arith.addi %187, %c-1_i32 : i32
            %249 = arith.trunci %248 : i32 to i8
            scf.yield %249 : i8
          } else {
            scf.yield %arg6 : i8
          }
          %224 = arith.extui %223 : i8 to i32
          %225 = arith.subi %224, %201 : i32
          %226 = arith.trunci %225 : i32 to i8
          %227 = arith.trunci %222 : i32 to i12
          %228 = arith.trunci %211 : i32 to i12
          %229 = arith.extui %226 : i8 to i32
          %230 = arith.andi %229, %c255_i32 : i32
          %231 = arith.andi %200, %c16777215_i32 : i32
          %232 = arith.shli %230, %c24_i32 : i32
          %233 = arith.ori %231, %232 : i32
          %234 = arith.extui %227 : i12 to i32
          %235 = arith.andi %234, %c4095_i32 : i32
          %236 = arith.andi %233, %c-16773121_i32 : i32
          %237 = arith.shli %235, %c12_i32 : i32
          %238 = arith.ori %236, %237 : i32
          %239 = arith.extui %228 : i12 to i32
          %240 = arith.andi %239, %c4095_i32 : i32
          %241 = arith.andi %238, %c-4096_i32 : i32
          %242 = arith.ori %241, %240 : i32
          %243 = arith.trunci %90 : i32 to i12
          %244 = arith.shli %c1_i12, %243 : i12
          %245 = arith.xori %244, %c-1_i12 : i12
          %246 = arith.andi %arg3, %245 : i12
          %247 = arith.ori %246, %244 : i12
          scf.yield %242, %247, %228, %227, %226 : i32, i12, i12, i12, i8
        } else {
          scf.yield %200, %arg3, %arg4, %arg5, %arg6 : i32, i12, i12, i12, i8
        }
        affine.yield %205#0, %205#1, %205#2, %205#3, %205#4 : i32, i12, i12, i12, i8
      } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
      %16 = arith.andi %1, %c2047_i12 : i12
      %17 = arith.ori %16, %c-2048_i12 : i12
      %18 = arith.extui %17 : i12 to i32
      %19 = arith.shrsi %18, %c11_i32 : i32
      %20 = arith.trunci %19 : i32 to i12
      %21 = arith.extui %15#1 : i12 to i32
      %22 = arith.extui %20 : i12 to i32
      %23 = arith.addi %21, %22 : i32
      %24 = arith.trunci %23 : i32 to i13
      %25 = arith.trunci %23 : i32 to i12
      %26 = arith.shrui %24, %c12_i13 : i13
      %27 = arith.trunci %26 : i13 to i1
      %28 = scf.if %27 -> (i3) {
        %41 = arith.extui %13#0 : i3 to i32
        %42 = arith.addi %41, %c1_i32 : i32
        %43 = arith.trunci %42 : i32 to i3
        scf.yield %43 : i3
      } else {
        scf.yield %13#0 : i3
      }
      %29 = arith.extui %28 : i3 to i27
      %30 = arith.andi %29, %c7_i27 : i27
      %31 = arith.shli %30, %c24_i27 : i27
      %32 = arith.extui %25 : i12 to i27
      %33 = arith.andi %32, %c4095_i27 : i27
      %34 = arith.andi %31, %c-16773121_i27 : i27
      %35 = arith.shli %33, %c12_i27 : i27
      %36 = arith.ori %34, %35 : i27
      %37 = arith.extui %36 : i27 to i32
      %38 = arith.shrsi %37, %c13_i32 : i32
      %39 = arith.trunci %38 : i32 to i14
      %40 = arith.extui %39 : i14 to i16
      scf.yield %40 : i16
    } else {
      %8 = arith.select %4, %c0_i16, %0 : i16
      scf.yield %8 : i16
    }
    return %7 : i16
  }
}
