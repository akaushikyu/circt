# Decision memos for Peter (nothing here is applied; CLAUDE.md "Pending decisions")

Numbers are from parsed harness outputs; "subset" = polybench, polybench_pragmas, forgebench, machsuite, spector_hls,
vitis_examples (73 compared designs) at hls-est 22d473858 unless stated. They will be refreshed after T4/T5 land.

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
