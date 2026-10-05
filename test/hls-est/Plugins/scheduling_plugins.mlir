// The scheduling interfaces through plugins of the test plugin
// (TestPlugin.cpp, design memo 8.7): each replaces one builtin.
// DEFINE: %{pipe} = --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule

// test-no-deps: no memory or iter_arg dependence (the pass still adds the
// structural edges), so the accumulation no longer has II 5 (its chained fadd latency; 4
// with N139's recurrence latencies, on in W9r18-impl, off by default since the W9 round 18
// review fixes).
// RUN: hls-est %S/Inputs/sched_kernel.mlir %{pipe} --bram-analysis --bram-debug-json=%t.deps.json -o /dev/null
// RUN: FileCheck %s --check-prefix=DEPS < %t.deps.json
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.dependences.model=test-no-deps %{pipe} --bram-analysis --bram-debug-json=%t.nodeps.json -o /dev/null
// RUN: FileCheck %s --check-prefix=NODEPS < %t.nodeps.json
// DEPS:      "pipelines": [
// DEPS:        "ii": 5,
// NODEPS:    "pipelines": [
// NODEPS-NOT:  "ii": 5,

// test-clocked-timing: a floating-point multiply takes ceil(20 ns / clock)
// cycles; at 5 ns the store after it starts two stages later than at 10 ns (the recurrence
// latencies of N139, which would replace the plugin's add latency on the accumulation, stay off:
// off by default since the W9 round 18 review fixes, pinned here anyway).
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.timing.model=test-clocked-timing --config-set scheduling.dependences.register_recurrence_latencies=false %{pipe} | FileCheck %s --check-prefix=CLK10
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.timing.model=test-clocked-timing --config-set run.clock_ns=5 --config-set scheduling.dependences.register_recurrence_latencies=false %{pipe} | FileCheck %s --check-prefix=CLK5
// CLK10: loopschedule.pipeline.stage start = 3 {
// CLK10-NOT: loopschedule.pipeline.stage start = 5 {
// CLK5:  loopschedule.pipeline.stage start = 5 {

// test-all-comb: every operation but the memory accesses is combinational:
// the accumulation runs at II 1.
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.timing.model=test-all-comb %{pipe} --bram-analysis --bram-debug-json=%t.comb.json -o /dev/null
// RUN: FileCheck %s --check-prefix=NODEPS < %t.comb.json

// test-fixed-ii: every loop at II 4; the 8 reads of `a` per iteration then
// need 2 port-cycles per cycle, a plain 2-port RAM instead of 7 copies; the
// scheduler is not a function of the problem alone, so no schedule is reused.
// RUN: hls-est %S/../Config/Inputs/replicate.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.modulo.model=test-fixed-ii --default-pipeline --bram-debug-json=%t.fixed.json --mlir-pass-statistics -o /dev/null 2>%t.stats | FileCheck %s --check-prefix=FIXED
// RUN: FileCheck %s --check-prefix=FIXEDJSON < %t.fixed.json
// RUN: FileCheck %s --check-prefix=STATS < %t.stats
// FIXED:      kind=RAM_2P  bram=2{{$}}
// FIXEDJSON:  "ii": 4,
// FIXEDJSON:  "scheduler": "test-fixed-ii",
// STATS:      0 schedules-reused

// test-seq-asap: the function body in one state; the three loads of `a`
// there are counted in that state (the builtin none leaves the scope to the
// stretch-pair rule: two loads share a state). The bank itself stays a
// 2-port RAM (vitis-auto spreads a replicable bank over its two ports).
// RUN: hls-est %S/Inputs/sched_kernel.mlir %{pipe} --bram-analysis --bram-debug-json=%t.pair.json -o /dev/null
// RUN: FileCheck %s --check-prefix=PAIR < %t.pair.json
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.sequential.model=test-seq-asap %{pipe} --bram-analysis --bram-debug-json=%t.state.json -o /dev/null
// RUN: FileCheck %s --check-prefix=STATE < %t.state.json
// PAIR:      "per_scope": [
// PAIR:      "same_state": "same state (independent, one straight-line stretch)
// PAIR-NEXT: "scope": "func",
// PAIR-NEXT: "scope_loc":
// PAIR-NEXT: "total": 2,
// STATE:     "per_scope": [
// STATE-NOT: "same_state"
// STATE:     "scope": "func",
// STATE-NEXT: "scope_loc":
// STATE-NEXT: "total": 3,
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.sequential.model=test-seq-asap %{pipe} | FileCheck %s --check-prefix=HLSSTATE
// HLSSTATE: hls.state = 0 : i64

// test-share-all with scheduling.emit_detail: one unit per operator class,
// written as hls.unit next to hls.op_timing; the BRAM numbers do not move.
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.binding.model=test-share-all --config-set scheduling.emit_detail=true %{pipe} | FileCheck %s --check-prefix=UNIT
// UNIT: hls.op_timing = {cls = "fpmul", latency = 4 : i64}
// UNIT-SAME: hls.unit =
// RUN: hls-est %S/Inputs/sched_kernel.mlir %{pipe} --bram-analysis -o /dev/null > %t.plain
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hls_est_test_plugin --config-set scheduling.binding.model=test-share-all --config-set scheduling.emit_detail=true %{pipe} --bram-analysis -o /dev/null > %t.bound
// RUN: diff %t.plain %t.bound
