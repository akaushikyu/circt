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
