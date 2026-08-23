// --list-plugins prints every registered implementation per interface; the
// builtins are the defaults of the Vitis profile.
// RUN: hls-est --list-plugins | FileCheck %s

// CHECK:      storage_selector:
// CHECK-NEXT:   vitis-bits-threshold [builtin]
// CHECK:      memory_architecture_policy:
// CHECK-NEXT:   vitis-auto [builtin]
// CHECK:      memory_mapper:
// CHECK-NEXT:   geometry-min [builtin]
// CHECK-NEXT:   vitis-aspect-min [builtin]
// CHECK-NEXT:   vitis-band7 [builtin]
// CHECK:      memory_grouping:
// CHECK-NEXT:   identity [builtin]
// CHECK:      implicit_buffer_model:
// CHECK-NEXT:   vitis-m_axi [builtin]
// CHECK:      pipeline_policy:
// CHECK-NEXT:   vitis-pipeline-loops [builtin]
// CHECK:      partition_policy:
// CHECK-NEXT:   vitis-td [builtin]
// CHECK:      fold_rule_set:
// CHECK-NEXT:   vitis-undef [builtin]
// CHECK-NEXT:   zero [builtin]
// CHECK:      operator_timing_model:
// CHECK-NEXT:   calyx-fixed [builtin]
// CHECK:      dependence_model:
// CHECK-NEXT:   cached-o1 [builtin]
// CHECK:      modulo_scheduler:
// CHECK-NEXT:   greedy [builtin]
// CHECK-NEXT:   greedy-simplex [builtin]
// CHECK-NEXT:   simplex [builtin]
// CHECK:      sequential_scheduler:
// CHECK-NEXT:   none [builtin]
// CHECK:      binder:
// CHECK-NEXT:   none [builtin]

// The debug JSON names the plugin used for each interface of --bram-analysis.
// RUN: hls-est %S/../Config/Inputs/kernel.mlir --default-pipeline --bram-debug-json=%t.json -o /dev/null
// RUN: FileCheck %s --check-prefix=JSON < %t.json
// JSON:      "plugins": {
// JSON-DAG:    "memory_architecture_policy": {
// JSON-DAG:    "memory_mapper": {
// JSON-DAG:      "name": "vitis-band7",
// JSON-DAG:      "origin": "builtin"
