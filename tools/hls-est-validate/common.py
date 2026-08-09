"""Shared configuration for the hls-est vs. Vitis HLS validation harness.

Everything runs inside WSL (Ubuntu-22.04).  Vitis HLS 2025.1 is a Windows
install on A: and is driven through cmd.exe; its work directories therefore
live on D: (visible to both sides).
"""
import hashlib
import json
import os
import re
import subprocess
import tempfile
import threading
from pathlib import Path

HERE = Path(__file__).resolve().parent
CIRCT = HERE.parent.parent                       # ~/circt

# ---- target (from D:/HLS/circt/build-test/sweep_workdir/*/hls_config.cfg and
#      build-test/report/*_csynth.rpt: Zynq-7020, 10 ns, Vitis 2025.1) ----------
PART = "xc7z020clg400-1"
CLOCK = "10ns"
FLOW_TARGET = "vivado"
# Extra [hls] config lines.  Peter's existing compilehlskernel.ps1 (which
# produced the regression-gate numbers bicg=13, gesummv=20, ...) disables
# throughput-driven array partitioning; with the 2025.1 default ('auto') plain
# polybench/atax goes from 13 to 68 BRAM because buff_A is split into 64 banks.
EXTRA_HLS_CFG = ["syn.array_partition.throughput_driven=off"]

# ---- Vitis HLS 2025.1 (Windows) ---------------------------------------------
VITIS_WIN_ROOT = r"A:\Vitis\2025.1"
VITIS_SETTINGS_BAT = VITIS_WIN_ROOT + r"\Vitis\settings64.bat"
VITIS_VPP_BAT = VITIS_WIN_ROOT + r"\Vitis\bin\v++.bat"
VITIS_VERSION = "2025.1"
VITIS_INCLUDE_WSL = "/mnt/a/Vitis/2025.1/Vitis/include"   # the real headers
CMD_EXE = "/mnt/c/Windows/System32/cmd.exe"
POWERSHELL_EXE = "/mnt/c/Windows/System32/WindowsPowerShell/v1.0/powershell.exe"

# llvm-dis able to read the 2025.1 bitcode (clang-3.9 based csynth LLVM).
# The 2026.1 Linux one works once its private libs are on LD_LIBRARY_PATH.
LLVM_DIS_CANDIDATES = [
    ("/mnt/a/Vitis/2025.1/tps/lnx64/clang-14.0.0/bin/llvm-dis", {}),   # reads every stage (3.9 and 7.0 producers)
    ("/home/peter/2026.1/lnx64/tools/clang-3.9-csynth/bin/llvm-dis",
     {"LD_LIBRARY_PATH": "/home/peter/2026.1/Model_Composer/lib/lnx64.o:"
                         "/home/peter/2026.1/lib/lnx64.o:"
                         "/home/peter/2026.1/lnx64/tools/clang-3.9-csynth/lib"}),
]
LLVM_DIS_WIN = r"A:\Vitis\2025.1\win64\tools\clang-3.9-csynth\bin\llvm-dis.exe"

# ---- where things go -----------------------------------------------------------
WORK_WIN_ROOT = "D:/HLS/hls-est-vitis/work"          # Vitis work dirs (deleted after harvest)
WORK_WSL_ROOT = "/mnt/d/HLS/hls-est-vitis/work"
CACHE_ROOT = Path.home() / "hls-est-work" / "vitis-cache"   # harvested Vitis artifacts, keyed by hash
RESULTS_DIR = HERE / "results"                        # small JSON/CSV summaries (committed)

# ---- frontend ----------------------------------------------------------------------
# CGEIST_BIN overrides the frontend binary (a private build under test, or a frozen copy, so that
# a reinstall during a long run cannot mix two cgeist versions in one result file).
CGEIST = os.environ.get("CGEIST_BIN") or "/mnt/d/HLS/Polygeist/build/bin/cgeist"
CLANG_RESOURCE_DIR = "/mnt/d/HLS/Polygeist/llvm-project/build/lib/clang/18"
POLYGEIST_TEST_HLS = "/mnt/d/HLS/Polygeist/tools/cgeist/Test/HLS"
SHIM_INCLUDE = POLYGEIST_TEST_HLS + "/Inputs/vitis"   # Polygeist's Vitis header stand-ins
POLYBENCH_UTIL_INCLUDE = "/mnt/d/HLS/Polygeist/tools/cgeist/Test/polybench/utilities"

# The harness default header shim (MEMOS.md M2, decision #8 of 2026-10-10: "Yes use exact class"):
# shim/exactclass, ap_int / ap_fixed as classes around a _BitInt, lowered by cgeist's
# --scalar-wrapper-abi, which the shim's cgeist_flags file supplies. "scalar" (the default
# before W1c: widened builtin ints, ap_fixed as float) and "exact" (_BitInt, no member
# functions) stay selectable with run_hlsest.py --shim.
DEFAULT_SHIM = "exactclass"

# HLS_EST_BIN overrides the binary (e.g. a frozen copy, so that a rebuild
# during a long run cannot mix two builds in one result file).
HLS_EST_DEFAULT = str(CIRCT / "build/clion/bin/hls-est")
HLS_EST = os.environ.get("HLS_EST_BIN") or HLS_EST_DEFAULT

# The canonical hls-est pipeline (CLAUDE.md).  Experiments vary this string.
# --infer-vitis-split-array is not in it (MEMOS.md M1, decision #1 of 2026-10-10): its
# port-pressure partitioning is the td=auto behaviour and the ground truth is td=off. The
# pass stays available (td=auto|off); SPLIT_PIPELINE is the former default, for comparisons.
# DME_FRONT (MEMOS.md M5 recommendation 1 with T8's --inline, "prefix B"; decision #4 of
# 2026-10-10) runs right after the top selection (run_hlsest.py prepends
# --symbol-privatize=exclude=<top> --symbol-dce): Vitis' integer folds and its undefined
# x / 0, then the arrays whose loads reach no output are deleted, as at Vitis' a.o.1.ll.
# The m_axi adapter cost that goes with it is a --bram-analysis default (--bram-maxi-adapters,
# on since W1c). Globals stay globals (no --promote-globals-to-allocas /
# --bram-attribute-globals before OPEN_ISSUES O10 / O17).
# --lower-polygeist-subindex (W3, MEMOS decision #11 under #36) comes first: cgeist passes a
# row argument of a kept `inline off` call (`f(a[k])`) as polygeist.subindex; the pass
# indexes the whole array instead and gives the callee a clone per argument form
# (OPEN_ISSUES O25). `--inline` keeps the calls to `hls.inline_off` callees (VITIS_NOTES N14).
# --mark-constant-fills (W7 item 3, decision #45 under #36) marks the arrays whose every write
# stores a compile-time constant, which Vitis turns into ROMs, before the folds (VITIS_NOTES N26).
# --split-struct-memrefs (W8b, under #36) gives each member of a local array of structs its own
# memref, as Vitis disaggregates it (VITIS_NOTES N29); it is a no-op on modules without such arrays.
DME_FRONT = ("--lower-polygeist-subindex --inline --split-struct-memrefs --mark-constant-fills "
             "--canonicalize --sccp --vitis-fold --dead-memory-elimination")
NO_FRONT_PIPELINE = ("--affine-loop-normalize --auto-pipeline-unroll "
                     "--memory-banking-bram --convert-affine-to-loopschedule --bram-analysis")
DEFAULT_PIPELINE = DME_FRONT + " " + NO_FRONT_PIPELINE
SPLIT_PIPELINE = ("--affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array "
                  "--memory-banking-bram --convert-affine-to-loopschedule --bram-analysis")
HLSEST_TIMEOUT = 120


def wsl_to_win(p):
    """/mnt/d/x/y -> D:/x/y (forward slashes, which Vitis and cmd accept in most places)."""
    p = str(p)
    m = re.match(r"^/mnt/([a-z])/(.*)$", p)
    if m:
        return f"{m.group(1).upper()}:/{m.group(2)}"
    if p.startswith("/home/"):
        return "//wsl.localhost/Ubuntu-22.04" + p
    return p


def win_backslash(p):
    return wsl_to_win(p).replace("/", "\\")


def sha256_of_files(paths, extra=""):
    h = hashlib.sha256()
    for p in sorted(paths):
        p = Path(p)
        h.update(str(p.name).encode())
        h.update(b"\0")
        h.update(p.read_bytes())
        h.update(b"\0")
    h.update(extra.encode())
    return h.hexdigest()


def git_hash(repo=CIRCT):
    try:
        return subprocess.run(["git", "-C", str(repo), "rev-parse", "--short=12", "HEAD"],
                              capture_output=True, text=True, check=True).stdout.strip()
    except Exception:
        return "unknown"


def file_sha256(p, n=16):
    try:
        h = hashlib.sha256()
        with open(p, "rb") as f:
            for chunk in iter(lambda: f.read(1 << 20), b""):
                h.update(chunk)
        return h.hexdigest()[:n]
    except OSError:
        return "unknown"


def hls_est_identity(binary=None):
    """(git, sha256) describing the hls-est binary a run uses.

    The repo HEAD only describes the repo's own build.  A binary given by
    HLS_EST_BIN (a frozen copy) is labelled by a `<binary>.git` sidecar file
    if one exists (first word: the commit it was built from), otherwise as
    unknown; the sha256 of the binary is recorded either way, so two result
    files can be checked for having used the same build.
    """
    binary = str(binary or HLS_EST)
    sha = file_sha256(binary)
    if os.path.realpath(binary) == os.path.realpath(HLS_EST_DEFAULT):
        return git_hash(), sha
    side = Path(binary + ".git")
    if side.exists():
        words = side.read_text().split()
        if words:
            return words[0], sha
    return f"unknown (HLS_EST_BIN={binary})", sha


def load_json(p, default=None):
    p = Path(p)
    if not p.exists():
        return default
    with open(p) as f:
        return json.load(f)


def dump_json(obj, p):
    """Write obj to p as JSON, atomically: into a temporary file of its own in the same directory,
    then os.replace. The temporary name is unique per call, so several processes or threads may
    write the same file (the cgeist md5 memo after a reinstall, for one) and a reader sees one
    complete version, never a mix. (Before, every writer used <p>.tmp.)"""
    p = Path(p)
    p.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(prefix=p.name + ".", suffix=".tmp", dir=str(p.parent))
    try:
        try:
            os.fchmod(fd, 0o644)         # mkstemp's 0600 -> what open() gave before
        except OSError:
            pass
        with os.fdopen(fd, "w") as f:
            json.dump(obj, f, indent=1, sort_keys=True)
        os.replace(tmp, p)
    except BaseException:
        try:
            os.unlink(tmp)
        except OSError:
            pass
        raise


def design_key(d):
    return f"{d['dataset']}/{d['benchmark']}"


_CGEIST_MD5 = {}
_CGEIST_MD5_LOCK = threading.Lock()
CGEIST_MD5_MEMO = Path.home() / "hls-est-work" / "cgeist-md5.json"


def _read_cgeist_md5_memo():
    """The md5 memo as a dict; {} when it is missing, unreadable or not a JSON object. A damaged
    memo only costs one hash: the md5 is recomputed and the memo rewritten."""
    try:
        memo = load_json(CGEIST_MD5_MEMO, {})
    except (OSError, ValueError):
        return {}
    return memo if isinstance(memo, dict) else {}


def _md5_stable(path):
    """(md5, os.stat_result) of the file at path, read through one descriptor; ('', None) when it
    cannot be read or changed while it was read (a copy in progress)."""
    try:
        with open(path, "rb") as f:
            st0 = os.fstat(f.fileno())
            h = hashlib.md5()
            for b in iter(lambda: f.read(1 << 20), b""):
                h.update(b)
            st1 = os.fstat(f.fileno())
    except OSError:
        return "", None
    if (st0.st_size, st0.st_mtime_ns) != (st1.st_size, st1.st_mtime_ns):
        return "", None
    return h.hexdigest(), st0


def cgeist_md5(binary=None):
    """md5 of the cgeist binary (default CGEIST). run_hlsest.py keys its MLIR cache on it, so a
    reinstalled or CGEIST_BIN cgeist never reuses another binary's output (W1c item 1), and
    experiment_pipeline.py's run cache through that key.

    Memoized per process and in ~/hls-est-work/cgeist-md5.json by (real path, size, mtime):
    hashing the 4 GB binary through /mnt/d takes minutes, and a reinstall (rename aside + copy)
    gives a new mtime. The hash and the memo key come from the same open file, and a file that
    changes while it is read is not hashed. A missing or damaged memo is recomputed.

    Returns '' when the binary cannot be read (missing, e.g. in the middle of a reinstall, or
    unreadable, or being written). '' is not memoized, so a later call tries again. A cache key
    must never be formed from '' (it would name no binary): run_hlsest.source_hash refuses it."""
    binary = str(binary or CGEIST)
    with _CGEIST_MD5_LOCK:
        if _CGEIST_MD5.get(binary):
            return _CGEIST_MD5[binary]
        real = os.path.realpath(binary)
        try:
            st = os.stat(real)
        except OSError:
            return ""
        memo_key = f"{real}|{st.st_size}|{st.st_mtime_ns}"
        md5 = _read_cgeist_md5_memo().get(memo_key)
        if not (isinstance(md5, str) and re.fullmatch(r"[0-9a-f]{32}", md5)):
            md5, st = _md5_stable(real)
            if not md5:
                return ""
            memo = _read_cgeist_md5_memo()
            memo[f"{real}|{st.st_size}|{st.st_mtime_ns}"] = md5
            try:
                dump_json(memo, CGEIST_MD5_MEMO)
            except OSError:
                pass                     # the memo is only an optimization
        _CGEIST_MD5[binary] = md5
        return md5


def md5_of_file(path):
    """md5 of a file (identifies the exact cgeist / hls-est binary a run used); '' if unreadable."""
    import hashlib
    try:
        h = hashlib.md5()
        with open(path, "rb") as f:
            for b in iter(lambda: f.read(1 << 20), b""):
                h.update(b)
        return h.hexdigest()
    except OSError:
        return ""
