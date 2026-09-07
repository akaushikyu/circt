#!/usr/bin/env python3
"""Join Vitis ground truth with hls-est predictions and diff totals and arrays.

    python3 compare.py [--vitis results/vitis.json] [--hlsest results/hlsest.json]
                       [--out results/compare.json] [--csv results/compare.csv] [--quiet]

Per design the comparison records:
  vitis_bram, hlsest_bram, diff (= hlsest - vitis), exact (bool), status (which side failed)
  arrays: one row per C array name, with the Vitis BRAM (summed over partition
          banks and modules), the hls-est BRAM (summed over banks of the same
          variable), the diff, Vitis words/bits/banks/core and the hls-est RAM type.
A design whose hls-est record carries its Vitis cache keys (run_hlsest.py `vitis_keys`) is compared
only with a ground-truth entry whose `key` is one of them; any other entry was synthesised from other
sources (another catalogue's record under the same dataset/benchmark key, or an edited design) and the
row gets status "sources differ".  Older result files without the keys are compared as before.
Array names: Vitis reports `<name>_U` instances per module (partition banks are
`<name>_<k>_U`); hls-est's debug JSON (--bram-debug-json) carries the
`polygeist.varname` / global symbol of each memref.  Without the debug JSON only
totals are compared.  A Vitis row is grouped by its own variable when the hls-est
names are known (see `vitis_array_name`), so that two real arrays `FM_buffer_1` /
`FM_buffer_2` are not folded into a fake `FM_buffer`.
"""
import argparse
import csv
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C  # noqa: E402

def math_core_index(path=None):
    """The Vitis modules of the hls:: math cores and the ROM tables of the inlined CORDIC entries,
    from the cost table (math_costs.json): {"modules": set, "tables": set};
    empty sets when the file cannot be read."""
    p = Path(path) if path else Path(__file__).resolve().parent / "math_costs.json"
    mods, tabs = set(), set()
    try:
        doc = json.loads(p.read_text())
    except (OSError, ValueError):
        return {"modules": mods, "tables": tabs}
    for e in doc.get("entries", []):
        core = e.get("core")
        if isinstance(core, list):
            mods.update(c for c in core if c)
        elif e.get("core_kind") == "inline_cordic":
            tabs.update(t["name"] for t in e.get("tables", []) if t.get("name"))
    return {"modules": mods, "tables": tabs}


MATH_CORES = math_core_index()

# Partition-bank (`_1`, `_0_7`) and inline (`.i`, `.i2`) suffixes, as in align_arrays.py.
BANK_TAIL_RE = re.compile(r"^(?:\.i\d*|[._]\d+)+$")


def known_root(name, known):
    """Longest name in `known` that `name` extends by bank / inline suffixes only, else None
    (align_arrays.known_root)."""
    best = None
    for k in known:
        if len(k) < len(name) and name.startswith(k) and BANK_TAIL_RE.match(name[len(k):]):
            if best is None or len(k) > len(best):
                best = k
    return best


def vitis_array_name(m, known=None):
    """Group name of one `* Memory:` row.  With the hls-est array names (`known`) the row's own
    variable (csynth.xml BindNode VARIABLE, else the instance without `_U`) decides: a known name
    stays itself (`FM_buffer_1`), a name that extends a known one by bank indices is folded into
    it (`localW_12` -> localW, `BRAM_1_0_7` -> BRAM_1), anything else keeps vitis_parse's bank
    grouping (`array`).  Without `known`, vitis_parse's grouping alone, which folds two real
    arrays `FM_buffer_1` / `FM_buffer_2` into a fake `FM_buffer` (align_arrays.py's T1 fix,
    ported here; totals are unaffected, only the per-array rows)."""
    if known:
        var = m.get("variable") or re.sub(r"_U(_x)?$", "", str(m.get("Memory") or ""))
        if var in known:
            return var
        root = known_root(var, known)
        if root is not None:
            return root
        # An array of an inlined callee: Vitis writes the inline suffixes `.i` as `_i`
        # (`current_node_embedding_in_i_i_i`, gnnbuilder gcn_qm9).
        stripped = re.sub(r"(?:_i\d*)+$", "", var)
        if stripped != var and stripped in known:
            return stripped
    return m.get("array") or m.get("Memory")


def module_multiplicity(v):
    """How many times each Vitis module is instantiated in the design: the sum over its instance
    rows of its parent's multiplicity (the top and any module without an instance row: 1). The
    memory table lists each memory once per module, not per instance: neuro_monarchs' 8
    `org_mult_HLS` instances x 31 BRAM are 248 in the total (W9r7 review defect 11)."""
    parents = {}
    for inst in v.get("instances", []):
        mod, par = inst.get("Module"), inst.get("parent")
        if mod and par:
            parents.setdefault(mod, []).append(par)
    memo = {}

    def mult(mod, depth=0):
        if mod in memo:
            return memo[mod]
        if mod not in parents or depth > 64:
            return 1
        memo[mod] = 1                    # cycle guard
        memo[mod] = sum(mult(p, depth + 1) for p in parents[mod])
        return memo[mod]
    return {mod: mult(mod) for mod in parents}


def vitis_arrays(v, known=None):
    """Aggregate the Vitis per-memory rows by C array name (banks and module copies summed;
    `known` = the hls-est array names, see `vitis_array_name`).
    m_axi/s_axi adapters and ROM tables of library functions are kept but flagged.
    hls:: math cores (MATH_CORES, from math_costs.json): an instance row of a core module (not
    nested in another core) is listed as `math_core:<module>` with the instance BRAM, the memory
    rows inside core modules are left out (their BRAM is the instance's), and an inlined CORDIC
    table row is `math_core:<table>`: the names hls-est's math_core records carry
    (--bram-analysis math-costs=)."""
    out = {}
    copies = module_multiplicity(v)
    for m in v.get("memories", []):
        if m.get("module") in MATH_CORES["modules"]:
            continue
        name = vitis_array_name(m, known)
        if m.get("array") in MATH_CORES["tables"]:
            name = "math_core:" + m["array"]
        a = out.setdefault(name, {"name": name, "vitis_bram": 0, "banks": 0, "rows": 0,
                                  "words": 0, "bits": m.get("Bits"), "cores": set(), "modules": set()})
        # once per instance of the memory's module (module_multiplicity)
        a["vitis_bram"] += (m.get("bram") or 0) * copies.get(m.get("module"), 1)
        a["banks"] += 1
        a["rows"] += 1
        a["words"] += m.get("Words") or 0
        if m.get("core"):
            a["cores"].add(m["core"])
        a["modules"].add(m.get("module", ""))
    # m_axi adapters: instance rows `<bundle>_m_axi_U` (module `<bundle>_m_axi`). They are not
    # memories, but `--bram-maxi-adapters` reports each bundle as a pseudo-memref with varname
    # `<bundle>_m_axi`, so list them under that name for the per-array diff (totals unchanged).
    for inst in v.get("instances", []):
        mod = inst.get("Module") or ""
        if not mod.endswith("_m_axi"):
            continue
        a = out.setdefault(mod, {"name": mod, "vitis_bram": 0, "banks": 0, "rows": 0,
                                 "words": 0, "bits": None, "cores": set(), "modules": set()})
        a["vitis_bram"] += inst.get("BRAM_18K") or 0
        a["rows"] += 1
        a["cores"].add("m_axi_adapter")
        a["modules"].add(inst.get("parent", ""))
    for inst in v.get("instances", []):
        mod = inst.get("Module") or ""
        if mod not in MATH_CORES["modules"] or inst.get("parent") in MATH_CORES["modules"]:
            continue
        name = "math_core:" + mod
        a = out.setdefault(name, {"name": name, "vitis_bram": 0, "banks": 0, "rows": 0,
                                  "words": 0, "bits": None, "cores": set(), "modules": set()})
        a["vitis_bram"] += inst.get("BRAM_18K") or 0
        a["rows"] += 1
        a["cores"].add("math_core")
        a["modules"].add(inst.get("parent", ""))
    for a in out.values():
        a["cores"] = sorted(a["cores"])
        a["modules"] = sorted(a["modules"])
    return out


# The source name inside a mangled global: a static local `<fn>@static@_ZZ<fn>E<len><name>[_<n>]`
# (cgeist names the global after its function and the Itanium name of the variable, `_<n>` the
# discriminator of a second static of that name) and an internal-linkage global `_ZL<len><name>`.
STATIC_LOCAL_RE = re.compile(r"@static@_ZZ.*E(\d+)([A-Za-z_]\w*)$")
INTERNAL_GLOBAL_RE = re.compile(r"^_ZL(\d+)([A-Za-z_]\w*)$")


def source_array_name(name):
    """The C name of an hls-est memref named after a mangled global (STATIC_LOCAL_RE /
    INTERNAL_GLOBAL_RE; the length prefix must match), else `name` unchanged.  Vitis names its
    memory rows by the C variable (`conv_0_out`), so without this every static local of a design
    (the gnnbuilder / flowgnn dataflow buffers) showed `vitis=None` in the per-array rows (W9
    round 6 review defect 8; totals are unaffected)."""
    if not isinstance(name, str):
        return name
    for rx in (STATIC_LOCAL_RE, INTERNAL_GLOBAL_RE):
        m = rx.search(name)
        if not m:
            continue
        ident, n = m.group(2), int(m.group(1))
        if len(ident) == n:
            return ident
        if rx is STATIC_LOCAL_RE and len(ident) > n and re.fullmatch(r"_\d+", ident[n:]):
            return ident[:n]
    return name


def hlsest_arrays(h):
    """Aggregate hls-est memrefs by variable name (a mangled global by its C name,
    source_array_name).  Prefers the debug JSON."""
    out = {}
    dbg = None
    dj = h.get("debug_json")
    if dj and Path(dj).exists():
        try:
            dbg = json.load(open(dj))
        except Exception:
            dbg = None
    if dbg and "memrefs" in dbg:
        for m in dbg["memrefs"]:
            name = source_array_name(m.get("varname") or m.get("name") or m.get("id"))
            a = out.setdefault(name, {"name": name, "hlsest_bram": 0, "banks": 0, "kinds": set(),
                                      "status": set(), "shape": m.get("shape"), "elem_bits": m.get("elem_bits")})
            a["hlsest_bram"] += m.get("bram") or 0
            a["banks"] += len(m.get("banks") or []) or 1
            if m.get("ram_type"):
                a["kinds"].add(m["ram_type"])
            a["status"].add(m.get("status") or "counted")
        for a in out.values():
            a["kinds"] = sorted(a["kinds"])
            a["status"] = sorted(a["status"])
        return out, True
    for m in h.get("memrefs", []):
        name = source_array_name(m.get("varname") or m.get("name") or m.get("head"))
        a = out.setdefault(name, {"name": name, "hlsest_bram": 0, "banks": 0, "kinds": set(), "status": set()})
        a["hlsest_bram"] += m.get("bram") or 0
        a["banks"] += 1
        if m.get("kind"):
            a["kinds"].add(m["kind"])
    for a in out.values():
        a["kinds"] = sorted(a["kinds"])
        a["status"] = sorted(a["status"])
    return out, False


def compare_one(key, v, h):
    r = {"key": key, "dataset": key.split("/")[0], "benchmark": key.split("/", 1)[1]}
    vb = (v or {}).get("totals", {}).get("BRAM") if v and v.get("status") == "ok" else None
    hb = h.get("total_bram") if h and h.get("status") == "ok" else None
    r["vitis_status"] = (v or {}).get("status", "missing")
    r["vitis_note"] = (v or {}).get("note", "")
    r["hlsest_status"] = (h or {}).get("status", "missing")
    r["vitis_bram"], r["hlsest_bram"] = vb, hb
    vkey, hkeys = (v or {}).get("key"), (h or {}).get("vitis_keys")
    if vb is not None and hb is not None and vkey and hkeys and vkey not in hkeys.values():
        r["diff"], r["exact"] = None, False
        r["status"] = "sources differ"
        r["vitis_key"], r["hlsest_vitis_keys"] = vkey, hkeys
        r["vitis_catalog"] = (v or {}).get("catalog")
    elif vb is not None and hb is not None:
        r["diff"] = hb - vb
        r["exact"] = (hb == vb)
        r["status"] = "compared"
    else:
        r["diff"], r["exact"] = None, False
        r["status"] = "vitis missing" if vb is None else "hls-est missing"
    arrays = []
    if v and h:
        ha, has_names = hlsest_arrays(h)
        va = vitis_arrays(v, set(ha) if has_names else None)
        r["array_names_available"] = has_names
        names = sorted(set(va) | set(ha))
        for n in names:
            a, b = va.get(n), ha.get(n)
            arrays.append({
                "name": n,
                "vitis_bram": a["vitis_bram"] if a else None,
                "vitis_words": a["words"] if a else None, "vitis_bits": a["bits"] if a else None,
                "vitis_banks": a["banks"] if a else None, "vitis_core": ",".join(a["cores"]) if a else None,
                "vitis_modules": ";".join(a["modules"]) if a else None,
                "hlsest_bram": b["hlsest_bram"] if b else None,
                "hlsest_banks": b["banks"] if b else None,
                "hlsest_kind": ",".join(b["kinds"]) if b else None,
                "hlsest_status": ",".join(b["status"]) if b else None,
                "diff": ((b["hlsest_bram"] if b else 0) - (a["vitis_bram"] if a else 0)),
            })
    r["arrays"] = arrays
    # BRAM that Vitis spends outside array memories (m_axi adapters, FIFOs): total - sum(memories)
    if v and v.get("status") == "ok":
        mem_sum = sum((m.get("bram") or 0) for m in v.get("memories", []))
        r["vitis_non_array_bram"] = (vb or 0) - mem_sum
    return r


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--vitis", default=str(C.RESULTS_DIR / "vitis.json"))
    ap.add_argument("--hlsest", default=str(C.RESULTS_DIR / "hlsest.json"))
    ap.add_argument("--out", default=str(C.RESULTS_DIR / "compare.json"))
    ap.add_argument("--csv", default=str(C.RESULTS_DIR / "compare.csv"))
    ap.add_argument("--quiet", action="store_true")
    ap.add_argument("--arrays", action="store_true", help="print per-array diffs of mismatches")
    args = ap.parse_args()

    V = C.load_json(args.vitis, {}) or {}
    H = C.load_json(args.hlsest, {}) or {}
    meta = H.pop("_meta", {})
    keys = sorted(set(V) | set(H))
    rows = [compare_one(k, V.get(k), H.get(k)) for k in keys]
    summary = summarize(rows)
    C.dump_json({"meta": meta, "summary": summary, "rows": rows}, args.out)
    with open(args.csv, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["dataset", "benchmark", "vitis_bram", "hlsest_bram", "diff", "exact", "status",
                    "vitis_status", "hlsest_status"])
        for r in rows:
            w.writerow([r["dataset"], r["benchmark"], r["vitis_bram"], r["hlsest_bram"], r["diff"],
                        r["exact"], r["status"], r["vitis_status"], r["hlsest_status"]])
    if not args.quiet:
        print_report(rows, summary, meta, args.arrays)


def summarize(rows):
    cmp_ = [r for r in rows if r["status"] == "compared"]
    s = {
        "designs": len(rows), "compared": len(cmp_),
        "exact": sum(1 for r in cmp_ if r["exact"]),
        "total_abs_error": sum(abs(r["diff"]) for r in cmp_),
        "vitis_missing": sum(1 for r in rows if r["status"] == "vitis missing"),
        "hlsest_missing": sum(1 for r in rows if r["status"] == "hls-est missing"),
        "sources_differ": sum(1 for r in rows if r["status"] == "sources differ"),
        "per_dataset": {},
    }
    by = defaultdict(list)
    for r in rows:
        by[r["dataset"]].append(r)
    for ds, rs in sorted(by.items()):
        c = [r for r in rs if r["status"] == "compared"]
        s["per_dataset"][ds] = {"designs": len(rs), "compared": len(c),
                                "exact": sum(1 for r in c if r["exact"]),
                                "abs_error": sum(abs(r["diff"]) for r in c),
                                "hlsest_failed": sum(1 for r in rs if r["status"] == "hls-est missing"),
                                "vitis_failed": sum(1 for r in rs if r["status"] == "vitis missing")}
    return s


def print_report(rows, s, meta, show_arrays):
    print(f"pipeline: {meta.get('pipeline')}   hls-est git: {meta.get('hls_est_git')}   "
          f"catalogue: {meta.get('catalog', 'not recorded')}")
    print(f"designs {s['designs']}  compared {s['compared']}  exact {s['exact']}  "
          f"|err| {s['total_abs_error']}  vitis-missing {s['vitis_missing']}  hls-est-missing {s['hlsest_missing']}"
          + (f"  sources-differ {s['sources_differ']}" if s.get("sources_differ") else ""))
    print(f"{'dataset':28s} {'n':>4s} {'cmp':>4s} {'exact':>5s} {'|err|':>7s} {'est-fail':>8s} {'vit-fail':>8s}")
    for ds, d in s["per_dataset"].items():
        print(f"{ds:28s} {d['designs']:4d} {d['compared']:4d} {d['exact']:5d} {d['abs_error']:7d} "
              f"{d['hlsest_failed']:8d} {d['vitis_failed']:8d}")
    mism = sorted([r for r in rows if r["status"] == "compared" and not r["exact"]],
                  key=lambda r: -abs(r["diff"]))
    print(f"\nmismatches ({len(mism)}), sorted by |diff|:")
    for r in mism:
        print(f"  {r['key']:50s} vitis={r['vitis_bram']:5d} hls-est={r['hlsest_bram']:5d} diff={r['diff']:+5d}")
        if show_arrays:
            for a in sorted(r["arrays"], key=lambda a: -abs(a["diff"] or 0)):
                if a["diff"]:
                    print(f"      {a['name']:28s} vitis={a['vitis_bram']} ({a['vitis_words']}x{a['vitis_bits']}, "
                          f"{a['vitis_banks']} banks, {a['vitis_core']})  hls-est={a['hlsest_bram']} "
                          f"({a['hlsest_kind']}, {a['hlsest_status']})  diff={a['diff']:+d}")
    fails = [r for r in rows if r["status"] != "compared"]
    if fails:
        print(f"\nnot compared ({len(fails)}):")
        for r in fails:
            if r["status"] == "sources differ":
                print(f"  {r['key']:50s} sources differ: ground truth key {r['vitis_key']} "
                      f"(catalogue {r.get('vitis_catalog') or 'not recorded'}), hls-est record "
                      f"{r['hlsest_vitis_keys'].get('off')} (td=off)")
                continue
            print(f"  {r['key']:50s} vitis: {r['vitis_status']} {r['vitis_note'][:60]} | hls-est: {r['hlsest_status']}")


if __name__ == "__main__":
    main()
