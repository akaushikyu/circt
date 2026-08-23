// --default-pipeline runs the configuration's tool.pipeline (the harness's
// common.DEFAULT_PIPELINE); its report equals the one of the same passes
// given as flags.
// RUN: hls-est %S/Inputs/kernel.mlir --default-pipeline -o /dev/null > %t.default
// RUN: hls-est %S/Inputs/kernel.mlir --lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills --canonicalize --sccp --vitis-fold --dead-memory-elimination --affine-loop-normalize --auto-pipeline-unroll --narrow-ram-widths --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis -o /dev/null > %t.flags
// RUN: diff %t.default %t.flags
// RUN: FileCheck %s < %t.default

// CHECK: memref.alloca
// CHECK-NEXT: kind=RAM_2P  bram=2{{$}}
// CHECK: Total BRAM: 2{{$}}
