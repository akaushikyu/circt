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
import contextlib
import fcntl
import hashlib
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


@contextlib.contextmanager
def file_lock(path, blocking=True):
    """Exclusive flock on <path>; yields the open lock file, or None instead of waiting when
    blocking=False and another process holds it. Two runners may share a work root: each design is synthesised by one runner
    at a time (its work directory is deleted at the start of a run, which once corrupted 37 cached
    results), and the summary file is updated by read-merge-write under its own lock."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    with open(path, "a+") as f:
        try:
            fcntl.flock(f, fcntl.LOCK_EX | (0 if blocking else fcntl.LOCK_NB))
        except BlockingIOError:
            yield None
            return
        try:
            yield f
        finally:
            fcntl.flock(f, fcntl.LOCK_UN)


def update_summary(out, updates):
    """Merge {key: result} into the summary JSON at <out> as it is on disk now, so a concurrent
    runner's or a --reparse's entries are kept."""
    with LOCK, file_lock(str(out) + ".lock"):
        for k, r in list(updates.items()):
            if r.get("cached") and r.get("cache_dir"):   # read before the lock: a --reparse may have rewritten it
                fresh = C.load_json(Path(r["cache_dir"]) / "result.json")
                if fresh:
                    fresh["cached"] = True
                    updates[k] = fresh
        cur = C.load_json(out, {}) or {}
        cur.update(updates)
        C.dump_json(cur, out)
        return cur
SRC_EXT = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx", ".inc", ".tcc", ".ipp", ".dat", ".txt"}


def design_files(d):
    """All files that can influence synthesis (sources + every header in the tree)."""
    root = Path(d["dir"])
    files = []
    for p in root.rglob("*"):
        if p.is_file() and (p.suffix.lower() in SRC_EXT or p.name in d["sources"]):
            files.append(p)
    return files


EXTRA_CFG = list(C.EXTRA_HLS_CFG)   # overridden by --td


def cflags_for(d):
    flags = []
    for inc in d.get("includes", []):
        p = (Path(d["dir"]) / inc).resolve()
        flags.append("-I" + C.wsl_to_win(p))
    for df in d.get("defines", []):
        flags.append("-D" + df)
    return flags


def extra_cfg_for(td):
    """The [hls] lines a run with --td <td> adds (C.EXTRA_HLS_CFG with its throughput_driven setting)."""
    return ([l for l in C.EXTRA_HLS_CFG if not l.startswith("syn.array_partition.throughput_driven")]
            + [f"syn.array_partition.throughput_driven={td}"])


def cache_key(d, extra_cfg=None, files=None):
    """The cache key of design record d: its files, top, flags and sources, the Vitis configuration and the
    [hls] lines (extra_cfg; default this run's EXTRA_CFG)."""
    cfg = EXTRA_CFG if extra_cfg is None else extra_cfg
    extra = "|".join([d["top"], C.PART, C.CLOCK, C.VITIS_VERSION, C.FLOW_TARGET,
                      " ".join(cflags_for(d)), " ".join(d["sources"]), " ".join(cfg), "cfg-v2"])
    return C.sha256_of_files(design_files(d) if files is None else files, extra)[:16]


def cache_keys(d):
    """{td: cache key} for both --td settings: the identity of the sources a ground-truth entry was
    synthesised from (each entry records its key), which compare.py checks against the hls-est side, so a
    result from one catalogue is never compared with a design of another (two catalogues can give one
    dataset/benchmark key different sources)."""
    files = design_files(d)
    return {td: cache_key(d, extra_cfg_for(td), files) for td in ("off", "auto")}


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
    lines += EXTRA_CFG
    return "\n".join(lines) + "\n"


def kill_windows_tree(marker):
    r"""Kill every Windows process whose command line names the work dir `marker` as a path prefix.
    Vitis children (vitis_hls.exe) spell the path with forward slashes while v++ gets backslashes, so
    every separator matches either one (the -like set [\/]). The dir must be followed by a
    separator: a bare prefix would also match sibling designs whose names extend this one
    (GradCAM__src_hls vs GradCAM__src_hls__avg_pool) and kill their runs."""
    sep = r"[\/]"
    pat = "".join(sep if ch in "/\\" else ch for ch in marker.rstrip("/\\")) + sep
    ps = ("Get-CimInstance Win32_Process | Where-Object { $_.CommandLine -like '*%s*' } | "
          "ForEach-Object { Stop-Process -Id $_.ProcessId -Force -ErrorAction SilentlyContinue }") % pat
    try:
        subprocess.run([C.POWERSHELL_EXE, "-NoProfile", "-Command", ps], timeout=120,
                       capture_output=True)
    except Exception:
        pass


def windows_tree_commit_gb(marker):
    r"""Committed memory (private bytes, GB) of the Windows processes whose command line names the work
    dir `marker`, matched like kill_windows_tree. None when the query fails. Windows stopped the WSL VM
    on 2026-10-12 when one vitis_hls.exe reached 71 GB of virtual memory next to WSL's 56 GB."""
    sep = r"[\/]"
    pat = "".join(sep if ch in "/\\" else ch for ch in marker.rstrip("/\\")) + sep
    ps = ("$t = (Get-CimInstance Win32_Process | Where-Object { $_.CommandLine -like '*%s*' } | "
          "Measure-Object -Property PrivatePageCount -Sum).Sum; if ($t) { $t } else { 0 }") % pat
    try:
        r = subprocess.run([C.POWERSHELL_EXE, "-NoProfile", "-Command", ps], timeout=60,
                           capture_output=True, text=True)
        return int(r.stdout.strip().splitlines()[-1]) / 2**30
    except Exception:
        return None


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


# Vitis's IP export nests <work>/hls/hls/impl/ip/subcore_prj/subcore_prj.srcs/sources_1/ip/<ip>/<ip>.xci (the IP
# name, <top>_<core>_ip, twice) under the work dir. With a long dataset/benchmark that passes Windows' 260-byte path
# limit after csynth has finished (Common 17-680, class_ece8893_spring_2025/NeuroFPGA_Project__symbolic_HLS), and v++
# exits non-zero. Such a design gets a short hashed work dir; the work dir is not part of the cache key, so keys and
# results are unchanged. DESIGN.txt in the dir names the design.
MAX_WORK_NAME = 24


def work_name(d):
    name = f"{d['dataset']}/{d['benchmark']}"
    if len(name) <= MAX_WORK_NAME:
        return name
    return "h/" + hashlib.sha1(name.encode()).hexdigest()[:12]


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

    tag = "" if EXTRA_CFG == list(C.EXTRA_HLS_CFG) else "td-" + EXTRA_CFG[-1].split("=")[-1] + "/"
    work_wsl = f"{C.WORK_WSL_ROOT}/{tag}{work_name(d)}"
    with file_lock(work_wsl + ".lock", blocking=False) as mine:
        if not mine:
            return {"dataset": d["dataset"], "benchmark": d["benchmark"], "top": d["top"], "key": key,
                    "status": "locked", "note": "another runner is synthesising this design"}
        if res_path.exists() and not args.force:      # the other runner finished it meanwhile
            r = C.load_json(res_path)
            r["cached"] = True
            return r
        return synthesise(d, args, key, cdir, res_path, tag, work_wsl, mine.fileno())


def synthesise(d, args, key, cdir, res_path, tag, work_wsl, lock_fd):
    work_win = f"{C.WORK_WIN_ROOT}/{tag}{work_name(d)}"
    shutil.rmtree(work_wsl, ignore_errors=True)
    Path(work_wsl).mkdir(parents=True, exist_ok=True)
    (Path(work_wsl) / "DESIGN.txt").write_text(f"{d['dataset']}/{d['benchmark']}" + os.linesep)
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
        # pass_fds: the child holds the design lock too, so if this runner dies the design stays
        # locked until the Vitis run itself ends (a restarted runner would otherwise wipe its work dir)
        with open(Path(work_wsl) / "vpp.out", "w") as fo, open(Path(work_wsl) / "vpp.err", "w") as fe:
            p = subprocess.Popen([C.CMD_EXE, "/c", cmd], cwd=work_wsl, stdout=fo, stderr=fe,
                                 text=True, errors="replace", pass_fds=(lock_fd,))
            # --mem-limit-gb: poll the run's committed memory and stop it above the limit, so one design
            # cannot exhaust Windows memory and take the WSL VM down with it.
            while p.poll() is None:
                if time.time() - t0 > args.timeout:
                    raise subprocess.TimeoutExpired(cmd, args.timeout)
                time.sleep(30 if args.mem_limit_gb else 5)
                if args.mem_limit_gb and p.poll() is None:
                    gb = windows_tree_commit_gb(work_win.replace("/", "\\"))
                    if gb is not None and gb > args.mem_limit_gb:
                        status, note = "vitis memory limit", f"{gb:.1f} GB > {args.mem_limit_gb} GB"
                        kill_windows_tree(work_win.replace("/", "\\"))
                        p.kill()
                        p.wait()
                        time.sleep(3)
                        break
        out = (Path(work_wsl) / "vpp.out").read_text(errors="replace")
        err = (Path(work_wsl) / "vpp.err").read_text(errors="replace")
        (Path(work_wsl) / "vpp_stdout.txt").write_text(out + "\n--- stderr ---\n" + err)
        if status == "ok" and p.returncode != 0:
            status = "vitis failed"
            errs = re.findall(r"^ERROR: .*$", out, re.M)
            note = (errs[0] if errs else f"exit {p.returncode}")[:300]
    except subprocess.TimeoutExpired:
        status, note = "vitis timeout", f"{args.timeout}s"
        kill_windows_tree(work_win.replace("/", "\\"))
        try:
            p.kill()
        except Exception:
            pass
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


def reparse(designs, args):
    summary = C.load_json(args.out, {}) or {}
    n = 0
    for d in designs:
        k = C.design_key(d)
        r = summary.get(k)
        if not r or r.get("status") != "ok" or not r.get("cache_dir"):
            continue
        parsed = VP.parse_cache_dir(r["cache_dir"], d["top"])
        if parsed.get("ok"):
            r["totals"] = VP.totals_from(parsed)
            for f in ("memories", "loops", "instances", "modules", "log"):
                r[f] = parsed.get(f, r.get(f))
            r["bind_nodes"] = parsed.get("bind_nodes", [])
            C.dump_json(r, Path(r["cache_dir"]) / "result.json")
            n += 1
    C.dump_json(summary, args.out)
    print(f"reparsed {n} cached results -> {args.out}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--datasets", default="", help="comma list; default: all with sources")
    ap.add_argument("--benchmarks", default="", help="comma list of benchmark names")
    ap.add_argument("-j", type=int, default=6)
    ap.add_argument("--timeout", type=int, default=3600)
    ap.add_argument("--mem-limit-gb", type=float, default=0,
                    help="stop a design whose Windows processes commit more than this many GB "
                         "(status 'vitis memory limit'); 0 = no limit")
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--keep-work", action="store_true")
    ap.add_argument("--list", action="store_true")
    ap.add_argument("--out", default=str(C.RESULTS_DIR / "vitis.json"))
    ap.add_argument("--reparse", action="store_true",
                    help="rebuild the summary from the cached reports (after a parser change); no synthesis")
    ap.add_argument("--td", default="off", choices=["off", "auto"],
                    help="syn.array_partition.throughput_driven (ground truth uses 'off')")
    ap.add_argument("--catalog", choices=D.CATALOGS, default=None,
                    help="design catalogue (designs.py): 'v2' (the HLSFactory 1.1.0 tree, default) or "
                         "'polygeist' (the Polygeist lit copies; $HLS_EST_CATALOG changes the default).  A v2 design whose sources equal "
                         "its Polygeist copy is that copy's record, so its cache entry is reused")
    args = ap.parse_args()
    global EXTRA_CFG
    EXTRA_CFG = extra_cfg_for(args.td)

    catalog = args.catalog or D.default_catalog()
    designs = [d for d in D.load_designs(catalog=catalog) if d.get("sources")]
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

    if args.reparse:
        with file_lock(str(args.out) + ".lock"):
            reparse(designs, args)
        return
    print(f"{len(designs)} designs (catalogue {catalog}), -j{args.j}, timeout {args.timeout}s", flush=True)
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
            r["catalog"] = catalog          # which catalogue's record produced this summary entry
            if not args.dry_run and r.get("status") != "locked":
                update_summary(args.out, {C.design_key(d): r})
            tot = r.get("totals", {}) or {}
            print(f"[{done}/{len(designs)}] {C.design_key(d):50s} {r.get('status'):14s} "
                  f"BRAM={tot.get('BRAM')} {'(cached)' if r.get('cached') else str(r.get('elapsed_s', '')) + 's'} "
                  f"{r.get('note', '')}", flush=True)
    summary = C.load_json(args.out, {}) or {}
    n_ok = sum(1 for r in summary.values() if r.get("status") == "ok")
    print(f"done: {n_ok} ok of {len(summary)} in summary -> {args.out}")


if __name__ == "__main__":
    main()
