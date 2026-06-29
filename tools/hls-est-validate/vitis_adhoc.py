#!/usr/bin/env python3
"""Synthesize one ad-hoc kernel with Vitis HLS (for behaviour experiments).

    python3 vitis_adhoc.py --name lutram_d64_w16 --src k.cpp --top k
                           [--cflags "-I..."] [--td off|auto] [--extra "syn.x=y" ...]
                           [--part ...] [--clock ...] [--force] [--keep] [--json out.json] [--quiet]

Runs under D:/HLS/hls-est-vitis/exp/<name>, keeps reports/log/db under
~/hls-est-work/experiments/<name>/ and prints a compact summary: totals, every
memory row of every module, the loop table and the transformation messages
(auto pipeline, unroll, array partition, replication, storage inference).
Results are cached on (source hash, top, config); --force re-runs.
"""
import argparse
import json
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C          # noqa: E402
import vitis_parse as VP    # noqa: E402
import run_vitis as RV      # noqa: E402

EXP_WIN = "D:/HLS/hls-est-vitis/exp"
EXP_WSL = "/mnt/d/HLS/hls-est-vitis/exp"
EXP_CACHE = Path.home() / "hls-est-work" / "experiments"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--name", required=True)
    ap.add_argument("--src", required=True, nargs="+", help="source file(s) (WSL paths)")
    ap.add_argument("--top", required=True)
    ap.add_argument("--cflags", default="")
    ap.add_argument("--td", default="off", choices=["off", "auto"],
                    help="syn.array_partition.throughput_driven")
    ap.add_argument("--extra", action="append", default=[], help="extra [hls] config lines")
    ap.add_argument("--part", default=C.PART)
    ap.add_argument("--clock", default=C.CLOCK)
    ap.add_argument("--timeout", type=int, default=1800)
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--keep", action="store_true")
    ap.add_argument("--json", default=None)
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args()

    name = re.sub(r"[^A-Za-z0-9_.-]", "_", args.name)
    srcs = [Path(s).resolve() for s in args.src]
    for s in srcs:
        if not s.exists():
            sys.exit(f"no such source: {s}")
    # Vitis (Windows) cannot open //wsl.localhost paths: stage the sources on D:.
    work_wsl = f"{EXP_WSL}/{name}"
    shutil.rmtree(work_wsl, ignore_errors=True)
    (Path(work_wsl) / "src").mkdir(parents=True, exist_ok=True)
    staged = []
    for s in srcs:
        dst = Path(work_wsl) / "src" / s.name
        shutil.copy2(s, dst)
        staged.append(dst)
    cfg_lines = [f"part={args.part}", "", "[hls]", f"flow_target={C.FLOW_TARGET}"]
    for s in staged:
        sw = C.wsl_to_win(s)
        cfg_lines.append(f"syn.file={sw}")
        if args.cflags:
            cfg_lines.append(f"syn.file_cflags={sw},{args.cflags}")
    cfg_lines += [f"syn.top={args.top}", f"clock={args.clock}",
                  f"syn.array_partition.throughput_driven={args.td}"] + args.extra
    cfg = "\n".join(cfg_lines) + "\n"
    key = C.sha256_of_files(srcs, cfg)[:12]
    cdir = EXP_CACHE / name / key
    res_path = cdir / "result.json"
    if res_path.exists() and not args.force:
        result = C.load_json(res_path)
        result["cached"] = True
    else:
        cfg_wsl = Path(work_wsl) / "hls_config.cfg"
        cfg_wsl.write_text(cfg)
        cmd = (f"{C.VITIS_SETTINGS_BAT} && {C.VITIS_VPP_BAT} -c --mode hls "
               f"--config {C.win_backslash(cfg_wsl)} --work_dir {C.win_backslash(Path(work_wsl) / 'hls')}")
        t0 = time.time()
        status, note = "ok", ""
        try:
            p = subprocess.run([C.CMD_EXE, "/c", cmd], cwd=work_wsl, capture_output=True, text=True,
                               errors="replace", timeout=args.timeout)
            (Path(work_wsl) / "vpp_stdout.txt").write_text(p.stdout + "\n--- stderr ---\n" + p.stderr)
            if p.returncode != 0:
                status = "vitis failed"
                errs = re.findall(r"^ERROR: .*$", p.stdout, re.M)
                note = (errs[0] if errs else f"exit {p.returncode}")[:400]
        except subprocess.TimeoutExpired:
            status, note = "vitis timeout", f"{args.timeout}s"
            RV.kill_windows_tree(f"{EXP_WIN}/{name}".replace("/", "\\"))
        elapsed = time.time() - t0
        parsed = VP.parse_work_dir(Path(work_wsl) / "hls", args.top)
        if status == "ok" and not parsed.get("ok"):
            status, note = "vitis failed", "no csynth report"
        result = {"name": name, "top": args.top, "status": status, "note": note, "elapsed_s": round(elapsed, 1),
                  "cfg": cfg, "sources": [str(s) for s in srcs], "vitis_version": parsed.get("Version"),
                  "totals": VP.totals_from(parsed) if parsed.get("ok") else {},
                  "memories": parsed.get("memories", []), "loops": parsed.get("loops", []),
                  "instances": parsed.get("instances", []), "modules": parsed.get("modules", {}),
                  "log": parsed.get("log", {}), "cache_dir": str(cdir), "cached": False}
        RV.harvest(Path(work_wsl) / "hls", cdir)
        shutil.copy2(cfg_wsl, cdir / "hls_config.cfg")
        for s in srcs:
            shutil.copy2(s, cdir / s.name)
        so = Path(work_wsl) / "vpp_stdout.txt"
        if so.exists():
            shutil.copy2(so, cdir / "vpp_stdout.txt")
        C.dump_json(result, res_path)
    if not args.keep:
        shutil.rmtree(work_wsl, ignore_errors=True)
    if args.json:
        C.dump_json(result, args.json)
    if not args.quiet:
        print_summary(result)


def print_summary(r):
    print(f"# {r['name']}  top={r['top']}  status={r['status']} {r.get('note', '')}  "
          f"elapsed={r.get('elapsed_s')}s {'(cached)' if r.get('cached') else ''}  cache={r.get('cache_dir')}")
    t = r.get("totals", {})
    print(f"totals: BRAM={t.get('BRAM')} DSP={t.get('DSP')} FF={t.get('FF')} LUT={t.get('LUT')}")
    print("memories (module | instance | array | bank | BRAM | words x bits | banks | core):")
    for m in r.get("memories", []):
        print(f"  {m['module'][:48]:48s} | {str(m.get('Memory')):22s} | {m['array']:18s} | {str(m['bank']):4s} | "
              f"{str(m['bram']):4s} | {m.get('Words')}x{m.get('Bits')} | {m.get('Banks')} | {m.get('core')}")
    print("loops (module | loop | II ach/target | trip | pipelined | iter latency):")
    for l in r.get("loops", []):
        print(f"  {l['module'][:48]:48s} | {l['name']:40s} | {l['ii_achieved']}/{l['ii_target']} | "
              f"{l['trip_count']} | {l['pipelined']} | {l['iter_latency']}")
    log = r.get("log", {})
    for k in ("auto_pipeline", "unroll_implied", "unroll", "partition_inferred", "partition_applied",
              "replicate", "storage_inferred", "flatten", "inline", "removed", "ii_violation", "error"):
        for e in log.get(k, []):
            print(f"  [{k}] " + " | ".join(str(x) for x in e))
    inst = [i for i in r.get("instances", []) if (i.get("BRAM_18K") or 0) > 0]
    if inst:
        print("instances with BRAM:")
        for i in inst:
            print(f"  {i.get('parent')[:40]:40s} {i.get('Instance')[:50]:50s} BRAM={i.get('BRAM_18K')}")


if __name__ == "__main__":
    main()
