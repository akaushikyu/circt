// Precedence of the configuration sources: the compiled-in defaults, then
// the --hls-config files in order, then --config-set. --dump-effective-config
// prints the merged document to stderr with _source next to every key that
// differs from the defaults, and the run continues.
// RUN: hls-est --hls-config=%S/Inputs/clock5.json --config-set run.clock_ns=7 --dump-effective-config %S/Inputs/kernel.mlir -o /dev/null 2>&1 >/dev/null | FileCheck %s

// CHECK: "_generated_by": "hls-est --dump-effective-config",
// CHECK: "run": {
// CHECK-NEXT: "_source": {
// CHECK-NEXT: "clock_ns": "--config-set run.clock_ns=7"
// CHECK-NEXT: },
// CHECK-NEXT: "clock_ns": 7,
// CHECK: "options": {
// CHECK-NEXT: "_source": {
// CHECK-NEXT: "pipeline_loops": "{{.*}}clock5.json"
// CHECK: "pipeline_loops": 32

// The --config alias and a later file winning over an earlier one.
// RUN: hls-est --config=%S/Inputs/clock5.json --config-set run.clock_ns=8 --hls-config=%S/Inputs/clock5.json --dump-effective-config %S/Inputs/kernel.mlir -o /dev/null 2>&1 >/dev/null | FileCheck %s --check-prefix=ORDER
// ORDER: "clock_ns": "--config-set run.clock_ns=8"

// A free-form plugin section set key by key: the keys are owned by the
// document (they once pointed into a freed command-line copy) and the
// override names the assignment.
// RUN: hls-est --config-set plugins.some-plugin.depth=4 --config-set plugins.some-plugin.mode=fast --dump-effective-config %S/Inputs/kernel.mlir -o /dev/null 2>&1 >/dev/null | FileCheck %s --check-prefix=FREE
// FREE:      "plugins": {
// FREE-NEXT:   "_source": {
// FREE-NEXT:     "some-plugin": "--config-set plugins.some-plugin.
// FREE:        "some-plugin": {
// FREE-NEXT:     "depth": 4,
// FREE-NEXT:     "mode": "fast"
