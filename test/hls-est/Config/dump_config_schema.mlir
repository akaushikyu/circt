// --dump-config-schema lists every key, one per line, with its type, unit,
// default, range, description, inventory rows and readers
// (tools/hls-est-validate/make_config_doc.py reads it).
// RUN: hls-est --dump-config-schema | FileCheck %s

// CHECK: "_generated_by": "hls-est --dump-config-schema"
// CHECK: "keys": [
// CHECK: "default":10,{{.*}}"path":"run.clock_ns"
// CHECK: "path":"device.memories[].geometries[].width"{{.*}}"unit":"bits"
// CHECK: "default":16,{{.*}}"min":1,{{.*}}"path":"tool.hls.memory_architecture.replication.max_copies",{{.*}}"rows":"K-02"
// CHECK: "default":"vitis-band7","doc":{{.*}}"interface":"memory_mapper",{{.*}}"path":"tool.backend.memory_mapper.plugin"
// CHECK: "path":"scheduling.modulo.model"
// CHECK: "plugin_interfaces": ["storage_selector", {{.*}}, "binder"]
