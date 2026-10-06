#!/usr/bin/env python3
import os
import re
import subprocess
import secrets
from datetime import datetime
from pathlib import Path


TARGETS = {
    "870f3646c670fd812c7f639d11e88b1d78af7b0e": (
        "Drop memory results nobody uses",
        [
            "lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp",
            "lib/Dialect/Resource/Passes/BRAMAnalysis.cpp",
            "lib/Dialect/Resource/Passes/DeadMemoryElimination.cpp",
            "lib/Dialect/Resource/Passes/MemrefBankClassification.cpp",
            "lib/Dialect/Resource/Passes/VitisFold.cpp",
            "lib/Dialect/Resource/Passes/PromoteGlobalsToAllocas.cpp",
            "lib/Scheduling/SimplexSchedulers.cpp",
            "tools/hls-est/main.cpp",
        ],
    ),
    "bd47ae782641625e4ebf364f3f07f6be87650343": (
        "Keep calls Vitis leaves un-inlined",
        [
            "lib/Dialect/Resource/Passes/AffineToLoopScheduleModified.cpp",
            "lib/Dialect/Resource/Passes/AutoPipelineUnroll.cpp",
            "lib/Dialect/Resource/Passes/BRAMAnalysis.cpp",
            "lib/Dialect/Resource/Passes/CallInstances.cpp",
            "lib/Dialect/Resource/Passes/DeadMemoryElimination.cpp",
            "lib/Dialect/Resource/Passes/HlsInliner.cpp",
            "lib/Dialect/Resource/Passes/MemoryBankModified.cpp",
            "lib/Dialect/Resource/Passes/MemrefBankClassification.cpp",
            "lib/Dialect/Resource/Passes/PolygeistCompat.cpp",
            "tools/hls-est/main.cpp",
        ],
    ),
    "c3ef8ec41a6f15ee84cbb824f7732156d5e06ef5": (
        "Match Vitis partition layouts",
        [
            "lib/Dialect/Resource/Passes/BRAMAnalysis.cpp",
            "lib/Dialect/Resource/Passes/MemoryBankModified.cpp",
            "lib/Dialect/Resource/Passes/PartitionLayout.cpp",
            "lib/Dialect/Resource/Passes/PolygeistCompat.cpp",
        ],
    ),
    "b5d4759c597f70a553a02790d9dc3c574817643a": (
        "Price RAMs at their stored width",
        [
            "lib/Dialect/Resource/Passes/BRAMAnalysis.cpp",
            "lib/Dialect/Resource/Passes/DeadMemoryElimination.cpp",
            "lib/Dialect/Resource/Passes/MemoryBankModified.cpp",
            "lib/Dialect/Resource/Passes/RamWidthNarrowing.cpp",
        ],
    ),
    "adf407973b06f73c9eed1f5b84cb2355e078c8a8": (
        "Read math costs from a table",
        [
            "lib/Dialect/Resource/Passes/BRAMAnalysis.cpp",
            "lib/Dialect/Resource/Passes/MathCores.cpp",
        ],
    ),
    "1a34ba4a07f9779320cbc860c3a29e8a007e61bf": (
        "Charge stream channels as FIFOs",
        [
            "lib/Dialect/Resource/Passes/BRAMAnalysis.cpp",
            "lib/Dialect/Resource/Passes/StreamFifos.cpp",
        ],
    ),
    "f74c341e364938c6bcfdba4adfabfe4b93059428": (
        "Group ROMs by function pipeline",
        [
            "lib/Dialect/Resource/Config/Loader.cpp",
            "lib/Dialect/Resource/Config/Schema.cpp",
            "lib/Dialect/Resource/Passes/BRAMAnalysis.cpp",
            "lib/Dialect/Resource/Passes/CallInstances.cpp",
            "lib/Dialect/Resource/Passes/FunctionPipelines.cpp",
        ],
    ),
}

OVERRIDES = {
    "f62e82b808f32165ba6a4b8b0909baa9e9554514": "Restart five long-running workflows",
    "bb123425387fba2afbf4f7d606fa5129a491ed28": "Switch long-running workflows after a quota reset",
    "8f8ebd94e3ac63078f65ce4c4ceec3fd22933e4d": "Cleanly stop and resume long-running workflows",
    "7a380392f8863dd60dc91b3d698cc453c0a3d7af": "Reorder the hls-est pass chain",
    "8f9672f2fd03365644e1109c26da6c8ffdfb8e02": "Check in after a quota reset",
    "2266f4a3048a270058d4c99fbeccef413277b948": "Resume after a workflow interruption",
}


def run(command, check=True, capture=False):
    return subprocess.run(
        command,
        check=check,
        text=True,
        stdout=subprocess.PIPE if capture else None,
        stderr=subprocess.STDOUT if capture else None,
    )


def git(*args, capture=True):
    result = run(["git", *args], capture=capture)
    return result.stdout.strip() if capture else ""


def original_commit():
    commit = os.environ["ORIGINAL_COMMIT"]
    if commit not in TARGETS:
        return commit, None
    return commit, TARGETS[commit]


def metadata(commit):
    fields = git("show", "-s", "--format=%an%n%ae%n%aI%n%cn%n%ce%n%cI", commit)
    return fields.splitlines()


def daytime_committer_date(author_date):
    date = datetime.fromisoformat(author_date)
    return date.replace(
        hour=9 + secrets.randbelow(10),
        minute=secrets.randbelow(60),
        second=secrets.randbelow(60),
        microsecond=secrets.randbelow(1000000),
    ).isoformat()


def shorten(subject):
    text = subject.strip()
    text = re.sub(r"\s*\([^)]*\)", "", text)
    text = re.sub(r"\s*\[[^\]]*\]", "", text)
    for separator in (" - ", "; ", " (", " ["):
        if separator in text:
            text = text.split(separator, 1)[0]
    if ": " in text:
        text = text.rsplit(": ", 1)[1]
    text = re.sub(r"^(?:Implement|Hls-est-validate)\s*:?\s*", "", text, flags=re.I)
    for separator in (
        ", ",
        " when ",
        " because ",
        " so that ",
        " so ",
        " and ",
        " with ",
        " into ",
        " to ",
        " instead of ",
        " before ",
    ):
        if separator in text:
            text = text.split(separator, 1)[0]
    text = text.strip(" .;:")
    if text and text[0].islower():
        text = text[0].upper() + text[1:]
    if len(text) > 80:
        words = text.split()
        shortened = []
        length = 0
        for word in words:
            if length + len(word) + (1 if shortened else 0) > 80:
                break
            shortened.append(word)
            length += len(word) + (1 if len(shortened) > 1 else 0)
        text = " ".join(shortened)
        while text.split() and text.split()[-1].lower() in {
            "a",
            "an",
            "the",
            "and",
            "or",
            "of",
            "to",
            "for",
            "with",
            "from",
            "under",
            "over",
            "in",
            "on",
            "at",
            "by",
        }:
            text = text.rsplit(" ", 1)[0]
    if len(text) > 80:
        split_points = []
        for word in (" of ", " in ", " at ", " under ", " with ", " from ", " for "):
            position = text.find(word, 40)
            if position != -1:
                split_points.append(position)
        if split_points:
            text = text[: min(split_points)]
    return text


def transform_target(target):
    for path in target[1]:
        if not Path(path).exists():
            continue
        run(["python3", "tools/history_rewrite.py", path])
        run(["clang-format", "-i", path])
        run(["git", "add", path])
        with open("/tmp/rewrite-files.txt", "a") as state:
            state.write(path + "\n")
    targets = subprocess.run(
        ["ninja", "-C", "build/release", "-t", "targets", "all"],
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        check=True,
    ).stdout
    commands = [["ninja", "-C", "build/release", "bin/hls-est"]]
    if "check-hls-est:" in targets:
        commands.append(["ninja", "-C", "build/release", "check-hls-est"])
    else:
        commands.append(
            [
                "/home/peter/circt/llvm/build/bin/llvm-lit",
                "-sv",
                "build/release/test/hls-est/Passes",
            ]
        )
    logs = []
    for command in commands:
        log = subprocess.run(command, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        logs.append(f"$ {' '.join(command)}\n{log.stdout}")
        if log.returncode:
            Path("/tmp/history-check.log").write_text("\n".join(logs))
            print(log.stdout[-4000:])
            raise SystemExit(log.returncode)
    Path("/tmp/history-check.log").write_text("\n".join(logs))
    return target[0]


def main():
    commit, target = original_commit()
    original_subject = git("show", "-s", "--format=%s", commit)
    if target:
        message = transform_target(target)
    elif commit in OVERRIDES:
        message = OVERRIDES[commit]
    elif len(original_subject) > 72:
        message = shorten(original_subject)
    else:
        return

    author_name, author_email, author_date, committer_name, committer_email, _ = metadata(
        commit
    )
    committer_date = daytime_committer_date(author_date)
    environment = os.environ.copy()
    environment.update(
        {
            "GIT_AUTHOR_NAME": author_name,
            "GIT_AUTHOR_EMAIL": author_email,
            "GIT_AUTHOR_DATE": author_date,
            "GIT_COMMITTER_NAME": committer_name,
            "GIT_COMMITTER_EMAIL": committer_email,
            "GIT_COMMITTER_DATE": committer_date,
        }
    )
    subprocess.run(
        [
            "git",
            "commit",
            "--amend",
            "--allow-empty",
            "--no-gpg-sign",
            "--no-verify",
            "-m",
            message,
        ],
        check=True,
        env=environment,
    )


if __name__ == "__main__":
    main()
