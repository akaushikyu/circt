#!/usr/bin/env python3
"""Generate the FINN-hlslib designs of the second held-out set (hls-doc/heldout2.md).

    python3 -I gen_finn.py [--finn /mnt/d/HLS_heldout2/src/finn-hlslib] [--out /mnt/d/HLS_heldout2/src/finn_gen]

Xilinx/finn-hlslib (BSD-3-Clause) ships one Vitis HLS unit test per library function: tb/test_<name>.tcl adds a
top file tb/<x>_top.cpp, which includes its configuration (tb/data/<config>.h, or macros in a tb-local header)
and, for the convolution / MVAU tests, its weights (tb/data/memdata*.h).  One design per test:

  finn__<test>             the test as the repository ships it: the top file and every tb-local file it includes
                           (transitively) copied unchanged, so that its quoted includes resolve inside the design
                           directory; the library headers stay in the checkout (-I <finn-hlslib>).
  finn__<test>__<variant>  the same files with the configuration header replaced by one written here (SWEEPS:
                           a small fixed list of parameter sets per test that satisfy the function's documented
                           constraints, e.g. OFMDim = (IFMDim - K) / S + 1, SIMD | channels, PE | output channels);
                           for the convolution tests also a weights header written here (random weights from
                           random.Random(f"{SEED}:{design}") in the repository's BinaryWeights /
                           FixedPointWeights layout).  -D flags of a test (dwcnm) are swept the same way.

No script of the repository is run (its tb/data/gen_weigths*.py are not used).  Output: <out>/<design>/ and
<out>/manifest.json (every design: test, top, sources, cflags, family, variant parameters).
"""
from __future__ import annotations

import argparse
import json
import os
import posixpath
import random
import re
import shutil
import subprocess
import sys
from pathlib import Path

SEED = 20261027

# The library function family each test exercises (the function its top calls; variants of one generator,
# pool or converter are one family).  Content-based families (build_heldout2.py) may merge these further.
FAMILY = {
    "swg": "sliding_window", "swg_kernelstride": "sliding_window", "swg_kernelstride_mmv": "sliding_window",
    "swg_1D": "sliding_window", "swg_1D_dws": "sliding_window",
    "conv3": "conv_mvau", "conv3_inj_stmr": "conv_mvau", "conv3_noinj_stmr": "conv_mvau",
    "tmrc_stmr": "conv_mvau", "conv_nonsquare": "conv_mvau", "convmmv": "conv_mvau",
    "conv_stream": "conv_mvau_stream", "conv_dws": "conv_dws", "conv_nonsquare_dws": "conv_dws",
    "pool": "maxpool", "pool_1d": "maxpool", "kernel_stride_pool": "maxpool",
    "dwc": "width_converter", "dwcnm": "width_converter", "qdma_stream": "qdma_stream",
    "add": "add_streams", "eltwise": "eltwise", "dup_stream": "duplicate_streams",
    "upsample": "upsample", "upsample_1d": "upsample", "label_select": "label_select",
    "max_norm": "max_norm", "channelwise_op": "channelwise_op",
}


def defines(**kv) -> str:
    return "".join(f"#define {k} {v}\n" for k, v in kv.items())


def swg(k, c, p, d, s, simd, mmv=1):
    return defines(SIMD=simd, KERNEL_DIM=k, IFM_Channels=c, IFMDim=d, OFMDim=(d - k) // s + 1, STRIDE=s,
                   INPUT_PRECISION=p, MMV=mmv, INPUT_MULTIPLIER=1)


def swg1d(k, c, p, d, s, simd):
    return defines(SIMD1=simd, KERNEL_DIM_x=k, KERNEL_DIM_y=1, IFM_Channels1=c, IFMDim_x=d, IFMDim_y=1,
                   OFMDim_x=(d - k) // s + 1, OFMDim_y=1, STRIDE_x=s, STRIDE_y=1, INPUT_PRECISION1=p,
                   DILATION_x=1, DILATION_y=1)


def swg1d_dws(k, c, d, simd, p):
    return defines(SIMD1=simd, KERNEL_DIM_x=k, IFM_Channels1=c, IFMDim_x=d, OFMDim_x=d - k + 1, STRIDE_x=1,
                   DILATION_x=1, INPUT_PRECISION1=p)


def pool(k, c, d, p, pe):
    return defines(KERNEL_DIM=k, FM_Channels1=c, IFMDim1=d, OFMDim1=d // k, PRECISION=p, PE1=pe)


def conv(k, simd, pe, w, ic, oc, d, ip, mmv=1):
    """config.h of the convolution tests: TILE1 = IFM_Channels * K * K * OFM_Channels / (SIMD * PE)."""
    tile = ic * k * k * oc // (simd * pe)
    return defines(KERNEL_DIM=k, SIMD1=simd, PE1=pe, MMV1=mmv, WIDTH=w, IFM_Channels1=ic, OFM_Channels1=oc,
                   IFMDim1=d, OFMDim1=d - k + 1, STRIDE=1, INPUT_PRECISION=ip, TILE1=tile, ACTIVATION_PRECISION=16)


def memdata(design: str, k, simd, pe, w, ic, oc, *_ignored) -> str:
    """Weights in finn-hlslib's BinaryWeights<SIMD, PE, TILES> (WIDTH 1) or FixedPointWeights<SIMD, ap_int<W>,
    PE, TILES> layout: PE rows of TILES words of SIMD * W bits."""
    tile = ic * k * k * oc // (simd * pe)
    rnd = random.Random(f"{SEED}:{design}")
    head = (f"static BinaryWeights<{simd},{pe},{tile}> weights = {{\n{{\n" if w == 1 else
            f"static FixedPointWeights<{simd},ap_int<{w}>,{pe},{tile}> weights = {{\n{{\n")
    rows = []
    for _ in range(pe):
        rows.append("{" + ",".join(hex(rnd.randrange(1 << (simd * w))) for _ in range(tile)) + "}")
    return ("// generated by circt tools/hls-est-validate/heldout2/gen_finn.py (random weights)\n"
            "#ifndef PARAMS_HPP\n#define PARAMS_HPP\nnamespace PARAM {\n" + head + ",\n".join(rows)
            + "\n}\n};\n}\n#endif\n")


CONV_SETS = {  # (K, SIMD, PE, WIDTH, IFM_Channels, OFM_Channels, IFMDim, INPUT_PRECISION)
    "k3_c4x16_d6_w1": (3, 2, 2, 1, 4, 16, 6, 8), "k3_c8x16_d10_w1": (3, 4, 4, 1, 8, 16, 10, 8),
    "k3_c8x8_d8_w4": (3, 4, 2, 4, 8, 8, 8, 8), "k1_c16x32_d8_w2": (1, 8, 4, 2, 16, 32, 8, 4),
    "k5_c2x8_d12_w1": (5, 1, 4, 1, 2, 8, 12, 8), "k3_c16x16_d6_w4": (3, 8, 8, 4, 16, 16, 6, 4),
    "k3_c32x32_d5_w1": (3, 16, 16, 1, 32, 32, 5, 1), "k2_c4x8_d7_w8": (2, 4, 4, 8, 4, 8, 7, 8),
}
# test -> {variant: {relative path: text or callable(design) -> text, "-D": {...}}}
SWEEPS = {
    "swg": {f"k{k}_c{c}_p{p}_d{d}_s{s}_simd{m}": {"data/input_gen.h": swg(k, c, p, d, s, m)}
            for k, c, p, d, s, m in [(3, 4, 8, 8, 1, 2), (3, 8, 4, 10, 1, 4), (2, 4, 8, 8, 2, 4), (5, 2, 8, 12, 1, 1),
                                     (3, 16, 4, 16, 1, 8), (1, 8, 8, 8, 1, 8), (4, 3, 8, 10, 2, 3)]},
    "swg_kernelstride": {f"k{k}_c{c}_p{p}_d{d}_s{s}_simd{m}": {"data/input_gen_kernelstride.h": swg(k, c, p, d, s, m)}
                         for k, c, p, d, s, m in [(3, 4, 8, 9, 2, 2), (5, 2, 8, 11, 3, 1), (3, 8, 4, 13, 2, 4),
                                                  (2, 4, 8, 8, 3, 2)]},
    "swg_kernelstride_mmv": {f"k{k}_c{c}_d{d}_s{s}_simd{m}_mmv{v}":
                             {"data/input_gen_kernelstride_mmv.h": swg(k, c, 8, d, s, m, v)}
                             for k, c, d, s, m, v in [(3, 2, 9, 2, 2, 2), (3, 4, 13, 2, 2, 3), (5, 2, 15, 2, 1, 2)]},
    "swg_1D": {f"k{k}_c{c}_p{p}_d{d}_s{s}_simd{m}": {"data/input_gen_1d.h": swg1d(k, c, p, d, s, m)}
               for k, c, p, d, s, m in [(3, 4, 8, 32, 1, 2), (5, 8, 8, 64, 1, 4), (7, 2, 16, 40, 1, 1),
                                        (3, 16, 8, 25, 2, 8)]},
    "swg_1D_dws": {f"k{k}_c{c}_d{d}_simd{m}_p{p}": {"data/input_gen_1d_dws.h": swg1d_dws(k, c, d, m, p)}
                   for k, c, d, m, p in [(3, 8, 32, 2, 8), (5, 4, 20, 1, 16), (7, 16, 40, 4, 8), (3, 12, 16, 3, 8)]},
    "pool": {f"k{k}_c{c}_d{d}_p{p}_pe{e}": {"data/pool_config.h": pool(k, c, d, p, e)}
             for k, c, d, p, e in [(2, 8, 8, 4, 1), (2, 32, 16, 8, 2), (3, 16, 12, 4, 4), (4, 4, 16, 8, 1),
                                   (2, 64, 8, 2, 8)]},
    "pool_1d": {f"k{k}_c{c}_d{d}_p{p}_pe{e}": {"data/pool_config.h": pool(k, c, d, p, e)}
                for k, c, d, p, e in [(2, 8, 8, 4, 1), (2, 32, 16, 8, 2), (3, 16, 12, 4, 4), (4, 4, 16, 8, 1)]},
    "dwc": {f"in{i}_out{o}_n{n}": {"data/dwc_config.h": defines(INPUT_WIDTH=i, OUT_WIDTH=o, NUM_REPEAT=n)}
            for i, o, n in [(16, 4, 8), (4, 16, 8), (64, 8, 16), (8, 64, 16), (24, 8, 6), (8, 24, 6)]},
    "dwcnm": {f"in{i}_out{o}": {"-D": {"INPUT_WIDTH": i, "OUT_WIDTH": o}}
              for i, o in [(48, 512), (24, 40), (40, 24), (100, 64), (64, 100), (200, 32)]},
    "add": {f"c{c}_w{i}_o{o}_n{n}_off{f}_sat{s}":
            {"data/add_config.h": defines(NUM_CHANNELS=c, INPUT_WIDTH=i, OUTPUT_WIDTH=o, NUM_WORDS=n, NUM_REPEAT=1,
                                          OFFSET=f, SAT=s)}
            for c, i, o, n, f, s in [(16, 8, 9, 4, 0, 0), (8, 4, 5, 8, 1, 1), (64, 2, 3, 2, 0, 1), (32, 8, 8, 16, 3, 1)]},
    "upsample": {f"p{p}_c{c}_o{o}_i{i}": {"data/upsample_config.h": "#ifndef UPSAMPLE_CONFIG_H\n" + defines(
                     UPSAMPLE_CONFIG_H="", PRECISION=p, FM_CHANNELS=c, OFMDIM=o, IFMDIM=i) + "#endif\n"}
                 for p, c, o, i in [(8, 8, 8, 4), (4, 32, 16, 8), (16, 4, 12, 3), (8, 16, 14, 7)]},
    "eltwise": {f"c{c}_w{a}_{b}_o{o}_n{n}": {"data/eltwise_config.h": "".join(
                    f"constexpr unsigned {k} = {v};\n" for k, v in (("NUM_CHANNELS", c), ("INPUT_1_WIDTH", a),
                                                                    ("INPUT_2_WIDTH", b), ("OUTPUT_WIDTH", o),
                                                                    ("NUM_WORDS", n), ("NUM_REPEAT", 1)))}
                for c, a, b, o, n in [(4, 8, 8, 9, 8), (16, 4, 4, 5, 4), (2, 16, 8, 17, 16)]},
    "conv3": {v: {"data/config.h": conv(*p), "data/memdata.h": (lambda d, p=p: memdata(d, *p))}
              for v, p in CONV_SETS.items()},
    "conv_stream": {v: {"data/config.h": conv(*p), "data/memdata.h": (lambda d, p=p: memdata(d, *p))}
                    for v, p in list(CONV_SETS.items())[:4]},
    "convmmv": {f"{v}_mmv{m}": {"data/config.h": conv(*p, mmv=m), "data/memdata.h": (lambda d, p=p: memdata(d, *p))}
                for v, p, m in [("k3_c4x8_d6_w1", (3, 2, 2, 1, 4, 8, 6, 8), 2),
                                ("k3_c8x8_d8_w1", (3, 4, 4, 1, 8, 8, 8, 8), 3)]},
}

_ADD = re.compile(r"^\s*add_files\s+(?!-tb)(\S+)(?:\s+-cflags\s+\"([^\"]*)\")?", re.M)
_TOP = re.compile(r"^\s*set_top\s+(\S+)", re.M)
_INC = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.M)


def tb_closure(tb: str, src: str) -> list[str]:
    """The top file and every file it includes (transitively, quoted includes) that lives under tb/,
    relative to tb/."""
    seen, todo = [], [src]
    while todo:
        rel = todo.pop(0)
        if rel in seen:
            continue
        seen.append(rel)
        text = Path(tb, rel).read_text(encoding="utf-8", errors="replace")
        for inc in _INC.findall(text):
            cand = posixpath.normpath(posixpath.join(posixpath.dirname(rel), inc))
            if os.path.isfile(posixpath.join(tb, cand)):
                todo.append(cand)
    return seen


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--finn", default="/mnt/d/HLS_heldout2/src/finn-hlslib")
    ap.add_argument("--out", default="/mnt/d/HLS_heldout2/src/finn_gen")
    a = ap.parse_args(argv)
    tb = posixpath.join(a.finn, "tb")
    commit = subprocess.run(["git", "-C", a.finn, "rev-parse", "HEAD"], capture_output=True, text=True).stdout.strip()
    if os.path.isdir(a.out):
        shutil.rmtree(a.out)
    os.makedirs(a.out)
    recs = []
    for tcl in sorted(Path(tb).glob("test_*.tcl")):
        test = tcl.stem[len("test_"):]
        text = tcl.read_text(encoding="utf-8", errors="replace")
        adds, tops = _ADD.findall(text), _TOP.findall(text)
        base = {"test": test, "tcl": f"tb/{tcl.name}", "top": tops[0] if tops else None,
                "family": FAMILY.get(test, test)}
        if not adds or not tops or not os.path.isfile(posixpath.join(tb, adds[0][0])):
            recs.append({**base, "design": f"finn__{test}", "status": "error",
                         "error": "no design file / set_top, or the design file is missing upstream"})
            continue
        src, cflags = adds[0]
        files = tb_closure(tb, src)
        dflags = dict(re.findall(r"-D(\w+)=(\S+)", cflags))
        for variant, spec in [(None, {})] + sorted(SWEEPS.get(test, {}).items()):
            design = f"finn__{test}" + (f"__{variant}" if variant else "")
            ddir = posixpath.join(a.out, design)
            os.makedirs(ddir)
            for rel in files:
                os.makedirs(posixpath.dirname(posixpath.join(ddir, rel)), exist_ok=True)
                shutil.copyfile(posixpath.join(tb, rel), posixpath.join(ddir, rel))
            generated = []
            for rel, body in spec.items():
                if rel == "-D":
                    continue
                if rel not in files:
                    raise SystemExit(f"{design}: {rel} is not a file the test includes")
                Path(ddir, rel).write_text(body(design) if callable(body) else body, encoding="utf-8", newline="\n")
                generated.append(rel)
            d = dict(dflags, **{k: str(v) for k, v in spec.get("-D", {}).items()})
            recs.append({**base, "design": design, "status": "ok", "variant": variant, "sources": [src],
                         "files": files, "generated": generated, "includes": [a.finn],
                         "defines": d, "upstream_cflags": cflags})
    man = {"generator": "circt tools/hls-est-validate/heldout2/gen_finn.py", "seed": SEED,
           "finn_hlslib": a.finn, "finn_hlslib_commit": commit, "designs": recs}
    Path(a.out, "manifest.json").write_text(json.dumps(man, indent=1) + "\n", encoding="utf-8")
    ok = sum(r["status"] == "ok" for r in recs)
    print(f"{ok} of {len(recs)} FINN designs written to {a.out}")
    for r in recs:
        if r["status"] != "ok":
            print(f"  {r['design']}: {r['error']}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
