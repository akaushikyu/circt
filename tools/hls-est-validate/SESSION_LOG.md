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
| wf_3050670d-893 | cgeist O23: no store-to-load forwarding across a loop that overwrites the location; fix, verify, fix, recheck | **done and installed** 18:11 (Polygeist 18a550dd + c70ba2b0; recheck: no defects); `flags/o23.installed` set; control run in OPEN_ISSUES O23 |
| wf_3a800524-b43 (W1) | Peter-approved defaults. W1a (landed + review fixes): drop `--infer-vitis-split-array` 919792784, `--bram-seq-dual-port` on 98e86b070, band BRAM formula 51b9a6434, `top=` 433f07113. W1c (in progress): exactclass harness default shim + cgeist md5 in the MLIR cache key b345b36b2 (#8), dead-memory front end in the default pipeline + m_axi adapters on fcf9a59b2 (#4), `float-loads-perfect` on 5b9418cb8 (#3), `forward-stores` under rule 4 (#5) next; then W1c review/fix, W1b (lit CHECK regeneration, full runs, workbook) | running (task w78m5npei): W1a and W1c landed with review fixes (W1c review: no defects); W1b (lit CHECK regeneration, workbook) running on Opus; writes `w1.done` |
| wf_bdcba361-69a (W2) | hls:: math-function cost: Vitis experiments (done: N16 fde45f14f, `math_costs.json` 30e2933f9, 45 entries; each core instance has a fixed BRAM cost, instances follow the call structure), then `--bram-analysis` reads the file | experiment and its review done; implementation running on Opus (task wtfqs7bh4); writes `w2.done` |
| wf_58a68378-45f (W3) | non-inlined functions: Vitis experiments (done: VITIS_NOTES N14, 34289e775); cgeist honours `inline off` + opt-in `--hls-keep-invariant-loops` (waits for `o23.installed`; writes `w3cgeist.done`); hls-est call support (waits for `w2.done`) | cgeist side done (`w3cgeist.done`); hls-est side re-running on Opus since 00:21 (task w2i9livtb) after its Fable agent ran out of credits; writes `w3.done` |
| wf_9be89a19-0be (W5) | frontend: narrow counters vs wider runtime bounds (#14; experiment done: N15 989279d91, recommends raising the loop and marking it so the pipeline decision does not collapse it early; no ground-truth design contains the case); then signed arithmetic marked non-wrapping (#13), Polygeist lit shim -> exactclass (#10) | experiment done; implementation re-running on Opus since 00:21 (task wzalafx2t) after Fable ran out of credits; private binary; writes `w5.done` |
| wf_7e144e09-d08 (W6) | #15 (Peter approved M10): exactclass proxy classes for assignable bit/range/concat selects + cgeist scalar replacement of proxy structs; one soda design and SkyNet first, then the 23 O15 designs; time-boxed | implementation on Opus since 00:25 (task wtaf1517m), waiting at its `w5.done` gate; private binary; writes `w6.done` |
| wf_2a1ab997-478 (P0) | generalization program, docs: `hls-doc/` index, harness guide, generated ground-truth/results pages, assistant memory, assumptions inventory (135 rows), config-vs-plugin design memo | **done** (eac94d95f, fb668bf4b, review fixes 014a3dbea); 15 design questions for Peter = decision #30 |
| wf_29146842-9ac (FB-diag) | forgebench gap diagnosis | **done** (a892b780c compare.py grouping, 0845d6dc0 report + N17 + O28, review fixes 697aae839): C1 callee array_partition lost at inlining, C2 globals unbanked (O4), C3 one copy per call site instead of one instance (O10/N14) explain 98% of forgebench |err|; C1 needs 2-D banking (O17 item 2) and W3's cgeist; `fbgap.done` set 23:05 |
| wf_5074c6a1-dc8 (W7) | forgebench fixes (Peter: go): replication overcount, never-accessed globals rule, ROM width narrowing, globals-promotion measurement + memo M11 (default change = Peter's decision), cgeist empty-module failures (after w6.done) | implementation on Opus since 00:25 (task w7mi9cj6b), waiting at its `w3.done` gate; writes `w7.done` |
| wf_7474f3cd-7d5 (W8) | HLSFactory_v2 catalogue: loader + sweep + cause classes (W8a, now); every design compilable by cgeist and ingested by hls-est (W8b, after w7.done + cgeist.final); ground truth for new designs, default catalogue switch, one cgeist lit test per design (W8c) | W8a done (5ff9321ce, c926618f5: 801 designs, cgeist 655, hls-est 318; review: every re-measured number reproduces); `fix:w8a` running (task w1r33ybq5); then the swap to `wf_w8_next.js` (verified: W8a's three calls replay from cache); writes `w8.done` |
| wf_3f96a4b0-371 (W9) | accuracy loop towards the goal band (exact or over-count <= 15%): measure, cluster out-of-band designs by cause, fix the largest cluster on Fable, review, fix, repeat (max 12 rounds, stop after 2 without gain); final `hls-doc/accuracy.md` | round-1 measurement running on Opus (task wawxilun9); writes `w9.done` |
| wf_2774bdf6-9f2 (W10) | decisions #33/#34: pin Vitis's automatic inlining rule with kernels (Opus), cgeist inlines like Vitis and merges conflicting array_partition pragmas the Vitis way, documented in `hls-doc/frontend-pragmas.md` (Fable); private cgeist | experiment done (N18, cfcbdbc9b); implementation on Opus since 00:21 (task wxpb85lzu), waiting at its `w6.done` gate; writes `w10.done` |
| wf_898379cf-367 (P1-P3; earlier launches wf_c3d16de8-975 and wf_21b4cfce-671 stopped before any work to add gates) | P1 every cgeist test mirrored as an hls-est lit test, covering every HLSFactory_v2 design + notes moved to `hls-doc/notes/`; P2 config file + plugins + docs; P3 refactor (readability) + speed, byte-identical | P1a (mirror tests) running on Opus (task wq17u99je); later phases wait for their gates |
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

**Derailed agents, 2026-10-10 15:30-17:00.** Peter asked mid-turn whether Vitis really ran. Agents of the workflows launched in that turn (the first W1 run, W2, W3) answered him in their reports, and every later agent that received such a report in its prompt answered too instead of working: all six W3 steps after the experiment returned without doing their task, and one of them touched `flags/w3.done`. Nothing was edited, committed or installed. Fix: `w3.done` removed; every workflow prompt now says that Peter's messages are for the coordinator and that answers to his question in quoted reports are to be ignored; W3 resumed (experiment cached), W2 and W5 relaunched, W5's gate moved from W3's journal to the new flag `w3cgeist.done`. Side effect: several derailed agents re-ran designs and kernels through Vitis from scratch (their reports list them: e.g. bicg, attention_op_p1, viterbi, gesummv, syrk, histogram); every re-run they report matched the cached result exactly.

**Model switch 2026-10-10 17:45.** Peter moved the session from Opus 5.5 to Fable 5.1 (new account). Commits by the coordinator from here on carry `Co-Authored-By: Claude Fable 5.1 <noreply@anthropic.com>`; agents launched earlier keep the Opus 5.5 trailer their prompts specify.

**Usage-limit outage, about 21:05-21:30 on 2026-10-10.** Every running agent died on the old account's limit. After the switch back to Opus 5.5 all eight workflows (W1, W2, W3, W5, W6, P0, FB-diag, W7) were resumed from their run IDs at 21:32, with completed steps from cache. Partial edits left by the dead agents: `AutoPipelineUnroll.cpp`, `LoopPragmas.h`, `test/hls-est/Passes/auto_pipeline_uncounted.mlir` (owner unclear, likely W5's #14 marker), the FB-diag's `compare.py` and `hls-doc/forgebench-gap.md`, and W3's Polygeist `HLSPragma.cc` + `inline-off-kept-call.c`. Agents of resumed workflows keep the Fable 5.1 trailer their prompts name (changing the prompts would discard their cached steps); new workflows (W8, P1-P3) use Opus 5.5.

**Model split, 22:35 on 2026-10-10 (Peter).** Each workflow step now names its model. Fable 5.1: W3 cgeist review/fix and the whole W3 hls-est side, W5, W6, W7, W8b with their reviews and fixes (if a Fable agent returns nothing, the step logs it and retries once on Opus). Opus 5.5: everything else (W1c fix, W1b, W2, W8a/W8c, P1-P3, the forgebench diagnosis fix) and the coordinating session. New hls-est order (gates): W1c fix (writes `w1c.done`) -> W3 hls-est side (waits for `w1c.done`) -> W7 (`fbgap.done`, `w3.done`) -> W8b (`w7.done`, `cgeist.final`; writes `w8b.done`) -> W2 (waits for `w8b.done`) -> W1b (waits for `w2.done`) -> W8c (waits for `w1.done`) -> P1-P3. Polygeist chain unchanged: W3 cgeist -> W5 -> W6 -> W8b. Finished steps were kept byte-identical so they replayed from cache; the restart re-ran the W1c fix, the W3 cgeist review, and the W5/W6/W7 implementations from the start (on their new models). W8 still runs its old script until its sweep step and its review/fix are cached; then the coordinator swaps in `scratchpad/wf_w8_next.js` (W8b on Fable, `w8b.done` flag, W8c gated on `w1.done`).

**Definition of done set by Peter (/goal, 22:45):** see the CLAUDE.md section of that name and MEMOS decision #32. Baseline: 58 of 89 compared designs in the goal band; 54 designs not compared yet. W8's pending script now requires a semantic-correctness check of every cgeist output.

**Peter's decisions, 23:20:** #33 merge pragmas the Vitis way (documented), #34 mimic Vitis's automatic inlining, #30 P2 recommendations accepted, #9 confirmed, and #36 DELEGATION: from now on the coordinator decides defaults and frontend behaviour by the criterion best-replicates-Vitis, with minimal supervision (recorded in MEMOS and CLAUDE.md). W1b now first moves `--vitis-fold` before `--canonicalize` (#35). W7 and W9 may change defaults when that replicates Vitis better. Incident: W3's hls-est step read the earlier 'prompt me to switch to Opus' as a stop and did no work; it was re-run with a model note in its prompt (the same note was added to the not-yet-run hard steps). Install order for cgeist builds: W3's (by W3's hls-est step if rule 4 holds), W5's, W6's, W10's; then touch `cgeist.final`.

**Limit handling, 2026-10-11 00:00 (Peter: never pause on an API limit).** Facts: Claude Code's local settings record no remaining-quota or reset time (reset times appear only in an agent's limit message; the live figure needs the OAuth token, which the coordinator does not read), and they report extra usage credits as unavailable (`out_of_credits`) - with credits, Claude Code itself continues past a plan limit. Mechanism now in every workflow script (takes effect at each workflow's next resume; prompts unchanged, so cached steps still replay): a step whose model's pool is exhausted re-runs once on the other model (Opus <-> Fable); if both fail, the workflow stops with 'limits: ...' instead of running later steps on empty input. The watcher reports deaths with the reset time parsed from the message; on such an event the coordinator schedules a resume of every stopped workflow for the reset time.

Coordinator steps pending (updated 2026-10-11 02:00): swap W8 to `wf_w8_next.js` (resumeFromRunId wf_7474f3cd-7d5) as soon as `fix:w8a` has a result; after tier 1 of the v2 Vitis run, re-run any tier-1 design that a sibling's timeout killed (tier 1 started before the killer fix 7f670e207); W8c merges `results/vitis-v2.json` into vitis.json; install the cgeist builds in order (W3's by W3's hls-est step if rule 4 holds; W5's after `w5.done`; W6's after `w6.done`; W10's after `w10.done`), each with a control harness (scalar and exactclass), then touch `flags/cgeist.final`; after `w1.done`, rewrite CLAUDE.md's "Current default pipeline" section and Shims row; decide W7's memo M11 under delegation #36 when W7 reports; after P1, update the note paths in CLAUDE.md; at 03:12 set `scratchpad/model.hard` back to `fable` (probe first); finally the formal pipeline sweep and REPORT.md. Done since the last update: O23 installed, `fbgap.done`, `p0.done`, the v2 Vitis run started (01:31).

## Appendix A — every file changed in ~/circt (branch hls-est-vitis-match), per commit, oldest first

Generated by `update_session_log.py` at 2026-10-11 01:58 from `git log --reverse --name-status e9da1aaf0..HEAD` (e9da1aaf0 = snapshot of Peter's pre-existing uncommitted tree). A = added, M = modified, D = deleted. Large result JSONs are git-ignored.

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

### 7a4029210 SESSION_LOG: W5 launched (decisions #13 #14 #10); coordinator steps updated

- M `tools/hls-est-validate/SESSION_LOG.md`

### a9a264b96 MEMOS: decision #15 approved (M10 plan)

- M `tools/hls-est-validate/MEMOS.md`

### ad990d32f SESSION_LOG: W6 (assignable range selects) launched

- M `tools/hls-est-validate/SESSION_LOG.md`

### 09740fb24 SESSION_LOG: derailed agents incident; W2/W5 relaunched, W3 resumed

- M `tools/hls-est-validate/SESSION_LOG.md`

### 047ee4670 SESSION_LOG: correct an uncounted number

- M `tools/hls-est-validate/SESSION_LOG.md`

### 919792784 hls-est-validate: drop --infer-vitis-split-array from the default pipeline (MEMOS M1, decision #1)

- M `test/hls-est/Estimation/Claude.md`
- M `test/hls-est/Estimation/run_all.sh`
- M `test/hls-est/Passes/dependence_scope.mlir`
- M `test/hls-est/Passes/index_castui.mlir`
- M `test/hls-est/Passes/pipeline_yield_late.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/check_debug_invariance.sh`
- M `tools/hls-est-validate/check_pipeline_unroll.py`
- M `tools/hls-est-validate/common.py`
- M `tools/hls-est-validate/experiment_pipeline.py`

### 98e86b070 hls-est: --bram-seq-dual-port on by default (MEMOS M6, decision #2)

- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `test/hls-est/Estimation/polybench/bicg.mlir`
- M `test/hls-est/Passes/seq_scope_ports.mlir`
- M `test/hls-est/Passes/seq_scope_ports_ir.mlir`
- M `test/hls-est/Passes/split_array_td_off_bram.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`

### 51b9a6434 hls-est: the 7-series depth-band formula is the default BRAM formula (MEMOS M4, decision #6)

- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `test/hls-est/Passes/aspect_modes.mlir`
- M `test/hls-est/Passes/bram_debug_json.mlir`
- A `test/hls-est/Passes/bram_formula_band.mlir`
- A `test/hls-est/Passes/bram_formula_rom_ir.mlir`
- M `test/hls-est/Passes/replication_1wnr.mlir`
- M `test/hls-est/Passes/replication_two_stores.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### 989279d91 VITIS_NOTES: N15 narrow loop counters against a wider runtime bound (W5, decision #14)

- M `tools/hls-est-validate/VITIS_NOTES.md`

### 433f07113 hls-est: --bram-analysis=top=<symbol> costs only what the top reaches (MEMOS M7, decision #7)

- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- A `test/hls-est/Passes/bram_top.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/run_hlsest.py`

### 88c81e070 hls-est-validate: W1a hash lines; MEMOS decisions #1, #2, #6, #7 implemented; notes

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### 30700ae50 hls-est-validate: CHANGELOG / OPEN_ISSUES for the cgeist O23 review fixes (Polygeist c70ba2b0)

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`

### fde45f14f hls-est-validate: VITIS_NOTES N16 hls:: math-function BRAM cost per core instance (W2-exp)

- M `tools/hls-est-validate/VITIS_NOTES.md`

### 30e2933f9 hls-est-validate: math_costs.json, the hls:: math-function cost table (W2-exp draft)

- A `tools/hls-est-validate/math_costs.json`

### 4a76b5f5c hls-est-validate: MEMOS decision #18 experiments done (N16, math_costs.json)

- M `tools/hls-est-validate/MEMOS.md`

### e36313850 SESSION_LOG: 17:50 check-in (W1a landed, W2/W5 experiments done, O23 fixes); model switch

- M `tools/hls-est-validate/SESSION_LOG.md`

### 0ae005759 hls-est: W1a defaults review fixes

- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `lib/Dialect/Resource/Passes/VitisFold.cpp`
- M `test/hls-est/Estimation/run_all.sh`
- M `test/hls-est/Passes/bram_formula_rom_ir.mlir`
- M `test/hls-est/Passes/bram_top.mlir`
- A `test/hls-est/Passes/bram_top_fold.mlir`
- A `test/hls-est/Passes/bram_top_scope.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/make_sheet.py`

### 78899ec78 hls-est-validate: W1a review fixes hash line; MEMOS #7 / O12 note the review fixes

- M `test/hls-est/Passes/bram_top_fold.mlir`
- M `test/hls-est/Passes/bram_top_scope.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`

### 187742aa2 cgeist O23 fix installed as build/bin/cgeist; O23 closed; control run recorded

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/SESSION_LOG.md`

### b345b36b2 hls-est-validate: exactclass is the harness default shim; MLIR cache key names the cgeist binary (MEMOS M2/M3, decision #8)

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/common.py`
- M `tools/hls-est-validate/experiment_pipeline.py`
- A `tools/hls-est-validate/results/baseline/hlsest-2026-10-10-exactclass-w1a-defaults.csv`
- M `tools/hls-est-validate/run_hlsest.py`

### fcf9a59b2 hls-est: dead-memory front end in the default pipeline; m_axi adapter cost on by default (MEMOS M5, decision #4)

- M `lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- M `test/hls-est/Passes/dependence_scope.mlir`
- M `test/hls-est/Passes/index_castui.mlir`
- M `test/hls-est/Passes/maxi_adapter.mlir`
- M `test/hls-est/Passes/pipeline_yield_late.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/check_debug_invariance.sh`
- M `tools/hls-est-validate/check_pipeline_unroll.py`
- M `tools/hls-est-validate/common.py`
- M `tools/hls-est-validate/experiment_pipeline.py`

### 5b9418cb8 hls-est: --auto-pipeline-unroll float-loads-perfect on by default (MEMOS M8, decision #3)

- M `lib/Dialect/Resource/Passes/AutoPipelineUnroll.cpp`
- M `test/hls-est/Passes/auto_pipeline_float_loads.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/experiment_pipeline.py`

### 560338e02 SESSION_LOG: 19:57 check-in (W1c decisions #8 #4 #3 landed)

- M `tools/hls-est-validate/SESSION_LOG.md`

### d4210fc36 hls-est: --convert-affine-to-loopschedule forward-stores on by default (MEMOS M6, decision #5)

- M `include/circt/Conversion/Passes.td`
- M `lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- M `test/hls-est/Passes/access_forwarding.mlir`
- M `test/hls-est/Passes/dme_attention_int.mlir`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/experiment_pipeline.py`

### 8257adddd hls-est-validate: memoize the cgeist md5 by path, size and mtime (W1c item 1 follow-up)

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/run_hlsest.py`

### bd678fa5c hls-est-validate: W1c hash lines; MEMOS decisions #8 #4 #3 #5 name their commits; final-defaults baseline CSV

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- A `tools/hls-est-validate/results/baseline/hlsest-2026-10-10-exactclass-w1c-defaults.csv`

### 2161982f5 Generalization program (config file, plugins, hls-doc, mirrored tests, refactor): decisions #23-#26, P0 and P1-P3 workflows launched

- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/SESSION_LOG.md`

### d57bc9c2c hls-doc: comparison.csv / comparison-summary.csv (current hls-est vs Vitis per design and per dataset; generator make_compare_csv.py)

- A `hls-doc/comparison-summary.csv`
- A `hls-doc/comparison.csv`
- A `tools/hls-est-validate/make_compare_csv.py`

### eac94d95f hls-doc: P0 documentation pages, make_hlsdoc.py, assistant memory migrated

- A `hls-doc/README.md`
- A `hls-doc/ground-truth-memories.md`
- A `hls-doc/ground-truth.md`
- A `hls-doc/harness.md`
- A `hls-doc/notes/README.md`
- A `hls-doc/notes/assistant-memory.md`
- A `hls-doc/results.md`
- A `tools/hls-est-validate/make_hlsdoc.py`

### fb668bf4b hls-doc: P0 inventory of hard-coded assumptions and the P2 configuration/plugin design memo

- A `hls-doc/design/assumptions-inventory.md`
- A `hls-doc/design/configuration-and-plugins.md`

### 7c5236c6b W7 forgebench fixes approved (decision #27); diagnosis and W7 workflows recorded; P1-P3 relaunched behind W7

- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/SESSION_LOG.md`

### 3e5a651c0 hls-doc: comparison CSVs now cover all 143 designs (the 31 outside the subset run with the same binary; none compared: hls-est or cgeist failures, or no Vitis result)

- M `hls-doc/comparison-summary.csv`
- M `hls-doc/comparison.csv`

### aa8c68eba HLSFactory_v2 catalogue (W8) and every-case lit tests (decisions #28 #29); outage and resume recorded

- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/SESSION_LOG.md`

### a892b780c hls-est-validate: compare.py groups Vitis memory rows by their own variable (align_arrays T1 fix ported)

- M `tools/hls-est-validate/compare.py`

### 014a3dbea hls-doc: P0 review fixes

- M `hls-doc/README.md`
- M `hls-doc/design/assumptions-inventory.md`
- M `hls-doc/design/configuration-and-plugins.md`
- M `hls-doc/harness.md`
- M `hls-doc/notes/README.md`

### e944cff14 P0 done; its 15 design questions recorded as decision #30 (waiting for Peter)

- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/SESSION_LOG.md`

### 0845d6dc0 hls-doc: forgebench-gap.md (FB-diag: why forgebench is off, which passes would fix it); VITIS_NOTES N17; OPEN_ISSUES O28

- A `hls-doc/forgebench-gap.md`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### 8863a3d63 hls-est-validate: W3-cgeist recorded (inline off honoured, --hls-keep-invariant-loops; Polygeist 62c40544 + 2ec1956c, not installed)

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`

### 38a0b7645 Model split (hard steps on Fable, rest on Opus) and reordered hls-est chain; decision #31

- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/SESSION_LOG.md`

### 85e43fedd hls-doc: goal-band metric (exact or over-count <= 15% of Vitis) in the comparison CSVs; baseline 58/89 compared designs in band

- M `hls-doc/comparison-summary.csv`
- M `hls-doc/comparison.csv`
- M `tools/hls-est-validate/make_compare_csv.py`

### 25060c328 hls-est: W1c exactclass defaults review fixes

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/common.py`
- M `tools/hls-est-validate/experiment_pipeline.py`
- M `tools/hls-est-validate/run_hlsest.py`
- M `tools/hls-est-validate/shim/exactclass/README.md`

### 65c03db9c Definition of done (Peter /goal): decision #32; W9 accuracy loop launched; W8/P1-P3 extended

- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/SESSION_LOG.md`

### 486676572 hls-doc: session-lessons skill (everything Claude got wrong on 2026-10-09/10 and the rule for each); linked from the hls-doc index

- M `hls-doc/README.md`
- A `hls-doc/skills/hls-est-session-lessons/SKILL.md`

### 697aae839 hls-doc: forgebench gap analysis review fixes

- M `hls-doc/forgebench-gap.md`
- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### e69c8e6cd Forgebench diagnosis done (fbgap.done); decision #33 waiting (merge conflicting partition pragmas)

- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/SESSION_LOG.md`

### dd4e5e766 MEMOS: Peter decisions 23:20 (#9 confirmed, #30 approved, #33 merge pragmas Vitis way, #34 mimic Vitis auto-inlining, #35 fold order, #36 delegation)

- M `tools/hls-est-validate/MEMOS.md`

### ba2a8fd71 SESSION_LOG: decisions of 23:20 incl. delegation; W10 launched; W3 hls-est step re-run

- M `tools/hls-est-validate/SESSION_LOG.md`

### fce323f95 hls-doc: results-table.tsv/.xlsx in Peter's sheet format (every design with Vitis ground truth that hls-est compiles; Diff = (Vitis - prediction) / Vitis)

- A `hls-doc/results-table.tsv`
- A `hls-doc/results-table.xlsx`
- A `tools/hls-est-validate/make_results_table.py`

### 1ccf07499 SESSION_LOG: limit handling (symmetric model fallback, clean stop, resume at reset)

- M `tools/hls-est-validate/SESSION_LOG.md`

### c87869bda SESSION_LOG: hard workflow steps switched to Opus until the usage reset (flag-file model switch)

- M `tools/hls-est-validate/SESSION_LOG.md`

### cfcbdbc9b hls-est-validate: VITIS_NOTES N18 Vitis automatic-inlining rule (W10-exp)

- M `tools/hls-est-validate/VITIS_NOTES.md`

### 70601cbd4 SESSION_LOG: Fable credits ran out; five workflows restarted on Opus via the model switch

- M `tools/hls-est-validate/SESSION_LOG.md`

### 5ff9321ce hls-est-validate: HLSFactory_v2 catalogue (--catalog v2), sweep of its 801 designs, hls-doc/hlsfactory-v2.md (W8a)

- M `hls-doc/README.md`
- M `hls-doc/harness.md`
- A `hls-doc/hlsfactory-v2.csv`
- A `hls-doc/hlsfactory-v2.md`
- M `tools/hls-est-validate/designs.py`
- A `tools/hls-est-validate/hlsfactory_v2.py`
- A `tools/hls-est-validate/make_hlsfactory_report.py`
- M `tools/hls-est-validate/run_hlsest.py`
- M `tools/hls-est-validate/run_vitis.py`
- A `tools/hls-est-validate/sweep_hlsfactory_v2.py`

### c926618f5 hls-est-validate: W8a recorded (HLSFactory_v2 catalogue and sweep); VITIS_NOTES N19 (C++14, __SYNTHESIS__); OPEN_ISSUES O30-O32

- M `tools/hls-est-validate/CHANGELOG.md`
- M `tools/hls-est-validate/MEMOS.md`
- M `tools/hls-est-validate/OPEN_ISSUES.md`
- M `tools/hls-est-validate/VITIS_NOTES.md`

### baa8eab9a run_vitis: per-design lock and merge-on-write summary, so concurrent runners cannot corrupt the cache

- M `tools/hls-est-validate/run_vitis.py`

### 000862f5e SESSION_LOG: v2 Vitis ground-truth run started; runner lock; W8c merges instead of re-running

- M `tools/hls-est-validate/SESSION_LOG.md`

### 7f670e207 run_vitis: review fixes for the runner lock; timeout killer kills only its own design; --dry-run writes nothing

- M `tools/hls-est-validate/results/.gitignore`
- M `tools/hls-est-validate/run_vitis.py`

### 87f9067cf CHANGELOG: run_vitis runner lock and its review fixes

- M `tools/hls-est-validate/CHANGELOG.md`

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

### c70ba2b0 cgeist: O23 review fixes

- M `Polygeist/lib/polygeist/Passes/AffineScalRep.cpp`
- M `Polygeist/tools/cgeist/Test/HLS/regressions/store-forward-loop-carried.c`

### 62c40544 cgeist: honour #pragma HLS inline off; opt-in --hls-keep-invariant-loops

- M `Polygeist/docs/hls-pragmas.md`
- M `Polygeist/include/polygeist/Passes/Passes.h`
- M `Polygeist/lib/polygeist/Passes/ParallelLICM.cpp`
- M `Polygeist/tools/cgeist/Lib/HLSPragma.cc`
- M `Polygeist/tools/cgeist/Lib/HLSPragma.h`
- M `Polygeist/tools/cgeist/Test/HLS/inline/inline.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/inline-off-kept-call.c`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/keep-invariant-loops.c`
- M `Polygeist/tools/cgeist/driver.cc`

### 2ec1956c cgeist: inline off: inline a call whose array argument does not fit the parameter shape

- M `Polygeist/docs/hls-pragmas.md`
- M `Polygeist/tools/cgeist/Lib/HLSPragma.cc`
- M `Polygeist/tools/cgeist/Test/HLS/regressions/inline-off-kept-call.c`

### b3a248a8 cgeist: mark C signed int arithmetic polygeist.nsw; AffineCFG proves every unmarked add / sub / mul (MEMOS #13, M9)

- M `Polygeist/include/polygeist/Passes/Passes.h`
- M `Polygeist/lib/polygeist/Passes/AffineCFG.cpp`
- M `Polygeist/lib/polygeist/Passes/CanonicalizeFor.cpp`
- M `Polygeist/lib/polygeist/Passes/PolygeistCanonicalize.cpp`
- M `Polygeist/tools/cgeist/Lib/clang-mlir.cc`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/signed-nowrap-mark.c`
- M `Polygeist/tools/cgeist/driver.cc`

### 5432780b cgeist: raise narrow-counter loops against runtime bounds by assuming termination; mark them hls.uncounted (MEMOS #14, VITIS_NOTES N15)

- M `Polygeist/include/polygeist/Passes/Passes.h`
- M `Polygeist/lib/polygeist/Passes/AffineCFG.cpp`
- M `Polygeist/lib/polygeist/Passes/CanonicalizeFor.cpp`
- M `Polygeist/lib/polygeist/Passes/RaiseToAffine.cpp`
- A `Polygeist/tools/cgeist/Test/HLS/regressions/narrow-counter-assume-termination.c`
- M `Polygeist/tools/cgeist/Test/HLS/regressions/narrow-counter-wrap.c`
- M `Polygeist/tools/cgeist/driver.cc`

## Appendix C — uncommitted work at 2026-10-11 01:58 (owned by running agents unless stated)

~/circt:

- `M include/circt/Dialect/Resource/Interfaces/MemoryDS.h`
- `M include/circt/Dialect/Resource/Passes/LoopPragmas.h`
- `M lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp`
- `M lib/Dialect/Resource/Passes/AutoPipelineUnroll.cpp`
- `M lib/Dialect/Resource/Passes/BRAMAnalysis.cpp`
- `M lib/Dialect/Resource/Passes/CMakeLists.txt`
- `M lib/Dialect/Resource/Passes/MemoryBankModified.cpp`
- `M lib/Dialect/Resource/Passes/MemrefBankClassification.cpp`
- `M test/hls-est/Passes/bram_debug_json.mlir`
- `M tools/hls-est-validate/SESSION_LOG.md`
- `M tools/hls-est-validate/hlsfactory_v2.py`
- `M tools/hls-est/main.cpp`

Polygeist:

- (clean)

## 2026-10-11 02:05–03:20 — Opus only; weekly limit; resumed on the other account; gate-launched workflows

- 02:05 Peter: "just keep everything on opus fable consumes too much". `scratchpad/model.hard` stays `opus`, the 03:12
  switch-back is cancelled, and every workflow helper has lost its Fable fallback: a failed Opus step stops the workflow,
  which is resumed after the reset. The watcher now reports any agent that runs on Fable. CLAUDE.md "Model per step" was
  updated. 02:25 Peter: scheduling becomes a plugin interface (MEMOS #37, 5a4109dbe; CLAUDE.md P2; the P2 prompt);
  the interface design runs as workflow wf_5a40922a-ea0 (`scratchpad/wf_sched.js`).
- About 03:00 every running agent stopped on "You've hit your weekly limit · resets Oct 15, 5am (America/New_York)" (the
  account logged in at 00:1x). Workflows still on their old in-memory scripts tried a Fable fallback, which failed on the
  same limit. Failed steps are journaled as `failed`, so a resume re-runs them fresh. Committed before the stop: W3-hlsest
  21a959f47 (kept calls of `inline off` callees), W5 items 1 and 2 (Polygeist b3a248a8, 5432780b; circt a44c6d985,
  a059d61fb); W8a's review fixes fd58d2795, and W8 was swapped to `wf_w8_next.js` at 02:37 (W8a replayed from cache).
- 03:15 resumed on the other account, only where the gate is open, so that no agent spends allowance polling a closed
  gate for hours: W3 (impl:W3-hlsest; task wlszx3338), W5 (impl:W5-cgeist; task wklfig0w5), and the scheduler-interface
  design (writer step; task wgg4t216p). The resume notes name the commits above as the step's own work. Launch order
  when the flags appear: `w3.done` -> W7; `w5.done` -> install W5's cgeist, then W6; `w6.done` -> install W6's cgeist,
  then W10; `w7.done` -> W8 (W8b); `w8b.done` -> W2; `w2.done` -> W1 (W1b); `w8.done` -> W9; all P1-P3 gates -> P1-P3.
- v2 Vitis ground truth, tier 1 done at about 03:05: 234 designs, 211 ok, 21 failed, 2 timeouts (1 h). 20 of the
  failures came from Vitis's IP export after csynth (Windows 260-byte path: Common 17-680, or IP_Flow 19-3505). They are
  being re-run with the short work dir of d71fb9eca (NeuroFPGA re-run: ok, BRAM 272). The remaining failure is
  sreenidhireddy lab3 (its top function is not in the sources: UNSUPPORTED). No failure came from the old timeout
  killer. Tier 2 (327 designs) started on the fixed runner.

## 2026-10-11 night: Peter's decisions #38-#40; W6 stopped; W11 real headers launched

- #38: the plugin design must be hardware-agnostic. Workflow `hw-agnostic-study` (wf_10f08a77-fb3) runs five vendor and
  HLS-tool surveys, a code audit and a design audit (AMD/Vitis specificity), then a design, a critique on Intel, Microchip
  and Lattice targets, and a revision. A writer workflow applies the result to the design memo after it finishes.
- Scheduler-interface design (#37) finished: 1dda02772, plus review fixes 00927a7aa (14 defects).
- #39: no more header shims; cgeist compiles the real Vitis headers. #40: hls-llvm-project's Xilinx HLS files are
  Apache-2.0 and its LLVM base is NCSA, so code may be ported (CLAUDE.md ground rule annotated). W6 (shim proxy classes,
  #15) stopped as superseded. W8b restarted with a no-new-shim note: its shim-gap classes go to W11. W10's gate is now
  `w5.done`.
- Feasibility inventory (scratchpad/realhdr/inventory.md). Vitis synthesis reads `Vitis/common/technology/autopilot`
  with `-D__VITIS_HLS__ -DAESL_SYN -D__SYNTHESIS__ -D__HLS_SYN__ -D__DSP48E1__ -include etc/autopilot_ssdm_op.h`.
  `bitwidth(N)` needs a small clang patch (mapping to `_BitInt`). The bit builtins are lowered in cgeist. Streams,
  tasks, ap_float, the FFT IP and the float math library need separate hls-est models.
- W11 launched (wf_c04f21dc-46a): plan, implement (private Polygeist and llvm-project worktrees and builds on ext4, under
  /home/peter/w11), independent validation (lit on the real headers; at least 300 differential kernels bit-exact against
  g++ with the real headers in C-simulation mode; widths compared with Vitis's a.g.ld.5.gdce.ll; harness `--shim real`
  against exactclass), review, fix. Integration into the shared build happens after W10.
- Correction: the minute timestamps on MEMOS #38-#40 were estimates and are removed (the clock read 03:52 just after #40).

## 2026-10-11 night: two study workflows paused at Peter's request

- Peter: "pause the ip-task modelling proposal and dse latency until the other agents are done then resume it". I stopped
  both: `ip-task-modelling-proposal` (wf_2cc8ddfe-0ef; memo M13) and `dse-latency-profile` (wf_166b34c1-070; memo M14,
  decision #41). Resume condition: when the workflows running at the time of the pause have finished. Those are W3
  (wlszx3338), W5 (wklfig0w5), W8/W8b (wjnnkc91v, up to the end of fix:w8b; W8c then waits for w1.done), W11
  (wg1qa3jyj), hw-agnostic-study (wqs7d2ges) and real-headers-feasibility (w56blukk2). The later gate-launched tracks
  (W7, W10, W2, W1b, W9, P1-P3) are not part of the condition. Resume with resumeFromRunId and the same script paths
  (workflows/scripts/ip-task-modelling-proposal-wf_2cc8ddfe-0ef.js and dse-latency-profile-wf_166b34c1-070.js).
  Completed steps replay from cache.

## 2026-10-11 ~10:40: v2 ground-truth runner restarted without hlsyn-vitis (memory)

- At 10:19 tier 2 was at 212 of 327 (vitis-v2.json: 434 ok, 10 timeouts, 2 failures). Then hlsyn-vitis/doitgen-red
  failed with "[HLS 200-103] Unexpected exception occurred: Out of Memory". Windows had 4.3 of 63.9 GB free, and one
  vitis_hls.exe held 15.2 GB. Every hlsyn-vitis design so far had timed out at 1 h or run out of memory (2mm, 3mm, adi,
  doitgen-red), and about 40 remained at 6 slots.
- The runner script and the runner were stopped. 34 Windows processes kept running under the ground-truth work root:
  the 6 in-flight hlsyn-vitis designs, plus two tier-1 class designs from before the killer fix (anirudh_tulasi lab3,
  shibao_su lab2), whose vitis_hls.exe children the old timeout killer missed. Stopping those processes was denied by
  the permission check, so Peter decides that. They end on their own, by finishing or by running out of memory.
- Relaunch (`scratchpad/vitis_v2_run2.sh`): tier 2 without hlsyn-vitis, then tier 3, at -j 4 (memory). Then hlsyn-vitis
  designs without an ok result, with --force, -j 2 and a 2 h timeout. No relaunched design is one of the orphans' designs,
  so their work directories are untouched.
