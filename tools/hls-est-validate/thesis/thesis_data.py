"""Loading and scoring of hls-est result files for the thesis tables.

Every number the thesis prints is computed here from result files: run_hlsest.py run files
(`<run>.json`), the Vitis ground truth (`results/vitis.json`), the comparison CSV with the time
columns (`hls-doc/hls-est-vs-vitis.csv`) and the round-10 out-of-band classification.

Scoring follows compare.py exactly for the totals (`compare_one`): a design is *compared* when
Vitis has status ok and a BRAM total, hls-est has status ok, and (when the run records them) the
design's Vitis cache key is one of the run's `vitis_keys`; otherwise the row is "vitis missing",
"hls-est missing" or "sources differ".  The goal band is make_compare_csv.band (exact, or an
over-count of at most 15 % of the Vitis value).  Every run is re-scored against the *current*
ground truth so that rows of different dates share one reference; `check_against_cmp` verifies
that the re-scoring reproduces a run's own compare.py summary.
"""
import csv
import hashlib
import json
import os
import re
import statistics
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent
VALIDATE = HERE.parent
CIRCT = VALIDATE.parent.parent
SCRATCH = Path.home() / "hls-est-work" / "coord" / "scratch"
RESULTS = VALIDATE / "results"
CACHE = SCRATCH / "thesis" / "cache"

sys.path.insert(0, str(VALIDATE))
import make_compare_csv  # noqa: E402  (the one definition of the goal band)

band, BAND_OVER = make_compare_csv.band, make_compare_csv.BAND_OVER

IN_BAND = ("exact", "over<=15%")


def expand(path):
    """Expand the manifest's $SCRATCH / $RESULTS prefixes and make the path absolute."""
    p = str(path).replace("$SCRATCH", str(SCRATCH)).replace("$RESULTS", str(RESULTS))
    return Path(p) if os.path.isabs(p) else CIRCT / p


def _cache_file(path):
    st = path.stat()
    tag = hashlib.sha1(f"{path}|{st.st_size}|{st.st_mtime_ns}".encode()).hexdigest()[:16]
    return CACHE / f"{path.stem}.{tag}.slim.json"


def load_run(path):
    """A run file reduced to the fields the thesis needs: {key: record}, meta.  Cached by path,
    size and mtime, because the run files are 30-75 MB each."""
    path = expand(path)
    cache = _cache_file(path)
    if cache.exists():
        with open(cache) as f:
            d = json.load(f)
        return d["runs"], d["meta"]
    with open(path) as f:
        raw = json.load(f)
    meta = raw.pop("_meta", {}) or {}
    runs = {}
    for key, r in raw.items():
        if not isinstance(r, dict):
            continue
        runs[key] = {"status": r.get("status"), "cgeist_status": r.get("cgeist_status"),
                     "total_bram": r.get("total_bram"), "vitis_keys": r.get("vitis_keys"),
                     "elapsed_s": r.get("elapsed_s"), "mlir": r.get("mlir"), "top": r.get("top")}
    slim_meta = {k: meta.get(k) for k in ("run_id", "hls_est", "hls_est_git", "hls_est_sha256", "cgeist",
                                           "cgeist_md5", "shim", "pipeline", "config_set", "mlir_from", "timeout")}
    CACHE.mkdir(parents=True, exist_ok=True)
    with open(cache, "w") as f:
        json.dump({"runs": runs, "meta": slim_meta}, f)
    return runs, slim_meta


def load_vitis(path=RESULTS / "vitis.json"):
    with open(path) as f:
        raw = json.load(f)
    out = {}
    for key, v in raw.items():
        if not isinstance(v, dict) or key.startswith("_"):
            continue
        totals = v.get("totals") or {}
        out[key] = {"ok": v.get("status") == "ok", "status": v.get("status"), "bram": totals.get("BRAM"),
                    "bram_util_pct": totals.get("BRAM_util_pct"), "key": v.get("key"), "elapsed_s": v.get("elapsed_s")}
    return out


def score(runs, vitis):
    """One row per design (union of run and ground-truth keys), as compare.py's compare_one."""
    rows = []
    for key in sorted(set(runs) | set(vitis)):
        v, h = vitis.get(key), runs.get(key)
        vb = v["bram"] if v and v["ok"] else None
        hb = h.get("total_bram") if h and h.get("status") == "ok" else None
        row = {"key": key, "dataset": key.split("/")[0], "vitis": vb, "hlsest": hb,
               "cgeist_ok": bool(h and h.get("cgeist_status") == "ok"), "hlsest_ok": hb is not None,
               "vitis_ok": vb is not None, "in_run": h is not None}
        hkeys = (h or {}).get("vitis_keys")
        if vb is not None and hb is not None and v.get("key") and hkeys and v["key"] not in hkeys.values():
            row["status"] = "sources differ"
        elif vb is not None and hb is not None:
            row["status"] = "compared"
        else:
            row["status"] = "vitis missing" if vb is None else "hls-est missing"
        row["band"] = band(vb, hb) if row["status"] == "compared" else ""
        row["diff"] = hb - vb if row["status"] == "compared" else None
        rows.append(row)
    return rows


def summarize(rows):
    """Headline numbers over a set of score rows."""
    design_rows = [r for r in rows if r["in_run"]]
    comp = [r for r in rows if r["status"] == "compared"]
    n = len(comp)
    exact = sum(r["band"] == "exact" for r in comp)
    inb = sum(r["band"] in IN_BAND for r in comp)
    under = sum(r["band"] == "under" for r in comp)
    over_le = sum(r["band"] == "over<=15%" for r in comp)
    over_gt = sum(r["band"] == "over>15%" for r in comp)
    abs_err = sum(abs(r["diff"]) for r in comp)
    vit_total = sum(r["vitis"] for r in comp)
    rel = [r["diff"] / r["vitis"] for r in comp if r["vitis"] > 0]
    zero_v = [r for r in comp if r["vitis"] == 0]
    return {
        "designs": len(design_rows),
        "cgeist_ok": sum(r["cgeist_ok"] for r in design_rows),
        "hlsest_ok": sum(r["hlsest_ok"] for r in design_rows),
        "vitis_ok": sum(r["vitis_ok"] for r in design_rows),
        "compared": n,
        "exact": exact,
        "in_band": inb,
        "under": under,
        "over_le15": over_le,
        "over_gt15": over_gt,
        "out_of_band": n - inb,
        "abs_err": abs_err,
        "vitis_bram_total": vit_total,
        "hlsest_bram_total": sum(r["hlsest"] for r in comp),
        "weighted_err_pct": 100.0 * abs_err / vit_total if vit_total else None,
        "exact_pct": 100.0 * exact / n if n else None,
        "in_band_pct": 100.0 * inb / n if n else None,
        "median_abs_rel_pct": 100.0 * statistics.median(abs(x) for x in rel) if rel else None,
        "mean_abs_rel_pct": 100.0 * statistics.fmean(abs(x) for x in rel) if rel else None,
        "median_abs_rel_nonexact_pct": (100.0 * statistics.median(abs(x) for x in rel if x != 0)
                                        if any(x != 0 for x in rel) else None),
        "compared_vitis_zero": len(zero_v),
        "compared_vitis_zero_exact": sum(r["band"] == "exact" for r in zero_v),
    }


def check_against_cmp(rows, cmp_path):
    """Return (ok, message): does the re-scoring reproduce the compare.py summary of the same run?"""
    with open(cmp_path) as f:
        s = json.load(f)["summary"]
    mine = summarize(rows)
    pairs = [("compared", "compared"), ("exact", "exact"), ("abs_err", "total_abs_error")]
    bad = [f"{a}: {mine[a]} vs {s[b]}" for a, b in pairs if mine[a] != s[b]]
    return (not bad, "; ".join(bad) if bad else "re-scoring equals compare.py")


def distinct_groups(rows, runs):
    """Group compared designs whose cgeist MLIR is byte-identical, with the same top and the same Vitis
    total (copies of one design under several dataset names).  Returns {group id: [rows]}."""
    groups = {}
    for r in rows:
        if r["status"] != "compared":
            continue
        rec = runs.get(r["key"], {})
        p = rec.get("mlir")
        if p and os.path.exists(p):
            with open(p, "rb") as f:
                h = hashlib.md5(f.read()).hexdigest()
        else:
            h = "missing:" + r["key"]
        groups.setdefault((h, rec.get("top"), r["vitis"]), []).append(r)
    return groups


NOTES_DIR = CIRCT / "hls-doc" / "notes"


def snapshot():
    with open(HERE / "ch06_manifest.json") as f:
        return json.load(f)["snapshot"]


def notes_text(name):
    """A notes file (VITIS_NOTES.md, OPEN_ISSUES.md, MEMOS.md, CHANGELOG.md) as it stood at the snapshot
    commit, so that the thesis counts the notes that belong to the evaluated run, not later rounds."""
    import subprocess
    return subprocess.run(["git", "-C", str(CIRCT), "show", f"{snapshot()['circt_commit']}:hls-doc/notes/{name}"],
                          check=True, capture_output=True, text=True).stdout


def _status_group(title):
    """The parenthesis of a note heading that states its status: the last top-level group mentioning
    confirmed / unconfirmed / observation / data / superseded (titles contain other parentheses)."""
    groups, depth, start = [], 0, None
    for i, ch in enumerate(title):
        if ch == "(":
            if depth == 0:
                start = i + 1
            depth += 1
        elif ch == ")" and depth:
            depth -= 1
            if depth == 0:
                groups.append(title[start:i])
    if depth and start is not None:      # a heading cut before its closing parenthesis
        groups.append(title[start:])
    hits = [g for g in groups if re.search(r"confirm|observation|\bdata\b|superseded", g, re.I)]
    return hits[-1] if hits else ""


def note_status(title):
    """(status, basis) of one VITIS_NOTES heading.  This is the one status parser of the thesis
    generators (chapters 1, 3, 4, 6 and 8 all count with it).

    status: "confirmed" | "partly confirmed" | "unconfirmed" | "method"
      - "unconfirmed": the status names a superseded rule, a corpus observation, data without a rule, or
        says "unconfirmed";
      - "partly confirmed": "partly confirmed", or "confirmed except where marked" / "where marked";
      - "confirmed": any other "confirmed";
      - "method": no status at all (notes on the measurement method, N8 and N9).
    basis (only for confirmed / partly confirmed): "kernels" when the status counts or names standalone
    kernels ("41 kernels", "kernel `w9r6_dfi4`"), else "corpus only" (confirmed on catalogue designs or ground-truth reports, no standalone kernel)."""
    g = _status_group(title).lower()
    if not g:
        return "method", ""
    if ("superseded" in g or "observation" in g or re.search(r"\bdata\b", g)
            or re.search(r"\bunconfirmed\b", g) and "partly" not in g and "except" not in g):
        return "unconfirmed", ""
    if "partly confirmed" in g or "where marked" in g:
        status = "partly confirmed"
    elif re.search(r"(?<!un)confirmed", g):
        status = "confirmed"
    else:
        return "unconfirmed", ""
    named = re.search(r"\d+ (?:\+ \d+ )*(?:\w+ )?kernels?\b|kernels? `", g)
    return status, ("kernels" if named else "corpus only")


def vitis_notes_index(path=None):
    """{'N31': {'title', 'status', 'basis'}} in file order (see note_status); by default VITIS_NOTES.md at
    the snapshot commit."""
    out = {}
    text = notes_text("VITIS_NOTES.md") if path is None else Path(path).read_text()
    if True:
        for line in text.splitlines():
            m = re.match(r"^## (N\d+[a-z]?)\. (.*)$", line.rstrip())
            if not m:
                continue
            status, basis = note_status(m.group(2))
            out[m.group(1)] = {"title": m.group(2), "status": status, "basis": basis}
    return out


def note_status_counts(index=None):
    """Counts of the shared status classes, with the confirmed notes split by their basis."""
    index = index or vitis_notes_index()
    c = {"notes": len(index), "confirmed": 0, "confirmed_kernels": 0, "confirmed_corpus": 0,
         "partly": 0, "unconfirmed": 0, "method": 0}
    for v in index.values():
        if v["status"] == "confirmed":
            c["confirmed"] += 1
            c["confirmed_kernels" if v["basis"] == "kernels" else "confirmed_corpus"] += 1
        elif v["status"] == "partly confirmed":
            c["partly"] += 1
        else:
            c[v["status"]] += 1
    c["confirmed_corpus_list"] = ", ".join(k for k, v in index.items()
                                            if v["status"] == "confirmed" and v["basis"] != "kernels")
    c["unconfirmed_list"] = ", ".join(k for k, v in index.items() if v["status"] == "unconfirmed")
    c["partly_list"] = ", ".join(k for k, v in index.items() if v["status"] == "partly confirmed")
    c["method_list"] = ", ".join(k for k, v in index.items() if v["status"] == "method")
    return c


def read_timing_csv(path):
    with open(path, newline="") as f:
        return list(csv.DictReader(f))


def parse_class_table(path):
    """The class table of the round-10 ranking (classes.md): {class: description}."""
    out = {}
    with open(path) as f:
        for line in f:
            cells = [c.strip() for c in line.strip().strip("|").split("|")]
            if len(cells) >= 5 and re.match(r"^K\d+[a-z]?$", cells[0]):
                out[cells[0]] = cells[4]
    return out
