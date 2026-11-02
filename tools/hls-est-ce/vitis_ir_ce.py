#!/usr/bin/env python3
"""Compiler Explorer driver: Vitis HLS 2025.1's own LLVM IR for a source, stage by stage.

    vitis_ir_ce.py [--top=NAME] [--stage=front|link|o1|o2|o3] [--function=NAME]
                   [--metadata] [--summary-only] <source>

Runs Vitis HLS csynth on the source with the ground-truth configuration (xc7z020, 10 ns,
throughput_driven off) through tools/hls-est-validate/vitis_adhoc.py, as an experiment (never
the ground-truth cache): the run is cached on the source hash, so only the first view of a source
waits for Vitis (about 1-3 min). Prints the csynth summary (BRAM/DSP/FF/LUT, memories, loops) and
the chosen IR stage from the run's db/ directory:
  front  a.g.ld.0.ll         the front end's output (clang + the ap_* headers), linked
  link   a.g.ld.5.gdce.ll    after global dead-code elimination, the input of the reflow passes
  o1     a.o.1.ll            after the first reflow passes (inlining, unrolling, partitioning)
  o2     a.o.2.ll            after the second (default)
  o3     a.o.3.ll            the last LLVM stage before scheduling
Debug metadata (!dbg and the trailing ! lines) is dropped unless --metadata is given.
"""
import hashlib
import json
import os
import re
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
VALIDATE = HERE.parent / "hls-est-validate"
STAGES = {"front": "a.g.ld.0.ll", "link": "a.g.ld.5.gdce.ll", "o1": "a.o.1.ll",
          "o2": "a.o.2.ll", "o3": "a.o.3.ll"}

HELP = """Report options:
  --stage=o2                                    a.o.2.ll: after the second reflow passes (default)
  --stage=o1                                    a.o.1.ll: after the first reflow passes (inlining, unrolling, partitioning)
  --stage=o3                                    a.o.3.ll: the last LLVM stage before scheduling
  --stage=link                                  a.g.ld.5.gdce.ll: the front end's output after global DCE (input of reflow)
  --stage=front                                 a.g.ld.0.ll: the front end's linked output
  --function=NAME                               Only the definition(s) whose name contains NAME
  --top=top                                     Top function for Vitis (default: the last function in the source)
  --metadata                                    Keep debug metadata (!dbg and the ! definitions)
  --summary-only                                Only the csynth summary, no IR
"""


def version():
    return "vitis-ir-ce 1.0 (Vitis HLS 2025.1 IR stages, xc7z020, 10 ns, td=off)"


def parse_args(argv):
    if argv and argv[0] in ("--version", "-v"):
        print(version())
        sys.exit(0)
    if "--help" in argv:
        print(HELP)
        sys.exit(0)
    opts = {"source": None, "top": None, "stage": "o2", "function": None,
            "metadata": False, "summary_only": False}
    for a in argv:
        if a.startswith("--top="):
            opts["top"] = a.split("=", 1)[1]
        elif a.startswith("--stage="):
            opts["stage"] = a.split("=", 1)[1]
        elif a.startswith("--function="):
            opts["function"] = a.split("=", 1)[1]
        elif a == "--metadata":
            opts["metadata"] = True
        elif a == "--summary-only":
            opts["summary_only"] = True
        elif a.startswith("-"):
            sys.exit(f"vitis-ir-ce: unknown option {a!r} (see --help)")
        elif opts["source"] is None:
            opts["source"] = a
        else:
            sys.exit(f"vitis-ir-ce: unexpected argument {a!r}")
    if opts["source"] is None:
        sys.exit("vitis-ir-ce: no source file")
    if opts["stage"] not in STAGES:
        sys.exit("vitis-ir-ce: --stage must be one of " + ", ".join(STAGES))
    return opts


def default_top(src):
    """The last function defined in the source (Compiler Explorer gives no top)."""
    text = re.sub(r"/\*.*?\*/|//[^\n]*", "", open(src, errors="replace").read(), flags=re.S)
    names = re.findall(r"\b([A-Za-z_]\w*)\s*\([^;{)]*\)\s*\{", text)
    names = [n for n in names if n not in ("if", "for", "while", "switch", "main")]
    return names[-1] if names else "top"


def run_vitis(src, top):
    """Run (or reuse) the cached Vitis experiment; returns its result dict."""
    digest = hashlib.sha256(open(src, "rb").read()).hexdigest()[:12]
    out = Path(os.environ.get("VITIS_IR_CE_TMP", "/tmp")) / f"vitis-ir-ce-{digest}-{top}.json"
    cmd = [sys.executable, str(VALIDATE / "vitis_adhoc.py"), "--name", f"ce_{digest}",
           "--src", str(src), "--top", top, "--json", str(out), "--quiet"]
    p = subprocess.run(cmd, capture_output=True, text=True, errors="replace")
    if not out.exists():
        sys.exit("// Vitis HLS run failed\n" + "\n".join(
            "// " + l for l in (p.stdout + p.stderr).splitlines()[-30:]))
    return json.load(open(out))


def summary(res, top):
    t = res.get("totals") or {}
    lines = [f"// {version()}", f"// top: {top}; Vitis run {'(cached) ' if res.get('cached') else ''}"
             f"status {res.get('status')}; experiment {res.get('cache_dir')}",
             "// csynth: BRAM_18K {} DSP {} FF {} LUT {}".format(
                 t.get("BRAM"), t.get("DSP"), t.get("FF"), t.get("LUT"))]
    for m in res.get("memories") or []:
        if isinstance(m, dict):
            lines.append("//   memory " + ", ".join(f"{k}={m[k]}" for k in
                                                     ("module", "variable", "Words", "Bits", "Banks", "core",
                                                      "BRAM_18K")
                                                     if k in m))
    for lp in res.get("loops") or []:
        if isinstance(lp, dict):
            lines.append("//   loop " + ", ".join(f"{k}={lp[k]}" for k in
                                                   ("module", "name", "trip_count", "pipelined", "ii_target",
                                                    "ii_achieved", "iter_latency", "latency_max")
                                                   if k in lp))
    if res.get("note"):
        lines.append("// note: " + str(res["note"])[:300])
    return lines


def strip_metadata(ir):
    ir = re.sub(r", !dbg ![0-9]+", "", ir)
    ir = re.sub(r", !(?:llvm\.loop|tbaa|xlx\.\w+|fpga\.\w+|reflow\.\w+) ![0-9]+", "", ir)
    return "\n".join(l for l in ir.splitlines() if not re.match(r"^!", l)).rstrip()


def only_functions(ir, name):
    out, keep = [], False
    for l in ir.splitlines():
        if l.startswith("define "):
            keep = name in l
        if keep:
            out.append(l)
        if keep and l == "}":
            keep = False
            out.append("")
    return "\n".join(out) or f"; no definition whose name contains {name!r}"


def main():
    opts = parse_args(sys.argv[1:])
    src = Path(opts["source"]).resolve()
    top = opts["top"] or default_top(src)
    res = run_vitis(src, top)
    print("\n".join(summary(res, top)))
    if opts["summary_only"]:
        return
    ll = Path(res.get("cache_dir") or "") / "db" / STAGES[opts["stage"]]
    if not ll.exists():
        print(f"// {ll.name} is not in the run's db/ directory (Vitis failed before that stage?)")
        return
    ir = ll.read_text(errors="replace")
    if not opts["metadata"]:
        ir = strip_metadata(ir)
    if opts["function"]:
        ir = only_functions(ir, opts["function"])
    print(f"\n// === Vitis IR: {ll.name} (--stage={opts['stage']}) ===")
    print(ir)


if __name__ == "__main__":
    main()
