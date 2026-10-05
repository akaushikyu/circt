#!/usr/bin/env python3
import subprocess
import sys
from pathlib import Path

OVERRIDES = {
    "f62e82b808f32165ba6a4b8b0909baa9e9554514",
    "bb123425387fba2afbf4f7d606fa5129a491ed28",
    "8f8ebd94e3ac63078f65ce4c4ceec3fd22933e4d",
    "7a380392f8863dd60dc91b3d698cc453c0a3d7af",
    "8f9672f2fd03365644e1109c26da6c8ffdfb8e02",
    "2266f4a3048a270058d4c99fbeccef413277b948",
}
TARGET_COMMITS = {
    "870f3646c670fd812c7f639d11e88b1d78af7b0e",
    "bd47ae782641625e4ebf364f3f07f6be87650343",
    "c3ef8ec41a6f15ee84cbb824f7732156d5e06ef5",
    "b5d4759c597f70a553a02790d9dc3c574817643a",
    "adf407973b06f73c9eed1f5b84cb2355e078c8a8",
    "1a34ba4a07f9779320cbc860c3a29e8a007e61bf",
    "f74c341e364938c6bcfdba4adfabfe4b93059428",
}


def main():
    path = Path(sys.argv[1])
    lines = path.read_text().splitlines()
    output = []
    for line in lines:
        output.append(line)
        fields = line.split()
        if not fields or fields[0] not in ("pick", "p"):
            continue
        commit = fields[1]
        full_commit = subprocess.check_output(
            ["git", "rev-parse", commit], text=True
        ).strip()
        subject = subprocess.check_output(
            ["git", "show", "-s", "--format=%s", commit], text=True
        ).strip()
        if (
            len(subject) > 72
            or full_commit in OVERRIDES
            or full_commit in TARGET_COMMITS
        ):
            output.append(
                f"exec env ORIGINAL_COMMIT={full_commit} python3 tools/history_commit.py"
            )
    path.write_text("\n".join(output) + "\n")


if __name__ == "__main__":
    main()
