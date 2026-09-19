//===- FoldUnrolledGuards.cpp - drop affine.if arms that never run --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// See FoldUnrolledGuards.h. Used by --auto-pipeline-unroll right after its
// unroll decisions (tool.hls.pipeline_decision.fold_unrolled_guards).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/FoldUnrolledGuards.h"

#include "mlir/Analysis/FlatLinearValueConstraints.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "mlir/IR/AffineExprVisitor.h"
#include "mlir/IR/IntegerSet.h"

using namespace mlir;
using namespace mlir::affine;

namespace {
/// What a guard is once its constant operands are substituted.
enum class GuardTruth { Unknown, AlwaysTrue, AlwaysFalse };
} // namespace

/// The constant value of an if operand: an arith.constant, or an
/// affine.apply whose operands are all constants.
static std::optional<int64_t> constantOperand(Value v) {
  if (std::optional<int64_t> c = getConstantIntValue(v))
    return c;
  auto apply = v.getDefiningOp<AffineApplyOp>();
  if (!apply)
    return std::nullopt;
  SmallVector<Attribute> operands;
  for (Value o : apply.getMapOperands()) {
    std::optional<int64_t> c = getConstantIntValue(o);
    if (!c)
      return std::nullopt;
    operands.push_back(IntegerAttr::get(o.getType(), *c));
  }
  SmallVector<Attribute> results;
  if (failed(apply.getAffineMap().constantFold(operands, results)) ||
      results.size() != 1)
    return std::nullopt;
  if (auto i = dyn_cast_or_null<IntegerAttr>(results.front()))
    return i.getInt();
  return std::nullopt;
}

static GuardTruth evaluateGuard(AffineIfOp ifOp) {
  IntegerSet set = ifOp.getIntegerSet();
  unsigned numDims = set.getNumDims(), numSyms = set.getNumSymbols();
  MLIRContext *ctx = ifOp.getContext();
  SmallVector<AffineExpr> dims, syms;
  bool anyConstant = false;
  for (auto [i, v] : llvm::enumerate(ifOp.getOperands())) {
    std::optional<int64_t> c = constantOperand(v);
    anyConstant |= c.has_value();
    AffineExpr e = c ? getAffineConstantExpr(*c, ctx)
                 : i < numDims ? getAffineDimExpr(i, ctx)
                               : getAffineSymbolExpr(i - numDims, ctx);
    (i < numDims ? dims : syms).push_back(e);
  }
  bool allTrue = true;
  SmallVector<AffineExpr> constraints;
  for (unsigned k = 0, e = set.getNumConstraints(); k < e; ++k) {
    AffineExpr expr = simplifyAffineExpr(
        set.getConstraint(k).replaceDimsAndSymbols(dims, syms), numDims,
        numSyms);
    constraints.push_back(expr);
    auto c = dyn_cast<AffineConstantExpr>(expr);
    if (!c) {
      allTrue = false;
      continue;
    }
    bool holds = set.isEq(k) ? c.getValue() == 0 : c.getValue() >= 0;
    if (!holds)
      return GuardTruth::AlwaysFalse;
  }
  if (allTrue)
    return anyConstant ? GuardTruth::AlwaysTrue : GuardTruth::Unknown;
  // A semi-affine constraint (a product of two operands) cannot be
  // flattened.
  if (!llvm::all_of(constraints,
                    [](AffineExpr e) { return e.isPureAffine(); }))
    return GuardTruth::Unknown;
  // The remaining constraints over the other operands: empty when no integer
  // point satisfies them inside the bounds of the loops whose induction
  // variables they name (`k + 4 * j == 127` with the copy's k = 0 has no
  // integer j; Autoencoder opt5 node5).
  FlatLinearValueConstraints cst(
      IntegerSet::get(numDims, numSyms, constraints, set.getEqFlags()));
  for (auto [i, v] : llvm::enumerate(ifOp.getOperands())) {
    auto forOp = getForInductionVarOwner(v);
    if (!forOp || !forOp.hasConstantBounds())
      continue;
    cst.addBound(presburger::BoundType::LB, i, forOp.getConstantLowerBound());
    cst.addBound(presburger::BoundType::UB, i,
                 forOp.getConstantUpperBound() - 1);
  }
  return cst.isEmpty() ? GuardTruth::AlwaysFalse : GuardTruth::Unknown;
}

/// Replace `ifOp` by the operations of `block` (or by nothing).
static void inlineArm(AffineIfOp ifOp, Block *block) {
  if (!block) {
    ifOp.erase();
    return;
  }
  auto yield = cast<AffineYieldOp>(block->getTerminator());
  for (Operation &op : llvm::make_early_inc_range(block->without_terminator()))
    op.moveBefore(ifOp);
  ifOp.replaceAllUsesWith(yield.getOperands());
  ifOp.erase();
}

unsigned circt::hls_analysis::foldConstantAffineIfs(Operation *root) {
  SmallVector<AffineIfOp> ifs;
  root->walk([&](AffineIfOp ifOp) { ifs.push_back(ifOp); });
  unsigned folded = 0;
  // Post-order: an inner if is visited (and possibly moved out of its arm)
  // before the if that holds it.
  for (AffineIfOp ifOp : ifs) {
    switch (evaluateGuard(ifOp)) {
    case GuardTruth::Unknown:
      continue;
    case GuardTruth::AlwaysTrue:
      inlineArm(ifOp, ifOp.getThenBlock());
      break;
    case GuardTruth::AlwaysFalse:
      inlineArm(ifOp, ifOp.hasElse() ? ifOp.getElseBlock() : nullptr);
      break;
    }
    ++folded;
  }
  return folded;
}
