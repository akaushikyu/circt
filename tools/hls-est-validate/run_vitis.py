#!/usr/bin/env python3
"""Run Vitis HLS C-synthesis (ground truth) on every design, with caching.

    python3 run_vitis.py [--datasets a,b] [--benchmarks x,y] [-j 6] [--timeout 3600]
                         [--force] [--dry-run] [--list]

For each design a v++ HLS config file is generated (part, clock, sources, top,
include flags) and `v++ -c --mode hls` is run through cmd.exe (Vitis 2025.1 is
a Windows install).  Results are cached under CACHE_ROOT keyed by a hash of
(every file in the design dir, top, part, clock, Vitis version, cflags); an
unchanged design is never re-synthesized.  After a run the reports, compile log
and the .autopilot/db bitcode / schedule databases are copied into the cache
entry (and the bitcode disassembled), then the Vitis work dir is deleted.

Summary of all designs: results/vitis.json  (one entry per dataset/benchmark).
"""
import argparse
import concurrent.futures as cf
import os
import re
import shutil
import subprocess
import sys
import threading
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                       # noqa: E402
import designs as D                      # noqa: E402
import vitis_parse as VP                 # noqa: E402

LOCK = threading.Lock()
SRC_EXT = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx", ".inc", ".tcc", ".ipp", ".dat", ".txt"}


def design_files(d):
    """All files that can influence synthesis (sources + every header in the tree)."""
    root = Path(d["dir"])
    files = []
    for p in root.rglob("*"):
        if p.is_file() and (p.suffix.lower() in SRC_EXT or p.name in d["sources"]):
            files.append(p)
    return files


def cflags_for(d):
    flags = []
    for inc in d.get("includes", []):
        p = (Path(d["dir"]) / inc).resolve()
        flags.append("-I" + C.wsl_to_win(p))
    for df in d.get("defines", []):
        flags.append("-D" + df)
    return flags


def cache_key(d):
    extra = "|".join([d["top"], C.PART, C.CLOCK, C.VITIS_VERSION, C.FLOW_TARGET,
                      " ".join(cflags_for(d)), " ".join(d["sources"]), " ".join(C.EXTRA_HLS_CFG), "cfg-v2"])
    return C.sha256_of_files(design_files(d), extra)[:16]


def cache_dir(d, key):
    return C.CACHE_ROOT / d["dataset"] / d["benchmark"] / key


def make_cfg(d, work_win):
    lines = [f"part={C.PART}", "", "[hls]", f"flow_target={C.FLOW_TARGET}"]
    flags = " ".join(cflags_for(d))
    for s in d["sources"]:
        sp = C.wsl_to_win((Path(d["dir"]) / s).resolve())
        lines.append(f"syn.file={sp}")
        if flags:
            lines.append(f"syn.file_cflags={sp},{flags}")
    lines.append(f"syn.top={d['top']}")
    lines.append(f"clock={C.CLOCK}")
    lines += C.EXTRA_HLS_CFG
    return "\n".join(lines) + "\n"


def kill_windows_tree(marker):
    """Kill every Windows process whose command line mentions `marker` (the work dir)."""
    ps = ("Get-CimInstance Win32_Process | Where-Object { $_.CommandLine -like '*%s*' } | "
          "ForEach-Object { Stop-Process -Id $_.ProcessId -Force -ErrorAction SilentlyContinue }") % marker
    try:
        subprocess.run([C.POWERSHELL_EXE, "-NoProfile", "-Command", ps], timeout=120,
                       capture_output=True)
    except Exception:
        pass


def disassemble(db_dir):
    """Produce .ll next to the interesting .bc files (idempotent)."""
    wanted = ["a.g.ld.0.bc", "a.g.ld.5.gdce.bc", "a.o.1.bc", "a.o.2.bc", "a.o.3.bc"]
    for exe, env in C.LLVM_DIS_CANDIDATES:
        if not Path(exe).exists():
            continue
        e = dict(os.environ)
        e.update(env)
        ok = True
        for b in wanted:
            src = Path(db_dir) / b
            if not src.exists():
                continue
            dst = src.with_suffix(".ll")
            if dst.exists() and dst.stat().st_size > 0:
                continue
            r = subprocess.run([exe, str(src), "-o", str(dst)], env=e, capture_output=True, timeout=600)
            if r.returncode != 0:
                ok = False
        if ok:
            return True
    return False


KEEP_DB_PATTERNS = [r"^a\.g\.ld\.0\.bc$", r"^a\.g\.ld\.5\.gdce\.bc$", r"^a\.o\.[123]\.bc$",
                    r"\.adb$", r"\.adb\.xml$", r"\.verbose\.(sched|bind)?\.?rpt$", r"\.verbose\.rpt$",
                    r"^hls_data\.json$", r"^all\.directive\.json$", r"^autopilot\.flow\.log$",
                    r"^fe_messages\.xml$", r"^design\.bindinfo\.xml$", r"^cmplx\..*\.json$"]


def harvest(work_wsl, cdir):
    """Copy the useful artifacts of a finished run into the cache dir."""
    W = Path(work_wsl)
    cdir.mkdir(parents=True, exist_ok=True)
    rep = W / "hls" / "syn" / "report"
    if rep.exists():
        shutil.copytree(rep, cdir / "report", dirs_exist_ok=True)
    for name in ("hls_compile.log", "hls.steps.log"):
        p = W / "logs" / name
        if p.exists():
            (cdir / "log").mkdir(exist_ok=True)
            shutil.copy2(p, cdir / "log" / name)
    rpt = W / "reports" / "hls_compile.rpt"
    if rpt.exists():
        (cdir / "log").mkdir(exist_ok=True)
        shutil.copy2(rpt, cdir / "log" / "hls_compile.rpt")
    db = W / "hls" / ".autopilot" / "db"
    if db.exists():
        (cdir / "db").mkdir(exist_ok=True)
        rx = [re.compile(p) for p in KEEP_DB_PATTERNS]
        for p in db.iterdir():
            if p.is_file() and any(r.search(p.name) for r in rx):
                shutil.copy2(p, cdir / "db" / p.name)
        try:
            disassemble(cdir / "db")
        except Exception as e:  # noqa: BLE001
            (cdir / "db" / "DISASSEMBLY_FAILED").write_text(str(e))


def run_one(d, args):
    key = cache_key(d)
    cdir = cache_dir(d, key)
    res_path = cdir / "result.json"
    if res_path.exists() and not args.force:
        r = C.load_json(res_path)
        r["cached"] = True
        return r
    if args.dry_run:
        return {"dataset": d["dataset"], "benchmark": d["benchmark"], "status": "dry-run", "key": key}

    work_wsl = f"{C.WORK_WSL_ROOT}/{d['dataset']}/{d['benchmark']}"
    work_win = f"{C.WORK_WIN_ROOT}/{d['dataset']}/{d['benchmark']}"
    shutil.rmtree(work_wsl, ignore_errors=True)
    Path(work_wsl).mkdir(parents=True, exist_ok=True)
    cfg_wsl = Path(work_wsl) / "hls_config.cfg"
    cfg_wsl.write_text(make_cfg(d, work_win))
    cfg_win = C.win_backslash(cfg_wsl)
    wd_win = C.win_backslash(Path(work_wsl) / "hls")
    # No quotes: cmd.exe strips the outer pair when the string starts with one,
    # which breaks '"a.bat" && "b.bat"'.  None of these paths contain spaces.
    cmd = (f'{C.VITIS_SETTINGS_BAT} && {C.VITIS_VPP_BAT} -c --mode hls '
           f'--config {cfg_win} --work_dir {wd_win}')
    t0 = time.time()
    status, note = "ok", ""
    try:
        p = subprocess.run([C.CMD_EXE, "/c", cmd], cwd=work_wsl, capture_output=True,
                           text=True, errors="replace", timeout=args.timeout)
        (Path(work_wsl) / "vpp_stdout.txt").write_text(p.stdout + "\n--- stderr ---\n" + p.stderr)
        if p.returncode != 0:
            status = "vitis failed"
            errs = re.findall(r"^ERROR: .*$", p.stdout, re.M)
            note = (errs[0] if errs else f"exit {p.returncode}")[:300]
    except subprocess.TimeoutExpired:
        status, note = "vitis timeout", f"{args.timeout}s"
        kill_windows_tree(work_win.replace("/", "\\"))
        time.sleep(3)
    elapsed = time.time() - t0

    parsed = VP.parse_work_dir(Path(work_wsl) / "hls", d["top"])
    if status == "ok" and not parsed.get("ok"):
        status, note = "vitis failed", "no csynth report"
    result = {
        "dataset": d["dataset"], "benchmark": d["benchmark"], "top": d["top"], "key": key,
        "status": status, "note": note, "elapsed_s": round(elapsed, 1),
        "part": C.PART, "clock": C.CLOCK, "vitis_version": parsed.get("Version") or C.VITIS_VERSION,
        "totals": VP.totals_from(parsed) if parsed.get("ok") else {},
        "memories": parsed.get("memories", []), "loops": parsed.get("loops", []),
        "instances": parsed.get("instances", []), "modules": parsed.get("modules", {}),
        "log": parsed.get("log", {}), "cache_dir": str(cdir), "cached": False,
    }
    harvest(Path(work_wsl) / "hls", cdir)
    shutil.copy2(cfg_wsl, cdir / "hls_config.cfg")
    so = Path(work_wsl) / "vpp_stdout.txt"
    if so.exists():
        shutil.copy2(so, cdir / "vpp_stdout.txt")
    C.dump_json(result, res_path)
    if not args.keep_work:
        shutil.rmtree(work_wsl, ignore_errors=True)
    return result


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--datasets", default="", help="comma list; default: all with sources")
    ap.add_argument("--benchmarks", default="", help="comma list of benchmark names")
    ap.add_argument("-j", type=int, default=6)
    ap.add_argument("--timeout", type=int, default=3600)
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--keep-work", action="store_true")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--out", default=str(C.RESULTS_DIR / "vitis.json"))
    args = ap.parse_args()

    designs = [d for d in D.load_designs() if d.get("sources")]
    if args.datasets:
        ds = set(args.datasets.split(","))
        designs = [d for d in designs if d["dataset"] in ds]
    if args.benchmarks:
        bs = set(args.benchmarks.split(","))
        designs = [d for d in designs if d["benchmark"] in bs]
    if args.list:
        for d in designs:
            print(f"{d['dataset']}/{d['benchmark']}\ttop={d['top']}\tmode={d['mode']}\tsrcs={len(d['sources'])}")
        print(len(designs), "designs")
        return

    summary = C.load_json(args.out, {}) or {}
    print(f"{len(designs)} designs, -j{args.j}, timeout {args.timeout}s", flush=True)
    done = 0
    with cf.ThreadPoolExecutor(max_workers=args.j) as ex:
        futs = {ex.submit(run_one, d, args): d for d in designs}
        for f in cf.as_completed(futs):
            d = futs[f]
            try:
                r = f.result()
            except Exception as e:  # noqa: BLE001
                r = {"dataset": d["dataset"], "benchmark": d["benchmark"], "top": d["top"],
                     "status": "harness error", "note": repr(e)[:300]}
            done += 1
            with LOCK:
                summary[C.design_key(d)] = r
                C.dump_json(summary, args.out)
            tot = r.get("totals", {}) or {}
            print(f"[{done}/{len(designs)}] {C.design_key(d):50s} {r.get('status'):14s} "
                  f"BRAM={tot.get('BRAM')} {'(cached)' if r.get('cached') else str(r.get('elapsed_s', '')) + 's'} "
                  f"{r.get('note', '')}", flush=True)
    n_ok = sum(1 for r in summary.values() if r.get("status") == "ok")
    print(f"done: {n_ok} ok of {len(summary)} in summary -> {args.out}")


if __name__ == "__main__":
    main()
