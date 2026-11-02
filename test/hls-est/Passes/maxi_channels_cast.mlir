// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=ch --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=CH
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=cast --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=CAST
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=wide --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=WIDE
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=ch --config-set 'tool.hls.implicit_buffers[0].read_fifo.per_channel=false' --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=CHOFF
// RUN: hls-est %s --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=cast --config-set 'tool.hls.implicit_buffers[0].read_fifo.cast_load_width=false' --bram-debug -o /dev/null 2>&1 | FileCheck %s --check-prefix=CASTOFF

// m_axi read adapters (VITIS_NOTES N56): one read FIFO per distinct
// `channel=` of a bundle's reading ports, and the FIFO is as wide as the
// widest load through a pointer cast.
//
// @ch: kernel w9r7_mx_ch2 (~/hls-est-work/exp-src/w9r7p/mx_ch2.cpp), three
// 256-bit read ports of bundle g0 on channels 0, 1, 1: two FIFOs of
// 256 x 256 bits = 2 x 15 (Vitis 54 = 24 arrays + 30). A write-only port on
// its own channel adds no read FIFO.
// @cast: kernel w9r7_mx_cast512 (mx_cast512.cpp), a `short *` port read as
// `*reinterpret_cast<ap_uint<512> *>(&a[i])` (cgeist: memref2pointer +
// getelementptr + llvm.load i512): one FIFO 256 x 512 bits = 29 (Vitis 33 =
// 4 + 29; without max_widen_bitwidth also 29, mx_cast512nw).
// @wide: kernel w9r7i_mx_w2048 (~/hls-est-work/exp-src/w9r7i/mx_w2048.cpp),
// an ap_uint<2048> read port: AXI4 moves at most 1024 bits a beat, the read
// FIFO is 256 x 1024 = 57 (Vitis 57; corpus connor_talley lab2 3 x 57).

// CH: 2 FIFOs, one per channel (N56)
// CH: m_axi.adapter bundle=g0 {{.*}}bram=30 (read FIFO 2x256x256b -> 30
// CHOFF: m_axi.adapter bundle=g0 {{.*}}bram=15 (read FIFO 256x256b -> 15
// CAST: 512 bits wide: a load through a pointer cast (N56)
// CAST: m_axi.adapter bundle=g0 {{.*}}bram=29 (read FIFO 256x512b -> 29
// WIDE: m_axi.adapter bundle=g0 {{.*}}bram=57 (read FIFO 256x1024b -> 57
// CASTOFF: m_axi.adapter bundle=g0 {{.*}}bram=2 (read FIFO 256x32b -> 2

module {
  func.func @ch(%a: memref<256xi256> {hls.interface = [{bundle = "g0", channel = 0 : i32, mode = "m_axi", offset = "slave", port = "a"}]},
                %b: memref<256xi256> {hls.interface = [{bundle = "g0", channel = 1 : i32, mode = "m_axi", offset = "slave", port = "b"}]},
                %c: memref<256xi256> {hls.interface = [{bundle = "g0", channel = 1 : i32, mode = "m_axi", offset = "slave", port = "c"}]},
                %w: memref<256xi256> {hls.interface = [{bundle = "g0", channel = 2 : i32, mode = "m_axi", offset = "slave", port = "w"}]}) {
    affine.for %i = 0 to 256 {
      %x = affine.load %a[%i] : memref<256xi256>
      %y = affine.load %b[%i] : memref<256xi256>
      %z = affine.load %c[%i] : memref<256xi256>
      %s = arith.addi %x, %y : i256
      %t = arith.addi %s, %z : i256
      affine.store %t, %w[%i] : memref<256xi256>
    } {hls.pipeline = {ii = 1 : i32}}
    return
  }
  func.func @cast(%a: memref<4096xi16> {hls.interface = [{bundle = "g0", max_widen_bitwidth = 512 : i32, mode = "m_axi", offset = "slave", port = "a"}]},
                  %out: memref<128xi512> {hls.interface = [{bundle = "g1", mode = "m_axi", offset = "slave", port = "out"}]}) {
    %c2 = arith.constant 2 : index
    %p = "polygeist.memref2pointer"(%a) : (memref<4096xi16>) -> !llvm.ptr
    affine.for %i = 0 to 128 {
      %o = arith.muli %i, %c2 : index
      %o64 = arith.index_cast %o : index to i64
      %g = llvm.getelementptr %p[%o64] : (!llvm.ptr, i64) -> !llvm.ptr, i8
      %v = llvm.load %g : !llvm.ptr -> i512
      affine.store %v, %out[%i] : memref<128xi512>
    } {hls.pipeline = {ii = 1 : i32}}
    return
  }
  func.func @wide(%a: memref<64xi2048> {hls.interface = [{bundle = "g0", mode = "m_axi", offset = "slave", port = "a"}]},
                  %out: memref<64xi32> {hls.interface = [{bundle = "g1", mode = "m_axi", offset = "slave", port = "out"}]}) {
    affine.for %i = 0 to 64 {
      %v = affine.load %a[%i] : memref<64xi2048>
      %t = arith.trunci %v : i2048 to i32
      affine.store %t, %out[%i] : memref<64xi32>
    } {hls.pipeline = {ii = 1 : i32}}
    return
  }
}
