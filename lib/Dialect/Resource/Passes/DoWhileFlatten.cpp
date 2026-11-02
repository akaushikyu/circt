//===- DoWhileFlatten.cpp - Vitis' do-while flatten refusal ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// See DoWhileFlatten.h and VITIS_NOTES N96.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/DoWhileFlatten.h"

#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/AffineExprVisitor.h"
#include "mlir/IR/IntegerSet.h"
#include "mlir/Interfaces/FunctionInterfaces.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "llvm/ADT/DenseMap.h"

using namespace mlir;
using namespace mlir::affine;

namespace {

/// The values of the sub-loop indices for one unrolled copy.
using Env = llvm::DenseMap<Value, int64_t>;

/// Integer values a copy computes from its constant sub-loop indices (the
/// arithmetic cgeist emits for C conditions); nullopt for anything else.
class Evaluator {
public:
  explicit Evaluator(const Env &env) : env(env) {}

  std::optional<int64_t> eval(Value v) {
    if (auto it = env.find(v); it != env.end())
      return it->second;
    Operation *op = v.getDefiningOp();
    if (!op)
      return std::nullopt;
    if (auto c = dyn_cast<arith::ConstantOp>(op)) {
      auto attr = dyn_cast<IntegerAttr>(c.getValue());
      if (!attr)
        return std::nullopt;
      const APInt &value = attr.getValue();
      return value.getBitWidth() == 1 ? static_cast<int64_t>(value.getZExtValue())
                                      : value.getSExtValue();
    }
    if (isa<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
            arith::ExtUIOp>(op))
      return eval(op->getOperand(0));
    if (auto trunc = dyn_cast<arith::TruncIOp>(op)) {
      std::optional<int64_t> x = eval(trunc.getIn());
      if (x && trunc.getType().isInteger(1))
        return *x & 1;
      return x;
    }
    if (auto sel = dyn_cast<arith::SelectOp>(op)) {
      std::optional<int64_t> c = eval(sel.getCondition());
      if (!c)
        return std::nullopt;
      return eval(*c ? sel.getTrueValue() : sel.getFalseValue());
    }
    if (auto cmp = dyn_cast<arith::CmpIOp>(op))
      return evalCmp(cmp);
    if (op->getNumOperands() == 2 && op->getNumResults() == 1 &&
        op->getNumRegions() == 0)
      return evalBinary(op);
    if (auto apply = dyn_cast<AffineApplyOp>(op))
      return evalMap(apply.getAffineMap(), apply.getMapOperands(), 0);
    if (auto ifOp = dyn_cast<AffineIfOp>(op)) {
      std::optional<bool> taken =
          evalSet(ifOp.getIntegerSet(), ifOp.getOperands());
      if (!taken)
        return std::nullopt;
      return evalYield(*taken ? ifOp.getThenRegion() : ifOp.getElseRegion(),
                       cast<OpResult>(v).getResultNumber());
    }
    if (auto ifOp = dyn_cast<scf::IfOp>(op)) {
      std::optional<int64_t> c = eval(ifOp.getCondition());
      if (!c)
        return std::nullopt;
      return evalYield(*c ? ifOp.getThenRegion() : ifOp.getElseRegion(),
                       cast<OpResult>(v).getResultNumber());
    }
    return std::nullopt;
  }

  /// Whether the copy satisfies `set` over `operands`; nullopt when an
  /// operand is not known.
  std::optional<bool> evalSet(IntegerSet set, ValueRange operands) {
    SmallVector<int64_t> values;
    for (Value operand : operands) {
      std::optional<int64_t> x = eval(operand);
      if (!x)
        return std::nullopt;
      values.push_back(*x);
    }
    for (unsigned i = 0, e = set.getNumConstraints(); i < e; ++i) {
      std::optional<int64_t> c =
          constantOf(set.getConstraint(i), set.getNumDims(), values);
      if (!c)
        return std::nullopt;
      if (set.isEq(i) ? *c != 0 : *c < 0)
        return false;
    }
    return true;
  }

private:
  std::optional<int64_t> evalCmp(arith::CmpIOp cmp) {
    std::optional<int64_t> a = eval(cmp.getLhs()), b = eval(cmp.getRhs());
    if (!a || !b)
      return std::nullopt;
    uint64_t ua = static_cast<uint64_t>(*a), ub = static_cast<uint64_t>(*b);
    switch (cmp.getPredicate()) {
    case arith::CmpIPredicate::eq: return *a == *b;
    case arith::CmpIPredicate::ne: return *a != *b;
    case arith::CmpIPredicate::slt: return *a < *b;
    case arith::CmpIPredicate::sle: return *a <= *b;
    case arith::CmpIPredicate::sgt: return *a > *b;
    case arith::CmpIPredicate::sge: return *a >= *b;
    case arith::CmpIPredicate::ult: return ua < ub;
    case arith::CmpIPredicate::ule: return ua <= ub;
    case arith::CmpIPredicate::ugt: return ua > ub;
    case arith::CmpIPredicate::uge: return ua >= ub;
    }
    return std::nullopt;
  }

  std::optional<int64_t> evalBinary(Operation *op) {
    std::optional<int64_t> a = eval(op->getOperand(0));
    std::optional<int64_t> b = eval(op->getOperand(1));
    if (!a || !b)
      return std::nullopt;
    if (isa<arith::AddIOp>(op)) return *a + *b;
    if (isa<arith::SubIOp>(op)) return *a - *b;
    if (isa<arith::MulIOp>(op)) return *a * *b;
    if (isa<arith::AndIOp>(op)) return *a & *b;
    if (isa<arith::OrIOp>(op)) return *a | *b;
    if (isa<arith::XOrIOp>(op)) return *a ^ *b;
    if (isa<arith::MinSIOp>(op)) return std::min(*a, *b);
    if (isa<arith::MaxSIOp>(op)) return std::max(*a, *b);
    if (*b == 0)
      return std::nullopt;
    if (isa<arith::DivSIOp>(op)) return *a / *b;
    if (isa<arith::RemSIOp>(op)) return *a % *b;
    if (*a < 0 || *b < 0)
      return std::nullopt;
    if (isa<arith::DivUIOp>(op)) return *a / *b;
    if (isa<arith::RemUIOp>(op)) return *a % *b;
    if (*b >= 63)
      return std::nullopt;
    if (isa<arith::ShLIOp>(op)) return *a << *b;
    if (isa<arith::ShRSIOp, arith::ShRUIOp>(op)) return *a >> *b;
    return std::nullopt;
  }

  std::optional<int64_t> evalMap(AffineMap map, ValueRange operands,
                                 unsigned result) {
    SmallVector<int64_t> values;
    for (Value operand : operands) {
      std::optional<int64_t> x = eval(operand);
      if (!x)
        return std::nullopt;
      values.push_back(*x);
    }
    return constantOf(map.getResult(result), map.getNumDims(), values);
  }

  std::optional<int64_t> evalYield(Region &region, unsigned index) {
    if (region.empty())
      return std::nullopt;
    Operation *term = region.front().getTerminator();
    if (!term || index >= term->getNumOperands())
      return std::nullopt;
    return eval(term->getOperand(index));
  }

  /// `expr` over dims then symbols, all bound to `values`.
  static std::optional<int64_t> constantOf(AffineExpr expr, unsigned numDims,
                                           ArrayRef<int64_t> values) {
    MLIRContext *ctx = expr.getContext();
    SmallVector<AffineExpr> dims, syms;
    for (unsigned i = 0; i < values.size(); ++i)
      (i < numDims ? dims : syms)
          .push_back(getAffineConstantExpr(values[i], ctx));
    AffineExpr folded =
        simplifyAffineExpr(expr.replaceDimsAndSymbols(dims, syms), 0, 0);
    if (auto c = dyn_cast<AffineConstantExpr>(folded))
      return c.getValue();
    return std::nullopt;
  }

  const Env &env;
};

/// Does `v` change from one iteration of `pipelined` to the next (its
/// index, a value read from memory, a value of a loop it does not unroll)?
/// The sub-loop indices are the copy's constants, never variant.
class VariantInPipeline {
public:
  VariantInPipeline(Operation *pipelined, const Env &env)
      : pipelined(pipelined), env(env) {}

  bool operator()(Value v) {
    if (env.count(v))
      return false;
    if (auto it = cache.find(v); it != cache.end())
      return it->second;
    cache[v] = true; // a cycle is variant
    bool variant = compute(v);
    cache[v] = variant;
    return variant;
  }

private:
  bool compute(Value v) {
    if (auto arg = dyn_cast<BlockArgument>(v)) {
      Operation *owner = arg.getOwner()->getParentOp();
      return pipelined == owner || pipelined->isProperAncestor(owner);
    }
    Operation *op = v.getDefiningOp();
    if (!pipelined->isProperAncestor(op))
      return false;
    if (op->getNumRegions() == 0) {
      if (!isMemoryEffectFree(op))
        return true; // a value read from memory
      return llvm::any_of(op->getOperands(),
                          [&](Value x) { return (*this)(x); });
    }
    bool variant = false;
    op->walk([&](Operation *inner) {
      if (inner != op && inner->getNumRegions() == 0 &&
          !isMemoryEffectFree(inner) && !inner->hasTrait<OpTrait::IsTerminator>()) {
        variant = true;
        return WalkResult::interrupt();
      }
      for (Value x : inner->getOperands())
        if (!op->isAncestor(x.getParentRegion()->getParentOp()) &&
            (*this)(x)) {
          variant = true;
          return WalkResult::interrupt();
        }
      return WalkResult::advance();
    });
    return variant;
  }

  Operation *pipelined;
  const Env &env;
  llvm::DenseMap<Value, bool> cache;
};

/// One guard between an access and the pipelined loop: the access runs in
/// its then arm (`thenArm`) or its else arm.
struct Guard {
  Operation *ifOp;
  bool thenArm;
};

/// Does the copy (`env`) run the guarded access in every iteration of the
/// pipelined loop? False when a guard is false for the copy or depends on
/// the pipelined loop's iteration (`if (c & 1)`: the address stays in the
/// loop); a guard invariant in the loop does not stop the hoist.
static bool runsEveryIteration(ArrayRef<Guard> guards, Operation *pipelined,
                               const Env &env) {
  Evaluator evaluator(env);
  VariantInPipeline variant(pipelined, env);
  for (const Guard &g : guards) {
    std::optional<bool> taken;
    bool isVariant = false;
    if (auto ifOp = dyn_cast<AffineIfOp>(g.ifOp)) {
      taken = evaluator.evalSet(ifOp.getIntegerSet(), ifOp.getOperands());
      if (!taken)
        isVariant = llvm::any_of(ifOp.getOperands(),
                                 [&](Value x) { return variant(x); });
    } else {
      auto scfIf = cast<scf::IfOp>(g.ifOp);
      if (std::optional<int64_t> c = evaluator.eval(scfIf.getCondition()))
        taken = *c != 0;
      else
        isVariant = variant(scfIf.getCondition());
    }
    if (taken && *taken != g.thenArm)
      return false;
    if (isVariant)
      return false;
  }
  return true;
}

/// Whether the subscript `expr` (over `operands`, dims first) uses the index
/// of one of `subLoops` that runs at least `minTrip` times.
static bool usesLongSubLoop(AffineExpr expr, unsigned numDims,
                            ArrayRef<Value> operands,
                            ArrayRef<AffineForOp> subLoops, uint64_t minTrip) {
  for (AffineForOp forOp : subLoops) {
    if (*getConstantTripCount(forOp) < minTrip)
      continue;
    for (auto [i, operand] : llvm::enumerate(operands)) {
      if (operand != forOp.getInductionVar())
        continue;
      bool used = i < numDims ? expr.isFunctionOfDim(i)
                              : expr.isFunctionOfSymbol(i - numDims);
      if (used)
        return true;
    }
  }
  return false;
}

} // namespace

llvm::SmallPtrSet<Operation *, 4>
circt::hls_analysis::doWhileParents(AffineForOp pipelined,
                                    uint64_t minSubLoopTrip,
                                    uint64_t maxCombinations) {
  llvm::SmallPtrSet<Operation *, 4> result;
  MLIRContext *ctx = pipelined.getContext();
  // The affine loops around the pipelined loop: the flatten candidates.
  SmallVector<AffineForOp> ancestors;
  for (Operation *op = pipelined->getParentOp();
       op && !isa<FunctionOpInterface>(op); op = op->getParentOp())
    if (auto forOp = dyn_cast<AffineForOp>(op))
      ancestors.push_back(forOp);
  if (ancestors.empty())
    return result;
  // A dim per ancestor index p, with p + step its next index. Behind
  // --affine-loop-normalize, p of a loop with a step or lower bound is
  // `affine.apply (d0 * step + lb)(normalized index)`: that value is p and
  // gets a dim of its own whose next index is p + step (w9r13rev_dv_s2k:
  // `i += 2`, rows i + 2k: refused like dv_p1).
  llvm::DenseMap<Value, unsigned> ancestorDim;
  SmallVector<AffineExpr> nextIndex; // p + step, per dim
  SmallVector<unsigned> ancestorOfDim;
  auto addDim = [&](Value index, unsigned ancestor, int64_t step) {
    unsigned d = nextIndex.size();
    ancestorDim[index] = d;
    ancestorOfDim.push_back(ancestor);
    nextIndex.push_back(getAffineDimExpr(d, ctx) + step);
  };
  for (auto [i, forOp] : llvm::enumerate(ancestors))
    addDim(forOp.getInductionVar(), i, forOp.getStepAsInt());
  for (auto [i, forOp] : llvm::enumerate(ancestors))
    for (Operation *user : forOp.getInductionVar().getUsers()) {
      auto apply = dyn_cast<AffineApplyOp>(user);
      if (!apply || apply.getMapOperands().size() != 1 ||
          apply.getAffineMap().getNumDims() != 1 ||
          ancestorDim.count(apply.getResult()))
        continue;
      AffineExpr e = apply.getAffineMap().getResult(0);
      // e = d0 * step + lb with constants step >= 1 and lb.
      AffineExpr d0 = getAffineDimExpr(0, ctx);
      auto valueAt = [&](int64_t x) {
        return dyn_cast<AffineConstantExpr>(simplifyAffineExpr(
            e.replace(d0, getAffineConstantExpr(x, ctx)), 1, 0));
      };
      AffineConstantExpr lbC = valueAt(0), at1C = valueAt(1);
      if (!lbC || !at1C)
        continue;
      int64_t step = at1C.getValue() - lbC.getValue();
      if (step < 1 || simplifyAffineExpr(e, 1, 0) !=
                          simplifyAffineExpr(d0 * step + lbC.getValue(), 1, 0))
        continue;
      addDim(apply.getResult(), i, step * forOp.getStepAsInt());
    }

  pipelined.getBody()->walk([&](Operation *op) {
    Value memref;
    AffineMap map;
    SmallVector<Value> operands;
    if (auto load = dyn_cast<AffineReadOpInterface>(op)) {
      memref = load.getMemRef();
      map = load.getAffineMap();
      operands = llvm::to_vector(load.getMapOperands());
    } else if (auto store = dyn_cast<AffineWriteOpInterface>(op)) {
      memref = store.getMemRef();
      map = store.getAffineMap();
      operands = llvm::to_vector(store.getMapOperands());
    } else {
      return;
    }
    auto type = dyn_cast<MemRefType>(memref.getType());
    if (!type || type.getRank() < 2)
      return; // a linearised subscript keeps the flatten (dv_lin)
    // The sub-loops the pipeline unrolls around the access, and its guards.
    SmallVector<AffineForOp> subLoops;
    SmallVector<Guard> guards;
    Operation *child = op;
    for (Operation *parent = op->getParentOp(); parent != pipelined;
         child = parent, parent = parent->getParentOp()) {
      if (auto forOp = dyn_cast<AffineForOp>(parent)) {
        if (!getConstantTripCount(forOp) || !forOp.hasConstantLowerBound())
          return; // not unrolled completely: no copy to look at
        subLoops.push_back(forOp);
      } else if (isa<AffineIfOp, scf::IfOp>(parent)) {
        bool thenArm =
            child->getParentRegion() == &parent->getRegion(0);
        guards.push_back({parent, thenArm});
      } else {
        return; // another region: not a straight-line copy
      }
    }
    if (subLoops.empty())
      return; // written out in the source (dv_expl): flattened
    uint64_t combinations = 1;
    for (AffineForOp forOp : subLoops) {
      combinations *= *getConstantTripCount(forOp);
      if (combinations > maxCombinations)
        return;
    }
    // Every copy of the access: the subscripts with the copy's sub-loop
    // indices substituted, the ancestors' indices as dims, any other
    // operand an opaque symbol.
    SmallVector<uint64_t> digits(subLoops.size(), 0);
    for (uint64_t n = 0; n < combinations; ++n) {
      Env env;
      for (auto [forOp, digit] : llvm::zip(subLoops, digits))
        env[forOp.getInductionVar()] =
            forOp.getConstantLowerBound() +
            static_cast<int64_t>(digit) * forOp.getStepAsInt();
      for (unsigned i = 0; i < digits.size(); ++i) {
        if (++digits[i] < *getConstantTripCount(subLoops[i]))
          break;
        digits[i] = 0;
      }
      if (!runsEveryIteration(guards, pipelined, env))
        continue;
      SmallVector<AffineExpr> dims, syms;
      unsigned opaque = 0;
      for (auto [i, operand] : llvm::enumerate(operands)) {
        AffineExpr e;
        if (auto it = env.find(operand); it != env.end())
          e = getAffineConstantExpr(it->second, ctx);
        else if (auto it = ancestorDim.find(operand); it != ancestorDim.end())
          e = getAffineDimExpr(it->second, ctx);
        else
          e = getAffineSymbolExpr(opaque++, ctx);
        (i < map.getNumDims() ? dims : syms).push_back(e);
      }
      for (AffineExpr r : map.getResults()) {
        AffineExpr s = simplifyAffineExpr(r.replaceDimsAndSymbols(dims, syms),
                                          nextIndex.size(), opaque);
        auto match = llvm::find(nextIndex, s);
        if (match == nextIndex.end() ||
            !usesLongSubLoop(r, map.getNumDims(), operands, subLoops,
                             minSubLoopTrip))
          continue;
        result.insert(
            ancestors[ancestorOfDim[match - nextIndex.begin()]].getOperation());
      }
    }
  });
  return result;
}
