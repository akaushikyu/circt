# hls-est vs. Vitis HLS matching — change log

Newest entry first. One entry per logical change, including changes that were
tried and reverted. Branch: `hls-est-vitis-match` in `~/circt`.

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
