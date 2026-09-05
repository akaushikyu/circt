//===- ConstantIndex.h - constant memref indices shared by passes ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// One definition of "this index is a compile-time constant" for the passes
// that have to agree on it:
//   --infer-vitis-split-array   td=off rule (b) completely partitions a
//                               dimension that only constants index;
//   --memory-banking-bram       an access whose bank index is a constant
//                               reads one bank, any other reads every bank
//                               and muxes them (f loads + f-1 selects).
// If banking resolved fewer constants than the inference, a dimension split
// *because* its indices are constant would be read through every bank, and
// each bank would be charged a port for every such access.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTINDEX_H
#define CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTINDEX_H

#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "mlir/IR/AffineExpr.h"
#include "mlir/IR/AffineMap.h"
#include "llvm/ADT/SmallVector.h"

#include <cstdint>
#include <optional>

namespace circt::hls_analysis {

/// The value of an index operand if it is a compile-time constant by the time
/// Vitis partitions and binds memories: an integer constant (also through
/// arith.index_cast / arith.index_castui), or the counter of an affine.for
/// with a constant lower bound that runs exactly once (the LLVM front end
/// folds such a loop away; cgeist usually does too).
inline std::optional<int64_t> getConstantIndexValue(mlir::Value v) {
  if (std::optional<int64_t> c = mlir::getConstantIntValue(v))
    return c;
  if (auto cast = v.getDefiningOp<mlir::arith::IndexCastOp>())
    return getConstantIndexValue(cast.getIn());
  if (auto cast = v.getDefiningOp<mlir::arith::IndexCastUIOp>()) {
    // Zero extension: only a non-negative source keeps its value.
    std::optional<int64_t> c = getConstantIndexValue(cast.getIn());
    if (c && *c >= 0)
      return c;
    return std::nullopt;
  }
  // An affine.apply whose operands all fold to constants (unrolling leaves
  // `affine.apply (d0 + 1)(%c0)` as the index of a memref.load).
  if (auto apply = v.getDefiningOp<mlir::affine::AffineApplyOp>()) {
    mlir::AffineMap map = apply.getAffineMap();
    if (map.getNumResults() != 1)
      return std::nullopt;
    llvm::SmallVector<int64_t, 4> operands;
    for (mlir::Value o : apply.getMapOperands()) {
      std::optional<int64_t> c = getConstantIndexValue(o);
      if (!c)
        return std::nullopt;
      operands.push_back(*c);
    }
    llvm::SmallVector<mlir::AffineExpr, 4> repl;
    for (int64_t c : operands)
      repl.push_back(mlir::getAffineConstantExpr(c, map.getContext()));
    unsigned nd = map.getNumDims();
    mlir::AffineExpr e = map.getResult(0).replaceDimsAndSymbols(
        llvm::ArrayRef(repl).take_front(nd), llvm::ArrayRef(repl).drop_front(nd));
    e = mlir::simplifyAffineExpr(e, 0, 0);
    if (auto ce = llvm::dyn_cast<mlir::AffineConstantExpr>(e))
      return ce.getValue();
    return std::nullopt;
  }
  if (mlir::affine::isAffineForInductionVar(v)) {
    mlir::affine::AffineForOp owner = mlir::affine::getForInductionVarOwner(v);
    if (owner.hasConstantLowerBound() &&
        mlir::affine::getConstantTripCount(owner) == uint64_t(1))
      return owner.getConstantLowerBound();
  }
  return std::nullopt;
}

/// `map` (taking `operands`, dimensions first) with every operand that
/// getConstantIndexValue resolves replaced by its value and every result
/// simplified. The map keeps its dimension and symbol counts, so it still
/// takes `operands`; it computes the same addresses at run time.
inline mlir::AffineMap foldConstantIndexOperands(mlir::AffineMap map,
                                                 mlir::ValueRange operands) {
  mlir::MLIRContext *ctx = map.getContext();
  unsigned numDims = map.getNumDims(), numSyms = map.getNumSymbols();
  llvm::SmallVector<mlir::AffineExpr, 8> dimRepl, symRepl;
  for (unsigned i = 0; i < numDims; ++i) {
    std::optional<int64_t> c = getConstantIndexValue(operands[i]);
    dimRepl.push_back(c ? mlir::getAffineConstantExpr(*c, ctx)
                        : mlir::getAffineDimExpr(i, ctx));
  }
  for (unsigned i = 0; i < numSyms; ++i) {
    std::optional<int64_t> c = getConstantIndexValue(operands[numDims + i]);
    symRepl.push_back(c ? mlir::getAffineConstantExpr(*c, ctx)
                        : mlir::getAffineSymbolExpr(i, ctx));
  }
  llvm::SmallVector<mlir::AffineExpr, 4> results;
  for (mlir::AffineExpr expr : map.getResults())
    results.push_back(mlir::simplifyAffineExpr(
        expr.replaceDimsAndSymbols(dimRepl, symRepl), numDims, numSyms));
  return mlir::AffineMap::get(numDims, numSyms, results, ctx);
}

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTINDEX_H
