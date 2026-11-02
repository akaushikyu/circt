# CLAUDE.md
# Task: build `loopschedule-vis`, a schedule visualizer for hls-est

Create all files under `~/circt/tools/loopschedule-vis/`. Don't modify anything outside except for purposes of building the tool adding to CMakeLists.txt

## Context
- This CIRCT tree contains my static BRAM estimator for FPGA HLS. Driver: `./build/bin/hls-est` (check `~/circt/bin` too if it's not there).
- Pipeline: `--auto-pipeline-unroll --canonicalize --affine-scalrep --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule`
- Tests: `test/hls-est/Estimation/polybench/` (bicg, gesummv, 2mm, 3mm, mvt, syr2k, syrk)
- I only care about the loopschedule part of the output: `loopschedule.pipeline` ops, their `loopschedule.pipeline.stage` ops (`start = N`), `loopschedule.register`, and `loopschedule.terminator` (iter_args/results).

## Step 1: inspect real IR before designing the parser
1. Run hls-est on 2–3 polybench tests, stopping after `--convert-affine-to-loopschedule`, Save the outputs under `tools/loopschedule-vis/test/inputs/`.
2. Read the loopschedule dialect ODS and printer/parser (`include/circt/Dialect/LoopSchedule/`, `lib/Dialect/LoopSchedule/`) so the parser matches the exact textual syntax in *this* fork (II, trip_count, iter_args, stage `start`, terminator format, any fork-specific ops like sequential/step or loopschedule.load/store).
3. Check which locations survive the pipeline: FileLineCol, fused, callsite, and `#locN` aliases printed at the end of the file.
   Show me a short summary of what you found before you write the tool.

## Step 2: the tool
Implement it in Python 3 (stdlib only) plus a self-contained HTML template, so I don't have to rebuild CIRCT (my links OOM). Files:
- `loopschedule_vis.py`: the CLI
- `template.html`: inline CSS/JS, **no CDN or network**; the generated HTML must open offline from WSL
- `loopschedule-vis`: shell wrapper
- `README.md`
- `test/`: sample inputs and a smoke-test script

CLI:
- `loopschedule-vis <file.mlir> [--source file.c|file.mlir] [-o out.html]`: the input is already-lowered loopschedule IR.
- `--run-hls-est`: treat the input as affine/source MLIR. Run hls-est with the pipeline up to convert-affine-to-loopschedule plus `--mlir-print-debuginfo`, then visualize. Flags: `--hls-est PATH`, `--pipeline "..."`.
- Source resolution order: `--source`; otherwise the most common file in the locs (if it exists on disk); otherwise the input MLIR in `--run-hls-est` mode; otherwise the loopschedule IR itself, using IR line numbers as the mapping.

Parser (textual IR, one op per line):
- Build an op tree using net brace depth per line, outside strings and `loc(...)`. Region-opening lines end in `{`, lines starting with `}` close regions, and `} do {` / `} else {` start the next region.
- The loc for an op with regions is on its closing line (e.g. `} : f32, index loc(#loc9)`). Resolve `#loc` aliases recursively and take the first FileLineCol.
- Expand results: `%1:2` becomes `%1#0`, `%1#1`.
- Build dataflow per pipeline:
    - For each stage, map result `%s#k` to register operand k.
    - Resolve pass-through registers back to the original producing op, and count the register hops.
    - Edge kinds: `comb` (producer in the same stage), `reg` (producer in an earlier stage), `carried` (use of an iter_arg, sourced from the terminator's iter_args operand; the "next iteration" happens at +II).
- Record the loop nest around each pipeline (affine.for / scf.for ancestors) with source lines.
- Stage cycle span: `[start, next stage start)`. The last stage is `start + 1`.
- Op categories for coloring: memory (load/store), float mul/div, float add/sub, int/index arith, cmp/select, constant, other.
- For memory ops, extract the memref (the SSA token directly before `[`).
- Map func args to C parameter names using the arg locs where possible.
- Function spans in the source: brace-match from the func loc line, or regex-find the definition (C: `name(...) {`, MLIR: `func.func @name(`).
- Emit JSON with source lines, functions (span, pipelines), pipelines (II, trip_count, nest, iter_args, stages, edges), and ops (id, name, text, stage, src_line, ir_line, category, memref). Embed it into the template.

## HTML UI
- **Left panel:** source with line numbers and light syntax highlighting for C and MLIR. Each function's span is marked in the gutter.
- **Right panel:** one collapsible section per function (all collapsed by default). Each lists its pipelines with II, trip count, depth, loop nest, and a strip of clickable stage chips.
- **Linking:**
    - Hovering or clicking a function in the source highlights its span and highlights/expands the matching schedule section on the right.
    - Hovering a schedule section highlights its source span.
    - Clicking a source line highlights any ops mapped to that line.
- **Stage selected (hover previews, click pins):** show a timing/Gantt diagram for the whole pipeline.
    - x axis is cycles, with a clock-waveform ruler like a logic analyzer. Rows are ops grouped by stage. Bars cover the stage's cycle span, colored by category.
    - The selected stage is full opacity with a tinted band; other stages are dimmed.
    - Draw edges as curves from producer bar end to consumer bar start: `comb` within the stage, `reg` outgoing to later stages (strong) and incoming from earlier ones (faint), and `carried` as dashed edges to a ghost tick at consumer start + II labeled "next iter". Add a toggle for showing all edges.
    - Tooltips show the full op text, stage, cycle span, source line, and register hops. Hovering a bar highlights and scrolls to its source line.
    - Below the diagram:
        - memory accesses in the selected stage, per memref (loads/stores)
        - a modulo reservation table for the pipeline: memrefs × cycles 0..II-1, access counts at `start mod II` (this is the per-cycle port demand that feeds my BRAM estimation)
- **Look:** a clean timing-diagram / datasheet aesthetic that supports light and dark mode via prefers-color-scheme. Keep it keyboard accessible. It must handle large kernels (3mm, unrolled) with a scrollable diagram.

## Step 3: verify
- Run the tool on all 7 polybench kernels. Fix any parse failures instead of skipping ops, and make the parser warn (not crash) on unrecognized loopschedule ops.
- For one kernel, sanity-check a few stages and edges by hand against the IR, and tell me what you checked.
- Add `test/run_smoke.sh`, which regenerates HTML for every test input and fails on errors.
- In the README, show how to open the HTML from WSL (`explorer.exe` / `wslview`).
This is a CIRCT fork containing **hls-est**, a static BRAM estimator for FPGA HLS. It works on MLIR affine/loopschedule IR and is validated against Vitis HLS `csynth` reports for a Zynq-7020. It's MSc research (York EECS Computer Architecture Group), so correctness against Vitis matters more than cleverness.

## Environment

- WSL2 on Windows. The tree lives at `/home/peter/circt`, on the WSL filesystem. Don't move work onto `/mnt/c` or `/mnt/d`, because DrvFs is very slow.
- LLVM/MLIR is built at `llvm/build` (gcc 11, RelWithDebInfo, assertions ON, `mold` linker).
- CIRCT uses an **in-source** CMake configure (clang++ 14, Debug, `mold`). Binaries land in `~/circt/bin`. Some notes refer to `./build/bin/hls-est`, so check which one exists before running anything.
- Linking is memory-hungry and has OOM'd before. Keep `LLVM_PARALLEL_LINK_JOBS=1`, and only build the targets you need (e.g. `hls-est`, `circt-opt`), never `all`.
- Never reconfigure CMake or change compilers or build types without asking.

