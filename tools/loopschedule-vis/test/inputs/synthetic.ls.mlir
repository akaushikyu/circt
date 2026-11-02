// Hand-written loopschedule IR exercising parser corner cases: fused and
// callsite locations, #loc aliases defined before and after use, multi-result
// stages, pass-through registers (two hops), loop-carried values, an empty
// scf.if with an else region, an op without a location, and an unrecognized
// loopschedule op (which must produce a warning, not a crash).
// Expected dataflow is asserted in ../run_smoke.sh.
#loc1 = loc("synthetic.c":3:8)
#loc2 = loc("synthetic.c":5:15)
#loc3 = loc(fused[#loc2, "synthetic.c":5:20])
#loc4 = loc(callsite("synthetic.c":6:9 at "synthetic.c":1:1))
module {
  func.func @dot(%arg0: memref<16xf32> loc("synthetic.c":1:11), %arg1: memref<16xf32> loc("synthetic.c":1:24)) -> f32 {
    %c0 = arith.constant 0 : index loc(#loc1)
    %c16 = arith.constant 16 : index loc(#loc1)
    %c1 = arith.constant 1 : index loc(#loc1)
    %cst = arith.constant 0.000000e+00 : f32 loc(#loc1)
    %0 = loopschedule.pipeline II =  1 trip_count =  16 iter_args(%arg2 = %c0, %arg3 = %cst) : (index, f32) -> f32 {
      %1 = arith.cmpi ult, %arg2, %c16 : index loc(#loc1)
      loopschedule.register %1 : i1 loc(#loc1)
    } do {
      %1:3 = loopschedule.pipeline.stage start = 0 {
        %4 = memref.load %arg0[%arg2] : memref<16xf32> loc(#loc2)
        %5 = memref.load %arg1[%arg2] : memref<16xf32> loc(#loc2)
        %6 = arith.addi %arg2, %c1 : index loc(#loc1)
        loopschedule.register %4, %5, %6 : f32, f32, index loc(#loc1)
      } : f32, f32, index loc(#loc5)
      %2:2 = loopschedule.pipeline.stage start = 1 {
        %4 = arith.mulf %1#0, %1#1 : f32 loc(#loc3)
        %5 = arith.cmpi ult, %1#2, %c16 : index
        loopschedule.frobnicate %4 : f32 loc(#loc1)
        loopschedule.register %4, %1#2 : f32, index loc(#loc1)
      } : f32, index loc(#loc5)
      %3 = loopschedule.pipeline.stage start = 3 {
        %4 = arith.addf %arg3, %2#0 : f32 loc(#loc4)
        %5 = arith.muli %2#1, %c1 : index loc(#loc1)
        %6 = arith.cmpi slt, %5, %c16 : index loc(#loc1)
        scf.if %6 {
        } else {
        } loc(#loc1)
        loopschedule.register %4 : f32 loc(#loc1)
      } : f32 loc(#loc5)
      loopschedule.terminator iter_args(%1#2, %3), results(%3) : (index, f32) -> f32 loc(#loc5)
    } loc(#loc5)
    return %0 : f32 loc(#loc1)
  } loc(#loc6)
} loc(#loc)
#loc = loc("synthetic.c":0:0)
#loc5 = loc("synthetic.c":3:3)
#loc6 = loc("synthetic.c":1:1)
