#!/usr/bin/env python3
"""Align every array of one design across the Vitis stages and hls-est.

usage: align_arrays.py <dataset>/<benchmark> [--hlsest-json F | --run-id ID] [--rtl DIR] [--json OUT]
                       [--vitis results/vitis.json] [--brief] [--no-args]

Stages (all grep-style scans; no file is printed whole):
  source   db/a.g.ld.5.gdce.ll  allocas / globals / top-function array arguments as the
                                front end emitted them (ap_fixed<W,..> structs = W bits)
  a.o.1    db/a.o.1.ll          after the first reflow stage (partition banks `x.1`, `x.2`)
  a.o.2    db/a.o.2.ll
  a.o.3    db/a.o.3.ll          the form handed to scheduling (banks `x_1`, flattened dims,
                                narrowed element widths, constant-initialised ROMs)
  sched    db/<module>.verbose.rpt  alloca names the scheduler sees (after a.o.3; only consulted
                                for arrays alive at a.o.3, because scalars are allocas there too):
                                shows IR banks merged back into one memory before scheduling
  report   the `* Memory:` rows of results/vitis.json (banks grouped by vitis_parse),
           plus the [HLS 214-*]/[HLS 200-2167] log lines that mention the array
  rtl      syn/verilog memories (only when a verilog dir exists: --rtl, or a leftover work
           dir found by rtl_memories.py; the harvest keeps no RTL)
  hls-est  the memrefs of hls-est's --bram-debug-json (grouped by varname)

One row per array: its source form, its form at each stage, the first stage where it
diverges from the source form (deleted / partitioned into N / width W->W' / flattened /
ROM / replicated xN / LUTRAM / interface / no memory instance), the Vitis BRAM and the
hls-est status and BRAM.  Every number is parsed from the named files.

Python 3 stdlib only (c++filt is used when present, with a small built-in fallback).
Importable: `align(key, ...)` returns the rows as dicts.
"""
import argparse
import glob
import json
import os
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import rtl_memories as RTL  # noqa: E402

RESULTS_VITIS = HERE / "results" / "vitis.json"
HLSEST_LOGS = Path.home() / "hls-est-work" / "hlsest-logs"
STAGES = ["source", "a.o.1", "a.o.2", "a.o.3"]
STAGE_FILES = {"source": "a.g.ld.5.gdce.ll", "a.o.1": "a.o.1.ll", "a.o.2": "a.o.2.ll", "a.o.3": "a.o.3.ll"}


# ---------------------------------------------------------------- names

def demangle_many(names):
    """{mangled: demangled} for every `_Z...` name (c++filt, else a small fallback).
    LLVM uniquing suffixes (`_ZL3foo.14966`) are stripped before demangling and the
    stripped name is mapped too."""
    raw = [n for n in names if n.startswith("_Z")]
    stripped = sorted({re.sub(r"\.\d+$", "", n) for n in raw})
    out = {}
    if stripped:
        try:
            p = subprocess.run(["c++filt"], input="\n".join(stripped) + "\n", capture_output=True, text=True, timeout=30)
            lines = p.stdout.splitlines()
            if len(lines) == len(stripped):
                out = dict(zip(stripped, lines))
        except Exception:
            out = {}
    for n in stripped:
        if n not in out or out[n] == n:
            out[n] = _fallback_demangle(n)
    for n in raw:
        out.setdefault(n, out[re.sub(r"\.\d+$", "", n)])
    return out


def _fallback_demangle(n):
    """Enough of the Itanium ABI for `_ZN<ns><name>E`, `_ZL<name>`, `_ZZ...E<name>` statics."""
    s = n[2:]
    parts = []
    i = 0
    nested = False
    while i < len(s):
        c = s[i]
        if c in "NLZE":
            nested = nested or c in "NZ"
            i += 1
            continue
        m = re.match(r"(\d+)", s[i:])
        if not m:
            break
        ln = int(m.group(1))
        i += len(m.group(1))
        parts.append(s[i:i + ln])
        i += ln
    return "::".join(parts) if parts else n


def strip_parens(s):
    out, depth = [], 0
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        elif depth == 0:
            out.append(ch)
    return "".join(out)


def static_discriminator(mangled):
    """Itanium discriminator of a function-local static: `...E17exp_x_msb_1_table_0` -> 2
    (no suffix = 1st, `_0` = 2nd, `_1` = 3rd).  c++filt drops it, so two different
    statics with the same name in one function would otherwise collapse into one."""
    for m in reversed(list(re.finditer(r"\d+", mangled))):
        ln = int(m.group())
        ident = mangled[m.end():m.end() + ln]
        tail = mangled[m.end() + ln:]
        if ln and len(ident) == ln and re.match(r"^[A-Za-z_]\w*$", ident) and re.fullmatch(r"(_\d+|__\d+_)?", tail):
            d = re.search(r"\d+", tail)
            return 0 if not tail else int(d.group()) + 2
    return 0


def canon(name, dm=None):
    """Canonical full name and its last component for an LLVM symbol."""
    n = name.strip()
    if n[:1] in "@%":
        n = n[1:]
    if n[:1] == '"' and n[-1:] == '"':
        n = n[1:-1]
    n = re.sub(r"\.\d+$", "", n)              # LLVM uniquing suffix on globals (`x.14966`)
    disc = 0
    if n.startswith("_Z"):
        disc = static_discriminator(n) if n.startswith("_ZZ") else 0
        n = (dm or {}).get(n) or _fallback_demangle(n)
    n = strip_parens(n)
    n = re.sub(r"<[^<>]*>", lambda m: "_" + re.sub(r"[^0-9A-Za-z]+", "_", m.group(0)).strip("_"), n)
    comps = [c for c in re.split(r"::|\.", n) if c]
    comps = [re.sub(r"[^0-9A-Za-z_]+", "_", c).strip("_") for c in comps]
    comps = [c for c in comps if c]
    full = "_".join(comps) if comps else n
    last = comps[-1] if comps else n
    if disc:
        full, last = f"{full}~{disc}", f"{last}~{disc}"
    return full, last


def bank_bases(name):
    """Every split of trailing bank indices, longest base first:
    `W_0_1` -> [('W_0', '1'), ('W', '0_1')]; `buff_A.3` -> [('buff_A', '3')]; `x` -> []."""
    out, cur, tail = [], name, ""
    while True:
        m = re.match(r"^(.*?)[._](\d+)$", cur)
        if not (m and m.group(1)):
            return out
        cur, tail = m.group(1), m.group(2) + ("_" + tail if tail else "")
        out.append((cur, tail))


def bank_base(name):
    """All trailing bank indices stripped (multi-dimensional partitions name banks
    `X_i_j`): `buff_A.3` -> ('buff_A', '3'), `BIAS_1_0_7` -> ('BIAS', '1_0_7'); otherwise
    (name, None).  Callers that know the source array names use known_root() first, so a
    real array `BIAS_1` keeps its own name and `BIAS_1_0_7` is its bank '0_7'."""
    b = bank_bases(name)
    return b[-1] if b else (name, None)


def sibling_base(name, others):
    """The longest bank base of `name` that another name in `others` shares (as itself or
    as one of its own bank bases); (name, None) when there is none."""
    for b, tail in bank_bases(name):
        if b in others or any(x != name and any(bx == b for bx, _ in bank_bases(x)) for x in others):
            return b, tail
    return name, None


# ---------------------------------------------------------------- types

def split_top(s, sep=","):
    out, depth, cur = [], 0, []
    for ch in s:
        if ch in "[<({":
            depth += 1
        elif ch in "]>)}":
            depth -= 1
        if ch == sep and depth == 0:
            out.append("".join(cur).strip())
            cur = []
        else:
            cur.append(ch)
    if "".join(cur).strip():
        out.append("".join(cur).strip())
    return out


def take_type(s):
    """Return (type_text, rest) for a type at the start of s (handles [..], {..}, %"..", ptr stars)."""
    s = s.lstrip()
    if not s:
        return "", ""
    if s[0] in "[{<":
        close = {"[": "]", "{": "}", "<": ">"}[s[0]]
        depth, i = 0, 0
        while i < len(s):
            if s[i] == s[0]:
                depth += 1
            elif s[i] == close:
                depth -= 1
                if depth == 0:
                    break
            i += 1
        t = s[:i + 1]
        rest = s[i + 1:]
    elif s[0] == "%":
        if s[1:2] == '"':
            j = s.find('"', 2)
            t, rest = s[:j + 1], s[j + 1:]
        else:
            m = re.match(r"%[\w.$]+", s)
            t, rest = m.group(0), s[m.end():]
    else:
        m = re.match(r"[\w.]+(?:\s*addrspace\(\d+\))?", s)
        if not m:
            return "", s
        t, rest = m.group(0), s[m.end():]
    m = re.match(r"(\s*(?:addrspace\(\d+\)\s*)?\*)+", rest)
    if m:
        t += m.group(0).replace(" ", "")
        rest = rest[m.end():]
    return t, rest


def type_bits(t, types, depth=0):
    """Bit width of a scalar/struct type; None if unknown."""
    t = t.strip()
    if depth > 12:
        return None
    m = re.match(r"^i(\d+)$", t)
    if m:
        return int(m.group(1))
    if t in ("float",):
        return 32
    if t in ("double",):
        return 64
    if t in ("half",):
        return 16
    if t.endswith("*"):
        return None
    m = re.match(r'^%"?struct\.(?:ap_fixed_base|ap_fixed|ap_ufixed|ap_int|ap_uint|ap_int_base|ssdm_int)<\s*(-?\d+)', t)
    if m:
        return int(m.group(1))
    m = re.match(r"^\[(\d+) x (.*)\]$", t)
    if m:
        b = type_bits(m.group(2), types, depth + 1)
        return None if b is None else int(m.group(1)) * b
    if t.startswith("{"):
        inner = t[1:-1]
        total = 0
        for f in split_top(inner):
            b = type_bits(f, types, depth + 1)
            if b is None:
                return None
            total += b
        return total
    if t.startswith("%"):
        body = types.get(t)
        if body:
            return type_bits(body, types, depth + 1)
    return None


def parse_array_type(t, types):
    """`[8 x [256 x T]]` -> dims [8,256], elem T, bits.  Scalars -> dims []."""
    dims = []
    cur = t.strip()
    while True:
        m = re.match(r"^\[(\d+) x (.*)\]$", cur)
        if not m:
            break
        dims.append(int(m.group(1)))
        cur = m.group(2).strip()
    return dims, cur, type_bits(cur, types)


def short_elem(t):
    t = t.strip()
    m = re.match(r'^%"?struct\.(ap_u?fixed|ap_u?int)<\s*([^>]*?)\s*>', t)
    if m:
        args = [a.strip() for a in m.group(2).split(",")]
        return f"{m.group(1)}<{','.join(args[:2])}>"
    m = re.match(r'^%"?struct\.([^".<]+)', t)
    if m:
        return "struct." + m.group(1)
    return t


# ---------------------------------------------------------------- .ll scanning

DEFINE_RE = re.compile(r'^define\b[^@]*@("[^"]+"|[^\s(]+)\((.*)\)[^()]*$')
ALLOCA_RE = re.compile(r'^\s*%("[^"]+"|[^\s=]+)\s*=\s*alloca\s+(.*)$')
GLOBAL_RE = re.compile(r'^@("[^"]+"|[^\s=]+)\s*=\s*(.*)$')
TYPEDEF_RE = re.compile(r'^(%"[^"]+"|%[\w.$]+)\s*=\s*type\s+(.*)$')


def scan_ll(path):
    """Grep-style scan.  Returns {'types','globals','allocas','functions','n_lines'}."""
    types, globs, allocas, functions = {}, [], [], {}
    cur_fn = None
    n = 0
    with open(path, errors="replace") as f:
        for line in f:
            n += 1
            if line.startswith("define"):
                m = DEFINE_RE.match(line)
                if m:
                    cur_fn = m.group(1).strip('"')
                    params = []
                    for p in split_top(m.group(2)):
                        t, rest = take_type(p)
                        mm = re.search(r"%(\"[^\"]+\"|[\w.$]+)\s*$", rest)
                        params.append({"type": t, "name": mm.group(1).strip('"') if mm else None,
                                       "dim_hint": (re.search(r'"fpga\.decayed\.dim\.hint"="(\d+)"', rest) or [None, None])[1]})
                    functions[cur_fn] = {"params": params, "line": n}
                continue
            if line.startswith("}"):
                cur_fn = None
                continue
            if line.startswith("%") and " = type " in line:
                m = TYPEDEF_RE.match(line)
                if m:
                    types[m.group(1)] = m.group(2).strip()
                continue
            if line.startswith("@"):
                m = GLOBAL_RE.match(line)
                if not m:
                    continue
                name = m.group(1).strip('"')
                rest = m.group(2)
                mk = re.search(r"\b(global|constant)\s+", rest)
                if not mk:
                    continue
                t, after = take_type(rest[mk.end():])
                if not t.startswith("[") or t.endswith("*"):
                    continue
                after = after.strip()
                if re.match(r'^c"', after) or re.match(r"^\[\d+ x i8\]$", t) and after.startswith("c"):
                    continue          # string literal
                if name.startswith("llvm.") or re.match(r"^\d+$", name) or name.endswith("_str") or name.startswith("empty"):
                    continue
                init = "zero" if after.startswith("zeroinitializer") else "none" if (not after or after.startswith(",") or after.startswith("align")) \
                    else "undef" if after.startswith("undef") else "data"
                linkage = " ".join(w for w in rest[:mk.start()].split() if w in ("internal", "private", "external", "linkonce_odr", "weak", "common"))
                globs.append({"name": name, "type": t, "init": init, "const": mk.group(1) == "constant",
                              "linkage": linkage, "line": n})
                continue
            if cur_fn and "= alloca" in line:
                m = ALLOCA_RE.match(line)
                if not m:
                    continue
                t, _ = take_type(m.group(2))
                if not t.startswith("[") or t.endswith("*"):
                    continue          # scalars and pointer spill slots (`%A.addr`) are not arrays
                allocas.append({"name": m.group(1).strip('"'), "func": cur_fn, "type": t, "line": n})
    return {"types": types, "globals": globs, "allocas": allocas, "functions": functions, "n_lines": n}


SCHED_ALLOCA_RE = re.compile(r'"%([\w.$]+) = alloca (i\d+) (\d+)"')


def scan_sched(db):
    """Alloca names in the scheduler's per-module reports (`<module>.verbose.rpt`, the form after
    a.o.3 that scheduling and binding see).  Scalars appear there too (`alloca i32 1`), so the
    names are only used for arrays still alive at a.o.3.  Returns {name: [module, ...]}."""
    out = {}
    for f in sorted(Path(db).glob("*.verbose.rpt")):
        mod = f.name[:-len(".verbose.rpt")]
        with open(f, errors="replace") as fh:
            for line in fh:
                if "= alloca" not in line:
                    continue
                for m in SCHED_ALLOCA_RE.finditer(line):
                    lst = out.setdefault(m.group(1), [])
                    if mod not in lst:
                        lst.append(mod)
    return out


BANK_TAIL_RE = re.compile(r"^(?:\.i\d*|[._]\d+)+$")   # partition banks (`.1`, `_1`, `_0_1`) and inline suffixes (`.i`)


def known_root(name, known):
    """Longest name in `known` that `name` equals or extends by bank/inline suffixes only.
    Returns (root, bank_tail) or (None, None)."""
    if name in known:
        return name, ""
    best = None
    for k in known:
        if len(k) < len(name) and name.startswith(k) and BANK_TAIL_RE.match(name[len(k):]):
            if best is None or len(k) > len(best):
                best = k
    return (best, name[len(best):]) if best else (None, None)


def stage_entities(scan, dm, top_names, group_banks=True, known_allocas=None, known_globals=None):
    """Group a stage's arrays by (kind, canonical function, base name) -> entity-form dict.
    `group_banks=False` for the source stage: before reflow there are no partition banks,
    and names like `table_0`/`table_1` are distinct statics, not banks.  For later stages a
    name is grouped under the source array it extends by bank suffixes (`buff_A.3`, `w_0_1`,
    `x.i`); without a source match, under a sibling `x` / `x_N` of the same stage.
    `known_allocas` = source alloca names, `known_globals` = {canonical full name: last
    component} of the source globals."""
    out = {}
    known_allocas = known_allocas or set()
    known_globals = known_globals or {}

    def add(key, item):
        e = out.setdefault(key, {"n": 0, "items": [], "words": 0})
        e["n"] += 1
        e["items"].append(item)
        e["words"] += item["words"] or 0

    def finish():
        """Per entity: `clones` = distinct raw functions holding it (Vitis clones a function per
        call site, `f.61`, `f.64`, ...; canon() folds them), `banks` = allocas per clone (max)."""
        for e in out.values():
            per_fn = {}
            for it in e["items"]:
                per_fn[it.get("func") or ""] = per_fn.get(it.get("func") or "", 0) + 1
            e["clones"] = len(per_fn)
            e["banks"] = max(per_fn.values()) if per_fn else 0
            e["words_per_clone"] = e["words"] // e["clones"] if e["clones"] else e["words"]

    by_fn = {}
    for a in scan["allocas"]:
        by_fn.setdefault(a["func"], []).append(a)
    for fn, lst in by_fn.items():
        fn_canon, _ = canon(fn, dm)
        names = {a["name"] for a in lst}
        for a in lst:
            dims, elem, bits = parse_array_type(a["type"], scan["types"])
            base, bank = a["name"], None
            if group_banks:
                root, tail = known_root(a["name"], known_allocas)
                if root is not None:
                    base, bank = root, (tail or None)
                else:
                    b, k = sibling_base(a["name"], names)
                    if k is not None:
                        base, bank = b, k
            words = 1
            for d in dims:
                words *= d
            add(("alloca", fn_canon, base), {"name": a["name"], "bank": bank, "dims": dims, "elem": short_elem(elem),
                                             "bits": bits, "words": words, "line": a["line"], "func": fn})
    gfull = {g["name"]: canon(g["name"], dm) for g in scan["globals"]}
    fulls = {f for f, _ in gfull.values()}
    for g in scan["globals"]:
        dims, elem, bits = parse_array_type(g["type"], scan["types"])
        full, last = gfull[g["name"]]
        bank = None
        if group_banks:
            root, tail = known_root(full, known_globals)
            if root is not None and tail:
                full, bank = root, tail
                last = known_globals.get(root) or root
            elif root is None:
                b, k = sibling_base(full, fulls)
                if k is not None:
                    full, bank = b, k
                    last = last[:len(last) - len(k) - 1] if last.endswith(k) and len(last) > len(k) + 1 else last
        words = 1
        for d in dims:
            words *= d
        add(("global", "", full), {"name": g["name"], "bank": bank, "dims": dims, "elem": short_elem(elem), "bits": bits,
                                   "words": words, "line": g["line"], "init": g["init"], "const": g["const"], "last": last})
    # top-function array / pointer arguments
    for fn, info in scan["functions"].items():
        fn_canon, fn_last = canon(fn, dm)
        if fn_canon not in top_names and fn_last not in top_names and fn not in top_names:
            continue
        for p in info["params"]:
            t = p["type"]
            if not (t.endswith("*") or t.startswith("[")):
                continue
            inner = t.rstrip("*").strip()
            inner = re.sub(r"\s*addrspace\(\d+\)$", "", inner)
            dims, elem, bits = parse_array_type(inner, scan["types"])
            if p["dim_hint"]:
                dims = [int(p["dim_hint"])] + dims
            words = 1
            for d in dims:
                words *= d
            add(("arg", fn_canon, p["name"] or "?"), {"name": p["name"], "bank": None, "dims": dims, "elem": short_elem(elem),
                                                     "bits": bits, "words": words if dims else None, "line": info["line"], "ptr": t.endswith("*")})
    finish()
    return out


# ---------------------------------------------------------------- hls-est / report / rtl

def default_pipeline_passes():
    try:
        import common as C   # noqa: E402
        return [t[2:] for t in C.DEFAULT_PIPELINE.split() if t.startswith("--")]
    except Exception:  # noqa: BLE001
        return None


def _is_subsequence(needle, hay):
    it = iter(hay)
    return all(any(x == y for y in it) for x in needle)


def find_debug_json(ds, bench, run_id=None, why=None):
    """The hls-est debug JSON for one design.  With `run_id`: that run.  Otherwise the newest run
    whose pass list (from the .err command line) contains the harness default pipeline
    (common.DEFAULT_PIPELINE) in order, so pipeline experiments (ablations) are not picked up by
    accident; if no run has it, the newest run.  `why` (a list) receives one line saying which."""
    if run_id:
        p = HLSEST_LOGS / run_id / f"{ds}__{bench}.debug.json"
        if why is not None:
            why.append(f"run {run_id} (given)")
        return str(p) if p.exists() else None
    pat = str(HLSEST_LOGS / "*" / f"{ds}__{bench}.debug.json")
    files = sorted(glob.glob(pat), key=os.path.getmtime)
    if not files:
        return None
    want = default_pipeline_passes()
    if want:
        for f in reversed(files):
            pl = hlsest_pipeline_of(f)
            if pl and _is_subsequence(want, [t.split("=")[0] for t in pl.split()]):
                if why is not None:
                    why.append(f"newest run whose passes include the default pipeline, options ignored "
                               f"({Path(f).parent.name}; {len(files)} runs have this design)")
                return f
    if why is not None:
        why.append(f"newest run ({Path(files[-1]).parent.name}); none of the {len(files)} runs used the default pipeline")
    return files[-1]


def hlsest_groups(debug_json):
    """memrefs grouped by (varname, MLIR line of the allocation): the banks of one array share
    the line and collapse into one group; two different arrays with the same varname (e.g. a
    callee's array inlined next to a local of the same name) stay apart as `name@L<line>`."""
    d = json.load(open(debug_json))
    lines_of = {}
    for m in d.get("memrefs", []):
        name = m.get("varname") or m.get("name") or m.get("id")
        lines_of.setdefault(name, set()).add((m.get("loc") or {}).get("line"))
    groups = {}
    for m in d.get("memrefs", []):
        vname = m.get("varname") or m.get("name") or m.get("id")
        line = (m.get("loc") or {}).get("line")
        name = vname if len(lines_of[vname]) == 1 else f"{vname}@L{line}"
        g = groups.setdefault(name, {"n": 0, "bram": 0, "statuses": {}, "kinds": set(), "shapes": [], "bits": set(),
                                     "ram_types": {}, "partition": None, "replication": set(), "reasons": [], "ids": [],
                                     "varname": vname, "mlir_line": line, "funcs": set()})
        g["funcs"].add(m.get("func"))
        g["n"] += 1
        g["bram"] += m.get("bram") or 0
        g["statuses"][m.get("status")] = g["statuses"].get(m.get("status"), 0) + 1
        g["kinds"].add(m.get("kind"))
        if m.get("shape") not in g["shapes"]:
            g["shapes"].append(m.get("shape"))
        g["bits"].add(m.get("elem_bits"))
        if m.get("ram_type"):
            g["ram_types"][m["ram_type"]] = g["ram_types"].get(m["ram_type"], 0) + 1
        p = m.get("partition")
        if p and not g["partition"]:
            g["partition"] = {k: p.get(k) for k in ("kind", "factor", "dim", "bank_count", "source")}
        if m.get("replication"):
            g["replication"].add(json.dumps(m["replication"], sort_keys=True))
        if m.get("exclude_reason") and len(g["reasons"]) < 2:
            g["reasons"].append(m["exclude_reason"])
        g["ids"].append(m.get("id"))
    for g in groups.values():
        g["kinds"] = sorted(x for x in g["kinds"] if x)
        g["bits"] = sorted(x for x in g["bits"] if x is not None)
        g["funcs"] = sorted(x for x in g["funcs"] if x)
        g["replication"] = [json.loads(x) for x in sorted(g["replication"])]
    return {"groups": groups, "total_bram": d.get("total_bram"), "version": d.get("version"), "path": debug_json,
            "n_memrefs": len(d.get("memrefs", [])), "pipeline": hlsest_pipeline_of(debug_json),
            "sum_bram": sum(g["bram"] for g in groups.values())}


def hlsest_pipeline_of(debug_json):
    """The pass list of the run that wrote this debug JSON (run_hlsest.py puts the command
    line on the first line of <prefix>.err).  None when unknown."""
    err = Path(str(debug_json).replace(".debug.json", ".err"))
    try:
        with open(err, errors="replace") as f:
            cmd = f.readline().split()
    except OSError:
        return None
    passes = [t[2:] for t in cmd if t.startswith("--") and not t.startswith("--bram-debug-json")]
    return " ".join(passes) if passes else None


def module_multiplicity(entry):
    """Instances of each module under the top, from the per-module `* Instance:` tables
    (vitis_parse instances[]: Module, parent), multiplied up the hierarchy.  A module that
    is never instantiated (the top) counts 1.  Returns {module: count}."""
    parents = {}
    for i in entry.get("instances") or []:
        m, par = i.get("Module"), i.get("parent")
        if m and par:
            parents.setdefault(m, []).append(par)
    memo = {}

    def mult(mod, stack=()):
        if mod in memo:
            return memo[mod]
        if mod not in parents or mod in stack:
            return 1
        n = sum(mult(par, stack + (mod,)) for par in parents[mod])
        memo[mod] = n
        return n
    return {m: mult(m) for m in set(parents) | {r.get("module") for r in entry.get("memories", []) if r.get("module")}}


def storage_report_fifos(cache_dir):
    """FIFO channels with BRAM from the '== Storage Report' of report/csynth.rpt (dataflow
    channels are not in the '* Memory:' tables).  Returns (bram_sum, [(name, bram, impl, 'W, D, B')])."""
    rpt = Path(cache_dir) / "report" / "csynth.rpt"
    if not rpt.exists():
        return 0, []
    rows, inside = [], False
    with open(rpt, errors="replace") as f:
        for line in f:
            if line.startswith("== Storage Report"):
                inside = True
                continue
            if inside and line.startswith("== "):
                break
            if not inside or not line.startswith("|"):
                continue
            cells = [c.strip() for c in line.strip().strip("|").split("|")]
            if len(cells) < 10 or "fifo" not in cells[1].lower():
                continue
            try:
                bram = int(cells[3]) if cells[3] else 0
            except ValueError:
                continue
            rows.append((cells[0], bram, cells[7], cells[9]))
    return sum(r[1] for r in rows), [r for r in rows if r[1]]


def vitis_reconcile(entry, rep_groups):
    """csynth total = memory rows (x module instances) + BRAM of leaf instances that hold no memory
    rows (m_axi/s_axi adapters, FIFOs).  Returns a dict with the parts and what is left over."""
    mem = sum(g["bram_eff"] for g in rep_groups.values())
    mem_mods = {r.get("module") for r in entry.get("memories", []) if r.get("module")}
    parents = {i.get("parent") for i in entry.get("instances") or []}
    mult = module_multiplicity(entry)
    leaf = [i for i in entry.get("instances") or []
            if (i.get("BRAM_18K") or 0) > 0 and i.get("Module") not in mem_mods and i.get("Module") not in parents]
    leaf_bram = sum((i.get("BRAM_18K") or 0) * mult.get(i.get("parent"), 1) for i in leaf)
    total = (entry.get("totals") or {}).get("BRAM")
    fifo_bram, fifos = storage_report_fifos(entry.get("cache_dir") or "")
    return {"total": total, "memories": mem, "leaf_instances": leaf_bram,
            "leaf_names": [f"{i.get('Instance')}={i.get('BRAM_18K')}" for i in leaf],
            "fifo_channels": fifo_bram, "fifo_names": [f"{n}={b}" for n, b, _impl, _shape in fifos],
            "unexplained": (total - mem - leaf_bram - fifo_bram) if isinstance(total, int) else None}


def report_key(m, known=None):
    """Group name of one `* Memory:` row: its own variable (csynth.xml BindNode VARIABLE, else
    the instance name without `_U`).  It is folded into another array only when it is a real
    partition bank: with the source names (`known`), when the variable is not a source array
    itself but extends one by bank indices (`V_3` -> V, `BIAS_1_0_7` -> BIAS_1); without them,
    vitis_parse's bank grouping (`array`).  Two real arrays `FM_buffer_1` / `FM_buffer_2` stay
    apart (vitis_parse alone would fold them into a fake `FM_buffer`)."""
    inst = str(m.get("Memory", ""))
    var = m.get("variable") or re.sub(r"_U(_x)?$", "", inst)
    if not known:
        name = m.get("array") or inst
        return re.sub(r"_U(_x)?$", "", name) if name == inst else name
    if var in known:
        return var
    root, _tail = known_root(var, known)
    return root if root is not None else var


def report_groups(entry, known=None):
    """`* Memory:` rows grouped by array (report_key: the row's own variable, banks folded into
    their source array), with the log lines about it.  `known` = source array names (allocas,
    globals, top arguments of a.g.ld.5.gdce); None = vitis_parse's grouping.
    `bram` sums the rows as printed (once per module); `bram_eff` multiplies each row by the
    number of instances of its module (a callee instantiated twice holds two copies)."""
    groups = {}
    mult = module_multiplicity(entry)
    for m in entry.get("memories", []):
        inst = str(m.get("Memory", ""))
        name = report_key(m, known)
        g = groups.setdefault(name, {"rows": 0, "bram": 0, "bram_eff": 0, "mult": set(), "words": 0, "bits": set(),
                                     "cores": {}, "modules": set(), "instances": [], "banks": set(), "variable": set()})
        g["rows"] += 1
        g["bram"] += m.get("BRAM_18K") or 0
        k = mult.get(m.get("module"), 1)
        g["bram_eff"] += (m.get("BRAM_18K") or 0) * k
        g["mult"].add(k)
        g["words"] += m.get("Words") or 0
        g["bits"].add(m.get("Bits"))
        g["cores"][m.get("core") or "?"] = g["cores"].get(m.get("core") or "?", 0) + 1
        g["modules"].add(m.get("module"))
        g["instances"].append(inst)
        if m.get("bank") is not None:
            g["banks"].add(m["bank"])
        if m.get("variable"):
            g["variable"].add(m["variable"])
    log = entry.get("log", {}) or {}
    for g in groups.values():
        g["bits"] = sorted(x for x in g["bits"] if x is not None)
        g["mult"] = sorted(g["mult"])
        g["modules"] = sorted(x for x in g["modules"] if x)
        g["banks"] = sorted(g["banks"])
        g["variable"] = sorted(g["variable"])
        g["log"] = []
    def mention(name):
        hits = []
        for cls in ("partition_inferred", "partition_applied", "partition_const_index", "partition_small",
                    "replicate", "memory_impl", "storage_inferred", "reshape", "ii_violation_ports"):
            for row in log.get(cls, []) or []:
                txt = " ".join(str(x) for x in row)
                if re.search(r"(^|[^0-9A-Za-z_])" + re.escape(name) + r"($|[^0-9A-Za-z_]|_RAM|_ROM)", txt):
                    hits.append((cls, row))
        return hits
    return groups, mention


def rtl_groups(vdir, known=None):
    """RTL memory instances grouped like report_key(): a source array keeps its name, a bank
    is folded into the source array it extends; without source names, into a bank base that
    another instance shares."""
    d = RTL.collect(vdir, with_adapters=False)
    groups = {}
    insts = {re.sub(r"_U(_x)?$", "", x["instance"]) for x in d["memories"]}
    for m in d["memories"]:
        base = re.sub(r"_U(_x)?$", "", m["instance"])
        if known and base in known:
            pass
        elif known and known_root(base, known)[0] is not None:
            base = known_root(base, known)[0]
        else:
            b, bank = sibling_base(base, insts)
            if bank is not None:
                base = b
        g = groups.setdefault(base, {"n": 0, "cores": set(), "styles": set(), "width": set(), "depth": 0, "ports": set(),
                                     "copies": set(), "parents": set(), "report_bram": 0, "init": set(),
                                     "copy_map": set(), "parent_instances": set()})
        g["n"] += 1
        g["cores"].add(m["core"] or "?")
        g["styles"].add(m["style"] or "-")
        g["width"].add(m["width"])
        g["depth"] += m["depth"] if isinstance(m["depth"], int) else 0
        g["ports"].add(m["port_modes"])
        g["copies"].add(m["copies"])
        g["parents"].add(m["parent"])
        g["parent_instances"].add(m.get("parent_instances", 1))
        g["report_bram"] += m["report_BRAM_18K"] or 0
        if m.get("copy_map_text"):
            g["copy_map"].add(m["copy_map_text"])
        if m["init"]:
            g["init"].add(Path(m["init"]["file"]).name)
    for g in groups.values():
        for k in ("cores", "styles", "width", "ports", "copies", "parents", "init", "copy_map", "parent_instances"):
            g[k] = sorted(str(x) for x in g[k])
    return groups, d


def assign_groups(groups, entities, key_of=None):
    """One-to-one name matching of entities to report / hls-est / rtl groups.
    Pass 1: canonical full name; pass 2: last component / raw name; pass 3: the group name's
    bank base (`V_3` -> `V`).  A group already taken is only reused when nothing else fits
    (then the entity gets a note).  `key_of(gname)` maps a group name to the name to compare
    (hls-est groups compare by varname).  Returns {id(entity): (gname, shared?)}."""
    if not groups:
        return {}
    key_of = key_of or (lambda n: n)
    by_key = {}
    for gname in groups:
        by_key.setdefault(key_of(gname), []).append(gname)
    taken, out = set(), {}

    def take(e, cands):
        free = [c for c in cands if c not in taken]
        if free:
            taken.add(free[0])
            out[id(e)] = (free[0], False)
            return True
        return False
    for e in entities:
        take(e, by_key.get(e["full"], []))
    for e in entities:
        if id(e) not in out:
            take(e, by_key.get(e["last"], []) + by_key.get(e["name"], []))
    for e in entities:
        if id(e) not in out:
            take(e, [g for k, gs in by_key.items() if any(b in (e["full"], e["last"]) for b, _ in bank_bases(k)) for g in gs])
    for e in entities:          # second entity with the same name as an already matched one
        if id(e) not in out:
            cands = by_key.get(e["full"], []) + by_key.get(e["last"], [])
            if cands:
                out[id(e)] = (cands[0], True)
    return out


# ---------------------------------------------------------------- alignment

def fmt_report_group(g):
    """`<rows>inst <cores> <words>x<bits> BRAM=<n>`; `BRAM=<per module>x<instances>=<total>` when the
    module holding the memory is instantiated more than once."""
    b = f"BRAM={g['bram']}"
    if g["bram_eff"] != g["bram"]:
        b = f"BRAM={g['bram']}x{'/'.join(str(k) for k in g['mult'])}inst={g['bram_eff']}"
    return (f"{g['rows']}inst " + "/".join(f"{c}x{n}" if n > 1 else c for c, n in g["cores"].items())
            + f" {g['words']}x{'/'.join(str(b) for b in g['bits'])} {b}")


def fmt_form(e):
    if not e:
        return "-"
    it = e["items"][0]
    dims = "x".join(str(d) for d in it["dims"]) if it["dims"] else "ptr"
    bits = it["bits"] if it["bits"] is not None else "?"
    s = f"{e.get('banks', e['n'])}x[{dims}]@{bits}"
    if e.get("clones", 1) > 1:
        s += f"/{e['clones']}fn"
    if it.get("const"):
        s += "C"
    elif it.get("init") == "data":
        s += "D"
    return s


def align(key, vitis_json=RESULTS_VITIS, hlsest_json=None, rtl_dir=None, no_args=False):
    ds, bench = key.split("/", 1)
    res = json.load(open(vitis_json))
    entry = res.get(key)
    if not entry:
        raise SystemExit(f"{key} not in {vitis_json}")
    cdir = Path(entry["cache_dir"])
    top = entry.get("top")
    scans, dms = {}, {}
    all_names = set()
    for st in STAGES:
        p = cdir / "db" / STAGE_FILES[st]
        if p.exists():
            scans[st] = scan_ll(p)
            all_names |= {g["name"] for g in scans[st]["globals"]} | set(scans[st]["functions"])
    dm = demangle_many(sorted(all_names))
    top_names = {top} if top else set()
    known_allocas, known_globals = set(), {}
    if "source" in scans:
        known_allocas = {a["name"] for a in scans["source"]["allocas"]}
        known_globals = dict(canon(g["name"], dm) for g in scans["source"]["globals"])
    forms = {st: stage_entities(scans[st], dm, top_names, group_banks=(st != "source"),
                                known_allocas=known_allocas, known_globals=known_globals) for st in scans}

    # entity list: start from the source stage, then add anything new in later stages
    entities = {}      # ent key -> {'kind','func','name','last','forms':{stage: form}}

    def ent_key(kind, fn, base, form):
        if kind == "global":
            # stage_entities already canonicalized global names; keep its last component
            return kind, "", base, form["items"][0].get("last") or base
        full, last = canon(base, dm)
        return kind, (fn if kind == "alloca" else ""), full, last

    for st in STAGES:
        for (kind, fn, base), form in forms.get(st, {}).items():
            k = ent_key(kind, fn, base, form)
            e = entities.get(k)
            if e is None:
                # second chance: same kind + same last component (functions get renamed between stages)
                cands = [x for x in entities.values() if x["kind"] == kind and (x["last"] == k[3] or x["full"] == k[2])]
                if kind == "alloca":
                    same_fn = [x for x in cands if x["func"] == fn]
                    cands = same_fn or [x for x in cands if st not in x["forms"]]
                else:
                    cands = [x for x in cands if st not in x["forms"]]
                e = cands[0] if len(cands) >= 1 else None
            if e is None:
                e = {"kind": kind, "func": fn, "full": k[2], "last": k[3], "name": base, "origin": st, "forms": {}}
                entities[k] = e
            e["forms"][st] = form
    sched = scan_sched(cdir / "db") if (cdir / "db").is_dir() else {}
    for e in entities.values():
        f3 = e["forms"].get("a.o.3")
        if e["kind"] == "alloca" and f3 and sched:
            names3 = {it["name"] for it in f3["items"]} | {e["name"]}
            e["sched_names"] = sorted(n for n in names3 if n in sched)
    known = set()
    if "source" in scans:
        known = set(known_allocas) | set(known_globals) | set(known_globals.values())
        for fn, info in scans["source"]["functions"].items():
            fc, fl = canon(fn, dm)
            if fc in top_names or fl in top_names or fn in top_names:
                known |= {p["name"] for p in info["params"] if p.get("name")}
    rep_groups, mention = report_groups(entry, known or None)
    hls = hlsest_groups(hlsest_json) if hlsest_json else None
    rtl, rtl_info = (rtl_groups(rtl_dir, known or None) if rtl_dir else (None, None))
    status, note = entry.get("status"), vitis_note(entry)
    # the memory tables exist (a run that timed out after csynth still has them; forgebench/mlp)
    has_report = bool(entry.get("memories")) or (status == "ok")

    ents = list(entities.values())
    a_rep = assign_groups(rep_groups, ents)
    a_hls = assign_groups(hls["groups"], ents, key_of=lambda n: hls["groups"][n]["varname"]) if hls else {}
    a_rtl = assign_groups(rtl, ents) if rtl else {}

    rows = []
    used_rep, used_hls, used_rtl = set(), set(), set()
    for e in ents:
        src = e["forms"].get("source") or e["forms"].get(e["origin"])
        rname, rshared = a_rep.get(id(e), (None, False))
        hname, hshared = a_hls.get(id(e), (None, False))
        tname, tshared = a_rtl.get(id(e), (None, False))
        rg = rep_groups.get(rname) if rname else None
        hg = hls["groups"].get(hname) if (hls and hname) else None
        tg = rtl.get(tname) if (rtl and tname) else None
        used_rep.add(rname)
        used_hls.add(hname)
        used_rtl.add(tname)
        row = {"array": e["last"] if e["kind"] != "global" else e["full"], "kind": e["kind"], "func": e["func"],
               "origin": e["origin"], "forms": {st: fmt_form(e["forms"].get(st)) for st in STAGES},
               "source_dims": src["items"][0]["dims"] if src else None, "source_bits": src["items"][0]["bits"] if src else None,
               "source_elem": src["items"][0]["elem"] if src else None,
               "report_name": rname, "hlsest_name": hname, "rtl_name": tname}
        sn = e.get("sched_names")
        row["forms"]["sched"] = (f"{len(sn)} alloca" + ("s" if len(sn) != 1 else "")) if sn else ("0 allocas" if sn == [] else "-")
        row["divergence"], row["notes"] = first_divergence(e, rg, tg, set(scans), status, note, has_report)
        for what, nm, shared in (("report", rname, rshared), ("hls-est", hname, hshared), ("rtl", tname, tshared)):
            if shared:
                row["notes"].append(f"{what} group {nm} also matched another array of the same name (name-only match)")
        if hname and hg and "@L" in hname:
            row["notes"].append(f"hls-est has several arrays named {hg['varname']}; matched {hname} by name order only "
                                f"(MLIR line {hg['mlir_line']})")
        f3 = e["forms"].get("a.o.3")
        if f3 and rg and f3["n"] != rg["rows"]:
            row["notes"].append(f"a.o.3 has {f3['n']} allocas/globals ({f3['words']} words"
                                + (f", {f3['clones']} function clones" if f3.get("clones", 1) > 1 else "")
                                + f") but the report has {rg['rows']} memory instance(s) ({rg['words']} words)")
            b3 = f3.get("banks", f3["n"])
            if b3 > 1 and rg["rows"] < f3["n"] and row["divergence"].startswith("partitioned into"):
                sn = e.get("sched_names")
                if sn is not None and len(sn) < b3:
                    row["divergence"] += (f"; merged back to {len(sn)} before scheduling ({','.join(sn)} in *.verbose.rpt); "
                                          f"report: {rg['rows']} memory of {rg['words']} words")
                else:
                    row["divergence"] += f"; report: {rg['rows']} memory of {rg['words']} words"
        row["vitis"] = fmt_report_group(rg) if rg else ("-" if has_report else "no report")
        row["vitis_bram"] = rg["bram_eff"] if rg else None
        row["vitis_log"] = [f"{cls}: {' '.join(str(x) for x in r)[:100]}" for cls, r in mention(rname or e["last"])][:4]
        row["rtl"] = (f"{tg['n']}inst {'/'.join(tg['cores'])} {tg['depth']}x{'/'.join(tg['width'])} ports={'/'.join(tg['ports'])} "
                      f"copies={'/'.join(tg['copies'])} style={'/'.join(tg['styles'])}"
                      + (f" parent x{'/'.join(tg['parent_instances'])}" if tg["parent_instances"] != ["1"] else ""))            if tg else ("-" if rtl is not None else "n/a")
        if tg and tg["copy_map"]:
            row["notes"].append("rtl copies: " + "; ".join(tg["copy_map"]))
        if hg:
            st = "/".join(f"{k}x{v}" if v > 1 else k for k, v in hg["statuses"].items())
            part = hg["partition"]
            ps = f" part={part['kind']}:{part['factor']}d{part['dim']}({part['source']})" if part else ""
            rt = "/".join(f"{k}x{v}" if v > 1 else k for k, v in hg["ram_types"].items())
            rep = f" rep={hg['replication'][0].get('copies', hg['replication'][0])}" if hg["replication"] and isinstance(hg["replication"][0], dict) else ""
            shp = hg["shapes"][0] if hg["shapes"] else None
            form = (f"{hg['n']}x[{'x'.join(str(x) for x in shp)}]@{'/'.join(str(b) for b in hg['bits'])}"
                    if isinstance(shp, list) else f"{hg['n']}x[?]@{'/'.join(str(b) for b in hg['bits'])}")
            row["hlsest"] = f"{form} {st}{ps} {rt}{rep} BRAM={hg['bram']}"
            row["hlsest_form"] = form
            row["hlsest_bram"] = hg["bram"]
            row["hlsest_status"] = st
            sb = src["items"][0]["bits"] if src else None
            if sb is not None and hg["bits"] and hg["bits"] != [sb]:
                row["notes"].append(f"element width differs: Vitis source {sb} bits, hls-est {hg['bits']} (check the shim)")
        else:
            row["hlsest"] = "-" if hls else "n/a"
            row["hlsest_form"] = "-"
            row["hlsest_bram"] = None
            row["hlsest_status"] = None
        rows.append(row)
    # report / hls-est / rtl rows that matched no IR entity (Vitis-created tables, adapters, hls-est-only memrefs)
    for name, g in rep_groups.items():
        if name in used_rep:
            continue
        rows.append({"array": name, "kind": "report-only", "func": "", "origin": "report", "forms": {st: "-" for st in STAGES},
                     "divergence": "not in the IR scans (Vitis-created table or renamed)", "notes": [],
                     "vitis": fmt_report_group(g), "vitis_bram": g["bram_eff"], "vitis_log": [], "rtl": "-", "hlsest": "-", "hlsest_form": "-", "hlsest_bram": None, "hlsest_status": None})
    if hls:
        for name, g in hls["groups"].items():
            if name in used_hls:
                continue
            rows.append({"array": str(name), "kind": "hls-est-only", "func": "", "origin": "hls-est", "forms": {st: "-" for st in STAGES},
                         "divergence": ("hls-est memref with no Vitis counterpart" if has_report and scans else
                                        f"no Vitis counterpart to compare ({status_text(status, note)}; "
                                        f"stages kept: {', '.join(sorted(scans)) or 'none'})"),
                         "notes": [], "vitis": "-" if has_report else "no report", "vitis_bram": None, "vitis_log": [],
                         "rtl": "-", "hlsest": f"{g['n']}memref " + "/".join(g["statuses"]) + f" BRAM={g['bram']}",
                         "hlsest_form": f"{g['n']}x{g['shapes'][0] if g['shapes'] else '?'}@{'/'.join(str(b) for b in g['bits'])}",
                         "hlsest_bram": g["bram"], "hlsest_status": "/".join(g["statuses"])})
    if no_args:
        # top arguments with no memory instance anywhere are pure interfaces; they are kept
        # by default (they show which inputs/outputs Vitis implements as ports/adapters)
        rows = [r for r in rows if r["kind"] != "arg"]
    rows.sort(key=lambda r: (-(max(r["vitis_bram"] or 0, r["hlsest_bram"] or 0)), r["kind"], r["array"]))
    meta = {"key": key, "top": top, "cache_dir": str(cdir), "stages_found": sorted(scans), "stage_lines": {s: scans[s]["n_lines"] for s in scans},
            "hlsest_json": hls["path"] if hls else None, "hlsest_total": hls["total_bram"] if hls else None,
            "hlsest_pipeline": hls["pipeline"] if hls else None,
            "vitis_bram_total": (entry.get("totals") or {}).get("BRAM"), "rtl_dir": str(rtl_info["verilog_dir"]) if rtl_info else None,
            "vitis_status": status, "vitis_note": note, "vitis_has_report": has_report,
            "vitis_reconcile": vitis_reconcile(entry, rep_groups),
            "hlsest_sum_groups": hls["sum_bram"] if hls else None}
    if rtl_info:
        ok, why = RTL.matches_ground_truth(rtl_info["verilog_dir"], entry)
        meta["rtl_check"] = ("matches the ground truth: " if ok else "WARNING, RTL is not from the ground-truth run: ") + why
    return rows, meta


def vitis_note(entry):
    """One-line reason of a Vitis run that did not finish ('' for ok runs)."""
    if entry.get("status") == "ok":
        return ""
    n = str(entry.get("note") or "").strip().splitlines()
    return (n[0] if n else "no note")[:160]


def status_text(status, note):
    """'vitis failed: <note>' (results statuses already start with 'vitis')."""
    st = str(status) if str(status).startswith("vitis") else f"Vitis {status}"
    return f"{st}: {note or 'no note'}"


def first_divergence(e, rg, tg, stages_found=None, status="ok", note="", has_report=True):
    """Name the first stage where the array stops looking like its source form.  A stage file
    that is not in the cache dir is reported as missing (with the Vitis failure, when the run
    failed), never as the stage that deleted the array."""
    forms = e["forms"]
    notes = []
    src = forms.get("source")
    stages_found = set(STAGES) if stages_found is None else stages_found
    why = status_text(status, note) if status != "ok" else "file not in the cache dir"
    if e["kind"] == "arg":
        if not rg and not has_report:
            return f"top argument (no memory table to compare: {why})", notes
        return ("interface (top argument; implemented as a port/adapter, not a local memory)" if not rg
                else f"interface with a memory instance in the report ({'/'.join(rg['cores'])})"), notes
    if src is None:
        later = [st for st in STAGES if st in forms]
        return f"first seen at {later[0] if later else '?'} (not in the source IR)", notes
    s0 = src["items"][0]
    s_words, s_bits, s_n = src.get("words_per_clone", src["words"]), s0["bits"], src.get("banks", src["n"])
    s_clones = src.get("clones", 1)
    seen_later = False
    for st in STAGES[1:]:
        f = forms.get(st)
        if f is None and st not in stages_found:
            return f"stage {st} missing ({why})", notes
        if f is None:
            if any(forms.get(x) for x in STAGES[STAGES.index(st) + 1:]) or rg:
                notes.append(f"absent at {st}")
                continue
            return f"deleted at {st}", notes
        seen_later = True
        it = f["items"][0]
        f_n, f_words = f.get("banks", f["n"]), f.get("words_per_clone", f["words"])
        if f.get("clones", 1) != s_clones and not any(x.startswith("function cloned") for x in notes):
            notes.append(f"function cloned: {f.get('clones', 1)} copies at {st} (source {s_clones})")
        if f_n != s_n and f_n > 1:
            tail = ""
            if f_words != s_words:
                tail = f", {f_words} words total vs {s_words}"
            return f"partitioned into {f_n} at {st}{tail}", notes
        if f_words != s_words:
            return f"resized {s_words}->{f_words} words at {st}", notes
        if it["bits"] is not None and s_bits is not None and it["bits"] != s_bits:
            return f"width {s_bits}->{it['bits']} at {st}", notes
        if it.get("const") and not s0.get("const"):
            return f"ROM (constant initialiser) at {st}", notes
        if it["dims"] != s0["dims"] and len(it["dims"]) != len(s0["dims"]):
            notes.append(f"flattened at {st}")
    if rg:
        cores = list(rg["cores"])
        if any("1WNR" in c for c in cores):
            inst = f", {rg['rows']} instances" if rg["rows"] > 1 else ""
            if tg:
                cps = [int(c) for c in tg["copies"] if c.isdigit()]
                if cps and max(cps) > 1:
                    return f"replicated: RAM_1WNR with {'/'.join(map(str, cps))} storage copies (RTL){inst}", notes
                return f"RAM_1WNR core but 1 storage copy in the RTL (ports {'/'.join(tg['ports'])}; not replicated){inst}", notes
            return f"RAM_1WNR core in the report (copies: see the RTL){inst}", notes
        if rg["rows"] > 1 and rg["banks"]:
            return f"partitioned into {rg['rows']} banks in the report (no IR banks)", notes
        if any("LUTRAM" in c for c in cores):
            return "LUTRAM in the report", notes
        if rg["bram"] == 0:
            return "0 BRAM in the report (LUTRAM/registers: Words*Bits < 1024 or ROM)", notes
        if any(c.startswith("ROM") for c in cores) and not s0.get("const"):
            return "ROM in the report", notes
        if rg["words"] != s_words and rg["words"]:
            return f"report words {rg['words']} != source {s_words}", notes
        if rg["bits"] and s_bits is not None and rg["bits"] != [s_bits]:
            return f"report bits {rg['bits']} != source {s_bits}", notes
        return "unchanged through a.o.3 and the report" + (" [flattened]" if notes else ""), notes
    if not has_report:
        return f"alive through a.o.3; no memory table to compare ({why})", notes
    if seen_later:
        return "no memory instance in the report (registers / scalarized / interface)", notes
    return "unknown", notes


# ---------------------------------------------------------------- printing

def reconcile_line(meta):
    """'Vitis BRAM 73 = memory rows 71 + leaf instances 2 (mem1_m_axi_U=2); hls-est 432 (arrays 432)'."""
    rc = meta.get("vitis_reconcile") or {}
    st = meta.get("vitis_status")
    if not isinstance(rc.get("total"), int):
        s = f"Vitis BRAM: no number ({status_text(st, meta.get('vitis_note'))}); memory rows {rc.get('memories')}"
        if meta.get("hlsest_json"):
            s += f"; hls-est total {meta.get('hlsest_total')} (sum over arrays {meta.get('hlsest_sum_groups')})"
        return s
    s = ("" if st == "ok" else f"[{status_text(st, meta.get('vitis_note'))}; the memory tables exist] ")
    s += (f"Vitis BRAM {rc.get('total')} = memory rows {rc.get('memories')} + leaf instances without memory rows "
         f"{rc.get('leaf_instances')}" + (f" ({', '.join(rc['leaf_names'])})" if rc.get("leaf_names") else ""))
    if rc.get("fifo_channels"):
        s += (f" + FIFO channels {rc['fifo_channels']} ({len(rc['fifo_names'])} with BRAM, Storage Report: "
              + ", ".join(rc["fifo_names"][:3]) + (", ..." if len(rc["fifo_names"]) > 3 else "") + ")")
    if rc.get("unexplained"):
        s += f" + UNEXPLAINED {rc['unexplained']}"
    if meta.get("hlsest_json"):
        s += f"; hls-est total {meta.get('hlsest_total')} (sum over arrays {meta.get('hlsest_sum_groups')})"
    return s


def print_rows(rows, meta, brief=False):
    print(f"{meta['key']}  top={meta['top']}  vitis={meta['vitis_status']}"
          + (f" ({meta.get('vitis_note')})" if meta.get("vitis_note") else "") + f" BRAM={meta['vitis_bram_total']}  "
          f"hls-est total={meta['hlsest_total']} ({Path(meta['hlsest_json']).parent.name + '/' + Path(meta['hlsest_json']).name if meta['hlsest_json'] else 'no debug json'})")
    print(f"cache={meta['cache_dir']}  stages={meta['stages_found']}  rtl={meta['rtl_dir'] or 'none'}")
    if meta.get("rtl_check"):
        print(f"rtl check: {meta['rtl_check']}")
    print(reconcile_line(meta))
    if meta.get("hlsest_json"):
        print(f"hls-est pipeline: {meta.get('hlsest_pipeline') or 'unknown (no .err next to the debug JSON)'}")
    print("form cells: <count>x[dims]@bits, C = constant initialiser, D = data initialiser; '-' = absent"
          + ("" if meta.get("vitis_has_report") else "; Vitis BRAM '?' = no memory table (the run failed)"))
    if not rows:
        print(f"no arrays to show: IR stages kept {', '.join(meta['stages_found']) or 'none'}; "
              + ("Vitis memory table empty" if meta.get("vitis_has_report") else
                 f"no Vitis memory table ({status_text(meta['vitis_status'], meta.get('vitis_note'))})")
              + ("" if meta.get("hlsest_json") else "; no hls-est debug JSON"))
        return
    if brief:
        cols = ["array", "kind", "source", "first divergence", "vitis BRAM", "hls-est form", "hls-est BRAM", "hls-est status"]
        table = [{"array": r["array"], "kind": r["kind"], "source": r["forms"]["source"], "first divergence": r["divergence"],
                  "vitis BRAM": r["vitis_bram"] if r["vitis_bram"] is not None else ("-" if meta.get("vitis_has_report") else "?"),
                  "hls-est form": r.get("hlsest_form") or "-",
                  "hls-est BRAM": r["hlsest_bram"] if r["hlsest_bram"] is not None else "-",
                  "hls-est status": r["hlsest_status"] or "-"} for r in rows]
        print(RTL.fmt_table(table, cols, max_w=64))
        notes = [r for r in rows if r["notes"]]
        for r in notes[:12]:
            print(f"  {r['array']}: " + "; ".join(r["notes"])[:200])
        return
    cols = ["array", "kind", "source", "a.o.1", "a.o.2", "a.o.3", "sched", "report", "rtl", "hls-est", "first divergence"]
    table = [{"array": r["array"], "kind": r["kind"], "source": r["forms"]["source"], "a.o.1": r["forms"]["a.o.1"],
              "a.o.2": r["forms"]["a.o.2"], "a.o.3": r["forms"]["a.o.3"], "sched": r["forms"].get("sched", "-"),
              "report": r["vitis"], "rtl": r["rtl"],
              "hls-est": r["hlsest"], "first divergence": r["divergence"]} for r in rows]
    print(RTL.fmt_table(table, cols, max_w=60))
    for r in rows:
        if r["vitis_log"] or r["notes"]:
            print(f"  {r['array']}: " + "; ".join(r["notes"] + r["vitis_log"]))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("key", help="dataset/benchmark")
    ap.add_argument("--vitis", default=str(RESULTS_VITIS))
    ap.add_argument("--hlsest-json", help="hls-est --bram-debug-json file (default: see --run-id)")
    ap.add_argument("--run-id", help="take the debug JSON of this run under ~/hls-est-work/hlsest-logs (default: the newest "
                                     "run that used the harness default pipeline)")
    ap.add_argument("--rtl", help="syn/verilog dir (default: a leftover work dir if rtl_memories.py finds one)")
    ap.add_argument("--json", help="write rows + meta as JSON")
    ap.add_argument("--brief", action="store_true", help="one short line per array")
    ap.add_argument("--no-args", action="store_true", help="hide the top-function argument rows (interfaces)")
    args = ap.parse_args()
    ds, bench = args.key.split("/", 1)
    why = []
    hj = args.hlsest_json or find_debug_json(ds, bench, args.run_id, why)
    if why:
        print(f"note: hls-est debug JSON: {why[0]}", file=sys.stderr)
    rtl = args.rtl
    if rtl is None:
        vdir, how = RTL.find_verilog_dir(args.key)
        rtl = str(vdir) if vdir else None
        if vdir:
            print(f"note: RTL taken from {how}", file=sys.stderr)
    rows, meta = align(args.key, args.vitis, hj, rtl, no_args=args.no_args)
    print_rows(rows, meta, brief=args.brief)
    if args.json:
        with open(args.json, "w") as f:
            json.dump({"meta": meta, "rows": rows}, f, indent=1, sort_keys=True, default=str)
        print(f"wrote {args.json}")


if __name__ == "__main__":
    main()
