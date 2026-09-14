# hls-est in Compiler Explorer

`hls_est_ce.py` turns HLS C/C++ into a per-array BRAM report the way the validation harness
runs hls-est (cgeist with the harness's front-end flags, then the default pipeline with
`--bram-analysis`). It is the `compiler.exe` of a local Compiler Explorer instance
(`D:\claude-compiler-explore\compiler-explore`, branch `hls-est-demo`).

## Run it

It runs as the systemd user service `hls-est-ce` (~/.config/systemd/user/hls-est-ce.service,
enabled, lingering on), so it starts with WSL: `systemctl --user status|restart hls-est-ce`;
its log is `~/hls-est-demo/ce.log`. By hand:

```bash
cd /mnt/d/claude-compiler-explore/compiler-explore
NODE_ENV=DEV node --no-warnings=ExperimentalWarning --import=tsx app.ts \
    --language c++ --port 10240 --tmp-dir /tmp
```

Open http://localhost:10240 in a browser on Windows. The four `HLS_*` entries in the
examples menu are the demo kernels; each starts with the Vitis HLS 2025.1 csynth number
for the same source (xc7z020, 10 ns, td=off). `--tmp-dir /tmp` matters: under WSL,
Compiler Explorer otherwise writes every compile to the Windows temp folder.

## Compilers

A third entry, **hls-est (current)** (`compiler.hlsestcurrent`), runs
`~/hls-est-demo/current/hls_est_ce_current.sh`: the same driver with today's tools frozen there
(the installed real-Vitis-headers cgeist and the W9 round-8 hls-est, refreshed 2026-10-21), while `hls-est` keeps the demo's
frozen tools. The instance also enables `llvm` (`--language c++ llvm`, a view-only `/bin/cat`
entry in `etc/config/llvm.local.properties`) so a design's Vitis IR stages (`db/a.*.ll` of a
Vitis run) can be opened next to the source.


A fourth entry, **hls-est -> Verilog (RTL back end M1)** (`compiler.hlsestrtl`), runs
`~/hls-est-demo/rtl/hls_rtl_ce.sh`: the RTL back end driver `tools/rtl-backend/hls_rtl_ce.py` of
branch `rtl-backend` (worktree `~/rtlspike/circt`) with its tools frozen in `~/hls-est-demo/rtl`
(hls-est and circt-opt from the float build, the installed cgeist). It prints the interface, hls-est's
LoopSchedule and the Verilog (`--show=verilog|schedule|interface`, `--full`). Examples `HLS_5` (vadd),
`HLS_6` (float dot product, HardFloat units), `HLS_7` (local array as a RAM module) and `HLS_8`
(polybench gemm) are written for it. `HLS_9_sha` (chstone/sha with sha.h inlined) is written for
"hls-est (current)": 7 BRAM_18K = Vitis per array (the frozen demo compiler gives 24).

A fifth entry, **Vitis HLS 2025.1 IR (csynth, xc7z020)** (`compiler.vitisir`), runs `vitis_ir_ce.py`:
Vitis HLS csynth on the source with the ground-truth configuration (through
`tools/hls-est-validate/vitis_adhoc.py`, as an experiment `ce_<source hash>`, never the ground-truth
cache), then prints the csynth summary (BRAM/DSP/FF/LUT, memories, loops) and one of Vitis's own LLVM
IR stages from the run's `db/`: `--stage=front` (a.g.ld.0.ll), `link` (a.g.ld.5.gdce.ll), `o1`, `o2`
(default), `o3` (a.o.N.ll); `--function=NAME` keeps only matching definitions, `--metadata` keeps the
debug metadata. The first view of a source waits for Vitis (about 30 s to a few minutes; the instance's
`compileTimeoutMs` is 900000 in `etc/config/compiler-explorer.local.properties`), later views reuse the
run. Put it next to the hls-est compiler to compare a design's IR with the decisions hls-est makes.

The compiler dropdown has **cgeist** (HLS C/C++ -> affine MLIR: the front end alone, with the
harness's flags; its options box takes cgeist flags) and **hls-est** (the same cgeist step, then
the hls-est pipeline and the BRAM report). Both run this driver; `compiler.cgeistlocal.options=--emit=cgeist`
selects the first. Put them side by side with "Add new..." -> "Compiler" in the source pane.

## Options (the options box of the hls-est compiler)

The arrow at the right of the options box opens a menu with every option below (and, for the
cgeist compiler, its `--hls-*` flags); clicking one appends it. The menu comes from the driver's
`--help`, so a new pass or setting only needs adding there.

| option | effect |
|---|---|
| `--top=NAME` | the top function (default `top`, else the last function) |
| `--explain` | per-array reasons: port demand, RAM type, bank math, why an array is not a memory |
| `--show=input` / `output` / `all` | append the cgeist MLIR, the MLIR after the pipeline, or both |
| `--list-passes` | the default pipeline with a description of every pass |
| `--<pass>` ... | hls-est passes: when any is given they **replace** the default pipeline and the output is the MLIR after them, like `mlir-opt`; add `--bram-analysis` to the list to also get the BRAM report above the MLIR |
| `-I...`, `-D...` | passed to cgeist |
| `--config-set=`, `--hls-config=`, `--load-plugin=`, `--mlir-...` | passed to hls-est as options, e.g. `--config-set=tool.hls.options.pipeline_loops=2` |

The report's header line names the pipeline that ran. **Opt Pipeline view:** in the output
pane, "Add new..." -> "Opt Pipeline" lists cgeist and every hls-est pass with the MLIR after
each one and a diff against the previous pass (the driver's `--opt-pipeline-file`, from
`--mlir-print-ir-after-all`).

## Binaries

The driver uses frozen copies under `~/hls-est-demo/` when they exist (`bin/cgeist`,
`bin/hls-est`, `bin/math_costs.json`, `shim/`, `clang/18`), so a rebuild of hls-est or a
cgeist install cannot change the demo, and the 4 GB debug cgeist loads from the Linux disk
(about 1 s per compile instead of up to a minute from `/mnt/d`). Without them it falls back
to the installed tools; `HLSEST_CE_CGEIST`, `HLSEST_CE_HLSEST`, `HLSEST_CE_SHIM`,
`HLSEST_CE_RESOURCE_DIR`, `HLSEST_CE_MATH_COSTS` and `HLSEST_CE_TMP` override each path.
To refresh the frozen hls-est: `cp ~/circt/build/clion/bin/hls-est ~/hls-est-demo/bin/`.
