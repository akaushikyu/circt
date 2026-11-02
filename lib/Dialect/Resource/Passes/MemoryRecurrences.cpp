//===- MemoryRecurrences.cpp - loop-carried memory recurrences ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// See MemoryRecurrences.h. Distances are found by evaluating every access's
// address over the first iterations of the loop: an index built from the
// induction variable, constants, values defined outside the loop (one fixed
// sample each; an enclosing loop's induction variable at its lower bound)
// and side-effect-free integer arithmetic is evaluated; an index that needs
// a loaded value, a call result or a loop-carried value is unknown.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/MemoryRecurrences.h"
#include "circt/Dialect/Resource/Config/Config.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "mlir/IR/IntegerSet.h"

#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/Hashing.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/ADT/TypeSwitch.h"

using namespace mlir;
using namespace mlir::affine;
using circt::hls_analysis::MemoryRecurrence;
using circt::hls_analysis::MemoryRecurrences;

namespace {

/// One load or store of the loop body, its address as a map over operands.
struct Access {
  Operation *op = nullptr;
  Value mem;
  bool isStore = false;
  Value value; ///< the stored value (store) or the loaded value (load)
  AffineMap map;
  SmallVector<Value, 4> operands;
  unsigned pos = 0;     ///< post-order position in the body
  bool known = true;    ///< every address can be evaluated
  SmallVector<uint64_t> addr; ///< address hash per evaluated iteration
  /// The access happens only where this set holds over predOperands (the
  /// enable of a bank's store; a run-time-bank load takes the enable of
  /// the store of its bank and address): elsewhere its address is a
  /// per-iteration sentinel no address of another iteration equals.
  IntegerSet pred;
  bool hasPred = false;
  SmallVector<Value, 4> predOperands;
};

/// The loop's induction variable, its iteration values and its body.
struct LoopShape {
  Operation *loop = nullptr;
  Value iv;
  int64_t lb = 0, step = 1;
  std::optional<int64_t> trip;
  Block *body = nullptr;
};

constexpr unsigned kMaxEvalDepth = 24;
/// Distances beyond this are not searched: a chain longer than this many
/// cycles would be needed for them to bound the II.
constexpr int64_t kMaxDistance = 256;
/// A value defined outside the loop that is not an enclosing loop's
/// induction variable is sampled at a large distinct value, so that a
/// symbolic stride (a[i * n + j]) does not fold addresses together.
constexpr int64_t kOutsideSampleBase = 1000003;
constexpr int64_t kOutsideSampleStride = 7919;

class AddressEvaluator {
public:
  explicit AddressEvaluator(const LoopShape &shape) : shape(shape) {}

  std::optional<int64_t> value(Value v, int64_t ivValue, unsigned depth = 0) {
    if (v == shape.iv)
      return ivValue;
    if (std::optional<int64_t> c = getConstantIntValue(v))
      return c;
    if (depth > kMaxEvalDepth)
      return std::nullopt;
    if (!isInsideLoop(v))
      return outsideSample(v);
    Operation *def = v.getDefiningOp();
    if (!def)
      return std::nullopt; // an iter_arg or a nested region's argument
    if (auto apply = dyn_cast<AffineApplyOp>(def)) {
      SmallVector<int64_t, 4> vals;
      for (Value o : apply.getMapOperands()) {
        std::optional<int64_t> x = value(o, ivValue, depth + 1);
        if (!x)
          return std::nullopt;
        vals.push_back(*x);
      }
      return expr(apply.getAffineMap().getResult(0), vals,
                  apply.getAffineMap().getNumDims());
    }
    auto unary = [&]() -> std::optional<int64_t> {
      return value(def->getOperand(0), ivValue, depth + 1);
    };
    auto binary =
        [&](llvm::function_ref<std::optional<int64_t>(int64_t, int64_t)> f)
        -> std::optional<int64_t> {
      std::optional<int64_t> a = value(def->getOperand(0), ivValue, depth + 1);
      if (!a)
        return std::nullopt;
      std::optional<int64_t> b = value(def->getOperand(1), ivValue, depth + 1);
      if (!b)
        return std::nullopt;
      return f(*a, *b);
    };
    return TypeSwitch<Operation *, std::optional<int64_t>>(def)
        .Case<arith::IndexCastOp, arith::IndexCastUIOp, arith::ExtSIOp,
              arith::ExtUIOp, arith::TruncIOp>([&](auto) { return unary(); })
        .Case<arith::AddIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            return a + b;
          });
        })
        .Case<arith::SubIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            return a - b;
          });
        })
        .Case<arith::MulIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            return a * b;
          });
        })
        .Case<arith::AndIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            return a & b;
          });
        })
        .Case<arith::OrIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            return a | b;
          });
        })
        .Case<arith::XOrIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            return a ^ b;
          });
        })
        .Case<arith::ShLIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            if (b < 0 || b > 62)
              return std::nullopt;
            return a << b;
          });
        })
        .Case<arith::ShRSIOp, arith::ShRUIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            if (b < 0 || b > 62)
              return std::nullopt;
            return a >> b;
          });
        })
        .Case<arith::DivSIOp, arith::DivUIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            if (b == 0)
              return std::nullopt;
            return a / b;
          });
        })
        .Case<arith::RemSIOp, arith::RemUIOp>([&](auto) {
          return binary([](int64_t a, int64_t b) -> std::optional<int64_t> {
            if (b == 0)
              return std::nullopt;
            return a % b;
          });
        })
        .Default([](Operation *) { return std::nullopt; });
  }

  /// An affine expression over dimension and symbol values.
  static std::optional<int64_t> expr(AffineExpr e, ArrayRef<int64_t> vals,
                                     unsigned numDims) {
    if (auto c = dyn_cast<AffineConstantExpr>(e))
      return c.getValue();
    if (auto d = dyn_cast<AffineDimExpr>(e))
      return vals[d.getPosition()];
    if (auto s = dyn_cast<AffineSymbolExpr>(e))
      return vals[numDims + s.getPosition()];
    auto bin = cast<AffineBinaryOpExpr>(e);
    std::optional<int64_t> a = expr(bin.getLHS(), vals, numDims);
    std::optional<int64_t> b = expr(bin.getRHS(), vals, numDims);
    if (!a || !b)
      return std::nullopt;
    switch (e.getKind()) {
    case AffineExprKind::Add:
      return *a + *b;
    case AffineExprKind::Mul:
      return *a * *b;
    case AffineExprKind::Mod:
      if (*b <= 0)
        return std::nullopt;
      return ((*a % *b) + *b) % *b;
    case AffineExprKind::FloorDiv:
      if (*b == 0)
        return std::nullopt;
      return *a / *b - ((*a % *b != 0) && ((*a < 0) != (*b < 0)));
    case AffineExprKind::CeilDiv:
      if (*b == 0)
        return std::nullopt;
      return *a / *b + ((*a % *b != 0) && ((*a < 0) == (*b < 0)));
    default:
      return std::nullopt;
    }
  }

private:
  bool isInsideLoop(Value v) const {
    Region *r = v.getParentRegion();
    return r && shape.loop->isAncestor(r->getParentOp());
  }

  /// An enclosing loop's induction variable: its lower bound plus
  /// `steps` steps (scheduling.dependences.enclosing_iv_sample_steps),
  /// clamped to its last iteration when the trip count is constant. At the
  /// lower bound a nest whose inner bounds are that counter (`for (iter = 1;
  /// ..)` around `for (i < iter) for (j < iter) for (k < iter)`,
  /// GP_selection) is one iteration long and a recurrence of the flattened
  /// loop is missed (OPEN_ISSUES O170 (b), kernel w9r16fx_gp_ffo).
  static int64_t enclosingSample(int64_t lb, int64_t step,
                                 std::optional<uint64_t> trip) {
    int64_t k =
        circt::hlsest::Config::get().scheduling.enclosingIvSampleSteps;
    if (trip)
      k = std::min<int64_t>(k, *trip > 0 ? static_cast<int64_t>(*trip) - 1
                                         : 0);
    return lb + k * step;
  }

  int64_t outsideSample(Value v) {
    if (auto arg = dyn_cast<BlockArgument>(v)) {
      if (auto outer = dyn_cast<AffineForOp>(arg.getOwner()->getParentOp()))
        if (arg == outer.getInductionVar() && outer.hasConstantLowerBound())
          return enclosingSample(outer.getConstantLowerBound(),
                                 outer.getStepAsInt(),
                                 getConstantTripCount(outer));
      if (auto outer = dyn_cast<scf::ForOp>(arg.getOwner()->getParentOp()))
        if (arg == outer.getInductionVar())
          if (std::optional<int64_t> lb =
                  getConstantIntValue(outer.getLowerBound())) {
            std::optional<int64_t> st = getConstantIntValue(outer.getStep());
            std::optional<int64_t> ub =
                getConstantIntValue(outer.getUpperBound());
            std::optional<uint64_t> trip;
            if (st && *st > 0 && ub)
              trip = *ub > *lb
                         ? static_cast<uint64_t>((*ub - *lb + *st - 1) / *st)
                         : 0;
            return enclosingSample(*lb, st && *st > 0 ? *st : 1, trip);
          }
    }
    auto [it, inserted] = samples.try_emplace(
        v, kOutsideSampleBase +
               kOutsideSampleStride * static_cast<int64_t>(samples.size()));
    return it->second;
  }

  const LoopShape &shape;
  DenseMap<Value, int64_t> samples;
};

std::optional<LoopShape> shapeOf(Operation *loop) {
  LoopShape s;
  s.loop = loop;
  if (auto f = dyn_cast<AffineForOp>(loop)) {
    s.iv = f.getInductionVar();
    s.lb = f.hasConstantLowerBound() ? f.getConstantLowerBound() : 0;
    s.step = f.getStepAsInt();
    if (std::optional<uint64_t> t = getConstantTripCount(f))
      s.trip = static_cast<int64_t>(*t);
    s.body = f.getBody();
    return s;
  }
  if (auto f = dyn_cast<scf::ForOp>(loop)) {
    s.iv = f.getInductionVar();
    std::optional<int64_t> lb = getConstantIntValue(f.getLowerBound());
    std::optional<int64_t> ub = getConstantIntValue(f.getUpperBound());
    std::optional<int64_t> st = getConstantIntValue(f.getStep());
    s.lb = lb.value_or(0);
    s.step = st.value_or(1);
    if (lb && ub && st && *st > 0)
      s.trip = std::max<int64_t>(0, (*ub - *lb + *st - 1) / *st);
    s.body = f.getBody();
    return s;
  }
  return std::nullopt;
}

std::optional<Access> accessOf(Operation *op) {
  Access a;
  a.op = op;
  auto identity = [&](ValueRange indices) {
    a.map = AffineMap::getMultiDimIdentityMap(indices.size(), op->getContext());
    a.operands.assign(indices.begin(), indices.end());
  };
  auto composed = [&](AffineMap map, ValueRange operands) {
    a.map = map;
    a.operands.assign(operands.begin(), operands.end());
    fullyComposeAffineMapAndOperands(&a.map, &a.operands);
  };
  if (auto l = dyn_cast<AffineLoadOp>(op)) {
    a.mem = l.getMemRef();
    a.value = l.getResult();
    composed(l.getAffineMap(), l.getMapOperands());
  } else if (auto s = dyn_cast<AffineStoreOp>(op)) {
    a.mem = s.getMemRef();
    a.isStore = true;
    a.value = s.getValueToStore();
    composed(s.getAffineMap(), s.getMapOperands());
  } else if (auto l = dyn_cast<memref::LoadOp>(op)) {
    a.mem = l.getMemRef();
    a.value = l.getResult();
    identity(l.getIndices());
  } else if (auto s = dyn_cast<memref::StoreOp>(op)) {
    a.mem = s.getMemRef();
    a.isStore = true;
    a.value = s.getValueToStore();
    identity(s.getIndices());
  } else if (auto s = dyn_cast<circt::hls_analysis::AffineStoreEnableOp>(op);
             s && circt::hlsest::Config::get()
                      .scheduling.bankStoreRecurrences) {
    // The store of one bank of a partitioned array whose bank is chosen at
    // run time (--memory-banking-bram), enabled where its bank is the one
    // chosen: the array's store before banking, so the array's loop-carried
    // recurrence stays visible (OPEN_ISSUES O170 (a): polybench_pragmas
    // k2mm `tmp1[i][j] +=` with tmp1 cyclic 4 on j; Vitis II 8).
    a.mem = s.getMemref();
    a.isStore = true;
    a.value = s.getValue();
    composed(s.getMap(), s.getMapOperands());
    a.pred = s.getCondition();
    a.hasPred = true;
    a.predOperands.assign(s.getSetOperands().begin(),
                          s.getSetOperands().end());
  } else {
    return std::nullopt;
  }
  return a;
}

/// The same map over the same operand values: the same address in every
/// iteration, whether or not it can be evaluated.
bool identicalAddress(const Access &x, const Access &y) {
  if (x.hasPred || y.hasPred)
    return false; // the same address, but maybe not in the same iterations
  return x.map == y.map && x.operands == y.operands;
}

/// Evaluate `a`'s address for iterations [0, count).
void evaluate(Access &a, const LoopShape &shape, AddressEvaluator &eval,
              unsigned count) {
  a.addr.reserve(count);
  SmallVector<int64_t, 4> vals(a.operands.size());
  SmallVector<int64_t, 4> coords;
  for (unsigned k = 0; k < count; ++k) {
    int64_t ivValue = shape.lb + static_cast<int64_t>(k) * shape.step;
    for (auto [i, v] : llvm::enumerate(a.operands)) {
      std::optional<int64_t> x = eval.value(v, ivValue);
      if (!x) {
        a.known = false;
        a.addr.clear();
        return;
      }
      vals[i] = *x;
    }
    coords.clear();
    for (AffineExpr e : a.map.getResults()) {
      std::optional<int64_t> x =
          AddressEvaluator::expr(e, vals, a.map.getNumDims());
      if (!x) {
        a.known = false;
        a.addr.clear();
        return;
      }
      coords.push_back(*x);
    }
    if (a.hasPred) {
      SmallVector<int64_t, 4> pv;
      for (Value v : a.predOperands) {
        std::optional<int64_t> x = eval.value(v, ivValue);
        if (!x) {
          a.known = false;
          a.addr.clear();
          return;
        }
        pv.push_back(*x);
      }
      bool holds = true;
      for (unsigned c = 0; c < a.pred.getNumConstraints() && holds; ++c) {
        std::optional<int64_t> x = AddressEvaluator::expr(
            a.pred.getConstraint(c), pv, a.pred.getNumDims());
        if (!x) {
          a.known = false;
          a.addr.clear();
          return;
        }
        holds = a.pred.isEq(c) ? *x == 0 : *x >= 0;
      }
      if (!holds) {
        // Disabled in this iteration: a sentinel of the iteration (equal
        // for two accesses disabled in the same iteration, so an element
        // they both touch whenever enabled stays "the same address").
        a.addr.push_back(llvm::hash_combine(0x5e471e1, k));
        continue;
      }
    }
    a.addr.push_back(llvm::hash_combine_range(coords.begin(), coords.end()));
  }
}

/// A key for "the same address in every evaluated iteration": the evaluated
/// addresses, or the map and operands when they cannot be evaluated.
uint64_t addressSignature(const Access &a) {
  if (a.known && !a.addr.empty())
    return llvm::hash_combine(
        1, llvm::hash_combine_range(a.addr.begin(), a.addr.end()));
  return llvm::hash_combine(
      2, a.map.getAsOpaquePointer(),
      llvm::hash_combine_range(a.operands.begin(), a.operands.end()));
}

/// The same address in one iteration: identical, or equal over the
/// evaluated iterations.
bool sameAddressInIteration(const Access &x, const Access &y) {
  if (identicalAddress(x, y))
    return true;
  if (!x.known || !y.known || x.addr.empty() || y.addr.empty())
    return false;
  return x.addr == y.addr;
}

/// The load reads, in every evaluated iteration but the first, the address
/// the store wrote in the iteration before.
bool alwaysPreviousIteration(const Access &store, const Access &load) {
  size_t n = std::min(store.addr.size() + 1, load.addr.size());
  if (n < 2)
    return false;
  for (size_t k = 1; k < n; ++k)
    if (load.addr[k] != store.addr[k - 1])
      return false;
  return true;
}

/// The iterations in which a load reads each address.
using AddressIndex = DenseMap<uint64_t, SmallVector<unsigned, 2>>;

AddressIndex indexAddresses(const Access &load) {
  AddressIndex index;
  for (auto [k, h] : llvm::enumerate(load.addr))
    index[h].push_back(static_cast<unsigned>(k));
  return index;
}

/// The smallest d in [1, maxD] such that the store writes in some iteration
/// k < window the address the load reads in iteration k + d.
std::optional<int64_t> carriedDistance(const Access &store,
                                       const AddressIndex &loadIndex,
                                       int64_t maxD, unsigned window) {
  std::optional<int64_t> best;
  for (size_t k = 0; k < window && k < store.addr.size(); ++k) {
    auto it = loadIndex.find(store.addr[k]);
    if (it == loadIndex.end())
      continue;
    for (unsigned kl : it->second) {
      if (kl <= k)
        continue;
      int64_t d = static_cast<int64_t>(kl - k);
      if (d <= maxD && (!best || d < *best))
        best = d;
      break; // the list is ascending: later iterations are farther
    }
    if (best && *best == 1)
      break;
  }
  return best;
}

/// For each value of the body, the loads of one memory it depends on and
/// the longest recurrence latency from each: the SSA operands, the arms of
/// an if, and a load forwarded from an earlier store of the same address in
/// the same iteration (the stored value's sources). Computed backwards from
/// the stores, memoised, without recursion (a long unrolled chain is deep).
class ChainSources {
public:
  using Sources = SmallVector<std::pair<unsigned, int64_t>, 2>; // load, lat

  ChainSources(Operation *loop, ArrayRef<Access> accesses,
               const DenseMap<Operation *, unsigned> &loadIndexOf,
               const DenseMap<unsigned, unsigned> &forwardedFrom,
               llvm::function_ref<int64_t(Operation *)> latency)
      : loop(loop), accesses(accesses), loadIndexOf(loadIndexOf),
        forwardedFrom(forwardedFrom), latency(latency) {}

  const Sources &of(Value root) {
    if (auto it = memo.find(root); it != memo.end())
      return it->second;
    // Iterative post-order DFS over the value graph.
    SmallVector<std::pair<Value, bool>> stack{{root, false}};
    while (!stack.empty()) {
      auto [v, expanded] = stack.pop_back_val();
      if (memo.count(v))
        continue;
      SmallVector<Value, 4> preds;
      predecessors(v, preds);
      if (!expanded) {
        stack.push_back({v, true});
        for (Value p : preds)
          if (!memo.count(p))
            stack.push_back({p, false});
        continue;
      }
      Sources out;
      int64_t lat = 0;
      Operation *def = v.getDefiningOp();
      if (def && def->getNumRegions() == 0)
        lat = std::max<int64_t>(0, latency(def));
      if (def) {
        if (auto it = loadIndexOf.find(def); it != loadIndexOf.end())
          merge(out, {{it->second, 0}}, 0);
      }
      for (Value p : preds)
        merge(out, memo[p], isForwardedStoreValue(v, p) ? 0 : lat);
      memo[v] = std::move(out);
    }
    return memo[root];
  }

private:
  bool inside(Value v) const {
    Region *r = v.getParentRegion();
    return r && loop->isAncestor(r->getParentOp());
  }

  /// A load's predecessor is the value of the store it is forwarded from.
  bool isForwardedStoreValue(Value v, Value p) const {
    Operation *def = v.getDefiningOp();
    if (!def)
      return false;
    auto it = loadIndexOf.find(def);
    if (it == loadIndexOf.end())
      return false;
    auto f = forwardedFrom.find(it->second);
    return f != forwardedFrom.end() && accesses[f->second].value == p;
  }

  void predecessors(Value v, SmallVectorImpl<Value> &out) const {
    Operation *def = v.getDefiningOp();
    if (!def || !inside(v))
      return;
    if (auto it = loadIndexOf.find(def); it != loadIndexOf.end()) {
      // A load: its own value, or the forwarded store's value.
      auto f = forwardedFrom.find(it->second);
      if (f != forwardedFrom.end())
        out.push_back(accesses[f->second].value);
      return;
    }
    if (def->getNumRegions() != 0) {
      // An if's result: the values its arms yield, and its condition.
      unsigned idx = cast<OpResult>(v).getResultNumber();
      for (Region &r : def->getRegions())
        for (Block &b : r)
          if (!b.empty())
            if (Operation *term = &b.back())
              if (idx < term->getNumOperands())
                out.push_back(term->getOperand(idx));
      for (Value o : def->getOperands())
        out.push_back(o);
      return;
    }
    for (Value o : def->getOperands())
      if (!isa<MemRefType>(o.getType()))
        out.push_back(o);
  }

  static void merge(Sources &into, const Sources &from, int64_t add) {
    for (auto [load, lat] : from) {
      auto it = llvm::find_if(into, [&](auto &e) { return e.first == load; });
      if (it == into.end())
        into.push_back({load, lat + add});
      else
        it->second = std::max(it->second, lat + add);
    }
  }

  Operation *loop;
  ArrayRef<Access> accesses;
  const DenseMap<Operation *, unsigned> &loadIndexOf;
  const DenseMap<unsigned, unsigned> &forwardedFrom;
  llvm::function_ref<int64_t(Operation *)> latency;
  DenseMap<Value, Sources> memo;
};

} // namespace

/// A store made under an if of the body (`if (j == 0) acc[i] = b0`) that a
/// later store of the same address at the body's top level overwrites in the
/// same iteration, with only loads of that address in between, uses no port
/// (the loads take the guarded value through a select), but only for a local
/// array that no operation outside the loop accesses. Vitis (kernels
/// w9r11i_gd_*, VITIS_NOTES N90): stream_hls MultiHeadSelfAttention1 opt2
/// node2 and gd_d / gd_f (the array is read only inside the loop): II 1, one
/// read and one write port; gd_a / gd_e (a later loop reads the array): the
/// guarded store stays, II 2.
static void eliminateGuardedStores(Operation *loop, Block *body,
                                   ArrayRef<Access> accesses,
                                   ArrayRef<unsigned> idx,
                                   MemoryRecurrences &result) {
  Value mem = accesses[idx.front()].mem;
  if (!isa_and_present<memref::AllocaOp, memref::AllocOp>(mem.getDefiningOp()))
    return;
  // Every other use is an access of this loop's body: a call or a view may
  // read it, and so may an access after the loop.
  for (Operation *user : mem.getUsers())
    if (!user->hasTrait<OpTrait::IsTerminator>() &&
        !isa<memref::DeallocOp>(user) &&
        (!loop->isAncestor(user) || !accessOf(user)))
      return;
  // The accesses of the memory in program order; for each guarded store,
  // the next access that is not a load of the same address must be a store
  // of that address at the body's top level.
  SmallVector<unsigned> ordered(idx.begin(), idx.end());
  llvm::sort(ordered, [&](unsigned x, unsigned y) {
    return accesses[x].pos < accesses[y].pos;
  });
  for (size_t n = 0; n < ordered.size(); ++n) {
    const Access &guarded = accesses[ordered[n]];
    if (!guarded.isStore || guarded.op->getBlock() == body ||
        result.promoted.contains(guarded.op))
      continue;
    for (size_t m = n + 1; m < ordered.size(); ++m) {
      const Access &next = accesses[ordered[m]];
      if (!sameAddressInIteration(next, guarded))
        break; // another address in between may alias it
      if (!next.isStore)
        continue; // a load of the address: served by the guarded value
      if (next.op->getBlock() == body) {
        result.promoted.insert(guarded.op);
        result.rule[guarded.op] = "N90a";
        ++result.standsFor[next.op];
      }
      break;
    }
  }
}

/// A load under an if of the body that reads the address a store at the
/// body's top level wrote earlier in the same iteration, with only loads of
/// that address in between, takes the stored value (GVN store-to-load
/// forwarding: the store dominates it) and uses no port; the store stands
/// for it. Loads in the same block are already forwarded by the access
/// clean-up of --convert-affine-to-loopschedule. Vitis: class_ece8893
/// barry_walker lab2 `output_matrix_local` (RMW of [j][k] in the pipelined
/// j loop, `if (i == N-1)` reads [j][h] after it): 1 BRAM per bank, one read
/// and one write port.
static void forwardToGuardedLoads(Block *body, ArrayRef<Access> accesses,
                                  ArrayRef<unsigned> idx,
                                  MemoryRecurrences &result) {
  SmallVector<unsigned> ordered(idx.begin(), idx.end());
  llvm::sort(ordered, [&](unsigned x, unsigned y) {
    return accesses[x].pos < accesses[y].pos;
  });
  for (size_t n = 0; n < ordered.size(); ++n) {
    const Access &store = accesses[ordered[n]];
    if (!store.isStore || store.op->getBlock() != body ||
        result.promoted.contains(store.op))
      continue;
    for (size_t m = n + 1; m < ordered.size(); ++m) {
      const Access &next = accesses[ordered[m]];
      if (next.isStore || !sameAddressInIteration(next, store))
        break;
      if (next.op->getBlock() != body && result.promoted.insert(next.op)) {
        result.rule[next.op] = "N90b";
        ++result.standsFor[store.op];
      }
    }
  }
}

/// The name the user gives a memory in a pragma's `variable=`: the alloca's
/// source name, the array a bank belongs to, the global a promoted alloca or
/// a get_global comes from. None for an unnamed memory (a callee parameter
/// after inlining).
static std::optional<StringRef> userNameOf(Value mem) {
  while (Operation *def = mem.getDefiningOp()) {
    if (auto cast = dyn_cast<memref::CastOp>(def)) {
      mem = cast.getSource();
      continue;
    }
    if (auto v = def->getAttrOfType<StringAttr>("polygeist.varname"))
      return v.getValue();
    if (auto b = def->getAttrOfType<StringAttr>("hls.bank_of"))
      return b.getValue();
    if (auto g = def->getAttrOfType<StringAttr>("hls.from_global"))
      return g.getValue();
    if (auto g = dyn_cast<memref::GetGlobalOp>(def))
      return g.getName();
    return std::nullopt;
  }
  return std::nullopt;
}

/// The variables a `#pragma HLS dependence variable=<v> inter false` (with no
/// direction, or RAW) declares free of loop-carried read-after-write
/// dependences, on `loop` or a loop around it: Vitis then schedules a
/// read-modify-write of <v> as if the next iteration never read what this
/// one wrote (VITIS_NOTES N122: kernel w9r15rev_rmw_dep, h[in[i]]++ at II 1
/// with the pragma, II 2 without it (N117)). A pragma on an enclosing loop
/// is assumed to cover the pipelined loop inside it (unconfirmed).
static llvm::StringSet<> userInterIndependent(Operation *loop) {
  llvm::StringSet<> names;
  for (Operation *op = loop; op && !isa<func::FuncOp>(op);
       op = op->getParentOp()) {
    auto arr = op->getAttrOfType<ArrayAttr>("hls.dependence");
    if (!arr)
      continue;
    for (Attribute a : arr) {
      auto d = dyn_cast<DictionaryAttr>(a);
      if (!d)
        continue;
      auto type = d.getAs<StringAttr>("type");
      auto dependent = d.getAs<BoolAttr>("dependent");
      auto variable = d.getAs<StringAttr>("variable");
      auto direction = d.getAs<StringAttr>("direction");
      if (!type || type.getValue() != "inter" || !dependent ||
          dependent.getValue() || !variable)
        continue;
      if (direction && !direction.getValue().equals_insensitive("RAW"))
        continue;
      names.insert(variable.getValue());
    }
  }
  return names;
}

MemoryRecurrences circt::hls_analysis::findMemoryRecurrences(
    Operation *loop, llvm::function_ref<int64_t(Operation *)> recurrenceLatency,
    const MemoryRecurrenceOptions &options, unsigned window) {
  std::optional<LoopShape> shape = shapeOf(loop);
  if (!shape || shape->step <= 0)
    return {};

  // The accesses of the body in post-order (program order for siblings).
  SmallVector<Access> accesses;
  unsigned pos = 0;
  for (Operation &top : *shape->body)
    top.walk<WalkOrder::PostOrder>([&](Operation *op) {
      if (std::optional<Access> a = accessOf(op)) {
        a->pos = pos;
        accesses.push_back(std::move(*a));
      }
      ++pos;
    });

  // A run-time-bank load takes the enable of its bank's store of the same
  // address (the bank select of the array's read before banking).
  for (Access &l : accesses) {
    if (l.isStore || !l.op->hasAttr("hls.runtime_bank"))
      continue;
    for (const Access &st : accesses)
      if (st.isStore && st.hasPred && st.mem == l.mem && st.map == l.map &&
          st.operands == l.operands) {
        l.pred = st.pred;
        l.hasPred = true;
        l.predOperands = st.predOperands;
        break;
      }
  }

  // Memories both read and written in the body.
  llvm::MapVector<Value, SmallVector<unsigned>> byMem;
  for (auto [i, a] : llvm::enumerate(accesses))
    byMem[a.mem].push_back(i);
  SmallVector<unsigned> candidates;
  for (auto &[mem, idx] : byMem) {
    bool loads = false, stores = false;
    for (unsigned i : idx)
      (accesses[i].isStore ? stores : loads) = true;
    if (loads && stores)
      candidates.append(idx.begin(), idx.end());
  }
  if (candidates.empty())
    return {};
  llvm::StringSet<> independent = userInterIndependent(loop);

  MemoryRecurrences result;
  AddressEvaluator eval(*shape);
  int64_t evalCount = window + kMaxDistance + 1;
  if (shape->trip)
    evalCount = std::min<int64_t>(evalCount, *shape->trip);
  for (unsigned i : candidates)
    evaluate(accesses[i], *shape, eval, static_cast<unsigned>(evalCount));

  for (auto &[mem, idx] : byMem) {
    SmallVector<unsigned> loads, stores;
    for (unsigned i : idx)
      (accesses[i].isStore ? stores : loads).push_back(i);
    if (loads.empty() || stores.empty())
      continue;

    // Store -> later load of the same address in one iteration: the load
    // reads the value the latest such store wrote.
    DenseMap<uint64_t, SmallVector<unsigned>> storesBySig;
    for (unsigned s : stores)
      storesBySig[addressSignature(accesses[s])].push_back(s);
    DenseMap<Operation *, unsigned> loadIndexOf;
    DenseMap<unsigned, unsigned> forwardedFrom;
    for (unsigned l : loads) {
      loadIndexOf[accesses[l].op] = l;
      auto it = storesBySig.find(addressSignature(accesses[l]));
      if (it == storesBySig.end())
        continue;
      std::optional<unsigned> latest;
      for (unsigned s : it->second)
        if (accesses[s].pos < accesses[l].pos &&
            sameAddressInIteration(accesses[s], accesses[l]) &&
            (!latest || accesses[s].pos > accesses[*latest].pos))
          latest = s;
      if (latest)
        forwardedFrom[l] = *latest;
    }

    // R1: Vitis keeps the element in a register for the whole inner loop:
    // one load in the first iteration, one store in the last; every other
    // access of the element (an init store under `j == 0`, a forwarded
    // re-load) uses no port. Only when every access of the memory in the
    // body names that element (another address could alias it in another
    // iteration).
    bool oneElement = llvm::all_of(idx, [&](unsigned i) {
      return sameAddressInIteration(accesses[i], accesses[idx.front()]);
    });
    bool promotedElement = false;
    auto promoteElement = [&]() {
      if (!oneElement || promotedElement)
        return;
      promotedElement = true;
      const Access *firstLoad = nullptr, *lastStore = nullptr;
      for (unsigned i : idx) {
        const Access &a = accesses[i];
        if (!a.isStore && (!firstLoad || a.pos < firstLoad->pos))
          firstLoad = &a;
        if (a.isStore && (!lastStore || a.pos > lastStore->pos))
          lastStore = &a;
      }
      for (unsigned i : idx)
        if (&accesses[i] != firstLoad && &accesses[i] != lastStore &&
            result.promoted.insert(accesses[i].op)) {
          result.rule[accesses[i].op] = "R1";
          ++result.standsFor[firstLoad->op];
        }
    };

    if (options.guardedStoreElimination)
      eliminateGuardedStores(loop, shape->body, accesses, idx, result);
    if (options.forwardToGuardedLoads)
      forwardToGuardedLoads(shape->body, accesses, idx, result);
    if (!options.recurrences)
      continue;
    std::optional<StringRef> memName = userNameOf(mem);
    bool userIndependent = options.userInterIndependence && memName &&
                           independent.contains(*memName);

    ChainSources chains(loop, accesses, loadIndexOf, forwardedFrom,
                        recurrenceLatency);
    DenseMap<unsigned, AddressIndex> loadIndexes;
    // N154: whether an access of the memref is a lane chosen at run time.
    const bool dynamicLane =
        options.dynamicLaneRmw && llvm::any_of(idx, [&](unsigned i) {
          return accesses[i].op->hasAttr("hls.dynamic_lane");
        });
    for (unsigned si : stores) {
      const Access &store = accesses[si];
      for (auto [li, chain] : chains.of(store.value)) {
        const Access &load = accesses[li];
        MemoryRecurrence rec;
        rec.chain = chain;
        rec.load = load.op;
        rec.store = store.op;
        if (!store.known || !load.known) {
          // One address value the body computes (h[v]++): the next
          // iteration may read what this one writes. Vitis forwards a
          // chain of at least two cycles through a reuse register (R4);
          // a shorter one still waits for the write, II 2 (VITIS_NOTES
          // N117, kernel w9r15p_hs_rmw).
          bool floor = options.unknownAddressMinII > 0;
          if ((chain <= 0 && !floor) || !identicalAddress(store, load))
            continue; // unknown distance between different index values
          rec.distance = 1;
          rec.rule = "R4";
          if (floor && chain < options.unknownAddressMinII) {
            rec.rule = "N117";
            chain = options.unknownAddressMinII;
            rec.chain = chain;
          }
        } else {
          // Only d < 2 + chain can bound the II above 1; d = 1 also decides
          // the register promotion of R1 / R3.
          int64_t maxD = std::clamp<int64_t>(chain + 1, 1, kMaxDistance);
          auto [it, fresh] = loadIndexes.try_emplace(li);
          if (fresh)
            it->second = indexAddresses(load);
          std::optional<int64_t> d =
              carriedDistance(store, it->second, maxD, window);
          if (!d)
            continue;
          rec.distance = *d;
          // R3 forwards the previous iteration's value only when the load
          // always reads what the store wrote one iteration earlier
          // (a[i] / a[i-1]); a distance of 1 in some iterations only
          // (b[i] / b[j] of a flattened nest) is a recurrence through the
          // memory, R2 with d = 1.
          rec.rule = *d >= 2                               ? "R2"
                     : sameAddressInIteration(store, load) ? "R1"
                     : alwaysPreviousIteration(store, load) ? "R3"
                                                             : "R2";
          // N154: a read-modify-write of a lane chosen at run time in an
          // aggregated word (hls.dynamic_lane, SplitStructMemrefs) is no
          // promoted element: Vitis addresses the lane, not the word, and
          // keeps the word in memory; the load waits for the previous
          // iteration's store, and the lane insert takes one more state
          // (kernel w9r21p_e1_vecrmw: II 3, one port).
          // Only at a word address the loop keeps (C[i][j] += x in the j
          // loop): a lane write that walks the words (p[i >> 3][i & 7] = v,
          // lit struct_through_calls, Vitis RAM_2P) stays R1.
          auto invariant = [](const Access &a) {
            return a.known && !a.addr.empty() && llvm::all_equal(a.addr);
          };
          if (dynamicLane && rec.rule == "R1" && invariant(store) &&
              invariant(load))
            rec.rule = "N154";
        }
        if (rec.rule == "R1")
          promoteElement();
        else if (rec.rule == "R3" && result.promoted.insert(load.op)) {
          result.rule[load.op] = "R3";
          ++result.standsFor[store.op];
        }
        if (userIndependent)
          continue; // the user's dependence pragma: no carried RAW bound
        bool throughRegister = rec.rule != "R2" && rec.rule != "N154";
        int64_t ii = throughRegister
                         ? chain
                         : (2 + chain + rec.distance - 1) / rec.distance;
        if (rec.rule == "N154") {
          ii += 1; // the lane insert
          result.laneRecurrences.push_back({store.op, load.op});
        }
        rec.ii = static_cast<unsigned>(std::max<int64_t>(1, ii));
        if (rec.ii > 1 && (!result.bound || rec.ii > result.bound->ii))
          result.bound = rec;
      }
    }
  }
  return result;
}
