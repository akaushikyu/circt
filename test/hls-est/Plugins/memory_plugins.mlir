// The memory interfaces through plugins of the test plugin (TestPlugin.cpp):
// a storage selector that puts every bank in block RAM (test-all-block), a
// memory architecture with one port and no replication (test-single-port,
// label test-sp), a mapper that prices every bank at one block
// (test-one-block), no implicit buffers (test-zero), and a grouping that puts
// memrefs pairwise in one memory (test-merge-pairs).

// RUN: hls-est %S/../Config/Inputs/kernel.mlir --load-plugin=%hls_est_test_plugin --default-pipeline --config-set tool.backend.storage_selector.plugin=test-all-block --config-set tool.hls.memory_architecture.plugin=test-single-port --config-set tool.backend.memory_mapper.plugin=test-one-block --bram-debug-json=%t.json -o /dev/null | FileCheck %s --check-prefix=ONE
// ONE:      memref.alloca
// ONE-NEXT:   kind=test-sp  bram=1{{$}}
// ONE:      memref.alloca
// ONE-NEXT:   kind=test-sp  bram=1{{$}}
// ONE:      Total BRAM: 2{{$}}
// RUN: FileCheck %s --check-prefix=ONEJSON < %t.json
// ONEJSON:      "plugins": {
// ONEJSON:        "memory_architecture_policy": {
// ONEJSON-NEXT:     "name": "test-single-port",
// ONEJSON-NEXT:     "origin": "test"
// ONEJSON:        "memory_mapper": {
// ONEJSON-NEXT:     "name": "test-one-block",
// ONEJSON-NEXT:     "origin": "test"
// ONEJSON:        "storage_selector": {
// ONEJSON-NEXT:     "name": "test-all-block",

// One port per bank: the loop that reads `a` twice per iteration runs at II 2
// (the builtin vitis-auto policy gives the bank 17 slots: II 1).
// RUN: hls-est %S/../Config/Inputs/kernel.mlir --load-plugin=%hls_est_test_plugin --default-pipeline --config-set tool.hls.memory_architecture.plugin=test-single-port --bram-debug-json=%t.sp.json -o /dev/null
// RUN: FileCheck %s --check-prefix=II < %t.sp.json
// II:      "pipelines": [
// II:        "ii": 2,

// Two memrefs in one memory: the first is priced for both (1040 words), the
// second costs nothing.
// RUN: hls-est %S/../Config/Inputs/kernel.mlir --load-plugin=%hls_est_test_plugin --default-pipeline --config-set tool.hls.grouping.plugin=test-merge-pairs -o /dev/null | FileCheck %s --check-prefix=GROUP
// GROUP:      kind=RAM_2P  bram=4{{$}}
// GROUP-NEXT:   one memory for the group [a, s] (test-merge-pairs): 1040x32b = 4 BRAM_18K
// GROUP:      kind=RAM_1P  bram=0{{$}}
// GROUP-NEXT:   in the memory of the group [a, s] (test-merge-pairs), priced with its first member
// GROUP:      Total BRAM: 4{{$}}

// No implicit buffers: an m_axi port costs nothing.
// RUN: hls-est %s --load-plugin=%hls_est_test_plugin --default-pipeline -o /dev/null | FileCheck %s --check-prefix=MAXI
// RUN: hls-est %s --load-plugin=%hls_est_test_plugin --default-pipeline --config-set 'tool.hls.implicit_buffers[0].plugin=test-zero' -o /dev/null | FileCheck %s --check-prefix=NOMAXI
// MAXI:   m_axi.adapter bundle=gmem func=@top bram=2
// MAXI:   Total BRAM: 2{{$}}
// NOMAXI-NOT: m_axi.adapter
// NOMAXI: Total BRAM: 0{{$}}
module {
  func.func @top(%in: memref<1024xi32> {hls.interface = [{mode = "m_axi", port = "in", max_read_burst_length = 64 : i64}]},
                 %out: memref<1024xi32>) {
    affine.for %i = 0 to 1024 {
      %v = affine.load %in[%i] : memref<1024xi32>
      affine.store %v, %out[%i] : memref<1024xi32>
    }
    return
  }
}

// A dataflow ping-pong channel goes where the storage selector puts it, like
// any other bank (P2 review): the 16x32 channel of @top is distributed RAM
// under the default selector and one true-dual-port block memory under
// test-all-block.
// RUN: hls-est %S/../Passes/bram_dataflow_channels.mlir --load-plugin=%hls_est_test_plugin --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis=top=top --config-set tool.backend.storage_selector.plugin=test-all-block -o /dev/null | FileCheck %s --check-prefix=PIPO
// PIPO:      single memory of all 2 blocks: F(16x32) at x18 (true dual port, one port per side) = 2 (never replicated)
// PIPO:      Total BRAM: 34{{$}}
