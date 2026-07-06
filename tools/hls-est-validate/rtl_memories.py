#!/usr/bin/env python3
"""Summarize the physical memories of a Vitis HLS design from its generated RTL.

usage: rtl_memories.py <where> [--json OUT] [--top NAME] [--all] [--no-report] [--no-adapters]
       rtl_memories.py <dataset>/<benchmark> --make-rtl     (re-synthesize once, keeping syn/verilog)

<where> is one of
  * a `syn/verilog` directory,
  * a Vitis work directory (`.../hls`, `.../hls/hls`, or the project root),
  * a harvested cache directory (`~/hls-est-work/vitis-cache/<ds>/<bench>/<hash>`),
  * a results key `dataset/benchmark` (resolved through results/vitis.json).

For every memory module (`*_RAM_*.v`, `*_ROM_*.v`, anything with a
`(* ram_style *)` / `(* rom_style *)` reg array) and every instance of it, it
reports: instance, parent module, core, ram_style/rom_style, data width,
address width and depth (module defaults and per-instance parameter
overrides), the port groups (address/ce/we/d/q per port index -> R, W or RW,
printed compactly as e.g. `RW+15R`), the storage copies (`ram0..ramN` of a
replicated RAM_1WNR) with which port writes and reads each copy, the ROM/RAM
init file, and how many times the parent module is instantiated under the top
(`xN`; from the RTL instantiations, independent of the reports).  The top
module's ports are classified (m_axi / s_axi bundles, ap_memory ports, scalars)
and the m_axi/s_axi adapters' header parameters are listed.  Partition banks
with identical rows are printed as one line (`buff_A_U[0..63] x64`); `--all`
prints every instance.

NOTE (harvest): `run_vitis.py` keeps `report/`, `log/` and `db/` but NOT
`syn/verilog`, so no ground-truth cache dir has RTL.  To cache it, harvest()
would have to copy `hls/syn/verilog/*_RAM_*.v`, `*_ROM_*.v`, their `.dat` init
files and the module headers of every other `*.v` (the top, the
`*_m_axi.v`/`*_s_axi.v` adapters and the sub-modules, for the instantiation
tree) into `<cache>/verilog/`.  Until then this tool reads a leftover work dir
(`/mnt/d/HLS/hls-est-vitis/{work,manual,exp}/...`), and a results key only
uses one whose own csynth memory table equals the ground-truth rows in
results/vitis.json (same configuration and source); it says which dir it used.
`--make-rtl` creates such a dir for one results key: it runs vitis_adhoc.py
with the design's sources, top and cflags (same part, clock and
throughput_driven setting as run_vitis.py) and `--keep`, under
`/mnt/d/HLS/hls-est-vitis/exp/<benchmark>/`.

Every number printed is parsed from the RTL text or from the csynth reports
next to it, except the column `n6(model)`, which is the VITIS_NOTES N6/N5
model (min over aspect modes, x36 only with one live port, < 1024 bits ->
LUTRAM) applied to the RTL shape; it is labelled as a model, is not computed
for `distributed`-style (LUTRAM) memories, and is there only to show where the
measured report number and the model disagree.

Python 3 stdlib only.  Importable: `collect(verilog_dir)` returns the JSON dict.
"""
import argparse
import json
import math
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
try:
    import vitis_parse as VP      # noqa: E402
except Exception:                 # pragma: no cover - the tool still works without the report join
    VP = None

RESULTS_VITIS = HERE / "results" / "vitis.json"

# Places where a leftover (not harvested) Vitis work dir may still hold RTL.  A candidate is
# only used for a results key when its own csynth memory table equals the ground-truth rows
# in results/vitis.json (same configuration, e.g. td=off vs td=auto, and same source).
WORK_DIR_CANDIDATES = [
    "/mnt/d/HLS/hls-est-vitis/work/{ds}/{bench}/hls/syn/verilog",
    "/mnt/d/HLS/hls-est-vitis/exp/{bench}/hls/hls/syn/verilog",
    "/mnt/d/HLS/hls-est-vitis/manual/{bench}_tdoff/hls/hls/syn/verilog",
    "/mnt/d/HLS/hls-est-vitis/manual/{bench}/hls/hls/syn/verilog",
    "/mnt/d/HLS/hls-est-vitis/manual/*/hls/hls/syn/verilog",
]

MODULE_RE = re.compile(r"^\s*module\s+([A-Za-z_][\w$]*)", re.M)
PARAM_RE = re.compile(r"\bparameter\s+(?:\[[^\]]*\]\s*)?([A-Za-z_]\w*)\s*=\s*([^,;\n)]+)")
STYLE_RE = re.compile(r"\(\*\s*(ram_style|rom_style)\s*=\s*\"([^\"]+)\"\s*\*\)")
STORAGE_RE = re.compile(r"\breg\s*(?:\[[^\]]+\])?\s*(ram\d*|rom\d*|mem\d*|srl\d*)\s*\[")
PORT_RE = re.compile(r"^\s*(input|output|inout)\s*(?:reg|wire)?\s*(\[[^\]]+\])?\s*([A-Za-z_]\w*)\s*[;,]", re.M)
READMEM_RE = re.compile(r"\$readmem[hb]\s*\(\s*\"([^\"]+)\"\s*,\s*(\w+)")
# `q3 <= ram2[address3];` (read of copy ram2 by port 3) and `ram2[address0] <= d0;` (write by port 0)
READ_RE = re.compile(r"\bq(\d+)\s*<=\s*([A-Za-z_]\w*)\s*\[\s*address(\d+)\s*\]")
WRITE_RE = re.compile(r"\b([A-Za-z_]\w*)\s*\[\s*address(\d+)\s*\]\s*<=\s*d(\d+)\b")
CORE_RE = re.compile(r"_(RAM_1WNR[A-Z0-9_]*|RAM_AUTO[A-Z0-9_]*|RAM_[A-Z0-9]+(?:_[A-Z0-9]+)*|ROM_[A-Z0-9]+(?:_[A-Z0-9]+)*|FIFO[A-Z0-9_]*|LUTRAM[A-Z0-9_]*)$", re.I)
INST_RE = re.compile(
    r"^\s*([A-Za-z_][\w$]*)\s*(?:#\s*\((?P<params>(?:\s*\.\w+\s*\([^)]*\)\s*,?)+)\s*\))?\s*(?P<inst>[A-Za-z_][\w$]*)\s*\(",
    re.M)
PARAM_OVERRIDE_RE = re.compile(r"\.(\w+)\s*\(\s*([^)]*?)\s*\)")
VERILOG_KEYWORDS = {"module", "endmodule", "always", "assign", "if", "else", "begin", "end", "case",
                    "endcase", "input", "output", "inout", "reg", "wire", "parameter", "localparam",
                    "function", "endfunction", "initial", "generate", "endgenerate", "for", "integer",
                    "default", "posedge", "negedge", "or", "and", "not", "timescale"}


def memory_signature(rows):
    return sorted((str(m.get("Memory")), m.get("BRAM_18K"), m.get("Words"), m.get("Bits")) for m in rows)


def report_dir_for(vdir):
    for rep in (Path(vdir).parent / "report", Path(vdir).parent.parent / "syn" / "report"):
        if rep.is_dir() and any(rep.glob("*_csynth.rpt")):
            return rep
    return None


def report_rows_for(vdir):
    """Memory-table rows of the csynth reports that belong to a verilog dir (sibling report/)."""
    if VP is None:
        return None
    rep = report_dir_for(vdir)
    if rep is None:
        return None
    rows = []
    for r in sorted(rep.glob("*_csynth.rpt")):
        rows += VP.parse_memory_table(r.read_text(errors="replace"), r.name[:-len("_csynth.rpt")])
    return rows


def report_total_bram(vdir):
    """csynth.xml BRAM_18K total next to the RTL (None when absent)."""
    rep = report_dir_for(vdir)
    if rep is None or VP is None or not (rep / "csynth.xml").exists():
        return None
    try:
        return (VP.parse_csynth_xml(rep / "csynth.xml").get("resources") or {}).get("BRAM_18K")
    except Exception:  # noqa: BLE001
        return None


def matches_ground_truth(vdir, entry):
    """(ok, reason): does the RTL dir's own memory table equal the ground-truth memory rows?"""
    rows = report_rows_for(vdir)
    if rows is None:
        return False, "no csynth report next to the RTL"
    a, b = memory_signature(rows), memory_signature(entry.get("memories") or [])
    if a == b:
        return True, f"its memory table equals the ground truth ({len(a)} rows)"
    sa, sb = set(a), set(b)
    return False, (f"memory table differs from the ground truth ({len(sa - sb)} rows only here, {len(sb - sa)} only in "
                   f"results/vitis.json; e.g. {sorted(sa - sb)[:2]})")


# ----------------------------------------------------------------------- resolve

def load_results(path=RESULTS_VITIS):
    try:
        with open(path) as f:
            return json.load(f)
    except Exception:  # noqa: BLE001
        return {}


def find_verilog_dir(where, results=None):
    """Return (verilog_dir, how) or (None, reason).  `how` says where it came from."""
    p = Path(where)
    if p.is_dir():
        for cand in (p, p / "syn" / "verilog", p / "hls" / "syn" / "verilog", p / "hls" / "hls" / "syn" / "verilog",
                     p / "verilog", p / "solution1" / "syn" / "verilog"):
            if cand.is_dir() and any(cand.glob("*.v")):
                return cand, "given"
        for depth in ("*/syn/verilog", "*/*/syn/verilog", "*/*/*/syn/verilog"):
            for cand in sorted(p.glob(depth)):
                if any(cand.glob("*.v")):
                    return cand, "found below the given dir"
        return None, f"no syn/verilog with *.v under {p}"
    if "/" in str(where) and not str(where).startswith("/"):
        key = str(where)
        res = results if results is not None else load_results()
        e = res.get(key)
        if e and e.get("cache_dir"):
            cdir = Path(e["cache_dir"])
            for cand in (cdir / "verilog", cdir / "syn" / "verilog"):
                if cand.is_dir() and any(cand.glob("*.v")):
                    return cand, "harvested cache"
        ds, bench = key.split("/", 1)
        rejected = []
        seen = set()
        for pat in WORK_DIR_CANDIDATES:
            for cand in sorted(Path("/").glob(pat.format(ds=ds, bench=bench).lstrip("/"))):
                if cand in seen or not cand.is_dir() or not any(cand.glob("*.v")):
                    continue
                seen.add(cand)
                ok, why = matches_ground_truth(cand, e or {})
                if ok:
                    return cand, f"leftover work dir ({why}; not the harvested cache)"
                if "*" not in pat:
                    rejected.append(f"{cand}: {why}")
        return None, (f"{key}: the harvest keeps no syn/verilog (see the NOTE in rtl_memories.py; "
                      f"`rtl_memories.py {key} --make-rtl` re-synthesizes it once) and no leftover work dir with a "
                      f"matching memory table was found" + ("; rejected: " + " | ".join(rejected) if rejected else ""))
    return None, f"{where}: not a directory and not a results key"


def make_rtl(key, timeout=3600):
    """Run vitis_adhoc.py for a results key with --keep so that exp/<bench>/hls/hls/syn/verilog exists."""
    import designs              # noqa: E402  (harness modules; imported lazily)
    import run_vitis as RV      # noqa: E402
    ds, bench = key.split("/", 1)
    cands = [d for d in designs.load_designs() if d["dataset"] == ds and d["benchmark"] == bench]
    if not cands:
        return 2, f"{key}: not in designs.load_designs()"
    d = cands[0]
    srcs = [str((Path(d["dir"]) / s).resolve()) for s in d["sources"]]
    cflags = " ".join(RV.cflags_for(d))
    cmd = [sys.executable, str(HERE / "vitis_adhoc.py"), "--name", bench, "--src", *srcs, "--top", d["top"],
           "--keep", "--quiet", "--timeout", str(timeout)]
    if cflags:
        cmd.append("--cflags=" + cflags)        # '=' form: the value starts with '-I'
    extra = [x for x in RV.EXTRA_CFG if not x.startswith("syn.array_partition.throughput_driven")]
    for x in extra:
        cmd.append("--extra=" + x)
    p = subprocess.run(cmd, capture_output=True, text=True, errors="replace")
    tail = (p.stdout + p.stderr).strip().splitlines()[-3:]
    return p.returncode, " | ".join(tail)


# ------------------------------------------------------------------------ parse

def _int_or_text(s):
    s = s.strip()
    try:
        return int(s)
    except ValueError:
        m = re.match(r"^\d+'[dhb]([0-9a-fA-F_]+)$", s)
        if m:
            try:
                base = {"d": 10, "h": 16, "b": 2}[s.split("'")[1][0]]
                return int(m.group(1).replace("_", ""), base)
            except Exception:  # noqa: BLE001
                pass
        return s


def parse_ports(text):
    """Port groups keyed by trailing index: [{'index', 'signals', 'mode'}], other port names."""
    groups = {}
    others = []
    for m in PORT_RE.finditer(text):
        name = m.group(3)
        mm = re.match(r"^(address|ce|we|d|q|dout|din|wen|ren)(\d+)$", name)
        if mm:
            groups.setdefault(int(mm.group(2)), set()).add(mm.group(1))
        else:
            others.append(name)
    ports = []
    for k in sorted(groups):
        g = groups[k]
        has_r = "q" in g or "dout" in g
        has_w = ("d" in g and "we" in g) or "din" in g or "wen" in g
        mode = "RW" if has_r and has_w else "R" if has_r else "W" if has_w else "?"
        ports.append({"index": k, "signals": sorted(g), "mode": mode})
    return ports, others


def compact_modes(ports):
    """['RW','R','R'] -> 'RW+2R'."""
    runs = []
    for p in ports:
        if runs and runs[-1][0] == p["mode"]:
            runs[-1][1] += 1
        else:
            runs.append([p["mode"], 1])
    return "+".join(f"{n}{m}" if n > 1 else m for m, n in runs)


def parse_copy_map(text, copies):
    """{copy: {'reads': [port...], 'writes': [port...]}} from the always blocks of a memory module."""
    cm = {c: {"reads": set(), "writes": set()} for c in copies}
    for q, store, addr in READ_RE.findall(text):
        if store in cm:
            cm[store]["reads"].add(int(addr))
    for store, addr, _d in WRITE_RE.findall(text):
        if store in cm:
            cm[store]["writes"].add(int(addr))
    return {c: {"reads": sorted(v["reads"]), "writes": sorted(v["writes"])} for c, v in cm.items()}


def copy_map_text(cm):
    """'all written by port 0; reads/copy: ram0=2 (q0,q1), 14 copies x1' style summary."""
    if not cm:
        return "-"
    wsets = {tuple(v["writes"]) for v in cm.values()}
    if len(wsets) == 1:
        w = tuple(wsets)[0]
        wtxt = ("all written by port " + ",".join(map(str, w))) if w else "never written (ROM)"
    else:
        wtxt = "writes " + "; ".join(f"{c}:{','.join(map(str, v['writes'])) or '-'}" for c, v in cm.items())
    by_n = {}
    for c, v in cm.items():
        by_n.setdefault(len(v["reads"]), []).append(c)
    parts = []
    for n, cs in sorted(by_n.items(), key=lambda kv: (-kv[0], kv[1][0])):
        if len(cs) <= 2:
            parts += [f"{c}={n}R(q{',q'.join(map(str, cm[c]['reads']))})" if n else f"{c}=0R" for c in cs]
        else:
            parts.append(f"{len(cs)} copies x{n}R")
    return f"{wtxt}; reads/copy: " + ", ".join(parts)


def parse_memory_file(path):
    """One `*_RAM_*.v` / `*_ROM_*.v` file -> dict, or None when it holds no storage array."""
    text = path.read_text(errors="replace")
    mods = MODULE_RE.findall(text)
    if not mods:
        return None
    name = mods[0]
    storage = STORAGE_RE.findall(text)
    styles = STYLE_RE.findall(text)
    if not storage and not styles:
        return None
    params = {k: _int_or_text(v) for k, v in PARAM_RE.findall(text)}
    ports, other_ports = parse_ports(text)
    core = None
    m = CORE_RE.search(name)
    if m:
        core = m.group(1).upper()
    init = None
    rm = READMEM_RE.search(text)
    if rm:
        init = {"file": rm.group(1), "target": rm.group(2)}
        dat = path.parent / Path(rm.group(1)).name
        if dat.exists():
            n = 0
            with open(dat, errors="replace") as f:
                for line in f:
                    if line.strip():
                        n += 1
            init["lines"] = n
    unref_dat = None
    if init is None and (path.parent / (path.stem + ".dat")).exists():
        unref_dat = path.stem + ".dat"      # Vitis writes it, but no $readmem in the module uses it
    copies = sorted(set(storage), key=lambda s: (re.sub(r"\d+$", "", s), int(re.search(r"(\d*)$", s).group(1) or -1)))
    style = {k: v for k, v in styles}
    cm = parse_copy_map(text, copies)
    return {
        "file": path.name,
        "module": name,
        "core": core,
        "kind": "ROM" if (core or "").startswith("ROM") or any(s.startswith("rom") for s in copies) else "RAM",
        "style": style.get("ram_style") or style.get("rom_style"),
        "style_attr": styles[0][0] if styles else None,
        "DataWidth": params.get("DataWidth"),
        "AddressWidth": params.get("AddressWidth"),
        "AddressRange": params.get("AddressRange"),
        "params": params,
        "ports": ports,
        "n_ports": len(ports),
        "port_modes": compact_modes(ports),
        "storage_arrays": copies,
        "copies": len(copies) if copies else None,
        "copy_map": cm,
        "copy_map_text": copy_map_text(cm) if len(copies) > 1 else None,
        "replicated_1wnr": len(copies) > 1,
        "core_1wnr": bool(core and "1WNR" in core),
        "init": init,
        "unreferenced_dat": unref_dat,
        "other_ports": other_ports,
    }


def module_spans(text):
    """[(start offset, module name)] for every module defined in a file."""
    return [(m.start(), m.group(1)) for m in MODULE_RE.finditer(text)]


def parse_instances(path, wanted):
    """Instantiations of modules in `wanted` inside one RTL file (parent = enclosing module)."""
    text = path.read_text(errors="replace")
    spans = module_spans(text)
    out = []
    for m in INST_RE.finditer(text):
        mod = m.group(1)
        if mod in VERILOG_KEYWORDS or mod not in wanted:
            continue
        parent = path.stem
        for off, name in spans:
            if off <= m.start():
                parent = name
        if parent == mod:
            continue
        overrides = {}
        if m.group("params"):
            for k, v in PARAM_OVERRIDE_RE.findall(m.group("params")):
                overrides[k] = _int_or_text(v)
        out.append({"instance": m.group("inst"), "module": mod, "parent": parent, "overrides": overrides})
    return out


def classify_top_ports(text):
    """Classify the top module's port names: AXI bundles, ap_memory ports, scalars, control."""
    mods = MODULE_RE.findall(text)
    if not mods:
        return None
    name = mods[0]
    body = text[text.find("module " + name):]
    header_end = body.find(");")
    header = body[:header_end] if header_end > 0 else body[:5000]
    names = re.findall(r"\b([A-Za-z_]\w*)\b", header.split("(", 1)[1] if "(" in header else header)
    names = [n for n in names if n not in VERILOG_KEYWORDS]
    axi_m, axi_s, apmem, control, scalar = {}, {}, {}, [], []
    for n in names:
        m = re.match(r"^m_axi_(\w+?)_(AW|W|B|AR|R)[A-Z]+$", n)
        if m:
            axi_m[m.group(1)] = axi_m.get(m.group(1), 0) + 1
            continue
        m = re.match(r"^s_axi_(\w+?)_[A-Z]+$", n)
        if m:
            axi_s[m.group(1)] = axi_s.get(m.group(1), 0) + 1
            continue
        m = re.match(r"^(\w+?)_(address|ce|we|d|q)(\d+)$", n)
        if m:
            apmem.setdefault(m.group(1), set()).add(m.group(2) + m.group(3))
            continue
        if n.startswith("ap_"):
            control.append(n)
            continue
        scalar.append(n)
    ap_mem = {}
    for k, v in apmem.items():
        has_q = any(s.startswith("q") for s in v)
        has_w = any(s.startswith("we") or s.startswith("d") for s in v)
        ap_mem[k] = {"signals": sorted(v), "ports": sorted({re.sub(r"^\D+", "", s) for s in v}, key=int),
                     "mode": "RW" if has_q and has_w else "R" if has_q else "W" if has_w else "?"}
    scalars = sorted({re.sub(r"_(ap_vld|ap_ack|ap_none|dout|empty_n|read|din|full_n|write)$", "", s) for s in scalar})
    return {"module": name, "m_axi_bundles": axi_m, "s_axi_bundles": axi_s, "ap_memory_ports": ap_mem,
            "control": control, "scalar_ports": scalars, "n_ports": len(names)}


def parse_adapter(path):
    """Header parameters of an m_axi / s_axi adapter and its internal storage arrays."""
    text = path.read_text(errors="replace")
    mods = MODULE_RE.findall(text)
    if not mods:
        return None
    first = text[text.find("module " + mods[0]):]
    header = first[:first.find(");")] if ");" in first else first[:4000]
    params = {}
    for k, v in re.findall(r"([A-Za-z_]\w*)\s*=\s*(\d+)", header):
        params[k] = int(v)
    storage = []
    for sm in re.finditer(r"\breg\s*\[([^\]]+)\]\s*(\w+)\s*\[([^\]]+)\]", text):
        storage.append({"name": sm.group(2), "width_expr": sm.group(1).strip(), "depth_expr": sm.group(3).strip()})
    styles = STYLE_RE.findall(text)
    return {"file": path.name, "module": mods[0], "submodules": mods[1:], "params": params,
            "storage_arrays": storage[:20], "styles": sorted({v for _, v in styles})}


# ----------------------------------------------------------------- N6 model

def n6_model_bram(depth, width, one_live_port):
    """VITIS_NOTES N6 (+N5 threshold).  A model, not a measurement."""
    if not isinstance(depth, int) or not isinstance(width, int) or depth <= 0 or width <= 0:
        return None
    if depth * width < 1024:
        return 0
    P = 1 << max(0, math.ceil(math.log2(depth)))
    modes = [(1, 16384), (2, 8192), (4, 4096), (9, 2048), (18, 1024)]
    if one_live_port:
        modes.append((36, 512))
    best = None
    for m, d in modes:
        n = math.ceil(width / m) * max(1, P // d)
        best = n if best is None else min(best, n)
    return best


# ------------------------------------------------------------------- collect

def _report_rows(vdir):
    """Memory-table rows (instance name -> row) from the csynth reports next to the RTL, if any."""
    rows = {}
    for m in report_rows_for(vdir) or []:
        rows.setdefault(str(m.get("Memory")), m)
    return rows


def hierarchy_multiplicity(edges, top):
    """{module: number of instances under `top`} from (parent, child) instantiation edges."""
    parents = {}
    for par, child in edges:
        parents.setdefault(child, []).append(par)
    memo = {top: 1} if top else {}

    def mult(mod, stack=()):
        if mod in memo:
            return memo[mod]
        if mod not in parents or mod in stack:
            return 1 if not top or mod == top else 0
        n = sum(mult(p, stack + (mod,)) for p in parents[mod])
        memo[mod] = n
        return n
    return {m: mult(m) for m in set(parents) | {p for p, _ in edges}}


def collect(vdir, top=None, with_report=True, with_adapters=True):
    vdir = Path(vdir)
    files = sorted(vdir.glob("*.v"))
    mem_mods = {}
    defined = {}
    for f in files:
        try:
            text = f.read_text(errors="replace")
        except OSError:
            continue
        for _off, name in module_spans(text):
            defined[name] = f
        if re.search(r"_(RAM|ROM|FIFO|LUTRAM)[A-Za-z0-9_]*\.v$", f.name, re.I) or re.search(r"_(m|s)_axi", f.name) is None:
            try:
                d = parse_memory_file(f)
            except Exception as e:  # noqa: BLE001
                d = None
                print(f"warning: {f.name}: {e}", file=sys.stderr)
            if d and (d["core"] or d["style"]):
                mem_mods[d["module"]] = d
    instances = []      # memory instances
    edges = []          # (parent module, child module) for every instantiation of a defined module
    for f in files:
        if f.stem in mem_mods:
            continue
        for ins in parse_instances(f, set(defined)):
            edges.append((ins["parent"], ins["module"]))
            if ins["module"] in mem_mods:
                instances.append(ins)
    # top: the given name, else the defined module nobody instantiates that is not a memory/adapter
    children = {c for _, c in edges}
    top_name = top if top in defined else None
    if top_name is None:
        roots = [m for m in defined if m not in children and m not in mem_mods
                 and not re.search(r"_(m|s)_axi", m) and defined[m].stem == m]
        top_name = roots[0] if len(roots) == 1 else (min(roots, key=len) if roots else None)
    mult = hierarchy_multiplicity(edges, top_name)
    report = _report_rows(vdir) if with_report else {}
    memories = []
    for ins in instances:
        md = mem_mods[ins["module"]]
        width = ins["overrides"].get("DataWidth", md["DataWidth"])
        depth = ins["overrides"].get("AddressRange", md["AddressRange"])
        awidth = ins["overrides"].get("AddressWidth", md["AddressWidth"])
        one_port = md["n_ports"] <= 1
        dist = (md["style"] or "").lower() in ("distributed", "registers") or "LUTRAM" in (md["core"] or "")
        if dist:
            n6 = None
        elif md["copies"] in (None, 1):
            n6 = n6_model_bram(depth, width, one_port)
        else:
            n6 = (n6_model_bram(depth, width, False) or 0) * md["copies"]
        rep = report.get(ins["instance"])
        k = mult.get(ins["parent"], 1)
        memories.append({
            "instance": ins["instance"], "parent": ins["parent"], "parent_instances": k,
            "module": md["module"], "core": md["core"], "kind": md["kind"], "style": md["style"],
            "width": width, "addr_bits": awidth, "depth": depth,
            "n_ports": md["n_ports"], "port_modes": md["port_modes"], "copies": md["copies"],
            "copy_map_text": md["copy_map_text"], "replicated_1wnr": md["replicated_1wnr"], "core_1wnr": md["core_1wnr"],
            "init": md["init"], "unreferenced_dat": md["unreferenced_dat"],
            "n6_model_bram": n6, "n6_not_applicable": "distributed (LUTRAM) style" if dist else None,
            "report_BRAM_18K": rep.get("BRAM_18K") if rep else None,
            "report_BRAM_18K_x_instances": (rep.get("BRAM_18K") or 0) * k if rep else None,
            "report_Words": rep.get("Words") if rep else None,
            "report_Bits": rep.get("Bits") if rep else None,
            "report_module": rep.get("module") if rep else None,
        })
    uninstantiated = [m for m in mem_mods if m not in {i["module"] for i in instances}]
    adapters = []
    if with_adapters:
        for f in files:
            if re.search(r"_(m|s)_axi\.v$", f.name):
                a = parse_adapter(f)
                if a:
                    adapters.append(a)
    top_info = None
    if top_name and top_name in defined:
        top_info = classify_top_ports(defined[top_name].read_text(errors="replace"))
        if top_info:
            top_info["file"] = defined[top_name].name
    rpt_sum = sum(m["report_BRAM_18K_x_instances"] or 0 for m in memories) if report else None
    return {
        "verilog_dir": str(vdir),
        "n_files": len(files),
        "top": top_info,
        # modules that hold memory instances and are instantiated other than once under the top
        "module_instances": {m: mult.get(m, 1) for m in sorted({x["parent"] for x in memories}) if mult.get(m, 1) != 1},
        "top_module": top_name,
        "memories": memories,
        "memory_modules": list(mem_mods.values()),
        "uninstantiated_memory_modules": uninstantiated,
        "adapters": adapters,
        "report_joined": bool(report),
        "report_bram_in_memories": rpt_sum,
        "csynth_total_bram": report_total_bram(vdir) if with_report else None,
        "n6_model_note": "n6(model) is the VITIS_NOTES N6/N5 formula applied to the RTL shape, not a measurement",
    }


# --------------------------------------------------------------------- print

def fmt_table(rows, cols, max_w=48):
    widths = [min(max_w, max(len(c), *(len(str(r.get(c, ""))) for r in rows))) if rows else len(c) for c in cols]
    out = ["  ".join(c.ljust(w) for c, w in zip(cols, widths))]
    out.append("  ".join("-" * w for w in widths))
    for r in rows:
        out.append("  ".join(str(r.get(c, ""))[:w].ljust(w) for c, w in zip(cols, widths)))
    return "\n".join(out)


def _bank_base(inst):
    b = re.sub(r"_U(_x)?$", "", inst)
    m = re.match(r"^(.*?)((?:_\d+)+)$", b)
    return (m.group(1), m.group(2)) if m else (b, "")


def table_rows(d, group=True):
    rows = []
    for m in d["memories"]:
        rows.append({
            "instance": m["instance"], "parent": m["parent"] + (f" x{m['parent_instances']}" if m["parent_instances"] != 1 else ""),
            "core": m["core"] or "?", "style": m["style"] or "-",
            "shape": f"{m['depth']}x{m['width']}", "addr": m["addr_bits"], "ports": m["port_modes"] or "-",
            "copies": m["copies"] if m["copies"] is not None else "-",
            "init": (Path(m["init"]["file"]).name[-30:] + f"({m['init'].get('lines', '?')})") if m["init"] else "-",
            "rpt_BRAM": m["report_BRAM_18K"] if m["report_BRAM_18K"] is not None else "-",
            "rpt_WxB": f"{m['report_Words']}x{m['report_Bits']}" if m["report_Words"] is not None else "-",
            "n6(model)": m["n6_model_bram"] if m["n6_model_bram"] is not None else ("dist" if m["n6_not_applicable"] else "-"),
        })
    if not group:
        return rows
    out, index = [], {}
    for r in rows:
        base, suf = _bank_base(r["instance"])
        key = (base, r["parent"], r["core"], r["style"], r["shape"], r["ports"], r["copies"], r["rpt_BRAM"], r["rpt_WxB"],
               r["n6(model)"], r["init"])
        if key in index:
            g = index[key]
            g["_n"] += 1
            g["_suffixes"].append(suf)
            continue
        g = dict(r)
        g["_n"], g["_suffixes"], g["_base"] = 1, [suf], base
        index[key] = g
        out.append(g)
    for g in out:
        if g["_n"] > 1:
            nums = sorted(int(s.strip("_").split("_")[-1]) if s else 0 for s in g["_suffixes"])
            rng = f"{nums[0]}..{nums[-1]}" if nums == list(range(nums[0], nums[-1] + 1)) else ",".join(map(str, nums[:6]))
            g["instance"] = f"{g['_base']}_U[{rng}] x{g['_n']}"
            if isinstance(g["rpt_BRAM"], int):
                g["rpt_BRAM"] = f"{g['rpt_BRAM']} each"
        for k in ("_n", "_suffixes", "_base"):
            g.pop(k)
    return out


def print_summary(d, how, show_all=False, out=None):
    p = lambda s="": print(s, file=out or sys.stdout)  # noqa: E731  (sys.stdout looked up per call: redirect_stdout works)
    p(f"RTL: {d['verilog_dir']}  ({how}; {d['n_files']} .v files; report joined: {d['report_joined']})")
    t = d.get("top")
    if t:
        apm = ", ".join(f"{k}:{v['mode']}x{len(v['ports'])}p" for k, v in t["ap_memory_ports"].items())
        p(f"top module {t['module']} ({t['file']}): {t['n_ports']} ports; m_axi bundles {t['m_axi_bundles'] or '-'}; "
          f"s_axi {t['s_axi_bundles'] or '-'}; ap_memory ports {{{apm}}}; scalars {t['scalar_ports']}")
    if d.get("module_instances"):
        p("memory-holding modules instantiated other than once under the top (RTL): "
          + ", ".join(f"{m} x{n}" for m, n in d["module_instances"].items()))
    rows = table_rows(d, group=not show_all)
    cols = ["instance", "parent", "core", "style", "shape", "addr", "ports", "copies", "init", "rpt_BRAM", "rpt_WxB", "n6(model)"]
    p(fmt_table(rows, cols))
    for m in d["memories"]:
        if m["copy_map_text"]:
            p(f"  {m['instance']}: {m['copies']} storage copies (ram0..ram{m['copies'] - 1}); {m['copy_map_text']}")
        elif m["core_1wnr"]:
            p(f"  {m['instance']}: {m['core']} core with a single storage copy (ports {m['port_modes']})")
    if d["report_joined"]:
        p(f"report BRAM held by these memories (x parent instances): {d['report_bram_in_memories']}; "
          f"csynth total BRAM_18K: {d['csynth_total_bram']}"
          + (f"; difference {d['csynth_total_bram'] - d['report_bram_in_memories']} is outside the memory instances "
             f"(adapters/FIFOs)" if isinstance(d['csynth_total_bram'], int) and d['csynth_total_bram'] != d['report_bram_in_memories'] else ""))
    if d["uninstantiated_memory_modules"]:
        p("memory modules never instantiated: " + ", ".join(d["uninstantiated_memory_modules"]))
    if d["adapters"]:
        p("adapters:")
        for a in d["adapters"]:
            keys = [k for k in a["params"] if re.search(r"DATA_WIDTH|ADDR_WIDTH|USER_DW|USER_AW|USER_MAXREQS|RFIFO|WFIFO|FIFO_DEPTH|BUFFER|MAXREQS|NUM_READ|NUM_WRITE", k)]
            ps = ", ".join(f"{k}={a['params'][k]}" for k in keys[:8])
            st = ", ".join(f"{s['name']}[{s['depth_expr']}]x[{s['width_expr']}]" for s in a["storage_arrays"][:3])
            p(f"  {a['module']}: {ps or '-'}; storage {st or '-'}")
    p(d["n6_model_note"])


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("where", help="verilog/work/cache dir or dataset/benchmark")
    ap.add_argument("--json", help="write the full result as JSON here")
    ap.add_argument("--top", help="top module name (default: the module no file instantiates)")
    ap.add_argument("--all", action="store_true", help="one line per instance (default: identical banks on one line)")
    ap.add_argument("--no-report", action="store_true", help="do not join the csynth memory tables")
    ap.add_argument("--no-adapters", action="store_true", help="skip the *_m_axi.v / *_s_axi.v adapters")
    ap.add_argument("--make-rtl", action="store_true",
                    help="for a dataset/benchmark key with no RTL: run vitis_adhoc.py --keep once (a Vitis run)")
    args = ap.parse_args()
    vdir, how = find_verilog_dir(args.where)
    if vdir is None and args.make_rtl and "/" in args.where and not args.where.startswith("/"):
        print(f"{how}\n-> running vitis_adhoc.py for {args.where} (keeps the work dir) ...", file=sys.stderr)
        rc, tail = make_rtl(args.where)
        print(f"vitis_adhoc.py exit {rc}: {tail}", file=sys.stderr)
        vdir, how = find_verilog_dir(args.where)
    if vdir is None:
        print(how, file=sys.stderr)
        return 2
    d = collect(vdir, top=args.top, with_report=not args.no_report, with_adapters=not args.no_adapters)
    d["source"] = how
    print_summary(d, how, show_all=args.all)
    if args.json:
        with open(args.json, "w") as f:
            json.dump(d, f, indent=1, sort_keys=True)
        print(f"wrote {args.json}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
