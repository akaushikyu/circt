# Vitis HLS 2025.1 behaviour notes (xc7z020clg400-1, 10 ns, throughput_driven=off)

Each entry: the rule as observed, the minimal kernel(s), the evidence (report /
log / IR lines), and whether hls-est models it. "confirmed" = reproduced with a
standalone kernel; "unconfirmed" = seen in benchmark output only.

Artifacts referenced below live in `~/hls-est-work/vitis-cache/<dataset>/<benchmark>/<hash>/`
(benchmarks) and `~/hls-est-work/experiments/<name>/<hash>/` (standalone kernels):
`report/*_csynth.rpt`, `log/hls_compile.log`, `db/a.g.ld.5.gdce.ll` (after the
clang-7 frontend + global DCE), `db/a.o.{1,2,3}.ll` (HLS optimisation stages).

## N1. Dead producer arrays are deleted before BRAM allocation (confirmed on the attention kernel)
- **Rule:** an array whose stored values cannot reach a top-level output is removed entirely (no memory, no BRAM), together with the computation feeding it. In forgebench `attention_op_p1`, `scale = (ap_fixed<16,5>)1.0 / hls::sqrt((ap_fixed<16,5>)16)` folds to a value that makes `scores[i][j] *= scale` a `store i16 0`; Q and K then feed nothing and are deleted, and so are the globals `BRAM_weights_q`/`BRAM_weights_k` that only fed Q and K.
- **Evidence:** `manual/attention_op_p1` run: `db/a.g.ld.5.gdce.ll` still has `%Q`, `%K` allocas (1 each) and the four `@BRAM_weights_*` globals; `db/a.o.1.ll` has no `%Q`/`%K` at all and `db/a.o.3.ll` keeps only `@BRAM_weights_v`, `@BRAM_attn_input`, `@BRAM_1` (`store i16 0, i16* %scores_addr` at a.o.3.ll:413). `top_csynth.rpt` memory table lists only `BRAM_attn_input_U` (2), `BRAM_1_U` (2), `BRAM_weights_v_U` (64). Total 73 BRAM (td=off), of which 2 are the `mem1_m_axi` adapter.
- **Headers:** with the real `ap_fixed.h`, `(ap_fixed<16,5>)16` has raw bits 0x8000 = -16.0 (AP_WRAP), `hls::sqrt(-16.0)` returns raw 0, and `1.0/0` traps in software (SIGFPE); the synthesized constant is whatever the fixed-point divider returns for /0 (to be read from `a.o.3.ll`).
- **hls-est:** not modelled (no dead-array elimination; globals always counted). Pass to add: a dead-memory elimination seeded from top-level outputs, plus fixed-point constant folding in the frontend shim/IR (CLAUDE.md step 2).

## N2. throughput-driven array partitioning changes everything (confirmed)
- **Rule:** with the 2025.1 default `syn.array_partition.throughput_driven=auto`, an array read R times per iteration of an auto-pipelined loop is partitioned (`[HLS 214-270] Inferring pragma 'array_partition type=complete dim=2' for array 'buff_A' due to pipeline pragma`), e.g. plain polybench/atax: buff_A -> 64 banks of 64x32 = 64 BRAM, total 68. With `off` (Peter's configuration, used for all ground truth here) buff_A stays one 8-BRAM RAM and the loop runs at II 32-36.
- **Evidence:** `vitis-cache/polybench/atax/36433f38cda6d555` (auto run, 68) vs `manual/atax_tdoff` and the td=off cache entry (13).
- **hls-est:** `--infer-vitis-split-array` models the `auto` behaviour; under td=off it should not split arrays for port pressure. To be settled by the ablation.

## N3. Automatic pipelining and unrolling (unconfirmed; experiments in progress)
- Observed (atax, attention): Vitis pipelines a loop and completely unrolls the loops nested inside it (`[HLS 214-291] ... complete unroll implied by the pipeline pragma`); the chosen pipeline level is not simply "innermost loop with trip count >= 64" (lp2 with 64 trips was unrolled under lp1; a 16-trip d loop was unrolled under an 8-trip j loop; a 256-trip loop was pipelined directly). Perfect nests are flattened (`[XFORM 203-541]`).
- **hls-est:** `--auto-pipeline-unroll` currently unrolls innermost loops with trip count > 32 (inverted comparison, see CHANGELOG) and never re-examines the parent; the rule must be replaced by Vitis's once the experiments pin it down.

## N4. Memory replication (RAM_1WNR) — partially known (unconfirmed)
- Peter's sweep (`D:\HLS\circt\build-test\sweep_report`, gemm-like kernel, no pragmas): R reads/iteration of a loop-invariant row -> `[HLS 200-2167] ... with N copies`, N = ceil(R/II)-1 capped at 15 (16 ports), II raised to ceil(R/16); reported BRAM = N x BRAM(one copy).
- Counter-example: atax's buff_A (64 varying reads per iteration) is not replicated (II 36). Rule under investigation.
- **hls-est:** no replication model; >2 accesses/cycle per bank is reported as "infeasible".

## N5. Small arrays (unconfirmed; experiments in progress)
- 32x16-bit local buffer -> 0 BRAM (distributed RAM, `RAM_AUTO_1R1W`, FF/LUT only); 64x31 and 64x16 -> 1 BRAM; 8x16 -> registers (32 FF). hls-est excludes arrays of <= 1024 bits, which puts 64x16 (1024 bits) on the wrong side.
