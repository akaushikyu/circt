#!/usr/bin/env python3
"""Sweep the HLSFactory v2 catalogue through cgeist and hls-est (W8a): which designs compile, which do
not, and why.

    HLS_EST_BIN=<frozen hls-est> CGEIST_BIN=<frozen cgeist> HOME=<private home> \\
    python3 sweep_hlsfactory_v2.py [-j 8] [--timeout 120] [--datasets a,b] [--benchmarks x,y]
                                   [--out results/hlsfactory-v2-sweep.json] [--merge [--drop-stale]]

Every HLSFactory design of designs.load_hlsfactory_v2() (polybench_pragmas / basic are not HLSFactory
designs and are left out) goes through run_hlsest.process(): cgeist with run_hlsest's command, MLIR
cache and shim (the harness default), then hls-est with the default pipeline (common.DEFAULT_PIPELINE)
and the per-design top selection.  A design's record is therefore what `run_hlsest.py --catalog v2`
writes for it, plus
  wall_s        wall time of the design (cgeist + top lookup + hls-est)
  cgeist_s      wall_s - hls-est's elapsed_s (about 0 when the MLIR came from the cache)
  cgeist_log    the log run_cgeist wrote (command, stdout, stderr of the last attempt)
  v2            catalogue facts: source_match, config, flows, Tcl part / clock / directives, notes
  cause / cause_detail / error_line   make_hlsfactory_report.classify() of a failure
--merge updates an existing --out file with the designs of this run (a re-sweep of a subset; with
--changed-only, of the designs whose record a loader change altered).  Designs of --out that the loaded
catalogue lacks are dropped (and listed in _meta.resweeps) only with --drop-stale; without it --merge
stops and names them, because a design can also be missing when the tree walk did not see its directory.
A catalogue load that reports a problem (an unreadable directory or file, an invalid hlsfactory.toml, a
duplicate key) stops the sweep before anything runs.  --followup star,synmacro adds diagnostics to an existing
--out: the '*' attempt of empty-module designs (record star_attempt) and a -D__SYNTHESIS__ run of failed
designs whose sources mention the macro (record synthesis_macro_experiment); neither changes a status.
--catalogue / --save-catalogue reuse a loaded catalogue (the tree walk over /mnt/d is slow under load).
cgeist's timeout is run_hlsest.CGEIST_TIMEOUT (600 s), hls-est's --timeout (120 s).
"""
import argparse
import concurrent.futures as cf
import re
import subprocess
import sys
import threading
import time
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parent))
import common as C                         # noqa: E402
import designs as D                        # noqa: E402
import make_hlsfactory_report as REP       # noqa: E402
import run_hlsest as R                     # noqa: E402
import run_vitis as RV                     # noqa: E402

LOCK = threading.Lock()
VITIS_KEYS: set = set()


def cgeist_log_of(d, shim):
    """The log run_cgeist writes for this design (same cache key)."""
    try:
        key = R.source_hash(d, shim)
    except Exception:                      # noqa: BLE001
        return None
    p = R.MLIR_ROOT / d["dataset"] / f"{d['benchmark']}.{key}.cgeist.log"
    return str(p) if p.exists() else None


def sweep_one(d, args, shim, run_id):
    t0 = time.time()
    try:
        r = R.process(d, args, shim, run_id)
    except Exception as e:                 # noqa: BLE001
        r = {"dataset": d["dataset"], "benchmark": d["benchmark"], "top": d["top"],
             "status": "harness error", "note": repr(e)[:300]}
    wall = time.time() - t0
    r["wall_s"] = round(wall, 2)
    el = r.get("elapsed_s") if isinstance(r.get("elapsed_s"), (int, float)) else 0
    r["cgeist_s"] = round(max(wall - el, 0.0), 2)
    r["cgeist_log"] = cgeist_log_of(d, shim)
    err = R.LOG_ROOT / run_id / f"{d['dataset']}__{d['benchmark']}.err"     # run_hlsest's log_prefix
    r["hlsest_log"] = str(err) if err.exists() else None
    r["sources"] = d["sources"]
    r["dir"] = d["dir"]
    v2 = d.get("v2", {})
    tcl = v2.get("tcl", {})
    r["v2"] = {"origin": d.get("origin"), "source_match": d.get("source_match"), "config": v2.get("config"),
               "flows": d.get("flows"), "v2_dir": d.get("v2_dir"), "rel": v2.get("rel"),
               "script": tcl.get("script"), "part": tcl.get("part"), "clock_ns": tcl.get("clock_ns"),
               "flow_target": tcl.get("flow_target"), "directives": tcl.get("directives"),
               "source_rule": v2.get("source_rule"), "source_notes": v2.get("source_notes", [])[:4],
               "tcl_errors": tcl.get("errors", [])[:4], "wip": v2.get("wip"),
               "polygeist_mode": v2.get("polygeist_mode"), "includes": d.get("includes"),
               "source_diff": v2.get("source_diff") or {}}
    r["defines"] = d.get("defines", [])
    if C.design_key(d) in VITIS_KEYS:
        # the Vitis cache key this record would use (run_vitis.cache_key); equal to the ground truth's
        # key means run_vitis.py --catalog v2 reuses the cached synthesis
        try:
            r["vitis_cache_key"] = RV.cache_key(d)
        except Exception as e:             # noqa: BLE001
            r["vitis_cache_key"] = f"error: {e!r}"[:200]
    r.update(REP.classify(r))
    return r


def mentions_synthesis_macro(d):
    """Whether a source or header of the design (include closure, hlsfactory_v2._file_set) names __SYNTHESIS__."""
    import hlsfactory_v2 as V2             # noqa: E402  (imported by designs.load_hlsfactory_v2)
    fs = V2._file_set(d["dir"], d["sources"], d.get("includes") or ["."])
    return any(b and b"__SYNTHESIS__" in b for b in fs.values())


def star_attempt(d, shim, run_id):
    """cgeist --function='*' alone (run_cgeist's first attempt), into a scratch file: its status and log."""
    out = R.MLIR_ROOT / d["dataset"] / f"{d['benchmark']}.star-{run_id}.mlir"
    out.parent.mkdir(parents=True, exist_ok=True)
    cmd = R.cgeist_cmd(d, shim, out, "*")
    log = out.with_suffix(".cgeist.log")
    try:
        p = subprocess.run(cmd, cwd=d["dir"], capture_output=True, text=True, errors="replace",
                           timeout=R.CGEIST_TIMEOUT)
    except subprocess.TimeoutExpired:
        return {"status": "cgeist timeout", "log": None}
    log.write_text(" ".join(cmd) + "\n\n" + p.stdout + "\n--- stderr ---\n" + p.stderr)
    has_func = out.exists() and re.search(r"func\.func\s", out.read_text(errors="replace"))
    if p.returncode == 0 and has_func:
        st = "ok"
    elif p.returncode == 0:
        st = "cgeist error: empty module (no functions emitted)"
    elif p.returncode < 0 or "Stack dump" in p.stderr or "PLEASE submit a bug report" in p.stderr:
        st = "cgeist crash"
    else:
        errs = [ln for ln in p.stderr.splitlines() if "error:" in ln]
        st = "cgeist error: " + (errs[0].strip()[:200] if errs else f"exit {p.returncode}")
    if out.exists():
        out.unlink()
    return {"status": st, "log": str(log), "rc": p.returncode}


def followup(a, designs, prev):
    """--followup: diagnostics on an existing sweep (--out with --merge), stored in its records."""
    if not prev:
        sys.exit("--followup needs --merge and an existing --out")
    md5 = R.cgeist_md5_or_raise() if hasattr(R, "cgeist_md5_or_raise") else R.cgeist_md5()
    if (prev["_meta"].get("cgeist_md5"), prev["_meta"].get("hls_est_sha256")) != (md5, C.hls_est_identity()[1]):
        sys.exit("--followup: this run's cgeist / hls-est differ from the ones of --out")
    shim = R.resolve_shim(a.shim)
    kinds = set(a.followup.split(","))
    by_key = {C.design_key(d): d for d in designs}
    run_id = a.run_id or "w8a-fu-" + time.strftime("%Y%m%d-%H%M%S")
    args = SimpleNamespace(pipeline=a.pipeline, timeout=a.timeout, force_cgeist=False, mlir_from=None,
                           mlir_from_records=None, no_privatize=False, no_debug_json=False)
    jobs = []
    for k, r in prev.items():
        if k == "_meta" or k not in by_key:
            continue
        d = by_key[k]
        if "star" in kinds and "empty module" in r.get("status", ""):
            jobs.append(("star", k, d))
        failed = r.get("status") != "ok" or r.get("cause")
        if (("synmacro" in kinds and failed) or ("synmacro-ok" in kinds and not failed)) \
                and "synthesis_macro_experiment" not in r and mentions_synthesis_macro(d):
            jobs.append(("synmacro", k, d))

    def run(job):
        kind, k, d = job
        if kind == "star":
            return kind, k, star_attempt(d, shim, run_id)
        d2 = dict(d, defines=list(d.get("defines", [])) + ["__SYNTHESIS__"])
        r2 = R.process(d2, args, shim, run_id)
        return kind, k, {"cgeist_status": r2.get("cgeist_status"), "status": r2.get("status"),
                         "total_bram": r2.get("total_bram"), "top_fn": r2.get("top_fn"),
                         "top_rule": r2.get("top_rule"), "mlir": r2.get("mlir")}

    started = time.strftime("%Y-%m-%d %H:%M:%S")
    print(f"followup {sorted(kinds)}: {len(jobs)} jobs", flush=True)
    with cf.ThreadPoolExecutor(max_workers=a.j) as ex:
        for i, (kind, k, res) in enumerate(ex.map(run, jobs), 1):
            prev[k]["star_attempt" if kind == "star" else "synthesis_macro_experiment"] = res
            print(f"[{i}/{len(jobs)}] {kind:8s} {k:60.60s} {res.get('status', '')[:60]}", flush=True)
    for _, k, _ in jobs:
        prev[k].update(REP.classify(prev[k]))
    prev["_meta"].setdefault("followups", []).append(
        {"run_id": run_id, "kinds": sorted(kinds), "jobs": len(jobs), "started": started,
         "finished": time.strftime("%Y-%m-%d %H:%M:%S")})
    C.dump_json(prev, a.out)
    print(f"followup done -> {a.out}")


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("-j", type=int, default=8)
    ap.add_argument("--timeout", type=int, default=C.HLSEST_TIMEOUT, help="hls-est timeout (s)")
    ap.add_argument("--datasets", default="")
    ap.add_argument("--benchmarks", default="")
    ap.add_argument("--keys", default="", help="comma-separated dataset/benchmark keys")
    ap.add_argument("--pipeline", default=C.DEFAULT_PIPELINE)
    ap.add_argument("--shim", default=C.DEFAULT_SHIM)
    ap.add_argument("--hlsfactory-root", default=None)
    ap.add_argument("--out", default=str(C.RESULTS_DIR / "hlsfactory-v2-sweep.json"))
    ap.add_argument("--merge", action="store_true", help="update --out instead of replacing it")
    ap.add_argument("--drop-stale", action="store_true",
                    help="with --merge: drop the designs of --out that the loaded catalogue lacks (after a loader "
                         "change that renames or removes designs); without it --merge refuses to drop them")
    ap.add_argument("--force-cgeist", action="store_true")
    ap.add_argument("--run-id", default=None)
    ap.add_argument("--extra-define", action="append", default=[],
                    help="experiment only: add -D<this> to every design's cgeist command (e.g. __SYNTHESIS__, "
                         "which Vitis defines during csynth); recorded in _meta.extra_defines")
    ap.add_argument("--vitis", default=str(C.RESULTS_DIR / "vitis.json"),
                    help="ground truth whose keys get a vitis_cache_key check")
    ap.add_argument("--catalogue", default=None,
                    help="read the catalogue (records + skipped / vanished) from this JSON instead of the tree "
                         "(written by --save-catalogue; loading the tree over /mnt/d can take minutes)")
    ap.add_argument("--save-catalogue", default=None, help="write the loaded catalogue to this JSON")
    ap.add_argument("--changed-only", action="store_true",
                    help="with --merge: sweep only the designs whose record (dir, sources, includes, defines, "
                         "top) differs from the one stored in --out, or that --out lacks (a loader fix)")
    ap.add_argument("--followup", default="",
                    help="comma list, with --merge, no new sweep: 'star' re-runs cgeist --function='*' for "
                         "designs that ended in an empty module (run_hlsest keeps only the by-name retry's "
                         "log, OPEN_ISSUES O28); 'synmacro' re-runs cgeist + hls-est with -D__SYNTHESIS__ for "
                         "failed designs whose sources mention __SYNTHESIS__ ('synmacro-ok': the same for the "
                         "designs that passed, to see whether the macro changes their estimate)")
    a = ap.parse_args()
    global VITIS_KEYS
    VITIS_KEYS = set((C.load_json(a.vitis, {}) or {}).keys())

    info: dict = {}
    t0 = time.time()
    if a.catalogue:
        cat = C.load_json(a.catalogue)
        designs, info = cat["records"], cat["info"]
    else:
        problems: list[str] = []
        designs = D.load_hlsfactory_v2(a.hlsfactory_root, problems=problems, info=info)
        if problems:
            sys.exit(f"catalogue load reported {len(problems)} problems (unreadable directories or files, invalid "
                     "hlsfactory.toml, duplicate keys); nothing swept:\n  " + "\n  ".join(problems[:20]))
    load_s = round(time.time() - t0, 1)
    if a.save_catalogue:
        C.dump_json({"records": designs, "info": info}, a.save_catalogue)
    all_keys = {C.design_key(d) for d in designs}
    prev = C.load_json(a.out, {}) if a.merge and Path(a.out).exists() else {}
    if a.followup:
        return followup(a, designs, prev)
    if a.changed_only:
        def sig(x):
            return (x.get("dir"), list(x.get("sources", [])), list(x.get("includes") or (x.get("v2") or {}).get("includes") or []),
                    list(x.get("defines", [])), x.get("top"))
        designs = [d for d in designs if C.design_key(d) not in prev or sig(d) != sig(prev[C.design_key(d)])]
    if a.datasets:
        keep = set(a.datasets.split(","))
        designs = [d for d in designs if d["dataset"] in keep]
    if a.benchmarks:
        keep = set(a.benchmarks.split(","))
        designs = [d for d in designs if d["benchmark"] in keep]
    if a.keys:
        keep = set(a.keys.split(","))
        designs = [d for d in designs if C.design_key(d) in keep]
    for d in designs:
        d["defines"] = list(d.get("defines", [])) + [x for x in a.extra_define if x not in d.get("defines", [])]
    shim = R.resolve_shim(a.shim)
    run_id = a.run_id or "w8a-" + time.strftime("%Y%m%d-%H%M%S")
    args = SimpleNamespace(pipeline=a.pipeline, timeout=a.timeout, force_cgeist=a.force_cgeist,
                           mlir_from=None, mlir_from_records=None, no_privatize=False, no_debug_json=False)
    ghash, bsha = C.hls_est_identity()
    md5 = R.cgeist_md5_or_raise() if hasattr(R, "cgeist_md5_or_raise") else R.cgeist_md5()
    meta = {"pipeline": a.pipeline, "shim": str(shim), "hls_est": C.HLS_EST, "hls_est_git": ghash,
            "hls_est_sha256": bsha, "cgeist": C.CGEIST, "cgeist_md5": md5,
            "polygeist_head": C.git_hash(Path(C.CGEIST).resolve().parents[2]),
            "hlsfactory_root": info.get("root"), "hlsfactory_head": C.git_hash(Path(info.get("root", "."))),
            "catalogue_load_s": load_s, "hlsest_timeout": a.timeout, "cgeist_timeout": R.CGEIST_TIMEOUT,
            "jobs": a.j, "run_id": run_id, "started": time.strftime("%Y-%m-%d %H:%M:%S"),
            "skipped": info.get("skipped", []), "vanished": info.get("vanished", []),
            "home": str(Path.home()), "extra_defines": a.extra_define}
    out = {}
    if prev:
        out = prev
        old = out.get("_meta", {})
        if (old.get("cgeist_md5"), old.get("hls_est_sha256")) != (md5, bsha):
            sys.exit("--merge: this run's cgeist / hls-est differ from the ones of --out; use a new --out")
        stale = sorted(k for k in out if k != "_meta" and k not in all_keys)
        if stale and not a.drop_stale:
            sys.exit(f"--merge: {len(stale)} designs of {a.out} are not in the loaded catalogue "
                     f"({', '.join(stale[:5])}{', ...' if len(stale) > 5 else ''}); after a loader change that "
                     "renames or removes designs re-run with --drop-stale, otherwise load the catalogue again "
                     "(a directory the walk did not see)")
        for k in stale:                     # designs the catalogue no longer has (renamed by a loader fix)
            del out[k]
        hist = old.get("resweeps", [])
        meta = dict(old, skipped=meta["skipped"], vanished=meta["vanished"],
                    resweeps=hist + [{"run_id": run_id, "started": meta["started"], "keys": len(designs),
                                      "dropped": stale, "catalogue_load_s": load_s}])
    out["_meta"] = meta
    print(f"{len(designs)} v2 designs (catalogue {load_s}s); cgeist {C.CGEIST} md5 {md5}; hls-est {bsha}",
          flush=True)
    done = 0
    with cf.ThreadPoolExecutor(max_workers=a.j) as ex:
        futs = {ex.submit(sweep_one, d, args, shim, run_id): d for d in designs}
        for f in cf.as_completed(futs):
            d = futs[f]
            r = f.result()
            done += 1
            with LOCK:
                out[C.design_key(d)] = r
                if done % 25 == 0:
                    C.dump_json(out, a.out)
            print(f"[{done}/{len(designs)}] {C.design_key(d):60.60s} {r.get('status', ''):40.40s} "
                  f"BRAM={r.get('total_bram')} {r['wall_s']}s {r.get('cause') or ''}", flush=True)
    out["_meta"]["finished"] = time.strftime("%Y-%m-%d %H:%M:%S")
    C.dump_json(out, a.out)
    n_ok = sum(1 for k, r in out.items() if k != "_meta" and r.get("status") == "ok")
    print(f"done: {n_ok} ok of {len(out) - 1} -> {a.out}")


if __name__ == "__main__":
    main()
