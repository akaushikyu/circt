#!/usr/bin/env python3
"""Thesis chapter 4, "The inferred decision model": the rule catalogue.

    ~/hls-est-work/coord/scratch/thesis/venv/bin/python make_ch4_rules.py

Writes hls-doc/thesis/04-inferred-decision-model.md, tables/ch4-rule-catalogue.{md,tex},
tables/ch4-stage-summary.{md,tex} and figures/ch4-rules-by-stage.{pdf,png}.

Inputs: ch4_rule_data.py (hand-written statements, no measured numbers), the Vitis runs of the cited
kernels (~/hls-est-work/experiments/<kernel>/<hash>/result.json), hls-doc/notes/VITIS_NOTES.md (note
titles), hls-doc/notes/OPEN_ISSUES.md (titles of the cited open issues), hls-doc/notes/CHANGELOG.md
(catalogue effects, verbatim), test/hls-est/Config/Inputs/default-config.json (configuration keys must
exist) and hls-doc/passes/ (pass names must have a page). Fails on a missing kernel run, an unknown
key, an unknown note or an unresolved reference.
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ch34_lib as L  # noqa: E402
import ch4_rule_data as D  # noqa: E402

OUT = L.THESIS / "04-inferred-decision-model.md"
INPUTS = ["tools/hls-est-validate/thesis/ch4_rule_data.py",
          "~/hls-est-work/experiments/*/*/result.json (cited kernels)",
          "hls-doc/notes/{VITIS_NOTES,OPEN_ISSUES,CHANGELOG}.md",
          "test/hls-est/Config/Inputs/default-config.json"]


def status_class(s):
    s = s.lower()
    if s.startswith("confirmed"):
        return "confirmed"
    if s.startswith("partly"):
        return "partly confirmed"
    return "unconfirmed"


def open_issue_titles():
    out = {}
    for line in L.read_text(L.NOTES / "OPEN_ISSUES.md").splitlines():
        m = re.match(r"^## (O\d+)\. (.*)$", line)
        if m:
            out[m.group(1)] = m.group(2)
    return out


def check_rules(keys, pages):
    notes = {i for i, _, _ in L.vitis_note_headings()}
    ids = set()
    for r in D.RULES:
        assert r["id"] not in ids, r["id"]
        ids.add(r["id"])
        assert r["stage"] in {s for s, _, _ in D.STAGES}, r["id"]
        for n in r["notes"]:
            if n not in notes:
                raise KeyError(f"{r['id']}: unknown note {n}")
        for k in r["keys"]:
            if not L.check_config_key(k, keys):
                raise KeyError(f"{r['id']}: configuration key {k} is not in the default configuration")
        for m in r["mechanism"]:
            for p in re.findall(r"--([a-z][a-z0-9-]+)", m):
                if p not in pages and p not in {"bram-analysis", "shim", "hls-trip-one-pipeline-unroll",
                                                "hls-keep-invariant-loops", "hls-auto-inline"}:
                    raise KeyError(f"{r['id']}: pass --{p} has no page in hls-doc/passes")


def kernel_table(r, used):
    rows = []
    for k in r["kernels"]:
        name, what = k[0], k[1]
        opts = k[2] if len(k) > 2 else {}
        s = L.kernel_summary(name, opts)
        used.add(name)
        rows.append([f"`{name}`", what, s["bram"], s["detail"], s["loops"], s["logs"]])
    return L.md_table(["kernel", "varies", "Vitis BRAM_18K", "memory rows", "pipelined loops (trip, II)",
                       "messages in the log"], rows, ["---", "---", "---:", "---", "---", "---"])


def render_rule(r, used, oi_titles, cited_oi):
    out = [f"### {r['id']}. {r['title']}", ""]
    out.append(f"*VITIS_NOTES:* {', '.join(r['notes'])}.")
    out.append("")
    out.append(L.expand_kernel_refs(r["statement"], used))
    out.append("")
    if r["kernels"]:
        out.append(kernel_table(r, used))
        out.append("")
    else:
        out.append("*No standalone kernel: the rule rests on corpus designs only.*")
        out.append("")
    out.append(f"- **Evidence:** {'; '.join(r['evidence'])}.")
    out.append(f"- **Status:** {r['status']}.")
    hl = r["hlsest"]
    for o in re.findall(r"O\d+", hl):
        cited_oi.add(o)
    out.append(f"- **hls-est:** {hl}.")
    if r["mechanism"]:
        out.append(f"- **Mechanism:** {', '.join('`' + m + '`' for m in r['mechanism'])}.")
    if r["keys"]:
        out.append(f"- **Configuration keys:** {', '.join('`' + k + '`' for k in r['keys'])}.")
    if r["effect"]:
        head, quote = L.changelog_effect(*r["effect"])
        out.append(f"- **Catalogue effect** (CHANGELOG, {head.split(' — ')[0]}, \"{head.split(' — ', 1)[1]}\"):")
        out.append(f"  > {quote}")
    out.append("")
    return "\n".join(out)


def figure(stats, gen_line):
    import ch34_plot as P
    L.FIGURES.mkdir(parents=True, exist_ok=True)
    stages = [s for s, _, _ in D.STAGES]
    names = [t for _, t, _ in D.STAGES]
    classes = ["confirmed", "partly confirmed", "unconfirmed"]
    fig, axes = P.plt.subplots(1, 2, figsize=(7.2, 3.4), gridspec_kw={"width_ratios": [1.15, 1]},
                               sharey=True)
    ax = axes[0]
    left = [0] * len(stages)
    ys = list(range(len(stages)))[::-1]
    for ci, c in enumerate(classes):
        vals = [stats[s][c] for s in stages]
        ax.barh(ys, vals, left=left, color=P.SERIES[ci], height=0.6, edgecolor="white", linewidth=1.5,
                label=c)
        left = [a + b for a, b in zip(left, vals)]
    for y, tot in zip(ys, left):
        ax.text(tot + 0.15, y, str(tot), va="center", fontsize=7, color=P.INK2)
    ax.set_yticks(ys)
    ax.set_yticklabels(names, fontsize=7.5)
    ax.set_xlabel("rules", fontsize=8)
    ax.xaxis.grid(True, color=P.GRID, linewidth=0.6)
    P.style(ax)
    ax.set_xlim(0, max(left) * 1.15)
    ax.xaxis.set_major_locator(P.plt.MaxNLocator(integer=True))
    fig.legend(*ax.get_legend_handles_labels(), fontsize=7, frameon=False, loc="upper center", ncol=3)
    ax2 = axes[1]
    kv = [stats[s]["kernels"] for s in stages]
    ax2.barh(ys, kv, color=P.SERIES[0], height=0.6)
    for y, v in zip(ys, kv):
        ax2.text(v + 0.3, y, str(v), va="center", fontsize=7, color=P.INK2)
    ax2.set_xlabel("distinct kernels cited", fontsize=8)
    ax2.xaxis.grid(True, color=P.GRID, linewidth=0.6)
    P.style(ax2)
    ax2.set_xlim(0, max(kv) * 1.15)
    fig.tight_layout(rect=(0, 0, 1, 0.93))
    P.save(fig, str(L.FIGURES / "ch4-rules-by-stage"), gen_line)


def main():
    keys = L.config_keys()
    pages = L.pass_pages()
    check_rules(keys, pages)
    gen = L.header(__file__, INPUTS)
    oi_titles = open_issue_titles()
    cited_oi = set()

    used = set()
    stats = {s: {"confirmed": 0, "partly confirmed": 0, "unconfirmed": 0, "kernels": 0}
             for s, _, _ in D.STAGES}
    body = []
    per_stage_kernels = {s: set() for s, _, _ in D.STAGES}
    for si, (sid, title, intro) in enumerate(D.STAGES, start=1):
        rules = [r for r in D.RULES if r["stage"] == sid]
        body.append(f"## 4.{si} {title}")
        body.append("")
        body.append(intro)
        body.append("")
        for r in rules:
            before = set(used)
            body.append(render_rule(r, used, oi_titles, cited_oi))
            per_stage_kernels[sid] |= {k[0] for k in r["kernels"]} | (used - before)
            stats[sid][status_class(r["status"])] += 1
        stats[sid]["kernels"] = len(per_stage_kernels[sid])

    # surprising behaviours
    surpr = [f"## 4.{len(D.STAGES) + 1} Surprising behaviours", "",
             "The rules above are written to be complete; the behaviours below are the ones that most "
             "contradicted what a reader of the Vitis documentation, or of the LLVM-based front end, would "
             "predict. Each cites the rule that states it and the kernels whose runs show it.", ""]
    for title, notes, rid, text in D.SURPRISES:
        assert rid in {r["id"] for r in D.RULES}, rid
        surpr.append(f"- **{title}** ({rid}; VITIS_NOTES {', '.join(notes)}). {L.expand_kernel_refs(text, used)}")
    surpr.append("")

    # limitations: the rules not confirmed and the open issues cited
    nconf = [r for r in D.RULES if status_class(r["status"]) != "confirmed"]
    lim = [f"## 4.{len(D.STAGES) + 2} What the catalogue does not settle", "",
           "The following rules are not fully confirmed; they are stated as observations, and the "
           "estimator either does not model them or models only their confirmed part.", ""]
    lim.append(L.md_table(["rule", "status"], [[f"{r['id']} {r['title']}", r["status"]] for r in nconf]))
    lim.append("")
    lim.append("Open issues the rules above refer to, with their titles from `hls-doc/notes/OPEN_ISSUES.md` "
               "(each entry there records whether, and how far, the issue has since been resolved):")
    lim.append("")
    for o in sorted(cited_oi, key=lambda x: int(x[1:])):
        t = oi_titles.get(o)
        if t is None:
            raise KeyError(f"open issue {o} cited but not in OPEN_ISSUES.md")
        lim.append(f"- **{o}.** {t}")
    lim.append("")
    lim.append("One gap underlies several of them: hls-est's modulo schedulers do not see loop-carried "
               "memory dependences (OPEN_ISSUES O1), so a loop whose II Vitis "
               "raises through a memory recurrence is scheduled faster in hls-est; this is why the stream "
               "timing of SC-5 cannot be adopted yet.")
    lim.append("")

    # overview tables
    ncls = {c: sum(1 for r in D.RULES if status_class(r["status"]) == c)
            for c in ("confirmed", "partly confirmed", "unconfirmed")}
    stage_rows = []
    for si, (sid, title, _) in enumerate(D.STAGES, start=1):
        st = stats[sid]
        stage_rows.append([f"4.{si}", title, st["confirmed"] + st["partly confirmed"] + st["unconfirmed"],
                           st["confirmed"], st["partly confirmed"], st["unconfirmed"], st["kernels"]])
    stage_rows.append(["", "all", len(D.RULES), ncls["confirmed"], ncls["partly confirmed"],
                       ncls["unconfirmed"], len(used)])
    stage_md = L.write_table("ch4-stage-summary",
                             ["section", "stage", "rules", "confirmed", "partly", "unconfirmed", "kernels"],
                             stage_rows, "Rules and cited kernels per decision stage", "tab:ch4-stages", gen,
                             colspec="llrrrrr", md_align=["---", "---", "---:", "---:", "---:", "---:", "---:"])
    cat_rows = [[r["id"], r["title"], ", ".join(r["notes"]), len(r["kernels"]), status_class(r["status"]),
                 r["hlsest"].split(":")[0].split(" (")[0].split(";")[0]] for r in D.RULES]
    cat_md = L.write_table("ch4-rule-catalogue", ["rule", "statement (short)", "notes", "kernels", "status", "hls-est"],
                           cat_rows, "The rule catalogue", "tab:ch4-catalogue", gen,
                           colspec="lp{6.2cm}lrll", md_align=["---", "---", "---", "---:", "---", "---"])
    figure(stats, gen)

    notes_cited = {n for r in D.RULES for n in r["notes"]} | {n for _, ns, _, _ in D.SURPRISES for n in ns}
    intro = L.fill_template(L.read_text(Path(__file__).parent / "templates" / "ch4_intro.md.in"), {
        "n_rules": len(D.RULES), "n_stages": len(D.STAGES), "n_notes_cited": len(notes_cited),
        "n_notes_total": len(L.vitis_note_headings()), "n_kernels": len(used),
        "n_confirmed": ncls["confirmed"], "n_partly": ncls["partly confirmed"],
        "n_unconfirmed": ncls["unconfirmed"],
        "uncited": ", ".join(i for i, _, _ in L.vitis_note_headings() if i not in notes_cited) or "none"})

    overview = ["## 4.0.1 Overview", "",
                "Table 4.1 counts the rules and the kernels they cite per stage (also as "
                "`tables/ch4-stage-summary.{md,tex}`), Figure 4.1 shows the same, and Table 4.2 "
                "(`tables/ch4-rule-catalogue.{md,tex}`) lists every rule.", "",
                "**Table 4.1.** Rules and cited kernels per decision stage.", "", stage_md, "",
                "![Figure 4.1: rules per decision stage by status, and the distinct kernels they cite]"
                "(figures/ch4-rules-by-stage.png)", "",
                "**Figure 4.1.** Rules per decision stage by status (left) and the distinct standalone kernels "
                "they cite (right).", "",
                "**Table 4.2.** The rule catalogue.", "", cat_md, ""]

    text = "\n".join([gen, "", intro, "\n".join(overview), "\n".join(body), "\n".join(surpr), "\n".join(lim)])
    leftover = re.findall(r"\[\[[^\]]+\]\]|\{\{[^}]+\}\}", text)
    if leftover:
        raise SystemExit(f"unresolved references: {leftover[:5]}")
    L.THESIS.mkdir(parents=True, exist_ok=True)
    with open(OUT, "w") as fh:
        fh.write(text.rstrip() + "\n")
    print(f"wrote {L.rel(OUT)}: {len(D.RULES)} rules, {len(used)} kernels")


if __name__ == "__main__":
    main()
