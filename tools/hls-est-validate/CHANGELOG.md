# hls-est vs. Vitis HLS matching — change log

Newest entry first. One entry per logical change, including changes that were
tried and reverted. Branch: `hls-est-vitis-match` in `~/circt`.

## 2026-10-09 — hls-est: --bram-debug / --bram-debug-json explanation mode; bank provenance attributes
- **Commit:** fa522b385
- **Files:** lib/Dialect/Resource/Passes/BRAMAnalysis.cpp, lib/Dialect/Resource/Passes/MemoryBankModified.cpp, lib/Dialect/Resource/Passes/InferVitisSplitArray.cpp, test/hls-est/Passes/bram_debug_json.mlir, test/hls-est/Passes/bram_debug_text.mlir, tools/hls-est-validate/check_debug_invariance.sh
- **What:** two global `llvm::cl` options (so they attach to any pipeline string): `--bram-debug` prints, to stderr after the normal report, one block per memref (id, name/varname, kind, loc, shape, element bits, words; status and exclusion reason; partition kind/factor/dim/source/bank index/count and the inference reason; every access with its scope, II, stage and store_enable flag; per-scope and combined port demand; the RAM type and why; the bank math: bits/BRAM, max width, config width, width tiles, depth/block, depth tiles, replication, blocks) and a summary sorted by BRAM; `--bram-debug-json=<path>` writes the same facts as JSON (`version`, `total_bram`, `functions`, `memrefs[]`, `summary[]`), which `compare.py` consumes. Memory banking now stamps every bank with `polygeist.varname`, `hls.preserve`, `hls.bank_of`, `hls.bank_index`, `hls.bank_count`, `hls.partition = {kind, factor, dim, source}` (the original pragma entry's fields; `source = "pragma"` when the entry has none) and `hls.partition_reason`; `infer-vitis-split-array` records `hls.partition_reason = "pipelined loop [lb..ub step s) @ loc: R reads/W writes per iteration, target II n, factor f (kind, dim d) (port-limited II a -> b)"`. No pass reads any of these attributes. Globals' accesses are not attributed (memref.global has no SSA result); the JSON says so in `ram_reason` instead of inventing data.
- **Why:** CLAUDE.md Step 3; the per-array JSON is the main debugging signal for Vitis mismatches (totals hide offsetting errors). Before this, banks created by `memory-banking-bram` had no attributes at all, so nothing could name them after the original alloca was erased.
- **Effect:** no estimate changes. `check_debug_invariance.sh` (every test/hls-est/Estimation/**/*.mlir, base pipeline, with vs. without the flags, stdout diffed): default pipeline (--affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis, 60 s timeout): 42 cases, 17 PASS, 0 FAIL, 25 ERR (hls-est timed out or failed identically in both runs: 19 timeouts, 4 x exit 1, 2 x abort); lit pipeline (--affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule --bram-analysis): 42 cases, 34 PASS, 0 FAIL, 8 ERR (1 timeout, 5 x exit 1, 2 x abort). No case produced a different stdout or a JSON total different from the report total. Lit `test/hls-est`: 45 tests, 17 passed (including the two new ones), 4 failed, 24 unresolved; the 28 non-passes are pre-existing: 24 Estimation inputs have no RUN line (unresolved) and 4 (forgebench/activation_op1, tiled_attn_p1, tiled_attn_p2, tiled_attn_module) pipe into FileCheck -check-prefix=CHECK-BRAM without defining any CHECK-BRAM: line.
- **Reverted?:** no

## 2026-10-09 — Vitis ground-truth configuration decided (throughput_driven=off)
- **Commit:** (harness, part of 3ad60fb79 and follow-ups)
- **Files:** tools/hls-est-validate/common.py (`EXTRA_HLS_CFG`), run_vitis.py
- **What:** every Vitis run uses `part=xc7z020clg400-1`, `clock=10ns`, `flow_target=vivado`, `syn.array_partition.throughput_driven=off`, Vitis 2025.1 (Windows install on A:, driven through cmd.exe from WSL).
- **Why:** CLAUDE.md asks for the part/clock of an existing script; Peter's `D:\HLS\circt\build-test\compilehlskernel.ps1` sets exactly these and produced the regression-gate numbers. Evidence that the setting matters: plain polybench/atax synthesizes to 13 BRAM with td=off (buff_A one 8-BRAM bank) but 68 with the 2025.1 default `auto` (buff_A split into 64 banks, log `[HLS 214-270] Inferring pragma 'array_partition type=complete dim=2' for array 'buff_A'`).
- **Effect:** defines the ground truth; no estimator change.
- **Reverted?:** no

## 2026-10-09 — hls-est: register DLTI and LLVM dialects; harness skeleton
- **Commit:** 3ad60fb79
- **Files:** tools/hls-est/main.cpp, tools/hls-est/CMakeLists.txt, tools/hls-est-validate/{common,designs,run_vitis,run_hlsest,vitis_parse,compare,make_sheet}.py
- **What:** hls-est now registers `mlir::DLTIDialect` and `mlir::LLVM::LLVMDialect`; the harness additionally strips the `module attributes {dlti.dl_spec = ..., llvm.data_layout = ...}` dictionary that cgeist (LLVM 18) emits, because the LLVM-23 MLIR parser in hls-est rejects the old `dlti` entry syntax (`expected a dense i64 elements attribute in the data layout entry`).
- **Why:** without this every fresh cgeist output failed to parse; the pre-generated `test/hls-est/Estimation/*.mlir` files had been hand-stripped.
- **Effect:** no estimate change (parser only). Enables the end-to-end harness.
- **Reverted?:** no

## 2026-10-09 — snapshot of Peter's uncommitted working tree
- **Commit:** e9da1aaf0
- **Files:** lib/Dialect/Resource/Passes/{AutoPipelineUnroll,BRAMAnalysis,InferVitisSplitArray,MemoryBankModified}.cpp, include/.../InferVitisSplitArray.h, test/hls-est/Estimation/* logs
- **What:** committed the pre-existing uncommitted state of `branch-hls` as the starting point of this branch so later diffs are clean. No code was changed.
- **Reverted?:** no
