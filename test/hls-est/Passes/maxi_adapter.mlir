// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis --bram-maxi-adapters --bram-debug -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG
// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=OFF

// --bram-maxi-adapters: every m_axi bundle of a public function's arguments
// (`hls.interface` entries with mode = "m_axi") gets the adapter instance
// `<bundle>_m_axi_U` Vitis adds (VITIS_NOTES.md N1a "Interfaces"; kernels
// ~/hls-est-work/exp-src/dead_globals/dg_g_maxi_*.cpp and
// ~/hls-est-work/exp-src/maxi/mx_*.cpp, reports under
// ~/hls-est-work/experiments/<kernel>/<hash>/report):
//   read FIFO, depth D = max_read_burst_length x num_read_outstanding
//   (default 16 x 16), bus W = max(32, element bits): D <= 32 -> 0;
//   D <= 1024 -> ceil(W/18); D <= 2048 -> ceil(W/9); D <= 4096 -> 8 (W = 32);
//   write buffer: 0 at max_write_burst_length 16, ceil(W/18) at 32 .. 256
//   (num_write_outstanding has no effect); read + write add up.
// Bundles without bundle= share "gmem". Expected per kernel (Vitis):
//   r 2, w 0, rw 2, r_o1 0, r_burst2 0, r_b64 2, r_b256 8, r_w64 4, w_b64 2,
//   r_d2048 4, rw_wb64 4, nobundle2 2; private functions have no interface.

// CHECK-DAG: m_axi.adapter bundle=mem1 func=@r bram=2 (read FIFO 256x32b -> 2, write burst 16 -> 0)
// CHECK-DAG: m_axi.adapter bundle=mem2 func=@w bram=0 (read FIFO 256x32b -> 0, write burst 16 -> 0)
// CHECK-DAG: m_axi.adapter bundle=mem1 func=@rw bram=2
// CHECK-DAG: m_axi.adapter bundle=mem1 func=@r_o1 bram=0 (read FIFO 16x32b -> 0
// CHECK-DAG: m_axi.adapter bundle=mem1 func=@r_burst2 bram=0 (read FIFO 2x32b -> 0
// CHECK-DAG: m_axi.adapter bundle=mem1 func=@r_b64 bram=2 (read FIFO 1024x32b -> 2
// CHECK-DAG: m_axi.adapter bundle=mem1 func=@r_b256 bram=8 (read FIFO 4096x32b -> 8
// CHECK-DAG: m_axi.adapter bundle=mem1 func=@r_w64 bram=4 (read FIFO 256x64b -> 4
// CHECK-DAG: m_axi.adapter bundle=mem2 func=@w_b64 bram=2 (read FIFO 256x32b -> 0, write burst 64 -> 2)
// CHECK-DAG: m_axi.adapter bundle=mem1 func=@r_d2048 bram=4 (read FIFO 2048x32b -> 4
// CHECK-DAG: m_axi.adapter bundle=mem1 func=@rw_wb64 bram=4 (read FIFO 256x32b -> 2, write burst 64 -> 2)
// CHECK-DAG: m_axi.adapter bundle=gmem func=@nobundle2 bram=2
// CHECK-NOT: func=@priv
// CHECK: Total BRAM: 30

// DBG: m_axi bundle 'mem1' (m_axi_adapter) in @r @
// DBG-NEXT: ports: in; bus width max(32, element bits) = 32
// DBG-NEXT: read FIFO: used, max_read_burst_length 16 x num_read_outstanding 16 = depth 256 -> 2 BRAM (depth > 32: BRAM FIFO, two ports (x18 bands of N8))
// DBG-NEXT: write buffer: no store to the bundle, max_write_burst_length 16 (num_write_outstanding 16 has no effect) -> 0 BRAM (no store: no write buffer cost)

// OFF-NOT: m_axi.adapter
// OFF: Total BRAM: 0

module {
  func.func @r(%in: memref<512xi32> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @w(%in: memref<512xi32>, %out: memref<512xi32> {hls.interface = [{bundle = "mem2", mode = "m_axi", offset = "slave", port = "out"}]}) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @rw(%in: memref<512xi32> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi32> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "out"}]}) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @r_o1(%in: memref<512xi32> {hls.interface = [{bundle = "mem1", mode = "m_axi", num_read_outstanding = 1 : i32, offset = "slave", port = "in"}]}, %out: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @r_burst2(%in: memref<512xi32> {hls.interface = [{bundle = "mem1", max_read_burst_length = 2 : i32, mode = "m_axi", num_read_outstanding = 1 : i32, offset = "slave", port = "in"}]}, %out: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @r_b64(%in: memref<512xi32> {hls.interface = [{bundle = "mem1", max_read_burst_length = 64 : i32, mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @r_b256(%in: memref<512xi32> {hls.interface = [{bundle = "mem1", max_read_burst_length = 256 : i32, mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @r_w64(%in: memref<512xi64> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi64>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi64>
      affine.store %v, %out[%i] : memref<512xi64>
    }
    return
  }
  func.func @w_b64(%in: memref<512xi32>, %out: memref<512xi32> {hls.interface = [{bundle = "mem2", max_write_burst_length = 64 : i32, mode = "m_axi", offset = "slave", port = "out"}]}) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @r_d2048(%in: memref<512xi32> {hls.interface = [{bundle = "mem1", max_read_burst_length = 128 : i32, mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @rw_wb64(%in: memref<512xi32> {hls.interface = [{bundle = "mem1", mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi32> {hls.interface = [{bundle = "mem1", max_write_burst_length = 64 : i32, mode = "m_axi", offset = "slave", port = "out"}]}) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func @nobundle2(%a: memref<512xi32> {hls.interface = [{mode = "m_axi", offset = "slave", port = "a"}]}, %b: memref<512xi32> {hls.interface = [{mode = "m_axi", offset = "slave", port = "b"}]}, %out: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %a[%i] : memref<512xi32>
      %w = affine.load %b[%i] : memref<512xi32>
      %s = arith.addi %v, %w : i32
      affine.store %s, %out[%i] : memref<512xi32>
    }
    return
  }
  func.func private @priv(%in: memref<512xi32> {hls.interface = [{bundle = "mem9", mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %in[%i] : memref<512xi32>
      affine.store %v, %out[%i] : memref<512xi32>
    }
    return
  }
}
