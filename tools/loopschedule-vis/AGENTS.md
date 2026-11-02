# loopschedule-vis: guide for agents

This file tells a coding agent (Claude Code or similar) how to answer
questions about an hls-est `loopschedule.pipeline` schedule. That covers the
CDFG the user is viewing, a single op, or a variable. You get the data through
the loopschedule-vis query API instead of reading raw IR by hand. The
user-facing docs are in `README.md`.

## Pick an access mode

| Situation | Use |
| --- | --- |
| The user has the viewer open (`loopschedule-vis serve`, default port 8765) | HTTP: `curl -s "http://localhost:8765/api/<command>?..."` |
| The user asks about "what I'm looking at", "this stage", "this op" | `GET /api/selection` (server only). It returns their live view. |
| No server is running; you have an IR file (`*.ls.mlir`) or `--json` output | CLI: `tools/loopschedule-vis/loopschedule-vis query <file> <command> ...` |
| You only have affine MLIR | CLI with lowering: `loopschedule-vis query --run-hls-est <file.mlir> <command> ...` |

Check whether a server is up with `curl -s http://localhost:8765/api/ping`.
If you are running on Windows and the server runs in WSL2, `localhost` still
works because WSL forwards the port. The CLI can also talk to a server:
`loopschedule-vis query --server http://localhost:8765 <command> ...`, or set
`$LOOPSCHEDULE_VIS_SERVER` and leave out the input file.

All results are JSON, except that the CLI prints `cdfg` as plain text.
Errors come back as `{"error": "..."}` with HTTP 400, or as exit status 1 on
the CLI.

## Model in one paragraph

A `loopschedule.pipeline` has an initiation interval `II`, a `trip_count` and
stages `S0..Sn`. Stage k starts at cycle `start` and spans
`[start, next stage's start)`; the last stage is 1 cycle. `latency` is the end
of the last stage minus the start of the first. Ops inside stages are numbered
globally (`op #N`, the `id` field). Dataflow edges from producer to consumer
come in three kinds:

- **comb**: the producer is in the same stage.
- **reg**: the producer is in an earlier stage. The value travels through
  stage registers, and `reg_hops` counts how many.
- **carried**: the value comes from the previous iteration through
  `iter_args`, and the consumer sees it at its stage start + II.

The **modulo reservation table (MRT)** counts loads and stores per memref at
cycle `stage start mod II`. That per-cycle port demand drives hls-est's BRAM
estimate. A count above 2 exceeds a dual-port BRAM (`over_dual_port`).

## Commands

Positional arguments can be given as path segments (`/api/stage/0/3`) or by
name (`/api/stage?pipeline=0&stage=3`). On the CLI, write them in order, with
options as `--name value`. `p`/`s` also work for `pipeline`/`stage`, and so
does `id` for a command's single positional. **URL-encode `%` as `%25`**, for
example `name=%2512` for `%12`. Quote URLs in the shell, because `&` needs it.

| Command | Args | Returns |
| --- | --- | --- |
| `help` | – | Command list with parameters. |
| `summary` | – | Title, IR/source paths, counts, warnings, and every function with pipeline briefs: `II`, `trip_count`, `depth`, `latency`, `ops`, `mem_ops`, edge counts by kind, `peak_port_demand`, `over_dual_port`. **Start here.** |
| `function` | `ref` (id or name) | The function's source text (its span) and pipeline briefs. |
| `pipeline` | `pipeline` | The brief, plus `nest` (the enclosing loops), `iter_args` (with the producing op), per-stage `stages` summary, `carried_edges` with `slack`, and `mrt` rows (`loads`/`stores`/`total` per cycle mod II, `peak`). |
| `stage` | `pipeline stage [--consts 1]` | The stage's cycle span, `mrt_column`, `memory` per memref, and `ops`. Each op lists `inputs` (`"%v <- #N kind (k reg hops)"`) and `outputs` (`"#N via %v kind"`). Constants are hidden unless `consts=1`. |
| `op` | `id` | Full op text, stage/cycles, `inputs`/`outputs` as structured edges, `external_operands` (constants, IVs, arguments, memrefs defined outside the pipeline), `src_text`, `ir_text`, and the memref's MRT row. |
| `value` | `name [--pipeline P] [--stage S]` | A variable. See **Variables** below. |
| `memref` | `name [--pipeline P]` | Every access to a memref by label (the C name) or SSA name, grouped by pipeline and stage with `cycle_mod_II`, plus its MRT rows. |
| `line` | `line` | A source line's text, its function, and the ops and stages mapped to it. |
| `search` | `q [--pipeline P] [--limit N]` | Ops whose name or text contains `q`. The match is case-insensitive. |
| `cdfg` | `pipeline [--stage S] [--consts 1]` | A compact text CDFG, one op per line: `#N <op text>  L<src>  <= %v<-#M kind+Hr, ...`. With `--stage`, `=> #M` lists the consumers in other stages. This is the densest way to read a schedule; prefer it to many `op` calls. Returns `{"text": ...}` over HTTP. |
| `ir` | `from [--to N]` | Numbered lines of the loopschedule IR (at most 400). The op `ir_line` fields point here. |
| `src` | `from [--to N]` | Numbered lines of the source shown in the viewer (the `.c` or `.mlir` from the locations). The `src_line` fields point here. |
| `selection` | – | **Server only.** `{selection, updated, age_seconds, context}`. See below. |
| `ping` | – | **Server only.** `{ok, title, agent}`. |

### Variables (`value`)

- **An SSA name** (`%12`, `%12#3`, `%arg4`): the result has `definitions` (ops
  producing it, with consumers) and `uses` (ops consuming it, each with its
  producer edge, or "defined outside the pipeline"). It also has `iter_args`
  where the name is the arg or its next value, `function_args` (with the C
  parameter name), and `memrefs`. `%s` also matches `%s#k`. **SSA names are
  scoped per region.** Every stage body restarts its numbering, so `%191` in
  S3 and `%191` in S7 are unrelated. Always narrow with `pipeline` (and
  `stage`) once you know them.
- **A source name** (`A`, `tmp`, `s`): `memrefs` whose label is that name
  (allocas through `polygeist.varname`, and function parameters),
  `function_args`, and `source_lines`. `source_lines` lists every line using
  the identifier, with the ops mapped to it. Scalars promoted to registers
  have no SSA name of their own in the source. Find them through their lines,
  then query the op ids.

### What the user is looking at (`selection`)

The browser page posts its state whenever it changes:

```json
{"pinned": {"p": 1, "s": 2}, "preview": null, "op": 471, "hover": null,
 "value": "buff_s_out", "line": 28, "fn": 0}
```

- `pinned` / `preview`: the stage pinned by a click, or the one previewed by
  hovering. `preview` wins while it is set.
- `op`: the op bar the user last clicked. The UI calls it the focused op.
- `hover`: the bar under the mouse right now.
- `value`: short text the user selected in the source or schedule pane,
  usually a variable name.
- `line`: the selected source line.
- `fn`: the pinned function.

`context` already resolves all of these: `viewing` (`"P1·S2 (pinned)"`),
`pipeline` (a brief), `stage` (the `stage` result), `focused_op` (the `op`
result), `hovered_op`, `selected_variable` (the `value` result, narrowed to
the viewed pipeline when that finds something), `source_line`, and
`function`. If `age_seconds` is large, the page may have been closed.

## Recipes

- **"Explain this stage":** `selection`, then `cdfg?pipeline=P&stage=S`. Walk
  the `<=` edges back into earlier stages with `op`.
- **"Why is II = N?":** use `pipeline`. Look at `carried_edges` (negative or
  small `slack` means a recurrence) and at `mrt` (a `peak` above 2 means port
  pressure). Recurrences through memory (a store in iteration i, then a load
  in iteration i+1) do **not** appear as carried edges. Find them with
  `memref` by comparing load and store stages of the same memref.
- **"Where does %x come from?":** `value?name=%25x&pipeline=P&stage=S`, then
  follow `producers[].from_id` with `op`.
- **"How is array A accessed?":** use `memref?name=A`, and `mrt` in
  `pipeline` for the per-cycle demand.
- **Map to source:** `src_line` means `src?from=L-3&to=L+3`, and `ir_line`
  means `ir?from=...`.

## Referring to things in answers

The viewer's Ask panel turns these patterns into links. Use them exactly:
`op #N`, `P<p>·S<s>` (`P1.S2` also works) and `L<n>` for source lines.

## Ask panel internals

The Ask panel in the page works like this:

1. The page sends `POST /api/ask {question, selection, session}`.
2. The server builds a prompt. It holds the resolved context: the text CDFG
   of the stage in view, the focused op, the selected variable and the source
   line. It also holds a short guide to this API.
3. The server runs the agent command with the prompt on stdin and returns
   `{answer, session, seconds, error?}`.
4. The default agent is
   `claude -p --output-format json --allowedTools "Bash(curl:*),Read,Grep,Glob"`,
   run from the repo root with `$LOOPSCHEDULE_VIS_SERVER` set.
5. Follow-up questions pass `--resume <session>`, so a conversation keeps its
   context. "new chat" in the panel clears it.

Override the agent with `--agent-cmd` (any command that reads a prompt on
stdin and prints an answer) and `--agent-model`.

The server binds 127.0.0.1. It rejects requests whose `Host` isn't
localhost/127.0.0.1 (DNS rebinding) and cross-origin POSTs, and it requires
`Content-Type: application/json` on POSTs.

## Code map

- `loopschedule_vis.py`: IR parser, schedule extraction (`build_data`), HTML
  rendering, and the CLI entry (`serve` and `query` dispatch to the API
  module).
- `loopschedule_api.py`: `COMMANDS` (the single command table),
  `QueryIndex` (`q_<command>` implementations and `context()`), `Agent` (the
  prompt and the agent subprocess), and the HTTP server.
- `template.html`: the page. Its "agent bridge" section holds selection sync,
  the Ask panel and answer linkification.
- `test/run_smoke.sh`: covers the query CLI, the server API and the ask
  bridge, using a stub agent.

When you add a query, add a `COMMANDS` entry and a `QueryIndex.q_<name>`
method. HTTP, CLI and `help` pick it up automatically. Then document it in the
table above.
