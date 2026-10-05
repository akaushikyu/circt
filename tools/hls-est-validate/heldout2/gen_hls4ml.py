#!/usr/bin/env python3
"""Generate the hls4ml designs of the second held-out set (hls-doc/heldout2.md).

    ~/hls-est-work/heldout2/venv/bin/python -I gen_hls4ml.py [--out /mnt/d/HLS_heldout2/src/hls4ml_gen] [-j 8]

Runs hls4ml (fastmachinelearning/hls4ml, Apache-2.0; the version installed in the venv is recorded) with its
PyTorch front end on a fixed set of small model architectures (ARCHS: dense MLPs in the style of the
wa-hls4ml '2layer' / '3layer' classes and the hls4ml jet-tagging MLP, Conv1D / Conv2D CNNs, a few recurrent,
residual and normalisation models) and writes one Vitis-backend project per (architecture, variant) with
HLSModel.write().  Nothing is synthesised: no hls4ml build(), no compile(), no report parsing.

Variants: a deterministic sample (random.Random(f"{SEED}:{arch}")) of VARIANTS_PER_ARCH points of the grid
precision x reuse factor x io_type x strategy, after a size filter (SIZE_LIMITS) that keeps every design small
enough for Vitis on xc7z020 (multipliers per layer after the reuse factor, total weights).  Weights are
random (torch.manual_seed per architecture); they only fix the ROM contents.

Output: <out>/<design>/ the hls4ml project (firmware/, myproject_test.cpp, build_prj.tcl, project.tcl,
hls4ml_config.yml) without the bundled firmware/ap_types copy (Vitis and the C reference builds use the real
Vitis headers) and tb_data/ (hls4ml's own test vectors), and <out>/manifest.json (every design: architecture,
family, variant, status).  The weights' .txt copies are kept: a build without __SYNTHESIS__ (a C reference run)
loads the weights from them (nnet_helpers.h load_weights_from_txt, directory WEIGHTS_DIR, default "weights").
"""
from __future__ import annotations

import argparse
import itertools
import json
import multiprocessing
import os
import random
import shutil
import sys
import traceback
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

SEED = 20261027
VARIANTS_PER_ARCH = 15
PRECISIONS = ["ap_fixed<16,6>", "ap_fixed<8,3>", "ap_fixed<12,4>", "ap_fixed<24,10>", "ap_fixed<6,2>"]
REUSE = [1, 2, 4, 8, 16, 64]
IO_TYPES = ["io_parallel", "io_stream"]
STRATEGIES = ["Latency", "Resource"]
# size filter: multipliers of the largest layer after the reuse factor, and total weights
SIZE_LIMITS = {"Latency": 1024, "Resource": 4096}
MAX_WEIGHTS = 32768
PART = "xc7z020clg400-1"

# ------------------------------------------------------------------------------------------ architectures
# A layer spec is a tuple: ("L", n_out) Linear, ("C1", c_out, k[, stride, pad]) Conv1d, ("C2", c_out, k[, stride,
# pad]) Conv2d, ("MP", k) / ("AP", k) max / average pool, ("BN",) batch norm, ("LN",) layer norm,
# ("F",) flatten, activations ("R",) ReLU, ("LR",) LeakyReLU, ("E",) ELU, ("S",) Sigmoid, ("T",) Tanh,
# ("SM",) Softmax; ("GRU", hidden) / ("LSTM", hidden) a recurrent layer returning the last state;
# ("RES", n) a residual dense block x + relu(Linear(n->n)(x)); ("CAT", n) concat(x, relu(Linear(x))).
ARCHS = {
    # dense (input: features)
    "dense2_relu":          ((16,), [("L", 32), ("R",), ("L", 5)]),
    "dense2_relu_softmax":  ((16,), [("L", 32), ("R",), ("L", 5), ("SM",)]),
    "jet_mlp":              ((16,), [("L", 64), ("R",), ("L", 32), ("R",), ("L", 32), ("R",), ("L", 5), ("SM",)]),
    "dense3_sigmoid":       ((10,), [("L", 20), ("S",), ("L", 10), ("S",), ("L", 1), ("S",)]),
    "dense3_tanh":          ((8,), [("L", 16), ("T",), ("L", 16), ("T",), ("L", 4)]),
    "dense_bn":             ((16,), [("L", 32), ("BN",), ("R",), ("L", 32), ("BN",), ("R",), ("L", 5), ("SM",)]),
    "dense1":               ((32,), [("L", 8)]),
    "dense_leaky":          ((12,), [("L", 24), ("LR",), ("L", 6), ("SM",)]),
    "dense_deep6":          ((16,), [("L", 16), ("R",)] * 5 + [("L", 2)]),
    "autoencoder":          ((32,), [("L", 16), ("R",), ("L", 4), ("R",), ("L", 16), ("R",), ("L", 32), ("S",)]),
    "dense_wide":           ((64,), [("L", 32), ("R",), ("L", 10), ("SM",)]),
    "dense_elu":            ((20,), [("L", 40), ("E",), ("L", 20), ("E",), ("L", 3)]),
    "dense_narrow_long":    ((4,), [("L", 8), ("R",)] * 4 + [("L", 1), ("S",)]),
    "dense_bottleneck":     ((48,), [("L", 8), ("R",), ("L", 48), ("R",), ("L", 6)]),
    "dense_layernorm":      ((16,), [("L", 32), ("LN",), ("R",), ("L", 8)]),
    "dense_residual":       ((16,), [("L", 16), ("R",), ("RES", 16), ("RES", 16), ("L", 4)]),
    "dense_concat":         ((12,), [("L", 12), ("R",), ("CAT", 12), ("L", 3), ("SM",)]),
    # recurrent (input: sequence length, features)
    "gru_small":            ((8, 4), [("GRU", 8), ("L", 3)]),
    "lstm_small":           ((8, 4), [("LSTM", 8), ("L", 3)]),
    # conv1d (input: channels, length)
    "conv1d_small":         ((2, 32), [("C1", 4, 3), ("R",), ("F",), ("L", 5)]),
    "conv1d_pool":          ((4, 32), [("C1", 8, 3), ("R",), ("MP", 2), ("C1", 8, 3), ("R",), ("AP", 2), ("F",), ("L", 5)]),
    "conv1d_deep":          ((1, 64), [("C1", 4, 5), ("R",), ("C1", 4, 5), ("R",), ("C1", 8, 5), ("R",), ("F",), ("L", 4)]),
    "conv1d_bn":            ((3, 24), [("C1", 6, 3), ("BN",), ("R",), ("MP", 2), ("F",), ("L", 3), ("SM",)]),
    "conv1d_stride":        ((2, 40), [("C1", 4, 4, 2), ("R",), ("F",), ("L", 4)]),
    "conv1d_tanh":          ((1, 16), [("C1", 3, 3), ("T",), ("C1", 3, 3), ("T",), ("F",), ("L", 2), ("S",)]),
    # conv2d (input: channels, height, width)
    "conv2d_tiny":          ((1, 8, 8), [("C2", 4, 3), ("R",), ("MP", 2), ("F",), ("L", 5), ("SM",)]),
    "conv2d_two":           ((1, 12, 12), [("C2", 4, 3), ("R",), ("MP", 2), ("C2", 8, 3), ("R",), ("F",), ("L", 10)]),
    "conv2d_rgb":           ((3, 10, 10), [("C2", 4, 3), ("R",), ("C2", 4, 3), ("R",), ("F",), ("L", 4)]),
    "conv2d_avg":           ((1, 10, 10), [("C2", 4, 3), ("R",), ("AP", 2), ("F",), ("L", 3)]),
    "conv2d_bn":            ((2, 8, 8), [("C2", 6, 3), ("BN",), ("R",), ("MP", 2), ("F",), ("L", 4)]),
    "conv2d_pointwise":     ((8, 6, 6), [("C2", 4, 1), ("R",), ("C2", 4, 1), ("R",), ("F",), ("L", 2)]),
    "conv2d_stride":        ((1, 16, 16), [("C2", 4, 4, 2), ("R",), ("F",), ("L", 4)]),
    "conv2d_pad":           ((1, 8, 8), [("C2", 4, 3, 1, 1), ("R",), ("C2", 4, 3, 1, 1), ("R",), ("MP", 2), ("F",), ("L", 4)]),
    "conv2d_mnist_like":    ((1, 14, 14), [("C2", 4, 3), ("R",), ("MP", 2), ("C2", 8, 3), ("R",), ("MP", 2), ("F",),
                                           ("L", 16), ("R",), ("L", 10), ("SM",)]),
    "conv2d_sigmoid":       ((1, 6, 6), [("C2", 2, 3), ("S",), ("F",), ("L", 1), ("S",)]),
    "conv2d_leaky":         ((2, 9, 9), [("C2", 4, 3), ("LR",), ("MP", 3), ("F",), ("L", 3)]),
    "conv2d_deep3":         ((1, 12, 12), [("C2", 4, 3), ("R",), ("C2", 4, 3), ("R",), ("C2", 4, 3), ("R",), ("MP", 2),
                                           ("F",), ("L", 5)]),
}


def build_model(arch: str):
    """The torch module of ARCHS[arch] with its multiplier counts: (module, input_shape, [mults per layer],
    total weights).  Shapes are traced with a dummy input."""
    import torch
    import torch.nn as nn

    shape, layers = ARCHS[arch]
    torch.manual_seed(SEED + sum(map(ord, arch)))

    class Res(nn.Module):
        def __init__(s, n):
            super().__init__()
            s.fc, s.act = nn.Linear(n, n), nn.ReLU()

        def forward(s, x):
            return x + s.act(s.fc(x))

    class Cat(nn.Module):
        def __init__(s, n_in, n):
            super().__init__()
            s.fc, s.act = nn.Linear(n_in, n), nn.ReLU()

        def forward(s, x):
            return torch.cat([x, s.act(s.fc(x))], dim=-1)

    class Last(nn.Module):
        def __init__(s, rnn):
            super().__init__()
            s.rnn = rnn

        def forward(s, x):
            return s.rnn(x)[0][:, -1, :]

    mods, mults = [], []
    x = torch.zeros((1,) + shape)
    for i, spec in enumerate(layers):
        kind = spec[0]
        if kind == "L":
            m = nn.Linear(x.shape[-1], spec[1])
            mults.append(x.shape[-1] * spec[1])
        elif kind in ("C1", "C2"):
            k = spec[2]
            stride = spec[3] if len(spec) > 3 else 1
            pad = spec[4] if len(spec) > 4 else 0
            cls = nn.Conv1d if kind == "C1" else nn.Conv2d
            m = cls(x.shape[1], spec[1], k, stride=stride, padding=pad)
            mults.append(x.shape[1] * spec[1] * (k if kind == "C1" else k * k))
        elif kind in ("MP", "AP"):
            dim = x.dim() - 2
            cls = {("MP", 1): nn.MaxPool1d, ("MP", 2): nn.MaxPool2d, ("AP", 1): nn.AvgPool1d, ("AP", 2): nn.AvgPool2d}
            m = cls[(kind, dim)](spec[1])
        elif kind == "BN":
            m = nn.BatchNorm1d(x.shape[1]) if x.dim() in (2, 3) else nn.BatchNorm2d(x.shape[1])
            with torch.no_grad():
                m.running_mean.uniform_(-0.5, 0.5)
                m.running_var.uniform_(0.5, 1.5)
                m.weight.uniform_(0.5, 1.5)
                m.bias.uniform_(-0.2, 0.2)
        elif kind == "LN":
            m = nn.LayerNorm(x.shape[-1])
        elif kind == "F":
            m = nn.Flatten()
        elif kind in ("GRU", "LSTM"):
            cls = nn.GRU if kind == "GRU" else nn.LSTM
            m = Last(cls(x.shape[-1], spec[1], batch_first=True))
            mults.append((3 if kind == "GRU" else 4) * spec[1] * (x.shape[-1] + spec[1]))
        elif kind == "RES":
            m = Res(spec[1])
            mults.append(spec[1] * spec[1])
        elif kind == "CAT":
            m = Cat(x.shape[-1], spec[1])
            mults.append(x.shape[-1] * spec[1])
        else:
            m = {"R": nn.ReLU, "LR": nn.LeakyReLU, "E": nn.ELU, "S": nn.Sigmoid, "T": nn.Tanh}.get(kind)
            m = m() if m else nn.Softmax(dim=-1)
        mods.append((f"{kind.lower()}{i}", m))
        with torch.no_grad():
            x = m.eval()(x)
    from collections import OrderedDict
    model = nn.Sequential(OrderedDict(mods)).eval()
    n_weights = sum(p.numel() for p in model.parameters())
    return model, shape, mults, n_weights


def variants(arch: str, mults: list[int], n_weights: int) -> list[dict]:
    grid = []
    for prec, rf, io, strat in itertools.product(PRECISIONS, REUSE, IO_TYPES, STRATEGIES):
        if n_weights > MAX_WEIGHTS or max(mults) / rf > SIZE_LIMITS[strat]:
            continue
        if strat == "Resource" and rf == 1:
            continue                       # Resource with reuse 1 is the Latency datapath with extra control
        grid.append({"precision": prec, "reuse_factor": rf, "io_type": io, "strategy": strat})
    rnd = random.Random(f"{SEED}:{arch}")
    return sorted(rnd.sample(grid, min(VARIANTS_PER_ARCH, len(grid))),
                  key=lambda v: (v["io_type"], v["strategy"], PRECISIONS.index(v["precision"]), v["reuse_factor"]))


def design_name(arch: str, v: dict) -> str:
    w, i = v["precision"][len("ap_fixed<"):-1].split(",")
    io = {"io_parallel": "par", "io_stream": "str"}[v["io_type"]]
    return f"{arch}__fx{w}_{i}_rf{v['reuse_factor']}_{io}_{v['strategy'][:3].lower()}"


def generate(job: tuple) -> dict:
    arch, v, out = job
    name = design_name(arch, v)
    rec = {"design": name, "arch": arch, "family": arch, **v}
    ddir = Path(out) / name
    try:
        import hls4ml
        model, shape, _, _ = build_model(arch)
        cfg = hls4ml.utils.config_from_pytorch_model(
            model, shape, granularity="model", backend="Vitis", default_precision=v["precision"],
            default_reuse_factor=v["reuse_factor"], channels_last_conversion="internal", transpose_outputs=False)
        cfg["Model"]["Strategy"] = v["strategy"]
        if ddir.exists():
            shutil.rmtree(ddir)
        tmp = Path(str(ddir) + ".tmp")
        if tmp.exists():
            shutil.rmtree(tmp)
        hm = hls4ml.converters.convert_from_pytorch_model(
            model, hls_config=cfg, output_dir=str(tmp), project_name="myproject", backend="Vitis",
            io_type=v["io_type"], part=PART)
        hm.write()
        for junk in ("firmware/ap_types", "tb_data"):
            shutil.rmtree(tmp / junk, ignore_errors=True)
        os.replace(tmp, ddir)
        rec["status"] = "ok"
    except Exception as e:  # noqa: BLE001  (one failed model must not stop the sweep)
        rec["status"] = "error"
        rec["error"] = (repr(e) + " | " + traceback.format_exc().strip().splitlines()[-1])[:400]
    return rec


def _worker_init():
    import torch
    torch.set_num_threads(1)


def main(argv=None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--out", default="/mnt/d/HLS_heldout2/src/hls4ml_gen")
    ap.add_argument("-j", type=int, default=8)
    a = ap.parse_args(argv)
    import hls4ml
    import torch
    os.makedirs(a.out, exist_ok=True)
    jobs, sizes = [], {}
    for arch in ARCHS:
        _, _, mults, nw = build_model(arch)
        sizes[arch] = {"max_layer_mults": max(mults), "weights": nw}
        for v in variants(arch, mults, nw):
            jobs.append((arch, v, a.out))
    # spawned workers: forking after torch has started its thread pools can deadlock the children
    with ProcessPoolExecutor(a.j, mp_context=multiprocessing.get_context("spawn"),
                             initializer=_worker_init) as ex:
        recs = list(ex.map(generate, jobs, chunksize=4))
    man = {"generator": "circt tools/hls-est-validate/heldout2/gen_hls4ml.py", "seed": SEED,
           "hls4ml_version": hls4ml.__version__, "torch_version": torch.__version__, "part": PART,
           "grid": {"precision": PRECISIONS, "reuse_factor": REUSE, "io_type": IO_TYPES, "strategy": STRATEGIES},
           "variants_per_arch": VARIANTS_PER_ARCH, "size_limits": SIZE_LIMITS, "max_weights": MAX_WEIGHTS,
           "archs": {k: {"input_shape": list(ARCHS[k][0]), "layers": [list(s) for s in ARCHS[k][1]], **sizes[k]}
                     for k in ARCHS},
           "designs": recs}
    Path(a.out, "manifest.json").write_text(json.dumps(man, indent=1) + "\n", encoding="utf-8")
    ok = sum(r["status"] == "ok" for r in recs)
    print(f"{ok} of {len(recs)} designs written to {a.out}")
    for r in recs:
        if r["status"] != "ok":
            print(f"  {r['design']}: {r['error'][:200]}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
