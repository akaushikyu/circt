"""Parsers for Vitis HLS 2025.1 csynth outputs (v++ -c --mode hls work dir).

Layout of a work dir W (after `v++ -c --mode hls --config cfg --work_dir W`):
  W/hls/syn/report/csynth.{rpt,xml}            top-level summary
  W/hls/syn/report/<module>_csynth.{rpt,xml}   one per RTL module (top, Pipeline_* , callees)
  W/hls/.autopilot/db/                         IR stages (*.bc), *.adb, *.verbose.*.rpt, hls_data.json
  W/logs/hls_compile.log                       transformation messages
"""
import re
import xml.etree.ElementTree as ET
from pathlib import Path

RES = ("BRAM_18K", "DSP", "FF", "LUT", "URAM")


def _num(s):
    s = s.strip()
    if s in ("-", "", "N/A"):
        return None
    try:
        return int(s)
    except ValueError:
        try:
            return float(s)
        except ValueError:
            return s          # e.g. '~0'


def parse_csynth_xml(path):
    """Totals, available resources and run configuration from csynth.xml."""
    root = ET.parse(path).getroot()
    out = {}
    ua = root.find("UserAssignments")
    if ua is not None:
        for tag in ("Part", "TopModelName", "TargetClockPeriod", "FlowTarget", "ProductFamily"):
            e = ua.find(tag)
            if e is not None:
                out[tag] = e.text
    v = root.find("ReportVersion/Version")
    out["Version"] = v.text if v is not None else None
    res = root.find("AreaEstimates/Resources")
    avail = root.find("AreaEstimates/AvailableResources")
    out["resources"] = {r: _num(res.find(r).text) for r in RES if res is not None and res.find(r) is not None}
    out["available"] = {r: _num(avail.find(r).text) for r in RES if avail is not None and avail.find(r) is not None}
    lat = root.find("PerformanceEstimates/SummaryOfOverallLatency")
    if lat is not None:
        out["latency"] = {c.tag: c.text for c in lat}
    return out


_ROW = re.compile(r"^\s*\|(.*)\|\s*$")


def _table_rows(lines, start_idx):
    """Rows of an ASCII table starting at the first '|' line at/after start_idx.
    Returns (list of cell-lists, index after the table)."""
    i = start_idx
    n = len(lines)
    while i < n and not lines[i].lstrip().startswith("|") and not lines[i].lstrip().startswith("+"):
        if lines[i].strip() == "N/A":
            return [], i + 1
        if lines[i].strip().startswith("*") or lines[i].strip().startswith("="):
            return [], i
        i += 1
    rows = []
    while i < n:
        s = lines[i].strip()
        if s.startswith("+"):
            i += 1
            continue
        m = _ROW.match(lines[i])
        if not m:
            break
        rows.append([c.strip() for c in m.group(1).split("|")])
        i += 1
    return rows, i


def parse_utilization_summary(rpt_text):
    """The '* Summary:' table of the Utilization Estimates section.
    Returns {'Total': {...}, 'Available': {...}, 'Utilization (%)': {...}, 'Memory': {...}, ...}"""
    lines = rpt_text.splitlines()
    out = {}
    for i, l in enumerate(lines):
        if l.strip().startswith("== Utilization Estimates"):
            j = i + 1
            while j < len(lines) and not lines[j].strip().startswith("* Summary"):
                j += 1
            rows, _ = _table_rows(lines, j + 1)
            if not rows:
                return out
            hdr = rows[0]
            for r in rows[1:]:
                if len(r) != len(hdr):
                    continue
                out[r[0]] = {hdr[k]: _num(r[k]) for k in range(1, len(hdr))}
            break
    return out


def parse_memory_table(rpt_text, module):
    """Rows of the '* Memory:' detail table of one module report."""
    lines = rpt_text.splitlines()
    mems = []
    for i, l in enumerate(lines):
        if l.strip() == "* Memory:":
            rows, _ = _table_rows(lines, i + 1)
            if not rows:
                return mems
            hdr = rows[0]
            for r in rows[1:]:
                if not r or r[0] == "Total" or len(r) != len(hdr):
                    continue
                d = {hdr[k]: _num(r[k]) for k in range(len(hdr))}
                d["module"] = module
                mems.append(normalize_memory(d))
            break
    return mems


_CORE_RE = re.compile(r"_(RAM_AUTO_1R1W|RAM_1P|RAM_2P|RAM_S2P|RAM_T2P|RAM_1WNR|RAM_1P_[A-Z0-9]+|RAM_2P_[A-Z0-9]+|RAM_T2P_[A-Z0-9]+|RAM_S2P_[A-Z0-9]+|ROM_AUTO_1R|ROM_1P|ROM_2P|ROM_NP|ROM_[A-Z0-9_]+|RAM_[A-Z0-9_]+|FIFO[A-Z0-9_]*|LUTRAM[A-Z0-9_]*)(_\d+)?$", re.I)


def normalize_memory(d):
    """Derive the C array name and partition-bank index from a memory row.

    Instance names look like `buff_A_U`, `V_3_U` (bank 3 of `V`), `scores_7_U`.
    Module names look like `<func>_<array>_RAM_AUTO_1R1W` or `<array>_RAM_1P`
    (shared between identical arrays, so the instance name is authoritative)."""
    inst = str(d.get("Memory", ""))
    name = inst[:-2] if inst.endswith("_U") else inst
    module = str(d.get("Module", ""))
    core = None
    m = _CORE_RE.search(module)
    if m:
        core = m.group(1).upper()
    base, bank = name, None
    mb = re.match(r"^(.*)_(\d+)$", name)
    if mb:
        # Only a bank if the module's embedded array name matches the prefix.
        pre = mb.group(1)
        if core and re.search(re.escape(pre) + r"_" + re.escape(m.group(1)), module, re.I):
            base, bank = pre, int(mb.group(2))
    d["array"] = base
    d["bank"] = bank
    d["core"] = core
    d["bram"] = d.get("BRAM_18K")
    return d


def parse_loop_table(rpt_text, module):
    """'* Loop:' table: per-loop latency/II/trip count/pipelined."""
    lines = rpt_text.splitlines()
    loops = []
    for i, l in enumerate(lines):
        if l.strip() == "* Loop:":
            rows, _ = _table_rows(lines, i + 1)
            if len(rows) < 2:
                return loops
            for r in rows[2:]:
                if len(r) < 8:
                    continue
                loops.append({
                    "module": module, "name": r[0].lstrip("- "), "depth": len(r[0]) - len(r[0].lstrip("- ")),
                    "latency_min": _num(r[1]), "latency_max": _num(r[2]),
                    "iter_latency": _num(r[3]), "ii_achieved": _num(r[4]), "ii_target": _num(r[5]),
                    "trip_count": _num(r[6]), "pipelined": r[7],
                })
            break
    return loops


def parse_instance_table(rpt_text, module):
    """'* Instance:' table of the utilization section: sub-module resources."""
    lines = rpt_text.splitlines()
    out = []
    seen_util = False
    for i, l in enumerate(lines):
        if l.strip().startswith("== Utilization Estimates"):
            seen_util = True
        if seen_util and l.strip() == "* Instance:":
            rows, _ = _table_rows(lines, i + 1)
            if not rows:
                return out
            hdr = rows[0]
            for r in rows[1:]:
                if not r or r[0] == "Total" or len(r) != len(hdr):
                    continue
                d = {hdr[k]: _num(r[k]) for k in range(len(hdr))}
                d["parent"] = module
                out.append(d)
            break
    return out


LOG_PATTERNS = {
    "auto_pipeline": re.compile(r"\[HLS 214-376\] automatically set the pipeline for Loop< ?(\S+?) ?> at (\S+?):(\d+):(\d+)"),
    "unroll_implied": re.compile(r"\[HLS 214-291\] Loop '(\S+)' is marked as complete unroll implied by the pipeline pragma \((\S+?):(\d+):(\d+)\)"),
    "unroll": re.compile(r"\[HLS 214-186\] Unrolling loop '(\S+)' \((\S+?):(\d+):(\d+)\) in function '([^']*)' (completely|partially) with a factor of (\d+)"),
    "partition_inferred": re.compile(r"\[HLS 214-270\] Inferring pragma '([^']*)' for array '([^']*)' due to (.*?) \((\S+?):(\d+):(\d+)\)"),
    "partition_applied": re.compile(r"\[HLS 214-248\] Applying array_partition to '([^']*)': (.*?) \((\S+?):(\d+):(\d+)\)"),
    "flatten": re.compile(r"\[XFORM 203-541\] Flattening a loop nest '(\S+)' \((\S+?):(\d+):(\d+)\) in function '([^']*)'"),
    "inline": re.compile(r"\[HLS 214-178\] Inlining function '([^']*)' into '([^']*)'"),
    "design_size": re.compile(r"\[HLS 200-1995\] There were (\d+) instructions in the design after the '([^']*)' phase"),
    "reshape": re.compile(r"\[HLS 214-\d+\] .*array_reshape.*?'([^']*)'"),
    "removed": re.compile(r"\[(?:HLS|XFORM) [\d-]+\] (?:Removing|removing|Deleting|Eliminating) .*"),
    "ii_violation": re.compile(r"\[HLS 200-885\] (.*)"),
    "replicate": re.compile(r"\[HLS 200-2167\] Implementing memory '([^']*)' using auto RAMs with (\d+) copies"),
    "storage_inferred": re.compile(r"\[HLS 200-1457\] Automatically inferring inferring (\S+) storage type for array '([^']*)'"),
    "memory_impl": re.compile(r"\[RTMG 210-278\] Implementing memory '([^']*)' using (.*)\."),
    "partition_const_index": re.compile(r"\[HLS 214-449\] Automatically partitioning array '([^']+)' dimension (\d+) completely based on constant index\. \(([^)]+)\)"),
    "partition_small": re.compile(r"\[HLS 214-421\] Automatically partitioning small array '([^']+)' completely based on array size"),
    "pipelining_result": re.compile(r"\[HLS 200-1470\] Pipelining result : Target II = (NA|\d+), Final II = (\d+), Depth = (\d+), loop '([^']+)'"),
    "ii_violation_ports": re.compile(r"\[HLS 200-885\] The II Violation in module '([^']+)' \(loop '([^']+)'\): Unable to schedule '(\w+)' operation (\d+) bit \('([^']+)', ([^)]+)\) on array '([^']+)' due to limited memory ports \(II = (\d+)\)"),
    "auto_inline": re.compile(r"\[HLS 214-364\] Automatically inlining function '([^']+)'|\[XFORM 203-602\] Inlining function '([^']+)' into '([^']+)'"),
    "perfect_nest": re.compile(r"\[HLS 200-2061\] Successfully converted nested loops '([^']+)'\([^)]*\) and '([^']+)'\([^)]*\) in function '([^']+)' into perfectly nested loops"),
    "flatten_disabled": re.compile(r"\[HLS 214-437\] Automatically disabling loop flattening for loop '([^']+)'|\[HLS 200-960\] Cannot flatten loop '([^']+)'"),
    "fifo_impl": re.compile(r"\[RTMG 210-285\] Implementing FIFO '([^']+)'"),
    "error": re.compile(r"^ERROR: (.*)"),
}


def parse_bind_nodes(csynth_xml_path):
    """csynth.xml ModuleInformation/Module/BindNodes: VARIABLE -> RTLNAME/SOURCE/OPTYPE per module
    (bind-stage; the BRAM attribute there is pre-replication, so only use it for names)."""
    out = []
    try:
        root = ET.parse(csynth_xml_path).getroot()
    except Exception:
        return out
    for mod in root.findall("ModuleInformation/Module"):
        mname = (mod.findtext("Name") or "").strip()
        for bn in mod.findall("BindNodes/BindNode"):
            if bn.get("BINDTYPE") != "storage":
                continue
            out.append({"module": mname, "variable": bn.get("VARIABLE"), "rtlname": bn.get("RTLNAME"),
                        "optype": bn.get("OPTYPE"), "impl": bn.get("IMPL"), "source": bn.get("SOURCE"),
                        "storagesize": bn.get("STORAGESIZE"), "bind_bram": bn.get("BRAM")})
    return out


def parse_compile_log(text):
    out = {k: [] for k in LOG_PATTERNS}
    elapsed = None
    for line in text.splitlines():
        for k, rx in LOG_PATTERNS.items():
            m = rx.search(line)
            if m:
                out[k].append(list(m.groups()) if m.groups() else [m.group(0)])
        m = re.search(r"Total elapsed time: (\d+)h (\d+)m (\d+)s", line)
        if m:
            elapsed = int(m.group(1)) * 3600 + int(m.group(2)) * 60 + int(m.group(3))
    out["elapsed_s"] = elapsed
    return out


def parse_work_dir(work_wsl, top):
    """Everything the harness keeps from one Vitis run.  Returns a dict."""
    W = Path(work_wsl)
    rep = W / "hls" / "syn" / "report"
    out = {"ok": False, "modules": {}, "memories": [], "loops": [], "instances": []}
    xml = rep / f"{top}_csynth.xml"
    if not xml.exists():
        xml = rep / "csynth.xml"
    if xml.exists():
        out.update(parse_csynth_xml(xml))
    top_rpt = rep / f"{top}_csynth.rpt"
    if not top_rpt.exists():
        top_rpt = rep / "csynth.rpt"
    if top_rpt.exists():
        txt = top_rpt.read_text(errors="replace")
        out["utilization_summary"] = parse_utilization_summary(txt)
        out["ok"] = True
    for r in sorted(rep.glob("*_csynth.rpt")):
        module = r.name[:-len("_csynth.rpt")]
        txt = r.read_text(errors="replace")
        out["modules"][module] = parse_utilization_summary(txt).get("Total", {})
        out["memories"] += parse_memory_table(txt, module)
        out["loops"] += parse_loop_table(txt, module)
        out["instances"] += parse_instance_table(txt, module)
    log = W / "logs" / "hls_compile.log"
    if log.exists():
        out["log"] = parse_compile_log(log.read_text(errors="replace"))
    cx = rep / "csynth.xml"
    if cx.exists():
        out["bind_nodes"] = parse_bind_nodes(cx)
        # Resolve partition banks and Vitis-created copies to source variables.
        by_rtl = {}
        for b in out["bind_nodes"]:
            by_rtl[(b["module"], b["rtlname"])] = b
        for m in out["memories"]:
            b = by_rtl.get((m.get("module"), m.get("Memory"))) or next(
                (x for x in out["bind_nodes"] if x["rtlname"] == m.get("Memory")), None)
            if b:
                m["variable"] = b["variable"]
                m["source"] = b["source"]
                m["optype"] = b["optype"]
                # Bank instances carry VARIABLE="V_1" (the bank name), so the
                # bind node only helps when the heuristic found no bank.
                if b["variable"] and m.get("bank") is None and b["variable"] != m.get("array"):
                    inst = str(m.get("Memory", ""))[:-2]
                    mb = re.match(r"^" + re.escape(b["variable"]) + r"_(\d+)$", inst)
                    if mb:
                        m["array"], m["bank"] = b["variable"], int(mb.group(1))
                    elif inst == b["variable"]:
                        m["array"] = b["variable"]
    return out


def totals_from(parsed):
    """(BRAM, DSP, FF, LUT, util%) in the spreadsheet's order."""
    res = parsed.get("resources", {})
    util = parsed.get("utilization_summary", {}).get("Utilization (%)", {})
    return {
        "BRAM": res.get("BRAM_18K"), "DSP": res.get("DSP"), "FF": res.get("FF"), "LUT": res.get("LUT"),
        "BRAM_util_pct": util.get("BRAM_18K"), "DSP_util_pct": util.get("DSP"),
        "FF_util_pct": util.get("FF"), "LUT_util_pct": util.get("LUT"),
    }


if __name__ == "__main__":
    import json
    import sys
    print(json.dumps(parse_work_dir(sys.argv[1], sys.argv[2]), indent=1, default=str)[:20000])
