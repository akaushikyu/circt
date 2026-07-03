# hls-est vs. Vitis HLS BRAM matching — report (draft, numbers updated at the end)

Branch `hls-est-vitis-match` in `~/circt`; frontend changes on branch `hls-est-vitis-match` in `D:\HLS\Polygeist`.
Companion files: `CHANGELOG.md` (every change), `VITIS_NOTES.md` (every confirmed Vitis rule), `OPEN_ISSUES.md`,
`hls-est-results.xlsx` (final), `baseline.xlsx` (before any change), `experiments/results.csv` (pipeline sweep).

## 1. Ground truth

- Vitis HLS 2025.1 (Windows install on A:, driven from WSL), `xc7z020clg400-1`, 10 ns, `flow_target=vivado`,
  `syn.array_partition.throughput_driven=off` — the configuration of Peter's `compilehlskernel.ps1`, which
  reproduces the regression-gate numbers (atax = 13). The 2025.1 default (`auto`) gives different numbers on 34 of
  131 designs (atax 68); both are in the spreadsheet (`vitis td=auto` sheet).
- Corpus: HLSFactory designs harvested under `Polygeist/tools/cgeist/Test/HLS/hlsfactory/Inputs` (catalogue from the
  `.test` files). Core datasets: accelerators, chstone, flowgnn, forgebench, machsuite, polybench, polybench_pragmas
  (the inline-pragma variants under `Test/HLS/polybench`), rosetta, soda, spector_hls, vitis_examples — 143 designs,
  131 synthesized (10 fail on vendor headers / URAM on Zynq-7000, flowgnn/gat exceeds 1 h).
- Per-array ground truth: every `*_csynth.rpt` memory table (banks grouped), csynth.xml totals and utilization,
  loop tables, the transformation log, and the `.autopilot/db` IR stages (disassembled) are cached under
  `~/hls-est-work/vitis-cache`.

## 2. Results

| stage | compared | exact | total abs error | hls-est failures |
|---|---|---|---|---|
| baseline, canonical pipeline (before any change) | 42 | 24 | 1105 | 89 |
| baseline, base pipeline | 74 | 31 | 8078 | 57 |
| T1 + T2 (perf + storage model), canonical | 66 | 32 | 1544 | 65 |
| T1 + T2, canonical without `--infer-vitis-split-array` | 64 | 38 | 782 | 67 |
| final (T3 + T4 + T5 + coverage + chosen pipeline) | TBD | TBD | TBD | TBD |

Per-dataset counts, the per-array comparison and the mismatch list with diagnosed causes are in the spreadsheet.

## 3. What Vitis does that hls-est did not model (all confirmed with standalone kernels; VITIS_NOTES.md)

1. Dead arrays: plain LLVM DCE/DSE at the first optimisation stage seeded from the outputs; `ap_fixed` constant folding
   (`(ap_fixed<16,5>)16 = -16`, `sqrt(-16) = 0`, `1/0 -> 0`) kills Q, K and their weight globals in the attention kernel.
2. Automatic pipelining: `pipeline_loops = 64`; a loop is pipelined iff every nesting path inside it has a trip-count
   product <= 64 (then everything inside is unrolled); perfect nests are flattened, never unrolled; imperfect parents are
   converted and flattened around a single pipelined child.
3. Memory replication (`RAM_1WNR`): copies = ceil((R+W)/II) - 1, capped at 16, never when a loop body stores twice.
4. BRAM_18K per bank: RAMB18 aspect modes with parity (x9/x18/x36), power-of-two depth, x36 only with one live port.
5. LUTRAM boundary: `Words * Bits >= 1024` (inclusive, exact width).
6. Partitions with td=off: arrays <= 4 elements and constant-index dimensions are still partitioned automatically;
   explicit pragmas and reshape as documented.
7. Globals behave like locals; `m_axi` read bundles cost 2 BRAM (32-bit, default bursts); arrays are charged once to the
   module of their lowest common accessor.

## 4. What changed in hls-est (details and numbers per entry in CHANGELOG.md)

- Debug mode `--bram-debug` / `--bram-debug-json` (per-memref derivation, no estimate change), bank provenance attributes.
- Performance: constant bank folding in banking, fast resource-bound modulo scheduler for large bodies, dependence-analysis fixes.
- Storage model: LUTRAM threshold, aspect modes, replication, 17-slot port model, invariant-load hoist, same-address load CSE.
- Pipeline decision (T3), dead-memory elimination + Vitis folds + globals + m_axi (T4), td=off partition inference (T5): TBD.
- Frontend (needs Peter's sign-off): cgeist lowers `_Float16`/`_BitInt(N)`; unsigned index casts, compound assignments,
  APInt folds, typedef signedness; width-exact shim `shim/exact`. Exact fixed-point semantics: route decision TBD.

## 5. Pipeline experiments

TBD (experiments/results.csv): ablation, reordering, added standard passes, option sweeps; the recommended global pipeline
and the reason for each pass's effect.

## 6. Open items and honest caveats

- `tiled_attn_module` base-pipeline total changed 600 -> 1321 between the baseline and the debug-mode commits (to bisect).
- Designs not compared: TBD list with reasons (cgeist crashes on class code, Polygeist-only ops, timeouts).
- Exact `ap_fixed` semantics end to end: TBD.
