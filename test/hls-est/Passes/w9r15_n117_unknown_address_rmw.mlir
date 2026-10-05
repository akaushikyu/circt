// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA72_hPA70_hPiS3_S3_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug -o /dev/null 2>&1 | FileCheck %s
// RUN: hls-est %s --symbol-privatize=exclude=_Z3topPA72_hPA70_hPiS3_S3_ --symbol-dce --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array=td=off --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set scheduling.dependences.unknown_address_min_ii=0 --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=OFF

// VITIS_NOTES N117, kernel w9r15p_hs_rmw (Vitis 2025.1 td=off: 22): three h[v]++
// histogram updates per pixel at addresses computed from a 3 x 3 window of the
// local in[72][72]: the read-modify-write at an address computed in the body is a
// recurrence (scheduling.dependences.unknown_address_min_ii = 2): II 2 and in
// RAM_1WNR 4 copies (16) as in Vitis. The histograms are 1 BRAM each against
// Vitis' 2 (RAM_AUTO_1R1W 256 x 32): unexplained, OPEN_ISSUES O154.
// Off run: II 1, in 8 copies (38).
// CHECK: Total BRAM: 19
// OFF: Total BRAM: 38

module {
  func.func @_Z3topPA72_hPA70_hPiS3_S3_(%arg0: memref<72x72xi8>, %arg1: memref<70x70xi8>, %arg2: memref<256xi32>, %arg3: memref<256xi32>, %arg4: memref<256xi32>) attributes {hls.orig_name = "top", llvm.linkage = #llvm.linkage<external>} {
    %c4_i32 = arith.constant 4 : i32
    %c2_i32 = arith.constant 2 : i32
    %c1_i32 = arith.constant 1 : i32
    %c0_i32 = arith.constant 0 : i32
    %alloca = memref.alloca() {hls.preserve, polygeist.varname = "hr"} : memref<256xi32>
    %alloca_0 = memref.alloca() {hls.preserve, polygeist.varname = "hg"} : memref<256xi32>
    %alloca_1 = memref.alloca() {hls.preserve, polygeist.varname = "hb"} : memref<256xi32>
    %alloca_2 = memref.alloca() {hls.preserve, polygeist.varname = "in"} : memref<72x72xi8>
    affine.for %arg5 = 0 to 256 {
      affine.store %c0_i32, %alloca_1[%arg5] : memref<256xi32>
      affine.store %c0_i32, %alloca_0[%arg5] : memref<256xi32>
      affine.store %c0_i32, %alloca[%arg5] : memref<256xi32>
    }
    affine.for %arg5 = 0 to 72 {
      affine.for %arg6 = 0 to 72 {
        %0 = affine.load %arg0[%arg5, %arg6] : memref<72x72xi8>
        affine.store %0, %alloca_2[%arg5, %arg6] : memref<72x72xi8>
      }
    }
    affine.for %arg5 = 1 to 71 {
      affine.for %arg6 = 1 to 71 {
        %0:3 = affine.for %arg7 = 0 to 3 iter_args(%arg8 = %c0_i32, %arg9 = %c0_i32, %arg10 = %c0_i32) -> (i32, i32, i32) {
          %18 = arith.index_cast %arg7 : index to i32
          %19 = arith.addi %18, %c1_i32 : i32
          %20:3 = affine.for %arg11 = 0 to 3 iter_args(%arg12 = %arg8, %arg13 = %arg9, %arg14 = %arg10) -> (i32, i32, i32) {
            %21 = arith.index_cast %arg11 : index to i32
            %22 = affine.load %alloca_2[%arg5 + %arg7 - 1, %arg6 + %arg11 - 1] : memref<72x72xi8>
            %23 = arith.extui %22 : i8 to i32
            %24 = arith.muli %23, %19 : i32
            %25 = arith.addi %arg14, %24 : i32
            %26 = arith.addi %21, %c2_i32 : i32
            %27 = arith.muli %23, %26 : i32
            %28 = arith.addi %arg13, %27 : i32
            %29 = arith.addi %18, %21 : i32
            %30 = arith.addi %29, %c1_i32 : i32
            %31 = arith.muli %23, %30 : i32
            %32 = arith.addi %arg12, %31 : i32
            affine.yield %32, %28, %25 : i32, i32, i32
          }
          affine.yield %20#0, %20#1, %20#2 : i32, i32, i32
        }
        %1 = arith.shrsi %0#2, %c4_i32 : i32
        %2 = arith.trunci %1 : i32 to i8
        %3 = arith.shrsi %0#1, %c4_i32 : i32
        %4 = arith.trunci %3 : i32 to i8
        %5 = arith.shrsi %0#0, %c4_i32 : i32
        %6 = arith.trunci %5 : i32 to i8
        %7 = arith.xori %2, %4 : i8
        %8 = arith.xori %7, %6 : i8
        affine.store %8, %arg1[%arg5 - 1, %arg6 - 1] : memref<70x70xi8>
        %9 = arith.index_castui %2 : i8 to index
        %10 = memref.load %alloca_1[%9] : memref<256xi32>
        %11 = arith.addi %10, %c1_i32 : i32
        memref.store %11, %alloca_1[%9] : memref<256xi32>
        %12 = arith.index_castui %4 : i8 to index
        %13 = memref.load %alloca_0[%12] : memref<256xi32>
        %14 = arith.addi %13, %c1_i32 : i32
        memref.store %14, %alloca_0[%12] : memref<256xi32>
        %15 = arith.index_castui %6 : i8 to index
        %16 = memref.load %alloca[%15] : memref<256xi32>
        %17 = arith.addi %16, %c1_i32 : i32
        memref.store %17, %alloca[%15] : memref<256xi32>
      }
    }
    affine.for %arg5 = 0 to 256 {
      %0 = affine.load %alloca_1[%arg5] : memref<256xi32>
      affine.store %0, %arg2[%arg5] : memref<256xi32>
      %1 = affine.load %alloca_0[%arg5] : memref<256xi32>
      affine.store %1, %arg3[%arg5] : memref<256xi32>
      %2 = affine.load %alloca[%arg5] : memref<256xi32>
      affine.store %2, %arg4[%arg5] : memref<256xi32>
    }
    return
  }
}
