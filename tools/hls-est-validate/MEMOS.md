# Decision memos for Peter (nothing here is applied; CLAUDE.md "Pending decisions")

Numbers are from parsed harness outputs; "subset" = polybench, polybench_pragmas, forgebench, machsuite, spector_hls,
vitis_examples (73 compared designs) at hls-est 22d473858 unless stated. They will be refreshed after T4/T5 land.

## Decisions recorded 2026-10-10 (Peter's answers to the question list)

| # | Question | Decision | Status |
|---|---|---|---|
| 1 | M1: drop `--infer-vitis-split-array` from the default pipeline | approved | implemented (W1a, 919792784) |
| 2 | M6: `--bram-seq-dual-port` on by default | approved | implemented (W1a, 98e86b070) |
| 3 | M8: `float-loads-perfect` by default | approved (with exactclass, which #8 now makes the default) | implemented (W1c item 3, 5b9418cb8: subset unchanged, 52 / 89; atax / bicg decisions = Vitis; kernels 74 -> 81 decisions, 64 -> 70 BRAM) |
| 4 | M5: dead-memory front end + m_axi adapter cost | approved (with exactclass); no globals promotion before O10/O17 | implemented (W1c item 2, fcf9a59b2: `DME_FRONT` = T8's prefix B in `DEFAULT_PIPELINE`, `--bram-maxi-adapters` on by default; 48 -> 52 / 89, \|err\| 8609 -> 8435) |
| 5 | M6: `forward-stores` | approved as recommended: only after #4, and only if rule 4 holds after a look at Llama_GPT_module's Q/K | implemented (W1c item 4, d4210fc36: rule 4 holds, 52 -> 55 / 89, \|err\| 8435 -> 8425; Llama_GPT_module 29 -> 33 is O10 + N16 per array, M6 addendum W1c) |
| 6 | M4: band formula as the default BRAM formula, written from our measurements | approved | implemented (W1a, 51b9a6434) |
| 7 | M7: `top=` option on `--bram-analysis` | approved | implemented (W1a, 433f07113; review fixes 0ae005759: top= = the prefix with attributed globals too) |
| 8 | M2/M3: `exactclass` as the harness default shim | approved ("Yes use exact class", 2026-10-10) | implemented (W1c item 1, b345b36b2; new baseline 48 / 89, \|err\| 8609) |
| 9 | `--scalar-wrapper-abi` default in cgeist | opt-in, the harness's exactclass shim passes it | confirmed by Peter 2026-10-10 23:20 |
| 10 | exactclass replaces Polygeist's lit shim `Test/HLS/Inputs/vitis` | approved (same as #8) | implemented (W5 item 3, Polygeist 95a5ce16: the headers are a copy of `shim/exactclass` plus its `cgeist_flags`; every `%vitis_include` RUN line passes `--scalar-wrapper-abi`; hlsfactory tests regenerated, 692 pass / 84 XFAIL, 24 new XFAILs from shim gaps (O15, `shim-hls-api`)). Interim: decision #39 (W11) moves the lit tests to the real Vitis headers |
| 11 | O10: cgeist honours `#pragma HLS inline off` | approved | implemented and **installed**: Polygeist 62c40544 + 2ec1956c (`--hls-ignore-inline-off` restores inlining), hls-est 21a959f47 prices kept calls per instance (N14); `build/bin/cgeist` = 2ec1956c since 2026-10-11 04:24 (rule 4: exactclass 55 / 89 = 55 / 89, \|err\| 8425 -> 5243; scalar 45 = 45, 31821 -> 28718; CHANGELOG W3-hlsest) |
| 12 | O5: cgeist opt-in flag to keep invariant inner loops in place | approved | implemented (W3, 62c40544: `--hls-keep-invariant-loops`, default off) and installed with #11 (2026-10-11 04:24). The harness does not pass it. With it the 3 O5 kernels = Vitis and the harness totals are unchanged; recommended for the harness flags (OPEN_ISSUES O5) |
| 13 | M9: unsigned 32-bit wrap assumption | approved: the frontend marks signed arithmetic as non-wrapping; keep today's behaviour until that lands | implemented in Polygeist (W5 item 1, b3a248a8: `polygeist.nsw`; `-affine-cfg-assume-nowrap-width=32` restores the old rule). Not installed: W5's private binary, the coordinator installs it |
| 14 | raise narrow counters against an `int` bound by assuming it fits | Peter: "do whatever you feel will make the result closer" - decide by a Vitis experiment (does Vitis pipeline such a loop?) | implemented (W5 item 2, option (C) of N15: Polygeist 5432780b raises such loops and marks `hls.uncounted`, `-canonicalize-for-assume-termination=false` restores the old behaviour; hls-est `--auto-pipeline-unroll` honours the mark). Not installed: W5's private binary, the coordinator installs it |
| 15 | O15: assignable `range()` references | Peter approved the M10 plan (2026-10-10): time-boxed experiment on one soda design and SkyNet, after the W3/W5 frontend work | to implement (W6) |
| 16 | regenerate the lit Estimation CHECK values from the current model (Vitis value in a comment) | approved, after the defaults are settled | implemented (W1b, CHANGELOG 2026-10-13 "lit: Estimation CHECKs regenerated"; lit 124 pass / 0 fail / 1 unresolved / 1 xfail) |
| 17 | the 12 designs without Vitis ground truth | exclude them for now and record why in the spreadsheet | done (2e8f04992, sheet "excluded designs") |
| 18 | `hls::exp` / `hls::sqrt` deviations in exactclass | Peter: find out whether these functions have a fixed cost (experiments); put the cost in a configuration file the programmer sets | experiments done: fixed BRAM per core instance, instances by call structure (VITIS_NOTES N16, fde45f14f); config `math_costs.json` (30e2933f9); **implemented (W2-impl, 2026-10-13):** `--bram-analysis math-costs=<file>`, the harness passes `math_costs.json` by default (`--no-math-costs` turns it off); exactclass shim markers keep the ap_fixed type (CHANGELOG 2026-10-13 "math cores") |
| 19 | keep the two small default-output changes (banking constants through index casts; RAM_2P label) | approved | done |
| 20 | correct the CLAUDE.md attention target | done (Peter + coordinator) | done |
| 21 | push / PRs | not yet | - |
| 22 | Phase 6 (DSP, FF, LUT) | started 2026-10-13 (see #56) | - |
| 23 | Generalization: every architectural assumption exposed in a designer config file; plugins (separately compilable) for what cannot be data | Peter directed it (2026-10-10 20:10) | phase P2 of wf_c3d16de8-975, after the open tracks |
| 24 | `hls-doc/`: home of all documentation, ground truth, current results, every note and the assistant's memory | Peter directed it | phase P0 (wf_2a1ab997-478) now; notes move in P1 |
| 25 | every cgeist test mirrored as an hls-est lit test | Peter directed it | phase P1 |
| 26 | refactor for readability / good engineering practice and speed, byte-identical outputs | Peter directed it ("nice and human readable, standard good software engineering practices") | phase P3 |
| 27 | forgebench fixes track W7: replication overcount, never-accessed globals Vitis keeps, ROM width narrowing, globals-promotion measurement (memo M11 for the default), cgeist empty-module failures | Peter: "go" (2026-10-10 20:50) | wf_5074c6a1-dc8: items 1-3 implemented (W7, #44 #45), item 4 = M11 (#46), item 5 skipped (w6.done never written: W6 stopped by #39) |
| 28 | HLSFactory_v2 (`D:\HLSFactory_v2\HLSFactory`) as the design catalogue; every design compilable by cgeist and ingested by hls-est | Peter directed it (21:05) | W8 wf_7474f3cd-7d5: W8a implemented (5ff9321ce: opt-in `--catalog v2`, 801 designs swept, 655 through cgeist, 318 through hls-est, failures classified in `hls-doc/hlsfactory-v2.md`); W8b part 1 done (CHANGELOG 2026-10-11 "check_semantics.py": the semantic check against the real Vitis headers, `hls-doc/semantics.md`; shim-gap classes moved to W11 per #39); W8b's cgeist / hls-est / harness-default fixes (OPEN_ISSUES O30 O31 O19 O25 O28 O36 O37) and W8c (ground truth for the 55 changed and 26 new designs, O32) open; W8c implemented 2026-10-13 (CHANGELOG "ground truth: the HLSFactory_v2 Vitis run merged" a1dfacc41, "HLSFactory_v2 is the default design catalogue" 514d266ca, "full HLSFactory_v2 runs ... saved as baselines": baselines `results/baseline/hlsest-2026-10-13-v2-*.csv`, hls-doc pages, the #52 designs listed as unsynthesised) |
| 29 | every case lit tested in cgeist and hls-est | Peter directed it (21:20) | cgeist side in W8c, hls-est side in P1a |
| 30 | P2 configuration/plugin design: the 15 questions in `hls-doc/design/configuration-and-plugins.md` section 11 (format JSON, nested snake_case keys, registry delivery, explicit pass option beats the file, `td` default of the bare split pass `off`, fixed pragma attribute names, seven plugin interfaces, MLIR loader + `--load-plugin`, build-tree-only headers in P2, `pipeline.default` in the config, `math_costs.json` referenced, `target.resources` recorded, `circt::hlsest` namespace, duplicate plugin names are an error, `--config` in run_hlsest.py and experiment_pipeline.py) | asked 2026-10-10 21:50 | approved: go with every recommendation (Peter 23:20) |
| 31 | model per step: hardest steps on Fable 5.1 (W3 cgeist review/fix + hls-est side, W5, W6, W7, W8b, each with its review and fix), everything else on Opus 5.5; the hls-est chain reordered so the hard model work runs first: W1c fix -> W3 hls-est -> W7 -> W8b -> W2 -> W1b -> W8c -> P1-P3 | Peter: "reorder your task so the hardest task only for fable" (2026-10-10 22:20) | done 22:35 (W8's re-pin swaps in after its sweep step is cached) |
| 32 | DEFINITION OF DONE (/goal): every HLSFactory_v2 design ingested by cgeist into semantically correct MLIR; every design has cgeist + hls-est lit tests that hls-est ingests without errors; plugin infrastructure + docs with a new-FPGA-architecture example; docs for every pass and the architecture; hls-est BRAM equals Vitis or over-counts by <= 15% for every design with ground truth | Peter, 2026-10-10 22:45 | W8b semantic check, W9 accuracy loop (wf_3f96a4b0-371), P1-P3 extended; baseline 58/89 in band |
| 33 | conflicting array_partition pragmas on one variable (OPEN_ISSUES O28 item 3; testing_unroll): cgeist rejects them today; Vitis keeps the larger factor whatever the order (N17 (c), kernels fbh6_conf_up/down). Proposal: cgeist merges them the Vitis way | approved (Peter 23:20): merge the Vitis way, documented in hls-doc | implemented (W10, Polygeist 989a2035 on branch w10-autoinline, to be merged onto hls-est-vitis-match; hls-doc/frontend-pragmas.md 3.1; VITIS_NOTES N28) |
| 34 | cgeist mimics Vitis's automatic inlining (keeps callees Vitis does not inline as calls; threshold to be pinned by kernels, N14 R8) | approved (Peter 23:20: "yes, mimic Vitis") | implemented (W10, Polygeist b1067998 on branch w10-autoinline, to be merged onto hls-est-vitis-match; hls-est side circt 6e3fb02b8; hls-doc/frontend-pragmas.md 3.2) |
| 35 | default dead-memory front end: `--vitis-fold` before `--canonicalize` (Vitis undef rules see the selects before they become min/max) | adopted under #36 | W1b |
| 36 | **DELEGATION:** "I want minimal supervision until you're done; do whatever you feel best replicates Vitis behaviour" - the coordinator and agents decide defaults, pipeline order, shim and frontend behaviour by the criterion *best replicates Vitis*, backed by Vitis evidence, working-loop rule 4 and the gates, and recorded here and in the CHANGELOG. Unchanged: no push / PR, Phase 6 (DSP/FF/LUT) on hold, never decompile Vitis, no name/size special cases | Peter 2026-10-10 23:20 | in force |
| 37 | Scheduling as a plugin interface (overrides #30 row 7, the design memo's section 8.1 "schedulers stay fixed until O1") | Peter, 2026-10-11 02:25: "it seems like scheduling must be part of the plugin infrastructure then make note of that". This followed the DSP/FF/LUT feasibility check (137 ground-truth designs; whole-hierarchy shares of Vitis's own estimate). FF is 62% pipeline/state registers. LUT is 54% operator logic and 24% multiplexers. DSP is the bound multipliers and cores. All of these depend on Vitis's schedule and operator binding. P2 therefore makes scheduling a plugin interface: the operation delay/latency model, the scheduling algorithm for pipelined and sequential regions, operator binding/sharing, and the schedule result that the BRAM port model (and later DSP/FF/LUT models) read. The built-in greedy resource-bound modulo scheduler and today's dependence analysis are the default plugins, with byte-identical output. | approved (Peter); designed 2026-10-11: five interfaces (OperatorTimingModel, DependenceModel, ModuloScheduler, SequentialScheduler, Binder) and the ScheduleView result contract, design memo section 8.7 (1dda02772; adversarial review: 14 defects, fixed in 00927a7aa); the vendor-neutral revision under #38 follows |
| 38 | The P2 configuration/plugin design must be hardware-agnostic | Peter, 2026-10-11 (night): "for plugin design the only [thing] I want [is] it to [be] hardware agnostic; study other fpga and how they allocate resources when doing the designing; look at intel fpga and other provider fpga designs". The target description and every plugin interface, including the scheduling interfaces of #37, must express the memory, DSP, logic and register resources of other vendors' devices (Intel/Altera, AMD families beyond 7-series, Lattice, Microchip, Achronix, Efinix, Gowin and others) and the allocation policies of their HLS tools (Intel HLS / oneAPI, SmartHLS, Catapult, Bambu and others). Vendor resources (BRAM_18K, RAMB18 aspect modes, DSP48, LUTRAM) become data of one target description. Vitis-specific allocation rules become one tool-policy plugin. AMD xc7z020 + Vitis 2025.1 stays the default target, with byte-identical output. | approved (Peter); designed 2026-10-11: audit of 272 assumptions (95 vendor-neutral, 10 AMD device, 4 7-series-only, 113 Vitis policy, 50 fused; 64 hard-coded in names/interfaces: hls-doc/design/amd-specificity-audit.md), vendor survey (hls-doc/design/fpga-resource-survey.md), memo revised to device / tool profile (tool.hls, tool.backend) / scheduling / run with 13 interfaces and ResourceVector costs (b954b36ea; adversarial review: 14 defects, fixed in dc955d3ed). Coordinator under #36: memo decision rows 16-19 and 21 adopted; row 20 = #42. The conflict between memo decision 5 and the P2c byte-identity gate is settled: SPLIT_PIPELINE pins `--infer-vitis-split-array=td=auto` explicitly, so the non-default split pipeline keeps its old meaning; the gate applies to the default pipeline. Open gaps G1, G2, G9, G10, G17 (memo section 12). |
| 39 | Real Vitis headers instead of header shims | Peter, 2026-10-11 (night): "I do not want to maintain a shim for every header file change cgeist to understand xilinx attributes validate it with test on real xilinx headers". cgeist compiles designs against the real Vitis 2025.1 headers in synthesis mode (-D__SYNTHESIS__). It understands the Xilinx front-end extensions those headers use: `__attribute__((bitwidth(N)))` on int/unsigned (etc/ap_common.h:252, :531) as an exact N-bit integer, the bit, part-select and concat builtins (etc/autopilot_ssdm_bits.h), and the `__fpga_*` intrinsics the stream, math and DSP headers need. It is validated by tests on the real headers: Polygeist lit tests that compile the real headers; differential execution of cgeist's MLIR against g++ with the real headers (C-simulation semantics) on random inputs, bit-exact; element widths compared with Vitis's own front-end IR (db/a.g.ld.5.gdce.ll in the ground-truth cache); and the harness under a new `--shim real`. No new shim headers are written (W8b's shim-gap classes move to this track, W11). W6 (exactclass proxy classes for range selects, #15) is superseded and stopped. exactclass stays the default until `real` matches or beats it on the harness, then it is frozen and retired. | approved (Peter); track W11; feasibility memo M12 (evidence, staged plan; go/no-go includes compile time, #41) |
| 40 | Reuse Xilinx's open-source front-end code in cgeist | Peter, 2026-10-11 (night): "is xilinx clang open source? if it has the appropriate license take the code and repurpose it for cgeist". Licence check (local checkout of github.com/Xilinx/hls-llvm-project at ee930469a6e, 2025-10-10). Xilinx's HLS front-end files (clang/lib/Sema/SemaXlxAttr.cpp, clang/lib/CodeGen/CGXlxAttr.cpp, clang/lib/Parse/ParseXlxPragma.cpp and any other file with the same header) are Apache-2.0: they may be copied and adapted into Polygeist (Apache-2.0 with LLVM exception), keeping the copyright and licence header and marking our changes. The LLVM 7 clang/llvm base is University of Illinois/NCSA (clang/LICENSE.TXT, llvm/LICENSE.TXT): permissive, keep the notice. Not copied: llvm/lib/Support/XilinxPlat/* (CoreQuerier.cpp: copyright only, no licence grant; reference reading only, as before) and the Vitis-installed headers (A:/Vitis/2025.1/Vitis/include: 'All Rights Reserved'): we compile against them and never vendor them. Headers checked into tests come from github.com/Xilinx/HLS_arbitrary_Precision_Types (Apache-2.0). There is no top-level LICENSE or NOTICE in hls-llvm-project. Xilinx edits inside NCSA upstream files whose licence is not stated are re-implemented, not copied. The code is LLVM-7-era: it is ported to cgeist's LLVM-18 clang. Example: the BitWidth TypeAttr (Attr.td:554, GNU spelling 'bitwidth', unsigned argument) maps onto clang 18's _BitInt(N). Each copied file is listed with its origin commit in the CHANGELOG. | approved (Peter); used by track W11 (#39) |
| 41 | Speed is a requirement: near-instant feedback for design-space exploration | Peter, 2026-10-11 (night): "the point of this tool is get near instant feedback for resource utilization for design changes to enable DSE how quick is hls-est currently". Measured from the HLSFactory_v2 sweep (hls-doc/hlsfactory-v2.csv: 319 designs where cgeist and hls-est both succeed; run at -j 8 on a loaded machine, so wall times are high): cgeist median 9.2 s, p90 33.8 s, max 371 s; hls-est median under 0.1 s, p90 1.9 s, max 58 s, 6 timeouts at 120 s; total median 9.3 s; Vitis csynth on the same designs median 86 s (median speed-up 8x). Proposed targets: a directive-only change (unroll, partition, pipeline II, bind_storage, inline as hls-est overrides, like set_directive_*) under 1 s, with no frontend re-run; a source change median under 2 s. Means: directive overrides in hls-est, precompiled headers, a single cgeist run per design, profiled cgeist and hls-est hot spots, schedule reuse for identical unrolled copies, a persistent server mode. Every P2/P3 change and every W11 change reports its effect on latency. | approved (Peter's stated goal); profiling and memo M14 in progress |
| 42 | May hls-est work read Vitis's installed device database platform.db? (design memo decision row 20) | Peter, 2026-10-11: "Yes". platform.db is a SQLite data file in the Vitis 2025.1 install (/mnt/a/Vitis/2025.1/Vitis/common/technology/xilinx/common/platform.db). It may be read read-only, with sqlite3 or Python's sqlite3 module, for device facts (resource counts, primitive geometries, operator and core data) for the device description files. It is data, not a binary, so the ground rule against disassembling or decompiling closed Vitis binaries and libraries is unaffected. The file, and dumps of it, are never copied into ~/circt, /mnt/d/HLS or hls-doc. Values taken from it are cited by table and key, and checked against a Vitis run before they become a default. | approved (Peter) |
| 43 | default pipeline: `--lower-polygeist-subindex` first, so cgeist's row arguments of kept calls (`polygeist.subindex`, O25) reach hls-est | adopted under #36 (W3-hlsest: no output change with the installed c70ba2b0 on the 87 / 86 designs compared before; needed by Llama_GPT_module and mult_op_module_dot with the W3 cgeist) | implemented (21a959f47, common.py `DME_FRONT`) |
| 44 | `--memory-banking-bram` partitions as Vitis: every entry of a spec, `dim = 0` = every dimension, the larger factor, callee-parameter pragmas on the arrays passed to them (kept calls), a callee form per argument partition, globals banked in place (VITIS_NOTES N24) | adopted under #36 (W7 item 1: subset 55 -> 66 / 89 exact, \|err\| 5243 -> 1608; no exact design lost) | implemented (W7 item 1 commit, CHANGELOG 2026-10-11 "partitions the way Vitis does") |
| 45 | `--mark-constant-fills` in the default pipeline (after `--inline`, before the folds): an array filled by one constant store is a ROM of that constant, every ROM priced at the width its values need, constant tables priced as ROMs also without `--bram-attribute-globals` (VITIS_NOTES N26) | adopted under #36 (W7 item 3: subset 67 -> 68 / 89, \|err\| 1583 -> 1567; no exact design lost; 15 of 16 W7 ROM kernels and 7 of 9 dead_globals kernels = Vitis) | implemented (W7 item 3 commit, CHANGELOG 2026-10-11 "an array filled by one constant store is a ROM") |
| 46 | M11: globals - bank in place (adopted, #44 / #45); `--bram-attribute-globals` and `--promote-globals-to-allocas` stay opt-in | adopted under #36 (W7 item 4: subset 68 / 89 \|err\| 1567 against 68 / 1655 with attribution and 65 / 2235 with promotion; per array O17 item 1 and O39) | recorded (MEMOS M11; nothing to implement) |
| 47 | Tests, results and documentation layout | Peter, 2026-10-12: "strip out [the markdown document references in the code] and explain them clearly; after you refactor to hw agnostic design create a comprehensive documentation on the overall design of the tool, all passes, what each of them do in detail with examples; clean up the test cases for hls-est: they should contain every hlsfactory case that cgeist can compile, get rid of all the shell script and csv tsv file; executing all hls-est test should be a cmake target that also generates all the results with test case => prediction in the hls-doc folder". Assigned: P1 (test suite of every compilable HLSFactory_v2 design with checked-in MLIR; no shell/csv/tsv; CMake targets check-hls-est and hls-est-results writing Markdown results into hls-doc), P3 (code comments without note references, self-contained explanations; full design and per-pass documentation with examples after the P2 refactor). | approved (Peter); in the P1-P3 workflow prompts |
| 48 | Fast-forward `hls-est-vitis-match` into local `main` when the agents are done? | Peter, 2026-10-12: "no". `main` stays untouched; all work stays on `hls-est-vitis-match`. | recorded |
| 49 | Add design-space-exploration metrics (Kendall tau of the ranking, feasibility agreement, Pareto recall) and a knob-sweep benchmark? | Peter, 2026-10-12: "yes". Scope: a benchmark that sweeps pragma knobs (unroll, pipeline, partition factors) on a set of designs, runs Vitis td=off and hls-est on each point, and reports the three metrics next to the per-design BRAM error. It joins the paused M14 study (DSE latency, #41) and starts when that study resumes, after W8b and W10. Vitis sweep points go to the experiments root, never the ground-truth cache. | recorded, scheduled with M14 |
| 50 | Compare csynth numbers with Vivado post-synthesis / implementation on 30-50 designs? | Peter, 2026-10-12: "no". csynth stays the only ground truth. | recorded |
| 51 | Cap the memory of each ground-truth Vitis run? | Peter, 2026-10-12 19:20: "24 GB cap is fine". hlsyn-vitis jacobi-2d committed 71 GB at 18:04 and Windows stopped the WSL VM. The v2 runner uses `run_vitis.py --mem-limit-gb 24` (44e4df035): a design above the cap is stopped and recorded as `vitis memory limit`, with no ground truth. | adopted for the v2 hlsyn-vitis runs |
| 52 | Keep synthesising the remaining hlsyn-vitis designs? | Peter, 2026-10-12 19:04: "stop hlsyn" (coordinator recommendation: the remaining designs are the ones that already timed out or failed; at the template instantiation (every loop pipelined, unroll 2) they exceed 2 h or 24 GB, two of them stopped the WSL VM, the kernels are covered by polybench / machsuite, and a design without ground truth drops out of the goal). Ground truth keeps the 17 of 42 hlsyn-vitis designs Vitis finished. Without ground truth (25): 2mm (vitis timeout); 3mm (vitis timeout); adi (vitis timeout); doitgen-red (vitis timeout); fdtd-2d (vitis failed); fdtd-2d-large (vitis failed); gemm-blocked (vitis failed); gemm-ncubed (vitis timeout); gemm-p (vitis timeout); gemm-p-large (vitis timeout); gemver (vitis timeout); heat-3d (vitis timeout); jacobi-2d (never run); seidel-2d (never run); spmv-crs (never run); spmv-ellpack (never run); stencil-3d (never run); stencil_stencil2d (never run); symm (never run); symm-opt (never run); symm-opt-medium (never run); syr2k (never run); syrk (never run); trmm (never run); trmm-opt (never run). Design-space accuracy uses the 22,212 pre-synthesised HLSyn points instead (#49, with a calibration on light points). W8c lists these designs as unsynthesised in the ground-truth pages. | adopted; runner stopped 19:04 |
| 53 | Lift the pause on the streams study (M13) for the FIFO kernel sweep? | Peter, 2026-10-12 23:35: "lift the streams pause, start the FIFO sweeps". The W9 diagnosis (coord/scratch/reports/w9prep.md) puts hls::stream FIFOs at 53,501 missing BRAM_18K over 123 out-of-band v2 designs. The sweep pins the FIFO pricing rule with minimal Vitis kernels (VITIS_NOTES entry); the hls-est model follows in W9 after W8b lands. Ping-pong buffers are not part of this decision. | done: VITIS_NOTES N31 (5a47fc91d, review fixes 4b559dbf3); hls-est model in W9 |
| 54 | Make the Vitis front-end flags (`-D__SYNTHESIS__ -D__VITIS_HLS__ -D__HLS_SYN__ -DAESL_SYN`, `-std=gnu++14` / `-std=gnu99`, VITIS_NOTES N19, OPEN_ISSUES O30 / O31) the harness default? | Delegated (#36), W8b 2026-10-13: yes. HLSFactory_v2 sweep h8 -> h9 (`~/hls-est-work/w8b7/runs/`, cgeist c17, hls-est p10): no estimate of the 674 designs ok in both changes; 16 more designs compile and are estimated (15 auto_ntt modules, pp4fpgas huffman_encoding); hlsyn-vitis aes gets past C++17 to two cgeist bugs, fixed in Polygeist fe364b78 / 9c83fd76. Harness subset: see the CHANGELOG entry. `VITIS_FRONTEND=0` restores the old command and cache keys. | implemented (run_hlsest.py, W8b) |
| 55 | Start the ping-pong buffer (PIPO) kernel sweep now? | Peter, 2026-10-13: "Yes start the ping pong". Same method as the FIFO sweep (#53): minimal Vitis kernels, adversarial review, VITIS_NOTES only; the hls-est model follows in W9. The W9 diagnosis puts dataflow PIPO buffers at 11,588 missing BRAM_18K over 46 out-of-band v2 designs. | done: VITIS_NOTES N33 (1169238c9, review fixes 15345f5e2); hls-est model in W9 |
| 56 | Start Phase 6 (DSP, FF, LUT)? | Peter, 2026-10-13: "Yes start ... modelling dsp ff and luts same rules apply within 15% overcount". Phase 6 starts. The rules of the BRAM work apply unchanged (Vitis is the reference, prove with minimal kernels, no overfitting, review cycle, regression gates). Target per resource and per design with Vitis ground truth: equal to Vitis or over-count by at most 15% (under-counts out of band), measured like the BRAM goal_band. Sequence: study and plan now (no code while W8b, W10 installs and W9-FIFO/PIPO models are in flight); implementation builds on the P2 scheduling and binding interfaces (#37). | adopted; study started |

Note: the "Regression gates" bullets of CLAUDE.md were restored on Peter's request (2026-10-10); the gates apply (test/hls-est no new
failures; polybench_pragmas bicg 8, gesummv 16, mvt 8, syrk 32 exact; designs exact in the latest run stay exact unless
explained per array).

## M1 — O2: drop `--infer-vitis-split-array` from the default pipeline

**Question.** The pass partitions arrays by port pressure, which is what Vitis does with
`syn.array_partition.throughput_driven=auto` (N2). The ground truth is td=off, where Vitis replicates (RAM_1WNR, N4)
instead and partitions only small arrays and constant-index dimensions (N7).

**Before / after (subset, hls-est 22d473858):**

| pipeline | exact | total abs error | designs ok |
|---|---|---|---|
| default (with split) | 33 / 73 | 5053 | 72 |
| without split | 39 / 73 | 4283 | 72 |

Whole core set at T1+T2 (143 designs, exact shim): with split 32 / 66 exact, |err| 1544; without 38 / 64, |err| 782.
No design that is exact with the split pass stops being exact without it (per-array check in the T2 review).

**What breaks without it.** Nothing in the td=off truth. Against the td=auto result set (results/vitis-tdauto.json) the
split pass is closer on the 34 designs where Vitis auto-partitions (atax 68, attention_op_p2 207), so keep the pass for a
future td=auto mode (T5 adds a `td=auto|off` option to it; under td=off it then only does the N7 automatic partitions).

**Cost.** None beyond re-running the subset (minutes); the Vitis cache is untouched.

**Recommendation.** Remove `--infer-vitis-split-array` from the default string, or keep it with `td=off` once T5 lands
(same effect). Either way the lit RUN lines and the Compiler Explorer integration need the new string.

**Addendum (T5, 2026-10-10): the alternative `--infer-vitis-split-array=td=off`.** The pass now has `td=auto|off`
(default `auto` = the inference above, output unchanged). `td=off` infers no port-pressure partition and only Vitis'
automatic td=off partitions (N7: <= 4 elements and all-constant arrays -> registers, a dimension indexed only by
constants -> complete). Harness subset, scalar shim, hls-est 7c5a8aae0 + T5, MLIR reused (`--mlir-from`), runs
`~/hls-est-work/t5/runs/`; exact / |err| on the 77 designs every run compares:

| pipeline | float-loads-perfect (M8) | exact | total abs error | changed vs. "without split" (Vitis) |
|---|---|---|---|---|
| default (with split, td=auto) | off | 35 / 77 | 14546 | - |
| without split | off | 41 / 77 | 17232 | - |
| with `--infer-vitis-split-array=td=off` | off | 41 / 77 | 17224 | gesummv 20 -> 134 (135), atax 11 -> 68 (13), bicg 12 -> 69 (14) |
| without split | on | 41 / 77 | 17230 | atax 11 -> 12, bicg 12 -> 13 |
| with `--infer-vitis-split-array=td=off` | on | 41 / 77 | 17116 | atax 12, bicg 13, gesummv 134 |

gesummv is Vitis' own `[HLS 214-449]` on buff_A and buff_B (64 + 64 banks; per array buff_A, buff_B, tmp1, tmp2 now
equal Vitis, buff_x is O3). atax / bicg regress only with the current T3 default: `--auto-pipeline-unroll` unrolls
lp4 / lp2 where Vitis flattens the float nest (O13), so every buff_A index on dimension 2 becomes a constant and the
rule fires; with `float-loads-perfect=true` the nest is flattened, j stays a variable and buff_A stays one RAM, as in
Vitis. Regression gates exact in every row. Kernels (CHANGELOG T5 entry): partition topic 126 / 136 exact with td=off
vs 119 without split and 116 with the default; T2's replication inputs 13 / 13 either way (td=auto 11 / 13).

**Recommendation (T5).** Keep the pass with `td=off` rather than dropping it, and only together with M8
(`float-loads-perfect=true`); without M8, dropping the pass is the safer of the two. Either way the lit RUN lines and the
Compiler Explorer integration need the new string. Not applied: the default pipeline is Peter's decision.

## M2 — O6: make `--shim exact` the harness default

**Question.** `scalar` widens `ap_int<W>` to 8/16/32/64 bits and maps `ap_fixed` to `float`; `exact` uses `_BitInt(W)`
and `_Float16` (W <= 16). Exact widths are needed for the LUTRAM threshold (N5: 93x11 bits = LUTRAM, scalar predicts BRAM),
every forgebench `ap_fixed<16,5>` array (2x BRAM with `float`), and any fixed-point folding.

**Before / after (base pipeline, whole core set, hls-est 3ad60fb79, Vitis td=off):**

| shim | compared | exact | total abs error | cgeist/hls-est failures |
|---|---|---|---|---|
| scalar | 74 | 31 | 8078 | 57 |
| exact | 61 | 24 | 5608 | 70 |

The exact shim loses 13 comparisons because `_BitInt` has no member functions: the 11 soda designs call
`ap_uint<256>::range()` / `operator()` and two more use concatenation. Route A (cgeist lowering of scalar-wrapper
classes, in progress on the Polygeist branch as an opt-in) restores those with a class-based shim (`exactclass`).

**What else changes.** Every baseline table was measured with `scalar`; switching re-measures all of them (hours of
hls-est runs, no new Vitis runs). The forgebench totals move substantially (e.g. activation_* 392 -> 256 under T2).

**Recommendation.** Make `exact` (or `exactclass` once route A is accepted) the default; keep `scalar` selectable for the
old numbers. Decide together with M3.

**Addendum (2026-10-10, hls-est 9389b61bc + T5/T6, cgeist 28236352 with route A).** Harness subset, all opt-in flags
off, MLIR reused from the T4/T6 runs (`~/hls-est-work/t6/runs/{base,xbase,cbase}_{def,nos}.cmp.json`), restricted to the
designs every shim compares. The `exactclass` column also has the M5 front end prepended (`--promote-globals-to-allocas
--vitis-fold --canonicalize --sccp --dead-memory-elimination` plus the m_axi adapter cost), so it measures M2 + M3 + M5
together; the `exact` column is the shim alone. Cells: exact / total |err|.

Default pipeline (79 designs):

| dataset | n | scalar | exact | exactclass + M5 |
|---|---|---|---|---|
| forgebench | 30 | 0 / 17330 | 2 / 2113 | 5 / 1698 |
| machsuite | 11 | 9 / 104 | 10 / 40 | 10 / 40 |
| polybench | 9 | 0 / 873 | 0 / 873 | 0 / 873 |
| polybench_pragmas | 7 | 6 / 16 | 6 / 16 | 6 / 16 |
| spector_hls | 8 | 7 / 4 | 7 / 4 | 7 / 4 |
| vitis_examples | 14 | 13 / 1 | 13 / 1 | 13 / 1 |
| **all** | 79 | **35 / 18328** | **38 / 3047** | **41 / 2632** |

Without `--infer-vitis-split-array` (80 designs):

| dataset | n | scalar | exact | exactclass + M5 |
|---|---|---|---|---|
| forgebench | 31 | 0 / 29009 | 2 / 5154 | 7 / 5887 |
| machsuite | 11 | 9 / 80 | 10 / 16 | 10 / 16 |
| polybench | 9 | 5 / 121 | 5 / 121 | 5 / 121 |
| polybench_pragmas | 7 | 6 / 16 | 6 / 16 | 6 / 16 |
| spector_hls | 8 | 8 / 0 | 8 / 0 | 8 / 0 |
| vitis_examples | 14 | 13 / 1 | 13 / 1 | 13 / 1 |
| **all** | 80 | **41 / 29227** | **44 / 5308** | **49 / 6041** |

The large scalar errors come from the forgebench conv_block designs, which compile since T4's robustness fixes and are
2x too large with `float` elements. The shim changes only forgebench and machsuite; polybench, spector_hls and
vitis_examples are identical across shims. No design that is exact under `scalar` stops being exact under `exact` (checked per design, both pipelines).
Two designs exact under `exact` stop matching in the `exactclass + M5` column: forgebench mult_op_p2 and vec_mtx_p1
(2 -> 4, Vitis 2). Per array they were exact only by cancellation: globals that Vitis does not keep as memories
offset the missing m_axi adapter (T4 CHANGELOG entry); the adapter cost added by M5 exposes the global error.
The regression gates hold in every run (T6). Route A's coverage run (7 datasets, default pipeline, no M5) gave
`exact` 31 vs `exactclass` 32 exact matches, with soda compiling again (CHANGELOG route A entry).

**Updated recommendation.** Make `exactclass` the harness default (with cgeist `--scalar-wrapper-abi` from its
`cgeist_flags`, M3), keep `scalar` selectable; the M5 front end is decided separately. Re-measuring every baseline
takes about an hour of hls-est runs and no Vitis runs.

**Addendum (T8, 2026-10-10, hls-est 957b1bd22 + T8 = `~/hls-est-work/t8/hls-est.t8a`, cgeist cbc105e0).** `exactclass` vs
`exact`, each shim's MLIR from one cgeist pass and every configuration on it (`--mlir-from`), runs in `~/hls-est-work/t8/runs/`
(`<x2|xc2>_<config>_<def|nos>.json`); the scalar column is T7's final run replayed with the T8 binary (identical, `s_*`).
"B" = `--inline --canonicalize --sccp --vitis-fold --dead-memory-elimination` after the top selection and `--bram-maxi-adapters`
(M5 recommendation 1 with T8's `--inline`); "A" = B plus `--promote-globals-to-allocas` (the T8 task prefix). Cells: exact / total |err|.

Without `--infer-vitis-split-array` (89 designs compared in every column):

| dataset | n | scalar | exact | exactclass | exact + B | exactclass + B | exact + A | exactclass + A |
|---|---|---|---|---|---|---|---|---|
| polybench | 9 | 5 / 121 | 5 / 121 | 5 / 121 | 5 / 121 | 5 / 121 | 5 / 121 | 5 / 121 |
| polybench_pragmas | 7 | 6 / 16 | 6 / 16 | 6 / 16 | 6 / 16 | 6 / 16 | 6 / 16 | 6 / 16 |
| forgebench | 40 | 1 / 31349 | 3 / 8559 | 3 / 8462 | 4 / 8563 | 7 / 8288 | 4 / 8872 | 7 / 9319 |
| machsuite | 11 | 10 / 16 | 10 / 16 | 10 / 16 | 10 / 16 | 10 / 16 | 10 / 16 | 10 / 16 |
| spector_hls | 8 | 8 / 0 | 8 / 0 | 8 / 0 | 8 / 0 | 8 / 0 | 8 / 0 | 8 / 0 |
| vitis_examples | 14 | 13 / 1 | 13 / 1 | 13 / 1 | 13 / 1 | 13 / 1 | 13 / 1 | 13 / 1 |
| **subset** | 89 | **43 / 31503** | **45 / 8713** | **45 / 8616** | **46 / 8717** | **49 / 8442** | **46 / 9026** | **49 / 9473** |

Default pipeline:

| dataset | n | scalar | exact | exactclass | exact + B | exactclass + B | exact + A | exactclass + A |
|---|---|---|---|---|---|---|---|---|
| polybench | 9 | 0 / 873 | 0 / 873 | 0 / 873 | 0 / 873 | 0 / 873 | 0 / 873 | 0 / 873 |
| polybench_pragmas | 7 | 6 / 16 | 6 / 16 | 6 / 16 | 6 / 16 | 6 / 16 | 6 / 16 | 6 / 16 |
| forgebench | 40 | 1 / 26363 | 3 / 6250 | 3 / 6857 | 4 / 6242 | 5 / 6609 | 6 / 6590 | 6 / 6837 |
| machsuite | 11 | 10 / 40 | 10 / 40 | 10 / 40 | 10 / 40 | 10 / 40 | 10 / 40 | 10 / 40 |
| spector_hls | 8 | 7 / 4 | 7 / 4 | 7 / 4 | 7 / 4 | 7 / 4 | 7 / 4 | 7 / 4 |
| vitis_examples | 14 | 13 / 1 | 13 / 1 | 13 / 1 | 13 / 1 | 13 / 1 | 13 / 1 | 13 / 1 |
| **subset** | 89 | **37 / 27297** | **39 / 7184** | **39 / 7791** | **40 / 7176** | **41 / 7543** | **42 / 7524** | **42 / 7771** |

Coverage on the two extra datasets (no Vitis ground truth, ok / designs): class_ece8893_spring_2025 exact 34 / 94, exactclass
32 / 94 (exactclass compiles anirudh_tulasi lab2, which `exact` stops at a `polygeist.subindex` (O25), and loses sahith lab2 (clang:
ambiguous conditional between two `ap_fixed` types), adithi_upadhya lab2 (hls-est crash) and lab2_hanchen (hls-est > 900 s);
kamya_hari lab3 and adithi_upadhya lab3 are a cgeist timeout at 600 s under exactclass and an empty module under exact);
accelerators 0 / 7 under both (cgeist errors and crashes, O25, empty modules).

What exactclass changes per design, with B (the only differences on the subset are forgebench): no split attention_op_p1 205 -> 73,
tiled_attn_p1 205 -> 73, tiled_attn_p2 57 -> 23 (Q / K and the q/k weights dead only with integer ap_fixed, = Vitis), Llama_GPT_module
0 -> 29 (Vitis 30), gpt_transformer_p1 0 -> 24 (28), tiled_attn_module 306 -> 110 (270, O16 / O10), conv_block_module / op2 / conv_module
and diff_orders_module (98 -> 1106, Vitis 1538) move with the integer op mix (not diagnosed per array, as in the route A entry);
default pipeline the same designs except diff_orders_module (gpt_transformer_p1 0 -> 28 = Vitis; attention_op_p1 / tiled_attn_p1
238 -> 78, the split pass banks V 8 ways, O2). No design exact under `exact` stops being exact under `exactclass` (B, both pipelines).

**Updated recommendation (T8).** Unchanged in direction, now with the hls-est side of route A in place: make `exactclass` the harness
default together with prefix B (M5): +3 exact over `exact` + B without the split pass (46 -> 49 / 89, |err| 8717 -> 8442) and +1 with
the default pipeline (40 -> 41), where the total error rises (7176 -> 7543, +367: conv_block_module +768, tiled_attn_module +104
(DME removes four arrays Vitis keeps, O16 / O10), conv_block_op2 +84, against conv_module -182 and the attention designs -160 / -160 /
-32; the conv designs move with the integer op mix under both shims, not diagnosed). `exactclass` alone (no prefix)
gains nothing over `exact` on the subset (45 = 45, 39 = 39); its value is that the folds and DME can act. Re-measuring every baseline:
a few minutes of hls-est per pipeline and shim (`--mlir-from`), plus one cgeist pass per shim (~20 min); no Vitis runs.

## M3 — frontend changes beyond C-semantics fixes (O10, O5, route A)

- **O10:** cgeist inlines callees marked `#pragma HLS inline off`; Vitis keeps one instance and charges its arrays once.
  Proposed fix: honour the pragma in cgeist (no inlining; keep the call) and let hls-est count the callee's memories once.
- **O5:** cgeist hoists invariant inner loops at every `-O`; Vitis does not before its flatten decision. Proposed fix:
  an option to disable that hoist for HLS inputs.
- **Route A:** lower classes with one scalar member (through base classes) to the scalar in cgeist, so an integer-backed
  `ap_fixed`/`ap_int` shim gives `iW` memrefs and bit-exact folds (design in `~/hls-est-work/feas/A/design.md`; the
  alternative, scalarizing struct memrefs inside hls-est, needs about 2000 lines). **Landed opt-in (2026-10-10):**
  Polygeist 8b07bf43 `--scalar-wrapper-abi` (default off; option-off output identical to the previous binary on all
  957 HLS lit RUN lines and the 783 harness designs, exact and scalar shims) and the harness-local shim
  `shim/exactclass` (selected with `--shim exactclass`; its `cgeist_flags` passes the option; 0 mismatches against
  g++ + the Vitis headers on 138 406 values, `hls::exp` within 1 LSB). *Corrected after the review (CHANGELOG "Route A review fixes"): that check used the host compiler only; through cgeist the MLIR had wrong constants on integers wider than 64 bits (Polygeist `SubToAdd`, fixed in Polygeist 28236352) and the shim had two Vitis differences (`ap_int` from a double >= 2^24, signed 1-bit types; fixed). `check_shim_cgeist.py` now checks through cgeist: 412 expressions x 3 paths, 0 mismatches. The ok count of `--shim exact` below (95) is about 97: two of its failures were hls-est timeouts under load.* Coverage, 7 datasets / 208 designs, current
  hls-est, default pipeline (CHANGELOG 2026-10-10): `--shim exact` ok 95 / exact matches 31 -> `--shim exactclass`
  ok 92 / exact 32 (sum |err| on the 57 designs compared by both 1911 -> 1750); new blockers: assignable range
  references (O15, 23 designs, 14 with ground truth, all failing with `exact` too), the O9 simplex assertion on
  forgebench attn_breakdown_* (3), 3 cgeist timeouts. The attention Q/K dead-code case (CLAUDE.md priority 1) still
  needs the hls-est side (track T8: inliner registration, Vitis-undef fold of `divsi x, 0`, dead-memory
  elimination). **For Peter:** (1) make `exactclass` (+ `--scalar-wrapper-abi`) the harness default? (2) switch
  Polygeist's `Test/HLS/Inputs/vitis` to it? (3) turn the option on by default in cgeist? Each is a separate decision;
  none is done.

Each needs Peter's OK before it becomes default behaviour of cgeist or of the harness.

**Addendum (T8, 2026-10-10): the hls-est side of route A is in place (all opt-in).** `--inline` now works on cgeist output (the
llvm dialect's inliner interface was missing; every cgeist module loads that dialect), and `--vitis-fold` models Vitis' undefined
value of an integer division by a constant 0 per use (VITIS_NOTES.md N13; T4's x / 0 -> 0 is `--vitis-fold=undef=false`). With
`--shim exactclass` and `--inline --canonicalize --sccp --vitis-fold --promote-globals-to-allocas --dead-memory-elimination` plus
`--bram-maxi-adapters`, forgebench attention_op_p1 is **73 = Vitis per array** without the split pass (BRAM_attn_input 2, BRAM_1 2,
BRAM_weights_v 64, V 2, scores 1, mem1_m_axi 2; Q, K, BRAM_weights_q, BRAM_weights_k eliminated, N1's a.o.1 list) and 78 with it
(V split 8 ways, O2); the same without `--promote-globals-to-allocas` (prefix "B" of M2 / M5). The head_dim-4 control
(`~/hls-est-work/feas/A/k_ctrl.cpp`, Vitis 6 = Q 3 + K 3) keeps Q and K (3 without the split pass; Q / K reach Vitis' 3 RAM_1WNR copies
each with `forward-stores`, O7 / M6; scores 1 vs 0 is O18), and the head_dim-16 kernel (Vitis 0) loses Q and K (scores 1, O18). With
`--shim exact` (f16) and `scalar` (f32) nothing folds (O16). The design study's "Route A alone does not kill Q and K" gap is closed.
Remaining route-A gaps found end to end: assignable range selects (O15), `polygeist.subindex` in cgeist output (O25; 18 designs of the
8 T8 datasets under exactclass), libm builtins with constant arguments left as calls (O24; no BRAM effect seen). The three decisions
above are unchanged; M2's T8 addendum has the numbers for (1).

## M4 — BRAM formula defaults after the open-source reconciliation (N8)

**Finding.** The 7-series branch of `MemoryQuerier::queryBRAM` in `~/hls-llvm-project` (tag 2025.1, `6ad94cf7d252`;
identical on `main` `ee930469a6e`) is a depth-band formula: <=512 words ceil(W/36) in SDP mode else ceil(W/18);
513-1024 ceil(W/18); 1025-2048 ceil(W/9); 2049-4096 min(ceil(W/4), 2*ceil(W/9)); 4097-8192 ceil(W/2); deeper
2^ceil(log2 ceil(D/16384)) * W; times ceil(n_eff/2) for the used ports, where a 1WnR memory with n > 2 ports counts
2n-2 (= n-1 copies at x18) and a ROM with n > 2 read ports counts n (= ceil(n/2) dual-port ROMs). SDP = one used port
or the pairs {R,W}/{W,R}/{R,R}. LUTRAM when W*D < 1024 and the implementation is auto.

**Agreement with the measured rules.** Up to 4096 words it equals N6 (min over aspect modes, x36 only with one live
port); copies equal N4 (`ceil((R+W)/II) - 1`, cap 16); LUTRAM equals N5. On the 23003 memory rows of results/vitis.json
the band formula matches all 23003, N6 matches 23000 (the 3 misses are ROMs read by more than two ports per cycle:
gsm `bitoff`, aes `sbox`). 18 new standalone kernels (`~/hls-est-work/experiments/fr_*`) settle the cases where the two
differ, all in favour of the band formula:

| case | Vitis = band formula | N6 / hls-est today |
|---|---|---|
| deeper than 4096 words, e.g. 8192x9 / 8192x18 / 16384x18 / 6000x27 | 5 / 9 / 18 / 14 | 4 / 8 / 16 / 12 |
| ROM read twice per cycle, 512x32 | 1 (SDP {R,R}) | 2 |
| ROM read 3 or 4 times per cycle, 512x32 | 4 (ceil(n/2) ROMs) | 2 |
| explicit ram_2p/t2p with one read-only + one write-only port, 512x72 | 2 | 3 |

**Proposal.** Make the band formula the default in `BRAMAnalysis.cpp` `estimateBlocks`, decide x36 with the SDP test
on the bank's used ports, and price read-only banks with n > 2 reads per cycle as ceil(n/2) ROMs. Corpus effect today:
the 3 ROM rows above become exact; no other benchmark row changes (none is deeper than 4096 words with a width the two
formulas disagree on). All current `aspect_modes.mlir` CHECK values stay. New lit values: 8192x9 = 5, 8192x18 = 9,
6000x27 = 14, 16384x18 = 18, ROM 512x32 with 2 reads = 1, with 3 or 4 reads = 4.

**Licence.** `CoreQuerier.cpp` carries only Xilinx/AMD copyright lines (no licence text in the file or directory;
`llvm/LICENSE.TXT` is NCSA). The proposal is to implement the rule from our own measurements (the table above and N6),
not to copy the source; the transcription in `formula_reconcile.py` mirrors the source branch for branch and should not
be ported into hls-est C++ without your decision.

**Cost.** A small C++ change plus lit tests; every baseline stays valid (3 rows move).

## M5 — T4 front-end cleanups and model extensions: dead-memory elimination, Vitis integer folds, globals as locals, m_axi adapters

**Question.** T4 added opt-in mechanisms (VITIS_NOTES.md N1a; CHANGELOG 2026-10-10 T4 entries). Which of them should join the
default pipeline or become `--bram-analysis` defaults?

| mechanism | how to turn it on | what it models |
|---|---|---|
| integer folds | `--vitis-fold` (pass), then `--canonicalize --sccp` | x/0 -> 0: what Vitis does for ap_fixed division (dg_d_fold_steps, dg_d_fold_divrem0b) and unsigned `%`; a refinement of Vitis' undef for C int `/`, `%` and unsigned `/` (dg_d_fold_divrem0, N1a); x*0 -> 0 follows from the canonicalization folds |
| dead-memory elimination | `--dead-memory-elimination` (pass) | arrays (locals and globals) whose loads reach no output are gone at a.o.1 (R1, R2, R5, R6) |
| globals as locals | `--promote-globals-to-allocas` (pass) + `--bram-attribute-globals` (flag) | R6: file-scope arrays get the banking, ports, replication and elimination of locals; constant globals are priced as ROMs (N8) |
| m_axi adapters | `--bram-maxi-adapters` (flag) | the `<bundle>_m_axi_U` instance BRAM (27 kernels: R8 plus 14 new `mx_*`) |
| calls in loop bodies | `--loopschedule-call-latency=1` (flag) | a math call no longer keeps its loop sequential |

The passes are meant to run right after the top selection (`experiment_pipeline.py` ABLATION rows `with-dme*`).

**Before / after** (harness subset, `-j 8 --timeout 120`, hls-est = the T4 commit, runs in `~/hls-est-work/t4/<run>.json`. "pre-T4
designs" = the designs the pre-T4 binary compared under the scalar shim (73 no split, 72 default), so newly compiling designs do not
hide changes. The exact and exactclass rows have no pre-T4 run; their "T4, nothing enabled" row is the reference. exactclass is
the harness-local integer ap_fixed shim of another track (`shim/exactclass`, `--scalar-wrapper-abi`, committed in c733e425e, opt-in). Designs
that hit the simplex assertion (O9) were re-run with the fallback build and merged (`_meta.t4_o9_patch` in each file).)

| shim | pipeline | configuration | run | exact / compared | abs err | exact / compared on the pre-T4 designs | abs err there |
|---|---|---|---|---|---|---|---|
| scalar | no split | pre-T4 binary | `base_nos` | 39 / 73 | 4283 | 39 / 73 | 4283 |
| scalar | no split | T4, nothing enabled (robustness only) | `new_nos` | 41 / 79 | 29197 | 39 / 72 | 4253 |
| scalar | no split | + `--bram-maxi-adapters` | `maxi_nos` | 41 / 80 | 29281 | 39 / 73 | 4327 |
| scalar | no split | + fold + DME | `dmeonly_nos` | 41 / 80 | 29227 | 39 / 73 | 4283 |
| scalar | no split | + promote + `--bram-attribute-globals` | `glob_nos` | 41 / 81 | 31119 | 39 / 73 | 6112 |
| scalar | no split | + `--bram-attribute-globals` only | `attr_nos` | 41 / 80 | 29262 | 39 / 73 | 4313 |
| scalar | no split | + all (with-dme) | `full_nos` | 41 / 80 | 22587 | 39 / 73 | 6168 |
| scalar | no split | + `--canonicalize --sccp` only | `canon_nos` | 41 / 80 | 29227 | 39 / 73 | 4283 |
| scalar | no split | + `--loopschedule-call-latency=1` | `call_nos` | 41 / 80 | 29227 | 39 / 73 | 4283 |
| scalar | default | pre-T4 binary | `base_def` | 33 / 72 | 5023 | 33 / 72 | 5023 |
| scalar | default | T4, nothing enabled | `new_def` | 35 / 77 | 14546 | 33 / 72 | 5023 |
| scalar | default | + all (with-dme) | `full_def` | 36 / 81 | 15892 | 33 / 72 | 6166 |
| exact | no split | T4, nothing enabled | `x_new_nos` | 44 / 79 | 3576 | 42 / 73 | 1439 |
| exact | no split | + `--bram-maxi-adapters` | `x_maxi_nos` | 46 / 80 | 5308 | 44 / 73 | 1437 |
| exact | no split | + fold + DME | `x_dmeonly_nos` | 44 / 80 | 5308 | 42 / 73 | 1439 |
| exact | no split | + all | `x_full_nos` | 46 / 80 | 3874 | 44 / 73 | 1707 |
| exact | default | T4, nothing enabled | `x_new_def` | 38 / 79 | 3047 | 36 / 72 | 2066 |
| exact | default | + `--bram-maxi-adapters` | `x_maxi_def` | 40 / 79 | 3033 | 38 / 72 | 2062 |
| exact | default | + all | `x_full_def` | 42 / 82 | 3904 | 39 / 72 | 2471 |
| exactclass | no split | T4, nothing enabled | `xc_new_nos` | 45 / 81 | 6219 | 42 / 73 | 1390 |
| exactclass | no split | + fold + DME | `xc_dmeonly_nos` | 45 / 81 | 6061 | 42 / 73 | 1232 |
| exactclass | no split | + fold + DME + `--bram-maxi-adapters` | `xc_dmemaxi_nos` | 49 / 81 | 6043 | 47 / 73 | 1210 |
| exactclass | no split | + all | `xc_full_nos` | 49 / 81 | 7063 | 47 / 73 | 2202 |
| exactclass | default | T4, nothing enabled | `xc_new_def` | 39 / 80 | 2886 | 36 / 72 | 2011 |
| exactclass | default | + fold + DME + `--bram-maxi-adapters` | `xc_dmemaxi_def` | 41 / 80 | 2634 | 39 / 72 | 1759 |
| exactclass | default | + all | `xc_full_def` | 42 / 81 | 3366 | 39 / 72 | 2052 |

**What changes, per array.**
- *m_axi adapters* are exact per bundle wherever hls-est finishes (all adapter rows of the subset; 27 / 27 kernels per bundle and in
  total). With exact widths they make activation_module / op2 / op3 (256 -> 258) and diff_dims_module_small (1152 -> 1154) exact.
  mult_op_p2, mult_op_p3 and vec_mtx_p1 stop being exact: they matched only because two globals that Vitis does not keep as
  memories (their partition pragmas sit on two dimensions or on a callee parameter, O17 items 2-3) cancelled the missing adapter.
  Under the scalar shim every forgebench top moves by +2 and none becomes exact (2x widths, O6).
- *Folds + DME* change nothing under the scalar and exact shims: cgeist already deletes the dead C-int arrays, and an ap_fixed that
  is f32 / f16 cannot fold the attention scale. With integer ap_fixed (exactclass) they remove Q, K and the q/k weights exactly as
  Vitis does: attention_op_p1 203 -> 71, tiled_attn_p1 203 -> 71, tiled_attn_p2 55 -> 21 (Vitis 73 / 73 / 23 = these + the adapter).
  tiled_attn_module 304 -> 108 against Vitis 270: Vitis keeps four arrays written by non-inlined `load_*` calls as 0R0W memories
  (N1a, O16; an inlining difference, O10).
- *Globals as locals* is right in isolation (R6) but exposes O17: callees Vitis keeps as modules make the promoted weight arrays
  RAM_1WNR with 15 copies (attention_op_p2/p3 18 -> 202 exact shim), two-dimension pragmas are banked on one dimension (vec_mtx_p1),
  callee-parameter pragmas are lost after inlining (mult_op_p2). It adds 1800-1900 |err| under the scalar shim and ~270 under the
  exact shim, and the only exact design it adds over folds + DME + adapters (attn_breakdown_op1, exact shim, default pipeline: 10) is a
  cancellation: the split pass banks the promoted weight buffers below the LUTRAM threshold (0 vs Vitis 1 each) and Q/K_buffer into
  four 1-BRAM banks each (4 vs Vitis 1).
- *Robustness* (on by default, not part of this proposal): conv_block_op2/3 and conv_module (and conv_block_module / op1 when they
  finish in 120 s) give numbers instead of an assertion; sobel_filter_x/y give 0 = Vitis; with the exact / exactclass shims machsuite
  viterbi gives 128 = Vitis instead of the simplex assertion.

**Recommendation.**
1. Adopt `--vitis-fold --canonicalize --sccp --dead-memory-elimination` (right after the top selection) and `--bram-maxi-adapters`
   together with an integer-backed ap_fixed frontend (exactclass, i.e. M3 route A / M2): +5 exact without split (42 -> 47 on the
   pre-T4 designs, |err| 1390 -> 1210) and +3 with the default pipeline (36 -> 39, |err| 2011 -> 1759). The three designs that stop
   matching are per-array cancellations of O17.
2. If the harness stays on `--shim exact`: `--bram-maxi-adapters` alone is +2 exact in both pipelines at the same error; the folds and
   DME are neutral there.
3. Under the scalar shim none of the mechanisms gains an exact design; do not change the default for it.
4. Do not adopt `--promote-globals-to-allocas` / `--bram-attribute-globals` before O10 (callee instances) and O17 items 2-3.
5. `--loopschedule-call-latency=1` is neutral on the subset; keep it off until a kernel pins the call latency.

**Cost.** Flags and passes only; re-running the subset takes ~7 minutes per pipeline. No Vitis runs (the 14 `mx_*` kernels are
cached under `~/hls-est-work/experiments/mx_*`). The lit RUN lines and `common.py DEFAULT_PIPELINE` are unchanged.

**Addendum (T4 review fixes, 2026-10-10).** The independent review of 77e9ca1fa found two medium and four low defects in the
opt-in mechanisms; all are fixed (CHANGELOG "T4 review fixes"): DME on multi-block function bodies (an inlined callee with an
early return gave `null operand found` and treated a live array as dead), ROM pricing of initialised tables cgeist emits without
`constant` (Vitis rom2r_int 1, hls-est was 2 with `--bram-attribute-globals`, now 1), m_axi ports used through a sub-function
(followed into the callee; Vitis mx_call_rw: write-only 0, read-only 2), the x/0 folds restricted to the four C operators with
the Vitis behaviour measured per operator (N1a "Division by a constant 0"), the harness labels a frozen `HLS_EST_BIN` binary
correctly, and the dead-array reasons list the chain of ops. Re-measured on byte-identical inputs (`run_hlsest.py --mlir-from` the
T4 run files; fixed binary `~/hls-est-work/t4fix/hls-est.t4fix`, runs `~/hls-est-work/t4fix/runs/`, `-j 6 --timeout 120`; the
counts are over the designs that finished in both runs; the 10 design/run pairs that hit the 120 s limit under load in the replay
(conv_block_module, conv_block_op1 / op3, conv_module, diff_dims_p3) were re-run with 900 s (`<run>.retry.json`) and are identical
too):

| shim | pipeline | configuration | T4 run | exact (designs ok in both) | abs err there | totals changed |
|---|---|---|---|---|---|---|
| scalar | default | nothing enabled | `new_def` | 35 -> 35 / 77 | 14546 -> 14546 | none |
| scalar | no split | nothing enabled | `new_nos` | 41 -> 41 / 78 | 20600 -> 20600 | none |
| scalar | default | + all (with-dme) | `full_def` | 36 -> 36 / 79 | 10472 -> 10472 | none |
| scalar | no split | + all (with-dme) | `full_nos` | 41 -> 41 / 80 | 22587 -> 22587 | none |
| exactclass | no split | fold + DME + adapters (recommendation 1) | `xc_dmemaxi_nos` | 49 -> 49 / 79 | 3765 -> 3765 | none |
| exactclass | default | fold + DME + adapters (recommendation 1) | `xc_dmemaxi_def` | 41 -> 41 / 78 | 2404 -> 2404 | none |
| exactclass | no split | + all | `xc_full_nos` | 49 -> 49 / 80 | 4945 -> 4945 | none |
| exactclass | default | + all | `xc_full_def` | 42 -> 42 / 79 | 3149 -> 3149 | none |

No subset design has a function-level branch, a C division by a constant 0, an m_axi port used inside a call that survives
cgeist's inlining (O10), or an initialised table read more than once per cycle, so the recommendation and its numbers stand.
The kernels: rom2r_int 2 -> 1 (= Vitis), mx_call_rw2 3 = Vitis, dg_d_fold_divrem0 12 (Vitis 6, O16: C-int x/0 is undef in
Vitis). Still open for recommendation 4: a constant table read more than twice per cycle is scheduled at a raised II instead of
replicated (O4 "ROM tables": rom3r_int 1 vs Vitis 4).

**Addendum (T8, 2026-10-10).** Two changes to the mechanisms of this memo, both inside opt-in passes (CHANGELOG "T8"):
`--vitis-fold` now models Vitis' undefined value of `x / 0` per use (option `undef`, default on; `undef=false` = the rule measured
above), and `--inline` works on cgeist output. Kernels: dg_d_fold_divrem0 12 -> 6 and dg_d_fold_divrem0b 8 -> 2, both = Vitis (O16's C
int part fixed). Harness (8 datasets: the subset plus class_ece8893_spring_2025 and accelerators; both shims, both pipelines, prefixes
A and B below, `undef` vs `undef=false` on byte-identical MLIR, `~/hls-est-work/t8/runs/`): **no design changes** - no harness design
divides by a constant 0 in C int arithmetic, and the attention scale is used only through sign extensions, where both rules give 0.
So the recommendation's numbers stand; they are re-measured here at the current HEAD (T5-T7 since T4) with `--inline` added and the
adapters on (prefix B = `--inline --canonicalize --sccp --vitis-fold --dead-memory-elimination` + `--bram-maxi-adapters`; A = B +
`--promote-globals-to-allocas`), subset, exact / |err| over 89 designs:

| shim | pipeline | nothing enabled | B (recommendation 1) | A (B + globals as locals) |
|---|---|---|---|---|
| exactclass | no split | 45 / 8616 | **49 / 8442** | 49 / 9473 |
| exactclass | default | 39 / 7791 | **41 / 7543** | 42 / 7771 |
| exact | no split | 45 / 8713 | 46 / 8717 | 46 / 9026 |
| exact | default | 39 / 7184 | 40 / 7176 | 42 / 7524 |
| scalar | default / no split | 37 / 27297, 43 / 31503 (T7, unchanged) | - | - |

B over nothing (exactclass): newly exact attention_op_p1, tiled_attn_p1, tiled_attn_p2 (no split; Q / K dead), activation_module /
op2 / op3, diff_dims_module_small (adapter), gpt_transformer_p1 (default); no longer exact mult_op_p2, mult_op_p3, vec_mtx_p1 (2 -> 4,
the adapter cancellation of O17 items 2-3, as before). A over B: +attn_breakdown_op1 and +mult_op_p3, -gpt_transformer_p1 with the
default pipeline (cancellations), none without the split pass, and +1031 / +228 |err| (attention_op_p2 / p3 20 -> 202, vec_mtx_p1
4 -> 242, Llama_GPT_module 29 -> 85, conv_A 99 -> 995: O17). **Recommendation 1 unchanged** (with `--inline` added: measured a no-op on
all 8 datasets, exactclass no split, `xc2_C_nos` vs `xc2_B_nos`, because cgeist already inlines every defined callee (O10); it makes
the prefix right for modules that keep calls), recommendation 4 unchanged: do not adopt `--promote-globals-to-allocas` before O10 / O17.

## M6 — O3 + O7: turn on `--bram-seq-dual-port`; `forward-stores` only together with dead-memory elimination

**Question.** In a non-pipelined region Vitis issues up to two accesses of one array per state and binds the array
ram_2p / ram_t2p (x18 columns) as soon as one state holds two (VITIS_NOTES.md N12, 33 kernels). hls-est charged every
sequential scope one live port. The T6 entry implements the rule behind `--bram-seq-dual-port` (a `--bram-analysis`
cl option, default off). It also re-measured `--convert-affine-to-loopschedule=forward-stores=true`, which O7 had tied
to this fix.

**Before / after** (harness subset, 110 designs with a Vitis total; `-j 8 --timeout 120`; frozen binary
`~/hls-est-work/t6/bin/hls-est.seq2`; runs `~/hls-est-work/t6/runs/`; scalar = the T5 run's cgeist outputs, exact /
exactclass = the cgeist outputs of `t4/x_full_def` / `t4rev/rxc_dme_def`; "M5 front" = `--vitis-fold --canonicalize
--sccp --dead-memory-elimination` before and `--bram-maxi-adapters` after the pipeline; cells: exact matches,
total abs error over the designs that ran):

| shim | pipeline | flags off | + `--bram-seq-dual-port` | + `forward-stores` as well |
|---|---|---|---|---|
| scalar | default | 35, 18328 | **37**, 18334 | 37, 18334 |
| scalar | no split | 41, 29227 | **44**, 29230 | 44, 29654 |
| exact | default | 38, 3047 | **40**, 3048 | 40, 3048 |
| exact | no split | 44, 5308 | **47**, 5301 (1) | 47, 5489 |
| exactclass + M5 front | default | 41, 2634 | **43**, 2635 | 43, 2635 |
| exactclass + M5 front | no split | 49, 6043 | **52**, 6036 | **55**, 6026 |

(1) In the suite run forgebench/conv_block_module hit the 120 s limit under load (two harness runs in parallel); run alone
it gives 6871, unchanged (`x2seq_nos_cbm.json`).

*Re-measured after the T6 review fixes* (memory order through other arrays, RAM_2P for two reads; binary
`~/hls-est-work/t6fix/hls-est.fix1`, runs `~/hls-est-work/t6fix/runs/`, same MLIR): every option cell of the table re-run,
and the scalar "flags off" cells too. Totals, statuses and per-array BRAM are identical to the table on all 112 designs
(the exact / no split cell now completes conv_block_module inside the limit: 47, 5301 over 80 designs); only the debug
RAM type changes (RAM_T2P -> RAM_2P on the arrays with two reads and at most one write per cycle).

**What `--bram-seq-dual-port` changes** (identical on every shim and front end; per array from the debug JSON):
- newly exact: polybench mvt (12 -> 14, default and no split), gesummv (134 -> 135, default), atax (11 -> 13) and bicg
  (12 -> 14) without split. Every changed polybench array is Vitis-exact: atax `buff_x`, bicg `buff_p`, gesummv `buff_x`,
  mvt `buff_y1` / `buff_y2` (the 64 hoisted invariant reads, two per state) and atax `buff_y_out`, bicg `buff_s_out`
  1 -> 2 = Vitis. For the last two the reason differs from Vitis' (O3 item 3: the promoted loads of the unrolled-j decision
  vs. Vitis' flattened II-1 pipeline; with `float-loads-perfect=true`, M8, they are 2 for Vitis' reason and the totals stay
  13 / 14).
- farther: atax 68 -> 70 and bicg 69 -> 71 with `--infer-vitis-split-array` (the same arrays, now right; the 64-bank
  buff_A split, O2, dominates); scalar shim only: forgebench conv_block_module / op2 / op3 +5 / +2 / +3 from `localWeights`
  RAM_1P -> RAM_2P. Vitis binds `localWeights` ram_2p too (256x16, 1 BRAM); the scalar shim makes it f32, which needs two
  x18 columns; with the exact shims 256x16 costs 1 either way and these designs do not change.
- nothing that matched stops matching; gates polybench_pragmas bicg 8, gesummv 16, mvt 8, syrk 32 exact in every run; no
  status changes; `--bram-analysis` time on conv_block_op1 0.21 s with or without it.
- kernels (N12): 20 / 24 of the kernels whose region hls-est keeps sequential match Vitis per array with it, 13 / 24
  without (19 seqports + 5 t6rev kernels; before the review fixes the option broke rv_memdep / rv_memdep2, where a memory
  order through a second array keeps the two loads apart). The 4 misses: 3 over-estimates where Vitis spreads two
  accesses over the slack around an inner-loop call, and 1 under-estimate (rv_sib2: Vitis starts two independent outlined
  inner loops together and loads for both in one state; the option ends the stretch at the first loop). Both are O21.

**What `forward-stores` changes on top:** nothing in the default pipeline on any shim. Without split it makes attention
Q / K replicable (the unrolled `Q[i][j] +=` becomes one store): 3 copies = Vitis RAM_1WNR where Q / K are live
(attention_op_p2 / p3, gpt_transformer_p1: exact per array with the exact shims; 2 x18 columns per copy with the scalar
shim's f32), but 2 -> 30 BRAM each where Vitis deletes Q / K (attention_op_p1, tiled_attn_*: N1). With the M5 front end
those are gone: +3 exact designs (attention_op_p2 / p3, gpt_transformer_p1), one design farther (Llama_GPT_module 29 -> 33,
Vitis 30: one of its two hls-est Q / K instances becomes RAM_1WNR where Vitis has one ram_t2p Q / K; not investigated).

**Recommendation.**
1. Make `--bram-seq-dual-port` part of the default (append it to `DEFAULT_PIPELINE` and the lit RUN lines, or flip its
   init): +2 exact (default pipeline) / +3 (no split) on every shim, nothing lost. The Estimation expectations of
   polybench atax / bicg / gesummv / mvt would be regenerated (70 / 71 / 135 / 14 under the default RUN pipeline).
2. Keep `forward-stores` off until the M5 front end (exactclass shim + `--dead-memory-elimination`) is the default; adopt
   it together with that (+3 exact there), after a look at Llama_GPT_module's Q / K.

**Addendum (W1c, 2026-10-10): decision #5 implemented.** Measured on the new defaults: the exactclass shim, the DME front, the m_axi adapters, and `float-loads-perfect` (W1c items 1-3). Harness subset, `--mlir-from` the W1c baseline. Runs in `~/hls-est-work/w1c/runs/`: `x_i3` (forward-stores off) and `x_i4fs` (on). Cells: exact / total \|err\| over 89 designs.

| forward-stores | subset | forgebench | changed designs (Vitis) |
|---|---|---|---|
| off (W1c item 3) | 52 / 8435 | 7 / 8288 | - |
| on | **55 / 8425** | 10 / 8278 | attention_op_p2 / p3 20 -> 24 (24), gpt_transformer_p1 24 -> 28 (28), Llama_GPT_module 29 -> 33 (30) |

*Llama_GPT_module, per array.* `grouped_multihead_attention_..._rope` has `#pragma HLS inline off`, and the top has `#pragma HLS allocation function instances=... limit=1`. The top calls it twice, with `(groups, is_rope)` = (8, 0) and (4, 1).
- Vitis builds one shared instance in which both arguments are runtime values. Its scores loop `VITIS_LOOP_207_9_VITIS_LOOP_208_10` (trip 64) runs at II 2 and its QKV loop at II 16. Q, K and scores are ram_t2p and V is RAM_1WNR, 1 BRAM each.
- cgeist inlines both calls with constant arguments (O10), so hls-est costs two instances:
  - The (4, 1) copy matches Vitis' instance: scores loop at II 2, Q / K RAM_2P 1 each, with or without forwarding.
  - The (8, 0) copy has no counterpart in Vitis. With forwarding its scores loop runs at II 1 and Q / K become RAM_1WNR with 3 copies each. That is exactly what Vitis does in the single-call designs where the function is specialized to constant arguments: attention_op_p2 and gpt_transformer_p1, whose scores loops run at II 1 with Q / K RAM_1WNR 3. Without forwarding the copy was RAM_2P 1 each (II 3).
- The duplicate instance therefore costs Q 3 + K 3 + V 1 + scores 1 = 8 with forwarding, against 4 without.
- Against that, hls-est does not cost the hls:: math tables Vitis instantiates in this design: the cordic arctan table 4 and the pow table 1 (N16, decision #18).
- So 33 = 30 + 8 - 5 and 29 = 30 + 4 - 5. Neither is right per array.

Kernels: dg_d_apfixed4 gives 8 with forwarding, = Vitis per array (Q 3 and K 3 RAM_1WNR, V 1, scores 1); without it, 4. dg_d_apfixed16 gives 2 = Vitis either way (`~/hls-est-work/w1c/dgk/`).

The forwarding itself is right wherever the function is specialized per call, which is what hls-est sees after inlining. The remaining error belongs to O10 (one instance per non-inlined callee, here also forced by `allocation limit=1`) and to the math-table cost (W2).

Rule 4 holds: +3 exact, \|err\| 8435 -> 8425, no exact design lost, and the one design that gets farther is explained per array by named issues. Every other memref keeps its status, RAM type and BRAM, except `scores`, which goes RAM_T2P -> RAM_2P at the same 1 BRAM in all five designs that change (attention_op_p2 / p3, gpt_transformer_p1, both instances in Llama_GPT_module, llama_transformer_p2). *Corrected in place by the W1c review fixes: this sentence named only llama_transformer_p2 (debug JSONs of `w1c/runs/x_i3` vs `x_i4`).* **Adopted as the default** (`forward-stores` default `true`; CHANGELOG W1c item 4).

## M7 — O12: let `--bram-analysis` cost only what the top function reaches

**Question.** Today the harness selects the top with `--symbol-privatize=exclude=<top> --symbol-dce` before the
pipeline. Without that prefix hls-est costs every public function, and cgeist emits uncalled alternative tops and
standalone copies of callees it already inlined (O10). On the 79 baseline designs, 15 totals change (up to 2x, e.g.
tiled_attn_module 600 -> 1321) and conv_A/B/C crash when the prefix is missing (bisect, O12).

**Proposal.** A `top=<symbol>` option on `--bram-analysis` (or an `hls.top` attribute set by cgeist), costing only memrefs
in functions reachable from the top through `func.call`, plus a warning when no top is given and several public functions
hold memrefs. With the prefix in place (as the harness and the lit RUN lines already do) nothing changes; it removes a trap
for hand-run commands and for the Compiler Explorer integration.

**Cost.** Small (one option, one reachability walk, lit tests); no baseline changes. Needs Peter's OK because it changes
what the default output means when no top is given.

## M8 — turn on `--auto-pipeline-unroll=float-loads-perfect` by default (O13)

**Question.** The T3 decision treats every hoistable inner-invariant load as making a nest imperfect (inner loop
unrolled, outer pipelined). Vitis does that only when the loaded element is an integer; with a float element it
converts the nest into a perfect one and flattens it (VITIS_NOTES.md N3, 18 kernels in
`~/hls-est-work/exp-src/pipeline_unroll_float`, all decisions read from the `hls_compile.log` 200-2061 / 214-376 /
214-186 / 203-541 lines; polybench atax lp3/lp4 and bicg lp1/lp2 in `results/vitis.json`). The option implements that
rule (T3 review fixes entry); the default is off.

**Before / after** (harness subset, `-j 8 --timeout 120`, hls-est = the T3 review fixes commit; runs in
`~/hls-est-work/t3r/`; "off" is identical per design to HEAD 22d473858):

| pipeline | option | exact | total abs error | hls-est ok | changed designs |
|---|---|---|---|---|---|
| default (with split) | off | 33 / 73 | 5053 | 74 | - |
| default (with split) | on | 33 / 73 | 5055 | 74 | atax 68 -> 69, bicg 69 -> 70 (Vitis 13 / 14; the split pass's partitions dominate, O2) |
| without split | off | 39 / 73 | 4283 | 74 | - |
| without split | on | 39 / 73 | 4281 | 74 | atax 11 -> 12, bicg 12 -> 13 (Vitis 13 / 14; buff_y_out / buff_s_out now 2 = Vitis, the rest is O3) |

The "on" rows are the harness files (`nosplit_f`, `canon_f`) with two designs corrected: there, forgebench
diff_dims_p3 (both pipelines) and conv_block_module (no split) hit the 120 s limit while other workflows loaded the
machine (load average 40-50 on 32 cores); run alone without a limit, diff_dims_p3 gives 384 with and without the option
and conv_block_module the same pre-existing `getIntOrFloatBitWidth` assertion, and the option does not change a single
decision in either. Uncorrected, the files read 39 / 72, |err| 4251 and 33 / 72, |err| 5025. Regression gate (polybench_pragmas bicg 8, gesummv 16, mvt 8, syrk 32) exact in all four
runs. Validation kernels (`check_pipeline_unroll.py`, 86 compared): decisions 74 -> 81 agree, BRAM totals 58 -> 64 equal
(pf_fadd/fmac/fmul/srchoist 4 -> 2, rv_rmw_hoist_f_m8_n64 25 -> 3, _m64_n64 98 -> 11, all = Vitis); the 5 remaining
disagreements are O10 (4) and O8 (1).

**What breaks.** No total in the subset. Decisions change in 7 of 96 subset designs (decision pass alone, remark sets
compared): atax, bicg, polybench_pragmas/bicg (total still 8 = Vitis), machsuite gemm_blocked (double; total
unchanged) and three ap_fixed designs - forgebench Llama_GPT_module, gpt_transformer_p1, llama_transformer_p2 (totals
unchanged). The last three are the risk: the scalar shim (and, per M2, the exact shim for W <= 16) gives `ap_fixed` a
float element type, so the rule fires on arrays that Vitis sees as `iN` and keeps imperfect. Unverified against those
designs' loop tables; by N3 those three decision changes are wrong.

**Recommendation.** Adopt together with an integer-backed `ap_fixed` shim (M3 route A / `exactclass`), where the MLIR
element type is the type Vitis decides on; until then keep it off (one global pipeline: no per-dataset switch).
Either way the lit RUN lines stay as they are (the option is tested in
`test/hls-est/Passes/auto_pipeline_float_loads.mlir` in both settings).

## M9 — cgeist: may unsigned 32-bit index arithmetic be assumed not to wrap? (`-affine-cfg-assume-nowrap-width`)

**Question.** Since cgeist round 4 (Polygeist 763b0046 + review fixes cbc105e0), AffineCFG turns integer add / sub / mul
into affine index expressions only when the exact result provably fits its type, except for integers of at least
`-affine-cfg-assume-nowrap-width` bits (hidden option, default 32), which are raised without a proof as before. For
signed `int` that matches C (overflow is undefined). For `unsigned int` it does not: unsigned arithmetic wraps, and the
IR (`arith.addi/subi/muli` on i32) cannot tell the two apart. Reproducer from the round-4 recheck (wrong with every
cgeist binary so far, correct with width 64):

```c
void t1(int A[8], int O[8]) { for (unsigned i = 0; i < 4; i++) O[i] = A[(i * 0x7FFFFFFFu) / 0x7FFFFFFFu]; }
// cgeist: affine.load %arg0[%iv] -> reads A[3] at i = 3; C reads A[0] (3 * (2^31 - 1) wraps to 2147483645)
```

**Options.**

| option | C semantics | effect on the harness (112 designs, scalar shim) |
|---|---|---|
| keep 32 (current) | wrong only for unsigned 32-bit arithmetic that wraps inside an index | none |
| 64: every i32 add / sub / mul needs a range proof | exact | 19 designs' cgeist output changes (forgebench attention / attn_breakdown / conv / gpt / llama / tiled_attn / diff_dims_module_small, spector_hls dct / fir): index arithmetic on `int` arguments such as `h * 4 + j` becomes a non-affine `memref.load`; all 112 statuses and BRAM totals unchanged |
| frontend marks signed arithmetic as non-wrapping (`overflow<nsw>` flags), AffineCFG trusts only those | exact for unsigned, keeps signed `int` affine | expected: none (not implemented; a cgeist change of moderate size) |

**Related, from the same reports (not wrong code):** a narrow counter passed to a call is treated as read both
signed and unsigned, so a loop whose counter crosses 2^(N-1) and is passed to an external function keeps an iter_arg;
narrow `*=` computes in `int` + `trunci` again, so an in-range narrow product (`k *= 8`) is no longer affine.

**Recommendation.** The third option is the faithful one and keeps today's IR for signed code. Until then keep 32;
switching to 64 costs nothing in BRAM today but makes 19 designs' accesses non-affine, which weakens banking and
scheduling. Evidence: CHANGELOG entries for Polygeist 763b0046 and cbc105e0; probes in the session scratchpad `r4\`,
`r6\` and `verify3\`.

## M10 — O15: assignable bit and range selects (`x.range(h, l) = v`): what they do and what supporting them takes

**What the source code does.** In Vitis' `ap_int` / `ap_uint` / `ap_fixed`, the calls `x.range(h, l)`, `x(h, l)`,
`x[i]`, `x.bit(i)` and the concatenation `(a, b)` return small proxy objects (`ap_range_ref`, `ap_bit_ref`,
`ap_concat_ref`, `af_range_ref`). A proxy holds a reference to `x` plus the bit positions. Reading it gives the bits
as a value. Assigning to it (`x.range(15, 0) = v;`) is a read-modify-write of `x`: clear bits h..l, OR in `v`
shifted to position l, write `x` back. Designs use this to pack narrow values into wide words:

| design group | example line | what it packs |
|---|---|---|
| soda (11 designs) | `dram_*_buf(255, 240) = Reinterpret<ap_uint<16>>(...)` | sixteen 16-bit values into one 256-bit memory word |
| accelerators Mask-Net_dataset, SkyNet_dataset | `DATA.range(FM_RG + 16*c, 16*c) = d.range(FM_RG, 0)` | feature-map lanes into wide DATA words |
| vitis_examples/01 fixed_point_sqrt | `result.range(W2-1, 0) = ap_uint<W2>(q >> 1)` | the low bits of a fixed-point result |
| 9 class_ece8893_spring_2025 labs | `temp.range(16*(jj+1)-1, 16*jj) = bits` | 16-bit lanes into a wide word |

**Why it matters for BRAM.** These arrays hold wide words (often 256 or 512 bits), so their BRAM count depends on the
exact word width, and each range write is a load plus a store of the whole word, which decides how many ports the
array needs (single- vs dual-port RAM, replication).

**Why these designs fail today.** All 23 stop in cgeist under every shim. `scalar` and `exact` turn `ap_uint<256>`
into a plain integer, which has no `.range()` at all. `exactclass` has `.range()` that returns a value, so reading
works, but assigning to it is a compile error (`no viable overloaded '='`). 14 of the 23 have Vitis ground truth
(the 11 soda designs, Mask-Net, SkyNet, fixed_point_sqrt); the 9 class labs do not.

**What supporting it takes** (both parts behind the existing opt-in `--scalar-wrapper-abi`, so nothing else changes):
1. *Shim:* give `exactclass` real proxy classes: a pointer to the word plus h and l, with an always-inlined
   `operator=` that does the read-modify-write on the word's integer, and reads that convert to a value.
2. *cgeist:* after inlining, the proxy is a small struct (pointer + two ints) in a local slot. Polygeist does not
   split such struct slots into scalars today, so a small scalar-replacement step for proxy-shaped structs is needed;
   then the code becomes `load word; and with mask; or (v << l); store word` on an `iW` array, which is the form
   Vitis' own front end produces and hls-est already handles.
3. *Check:* compile one soda design and SkyNet, confirm the MLIR has plain `iW` arrays and the read-modify-write, run
   hls-est and compare per array with Vitis; add the shim cases to `check_shim_cgeist.py` (bit-exact against the real
   Vitis headers).

**Expected effect.** 14 designs with ground truth become comparable (today they read "cgeist error"); whether they
match Vitis is not known until they run. No effect on any design that compiles today.

**Recommendation.** Yes, as a time-boxed experiment on one soda design and SkyNet first (steps 1-3), run after the
W3 cgeist work (one frontend change at a time). If the scalar-replacement step turns out large or fragile, stop and
report; the 23 designs then stay excluded as "cgeist error". Waiting for your OK on this plan.

## M11 — Globals: bank them in place (adopted), attribute their accesses or promote them to allocas (not adopted) (W7 item 4, 2026-10-11)

**Question.** hls-doc/forgebench-gap.md C2: a `memref.global` was one unbanked, unattributed RAM_1P (OPEN_ISSUES O4). Three routes: (1) bank globals in place by their own pragma and the pragmas of the parameters they reach and keep pricing them without access attribution; (2) additionally `--bram-attribute-globals` (port demand, replication through the get_global sites, as for an alloca); (3) `--promote-globals-to-allocas --bram-attribute-globals` (MEMOS M5's "globals as locals").

**Measurement.** One binary (`~/hls-est-work/w7/bin/hls-est.a6`, md5 24137668..., W7 items 1-3), the MLIR of `w3g/r/x_g3.json` (installed cgeist 2ec1956c, exactclass), the whole Polygeist catalogue (787 designs, 95 with Vitis ground truth; the harness subset is 89 of them). Route (1) is the W7 default (`w7/r/a6.json`); (2) appends `--bram-attribute-globals` (`a7.json`); (3) adds `--promote-globals-to-allocas` before `--dead-memory-elimination` plus the flag (`a8.json`, MEMOS M5's placement).

| run | subset exact / 89 | subset \|err\| | catalogue exact / 95 | catalogue \|err\| | forgebench exact / 40 | forgebench \|err\| |
|---|---|---|---|---|---|---|
| before W7 (x_g3, hls-est bcfb9bb3a) | 55 | 5243 | 56 | 5631 | 10 | 5096 |
| (1) W7 default: banked in place | **68** | **1567** | **70** | **1952** | **23** | **1420** |
| (2) (1) + `--bram-attribute-globals` | 68 | 1655 | 70 | 2037 | 23 | 1508 |
| (3) (1) + promotion + attribution | 65 | 2235 | 67 | 2611 | 20 | 2088 |

Per design (forgebench rows that differ anywhere; bold = Vitis):

| design | Vitis | x_g3 | (1) | (2) | (3) |
|---|---|---|---|---|---|
| Llama_GPT_module | 30 | 25 | 25 | 123 | 123 |
| attention_op_p2 / p3 | 24 | **24** | **24** | **24** | 206 |
| attn_breakdown_module / op2 | 17 | 13 | 13 | 13 | 69 |
| attn_breakdown_op1 | 10 | 11 | 11 | 11 | 67 |
| conv_A | 594 | 99 | 99 | 99 | 995 |
| gpt_transformer_p1 | 28 | **28** | **28** | **28** | 84 |
| llama_transformer_p2 | 30 | 25 | 25 | 25 | 81 |
| mult_op_p2 / p3 | 2 | 4 | 4 | 4 | 32 |
| diff_dims_p1 / p2 / p3, diff_orders_p1 / p2 / p3, testing_impl, vec_mtx_p1, vec_mtx_module | 210 / 114 / 354, 130 / 2 / 514, 2, 2, 2 | 162 / 66 / 194, 22 / 11 / 34, 6, 4, 12 | **all = Vitis** | **all = Vitis** | **all = Vitis** |

Outside forgebench only class_ece8893_2023_spring ECG_Classifier Baseline moves (198 -> 201 with (2), 207 with (3); Vitis 357).

**Why (2) and (3) lose.** Per array: in Llama_GPT_module (2) makes `FF_weights_2` 4 -> 60 and `BRAM_weights_q` / `k` / `v` 1 -> 15 (RAM_1WNR, 15 copies) where Vitis has 4 / 1 each: the reads sit in loops of callees Vitis keeps as modules (`grouped_multihead_attention_*`, the feed-forward), which hls-est sees inlined or as pipelined loops of the caller. OPEN_ISSUES O17 item 1 (Vitis does not replicate a global its sub-modules read through ports; unconfirmed as a rule). (3) adds the same on every global it promotes (attention_op_p2 / p3 `BRAM_weights_*` 4 -> 60) and conv_A's `BRAM_conv_weight` 64 -> 960: promoted, read 16 times per iteration, but still unpartitioned because cgeist lost the pragma when it inlined `conv2d` (O39).

**Adopted (decision #46 under #36).** Route (1): `--memory-banking-bram` banks globals in place (W7 item 1, #44), and constant-initialised globals are priced as ROMs through their get_global sites without the flag (W7 item 3, #45). `--bram-attribute-globals` and `--promote-globals-to-allocas` stay opt-in. Revisit when O17 item 1 is modelled (no replication of an array for the loops of a callee Vitis keeps as a module) and O39 is fixed; then measure (2) again.

## M12 — Real Vitis headers through cgeist vs the exactclass shim

**Question** (Peter, 2026-10-11): "should you get the real headers instead of relying on a shim which is better".

**Status.** Peter has already chosen the direction. Decision #39 says cgeist compiles designs against the real
2025.1 headers in synthesis mode, and exactclass stays the default until `--shim real` matches or beats it
(MEMOS.md:48). Decision #40 allows copying Xilinx's Apache-2.0 front-end files (MEMOS.md:49). Decision #41 makes speed
a requirement (MEMOS.md:50). This memo does not reopen #39. It records the evidence from the W11 inventory and probe,
corrects four facts in #39's text, scopes what the real headers can and cannot fix, and gives the staged plan with
a go/no-go experiment. Evidence files: `scratchpad/realhdr/inventory.md`, `scratchpad/realhdr/probe.md`, artifacts under
`~/hls-est-work/realhdr/`.

### Short answer

Yes, for `ap_int`, `ap_fixed`, the fixed-point `hls_math` and `hls_vector`. The real headers are better there,
because they are by definition what Vitis compiles, and they carry the header pragmas (BIND_STORAGE on the math
tables) that no shim reproduces. But the installed cgeist cannot use them today. In synthesis mode every ap design
fails, and once the hard errors are hidden, every ap value silently becomes `i32`. Making them work needs a patched
embedded clang. As measured, the real headers also parse 18–115x slower than exactclass, which conflicts with the
speed goal (#41) until the cause is found. Streams, tasks, `ap_float` and the FFT IP need new hls-est models
whichever headers are used. The real headers make those designs parse. They do not make them estimable.

### Corrections to the facts in decision #39

1. **Include directory.** Vitis synthesis passes `-I .../common/technology/autopilot`, not `Vitis/include`
   (`autopilot.flow.log:331` in `vitis-cache/polybench/atax/36433f38cda6d555/db/`). The full line is
   `-fhls -D__VITIS_HLS__ -DAESL_SYN -D__SYNTHESIS__ -D__HLS_SYN__ -include etc/autopilot_ssdm_op.h -D__DSP48E1__`.
   Eight headers differ between the two trees (`rh_hdrdiff.sh`). `Vitis/include/hls_stream.h` is the simulation
   model (`X_HLS_STREAM_SIM_H`, with `<thread>`, `<mutex>`). The synthesis model is `autopilot/hls_stream_39.h`.
   The 68 other headers, all ap_* included, are identical.
2. **`ap_common.h:252` is dead code for us.** The `1024*mode` width encoding sits in the clang-3.1 branch
   (`etc/ap_common.h:239`). Clang 18 takes the `#else` at :523. The active storage is `ssdm_int<N,S>` with
   `int/unsigned V __attribute__((bitwidth(_AP_N)))` (`:529-542`).
3. **hls_math is not blocked by intrinsics.** `hls_math.h` and the `etc/hls_*_apfixed.h` headers have no direct
   `__fpga_*` use (grep count 0, probe section 1). They are blocked by `__fp16` arguments and returns
   (`ap_common.h:632`, `hls_half.h:12`) and by cgeist's pragma parser (`HLSPragmaParse.cc:327` rejects the qualified
   `variable=fourth_order_double::sin_cos_K0` at `etc/hls_hotbm_apfixed.h:91-95`). The float `hls_math` functions are
   only declared (`hls_math.h:577-601`); their bodies are in the closed `libhlsm_39.bc`, which we may not read.
4. **Builtin count.** `autopilot_ssdm_bits.h` has 15 lines with `__builtin_bit` (`grep -c`). The ap headers reach the
   builtins through the `_AP_ROOT_op_*` macros (`ap_common.h:645-661`): about 173 uses. In the 9 probe kernels clang
   reports 1336 undeclared-builtin uses (`errinv.txt`).

### Evidence

**The installed cgeist with the real headers** (probe; cgeist md5 6ff60ea1, hls-est md5 071f97ba):
- *Synthesis mode:* all 8 ap/hls micro-kernels stop at the 20-error limit. The causes are 12 undeclared
  `__builtin_bit_*` builtins, `__fp16` arguments, and (with the autopilot tree) `__fpga_fifo_*`.
- *Synthesis mode with a probe prelude* that declares the builtins as opaque functions and maps `__fp16` to
  `_Float16`: clang parses all 9 kernels. cgeist then **silently drops every width**. `bitwidth` is ignored with one
  warning per template. ap_int<17>, ap_int<34>, ap_uint<256> and ap_fixed<16,5> all become `i32`. `ap_int<12>[1024]`
  becomes `memref<1024xi32>`, and hls-est reports 2 BRAM_18K where exactclass gives 1. No error is raised. Design
  `vitis_examples/05 ap_arithmetic` gets `i32` for every argument, ap_int<33> included. Every bit or range operation
  becomes an opaque call on a local's address, which hls-est rejects.
- *Without `__SYNTHESIS__` (ap_private):* clang parses everything. cgeist asserts (`ValueCategory.cc:154`,
  `Casting.h:578`) or emits `memref<!llvm.struct<...>>` with widths rounded to C types (k3: 13052 lines against
  478 with the shim). hls-est rejects all of it.
- *Designs:* the four that pass under the real headers are plain C (byte-identical MLIR to exactclass). The one ap
  design that passes under exactclass (forgebench/attention_op_p1, 73 = Vitis) fails under every real-header
  configuration.

**The exactclass shim today.** 1667 lines (`wc -l shim/exactclass/*`), validated bit-exact against g++ with the real
headers by `check_shim.py` (417 lines) and `check_shim_cgeist.py` (334 lines). It is the only configuration that gives
correct widths for ap designs today. Its gaps, from the W8a sweep (`hls-doc/hlsfactory-v2.md`, failure table):

| class | designs | what the real headers would do |
|---|---:|---|
| `shim-range-select` (assignable `range()`) | 27 | the real `ap_range_ref` exists (`etc/ap_int_ref.h:295-297`); fixed only if cgeist reduces the proxy (pointer + two ints) to scalars, the same open step as M10 step 2 |
| `missing-vendor-header`: `hls_fft.h` 16, `hls_task.h` 1, `ap_float.h` 1 | 18 | parse once F2/F6/F7/F11/F14 work; estimation needs an FFT IP model, a task/dataflow model, and `llvm.fpga.float.*` costs |
| `needs-synthesis-macro` | 18 | fixed: the flow defines the macros |
| `shim-hls-api` (stream, vector, math) | 11 | vector and fixed-point math fixed after F1/F2/F4/F7; streams need `__fpga_fifo_*` lowering and a FIFO model |
| `shim-std-include` | 5 | fixed: the real headers include `<stdint.h>`, `<cmath>` and so on (`hls_math.h:26-29`) |
| `shim-ap-feature` | 4 | fixed: the real class has every member |

The sweep total is 483 failing designs. The largest class, `hlsest-parse` (334), is unchanged by any header choice.

**Compile time** (this step, `scratchpad/rh_memo_time.sh` and `rh_memo_time2.sh`, clang 18 `-fsyntax-only` from
Polygeist's llvm-project build, which is `CMAKE_BUILD_TYPE=DEBUG` with assertions (`llvm-project/build/CMakeCache.txt`);
the machine was shared, load average 20 on 32 cores at 04:48). Absolute times are inflated by the debug build and the
load. The ratios are the evidence.

| kernel | real headers + prelude | exactclass |
|---|---:|---:|
| k1 ap_int<17> arithmetic, 3 runs | 34.0, 47.5, 40.4 s | 2.07, 2.44, 2.29 s |
| k4 ap_int<12>[1024], 3 runs | 41.9, 35.2, 33.6 s | 2.14, 2.26, 1.62 s |
| k6a hls::sqrt/exp on ap_fixed, 1 run | 434.8 s | 2.76 s |

The split (`realhdr/memo_time2.txt`, one run each) shows the cost is parsing, not reading `/mnt/a`:

| kernel | preprocess real (reads `/mnt/a`) | preprocessed lines real / shim | parse `.ii` real | parse `.ii` shim |
|---|---:|---:|---:|---:|
| k1 | 8.8 s | 7926 / 866 | 32.2 s | 1.7 s |
| k6a | 1.6 s | 30234 / 7857 | 836.4 s | 7.3 s |

The real headers give 4–9x more lines but 18–115x more parse time. Something in them (template instantiation or
constexpr evaluation, perhaps made worse by the prelude's opaque builtins or by the ignored `bitwidth`) is superlinear.
The cause is **unconfirmed**. The same debug clang libraries are linked into cgeist, so cgeist pays the same cost.
Decision #41 asks for a source-change median under 2 s. Exactclass is already near that bound; the real headers, as
measured, are 1–2 orders of magnitude away from it. Two levers exist and are both untested: a release build of the
embedded clang (helps every configuration), and a precompiled header per (header set, flags) built once in a private
work directory (a derived file, never checked in).

### Options

**(1) Keep exactclass and fill its gaps by hand.**
- *Effort:* proxy classes for `range()`/bit refs plus a cgeist scalar-replacement step (M10, both unbuilt); stand-in
  headers for `hls_fft.h`, `hls_task.h`, `ap_float.h`, `hls::vector`, `hls::stream` and the std includes. Each is
  new shim code, about 100–500 lines each (estimate, unmeasured).
- *Risks:* semantics are only as exact as the differential tests cover. The header pragmas in the fixed-point math
  (26 `BIND_STORAGE`, 110 `unroll`, 55 `pipeline`, 10 `array_partition`; inventory F7) are lost, so a math table's
  storage kind comes from hls-est's own rules or from the per-core cost of N16. Every Vitis header change means
  shim work. Licence is clean (our own code).
- *Fixes:* range 27 (after M10 step 2), ap-feature 4, std 5, synthesis-macro 18 (harness flags), API 11 partly.
  The 18 missing-header designs only as stand-ins.
- *Against:* Peter rejected maintaining a shim per header (#39). Not recommended.

**(2) Real headers in synthesis mode, with cgeist support for the Xilinx extensions.**
- *Components:*
  - Harness and driver: `-I .../autopilot`, the five `-D` macros, `-include etc/autopilot_ssdm_op.h`, gnu++14
    mode for `typeof`, native half arguments and returns. Tens of lines.
  - F1, `bitwidth(N)` as `_BitInt(N)`, including a template-dependent N (clang 18 has `DependentBitIntType`): a patch
    to the embedded clang (`Attr.td` entry plus a `processTypeAttrs` case), about 50–150 lines. Polygeist's
    llvm-project becomes a fork, and the clang libraries must be rebuilt. Under `--shim real` an unknown or ignored
    `bitwidth` must become an error, because today it fails silently.
  - F2, the 12 bit builtins: intercept the calls in cgeist and emit `arith` shift/mask/trunc/ext, taking the width
    from the operand before its `(void*)` cast. About 300–600 lines plus tests. hls-est needs nothing new.
  - F7, the pragma parser: accept qualified `variable=` names and `variable=this`. Small to medium.
  - F6 `no_ctor`, F8 `_ssdm_op_*` calls: ignore or interpret. Small.
  - The ValueCategory/Casting asserts behind the parse errors: unknown size.
  - F9 streams: `__fpga_fifo_*` lowering plus a FIFO model in hls-est. Medium to large, a modelling track.
  - F10 tasks, F11 `ap_float`, F14 FFT IP, F12 float math: new hls-est operations and resource models. Large; each
    is its own track. F12 already has the N16 per-core model through external calls.
- *Risks:*
  - Semantic exactness. `bitwidth` types up to 32 bits promote to `int`, 33–64 bits to `i64`, wider ones not at all
    (hls-llvm-project `SemaExpr.cpp:743-756`). `_BitInt` never promotes. The ap binary operators widen both operands
    first (`ap_int_base.h:1465-1471`), which hides most of this. Shifts, compares and `ap_fixed` quantisation on the
    raw `V` are unconfirmed. Differential testing must cover them.
  - Width exactness: exact by construction once F1 lands. Today it is silently wrong, which is the worst failure mode.
  - Compile time: the measurement above. This is the largest risk against #41.
  - Upstream compatibility: a clang fork inside Polygeist, kept across LLVM bumps. Rebuild cost: the clang libraries
    on `/mnt/d` link slowly; build objects with ninja and link on ext4.
  - Licence: allowed by #40 for the Apache-2.0 Xlx files. Implementing independently is simpler, because H's
    `APIntType` AST node on LLVM 7 does not carry over to clang 18. The Vitis headers ("All Rights Reserved") are
    never copied; lit tests point at the install and are UNSUPPORTED without it, or use the Apache-2.0
    `HLS_arbitrary_Precision_Types` headers.
- *Fixes:* synthesis-macro 18, std 5, ap-feature 4, API 11 except streams, range 27 if the proxy reduces to scalars.
  Missing-header 18 parse only.

**(3) Hybrid: exactclass for ap_int/ap_fixed, real headers for hls_math, hls_fft and the rest.**
- *Effort:* the include order puts the shim's `ap_fixed.h` before the real one. The real fixed-point math headers use
  only the public ap API: no `_ssdm_`, `_AP_ROOT`, `__builtin_bit` or `.V` uses (grep count 0 over
  `etc/hls_*_apfixed.h`, this step). They still need `__fp16` arguments (`hls_half.h`), the pragma-parser fixes, and
  whatever ap members exactclass lacks.
- *Risks:* two semantic sources mixed in one design. Shim maintenance for ap_* stays, which #39 rejects. The real
  `hls_fft.h`, `hls_stream_39.h` and `ap_float.h` use `__fpga_*` builtins and `no_ctor` directly, so the hybrid does
  not help them.
- *Fixes:* the fixed-point math part of `shim-hls-api`, and the header pragmas of the math tables. Nothing else.
- *Use:* as a stage of option 2, not as an end state.

**(4) What the evidence suggests instead: option 2, staged, with exactclass as the oracle.**
- Keep exactclass frozen as the reference. Every real-header MLIR is compared with the exactclass MLIR on the designs
  both compile: same element types, same per-array BRAM. This catches silent width loss at once.
- Rejected alternatives:
  - Use Xilinx's own clang (hls-llvm-project) to produce LLVM IR and import it into MLIR. hls-est needs
    affine/memref, and the LLVM-dialect import gives neither. It would also need a second compiler build.
  - Use Vitis's own `a.g.ld.5.gdce.ll`. That needs a Vitis run per design, which defeats #41.
  - ap_private mode. It never gives MLIR that hls-est accepts, and its widths are rounded to C types.

### Validation (all options)

1. **Bit-exact semantics.** Lower cgeist's MLIR, run it on random and edge inputs, and compare every output buffer bit
   for bit with g++ built against the real headers (C-simulation semantics). Extend `check_shim_cgeist.py` to a
   `--shim real` mode. Include kernels that target promotion: shifts by more than the width, signed compares across
   widths, `ap_fixed` RND/SAT on 31-, 32-, 33- and 64-bit boundaries, and range selects with Lo > Hi.
2. **Widths.** Compare the element type of every memref with the alloca or global type in Vitis's
   `db/a.g.ld.5.gdce.ll` (534 cached captures) and with the csynth memory-table word width.
3. **BRAM.** The harness under `--shim real` against exactclass and Vitis, per array. Rule 4 applies.
4. **Speed.** cgeist wall time per design, median and p90, against exactclass (#41).

### Recommendation

Take option 2 in stages, with option 4's oracle, by the criterion best-replicates-Vitis (#36, #39). Exactclass stays
the default until stage 3 passes. No new shim code is written.

- **Stage 0 (done).** Inventory and probe: the gaps are known and the installed cgeist cannot use the real headers.
- **Stage 1a, cheap, no rebuild.** Find the parse-time cause: `-ftime-trace` on the saved
  `realhdr/memo-time/{k1_apint17,k6a_math_fixed}.real.ii`, and the same parse with a release clang 18 if one is on the
  machine. If the cost is in code the F1 patch changes (for example, overloads that collapse when every width is
  `i32`), stage 1b re-measures it; if it is inherent to the headers, a precompiled header is the remedy to test.
- **Stage 1b, go/no-go experiment, private cgeist build only.** Patch the private embedded clang for F1 (`bitwidth` →
  `_BitInt(N)`, dependent N included, ignored attribute is an error under `--shim real`), add F2 (bit builtins to
  `arith`), native half arguments, and the two pragma-parser fixes. Point at the autopilot tree with the flow's
  macros. Run the 9 probe kernels, `vitis_examples/05 ap_arithmetic`, `vitis_examples/01 fixed_point_sqrt` and
  `forgebench/attention_op_p1`.
  - **Go** if all of these hold: (a) every ap value has the exact `iN` width, equal to exactclass and to Vitis's
    `a.g.ld.5.gdce.ll`; (b) the differential check is bit-exact on all 9 kernels; (c) attention_op_p1 gives 73 with
    the same per-array split as exactclass; (d) fixed_point_sqrt reaches hls-est as plain `iW` memrefs (the
    `ap_range_ref` question); (e) cgeist wall time on each of these designs is at most 2x exactclass, with a
    precompiled header if needed.
  - **No-go** if F1 needs more than about 300 lines or breaks template deduction, or if compile time stays more than
    5x exactclass with precompiled headers. Then stop, report, and keep exactclass as the default; the 18
    synthesis-macro and 5 std-include designs can still be fixed by harness flags alone.
- **Stage 2.** The fixed-point math and `hls::vector` (the header pragmas reach hls-annotate). Then the range-proxy
  scalar replacement if (d) failed. Re-run the HLSFactory_v2 sweep under `--shim real`.
- **Stage 3.** The harness subset under `--shim real` against exactclass and Vitis. Switch the default when `real`
  has at least as many exact designs and no unexplained per-array regression (rule 4); freeze and retire exactclass
  after that, as #39 says.
- **Stage 4, separate modelling tracks, each with its own memo.** Streams (FIFO model), `hls::task` (dataflow),
  `ap_float`, the FFT IP. The real headers are a precondition for these, not a solution.

**Cost of the switch.** Changing the default shim changes the input of every ap design, so every baseline is re-run
once at stage 3 (as for O6).


**Coordinator addendum (2026-10-11).** Speed is part of W11's go/no-go (#41). `--shim real` replaces exactclass only if its cgeist compile time on the harness is acceptable against #41's targets (median under 2 s for a source change), with a release-built clang and, if needed, a precompiled header, and the cause of the superlinear parse time found. The DSE latency study (M14) measures real against exactclass when it resumes.

## M15 — Phase 6 plan (DSP, FF, LUT; decision #56)

| memo | pointer | status |
|---|---|---|
| M15 | `hls-doc/design/phase6-plan.md`: category shares, the model and Vitis evidence per category, the kernels still needed, the mapping onto the P2 scheduling interfaces (#37, memo section 8.7), the stages S0-S6 with in-band ceilings, the risks, the harness / compare / make_compare_csv extensions and the position against W9 and P1-P3. Studies: `~/hls-est-work/coord/scratch/p6/{ground-truth-anatomy,cost-tables,hlsest-capabilities}.md`. Open decisions: cost-table delivery under #42, P2-sched first, the under-count policy, when `hls.state` may change BRAM. | plan written, waiting for coordinator sequencing |
