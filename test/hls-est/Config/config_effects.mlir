// Configuration keys take effect, and an explicit pass option beats them
// (design memo section 5).

// Replication: a bank read 8 times per cycle is RAM_1WNR with 7 copies; with
// max_copies = 2 it has 2 copies and the scheduler's pool is 2 * (2 - 1) + 1
// = 3 slots (II 3).
// RUN: hls-est %S/Inputs/replicate.mlir --default-pipeline -o /dev/null | FileCheck %s --check-prefix=REP16
// REP16: kind=RAM_1WNR  bram=14{{$}}
// REP16-NEXT: 1024x32b -> RAM_1WNR, 7 copies x 2 (x18/port) = 14 BRAM_18K
// RUN: hls-est %S/Inputs/replicate.mlir --default-pipeline --config-set tool.hls.memory_architecture.replication.max_copies=2 -o /dev/null | FileCheck %s --check-prefix=REP2
// REP2: kind=RAM_1WNR  bram=4{{$}}
// REP2-NEXT: 1024x32b -> RAM_1WNR, 2 copies x 2 (x18/port) = 4 BRAM_18K

// The block-RAM threshold: the 16 x 32 array (512 bits) becomes a BRAM at
// min_block_bits = 512.
// RUN: hls-est %S/Inputs/kernel.mlir --default-pipeline --config-set tool.backend.storage_selector.min_block_bits=512 -o /dev/null | FileCheck %s --check-prefix=MIN512
// MIN512: kind=RAM_2P  bram=2{{$}}
// MIN512: kind=RAM_1P  bram=1{{$}}
// MIN512-NEXT: 16x32b -> RAM_1P (x36/port) = 1 BRAM_18K
// MIN512: Total BRAM: 3{{$}}

// GVN of --convert-affine-to-loopschedule (a function pass, run on clones):
// tool.hls.middle_end.gvn_loads=false keeps both loads (RAM_2P); the pass
// option cse-loads=true given explicitly beats the file, with and without
// threading.
// RUN: hls-est %S/Inputs/gvn.mlir --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null | FileCheck %s --check-prefix=GVN
// RUN: hls-est %S/Inputs/gvn.mlir --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis --config-set tool.hls.middle_end.gvn_loads=false -o /dev/null | FileCheck %s --check-prefix=NOGVN
// RUN: hls-est %S/Inputs/gvn.mlir --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram '--convert-affine-to-loopschedule=cse-loads=true' --bram-analysis --config-set tool.hls.middle_end.gvn_loads=false -o /dev/null | FileCheck %s --check-prefix=GVN
// RUN: hls-est %S/Inputs/gvn.mlir --affine-loop-normalize --auto-pipeline-unroll --memory-banking-bram '--convert-affine-to-loopschedule=cse-loads=true' --bram-analysis --config-set tool.hls.middle_end.gvn_loads=false --mlir-disable-threading -o /dev/null | FileCheck %s --check-prefix=GVN
// GVN: kind=RAM_1P  bram=2{{$}}
// NOGVN: kind=RAM_2P  bram=2{{$}}

// The automatic pipeline decision: pipeline_loops = 0 turns it off (no loop
// is tagged hls.pipeline); the pass option beats the file.
// RUN: hls-est %S/Inputs/kernel.mlir --auto-pipeline-unroll --config-set tool.hls.options.pipeline_loops=0 | FileCheck %s --check-prefix=NOPIPE
// RUN: hls-est %S/Inputs/kernel.mlir '--auto-pipeline-unroll=pipeline-loops=64' --config-set tool.hls.options.pipeline_loops=0 | FileCheck %s --check-prefix=PIPE
// NOPIPE-NOT: hls.pipeline
// PIPE: hls.pipeline = [{II = 0 : i32, source = "auto"}]

// The bram-formula option beats tool.backend.memory_mapper.plugin.
// RUN: hls-est %S/Inputs/kernel.mlir --default-pipeline --config-set tool.backend.memory_mapper.plugin=vitis-aspect-min --bram-debug-json=%t.n6.json -o /dev/null
// RUN: FileCheck %s --check-prefix=N6 < %t.n6.json
// N6: "bram_formula": "n6"
