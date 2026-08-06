

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/AutoPipelineUnroll.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
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
#include "llvm/ADT/MapVector.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/Debug.h"

#include <functional>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <tuple>
#include <vector>

#define DEBUG_TYPE "auto-pipeline-unroll"

using namespace mlir;
using namespace mlir::affine;
using circt::hls_analysis::getFlattenedParents;
using circt::hls_analysis::kCallDepthAttr;
using circt::hls_analysis::kCallOccupancyAttr;
using circt::hls_analysis::kLoopAutoUnrolledAttr;
using circt::hls_analysis::kLoopCallBoundaryAttr;
using circt::hls_analysis::kLoopFlattenedParentsAttr;
using circt::hls_analysis::kLoopPipelineAttr;
using circt::hls_analysis::kLoopPipelineAutoSource;
using circt::hls_analysis::kLoopPipelineOffAttr;
using circt::hls_analysis::kLoopUncountedAttr;
using circt::hls_analysis::kLoopUnrollAttr;
using circt::hls_analysis::kLoopUnrollOffAttr;
using circt::hls_analysis::kLoopUnrollPartialAttr;

namespace {

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
  Builder buildPoint(loop.getContext());
  loop->setAttr(
      kLoopPipelineAttr,
      buildPoint.getArrayAttr({buildPoint.getDictionaryAttr(
          {buildPoint.getNamedAttr("II", buildPoint.getI32IntegerAttr(0)),
           buildPoint.getNamedAttr("source", buildPoint.getStringAttr(
                                                 kLoopPipelineAutoSource))})}));
}

static void addFlattenedParents(AffineForOp loop, unsigned count) {
  if (count == 0)
    return;
  Builder buildPoint(loop.getContext());
  loop->setAttr(
      kLoopFlattenedParentsAttr,
      buildPoint.getI64IntegerAttr(getFlattenedParents(loop) + count));
}

/// One affine or memref load/store: its memory and composed address.
struct Access {
  Operation *op = nullptr;
  Value mem;
  bool isWrite = false;
  AffineMap map;
  SmallVector<Value, 8> operands;
};

static std::optional<Access> getAccess(Operation *op) {
  Access arrayValue;
  arrayValue.op = op;
  MLIRContext *context = op->getContext();
  if (auto load = dyn_cast<AffineLoadOp>(op)) {
    arrayValue.mem = load.getMemRef();
    arrayValue.map = load.getAffineMap();
    arrayValue.operands.assign(load.getMapOperands().begin(),
                               load.getMapOperands().end());
  } else if (auto store = dyn_cast<AffineStoreOp>(op)) {
    arrayValue.mem = store.getMemRef();
    arrayValue.isWrite = true;
    arrayValue.map = store.getAffineMap();
    arrayValue.operands.assign(store.getMapOperands().begin(),
                               store.getMapOperands().end());
  } else if (auto load = dyn_cast<memref::LoadOp>(op)) {
    arrayValue.mem = load.getMemRef();
    arrayValue.map =
        AffineMap::getMultiDimIdentityMap(load.getIndices().size(), context);
    arrayValue.operands.assign(load.getIndices().begin(),
                               load.getIndices().end());
  } else if (auto store = dyn_cast<memref::StoreOp>(op)) {
    arrayValue.mem = store.getMemRef();
    arrayValue.isWrite = true;
    arrayValue.map =
        AffineMap::getMultiDimIdentityMap(store.getIndices().size(), context);
    arrayValue.operands.assign(store.getIndices().begin(),
                               store.getIndices().end());
  } else {
    return std::nullopt;
  }
  fullyComposeAffineMapAndOperands(&arrayValue.map, &arrayValue.operands);
  canonicalizeMapAndOperands(&arrayValue.map, &arrayValue.operands);
  arrayValue.map = simplifyAffineMap(arrayValue.map);
  return arrayValue;
}

static bool sameAddress(const Access &exprValue, const Access &rowValue) {
  return exprValue.mem == rowValue.mem && exprValue.map == rowValue.map &&
         exprValue.operands == rowValue.operands;
}

static bool isInvariantIn(const Access &arrayValue, AffineForOp loop) {
  if (!loop.isDefinedOutsideOfLoop(arrayValue.mem))
    return false;
  return llvm::all_of(arrayValue.operands, [&](Value valueHandle) {
    return loop.isDefinedOutsideOfLoop(valueHandle);
  });
}

/// True if some op inside `loop` may write `mem`, or uses it opaquely.
static bool isMemrefWrittenInLoop(Value mem, AffineForOp loop) {
  bool written = false;
  loop.getBody()->walk([&](Operation *op) {
    if (!llvm::is_contained(op->getOperands(), mem))
      return WalkResult::advance();
    auto eff = dyn_cast<MemoryEffectOpInterface>(op);
    if (!eff) {
      written = true;
      return WalkResult::interrupt();
    }
    SmallVector<MemoryEffects::EffectInstance> effects;
    eff.getEffectsOnValue(mem, effects);
    for (auto &entryValue : effects)
      if (!isa<MemoryEffects::Read>(entryValue.getEffect())) {
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
static bool provablyDisjoint(const Access &exprValue, const Access &rowValue) {
  if (exprValue.operands != rowValue.operands ||
      exprValue.map.getNumResults() != rowValue.map.getNumResults())
    return false;
  for (auto [ex, ey] :
       llvm::zip(exprValue.map.getResults(), rowValue.map.getResults())) {
    AffineExpr dimensionIndex = simplifyAffineExpr(
        ex - ey, exprValue.map.getNumDims(), exprValue.map.getNumSymbols());
    if (auto candidateValue = dyn_cast<AffineConstantExpr>(dimensionIndex))
      if (candidateValue.getValue() != 0)
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
static bool
isPromotableIn(Value mem, AffineForOp loop,
               SmallVector<SmallVector<Access, 4>, 2> *groups = nullptr) {
  bool ok = true, anyStore = false, allDirect = true;
  SmallVector<SmallVector<Access, 4>, 2> found;
  loop.getBody()->walk([&](Operation *op) {
    if (!llvm::is_contained(op->getOperands(), mem))
      return WalkResult::advance();
    std::optional<Access> arrayValue = getAccess(op);
    if (!arrayValue || arrayValue->mem != mem ||
        !isInvariantIn(*arrayValue, loop)) {
      ok = false;
      return WalkResult::interrupt();
    }
    anyStore |= arrayValue->isWrite;
    if (op->getBlock() != loop.getBody())
      allDirect = false;
    auto *globalOp = llvm::find_if(found, [&](auto &grp) {
      return sameAddress(grp.front(), *arrayValue);
    });
    if (globalOp != found.end()) {
      globalOp->push_back(*arrayValue);
    } else {
      for (auto &grp : found)
        if (!provablyDisjoint(grp.front(), *arrayValue)) {
          ok = false;
          return WalkResult::interrupt();
        }
      found.push_back({*arrayValue});
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
    std::optional<Access> arrayValue = getAccess(op);
    if (!arrayValue)
      return cur;
    while (cur && movableOutOf(*arrayValue, cur))
      cur = cur->getParentOfType<AffineForOp>();
    return cur;
  }

  bool movableOutOf(const Access &arrayValue, AffineForOp loop) {
    if (!isInvariantIn(arrayValue, loop))
      return false;
    if (!arrayValue.isWrite && !written(arrayValue.mem, loop))

      return !(floatLoadsPerfect && hasFloatElement(arrayValue.mem));
    return promotable(arrayValue.mem, loop);
  }

  const bool floatLoadsPerfect;

private:
  using Key = std::pair<Value, Operation *>;
  bool written(Value mem, AffineForOp loop) {
    Key key{mem, loop.getOperation()};
    auto it = writtenCache.find(key);
    if (it != writtenCache.end())
      return it->second;
    bool widthValue = isMemrefWrittenInLoop(mem, loop);
    writtenCache[key] = widthValue;
    return widthValue;
  }
  bool promotable(Value mem, AffineForOp loop) {
    Key key{mem, loop.getOperation()};
    auto it = promotableCache.find(key);
    if (it != promotableCache.end())
      return it->second;
    bool portValue = isPromotableIn(mem, loop);
    promotableCache[key] = portValue;
    return portValue;
  }
  DenseMap<Key, bool> writtenCache, promotableCache;
};

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
  uint64_t trip = 1;
  int userPipelineIdx = -1;
  bool pipelineOff = false;
  /// The node is one `hls.uncounted` loop that would have collapsed with its
  /// only child (a perfect pair, constant inner trip count) had it been
  /// counted (step 1); it may still be flattened into that child (step 3).
  bool uncountedPerfect = false;

  bool constInside = true;
  uint64_t maxPath = 1;
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
  std::optional<Access> arrayValue = getAccess(op);
  if (!arrayValue || arrayValue->isWrite || !hasFloatElement(arrayValue->mem))
    return false;
  return !isMemrefWrittenInLoop(arrayValue->mem, inner);
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
      return WalkResult::advance();
    if (isMemoryEffectFree(op))
      return WalkResult::advance();
    if (licm.effectiveLoop(op) != outer)
      return WalkResult::advance();
    if (licm.floatLoadsPerfect && isSinkableFloatLoad(op, outer, inner))
      return WalkResult::advance();
    perfect = false;
    return WalkResult::interrupt();
  });
  if (!perfect)
    return false;

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

static uint64_t saturatingMul(uint64_t arrayValue, uint64_t buildPoint) {
  uint64_t resultValue;
  if (__builtin_mul_overflow(arrayValue, buildPoint, &resultValue))
    return std::numeric_limits<uint64_t>::max();
  return resultValue;
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
      if (auto callSite = dyn_cast<CallOpInterface>(op)) {
        auto callee = dyn_cast_or_null<func::FuncOp>(
            callSite.resolveCallableInTable(&symbolTable));
        if (!callee || callee.isExternal() ||
            !callStack.insert(callee.getOperation()).second)
          return WalkResult::advance();
        collectChildren(callee.getBody(), true, loops, opaqueLoop, callStack);
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
      collectChildren(cur.getRegion(), false, childLoops, opaqueLoop,
                      callStack);
      if (childLoops.size() != 1 || opaqueLoop || childLoops[0].second)
        break;
      AffineForOp child = childLoops[0].first;

      if (!getConstantTripCount(child) || child->hasAttr(kLoopUnrollOffAttr))
        break;
      if (!isPerfectPair(cur, child, licm))
        break;

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
    for (auto [indexValue, loop] : llvm::enumerate(node->chain)) {
      if (node->userPipelineIdx < 0 && isUserPipelined(loop))
        node->userPipelineIdx = static_cast<int>(indexValue);
      if (loop->hasAttr(kLoopUnrollPartialAttr))
        node->userFixed = true;
    }
    node->pipelineOff = node->chain.back()->hasAttr(kLoopPipelineOffAttr);
    for (auto [loop, childViaCall] : childLoops) {

      Operation *owner = nullptr;
      if (auto function = loop->getParentOfType<func::FuncOp>())
        owner = function.getOperation();
      bool pushed = owner && callStack.insert(owner).second;
      node->children.push_back(build(loop, childViaCall, callStack));
      if (pushed)
        callStack.erase(owner);
    }
    if (opaqueLoop) {

      auto opaque = std::make_unique<Node>();
      opaque->dynamic = true;
      opaque->constInside = false;
      node->children.push_back(std::move(opaque));
    }
    node->constInside = !node->dynamic;
    node->hasUserPipeline = node->userPipelineIdx >= 0;
    node->hasUserFixed = node->userFixed;
    uint64_t maxChild = 1;
    for (auto &candidateValue : node->children) {
      node->constInside &= candidateValue->constInside;
      node->hasUserPipeline |= candidateValue->hasUserPipeline;
      node->hasUserFixed |= candidateValue->hasUserFixed;
      maxChild = std::max(maxChild, candidateValue->maxPath);
    }
    node->maxPath = saturatingMul(node->trip, maxChild);
    return node;
  }

  LicmModel &licm;
  SymbolTableCollection symbolTable;
};

/// Vitis LICM on a loop about to be unrolled: ops directly in `loop`'s body
/// whose operands are all defined outside it (or by ops hoisted before them)
/// move before the loop - pure speculatable ops, and loads from a memory the
/// loop never writes. After the unroll, the pipelined parent then holds one
/// such load instead of trip-count copies of it.
static unsigned hoistInvariantOps(AffineForOp loop) {
  DenseSet<Value> invariant;
  auto isInvariantValue = [&](Value valueHandle) {
    return loop.isDefinedOutsideOfLoop(valueHandle) ||
           invariant.contains(valueHandle);
  };
  DenseMap<Value, bool> writtenCache;
  auto writtenInLoop = [&](Value mem) {
    auto it = writtenCache.find(mem);
    if (it != writtenCache.end())
      return it->second;
    bool widthValue = isMemrefWrittenInLoop(mem, loop);
    writtenCache[mem] = widthValue;
    return widthValue;
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
    for (Value resultValue : op.getResults())
      invariant.insert(resultValue);
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

  SmallVector<Value, 4> mems;
  for (Operation &op : loop.getBody()->without_terminator()) {
    std::optional<Access> arrayValue = getAccess(&op);
    if (arrayValue && !llvm::is_contained(mems, arrayValue->mem))
      mems.push_back(arrayValue->mem);
  }
  for (Value mem : mems) {
    SmallVector<SmallVector<Access, 4>, 2> groups;
    if (!isPromotableIn(mem, loop, &groups) || groups.empty())
      continue;
    bool allAffine = llvm::all_of(groups, [](auto &grp) {
      return llvm::all_of(grp, [](const Access &arrayValue) {
        return isa<AffineLoadOp, AffineStoreOp>(arrayValue.op);
      });
    });
    Type elemType = cast<MemRefType>(mem.getType()).getElementType();
    if (!allAffine || !elemType.isIntOrIndexOrFloat())
      continue;
    for (auto &accesses : groups) {
      const Access &first = accesses.front();
      bool anyStore = llvm::any_of(accesses, [](const Access &arrayValue) {
        return arrayValue.isWrite;
      });
      OpBuilder buildPoint(loop);
      Value initialValue;
      if (!first.isWrite) {
        initialValue = AffineLoadOp::create(buildPoint, first.op->getLoc(), mem,
                                            first.map, first.operands);
      } else {

        initialValue =
            arith::ConstantOp::create(buildPoint, loop.getLoc(), elemType,
                                      buildPoint.getZeroAttr(elemType));
      }
      if (!anyStore) {

        for (const Access &arrayValue : accesses) {
          arrayValue.op->getResult(0).replaceAllUsesWith(initialValue);
          arrayValue.op->erase();
        }
        ++promoted;
        continue;
      }
      IRRewriter rewriter(loop.getContext());
      SmallPtrSet<Operation *, 8> accessOps;
      for (const Access &arrayValue : accesses)
        accessOps.insert(arrayValue.op);
      Block *body = loop.getBody();
      DictionaryAttr attrs = loop->getDiscardableAttrDictionary();
      FailureOr<LoopLikeOpInterface> replaced =
          loop.replaceWithAdditionalYields(
              rewriter, initialValue, false,
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
      AffineStoreOp::create(after, loop.getLoc(), loop.getResults().back(), mem,
                            first.map, first.operands);
      ++promoted;
    }
  }
  return loop;
}

static std::string locString(Location loc) {
  std::string stringValue;
  llvm::raw_string_ostream os(stringValue);
  loc.print(os);
  return stringValue;
}

namespace call_depth {

constexpr double kLoadDataNs = 3.25;
constexpr double kLogicNs = 0.99;
constexpr double kSelectNs = 0.69;
constexpr double kVariableShiftNs = 4.42;
constexpr double kConstantMultiplierNs = 5.58;
constexpr unsigned kNarrowMultiplyCycles = 2;
constexpr unsigned kMultiCycleOpCycles = 3;
constexpr unsigned kPortsPerMemory = 2;

/// Carry-chain delay (adder, subtractor, comparator) of a `bits`-wide op.
inline double carryChainNs(unsigned bits) {
  if (bits <= 10)
    return 1.91;
  if (bits <= 16)
    return 2.07;
  if (bits <= 32)
    return 2.55;
  return 3.52;
}

/// Delay of a three-input adder (`TernaryAdder`) of a `bits`-wide result:
/// Vitis groups an add / sub whose only use is another add / sub into one
/// three-input operator that starts when its three inputs are ready (W3
/// review 2 D3, w3r2_k8 `a[i] + a[1023 - i] + a[(i * 7) & 1023]`: the third
/// load arrives 3.25 ns into cycle 2, 3.25 + 4.37 > 7.3 ns, the root add in
/// cycle 3, latency 3, II 16 = 4 calls x depth 4). Values: the mode per width
/// of the `root node of TernaryAdder` delays in the verbose schedule reports
/// of the ground-truth cache and the experiments (i4 3.31 ... i10 3.72, i16
/// 3.90, i32 4.37, i34 4.42 ns), taken at the top of each band.
inline double ternaryAdderNs(unsigned bits) {
  if (bits <= 10)
    return 3.72;
  if (bits <= 16)
    return 3.90;
  if (bits <= 32)
    return 4.37;
  return 4.42;
}

/// Data width of a value for the delay table: an index is an address, which
/// Vitis narrows (w3rev_k2: `i10`); treat it as 32 bits.
inline unsigned bitsOf(Type typeValue) {
  if (typeValue.isIntOrFloat())
    return typeValue.getIntOrFloatBitWidth();
  return 32;
}

/// When a value is ready: the cycle and the nanoseconds used in it.
struct Ready {
  unsigned cycle = 0;
  double ns = 0.0;
  bool operator<(const Ready &opHandle) const {
    return cycle != opHandle.cycle ? cycle < opHandle.cycle : ns < opHandle.ns;
  }
};

class Model {
public:
  explicit Model(double budgetNs) : budgetNs(budgetNs) {}

  /// Depth (latency + 1) of one call of `fn`, or nullopt when `fn` (or a
  /// function it calls) still has loops, calls itself or calls a function
  /// without a body.
  std::optional<unsigned> depth(func::FuncOp function,
                                SymbolTableCollection &symbolTable) {
    auto it = memo.find(function.getOperation());
    if (it != memo.end())
      return it->second;
    if (!onStack.insert(function.getOperation()).second)
      return std::nullopt;
    std::optional<unsigned> dimensionIndex = schedule(function, symbolTable);
    onStack.erase(function.getOperation());
    memo[function.getOperation()] = dimensionIndex;
    return dimensionIndex;
  }

private:
  double budgetNs;
  DenseMap<Operation *, std::optional<unsigned>> memo;
  SmallPtrSet<Operation *, 4> onStack;

  /// `start` plus a combinational delay, moved to the next cycle when it
  /// does not fit the budget.
  Ready chain(Ready start, double delayNs) const {
    if (delayNs <= 0.0)
      return start;
    if (start.ns + delayNs <= budgetNs)
      return {start.cycle, start.ns + delayNs};
    return {start.cycle + 1, delayNs};
  }

  static std::optional<int64_t> constantInt(Value valueHandle) {
    if (auto candidateValue = valueHandle.getDefiningOp<arith::ConstantOp>())
      if (auto loopIndex = dyn_cast<IntegerAttr>(candidateValue.getValue()))
        return loopIndex.getValue().getSExtValue();
    return std::nullopt;
  }

  /// Ready time of a multiply: a constant factor is shifts and adds, two
  /// variables a pipelined multiplier.
  Ready multiply(arith::MulIOp mul, Ready start) const {
    unsigned bits = bitsOf(mul.getType());
    std::optional<int64_t> candidateValue = constantInt(mul.getLhs());
    if (!candidateValue)
      candidateValue = constantInt(mul.getRhs());
    if (candidateValue) {
      uint64_t mag = *candidateValue < 0
                         ? 0 - static_cast<uint64_t>(*candidateValue)
                         : static_cast<uint64_t>(*candidateValue);
      unsigned setBits = llvm::popcount(mag);
      if (setBits <= 1)
        return start;
      if (setBits == 2)
        return chain(start, carryChainNs(bits));
      return chain(start, kConstantMultiplierNs);
    }
    unsigned cycles = bits <= 32 ? kNarrowMultiplyCycles : kMultiCycleOpCycles;
    return {start.cycle + cycles, 0.0};
  }

  /// Latency in whole cycles of a floating-point or math op (the operator
  /// table of --convert-affine-to-loopschedule), 0 for a combinational one.
  static unsigned floatCycles(Operation *op) {
    if (isa<arith::MulFOp>(op))
      return 4;
    if (isa<arith::AddFOp, arith::SubFOp, arith::MaximumFOp, arith::MinimumFOp,
            arith::MaxNumFOp, arith::MinNumFOp, math::FmaOp, math::FloorOp,
            math::CeilOp, math::RoundOp, math::RoundEvenOp, math::TruncOp>(op))
      return 5;
    if (isa<arith::DivFOp, arith::RemFOp>(op))
      return 12;
    if (isa<math::SqrtOp, math::RsqrtOp>(op))
      return 16;
    if (isa<math::AbsFOp, math::AbsIOp, math::CopySignOp>(op))
      return 0;
    if (isa_and_nonnull<math::MathDialect>(op->getDialect()))
      return 20;
    return 0;
  }

  /// For an integer add / sub `op`, the add / sub of the same type that is
  /// only used by `op` and is not itself the root of a three-input adder:
  /// the two form one TernaryAdder (ternaryAdderNs). Null otherwise; index
  /// arithmetic (addresses) is never grouped.
  static Operation *ternaryInner(Operation *op,
                                 const SmallPtrSetImpl<Operation *> &roots) {
    if (!isa<arith::AddIOp, arith::SubIOp>(op) ||
        !isa<IntegerType>(op->getResult(0).getType()))
      return nullptr;
    for (Value valueHandle : op->getOperands()) {
      Operation *dimensionIndex = valueHandle.getDefiningOp();
      if (dimensionIndex && isa<arith::AddIOp, arith::SubIOp>(dimensionIndex) &&
          valueHandle.hasOneUse() &&
          valueHandle.getType() == op->getResult(0).getType() &&
          !roots.contains(dimensionIndex))
        return dimensionIndex;
    }
    return nullptr;
  }

  std::optional<unsigned> schedule(func::FuncOp function,
                                   SymbolTableCollection &symbolTable) {
    DenseMap<Value, Ready> ready;

    std::map<std::tuple<const void *, const void *, unsigned>, unsigned> ports;
    unsigned latency = 0;
    bool unsupported = false;

    SmallPtrSet<Operation *, 8> ternaryRoots;

    auto readyOf = [&](Value valueHandle) {
      auto it = ready.find(valueHandle);
      return it == ready.end() ? Ready{} : it->second;
    };
    auto latest = [&](ValueRange vs) {
      Ready resultValue;
      for (Value valueHandle : vs)
        resultValue = std::max(resultValue, readyOf(valueHandle));
      return resultValue;
    };
    auto latestCycle = [&](ValueRange vs) {
      unsigned candidateValue = 0;
      for (Value valueHandle : vs)
        candidateValue = std::max(candidateValue, readyOf(valueHandle).cycle);
      return candidateValue;
    };

    auto issue = [&](Value mem, unsigned cycle) {
      circt::hls_analysis::StorageRoot root =
          circt::hls_analysis::storageRoot(mem);
      const void *valueKey =
          root.value ? root.value.getAsOpaquePointer() : nullptr;
      const void *globalKey = root.global;
      while (ports[{valueKey, globalKey, cycle}] >= kPortsPerMemory)
        ++cycle;
      ++ports[{valueKey, globalKey, cycle}];
      return cycle;
    };

    function.getBody().walk<WalkOrder::PreOrder>([&](Operation *op) {
      if (isa<LoopLikeOpInterface>(op)) {
        unsupported = true;
        return WalkResult::interrupt();
      }
      Ready start = latest(op->getOperands());
      Ready done = start;
      Value mem;
      ValueRange indices;
      bool isLoad = false, isStore = false;
      if (auto lowerIndex = dyn_cast<AffineLoadOp>(op)) {
        mem = lowerIndex.getMemRef();
        indices = lowerIndex.getMapOperands();
        isLoad = true;
      } else if (auto lowerIndex = dyn_cast<memref::LoadOp>(op)) {
        mem = lowerIndex.getMemRef();
        indices = lowerIndex.getIndices();
        isLoad = true;
      } else if (auto stringValue = dyn_cast<AffineStoreOp>(op)) {
        mem = stringValue.getMemRef();
        indices = stringValue.getMapOperands();
        isStore = true;
      } else if (auto stringValue = dyn_cast<memref::StoreOp>(op)) {
        mem = stringValue.getMemRef();
        indices = stringValue.getIndices();
        isStore = true;
      }
      if (isLoad) {
        unsigned candidateValue = issue(mem, latestCycle(indices));
        done = {candidateValue + 1, kLoadDataNs};
      } else if (isStore) {
        unsigned candidateValue =
            issue(mem, std::max(latestCycle(indices),
                                readyOf(op->getOperand(0)).cycle));
        latency = std::max(latency, candidateValue);
      } else if (auto callSite = dyn_cast<CallOpInterface>(op)) {
        auto callee = dyn_cast_or_null<func::FuncOp>(
            callSite.resolveCallableInTable(&symbolTable));
        std::optional<unsigned> inner;
        if (callee && !callee.isExternal())
          inner = depth(callee, symbolTable);
        if (!inner) {
          unsupported = true;
          return WalkResult::interrupt();
        }
        done = {start.cycle + *inner, 0.0};
        latency = std::max(latency, done.cycle);
      } else if (auto mul = dyn_cast<arith::MulIOp>(op)) {
        done = multiply(mul, start);
      } else if (isa<arith::DivSIOp, arith::DivUIOp, arith::RemSIOp,
                     arith::RemUIOp, arith::CeilDivSIOp, arith::CeilDivUIOp,
                     arith::FloorDivSIOp>(op)) {
        done = {start.cycle + kMultiCycleOpCycles, 0.0};
      } else if (Operation *inner = ternaryInner(op, ternaryRoots)) {

        SmallVector<Value, 3> leaves(inner->getOperands());
        for (Value valueHandle : op->getOperands())
          if (valueHandle.getDefiningOp() != inner)
            leaves.push_back(valueHandle);
        done = chain(latest(leaves),
                     ternaryAdderNs(bitsOf(op->getResult(0).getType())));
        ternaryRoots.insert(op);
      } else if (isa<arith::AddIOp, arith::SubIOp, arith::CmpIOp>(op)) {
        done = chain(start, carryChainNs(bitsOf(op->getOperand(0).getType())));
      } else if (isa<arith::AndIOp, arith::OrIOp, arith::XOrIOp>(op)) {
        done = chain(start, kLogicNs);
      } else if (isa<arith::SelectOp>(op)) {
        done = chain(start, kSelectNs);
      } else if (isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp>(op)) {
        if (!constantInt(op->getOperand(1)))
          done = chain(start, kVariableShiftNs);
      } else if (unsigned candidateValue = floatCycles(op)) {
        done = {start.cycle + candidateValue, 0.0};
      } else if (isa<func::ReturnOp>(op)) {
        latency = std::max(latency, start.cycle);
      } else if (op->hasTrait<OpTrait::IsTerminator>()) {

        if (Operation *parent = op->getParentOp())
          if (parent->getNumResults() == op->getNumOperands())
            for (auto [resultValue, valueHandle] :
                 llvm::zip(parent->getResults(), op->getOperands()))
              ready[resultValue] =
                  std::max(readyOf(resultValue), readyOf(valueHandle));
      }

      for (Value resultValue : op->getResults())
        if (!ready.count(resultValue))
          ready[resultValue] = done;
      return WalkResult::advance();
    });
    if (unsupported)
      return std::nullopt;
    return latency + 1;
  }
};

} // namespace call_depth

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

  Option<double> clockPeriodNs{
      *this, "clock-period-ns",
      llvm::cl::desc("Target clock period in ns for the depth of a call in "
                     "a pipelined loop (Vitis create_clock; default 10, the "
                     "ground-truth configuration)"),
      llvm::cl::init(10.0)};
  Option<double> clockUncertaintyPct{
      *this, "clock-uncertainty-pct",
      llvm::cl::desc("Clock uncertainty in percent of the period (Vitis "
                     "default 27)"),
      llvm::cl::init(27.0)};

  StringRef getArgument() const final { return "auto-pipeline-unroll"; }
  StringRef getDescription() const final {
    return "Vitis automatic pipeline / unroll / flatten decision "
           "(config_compile -pipeline_loops)";
  }

  void getDependentDialects(DialectRegistry &targetRegistry) const override {
    targetRegistry.insert<arith::ArithDialect, memref::MemRefDialect>();
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
      Builder buildPoint(loop.getContext());
      if (factor == 1) {
        loop->setAttr(kLoopUnrollPartialAttr, buildPoint.getI64IntegerAttr(1));
        remark(loop.getLoc(), "user unroll: factor 1, the loop is never "
                              "auto-unrolled into a parent pipeline");
        continue;
      }
      if (factor == 0 || (trip && factor >= *trip)) {
        if (!trip) {
          remark(loop.getLoc(), "user unroll: dynamic trip count, left rolled");
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
    Builder buildPoint(loop.getContext());
    auto markMain = [&](AffineForOp main) {
      main->setAttr(kLoopUnrollPartialAttr,
                    buildPoint.getI64IntegerAttr(static_cast<int64_t>(factor)));
    };

    if (llvm::hasSingleElement(loop.getBody()->getOperations())) {
      markMain(loop);
      return;
    }

    Block *block = loop->getBlock();
    Operation *prev = loop->getPrevNode();
    Operation *next = loop->getNextNode();
    int64_t step = loop.getStepAsInt();

    loop->setAttr(kUnrollPendingAttr, buildPoint.getUnitAttr());
    if (failed(loopUnrollByFactor(loop, factor))) {

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
        markMain(forOp);
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
      } else if (auto callSite = dyn_cast<CallOpInterface>(op)) {
        auto callee = dyn_cast_or_null<func::FuncOp>(
            callSite.resolveCallableInTable(&symbolTable));
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

    if (auto owner = pipelined->getParentOfType<func::FuncOp>())
      visitedCallees.insert(owner.getOperation());
    collectInner(pipelined.getRegion(), inner, visitedCallees, symbolTable);
    Builder buildPoint(pipelined.getContext());
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
      remark(loop.getLoc(), "unrolling loop completely with a factor of " +
                                Twine(*trip) +
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
      record.push_back(buildPoint.getDictionaryAttr(
          {buildPoint.getNamedAttr("factor", buildPoint.getI64IntegerAttr(
                                                 static_cast<int64_t>(*trip))),
           buildPoint.getNamedAttr("loc", loc)}));
    }
    if (!record.empty())
      pipelined->setAttr(kLoopAutoUnrolledAttr,
                         buildPoint.getArrayAttr(record));
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

  void decide(Node &elementCount, SymbolTableCollection &symbolTable) {
    if (elementCount.chain.empty())
      return;
    unsigned T = pipelineLoops;
    if (elementCount.userPipelineIdx >= 0) {
      AffineForOp useValue = elementCount.chain[elementCount.userPipelineIdx];
      elementCount.tagged = useValue;
      addFlattenedParents(useValue, elementCount.userPipelineIdx);
      remark(useValue.getLoc(), "user pipeline: unrolling everything inside, " +
                                    Twine(elementCount.userPipelineIdx) +
                                    " perfect parent(s) flattened into it");
      unrollInside(useValue, symbolTable);

      elementCount.tagged =
          promotePipelined ? promoteOutOfPipeline(useValue) : useValue;
      elementCount.chain[elementCount.userPipelineIdx] = elementCount.tagged;
      return;
    }
    bool feasible = T > 0 && !elementCount.pipelineOff;
    for (auto &candidateValue : elementCount.children)
      feasible &= candidateValue->constInside && candidateValue->maxPath <= T &&
                  !candidateValue->hasUserPipeline &&
                  !candidateValue->hasUserFixed;
    if (feasible) {
      AffineForOp portValue = elementCount.chain.back();
      elementCount.tagged = portValue;
      tagAutoPipeline(portValue);
      addFlattenedParents(portValue, elementCount.chain.size() - 1);
      remark(
          portValue.getLoc(),
          "automatically set the pipeline for the loop (trip " +
              (elementCount.dynamic ? Twine("?") : Twine(elementCount.trip)) +
              ", " + Twine(elementCount.chain.size() - 1) +
              " perfect parent(s) flattened, " +
              Twine(elementCount.children.size()) +
              " inner loop(s) to unroll)");
      unrollInside(portValue, symbolTable);
      elementCount.tagged =
          promotePipelined ? promoteOutOfPipeline(portValue) : portValue;
      elementCount.chain.back() = elementCount.tagged;
      return;
    }
    for (auto &candidateValue : elementCount.children)
      if (!candidateValue->viaCall)
        decide(*candidateValue, symbolTable);

    if (elementCount.children.size() != 1)
      return;
    Node &candidateValue = *elementCount.children.front();

    if (candidateValue.viaCall || candidateValue.chain.empty() ||
        !candidateValue.tagged ||
        (elementCount.dynamic && !elementCount.uncountedPerfect) ||
        candidateValue.dynamic)
      return;
    if (candidateValue.chain.front()->getBlock() !=
        elementCount.chain.back().getBody())
      return;
    addFlattenedParents(candidateValue.tagged, elementCount.chain.size());
    elementCount.tagged = candidateValue.tagged;
    remark(elementCount.chain.front().getLoc(),
           "flattening the loop (and " + Twine(elementCount.chain.size() - 1) +
               " perfect inner loop(s)) into the pipelined loop at " +
               locString(candidateValue.tagged.getLoc()));
  }

  /// The functions with a body, every caller before its callees (reverse
  /// post-order of the call graph; a call cycle is cut where the walk meets
  /// it). With calls kept (`#pragma HLS inline off`, W3), Vitis decides a
  /// caller loop against the callee's loops as they are written, before the
  /// callee's own decision changes them (VITIS_NOTES.md N14 R7: `inl_f2` a
  /// 16-trip callee loop is unrolled into the pipelined caller loop; corpus
  /// attn_breakdown_op1 and kernel w3h_cb_nest256: a callee nest of 8 x 8 x 4
  /// trips keeps the 8-trip caller loop sequential, the callee pipelines its
  /// own flattened loop). Deciding the callee first would unroll its inner
  /// loops and let the caller pass the trip-count test on what is left.
  static SmallVector<func::FuncOp>
  callersFirst(ModuleOp rootModule, SymbolTableCollection &symbolTable) {
    SmallVector<func::FuncOp> postOrder;
    DenseSet<Operation *> visited;
    std::function<void(func::FuncOp)> visit = [&](func::FuncOp function) {
      if (!visited.insert(function.getOperation()).second)
        return;
      function.walk([&](CallOpInterface callSite) {
        auto callee = dyn_cast_or_null<func::FuncOp>(
            callSite.resolveCallableInTable(&symbolTable));
        if (callee && !callee.isExternal())
          visit(callee);
      });
      postOrder.push_back(function);
    };
    for (auto function : rootModule.getOps<func::FuncOp>())
      if (!function.isExternal())
        visit(function);
    return SmallVector<func::FuncOp>(llvm::reverse(postOrder));
  }

  /// Whether `fn`, or a function it calls, still holds a loop.
  static bool hasLoops(func::FuncOp function,
                       SymbolTableCollection &symbolTable,
                       SmallPtrSetImpl<Operation *> &stack) {
    if (!stack.insert(function.getOperation()).second)
      return false;
    bool found = false;
    function.walk([&](Operation *op) {
      if (isa<LoopLikeOpInterface>(op)) {
        found = true;
        return WalkResult::interrupt();
      }
      if (auto callSite = dyn_cast<CallOpInterface>(op))
        if (auto callee = dyn_cast_or_null<func::FuncOp>(
                callSite.resolveCallableInTable(&symbolTable)))
          if (!callee.isExternal() && hasLoops(callee, symbolTable, stack)) {
            found = true;
            return WalkResult::interrupt();
          }
      return WalkResult::advance();
    });
    stack.erase(function.getOperation());
    return found;
  }

  /// Cycles one call of the loop-free `fn` holds its instance: its accesses
  /// to each memory (an argument, a local array, a global), two per cycle
  /// (a memory's two ports), the busiest memory deciding; at least 1. A
  /// nested call counts with its own occupancy.
  static unsigned occupancy(func::FuncOp function,
                            SymbolTableCollection &symbolTable,
                            SmallPtrSetImpl<Operation *> &stack) {
    if (!stack.insert(function.getOperation()).second)
      return 1;
    unsigned cycles = 1;
    llvm::MapVector<std::pair<Value, Operation *>, unsigned> perMemory;

    std::set<
        std::tuple<const void *, bool, const void *, std::vector<const void *>>>
        seen;
    function.walk([&](Operation *op) {
      Value mem;
      bool isWrite = false;
      Attribute map;
      ValueRange indices;
      if (auto lowerIndex = dyn_cast<AffineLoadOp>(op)) {
        mem = lowerIndex.getMemRef();
        map = lowerIndex.getMapAttr();
        indices = lowerIndex.getMapOperands();
      } else if (auto stringValue = dyn_cast<AffineStoreOp>(op)) {
        mem = stringValue.getMemRef();
        isWrite = true;
        map = stringValue.getMapAttr();
        indices = stringValue.getMapOperands();
      } else if (auto lowerIndex = dyn_cast<memref::LoadOp>(op)) {
        mem = lowerIndex.getMemRef();
        indices = lowerIndex.getIndices();
      } else if (auto stringValue = dyn_cast<memref::StoreOp>(op)) {
        mem = stringValue.getMemRef();
        isWrite = true;
        indices = stringValue.getIndices();
      } else if (auto callSite = dyn_cast<CallOpInterface>(op)) {
        if (auto callee = dyn_cast_or_null<func::FuncOp>(
                callSite.resolveCallableInTable(&symbolTable)))
          if (!callee.isExternal())
            cycles = std::max(cycles, occupancy(callee, symbolTable, stack));
        return;
      }
      if (!mem)
        return;
      std::vector<const void *> address;
      for (Value valueHandle : indices)
        address.push_back(valueHandle.getAsOpaquePointer());
      const void *memKey = mem.getAsOpaquePointer();
      const void *mapKey = map ? map.getAsOpaquePointer() : nullptr;

      if (!isWrite && seen.count({memKey, true, mapKey, address}))
        return;
      if (!seen.insert({memKey, isWrite, mapKey, std::move(address)}).second)
        return;
      circt::hls_analysis::StorageRoot root =
          circt::hls_analysis::storageRoot(mem);
      ++perMemory[{root.value, root.global}];
    });
    for (auto &[key, elementCount] : perMemory)
      cycles = std::max(cycles, (elementCount + 1) / 2);
    stack.erase(function.getOperation());
    return cycles;
  }

  /// The call boundary after the decisions (VITIS_NOTES.md N14 R7): a loop
  /// that is not pipelined and calls a kept function that still has loops
  /// gets `hls.call_boundary` (Vitis pipelines the callee's loops in the
  /// callee and leaves the caller loop sequential: w3h_cb_nest256,
  /// attn_breakdown_op1 `VITIS_LOOP_232_1`); a call inside a pipelined loop
  /// gets `hls.call_occupancy` (its callee is loop-free by then, R7) and
  /// `hls.call_depth` (the states of one call, for calls that share an
  /// instance; N14 R2 in a pipelined loop).
  static void markCallBoundaries(ModuleOp rootModule,
                                 SymbolTableCollection &symbolTable,
                                 call_depth::Model &depthModel) {
    rootModule.walk([&](CallOpInterface callSite) {
      auto callee = dyn_cast_or_null<func::FuncOp>(
          callSite.resolveCallableInTable(&symbolTable));
      if (!callee || callee.isExternal())
        return;
      auto loop = callSite->getParentOfType<AffineForOp>();
      if (!loop)
        return;
      OpBuilder buildPoint(callSite.getContext());
      SmallPtrSet<Operation *, 8> stack;
      if (loop->hasAttr(kLoopPipelineAttr)) {
        unsigned occ = occupancy(callee, symbolTable, stack);
        callSite->setAttr(kCallOccupancyAttr,
                          buildPoint.getI64IntegerAttr(occ));
        if (std::optional<unsigned> dimensionIndex =
                depthModel.depth(callee, symbolTable))
          callSite->setAttr(
              kCallDepthAttr,
              buildPoint.getI64IntegerAttr(std::max(*dimensionIndex, occ)));
        return;
      }
      if (!loop->hasAttr(kLoopCallBoundaryAttr) &&
          hasLoops(callee, symbolTable, stack))
        loop->setAttr(kLoopCallBoundaryAttr,
                      buildPoint.getStringAttr(callee.getSymName()));
    });
  }

  void runOnOperation() override {
    ModuleOp rootModule = getOperation();
    SymbolTableCollection symbolTable;

    rootModule.walk([&](AffineForOp loop) {
      if (isAutoPipelineTag(loop->getAttr(kLoopPipelineAttr)))
        loop->removeAttr(kLoopPipelineAttr);
      loop->removeAttr(kLoopFlattenedParentsAttr);
      loop->removeAttr(kLoopAutoUnrolledAttr);
      loop->removeAttr(kLoopCallBoundaryAttr);
    });
    rootModule.walk([&](CallOpInterface callSite) {
      callSite->removeAttr(kCallOccupancyAttr);
      callSite->removeAttr(kCallDepthAttr);
    });
    for (auto func : rootModule.getOps<func::FuncOp>())
      func->removeAttr(circt::hls_analysis::kPortBoundArgsAttr);

    for (auto func : rootModule.getOps<func::FuncOp>())
      if (!func.isExternal())
        applyUserUnrolls(func);

    for (func::FuncOp func : callersFirst(rootModule, symbolTable)) {
      LicmModel licm(floatLoadsPerfect);
      Forest forest(licm);

      SmallVector<AffineForOp, 8> roots;
      func.getBody().walk<WalkOrder::PreOrder>([&](AffineForOp loop) {
        roots.push_back(loop);
        return WalkResult::skip();
      });
      SmallVector<std::unique_ptr<Node>> nodes;
      SmallPtrSet<Operation *, 4> callStack;
      callStack.insert(func.getOperation());
      for (AffineForOp loop : roots)
        nodes.push_back(forest.build(loop, false, callStack));
      for (auto &node : nodes)
        decide(*node, symbolTable);
    }
    call_depth::Model depthModel(clockPeriodNs *
                                 (1.0 - clockUncertaintyPct / 100.0));
    markCallBoundaries(rootModule, symbolTable, depthModel);
    markPortBoundArgs(rootModule);
  }

  /// `hls.port_bound_args` on every function whose memref arguments name an
  /// array that crosses a module instantiated at more than one place
  /// (VITIS_NOTES.md N14 R6; W3 review D2: w3rev_k3 / k3b / w3fx_d2_conc).
  /// MemrefBankClassification gives such an argument two ports instead of
  /// the replicable pool, so the callee's loop II rises as in Vitis (rd3
  /// II 2). The instances are counted after the unroll decisions, on the
  /// final call sites.
  static void markPortBoundArgs(ModuleOp rootModule) {
    using namespace circt::hls_analysis;
    InstanceModel model = computeInstances(rootModule);
    OpBuilder buildPoint(rootModule.getContext());
    for (auto function : rootModule.getOps<func::FuncOp>()) {
      if (function.isExternal())
        continue;
      SmallVector<int64_t> bound;
      for (BlockArgument arg : function.getArguments())
        if (isa<BaseMemRefType>(arg.getType()) &&
            model.argReachesSharedModule(function, arg.getArgNumber()))
          bound.push_back(arg.getArgNumber());
      if (!bound.empty())
        function->setAttr(kPortBoundArgsAttr,
                          buildPoint.getI64ArrayAttr(bound));
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
