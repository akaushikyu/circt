#!/usr/bin/env python3
"""One trace bundle per kernel: everything the harness knows about how Vitis and hls-est
treated one design, written to ~/hls-est-work/traces/<dataset>__<benchmark>/.

usage: vitis_trace.py <dataset>/<benchmark> [<dataset>/<benchmark> ...] [--summary]
                      [--hlsest-json F | --run-id ID] [--rtl DIR] [--out-root DIR]
                      [--vitis results/vitis.json] [--no-write]

Bundle contents (all derived from results/vitis.json, the cache dir's db/*.ll, the hls-est
--bram-debug-json and, when available, an RTL dir found by rtl_memories.py):
  README.md              index + the <= 60-line summary
  align_arrays.txt/json  one row per array across source / a.o.1 / a.o.2 / a.o.3 / sched (the
                         <module>.verbose.rpt allocas) / report / rtl / hls-est, with the first stage
                         where it diverges from its source form
  loop_decisions.txt     Vitis: the [HLS 214-*]/[XFORM]/[HLS 200-*] log lines by class (auto_pipeline,
                         unroll, flatten, partition, replicate, memory_impl, ...);
                         hls-est: the pipelines[] of its debug JSON (II, trip count, unrolled loops)
  loop_tables.txt        the per-module '* Loop:' tables (pipelined, II, trip count, latency)
  memory_tables.txt      the per-module '* Memory:' tables, BRAM-holding instances, csynth totals and
                         the reconciliation total = memory rows + leaf instances (adapters)
  hlsest_debug.txt       hls-est's debug JSON summarized per array (status, partition, RAM type, bank math)
  rtl_memories.txt/json  physical memories from syn/verilog (only when an RTL dir exists)
  trace.json             the same data, machine-readable

`--summary` prints the trace in at most 60 lines (for the context budget).
The hls-est debug JSON defaults to the newest run under ~/hls-est-work/hlsest-logs that used
the harness default pipeline (see align_arrays.find_debug_json); --run-id / --hlsest-json override.
Python 3 stdlib only.
"""
import argparse
import contextlib
import io
import json
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import align_arrays as AA   # noqa: E402
import rtl_memories as RTL  # noqa: E402

TRACES_ROOT = Path.home() / "hls-est-work" / "traces"
LOG_CLASSES = ["auto_pipeline", "unroll", "unroll_implied", "flatten", "flatten_disabled", "perfect_nest",
               "pipelining_result", "ii_violation_ports", "partition_inferred", "partition_applied",
               "partition_const_index", "partition_small", "reshape", "replicate", "memory_impl",
               "storage_inferred", "fifo_impl", "inline", "auto_inline", "removed", "error"]
SUMMARY_MAX = 60


def short_path(s):
    s = str(s)
    if "/" in s or "\\" in s:
        return re.split(r"[/\\]", s)[-1]
    return s


def fmt_log_row(cls, row):
    if cls in ("flatten_disabled", "auto_inline"):
        vals = [x for x in row if x is not None]          # alternation patterns: keep the groups that matched
        return (("no-flatten " if cls == "flatten_disabled" else "auto-inline ") + " -> ".join(str(v) for v in vals))[:140]
    r = [short_path(x) if isinstance(x, str) and ("/" in x or "\\" in x) else str(x) for x in row]
    try:
        if cls == "auto_pipeline":
            return f"pipeline {r[0]} @{r[1]}:{r[2]}"
        if cls == "unroll":
            return f"unroll {r[0]} @{r[1]}:{r[2]} in {r[4]} {r[5]} factor {r[6]}"
        if cls == "unroll_implied":
            return f"unroll(implied) {r[0]} @{r[1]}:{r[2]}"
        if cls == "flatten":
            return f"flatten {r[0]} @{r[1]}:{r[2]} in {r[4]}"
        if cls == "pipelining_result":
            return f"loop {r[3]}: target II {r[0]} final II {r[1]} depth {r[2]}"
        if cls == "ii_violation_ports":
            return f"II violation {r[1]} ({r[0]}): {r[2]} on {r[6]} -> II {r[7]}"
        if cls == "partition_inferred":
            return f"infer '{r[0]}' for {r[1]} ({r[2]}) @{r[3]}:{r[4]}"
        if cls == "partition_applied":
            return f"apply to {r[0][:50]}: {r[1]} @{r[2]}:{r[3]}"
        if cls == "partition_const_index":
            return f"auto-partition {r[0]} dim {r[1]} (constant index) {r[2]}"
        if cls == "partition_small":
            return f"auto-partition small array {r[0]}"
        if cls == "replicate":
            return f"replicate {r[0]}: {r[1]} copies"
        if cls == "memory_impl":
            return f"impl {r[0]} using {r[1]}"
        if cls == "storage_inferred":
            return f"storage {r[0]} for {r[1]}"
    except IndexError:
        pass
    return " ".join(r)[:140]


def mlir_line(loc):
    """'/path/x.mlir:179:5' -> 'L179'."""
    m = re.search(r":(\d+):\d+$", str(loc or ""))
    return f"L{m.group(1)}" if m else str(loc)


def hlsest_pipeline_rows(hls_json):
    rows = []
    for p in (hls_json or {}).get("pipelines") or []:
        unr = p.get("unrolled") or []
        rows.append({"func": p.get("func"), "loop@mlir": mlir_line(p.get("scope_loc")), "source": p.get("source"),
                     "II": p.get("ii"), "trip": p.get("trip_count"),
                     "unrolled": ", ".join(f"{mlir_line(u.get('loc'))}x{u.get('factor')}" for u in unr) or "-",
                     "partial": p.get("unroll_partial") if p.get("unroll_partial") is not None else "-",
                     "flattened parents": p.get("flattened_parents")})
    return rows


def loop_decisions_text(entry, hls_json):
    log = entry.get("log") or {}
    lines = ["# Vitis (hls_compile.log, classified by vitis_parse.LOG_PATTERNS)"]
    for cls in LOG_CLASSES:
        rows = log.get(cls) or []
        if not rows:
            continue
        lines.append(f"## {cls} ({len(rows)})")
        for row in rows:
            lines.append("  " + fmt_log_row(cls, row))
    if len(lines) == 1:
        lines.append("(no log classes captured; results/vitis.json has no 'log' for this design)")
    lines.append("")
    lines.append("# hls-est (debug JSON pipelines[]; loop locations are MLIR lines, not C lines)")
    hr = hlsest_pipeline_rows(hls_json)
    lines.append(RTL.fmt_table(hr, ["func", "loop@mlir", "source", "II", "trip", "unrolled", "partial", "flattened parents"], max_w=70)
                 if hr else "(no pipelines in the debug JSON)")
    return "\n".join(lines)


def loop_tables_text(entry):
    loops = entry.get("loops") or []
    rows = [{"module": l.get("module"), "loop": l.get("name"), "pipelined": l.get("pipelined"),
             "II tgt": l.get("ii_target"), "II": l.get("ii_achieved"), "trip": l.get("trip_count"),
             "depth": l.get("depth"), "iter lat": l.get("iter_latency"), "lat min": l.get("latency_min"),
             "lat max": l.get("latency_max")} for l in loops]
    rows.sort(key=lambda r: (str(r["module"]), str(r["loop"])))
    if not rows:
        return "(no loop tables)"
    return RTL.fmt_table(rows, ["module", "loop", "pipelined", "II tgt", "II", "trip", "depth", "iter lat", "lat min", "lat max"], max_w=70)


def memory_tables_text(entry, meta):
    mems = entry.get("memories") or []
    out = []
    by_mod = {}
    for m in mems:
        by_mod.setdefault(m.get("module"), []).append(m)
    mult = AA.module_multiplicity(entry)
    for mod in sorted(by_mod, key=str):
        rows = by_mod[mod]
        k = mult.get(mod, 1)
        s = sum(r.get("BRAM_18K") or 0 for r in rows)
        out.append(f"## module {mod}: {len(rows)} memories, BRAM_18K {s}"
                   + (f" (module instantiated {k}x -> {k * s})" if k != 1 else ""))
        table = [{"Memory": r.get("Memory"), "Module": r.get("Module"), "core": r.get("core"), "BRAM_18K": r.get("BRAM_18K"),
                  "Words": r.get("Words"), "Bits": r.get("Bits"), "Banks": r.get("Banks"), "array": r.get("array"),
                  "bank": r.get("bank") if r.get("bank") is not None else "-", "variable": r.get("variable") or "-",
                  "optype": r.get("optype") or "-"} for r in rows]
        out.append(RTL.fmt_table(table, ["Memory", "Module", "core", "BRAM_18K", "Words", "Bits", "Banks", "array", "bank",
                                         "variable", "optype"], max_w=60))
    inst = [i for i in (entry.get("instances") or []) if (i.get("BRAM_18K") or 0) > 0]
    if inst:
        out.append("## instances with BRAM (hierarchical: a sub-module's row includes its memories)")
        out.append(RTL.fmt_table([{"Instance": i.get("Instance"), "Module": i.get("Module"), "parent": i.get("parent"),
                                   "BRAM_18K": i.get("BRAM_18K")} for i in inst], ["Instance", "Module", "parent", "BRAM_18K"], max_w=70))
    tot = entry.get("totals") or {}
    out.append(f"## csynth totals: BRAM {tot.get('BRAM')} DSP {tot.get('DSP')} FF {tot.get('FF')} LUT {tot.get('LUT')} "
               f"(util% BRAM {tot.get('BRAM_util_pct')} DSP {tot.get('DSP_util_pct')} FF {tot.get('FF_util_pct')} "
               f"LUT {tot.get('LUT_util_pct')})")
    out.append("   " + AA.reconcile_line(meta))
    return "\n".join(out)


def hlsest_debug_text(debug_json):
    if not debug_json:
        return "(no hls-est debug JSON found)", None
    d = json.load(open(debug_json))
    lines = [f"debug JSON {debug_json} (version {d.get('version')}), total BRAM {d.get('total_bram')}, "
             f"{len(d.get('memrefs', []))} memrefs",
             f"pipeline: {AA.hlsest_pipeline_of(debug_json) or 'unknown'}"]
    groups = {}
    for m in d.get("memrefs", []):
        groups.setdefault((m.get("varname") or m.get("name") or m.get("id"), (m.get("loc") or {}).get("line")), []).append(m)
    names = {}
    for (v, _l) in groups:
        names[v] = names.get(v, 0) + 1
    order = sorted(groups.items(), key=lambda kv: -sum(x.get("bram") or 0 for x in kv[1]))
    for (vname, line), ms in order:
        m0 = ms[0]
        name = vname if names[vname] == 1 else f"{vname}@L{line}"
        bram = sum(x.get("bram") or 0 for x in ms)
        st, rt = {}, {}
        for x in ms:
            st[x.get("status")] = st.get(x.get("status"), 0) + 1
            rt[x.get("ram_type")] = rt.get(x.get("ram_type"), 0) + 1
        p = m0.get("partition")
        lines.append(f"## {name}: {len(ms)} memref(s), BRAM {bram}, status {st}, kind {m0.get('kind')}, func {m0.get('func')}")
        lines.append(f"   shape {m0.get('shape')} x {m0.get('elem_bits')}b ({m0.get('elem_type')}), words {m0.get('words')}, "
                     f"loc {short_path((m0.get('loc') or {}).get('file'))}:{(m0.get('loc') or {}).get('line')}")
        if p:
            lines.append(f"   partition {p.get('kind')} factor {p.get('factor')} dim {p.get('dim')} banks {p.get('bank_count')} "
                         f"source {p.get('source')}: {str(p.get('reason'))[:150]}")
        lines.append(f"   ram_type {rt}; replication {json.dumps(m0.get('replication'))[:220]}")
        if m0.get("ram_reason"):
            lines.append(f"   reason: {str(m0.get('ram_reason'))[:220]}")
        if m0.get("exclude_reason"):
            lines.append(f"   excluded: {str(m0.get('exclude_reason'))[:200]}")
        pd = m0.get("port_demand") or {}
        if pd:
            lines.append(f"   port demand reads {pd.get('reads')} writes {pd.get('writes')} total {pd.get('total')}; per scope "
                         + "; ".join(f"{s.get('scope')}@{mlir_line(s.get('scope_loc'))} II {s.get('ii')} R{s.get('reads')} "
                                     f"W{s.get('writes')}" for s in (pd.get('per_scope') or [])[:4]))
        bm = m0.get("bank_math")
        if bm:
            lines.append(f"   bank math (first memref): {json.dumps(bm, sort_keys=True)}")
    return "\n".join(lines), d


def _capture(fn):
    buf = io.StringIO()
    with contextlib.redirect_stdout(buf):
        fn()
    return buf.getvalue()


def build(key, vitis_json, hlsest_json, rtl_dir, out_root, write=True, run_id=None):
    ds, bench = key.split("/", 1)
    res = json.load(open(vitis_json))
    entry = res.get(key)
    if not entry:
        raise SystemExit(f"{key} not in {vitis_json}")
    why = []
    hj = hlsest_json or AA.find_debug_json(ds, bench, run_id, why)
    rtl_how = "given (--rtl)" if rtl_dir else None
    if rtl_dir is None:
        vdir, rtl_how = RTL.find_verilog_dir(key, results=res)
        rtl_dir = str(vdir) if vdir else None
    rows, meta = AA.align(key, vitis_json, hj, rtl_dir)
    meta["rtl_source"] = rtl_how if rtl_dir else "none (the harvest keeps no syn/verilog; `rtl_memories.py KEY --make-rtl`)"
    meta["hlsest_pick"] = why[0] if why else ("given (--hlsest-json)" if hlsest_json else None)
    align_txt = _capture(lambda: AA.print_rows(rows, meta))
    hls_txt, hls_json = hlsest_debug_text(hj)
    loops_txt = loop_tables_text(entry)
    dec_txt = loop_decisions_text(entry, hls_json)
    mem_txt = memory_tables_text(entry, meta)
    rtl_txt, rtl_json = None, None
    if rtl_dir:
        rtl_json = RTL.collect(rtl_dir, top=entry.get("top"))
        rtl_json["source"] = rtl_how
        rtl_txt = _capture(lambda: RTL.print_summary(rtl_json, rtl_how or "given"))
    bundle = out_root / f"{ds}__{bench}"
    summary = summary_lines(key, entry, rows, meta, hls_json, rtl_json, bundle if write else None)
    if write:
        bundle.mkdir(parents=True, exist_ok=True)
        (bundle / "align_arrays.txt").write_text(align_txt)
        (bundle / "align_arrays.json").write_text(json.dumps({"meta": meta, "rows": rows}, indent=1, sort_keys=True, default=str))
        (bundle / "loop_decisions.txt").write_text(dec_txt + "\n")
        (bundle / "loop_tables.txt").write_text(loops_txt + "\n")
        (bundle / "memory_tables.txt").write_text(mem_txt + "\n")
        (bundle / "hlsest_debug.txt").write_text(hls_txt + "\n")
        for stale in ("rtl_memories.txt", "rtl_memories.json"):
            if not rtl_txt and (bundle / stale).exists():
                (bundle / stale).unlink()
        if rtl_txt:
            (bundle / "rtl_memories.txt").write_text(rtl_txt + "\n")
            (bundle / "rtl_memories.json").write_text(json.dumps(rtl_json, indent=1, sort_keys=True))
        (bundle / "trace.json").write_text(json.dumps({
            "key": key, "meta": meta,
            "vitis": {k: entry.get(k) for k in ("status", "top", "totals", "cache_dir", "key", "part", "clock", "vitis_version",
                                                "loops", "memories", "instances", "log", "note")},
            "arrays": rows,
            "hlsest": {"path": hj, "pick": meta.get("hlsest_pick"), "total_bram": (hls_json or {}).get("total_bram"),
                       "version": (hls_json or {}).get("version"), "pipelines": (hls_json or {}).get("pipelines")},
            "rtl": rtl_json}, indent=1, sort_keys=True, default=str))
        readme = [f"# trace {key}", "",
                  f"- top: `{entry.get('top')}`; Vitis status `{entry.get('status')}` ({entry.get('vitis_version')}, "
                  f"{entry.get('part')}, {entry.get('clock')}); cache `{entry.get('cache_dir')}`",
                  f"- hls-est debug JSON: `{hj}` ({meta.get('hlsest_pick')})",
                  f"- RTL: {meta['rtl_source']}" + (f" (`{rtl_dir}`)" if rtl_dir else ""), "",
                  "| file | content |", "|---|---|",
                  "| align_arrays.txt/json | every array across source / a.o.1 / a.o.2 / a.o.3 / sched / report / rtl / hls-est, first divergence |",
                  "| loop_decisions.txt | Vitis log lines by class (auto_pipeline, unroll, flatten, partition, replicate, ...); hls-est pipelines[] |",
                  "| loop_tables.txt | per-module loop tables |",
                  "| memory_tables.txt | per-module memory tables, BRAM instances, csynth totals, reconciliation |",
                  "| hlsest_debug.txt | hls-est debug JSON per array |"]
        if rtl_txt:
            readme.append("| rtl_memories.txt/json | physical memories in the RTL (ports, copies, style, init) |")
        readme += ["| trace.json | all of the above, machine-readable |", "", "## summary", "", "```"] + summary + ["```", ""]
        (bundle / "README.md").write_text("\n".join(readme))
    return bundle, summary


def summary_lines(key, entry, rows, meta, hls_json, rtl_json=None, bundle=None):
    """<= SUMMARY_MAX lines.  Sections get fixed budgets; overflow says where the rest is."""
    tot = entry.get("totals") or {}
    out = []
    hj = meta.get("hlsest_json")
    out.append(f"{key}: top {entry.get('top')}; Vitis {entry.get('status')} BRAM {tot.get('BRAM')} DSP {tot.get('DSP')} "
               f"FF {tot.get('FF')} LUT {tot.get('LUT')}; hls-est total {meta.get('hlsest_total')} "
               f"({Path(hj).parent.name if hj else 'no debug json'})")
    out.append(f"cache {meta.get('cache_dir')}" + (f"; bundle {bundle}" if bundle else ""))
    out.append(f"rtl: {meta.get('rtl_dir') or meta.get('rtl_source')}")
    out.append(f"hls-est pipeline: {meta.get('hlsest_pipeline') or 'unknown'} [{meta.get('hlsest_pick') or '-'}]")
    out.append(AA.reconcile_line(meta))
    # arrays with BRAM on either side (biggest first, differences marked); the rest grouped by divergence
    arr = [r for r in rows if r["kind"] != "arg" and ((r["vitis_bram"] or 0) or (r["hlsest_bram"] or 0))]
    rest = [r for r in rows if r["kind"] != "arg" and r not in arr]
    out.append("arrays with BRAM [Vitis | hls-est | hls-est status] source form -> first divergence   (* = BRAM differs)")
    budget_arr = 12
    for i, r in enumerate(arr):
        if i >= budget_arr:
            out.append(f"  ... +{len(arr) - i} more arrays with BRAM (align_arrays.txt)")
            break
        vb, hb = r["vitis_bram"], r["hlsest_bram"]
        mark = "*" if (vb or 0) != (hb or 0) else " "
        out.append(f" {mark}{r['array'][:28]:28} [{str(vb if vb is not None else '-'):>4} | {str(hb if hb is not None else '-'):>4} | "
                   f"{(r['hlsest_status'] or '-')[:14]:14}] {r['forms']['source']} -> {r['divergence'][:64]}"
                   + (f" | hls-est {r.get('hlsest_form')}" if r.get("hlsest_form") not in (None, "-") else ""))
    groups = {}
    for r in rest:
        cat = re.sub(r" at a\.o\.\d.*| \(.*", "", r["divergence"])
        stg = re.search(r"at (a\.o\.\d)", r["divergence"])
        groups.setdefault(cat + (f" at {stg.group(1)}" if stg else ""), []).append(r["array"])
    if groups:
        out.append("arrays with 0 BRAM on both sides, by first divergence:")
        for cat, names in sorted(groups.items(), key=lambda kv: -len(kv[1]))[:4]:
            out.append(f"  {cat} ({len(names)}): " + ", ".join(names)[:140])
    args_only = [r for r in rows if r["kind"] == "arg" and not r["vitis_bram"] and not r["hlsest_bram"]]
    if args_only:
        out.append("  interfaces: " + ", ".join(f"{r['array']}({r['forms']['source']})" for r in args_only)[:150])
    notes = [r for r in arr if r.get("notes")]
    for r in notes[:4]:
        out.append(f"  note {r['array']}: " + "; ".join(r["notes"])[:150])
    if len(notes) > 4:
        out.append(f"  ... +{len(notes) - 4} more notes (align_arrays.txt)")
    # RTL facts that the report does not show
    if rtl_json:
        mems = rtl_json.get("memories") or []
        rep = [m for m in mems if (m.get("copies") or 1) > 1]
        dist = [m for m in mems if (m.get("style") or "") == "distributed"]
        facts = [f"{len(mems)} memory instances"]
        facts += [f"{m['instance']} {m['copies']} copies ports {m['port_modes']}" for m in rep[:3]]
        if dist:
            facts.append(f"{len(dist)} distributed-style (LUTRAM): " + ", ".join(m["instance"] for m in dist)[:80])
        if rtl_json.get("module_instances"):
            top = re.escape(str(entry.get("top")))
            facts.append("parents instantiated: " + ", ".join(f"{re.sub('^' + top + '_', '', m)} x{n}"
                                                               for m, n in rtl_json["module_instances"].items())[:90])
        t = rtl_json.get("top") or {}
        if t.get("m_axi_bundles"):
            facts.append("m_axi " + ",".join(t["m_axi_bundles"]))
        out.append("rtl: " + "; ".join(facts)[:220])
    # loop decisions (Vitis log)
    log = entry.get("log") or {}
    dec = []
    for cls in ("auto_pipeline", "unroll", "flatten", "flatten_disabled", "partition_inferred", "partition_const_index",
                "partition_small", "replicate", "storage_inferred"):
        for row in log.get(cls) or []:
            dec.append(fmt_log_row(cls, row))
    viol = {}
    for row in log.get("ii_violation_ports") or []:
        try:
            ii = int(row[7])
        except (TypeError, ValueError, IndexError):
            continue
        viol.setdefault((row[1], row[6]), set()).add(ii)
    out.append(f"Vitis loop/memory decisions from the log ({len(dec)} + {len(viol)} port-limited loop/array pairs):")
    for d in dec[:10]:
        out.append("  " + d[:150])
    if len(dec) > 10:
        out.append(f"  ... +{len(dec) - 10} more (loop_decisions.txt)")
    if viol:
        def iis(v):
            v = sorted(v)
            return f"{v[0]}-{v[-1]}" if len(v) > 2 and v == list(range(v[0], v[-1] + 1)) else ",".join(map(str, v))
        out.append(("  port-limited (II tried and failed): "
                    + "; ".join(f"{lp}/{a} II {iis(v)}" for (lp, a), v in sorted(viol.items())))[:220])
    # loop table (pipelined loops first) and hls-est's pipelines next to it
    loops = sorted(entry.get("loops") or [], key=lambda l: (l.get("pipelined") != "yes", str(l.get("module")), str(l.get("name"))))
    out.append(f"Vitis loop table ({len(loops)} loops): loop  pipelined  II  trip  iter-latency  [module]")
    for l in loops[:7]:
        out.append(f"  {str(l.get('name'))[:40]:40} {str(l.get('pipelined')):4} II {str(l.get('ii_achieved')):>3} "
                   f"trip {str(l.get('trip_count')):>6} lat {str(l.get('iter_latency')):>5} [{short_path(l.get('module'))[:46]}]")
    if len(loops) > 7:
        out.append(f"  ... +{len(loops) - 7} more (loop_tables.txt)")
    hp = hlsest_pipeline_rows(hls_json)
    if hls_json is not None:
        out.append(f"hls-est pipelines ({len(hp)}; MLIR lines): "
                   + "; ".join(f"{r['loop@mlir']} II {r['II']} trip {r['trip']}"
                               + (f" unroll {r['unrolled']}" if r["unrolled"] != "-" else "") for r in hp)[:330])
    # memory table
    mems = sorted(entry.get("memories") or [], key=lambda m: -(m.get("BRAM_18K") or 0))
    out.append(f"Vitis memory table ({len(mems)} rows, sum BRAM {sum(m.get('BRAM_18K') or 0 for m in mems)} as printed): "
               f"Memory  core  Words x Bits  BRAM  [module]")
    for m in mems[:6]:
        out.append(f"  {str(m.get('Memory'))[:34]:34} {str(m.get('core'))[:20]:20} {str(m.get('Words')):>6}x{str(m.get('Bits')):<3} "
                   f"{str(m.get('BRAM_18K')):>3} [{str(m.get('module'))[:40]}]")
    if len(mems) > 6:
        out.append(f"  ... +{len(mems) - 6} more (memory_tables.txt)")
    if len(out) > SUMMARY_MAX:
        out = out[:SUMMARY_MAX - 1] + [f"  ... summary truncated to {SUMMARY_MAX} lines; see the bundle"]
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("keys", nargs="+", help="dataset/benchmark (one or more)")
    ap.add_argument("--summary", action="store_true", help="print the <= 60-line summary")
    ap.add_argument("--hlsest-json", help="hls-est debug JSON (only with a single key)")
    ap.add_argument("--run-id", help="hls-est run id under ~/hls-est-work/hlsest-logs")
    ap.add_argument("--rtl", help="syn/verilog dir (only with a single key)")
    ap.add_argument("--out-root", default=str(TRACES_ROOT))
    ap.add_argument("--vitis", default=str(AA.RESULTS_VITIS))
    ap.add_argument("--no-write", action="store_true", help="do not write the bundle (summary only)")
    args = ap.parse_args()
    if len(args.keys) > 1 and (args.hlsest_json or args.rtl):
        ap.error("--hlsest-json / --rtl need a single key")
    rc = 0
    for key in args.keys:
        try:
            bundle, summary = build(key, args.vitis, args.hlsest_json, args.rtl, Path(args.out_root),
                                    write=not args.no_write, run_id=args.run_id)
        except SystemExit as e:
            print(f"{key}: {e}", file=sys.stderr)
            rc = 2
            continue
        if args.summary or args.no_write:
            print("\n".join(summary))
        else:
            print(f"bundle: {bundle}  ({', '.join(f'{f.name} {f.stat().st_size}B' for f in sorted(bundle.iterdir()))})")
    return rc


if __name__ == "__main__":
    sys.exit(main())
