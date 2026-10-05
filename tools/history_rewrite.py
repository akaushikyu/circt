#!/usr/bin/env python3
import argparse
import re
from pathlib import Path


RENAMES = {
    "a": "arrayValue",
    "b": "buildPoint",
    "c": "candidateValue",
    "d": "dimensionIndex",
    "e": "entryValue",
    "f": "fieldValue",
    "g": "globalOp",
    "h": "highIndex",
    "i": "loopIndex",
    "j": "innerIndex",
    "k": "keyValue",
    "l": "lowerIndex",
    "m": "memoryOp",
    "n": "elementCount",
    "o": "opHandle",
    "p": "portValue",
    "q": "queueValue",
    "r": "resultValue",
    "s": "stringValue",
    "t": "typeValue",
    "u": "useValue",
    "v": "valueHandle",
    "w": "widthValue",
    "x": "exprValue",
    "y": "rowValue",
    "z": "depthValue",
    "ty": "memRefType",
    "ctx": "context",
    "res": "passResult",
    "val": "operandValue",
    "idx": "indexValue",
    "cb": "callback",
    "gg": "globalUse",
    "vn": "variableName",
    "sym": "symbolName",
    "init": "initialValue",
    "dense": "denseValue",
    "uses": "symbolUses",
    "alloca": "localAlloca",
    "repl": "replacementValue",
    "builder": "passBuilder",
    "call": "callSite",
    "callable": "calledFunction",
    "wouldBeCloned": "cloneRequested",
    "ret": "returnOp",
    "newDest": "continuationBlock",
    "valuesToRepl": "replacementValues",
    "registry": "targetRegistry",
    "dialect": "targetDialect",
    "inlineIgnoreInlineOff": "allowInliningKeptCallees",
    "HlsFuncInlinerInterface": "VitisInlinerInterface",
}

HEADERS = {
    "DeadMemoryElimination.cpp": "drop memory results nobody uses",
    "VitisFold.cpp": "fold the forms Vitis optimizes",
    "PromoteGlobalsToAllocas.cpp": "localize single-function globals",
    "CallInstances.cpp": "charge functions per call instance",
    "HlsInliner.cpp": "respect Vitis inline decisions",
    "PolygeistCompat.cpp": "bridge Polygeist forms into hls-est",
    "PartitionLayout.cpp": "lay out memory banks",
    "RamWidthNarrowing.cpp": "narrow RAM element widths",
    "MathCores.cpp": "price math operations",
    "StreamFifos.cpp": "charge stream channels as FIFOs",
    "FunctionPipelines.cpp": "group ROMs by function pipeline",
}


def tokenize(source):
    pattern = re.compile(
        r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|'
        r"'(?:\\.|[^'\\])*'|[A-Za-z_]\w*|\d[\w.+-]*|::|\s+|.",
        re.DOTALL,
    )
    return pattern.findall(source)


def transform(source):
    tokens = tokenize(source)
    member_names = set(re.findall(r"(?:\.|->)\s*([A-Za-z_]\w*)", source))
    output = []
    for index, token in enumerate(tokens):
        if token.startswith("//") and not token.startswith("///"):
            if "SPDX-License-Identifier" not in token:
                continue
        if token.startswith("/*"):
            if "SPDX-License-Identifier" not in token:
                continue
            output.append(token)
            continue
        if token in RENAMES and token not in member_names and (
            index == 0 or tokens[index - 1] not in (".", "->", "::")
        ):
            output.append(RENAMES[token])
        else:
            output.append(token)
    return "".join(output)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("source", type=Path)
    args = parser.parse_args()
    source = args.source.read_text()
    if not source.startswith("//===- "):
        description = HEADERS.get(args.source.name, "estimate Vitis resources")
        prefix = "//===- "
        suffix = " ===//"
        content = f"{args.source.name} - {description}"
        dashes = "-" * max(3, 79 - len(prefix) - len(content) - len(suffix))
        header = prefix + content + " " + dashes + suffix + "\n\n"
        source = header + source
    args.source.write_text(transform(source))


if __name__ == "__main__":
    main()
