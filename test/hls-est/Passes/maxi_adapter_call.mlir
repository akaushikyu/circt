// RUN: hls-est %s --affine-loop-normalize --convert-affine-to-loopschedule --bram-analysis --bram-maxi-adapters --bram-debug -o /dev/null > %t.out 2> %t.err
// RUN: FileCheck %s --input-file=%t.out
// RUN: FileCheck %s --input-file=%t.err --check-prefix=DBG

// --bram-maxi-adapters with an m_axi argument passed to a sub-function: the
// callee's accesses are the bundle's accesses. Vitis 2025.1, kernels
// mx_call_rw / mx_call_rw2 (~/hls-est-work/exp-src/t4fix; `rd` and `wr` kept
// as separate modules with `inline off`): mem3, only read inside `rd`, has
// the read FIFO (mem3_m_axi_U 2 BRAM); mem2, only written inside `wr`, costs
// 0 (no mem2 instance with BRAM), like the write-only dg_g_maxi_w. A callee
// without a body in the module is still assumed to read and write the port.

// CHECK-DAG: m_axi.adapter bundle=mem2 func=@top bram=0 (read FIFO 256x32b -> 0, write burst 16 -> 0)
// CHECK-DAG: m_axi.adapter bundle=mem3 func=@top bram=2 (read FIFO 256x32b -> 2, write burst 16 -> 0)
// CHECK-DAG: m_axi.adapter bundle=mem4 func=@ext_top bram=2 (read FIFO 256x32b -> 2, write burst 16 -> 0)

// DBG: m_axi bundle 'mem3' (m_axi_adapter) in @top @
// DBG: read FIFO: used
// DBG: write buffer: no store to the bundle
// DBG: note: an argument of the bundle is passed to a call; its accesses in the callee are counted
// DBG: m_axi bundle 'mem2' (m_axi_adapter) in @top @
// DBG: read FIFO: no load from the bundle
// DBG: write buffer: used
// DBG: note: an argument of the bundle is passed to a call; its accesses in the callee are counted
// DBG: m_axi bundle 'mem4' (m_axi_adapter) in @ext_top @
// DBG: note: an argument of the bundle is passed to a call without a body in the module; assumed read and written

module {
  func.func private @wr(%o: memref<512xi32>, %b: memref<512xi32>) {
    affine.for %i = 0 to 512 {
      %v = affine.load %b[511 - %i] : memref<512xi32>
      affine.store %v, %o[%i] : memref<512xi32>
    }
    return
  }
  func.func private @rd(%b: memref<512xi32>, %x: memref<512xi32>) {
    %c1 = arith.constant 1 : i32
    affine.for %i = 0 to 512 {
      %v = affine.load %x[%i] : memref<512xi32>
      %w = arith.addi %v, %c1 : i32
      affine.store %w, %b[%i] : memref<512xi32>
    }
    return
  }
  func.func @top(%in: memref<512xi32> {hls.interface = [{bundle = "mem3", mode = "m_axi", offset = "slave", port = "in"}]}, %out: memref<512xi32> {hls.interface = [{bundle = "mem2", mode = "m_axi", offset = "slave", port = "out"}]}) {
    %buf = memref.alloca() {polygeist.varname = "buf"} : memref<512xi32>
    func.call @rd(%buf, %in) : (memref<512xi32>, memref<512xi32>) -> ()
    func.call @wr(%out, %buf) : (memref<512xi32>, memref<512xi32>) -> ()
    return
  }
  func.func private @ext(memref<512xi32>)
  func.func @ext_top(%out: memref<512xi32> {hls.interface = [{bundle = "mem4", mode = "m_axi", offset = "slave", port = "out"}]}) {
    func.call @ext(%out) : (memref<512xi32>) -> ()
    return
  }
}
