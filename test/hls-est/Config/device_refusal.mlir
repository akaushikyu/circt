// A tool profile refuses a device it cannot price, before any pass runs, and
// names what the device lacks (design memo 1a rule 2, gap G1).

// Lattice Nexus EBR has the geometry of an AMD RAMB18 but no Vitis part
// library: the Vitis profile's vitis-band7 mapper refuses it (geometry alone
// is not accepted), and the profile's report class and block memory are
// missing too.
// RUN: not hls-est --config-set run.device=%S/Inputs/devices/lattice-lifcl-40.device.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=NEXUS
// NEXUS-DAG: error: hls-config: <defaults>: tool.report.primary_memory_class: 'BRAM_18K' is not a resource class of the device
// NEXUS-DAG: error: hls-config: tool.backend.storage_selector.block: device 'lattice-lifcl-40' has no memory 'ramb18'
// NEXUS-DAG: error: hls-config: tool.backend.memory_mapper: vitis-band7 cannot price device 'lattice-lifcl-40': the device has no tool_ids.vitis.library

// A block RAM with another geometry (20 Kbit, x5 ... x40) is refused even
// with the Vitis library string.
// RUN: not hls-est --config-set run.device=%S/Inputs/devices/lsram-like.device.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=LSRAM
// LSRAM: error: hls-config: tool.backend.memory_mapper: vitis-band7 cannot price device 'lsram-like': its block memory 'ramb18' has 20480 bits, the bands price 18432-bit RAMB18 blocks
// LSRAM-NOT: error

// An unknown plugin name is refused by the loader, with the registered names.
// RUN: not hls-est --config-set scheduling.modulo.model=nope %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=PLUGIN
// PLUGIN: error: hls-config: --config-set scheduling.modulo.model=nope: scheduling.modulo.model: no modulo_scheduler plugin named 'nope' is registered (registered: greedy, greedy-simplex, simplex)

// The clock is recorded and read by the call-depth model of the pipeline
// decision only; a kernel without calls in a pipelined loop keeps its report.
// RUN: hls-est %S/Inputs/kernel.mlir --default-pipeline -o /dev/null > %t.10ns
// RUN: hls-est %S/Inputs/kernel.mlir --default-pipeline --config-set run.clock_ns=5 -o /dev/null > %t.5ns
// RUN: diff %t.10ns %t.5ns
