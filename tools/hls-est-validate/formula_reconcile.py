#!/usr/bin/env python3
"""Reconcile the measured BRAM rules (VITIS_NOTES N4 replication, N5 LUTRAM threshold,
N6 aspect modes) with the open-source Vitis HLS resource formula (VITIS_NOTES N8).

Open source read (not copied): hls-llvm-project (https://github.com/Xilinx/hls-llvm-project),
tag 2025.1 = commit 6ad94cf7d252558671697144fcce0415379fe3f8 ("2025.1 release"; the
files below are byte-identical on main ee930469a6e at the time of reading), worktree
~/hls-llvm-project-2025:
  llvm/lib/Support/XilinxPlat/CoreQuerier.cpp  MemoryQuerier::queryBRAM / isSDPMode /
      oldBramImplNum / newBramImplNum / queryLUT / queryFF / queryURAM,
      DoubleKeyMemoryQuerier::queryResource, QuerierFactory::getCoreQuerier
  llvm/lib/Support/XilinxPlat/CoreInst.cpp     StorageInst::setMemUsedPorts / isDRAM /
      isAuto / isBRAM / isURAM, CoreInstFactory::isUltrascale / is7Series
The functions prefixed `open_` are a pseudo-code transcription written from reading that
code; nothing is copied.  Where the measurements and the transcription differ, the
measurements win.

Per memory row (results JSON `memories[]`, plus experiments/*/*/result.json) it evaluates
  pred_n6    the measured model (N4/N5/N6, as in hls-est BRAMAnalysis.cpp):
             0 when impl is auto and Words*Bits < 1024 (or the core is LUTRAM);
             else copies x per-copy, per-copy = min over RAMB18 aspect modes m of
             ceil(W/m) * max(1, P/depth(m)), P = 2^ceil(log2 Words), x36 only with one
             live port (bind optype ram_1p / rom_1p / ram_s2p); RAM_1WNR: x18 per copy,
             copies from `[HLS 200-2167] ... with N copies` (1 for "using auto RAMs").
  pred_open  open_query_bram() with the used-port vector derived from the same inputs
             ("core reading"): ram_1p {RW}, rom_1p {R}, ram_s2p {W,R}, ram_2p {RW,R},
             ram_t2p {RW,RW}, RAM_1WNR {RW}+{R}*copies, multi-port ROM {R}*n
             (n from the literal vector when present, else 2).
  pred_vec   open_query_bram() fed with Vitis's own port vectors: the per-module
             `<MemPortTyVec>` lines of db/*.verbose.bind.rpt (bind_portvec.py; 0 = W,
             1 = R, 2 = RW, 3 = unused) merged slot-wise over the modules that touch the
             array (a slot read in one module and written in another is RW).  Caveat:
             a module's own local arrays have no MemPortTyVec in that module's report,
             so accesses made directly by the owner module are missing (atax buff_x).
and prints how many rows each matches, the N6 misses with a diagnosis category, the
SDP-definition and 1WnR cross-checks, and the legacy-corpus reproduction (the 13391-row
corpus of the CHANGELOG "Vitis storage model" entry, results/baseline/vitis-tdoff.json).

Outputs: --csv (rows of interest: any miss or disagreement), --summary-csv (counts),
--csv-all (optional, every row).

Usage:
  python3 formula_reconcile.py [--vitis results/vitis.json] [--legacy results/baseline/vitis-tdoff.json]
      [--extra other.json ...] [--experiments ~/hls-est-work/experiments]
      [--portvec ~/hls-est-work/exp-notes/bind_portvec.json] [--csv ...] [--summary-csv ...]
      [--csv-all ...] [--list-misses N] [--self-check]
"""
import argparse
import csv
import glob
import json
import os
from collections import Counter, OrderedDict

HERE = os.path.dirname(os.path.abspath(__file__))

# --------------------------------------------------------------------------------------
# Measured model (VITIS_NOTES N4 / N5 / N6; hls-est BRAMAnalysis.cpp estimateBlocks)
# --------------------------------------------------------------------------------------
ASPECT_MODES = ((1, 16384), (2, 8192), (4, 4096), (9, 2048), (18, 1024), (36, 512))
LUTRAM_BITS = 1024  # N5: Words*Bits < 1024 and impl auto -> distributed RAM, 0 BRAM_18K
WIDE_OPTYPES = {"ram_1p": True, "rom_1p": True, "ram_s2p": True, "ram_2p": False, "ram_t2p": False, "rom_2p": False, "rom_np": False}


def pow2_ceil(n):
    p = 1
    while p < n:
        p *= 2
    return p


def cdiv(a, b):
    return -(-a // b)


def n6_per_copy(width, depth, wide):
    """N6 R1/R2: cheapest RAMB18 aspect mode, address space rounded up to a power of two."""
    if width <= 0 or depth <= 0:
        return 0
    P = pow2_ceil(depth)
    best = None
    for m, d in ASPECT_MODES:
        if m == 36 and not wide:
            continue
        blocks = cdiv(width, m) * max(1, P // d)
        best = blocks if best is None else min(best, blocks)
    return best


# --------------------------------------------------------------------------------------
# Open-source formula: transcription of MemoryQuerier::queryBRAM for a 7-series part
# --------------------------------------------------------------------------------------
W_ONLY, R_ONLY, RW, UNUSED = 0, 1, 2, 3  # MemoryQuerier::PORT_TYPE (0..2); 3 = "> READ_WRITE"


def open_used_ports(vec):
    """StorageInst::setMemUsedPorts: the stored vector keeps only entries <= READ_WRITE."""
    return [p for p in vec if p <= RW]


def open_is_sdp(used, core_name=""):
    """MemoryQuerier::isSDPMode on the already-filtered vector.  Its "any entry > READ_WRITE
    -> SDP" branch can never fire because setMemUsedPorts removed those entries, so:
    SDP iff exactly one used port, or the vector is exactly {R,W}, {W,R} or {R,R}.
    (The RAM_coregen core is excluded from the two-entry rule.)"""
    if len(used) == 1:
        return True
    if len(used) > 1 and core_name != "RAM_coregen":
        return used in ([R_ONLY, W_ONLY], [W_ONLY, R_ONLY], [R_ONLY, R_ONLY])
    return False


def open_old_bram_impl_num(width, depth, sdp, family="zynq"):
    """MemoryQuerier::oldBramImplNum: RAMB18 count of one W x D memory by depth band.
    Zynq-7000 is neither virtex4/virtex5/spartan nor UltraScale."""
    if depth > 8192:  # 16k x 1 columns; the 16k-block count is rounded up to a power of 2
        return pow2_ceil(cdiv(depth, 16384)) * width
    if depth > 4096:  # 8k x 2
        return cdiv(width, 2)
    if depth > 2048:  # 4k x 4, or two 2k x 9 stacked (not on virtex4/spartan)
        n = cdiv(width, 4)
        if family not in ("virtex4", "spartan"):
            n = min(n, 2 * cdiv(width, 9))
        return n
    if depth > 1024:  # 2k x 9
        return cdiv(width, 9)
    if depth > 512:  # 1k x 18
        return cdiv(width, 18)
    if sdp and family != "virtex5":  # 512 x 36 only in simple-dual-port mode
        return cdiv(width, 36)
    return cdiv(width, 18)


def open_new_bram_impl_num(width, depth, sdp):
    """MemoryQuerier::newBramImplNum (UltraScale only; never used for Zynq-7000): greedy
    RAMB36 cascades of width 72 (SDP only, 512 deep) / 36 / 18 / 9 / 4 / 2 / 1, each
    cascade ceil(D / depth(width)) blocks, total doubled to RAMB18."""
    pairs = [(512, 72)] if sdp else []
    pairs += [(1024, 36), (2048, 18), (4096, 9), (8192, 4), (16384, 2), (32768, 1)]
    total, remain = 0, width
    for d, w in pairs:
        k = remain // w
        remain -= k * w
        total += k * cdiv(depth, d)
    return total * 2


def open_query_bram(width, depth, vec, impl="auto", core_name="", family="zynq"):
    """MemoryQuerier::queryBRAM.  `vec` = port vector as the binder sets it (unused slots
    allowed; they are dropped as setMemUsedPorts does).  impl in auto|bram|lutram|uram.
    Returns (bram, info)."""
    is_dram = impl == "lutram" or (width * depth < LUTRAM_BITS and impl == "auto")
    if impl == "uram" or is_dram:
        return 0, {"dram": is_dram, "uram": impl == "uram", "sdp": "", "n": "", "mult": 0, "per_copy": 0}
    used = open_used_ports(vec)
    sdp = open_is_sdp(used, core_name)
    n = len(used)
    is_rom = all(p == R_ONLY for p in used)  # vacuously true for n == 0
    eff = n
    if n > 2 and not is_rom:  # 1WnR: each port beyond two costs a whole extra RAM
        sdp = False
        eff = 2 * n - 2
    elif n > 2 and is_rom:  # n-port ROM: one dual-port ROM per two read ports
        sdp = False
    per = open_old_bram_impl_num(width, depth, sdp, family)
    if family in ("kintexu", "virtexu", "zynqu"):
        per = min(per, open_new_bram_impl_num(width, depth, sdp))
    mult = (eff + 1) // 2 if eff > 0 else 1  # a FIFO has no used ports -> no multiplier
    return per * mult, {"dram": False, "uram": False, "sdp": int(sdp), "n": n, "rom": is_rom, "mult": mult, "per_copy": per}


# --------------------------------------------------------------------------------------
# Row model
# --------------------------------------------------------------------------------------
def toint(x, default=None):
    try:
        return int(x)
    except (TypeError, ValueError):
        return default


def impl_of(core, bind_impl):
    """Storage implementation from the core / RTL module name and the bind node IMPL."""
    c = (core or "").upper()
    if "LUTRAM" in c or "DISTRIBUTE" in c:
        return "lutram"
    if "URAM" in c:
        return "uram"
    if "_BRAM" in c:
        return "bram"
    if "AUTO" in c:
        return "auto"
    bi = (bind_impl or "").lower()
    if bi in ("auto", "bram", "lutram", "uram"):
        return bi
    return "auto"


def core_reading(optype, is_1wnr, copies, n_vec):
    """Used-port vector from the storage type the bind chose (same inputs as N6)."""
    if is_1wnr:
        return [RW] + [R_ONLY] * max(1, copies or 1)
    return {"ram_1p": [RW], "rom_1p": [R_ONLY], "ram_s2p": [W_ONLY, R_ONLY], "ram_2p": [RW, R_ONLY],
            "ram_t2p": [RW, RW], "rom_2p": [R_ONLY, R_ONLY]}.get(optype) or ([R_ONLY] * max(2, n_vec or 2) if optype == "rom_np" else None)


def merge_vectors(vecs):
    """Slot-wise union of per-module MemPortTyVec strings."""
    slots = []
    for _module, s in vecs:
        try:
            toks = [int(t) for t in s.split()]
        except ValueError:
            continue
        for i, t in enumerate(toks):
            while len(slots) <= i:
                slots.append(set())
            slots[i] |= {W_ONLY: {"W"}, R_ONLY: {"R"}, RW: {"R", "W"}}.get(t, set())
    return [RW if s == {"R", "W"} else R_ONLY if s == {"R"} else W_ONLY if s == {"W"} else UNUSED for s in slots]


def related_vectors(vecs, owner):
    """Vectors of the modules that belong to the owner (the owner itself and its
    `<owner>_...` sub-modules, `_s` template suffix dropped); all vectors if none."""
    base = owner[:-2] if owner.endswith("_s") else owner
    rel = [(m, v) for m, v in vecs if m == owner or m.startswith(base + "_")]
    return (rel, "owner") if rel else (list(vecs), "all-modules")


def load_runs(path, experiments=False):
    d = json.load(open(path))
    if experiments:
        return [(os.path.basename(os.path.dirname(os.path.dirname(path))), d, os.path.dirname(path))]
    return [(k, v, v.get("cache_dir") or "") for k, v in d.items() if isinstance(v, dict)]


def rows_of(label, runs):
    for key, v, run_dir in runs:
        mems = v.get("memories") or []
        if not mems:
            continue
        log = v.get("log") or {}
        rep = [(r[0], toint(r[1], 1)) for r in (log.get("replicate") or []) if len(r) >= 2]
        auto_1wnr = {r[0] for r in (log.get("memory_impl") or []) if r and "1WNR" in r[0].upper()}
        bind = {}
        for b in v.get("bind_nodes") or []:
            bind.setdefault((b.get("module"), b.get("rtlname")), b)
            bind.setdefault((None, b.get("rtlname")), b)
        sib = {}
        for m in mems:
            if m.get("optype"):
                sib.setdefault((m.get("module"), m.get("Module")), m["optype"])
        dataset, bench = key.split("/", 1) if "/" in key else ("experiment", key)
        for m in mems:
            core = m.get("core") or ""
            rtl_mod = m.get("Module") or ""
            owner = m.get("module") or ""
            is_1wnr = "1WNR" in core.upper() or "1WNR" in rtl_mod.upper()
            copies, copies_src = 1, ""
            if is_1wnr:
                full = owner + "_" + rtl_mod
                hit = [c for n, c in rep if n.endswith(full)] or [c for n, c in rep if n.endswith("_" + rtl_mod) or n == rtl_mod]
                if hit:
                    copies, copies_src = hit[0], "replicate msg"
                elif any(n.endswith(rtl_mod) for n in auto_1wnr):
                    copies, copies_src = 1, "auto RAMs msg"
                else:
                    copies, copies_src = 1, "none (default 1)"
            b = bind.get((owner, m.get("Memory"))) or bind.get((None, m.get("Memory")))
            optype = m.get("optype") or sib.get((owner, rtl_mod)) or ""
            yield OrderedDict(
                source=label, design=key, dataset=dataset, benchmark=bench, run_dir=run_dir,
                memory=m.get("Memory") or "", module=owner, rtl_module=rtl_mod, array=m.get("array") or "",
                words=toint(m.get("Words")), bits=toint(m.get("Bits")), bram=toint(m.get("BRAM_18K")),
                lut=toint(m.get("LUT")), ff=toint(m.get("FF")),
                core=core, optype=optype, optype_src="row" if m.get("optype") else ("sibling bank" if optype else "none"),
                impl=impl_of(core or rtl_mod, b.get("impl") if b else None), is_1wnr=int(is_1wnr),
                copies=copies, copies_src=copies_src)


def evaluate(r, portvec, legacy_wide_default=False):
    W, D, bram = r["bits"], r["words"], r["bram"]
    blank = ("wide_n6", "pred_n6", "match_n6", "ports_open", "sdp_open", "mult_open", "pred_open", "match_open",
             "vec_scope", "vec_modules", "vec_merged", "sdp_vec", "nports_vec", "mult_vec", "pred_vec", "match_vec")
    for k in blank:
        r[k] = ""
    if W is None or D is None or bram is None:
        r["category"] = "unparsed row"
        return
    # --- literal port vector ---
    vecs = (portvec.get(r["run_dir"]) or {})
    name = r["memory"][:-2] if r["memory"].endswith("_U") else r["memory"]
    # Vitis renames C/RTL reserved words (buf -> buf_r, in -> in_r) in the bind reports
    cand = vecs.get(name) or vecs.get(name + "_r") or []
    vec = None
    if cand:
        rel, scope = related_vectors(cand, r["module"])
        vec = merge_vectors(rel)
        r["vec_scope"], r["vec_modules"], r["vec_merged"] = scope, len(rel), " ".join(map(str, vec))
    n_vec = len(open_used_ports(vec)) if vec else None
    # --- measured model ---
    wide = WIDE_OPTYPES.get(r["optype"])
    if r["is_1wnr"]:
        wide = False
    if wide is None and legacy_wide_default:
        wide = True  # the legacy corpus check: no bind optype -> x36 allowed
    lut = (r["impl"] == "auto" and W * D < LUTRAM_BITS) or r["impl"] == "lutram"
    if lut:
        pred_n6, alt_n6 = 0, 0
    elif wide is None:
        pred_n6, alt_n6 = None, None
    else:
        k = r["copies"] if r["is_1wnr"] else 1
        pred_n6, alt_n6 = k * n6_per_copy(W, D, wide), k * n6_per_copy(W, D, not wide)
    r["wide_n6"] = "" if wide is None else int(wide)
    r["pred_n6"] = "" if pred_n6 is None else pred_n6
    r["match_n6"] = "" if pred_n6 is None else int(pred_n6 == bram)
    impl = r["impl"] if r["impl"] in ("auto", "bram", "lutram", "uram") else "auto"
    # --- open formula, core reading ---
    ports = core_reading(r["optype"], r["is_1wnr"], r["copies"], n_vec)
    if ports is None and (legacy_wide_default or lut):
        ports = [RW]  # legacy check: x36 assumed; DRAM: the port vector does not matter
    if ports is not None:
        p, info = open_query_bram(W, D, ports, impl)
        r["ports_open"] = " ".join("WR2"[x] for x in ports).replace("2", "RW")
        r["sdp_open"], r["mult_open"], r["pred_open"], r["match_open"] = info["sdp"], info["mult"], p, int(p == bram)
    # --- open formula, Vitis port vectors ---
    if vec:
        p, info = open_query_bram(W, D, vec, impl)
        r["sdp_vec"], r["nports_vec"], r["mult_vec"], r["pred_vec"], r["match_vec"] = info["sdp"], info["n"], info["mult"], p, int(p == bram)
    r["category"] = "" if r["match_n6"] == 1 else diagnose(r, alt_n6)


def diagnose(r, alt_n6):
    W, D, bram = r["bits"], r["words"], r["bram"]
    core = r["core"].upper()
    if r["match_n6"] == "":
        return "port mode unknown (no bind optype)"
    if r["is_1wnr"]:
        if r["pred_vec"] != "" and r["pred_vec"] == bram:
            return "1WnR copies: message %s gives %s copies, port vector n-1 = %s matches" % (r["copies_src"], r["copies"], r["mult_vec"])
        return "1WnR copies (%s)" % r["copies_src"]
    if r["optype"] == "rom_np":
        return "multi-port ROM (N6 has no rule; open: ceil(n/2) dual-port ROMs, x18)"
    if bram == 0 and W * D >= LUTRAM_BITS and r["impl"] == "auto":
        return "0 BRAM reported for a >= 1024-bit auto memory"
    if W * D < LUTRAM_BITS and r["impl"] == "auto":
        return "LUTRAM edge (< 1024 bits but BRAM)"
    if alt_n6 == bram and r["pred_vec"] == bram:
        return "x36/x18: bound %s (impl %s) but the used-port vector [%s] is SDP=%s; open formula on the vector right" % (
            r["optype"] or "<no optype>", r["impl"], r["vec_merged"], r["sdp_vec"])
    if alt_n6 == bram and r["pred_open"] == bram:
        return "x36/x18: bound %s; open SDP rule on its port vector [%s] right" % (r["optype"], r["ports_open"])
    if alt_n6 == bram:
        return "x36/x18: the other port mode matches (optype %s, impl %s, no vector)" % (r["optype"], r["impl"])
    if D > 4096 and (r["pred_open"] == bram or r["pred_vec"] == bram):
        return "deep band (> 4096 words): open x2/x1 columns right, N6 x9 stacking wrong"
    if r["pred_open"] == bram or r["pred_vec"] == bram:
        return "open formula matches, N6 does not"
    if r["impl"] not in ("auto",):
        return "explicit impl %s" % r["impl"]
    return "unexplained"


def summarize(sel, title, out):
    n = len(sel)
    if not n:
        return
    def cnt(f):
        return sum(1 for r in sel if f(r))
    a = cnt(lambda r: r["match_n6"] == 1)
    b = cnt(lambda r: r["match_open"] == 1)
    both = cnt(lambda r: r["match_n6"] == 1 and r["match_open"] == 1)
    neither = cnt(lambda r: r["match_n6"] != 1 and r["match_open"] != 1)
    vec_rows = [r for r in sel if r["match_vec"] != ""]
    vm = sum(1 for r in vec_rows if r["match_vec"] == 1)
    print("%-62s rows %6d | N6 %6d | open %6d | both %6d | N6 only %4d | open only %4d | neither %4d | open(Vitis vectors) %d/%d"
          % (title, n, a, b, both, a - both, b - both, neither, vm, len(vec_rows)))
    out.append(OrderedDict(subset=title, rows=n, n6=a, open=b, both=both, n6_only=a - both, open_only=b - both, neither=neither,
                           vec_rows=len(vec_rows), vec_match=vm))


def subsets(sel):
    yield "all rows", sel
    yield "plain (non-1WNR, >= 1024 bits)", [r for r in sel if not r["is_1wnr"] and (r["words"] or 0) * (r["bits"] or 0) >= LUTRAM_BITS]
    yield "RAM_1WNR", [r for r in sel if r["is_1wnr"]]
    yield "< 1024 bits", [r for r in sel if (r["words"] or 0) * (r["bits"] or 0) < LUTRAM_BITS]


def self_check():
    diffs = 0
    depths = sorted(set(list(range(1, 2100)) + [2500, 3000, 4095, 4096, 4097, 5000, 8191, 8192, 8193, 12000, 16383, 16384,
                                                 16385, 20000, 32768, 32769, 40200, 50176, 65537, 73200, 100000, 192000]))
    pts = 0
    for w in range(1, 300):
        for dpt in depths:
            for wide in (True, False):
                pts += 1
                if n6_per_copy(w, dpt, wide) != open_old_bram_impl_num(w, dpt, wide):
                    diffs += 1
                    if diffs <= 10:
                        print("DIFF W=%d D=%d sdp=%s n6=%d open=%d" % (w, dpt, wide, n6_per_copy(w, dpt, wide), open_old_bram_impl_num(w, dpt, wide)))
    print("self-check: %d of %d (W in 1..299, D, mode) points differ between N6 per-copy and oldBramImplNum" % (diffs, pts))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--vitis", default=os.path.join(HERE, "results", "vitis.json"))
    ap.add_argument("--legacy", default=os.path.join(HERE, "results", "baseline", "vitis-tdoff.json"),
                    help="the corpus of the CHANGELOG 'Vitis storage model' check ('' to skip)")
    ap.add_argument("--extra", action="append", default=[], help="another results JSON (e.g. results/vitis-tdauto.json)")
    ap.add_argument("--experiments", default=os.path.expanduser("~/hls-est-work/experiments"))
    ap.add_argument("--portvec", default=os.path.expanduser("~/hls-est-work/exp-notes/bind_portvec_n8.json"),
                    help="bind_portvec.py output (N8 used bind_portvec.json + `--update` with the fr_* kernels)")
    ap.add_argument("--csv", default=os.path.join(HERE, "results", "formula_reconcile.csv"))
    ap.add_argument("--summary-csv", default=os.path.join(HERE, "results", "formula_reconcile_summary.csv"))
    ap.add_argument("--csv-all", default="", help="also write every row here")
    ap.add_argument("--list-misses", type=int, default=150)
    ap.add_argument("--self-check", action="store_true")
    args = ap.parse_args()

    if args.self_check:
        self_check()
    portvec = json.load(open(args.portvec)) if args.portvec and os.path.exists(args.portvec) else {}
    print("port vectors: %d run dirs (%s)" % (len(portvec), args.portvec or "-"))

    groups = [(os.path.basename(args.vitis), load_runs(args.vitis), False)]
    for p in args.extra:
        groups.append((os.path.basename(p), load_runs(p), False))
    if args.experiments:
        runs = []
        for rj in sorted(glob.glob(os.path.join(args.experiments, "*", "*", "result.json"))):
            try:
                runs += load_runs(rj, experiments=True)
            except (OSError, ValueError):
                pass
        groups.append(("experiments", runs, False))
    if args.legacy and os.path.exists(args.legacy):
        groups.append(("legacy:" + os.path.basename(args.legacy), load_runs(args.legacy), True))

    rows, summary = [], []
    for label, runs, legacy in groups:
        sel = list(rows_of(label, runs))
        for r in sel:
            evaluate(r, portvec, legacy_wide_default=legacy)
        rows += sel
        print()
        for name, s in subsets(sel):
            summarize(s, "[%s] %s" % (label, name), summary)
        cats = Counter(r["category"] for r in sel if r["category"])
        if cats:
            print("  N6 misses by category:")
            for c, n in sorted(cats.items(), key=lambda kv: -kv[1]):
                print("    %5d  %s" % (n, c))

    # ---- N6 misses ----
    for label, _runs, legacy in groups:
        missed = [r for r in rows if r["source"] == label and r["category"]]
        if not missed:
            continue
        print("\n=== N6 misses [%s]: %d ===" % (label, len(missed)))
        print("design | memory | WordsxBits | core | optype | impl | copies | Vitis | N6 | open | vec -> open(vec) | category")
        for r in missed[: args.list_misses]:
            print("%s | %s | %sx%s | %s | %s | %s | %s | %s | %s | %s | [%s] -> %s | %s" % (
                r["design"], r["memory"], r["words"], r["bits"], r["core"], r["optype"] or "-", r["impl"],
                r["copies"] if r["is_1wnr"] else "", r["bram"], r["pred_n6"], r["pred_open"], r["vec_merged"], r["pred_vec"], r["category"]))
        if len(missed) > args.list_misses:
            print("... %d more (CSV)" % (len(missed) - args.list_misses))

    # ---- legacy corpus: reproduce the CHANGELOG "Vitis storage model" check exactly ----
    # corpus = non-1WNR rows with Words*Bits >= 1024; rule = n6_per_copy(W, D, wide) with
    # wide from the row's own bind optype or True when absent; no impl / LUTRAM handling.
    leg = [r for r in rows if r["source"].startswith("legacy:") and r["words"] is not None and r["bits"] is not None
           and not r["is_1wnr"] and r["words"] * r["bits"] >= LUTRAM_BITS]
    if leg:
        cur = {(r["design"], r["memory"], r["rtl_module"]): r for r in rows if r["source"] == groups[0][0]}
        miss = []
        for r in leg:
            wide = WIDE_OPTYPES.get(r["optype"], True) if r["optype_src"] == "row" else True
            r["legacy_pred"] = n6_per_copy(r["bits"], r["words"], wide)
            if r["legacy_pred"] == r["bram"]:
                continue
            now = cur.get((r["design"], r["memory"], r["rtl_module"]))
            if r["impl"] == "lutram":
                k = "explicit LUTRAM core (%s): 0 BRAM; the legacy check had no impl rule" % r["core"]
            elif now is None:
                k = "not in current results"
            elif now["bram"] != r["bram"]:
                k = "Vitis number differs in current results"
            elif now["optype"] == "rom_np":
                k = "multi-port ROM (current bind: rom_np, vector [%s]); open ceil(n/2) right" % now["vec_merged"]
            elif now["match_n6"] == 1 and not now["wide_n6"]:
                k = "x18: current bind optype %s (two live ports); legacy file had no optype, x36 assumed" % now["optype"]
            elif now["match_n6"] == 1:
                k = "N6 exact on current results"
            else:
                k = "still missed: " + now["category"]
            r["legacy_note"] = k
            miss.append(r)
        print("\n=== legacy corpus check reproduced [%s]: %d rows, legacy rule exact %d, missed %d ===" % (
            leg[0]["source"], len(leg), len(leg) - len(miss), len(miss)))
        c = Counter(r["legacy_note"] for r in miss)
        for k, n in c.most_common():
            print("  %5d  %s" % (n, k))
        g = Counter((r["legacy_note"].split(":")[0].split(" (")[0], r["design"], "%sx%s" % (r["words"], r["bits"]), r["core"], r["bram"],
                     r["legacy_pred"], cur.get((r["design"], r["memory"], r["rtl_module"]), {}).get("pred_n6", ""),
                     cur.get((r["design"], r["memory"], r["rtl_module"]), {}).get("pred_open", "")) for r in miss)
        print("  rows grouped: n | category | design | WordsxBits | core | Vitis | legacy N6 | N6 (current optype) | open")
        for k, n in sorted(g.items(), key=lambda kv: (kv[0][0], kv[0][1], kv[0][2])):
            print("  %3d | %s | %s | %s | %s | %s | %s | %s | %s" % ((n,) + k))

    # ---- SDP definition cross-check (Vitis vectors vs N6 one-live-port rule) ----
    main_rows = [r for r in rows if not r["source"].startswith("legacy:")]
    chk = [r for r in main_rows if r["sdp_vec"] != "" and r["wide_n6"] != "" and not r["is_1wnr"]
           and r["impl"] == "auto" and r["words"] * r["bits"] >= LUTRAM_BITS and r["words"] <= 512]
    print("\n=== SDP (open, Vitis vector) vs x36 allowed (N6, optype): non-1WNR auto rows, >= 1024 bits, depth <= 512 (the only band where it matters): %d ===" % len(chk))
    c = Counter((r["optype"], r["vec_merged"] if len(r["vec_merged"]) <= 12 else r["vec_merged"][:12] + "..", int(r["sdp_vec"]), int(r["wide_n6"]),
                 "N6 ok" if r["match_n6"] == 1 else "N6 miss", "vec ok" if r["match_vec"] == 1 else "vec miss") for r in chk)
    print("  count  optype   merged-vec      SDP(vec) wide(N6)  N6    open(vec)")
    for k, n in c.most_common(40):
        print("  %5d  %-8s [%-13s] %d        %d        %-7s %s" % (n, k[0], k[1], k[2], k[3], k[4], k[5]))
    agree = sum(1 for r in chk if int(r["sdp_vec"]) == int(r["wide_n6"]))
    print("  SDP(vec) == wide(N6): %d / %d; where they differ, N6 right %d, open(vec) right %d, the count does not depend on it %d" % (
        agree, len(chk), sum(1 for r in chk if int(r["sdp_vec"]) != int(r["wide_n6"]) and r["match_n6"] == 1 and r["match_vec"] != 1),
        sum(1 for r in chk if int(r["sdp_vec"]) != int(r["wide_n6"]) and r["match_vec"] == 1 and r["match_n6"] != 1),
        sum(1 for r in chk if int(r["sdp_vec"]) != int(r["wide_n6"]) and r["match_vec"] == 1 and r["match_n6"] == 1)))

    # ---- 1WnR cross-check: copies (replicate message) vs n_ports - 1 (open) ----
    w = [r for r in main_rows if r["is_1wnr"]]
    print("\n=== RAM_1WNR rows: %d; copies (message) vs open multiplier n-1 from the Vitis vector ===" % len(w))
    c = Counter((r["copies_src"], r["copies"], r["nports_vec"], r["mult_vec"], "Vitis=%s" % r["bram"], "N6 ok" if r["match_n6"] == 1 else "N6 miss",
                 "vec ok" if r["match_vec"] == 1 else ("vec miss" if r["match_vec"] == 0 else "no vec")) for r in w)
    for k, n in sorted(c.items(), key=lambda kv: (-kv[1], str(kv[0])))[:40]:
        print("  %4d  copies=%s (%s)  n_ports(vec)=%s -> mult %s  %s  %s  %s" % (n, k[1], k[0], k[2], k[3], k[4], k[5], k[6]))
    print("  copies == n_ports(vec) - 1: %d / %d rows with a vector" % (
        sum(1 for r in w if r["nports_vec"] != "" and r["copies"] == r["nports_vec"] - 1), sum(1 for r in w if r["nports_vec"] != "")))

    # ---- LUTRAM resources (MemoryQuerier::queryLUT / queryFF for a DRAM storage) ----
    lut_rows = [r for r in main_rows if r["words"] is not None and r["bits"] is not None and r["bram"] == 0
                and r["impl"] in ("auto", "lutram") and r["words"] * r["bits"] < LUTRAM_BITS and r.get("lut") is not None]
    if lut_rows:
        ok_lut = sum(1 for r in lut_rows if r["lut"] == cdiv(r["words"] * r["bits"], 64))
        nport = lambda r: r["nports_vec"] if r["nports_vec"] not in ("", None, 0) else {"ram_1p": 1, "rom_1p": 1}.get(r["optype"], 2)
        ok_ff = sum(1 for r in lut_rows if r["ff"] == r["bits"] * nport(r))
        ok_ff1 = sum(1 for r in lut_rows if r["ff"] == r["bits"])
        print("\n=== LUTRAM rows (< 1024 bits, 0 BRAM): %d; LUT == ceil(W*D/64): %d; FF == W x used ports: %d; FF == W: %d ===" % (
            len(lut_rows), ok_lut, ok_ff, ok_ff1))

    # ---- multi-port ROM rows ----
    rom = [r for r in main_rows if r["optype"] == "rom_np" and not r["is_1wnr"]]
    if rom:
        print("\n=== multi-port ROM rows (optype rom_np, not 1WNR): %d ===" % len(rom))
        for r in rom[:20]:
            print("  %s %s %sx%s Vitis %s | N6 %s | open %s | vec [%s] -> %s" % (r["design"], r["memory"], r["words"], r["bits"], r["bram"],
                                                                             r["pred_n6"], r["pred_open"], r["vec_merged"], r["pred_vec"]))

    # ---- CSV ----
    cols = ["source", "design", "dataset", "benchmark", "memory", "module", "rtl_module", "array", "words", "bits", "bram", "core",
            "optype", "optype_src", "impl", "is_1wnr", "copies", "copies_src", "wide_n6", "pred_n6", "match_n6", "ports_open",
            "sdp_open", "mult_open", "pred_open", "match_open", "vec_scope", "vec_modules", "vec_merged", "sdp_vec", "nports_vec",
            "mult_vec", "pred_vec", "match_vec", "category", "legacy_pred", "legacy_note"]

    def write(path, sel):
        os.makedirs(os.path.dirname(os.path.abspath(path)), exist_ok=True)
        with open(path, "w", newline="") as f:
            wtr = csv.writer(f)
            wtr.writerow(cols)
            for r in sel:
                wtr.writerow(["" if r.get(c) is None else r.get(c, "") for c in cols])
        print("wrote %s (%d rows)" % (path, len(sel)))

    interesting = [r for r in rows if r["match_n6"] != 1 or r["match_open"] != 1 or r["match_vec"] == 0 or r.get("legacy_note")]
    print()
    write(args.csv, interesting)
    if args.csv_all:
        write(args.csv_all, rows)
    if args.summary_csv:
        with open(args.summary_csv, "w", newline="") as f:
            wtr = csv.DictWriter(f, fieldnames=list(summary[0].keys()))
            wtr.writeheader()
            wtr.writerows(summary)
        print("wrote %s (%d rows)" % (args.summary_csv, len(summary)))


if __name__ == "__main__":
    main()
