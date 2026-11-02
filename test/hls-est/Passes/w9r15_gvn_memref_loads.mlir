// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA72_hPA70_hPiS3_S3_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA72_hPA70_hPiS3_S3_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.middle_end.gvn_memref_loads=false --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// Kernel w9r15i_hs_ap4 (Vitis 2025.1 td=off: 22, in RAM_1WNR 4 copies = 16 at II 2): the
// Dehazing debayer shape with ap_uint<8> counters (cgeist promotes them, OPEN_ISSUES
// O101): each window element of the local in[72][72] is read three times, once per
// colour, between stores into completely partitioned temporaries; the reads are
// memref.loads (their index is ap_uint arithmetic). The repeated loads of one index
// are one read (tool.hls.middle_end.gvn_memref_loads): 9 reads at II 2 (N117), in 16.
// The histograms are 1 BRAM each against Vitis' 2 (OPEN_ISSUES O154).
// Off run: 27 reads, in 13 copies.
// CHECK: Total BRAM: 19
// OFF: Total BRAM: 55

module {
  func.func @_Z3topPA72_hPA70_hPiS3_S3_(%arg0: memref<72x72xi8>, %arg1: memref<70x70xi8>, %arg2: memref<256xi32>, %arg3: memref<256xi32>, %arg4: memref<256xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c3_i8 = arith.constant 3 : i8
    %c-1_i33 = arith.constant -1 : i33
    %c2_i33 = arith.constant 2 : i33
    %c1_i33 = arith.constant 1 : i33
    %c4_i32 = arith.constant 4 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %0 = llvm.mlir.undef : i8
    %alloca = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "tB"}], hls.preserve, polygeist.varname = "tB"} : memref<9xi32>
    %alloca_0 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "tG"}], hls.preserve, polygeist.varname = "tG"} : memref<9xi32>
    %alloca_1 = memref.alloca() {hls.array_partition = [{dim = 1 : i32, kind = "complete", variable = "tR"}], hls.preserve, polygeist.varname = "tR"} : memref<9xi32>
    %alloca_2 = memref.alloca() {hls.preserve, polygeist.varname = "hr"} : memref<256xi32>
    %alloca_3 = memref.alloca() {hls.preserve, polygeist.varname = "hg"} : memref<256xi32>
    %alloca_4 = memref.alloca() {hls.preserve, polygeist.varname = "hb"} : memref<256xi32>
    %alloca_5 = memref.alloca() {hls.preserve, polygeist.varname = "in"} : memref<72x72xi8>
    affine.for %arg5 = 0 to 256 {
      affine.store %c0_i32, %alloca_4[%arg5] : memref<256xi32>
      affine.store %c0_i32, %alloca_3[%arg5] : memref<256xi32>
      affine.store %c0_i32, %alloca_2[%arg5] : memref<256xi32>
    }
    affine.for %arg5 = 0 to 72 {
      affine.for %arg6 = 0 to 72 {
        %2 = affine.load %arg0[%arg5, %arg6] : memref<72x72xi8>
        affine.store %2, %alloca_5[%arg5, %arg6] : memref<72x72xi8>
      }
    }
    %1:2 = affine.for %arg5 = 1 to 71 iter_args(%arg6 = %0, %arg7 = %0) -> (i8, i8) {
      %2 = arith.index_cast %arg5 : index to i8
      %3 = arith.extui %2 : i8 to i32
      %4:2 = affine.for %arg8 = 1 to 71 iter_args(%arg9 = %arg6, %arg10 = %arg7) -> (i8, i8) {
        %5 = arith.index_cast %arg8 : index to i8
        %6 = arith.extui %5 : i8 to i32
        %7 = affine.for %arg11 = 0 to 3 iter_args(%arg12 = %arg9) -> (i8) {
          %26 = arith.index_cast %arg11 : index to i8
          %27 = arith.extui %26 : i8 to i32
          %28 = arith.addi %3, %27 : i32
          %29 = arith.trunci %28 : i32 to i9
          %30 = arith.extui %29 : i9 to i33
          %31 = arith.addi %30, %c-1_i33 : i33
          %32 = arith.index_cast %31 : i33 to index
          %33 = arith.extui %26 : i8 to i33
          %34 = arith.addi %33, %c1_i33 : i33
          %35 = arith.extsi %34 : i33 to i41
          affine.for %arg13 = 0 to 3 {
            %36 = arith.index_cast %arg13 : index to i8
            %37 = arith.extui %36 : i8 to i32
            %38 = arith.addi %6, %37 : i32
            %39 = arith.trunci %38 : i32 to i9
            %40 = arith.extui %39 : i9 to i33
            %41 = arith.addi %40, %c-1_i33 : i33
            %42 = arith.index_cast %41 : i33 to index
            %43 = memref.load %alloca_5[%32, %42] : memref<72x72xi8>
            %44 = arith.extui %43 : i8 to i41
            %45 = arith.muli %44, %35 : i41
            %46 = arith.trunci %45 : i41 to i32
            affine.store %46, %alloca_1[%arg13 + %arg11 * 3] : memref<9xi32>
            %47 = memref.load %alloca_5[%32, %42] : memref<72x72xi8>
            %48 = arith.extui %36 : i8 to i33
            %49 = arith.addi %48, %c2_i33 : i33
            %50 = arith.extui %47 : i8 to i41
            %51 = arith.extsi %49 : i33 to i41
            %52 = arith.muli %50, %51 : i41
            %53 = arith.trunci %52 : i41 to i32
            affine.store %53, %alloca_0[%arg13 + %arg11 * 3] : memref<9xi32>
            %54 = memref.load %alloca_5[%32, %42] : memref<72x72xi8>
            %55 = arith.addi %27, %37 : i32
            %56 = arith.trunci %55 : i32 to i9
            %57 = arith.extui %56 : i9 to i33
            %58 = arith.addi %57, %c1_i33 : i33
            %59 = arith.extui %54 : i8 to i41
            %60 = arith.extsi %58 : i33 to i41
            %61 = arith.muli %59, %60 : i41
            %62 = arith.trunci %61 : i41 to i32
            affine.store %62, %alloca[%arg13 + %arg11 * 3] : memref<9xi32>
          }
          affine.yield %c3_i8 : i8
        }
        %8:3 = affine.for %arg11 = 0 to 9 iter_args(%arg12 = %c0_i32, %arg13 = %c0_i32, %arg14 = %c0_i32) -> (i32, i32, i32) {
          %26 = affine.load %alloca_1[%arg11] : memref<9xi32>
          %27 = arith.addi %arg14, %26 : i32
          %28 = affine.load %alloca_0[%arg11] : memref<9xi32>
          %29 = arith.addi %arg13, %28 : i32
          %30 = affine.load %alloca[%arg11] : memref<9xi32>
          %31 = arith.addi %arg12, %30 : i32
          affine.yield %31, %29, %27 : i32, i32, i32
        }
        %9 = arith.shrsi %8#2, %c4_i32 : i32
        %10 = arith.trunci %9 : i32 to i8
        %11 = arith.shrsi %8#1, %c4_i32 : i32
        %12 = arith.trunci %11 : i32 to i8
        %13 = arith.shrsi %8#0, %c4_i32 : i32
        %14 = arith.trunci %13 : i32 to i8
        %15 = arith.xori %10, %12 : i8
        %16 = arith.xori %15, %14 : i8
        affine.store %16, %arg1[%arg5 - 1, %arg8 - 1] : memref<70x70xi8>
        %17 = arith.index_castui %10 : i8 to index
        %18 = memref.load %alloca_4[%17] : memref<256xi32>
        %19 = arith.addi %18, %c1_i32 : i32
        memref.store %19, %alloca_4[%17] : memref<256xi32>
        %20 = arith.index_castui %12 : i8 to index
        %21 = memref.load %alloca_3[%20] : memref<256xi32>
        %22 = arith.addi %21, %c1_i32 : i32
        memref.store %22, %alloca_3[%20] : memref<256xi32>
        %23 = arith.index_castui %14 : i8 to index
        %24 = memref.load %alloca_2[%23] : memref<256xi32>
        %25 = arith.addi %24, %c1_i32 : i32
        memref.store %25, %alloca_2[%23] : memref<256xi32>
        affine.yield %7, %c3_i8 : i8, i8
      }
      affine.yield %4#0, %4#1 : i8, i8
    }
    affine.for %arg5 = 0 to 256 {
      %2 = affine.load %alloca_4[%arg5] : memref<256xi32>
      affine.store %2, %arg2[%arg5] : memref<256xi32>
      %3 = affine.load %alloca_3[%arg5] : memref<256xi32>
      affine.store %3, %arg3[%arg5] : memref<256xi32>
      %4 = affine.load %alloca_2[%arg5] : memref<256xi32>
      affine.store %4, %arg4[%arg5] : memref<256xi32>
    }
    return
  }
}
