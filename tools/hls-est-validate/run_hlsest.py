#!/usr/bin/env python3
"""Run cgeist and then hls-est on every design (the prediction side).

    python3 run_hlsest.py [--datasets a,b] [--benchmarks x,y] [-j 8] [--timeout 120]
                          [--pipeline "<hls-est flags>"]
                          [--shim exactclass|exact|scalar|real|polygeist|<dir>]
                          [--out results/hlsest.json] [--force-cgeist] [--debug-json]
                          [--mlir-from <earlier result json>]
                          [--math-costs <cost table json> | --no-math-costs]
                          [--hls-config <configuration json>] [--config-set key.path=value ...]
                          [--load-plugin <lib> ...]

--shim defaults to common.DEFAULT_SHIM = real (MEMOS.md #67; exactclass, the default of MEMOS
decision #8 until W11-adopt, stays selectable): a name is a directory under shim/, "polygeist"
Polygeist's own stand-ins, anything else a path. The shim's cgeist_flags file (exactclass:
--scalar-wrapper-abi) is appended to the cgeist command.
--shim real is no shim: the real Vitis 2025.1 headers (the synthesis tree
common/technology/autopilot, read from the install, never copied) with the Vitis front end's
macros and -include, through cgeist's Xilinx extensions (--xlx-prelude --xlx-headers, clang
-fxlx-bitwidth / -fxlx-apint-promote; MEMOS #39, M12, track W11); see shim/real/README.md. It
needs a cgeist with the W11 Xilinx extensions (the installed one since Polygeist 483ef69c,
MEMOS #66) and stops at once with another binary.

Per design:
  1. cgeist <sources> --function=<top> -S --hls-annotate --raise-scf-to-affine
     --memref-fullrank [<shim>/cgeist_flags] -I <shim> -I <design includes> -o <mlir>
     (cached under ~/hls-est-work/mlir by a hash of the sources, the design's headers, the
     shim's path and every file in it (README included), the shim's cgeist flags and the md5
     of the cgeist binary, so a reinstalled or CGEIST_BIN cgeist never reuses another
     binary's output; a run that would call cgeist stops when that binary cannot be hashed)
  2. hls-est <mlir> --symbol-privatize=exclude=<top> --symbol-dce <pipeline>
     (the privatize/dce pair keeps only the top and what it calls, which is how
     the inlining double count was fixed), with top=<top> added to the pipeline's
     --bram-analysis (MEMOS M7: costs only what the top reaches through calls;
     the same set as the prefix gives, and no warning about several public
     functions). --no-privatize drops both.
--hls-config / --config-set / --load-plugin are passed to every hls-est command
(hls-doc/configuration.md, hls-doc/plugins.md); _meta records the file, its md5, the assignments,
the plugins and the hash of the effective configuration (`hls-est --dump-effective-config`'s
`_hash`), which is also recorded without a file (the defaults' hash), when the binary has the option.
--math-costs (default tools/hls-est-validate/math_costs.json: the cost table is how the
programmer sets the BRAM of the hls:: math cores, one fixed cost per core instance) adds
math-costs=<path> to the pipeline's --bram-analysis, so every math call is priced from the table;
--no-math-costs leaves it out (no math cost, the behaviour before W2). A binary without the option
runs without it (recorded per design as math_costs null).
--mlir-from reuses the MLIR files (and cgeist outcomes) an earlier result file
recorded instead of running cgeist, so two hls-est builds or pipelines can be
compared on byte-identical inputs even after a shim or cgeist change.
Status strings follow CLAUDE.md: ok | cgeist crash | cgeist error: ... |
hls-est error: <status> | hls-est timeout <N>s.
"""
import argparse
import concurrent.futures as cf
import hashlib
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
import threading
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                       # noqa: E402
import designs as D                      # noqa: E402
import run_vitis as RV                   # noqa: E402  (cache_keys: the ground truth's source identity)

LOCK = threading.Lock()
MLIR_ROOT = Path.home() / "hls-est-work" / "mlir"
LOG_ROOT = Path.home() / "hls-est-work" / "hlsest-logs"
CGEIST_TIMEOUT = 600
HDR_EXT = {".h", ".hh", ".hpp", ".hxx", ".inc", ".tcc", ".ipp"}


# The harness default cost table of the hls:: math cores (the programmer edits it).
DEFAULT_MATH_COSTS = Path(__file__).resolve().parent / "math_costs.json"


def add_math_costs_args(ap):
    """--math-costs / --no-math-costs (run_hlsest.py and sweep_hlsfactory_v2.py)."""
    ap.add_argument("--math-costs", default=str(DEFAULT_MATH_COSTS),
                    help="cost table of the hls:: math cores, passed as --bram-analysis math-costs= "
                         f"(default {DEFAULT_MATH_COSTS.name})")
    ap.add_argument("--no-math-costs", action="store_true",
                    help="no math-core cost (leave math-costs= out)")


def resolve_math_costs(args):
    """args.math_costs: the absolute path of the cost table, or None with --no-math-costs."""
    if args.no_math_costs:
        args.math_costs = None
    elif not Path(args.math_costs).is_file():
        sys.exit(f"--math-costs {args.math_costs}: no such file (--no-math-costs to run without)")
    else:
        args.math_costs = str(Path(args.math_costs).resolve())


def resolve_shim(s):
    if s in ("polygeist", "", None):
        return Path(C.SHIM_INCLUDE)
    p = Path(__file__).resolve().parent / "shim" / s
    if p.is_dir():
        return p
    return Path(s).resolve()


def check_shim_supported(shim):
    """Stop before any design runs when the shim needs cgeist options the binary lacks (shim/real:
    --xlx-headers, only in a cgeist of Polygeist branch w11-integrate) or include directories that
    are missing (the Vitis install); otherwise every design would fail with the same error."""
    flags = shim_cgeist_flags(shim)
    for i, f in enumerate(flags):
        if f == "-I" and i + 1 < len(flags) and not Path(flags[i + 1]).is_dir():
            sys.exit(f"shim {shim}: include directory {flags[i + 1]} does not exist")
    needed = [f for f in flags if f in ("--xlx-headers", "--xlx-prelude")]
    if not needed:
        return
    try:
        out = subprocess.run([C.CGEIST, "--help-hidden"], capture_output=True, text=True,
                             errors="replace", timeout=300).stdout
    except (OSError, subprocess.SubprocessError) as e:
        sys.exit(f"shim {shim}: cannot run {C.CGEIST} --help-hidden: {e}")
    missing = [f for f in needed if f not in out]
    if missing:
        sys.exit(f"shim {shim} needs cgeist {' '.join(missing)}, which {C.CGEIST} does not have "
                 "(build Polygeist branch w11-integrate and point CGEIST_BIN at it)")
    # The clang the cgeist embeds must accept the cc1 options the shim passes (-fxlx-bitwidth
    # comes from the llvm-project patch of branch w11-xlx-bitwidth; a cgeist built against an
    # unpatched LLVM has --xlx-headers but rejects it): compile a probe with the shim's flags.
    if "-fxlx-bitwidth" in flags:
        err = probe_shim_compile(shim, flags)
        if err:
            sys.exit(f"shim {shim}: {C.CGEIST} cannot compile with the shim's flags ({err}); it needs "
                     "a clang with -fxlx-bitwidth (llvm-project branch w11-xlx-bitwidth)")


def probe_shim_compile(shim, flags):
    """'' when C.CGEIST compiles a C++ probe that uses the Xilinx bitwidth attribute with the shim's
    flags, else the first error line."""
    import tempfile
    probe = "typedef int __attribute__((bitwidth(7))) i7;\ni7 f(i7 a) { return a; }\n"
    with tempfile.TemporaryDirectory(prefix="shimprobe") as d:
        src = Path(d) / "probe.cpp"
        src.write_text(probe)
        cmd = [C.CGEIST, str(src), "--function=*", "-S", *flags,
               f"-resource-dir={C.CLANG_RESOURCE_DIR}", "-I", str(shim), "-o", str(Path(d) / "probe.mlir")]
        try:
            r = subprocess.run(cmd, capture_output=True, text=True, errors="replace", timeout=300)
        except (OSError, subprocess.SubprocessError) as e:
            return str(e)
        if r.returncode == 0 and (Path(d) / "probe.mlir").exists():
            return ""
        lines = [l for l in (r.stderr or "").splitlines() if l.strip()]
        errors = [l for l in lines if "error" in l.lower() or "unknown" in l.lower()]
        return ((errors or lines or [f"exit {r.returncode}"])[0]).strip()[:300]


# ---------------------------------------------------------------- cgeist ----

def shim_cgeist_flags(shim):
    """Extra cgeist flags a shim needs, from <shim dir>/cgeist_flags (whitespace-separated,
    '#' starts a comment); e.g. shim/exactclass needs --scalar-wrapper-abi. [] without the file."""
    p = Path(shim) / "cgeist_flags"
    if not p.is_file():
        return []
    flags = []
    for line in p.read_text().splitlines():
        flags += line.split("#", 1)[0].split()
    return flags


# What Vitis 2025.1's front end is given beyond the design's own flags (VITIS_NOTES N19, OPEN_ISSUES
# O30 / O31): the synthesis macros, and the language standard (C++ sources get no -std= and compile
# as C++14, the hls-llvm-project clang's default gnu++14; C sources get -std=gnu99).  On by default
# since W8b measured it (MEMOS decision #54: no estimate of the v2 catalogue or the harness subset
# changes, 16 more v2 designs compile); VITIS_FRONTEND=0 gives the command and cache keys of before.
VITIS_FRONTEND_DEFINES = ("__SYNTHESIS__", "__VITIS_HLS__", "__HLS_SYN__", "AESL_SYN")
VITIS_FRONTEND = os.environ.get("VITIS_FRONTEND", "1") not in ("0", "off", "no", "")


def vitis_frontend_flags(d):
    """The macros and -std= flag Vitis' front end adds for design d ([] when VITIS_FRONTEND is off).
    -std= only when all sources are one language: a single flag cannot serve C and C++ at once, and
    clang rejects a C++ standard for a C file."""
    if not VITIS_FRONTEND:
        return []
    flags = ["-D" + m for m in VITIS_FRONTEND_DEFINES]
    langs = {"c" if s.endswith(".c") else "c++" for s in d["sources"]}
    if langs == {"c"}:
        flags.append("-std=gnu99")
    elif langs == {"c++"}:
        flags.append("-std=gnu++14")
    return flags


def cgeist_cmd(d, shim, out, func):
    cmd = [C.CGEIST, *d["sources"], f"--function={func}", "-S", "--hls-annotate",
           "--raise-scf-to-affine", "--memref-fullrank", *shim_cgeist_flags(shim),
           f"-resource-dir={C.CLANG_RESOURCE_DIR}", *vitis_frontend_flags(d), "-I", str(shim), "-I", "."]
    for inc in d.get("includes", []):
        if inc != ".":
            cmd += ["-I", inc]
    if d["dataset"] == "polybench_pragmas":
        cmd += ["-I", C.POLYBENCH_UTIL_INCLUDE]
    for df in d.get("defines", []):
        cmd += ["-D" + df]
    cmd += ["-o", str(out)]
    return cmd


class CgeistUnhashable(RuntimeError):
    """The cgeist binary cannot be hashed, so no MLIR cache key can name it."""


def cgeist_md5_or_raise():
    """C.cgeist_md5(), or CgeistUnhashable when the binary cannot be read. Before W1c the MLIR
    cache key named no binary, so a cgeist reinstall silently reused the previous binary's MLIR
    (the W1a scalar runs read 2026-10-09 MLIR, CHANGELOG W1c item 1); a key built from an empty
    md5 would do the same (W1c's x_w1a run, started during a reinstall, has _meta.cgeist_md5 '')."""
    md5 = C.cgeist_md5()
    if not md5:
        raise CgeistUnhashable(
            f"cannot hash the cgeist binary {C.CGEIST} (missing, unreadable or being replaced); "
            "no MLIR cache key without its md5. Retry once it is in place, or set CGEIST_BIN to a copy")
    return md5


def source_hash(d, shim):
    files = [Path(d["dir"]) / s for s in d["sources"]]
    for p in Path(d["dir"]).rglob("*"):
        if p.is_file() and p.suffix.lower() in HDR_EXT:
            files.append(p)
    for p in Path(shim).glob("*"):
        if p.is_file():
            files.append(p)
    extra = "|".join([d["top"], " ".join(d.get("includes", [])), " ".join(d.get("defines", [])),
                      str(shim), "cgeist-v3"])
    flags = shim_cgeist_flags(shim)
    if flags:   # only then, so that the keys of shims without cgeist_flags do not change
        extra += "|cgeist-flags:" + " ".join(flags)
    fe = vitis_frontend_flags(d)
    if fe:      # likewise: VITIS_FRONTEND=0 keeps the keys from before W8b
        extra += "|vitis-frontend:" + " ".join(fe)
    extra += "|cgeist-md5:" + cgeist_md5_or_raise()
    return C.sha256_of_files(files, extra)[:16]


def select_designs(datasets="", benchmarks=""):
    """The designs of the comma-separated datasets / benchmarks (all when empty)."""
    designs = D.load_designs()
    if datasets:
        ds = set(datasets.split(","))
        designs = [d for d in designs if d["dataset"] in ds]
    if benchmarks:
        bs = set(benchmarks.split(","))
        designs = [d for d in designs if d["benchmark"] in bs]
    return designs


def inputs_digest(designs, shim):
    """sha256 over the design keys and, per design, its MLIR cache key (source_hash: sources,
    headers, shim files and cgeist flags, cgeist md5) or, for an mlir-only design, its MLIR file:
    everything a run of these designs reads except the hls-est binary and the pipeline.
    experiment_pipeline.py keys its run cache on it. Raises CgeistUnhashable like source_hash."""
    h = hashlib.sha256()
    for d in sorted(designs, key=C.design_key):
        if d.get("mode") == "mlir-only":
            part = "mlir:" + C.file_sha256(d["mlir"], 64)
        elif d.get("sources"):
            part = "src:" + source_hash(d, shim)
        else:
            part = "no-sources"
        h.update(f"{C.design_key(d)}\0{part}\0".encode())
    return h.hexdigest()


def mlir_from_record(d, args):
    """The --mlir-from record that replaces cgeist for design d, or None (cgeist runs)."""
    prev = (args.mlir_from_records or {}).get(C.design_key(d))
    if prev and prev.get("mlir") and Path(prev["mlir"]).exists():
        return prev
    if prev and str(prev.get("cgeist_status", "ok")) != "ok":
        return prev
    return None


def needs_cgeist(d, args):
    return d.get("mode") != "mlir-only" and bool(d.get("sources")) and mlir_from_record(d, args) is None


def run_cgeist(d, shim, force=False):
    """Returns (status, mlir_path_or_None, note)."""
    if d.get("mode") == "mlir-only":
        return "ok", Path(d["mlir"]), "mlir-only"
    if not d.get("sources"):
        return "cgeist error: no sources", None, ""
    key = source_hash(d, shim)
    out = MLIR_ROOT / d["dataset"] / f"{d['benchmark']}.{key}.mlir"
    meta = out.with_suffix(".status")
    if out.exists() and meta.exists() and not force:
        st = meta.read_text().strip()
        return (st, out if st == "ok" else None, "cached")
    out.parent.mkdir(parents=True, exist_ok=True)
    log = out.with_suffix(".cgeist.log")
    status, note = "ok", ""
    # Every attempt's command and output, so that a failed by-name retry does not hide why the '*'
    # attempt failed (OPEN_ISSUES O28: the log held only the retry's empty output).
    attempts = ""
    # The HLSFactory lit tests were generated with --function='*'; a C++ top
    # given by name can silently produce an empty module.  Try '*' first.
    for func in ("*", d["top"]):
        cmd = cgeist_cmd(d, shim, out, func)
        try:
            p = subprocess.run(C.mem_limited(cmd), cwd=d["dir"], capture_output=True, text=True,
                               errors="replace", timeout=CGEIST_TIMEOUT)
        except subprocess.TimeoutExpired:
            status, note = "cgeist timeout", f"{CGEIST_TIMEOUT}s"
            break
        this = " ".join(cmd) + "\n\n" + p.stdout + "\n--- stderr ---\n" + p.stderr
        attempts = this + ("\n\n--- earlier attempt ---\n" + attempts if attempts else "")
        log.write_text(attempts)    # the latest attempt first: its command is the log's first line
        if p.returncode == 0 and out.exists() and out.stat().st_size > 0                 and re.search(r"func\.func\s", out.read_text(errors="replace")):
            sanitize_mlir(out)
            status, note = "ok", f"--function={func}"
            break
        if p.returncode == 0:
            status, note = "cgeist error: empty module (no functions emitted)", f"--function={func}"
            continue
        if p.returncode != 0 and C.out_of_memory(p.stderr):
            status = f"cgeist out of memory (> {C.MEM_LIMIT_GB:g} GB)"
        elif p.returncode < 0 or "Stack dump" in p.stderr or "PLEASE submit a bug report" in p.stderr:
            status = "cgeist crash"
        else:
            errs = [l for l in p.stderr.splitlines() if "error:" in l]
            status = "cgeist error: " + (errs[0].strip()[:200] if errs else f"exit {p.returncode}")
        note = f"--function={func}"
        if func == "*":
            continue          # retry with the top function by name
        break
    meta.write_text(status)
    if status != "ok" and out.exists():
        out.unlink()
    return status, (out if status == "ok" else None), note


def sanitize_mlir(path):
    """cgeist (LLVM 18) emits `module attributes {dlti.dl_spec = ..., llvm.data_layout = ...}`
    in a syntax the LLVM-23 MLIR parser of hls-est rejects; the data layout is
    irrelevant to BRAM estimation, so drop the module attribute dictionary."""
    p = Path(path)
    txt = p.read_text(errors="replace")
    new = re.sub(r"^module attributes \{.*\} \{$", "module {", txt, count=1, flags=re.M)
    if new != txt:
        p.write_text(new)


# ------------------------------------------------------------- top in MLIR ---

def mlir_functions(mlir_path):
    txt = Path(mlir_path).read_text(errors="replace")
    return re.findall(r"func\.func\s+(?:private\s+)?@([A-Za-z0-9_$.]+)", txt)


def demangle(names):
    try:
        p = subprocess.run(["c++filt"], input="\n".join(names), capture_output=True, text=True, timeout=30)
        return dict(zip(names, p.stdout.splitlines()))
    except Exception:
        return {n: n for n in names}


def find_top(mlir_path, top):
    funcs = mlir_functions(mlir_path)
    if top in funcs:
        return top, "exact"
    dm = demangle(funcs)
    for n in funcs:
        base = dm.get(n, n).split("(")[0].split("::")[-1].strip()
        if base == top:
            return n, "demangled"
    m = re.compile(r"^_Z(?:N\d*)?(\d+)(" + re.escape(top) + r")(?![A-Za-z0-9_])")
    for n in funcs:
        mm = m.match(n)
        if mm and int(mm.group(1)) == len(top):
            return n, "mangled"
    if len(funcs) == 1:
        return funcs[0], "single"
    return (funcs[-1] if funcs else None), "last"


# ---------------------------------------------------------------- hls-est ----

BLOCK_RE = re.compile(r"^(memref\.(?:alloca|global|arg)[^\n]*)$", re.M)


def parse_hlsest_output(text):
    """Text report: one block per memref followed by 'Total BRAM: N'."""
    mems = []
    cur = None
    total = None
    for line in text.splitlines():
        m = re.match(r"^(memref\.\w+)\s+(.*)$", line)
        if m and not line.startswith(" "):
            cur = {"op": m.group(1), "head": m.group(2).strip(), "kind": None, "bram": None, "detail": []}
            loc = re.search(r'loc\("([^"]*)":(\d+):(\d+)\)', line)
            if loc:
                cur["loc"] = [loc.group(1), int(loc.group(2)), int(loc.group(3))]
            nm = re.search(r"@(\S+)", m.group(2))
            cur["name"] = nm.group(1) if nm and not m.group(2).startswith("@ loc") else None
            vn = re.search(r'varname\s*=\s*"?([A-Za-z0-9_]+)"?', line)
            if vn:
                cur["varname"] = vn.group(1)
            mems.append(cur)
            continue
        m = re.match(r"^\s+kind=(\S+)\s+bram=(\d+)", line)
        if m and cur is not None:
            cur["kind"], cur["bram"] = m.group(1), int(m.group(2))
            continue
        m = re.match(r"^\s*Total BRAM:\s*(\d+)", line)
        if m:
            total = int(m.group(1))
            continue
        if cur is not None and line.startswith("    "):
            cur["detail"].append(line.strip())
    return total, mems


_TOP_SUPPORT = {}
_TOP_LOCK = threading.Lock()


def bram_top_supported(binary):
    """Whether this hls-est build has --bram-analysis's top= option (from its --help), so that a
    frozen binary older than the option still runs (it then gets the prefix alone)."""
    return bram_option_supported(binary, "top")


def bram_option_supported(binary, option):
    """Whether this hls-est build's --bram-analysis has the pass option `option` (top,
    math-costs, ...), read from its --help once per binary."""
    key = (binary, option)
    with _TOP_LOCK:
        if key not in _TOP_SUPPORT:
            ok = False
            try:
                out = subprocess.run([binary, "--help"], capture_output=True, text=True, errors="replace",
                                     timeout=60).stdout
                lines = out.splitlines()
                for i, line in enumerate(lines):
                    if re.match(r"\s+--bram-analysis\s+-", line):
                        ind = len(line) - len(line.lstrip())
                        for m in lines[i + 1:]:
                            s = m.lstrip()
                            if s.startswith("--") and len(m) - len(s) <= ind:
                                break
                            if s.startswith(f"--{option}="):
                                ok = True
                        break
            except (OSError, subprocess.SubprocessError):
                ok = False
            _TOP_SUPPORT[key] = ok
        return _TOP_SUPPORT[key]


def with_top(args, top_fn):
    """The pipeline's --bram-analysis with top=<top_fn> (MEMOS M7). A --bram-analysis that
    already has options keeps them (one argv element: "--bram-analysis=<opts> top=<fn>");
    one that already names a top is left alone."""
    out = []
    for a in args:
        if a == "--bram-analysis":
            a = f"--bram-analysis=top={top_fn}"
        elif a.startswith("--bram-analysis=") and not re.search(r"(^|[= ])top=", a[len("--bram-analysis="):]):
            a = f"{a} top={top_fn}"
        out.append(a)
    return out


def with_bram_option(args, option):
    """The pipeline's --bram-analysis with the pass option `option` ("math-costs=<path>") added
    (one argv element, as with_top); an option of that name already given is left alone."""
    name = option.split("=", 1)[0]
    out = []
    for a in args:
        if a == "--bram-analysis":
            a = f"--bram-analysis={option}"
        elif a.startswith("--bram-analysis=") and not re.search(rf"(^|[= ]){re.escape(name)}=",
                                                                 a[len("--bram-analysis="):]):
            a = f"{a} {option}"
        out.append(a)
    return out


# The configuration arguments of every hls-est command (--hls-config, --config-set, --load-plugin;
# set by main from the command line).
CONFIG_ARGS = []


def config_args(args):
    """The hls-est arguments that select the configuration and load plugins."""
    out = [f"--load-plugin={lib}" for lib in args.load_plugin]
    if args.hls_config:
        out.append(f"--hls-config={Path(args.hls_config).resolve()}")
    for a in args.config_set:
        out += ["--config-set", a]
    return out


def effective_config_hash(cfg_args):
    """The `_hash` of `hls-est <cfg_args> --dump-effective-config` (None when the binary has no
    such option, or the configuration does not load: then every design fails with the reason)."""
    try:
        p = subprocess.run([C.HLS_EST, *cfg_args, "--dump-effective-config"], capture_output=True,
                           text=True, errors="replace", timeout=120, stdin=subprocess.DEVNULL)
    except (OSError, subprocess.TimeoutExpired):
        return None
    for text in (p.stderr, p.stdout):
        try:
            return json.loads(text).get("_hash")
        except (ValueError, AttributeError):
            m = re.search(r'"_hash":\s*"([0-9a-f]+)"', text)
            if m:
                return m.group(1)
    return None


def run_hlsest(mlir, top_fn, pipeline, timeout, log_prefix, privatize=True, debug_json=None,
               math_costs=None):
    """... math_costs: the cost table to add as --bram-analysis math-costs= (None: none); the
    result records the one actually passed (None also when the binary lacks the option)."""
    cmd = [C.HLS_EST, str(mlir)]
    args = pipeline.split()
    if privatize and top_fn:
        cmd += [f"--symbol-privatize=exclude={top_fn}", "--symbol-dce"]
        if bram_top_supported(C.HLS_EST):
            args = with_top(args, top_fn)
    applied = None
    if math_costs and bram_option_supported(C.HLS_EST, "math-costs"):
        args = with_bram_option(args, f"math-costs={math_costs}")
        applied = str(math_costs)
    cmd += args
    cmd += CONFIG_ARGS
    if debug_json:
        cmd += [f"--bram-debug-json={debug_json}"]
    cmd += ["-o", "/dev/null"]
    t0 = time.time()
    try:
        p = subprocess.run(C.mem_limited(cmd), capture_output=True, text=True, errors="replace",
                           timeout=timeout)
    except subprocess.TimeoutExpired:
        return {"status": f"hls-est timeout {timeout}s", "elapsed_s": timeout, "cmd": shlex.join(cmd)}
    el = time.time() - t0
    Path(log_prefix + ".out").write_text(p.stdout)
    Path(log_prefix + ".err").write_text(shlex.join(cmd) + "\n\n" + p.stderr)
    total, mems = parse_hlsest_output(p.stdout + "\n" + p.stderr)
    # pipeline_full = every pass actually run, incl. the per-design top-selection prefix
    # (--symbol-privatize/--symbol-dce) and --bram-analysis's top=.  Re-run a case from
    # `cmd`/`pipeline_full` (shell-quoted: an option list with a space is one argument), never
    # from `pipeline` alone: without the prefix uncalled public functions are costed too (O12).
    full = shlex.join(a for a in cmd[2:] if a not in ("-o", "/dev/null"))
    r = {"elapsed_s": round(el, 2), "cmd": shlex.join(cmd), "pipeline_full": full, "total_bram": total,
         "memrefs": mems, "exit": p.returncode, "math_costs": applied}
    if p.returncode != 0 and C.out_of_memory(p.stderr):
        r["status"] = f"hls-est out of memory (> {C.MEM_LIMIT_GB:g} GB)"
    elif p.returncode < 0 or p.returncode > 1 and ("Stack dump" in p.stderr or "Aborted" in p.stderr or "Assertion" in p.stderr):
        r["status"] = "hls-est error: crash"
        a = re.search(r"Assertion `([^']*)' failed", p.stderr)
        r["note"] = (a.group(0) if a else p.stderr.strip().splitlines()[-1] if p.stderr.strip() else "")[:200]
    elif p.returncode != 0:
        errs = [l for l in p.stderr.splitlines() if "error:" in l]
        r["status"] = "hls-est error: " + (errs[0].split("error:", 1)[1].strip()[:160] if errs else f"exit {p.returncode}")
    elif total is None:
        r["status"] = "hls-est error: no total"
    else:
        r["status"] = "ok"
    if debug_json and Path(debug_json).exists():
        r["debug_json"] = debug_json
    return r


def process(d, args, shim, run_id):
    r = {"dataset": d["dataset"], "benchmark": d["benchmark"], "top": d["top"], "mode": d.get("mode"),
         "pipeline": args.pipeline, "shim": str(shim)}
    if d.get("sources") and d.get("mode") != "mlir-only":
        try:
            # the Vitis cache keys of this record (both --td): compare.py compares a design only with a
            # ground-truth entry synthesised from the same sources
            r["vitis_keys"] = RV.cache_keys(d)
        except OSError as e:
            r["vitis_keys_error"] = repr(e)[:200]
    prev = mlir_from_record(d, args)
    if prev and prev.get("mlir") and Path(prev["mlir"]).exists():
        st, mlir, note = "ok", Path(prev["mlir"]), f"from {args.mlir_from}"
    elif prev:
        st, mlir, note = prev["cgeist_status"], None, f"from {args.mlir_from}"
    else:
        st, mlir, note = run_cgeist(d, shim, args.force_cgeist)
    r["cgeist_status"], r["cgeist_note"] = st, note
    if st != "ok":
        r["status"] = st
        return r
    r["mlir"] = str(mlir)
    top_fn, rule = find_top(mlir, d["top"])
    r["top_fn"], r["top_rule"] = top_fn, rule
    if rule in ("single", "last") and d["top"] and d["top"] not in (top_fn or ""):
        # The design's top is not among the MLIR functions: the fallback function (a helper such
        # as ap_detail::bits::val) is not the design, so its estimate is no estimate (W8b review:
        # three designs reported ok with BRAM 0). make_hlsfactory_report.py tells whether the top
        # is defined in the sources at all (top-not-found / top-not-in-sources).
        r["status"] = "top not found"
        r["note"] = f"top {d['top']!r} is not among the MLIR functions (fallback '{rule}' would pick {top_fn!r})"
        return r
    log_prefix = str(LOG_ROOT / run_id / f"{d['dataset']}__{d['benchmark']}")
    Path(log_prefix).parent.mkdir(parents=True, exist_ok=True)
    # Always emit the per-memref debug JSON: compare.py needs it to match arrays by name.
    dbg = log_prefix + ".debug.json" if not args.no_debug_json else None
    hr = run_hlsest(mlir, top_fn, args.pipeline, args.timeout, log_prefix,
                    privatize=not args.no_privatize, debug_json=dbg,
                    math_costs=getattr(args, "math_costs", None))
    r.update(hr)
    return r


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--datasets", default="")
    ap.add_argument("--benchmarks", default="")
    ap.add_argument("-j", type=int, default=8)
    ap.add_argument("--timeout", type=int, default=C.HLSEST_TIMEOUT)
    ap.add_argument("--pipeline", default=C.DEFAULT_PIPELINE)
    ap.add_argument("--shim", default=C.DEFAULT_SHIM,
                    help=f"header shim (default {C.DEFAULT_SHIM}; scalar / exact / real (the real Vitis headers, "
                         "needs a W11 cgeist) / polygeist / a directory)")
    ap.add_argument("--out", default=str(C.RESULTS_DIR / "hlsest.json"))
    ap.add_argument("--run-id", default=None)
    ap.add_argument("--force-cgeist", action="store_true")
    ap.add_argument("--mlir-from", default=None,
                    help="earlier run_hlsest result json: reuse its MLIR files instead of running cgeist")
    ap.add_argument("--no-privatize", action="store_true")
    ap.add_argument("--debug-json", action="store_true", help="(default now; kept for compatibility)")
    ap.add_argument("--no-debug-json", action="store_true")
    ap.add_argument("--quiet", action="store_true")
    add_math_costs_args(ap)
    ap.add_argument("--hls-config", default=None,
                    help="hls-est configuration file (hls-doc/configuration.md); default: none (the "
                         "compiled-in xc7z020 + Vitis 2025.1 defaults)")
    ap.add_argument("--config-set", action="append", default=[], metavar="KEY.PATH=VALUE",
                    help="one configuration assignment, passed as hls-est --config-set (repeatable)")
    ap.add_argument("--load-plugin", action="append", default=[], metavar="LIB",
                    help="an hls-est plugin library (hls-doc/plugins.md; repeatable)")
    ap.add_argument("--catalog", choices=D.CATALOGS, default=None,
                    help="design catalogue (designs.py): 'v2' (the HLSFactory 1.1.0 tree, default) or "
                         "'polygeist' (the Polygeist lit copies; $HLS_EST_CATALOG changes the default)")
    args = ap.parse_args()

    shim = resolve_shim(args.shim)
    check_shim_supported(shim)
    resolve_math_costs(args)
    args.mlir_from_records = None
    if args.mlir_from:
        prev = C.load_json(args.mlir_from, {}) or {}
        args.mlir_from_records = {k: v for k, v in prev.items() if k != "_meta"}
    catalog = args.catalog or D.default_catalog()
    designs = D.load_designs(catalog=catalog)
    if args.datasets:
        ds = set(args.datasets.split(","))
        designs = [d for d in designs if d["dataset"] in ds]
    if args.benchmarks:
        bs = set(args.benchmarks.split(","))
        designs = [d for d in designs if d["benchmark"] in bs]
    n_cgeist = sum(1 for d in designs if needs_cgeist(d, args))
    if n_cgeist:
        try:
            cgeist_md5_or_raise()
        except CgeistUnhashable as e:
            sys.exit(f"run_hlsest.py: {e} ({n_cgeist} designs would run cgeist)")
    CONFIG_ARGS[:] = config_args(args)
    run_id = args.run_id or time.strftime("%Y%m%d-%H%M%S")
    ghash, bsha = C.hls_est_identity()
    results = {"_meta": {"pipeline": args.pipeline, "shim": str(shim), "hls_est_git": ghash,
                         "cgeist": C.CGEIST, "cgeist_md5": C.cgeist_md5(),
                         "polygeist_head": C.git_hash(Path(C.CGEIST).resolve().parents[2]),
                         "hls_est_sha256": bsha, "mlir_from": args.mlir_from,
                         "top_passes": ("none" if args.no_privatize else
                                        "--symbol-privatize=exclude=<top> --symbol-dce prepended per design; "
                                        + ("top=<top> on --bram-analysis" if bram_top_supported(C.HLS_EST)
                                         else "no top= (this hls-est build has no such option)")),
                         "timeout": args.timeout, "run_id": run_id, "hls_est": C.HLS_EST,
                         "math_costs": args.math_costs,
                         "vitis_frontend": VITIS_FRONTEND,
                         "math_costs_md5": C.md5_of_file(args.math_costs) if args.math_costs else None,
                         "math_costs_applied": bool(args.math_costs) and
                                               bram_option_supported(C.HLS_EST, "math-costs")}}
    results["_meta"].update({
        "hls_config": str(Path(args.hls_config).resolve()) if args.hls_config else None,
        "hls_config_md5": C.md5_of_file(args.hls_config) if args.hls_config else None,
        "config_set": list(args.config_set),
        "load_plugin": [{"path": lib, "md5": C.md5_of_file(lib)} for lib in args.load_plugin],
        "config_hash": effective_config_hash(CONFIG_ARGS),
        "config_args": shlex.join(CONFIG_ARGS),
    })
    results["_meta"]["catalog"] = (f"{catalog} ({D.hlsfactory_root()})" if catalog != "polygeist"
                                   else catalog)
    if not args.quiet:
        print(f"{len(designs)} designs; pipeline: {args.pipeline}; shim: {shim}; git {ghash}", flush=True)
    done = 0
    with cf.ThreadPoolExecutor(max_workers=args.j) as ex:
        futs = {ex.submit(process, d, args, shim, run_id): d for d in designs}
        for f in cf.as_completed(futs):
            d = futs[f]
            try:
                r = f.result()
            except Exception as e:  # noqa: BLE001
                r = {"dataset": d["dataset"], "benchmark": d["benchmark"], "status": "harness error",
                     "note": repr(e)[:300]}
            done += 1
            with LOCK:
                results[C.design_key(d)] = r
            if not args.quiet:
                print(f"[{done}/{len(designs)}] {C.design_key(d):50s} {r.get('status', ''):40.40s} "
                      f"BRAM={r.get('total_bram')} {r.get('elapsed_s', '')}s", flush=True)
    C.dump_json(results, args.out)
    n_ok = sum(1 for k, r in results.items() if k != "_meta" and r.get("status") == "ok")
    print(f"done: {n_ok} ok of {len(results) - 1} -> {args.out}")


if __name__ == "__main__":
    main()
