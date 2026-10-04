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
#include "circt/Dialect/Resource/Passes/ConstantIndex.h"

#include "mlir/Analysis/FlatLinearValueConstraints.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
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
  // Nested applies and index arithmetic on constants (an unrolled copy's
  // `apply(d0 * 16)(apply(d0 + 6)(%c0))`, nikhil_p lab2 kernel_attention_V):
  // OPEN_ISSUES O151, key tool.hls.pipeline_decision.fold_nested_constant_guards.
  if (circt::hlsest::Config::get()
          .tool.hls.pipelineDecision.foldNestedConstantGuards)
    if (std::optional<int64_t> c =
            circt::hls_analysis::getConstantIndexValue(v))
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

/// The constant bounds [lb, ub] of `v` when it is the induction variable of
/// an affine.for or scf.for with constant bounds.
static std::optional<std::pair<int64_t, int64_t>> ivBounds(Value v) {
  if (auto forOp = getForInductionVarOwner(v)) {
    if (!forOp.hasConstantBounds() || forOp.getStepAsInt() <= 0)
      return std::nullopt;
    return std::make_pair(forOp.getConstantLowerBound(),
                          forOp.getConstantUpperBound() - 1);
  }
  auto arg = dyn_cast<BlockArgument>(v);
  if (!arg)
    return std::nullopt;
  auto forOp = dyn_cast<scf::ForOp>(arg.getOwner()->getParentOp());
  if (!forOp || forOp.getInductionVar() != v)
    return std::nullopt;
  std::optional<int64_t> lb = getConstantIntValue(forOp.getLowerBound());
  std::optional<int64_t> ub = getConstantIntValue(forOp.getUpperBound());
  std::optional<int64_t> st = getConstantIntValue(forOp.getStep());
  if (!lb || !ub || !st || *st <= 0)
    return std::nullopt;
  return std::make_pair(*lb, *ub - 1);
}

namespace {
/// An scf.if condition as affine constraints over the values it is computed
/// from (the leaves: loop induction variables, any other value as an
/// unbounded integer). A condition is a disjunction of conjunctions.
struct ConditionBuilder {
  MLIRContext *ctx;
  SmallVector<Value> leaves;
  /// Expressions that must be >= 0 in the whole domain for the translation
  /// to hold (the dividend of remsi / divsi, the operands of an unsigned
  /// compare).
  SmallVector<AffineExpr> nonNegative;
  struct Conj {
    SmallVector<AffineExpr> exprs;
    SmallVector<bool> eq;
  };
  using Disj = SmallVector<Conj, 2>;

  explicit ConditionBuilder(MLIRContext *ctx) : ctx(ctx) {}

  AffineExpr leaf(Value v) {
    auto *it = llvm::find(leaves, v);
    unsigned pos = it - leaves.begin();
    if (it == leaves.end())
      leaves.push_back(v);
    return getAffineDimExpr(pos, ctx);
  }

  /// `v` as an affine expression of the leaves, or null.
  AffineExpr expr(Value v, unsigned depth = 0) {
    if (depth > 32)
      return AffineExpr();
    if (std::optional<int64_t> c = getConstantIntValue(v))
      return getAffineConstantExpr(*c, ctx);
    Operation *def = v.getDefiningOp();
    if (!def)
      return leaf(v);
    auto sub = [&](Value x) { return expr(x, depth + 1); };
    if (auto apply = dyn_cast<AffineApplyOp>(def)) {
      AffineMap map = apply.getAffineMap();
      SmallVector<AffineExpr> dims, syms;
      for (auto [i, o] : llvm::enumerate(apply.getMapOperands())) {
        AffineExpr e = sub(o);
        if (!e)
          return AffineExpr();
        (i < map.getNumDims() ? dims : syms).push_back(e);
      }
      return map.getResult(0).replaceDimsAndSymbols(dims, syms);
    }
    if (isa<arith::IndexCastOp, arith::ExtSIOp>(def))
      return sub(def->getOperand(0));
    if (isa<arith::AddIOp, arith::SubIOp, arith::MulIOp>(def)) {
      AffineExpr a = sub(def->getOperand(0)), b = sub(def->getOperand(1));
      if (!a || !b)
        return AffineExpr();
      if (isa<arith::AddIOp>(def))
        return a + b;
      if (isa<arith::SubIOp>(def))
        return a - b;
      if (!isa<AffineConstantExpr>(a) && !isa<AffineConstantExpr>(b))
        return AffineExpr(); // a product of two variables
      return a * b;
    }
    // C's `%` normalised to a non-negative result
    // (`r = x rem c; r < 0 ? r + c : r`): x mod c for every x.
    if (auto sel = dyn_cast<arith::SelectOp>(def)) {
      auto cmp = sel.getCondition().getDefiningOp<arith::CmpIOp>();
      auto rem = sel.getFalseValue().getDefiningOp<arith::RemSIOp>();
      auto add = sel.getTrueValue().getDefiningOp<arith::AddIOp>();
      std::optional<int64_t> c =
          rem ? getConstantIntValue(rem.getRhs()) : std::nullopt;
      if (cmp && rem && add && c && *c > 0 &&
          cmp.getPredicate() == arith::CmpIPredicate::slt &&
          cmp.getLhs() == rem.getResult() &&
          getConstantIntValue(cmp.getRhs()) == 0 &&
          llvm::is_contained(add->getOperands(), rem.getResult()) &&
          llvm::any_of(add->getOperands(), [&](Value o) {
            return getConstantIntValue(o) == *c;
          })) {
        AffineExpr x = sub(rem.getLhs());
        return x ? x % *c : AffineExpr();
      }
      return leaf(v);
    }
    if (isa<arith::RemSIOp, arith::RemUIOp, arith::DivSIOp, arith::DivUIOp,
            arith::FloorDivSIOp>(def)) {
      std::optional<int64_t> c = getConstantIntValue(def->getOperand(1));
      AffineExpr x = sub(def->getOperand(0));
      if (!c || *c <= 0 || !x)
        return leaf(v);
      if (!isa<arith::FloorDivSIOp>(def))
        nonNegative.push_back(x); // truncation = floor for x >= 0
      return isa<arith::RemSIOp, arith::RemUIOp>(def) ? x % *c
                                                       : x.floorDiv(*c);
    }
    return leaf(v);
  }

  static Disj conj(AffineExpr e, bool eq) {
    Conj c;
    c.exprs.push_back(e);
    c.eq.push_back(eq);
    return Disj{c};
  }

  /// `cond` (or its negation) as constraints; nullopt when it is not
  /// expressible.
  std::optional<Disj> condition(Value cond, bool negate, unsigned depth = 0) {
    if (depth > 16)
      return std::nullopt;
    Operation *def = cond.getDefiningOp();
    if (auto cmp = dyn_cast_or_null<arith::CmpIOp>(def)) {
      AffineExpr a = expr(cmp.getLhs()), b = expr(cmp.getRhs());
      if (!a || !b)
        return std::nullopt;
      using P = arith::CmpIPredicate;
      P p = negate ? arith::invertPredicate(cmp.getPredicate())
                   : cmp.getPredicate();
      if (p == P::ult || p == P::ule || p == P::ugt || p == P::uge) {
        nonNegative.push_back(a);
        nonNegative.push_back(b);
        p = p == P::ult   ? P::slt
            : p == P::ule ? P::sle
            : p == P::ugt ? P::sgt
                          : P::sge;
      }
      AffineExpr d = a - b;
      switch (p) {
      case P::eq:
        return conj(d, true);
      case P::ne: {
        Disj r = conj(d - 1, false);
        r.append(conj(-d - 1, false));
        return r;
      }
      case P::slt:
        return conj(-d - 1, false);
      case P::sle:
        return conj(-d, false);
      case P::sgt:
        return conj(d - 1, false);
      case P::sge:
        return conj(d, false);
      default:
        return std::nullopt;
      }
    }
    if (isa_and_present<arith::AndIOp, arith::OrIOp>(def)) {
      // De Morgan: a negated and is an or of the negations.
      bool isAnd = isa<arith::AndIOp>(def) != negate;
      std::optional<Disj> x = condition(def->getOperand(0), negate, depth + 1);
      std::optional<Disj> y = condition(def->getOperand(1), negate, depth + 1);
      if (!x || !y)
        return std::nullopt;
      if (!isAnd) {
        x->append(*y);
        return x;
      }
      Disj r;
      for (const Conj &cx : *x)
        for (const Conj &cy : *y) {
          Conj c = cx;
          c.exprs.append(cy.exprs);
          c.eq.append(cy.eq);
          r.push_back(c);
        }
      return r;
    }
    return std::nullopt;
  }

  /// No integer point satisfies `c` with every leaf inside its loop's
  /// bounds.
  bool emptyConj(ArrayRef<AffineExpr> exprs, ArrayRef<bool> eq) {
    unsigned n = leaves.size();
    SmallVector<AffineExpr> simplified;
    for (AffineExpr e : exprs) {
      e = simplifyAffineExpr(e, n, 0);
      if (!e.isPureAffine())
        return false;
      simplified.push_back(e);
    }
    FlatLinearValueConstraints cst(IntegerSet::get(n, 0, simplified, eq));
    for (auto [i, v] : llvm::enumerate(leaves))
      if (std::optional<std::pair<int64_t, int64_t>> b = ivBounds(v)) {
        cst.addBound(presburger::BoundType::LB, i, b->first);
        cst.addBound(presburger::BoundType::UB, i, b->second);
      }
    return cst.isEmpty();
  }

  bool empty(const Disj &d) {
    return llvm::all_of(d, [&](const Conj &c) {
      return emptyConj(c.exprs, c.eq);
    });
  }

  /// Every recorded non-negativity requirement holds in the domain.
  bool requirementsHold() {
    for (size_t i = 0; i < nonNegative.size(); ++i) // may grow: no iterators
      if (!emptyConj({-nonNegative[i] - 1}, {false}))
        return false;
    return true;
  }
};
} // namespace

/// An scf.if whose condition is affine in loop induction variables (after
/// the unroll, of the copy's constant index and the remaining loops'
/// variables): kernel w9r11rev_fg_mod, `if ((j * 4 + k) % 8 == 0)` in an
/// unrolled k loop is `arith.remsi` + `scf.if`; copies k = 1..3 never run.
static GuardTruth evaluateGuard(scf::IfOp ifOp) {
  if (std::optional<int64_t> c = getConstantIntValue(ifOp.getCondition()))
    return *c ? GuardTruth::AlwaysTrue : GuardTruth::AlwaysFalse;
  // A comparison of values computed from constants only (an unrolled copy's
  // `index_cast(k) != 3`, Dehazing tile_median's window counters; VITIS_NOTES
  // N110 corpus): LLVM folds it before Vitis schedules.
  if (circt::hls_analysis::foldConstantConditionals())
    if (std::optional<bool> c =
            circt::hls_analysis::getConstantCondition(ifOp.getCondition()))
      return *c ? GuardTruth::AlwaysTrue : GuardTruth::AlwaysFalse;
  ConditionBuilder cb(ifOp.getContext());
  std::optional<ConditionBuilder::Disj> t =
      cb.condition(ifOp.getCondition(), /*negate=*/false);
  std::optional<ConditionBuilder::Disj> f =
      cb.condition(ifOp.getCondition(), /*negate=*/true);
  if (!t || !f)
    return GuardTruth::Unknown;
  // Only conditions that name a loop variable: the others are left to
  // --canonicalize / --sccp.
  if (!llvm::any_of(cb.leaves, [](Value v) { return ivBounds(v).has_value(); }))
    return GuardTruth::Unknown;
  if (!cb.requirementsHold())
    return GuardTruth::Unknown;
  if (cb.empty(*t))
    return GuardTruth::AlwaysFalse;
  if (cb.empty(*f))
    return GuardTruth::AlwaysTrue;
  return GuardTruth::Unknown;
}

/// Replace `ifOp` by the operations of `block` (or by nothing).
static void inlineArm(Operation *ifOp, Block *block) {
  if (!block) {
    ifOp->erase();
    return;
  }
  Operation *yield = block->getTerminator();
  for (Operation &op : llvm::make_early_inc_range(block->without_terminator()))
    op.moveBefore(ifOp);
  ifOp->replaceAllUsesWith(yield->getOperands());
  ifOp->erase();
}

/// VITIS_NOTES N89 (b): inside the then arm of an if whose set, with its
/// constant operands substituted, holds an equality that fixes one operand
/// (`j + 3 - 18 == 0` in unrolled copy k = 3: j = 15), that operand is that
/// constant (LLVM GVN propagates a dominating equality into the branch).
/// The uses of the operand in the arm are replaced by the constant, so an
/// address it computes becomes constant and an invariant load can be
/// hoisted (kernel w9r11rev_fg_unr: `if (k + j == 18) s += buf[k * 16 + j]`,
/// copy 3 reads buf[63]; Vitis keeps one read port per cycle, 1 BRAM).
/// Returns the number of operands replaced.
static unsigned pinEqualOperands(AffineIfOp ifOp) {
  IntegerSet set = ifOp.getIntegerSet();
  unsigned numDims = set.getNumDims(), numSyms = set.getNumSymbols();
  MLIRContext *ctx = ifOp.getContext();
  SmallVector<AffineExpr> dims, syms;
  for (auto [i, v] : llvm::enumerate(ifOp.getOperands())) {
    std::optional<int64_t> c = constantOperand(v);
    AffineExpr e = c ? getAffineConstantExpr(*c, ctx)
                 : i < numDims ? getAffineDimExpr(i, ctx)
                               : getAffineSymbolExpr(i - numDims, ctx);
    (i < numDims ? dims : syms).push_back(e);
  }
  unsigned pinned = 0;
  Region &thenRegion = ifOp.getThenRegion();
  for (unsigned k = 0, e = set.getNumConstraints(); k < e; ++k) {
    if (!set.isEq(k))
      continue;
    AffineExpr expr = simplifyAffineExpr(
        set.getConstraint(k).replaceDimsAndSymbols(dims, syms), numDims,
        numSyms);
    if (!expr.isPureAffine())
      continue;
    // expr = coeff * x + rest, rest a constant, |coeff| == 1.
    std::optional<unsigned> pos;
    bool several = false;
    for (unsigned i = 0; i < numDims + numSyms; ++i) {
      bool isDim = i < numDims;
      if (!(isDim ? expr.isFunctionOfDim(i)
                  : expr.isFunctionOfSymbol(i - numDims)))
        continue;
      several |= pos.has_value();
      pos = i;
    }
    if (!pos || several)
      continue;
    AffineExpr zero = getAffineConstantExpr(0, ctx);
    SmallVector<AffineExpr> d0(dims), s0(syms);
    (*pos < numDims ? d0[*pos] : s0[*pos - numDims]) = zero;
    auto rest = dyn_cast<AffineConstantExpr>(simplifyAffineExpr(
        expr.replaceDimsAndSymbols(d0, s0), numDims, numSyms));
    AffineExpr one = getAffineConstantExpr(1, ctx);
    SmallVector<AffineExpr> d1(d0), s1(s0);
    (*pos < numDims ? d1[*pos] : s1[*pos - numDims]) = one;
    auto atOne = dyn_cast<AffineConstantExpr>(simplifyAffineExpr(
        expr.replaceDimsAndSymbols(d1, s1), numDims, numSyms));
    if (!rest || !atOne)
      continue;
    int64_t coeff = atOne.getValue() - rest.getValue();
    if (coeff != 1 && coeff != -1)
      continue;
    int64_t value = -rest.getValue() / coeff;
    Value operand = ifOp.getOperand(*pos);
    if (!isa<IndexType>(operand.getType()) ||
        !llvm::any_of(operand.getUses(), [&](OpOperand &u) {
          return thenRegion.isAncestor(u.getOwner()->getParentRegion());
        }))
      continue;
    auto func = ifOp->getParentOfType<FunctionOpInterface>();
    if (!func || func.getFunctionBody().empty())
      continue;
    OpBuilder b = OpBuilder::atBlockBegin(&func.getFunctionBody().front());
    Value c = arith::ConstantIndexOp::create(b, ifOp.getLoc(), value);
    operand.replaceUsesWithIf(c, [&](OpOperand &u) {
      return thenRegion.isAncestor(u.getOwner()->getParentRegion());
    });
    ++pinned;
  }
  return pinned;
}

/// Count `what` on the nearest enclosing loop (a --bram-debug record that
/// the conversion to a pipeline carries).
static void countOnLoop(Operation *op, StringRef what, unsigned n) {
  if (!n)
    return;
  Operation *loop = op->getParentOfType<AffineForOp>();
  if (!loop)
    loop = op->getParentOfType<scf::ForOp>();
  if (!loop)
    return;
  auto prev = loop->getAttrOfType<IntegerAttr>(what);
  loop->setAttr(what, IntegerAttr::get(IntegerType::get(op->getContext(), 64),
                                       (prev ? prev.getInt() : 0) + n));
}

circt::hls_analysis::FoldedGuards
circt::hls_analysis::foldConstantAffineIfs(Operation *root) {
  SmallVector<Operation *> ifs;
  root->walk([&](Operation *op) {
    if (isa<AffineIfOp, scf::IfOp>(op))
      ifs.push_back(op);
  });
  FoldedGuards result;
  // Post-order: an inner if is visited (and possibly moved out of its arm)
  // before the if that holds it.
  for (Operation *op : ifs) {
    GuardTruth truth;
    Block *thenBlock, *elseBlock;
    if (auto ifOp = dyn_cast<AffineIfOp>(op)) {
      truth = evaluateGuard(ifOp);
      thenBlock = ifOp.getThenBlock();
      elseBlock = ifOp.hasElse() ? ifOp.getElseBlock() : nullptr;
      if (truth == GuardTruth::Unknown) {
        unsigned pinned = pinEqualOperands(ifOp);
        result.pinnedOperands += pinned;
        countOnLoop(op, kPinnedGuardOperandsAttr, pinned);
        continue;
      }
    } else {
      auto sIf = cast<scf::IfOp>(op);
      truth = evaluateGuard(sIf);
      thenBlock = sIf.thenBlock();
      elseBlock = sIf.elseBlock();
      if (truth == GuardTruth::Unknown)
        continue;
      ++result.scfIfs;
    }
    countOnLoop(op, kFoldedGuardsAttr, 1);
    inlineArm(op, truth == GuardTruth::AlwaysTrue ? thenBlock : elseBlock);
    ++result.folded;
  }
  return result;
}
