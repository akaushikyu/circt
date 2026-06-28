# loopschedule-vis

An offline, interactive timing-diagram viewer for the `loopschedule.pipeline`
schedules that hls-est produces with `--convert-affine-to-loopschedule`.

It is plain Python 3 (standard library only) plus a self-contained HTML
template, so nothing in CIRCT needs rebuilding to use or change it. The
generated page has all of its CSS, JS and data inline, with no CDN or network
access, so it opens straight from the WSL filesystem.

## Usage

```sh
# Already-lowered loopschedule IR (emit it with --mlir-print-debuginfo to get
# source mapping):
tools/loopschedule-vis/loopschedule-vis bicg.ls.mlir -o bicg.html

# Affine MLIR: run hls-est first, then visualize.
cd ~/circt
tools/loopschedule-vis/loopschedule-vis --run-hls-est \
    test/hls-est/Estimation/polybench/bicg.mlir -o bicg.html
```

| Option | Meaning |
| --- | --- |
| `-o, --output FILE` | Output HTML (default: `<input basename>.html` in the current directory). |
| `--source FILE` | Source file (`.c` or `.mlir`) shown on the left. |
| `--run-hls-est` | Treat the input as affine/source MLIR and lower it with hls-est. |
| `--hls-est PATH` | hls-est binary. Default: `$HLS_EST`, then `build/bin`, `bin`, `build/clion/bin` under the repo root, then `$PATH`. |
| `--pipeline "FLAGS"` | hls-est flags for `--run-hls-est`. Default: `--auto-pipeline-unroll --canonicalize --affine-scalrep --affine-loop-normalize --memory-banking-bram --convert-affine-to-loopschedule`. `--mlir-print-debuginfo` is always added. |
| `--save-ir FILE` | With `--run-hls-est`, also save the lowered IR. |
| `--json FILE` | Also write the extracted schedule data as JSON. |
| `--title TEXT` | Page title. |
| `--werror` | Exit with status 2 if there were any warnings. |

The source panel is chosen in this order:
1. `--source`.
2. The file referenced most often by the op locations, if it exists. Relative
   paths are tried against the current directory, the input's directory and
   its parents, and the repo root.
3. In `--run-hls-est` mode, the input MLIR.
4. The loopschedule IR itself. IR line numbers then serve as the mapping.

For the polybench tests, the locations point to the `.mlir` test file, so that
is what appears on the left.

## Asking an agent about the schedule

`serve` serves the same page over HTTP and adds three things: a JSON query
API, live tracking of what you are looking at, and an **Ask agent** panel that
forwards questions to Claude Code (`claude -p`):

```sh
tools/loopschedule-vis/loopschedule-vis serve bicg.ls.mlir   # http://localhost:8765/
tools/loopschedule-vis/loopschedule-vis serve --run-hls-est \
    test/hls-est/Estimation/polybench/bicg.mlir --port 9000
```

Open the URL in a Windows browser; WSL2 forwards `localhost`. Then press
**Ask agent** (or `a`). Each question is sent together with the context shown
at the top of the panel:

- the stage in view (pinned, or previewed by hover);
- the **focused op**, the last Gantt bar you clicked. It gets a red outline;
- a **variable**: select a short piece of text in the source or schedule pane,
  e.g. `tmp`, `A` or `%12#3`;
- the selected source line.

Remove any of them with its ✕. The agent can query the rest of the schedule
itself through the API. In answers, `op #N`, `P1·S2` and `L42` are links that
jump to the op, stage or source line. Follow-up questions continue the same
conversation, and **new chat** starts over.

| Option | Meaning |
| --- | --- |
| `--port N` | Port (default 8765; `0` picks a free one). `--host` sets the bind address (default `127.0.0.1`). |
| `--agent-cmd "CMD"` | Agent command. The prompt goes to stdin and the answer comes back on stdout. Default: `claude -p --output-format json --allowedTools "Bash(curl:*),Read,Grep,Glob"`. |
| `--agent-model M`, `--agent-timeout S` | Passed to `claude --model`, and seconds per question (default 600). |
| `--no-agent` | Serve the page and API only. |
| `-v` | Log requests. You can watch which API calls the agent makes. |

You can also skip the panel and ask Claude Code in a terminal: "what am I
looking at in loopschedule-vis?" The agent reads `GET /api/selection` to see
your current view. [AGENTS.md](AGENTS.md) (also served at `/api/docs`, and
loaded by Claude Code through `CLAUDE.md` in this directory) documents every
endpoint for agents.

### Query API and CLI

Every query is available over HTTP from a running server, or offline from the
command line:

```sh
curl -s "http://localhost:8765/api/selection"                  # your current view, resolved
curl -s "http://localhost:8765/api/cdfg?pipeline=1&stage=2"    # {"text": ...}
curl -s "http://localhost:8765/api/value?name=%2512&pipeline=1" # %12 (URL-encode %)

loopschedule-vis query bicg.ls.mlir summary
loopschedule-vis query bicg.ls.mlir cdfg 1 --stage 2           # prints text
loopschedule-vis query bicg.ls.mlir value buff_s_out
loopschedule-vis query test/out/bicg.ls.json op 471            # --json output works too
loopschedule-vis query --server http://localhost:8765 selection
```

Commands: `summary`, `function`, `pipeline`, `stage`, `op`, `value` (an SSA
or source variable), `memref`, `line`, `search`, `cdfg`, `ir`, `src`,
`selection` and `ping` (the last two need a server), and `help`. See
[AGENTS.md](AGENTS.md) for their arguments and results.

The server only accepts requests for `localhost`/`127.0.0.1`. It refuses
cross-origin POSTs, so another web page cannot trigger the agent.

## Opening the HTML from WSL

```sh
explorer.exe "$(wslpath -w bicg.html)"   # default Windows browser
wslview bicg.html                        # if wslu is installed
```

You can also paste `\\wsl.localhost\Ubuntu-22.04\home\<you>\...\bicg.html` into
a Windows browser's address bar.

## The page

- **Left: source.** The source has line numbers and light C/MLIR highlighting.
  A function's span is marked with a bar in the gutter and an `ƒ name` tag.
  - Hovering a function highlights its span and its schedule section.
    Clicking a function expands and pins that section.
  - Clicking a line highlights every op mapped to it: stage chips get a ring,
    Gantt bars get an outline, and the line summary above the schedules links
    to each stage.
  - ↑/↓ move the selected line, Enter opens its function, and Esc clears.
- **Right: schedules.** There is one collapsible section per function, all
  collapsed at first. Each pipeline shows:
  - II, trip count, depth (stages), latency (cycles), memory op count, loop
    nest and iter_args. For iter_args it names the terminator operand and the
    op that really produces it.
  - A strip of stage chips. The mini bar under each chip shows its op mix.
    Hover or focus a chip to preview a stage and click to pin it.
    ←/→/Home/End move between stages (the pin follows), and Esc unpins.
- **Stage selected: timing diagram.**
  - The x axis is in cycles, with a clock-waveform ruler and dashed markers at
    multiples of II.
  - Rows are ops grouped by stage. Bars span the stage's cycles `[start,
    next start)` (the last stage is 1 cycle) and are colored by category.
  - The selected stage gets a tinted band and the other stages are dimmed.
  - Edges:
    - `comb` edges run within the selected stage.
    - `reg` edges leaving the stage are drawn strong and ones entering it
      faint.
    - `carried` edges are dashed and go to a "next iter" tick at consumer
      start + II.
    - "show all edges" draws the rest faintly.
  - Constants are hidden by default (each stage passes dozens of index
    constants through). Use "show constants" to see them.
  - Hovering a bar shows the full op, stage, cycle span, source/IR lines,
    memref, and each input with its edge kind and register-hop count. It also
    highlights the source line and scrolls to it.
  - Below the diagram:
    - The selected stage's memory accesses per memref.
    - The pipeline's **modulo reservation table**: memrefs × cycles `0..II-1`,
      counting every load and store at `start mod II`. This is the per-cycle
      port demand behind the BRAM estimate. Cells above 2 (a dual-port BRAM's
      limit) are flagged.
- It follows `prefers-color-scheme` for light or dark mode. The splitter
  between the panes can be dragged, or moved with ←/→ when focused.

## How the IR is read

The parser works on textual IR, one op per line, and does not need CIRCT's
Python bindings.

- **Op tree.** Each line's net brace depth is counted outside strings and
  `loc(...)`.
  - A line ending in `{` opens a region.
  - A line starting with `}` closes one.
  - `} do {`, `} else {` and `}, {` start the next region of the same op.
  - For an op with regions, the location is on its closing line.
- **Locations.** `#locN` aliases (defined at the top or bottom of the file) are
  resolved recursively, and the first `FileLineCol` inside `fused`,
  `callsite` or name locations is used.
- **SSA scoping.** hls-est's printer reuses names in sibling regions: every
  stage body starts again at `%191`, and `%128` can be both a condition-region
  `cmpi` and a stage result. So each name is looked up in its own region, then
  in enclosing regions.
- **Dataflow.**
  - Multi-result stages (`%s:N`) expand to `%s#0..N-1`, and `%s#k` is operand
    `k` of the stage's `loopschedule.register`.
  - Uses are traced back through pass-through registers to the op that really
    produced them. The number of registers crossed is the hop count. Stages
    may read results from any earlier stage, not only the previous one.
  - An edge is `comb` if the producer is in the same stage and `reg` if it is
    in an earlier stage.
  - A use of an iter_arg is a `carried` edge from whatever produces the
    matching `loopschedule.terminator iter_args(...)` operand.
- **Ops.** Every op inside a stage (including ops nested in `scf.if`) is
  shown, except the stage's own register. Unrecognized `loopschedule.*` ops
  produce a warning and are drawn as "other".
- **Function arguments.** Arguments are mapped to C parameter names through
  their argument locations. `polygeist.varname` names the allocas.

## Tests

```sh
tools/loopschedule-vis/test/run_smoke.sh               # all test/inputs
tools/loopschedule-vis/test/run_smoke.sh --run-hls-est # + a live hls-est run
```

`test/inputs/` holds the loopschedule IR for the 7 polybench kernels (bicg,
gesummv, k2mm, k3mm, mvt, syr2k, syrk). It was generated with the default
`--pipeline` flags plus `--mlir-print-debuginfo`, run from the repo root.

`synthetic.ls.mlir` (with `synthetic.c`) is a small hand-written case covering
fused and callsite locations, pass-through registers, loop-carried values,
`scf.if`/`else`, an op without a location and an unknown loopschedule op. The
smoke test checks its exact edge set, stage spans, source lines, C parameter
names and reservation table.

It also runs the query CLI on the synthetic input, both from IR and from
`--json`. Then it starts `serve` on a free port and checks the API, the
selection round trip, the cross-origin check and `/api/ask`. The ask check
uses a stub agent, so no Claude call is made.

The smoke test fails if any input exits non-zero, if a polybench input warns,
or if the generated data is malformed. Output goes to `test/out/`, which is
git-ignored.

To regenerate the inputs after changing the pipeline:

```sh
cd ~/circt
for k in bicg gesummv k2mm k3mm mvt syr2k syrk; do
  build/clion/bin/hls-est test/hls-est/Estimation/polybench/$k.mlir \
    --auto-pipeline-unroll --canonicalize --affine-scalrep --affine-loop-normalize \
    --memory-banking-bram --convert-affine-to-loopschedule --mlir-print-debuginfo \
    -o tools/loopschedule-vis/test/inputs/$k.ls.mlir
done
```
