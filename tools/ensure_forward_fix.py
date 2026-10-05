#!/usr/bin/env python3
from pathlib import Path


path = Path("lib/Dialect/Resource/Passes/PolygeistCompat.cpp")
source = path.read_text()
guard = """        if (!from.getElementType().isIntOrFloat() || from.getNumElements() <= 1)
          continue;
        if (auto argument = dyn_cast<BlockArgument>(cast.getSource()))
          if (auto owner =
                  dyn_cast<func::FuncOp>(argument.getOwner()->getParentOp()))
            if (owner.isPublic())
              continue;
"""
if guard not in source:
    marker = "        forms.push_back({static_cast<unsigned>(loopIndex), from});"
    if source.count(marker) != 1:
        raise SystemExit("could not locate cast-specialization insertion point")
    source = source.replace(marker, guard + marker)
    path.write_text(source)

path = Path("lib/Dialect/Resource/Passes/BRAMAnalysis.cpp")
source = path.read_text()
shadowing_loc = '''static std::string locString(Location loc) {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  loc.print(os);
  return stringValue;
}

'''
if shadowing_loc in source:
    source = source.replace(shadowing_loc, "")
    path.write_text(source)

path = Path("lib/Dialect/Resource/Passes/AutoPipelineUnroll.cpp")
source = path.read_text()
include = '#include "circt/Dialect/Resource/Passes/AffineUnroll.h"\n'
if include not in source:
    anchor = '#include "mlir/Dialect/Affine/LoopUtils.h"\n'
    if anchor not in source:
        raise SystemExit("could not locate AffineUnroll include point")
    source = source.replace(anchor, anchor + include)
for old, new in (
    ("loopUnrollFull(loop)", "circt::hls_analysis::hlsLoopUnrollFull(loop)"),
    (
        "loopUnrollByFactor(loop, factor)",
        "circt::hls_analysis::hlsLoopUnrollByFactor(loop, factor)",
    ),
    ("loopUnrollFull(forOp)", "circt::hls_analysis::hlsLoopUnrollFull(forOp)"),
):
    source = source.replace(old, new)
path.write_text(source)
