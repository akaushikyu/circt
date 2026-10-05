// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --bram-debug > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.err
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll -o - | FileCheck %s --check-prefix=PROMOTE
//
// VITIS_NOTES.md N4: the RAM_1WNR copies of an array are sized for the II
// of the loop, which a loop-carried recurrence bounds (spector_hls/fir: 8
// reads of ai_a0 per iteration at the II 6 of the promoted `firReal[l] +=`
// recurrence -> one copy = 2 BRAM). The recurrence reaches the scheduler only
// as an iter_args chain, which is what the register promotion of
// --auto-pipeline-unroll (`promote-pipelined`) produces.
//
// @chain: acc = 0; i(64) { j(8) { acc = acc + la[i][j] * lb[j] } ; lo[i] = acc }
//   with f32 and acc carried ACROSS i (an iter_arg of the i loop). After
//   --auto-pipeline-unroll the i loop is pipelined, j unrolled: 8 reads of
//   la per iteration feeding one loop-carried chain of 8 fadds - the
//   recurrence-bound II is far above the 1 cycle the 17 slots of la would
//   allow, so la gets no copies (Vitis builds no copies a recurrence cannot
//   use). (A chain re-initialised every i iteration is not loop-carried:
//   pu_red_m8_n16_float, II 1, 15 copies.)
// @independent: the same 8 reads summed with a tree (no loop-carried chain):
//   recurrence II 1, port-limited II 1 -> 7 copies.
// @promoted: i(64) { j(8) #pragma HLS unroll { acc[j] += la[i][j] } }: the
//   user unroll of j leaves 8 locations acc[0..7] that are invariant in the
//   pipelined i loop; Vitis promotes them to registers (LLVM LICM scalar
//   promotion of each location, spector_hls/fir's firReal/firImag), so the
//   pipeline holds no acc access at all and the recurrences run through
//   iter_args, where the scheduler sees them. (Without the pragma the nest
//   is perfect and flattened, like pu_memred_ind_m8_n16.)

// CHECK:      la (alloca)
// CHECK:        replication: replicable (max 1 store(s) per loop body), copies 1
// CHECK:          8R+0W per iteration -> ceil(8/{{[0-9]+}})=1 port-cycles -> copies 1
// CHECK:        ram type: RAM_2P
// CHECK:        bram: 2
func.func @chain(%a: memref<64x8xf32>, %b: memref<8xf32>, %out: memref<64xf32>) {
  %cst = arith.constant 0.000000e+00 : f32
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<64xf32>
  %lb = memref.alloca() {hls.preserve, polygeist.varname = "lb"} : memref<8xf32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<64x8xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 8 {
      %0 = affine.load %a[%i, %j] : memref<64x8xf32>
      affine.store %0, %la[%i, %j] : memref<64x8xf32>
    }
  }
  affine.for %j = 0 to 8 {
    %0 = affine.load %b[%j] : memref<8xf32>
    affine.store %0, %lb[%j] : memref<8xf32>
  }
  %acc = affine.for %i = 0 to 64 iter_args(%carried = %cst) -> (f32) {
    %0 = affine.for %j = 0 to 8 iter_args(%s = %carried) -> (f32) {
      %1 = affine.load %la[%i, %j] : memref<64x8xf32>
      %2 = affine.load %lb[%j] : memref<8xf32>
      %3 = arith.mulf %1, %2 : f32
      %4 = arith.addf %s, %3 : f32
      affine.yield %4 : f32
    }
    affine.store %0, %lo[%i] : memref<64xf32>
    affine.yield %0 : f32
  }
  affine.store %acc, %lo[0] : memref<64xf32>
  affine.for %i = 0 to 64 {
    %0 = affine.load %lo[%i] : memref<64xf32>
    affine.store %0, %out[%i] : memref<64xf32>
  }
  return
}

// CHECK:      la (alloca)
// CHECK:        replication: replicable (max 1 store(s) per loop body), copies 7
// CHECK:          8R+0W per iteration -> ceil(8/1)=8 port-cycles -> copies 7
// CHECK:        ram type: RAM_1WNR
func.func @independent(%a: memref<64x8xf32>, %out: memref<64xf32>) {
  %lo = memref.alloca() {hls.preserve, polygeist.varname = "lo"} : memref<64xf32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<64x8xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 8 {
      %0 = affine.load %a[%i, %j] : memref<64x8xf32>
      affine.store %0, %la[%i, %j] : memref<64x8xf32>
    }
  }
  affine.for %i = 0 to 64 {
    %0 = affine.load %la[%i, 0] : memref<64x8xf32>
    %1 = affine.load %la[%i, 1] : memref<64x8xf32>
    %2 = affine.load %la[%i, 2] : memref<64x8xf32>
    %3 = affine.load %la[%i, 3] : memref<64x8xf32>
    %4 = affine.load %la[%i, 4] : memref<64x8xf32>
    %5 = affine.load %la[%i, 5] : memref<64x8xf32>
    %6 = affine.load %la[%i, 6] : memref<64x8xf32>
    %7 = affine.load %la[%i, 7] : memref<64x8xf32>
    %8 = arith.addf %0, %1 : f32
    %9 = arith.addf %2, %3 : f32
    %10 = arith.addf %4, %5 : f32
    %11 = arith.addf %6, %7 : f32
    %12 = arith.addf %8, %9 : f32
    %13 = arith.addf %10, %11 : f32
    %14 = arith.addf %12, %13 : f32
    affine.store %14, %lo[%i] : memref<64xf32>
  }
  affine.for %i = 0 to 64 {
    %0 = affine.load %lo[%i] : memref<64xf32>
    affine.store %0, %out[%i] : memref<64xf32>
  }
  return
}

// PROMOTE-LABEL: func.func @promoted
// PROMOTE:       %[[ACC:.*]] = memref.alloca() {{.*}}"acc"
// PROMOTE-COUNT-8: affine.load %[[ACC]][
// PROMOTE:       affine.for %{{.*}} = 0 to 64 iter_args
// PROMOTE-NOT:     affine.load %[[ACC]][
// PROMOTE-NOT:     affine.store %{{.*}}, %[[ACC]][
// PROMOTE:       } {hls.pipeline = [{II = 0 : i32, source = "auto"}], hls.promoted_element_iter_args = array<i64: {{[0-9, ]+}}>}
// PROMOTE-COUNT-8: affine.store %{{.*}}, %[[ACC]][
func.func @promoted(%a: memref<64x8xf32>, %out: memref<8xf32>) {
  %acc = memref.alloca() {hls.preserve, polygeist.varname = "acc"} : memref<8xf32>
  %la = memref.alloca() {hls.preserve, polygeist.varname = "la"} : memref<64x8xf32>
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 8 {
      %0 = affine.load %a[%i, %j] : memref<64x8xf32>
      affine.store %0, %la[%i, %j] : memref<64x8xf32>
    }
  }
  affine.for %i = 0 to 64 {
    affine.for %j = 0 to 8 {
      %0 = affine.load %la[%i, %j] : memref<64x8xf32>
      %1 = affine.load %acc[%j] : memref<8xf32>
      %2 = arith.addf %1, %0 : f32
      affine.store %2, %acc[%j] : memref<8xf32>
    } {hls.unroll = [{factor = 0 : i32, skip_exit_check = false}]}
  }
  affine.for %j = 0 to 8 {
    %0 = affine.load %acc[%j] : memref<8xf32>
    affine.store %0, %out[%j] : memref<8xf32>
  }
  return
}
