// The compiled-in configuration (device amd-xc7z020clg400-1, tool profile
// vitis-2025.1) as --dump-default-config prints it. The golden file changes
// only when a key is added or a default changes: regenerate it with
//   hls-est --dump-default-config > test/hls-est/Config/Inputs/default-config.json
// and review the diff (a moved default needs Peter's decision, MEMOS.md).
// RUN: hls-est --dump-default-config | diff %S/Inputs/default-config.json -

// The dump read back gives the same configuration hash as no file at all.
// RUN: hls-est --dump-default-config > %t.json
// RUN: hls-est --dump-effective-config %S/Inputs/kernel.mlir -o /dev/null 2>&1 | grep '"_hash"' > %t.nofile
// RUN: hls-est --hls-config=%t.json --dump-effective-config %S/Inputs/kernel.mlir -o /dev/null 2>&1 | grep '"_hash"' > %t.file
// RUN: diff %t.nofile %t.file
