#!/usr/bin/env python3
"""HLSFactory 1.1.0 ("v2") design catalogue for the hls-est validation harness.

designs.load_hlsfactory_v2() (and designs.load_designs(catalog="v2")) build one design record per
HLSFactory design straight from the framework tree (default /mnt/d/HLSFactory_v2/HLSFactory, or
$HLSFACTORY_ROOT) instead of from the Polygeist lit copies (tools/cgeist/Test/HLS/hlsfactory, harvested
from an older HLSFactory by its harvest.py).

Design discovery, under hlsfactory/hls_dataset_sources/<dataset>/...:
  1. a directory with hlsfactory.toml is a design (HLSFactory 1.1: framework.DesignDataset.from_dir and
     design_config.py, whose validation rules read_design_config() below repeats); the VitisHLSSynthFlow
     setting synth_tcl names its synthesis script.  A design without that flow is listed as skipped.
  2. otherwise a directory with dataset_hls.tcl (the HLSFactory convention before the toml files; the toml
     migration covers 8 of the 23 dataset directories) is a design synthesized by that script.
  3. otherwise every Tcl script in a directory that names a top (set_top) and runs csynth_design, and that no
     other design script sources (hp_fft_hls/common.tcl is the library its 16 variants source), is a design:
     the class projects, rosetta, hlsyn-vitis and WIP have no dataset_hls.tcl (the rule the Polygeist
     harvest used).  Scripts of one directory that reach the same top and sources are one design.
  4. a script with @NAME@ placeholders is a template.  TEMPLATE_RULES expands the ones whose dataset
     documents the generation (auto_ntt: one project per cpp/<task>.cpp); any other is listed as skipped.

The synthesis script is evaluated by TclSubset, a small Tcl interpreter (set/list/expr/if/foreach/proc/
source/file/glob/string, ...) in which the Vitis commands only record what they are given: set_top,
add_files (-tb, -cflags), set_part, create_clock, open_solution -flow_target, config_*, set_directive_*.
Nothing is executed (exec, file delete etc. are recorded no-ops).  Unknown commands return "" and an
error in one top-level command is recorded and the next command runs, so a script that only Vitis can run
completely still yields its top and files.

Design sources = the add_files entries without -tb (directories expand to their C/C++ files; a missing file
is looked up by name in the design tree, as the harvest did); with none, every C/C++ file of the design
tree whose name does not look like a testbench (the harvest's fallback).  A file added both as a design
file and with -tb counts as a testbench file (cgeist --function='*' would lower its main and file I/O,
which hls-est cannot parse), unless it defines the top function: Vitis compiles every design file, and the
file that defines the top is part of what it synthesizes (accelerators/DGNN_Booster_* add their only design
file both ways).  What Vitis does with the other both-ways files is unconfirmed.  Includes =
"." + the src/include/inc/hls/cpp subdirectories that exist (generate.py's rule) + the -I of design-file
cflags; defines = their -D.

A directory that cannot be listed and a file that cannot be read are problems (discover() and load()
report them; designs.load_hlsfactory_v2() raises on them), never a design or a file that silently goes
missing: os.walk drops an unlistable directory without a word.

Key stability: a design that also exists in the Polygeist copy keeps that copy's key (dataset/benchmark,
benchmark = the design path below the dataset with "/" -> "__").  Its source set (the design sources and
every header of the design tree, contents compared with CRLF -> LF, since the HLSFactory_v2 checkout has
core.autocrlf=true) is compared with the copy's.  Identical (or identical after the harvest's own
transform: HLSyn placeholders instantiated, undecodable bytes replaced) -> the record is the Polygeist
record itself (same dir, sources, includes), so every cache key (the Vitis cache key hashes the design
directory and absolute include paths) and every earlier result stays valid; it gains origin, flows and
the v2 fields.  Different -> the record points at the HLSFactory_v2 directory under the same key and the
difference is recorded (source_match, v2.source_diff); its ground truth is re-run in W8c.  Designs only
in v2 get new keys; Polygeist designs that are no longer in v2 are reported by catalogue_report().

Python 3.10, stdlib only (tomllib is used when it exists, a TOML subset reader otherwise; the HLSFactory
package itself needs Python >= 3.12 and is not imported).
"""
from __future__ import annotations

import fnmatch
import glob as _glob
import hashlib
import math
import os
import posixpath
import re
from collections import Counter, defaultdict
from pathlib import Path

try:                                     # Python >= 3.11
    import tomllib as _tomllib           # type: ignore
except ImportError:                      # Python 3.10 (the harness)
    _tomllib = None

DEFAULT_ROOT = "/mnt/d/HLSFactory_v2/HLSFactory"
SOURCES_SUBDIR = "hlsfactory/hls_dataset_sources"
CONFIG_FILENAME = "hlsfactory.toml"
LEGACY_SYNTH_TCL = "dataset_hls.tcl"
SYNTH_FLOW = "VitisHLSSynthFlow"

C_SRC_EXT = {".c", ".cc", ".cpp", ".cxx"}
HDR_EXT = {".h", ".hh", ".hpp", ".hxx", ".inc", ".tcc", ".ipp"}
# harvest.py's testbench-name rule (fallback source selection only)
TB_NAME = re.compile(r"(^|[_\-.])(tb|test|tests|testbench|main|golden|sw|host|"
                     r"driver|ref|reference|harness|check|verify)([_\-.]|$)", re.I)
INCLUDE_SUBDIRS = ("src", "include", "inc", "hls", "cpp")      # generate.py incs()
PLACEHOLDER = re.compile(r"@[A-Z][A-Z0-9_]*@")
SET_TOP_LINE = re.compile(r"^[ \t]*set_top[ \t]+\S", re.M)

# Dataset directories that hold no Vitis project at all (listed, never swept).
DATASET_NOTES = {
    "hlsyn": "HLSyn design-space descriptions (designs/*.json, no C sources, no Tcl); their Vitis "
             "projects are the hlsyn-vitis dataset",
}

# Templates whose dataset documents how they are instantiated.
TEMPLATE_RULES = {
    # auto_ntt/README.md and Makefile `run_hls target=<task>`: copy tcl_template/run_hls.tcl into
    # <task>_project/, link ../cpp/<task>.cpp, ../cpp/ntt.h and ../src there, replace @MODULE_NAME@
    # with <task>; one Vitis project per cpp/<task>.cpp (README: "TASK_NAME is the cpp file name").
    "auto_ntt/tcl_template/run_hls.tcl": {
        "placeholder": "@MODULE_NAME@",
        "modules": "cpp/*.cpp",
        "links": {"{m}.cpp": "cpp/{m}.cpp", "ntt.h": "cpp/ntt.h", "src": "src"},
        "project_includes": ["cpp"],          # the project dir holds the ntt.h link
    },
}


# Paths in records and in the interpreter are WSL (posix) strings; every filesystem access goes through
# LOCAL (None = the path as is), which designs.py sets to its local() mapping when it runs on Windows.
LOCAL = None


def _L(p: str) -> str:
    return str(LOCAL(p)) if LOCAL else p


# Directory listings and file contents are cached for the life of the process: the tree sits on
# /mnt/d, where every listing and stat crosses the WSL file-system bridge.
_DIRS: dict[str, tuple[list[str], list[str]]] = {}
_BYTES: dict[str, bytes] = {}
# Every listing / stat / read failure met since the last _drain_io_errors(); discover() and load() move
# them into `problems`.  A listing failure is cached with the listing (_SCAN_ERRORS, by the directory whose
# listing failed or held the entry) and reported again by every _walk() through that directory, so a second
# load in the same process reports it too.
IO_ERRORS: list[str] = []
_SCAN_ERRORS: dict[str, list[str]] = {}


def _io_error_text(path: str, what: str, e: OSError) -> str:
    return f"{path}: cannot {what} ({e.strerror or e})"


def _io_error(path: str, what: str, e: OSError) -> None:
    IO_ERRORS.append(_io_error_text(path, what, e))


def _drain_io_errors(problems: list[str]) -> None:
    for e in dict.fromkeys(IO_ERRORS):
        if e not in problems:
            problems.append(e)
    IO_ERRORS.clear()


def _is_dir_entry(entry, path: str, errors: list[str]) -> bool | None:
    """entry.is_dir() (following symlinks, as os.walk does); None and an error line when it fails, where
    os.walk would silently take the entry for a file."""
    try:
        return entry.is_dir()
    except OSError as e:
        errors.append(_io_error_text(path, "stat", e))
        return None


def _scan(top: str) -> None:
    """Fill _DIRS for the tree under `top` the way os.walk(top) lists it (top-down; symlinked directories are
    listed but not entered; __pycache__ and hidden directories left out), except that a directory that cannot
    be listed (cached as empty) and an entry that cannot be stat'ed (left out) are recorded in _SCAN_ERRORS
    instead of vanishing; _walk() reports them."""
    stack = [posixpath.normpath(top)]
    while stack:
        dp = stack.pop()
        try:
            with os.scandir(_L(dp)) as it:
                entries = list(it)
        except OSError as e:
            _SCAN_ERRORS[dp] = [_io_error_text(dp, "list directory", e)]
            _DIRS[dp] = ([], [])
            continue
        dn, fn, enter, errors = [], [], [], []
        for e in entries:
            path = posixpath.join(dp, e.name)
            is_dir = _is_dir_entry(e, path, errors)
            if is_dir is None:
                continue
            if not is_dir:
                fn.append(e.name)
                continue
            if e.name == "__pycache__" or e.name.startswith("."):
                continue
            dn.append(e.name)
            try:
                link = e.is_symlink()
            except OSError:
                link = False
            if not link:
                enter.append(e.name)
        dn.sort()
        _DIRS[dp] = (dn, sorted(fn))
        if errors:
            _SCAN_ERRORS[dp] = errors
        stack.extend(posixpath.join(dp, d) for d in sorted(enter, reverse=True))


def _isfile(p):
    p = posixpath.normpath(p)
    parent = posixpath.dirname(p)
    if parent in _DIRS:
        return posixpath.basename(p) in _DIRS[parent][1]
    return os.path.isfile(_L(p))


def _isdir(p):
    p = posixpath.normpath(p)
    if p in _DIRS:
        return True
    parent = posixpath.dirname(p)
    if parent in _DIRS:
        return posixpath.basename(p) in _DIRS[parent][0]
    return os.path.isdir(_L(p))


def _exists(p):
    return _isfile(p) or _isdir(p) or os.path.exists(_L(p))


def _read_bytes(p) -> bytes:
    p = posixpath.normpath(p)
    if p not in _BYTES:
        _BYTES[p] = Path(_L(p)).read_bytes()
    return _BYTES[p]


def _read_text(p) -> str:
    return _read_bytes(p).decode("utf-8", errors="replace").replace("\r\n", "\n")


def _listdir(p) -> list[str]:
    return sorted(os.listdir(_L(p)))


def _glob_paths(base: str, pattern: str) -> list[str]:
    lb = _L(base)
    return [posixpath.join(base, os.path.relpath(h, lb).replace("\\", "/"))
            for h in sorted(_glob.glob(os.path.join(lb, pattern)))]


class DesignConfigError(ValueError):
    """An hlsfactory.toml that design_config.py would reject."""


# =====================================================================================================
# hlsfactory.toml (design_config.py rules)
# =====================================================================================================
REQUIRED_FLOW_SETTINGS = {                 # design_config.FlowConfig._REQUIRED_SETTINGS
    "OptDSLv2": {"opt_dsl_file"},
    "VitisHLSSynthFlow": {"synth_tcl"},
    "VitisHLSCsimFlow": {"csim_tcl"},
    "VitisHLSImplFlow": {"impl_tcl"},
    "VitisHLSCosimFlow": {"cosim_tcl"},
    "VitisHLSCosimSetupFlow": {"cosim_setup_tcl"},
}


def _toml_string(s: str, lineno: int) -> tuple[str, str]:
    """Parse a TOML basic ("...") or literal ('...') string at the start of s; return (value, rest)."""
    q = s[0]
    if q == "'":
        end = s.find("'", 1)
        if end < 0:
            raise DesignConfigError(f"line {lineno}: unterminated string")
        return s[1:end], s[end + 1:]
    out, i = [], 1
    esc = {"n": "\n", "t": "\t", "r": "\r", '"': '"', "\\": "\\", "b": "\b", "f": "\f"}
    while i < len(s):
        c = s[i]
        if c == "\\":
            n = s[i + 1:i + 2]
            if n in esc:
                out.append(esc[n])
                i += 2
                continue
            if n in ("u", "U"):
                w = 4 if n == "u" else 8
                out.append(chr(int(s[i + 2:i + 2 + w], 16)))
                i += 2 + w
                continue
            raise DesignConfigError(f"line {lineno}: bad escape \\{n}")
        if c == '"':
            return "".join(out), s[i + 1:]
        out.append(c)
        i += 1
    raise DesignConfigError(f"line {lineno}: unterminated string")


def _toml_value(s: str, lineno: int):
    s = s.strip()
    if not s:
        raise DesignConfigError(f"line {lineno}: missing value")
    if s[0] in "\"'":
        v, rest = _toml_string(s, lineno)
        if rest.strip():
            raise DesignConfigError(f"line {lineno}: text after string")
        return v
    if s[0] == "[":
        if not s.endswith("]"):
            raise DesignConfigError(f"line {lineno}: unterminated array")
        body, items = s[1:-1].strip(), []
        while body:
            if body[0] in "\"'":
                v, body = _toml_string(body, lineno)
            else:
                m = re.match(r"[^,\]]+", body)
                v, body = _toml_value(m.group(0), lineno), body[m.end():]
            items.append(v)
            body = body.strip()
            if body.startswith(","):
                body = body[1:].strip()
            elif body:
                raise DesignConfigError(f"line {lineno}: bad array")
        return items
    if s in ("true", "false"):
        return s == "true"
    if re.fullmatch(r"[+-]?\d[\d_]*", s):
        return int(s.replace("_", ""))
    if re.fullmatch(r"[+-]?\d[\d_]*(\.\d+)?([eE][+-]?\d+)?", s):
        return float(s.replace("_", ""))
    raise DesignConfigError(f"line {lineno}: unsupported TOML value {s!r}")


def _strip_toml_comment(line: str) -> str:
    out, q = [], None
    for i, c in enumerate(line):
        if q:
            if c == q and not (q == '"' and line[i - 1] == "\\"):
                q = None
        elif c in "\"'":
            q = c
        elif c == "#":
            break
        out.append(c)
    return "".join(out)


def parse_toml_subset(text: str) -> dict:
    """The TOML that hlsfactory.toml files use: key = string / array / int / bool, [table],
    [[array of tables]], comments; multi-line arrays.  Anything else raises DesignConfigError."""
    root: dict = {}
    cur = root
    pending, start = "", 0
    for lineno, raw in enumerate(text.splitlines(), 1):
        line = _strip_toml_comment(raw).strip()
        if pending:
            pending += " " + line
            if pending.count("[") > pending.count("]"):
                continue
            line, pending, lineno = pending, "", start
        if not line:
            continue
        if line.startswith("[["):
            name = line[2:].rstrip()
            if not name.endswith("]]"):
                raise DesignConfigError(f"line {lineno}: bad table header")
            arr = root.setdefault(name[:-2].strip(), [])
            arr.append({})
            cur = arr[-1]
        elif line.startswith("["):
            if not line.endswith("]"):
                raise DesignConfigError(f"line {lineno}: bad table header")
            cur = root.setdefault(line[1:-1].strip(), {})
        else:
            key, eq, val = line.partition("=")
            key = key.strip().strip('"')
            if not eq or not re.fullmatch(r"[A-Za-z0-9_\-]+", key):
                raise DesignConfigError(f"line {lineno}: unsupported TOML line {raw!r}")
            if val.strip().startswith("[") and val.count("[") > val.count("]"):
                pending, start = f"{key} = {val.strip()}", lineno
                continue
            cur[key] = _toml_value(val, lineno)
    if pending:
        raise DesignConfigError("unterminated multi-line array")
    return root


def read_toml(path) -> dict:
    data = _read_bytes(path)
    if _tomllib is not None:
        try:
            return _tomllib.loads(data.decode("utf-8"))
        except Exception as e:            # noqa: BLE001  (tomllib.TOMLDecodeError)
            raise DesignConfigError(str(e)) from e
    return parse_toml_subset(data.decode("utf-8"))


def _nonempty_str(v, what):
    if not isinstance(v, str) or not v.strip():
        raise DesignConfigError(f"`{what}` must be a non-empty string; got {v!r}.")
    return v.strip()


def design_config_from_mapping(data) -> dict:
    """design_config.DesignConfig.from_mapping + __post_init__ validation, as plain data:
    {design_name, dataset_name, tags, env_vars, flows: [{flow_name, settings}]}."""
    if not isinstance(data, dict):
        raise DesignConfigError("Design configuration must be a mapping.")
    for k in ("design_name", "dataset_name"):
        if k not in data:
            raise DesignConfigError(f"`{k}` is required.")
    tags = data.get("tags", [])
    if not isinstance(tags, list):
        raise DesignConfigError("`tags` must be a list of strings if provided.")
    env = data.get("env_vars", {})
    if not isinstance(env, dict):
        raise DesignConfigError("`env_vars` must be a table of string values if provided.")
    for k, v in env.items():
        if not isinstance(k, str) or not k or not isinstance(v, str):
            raise DesignConfigError(f"`env_vars` entry {k!r} = {v!r} is not a string pair.")
    raw_flows = data.get("flow_configs", [])
    if not isinstance(raw_flows, list):
        raise DesignConfigError("`flow_configs` must be an array of tables.")
    flows, seen = [], set()
    for idx, entry in enumerate(raw_flows):
        if not isinstance(entry, dict):
            raise DesignConfigError(f"Entry {idx} in `flow_configs` must be a table.")
        if "flow_name" not in entry or not isinstance(entry["flow_name"], str) or not entry["flow_name"].strip():
            raise DesignConfigError(f"Invalid flow configuration at index {idx}: no `flow_name`.")
        name = entry["flow_name"].strip()
        settings = {}
        fs = entry.get("flow_settings")
        if fs is not None:
            if not isinstance(fs, dict):
                raise DesignConfigError(f"flow {name}: `flow_settings` must be a table of string values.")
            settings.update(fs)
        for k, v in entry.items():
            if k not in ("flow_name", "flow_settings"):
                settings[k] = v
        for k, v in settings.items():
            if not isinstance(v, str):
                raise DesignConfigError(f"flow {name}: setting `{k}` must be a string; got {v!r}.")
        missing = sorted(REQUIRED_FLOW_SETTINGS.get(name, set()) - set(settings))
        if missing:
            raise DesignConfigError(f"Flow `{name}` is missing required setting(s): {', '.join(missing)}.")
        if name in seen:
            raise DesignConfigError(f"Duplicate flow configuration for `{name}` is not allowed.")
        seen.add(name)
        flows.append({"flow_name": name, "settings": settings})
    return {"design_name": _nonempty_str(data["design_name"], "design_name"),
            "dataset_name": _nonempty_str(data["dataset_name"], "dataset_name"),
            "tags": [_nonempty_str(t, "tags") for t in tags], "env_vars": dict(env), "flows": flows}


def read_design_config(path) -> dict:
    return design_config_from_mapping(read_toml(path))


# =====================================================================================================
# Tcl subset
# =====================================================================================================
class TclError(Exception):
    pass


class _TclExit(Exception):
    pass


class _TclReturn(Exception):
    def __init__(self, value=""):
        super().__init__(value)
        self.value = value


class _TclBreak(Exception):
    pass


class _TclContinue(Exception):
    pass


def _match_brace(s: str, i: int) -> int:
    depth, j = 0, i
    while j < len(s):
        c = s[j]
        if c == "\\":
            j += 2
            continue
        if c == "{":
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0:
                return j
        j += 1
    raise TclError("missing close-brace")


def _match_bracket(s: str, i: int) -> int:
    depth, j = 0, i
    while j < len(s):
        c = s[j]
        if c == "\\":
            j += 2
            continue
        if c == "{":
            j = _match_brace(s, j) + 1
            continue
        if c == "[":
            depth += 1
        elif c == "]":
            depth -= 1
            if depth == 0:
                return j
        j += 1
    raise TclError("missing close-bracket")


def _match_quote(s: str, i: int) -> int:
    j = i + 1
    while j < len(s):
        c = s[j]
        if c == "\\":
            j += 2
            continue
        if c == "[":
            j = _match_bracket(s, j) + 1
            continue
        if c == '"':
            return j
        j += 1
    raise TclError("missing close-quote")


def _split_commands(script: str) -> list[list[tuple[str, str]]]:
    """Script -> commands, each a list of (kind, text) words; kind is brace / quote / bare."""
    cmds, words = [], []
    i, n = 0, len(script)
    while i < n:
        c = script[i]
        if c in " \t\r\f\v":
            i += 1
            continue
        if c == "\\" and i + 1 < n and script[i + 1] in "\r\n":
            i += 2
            continue
        if c in "\n;":
            if words:
                cmds.append(words)
                words = []
            i += 1
            continue
        if not words and c == "#":
            while i < n and script[i] != "\n":
                i += 2 if script[i] == "\\" else 1
            continue
        if c == "{" and script[i:i + 3] != "{*}":
            j = _match_brace(script, i)
            words.append(("brace", script[i + 1:j]))
            i = j + 1
        elif c == '"':
            j = _match_quote(script, i)
            words.append(("quote", script[i + 1:j]))
            i = j + 1
        else:
            j = i + (3 if script[i:i + 3] == "{*}" else 0)
            while j < n and script[j] not in " \t\r\n;":
                if script[j] == "\\":
                    j += 2
                    continue
                if script[j] == "[":
                    j = _match_bracket(script, j) + 1
                    continue
                if script[j] == "$" and script[j + 1:j + 2] == "{":
                    k = script.find("}", j)
                    j = (k + 1) if k > 0 else n
                    continue
                j += 1
            words.append(("bare", script[i:j]))
            i = j
    if words:
        cmds.append(words)
    return cmds


def list_elements(s: str) -> list[str]:
    """Tcl list -> elements."""
    out, i, n = [], 0, len(s)
    while i < n:
        if s[i].isspace():
            i += 1
            continue
        if s[i] == "{":
            j = _match_brace(s, i)
            out.append(s[i + 1:j])
            i = j + 1
        elif s[i] == '"':
            j = _match_quote(s, i)
            out.append(_backslash(s[i + 1:j]))
            i = j + 1
        else:
            j = i
            while j < n and not s[j].isspace():
                j += 2 if s[j] == "\\" else 1
            out.append(_backslash(s[i:j]))
            i = j
    return out


def list_format(items) -> str:
    out = []
    for e in items:
        e = str(e)
        if e == "":
            out.append("{}")
        elif re.search(r'[\s{}\[\]$";\\]', e):
            out.append("{" + e + "}" if e.count("{") == e.count("}") else re.sub(r'([\s{}\[\]$";\\])', r"\\\1", e))
        else:
            out.append(e)
    return " ".join(out)


_BS = {"n": "\n", "t": "\t", "r": "\r", "a": "\a", "b": "\b", "f": "\f", "v": "\v"}


def _backslash(s: str) -> str:
    if "\\" not in s:
        return s
    out, i = [], 0
    while i < len(s):
        if s[i] == "\\" and i + 1 < len(s):
            c = s[i + 1]
            if c in "\r\n":
                i += 2
                while i < len(s) and s[i] in " \t\r\n":
                    i += 1
                out.append(" ")
                continue
            out.append(_BS.get(c, c))
            i += 2
            continue
        out.append(s[i])
        i += 1
    return "".join(out)


def _num(v):
    """Tcl value -> int / float when it is a number, else the string."""
    if isinstance(v, (int, float)):
        return v
    s = str(v).strip()
    try:
        return int(s, 0) if re.fullmatch(r"[+-]?(0[xX][0-9a-fA-F]+|\d+)", s) else float(s)
    except ValueError:
        return s


def _fmt(v) -> str:
    if isinstance(v, bool):
        return "1" if v else "0"
    if isinstance(v, float):
        if v == int(v) and abs(v) < 1e15:
            return f"{v:.1f}"
        return repr(v)
    return str(v)


class TclSubset:
    """Evaluates HLS synthesis scripts and records the Vitis commands they issue (see module doc)."""

    MAX_STEPS = 200000

    def __init__(self, cwd: str, env: dict | None = None, links: dict | None = None,
                 argv: list[str] | None = None):
        self.cwd = posixpath.normpath(cwd)
        self.env = dict(env or {})
        self.links = dict(links or {})          # path relative to the project dir -> real path
        self.globals: dict = {"argv": list_format(argv or []), "argc": str(len(argv or [])),
                              "argv0": "", "tcl_platform": {"platform": "unix", "os": "Linux"}}
        self.frames = [self.globals]
        self.procs: dict = {}
        self.steps = 0
        self.script_stack: list[str] = []
        # what the script did
        self.top = None
        self.files: list[dict] = []             # {path, abs, tb, cflags, csimflags}
        self.part = None
        self.clock = None
        self.flow_target = None
        self.project = None
        self.directives: list[str] = []
        self.configs: list[str] = []
        self.actions: list[str] = []
        self.sourced: list[str] = []
        self.missing: list[str] = []
        self.unknown: Counter = Counter()
        self.errors: list[str] = []
        self.unset_env: set = set()
        self.mentions_csynth = False            # some evaluated script names csynth_design

    # ------------------------------------------------------------------ variables
    def _frame_for(self, name):
        if name.startswith("::"):
            return self.globals, name[2:]
        return self.frames[-1], name

    def get_var(self, name, index=None):
        if name in ("env", "::env"):
            if index is None:
                raise TclError("can't read \"env\": variable is array")
            if index not in self.env:
                self.unset_env.add(index)
                raise TclError(f"can't read \"env({index})\": no such variable")
            return self.env[index]
        frame, n = self._frame_for(name)
        if n not in frame and frame is not self.globals and n in self.globals:
            frame = self.globals                 # lenient: procs see globals
        if n not in frame:
            raise TclError(f"can't read \"{name}\": no such variable")
        v = frame[n]
        if index is not None:
            if not isinstance(v, dict) or index not in v:
                raise TclError(f"can't read \"{name}({index})\": no such element")
            return v[index]
        if isinstance(v, dict):
            raise TclError(f"can't read \"{name}\": variable is array")
        return v

    def set_var(self, name, value, index=None):
        m = re.fullmatch(r"([^(]+)\((.*)\)", name) if index is None else None
        if m:
            name, index = m.group(1), m.group(2)
        if name in ("env", "::env") and index is not None:
            self.env[index] = value
            return value
        frame, n = self._frame_for(name)
        if index is None:
            frame[n] = value
        else:
            arr = frame.setdefault(n, {})
            if not isinstance(arr, dict):
                raise TclError(f"can't set \"{name}({index})\": variable isn't array")
            arr[index] = value
        return value

    def var_exists(self, name):
        m = re.fullmatch(r"([^(]+)\((.*)\)", name)
        try:
            self.get_var(m.group(1), m.group(2)) if m else self.get_var(name)
            return True
        except TclError:
            return False

    # ------------------------------------------------------------------ substitution
    def subst(self, text: str) -> str:
        if not any(c in text for c in "$[\\"):
            return text
        out, i, n = [], 0, len(text)
        while i < n:
            c = text[i]
            if c == "\\" and i + 1 < n:
                j = i + 2
                if text[i + 1] in "\r\n":
                    while j < n and text[j] in " \t\r\n":
                        j += 1
                out.append(_backslash(text[i:j]) if text[i + 1] not in "\r\n" else " ")
                i = j
            elif c == "[":
                j = _match_bracket(text, i)
                out.append(self.eval(text[i + 1:j]))
                i = j + 1
            elif c == "$":
                if text[i + 1:i + 2] == "{":
                    j = text.find("}", i)
                    if j < 0:
                        raise TclError("missing close-brace for variable name")
                    out.append(self.get_var(text[i + 2:j]))
                    i = j + 1
                    continue
                m = re.match(r"(?:::)?[A-Za-z0-9_]+(?:::[A-Za-z0-9_]+)*", text[i + 1:])
                if not m:
                    out.append("$")
                    i += 1
                    continue
                name = m.group(0)
                j = i + 1 + m.end()
                if text[j:j + 1] == "(":
                    k, depth = j, 0
                    while k < n:
                        if text[k] == "(":
                            depth += 1
                        elif text[k] == ")":
                            depth -= 1
                            if depth == 0:
                                break
                        k += 1
                    out.append(self.get_var(name, self.subst(text[j + 1:k])))
                    i = k + 1
                else:
                    out.append(self.get_var(name))
                    i = j
            else:
                k = i
                while k < n and text[k] not in "\\[$":
                    k += 1
                out.append(text[i:k])
                i = k
        return "".join(out)

    def _words(self, words) -> list[str]:
        argv = []
        for kind, text in words:
            if kind == "brace":
                argv.append(text)
            elif kind == "bare" and text.startswith("{*}"):
                argv.extend(list_elements(self.subst(text[3:])))
            else:
                argv.append(self.subst(text))
        return argv

    # ------------------------------------------------------------------ evaluation
    def eval(self, script: str) -> str:
        result = ""
        for words in _split_commands(script):
            result = self.call(self._words(words))
        return result

    def run_file(self, path: str, lenient: bool = True) -> None:
        """Evaluate a script file; with lenient, an error in one top-level command is recorded and the
        next command runs.  exit / quit end the evaluation."""
        try:
            self._source(path, lenient)
        except _TclExit:
            pass

    def _source(self, path, lenient=False):
        p = self.resolve(path)
        if not _isfile(p):
            self.missing.append(path)
            return ""
        self.sourced.append(posixpath.normpath(p))
        text = _read_text(p)
        if re.search(r"^\s*csynth_design\b", text, re.M):
            self.mentions_csynth = True
        self.script_stack.append(p)
        try:
            if not lenient:
                return self.eval(text)
            result = ""
            try:
                cmds = _split_commands(text)
            except TclError as e:
                self.errors.append(f"{posixpath.basename(p)}: parse: {e}")
                return ""
            for words in cmds:
                try:
                    result = self.call(self._words(words))
                except (TclError, _TclBreak, _TclContinue, _TclReturn) as e:
                    head = " ".join(t for _, t in words)[:100]
                    self.errors.append(f"{posixpath.basename(p)}: {head!r}: {e}")
            return result
        finally:
            self.script_stack.pop()

    def resolve(self, path: str) -> str:
        """A path as the script means it (relative to the current directory; project links)."""
        path = path.strip()
        if not path:
            return self.cwd
        norm = posixpath.normpath(path.replace("\\", "/"))
        for k, v in self.links.items():
            if norm == k or norm.startswith(k + "/"):
                return posixpath.normpath(v + norm[len(k):])
        if posixpath.isabs(norm):
            return norm
        return posixpath.normpath(posixpath.join(self.cwd, norm))

    def call(self, argv: list[str]) -> str:
        self.steps += 1
        if self.steps > self.MAX_STEPS:
            raise TclError("step limit reached")
        if not argv:
            return ""
        name = argv[0].lstrip(":") if argv[0].startswith("::") else argv[0]
        if name in self.procs:
            return self._call_proc(name, argv[1:])
        fn = getattr(self, "cmd_" + name, None)
        if fn is not None:
            return fn(argv[1:]) or ""
        if name.startswith("set_directive_"):
            self.directives.append(" ".join(argv))
            return ""
        if name.startswith("config_"):
            self.configs.append(" ".join(argv))
            return ""
        self.unknown[name] += 1
        return ""

    def _call_proc(self, name, args):
        params, body = self.procs[name]
        frame = {}
        for i, p in enumerate(params):
            pe = list_elements(p)
            pname = pe[0]
            if pname == "args" and i == len(params) - 1:
                frame["args"] = list_format(args[i:])
                break
            if i < len(args):
                frame[pname] = args[i]
            elif len(pe) > 1:
                frame[pname] = pe[1]
            else:
                raise TclError(f"wrong # args: should be \"{name} {' '.join(params)}\"")
        self.frames.append(frame)
        try:
            return self.eval(body)
        except _TclReturn as r:
            return r.value
        finally:
            self.frames.pop()

    # ------------------------------------------------------------------ core commands
    def cmd_set(self, a):
        if len(a) == 1:
            m = re.fullmatch(r"([^(]+)\((.*)\)", a[0])
            return self.get_var(m.group(1), m.group(2)) if m else self.get_var(a[0])
        if len(a) != 2:
            raise TclError("wrong # args: set varName ?newValue?")
        return self.set_var(a[0], a[1])

    def cmd_unset(self, a):
        for n in a:
            if n.startswith("-"):
                continue
            frame, k = self._frame_for(n)
            frame.pop(k, None)

    def cmd_global(self, a):
        for n in a:
            if n in self.globals and self.frames[-1] is not self.globals:
                self.frames[-1][n] = self.globals[n]

    cmd_variable = cmd_global

    def cmd_append(self, a):
        v = self.get_var(a[0]) if self.var_exists(a[0]) else ""
        return self.set_var(a[0], v + "".join(a[1:]))

    def cmd_lappend(self, a):
        v = self.get_var(a[0]) if self.var_exists(a[0]) else ""
        return self.set_var(a[0], list_format(list_elements(v) + a[1:]))

    def cmd_incr(self, a):
        v = int(_num(self.get_var(a[0]) if self.var_exists(a[0]) else "0"))
        return self.set_var(a[0], str(v + (int(_num(a[1])) if len(a) > 1 else 1)))

    def cmd_list(self, a):
        return list_format(a)

    def cmd_llength(self, a):
        return str(len(list_elements(a[0])))

    def _index(self, idx, n):
        idx = idx.strip()
        m = re.fullmatch(r"end(?:([+-])(\d+))?", idx)
        if m:
            off = int(m.group(2) or 0)
            return n - 1 + (off if m.group(1) == "+" else -off)
        return int(_num(idx))

    def cmd_lindex(self, a):
        v = a[0]
        idxs = a[1:] if len(a) > 2 else (list_elements(a[1]) if len(a) == 2 else [])
        for idx in idxs:
            el = list_elements(v)
            i = self._index(idx, len(el))
            v = el[i] if 0 <= i < len(el) else ""
        return v

    def cmd_lrange(self, a):
        el = list_elements(a[0])
        i, j = self._index(a[1], len(el)), self._index(a[2], len(el))
        return list_format(el[max(i, 0):j + 1])

    def cmd_lsearch(self, a):
        opts = [x for x in a[:-2] if x.startswith("-")]
        el, pat = list_elements(a[-2]), a[-1]
        for i, e in enumerate(el):
            if (e == pat) if "-exact" in opts else fnmatch.fnmatchcase(e, pat):
                return str(i)
        return "-1"

    def cmd_lsort(self, a):
        return list_format(sorted(list_elements(a[-1])))

    def cmd_concat(self, a):
        return " ".join(x.strip() for x in a if x.strip())

    def cmd_join(self, a):
        return (a[1] if len(a) > 1 else " ").join(list_elements(a[0]))

    def cmd_split(self, a):
        chars = a[1] if len(a) > 1 else " \t\n"
        return list_format(re.split("[" + re.escape(chars) + "]", a[0]) if chars else list(a[0]))

    def cmd_expr(self, a):
        return _fmt(_Expr(self, " ".join(a)).value())

    def cmd_if(self, a):
        i = 0
        while i < len(a):
            cond = a[i]
            i += 1
            if i < len(a) and a[i] == "then":
                i += 1
            body = a[i]
            i += 1
            if _truth(_Expr(self, cond).value()):
                return self.eval(body)
            if i >= len(a):
                return ""
            if a[i] == "elseif":
                i += 1
                continue
            if a[i] == "else":
                i += 1
            return self.eval(a[i])
        return ""

    def _loop_body(self, body):
        try:
            self.eval(body)
        except _TclContinue:
            pass

    def cmd_foreach(self, a):
        body, pairs = a[-1], a[:-1]
        specs = [(list_elements(pairs[k]), list_elements(pairs[k + 1])) for k in range(0, len(pairs), 2)]
        rounds = max((math.ceil(len(vals) / max(len(vs), 1)) for vs, vals in specs), default=0)
        try:
            for r in range(rounds):
                for vs, vals in specs:
                    for k, v in enumerate(vs):
                        idx = r * len(vs) + k
                        self.set_var(v, vals[idx] if idx < len(vals) else "")
                self._loop_body(body)
        except _TclBreak:
            pass
        return ""

    def cmd_for(self, a):
        start, test, nxt, body = a
        self.eval(start)
        n = 0
        try:
            while _truth(_Expr(self, test).value()):
                n += 1
                if n > 10000:
                    raise TclError("for: iteration limit")
                self._loop_body(body)
                self.eval(nxt)
        except _TclBreak:
            pass
        return ""

    def cmd_while(self, a):
        n = 0
        try:
            while _truth(_Expr(self, a[0]).value()):
                n += 1
                if n > 10000:
                    raise TclError("while: iteration limit")
                self._loop_body(a[1])
        except _TclBreak:
            pass
        return ""

    def cmd_break(self, a):
        raise _TclBreak()

    def cmd_continue(self, a):
        raise _TclContinue()

    def cmd_proc(self, a):
        self.procs[a[0].lstrip(":")] = (list_elements(a[1]), a[2])
        return ""

    def cmd_return(self, a):
        args = [x for x in a if not x.startswith("-")]
        raise _TclReturn(args[-1] if args else "")

    def cmd_catch(self, a):
        try:
            r = self.eval(a[0])
            code = "0"
        except (TclError, _TclBreak, _TclContinue) as e:
            r, code = str(e), "1"
        except _TclReturn as e:
            r, code = e.value, "2"
        if len(a) > 1:
            self.set_var(a[1], r)
        return code

    def cmd_eval(self, a):
        return self.eval(" ".join(a))

    def cmd_uplevel(self, a):
        return self.eval(" ".join(a[1:] if a and re.fullmatch(r"#?\d+", a[0]) else a))

    def cmd_puts(self, a):
        return ""

    def cmd_error(self, a):
        raise TclError(a[0] if a else "error")

    def cmd_exit(self, a):
        raise _TclExit()

    cmd_quit = cmd_exit

    def cmd_info(self, a):
        sub = a[0] if a else ""
        if sub == "exists":
            return "1" if self.var_exists(a[1]) else "0"
        if sub == "script":
            return self.script_stack[-1] if self.script_stack else ""
        if sub == "commands":
            return ""
        raise TclError(f"info {sub}: not supported")

    def cmd_source(self, a):
        args = [x for x in a if x not in ("-encoding",)]
        return self._source(args[-1])

    def cmd_cd(self, a):
        self.cwd = self.resolve(a[0]) if a else self.cwd
        return ""

    def cmd_pwd(self, a):
        return self.cwd

    def cmd_exec(self, a):
        self.unknown["exec (not run)"] += 1
        return ""

    def cmd_file(self, a):
        sub, rest = a[0], a[1:]
        if sub == "exists":
            return "1" if _exists(self.resolve(rest[0])) else "0"
        if sub == "isfile":
            return "1" if _isfile(self.resolve(rest[0])) else "0"
        if sub == "isdirectory":
            return "1" if _isdir(self.resolve(rest[0])) else "0"
        if sub == "join":
            return posixpath.join(*rest)
        if sub == "dirname":
            return posixpath.dirname(rest[0]) or "."
        if sub == "tail":
            return posixpath.basename(rest[0])
        if sub == "rootname":
            return posixpath.splitext(rest[0])[0]
        if sub == "extension":
            return posixpath.splitext(rest[0])[1]
        if sub == "normalize":
            return self.resolve(rest[0])
        if sub in ("mkdir", "delete", "copy", "rename", "link", "attributes", "mtime"):
            self.unknown[f"file {sub} (not run)"] += 1
            return ""
        raise TclError(f"file {sub}: not supported")

    def cmd_glob(self, a):
        nocomplain, directory, pats, i = False, None, [], 0
        while i < len(a):
            x = a[i]
            if x == "-nocomplain":
                nocomplain = True
            elif x in ("-directory", "-path", "-types"):
                if x == "-directory":
                    directory = a[i + 1]
                i += 1
            elif x == "--":
                pats += a[i + 1:]
                break
            elif x.startswith("-"):
                pass
            else:
                pats.append(x)
            i += 1
        base = self.resolve(directory) if directory else self.cwd
        out = []
        for p in pats:
            for hit in _glob_paths(base, p):
                out.append(posixpath.relpath(hit, base) if not directory and not posixpath.isabs(p)
                           else hit)
        if not out and not nocomplain:
            raise TclError(f"no files matched glob patterns \"{' '.join(pats)}\"")
        return list_format(out)

    def cmd_string(self, a):
        sub, r = a[0], a[1:]
        flags = [x for x in r if x in ("-nocase", "-exact")]
        r = [x for x in r if x not in ("-nocase", "-exact", "-length")]
        if sub == "equal":
            x, y = r[0], r[1]
            return "1" if (x.lower() == y.lower() if flags else x == y) else "0"
        if sub == "compare":
            x, y = r[0], r[1]
            return str((x > y) - (x < y))
        if sub == "match":
            return "1" if fnmatch.fnmatchcase(r[1], r[0]) else "0"
        if sub == "length":
            return str(len(r[0]))
        if sub == "tolower":
            return r[0].lower()
        if sub == "toupper":
            return r[0].upper()
        if sub in ("trim", "trimleft", "trimright"):
            chars = r[1] if len(r) > 1 else None
            return {"trim": r[0].strip, "trimleft": r[0].lstrip, "trimright": r[0].rstrip}[sub](chars)
        if sub == "first":
            return str(r[1].find(r[0]))
        if sub == "last":
            return str(r[1].rfind(r[0]))
        if sub == "range":
            i, j = self._index(r[1], len(r[0])), self._index(r[2], len(r[0]))
            return r[0][max(i, 0):j + 1]
        if sub == "index":
            i = self._index(r[1], len(r[0]))
            return r[0][i] if 0 <= i < len(r[0]) else ""
        if sub == "map":
            m, s = list_elements(r[0]), r[1]
            out, i = [], 0
            while i < len(s):
                for k in range(0, len(m) - 1, 2):
                    if m[k] and s.startswith(m[k], i):
                        out.append(m[k + 1])
                        i += len(m[k])
                        break
                else:
                    out.append(s[i])
                    i += 1
            return "".join(out)
        if sub == "is":
            cls, v = r[0], r[-1]
            if cls in ("integer", "int", "wide", "entier"):
                return "1" if re.fullmatch(r"\s*[+-]?\d+\s*", v) else "0"
            if cls == "double":
                return "1" if isinstance(_num(v), (int, float)) else "0"
            return "0"
        raise TclError(f"string {sub}: not supported")

    def cmd_format(self, a):
        args = [_num(x) for x in a[1:]]
        try:
            return a[0] % tuple(args)
        except (TypeError, ValueError) as e:
            raise TclError(f"format: {e}") from e

    def cmd_regexp(self, a):
        opts = []
        while a and a[0].startswith("-"):
            opts.append(a.pop(0))
            if opts[-1] == "--":
                break
        m = re.search(a[0], a[1], re.I if "-nocase" in opts else 0)
        for k, var in enumerate(a[2:]):
            self.set_var(var, (m.group(k) or "") if m and k <= (m.re.groups) else "")
        return "1" if m else "0"

    def cmd_regsub(self, a):
        opts = []
        while a and a[0].startswith("-"):
            opts.append(a.pop(0))
            if opts[-1] == "--":
                break
        rep = re.sub(r"\\(\d)", r"\\g<\1>", a[2]).replace("&", r"\g<0>")
        out = re.sub(a[0], rep, a[1], count=0 if "-all" in opts else 1)
        if len(a) > 3:
            self.set_var(a[3], out)
            return "1"
        return out

    def cmd_array(self, a):
        sub = a[0]
        if sub == "set":
            el = list_elements(a[2])
            for k in range(0, len(el) - 1, 2):
                self.set_var(a[1], el[k + 1], el[k])
            return ""
        if sub == "exists":
            frame, n = self._frame_for(a[1])
            return "1" if isinstance(frame.get(n), dict) else "0"
        raise TclError(f"array {sub}: not supported")

    def cmd_clock(self, a):
        return "0"

    # ------------------------------------------------------------------ Vitis HLS commands (recorded)
    def cmd_open_project(self, a):
        names = [x for x in a if not x.startswith("-")]
        self.project = names[-1] if names else None

    def cmd_set_top(self, a):
        names = [x for x in a if not x.startswith("-")]
        if names:
            self.top = names[-1].strip()

    def cmd_add_files(self, a):
        tb, cflags, csimflags, paths, i = False, "", "", [], 0
        while i < len(a):
            x = a[i]
            if x == "-tb":
                tb = True
            elif x in ("-cflags", "-csimflags", "-blackbox", "-fileset"):
                if x == "-cflags":
                    cflags = a[i + 1] if i + 1 < len(a) else ""
                elif x == "-csimflags":
                    csimflags = a[i + 1] if i + 1 < len(a) else ""
                i += 1
            elif x.startswith("-") and len(x) > 1:
                pass
            else:
                paths.extend(list_elements(x))
            i += 1
        for p in paths:
            self.files.append({"path": p, "abs": self.resolve(p), "tb": tb, "cflags": cflags,
                               "csimflags": csimflags})

    cmd_add_file = cmd_add_files

    def cmd_open_solution(self, a):
        if "-flow_target" in a:
            k = a.index("-flow_target")
            if k + 1 < len(a):
                self.flow_target = a[k + 1]

    def cmd_set_part(self, a):
        names = [x for x in a if not x.startswith("-")]
        if names:
            self.part = list_elements(names[-1])[0] if list_elements(names[-1]) else names[-1]

    def cmd_create_clock(self, a):
        if "-period" in a:
            k = a.index("-period")
            if k + 1 < len(a):
                self.clock = a[k + 1]

    def cmd_get_clock_period(self, a):
        return self.clock or ""

    def cmd_csynth_design(self, a):
        self.actions.append("csynth_design")

    def cmd_csim_design(self, a):
        self.actions.append("csim_design")

    def cmd_cosim_design(self, a):
        self.actions.append("cosim_design")

    def cmd_export_design(self, a):
        self.actions.append("export_design")

    def cmd_close_project(self, a):
        return ""

    cmd_close_solution = cmd_close_project
    cmd_delete_project = cmd_close_project
    cmd_delete_solution = cmd_close_project
    cmd_set_clock_uncertainty = cmd_close_project


def _truth(v) -> bool:
    v = _num(v)
    if isinstance(v, str):
        s = v.strip().lower()
        if s in ("true", "yes", "on"):
            return True
        if s in ("false", "no", "off", ""):
            return False
        raise TclError(f"expected boolean value but got \"{v}\"")
    return bool(v)


class _Expr:
    """Tcl expr: operands are substituted by the interpreter, then parsed by precedence climbing."""

    TOKEN = re.compile(r"\s*(?:(?P<num>0[xX][0-9a-fA-F]+|\d+\.?\d*(?:[eE][+-]?\d+)?|\.\d+(?:[eE][+-]?\d+)?)"
                       r"|(?P<op>\*\*|==|!=|<=|>=|&&|\|\||<<|>>|[-+*/%<>!~()?:,&|^])"
                       r"|(?P<word>[A-Za-z_][A-Za-z0-9_]*))")
    BINARY = [("||",), ("&&",), ("|",), ("^",), ("&",), ("in", "ni"), ("eq", "ne"), ("==", "!="),
              ("<", ">", "<=", ">="), ("<<", ">>"), ("+", "-"), ("*", "/", "%"), ("**",)]
    FUNCS = {"abs": abs, "int": lambda x: int(x), "wide": lambda x: int(x), "entier": lambda x: int(x),
             "double": float, "round": lambda x: int(math.floor(x + 0.5)), "ceil": math.ceil,
             "floor": math.floor, "sqrt": math.sqrt, "pow": math.pow, "exp": math.exp, "log": math.log,
             "log10": math.log10, "log2": math.log2, "min": min, "max": max, "bool": lambda x: bool(x)}

    def __init__(self, interp: TclSubset, text: str):
        self.interp = interp
        self.toks = self._tokenize(text)
        self.i = 0

    def _tokenize(self, s):
        toks, i, n = [], 0, len(s)
        while i < n:
            if s[i].isspace():
                i += 1
                continue
            c = s[i]
            if c == "$":
                j = i + 1
                if s[j:j + 1] == "{":
                    j = s.find("}", j) + 1
                else:
                    m = re.match(r"(?:::)?[A-Za-z0-9_]+(?:::[A-Za-z0-9_]+)*", s[j:])
                    j += m.end() if m else 0
                    if s[j:j + 1] == "(":
                        j = s.find(")", j) + 1
                toks.append(("val", self.interp.subst(s[i:j])))
                i = j
            elif c == "[":
                j = _match_bracket(s, i)
                toks.append(("val", self.interp.eval(s[i + 1:j])))
                i = j + 1
            elif c == '"':
                j = _match_quote(s, i)
                toks.append(("str", self.interp.subst(s[i + 1:j])))
                i = j + 1
            elif c == "{":
                j = _match_brace(s, i)
                toks.append(("str", s[i + 1:j]))
                i = j + 1
            else:
                m = self.TOKEN.match(s, i)
                if not m or m.end() == i:
                    raise TclError(f"expr: cannot parse {s[i:i + 20]!r}")
                if m.group("num"):
                    toks.append(("val", m.group("num")))
                elif m.group("op"):
                    toks.append(("op", m.group("op")))
                else:
                    w = m.group("word")
                    if w in ("eq", "ne", "in", "ni"):
                        toks.append(("op", w))
                    elif s[m.end():].lstrip().startswith("(") and w in self.FUNCS:
                        toks.append(("func", w))
                    else:
                        toks.append(("str", w))
                i = m.end()
        return toks

    def _peek(self):
        return self.toks[self.i] if self.i < len(self.toks) else (None, None)

    def _take(self):
        t = self._peek()
        self.i += 1
        return t

    def value(self):
        if not self.toks:
            raise TclError("expr: empty expression")
        v = self._ternary()
        if self.i != len(self.toks):
            raise TclError("expr: trailing tokens")
        return v

    def _ternary(self):
        c = self._binary(0)
        if self._peek() == ("op", "?"):
            self._take()
            a = self._ternary()
            if self._take() != ("op", ":"):
                raise TclError("expr: missing ':'")
            b = self._ternary()
            return a if _truth(c) else b
        return c

    def _binary(self, level):
        if level == len(self.BINARY):
            return self._unary()
        lhs = self._binary(level + 1)
        while True:
            kind, op = self._peek()
            if kind != "op" or op not in self.BINARY[level]:
                return lhs
            self._take()
            rhs = self._binary(level + 1) if op != "**" else self._binary(level)
            lhs = self._apply(op, lhs, rhs)

    def _unary(self):
        kind, op = self._peek()
        if kind == "op" and op in ("-", "+", "!", "~"):
            self._take()
            v = _num(self._unary())
            if op == "!":
                return not _truth(v)
            if isinstance(v, str):
                raise TclError(f"expr: can't use non-numeric string \"{v}\" as operand of \"{op}\"")
            return -v if op == "-" else (~v if op == "~" else v)
        return self._primary()

    def _primary(self):
        kind, v = self._take()
        if kind == "op" and v == "(":
            r = self._ternary()
            if self._take() != ("op", ")"):
                raise TclError("expr: missing ')'")
            return r
        if kind == "func":
            if self._take() != ("op", "("):
                raise TclError("expr: missing '('")
            args = []
            if self._peek() != ("op", ")"):
                while True:
                    args.append(_num(self._ternary()))
                    if self._peek() == ("op", ","):
                        self._take()
                        continue
                    break
            if self._take() != ("op", ")"):
                raise TclError("expr: missing ')'")
            try:
                return self.FUNCS[v](*args)
            except (TypeError, ValueError) as e:
                raise TclError(f"expr: {v}(): {e}") from e
        if kind in ("val", "str"):
            return v
        raise TclError(f"expr: unexpected {v!r}")

    @staticmethod
    def _apply(op, a, b):
        if op in ("eq", "ne"):
            r = _fmt(a) == _fmt(b)
            return r if op == "eq" else not r
        if op in ("in", "ni"):
            r = _fmt(a) in list_elements(_fmt(b))
            return r if op == "in" else not r
        if op == "&&":
            return _truth(a) and _truth(b)
        if op == "||":
            return _truth(a) or _truth(b)
        x, y = _num(a), _num(b)
        if op in ("==", "!=", "<", ">", "<=", ">="):
            if isinstance(x, str) or isinstance(y, str):
                x, y = _fmt(a), _fmt(b)
            return {"==": x == y, "!=": x != y, "<": x < y, ">": x > y, "<=": x <= y, ">=": x >= y}[op]
        if isinstance(x, str) or isinstance(y, str):
            raise TclError(f"expr: can't use non-numeric string as operand of \"{op}\"")
        if op == "+":
            return x + y
        if op == "-":
            return x - y
        if op == "*":
            return x * y
        if op == "/":
            if y == 0:
                raise TclError("divide by zero")
            return x // y if isinstance(x, int) and isinstance(y, int) else x / y
        if op == "%":
            return x % y
        if op == "**":
            return x ** y
        if op == "<<":
            return x << y
        if op == ">>":
            return x >> y
        if op == "&":
            return x & y
        if op == "|":
            return x | y
        if op == "^":
            return x ^ y
        raise TclError(f"expr: operator {op}")


def clock_ns(clock: str | None):
    """create_clock -period value -> ns (a bare number is ns; 300MHz -> 3.333)."""
    if not clock:
        return None
    m = re.fullmatch(r"\s*([\d.]+)\s*([a-zA-Z]*)\s*", str(clock))
    if not m:
        return None
    v, unit = float(m.group(1)), m.group(2).lower()
    if unit in ("", "ns"):
        return v
    if unit == "mhz":
        return round(1000.0 / v, 4)
    if unit == "ghz":
        return round(1.0 / v, 4)
    if unit == "ps":
        return v / 1000.0
    return None


# =====================================================================================================
# discovery
# =====================================================================================================
def _sources_root(root: str) -> str:
    return posixpath.join(root.rstrip("/"), SOURCES_SUBDIR)


def _walk(top: str):
    """os.walk (top-down, sorted, without __pycache__ / hidden directories) from the listing cache;
    yields WSL-style paths.  The listing errors of every directory it passes go to IO_ERRORS."""
    top = posixpath.normpath(top)
    if top not in _DIRS:
        if not os.path.isdir(_L(top)):
            return
        _scan(top)
    stack = [top]
    while stack:
        dp = stack.pop()
        dn, fn = _DIRS[dp]
        IO_ERRORS.extend(_SCAN_ERRORS.get(dp, ()))
        yield dp, list(dn), list(fn)
        stack.extend(posixpath.join(dp, d) for d in reversed(dn) if posixpath.join(dp, d) in _DIRS)


def _norm_bytes(b: bytes) -> bytes:
    return b.replace(b"\r\n", b"\n")


def _harvest_transform(b: bytes) -> bytes:
    """What Polygeist's harvest.py wrote for a file: text decoded with replacement, HLSyn placeholders
    instantiated (auto{__PARA__L} -> 2, auto{__TILE__L} -> 1, `pipeline auto{__PIPE__L}` -> `pipeline`)."""
    t = b.decode("utf-8", errors="replace")
    t = re.sub(r"(pipeline\s+)auto\{__PIPE__\w+\}", r"\1", t, flags=re.I)
    t = re.sub(r"auto\{__PARA__\w+\}", "2", t)
    t = re.sub(r"auto\{__TILE__\w+\}", "1", t)
    return t.encode("utf-8")


def _rel(path: str, base: str) -> str:
    return posixpath.relpath(path.replace("\\", "/"), base.replace("\\", "/"))


def _c_files(d: str) -> list[str]:
    out = []
    for dp, _, fn in _walk(d):
        out += [posixpath.join(dp, f) for f in fn if posixpath.splitext(f)[1].lower() in C_SRC_EXT]
    return out


def _headers(d: str) -> list[str]:
    out = []
    for dp, _, fn in _walk(d):
        out += [posixpath.join(dp, f) for f in fn if posixpath.splitext(f)[1].lower() in HDR_EXT]
    return out


def _has_set_top(text: str) -> bool:
    return bool(SET_TOP_LINE.search(text))


def evaluate_script(design_dir: str, script: str, env=None, links=None, text_override=None) -> TclSubset:
    t = TclSubset(design_dir, env=env, links=links)
    if text_override is None:
        t.run_file(script)
    else:
        t.script_stack.append(posixpath.join(design_dir, script))
        try:
            for words in _split_commands(text_override):
                try:
                    t.call(t._words(words))
                except (TclError, _TclBreak, _TclContinue, _TclReturn) as e:
                    t.errors.append(f"{script}: {' '.join(x for _, x in words)[:100]!r}: {e}")
        except _TclExit:
            pass
        except TclError as e:
            t.errors.append(f"{script}: parse: {e}")
    return t


def _sources_from_tcl(t: TclSubset, design_dir: str) -> tuple[list[str], list[str], list[str]]:
    """(design sources as paths relative to design_dir, header files named by add_files, notes).
    A file the script adds both as a design file and with -tb is a testbench file unless it defines the top:
    hp_fft_hls's common.tcl and hlsyn-vitis' project.tcl add testbench.cpp (main, file I/O) both ways, and
    cgeist --function='*' would lower its main too.  The file that defines the top stays a design source:
    Vitis compiles every design file and synthesizes the top from it (accelerators/DGNN_Booster_* add their
    only design file, top and main, both ways).  A both-ways file that defines only functions the top calls
    would still be dropped (no such design known; what Vitis does with both-ways files is unconfirmed)."""
    srcs, hdrs, notes = [], [], []
    tb_files = {posixpath.normpath(f["abs"]) for f in t.files if f["tb"]}
    for f in t.files:
        if f["tb"]:
            continue
        p = f["abs"]
        if posixpath.normpath(p) in tb_files:
            if not (_isfile(p) and _defines_function(p, t.top)):
                notes.append(f"add_files {f['path']}: also added with -tb; treated as a testbench file")
                continue
            notes.append(f"add_files {f['path']}: also added with -tb; kept as a design file "
                         f"(it defines the top {t.top})")
        if _isdir(p):
            for c in _c_files(p):
                srcs.append(c)
            continue
        if not _isfile(p):
            name = posixpath.basename(f["path"].replace("\\", "/"))
            hits = [posixpath.join(dp, x) for dp, _, fn in _walk(design_dir) for x in fn if x == name] if name else []
            if hits:
                notes.append(f"add_files {f['path']}: not found; resolved by name to {_rel(hits[0], design_dir)}")
                p = hits[0]
            else:
                notes.append(f"add_files {f['path']}: not found")
                continue
        ext = posixpath.splitext(p)[1].lower()
        if ext in C_SRC_EXT:
            srcs.append(p)
        elif ext in HDR_EXT:
            hdrs.append(p)
        else:
            notes.append(f"add_files {f['path']}: not a C/C++ file")
    seen, out = set(), []
    for s in srcs:
        r = _rel(s, design_dir)
        if r not in seen:
            seen.add(r)
            out.append(r)
    return out, [_rel(h, design_dir) for h in hdrs], notes


C_COMMENT = re.compile(r"//[^\n]*|/\*.*?\*/", re.S)


def _text_defines_function(text: str, name: str) -> bool:
    """Whether C/C++ `text` defines a function `name`: the name right after a type-like token (identifier,
    `>`, `*`, `&`; optionally qualified `ns::`), a parameter list without ';', braces or parentheses, then
    `{` (after an optional const), comments removed.  A call (`name(a);`, `x = name(a)`, `if (n * name(a)) {`)
    is not a definition; neither is a definition with a function-pointer parameter (the rule then treats the
    file as before the fix).  A heuristic for the both-ways rule of _sources_from_tcl."""
    if not name:
        return False
    pat = r"[\w>*&]\s*(?:\w+\s*::\s*)*\b" + re.escape(name) + r"\s*\([^;{}()]*\)\s*(?:const\s*)?\{"
    return re.search(pat, C_COMMENT.sub(" ", text)) is not None


def _defines_function(path: str, name: str) -> bool:
    try:
        return _text_defines_function(_read_text(path), name)
    except OSError as e:
        _io_error(path, "read", e)
        return False


def _cflag_parts(t: TclSubset, design_dir: str):
    incs, defs, other = [], [], []
    for f in t.files:
        if f["tb"] or not f["cflags"]:
            continue
        toks = list_elements(f["cflags"])
        k = 0
        while k < len(toks):
            x = toks[k]
            if x in ("-I", "-D") and k + 1 < len(toks):
                x, k = x + toks[k + 1], k + 1
            if x.startswith("-I"):
                p = t.resolve(x[2:])
                r = _rel(p, design_dir)
                v = r if not r.startswith("..") else p
                if v not in incs:
                    incs.append(v.rstrip("/") or ".")
            elif x.startswith("-D"):
                if x[2:] not in defs:
                    defs.append(x[2:])
            elif x not in other:
                other.append(x)
            k += 1
    return incs, defs, other


def _default_includes(design_dir: str) -> list[str]:
    return ["."] + [s for s in INCLUDE_SUBDIRS if _isdir(posixpath.join(design_dir, s))]


def _lang(src: str) -> str:
    return {".c": "c", ".cc": "cpp", ".cpp": "cpp", ".cxx": "cpp"}.get(posixpath.splitext(src)[1].lower(),
                                                                         "unknown")


def _safe_name(rel: str) -> str:
    return rel.replace("/", "__").replace(" ", "_")


def _key_parts(rel: str) -> tuple[str, str]:
    """design path below hls_dataset_sources -> (dataset, benchmark), the Polygeist naming."""
    ds = rel.split("/")[0]
    return ds, (_safe_name(rel) if rel == ds else _safe_name(rel)[len(ds) + 2:])


def _entry_record(rel, ddir, script, t, config, flows, cfg, extra_includes=(), notes=(), virtual=False):
    """A v2 design record (pointing at the HLSFactory_v2 directory) from an evaluated script."""
    srcs, named_hdrs, snotes = _sources_from_tcl(t, ddir)
    rule = "tcl"
    if any("resolved by name" in n for n in snotes):
        rule = "tcl+name"
    if not srcs:
        srcs = [_rel(c, ddir) for c in _c_files(ddir) if not TB_NAME.search(Path(c).stem)]
        rule = "fallback"
        snotes.append("no add_files design source resolved: every C/C++ file of the design tree "
                      "except testbench-like names (the harvest's fallback)")
    incs, defs, other = _cflag_parts(t, ddir)
    includes = []
    for x in list(_default_includes(ddir)) + list(extra_includes) + incs:
        if x not in includes:
            includes.append(x)
    ds, bench = _key_parts(rel)
    from_wsl = ddir.replace("\\", "/")
    tcl = {"script": script, "part": t.part, "clock": t.clock, "clock_ns": clock_ns(t.clock),
           "flow_target": t.flow_target, "actions": sorted(set(t.actions)),
           "directives": len(t.directives), "configs": t.configs[:20],
           "sourced": [_rel(s, ddir) for s in t.sourced], "missing_sources": t.missing,
           "unknown_commands": dict(t.unknown), "errors": t.errors[:20],
           "unset_env": sorted(t.unset_env), "named_headers": named_hdrs, "cflags_other": other}
    return {
        "dataset": ds, "benchmark": bench, "slug": re.sub(r"[^\w.+-]+", "_", bench),
        "top": t.top, "mode": "v2", "reason": "",
        "dir": from_wsl, "win_dir": None, "sources": srcs, "includes": includes, "defines": defs,
        "cgeist_args": [], "function_arg": "*", "expect_nonzero_exit": False, "lit_includes": [],
        "test_file": None, "lang": _lang(srcs[0]) if srcs else "unknown",
        "origin": "hlsfactory_v2", "flows": flows,
        "v2_dir": from_wsl, "v2_win_dir": None, "source_match": "new",
        "v2": {"rel": rel, "config": config, "toml": cfg, "tcl": tcl, "source_rule": rule,
               "source_notes": list(notes) + snotes, "virtual_dir": virtual},
    }


def discover(root: str, problems: list[str]) -> tuple[list[dict], list[dict]]:
    """All v2 designs (records pointing at the HLSFactory_v2 tree) and the skipped entries
    [{rel, reason}]."""
    src_root = _sources_root(root)
    if not _isdir(src_root):
        problems.append(f"{src_root}: HLSFactory dataset directory not found")
        return [], []
    designs, skipped = [], []
    dirs = []                                    # (rel, abs, files)
    for ds in _listdir(src_root):
        dpath = posixpath.join(src_root, ds)
        if not _isdir(dpath) or ds.startswith((".", "__")):
            continue
        if ds in DATASET_NOTES:
            skipped.append({"rel": ds, "reason": DATASET_NOTES[ds]})
            continue
        for dp, _, fn in _walk(dpath):
            dirs.append((_rel(dp, src_root), dp, fn))

    sourced_by_designs: set[str] = set()
    pending_scan = []
    for rel, dp, fn in dirs:
        if CONFIG_FILENAME in fn:
            try:
                cfg = read_design_config(posixpath.join(dp, CONFIG_FILENAME))
            except (DesignConfigError, OSError, UnicodeDecodeError) as e:
                problems.append(f"{rel}/{CONFIG_FILENAME}: {e}")
                skipped.append({"rel": rel, "reason": f"invalid {CONFIG_FILENAME}: {e}"})
                continue
            flows = [f["flow_name"] for f in cfg["flows"]]
            synth = next((f for f in cfg["flows"] if f["flow_name"] == SYNTH_FLOW), None)
            if synth is None:
                skipped.append({"rel": rel, "reason": f"{CONFIG_FILENAME} has no {SYNTH_FLOW} "
                                                      f"(flows: {', '.join(flows) or 'none'})"})
                continue
            script = synth["settings"]["synth_tcl"]
            t = evaluate_script(dp, script, env=cfg["env_vars"])
            sourced_by_designs.update(t.sourced)
            if not t.top:
                skipped.append({"rel": rel, "reason": f"{script} reaches no set_top "
                                                      f"(errors: {'; '.join(t.errors[:2]) or 'none'})"})
                continue
            notes = []
            if cfg["design_name"] != posixpath.basename(dp):
                notes.append(f"toml design_name {cfg['design_name']!r} != directory name")
            if cfg["dataset_name"] != rel.split("/")[0]:
                notes.append(f"toml dataset_name {cfg['dataset_name']!r} != dataset directory")
            designs.append(_entry_record(rel, dp, script, t, "toml", flows, cfg, notes=notes))
        elif LEGACY_SYNTH_TCL in fn:
            t = evaluate_script(dp, LEGACY_SYNTH_TCL)
            sourced_by_designs.update(t.sourced)
            if not t.top:
                skipped.append({"rel": rel, "reason": f"{LEGACY_SYNTH_TCL} reaches no set_top "
                                                      f"(errors: {'; '.join(t.errors[:2]) or 'none'})"})
                continue
            designs.append(_entry_record(rel, dp, LEGACY_SYNTH_TCL, t, LEGACY_SYNTH_TCL,
                                         [f"{SYNTH_FLOW} (legacy {LEGACY_SYNTH_TCL}, no {CONFIG_FILENAME})"],
                                         None))
        else:
            cands = []
            for f in fn:
                if not f.endswith(".tcl"):
                    continue
                try:
                    text = _read_text(posixpath.join(dp, f))
                except OSError as e:
                    _io_error(posixpath.join(dp, f), "read", e)
                    continue
                if _has_set_top(text):
                    cands.append((f, text))
            if cands:
                pending_scan.append((rel, dp, cands))

    for rel, dp, cands in pending_scan:
        entries = []
        local_sourced: set[str] = set()
        evaluated = []
        for f, text in cands:
            path = posixpath.normpath(posixpath.join(dp, f))
            if path in sourced_by_designs:
                skipped.append({"rel": f"{rel}/{f}", "reason": "library script: sourced by the synthesis "
                                                                "script of other designs"})
                continue
            tkey = _rel(path, _sources_root(root))
            if tkey in TEMPLATE_RULES:
                designs.extend(_expand_template(root, rel, dp, f, text, TEMPLATE_RULES[tkey], problems))
                continue
            if PLACEHOLDER.search(re.sub(r"(?m)^\s*#.*$", "", text)):
                skipped.append({"rel": f"{rel}/{f}", "reason": "template script (@NAME@ placeholders) "
                                                                "without a documented instantiation"})
                continue
            t = evaluate_script(dp, f)
            local_sourced.update(s for s in t.sourced if posixpath.normpath(s) != path)
            evaluated.append((f, path, t))
        for f, path, t in evaluated:
            if path in local_sourced:
                skipped.append({"rel": f"{rel}/{f}", "reason": "sourced by another script of the directory"})
                continue
            if not t.top:
                skipped.append({"rel": f"{rel}/{f}", "reason": "evaluated script reaches no set_top"})
                continue
            notes = []
            if "csynth_design" not in t.actions and not t.mentions_csynth:
                notes.append(f"{f} sets up the project but has no csynth_design (commented out)")
            entries.append(_entry_record(rel, dp, f, t, "tcl-scan",
                                         [f"{SYNTH_FLOW} (Tcl project {f}; no {CONFIG_FILENAME} or "
                                          f"{LEGACY_SYNTH_TCL})"], None, notes=notes))
        # one design per (top, sources): prefer the script with fewest notes, then by name
        merged: dict = {}
        for e in entries:
            k = (e["top"], tuple(sorted(e["sources"])))
            score = (len(e["v2"]["source_notes"]) + len(e["v2"]["tcl"]["errors"]), e["v2"]["tcl"]["script"])
            if k not in merged or score < merged[k][0]:
                if k in merged:
                    e["v2"].setdefault("same_design_scripts", []).extend(
                        [merged[k][1]["v2"]["tcl"]["script"]] + merged[k][1]["v2"].get("same_design_scripts", []))
                merged[k] = (score, e)
            else:
                merged[k][1]["v2"].setdefault("same_design_scripts", []).append(e["v2"]["tcl"]["script"])
        kept = [e for _, e in sorted(merged.values(), key=lambda x: x[0][1])]
        if len(kept) > 1:
            for e in kept:
                e["v2"]["multi_script_dir"] = True
        designs.extend(kept)
    out = []
    for d in designs:
        if d["sources"]:
            out.append(d)
        else:
            skipped.append({"rel": f"{d['v2']['rel']}/{d['v2']['tcl']['script']}",
                            "reason": "no design source file exists ("
                                      + "; ".join(d["v2"]["source_notes"][:2]) + ")"})
    _drain_io_errors(problems)
    return out, skipped


def _expand_template(root, rel, dp, script, text, rule, problems) -> list[dict]:
    """TEMPLATE_RULES: one design per module, evaluated as the dataset's Makefile would run it."""
    ds_dir = posixpath.join(_sources_root(root), rel.split("/")[0])
    out = []
    mods = _glob_paths(ds_dir, rule["modules"])
    for mpath in mods:
        m = posixpath.splitext(posixpath.basename(mpath))[0]
        links = {k.format(m=m): posixpath.normpath(posixpath.join(ds_dir, v.format(m=m)))
                 for k, v in rule["links"].items()}
        inst = text.replace(rule["placeholder"], m)
        t = evaluate_script(ds_dir, posixpath.join(_rel(dp, ds_dir), script), links=links,
                            text_override=inst)
        vrel = f"{rel.split('/')[0]}/{m}"
        rec = _entry_record(vrel, ds_dir, posixpath.join(_rel(dp, ds_dir), script), t, "template",
                            [f"{SYNTH_FLOW} (template {_rel(posixpath.join(dp, script), ds_dir)} instantiated "
                             f"for {m})"], None, extra_includes=rule.get("project_includes", ()),
                            notes=[f"{rule['placeholder']} = {m} (dataset Makefile rule)"], virtual=True)
        out.append(rec)
    if not mods:
        problems.append(f"{rel}/{script}: template rule matched no module")
    return out


# =====================================================================================================
# comparison with the Polygeist copy
# =====================================================================================================
INCLUDE_LINE = re.compile(rb'^[ \t]*#[ \t]*include[ \t]*([<"])([^">\r\n]+)[">]', re.M)


def _file_set(ddir: str, sources: list[str], includes=(".",)) -> dict[str, bytes | None]:
    """{path relative to ddir: content} for the sources, every header of the tree, and every file outside
    the tree that their #include lines reach (quoted: the including file's directory, then the include
    dirs; angle brackets: the include dirs), followed transitively.  Files the copy cannot see (e.g. a
    ../host/typedefs.h that only the HLSFactory tree has) make two trees differ."""
    paths = {}
    for s in sources:
        paths[posixpath.normpath(s)] = posixpath.join(ddir, s)
    for h in _headers(ddir):
        paths.setdefault(_rel(h, ddir), h)
    inc_dirs = [posixpath.normpath(posixpath.join(ddir, i)) for i in includes]
    out: dict = {}
    todo = list(paths.items())
    while todo:
        r, p = todo.pop()
        if r in out:
            continue
        try:
            out[r] = _read_bytes(p)
        except OSError as e:
            _io_error(p, "read", e)
            out[r] = None
            continue
        for kind, name in INCLUDE_LINE.findall(out[r]):
            name = name.decode("utf-8", errors="replace").strip()
            bases = ([posixpath.dirname(p)] if kind == b'"' else []) + inc_dirs
            for b in bases:
                q = posixpath.normpath(posixpath.join(b, name))
                if _isfile(q):
                    rq = _rel(q, ddir)
                    if rq not in out and rq not in paths:
                        paths[rq] = q
                        todo.append((rq, q))
                    break
    return out


def compare_sources(v2_dir, v2_sources, pg_dir, pg_sources, v2_includes=(".",),
                    pg_includes=(".",)) -> tuple[str, dict]:
    a = _file_set(v2_dir, v2_sources, v2_includes)
    b = _file_set(pg_dir, pg_sources, pg_includes)
    diff = {"only_v2": sorted(set(a) - set(b)), "only_polygeist": sorted(set(b) - set(a)),
            "changed": [], "harvest_transformed": [],
            "sources_v2": sorted(posixpath.normpath(s) for s in v2_sources),
            "sources_polygeist": sorted(posixpath.normpath(s) for s in pg_sources)}
    for r in sorted(set(a) & set(b)):
        x, y = a[r], b[r]
        if x is None or y is None:
            diff["changed"].append(r)
            continue
        xn, yn = _norm_bytes(x), _norm_bytes(y)
        if xn == yn:
            continue
        if _norm_bytes(_harvest_transform(xn)) == yn:
            diff["harvest_transformed"].append(r)
        else:
            diff["changed"].append(r)
    if diff["sources_v2"] != diff["sources_polygeist"] or diff["only_v2"] or diff["only_polygeist"]:
        return "file-set-differs", diff
    if diff["changed"]:
        return "content-differs", diff
    if diff["harvest_transformed"]:
        return "identical-after-harvest", diff
    return "identical", diff


def content_hash(ddir: str, sources: list[str], includes=(".",)) -> str:
    h = hashlib.sha256()
    for r, b in sorted(_file_set(ddir, sources, includes).items()):
        h.update(r.encode() + b"\0" + (_norm_bytes(b) if b is not None else b"<unreadable>") + b"\0")
    return h.hexdigest()[:16]


def load(root: str, polygeist_records: list[dict], test_hls_wsl: str, problems: list[str],
         to_win=None) -> tuple[list[dict], dict]:
    """The v2 catalogue (see module doc) and a report dict {skipped, vanished, polygeist_root}."""
    raw, skipped = discover(root, problems)
    inputs = posixpath.join(test_hls_wsl.rstrip("/"), "hlsfactory", "Inputs")
    pg_by_rel = {}
    for d in polygeist_records:
        pg_by_rel.setdefault(_rel(d["dir"], inputs), []).append(d)
    by_rel = defaultdict(list)
    for r in raw:
        by_rel[r["v2"]["rel"]].append(r)
    out, used_keys = [], set()
    matched_pg = set()
    for rel in sorted(by_rel):
        recs = by_rel[rel]
        pgs = pg_by_rel.get(rel, [])
        pg = pgs[0] if pgs else None
        # the record that keeps the directory's key: the one whose top is the Polygeist top, else the first
        lead = None
        if pg is not None:
            same_top = [r for r in recs if r["top"] == pg["top"]]
            lead = max(same_top, key=lambda r: len(set(r["sources"]) & set(pg["sources"]))) if same_top else recs[0]
        for r in recs:
            if len(recs) > 1 and r is not lead:
                r["benchmark"] += "__" + _safe_name(posixpath.splitext(r["v2"]["tcl"]["script"])[0])
                r["slug"] = re.sub(r"[^\w.+-]+", "_", r["benchmark"])
            if r is lead:
                matched_pg.add(id(pg))
                r["dataset"], r["benchmark"], r["slug"] = pg["dataset"], pg["benchmark"], pg["slug"]
                r["v2"]["polygeist_top"] = pg["top"]
                if r["top"] != pg["top"]:
                    status, diff = "top-differs", {}
                else:
                    status, diff = compare_sources(r["dir"], r["sources"], pg["dir"], pg["sources"],
                                                   r["includes"], pg.get("includes") or ["."])
                r["source_match"] = status
                r["v2"]["source_diff"] = diff
                r["v2"]["polygeist_mode"] = pg.get("mode")
                keep = {k: r[k] for k in ("origin", "flows", "v2_dir", "v2_win_dir", "source_match", "v2")}
                keep["v2"]["v2_sources"] = r["sources"]
                keep["v2"]["v2_includes"] = r["includes"]
                keep["v2"]["v2_defines"] = r["defines"]
                if status in ("identical", "identical-after-harvest"):
                    # the Polygeist record itself (cache keys and earlier results stay valid)
                    r = dict(pg)
                    r.update(keep)
                elif (status == "file-set-differs" and diff.get("harvest_transformed") and not diff["only_v2"]
                      and not diff["changed"]):
                    # the v2 files are HLSyn templates (auto{__PARA__...} pragmas) that only the copy
                    # instantiates, and the copy has every file of the v2 design: compile the copy's files
                    # with the v2 source list
                    srcs, defs = r["sources"], r["defines"]
                    r = dict(pg)
                    r.update(keep)
                    r.update(sources=srcs, defines=defs, mode="v2", lang=_lang(srcs[0]))
                    r["v2"]["source_notes"] = r["v2"]["source_notes"] + [
                        "compiled from the Polygeist copy, whose harvest instantiated the HLSyn placeholders "
                        "(auto{__PARA__*} = 2, auto{__TILE__*} = 1, pipeline auto{__PIPE__*} = pipeline)"]
            key = f"{r['dataset']}/{r['benchmark']}"
            if key in used_keys:
                problems.append(f"{key}: duplicate key in the v2 catalogue ({rel})")
                continue
            used_keys.add(key)
            if to_win:
                r["win_dir"] = r.get("win_dir") or to_win(r["dir"])
                r["v2_win_dir"] = to_win(r["v2_dir"])
            r["v2"]["content_hash"] = content_hash(r["v2_dir"], r["v2"].get("v2_sources", r["sources"]),
                                                   r["v2"].get("v2_includes", r["includes"]))
            r["v2"]["wip"] = rel.split("/")[0] == "WIP"
            out.append(r)
    vanished = [{"key": f"{d['dataset']}/{d['benchmark']}", "rel": _rel(d["dir"], inputs), "top": d["top"],
                 "mode": d.get("mode")}
                for d in polygeist_records if id(d) not in matched_pg]
    _drain_io_errors(problems)
    return out, {"skipped": skipped, "vanished": vanished, "root": root}


def catalogue_report(records: list[dict], info: dict) -> str:
    """Plain-text summary: per dataset designs / source-match classes, skipped and vanished entries."""
    per = defaultdict(Counter)
    for r in records:
        per[r["dataset"]][r["source_match"]] += 1
    cols = ["identical", "identical-after-harvest", "content-differs", "file-set-differs", "top-differs", "new"]
    w = max([7] + [len(k) for k in per])
    lines = [f"{'dataset':<{w}}  {'total':>5}  " + "  ".join(f"{c:>{max(len(c), 5)}}" for c in cols)]
    tot = Counter()
    for ds in sorted(per):
        c = per[ds]
        tot.update(c)
        lines.append(f"{ds:<{w}}  {sum(c.values()):>5}  " + "  ".join(f"{c[k]:>{max(len(k), 5)}}" for k in cols))
    lines.append(f"{'TOTAL':<{w}}  {sum(tot.values()):>5}  " + "  ".join(f"{tot[k]:>{max(len(k), 5)}}" for k in cols))
    lines.append(f"\nskipped ({len(info['skipped'])}):")
    lines += [f"  {s['rel']}: {s['reason']}" for s in info["skipped"]]
    lines.append(f"\nPolygeist designs not in v2 ({len(info['vanished'])}):")
    lines += [f"  {v['key']} (top {v['top']}, lit mode {v['mode']})" for v in info["vanished"]]
    return "\n".join(lines)


# =====================================================================================================
# self checks (python3 hlsfactory_v2.py [--toml-root <HLSFactory root>])
# =====================================================================================================
def _self_test() -> None:
    t = TclSubset("/nonexistent")
    ev = t.eval
    assert list_elements('a {b c} "d e" {}') == ["a", "b c", "d e", ""]
    assert list_format(["a", "b c", ""]) == "a {b c} {}"
    assert ev("set x [list a {b c}]; llength $x") == "2"
    assert ev("lindex $x 1") == "b c"
    assert ev("expr {1000.0 / 250}") == "4.0"
    assert ev("expr {7 / 2}") == "3"
    assert ev("expr {1 + 2 * 3}") == "7"
    assert ev('set argv [list atax syn]; expr {[lindex $argv 1] == "syn"}') == "1"
    assert ev('expr {[lindex $argv 1] eq "csim" ? 1 : 2}') == "2"
    assert ev('if {[lindex $argv 1] == "csim"} {set r a} elseif {[lindex $argv 1] == "syn"} {set r b} else {set r c}') == "b"
    assert ev("proc f {a {b 2}} {return [expr {$a * $b}]}; f 3") == "6"
    assert ev("set s 0; foreach {i j} {1 2 3 4} {incr s $j}; set s") == "6"
    assert ev('set p "x"; append p y; string toupper $p') == "XY"
    ev('set src_path "."; set fs [list "$src_path/a.cpp" \\n "$src_path/tb.cpp"]; '
       'foreach f $fs {add_files $f}; add_files -tb "$src_path/tb.cpp" -cflags "-DX -I inc"')
    assert [(f["path"], f["tb"]) for f in t.files] == [("./a.cpp", False), ("./tb.cpp", False), ("./tb.cpp", True)]
    assert t.files[-1]["cflags"] == "-DX -I inc"
    ev("set_top {kernel_atax}; create_clock -period 300MHz -name default; set_directive_pipeline f/L")
    assert t.top == "kernel_atax" and clock_ns(t.clock) == 3.3333 and len(t.directives) == 1
    try:
        ev("set_part $env(TARGET_PART_NUM)")
        raise AssertionError("unset env read")
    except TclError:
        assert "TARGET_PART_NUM" in t.unset_env
    t2 = TclSubset("/nonexistent")
    try:
        t2.eval("set_top a\nexit\nset_top b")
    except _TclExit:
        pass
    assert t2.top == "a"
    doc = 'design_name = "x" # c\ndataset_name = \'y\'\ntags = []\n[env_vars]\nA = "1"\n\n[[flow_configs]]\n' \
          'flow_name = "VitisHLSSynthFlow"\nsynth_tcl = "dataset_hls.tcl"\n'
    cfg = design_config_from_mapping(parse_toml_subset(doc))
    assert cfg["flows"][0]["settings"]["synth_tcl"] == "dataset_hls.tcl" and cfg["env_vars"] == {"A": "1"}
    for text, want in [("void k(int a[4]) {", True), ("void\nk (int *a,\n int n)\n{", True),
                       ("ap_uint<8> k(ap_uint<8> x) const {", True), ("void ns::k(int a) {", True),
                       ('extern "C" { void k(int a[4]){ a[0] = 1; } }', True),
                       ("int main() { k(a); return 0; }", False), ("x = k(a); if (k(b)) { y(); }", False),
                       ("void k(int a[4]);", False), ("// void k(int a) {\n", False),
                       ("/* void k(int a) { */ int z;", False), ("void kk(int a) {", False),
                       ("if (n * k(a)) { y(); }", False), ("while (a > k(b)) {", False),
                       ("if (x && k(a)) {", False)]:
        assert _text_defines_function(text, "k") == want, text


def _check_toml(root: str) -> int:
    """Every hlsfactory.toml: the subset reader == tomllib (run with a Python that has tomllib)."""
    if _tomllib is None:
        print("tomllib not available (Python < 3.11): nothing to compare against")
        return 1
    n = bad = 0
    for dp, _, fn in _walk(_sources_root(root)):
        if CONFIG_FILENAME in fn:
            p = posixpath.join(dp, CONFIG_FILENAME)
            n += 1
            text = _read_bytes(p).decode("utf-8")
            a, b = parse_toml_subset(text), _tomllib.loads(text)
            if a != b or design_config_from_mapping(a) != design_config_from_mapping(b):
                bad += 1
                print(f"MISMATCH {p}")
    print(f"{n} {CONFIG_FILENAME} files, {bad} mismatches between the subset reader and tomllib")
    return 1 if bad else 0


if __name__ == "__main__":
    import sys
    _self_test()
    print("self test ok")
    if len(sys.argv) > 2 and sys.argv[1] == "--toml-root":
        sys.exit(_check_toml(sys.argv[2]))
