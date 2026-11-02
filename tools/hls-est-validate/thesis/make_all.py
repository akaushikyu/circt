#!/usr/bin/env python3
"""Render the whole thesis draft in the order the generators depend on each other.

    ~/hls-est-work/coord/scratch/thesis/venv/bin/python make_all.py [--no-figures]

1. make_thesis_tables.py  chapter 6; writes data/ch06-numbers.json, which the frame chapters read
2. make_ch3_methodology.py chapter 3
3. make_ch4_rules.py       chapter 4 and Appendix A
4. frame_chapters.py       abstract and chapters 1, 2, 5, 7, 8 (quote chapter 6's numbers as ev_*)

Every generator runs with the interpreter that runs this script (the private venv has matplotlib).
"""
import argparse
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--no-figures", action="store_true", help="passed to make_thesis_tables.py")
    a = ap.parse_args()
    steps = [["make_thesis_tables.py"] + (["--no-figures"] if a.no_figures else []),
             ["make_ch3_methodology.py"], ["make_ch4_rules.py"], ["frame_chapters.py"]]
    for step in steps:
        print("==", " ".join(step), flush=True)
        subprocess.run([sys.executable, str(HERE / step[0])] + step[1:], check=True, cwd=str(HERE))


if __name__ == "__main__":
    main()
