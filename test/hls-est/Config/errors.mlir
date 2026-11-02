// Validation of the configuration: every error names the file (or the
// --config-set) and the key, the run stops with exit status 1 before the
// input is read, and all errors are reported, not just the first.

// RUN: not hls-est --hls-config=%S/Inputs/errors/unknown_key.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=UNKNOWN
// UNKNOWN: error: hls-config: {{.*}}unknown_key.json: tool.backend.memory_mapper.depth_roundig: unknown key (did you mean depth_rounding?)

// RUN: not hls-est --hls-config=%S/Inputs/errors/wrong_type.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=TYPE
// TYPE: error: hls-config: {{.*}}wrong_type.json: tool.hls.memory_architecture.replication.max_copies: wrong type: expected a non-negative integer

// RUN: not hls-est --hls-config=%S/Inputs/errors/out_of_range.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=RANGE
// RANGE: error: hls-config: {{.*}}out_of_range.json: tool.hls.memory_architecture.replication.max_copies: out of range: 0 < minimum 1

// RUN: not hls-est --hls-config=%S/Inputs/errors/bad_enum.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=ENUM
// ENUM: error: hls-config: {{.*}}bad_enum.json: tool.backend.memory_mapper.depth_rounding: 'ceil' is not one of pow2, exact

// RUN: not hls-est --hls-config=%S/Inputs/errors/no_version.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=VERSION
// VERSION: error: hls-config: {{.*}}no_version.json: version: missing (required; this hls-est reads version 1)

// RUN: not hls-est --hls-config=%S/Inputs/errors/bad_json.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=JSON
// JSON: error: hls-config: {{.*}}bad_json.json: not valid JSON: [2:24, byte=39]: Expected object key

// RUN: not hls-est --hls-config=%S/Inputs/errors/bands.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=BANDS
// BANDS: error: hls-config: {{.*}}bands.json: tool.backend.memory_mapper.depth_bands[1]: max_depth 512 is not above the previous band's 1024
// BANDS: error: hls-config: {{.*}}bands.json: tool.backend.memory_mapper.depth_bands: needs exactly one beyond band

// RUN: not hls-est --hls-config=%S/Inputs/errors/unknown_device.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=DEVICE
// DEVICE: error: hls-config: {{.*}}unknown_device.json: run.device: 'xilinx-unknown-part' is neither a compiled-in device (amd-xc7z020clg400-1) nor a .json path

// Cross-key checks of a device: an undeclared resource class, a geometry
// larger than the block, a port width that is no geometry's width.
// RUN: not hls-est --hls-config=%S/Inputs/errors/device_checks.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=CROSS
// CROSS-DAG: device.memories(ramb18).cost: names the undeclared resource class 'BRAM_36K'
// CROSS-DAG: device.memories(ramb18).geometries: 1024x36 holds more than the 18432 bits of one instance
// CROSS-DAG: device.memories(ramb18).port_configs(tdp).max_width: 18 is the width of no geometry

// --config-set: a bad enum value, a missing array element, a missing file.
// RUN: not hls-est --config-set tool.report.stdout_format=html %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=SET
// SET: error: hls-config: --config-set tool.report.stdout_format=html: tool.report.stdout_format: 'html' is not one of vitis-bram, per-class
// RUN: not hls-est --config-set tool.hls.implicit_buffers[3].enabled=false %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=INDEX
// INDEX: error: hls-config: --config-set tool.hls.implicit_buffers[3].enabled=false: tool.hls.implicit_buffers[3] does not exist
// RUN: not hls-est --hls-config=%S/Inputs/errors/does-not-exist.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=MISSING
// MISSING: error: hls-config: {{.*}}does-not-exist.json: cannot read: No such file or directory

// P2 review: values the loader once accepted silently.
// A reserved value that is not implemented.
// RUN: not hls-est --config-set tool.hls.pipeline_decision.flatten_across_calls=true %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=FLATTEN
// FLATTEN: error: hls-config: --config-set tool.hls.pipeline_decision.flatten_across_calls=true: tool.hls.pipeline_decision.flatten_across_calls: true is not implemented (reserved; only false, D-11)
// An unknown section names the file or --config-set that put it there.
// RUN: not hls-est --config-set tool.hls.optionz.pipeline_loops=3 %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=SECTSET
// SECTSET: error: hls-config: --config-set tool.hls.optionz.pipeline_loops=3: tool.hls.optionz: unknown key (did you mean options?)
// RUN: not hls-est --hls-config=%S/Inputs/errors/unknown_section.json %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=SECTFILE
// SECTFILE: error: hls-config: {{.*}}unknown_section.json: tool.hls.optionz: unknown key (did you mean options?)
// An operator class calyx-fixed does not read.
// RUN: not hls-est --config-set scheduling.timing.operator_latencies.fp_mul=3 %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=LATCLS
// LATCLS: error: hls-config: --config-set scheduling.timing.operator_latencies.fp_mul=3: scheduling.timing.operator_latencies.fp_mul: calyx-fixed has no operator class 'fp_mul' (did you mean fpmul?)
// A tier that is not one.
// RUN: not hls-est --config-set tool.backend.storage_selector.below=nosuchtier %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=BELOW
// BELOW: tool.backend.storage_selector.below: 'nosuchtier' is not one of registers, distributed, hard-small, block, large
// A priced port configuration no device memory has.
// RUN: not hls-est --config-set tool.hls.memory_architecture.priced_configs.wide=xyz %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=PRICED
// PRICED: tool.hls.memory_architecture.priced_configs.wide: 'xyz' is the port configuration of no device memory (device: sdp, sp, tdp)
// A plugin section no plugin key selects.
// RUN: not hls-est --config-set plugins.nosuch.x=1 %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=PSECT
// PSECT: error: hls-config: --config-set plugins.nosuch.x=1: plugins.nosuch: no plugin key selects a plugin named 'nosuch', so nothing reads this section
// An integer beyond 64 bits is out of range, not of the wrong type.
// RUN: not hls-est --config-set tool.hls.options.pipeline_loops=99999999999999999999 %S/Inputs/kernel.mlir 2>&1 | FileCheck %s --check-prefix=BIG
// BIG: tool.hls.options.pipeline_loops: out of range: 1e+20 exceeds the 64-bit integer range
