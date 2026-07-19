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
| wf_62456172-632 | T3 fix → T4 → T5 → T6 → T7 → T8 (route A hls-est side: Vitis undef rules in `--vitis-fold`, inliner interface, attention end to end) | **done**: T8 90a14d498 + ec2c787a8, review fixes a752b67e5; attention_op_p1 = 73 = Vitis per array with exactclass + prefix B + adapters; no harness design changed by the fixes |
| wf_ed71d84a-f64 | route A cgeist side (opt-in `--scalar-wrapper-abi`), `shim/exactclass` + `cgeist_flags`, bit-exactness, coverage | **done**: Polygeist 8b07bf43 + review fixes 28236352; circt c733e425e, bfa8a17fe |
| wf_453191fc-b80 | cgeist round 3: `+=` path, wrapping unsigned loops, unsigned bounds, mixed-sign counters | **done**: Polygeist 8490cbbb; its verifier found a new wrong-code regression (narrow `-=`/`*=` promoted to non-wrapping affine) and two incomplete fixes → round 4 |
| wf_e91158f4-96e + wf_cde0098f-30a | priority 4 (N8 formula reconciliation) + priority 5 tools, then their review fixes | **done**: 3a0c04cc8, b93c11751, dbb6b9550, c85766872; memo M4 |
| wf_05612499-391 | cgeist round 4: AffineCFG no longer promotes narrow integer arithmetic that can wrap, second-counter shortcut, cast chains through inlining, loop exit values, float compound rounding, div/rem sign check at every width | **done**: Polygeist 763b0046 + review fixes cbc105e0 (circt dbf091007, b60c020ee); recheck: no defects, harness byte-identical; open: unsigned 32-bit wrap assumption → memo M9 |
| wf_3050670d-893 | cgeist O23: no store-to-load forwarding across a loop that overwrites the location (lost accumulations in mult_op_module_dot, mult_op_p3, testing_impl); fix, verify, fix, recheck | running; binary kept private at /home/peter/tmp/o23/ - **install into build/bin/cgeist only after T8 has finished** (coordinator step) |
| wf_3a800524-b43 (W1) | Peter-approved defaults: W1a drop `--infer-vitis-split-array`, `--bram-seq-dual-port` on, band BRAM formula, `top=`; W1c exactclass harness shim (#8), dead-memory front end + m_axi adapters (#4), `float-loads-perfect` (#3), `forward-stores` if rule 4 holds (#5); W1b lit Estimation CHECK regeneration, full runs, workbook | waits for `fix-T8.done`; writes `w1.done`. (First launch wf_baed0f13-918 was derailed: its agents answered Peter's mid-turn question instead of working; stopped, nothing edited.) |
| wf_72c9c655-ac2 (W2) | hls:: math-function cost: Vitis experiments now, then a configuration file read by `--bram-analysis` (Peter: "punt them to a configuration file") | experiments running; implementation waits for `w1.done`; writes `w2.done` |
| wf_58a68378-45f (W3) | non-inlined functions: Vitis experiments now; cgeist honours `inline off` + opt-in `--hls-keep-invariant-loops` (waits for `o23.installed`); hls-est call support (waits for `w2.done`) | experiments running; writes `w3.done` |
| wf_a05ffb25-dfb (W5) | frontend: Vitis experiment on narrow counters vs wider runtime bounds (#14, now); after W3's cgeist step: signed arithmetic marked non-wrapping + AffineCFG trusts only that (#13), the #14 behaviour the evidence favours, Polygeist lit shim -> exactclass (#10) | experiment running; private binary; writes `w5.done` |
| wf_1620e0fa-ab0 | `tiled_attn_module` 600→1321 bisect | **done**: harness artefact, O12, memo M7, `pipeline_full` recorded |

**Session-limit outage, 19:40–21:10.** Every agent of the four workflows stopped mid-step on the usage limit. At 21:15
they were stopped and resumed (completed steps replayed from cache). The interrupted steps were told that the
uncommitted edits in their files are their own partial work. The interrupted route-A attempt had installed a cgeist
with the wrapper lowering switched on by default; that binary is kept as `cgeist.routeA-partial-1938` and the round-2
binary was put back as `build/bin/cgeist`. Workflow prompts were updated to the new CLAUDE.md rules: no edits to
`DEFAULT_PIPELINE`, lit RUN pipelines or output-changing option defaults (proposals go to `MEMOS.md`); route A opt-in;
commit trailer Opus 5.5. Sequencing now uses flag files in `~/hls-est-work/flags/` instead of journal counts.

**Login expiry, about 09:25 on 2026-10-10.** The expired login killed the round-4 fix and recheck agents and T7/T8 of the
main sequence (T7 mid-implementation; its uncommitted edits are in Appendix C). The fix agent's partial `AffineCFG.cpp`
edit was never installed (`bin/cgeist` is still the 763b0046 build from 07:10). After `/login`, both workflows were
resumed at 09:35 from their run IDs; the round-4 fix prompt got a note about its partial edit.

Still to do after the workflows: refresh `MEMOS.md` numbers, the formal pipeline sweep (`experiment_pipeline.py`),
`hls-est-results.xlsx`, lit cleanup with `regen_estimation_checks.py`, `REPORT.md`. (The `tiled_attn_module` 600→1321
bisect is done: no regression, a re-run without the top-selection prefix; O12, `pipeline_full` now recorded by `run_hlsest.py`.)
Regenerate the appendices below with `python3 update_session_log.py` after each batch of commits.

Coordinator steps pending: install the O23 cgeist after T8 and the O23 recheck, then touch `flags/o23.installed`; after W1, update CLAUDE.md's "Current default pipeline" section and Shims row; after W3 has installed its cgeist and `w5.done` exists, install W5's private cgeist (its report names it) and run a control harness; #15 (O15 range selects) waits for Peter's OK on memo M10; finally the formal pipeline sweep and REPORT.md.

## Appendix A — every file changed in ~/circt (branch hls-est-vitis-match), per commit, oldest first

Generated by `update_session_log.py` at 2026-10-10 16:25 from `git log --reverse --name-status e9da1aaf0..HEAD` (e9da1aaf0 = snapshot of Peter's pre-existing uncommitted tree). A = added, M = modified, D = deleted. Large result JSONs are git-ignored.

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

### fcbe95c73 hls-est-validate: record pipeline_full (top-selection prefix) per result; O12 closed as harness artefact; memo M7

- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/REPORT.md`
- M `tools/hls-est-validate/SESSION_LOG.md`
- M `tools/hls-est-validate/run_hlsest.py`

### 3a0c04cc8 hls-est-validate: open-source BRAM formula reconciliation (N8)

- M `tools/hls-est-validate/VITIS_NOTES.md`
- A `tools/hls-est-validate/bind_portvec.py`
- A `tools/hls-est-validate/formula_reconcile.py`
- A `tools/hls-est-validate/results/formula_reconcile.csv`
- A `tools/hls-est-validate/results/formula_reconcile_summary.csv`

### b93c11751 hls-est-validate: rtl_memories, align_arrays, vitis_trace visibility tools

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- A `tools/hls-est-validate/align_arrays.py`
- A `tools/hls-est-validate/rtl_memories.py`
- A `tools/hls-est-validate/vitis_trace.py`

### 6c272536e hls-est-validate: CHANGELOG hash for b93c11751 (visibility tools)

- M `tools/hls-est-validate/CHANGELOG.md`

### 547677b2d hls-est: T3 pipeline decision review fixes

- M `include/circt/Dialect/Resource/Passes/LoopPragmas.h`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/AutoPipelineUnroll.cpp`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- A `test/hls-est/Passes/auto_pipeline_float_loads.mlir`
- M `test/hls-est/Passes/auto_pipeline_inner65_flattened.mlir`
- M `test/hls-est/Passes/auto_pipeline_inner_unrolled.mlir`
- M `test/hls-est/Passes/auto_pipeline_multilevel.mlir`
- A `test/hls-est/Passes/auto_pipeline_partial_epilogue.mlir`
- M `test/hls-est/Passes/auto_pipeline_perfect_nest.mlir`
- A `test/hls-est/Passes/auto_pipeline_recursion.mlir`
- M `test/hls-est/Passes/auto_pipeline_siblings.mlir`
- M `test/hls-est/Passes/auto_pipeline_threshold.mlir`
- M `test/hls-est/Passes/auto_pipeline_user_pragma.mlir`
- A `test/hls-est/Passes/bram_debug_pipelines.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est-validate/check_pipeline_unroll.py`

### 0b0ee7407 hls-est-validate: CHANGELOG hash for 547677b2d (T3 pipeline decision review fixes)

- M `tools/hls-est-validate/CHANGELOG.md`

### aade7e60d MEMOS: M4 - BRAM formula defaults after the open-source reconciliation (N8)

- M `tools/hls-est-validate/MEMOS.md`

### 4703402c7 SESSION_LOG: regenerate after N8 / visibility tools / M4

- M `tools/hls-est-validate/SESSION_LOG.md`

### 321de8cc5 SESSION_LOG: regenerate after the T3 review fixes (547677b2d)

- M `tools/hls-est-validate/SESSION_LOG.md`

### dbb6b9550 hls-est-validate: N8 and visibility-tool review fixes

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est-validate/align_arrays.py`
- M `tools/hls-est-validate/formula_reconcile.py`
- M `tools/hls-est-validate/results/formula_reconcile.csv`
- M `tools/hls-est-validate/results/formula_reconcile_summary.csv`
- M `tools/hls-est-validate/rtl_memories.py`
- M `tools/hls-est-validate/vitis_trace.py`

### 033ab30f1 hls-est-validate: CHANGELOG hash for dbb6b9550 (N8 and visibility-tool review fixes)

- M `tools/hls-est-validate/CHANGELOG.md`

### c85766872 formula_reconcile: owner_ops counts distinct instructions; follow _r-renamed callees (re-check findings)

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est-validate/formula_reconcile.py`
- M `tools/hls-est-validate/results/formula_reconcile.csv`

### 6d7d92178 SESSION_LOG: regenerate after the N8/tools review fixes

- M `tools/hls-est-validate/SESSION_LOG.md`

### c733e425e hls-est-validate: exactclass shim (opt-in), shim-specific cgeist flags

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- A `tools/hls-est-validate/check_shim.py`
- M `tools/hls-est-validate/run_hlsest.py`
- A `tools/hls-est-validate/shim/exactclass/README.md`
- A `tools/hls-est-validate/shim/exactclass/ap_axi_sdata.h`
- A `tools/hls-est-validate/shim/exactclass/ap_cint.h`
- A `tools/hls-est-validate/shim/exactclass/ap_fixed.h`
- A `tools/hls-est-validate/shim/exactclass/ap_int.h`
- A `tools/hls-est-validate/shim/exactclass/cgeist_flags`
- A `tools/hls-est-validate/shim/exactclass/hls_half.h`
- A `tools/hls-est-validate/shim/exactclass/hls_math.h`
- A `tools/hls-est-validate/shim/exactclass/hls_stream.h`
- A `tools/hls-est-validate/shim/exactclass/hls_vector.h`

### 9aece8db8 SESSION_LOG: regenerate after route A (Polygeist 8b07bf43, circt c733e425e)

- M `tools/hls-est-validate/SESSION_LOG.md`

### 77e9ca1fa hls-est: dead-memory elimination, Vitis integer folds, globals as allocas, m_axi adapter cost, robustness

- M `include/circt/Dialect/Resource/Interfaces/MemoryDS.h`
- A `include/circt/Dialect/Resource/Passes/VitisCleanup.h`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/CMakeLists.txt`
- A `lib/Dialect/Resource/Passes/DeadMemoryElimination.cpp`
- M `lib/Dialect/Resource/Passes/MemrefBankClassification.cpp`
- A `lib/Dialect/Resource/Passes/PromoteGlobalsToAllocas.cpp`
- A `lib/Dialect/Resource/Passes/VitisFold.cpp`
- M `lib/Scheduling/SimplexSchedulers.cpp`
- A `test/hls-est/Passes/bram_attribute_globals.mlir`
- A `test/hls-est/Passes/dead_memory_elimination.mlir`
- A `test/hls-est/Passes/dme_attention_int.mlir`
- A `test/hls-est/Passes/maxi_adapter.mlir`
- A `test/hls-est/Passes/promote_globals.mlir`
- A `test/hls-est/Passes/robust_inputs.mlir`
- A `test/hls-est/Passes/simplex_fallback.mlir`
- A `test/hls-est/Passes/vitis_fold.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est-validate/common.py`
- M `tools/hls-est-validate/compare.py`
- M `tools/hls-est-validate/experiment_pipeline.py`
- M `tools/hls-est/CMakeLists.txt`
- M `tools/hls-est/main.cpp`

### 5d58127fb hls-est-validate: CHANGELOG hash for 77e9ca1fa (T4)

- M `tools/hls-est-validate/CHANGELOG.md`

### e06199200 SESSION_LOG: regenerate after T4 (77e9ca1fa)

- M `tools/hls-est-validate/SESSION_LOG.md`

### c6e42c3b3 hls-est: T4 review fixes

- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/DeadMemoryElimination.cpp`
- M `lib/Dialect/Resource/Passes/VitisFold.cpp`
- A `test/hls-est/Passes/bram_rom_initialised_global.mlir`
- M `test/hls-est/Passes/dme_attention_int.mlir`
- A `test/hls-est/Passes/dme_cfg.mlir`
- A `test/hls-est/Passes/maxi_adapter_call.mlir`
- M `test/hls-est/Passes/vitis_fold.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est-validate/common.py`
- M `tools/hls-est-validate/experiment_pipeline.py`
- M `tools/hls-est-validate/make_sheet.py`
- M `tools/hls-est-validate/run_hlsest.py`

### 7c5a8aae0 hls-est-validate: CHANGELOG hash for c6e42c3b3 (T4 review fixes)

- M `tools/hls-est-validate/CHANGELOG.md`

### bb6498998 infer-vitis-split-array: td=off automatic partitions (small arrays, constant-index dimensions)

- M `include/circt/Dialect/Resource/Interfaces/MemoryDS.h`
- M `include/circt/Dialect/Resource/Passes/MemrefBankClassification.h`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/InferVitisSplitArray.cpp`
- M `lib/Dialect/Resource/Passes/MemrefBankClassification.cpp`
- A `test/hls-est/Passes/split_array_registers_sched.mlir`
- A `test/hls-est/Passes/split_array_td_off.mlir`
- A `test/hls-est/Passes/split_array_td_off_bram.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### d26bad5c1 hls-est-validate: CHANGELOG hash for bb6498998 (td=off automatic partitions)

- M `tools/hls-est-validate/CHANGELOG.md`

### bfa8a17fe hls-est-validate: route A review fixes (exactclass shim, check_shim_cgeist)

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est-validate/check_shim.py`
- A `tools/hls-est-validate/check_shim_cgeist.py`
- M `tools/hls-est-validate/shim/exactclass/README.md`
- M `tools/hls-est-validate/shim/exactclass/ap_fixed.h`
- M `tools/hls-est-validate/shim/exactclass/ap_int.h`
- M `tools/hls-est-validate/shim/exactclass/hls_math.h`

### 6ad4853a5 SESSION_LOG: regenerate after T4 fixes, T5 and the route A review fixes

- M `tools/hls-est-validate/SESSION_LOG.md`

### 34626b713 hls-est-validate: CHANGELOG for Polygeist 8490cbbb (cgeist +=, wrapping narrow loops, unsigned bounds, mixed-sign counters)

- M `tools/hls-est-validate/CHANGELOG.md`

### 7c261b1d0 hls-est: T5 review fixes

- A `include/circt/Dialect/Resource/Passes/ConstantIndex.h`
- M `lib/Dialect/Resource/Passes/InferVitisSplitArray.cpp`
- M `lib/Dialect/Resource/Passes/MemoryBankModified.cpp`
- M `test/hls-est/Passes/banking_constant_operand.mlir`
- M `test/hls-est/Passes/split_array_td_off.mlir`
- A `test/hls-est/Passes/split_array_td_off_banking.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### 009ad6529 hls-est-validate: CHANGELOG hash for 7c261b1d0 (T5 review fixes)

- M `tools/hls-est-validate/CHANGELOG.md`

### f959c57dc SESSION_LOG: cgeist round 3 done, round 4 launched; workflow table refreshed

- M `tools/hls-est-validate/SESSION_LOG.md`

### 3ceac5ba4 hls-est: two ports per state in sequential scopes (--bram-seq-dual-port, opt-in); forward-stores re-measured (T6)

- M `include/circt/Conversion/Passes.td`
- M `include/circt/Dialect/Resource/Passes/LoopPragmas.h`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `test/hls-est/Passes/access_forwarding.mlir`
- A `test/hls-est/Passes/seq_scope_ports.mlir`
- A `test/hls-est/Passes/seq_scope_ports_ir.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- A `tools/hls-est-validate/sched_ports.py`

### 9389b61bc hls-est-validate: CHANGELOG hash for 3ceac5ba4 (T6 sequential-scope ports)

- M `tools/hls-est-validate/CHANGELOG.md`

### bf35f5e63 MEMOS: M2 addendum - per-dataset shim comparison after T4-T6 and route A

- M `tools/hls-est-validate/MEMOS.md`

### eabd8e1a6 MEMOS: M2 addendum - state the two designs that lose exactness with exactclass + M5

- M `tools/hls-est-validate/MEMOS.md`

### ecd9cac8a SESSION_LOG: regenerate after T5 fixes, T6 and the M2 addendum

- M `tools/hls-est-validate/SESSION_LOG.md`

### dbf091007 hls-est-validate: CHANGELOG for Polygeist 763b0046 (no wrapping-blind affine promotion of narrow arithmetic, counter shortcuts, cast chains, exit values, float compound)

- M `tools/hls-est-validate/CHANGELOG.md`

### 5756bd6fc hls-est: T6 O3/forward-stores review fixes

- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `test/hls-est/Passes/access_cse.mlir`
- M `test/hls-est/Passes/seq_scope_ports.mlir`
- M `test/hls-est/Passes/seq_scope_ports_ir.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### 8e65ec485 hls-est-validate: CHANGELOG hash for 5756bd6fc (T6 review fixes)

- M `tools/hls-est-validate/CHANGELOG.md`

### 850c65303 SESSION_LOG: T6 review fixes, cgeist round 4 landed

- M `tools/hls-est-validate/SESSION_LOG.md`

### ba4a61952 SESSION_LOG: login-expiry interruption and resume

- M `tools/hls-est-validate/SESSION_LOG.md`

### 8c203d07b SESSION_LOG: round 4 review fixes landed, T7 in progress

- M `tools/hls-est-validate/SESSION_LOG.md`

### b60c020ee hls-est-validate: CHANGELOG for Polygeist cbc105e0 (cgeist round 4 review fixes: narrow constants by representative, floordiv / mod only for non-negative dividends)

- M `tools/hls-est-validate/CHANGELOG.md`

### 07edef6c6 MEMOS: M9 - unsigned 32-bit wrap assumption in cgeist AffineCFG (round-4 open question)

- M `tools/hls-est-validate/MEMOS.md`

### 884f6966f SESSION_LOG: cgeist round 4 closed; memo M9

- M `tools/hls-est-validate/SESSION_LOG.md`

### c37a6a7b6 hls-est: accept arith.index_castui wherever arith.index_cast is (T7 a)

- M `lib/Conversion/AffineToLoopSchedule/AffineToLoopSchedule.cpp`
- M `lib/Dialect/LoopSchedule/LoopScheduleOps.cpp`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- A `test/hls-est/Passes/index_castui.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`

### 0d1ba9953 hls-est: name each pipeline's scheduler in --bram-debug; O9 asserts (T7 b)

- M `include/circt/Dialect/Resource/Passes/LoopPragmas.h`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Scheduling/SimplexSchedulers.cpp`
- M `test/hls-est/Passes/bram_debug_pipelines.mlir`
- M `test/hls-est/Passes/simplex_fallback.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`

### 6538b104d hls-est: pipeline stages up to a late terminator (mult_op_p3 abort, T7 c)

- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- A `test/hls-est/Passes/pipeline_yield_late.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`

### 843459412 hls-est: memory dependence analysis only inside innermost loops (T7 d1)

- M `include/circt/Analysis/DependenceAnalysis.h`
- M `lib/Analysis/DependenceAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `lib/Dialect/Resource/Passes/CyclicSchedulingAnalysisModified.cpp`
- A `test/hls-est/Passes/dependence_scope.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`

### 500079055 hls-est: solve identical modulo scheduling problems once (T7 d2)

- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- A `test/hls-est/Passes/schedule_reuse.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`

### bf614722f hls-est: sparse simplex pivots; the 9 user-unroll timeouts finish (T7 d3)

- M `lib/Scheduling/SimplexSchedulers.cpp`
- M `tools/hls-est-validate/CHANGELOG.md`

### 957b1bd22 hls-est-validate: OPEN_ISSUES O22 (soda in cgeist under scalar/exact shims); CHANGELOG hashes for T7

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`

### 98642477c hls-est-validate: CGEIST_BIN override for the frontend binary

- M `tools/hls-est-validate/common.py`

### ba8c03445 SESSION_LOG: T7 done, cgeist O23 fix launched (private binary until T8 finishes)

- M `tools/hls-est-validate/SESSION_LOG.md`

### 02844a4d6 cgeist: no store-to-load forwarding across intervening writes (O23)

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`

### 90a14d498 hls-est: Vitis undef rules in --vitis-fold, llvm inliner interface; route A end to end (T8)

- M `include/circt/Dialect/Resource/Passes/VitisCleanup.h`
- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/VitisFold.cpp`
- M `test/hls-est/Passes/dme_attention_int.mlir`
- M `test/hls-est/Passes/vitis_fold.mlir`
- A `test/hls-est/Passes/vitis_fold_undef.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`
- M `tools/hls-est/CMakeLists.txt`
- M `tools/hls-est/main.cpp`

### 26de5df12 hls-est-validate: CHANGELOG hash for T8 (90a14d498)

- M `tools/hls-est-validate/CHANGELOG.md`

### ec2c787a8 hls-est: T8 self-review fixes in --vitis-fold

- M `lib/Dialect/Resource/Passes/VitisFold.cpp`
- M `test/hls-est/Passes/vitis_fold_undef.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`

### e7092c35a hls-est-validate: CHANGELOG hash for the T8 self-review fixes (ec2c787a8)

- M `tools/hls-est-validate/CHANGELOG.md`

### 7fb817046 hls-est-validate: one workbook (hls-est-results.xlsx) with ground truth and predictions; runs record the cgeist binary

- M `tools/hls-est-validate/common.py`
- A `tools/hls-est-validate/hls-est-results.xlsx`
- M `tools/hls-est-validate/make_sheet.py`
- M `tools/hls-est-validate/run_hlsest.py`

### 2ac74c794 MEMOS: decisions recorded 2026-10-10 (Peter's answers)

- M `tools/hls-est-validate/MEMOS.md`

### df5c31271 SESSION_LOG: W1-W3 launched for Peter's decisions

- M `tools/hls-est-validate/SESSION_LOG.md`

### 80139b366 MEMOS: decisions #8/#10 approved (exactclass), #3-#5 unblocked; gates restored in CLAUDE.md

- M `tools/hls-est-validate/MEMOS.md`

### a0370765a SESSION_LOG: W1 relaunched with the exactclass decisions; coordinator steps

- M `tools/hls-est-validate/SESSION_LOG.md`

### 34289e775 hls-est-validate: VITIS_NOTES N14 non-inlined functions; O5/O10 Vitis evidence (W3-exp)

- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### a752b67e5 hls-est: T8 route A hls-est side review fixes

- M `lib/Dialect/Resource/Passes/DeadMemoryElimination.cpp`
- M `lib/Dialect/Resource/Passes/VitisFold.cpp`
- M `test/hls-est/Passes/vitis_fold_undef.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### f5be2a668 hls-est-validate: CHANGELOG hash for the T8 review fixes (a752b67e5)

- M `tools/hls-est-validate/CHANGELOG.md`

### e12ea00da SESSION_LOG: T3-T8 workflow complete

- M `tools/hls-est-validate/SESSION_LOG.md`

### 2e8f04992 hls-est-validate: workbook marks the 12 designs without Vitis ground truth as excluded, with the reason

- M `tools/hls-est-validate/hls-est-results.xlsx`
- M `tools/hls-est-validate/make_sheet.py`

### 008ee6246 MEMOS: decisions #13 #14 #15 #17; M10 write-up on assignable range selects (O15)

- M `tools/hls-est-validate/MEMOS.md`

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

### 8b07bf43 cgeist: opt-in lowering of scalar-wrapper classes to their scalar (--scalar-wrapper-abi)

- M `Polygeist/tools/cgeist/Lib/CGCall.cc`
- M `Polygeist/tools/cgeist/Lib/CGStmt.cc`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.cc`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.h`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/Inputs/mini_fixed.h`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/attention_ctrl.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/attention_mirror.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/builtin_bit_cast.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_chain.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_ctor.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_global.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_not.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_off.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_sizeof.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_type.cpp`

### 28236352 cgeist: route A review fixes

- M `Polygeist/lib/polygeist/Passes/CanonicalizeFor.cpp`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.cc`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.h`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/wide-int-sub-const.c`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_derived.cpp`
- M `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_not.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_static_local.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/wrapper/wrapper_valueinit.cpp`

### 8490cbbb cgeist: += through the compound path, no raising of wrapping unsigned loops, unsigned bounds, mixed-sign counters

- M `Polygeist/lib/polygeist/Passes/CanonicalizeFor.cpp`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.cc`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/narrow-counter-wrap.c`
- M `Polygeist/tools/cgeist/Test/Verification/fscanf.c`

### 763b0046 cgeist: no wrapping-blind affine promotion of narrow integer arithmetic, counter shortcuts, cast chains, exit values, float compound

- M `Polygeist/lib/polygeist/Passes/AffineCFG.cpp`
- M `Polygeist/lib/polygeist/Passes/CanonicalizeFor.cpp`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.cc`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/counter-exit-value.c`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/float-compound-double.c`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/narrow-arith-wrap.c`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/narrow-cast-chain.c`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/narrow-counter-shared-start.c`
- A `Polygeist/tools/cgeist/Test/Verification/float-compound-assign.c`
- A `Polygeist/tools/cgeist/Test/Verification/loop-exit-value.c`

### cbc105e0 cgeist: round 4 review fixes

- M `Polygeist/lib/polygeist/Passes/AffineCFG.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/divrem-negative-dividend.c`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/narrow-const-representative.c`

### 18a550dd cgeist: no store-to-load forwarding across intervening writes (O23)

- M `Polygeist/include/polygeist/Passes/Passes.h`
- A `Polygeist/lib/polygeist/Passes/AffineScalRep.cpp`
- M `Polygeist/lib/polygeist/Passes/CMakeLists.txt`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/store-forward-loop-carried.c`
- A `Polygeist/tools/cgeist/Test/Verification/store-forward-loop.c`
- M `Polygeist/tools/cgeist/driver.cc`

## Appendix C — uncommitted work at 2026-10-10 16:25 (owned by running agents unless stated)

~/circt:

- `M lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- `M test/hls-est/Estimation/Claude.md`
- `M test/hls-est/Estimation/run_all.sh`
- `M test/hls-est/Passes/dependence_scope.mlir`
- `M test/hls-est/Passes/index_castui.mlir`
- `M test/hls-est/Passes/pipeline_yield_late.mlir`
- `M test/hls-est/Passes/seq_scope_ports.mlir`
- `M test/hls-est/Passes/seq_scope_ports_ir.mlir`
- `M tools/hls-est-validate/SESSION_LOG.md`
- `M tools/hls-est-validate/check_debug_invariance.sh`
- `M tools/hls-est-validate/check_pipeline_unroll.py`
- `M tools/hls-est-validate/common.py`
- `M tools/hls-est-validate/experiment_pipeline.py`

Polygeist:

- `M lib/polygeist/Passes/AffineScalRep.cpp`
- `M tools/cgeist/Test/HLS/regressions/store-forward-loop-carried.c`
