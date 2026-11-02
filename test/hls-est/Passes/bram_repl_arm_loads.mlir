// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=relu --bram-debug-json=%t.json -o /dev/null | FileCheck %s
// RUN: FileCheck %s --input-file=%t.json --check-prefix=JSON
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram "--convert-affine-to-loopschedule=merge-if-else-accesses=false" --bram-analysis=top=relu -o /dev/null | FileCheck %s --check-prefix=OFF

// `if (y[i] < 0) y[i] = 0; else if (y[i] > 6) y[i] = 6;` reads y[i] once:
// the load in the else arm reads the address the load before the if
// already read, with nothing in between that may write it (Vitis GVN). The
// two stores lie in exclusive arms (one write port), so y is read once and
// written once per iteration at II 1: a 2-port RAM, not a RAM_1WNR (Vitis
// 2025.1 td=off, DSC_Acceleration optimized `reLU6_1` / `reLU6_2` on
// conv_out_buf: 32 banks of 1 BRAM_18K, no copies). With the merge off the
// second load stays: 2 reads + 1 write per iteration, 2 copies.

// CHECK: 1024x16b -> RAM_2P (x18/port) = 1 BRAM_18K
// CHECK: Total BRAM: 1
// JSON: "merged_loads": 1,
// OFF: RAM_1WNR, 2 copies
// OFF: Total BRAM: 2

func.func @relu(%in: memref<1024xi16>, %out: memref<1024xi16>) {
  %c0 = arith.constant 0 : i16
  %c6 = arith.constant 6 : i16
  %Y = memref.alloca() {hls.preserve, polygeist.varname = "Y"} : memref<1024xi16>
  affine.for %i = 0 to 1024 {
    %v = affine.load %in[%i] : memref<1024xi16>
    affine.store %v, %Y[%i] : memref<1024xi16>
  } {hls.pipeline = [{II = 1 : i32}]}
  affine.for %i = 0 to 1024 {
    %y = affine.load %Y[%i] : memref<1024xi16>
    %neg = arith.cmpi slt, %y, %c0 : i16
    scf.if %neg {
      affine.store %c0, %Y[%i] : memref<1024xi16>
    } else {
      %y2 = affine.load %Y[%i] : memref<1024xi16>
      %big = arith.cmpi sgt, %y2, %c6 : i16
      scf.if %big {
        affine.store %c6, %Y[%i] : memref<1024xi16>
      }
    }
  } {hls.pipeline = [{II = 1 : i32}]}
  affine.for %i = 0 to 1024 {
    %v = affine.load %Y[1023 - %i] : memref<1024xi16>
    affine.store %v, %out[%i] : memref<1024xi16>
  } {hls.pipeline = [{II = 1 : i32}]}
  return
}
