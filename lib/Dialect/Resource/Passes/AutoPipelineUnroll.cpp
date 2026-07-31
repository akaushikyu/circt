//===- AutoPipelineUnroll.cpp - Vitis automatic pipeline/unroll/flatten ---===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Reproduces the automatic pipeline / unroll / flatten decision of Vitis HLS
// (`config_compile -pipeline_loops`, default 64). Evidence: VITIS_NOTES.md
// N3, exp-notes/pipeline_unroll.md and pipeline_unroll_chk.md (64 kernels).
//
// Per function:
//
//  0. User `hls.unroll` pragmas are applied first (complete, or by factor),
//     as Vitis does before its automatic decision. A loop that keeps a
//     partial user unroll (factor below the trip count, 1 included) is never
//     unrolled completely for an enclosing automatic pipeline: it blocks the
//     auto-pipelining of every loop around it and is pipelined itself (Vitis
//     ground truth of spector_hls/fir, forgebench/mult_op_p1, diff_dims_p1,
//     diff_orders_p1: the partially unrolled loops - and their user-made
//     copies - are the pipelined ones, their parents are not). Vitis keeps
//     the remainder iterations of a trip count the factor does not divide in
//     the unrolled body (exit checks), it has no epilogue loop: the cleanup
//     loop MLIR generates is unrolled completely into straight-line code
//     after the loop, and only the main loop carries `hls.unroll_partial`
//     (none does when the main loop is left with a single iteration and
//     MLIR replaces it by its body).
//
//  1. Perfect-nest collapse. A loop whose body holds exactly one nested loop
//     and no memory operation outside it (register-only code is allowed)
//     forms a perfect nest with that loop; chains collapse into ONE loop for
//     the decision, with the product of the trip counts. Perfectness is
//     judged as Vitis sees it after LLVM LICM and scalar promotion: a load
//     whose address does not change with the inner loop, from a memory the
//     inner loop never writes, is hoisted into the outer body, and the
//     accesses of a memory touched at one inner-invariant address only
//     (`acc[i] += ...`) are promoted to a register with the load before and
//     the store after the inner loop. Both make the nest imperfect; pure
//     arithmetic never does. The hoist rule is confirmed for integer
//     elements only: Vitis flattens the same nest when the invariant load
//     reads a floating-point element (see "Perfectness and floating point"
//     below; option float-loads-perfect, default on). Promotion makes the
//     nest imperfect whatever the element type. A loop marked
//     `hls.uncounted` (cgeist: a counter narrower than its runtime bound,
//     `for (uint8_t i = 0; i < n; i++)` with int n) is never the outer loop
//     of a collapsed pair: Vitis, which cannot compute its trip count, treats
//     it like the outer loop of an imperfect nest (VITIS_NOTES.md N15: the
//     loop is pipelined and a <= 64-trip perfect inner loop unrolled into it,
//     where an `int` counter gets the inner loop pipelined and flattened).
//     When its perfect inner loop is pipelined instead, it is flattened into
//     it in step 3 despite its runtime bound, as the collapse would have
//     done (N15: nc_f_u8 like nc_f_int).
//
//  2. Top-down decision. A (collapsed) loop P is pipelined iff every loop
//     nested anywhere inside it - loops of called functions included - has a
//     constant trip count and the product of the trip counts along every
//     nesting path inside P is <= T. Every loop inside P is then completely
//     unrolled (all levels, callee loops included), after the invariant loads
//     have been hoisted and the register-promotable accesses promoted out of
//     the loops being unrolled - and, once they are unrolled, out of the
//     pipelined loop itself (option promote-pipelined, default on) - so the
//     pipelined body carries the accesses Vitis schedules (one `acc[i]` load
//     and store, not 64 of each; `acc[0..7] +=` of an unrolled body becomes
//     eight register recurrences and the loop reads nothing of acc). A loop
//     containing no loop is pipelined as it is, whatever its trip count. If P
//     fails, each child loop is decided on its own.
//
//  3. Flattening. A loop Q that was not pipelined, has exactly one child
//     loop C (directly in its body, no call boundary), constant bounds, and
//     whose C (constant trip counts) ends up pipelined, is converted and
//     flattened by Vitis into C's pipeline. C is tagged with
//     `hls.flattened_parents = N` (counting Q and, recursively, Q's parents
//     and the perfect-chain members above C) so that later passes treat the
//     induction variables of those N ancestors as loop-variant for C's
//     pipeline: --convert-affine-to-loopschedule does not hoist such loads
//     and --infer-vitis-split-array / --bram-analysis count them.
//
// Tags: the pipelined loop gets `hls.pipeline = [{II = 0 : i32, source =
// "auto"}]` and, when it unrolled loops, `hls.auto_unrolled = [{factor, loc},
// ...]` (a record for --bram-debug). A user `hls.pipeline` is kept as written
// and always wins (the loop is pipelined whatever T, everything inside it is
// unrolled); a user `hls.pipeline_off` loop is never auto-pipelined.
// `pipeline-loops=0` disables the automatic decision; user pragmas are still
// applied.
//
// Perfectness and floating point (VITIS_NOTES.md N3, exp-src/
// pipeline_unroll_float): a load at an inner-invariant address makes the nest
// imperfect only when the loaded element is an integer. The same nest
// reading a float element (`lo[i][j] = la[i][j] * lb[i]`, float `lb`) is
// converted into a perfect nest and flattened by Vitis
// (rv_st_hoist_f_m64_n64, rv_rmw_hoist_f_m8_n64 / _m64_n64, pf_fmul_m8_n64,
// pf_fadd_m8_n64, pf_fmac_m8_n32, pf_srchoist_m8_n64 - the load written in
// the outer body in the source -, pm_floatarr_iop_m8_n64 - float arrays,
// integer arithmetic; polybench atax lp3/lp4, bicg lp1/lp2), while every
// integer twin is unrolled (rv_st_hoist_m64_n64, rv_rmw_hoist_m8_n64,
// pi_add_m8_n64, pi_mul3_m8_n64, pl_mul_m8_n64, pi_srchoist_m8_n64,
// pm_intarr_fop_m8_n64 - int arrays, float arithmetic), and so is a body
// with one float and one int invariant load (pf_twoload_m8_n64). It is the
// type of the load, not of the arithmetic. Register promotion of an
// accumulator makes the nest imperfect for float elements too
// (pf_memred_m8_n16; atax lp1/lp2, bicg lp3/lp4, gesummv, mvt). Vitis'
// mechanism is not visible in the IR dumps (the decision precedes a.o.1.ll,
// where the float load is hoisted all the same). Option float-loads-perfect
// applies this rule; it is on by default (MEMOS.md M8, decision #3 of
// 2026-10-10, together with the exactclass harness shim); =false gives the
// original T3 model, where every hoistable invariant load breaks
// perfectness. The rule keys on the MLIR element type, so it is right where
// that is the type Vitis sees: with the exactclass shim an ap_fixed is an
// integer, as in Vitis; the scalar shim (ap_fixed = float/double) and the
// exact shim (W <= 16: _Float16) make ap_fixed loads float, against N3.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/AutoPipelineUnroll.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/IR/SymbolTable.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/Debug.h"

#include <limits>

#define DEBUG_TYPE "auto-pipeline-unroll"

using namespace mlir;
using namespace mlir::affine;
using circt::hls_analysis::getFlattenedParents;
using circt::hls_analysis::kLoopAutoUnrolledAttr;
using circt::hls_analysis::kLoopFlattenedParentsAttr;
using circt::hls_analysis::kLoopPipelineAttr;
using circt::hls_analysis::kLoopPipelineAutoSource;
using circt::hls_analysis::kLoopPipelineOffAttr;
using circt::hls_analysis::kLoopUnrollAttr;
using circt::hls_analysis::kLoopUncountedAttr;
using circt::hls_analysis::kLoopUnrollOffAttr;
using circt::hls_analysis::kLoopUnrollPartialAttr;

namespace {

//===----------------------------------------------------------------------===//
// Pragma attributes
//===----------------------------------------------------------------------===//

/// Set on a loop only for the duration of its loopUnrollByFactor call, so
/// that the main loop and the cleanup clone can be found afterwards.
constexpr llvm::StringLiteral kUnrollPendingAttr = "hls.unroll_partial_pending";

/// First dictionary of a `[{...}]` (or bare `{...}`) pragma attribute.
static DictionaryAttr pragmaDict(Attribute attr) {
  if (auto array = dyn_cast_or_null<ArrayAttr>(attr))
    attr = array.empty() ? Attribute() : array[0];
  return dyn_cast_or_null<DictionaryAttr>(attr);
}

static bool isAutoPipelineTag(Attribute attr) {
  DictionaryAttr dict = pragmaDict(attr);
  if (!dict)
    return false;
  auto source = dict.getAs<StringAttr>("source");
  return source && source.getValue() == kLoopPipelineAutoSource;
}

/// A `hls.pipeline` the user wrote (not this pass's own tag).
static bool isUserPipelined(AffineForOp loop) {
  Attribute attr = loop->getAttr(kLoopPipelineAttr);
  return attr && !isAutoPipelineTag(attr) &&
         !loop->hasAttr(kLoopPipelineOffAttr);
}

/// User unroll factor of `loop`; 0 = complete; nullopt = no pragma.
static std::optional<uint64_t> userUnrollFactor(AffineForOp loop) {
  if (loop->hasAttr(kLoopUnrollOffAttr))
    return std::nullopt;
  Attribute attr = loop->getAttr(kLoopUnrollAttr);
  if (!attr)
    return std::nullopt;
  DictionaryAttr dict = pragmaDict(attr);
  if (!dict)
    return 0;
  if (auto factor = dict.getAs<IntegerAttr>("factor"))
    return factor.getInt() > 0 ? static_cast<uint64_t>(factor.getInt()) : 0;
  return 0;
}

static void tagAutoPipeline(AffineForOp loop) {
  Builder b(loop.getContext());
  loop->setAttr(
      kLoopPipelineAttr,
      b.getArrayAttr({b.getDictionaryAttr(
          {b.getNamedAttr("II", b.getI32IntegerAttr(0)),
           b.getNamedAttr("source",
                          b.getStringAttr(kLoopPipelineAutoSource))})}));
}

static void addFlattenedParents(AffineForOp loop, unsigned count) {
  if (count == 0)
    return;
  Builder b(loop.getContext());
  loop->setAttr(kLoopFlattenedParentsAttr,
                b.getI64IntegerAttr(getFlattenedParents(loop) + count));
}

//===----------------------------------------------------------------------===//
// Memory accesses and the LICM / promotion model
//===----------------------------------------------------------------------===//

/// One affine or memref load/store: its memory and composed address.
struct Access {
  Operation *op = nullptr;
  Value mem;
  bool isWrite = false;
  AffineMap map;
  SmallVector<Value, 8> operands;
};

static std::optional<Access> getAccess(Operation *op) {
  Access a;
  a.op = op;
  MLIRContext *ctx = op->getContext();
  if (auto load = dyn_cast<AffineLoadOp>(op)) {
    a.mem = load.getMemRef();
    a.map = load.getAffineMap();
    a.operands.assign(load.getMapOperands().begin(),
                      load.getMapOperands().end());
  } else if (auto store = dyn_cast<AffineStoreOp>(op)) {
    a.mem = store.getMemRef();
    a.isWrite = true;
    a.map = store.getAffineMap();
    a.operands.assign(store.getMapOperands().begin(),
                      store.getMapOperands().end());
  } else if (auto load = dyn_cast<memref::LoadOp>(op)) {
    a.mem = load.getMemRef();
    a.map = AffineMap::getMultiDimIdentityMap(load.getIndices().size(), ctx);
    a.operands.assign(load.getIndices().begin(), load.getIndices().end());
  } else if (auto store = dyn_cast<memref::StoreOp>(op)) {
    a.mem = store.getMemRef();
    a.isWrite = true;
    a.map = AffineMap::getMultiDimIdentityMap(store.getIndices().size(), ctx);
    a.operands.assign(store.getIndices().begin(), store.getIndices().end());
  } else {
    return std::nullopt;
  }
  fullyComposeAffineMapAndOperands(&a.map, &a.operands);
  canonicalizeMapAndOperands(&a.map, &a.operands);
  a.map = simplifyAffineMap(a.map);
  return a;
}

static bool sameAddress(const Access &x, const Access &y) {
  return x.mem == y.mem && x.map == y.map && x.operands == y.operands;
}

static bool isInvariantIn(const Access &a, AffineForOp loop) {
  if (!loop.isDefinedOutsideOfLoop(a.mem))
    return false;
  return llvm::all_of(a.operands,
                      [&](Value v) { return loop.isDefinedOutsideOfLoop(v); });
}

/// True if some op inside `loop` may write `mem`, or uses it opaquely.
static bool isMemrefWrittenInLoop(Value mem, AffineForOp loop) {
  bool written = false;
  loop.getBody()->walk([&](Operation *op) {
    if (!llvm::is_contained(op->getOperands(), mem))
      return WalkResult::advance();
    auto eff = dyn_cast<MemoryEffectOpInterface>(op);
    if (!eff) {
      written = true; // a call, a cast: unknown effects
      return WalkResult::interrupt();
    }
    SmallVector<MemoryEffects::EffectInstance> effects;
    eff.getEffectsOnValue(mem, effects);
    for (auto &e : effects)
      if (!isa<MemoryEffects::Read>(e.getEffect())) {
        written = true;
        return WalkResult::interrupt();
      }
    return WalkResult::advance();
  });
  return written;
}

/// Two loop-invariant addresses of one memory that provably never meet:
/// same operands, and the maps differ by a nonzero constant in some
/// dimension (`acc[0]` vs `acc[1]`, `buf[i][2]` vs `buf[i][5]`).
static bool provablyDisjoint(const Access &x, const Access &y) {
  if (x.operands != y.operands || x.map.getNumResults() != y.map.getNumResults())
    return false;
  for (auto [ex, ey] : llvm::zip(x.map.getResults(), y.map.getResults())) {
    AffineExpr d = simplifyAffineExpr(ex - ey, x.map.getNumDims(),
                                      x.map.getNumSymbols());
    if (auto c = dyn_cast<AffineConstantExpr>(d))
      if (c.getValue() != 0)
        return true;
  }
  return false;
}

/// Vitis (LLVM LICM scalar promotion) keeps a location of `mem` in a
/// register across `loop` when every use of `mem` inside the loop is a load
/// or store at an address that does not change with the loop, and the
/// distinct addresses are provably disjoint (LLVM promotes each must-alias
/// set on its own: `acc[0] += ..; acc[1] += ..` become two registers). At
/// least one access must be a store (a read-only location is hoisted, not
/// promoted). `groups`, if given, receives the accesses per address in
/// program order, or stays empty when some access is nested in a region of
/// the body (an `affine.if`), which the physical rewrite does not handle.
static bool isPromotableIn(Value mem, AffineForOp loop,
                           SmallVector<SmallVector<Access, 4>, 2> *groups =
                               nullptr) {
  bool ok = true, anyStore = false, allDirect = true;
  SmallVector<SmallVector<Access, 4>, 2> found;
  loop.getBody()->walk([&](Operation *op) {
    if (!llvm::is_contained(op->getOperands(), mem))
      return WalkResult::advance();
    std::optional<Access> a = getAccess(op);
    if (!a || a->mem != mem || !isInvariantIn(*a, loop)) {
      ok = false; // stored as a value, passed to a call, variant address
      return WalkResult::interrupt();
    }
    anyStore |= a->isWrite;
    if (op->getBlock() != loop.getBody())
      allDirect = false;
    auto *g = llvm::find_if(found, [&](auto &grp) {
      return sameAddress(grp.front(), *a);
    });
    if (g != found.end()) {
      g->push_back(*a);
    } else {
      for (auto &grp : found)
        if (!provablyDisjoint(grp.front(), *a)) {
          ok = false; // may alias another promoted location
          return WalkResult::interrupt();
        }
      found.push_back({*a});
    }
    return WalkResult::advance();
  });
  if (!ok || !anyStore)
    return false;
  if (groups) {
    if (allDirect)
      *groups = std::move(found);
    else
      groups->clear();
  }
  return true;
}

static bool hasFloatElement(Value mem) {
  return isa<FloatType>(cast<MemRefType>(mem.getType()).getElementType());
}

/// Where Vitis' LICM / promotion leave a memory operation AT DECISION TIME:
/// the innermost loop out of which it cannot move. Opaque memory ops (calls,
/// hls.store_enable, ...) stay where they are. With `floatLoadsPerfect`, so
/// does a read-only load of a floating-point element (observed, see the file
/// header; the physical hoist that Vitis' later LICM applies to it is done
/// by hoistInvariantOps when a loop is actually unrolled).
class LicmModel {
public:
  explicit LicmModel(bool floatLoadsPerfect)
      : floatLoadsPerfect(floatLoadsPerfect) {}

  /// The loop whose body `op` effectively sits in (nullptr: outside every
  /// loop of the function).
  AffineForOp effectiveLoop(Operation *op) {
    AffineForOp cur = op->getParentOfType<AffineForOp>();
    std::optional<Access> a = getAccess(op);
    if (!a)
      return cur;
    while (cur && movableOutOf(*a, cur))
      cur = cur->getParentOfType<AffineForOp>();
    return cur;
  }

  bool movableOutOf(const Access &a, AffineForOp loop) {
    if (!isInvariantIn(a, loop))
      return false;
    if (!a.isWrite && !written(a.mem, loop))
      // LICM hoist (confirmed for integer elements; a float load stays put
      // for the decision under float-loads-perfect).
      return !(floatLoadsPerfect && hasFloatElement(a.mem));
    return promotable(a.mem, loop);
  }

  const bool floatLoadsPerfect;

private:
  using Key = std::pair<Value, Operation *>;
  bool written(Value mem, AffineForOp loop) {
    Key key{mem, loop.getOperation()};
    auto it = writtenCache.find(key);
    if (it != writtenCache.end())
      return it->second;
    bool w = isMemrefWrittenInLoop(mem, loop);
    writtenCache[key] = w;
    return w;
  }
  bool promotable(Value mem, AffineForOp loop) {
    Key key{mem, loop.getOperation()};
    auto it = promotableCache.find(key);
    if (it != promotableCache.end())
      return it->second;
    bool p = isPromotableIn(mem, loop);
    promotableCache[key] = p;
    return p;
  }
  DenseMap<Key, bool> writtenCache, promotableCache;
};

//===----------------------------------------------------------------------===//
// Loop forest
//===----------------------------------------------------------------------===//

struct Node {
  /// Perfect chain, outermost first. The decision treats it as one loop.
  SmallVector<AffineForOp, 3> chain;
  SmallVector<std::unique_ptr<Node>, 4> children;
  /// Reached through a call from the parent node: no flattening across it,
  /// decided when its own function is processed.
  bool viaCall = false;
  /// Some chain member has no constant trip count, carries `hls.unroll_off`,
  /// or the node stands for a loop that is not an affine.for at all.
  bool dynamic = false;
  /// Some chain member keeps a partial user unroll (`hls.unroll_partial`):
  /// never unrolled by an enclosing pipeline, pipelined on its own.
  bool userFixed = false;
  uint64_t trip = 1; // product of the chain's trip counts (if !dynamic)
  int userPipelineIdx = -1; // outermost user-pipelined chain member
  bool pipelineOff = false; // chain.back() carries hls.pipeline_off
  /// The node is one `hls.uncounted` loop that would have collapsed with its
  /// only child (a perfect pair, constant inner trip count) had it been
  /// counted (step 1); it may still be flattened into that child (step 3).
  bool uncountedPerfect = false;
  // Derived over the subtree.
  bool constInside = true;
  uint64_t maxPath = 1; // trip * max over children of maxPath
  bool hasUserPipeline = false;
  bool hasUserFixed = false;
  /// The pipelined loop that absorbs this node: the node's own innermost
  /// loop when it is pipelined, or the child's when it is flattened into it.
  AffineForOp tagged;
};

/// A read-only load of a floating-point element directly in `outer`'s body
/// from a memory `inner` never writes. cgeist's own LICM moves inner-invariant
/// loads there (`lb[i]` of `lo[i][j] = la[i][j] * lb[i]` ends up before the j
/// loop in the MLIR), and a source may hold it there too (`float t = lb[i];`
/// before the j loop, pf_srchoist_m8_n64), but Vitis converts such a nest
/// into a perfect one and flattens it (see the file header), so under
/// float-loads-perfect the load is judged as if it were in the inner loop.
static bool isSinkableFloatLoad(Operation *op, AffineForOp outer,
                                AffineForOp inner) {
  if (op->getBlock() != outer.getBody())
    return false;
  std::optional<Access> a = getAccess(op);
  if (!a || a->isWrite || !hasFloatElement(a->mem))
    return false;
  return !isMemrefWrittenInLoop(a->mem, inner);
}

/// Does `outer` form a perfect nest with `inner` (the only loop directly in
/// its body), as Vitis judges it after LICM / promotion?
static bool isPerfectPair(AffineForOp outer, AffineForOp inner,
                          LicmModel &licm) {
  if (inner->getBlock() != outer.getBody())
    return false;
  bool perfect = true;
  outer.getBody()->walk<WalkOrder::PreOrder>([&](Operation *op) {
    if (op == inner.getOperation())
      return WalkResult::skip();
    if (isa<LoopLikeOpInterface>(op) || isa<CallOpInterface>(op)) {
      perfect = false;
      return WalkResult::interrupt();
    }
    if (op->getNumRegions() > 0)
      return WalkResult::advance(); // look inside ifs
    if (isMemoryEffectFree(op))
      return WalkResult::advance();
    if (licm.effectiveLoop(op) != outer)
      return WalkResult::advance(); // hoisted further out
    if (licm.floatLoadsPerfect && isSinkableFloatLoad(op, outer, inner))
      return WalkResult::advance(); // sunk back by Vitis' nest conversion
    perfect = false;
    return WalkResult::interrupt();
  });
  if (!perfect)
    return false;
  // Memory ops of the inner nest that LICM / promotion move into outer's
  // body.
  inner.getBody()->walk([&](Operation *op) {
    if (!getAccess(op))
      return WalkResult::advance();
    if (licm.effectiveLoop(op) == outer) {
      perfect = false;
      return WalkResult::interrupt();
    }
    return WalkResult::advance();
  });
  return perfect;
}

static uint64_t saturatingMul(uint64_t a, uint64_t b) {
  uint64_t r;
  if (__builtin_mul_overflow(a, b, &r))
    return std::numeric_limits<uint64_t>::max();
  return r;
}

class Forest {
public:
  Forest(LicmModel &licm) : licm(licm) {}

  /// Loops directly inside `region` (not nested in another loop), following
  /// calls into their callees. `opaqueLoop` is set when a loop that is not
  /// an affine.for is met.
  void collectChildren(Region &region, bool viaCall,
                       SmallVector<std::pair<AffineForOp, bool>, 4> &loops,
                       bool &opaqueLoop,
                       SmallPtrSetImpl<Operation *> &callStack) {
    region.walk<WalkOrder::PreOrder>([&](Operation *op) {
      if (auto forOp = dyn_cast<AffineForOp>(op)) {
        loops.emplace_back(forOp, viaCall);
        return WalkResult::skip();
      }
      if (isa<LoopLikeOpInterface>(op)) {
        opaqueLoop = true;
        return WalkResult::skip();
      }
      if (auto call = dyn_cast<CallOpInterface>(op)) {
        auto callee = dyn_cast_or_null<func::FuncOp>(
            call.resolveCallableInTable(&symbolTable));
        if (!callee || callee.isExternal() ||
            !callStack.insert(callee.getOperation()).second)
          return WalkResult::advance();
        collectChildren(callee.getBody(), /*viaCall=*/true, loops, opaqueLoop,
                        callStack);
        callStack.erase(callee.getOperation());
      }
      return WalkResult::advance();
    });
  }

  std::unique_ptr<Node> build(AffineForOp root, bool viaCall,
                              SmallPtrSetImpl<Operation *> &callStack) {
    auto node = std::make_unique<Node>();
    node->viaCall = viaCall;
    node->chain.push_back(root);
    AffineForOp cur = root;
    SmallVector<std::pair<AffineForOp, bool>, 4> childLoops;
    bool opaqueLoop = false;
    while (true) {
      childLoops.clear();
      opaqueLoop = false;
      collectChildren(cur.getRegion(), /*viaCall=*/false, childLoops,
                      opaqueLoop, callStack);
      if (childLoops.size() != 1 || opaqueLoop || childLoops[0].second)
        break;
      AffineForOp child = childLoops[0].first;
      // A dynamic inner loop is never flattened (Vitis' semi-perfect rule
      // allows a variable bound on the outermost loop only).
      if (!getConstantTripCount(child) ||
          child->hasAttr(kLoopUnrollOffAttr))
        break;
      if (!isPerfectPair(cur, child, licm))
        break;
      // An uncounted loop (only ever the first chain member: its trip count
      // is not constant) does not collapse with its child (step 1, N15).
      if (cur->hasAttr(kLoopUncountedAttr)) {
        node->uncountedPerfect = true;
        break;
      }
      node->chain.push_back(child);
      cur = child;
    }
    for (AffineForOp loop : node->chain) {
      std::optional<uint64_t> trip = getConstantTripCount(loop);
      if (!trip || loop->hasAttr(kLoopUnrollOffAttr))
        node->dynamic = true;
      else
        node->trip = saturatingMul(node->trip, *trip);
    }
    for (auto [idx, loop] : llvm::enumerate(node->chain)) {
      if (node->userPipelineIdx < 0 && isUserPipelined(loop))
        node->userPipelineIdx = static_cast<int>(idx);
      if (loop->hasAttr(kLoopUnrollPartialAttr))
        node->userFixed = true;
    }
    node->pipelineOff = node->chain.back()->hasAttr(kLoopPipelineOffAttr);
    for (auto [loop, childViaCall] : childLoops) {
      // A child reached through a call: keep its function on the call stack
      // while its subtree is built, so that a call back into that function
      // (direct or mutual recursion) is cut there too, not only during
      // collectChildren. Children of this function are already covered by
      // the entry runOnOperation pushed.
      Operation *owner = nullptr;
      if (auto fn = loop->getParentOfType<func::FuncOp>())
        owner = fn.getOperation();
      bool pushed = owner && callStack.insert(owner).second;
      node->children.push_back(build(loop, childViaCall, callStack));
      if (pushed)
        callStack.erase(owner);
    }
    if (opaqueLoop) {
      // A loop that is not an affine.for: a dynamic child.
      auto opaque = std::make_unique<Node>();
      opaque->dynamic = true;
      opaque->constInside = false;
      node->children.push_back(std::move(opaque));
    }
    node->constInside = !node->dynamic;
    node->hasUserPipeline = node->userPipelineIdx >= 0;
    node->hasUserFixed = node->userFixed;
    uint64_t maxChild = 1;
    for (auto &c : node->children) {
      node->constInside &= c->constInside;
      node->hasUserPipeline |= c->hasUserPipeline;
      node->hasUserFixed |= c->hasUserFixed;
      maxChild = std::max(maxChild, c->maxPath);
    }
    node->maxPath = saturatingMul(node->trip, maxChild);
    return node;
  }

  LicmModel &licm;
  SymbolTableCollection symbolTable;
};

//===----------------------------------------------------------------------===//
// Physical transforms: hoist, promote, unroll
//===----------------------------------------------------------------------===//

/// Vitis LICM on a loop about to be unrolled: ops directly in `loop`'s body
/// whose operands are all defined outside it (or by ops hoisted before them)
/// move before the loop - pure speculatable ops, and loads from a memory the
/// loop never writes. After the unroll, the pipelined parent then holds one
/// such load instead of trip-count copies of it.
static unsigned hoistInvariantOps(AffineForOp loop) {
  DenseSet<Value> invariant;
  auto isInvariantValue = [&](Value v) {
    return loop.isDefinedOutsideOfLoop(v) || invariant.contains(v);
  };
  DenseMap<Value, bool> writtenCache;
  auto writtenInLoop = [&](Value mem) {
    auto it = writtenCache.find(mem);
    if (it != writtenCache.end())
      return it->second;
    bool w = isMemrefWrittenInLoop(mem, loop);
    writtenCache[mem] = w;
    return w;
  };
  SmallVector<Operation *> toHoist;
  for (Operation &op : loop.getBody()->without_terminator()) {
    if (op.getNumRegions() != 0)
      continue;
    bool hoistable = false;
    if (auto load = dyn_cast<AffineLoadOp>(op)) {
      hoistable = llvm::all_of(load.getMapOperands(), isInvariantValue) &&
                  isInvariantValue(load.getMemRef()) &&
                  !writtenInLoop(load.getMemRef());
    } else if (auto load = dyn_cast<memref::LoadOp>(op)) {
      hoistable = llvm::all_of(load.getIndices(), isInvariantValue) &&
                  isInvariantValue(load.getMemRef()) &&
                  !writtenInLoop(load.getMemRef());
    } else if (isMemoryEffectFree(&op) && isSpeculatable(&op) &&
               op.getNumResults() > 0) {
      hoistable = llvm::all_of(op.getOperands(), isInvariantValue);
    }
    if (!hoistable)
      continue;
    toHoist.push_back(&op);
    for (Value r : op.getResults())
      invariant.insert(r);
  }
  for (Operation *op : toHoist)
    op->moveBefore(loop);
  return toHoist.size();
}

/// Register promotion of every memory `loop` touches at loop-invariant,
/// pairwise disjoint addresses only (Vitis / LLVM LICM scalar promotion):
/// per address, one load before the loop, the value carried as an iter_arg,
/// one store after (a read-only address is just loaded before the loop).
/// Only affine accesses directly in the body are rewritten. Returns the loop
/// (a new op, with the same attributes, when something was promoted).
static AffineForOp promoteInvariantAccesses(AffineForOp loop,
                                            unsigned &promoted) {
  // Memories accessed directly in the body, in first-access order.
  SmallVector<Value, 4> mems;
  for (Operation &op : loop.getBody()->without_terminator()) {
    std::optional<Access> a = getAccess(&op);
    if (a && !llvm::is_contained(mems, a->mem))
      mems.push_back(a->mem);
  }
  for (Value mem : mems) {
    SmallVector<SmallVector<Access, 4>, 2> groups;
    if (!isPromotableIn(mem, loop, &groups) || groups.empty())
      continue;
    bool allAffine = llvm::all_of(groups, [](auto &grp) {
      return llvm::all_of(grp, [](const Access &a) {
        return isa<AffineLoadOp, AffineStoreOp>(a.op);
      });
    });
    Type elemType = cast<MemRefType>(mem.getType()).getElementType();
    if (!allAffine || !elemType.isIntOrIndexOrFloat())
      continue;
    for (auto &accesses : groups) {
      const Access &first = accesses.front();
      bool anyStore = llvm::any_of(
          accesses, [](const Access &a) { return a.isWrite; });
      OpBuilder b(loop);
      Value init;
      if (!first.isWrite) {
        init = AffineLoadOp::create(b, first.op->getLoc(), mem, first.map,
                                    first.operands);
      } else {
        // The first access is a store: no value flows in.
        init = arith::ConstantOp::create(b, loop.getLoc(), elemType,
                                         b.getZeroAttr(elemType));
      }
      if (!anyStore) {
        // A read-only location: LICM hoists it (one load before the loop).
        for (const Access &a : accesses) {
          a.op->getResult(0).replaceAllUsesWith(init);
          a.op->erase();
        }
        ++promoted;
        continue;
      }
      IRRewriter rewriter(loop.getContext());
      SmallPtrSet<Operation *, 8> accessOps;
      for (const Access &a : accesses)
        accessOps.insert(a.op);
      Block *body = loop.getBody();
      DictionaryAttr attrs = loop->getDiscardableAttrDictionary();
      FailureOr<LoopLikeOpInterface> replaced =
          loop.replaceWithAdditionalYields(
              rewriter, init, /*replaceInitOperandUsesInLoop=*/false,
              [&](OpBuilder &, Location, ArrayRef<BlockArgument> newArgs) {
                Value cur = newArgs[0];
                SmallVector<Operation *> toErase;
                for (Operation &op : body->without_terminator()) {
                  if (!accessOps.contains(&op))
                    continue;
                  if (auto store = dyn_cast<AffineStoreOp>(op))
                    cur = store.getValueToStore();
                  else
                    op.getResult(0).replaceAllUsesWith(cur);
                  toErase.push_back(&op);
                }
                for (Operation *op : toErase)
                  op->erase();
                return SmallVector<Value>{cur};
              });
      if (failed(replaced))
        break;
      loop = cast<AffineForOp>(replaced->getOperation());
      loop->setDiscardableAttrs(attrs);
      OpBuilder after(loop.getContext());
      after.setInsertionPointAfter(loop);
      AffineStoreOp::create(after, loop.getLoc(), loop.getResults().back(),
                            mem, first.map, first.operands);
      ++promoted;
    }
  }
  return loop;
}

static std::string locString(Location loc) {
  std::string s;
  llvm::raw_string_ostream os(s);
  loc.print(os);
  return s;
}

struct AutoPipelineUnrollPass
    : public PassWrapper<AutoPipelineUnrollPass, OperationPass<ModuleOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(AutoPipelineUnrollPass)

  AutoPipelineUnrollPass() = default;
  AutoPipelineUnrollPass(const AutoPipelineUnrollPass &other)
      : PassWrapper(other) {}

  Option<unsigned> pipelineLoops{
      *this, "pipeline-loops",
      llvm::cl::desc("Vitis config_compile -pipeline_loops: a loop whose "
                     "nested trip-count products are all <= this is "
                     "pipelined and everything inside it unrolled; 0 "
                     "disables the automatic decision (default 64)"),
      llvm::cl::init(64)};
  Option<bool> promotePipelined{
      *this, "promote-pipelined",
      llvm::cl::desc("Also promote the loop-invariant accesses of the "
                     "pipelined loop itself to registers once its inner "
                     "loops are unrolled (Vitis LICM; off keeps them as "
                     "memory accesses of the pipeline)"),
      llvm::cl::init(true)};
  Option<bool> floatLoadsPerfect{
      *this, "float-loads-perfect",
      llvm::cl::desc("A read-only inner-invariant load of a floating-point "
                     "element does not make a loop nest imperfect, so the "
                     "nest is flattened rather than its inner loop unrolled "
                     "(Vitis 2025.1 observation, VITIS_NOTES.md N3). On by "
                     "default (MEMOS.md M8, decision #3); =false: every "
                     "hoistable invariant load breaks perfectness, the "
                     "original T3 rule"),
      llvm::cl::init(true)};
  Option<bool> emitRemarks{
      *this, "emit-remarks",
      llvm::cl::desc("Print one remark per decision (pipeline, unroll, "
                     "flatten, user unroll)"),
      llvm::cl::init(false)};

  StringRef getArgument() const final { return "auto-pipeline-unroll"; }
  StringRef getDescription() const final {
    return "Vitis automatic pipeline / unroll / flatten decision "
           "(config_compile -pipeline_loops)";
  }

  void getDependentDialects(DialectRegistry &registry) const override {
    registry.insert<arith::ArithDialect, memref::MemRefDialect>();
  }

  void remark(Location loc, const Twine &msg) {
    if (emitRemarks)
      mlir::emitRemark(loc) << msg;
    LLVM_DEBUG(llvm::dbgs() << msg << " @ " << loc << "\n");
  }

  /// Step 0: user `hls.unroll` pragmas, innermost loops first.
  void applyUserUnrolls(func::FuncOp func) {
    SmallVector<AffineForOp> loops;
    func.walk<WalkOrder::PostOrder>([&](AffineForOp loop) {
      if (userUnrollFactor(loop))
        loops.push_back(loop);
    });
    for (AffineForOp loop : loops) {
      uint64_t factor = *userUnrollFactor(loop);
      std::optional<uint64_t> trip = getConstantTripCount(loop);
      loop->removeAttr(kLoopUnrollAttr);
      Builder b(loop.getContext());
      if (factor == 1) {
        loop->setAttr(kLoopUnrollPartialAttr, b.getI64IntegerAttr(1));
        remark(loop.getLoc(), "user unroll: factor 1, the loop is never "
                              "auto-unrolled into a parent pipeline");
        continue;
      }
      if (factor == 0 || (trip && factor >= *trip)) {
        if (!trip) {
          remark(loop.getLoc(),
                 "user unroll: dynamic trip count, left rolled");
          continue;
        }
        remark(loop.getLoc(),
               "user unroll: completely (trip " + Twine(*trip) + ")");
        if (failed(loopUnrollFull(loop)))
          LLVM_DEBUG(llvm::dbgs() << "  loopUnrollFull failed\n");
        continue;
      }
      remark(loop.getLoc(), "user unroll: by factor " + Twine(factor) +
                                " (the loop is never auto-unrolled into a "
                                "parent pipeline)");
      applyPartialUnroll(loop, factor);
    }
  }

  /// `#pragma HLS unroll factor=F` with 1 < F < trip count (or a dynamic
  /// trip count). loopUnrollByFactor keeps `loop` as the main loop (step
  /// scaled by F) and, when F does not divide the trip count, clones it -
  /// attributes included - into a cleanup loop with the original step right
  /// after it; either loop is replaced by its body when it is left with a
  /// single iteration (`loop` is then erased). Vitis has no epilogue loop
  /// (the exit checks stay in the unrolled body): the cleanup loop is
  /// unrolled completely into straight-line code, and only the main loop -
  /// if it is still a loop - gets `hls.unroll_partial`, so no second
  /// partially-unrolled pipeline appears.
  void applyPartialUnroll(AffineForOp loop, uint64_t factor) {
    Builder b(loop.getContext());
    auto markMain = [&](AffineForOp main) {
      main->setAttr(kLoopUnrollPartialAttr,
                    b.getI64IntegerAttr(static_cast<int64_t>(factor)));
    };
    // An empty body: loopUnrollByFactor leaves the loop as it is.
    if (llvm::hasSingleElement(loop.getBody()->getOperations())) {
      markMain(loop);
      return;
    }
    // Where the results of the call will sit: between `prev` and `next`
    // (both survive it; a loop always has a terminator after it).
    Block *block = loop->getBlock();
    Operation *prev = loop->getPrevNode();
    Operation *next = loop->getNextNode();
    int64_t step = loop.getStepAsInt();
    // A temporary marker the cleanup clone inherits, to find both loops.
    loop->setAttr(kUnrollPendingAttr, b.getUnitAttr());
    if (failed(loopUnrollByFactor(loop, factor))) {
      // Fails before touching the IR (bounds with several results).
      LLVM_DEBUG(llvm::dbgs() << "  loopUnrollByFactor failed\n");
      loop->removeAttr(kUnrollPendingAttr);
      markMain(loop);
      return;
    }
    SmallVector<AffineForOp, 2> results;
    for (Operation *op = prev ? prev->getNextNode() : &block->front();
         op && op != next; op = op->getNextNode())
      if (auto forOp = dyn_cast<AffineForOp>(op))
        if (forOp->hasAttr(kUnrollPendingAttr))
          results.push_back(forOp);
    for (AffineForOp forOp : results) {
      forOp->removeAttr(kUnrollPendingAttr);
      if (forOp.getStepAsInt() != step) {
        markMain(forOp); // the main loop, step * factor
        continue;
      }
      remark(forOp.getLoc(),
             "user unroll: remainder iterations unrolled completely (Vitis "
             "keeps them in the unrolled body, there is no epilogue loop)");
      if (failed(loopUnrollFull(forOp)))
        remark(forOp.getLoc(), "user unroll: the remainder loop has a "
                               "dynamic trip count, left rolled");
    }
  }

  /// Every loop inside `region`, innermost first, callee loops included.
  void collectInner(Region &region, SmallVector<AffineForOp> &out,
                    SmallPtrSetImpl<Operation *> &visitedCallees,
                    SymbolTableCollection &symbolTable) {
    region.walk<WalkOrder::PostOrder>([&](Operation *op) {
      if (auto forOp = dyn_cast<AffineForOp>(op)) {
        out.push_back(forOp);
      } else if (auto call = dyn_cast<CallOpInterface>(op)) {
        auto callee = dyn_cast_or_null<func::FuncOp>(
            call.resolveCallableInTable(&symbolTable));
        if (callee && !callee.isExternal() &&
            visitedCallees.insert(callee.getOperation()).second)
          collectInner(callee.getBody(), out, visitedCallees, symbolTable);
      }
    });
  }

  /// Everything inside the pipelined loop is unrolled completely. Each
  /// unrolled loop is recorded on `pipelined` in `hls.auto_unrolled`.
  void unrollInside(AffineForOp pipelined, SymbolTableCollection &symbolTable) {
    SmallVector<AffineForOp> inner;
    SmallPtrSet<Operation *, 4> visitedCallees;
    // The function that owns `pipelined` is never re-entered through a call
    // (direct or mutual recursion): that would collect `pipelined` itself,
    // or an ancestor of it, and erase it under our feet.
    if (auto owner = pipelined->getParentOfType<func::FuncOp>())
      visitedCallees.insert(owner.getOperation());
    collectInner(pipelined.getRegion(), inner, visitedCallees, symbolTable);
    Builder b(pipelined.getContext());
    SmallVector<Attribute> record;
    if (auto prev = pipelined->getAttrOfType<ArrayAttr>(kLoopAutoUnrolledAttr))
      record.append(prev.begin(), prev.end());
    for (AffineForOp loop : inner) {
      if (loop == pipelined || loop->isProperAncestor(pipelined))
        continue;
      std::optional<uint64_t> trip = getConstantTripCount(loop);
      if (!trip) {
        remark(loop.getLoc(), "cannot unroll: dynamic trip count");
        continue;
      }
      unsigned hoisted = hoistInvariantOps(loop);
      unsigned promoted = 0;
      loop = promoteInvariantAccesses(loop, promoted);
      remark(loop.getLoc(),
             "unrolling loop completely with a factor of " + Twine(*trip) +
                 " (implied by the pipeline of the loop at " +
                 locString(pipelined.getLoc()) + "; hoisted " +
                 Twine(hoisted) + " invariant op(s), promoted " +
                 Twine(promoted) + " memory(ies) to registers)");
      loop->removeAttr(kLoopPipelineAttr);
      loop->removeAttr(kLoopFlattenedParentsAttr);
      loop->removeAttr(kLoopAutoUnrolledAttr);
      LocationAttr loc = loop.getLoc();
      if (failed(loopUnrollFull(loop))) {
        LLVM_DEBUG(llvm::dbgs() << "  loopUnrollFull failed\n");
        continue;
      }
      record.push_back(b.getDictionaryAttr(
          {b.getNamedAttr("factor",
                          b.getI64IntegerAttr(static_cast<int64_t>(*trip))),
           b.getNamedAttr("loc", loc)}));
    }
    if (!record.empty())
      pipelined->setAttr(kLoopAutoUnrolledAttr, b.getArrayAttr(record));
  }

  /// LLVM LICM also promotes the accesses that became loop-invariant in the
  /// pipelined loop itself once its inner loops were unrolled
  /// (`acc[0..7] += ..` in a loop over k): the recurrence then runs through
  /// registers and the scheduler sees it as an iter_args recurrence.
  AffineForOp promoteOutOfPipeline(AffineForOp loop) {
    unsigned promoted = 0;
    AffineForOp result = promoteInvariantAccesses(loop, promoted);
    if (promoted)
      remark(result.getLoc(), "promoted " + Twine(promoted) +
                                  " invariant location(s) of the pipelined "
                                  "loop to registers");
    return result;
  }

  void decide(Node &n, SymbolTableCollection &symbolTable) {
    if (n.chain.empty())
      return; // placeholder for a non-affine loop
    unsigned T = pipelineLoops;
    if (n.userPipelineIdx >= 0) {
      AffineForOp u = n.chain[n.userPipelineIdx];
      n.tagged = u;
      addFlattenedParents(u, n.userPipelineIdx);
      remark(u.getLoc(), "user pipeline: unrolling everything inside, " +
                             Twine(n.userPipelineIdx) +
                             " perfect parent(s) flattened into it");
      unrollInside(u, symbolTable);
      // Promotion replaces the loop op; keep the node's handles current (the
      // parent's flatten step reads chain.front()).
      n.tagged = promotePipelined ? promoteOutOfPipeline(u) : u;
      n.chain[n.userPipelineIdx] = n.tagged;
      return;
    }
    bool feasible = T > 0 && !n.pipelineOff;
    for (auto &c : n.children)
      feasible &= c->constInside && c->maxPath <= T && !c->hasUserPipeline &&
                  !c->hasUserFixed;
    if (feasible) {
      AffineForOp p = n.chain.back();
      n.tagged = p;
      tagAutoPipeline(p);
      addFlattenedParents(p, n.chain.size() - 1);
      remark(p.getLoc(),
             "automatically set the pipeline for the loop (trip " +
                 (n.dynamic ? Twine("?") : Twine(n.trip)) + ", " +
                 Twine(n.chain.size() - 1) + " perfect parent(s) flattened, " +
                 Twine(n.children.size()) + " inner loop(s) to unroll)");
      unrollInside(p, symbolTable);
      n.tagged = promotePipelined ? promoteOutOfPipeline(p) : p;
      n.chain.back() = n.tagged;
      return;
    }
    for (auto &c : n.children)
      if (!c->viaCall)
        decide(*c, symbolTable);
    // Flattening of this (imperfect) loop into its single pipelined child.
    if (n.children.size() != 1)
      return;
    Node &c = *n.children.front();
    // An uncounted loop that is a perfect parent (not collapsed in step 1)
    // is flattened into its pipelined child as the counted loop is through
    // the collapse: its runtime bound is the variable outermost bound the
    // semi-perfect rule allows (N15: nc_f_u8 is flattened like nc_f_int). A
    // loop around it is not (c.dynamic).
    if (c.viaCall || c.chain.empty() || !c.tagged ||
        (n.dynamic && !n.uncountedPerfect) || c.dynamic)
      return;
    if (c.chain.front()->getBlock() != n.chain.back().getBody())
      return; // the child loop is conditional
    addFlattenedParents(c.tagged, n.chain.size());
    n.tagged = c.tagged;
    remark(n.chain.front().getLoc(),
           "flattening the loop (and " + Twine(n.chain.size() - 1) +
               " perfect inner loop(s)) into the pipelined loop at " +
               locString(c.tagged.getLoc()));
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();
    SymbolTableCollection symbolTable;

    // Idempotency: drop the tags of a previous run.
    module.walk([&](AffineForOp loop) {
      if (isAutoPipelineTag(loop->getAttr(kLoopPipelineAttr)))
        loop->removeAttr(kLoopPipelineAttr);
      loop->removeAttr(kLoopFlattenedParentsAttr);
      loop->removeAttr(kLoopAutoUnrolledAttr);
    });

    for (auto func : module.getOps<func::FuncOp>())
      if (!func.isExternal())
        applyUserUnrolls(func);

    for (auto func : module.getOps<func::FuncOp>()) {
      if (func.isExternal())
        continue;
      LicmModel licm(floatLoadsPerfect);
      Forest forest(licm);
      // Top-level loops of this function; callee loops are decided with
      // their own function and only take part in the feasibility test.
      SmallVector<AffineForOp, 8> roots;
      func.getBody().walk<WalkOrder::PreOrder>([&](AffineForOp loop) {
        roots.push_back(loop);
        return WalkResult::skip();
      });
      SmallVector<std::unique_ptr<Node>> nodes;
      SmallPtrSet<Operation *, 4> callStack;
      callStack.insert(func.getOperation());
      for (AffineForOp loop : roots)
        nodes.push_back(forest.build(loop, /*viaCall=*/false, callStack));
      for (auto &node : nodes)
        decide(*node, symbolTable);
    }
  }
};

} // namespace

namespace circt::hls_analysis {

std::unique_ptr<mlir::Pass> createAutoPipelineUnrollPass() {
  return std::make_unique<AutoPipelineUnrollPass>();
}

void registerAutoPipelineUnrollPass() {
  ::mlir::PassRegistration<AutoPipelineUnrollPass>();
}

} // namespace circt::hls_analysis
