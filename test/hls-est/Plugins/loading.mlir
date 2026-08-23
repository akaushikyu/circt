// Loading plugins (hls-doc/plugins.md): --load-plugin registers the
// library's implementations, which --list-plugins shows with their origin; a
// configuration may name them wherever --hls-config stands on the command
// line (the configuration is validated after the whole command line is
// parsed); a library that registers a name already taken stops the run.

// RUN: hls-est --load-plugin=%hls_est_test_plugin --list-plugins | FileCheck %s --check-prefix=LIST
// LIST:      memory_mapper:
// LIST:        test-one-block [test] test: one block per bank
// LIST:        vitis-band7 [builtin]
// LIST:      modulo_scheduler:
// LIST:        test-fixed-ii [test]

// RUN: hls-est %S/../Config/Inputs/replicate.mlir --hls-config=%S/Inputs/fixed-ii.json --load-plugin=%hls_est_test_plugin --default-pipeline -o /dev/null | FileCheck %s --check-prefix=ORDER
// RUN: hls-est %S/../Config/Inputs/replicate.mlir --load-plugin=%hls_est_test_plugin --hls-config=%S/Inputs/fixed-ii.json --default-pipeline -o /dev/null | FileCheck %s --check-prefix=ORDER
// ORDER: kind=RAM_2P  bram=2{{$}}

// Without the library the name is unknown.
// RUN: not hls-est %S/../Config/Inputs/replicate.mlir --hls-config=%S/Inputs/fixed-ii.json -o /dev/null 2>&1 | FileCheck %s --check-prefix=UNKNOWN
// UNKNOWN: error: hls-config: {{.*}}fixed-ii.json: scheduling.modulo.model: no modulo_scheduler plugin named 'test-fixed-ii' is registered (registered: greedy, greedy-simplex, simplex)

// RUN: env HLS_EST_TEST_DUPLICATE=1 not hls-est --load-plugin=%hls_est_test_plugin --list-plugins 2>&1 | FileCheck %s --check-prefix=DUP
// DUP: error: hls-est plugin: a memory_mapper named 'vitis-band7' is already registered (by builtin); 'test' must choose another name

// RUN: not hls-est --load-plugin=%t.does-not-exist.so --list-plugins 2>&1 | FileCheck %s --check-prefix=MISSING
// MISSING: error: --load-plugin: {{.*}}does-not-exist.so:
