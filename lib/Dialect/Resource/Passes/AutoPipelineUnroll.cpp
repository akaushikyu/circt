

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/AutoPipelineUnroll.h"
#include "../Plugins/Builtin/Builtins.h"
#include "circt/Dialect/Resource/Config/ConfigUtils.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/DoWhileFlatten.h"
#include "circt/Dialect/Resource/Passes/FloatOps.h"
#include "circt/Dialect/Resource/Passes/FoldUnrolledGuards.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "circt/Dialect/Resource/Plugins/Registry.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "circt/Dialect/Resource/Passes/AffineUnroll.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/Diagnostics.h"
#include "mlir/IR/IRMapping.h"
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
using circt::hls_analysis::kLoopFlattenRefusedAttr;
using circt::hls_analysis::kLoopPipelineAttr;
using circt::hls_analysis::kLoopPipelineAutoSource;
using circt::hls_analysis::kLoopPipelineOffAttr;
using circt::hls_analysis::kLoopUncountedAttr;
using circt::hls_analysis::kLoopUnrollAttr;
using circt::hls_analysis::kLoopUnrollOffAttr;
using circt::hls_analysis::kLoopUnrollPartialAttr;
using circt::hls_analysis::kLoopUnrollRuntimeGuardedAttr;

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
static bool isUserPipelined(Operation *loop) {
  Attribute attr = loop->getAttr(kLoopPipelineAttr);
  return attr && !isAutoPipelineTag(attr) &&
         !loop->hasAttr(kLoopPipelineOffAttr);
}

/// User unroll factor of `loop`; 0 = complete; nullopt = no pragma.
static std::optional<uint64_t> userUnrollFactor(Operation *loop) {
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

static void tagAutoPipeline(Operation *loop) {
  Builder buildPoint(loop->getContext());
  loop->setAttr(
      kLoopPipelineAttr,
      buildPoint.getArrayAttr({buildPoint.getDictionaryAttr(
          {buildPoint.getNamedAttr("II", buildPoint.getI32IntegerAttr(0)),
           buildPoint.getNamedAttr("source", buildPoint.getStringAttr(
                                                 kLoopPipelineAutoSource))})}));
}

/// A loop whose trip count is not known when the decision is made: an
/// `scf.for` whose bounds are no affine symbols (a bound loaded inside an
/// enclosing loop, `count = n[j]; while (count >= 16)`, which cgeist cannot
/// raise to an affine.for) or an `scf.while` (an exit that depends on data).
/// Vitis pipelines such a loop like any other when every loop inside it has
/// a constant trip count and the trip-count products inside it are <= T
/// (VITIS_NOTES.md N53: kernels o72_fa / o72_fe / o72_wa / o72_xw /
/// shafix_v4, trip `?` or `1 ~ 268435456`, inner and callee loops unrolled).
/// A constant-bound scf.for is raised to an affine.for by --vitis-fold
/// (raise-counted-loops) before this pass.
static bool isRuntimeLoop(Operation *op) {
  return isa<scf::ForOp, scf::WhileOp>(op);
}

static void markFlattenRefused(AffineForOp loop) {
  loop->setAttr(kLoopFlattenRefusedAttr, UnitAttr::get(loop.getContext()));
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

/// True if some op inside `loop` (an affine.for or a runtime loop) may write
/// `mem`, or uses it opaquely.
static bool isMemrefWrittenInLoop(Value mem, Operation *loop) {
  bool written = false;
  loop->walk([&](Operation *op) {
    if (op == loop)
      return WalkResult::advance();
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

/// `e` as (the expression without its constant term, the constant term):
/// `d0 * 2 + 5` is (d0 * 2, 5), `7` is (null, 7), `d0` is (d0, 0). Simplified
/// affine expressions keep the constant as the right operand of the outermost
/// addition.
static std::pair<AffineExpr, int64_t> splitConstantTerm(AffineExpr entryValue) {
  if (auto candidateValue = dyn_cast<AffineConstantExpr>(entryValue))
    return {AffineExpr(), candidateValue.getValue()};
  if (auto add = dyn_cast<AffineBinaryOpExpr>(entryValue))
    if (add.getKind() == AffineExprKind::Add)
      if (auto candidateValue = dyn_cast<AffineConstantExpr>(add.getRHS()))
        return {add.getLHS(), candidateValue.getValue()};
  return {entryValue, 0};
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
    auto [vx, cx] = splitConstantTerm(ex);
    auto [vy, cy] = splitConstantTerm(ey);
    if (vx == vy && cx != cy)
      return true;
  }
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

/// Whether `v` names (part of) `mem` through casts, views and pointer
/// conversions of it (a `memref.cast` passed to a callee that reads the
/// element: cgeist's `hls::stream::write(const T &)` argument), without being
/// `mem` itself.
static bool isAliasOf(Value valueHandle, Value mem) {
  for (unsigned depth = 0; depth < 8 && valueHandle != mem; ++depth) {
    if (!isa<BaseMemRefType, LLVM::LLVMPointerType>(valueHandle.getType()))
      return false;
    Operation *def = valueHandle.getDefiningOp();
    if (!def || def->getNumOperands() == 0 || getAccess(def) ||
        isa<CallOpInterface>(def))
      return false;
    valueHandle = def->getOperand(0);
    if (valueHandle == mem)
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

  std::optional<SmallVector<AffineExpr, 4>> shared;
  bool uniform = true;
  DenseMap<AffineMap, unsigned> groupOfMap;
  std::set<SmallVector<int64_t, 4>> seenConstants;
  auto nonConstantParts = [](const Access &exprValue) {
    SmallVector<AffineExpr, 4> parts;
    for (AffineExpr entryValue : exprValue.map.getResults())
      parts.push_back(splitConstantTerm(entryValue).first);
    return parts;
  };
  loop.getBody()->walk([&](Operation *op) {
    if (llvm::any_of(op->getOperands(), [&](Value valueHandle) {
          return valueHandle != mem && isAliasOf(valueHandle, mem);
        })) {
      ok = false;
      return WalkResult::interrupt();
    }
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
    if (uniform) {
      SmallVector<AffineExpr, 4> parts = nonConstantParts(*arrayValue);
      if (!shared)
        shared = parts;
      if (*shared == parts &&
          (found.empty() ||
           found.front().front().operands == arrayValue->operands)) {
        auto it = groupOfMap.find(arrayValue->map);
        if (it != groupOfMap.end()) {
          found[it->second].push_back(*arrayValue);
          return WalkResult::advance();
        }

        SmallVector<int64_t, 4> constants;
        for (AffineExpr entryValue : arrayValue->map.getResults())
          constants.push_back(splitConstantTerm(entryValue).second);
        if (seenConstants.insert(constants).second) {
          groupOfMap[arrayValue->map] = found.size();
          found.push_back({*arrayValue});
          return WalkResult::advance();
        }
      }
      uniform = false;
    }
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
  /// The node is one runtime loop (isRuntimeLoop: scf.for / scf.while; the
  /// chain is empty): a pipeline candidate of its own, never collapsed or
  /// flattened with another loop, dynamic for every loop around it.
  Operation *runtimeLoop = nullptr;
  /// The runtime loop is an scf.for whose body is a perfect nest over its
  /// only child, an affine chain of constant trip counts
  /// (isPerfectRuntimePair): flattened into that chain's pipeline.
  bool perfectRuntime = false;
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
  /// The loops around `tagged` Vitis does not flatten into it (N96,
  /// doWhileParents): an automatic pipeline's unroll makes their next index
  /// a subscript.
  llvm::SmallPtrSet<Operation *, 4> doWhileParents;
  /// Some loop of the node was not flattened into `tagged` for that reason:
  /// no loop around the node is flattened into it either.
  bool flattenRefused = false;
};

/// A read-only load of a floating-point element directly in `outer`'s body
/// from a memory `inner` never writes. cgeist's own LICM moves inner-invariant
/// loads there (`lb[i]` of `lo[i][j] = la[i][j] * lb[i]` ends up before the j
/// loop in the MLIR), and a source may hold it there too (`float t = lb[i];`
/// before the j loop, pf_srchoist_m8_n64), but Vitis converts such a nest
/// into a perfect one and flattens it (see the file header), so under
/// float-loads-perfect the load is judged as if it were in the inner loop.
static bool isSinkableFloatLoad(Operation *op, Block *outerBody,
                                AffineForOp inner) {
  if (op->getBlock() != outerBody)
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
    if (licm.floatLoadsPerfect &&
        isSinkableFloatLoad(op, outer.getBody(), inner))
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

/// Does the runtime-trip scf.for `outer` (isRuntimeLoop) form a perfect nest
/// with `inner`, the only loop directly in its body? Judged as isPerfectPair
/// judges an affine pair, with what LICM cannot see through an scf.for
/// treated conservatively: a memory operation in outer's body (other than a
/// sinkable float load) makes the nest imperfect, and so does an access of
/// the inner nest that LICM / promotion move out of `inner` unless it is a
/// read of a memory outer never writes at an address that does not change
/// with outer (hoisted past outer as well). Vitis flattens such a nest into
/// `inner`'s pipeline (VITIS_NOTES.md N53 (b): o72r_pf / pf2 / pf3 / pf4 /
/// acc / s65, o72f_pf7: flatten `VITIS_LOOP_<outer>`, trip `?`); a distance-1
/// recurrence of the inner loop (`buf[i][k] = buf[i][k-1] ..`, o72r_raw /
/// o72f_rawm) is not flattened, as for an affine nest (o72f_rawc; O8, not
/// modelled for either).
static bool isPerfectRuntimePair(scf::ForOp outer, AffineForOp inner,
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
    if (op->getNumRegions() > 0 || isMemoryEffectFree(op))
      return WalkResult::advance();
    if (licm.floatLoadsPerfect &&
        isSinkableFloatLoad(op, outer.getBody(), inner))
      return WalkResult::advance();
    perfect = false;
    return WalkResult::interrupt();
  });
  if (!perfect)
    return false;
  auto definedOutside = [&](Value valueHandle) {
    return !outer->isAncestor(valueHandle.getParentRegion()->getParentOp());
  };
  inner->walk([&](Operation *op) {
    std::optional<Access> arrayValue = getAccess(op);
    if (!arrayValue)
      return WalkResult::advance();
    AffineForOp eff = licm.effectiveLoop(op);
    if (eff && inner->isAncestor(eff))
      return WalkResult::advance();
    bool pastOuter = !arrayValue->isWrite && definedOutside(arrayValue->mem) &&
                     llvm::all_of(arrayValue->operands, definedOutside) &&
                     !isMemrefWrittenInLoop(arrayValue->mem, outer);
    if (pastOuter)
      return WalkResult::advance();
    perfect = false;
    return WalkResult::interrupt();
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
  /// calls into their callees: the affine.for loops in `loops`, the runtime
  /// loops (isRuntimeLoop) in `runtimeLoops`. `opaqueLoop` is set when any
  /// other loop is met.
  void
  collectChildren(Region &region, bool viaCall,
                  SmallVector<std::pair<AffineForOp, bool>, 4> &loops,
                  SmallVector<std::pair<Operation *, bool>, 2> &runtimeLoops,
                  bool &opaqueLoop, SmallPtrSetImpl<Operation *> &callStack) {
    region.walk<WalkOrder::PreOrder>([&](Operation *op) {
      if (auto forOp = dyn_cast<AffineForOp>(op)) {
        loops.emplace_back(forOp, viaCall);
        return WalkResult::skip();
      }
      if (isRuntimeLoop(op)) {
        runtimeLoops.emplace_back(op, viaCall);
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
        collectChildren(callee.getBody(), true, loops, runtimeLoops, opaqueLoop,
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
    SmallVector<std::pair<Operation *, bool>, 2> runtimeChildren;
    bool opaqueLoop = false;
    while (true) {
      childLoops.clear();
      runtimeChildren.clear();
      opaqueLoop = false;
      collectChildren(cur.getRegion(), false, childLoops, runtimeChildren,
                      opaqueLoop, callStack);
      if (childLoops.size() != 1 || opaqueLoop || !runtimeChildren.empty() ||
          childLoops[0].second)
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
    buildChildren(*node, childLoops, runtimeChildren, callStack);
    if (opaqueLoop) {

      auto opaque = std::make_unique<Node>();
      opaque->dynamic = true;
      opaque->constInside = false;
      node->children.push_back(std::move(opaque));
    }
    node->hasUserPipeline = node->userPipelineIdx >= 0;
    summarize(*node);
    return node;
  }

  /// A runtime loop (isRuntimeLoop) and the loops inside it: it is decided
  /// like a one-loop chain whose trip count is unknown (N53), so it is
  /// dynamic for every loop around it, and the loops of all its regions (an
  /// scf.while's condition region included) are its children.
  std::unique_ptr<Node> buildRuntime(Operation *loop, bool viaCall,
                                     SmallPtrSetImpl<Operation *> &callStack) {
    auto node = std::make_unique<Node>();
    node->viaCall = viaCall;
    node->runtimeLoop = loop;
    node->dynamic = true;
    node->pipelineOff = loop->hasAttr(kLoopPipelineOffAttr);
    node->hasUserPipeline = isUserPipelined(loop);
    SmallVector<std::pair<AffineForOp, bool>, 4> childLoops;
    SmallVector<std::pair<Operation *, bool>, 2> runtimeChildren;
    bool opaqueLoop = false;
    for (Region &region : loop->getRegions())
      collectChildren(region, false, childLoops, runtimeChildren, opaqueLoop,
                      callStack);
    if (auto forOp = dyn_cast<scf::ForOp>(loop))
      node->perfectRuntime =
          !node->pipelineOff && !opaqueLoop && runtimeChildren.empty() &&
          childLoops.size() == 1 && !childLoops[0].second &&
          getConstantTripCount(childLoops[0].first) &&
          !childLoops[0].first->hasAttr(kLoopUnrollOffAttr) &&
          isPerfectRuntimePair(forOp, childLoops[0].first, licm);
    buildChildren(*node, childLoops, runtimeChildren, callStack);
    if (opaqueLoop) {
      auto opaque = std::make_unique<Node>();
      opaque->dynamic = true;
      opaque->constInside = false;
      node->children.push_back(std::move(opaque));
    }
    summarize(*node);
    return node;
  }

  /// The subtrees of the loops collectChildren found, affine loops first.
  void buildChildren(Node &node,
                     ArrayRef<std::pair<AffineForOp, bool>> childLoops,
                     ArrayRef<std::pair<Operation *, bool>> runtimeChildren,
                     SmallPtrSetImpl<Operation *> &callStack) {

    auto withOwner = [&](Operation *loop, auto buildFn) {
      Operation *owner = nullptr;
      if (auto fn = loop->getParentOfType<func::FuncOp>())
        owner = fn.getOperation();
      bool pushed = owner && callStack.insert(owner).second;
      node.children.push_back(buildFn());
      if (pushed)
        callStack.erase(owner);
    };
    for (auto [loop, childViaCall] : childLoops)
      withOwner(loop, [&] { return build(loop, childViaCall, callStack); });
    for (auto [loop, childViaCall] : runtimeChildren)
      withOwner(loop,
                [&] { return buildRuntime(loop, childViaCall, callStack); });
  }

  /// The properties derived over the subtree (hasUserPipeline holds the
  /// node's own on entry).
  static void summarize(Node &node) {
    node.constInside = !node.dynamic;
    node.hasUserFixed = node.userFixed;
    uint64_t maxChild = 1;
    for (auto &candidateValue : node.children) {
      node.constInside &= candidateValue->constInside;
      node.hasUserPipeline |= candidateValue->hasUserPipeline;
      node.hasUserFixed |= candidateValue->hasUserFixed;
      maxChild = std::max(maxChild, candidateValue->maxPath);
    }
    node.maxPath = saturatingMul(node.trip, maxChild);
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
  std::optional<uint64_t> trips = getConstantTripCount(loop);
  bool runsAtLeastOnce = trips && *trips >= 1;

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

    SmallVector<const SmallVector<Access, 4> *> carried;
    SmallVector<Value> inits;
    for (auto &accesses : groups) {
      const Access &first = accesses.front();
      bool anyStore = llvm::any_of(accesses, [](const Access &arrayValue) {
        return arrayValue.isWrite;
      });
      OpBuilder buildPoint(loop);
      Value init;
      if (!first.isWrite || !runsAtLeastOnce) {

        init = AffineLoadOp::create(buildPoint, first.op->getLoc(), mem,
                                    first.map, first.operands);
      } else {

        init = arith::ConstantOp::create(buildPoint, loop.getLoc(), elemType,
                                         buildPoint.getZeroAttr(elemType));
      }
      if (!anyStore) {

        for (const Access &arrayValue : accesses) {
          arrayValue.op->getResult(0).replaceAllUsesWith(init);
          arrayValue.op->erase();
        }
        ++promoted;
        continue;
      }
      carried.push_back(&accesses);
      inits.push_back(init);
    }
    if (carried.empty())
      continue;
    IRRewriter rewriter(loop.getContext());
    DenseMap<Operation *, unsigned> carriedIndexOf;
    for (auto [loopIndex, accesses] : llvm::enumerate(carried))
      for (const Access &arrayValue : *accesses)
        carriedIndexOf[arrayValue.op] = loopIndex;
    Block *body = loop.getBody();
    DictionaryAttr attrs = loop->getDiscardableAttrDictionary();
    FailureOr<LoopLikeOpInterface> replaced = loop.replaceWithAdditionalYields(
        rewriter, inits, false,
        [&](OpBuilder &, Location, ArrayRef<BlockArgument> newArgs) {
          SmallVector<Value> cur(newArgs.begin(), newArgs.end());
          SmallVector<Operation *> toErase;
          for (Operation &op : body->without_terminator()) {
            auto it = carriedIndexOf.find(&op);
            if (it == carriedIndexOf.end())
              continue;
            if (auto store = dyn_cast<AffineStoreOp>(op))
              cur[it->second] = store.getValueToStore();
            else
              op.getResult(0).replaceAllUsesWith(cur[it->second]);
            toErase.push_back(&op);
          }
          for (Operation *op : toErase)
            op->erase();
          return cur;
        });
    if (failed(replaced))
      continue;
    loop = cast<AffineForOp>(replaced->getOperation());
    loop->setDiscardableAttrs(attrs);

    unsigned firstResult = loop.getNumResults() - carried.size();
    for (auto [loopIndex, accesses] : llvm::enumerate(carried)) {
      const Access &first = accesses->front();
      OpBuilder after(loop.getContext());
      after.setInsertionPointAfter(loop);
      AffineStoreOp::create(after, loop.getLoc(),
                            loop.getResult(firstResult + loopIndex), mem,
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

using circt::hlsest::CallDepthConfig;
using circt::hlsest::SchedulingConfig;

/// When a value is ready: the cycle and the nanoseconds used in it.
struct Ready {
  unsigned cycle = 0;
  double ns = 0.0;
  bool operator<(const Ready &o) const {
    return cycle != o.cycle ? cycle < o.cycle : ns < o.ns;
  }
};

class Model {
public:
  Model(double budgetNs, const SchedulingConfig &sched)
      : budgetNs(budgetNs), delays(sched.callDepth), sched(sched) {}

  /// Depth (latency + 1) of one call of `fn`, or nullopt when `fn` (or a
  /// function it calls) still has loops, calls itself or calls a function
  /// without a body.
  std::optional<unsigned> depth(func::FuncOp fn,
                                SymbolTableCollection &symbolTable) {
    auto it = memo.find(fn.getOperation());
    if (it != memo.end())
      return it->second;
    if (!onStack.insert(fn.getOperation()).second)
      return std::nullopt;
    std::optional<unsigned> dimensionIndex = schedule(fn, symbolTable);
    onStack.erase(fn.getOperation());
    memo[fn.getOperation()] = dimensionIndex;
    return dimensionIndex;
  }

private:
  double budgetNs;
  const CallDepthConfig &delays;
  const SchedulingConfig &sched;
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

  /// Data width of a value for the delay table: an index is an address, which
  /// Vitis narrows (w3rev_k2: `i10`); it is timed at `index_bits` (32).
  unsigned bitsOf(Type typeValue) const {
    if (typeValue.isIntOrFloat())
      return typeValue.getIntOrFloatBitWidth();
    return static_cast<unsigned>(delays.indexBits);
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
        return chain(start, delays.carryChain(bits));
      return chain(start, delays.constantMultiplierNs);
    }
    unsigned cycles = static_cast<int64_t>(bits) <= delays.narrowMultiplyMaxBits
                          ? static_cast<unsigned>(delays.narrowMultiplyCycles)
                          : static_cast<unsigned>(sched.latency("multicycle"));
    return {start.cycle + cycles, 0.0};
  }

  /// Latency in whole cycles of a floating-point or math op (the operator
  /// table of --convert-affine-to-loopschedule), 0 for a combinational one.
  unsigned floatCycles(Operation *op) const {
    auto lat = [&](llvm::StringRef cls) {
      return static_cast<unsigned>(sched.latency(cls));
    };
    if (isa<arith::MulFOp>(op) ||
        circt::hls_analysis::isExactReciprocalDivide(op))
      return lat("fpmul");
    if (isa<arith::AddFOp, arith::SubFOp, arith::MaximumFOp, arith::MinimumFOp,
            arith::MaxNumFOp, arith::MinNumFOp, math::FmaOp, math::FloorOp,
            math::CeilOp, math::RoundOp, math::RoundEvenOp, math::TruncOp>(op))
      return lat("fpaddsub");
    auto width = [&] {
      Type elt = getElementTypeOrSelf(op->getResult(0).getType());
      return elt.isIntOrFloat() ? elt.getIntOrFloatBitWidth() : 0u;
    };
    if (isa<arith::DivFOp, arith::RemFOp>(op))
      return lat(sched.floatClass("fpdiv", width()));
    if (isa<math::SqrtOp, math::RsqrtOp>(op))
      return lat(sched.floatClass("fpsqrt", width()));
    if (isa<math::AbsFOp, math::AbsIOp, math::CopySignOp>(op))
      return 0;
    if (isa_and_nonnull<math::MathDialect>(op->getDialect()))
      return lat("fptrans");
    return 0;
  }

  /// For an integer add / sub `op`, the add / sub of the same type that is
  /// only used by `op` and is not itself the root of a three-input adder:
  /// the two form one TernaryAdder (scheduling.call_depth.ternary_adder_ns).
  /// Null otherwise; index arithmetic (addresses) is never grouped.
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

  std::optional<unsigned> schedule(func::FuncOp fn,
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
      while (ports[{valueKey, globalKey, cycle}] >=
             static_cast<unsigned>(delays.portsPerMemory))
        ++cycle;
      ++ports[{valueKey, globalKey, cycle}];
      return cycle;
    };

    fn.getBody().walk<WalkOrder::PreOrder>([&](Operation *op) {
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
        done = {candidateValue + 1, delays.loadDataNs};
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
        done = {start.cycle +
                    static_cast<unsigned>(sched.latency("multicycle")),
                0.0};
      } else if (Operation *inner = ternaryInner(op, ternaryRoots)) {

        SmallVector<Value, 3> leaves(inner->getOperands());
        for (Value valueHandle : op->getOperands())
          if (valueHandle.getDefiningOp() != inner)
            leaves.push_back(valueHandle);
        done = chain(latest(leaves),
                     delays.ternaryAdder(bitsOf(op->getResult(0).getType())));
        ternaryRoots.insert(op);
      } else if (isa<arith::AddIOp, arith::SubIOp, arith::CmpIOp>(op)) {
        done = chain(start,
                     delays.carryChain(bitsOf(op->getOperand(0).getType())));
      } else if (isa<arith::AndIOp, arith::OrIOp, arith::XOrIOp>(op)) {
        done = chain(start, delays.logicNs);
      } else if (isa<arith::SelectOp>(op)) {
        done = chain(start, delays.selectNs);
      } else if (isa<arith::ShLIOp, arith::ShRSIOp, arith::ShRUIOp>(op)) {
        if (!constantInt(op->getOperand(1)))
          done = chain(start, delays.variableShiftNs);
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

  unsigned pipelineLoopsValue = 64;
  bool promotePipelinedValue = true;
  bool floatLoadsPerfectValue = true;
  /// tool.hls.pipeline_decision.do_while_flatten_refusal (N96).
  bool doWhileRefusalValue = true;
  /// tool.hls.pipeline_decision.do_while_min_subloop_trip (N96).
  uint64_t doWhileMinSubLoopTrip = 3;
  /// tool.hls.pipeline_decision.partial_unroll_runtime_loops (N103).
  bool partialUnrollRuntimeValue = true;

  /// How many of `loops` (outermost first, the innermost directly around
  /// the pipeline's absorbed loops) flatten into the pipeline: those inside
  /// the innermost loop of `refused` (N96).
  static unsigned
  flattenableParents(ArrayRef<AffineForOp> loops,
                     const llvm::SmallPtrSetImpl<Operation *> &refused) {
    unsigned count = 0;
    for (AffineForOp loop : llvm::reverse(loops)) {
      if (refused.contains(loop.getOperation()))
        break;
      ++count;
    }
    return count;
  }

  /// The cycle budget of the call-depth model: the clock period less the
  /// clock uncertainty.
  double callDepthBudgetNs(const circt::hlsest::Config &cfg) const {
    double period =
        circt::hlsest::resolveOption(clockPeriodNs, cfg.run.clockNs);
    if (clockUncertaintyPct.hasValue())
      return period * (1.0 - clockUncertaintyPct / 100.0);
    const circt::hlsest::TimingMargin &memoryOp = cfg.tool.hls.timingMargin;
    if (memoryOp.fraction)
      return period * (1.0 - *memoryOp.fraction);
    if (memoryOp.ns)
      return period - *memoryOp.ns;
    return period;
  }

  std::function<void(Location, const Twine &)> remarkFn;

  void remark(Location loc, const Twine &msg) {
    if (remarkFn)
      remarkFn(loc, msg);
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
      if (factor != 1)
        markUserUnrollCopies(loop);
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
        if (failed(circt::hls_analysis::hlsLoopUnrollFull(loop)))
          LLVM_DEBUG(llvm::dbgs() << "  loopUnrollFull failed\n");
        continue;
      }
      remark(loop.getLoc(), "user unroll: by factor " + Twine(factor) +
                                " (the loop is never auto-unrolled into a "
                                "parent pipeline)");
      applyPartialUnroll(loop, factor);
    }
    if (!partialUnrollRuntimeValue)
      return;
    SmallVector<scf::ForOp> runtimeLoops;
    func.walk<WalkOrder::PostOrder>([&](scf::ForOp loop) {
      std::optional<uint64_t> fieldValue = userUnrollFactor(loop);
      if (!fieldValue || *fieldValue <= 1)
        return;

      for (Operation *portValue = loop->getParentOp();
           portValue && !isa<func::FuncOp>(portValue);
           portValue = portValue->getParentOp())
        if ((isa<AffineForOp>(portValue) || isRuntimeLoop(portValue)) &&
            isUserPipelined(portValue)) {
          remark(loop.getLoc(), "user unroll: run-time trip count inside a "
                                "pipelined loop, left rolled");
          return;
        }
      runtimeLoops.push_back(loop);
    });
    for (scf::ForOp loop : runtimeLoops) {
      uint64_t factor = *userUnrollFactor(loop);
      markUserUnrollCopies(loop);
      remark(loop.getLoc(), "user unroll: run-time trip count, by factor " +
                                Twine(factor) +
                                " with guarded copies (VITIS_NOTES N103)");
      applyRuntimePartialUnroll(loop, factor);
    }
  }

  /// Marks the calls and math ops of a loop a user `unroll` pragma unrolls
  /// (hls.user_unroll_copy; the copies inherit the mark): debug provenance
  /// and the N16 R6 test in --bram-analysis (a library core called from such
  /// copies stays one module per copy).
  static void markUserUnrollCopies(Operation *loop) {
    Builder buildPoint(loop->getContext());
    loop->walk([&](Operation *op) {
      if (isa<CallOpInterface>(op) ||
          op->getName().getDialectNamespace() == "math")
        op->setAttr(circt::hls_analysis::kUserUnrollCopyAttr,
                    buildPoint.getUnitAttr());
    });
  }

  /// `#pragma HLS unroll factor=F` on an scf.for whose trip count is only
  /// known at run time (VITIS_NOTES N103: Vitis applies it, [HLS 214-188],
  /// and keeps the loop's II). The loop becomes one of step F * step whose
  /// body holds F copies; copy u > 0 runs under `iv + u * step < ub` (Vitis
  /// keeps the exit test in the unrolled body, there is no epilogue loop).
  /// Loop-carried values flow through the copies (an skipped copy passes
  /// them on unchanged). The new loop carries `hls.unroll_partial`.
  void applyRuntimePartialUnroll(scf::ForOp loop, uint64_t factor) {
    OpBuilder buildPoint(loop);
    Location loc = loop.getLoc();
    Value step = loop.getStep();
    Type ivType = step.getType();
    auto constant = [&](OpBuilder &ob, int64_t valueHandle) -> Value {
      if (ivType.isIndex())
        return ob.create<arith::ConstantIndexOp>(loc, valueHandle);
      return ob.create<arith::ConstantOp>(
          loc, ob.getIntegerAttr(ivType, valueHandle));
    };
    Value newStep = buildPoint.createOrFold<arith::MulIOp>(
        loc, step, constant(buildPoint, static_cast<int64_t>(factor)));
    Block *oldBody = loop.getBody();
    auto cloneBody = [&](OpBuilder &ob, Value iv, ValueRange carried) {
      IRMapping map;
      map.map(loop.getInductionVar(), iv);
      map.map(loop.getRegionIterArgs(), carried);
      for (Operation &op : oldBody->without_terminator())
        ob.clone(op, map);
      auto yield = cast<scf::YieldOp>(oldBody->getTerminator());
      SmallVector<Value> out;
      for (Value valueHandle : yield.getOperands())
        out.push_back(map.lookupOrDefault(valueHandle));
      return out;
    };
    auto newLoop = buildPoint.create<scf::ForOp>(
        loc, loop.getLowerBound(), loop.getUpperBound(), newStep,
        loop.getInitArgs(),
        [&](OpBuilder &ob, Location lowerIndex, Value iv, ValueRange args) {
          SmallVector<Value> carried = cloneBody(ob, iv, args);
          for (uint64_t useValue = 1; useValue < factor; ++useValue) {
            Value offset = ob.createOrFold<arith::MulIOp>(
                lowerIndex, step, constant(ob, static_cast<int64_t>(useValue)));
            Value ivU = ob.create<arith::AddIOp>(lowerIndex, iv, offset);

            Value inRange =
                ob.create<arith::CmpIOp>(lowerIndex, arith::CmpIPredicate::slt,
                                         ivU, loop.getUpperBound());
            auto guard = ob.create<scf::IfOp>(
                lowerIndex, inRange,
                [&](OpBuilder &tb, Location) {
                  tb.create<scf::YieldOp>(lowerIndex,
                                          cloneBody(tb, ivU, carried));
                },
                [&](OpBuilder &eb, Location) {
                  eb.create<scf::YieldOp>(lowerIndex, carried);
                });
            carried.assign(guard.getResults().begin(),
                           guard.getResults().end());
          }
          ob.create<scf::YieldOp>(lowerIndex, carried);
        });
    for (NamedAttribute attr : loop->getDiscardableAttrs())
      if (attr.getName() != kLoopUnrollAttr)
        newLoop->setAttr(attr.getName(), attr.getValue());
    newLoop->setAttr(kLoopUnrollPartialAttr, buildPoint.getI64IntegerAttr(
                                                 static_cast<int64_t>(factor)));
    newLoop->setAttr(kLoopUnrollRuntimeGuardedAttr, buildPoint.getUnitAttr());
    loop.replaceAllUsesWith(newLoop.getResults());
    loop.erase();
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

    auto isCoreOp = [](Operation *op) {
      return isa<CallOpInterface>(op) ||
             op->getName().getDialectNamespace() == "math";
    };
    unsigned coreOpsPerIteration = 0;
    loop.getBody()->walk([&](Operation *op) {
      if (isCoreOp(op)) {
        op->setAttr(kUnrollPendingAttr, buildPoint.getUnitAttr());
        ++coreOpsPerIteration;
      }
    });
    std::optional<uint64_t> tripCount = affine::getConstantTripCount(loop);

    loop->setAttr(kUnrollPendingAttr, buildPoint.getUnitAttr());
    auto clearPending = [&] {
      for (Operation *op = prev ? prev->getNextNode() : &block->front();
           op && op != next; op = op->getNextNode())
        op->walk([&](Operation *inner) {
          if (isCoreOp(inner))
            inner->removeAttr(kUnrollPendingAttr);
        });
    };
    if (failed(circt::hls_analysis::hlsLoopUnrollByFactor(loop, factor))) {

      LLVM_DEBUG(llvm::dbgs() << "  loopUnrollByFactor failed\n");
      loop->removeAttr(kUnrollPendingAttr);
      clearPending();
      markMain(loop);
      return;
    }
    SmallVector<AffineForOp, 2> results;
    for (Operation *op = prev ? prev->getNextNode() : &block->front();
         op && op != next; op = op->getNextNode())
      if (auto forOp = dyn_cast<AffineForOp>(op))
        if (forOp->hasAttr(kUnrollPendingAttr))
          results.push_back(forOp);

    bool cleanupLoopKept = llvm::any_of(results, [&](AffineForOp fieldValue) {
      return fieldValue.getStepAsInt() == step;
    });
    auto markRemainder = [&](Operation *op) {
      op->setAttr(circt::hls_analysis::kUnrollRemainderAttr,
                  buildPoint.getUnitAttr());
    };
    if (!cleanupLoopKept && tripCount && *tripCount % factor == 1) {
      SmallVector<Operation *> straightLine;
      for (Operation *op = prev ? prev->getNextNode() : &block->front();
           op && op != next; op = op->getNextNode()) {
        if (auto forOp = dyn_cast<AffineForOp>(op);
            forOp && forOp->hasAttr(kUnrollPendingAttr))
          continue;
        op->walk<WalkOrder::PreOrder>([&](Operation *inner) {
          if (isCoreOp(inner) && inner->hasAttr(kUnrollPendingAttr))
            straightLine.push_back(inner);
        });
      }
      if (coreOpsPerIteration <= straightLine.size())
        for (Operation *op :
             ArrayRef(straightLine).take_back(coreOpsPerIteration))
          markRemainder(op);
    }
    clearPending();
    for (AffineForOp forOp : results) {
      forOp->removeAttr(kUnrollPendingAttr);
      if (forOp.getStepAsInt() != step) {
        markMain(forOp);
        continue;
      }
      forOp.getBody()->walk([&](Operation *op) {
        if (isCoreOp(op))
          markRemainder(op);
      });
      remark(forOp.getLoc(),
             "user unroll: remainder iterations unrolled completely (Vitis "
             "keeps them in the unrolled body, there is no epilogue loop)");
      if (failed(circt::hls_analysis::hlsLoopUnrollFull(forOp)))
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

  /// Everything inside the pipelined loop (an affine.for or a runtime loop)
  /// is unrolled completely. Each unrolled loop is recorded on `pipelined`
  /// in `hls.auto_unrolled`. Returns the number of loops unrolled.
  unsigned unrollInside(Operation *pipelined,
                        SymbolTableCollection &symbolTable) {
    SmallVector<AffineForOp> inner;
    SmallPtrSet<Operation *, 4> visitedCallees;

    if (auto owner = pipelined->getParentOfType<func::FuncOp>())
      visitedCallees.insert(owner.getOperation());
    for (Region &region : pipelined->getRegions())
      collectInner(region, inner, visitedCallees, symbolTable);
    Builder buildPoint(pipelined->getContext());
    SmallVector<Attribute> record;
    if (auto prev = pipelined->getAttrOfType<ArrayAttr>(kLoopAutoUnrolledAttr))
      record.append(prev.begin(), prev.end());
    unsigned unrolled = 0;
    for (AffineForOp loop : inner) {
      if (loop.getOperation() == pipelined || loop->isProperAncestor(pipelined))
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
                                locString(pipelined->getLoc()) + "; hoisted " +
                                Twine(hoisted) + " invariant op(s), promoted " +
                                Twine(promoted) + " memory(ies) to registers)");
      loop->removeAttr(kLoopPipelineAttr);
      loop->removeAttr(kLoopFlattenedParentsAttr);
      loop->removeAttr(kLoopAutoUnrolledAttr);
      LocationAttr loc = loop.getLoc();
      if (failed(circt::hls_analysis::hlsLoopUnrollFull(loop))) {
        LLVM_DEBUG(llvm::dbgs() << "  loopUnrollFull failed\n");
        continue;
      }
      record.push_back(buildPoint.getDictionaryAttr(
          {buildPoint.getNamedAttr("factor", buildPoint.getI64IntegerAttr(
                                                 static_cast<int64_t>(*trip))),
           buildPoint.getNamedAttr("loc", loc)}));
      ++unrolled;
    }
    if (!record.empty())
      pipelined->setAttr(kLoopAutoUnrolledAttr,
                         buildPoint.getArrayAttr(record));
    return unrolled;
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
    if (n.runtimeLoop)
      return decideRuntime(n, symbolTable);
    if (n.chain.empty())
      return;
    unsigned T = pipelineLoopsValue;
    if (n.userPipelineIdx >= 0) {
      AffineForOp useValue = n.chain[n.userPipelineIdx];
      n.tagged = useValue;
      addFlattenedParents(useValue, n.userPipelineIdx);
      remark(useValue.getLoc(), "user pipeline: unrolling everything inside, " +
                                    Twine(n.userPipelineIdx) +
                                    " perfect parent(s) flattened into it");
      unrollInside(useValue, symbolTable);

      n.tagged =
          promotePipelinedValue ? promoteOutOfPipeline(useValue) : useValue;
      n.chain[n.userPipelineIdx] = n.tagged;
      return;
    }
    bool feasible = T > 0 && !n.pipelineOff;
    for (auto &candidateValue : n.children)
      feasible &= candidateValue->constInside && candidateValue->maxPath <= T &&
                  !candidateValue->hasUserPipeline &&
                  !candidateValue->hasUserFixed;
    if (feasible) {
      AffineForOp portValue = n.chain.back();
      n.tagged = portValue;
      tagAutoPipeline(portValue);

      if (doWhileRefusalValue)
        n.doWhileParents = circt::hls_analysis::doWhileParents(
            portValue, doWhileMinSubLoopTrip);
      unsigned parents =
          flattenableParents(ArrayRef(n.chain).drop_back(), n.doWhileParents);
      if (parents + 1 < n.chain.size()) {
        n.flattenRefused = true;
        markFlattenRefused(n.chain[n.chain.size() - 2 - parents]);
        remark(n.chain[n.chain.size() - 2 - parents].getLoc(),
               "not flattened into the pipelined loop at " +
                   locString(portValue.getLoc()) +
                   ": its unrolled sub-loop subscripts the next index of "
                   "this loop (Vitis 200-960, do-while loop)");
      }
      addFlattenedParents(portValue, parents);

      uint64_t trip = 1;
      for (AffineForOp member : ArrayRef(n.chain).take_back(parents + 1))
        trip = saturatingMul(trip, getConstantTripCount(member).value_or(1));
      remark(portValue.getLoc(),
             "automatically set the pipeline for the loop (trip " +
                 (n.dynamic ? Twine("?") : Twine(trip)) + ", " +
                 Twine(parents) + " perfect parent(s) flattened, " +
                 Twine(n.children.size()) + " inner loop(s) to unroll)");
      unrollInside(portValue, symbolTable);
      n.tagged =
          promotePipelinedValue ? promoteOutOfPipeline(portValue) : portValue;
      n.chain.back() = n.tagged;
      return;
    }
    for (auto &candidateValue : n.children)
      if (!candidateValue->viaCall)
        decide(*candidateValue, symbolTable);

    if (n.children.size() != 1)
      return;
    Node &candidateValue = *n.children.front();

    if (candidateValue.viaCall || candidateValue.chain.empty() ||
        !candidateValue.tagged || (n.dynamic && !n.uncountedPerfect) ||
        candidateValue.dynamic)
      return;
    if (candidateValue.chain.front()->getBlock() != n.chain.back().getBody())
      return;
    if (candidateValue.flattenRefused)
      return;
    unsigned parents =
        flattenableParents(n.chain, candidateValue.doWhileParents);
    if (parents < n.chain.size()) {
      markFlattenRefused(n.chain[n.chain.size() - 1 - parents]);
      remark(n.chain[n.chain.size() - 1 - parents].getLoc(),
             "not flattened into the pipelined loop at " +
                 locString(candidateValue.tagged.getLoc()) +
                 ": its unrolled sub-loop subscripts the next index of this "
                 "loop (Vitis 200-960, do-while loop)");

      addFlattenedParents(candidateValue.tagged, parents);
      n.flattenRefused = true;
      return;
    }
    addFlattenedParents(candidateValue.tagged, n.chain.size());
    n.tagged = candidateValue.tagged;
    n.doWhileParents = candidateValue.doWhileParents;
    remark(n.chain.front().getLoc(),
           "flattening the loop (and " + Twine(n.chain.size() - 1) +
               " perfect inner loop(s)) into the pipelined loop at " +
               locString(candidateValue.tagged.getLoc()));
  }

  /// A runtime loop (N53) is pipelined under the test of an affine one: its
  /// own trip count does not matter, every loop inside it (callee loops
  /// included) must have a constant trip count with products <= T. An
  /// scf.for whose body is a perfect nest (isPerfectRuntimePair) is instead
  /// collapsed with it as a perfect affine parent is (step 1; a variable
  /// bound is allowed on the outermost loop of a flattened nest): the nest
  /// is decided as its inner chain and the runtime loop is flattened into
  /// that chain's pipeline (N53 (b)). Otherwise it is never flattened with
  /// another loop (its parent's trip count is unknown to it), and
  /// promoteOutOfPipeline, an affine transform, is not applied to it.
  void decideRuntime(Node &n, SymbolTableCollection &symbolTable) {
    Operation *loop = n.runtimeLoop;
    unsigned T = pipelineLoopsValue;
    if (isUserPipelined(loop)) {
      remark(loop->getLoc(), "user pipeline of a runtime-trip loop: "
                             "unrolling everything inside");
      unrollInside(loop, symbolTable);
      return;
    }
    if (n.perfectRuntime && T > 0) {
      Node &candidateValue = *n.children.front();
      decide(candidateValue, symbolTable);
      if (candidateValue.tagged &&
          llvm::is_contained(candidateValue.chain, candidateValue.tagged)) {
        addFlattenedParents(candidateValue.tagged, 1);
        n.tagged = candidateValue.tagged;
        remark(loop->getLoc(),
               "flattening the runtime-trip loop (perfect nest) into the "
               "pipelined loop at " +
                   locString(candidateValue.tagged.getLoc()));
      }
      return;
    }
    bool feasible = T > 0 && !n.pipelineOff;
    for (auto &candidateValue : n.children)
      feasible &= candidateValue->constInside && candidateValue->maxPath <= T &&
                  !candidateValue->hasUserPipeline &&
                  !candidateValue->hasUserFixed;
    if (feasible) {
      tagAutoPipeline(loop);
      unsigned unrolled = unrollInside(loop, symbolTable);
      remark(loop->getLoc(),
             "automatically set the pipeline for the runtime-trip loop "
             "(unrolled " +
                 Twine(unrolled) + " inner loop(s))");
      return;
    }
    for (auto &candidateValue : n.children)
      if (!candidateValue->viaCall)
        decide(*candidateValue, symbolTable);
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
  callersFirst(ModuleOp module, SymbolTableCollection &symbolTable) {
    SmallVector<func::FuncOp> postOrder;
    DenseSet<Operation *> visited;
    std::function<void(func::FuncOp)> visit = [&](func::FuncOp fn) {
      if (!visited.insert(fn.getOperation()).second)
        return;
      fn.walk([&](CallOpInterface callSite) {
        auto callee = dyn_cast_or_null<func::FuncOp>(
            callSite.resolveCallableInTable(&symbolTable));
        if (callee && !callee.isExternal())
          visit(callee);
      });
      postOrder.push_back(fn);
    };
    for (auto fn : module.getOps<func::FuncOp>())
      if (!fn.isExternal())
        visit(fn);
    return SmallVector<func::FuncOp>(llvm::reverse(postOrder));
  }

  /// Whether `fn`, or a function it calls, still holds a loop.
  static bool hasLoops(func::FuncOp fn, SymbolTableCollection &symbolTable,
                       SmallPtrSetImpl<Operation *> &stack) {
    if (!stack.insert(fn.getOperation()).second)
      return false;
    bool found = false;
    fn.walk([&](Operation *op) {
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
    stack.erase(fn.getOperation());
    return found;
  }

  /// Cycles one call of the loop-free `fn` holds its instance: its accesses
  /// to each memory (an argument, a local array, a global), two per cycle
  /// (a memory's two ports), the busiest memory deciding; at least 1. A
  /// nested call counts with its own occupancy.
  static unsigned occupancy(func::FuncOp fn, SymbolTableCollection &symbolTable,
                            SmallPtrSetImpl<Operation *> &stack) {
    return circt::hls_analysis::estimateCallOccupancy(fn, symbolTable, stack);
  }

  /// The call boundary after the decisions (VITIS_NOTES.md N14 R7): a loop
  /// that is not pipelined and calls a kept function that still has loops
  /// gets `hls.call_boundary` (Vitis pipelines the callee's loops in the
  /// callee and leaves the caller loop sequential: w3h_cb_nest256,
  /// attn_breakdown_op1 `VITIS_LOOP_232_1`); a call inside a pipelined loop
  /// gets `hls.call_occupancy` (its callee is loop-free by then, R7) and
  /// `hls.call_depth` (the states of one call, for calls that share an
  /// instance; N14 R2 in a pipelined loop).
  static void markCallBoundaries(ModuleOp module,
                                 SymbolTableCollection &symbolTable,
                                 call_depth::Model &depthModel) {
    module.walk([&](CallOpInterface callSite) {
      auto callee = dyn_cast_or_null<func::FuncOp>(
          callSite.resolveCallableInTable(&symbolTable));
      if (!callee || callee.isExternal())
        return;

      Operation *loop = callSite->getParentOfType<AffineForOp>();
      if (auto inner = callSite->getParentOfType<LoopLikeOpInterface>();
          inner && isRuntimeLoop(inner) && inner->hasAttr(kLoopPipelineAttr))
        loop = inner;
      if (!loop)
        return;
      OpBuilder buildPoint(callSite.getContext());
      SmallPtrSet<Operation *, 8> stack;
      if (loop->hasAttr(kLoopPipelineAttr)) {
        unsigned occ = occupancy(callee, symbolTable, stack);
        callSite->setAttr(kCallOccupancyAttr,
                          buildPoint.getI64IntegerAttr(occ));
        if (std::optional<unsigned> dimensionIndex =
                depthModel.depth(callee, symbolTable)) {
          callSite->setAttr(
              kCallDepthAttr,
              buildPoint.getI64IntegerAttr(std::max(*dimensionIndex, occ)));

          if (*dimensionIndex < occ)
            callSite->setAttr(circt::hls_analysis::kCallDepthEstimateAttr,
                              buildPoint.getI64IntegerAttr(*dimensionIndex));
        }
        return;
      }
      if (!loop->hasAttr(kLoopCallBoundaryAttr) &&
          hasLoops(callee, symbolTable, stack))
        loop->setAttr(kLoopCallBoundaryAttr,
                      buildPoint.getStringAttr(callee.getSymName()));
    });
  }

  void runOnOperation() override {
    ModuleOp module = getOperation();
    const circt::hlsest::Config &cfg = circt::hlsest::Config::get();
    const circt::hlsest::PipelineDecisionConfig &pd =
        cfg.tool.hls.pipelineDecision;
    if (pd.flattenAcrossCalls) {

      module.emitError("--auto-pipeline-unroll: "
                       "tool.hls.pipeline_decision.flatten_across_calls = true "
                       "is not implemented");
      return signalPassFailure();
    }

    circt::hlsest::PipelineDecisionOptions options;
    options.pipelineLoops = circt::hlsest::resolveOption<unsigned>(
        pipelineLoops,
        static_cast<unsigned>(cfg.tool.hls.options.pipelineLoops));
    options.promotePipelined =
        circt::hlsest::resolveOption(promotePipelined, pd.promotePipelined);
    options.floatLoadsPerfect =
        circt::hlsest::resolveOption(floatLoadsPerfect, pd.floatLoadsPerfect);
    options.callDepthBudgetNs = callDepthBudgetNs(cfg);
    if (emitRemarks)
      options.remark = [](Location loc, const Twine &msg) {
        mlir::emitRemark(loc) << msg;
      };

    circt::hlsest::ConfigDiagnostics diag;
    std::unique_ptr<circt::hlsest::PipelinePolicy> policy =
        circt::hlsest::PluginRegistry<circt::hlsest::PipelinePolicy>::instance()
            .create(pd.policy, cfg, diag);
    if (!policy) {
      InFlightDiagnostic dimensionIndex =
          module.emitError("--auto-pipeline-unroll: ");
      llvm::interleave(diag.errors, dimensionIndex, "; ");
      return signalPassFailure();
    }
    if (failed(policy->decide(module, options)))
      return signalPassFailure();

    if (pd.foldUnrolledGuards) {
      circt::hls_analysis::FoldedGuards fieldValue =
          circt::hls_analysis::foldConstantAffineIfs(module);
      LLVM_DEBUG(llvm::dbgs() << "folded " << fieldValue.folded << " guard(s) ("
                              << fieldValue.scfIfs << " scf.if), pinned "
                              << fieldValue.pinnedOperands << " operand(s)\n");
    }
  }

  /// The Vitis decision procedure (the builtin PipelinePolicy
  /// vitis-pipeline-loops): user unrolls, then per function the pipelined
  /// loops, the unrolled and the flattened ones, then the call boundaries
  /// and the port-bound arguments.
  LogicalResult runDecision(ModuleOp module,
                            const circt::hlsest::PipelineDecisionOptions &o) {
    SymbolTableCollection symbolTable;
    pipelineLoopsValue = o.pipelineLoops;
    promotePipelinedValue = o.promotePipelined;
    floatLoadsPerfectValue = o.floatLoadsPerfect;
    doWhileRefusalValue = circt::hlsest::Config::get()
                              .tool.hls.pipelineDecision.doWhileFlattenRefusal;
    doWhileMinSubLoopTrip = static_cast<uint64_t>(
        circt::hlsest::Config::get()
            .tool.hls.pipelineDecision.doWhileMinSubLoopTrip);
    partialUnrollRuntimeValue =
        circt::hlsest::Config::get()
            .tool.hls.pipelineDecision.partialUnrollRuntimeLoops;
    remarkFn = o.remark;

    module.walk([&](Operation *op) {
      if (isRuntimeLoop(op)) {
        if (isAutoPipelineTag(op->getAttr(kLoopPipelineAttr)))
          op->removeAttr(kLoopPipelineAttr);
        op->removeAttr(kLoopAutoUnrolledAttr);
      }
    });
    module.walk([&](AffineForOp loop) {
      if (isAutoPipelineTag(loop->getAttr(kLoopPipelineAttr)))
        loop->removeAttr(kLoopPipelineAttr);
      loop->removeAttr(kLoopFlattenedParentsAttr);
      loop->removeAttr(kLoopFlattenRefusedAttr);
      loop->removeAttr(kLoopAutoUnrolledAttr);
      loop->removeAttr(kLoopCallBoundaryAttr);
    });
    module.walk([&](CallOpInterface callSite) {
      callSite->removeAttr(kCallOccupancyAttr);
      callSite->removeAttr(kCallDepthAttr);
      callSite->removeAttr(circt::hls_analysis::kCallDepthEstimateAttr);
    });
    for (auto func : module.getOps<func::FuncOp>())
      func->removeAttr(circt::hls_analysis::kPortBoundArgsAttr);

    for (auto func : module.getOps<func::FuncOp>())
      if (!func.isExternal())
        applyUserUnrolls(func);

    for (func::FuncOp func : callersFirst(module, symbolTable)) {
      LicmModel licm(floatLoadsPerfectValue);
      Forest forest(licm);

      SmallVector<Operation *, 8> roots;
      func.getBody().walk<WalkOrder::PreOrder>([&](Operation *op) {
        if (!isa<AffineForOp>(op) && !isRuntimeLoop(op))
          return WalkResult::advance();
        roots.push_back(op);
        return WalkResult::skip();
      });
      SmallVector<std::unique_ptr<Node>> nodes;
      SmallPtrSet<Operation *, 4> callStack;
      callStack.insert(func.getOperation());
      for (Operation *loop : roots) {
        if (auto forOp = dyn_cast<AffineForOp>(loop))
          nodes.push_back(forest.build(forOp, false, callStack));
        else
          nodes.push_back(forest.buildRuntime(loop, false, callStack));
      }
      for (auto &node : nodes)
        decide(*node, symbolTable);
    }
    call_depth::Model depthModel(o.callDepthBudgetNs,
                                 circt::hlsest::Config::get().scheduling);
    markCallBoundaries(module, symbolTable, depthModel);
    markPortBoundArgs(module);
    return success();
  }

  /// `hls.port_bound_args` on every function whose memref arguments name an
  /// array that crosses a module instantiated at more than one place
  /// (VITIS_NOTES.md N14 R6; W3 review D2: w3rev_k3 / k3b / w3fx_d2_conc).
  /// MemrefBankClassification gives such an argument two ports instead of
  /// the replicable pool, so the callee's loop II rises as in Vitis (rd3
  /// II 2). The instances are counted after the unroll decisions, on the
  /// final call sites.
  static void markPortBoundArgs(ModuleOp module) {
    using namespace circt::hls_analysis;
    InstanceModel model = computeInstances(module);
    OpBuilder buildPoint(module.getContext());
    for (auto fn : module.getOps<func::FuncOp>()) {
      if (fn.isExternal())
        continue;
      SmallVector<int64_t> bound;
      for (BlockArgument arg : fn.getArguments())
        if (isa<BaseMemRefType>(arg.getType()) &&
            model.argReachesSharedModule(fn, arg.getArgNumber()))
          bound.push_back(arg.getArgNumber());
      if (!bound.empty())
        fn->setAttr(kPortBoundArgsAttr, buildPoint.getI64ArrayAttr(bound));
    }
  }
};

/// vitis-pipeline-loops: Vitis' config_compile -pipeline_loops decision
/// (VITIS_NOTES N3), the code of this pass.
class VitisPipelineLoops : public circt::hlsest::PipelinePolicy {
public:
  StringRef name() const override { return "vitis-pipeline-loops"; }
  LogicalResult
  decide(ModuleOp module,
         const circt::hlsest::PipelineDecisionOptions &options) const override {
    AutoPipelineUnrollPass impl;
    return impl.runDecision(module, options);
  }
};

} // namespace

void circt::hlsest::builtin::registerPipelinePolicies() {
  circt::hlsest::PluginRegistry<circt::hlsest::PipelinePolicy>::instance().add(
      "vitis-pipeline-loops",
      "Vitis config_compile -pipeline_loops: pipeline a loop whose nested "
      "trip-count products are all <= pipeline_loops, unroll inside, flatten "
      "perfect parents (VITIS_NOTES N3)",
      [] { return std::make_unique<VitisPipelineLoops>(); }, "builtin");
}

namespace circt::hls_analysis {

std::unique_ptr<mlir::Pass> createAutoPipelineUnrollPass() {
  return std::make_unique<AutoPipelineUnrollPass>();
}

void registerAutoPipelineUnrollPass() {
  ::mlir::PassRegistration<AutoPipelineUnrollPass>();
}

} // namespace circt::hls_analysis
