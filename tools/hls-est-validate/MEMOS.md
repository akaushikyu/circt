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

## M3 — frontend changes beyond C-semantics fixes (O10, O5, route A)

- **O10:** cgeist inlines callees marked `#pragma HLS inline off`; Vitis keeps one instance and charges its arrays once.
  Proposed fix: honour the pragma in cgeist (no inlining; keep the call) and let hls-est count the callee's memories once.
- **O5:** cgeist hoists invariant inner loops at every `-O`; Vitis does not before its flatten decision. Proposed fix:
  an option to disable that hoist for HLS inputs.
- **Route A:** lower classes with one scalar member (through base classes) to the scalar in cgeist, so an integer-backed
  `ap_fixed`/`ap_int` shim gives `iW` memrefs and bit-exact folds (design in `~/hls-est-work/feas/A/design.md`; the
  alternative, scalarizing struct memrefs inside hls-est, needs about 2000 lines). Lands as `--scalar-wrapper-abi`
  (off by default) plus the harness-local shim `exactclass`; the attention Q/K dead-code case (CLAUDE.md priority 1)
  depends on it. Not covered: assignable range references (`x.range(h,l) = v`, 125 corpus lines).

Each needs Peter's OK before it becomes default behaviour of cgeist or of the harness.

## M4 — BRAM formula defaults (priority 4)

To be written from the open-source reconciliation (N8) when it lands: which of N6's rules the `queryBRAM` source agrees
with, where the 2025.1 binary differs, and whether any default constant in hls-est should change.

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
