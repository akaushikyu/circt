# Session log — every file changed, and what changed (2026-10-09)

Written at the hand-over from Fable 5.1 to Opus 5.5. Per-change detail with Vitis evidence and before/after numbers is in
`CHANGELOG.md`; Vitis rules in `VITIS_NOTES.md` (N1–N8); open problems in `OPEN_ISSUES.md` (O1–O11); decision memos in
`MEMOS.md`; the running report in `REPORT.md`. This file is the file-level index. The appendices at the end are generated
from git and list every file of every commit.

**Commit attribution from now on:** `Co-Authored-By: Claude Opus 5.5 <noreply@anthropic.com>` (earlier commits carry the
Fable 5.1 line; workflows launched before the switch still use it).

## 1. Summary by area (~/circt, branch `hls-est-vitis-match`)

### hls-est C++ (lib/, include/, tools/hls-est/)
| file | what changed | commit(s) |
|---|---|---|
| `tools/hls-est/main.cpp`, `tools/hls-est/CMakeLists.txt` | registered the DLTI and LLVM dialects (cgeist output parses) | 3ad60fb79 |
| `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp` | `--bram-debug` / `--bram-debug-json` (JSON v2); RAMB18 aspect-mode formula with power-of-two address depth; x36 only with one live port; RAM_1WNR replication (`analyzeReplication`); reads of merged/forwarded access attributes | fa522b385, 93dba77f4, 342b39dfc, 798e705e4 |
| `include/circt/Dialect/Resource/Interfaces/MemoryDS.h`, `lib/Dialect/Resource/Interfaces/MemoryInterface.cpp` | LUTRAM threshold `Words*Bits >= 1024` (was `>`); replication constants | 342b39dfc |
| `lib/Dialect/Resource/Passes/MemoryBankModified.cpp` | bank provenance attributes (`polygeist.varname`, `hls.bank_of/index/count`, `hls.partition`); canonicalize composed maps so constant indices give constant banks | fa522b385, 99ac05534 |
| `lib/Dialect/Resource/Passes/InferVitisSplitArray.cpp` | `hls.partition_reason`; invariance relative to flattened loops | fa522b385, 22d473858 |
| `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`, `include/circt/Conversion/Passes.td` | fast greedy modulo scheduler (`fast-threshold`, default 150), `cse`; in-pass invariant-load hoist (alias-aware); same-address load CSE (`cse-loads` on) and store forwarding (`forward-stores` off); unsupported ops leave a loop sequential instead of failing; flattened-loop awareness | 99ac05534, 97cf18a10, 342b39dfc, 798e705e4, 22d473858 |
| `lib/Dialect/Resource/Passes/MemrefBankClassification.cpp` + `.h` | 17-slot (replicable) vs 2-slot port model; replicability = at most one store per loop body | 342b39dfc, 798e705e4 |
| `lib/Analysis/DependenceAnalysis.cpp`, `include/circt/Analysis/DependenceAnalysis.h`, `lib/Dialect/Resource/Passes/CyclicSchedulingAnalysisModified.cpp` + `.h` | memoized dependence tests, constant-index pruning, correct `replaceOp` re-keying; analysis passed by reference | 99ac05534 |
| `include/circt/Conversion/Passes.h.inc` | deleted a stale checked-in generated header that shadowed the build's copy | 99ac05534 |
| `lib/Dialect/Resource/Passes/AutoPipelineUnroll.cpp` (rewritten), `include/circt/Dialect/Resource/Passes/LoopPragmas.h` (new) | Vitis automatic pipeline/unroll/flatten decision (`pipeline-loops=64`, per-path products, perfect-nest collapse, user pragmas, `hls.flattened_parents`) | 22d473858 (review fix in progress, uncommitted) |
| `test/hls-est/Passes/*.mlir` (≈30 new) | lit tests for debug mode, banking, fast scheduler, replication, LUTRAM, aspect modes, hoisting, CSE/forwarding, auto pipeline | per commit, see Appendix A |
| `test/hls-est/Estimation/polybench/{gemm,bicg}.mlir` | CHECK values updated to the T3 model (gemm 256 = Vitis) | 22d473858 |

### Harness and notes (tools/hls-est-validate/)
| file | what it is / what changed |
|---|---|
| `common.py` | paths, Vitis config (part, 10 ns, `throughput_driven=off`), default pipeline |
| `designs.py` | design catalogue from the HLSFactory `.test` files (787 designs) |
| `run_vitis.py` | cached, parallel Vitis 2025.1 runs via cmd.exe; `--td auto|off`; `--reparse`; timeout killer for both slash styles |
| `vitis_parse.py` | csynth.xml/rpt, memory/loop/instance tables, log message classes, BindNode names, partition-bank grouping by sibling rows, `parse_cache_dir` |
| `run_hlsest.py` | cgeist + hls-est per design; `--shim polygeist|scalar|exact`; strips cgeist's dlti attributes; always writes the debug JSON |
| `compare.py` | totals + per-array diff (by name via the debug JSON) |
| `make_sheet.py` | spreadsheet incl. `vitis td=auto` sheet |
| `experiment_pipeline.py` | ablation/reorder/option sweeps → `experiments/results.csv` |
| `vitis_adhoc.py` | one-kernel Vitis experiments (`~/hls-est-work/experiments/`) |
| `check_debug_invariance.sh`, `check_pipeline_unroll.py` | debug-mode invariance; T3 decision table vs Vitis logs |
| `regen_estimation_checks.py` | rewrites the RUN/CHECK headers of `test/hls-est/Estimation` (not run yet) |
| `shim/scalar/`, `shim/exact/` | header stand-ins (builtin widths; `_BitInt`/`_Float16`) |
| `CHANGELOG.md`, `VITIS_NOTES.md`, `OPEN_ISSUES.md`, `MEMOS.md`, `REPORT.md`, `SESSION_LOG.md` | notes |
| `baseline.xlsx`, `results/baseline/*.csv`, `results/.gitignore` | baseline before model changes |

## 2. Polygeist (/mnt/d/HLS, branch `hls-est-vitis-match`)
| commit | files | what |
|---|---|---|
| d279a433 | `tools/cgeist/Lib/clang-mlir.cc` | `_Float16`/`__bf16`/`_BitInt(N)` lowered to f16/bf16/iN |
| 8017846b | `clang-mlir.cc`, `clang-mlir.h`, `lib/polygeist/Passes/AffineCFG.cpp` | unsigned index casts (`index_castui`), compound-assignment widths, APInt constant folds, typedef signedness |
| e5b6bbc9 | `clang-mlir.cc`, `lib/polygeist/Passes/CanonicalizeFor.cpp` | unsigned float compound (`fptoui`), bool compound (`!= 0`), loops with zero-extended narrow counters raise to affine |

Binaries in `Polygeist/build/bin/`: `cgeist` (current), `cgeist.prev-8017846b`, `cgeist.prev-fix3v1`,
`cgeist.orig-hls-preserve-name` (never touch).

## 3. Work in flight at hand-over (background workflows; results arrive as notifications)
| workflow | what | state |
|---|---|---|
| wf_62456172-632 | T3 review fix → T4 (dead-memory elimination, integer folds, globals as allocas, m_axi cost, robustness) → T5 (td=off partition inference, opt-in) → T6 (priority 2: O3 + forward-stores) → T7 (priority 6: `index_castui`, O9 fallback, crashes, timeouts) → T8 (route A hls-est side: inliner, Vitis undef folds, attention end to end) | T3 fix running |
| wf_ed71d84a-f64 | route A cgeist side (opt-in `--scalar-wrapper-abi`, default off), `shim/exactclass` + `cgeist_flags`, bit-exactness, coverage | implementing |
| wf_453191fc-b80 | cgeist round 3: `+=` path, wrapping unsigned loops, unsigned bounds, mixed-sign counters | waits for `~/hls-est-work/flags/routeA.done` |
| wf_e91158f4-96e | priority 4 (N8 formula reconciliation vs `~/hls-llvm-project`) + priority 5 tools (`rtl_memories.py`, `align_arrays.py`, `vitis_trace.py`, `bind_portvec.py`) | running |

**Session-limit outage, 19:40–21:10.** Every agent of the four workflows stopped mid-step on the usage limit. At 21:15
they were stopped and resumed (completed steps replayed from cache). The interrupted steps were told that the
uncommitted edits in their files are their own partial work. The interrupted route-A attempt had installed a cgeist
with the wrapper lowering switched on by default; that binary is kept as `cgeist.routeA-partial-1938` and the round-2
binary was put back as `build/bin/cgeist`. Workflow prompts were updated to the new CLAUDE.md rules: no edits to
`DEFAULT_PIPELINE`, lit RUN pipelines or output-changing option defaults (proposals go to `MEMOS.md`); route A opt-in;
commit trailer Opus 5.5. Sequencing now uses flag files in `~/hls-est-work/flags/` instead of journal counts.

Still to do after the workflows: refresh `MEMOS.md` numbers, the formal pipeline sweep (`experiment_pipeline.py`),
`hls-est-results.xlsx`, lit cleanup with `regen_estimation_checks.py`, `REPORT.md`. (The `tiled_attn_module` 600→1321
bisect is done: no regression, a re-run without the top-selection prefix; O12, `pipeline_full` now recorded by `run_hlsest.py`.)
Regenerate the appendices below with `python3 update_session_log.py` after each batch of commits.

## Appendix A — every file changed in ~/circt (branch hls-est-vitis-match), per commit, oldest first

Generated by `update_session_log.py` at 2026-10-09 21:33 from `git log --reverse --name-status e9da1aaf0..HEAD` (e9da1aaf0 = snapshot of Peter's pre-existing uncommitted tree). A = added, M = modified, D = deleted. Large result JSONs are git-ignored.

### 3ad60fb79 hls-est: register DLTI/LLVM dialects; add hls-est-validate harness skeleton

- A `tools/hls-est-validate/common.py`
- A `tools/hls-est-validate/compare.py`
- A `tools/hls-est-validate/designs.py`
- A `tools/hls-est-validate/make_sheet.py`
- A `tools/hls-est-validate/run_hlsest.py`
- A `tools/hls-est-validate/run_vitis.py`
- A `tools/hls-est-validate/vitis_parse.py`
- M `tools/hls-est/CMakeLists.txt`
- M `tools/hls-est/main.cpp`

### d4285e5d3 hls-est-validate: td=off ground-truth config, scalar shim, ad-hoc Vitis runner, pipeline experiments, notes

- A `tools/hls-est-validate/CHANGELOG.md`
- A `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est-validate/common.py`
- A `tools/hls-est-validate/experiment_pipeline.py`
- M `tools/hls-est-validate/run_hlsest.py`
- A `tools/hls-est-validate/shim/scalar/README.md`
- A `tools/hls-est-validate/shim/scalar/ap_axi_sdata.h`
- A `tools/hls-est-validate/shim/scalar/ap_cint.h`
- A `tools/hls-est-validate/shim/scalar/ap_fixed.h`
- A `tools/hls-est-validate/shim/scalar/ap_int.h`
- A `tools/hls-est-validate/shim/scalar/hls_half.h`
- A `tools/hls-est-validate/shim/scalar/hls_math.h`
- A `tools/hls-est-validate/shim/scalar/hls_stream.h`
- A `tools/hls-est-validate/shim/scalar/hls_vector.h`
- A `tools/hls-est-validate/vitis_adhoc.py`
- M `tools/hls-est-validate/vitis_parse.py`

### 19b99a8cf hls-est-validate: scalar shim default; VITIS_NOTES: confirmed dead-array, pipeline/unroll, replication, aspect-ratio and LUTRAM rules

- M `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est-validate/experiment_pipeline.py`
- M `tools/hls-est-validate/run_hlsest.py`

### fa522b385 hls-est: add --bram-debug / --bram-debug-json explanation mode and bank provenance attributes

- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/InferVitisSplitArray.cpp`
- M `lib/Dialect/Resource/Passes/MemoryBankModified.cpp`
- A `test/hls-est/Passes/bram_debug_json.mlir`
- A `test/hls-est/Passes/bram_debug_text.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- A `tools/hls-est-validate/check_debug_invariance.sh`

### 7f1eb8500 VITIS_NOTES: partition pragmas, reshape, bind_storage and automatic partition rules; aspect depth rounding

- M `tools/hls-est-validate/VITIS_NOTES.md`

### 11ebf1e65 run_vitis: --td auto|off option (separate work dirs), timeout killer matches both slash styles

- M `tools/hls-est-validate/run_vitis.py`

### 93dba77f4 hls-est: debug mode review fixes

- M `include/circt/Dialect/Resource/Interfaces/MemoryDS.h`
- M `lib/Dialect/Resource/Interfaces/MemoryInterface.cpp`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/MemoryBankModified.cpp`
- A `test/hls-est/Passes/bram_debug_provenance.mlir`
- A `test/hls-est/Passes/bram_debug_status.mlir`
- M `test/hls-est/Passes/bram_debug_text.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`

### eff5526e5 hls-est-validate: baseline results (Vitis td=off ground truth vs hls-est before model changes)

- A `tools/hls-est-validate/baseline.xlsx`
- A `tools/hls-est-validate/results/.gitignore`
- A `tools/hls-est-validate/results/baseline/compare-base-scalar.csv`
- A `tools/hls-est-validate/results/baseline/compare-canonical-scalar.csv`

### bb4a3876f hls-est-validate: CHANGELOG entry for the debug mode review fixes (93dba77f4)

- M `tools/hls-est-validate/CHANGELOG.md`

### 99ac05534 hls-est: fold constant bank indices in banking; fast resource-bound scheduling for large bodies

- M `include/circt/Analysis/DependenceAnalysis.h`
- D `include/circt/Conversion/Passes.h.inc`
- M `include/circt/Conversion/Passes.td`
- M `include/circt/Dialect/Resource/Passes/CyclicSchedulingAnalysisModified.h`
- M `lib/Analysis/DependenceAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/CyclicSchedulingAnalysisModified.cpp`
- M `lib/Dialect/Resource/Passes/MemoryBankModified.cpp`
- A `test/hls-est/Passes/banking_constant_operand.mlir`
- A `test/hls-est/Passes/fast_schedule.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`

### d2a4d3a5c hls-est-validate: CHANGELOG precision for 99ac05534 (cse=false, exact-scheduler and diff_orders_module measurements)

- M `tools/hls-est-validate/CHANGELOG.md`

### 0110ede88 hls-est-validate: width-exact shim (f16/_BitInt) for cgeist

- A `tools/hls-est-validate/shim/exact/README.md`
- A `tools/hls-est-validate/shim/exact/ap_axi_sdata.h`
- A `tools/hls-est-validate/shim/exact/ap_cint.h`
- A `tools/hls-est-validate/shim/exact/ap_fixed.h`
- A `tools/hls-est-validate/shim/exact/ap_int.h`
- A `tools/hls-est-validate/shim/exact/hls_half.h`
- A `tools/hls-est-validate/shim/exact/hls_math.h`
- A `tools/hls-est-validate/shim/exact/hls_stream.h`
- A `tools/hls-est-validate/shim/exact/hls_vector.h`

### 97cf18a10 hls-est: T1 perf review fixes

- M `lib/Analysis/DependenceAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- A `test/hls-est/Passes/fast_schedule_recurrence.mlir`
- A `test/hls-est/Passes/memory_recurrence_xfail.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- A `tools/hls-est-validate/OPEN_ISSUES.md`

### 9deaaafde hls-est-validate: CHANGELOG hash for 97cf18a10 (T1 perf review fixes)

- M `tools/hls-est-validate/CHANGELOG.md`

### 342b39dfc hls-est: Vitis storage model (LUTRAM >= 1024, RAMB18 aspect modes / true-dual-port x18 cost, RAM_1WNR replication, 17-slot port model)

- M `include/circt/Conversion/Passes.td`
- M `include/circt/Dialect/Resource/Interfaces/MemoryDS.h`
- M `include/circt/Dialect/Resource/Passes/MemrefBankClassification.h`
- M `lib/Dialect/Resource/Interfaces/MemoryInterface.cpp`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/MemrefBankClassification.cpp`
- A `test/hls-est/Passes/aspect_modes.mlir`
- M `test/hls-est/Passes/bram_debug_json.mlir`
- M `test/hls-est/Passes/bram_debug_status.mlir`
- M `test/hls-est/Passes/bram_debug_text.mlir`
- M `test/hls-est/Passes/fast_schedule.mlir`
- A `test/hls-est/Passes/invariant_load_hoist.mlir`
- A `test/hls-est/Passes/lutram_threshold.mlir`
- A `test/hls-est/Passes/replication_1wnr.mlir`
- A `test/hls-est/Passes/replication_two_stores.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### e72edc03c hls-est-validate: CHANGELOG hash for 342b39dfc (Vitis storage model)

- M `tools/hls-est-validate/CHANGELOG.md`

### 29ed802b2 CHANGELOG: run_vitis --td option, timeout killer fix, runner-collision incident

- M `tools/hls-est-validate/CHANGELOG.md`

### 798e705e4 hls-est: T2 storage review fixes

- M `include/circt/Conversion/Passes.td`
- M `include/circt/Dialect/Resource/Passes/MemrefBankClassification.h`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/MemrefBankClassification.cpp`
- A `test/hls-est/Passes/access_cse.mlir`
- A `test/hls-est/Passes/access_forwarding.mlir`
- A `test/hls-est/Passes/invariant_load_alias.mlir`
- M `test/hls-est/Passes/lutram_threshold.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### 43ee17899 hls-est-validate: CHANGELOG hash for 798e705e4 (T2 storage review fixes)

- M `tools/hls-est-validate/CHANGELOG.md`

### 85f57d83d VITIS_NOTES: replication applies per partition bank (fu_part_rep)

- M `tools/hls-est-validate/VITIS_NOTES.md`

### 57627d6c8 make_sheet: add a vitis td=auto sheet (secondary ground truth vs td=off)

- M `tools/hls-est-validate/make_sheet.py`

### f6540e9b8 CHANGELOG: cgeist unsigned index casts, compound-assignment widths, APInt folds, typedef signedness (Polygeist 8017846b)

- M `tools/hls-est-validate/CHANGELOG.md`

### d1cc09130 run_hlsest: always write the per-memref debug JSON so compare.py matches arrays by name

- M `tools/hls-est-validate/run_hlsest.py`

### 6313d6de8 vitis_parse: group partition banks by sibling rows (owner module is unreliable); run_vitis --reparse

- M `tools/hls-est-validate/run_vitis.py`
- M `tools/hls-est-validate/vitis_parse.py`

### adfa8f797 hls-est-validate: Estimation lit-header regeneration script; report draft

- A `tools/hls-est-validate/REPORT.md`
- A `tools/hls-est-validate/regen_estimation_checks.py`

### d547c96dd REPORT: route A chosen for exact ap_fixed semantics

- M `tools/hls-est-validate/REPORT.md`

### 22d473858 hls-est: Vitis automatic pipeline/unroll/flatten decision (pipeline_loops=64)

- A `include/circt/Dialect/Resource/Passes/LoopPragmas.h`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/AutoPipelineUnroll.cpp`
- M `lib/Dialect/Resource/Passes/InferVitisSplitArray.cpp`
- M `test/hls-est/Estimation/polybench/bicg.mlir`
- M `test/hls-est/Estimation/polybench/gemm.mlir`
- A `test/hls-est/Passes/auto_pipeline_inner65_flattened.mlir`
- A `test/hls-est/Passes/auto_pipeline_inner_unrolled.mlir`
- A `test/hls-est/Passes/auto_pipeline_multilevel.mlir`
- A `test/hls-est/Passes/auto_pipeline_perfect_nest.mlir`
- A `test/hls-est/Passes/auto_pipeline_siblings.mlir`
- A `test/hls-est/Passes/auto_pipeline_threshold.mlir`
- A `test/hls-est/Passes/auto_pipeline_user_pragma.mlir`
- A `test/hls-est/Passes/flattened_parents_hoist.mlir`
- A `test/hls-est/Passes/replication_rec_ii.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- A `tools/hls-est-validate/check_pipeline_unroll.py`
- M `tools/hls-est-validate/experiment_pipeline.py`

### 815b755f4 hls-est-validate: CHANGELOG hash for 22d473858 (Vitis pipeline/unroll/flatten decision)

- M `tools/hls-est-validate/CHANGELOG.md`

### 80e536b44 hls-est-validate: CHANGELOG for Polygeist e5b6bbc9 (unsigned float compound, bool compound, zero-extended counters raise)

- M `tools/hls-est-validate/CHANGELOG.md`

### 5e17192bb hls-est-validate: decision memos for Peter (O2 split pass, O6 exact shim, frontend changes, formula defaults)

- A `tools/hls-est-validate/MEMOS.md`

### 2a665061a hls-est-validate: SESSION_LOG.md - every file changed this session, per area and per commit

- A `tools/hls-est-validate/SESSION_LOG.md`

### 55d9234f7 hls-est-validate: SESSION_LOG update (outage restart, new tracks T6-T8), update_session_log.py

- M `tools/hls-est-validate/SESSION_LOG.md`
- A `tools/hls-est-validate/update_session_log.py`

### c1f54089e hls-est-validate: OPEN_ISSUES O12 - tiled_attn_module 600->1321 is the omitted top-selection prefix, not a regression

- M `tools/hls-est-validate/OPEN_ISSUES.md`

## Appendix B — every file changed in Polygeist (/mnt/d/HLS, branch hls-est-vitis-match), per commit

### d279a433 cgeist: lower _Float16/__bf16 and _BitInt(N) scalars to f16/bf16/iN

- M `Polygeist/tools/cgeist/Lib/clang-mlir.cc`

### 8017846b cgeist: unsigned index casts, compound assignment widths, APInt constant folds, typedef signedness

- M `Polygeist/lib/polygeist/Passes/AffineCFG.cpp`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.cc`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.h`

### e5b6bbc9 cgeist: unsigned float compound back-conversion, bool compound, raise loops with zero-extended counters

- M `Polygeist/lib/polygeist/Passes/CanonicalizeFor.cpp`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.cc`

## Appendix C — uncommitted work at 2026-10-09 21:33 (owned by running agents unless stated)

~/circt:

- `M include/circt/Dialect/Resource/Passes/LoopPragmas.h`
- `M lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- `M lib/Dialect/Resource/Passes/AutoPipelineUnroll.cpp`
- `M lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- `M test/hls-est/Passes/auto_pipeline_inner65_flattened.mlir`
- `M test/hls-est/Passes/auto_pipeline_inner_unrolled.mlir`
- `M test/hls-est/Passes/auto_pipeline_multilevel.mlir`
- `M test/hls-est/Passes/auto_pipeline_perfect_nest.mlir`
- `M test/hls-est/Passes/auto_pipeline_siblings.mlir`
- `M test/hls-est/Passes/auto_pipeline_threshold.mlir`
- `M test/hls-est/Passes/auto_pipeline_user_pragma.mlir`
- `M tools/hls-est-validate/MEMOS.md`
- `M tools/hls-est-validate/OPEN_ISSUES.md`
- `M tools/hls-est-validate/REPORT.md`
- `M tools/hls-est-validate/SESSION_LOG.md`
- `M tools/hls-est-validate/VITIS_NOTES.md`
- `M tools/hls-est-validate/check_pipeline_unroll.py`
- `M tools/hls-est-validate/run_hlsest.py`

Polygeist:

- `M tools/cgeist/Lib/CGCall.cc`
- `M tools/cgeist/Lib/CGStmt.cc`
- `M tools/cgeist/Lib/clang-mlir.cc`
- `M tools/cgeist/Lib/clang-mlir.h`
