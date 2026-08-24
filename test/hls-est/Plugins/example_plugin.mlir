// The out-of-tree example plugin (tools/hls-est-plugins/example, built in
// tree as HlsEstExamplePlugin): a replacement modulo scheduler and a
// replacement delay model.

// asap-fixed-ii at its resource-minimum II gives the builtin's numbers on a
// bank read 8 times per iteration (II 1, RAM_1WNR with 7 copies); with its
// floor plugins.asap-fixed-ii.min_ii = 4 the loop runs at II 4 and the bank
// is one 2-port RAM.
// RUN: hls-est %S/../Config/Inputs/replicate.mlir --load-plugin=%hlsest_example_plugin --config-set scheduling.modulo.model=asap-fixed-ii --default-pipeline --bram-debug-json=%t.json -o /dev/null | FileCheck %s --check-prefix=ASAP
// RUN: FileCheck %s --check-prefix=ASAPJSON < %t.json
// ASAP: kind=RAM_1WNR  bram=14{{$}}
// ASAPJSON: "scheduler": "asap-fixed-ii",
// ASAPJSON: "modulo_scheduler"
// RUN: hls-est %S/../Config/Inputs/replicate.mlir --load-plugin=%hlsest_example_plugin --config-set scheduling.modulo.model=asap-fixed-ii --config-set plugins.asap-fixed-ii.min_ii=4 --default-pipeline -o /dev/null | FileCheck %s --check-prefix=FLOOR
// FLOOR: kind=RAM_2P  bram=2{{$}}
// RUN: not hls-est %S/../Config/Inputs/replicate.mlir --load-plugin=%hlsest_example_plugin --config-set scheduling.modulo.model=asap-fixed-ii --config-set plugins.asap-fixed-ii.min_ii=0 2>&1 | FileCheck %s --check-prefix=BADII
// The plugin's error names the --config-set that set the key (P2 review).
// BADII: error: hls-config: --config-set plugins.asap-fixed-ii.min_ii=0: plugins.asap-fixed-ii.min_ii: expected an integer >= 1

// clock-scaled: the calyx-fixed latencies scaled from 10 ns to run.clock_ns;
// at 5 ns the multiply takes 8 cycles and the store after it starts at stage 9.
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hlsest_example_plugin --config-set scheduling.timing.model=clock-scaled --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule | FileCheck %s --check-prefix=CLK10
// RUN: hls-est %S/Inputs/sched_kernel.mlir --load-plugin=%hlsest_example_plugin --config-set scheduling.timing.model=clock-scaled --config-set run.clock_ns=5 --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule | FileCheck %s --check-prefix=CLK5
// CLK10: loopschedule.pipeline.stage start = 5 {
// CLK10-NOT: loopschedule.pipeline.stage start = 9 {
// CLK5:  loopschedule.pipeline.stage start = 9 {
