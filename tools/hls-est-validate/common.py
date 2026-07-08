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
CGEIST = "/mnt/d/HLS/Polygeist/build/bin/cgeist"
CLANG_RESOURCE_DIR = "/mnt/d/HLS/Polygeist/llvm-project/build/lib/clang/18"
POLYGEIST_TEST_HLS = "/mnt/d/HLS/Polygeist/tools/cgeist/Test/HLS"
SHIM_INCLUDE = POLYGEIST_TEST_HLS + "/Inputs/vitis"   # Polygeist's Vitis header stand-ins
POLYBENCH_UTIL_INCLUDE = "/mnt/d/HLS/Polygeist/tools/cgeist/Test/polybench/utilities"

# HLS_EST_BIN overrides the binary (e.g. a frozen copy, so that a rebuild
# during a long run cannot mix two builds in one result file).
HLS_EST = os.environ.get("HLS_EST_BIN") or str(CIRCT / "build/clion/bin/hls-est")

# The canonical hls-est pipeline (CLAUDE.md).  Experiments vary this string.
DEFAULT_PIPELINE = ("--affine-loop-normalize --auto-pipeline-unroll --infer-vitis-split-array "
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


def load_json(p, default=None):
    p = Path(p)
    if not p.exists():
        return default
    with open(p) as f:
        return json.load(f)


def dump_json(obj, p):
    p = Path(p)
    p.parent.mkdir(parents=True, exist_ok=True)
    tmp = p.with_suffix(p.suffix + ".tmp")
    with open(tmp, "w") as f:
        json.dump(obj, f, indent=1, sort_keys=True)
    os.replace(tmp, p)


def design_key(d):
    return f"{d['dataset']}/{d['benchmark']}"
