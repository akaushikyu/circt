

// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "circt/Dialect/Resource/Passes/AffineToLoopScheduleModified.h"
#include "circt/Analysis/DependenceAnalysis.h"
#include "circt/Dialect/LoopSchedule/LoopScheduleOps.h"
#include "circt/Dialect/Resource/HLS/HLSDialect.h"
#include "circt/Dialect/Resource/HLS/HLSOps.h"
#include "circt/Dialect/Resource/Passes/CallInstances.h"
#include "circt/Dialect/Resource/Passes/CyclicSchedulingAnalysisModified.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Dialect/Resource/Passes/MemrefBankClassification.h"
#include "circt/Scheduling/Algorithms.h"
#include "circt/Scheduling/Problems.h"
#include "mlir/Conversion/AffineToStandard/AffineToStandard.h"
#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineMemoryOpInterfaces.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/IR/AffineValueMap.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Affine/Utils.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/ControlFlow/IR/ControlFlow.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/Math/IR/Math.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/IR/BuiltinDialect.h"
#include "mlir/IR/Dominance.h"
#include "mlir/IR/IRMapping.h"
#include "mlir/IR/ImplicitLocOpBuilder.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/Interfaces/CallInterfaces.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/RegionUtils.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/Debug.h"
#include <cassert>
#include <limits>
#include <mlir/IR/IntegerSet.h>
#include <queue>
#include <unordered_map>

#define DEBUG_TYPE "affine-to-loopschedule"

#include "llvm/ADT/MapVector.h"
#include "llvm/Support/CommandLine.h"

static llvm::cl::opt<int> loopScheduleCallLatency(
    "loopschedule-call-latency",
    llvm::cl::desc("--convert-affine-to-loopschedule: operator latency for a "
                   "func.call without memref operands inside a loop body "
                   "(-1: leave that loop sequential)"),
    llvm::cl::init(-1));

static llvm::cl::opt<int> loopScheduleKeptCallLatency(
    "loopschedule-kept-call-latency",
    llvm::cl::desc("--convert-affine-to-loopschedule: operator latency for a "
                   "func.call to a function defined in the module inside a "
                   "loop body (-1: leave that loop sequential)"),
    llvm::cl::init(1));

namespace circt {

#define GEN_PASS_DECL_AFFINETOLOOPSCHEDULE
#define GEN_PASS_DEF_AFFINETOLOOPSCHEDULE
#include "circt/Conversion/Passes.h.inc"
} // namespace circt

using namespace mlir;
using namespace mlir::arith;
using namespace mlir::memref;
using namespace mlir::scf;
using namespace mlir::func;
using namespace mlir::affine;
using namespace circt;
using namespace circt::analysis;
using namespace circt::scheduling;
using namespace circt::loopschedule;
using namespace circt::hls_analysis;

namespace {

struct AffineToLoopSchedule
    : public circt::impl::AffineToLoopScheduleBase<AffineToLoopSchedule> {

  AffineToLoopSchedule() = default;
  AffineToLoopSchedule(const AffineToLoopSchedule &other)
      : circt::impl::AffineToLoopScheduleBase<AffineToLoopSchedule>(other) {}

  void unrollInnerReductions();
  void runOnOperation() override;

private:
  ModuloProblem getModuloProblem(CyclicProblem &prob);
  LogicalResult
  lowerAffineStructures(MemoryDependenceAnalysis &dependenceAnalysis);

  LogicalResult populateOperatorTypes(AffineForOp forOp, ModuloProblem &problem,
                                      const BRAMClassification &bramClass);

  LogicalResult solveSchedulingProblem(AffineForOp forOp,
                                       ModuloProblem &problem);
  LogicalResult createLoopSchedulePipeline(AffineForOp forOp,
                                           ModuloProblem &problem);

  void coalescePerfectNests();

  void hoistInvariantLoads();
  void cleanupRedundantAccesses();

  CyclicSchedulingAnalysis *schedulingAnalysis;

  Statistic numDepPairs{this, "dependence-pairs",
                        "Same-memref access pairs the memory dependence "
                        "analysis enumerated"};
  Statistic numDepTests{this, "dependence-tests",
                        "Dependence tests it ran (memo misses)"};
  Statistic numDeps{this, "dependences", "Memory dependences it recorded"};

  Option<bool> reuseSchedules{
      *this, "reuse-schedules",
      llvm::cl::desc("Give a loop whose scheduling problem is identical to an "
                     "already scheduled loop's (same operations in the same "
                     "order, operator latencies, resource limits and sharing, "
                     "dependences and distances) that loop's II and start "
                     "times instead of solving it again. Both schedulers are "
                     "deterministic functions of these inputs, so the result "
                     "is the same."),
      llvm::cl::init(true)};
  Option<bool> verifyScheduleReuse{
      *this, "verify-schedule-reuse",
      llvm::cl::desc("With reuse-schedules: solve every reused loop anyway, "
                     "keep the solved schedule and warn if it differs from "
                     "the reused one."),
      llvm::cl::init(false)};
  Statistic numSchedulesSolved{this, "schedules-solved",
                               "Loops whose scheduling problem was solved"};
  Statistic numSchedulesReused{
      this, "schedules-reused",
      "Loops that reused the schedule of an identical scheduling problem"};
  Statistic numReuseMismatches{
      this, "schedule-reuse-mismatches",
      "verify-schedule-reuse: reused schedules that differ from a new solve"};

  struct CachedSchedule {
    SmallVector<int64_t> signature;
    unsigned ii = 0;
    SmallVector<unsigned> startTimes;
    std::string scheduler;
    std::string loc;
  };

  std::unordered_map<size_t, SmallVector<CachedSchedule, 1>> scheduleCache;
};

} // namespace

/// MODIFIED (T7): everything the modulo schedulers (ModuloSimplexScheduler,
/// FastModuloScheduler) read from a ModuloProblem, with operations numbered by
/// their position in the problem and operator / resource types by their first
/// use: per operation its name, linked operator type and latency, linked
/// resource types and limits, and its dependences (source position, kind,
/// operand indices, distance); plus the anchor's position. Both schedulers
/// only compare operator / resource types for identity, iterate operations and
/// dependences in problem order and break ties by that order, so two problems
/// with equal signatures get the same II and the same start time per
/// position. The typical case is a body that a user unroll of an outer loop
/// copied N times: the copies differ in the memrefs (of one type) they access
/// and in the constants of their outer-index arithmetic, so their problems
/// are identical (forgebench diff_orders_p1: 137 of 140 innermost loops
/// reuse a schedule) unless such a constant enters the body (diff_orders_module
/// with --infer-vitis-split-array: copy k reads a bank at `[(%iv + j) floordiv
/// 16, %outer + k]`, and its problem differs from copy k+1's; 278 of 417 loops
/// reuse).
static SmallVector<int64_t> scheduleSignature(ModuloProblem &prob,
                                              Operation *anchor) {
  SmallVector<int64_t> widthValue;
  DenseMap<Operation *, int64_t> index;
  int64_t elementCount = 0;
  for (Operation *op : prob.getOperations())
    index[op] = elementCount++;
  DenseMap<const void *, int64_t> oprIds, rsrcIds;
  auto idOf = [](DenseMap<const void *, int64_t> &ids, const void *key) {
    auto [it, fresh] = ids.try_emplace(key, ids.size());
    (void)fresh;
    return it->second;
  };
  auto optToWord = [](auto opt) -> int64_t {
    return opt ? static_cast<int64_t>(*opt) : -1;
  };
  auto position = [&](Operation *op) -> int64_t {
    auto it = index.find(op);
    return it == index.end() ? -1 : it->second;
  };
  widthValue.push_back(elementCount);
  widthValue.push_back(position(anchor));
  for (Operation *op : prob.getOperations()) {
    widthValue.push_back(
        reinterpret_cast<intptr_t>(op->getName().getAsOpaquePointer()));
    if (auto opr = prob.getLinkedOperatorType(op)) {
      widthValue.push_back(idOf(oprIds, opr->getAttr().getAsOpaquePointer()));
      widthValue.push_back(optToWord(prob.getLatency(*opr)));
    } else {
      widthValue.append({-1, -1});
    }
    if (auto rsrcs = prob.getLinkedResourceTypes(op)) {
      widthValue.push_back(rsrcs->size());
      for (Problem::ResourceType resultValue : *rsrcs) {
        widthValue.push_back(
            idOf(rsrcIds, resultValue.getAttr().getAsOpaquePointer()));
        widthValue.push_back(optToWord(prob.getLimit(resultValue)));
      }
    } else {
      widthValue.push_back(-1);
    }
    int64_t numDeps = 0;
    for (auto &dep : prob.getDependences(op)) {
      widthValue.push_back(position(dep.getSource()));
      widthValue.push_back(dep.isAuxiliary());
      widthValue.push_back(optToWord(dep.getSourceIndex()));
      widthValue.push_back(optToWord(dep.getDestinationIndex()));
      widthValue.push_back(optToWord(prob.getDistance(dep)));
      ++numDeps;
    }
    widthValue.push_back(-2 - numDeps);
  }
  return widthValue;
}

static bool isInnermostAffineFor(AffineForOp forOp);

namespace {
/// The memref itself plus every value derived from it through a view-like op
/// (memref.cast, subview, reinterpret_cast, expand/collapse_shape, ...),
/// transitively. `escaped`: some member has a use that is neither a plain
/// access nor a view - a call, an op with regions taking it (scf.for
/// iter_args), a terminator yielding it, or an op producing a memref we
/// cannot follow - so the set may be incomplete.
struct MemrefAliasInfo {
  SmallPtrSet<Value, 4> members;
  bool escaped = false;
};
} // namespace

/// A use through which the memref cannot flow anywhere else: an affine access
/// or a region-free, non-call op with declared effects and no memref result.
static bool isPlainMemrefUse(Operation *user) {
  if (isa<AffineReadOpInterface, AffineWriteOpInterface>(user))
    return true;
  if (isa<CallOpInterface>(user) || user->getNumRegions() != 0 ||
      user->hasTrait<OpTrait::IsTerminator>() ||
      !isa<MemoryEffectOpInterface>(user))
    return false;
  return llvm::none_of(user->getResultTypes(), [](Type typeValue) {
    return isa<BaseMemRefType>(typeValue);
  });
}

static MemrefAliasInfo collectMemrefAliases(Value mem) {
  MemrefAliasInfo info;
  SmallVector<Value> worklist{mem};
  info.members.insert(mem);
  while (!worklist.empty()) {
    Value valueHandle = worklist.pop_back_val();
    for (Operation *user : valueHandle.getUsers()) {
      if (isa<ViewLikeOpInterface>(user)) {
        for (Value resultValue : user->getResults())
          if (isa<BaseMemRefType>(resultValue.getType()) &&
              info.members.insert(resultValue).second)
            worklist.push_back(resultValue);
        continue;
      }
      if (!isPlainMemrefUse(user))
        info.escaped = true;
    }
  }
  return info;
}

/// True if some op inside `forOp` may write the memref through any member of
/// its alias set (or uses one opaquely), or if the memref has escaped.
static bool isMemrefWrittenInLoop(const MemrefAliasInfo &alias,
                                  AffineForOp forOp) {
  if (alias.escaped)
    return true;
  bool written = false;
  forOp.getBody()->walk([&](Operation *op) {
    if (isa<ViewLikeOpInterface>(op))
      return WalkResult::advance();
    for (Value opd : op->getOperands()) {
      if (!alias.members.contains(opd))
        continue;
      if (isa<AffineWriteOpInterface>(op)) {
        written = true;
        return WalkResult::interrupt();
      }
      if (isa<AffineReadOpInterface>(op))
        continue;
      auto eff = dyn_cast<MemoryEffectOpInterface>(op);
      if (!eff) {
        written = true;
        return WalkResult::interrupt();
      }
      SmallVector<MemoryEffects::EffectInstance> effects;
      eff.getEffectsOnValue(opd, effects);
      for (auto &entryValue : effects)
        if (!isa<MemoryEffects::Read>(entryValue.getEffect())) {
          written = true;
          return WalkResult::interrupt();
        }
    }
    return WalkResult::advance();
  });
  return written;
}

void AffineToLoopSchedule::hoistInvariantLoads() {
  SmallVector<AffineForOp> loops;
  getOperation().walk([&](AffineForOp forOp) {
    if (isInnermostAffineFor(forOp))
      loops.push_back(forOp);
  });

  DenseMap<Value, MemrefAliasInfo> aliasCache;
  auto aliasInfo = [&](Value mem) -> const MemrefAliasInfo & {
    auto it = aliasCache.find(mem);
    if (it == aliasCache.end())
      it = aliasCache.try_emplace(mem, collectMemrefAliases(mem)).first;
    return it->second;
  };

  unsigned hoistedLoads = 0, hoistedPure = 0;
  for (AffineForOp forOp : loops) {

    AffineForOp root = circt::hls_analysis::getFlattenedRoot(forOp);
    DenseSet<Value> invariant;
    auto isInvariantValue = [&](Value valueHandle) {
      return root.isDefinedOutsideOfLoop(valueHandle) ||
             invariant.contains(valueHandle);
    };
    DenseMap<Value, bool> writtenCache;
    auto writtenInLoop = [&](Value mem) {
      auto it = writtenCache.find(mem);
      if (it != writtenCache.end())
        return it->second;
      bool widthValue = isMemrefWrittenInLoop(aliasInfo(mem), root);
      writtenCache[mem] = widthValue;
      return widthValue;
    };

    SmallVector<Operation *> toHoist;
    for (Operation &op : forOp.getBody()->without_terminator()) {
      if (op.getNumRegions() != 0)
        continue;
      bool hoistable = false;
      if (auto load = dyn_cast<AffineLoadOp>(op)) {
        hoistable = llvm::all_of(load.getMapOperands(), isInvariantValue) &&
                    isInvariantValue(load.getMemRef()) &&
                    !writtenInLoop(load.getMemRef());
        if (hoistable)
          ++hoistedLoads;
      } else if (isMemoryEffectFree(&op) && isSpeculatable(&op) &&
                 op.getNumResults() > 0) {
        hoistable = llvm::all_of(op.getOperands(), isInvariantValue);
        if (hoistable)
          ++hoistedPure;
      }
      if (!hoistable)
        continue;
      toHoist.push_back(&op);
      for (Value resultValue : op.getResults())
        invariant.insert(resultValue);
    }

    for (Operation *op : toHoist)
      op->moveBefore(forOp);
  }
  LLVM_DEBUG(llvm::dbgs() << "hoisted " << hoistedLoads
                          << " loop-invariant affine.load and " << hoistedPure
                          << " pure ops out of innermost loops\n");
}

namespace {
enum class AddrRelation { Same, Disjoint, MayAlias };

struct AccessAddr {
  AffineMap map;
  SmallVector<Value, 4> operands;
  AccessAddr(AffineMap memoryOp, ValueRange opds)
      : map(memoryOp), operands(opds.begin(), opds.end()) {
    fullyComposeAffineMapAndOperands(&map, &operands);
    canonicalizeMapAndOperands(&map, &operands);
  }
};

/// What is known about one address of a memref at the current point of a
/// block.
struct KnownValue {
  AccessAddr addr;
  Value value;
  Operation *store;
  bool readSince;
};
} // namespace

static AddrRelation compareAddresses(const AccessAddr &arrayValue,
                                     const AccessAddr &buildPoint) {
  if (arrayValue.map.getNumResults() != buildPoint.map.getNumResults())
    return AddrRelation::MayAlias;
  AffineValueMap va(arrayValue.map, arrayValue.operands),
      vb(buildPoint.map, buildPoint.operands), diff;
  AffineValueMap::difference(va, vb, &diff);
  bool allZero = true;
  for (unsigned dimensionIndex = 0, elementCount = diff.getNumResults();
       dimensionIndex < elementCount; ++dimensionIndex) {
    auto candidateValue =
        dyn_cast<AffineConstantExpr>(diff.getResult(dimensionIndex));
    if (!candidateValue)
      allZero = false;
    else if (candidateValue.getValue() != 0)
      return AddrRelation::Disjoint;
  }
  return allZero ? AddrRelation::Same : AddrRelation::MayAlias;
}

static int64_t counterAttr(Operation *op, StringRef name) {
  if (auto arrayValue = op->getAttrOfType<IntegerAttr>(name))
    return arrayValue.getInt();
  return 0;
}

static void addCounterAttr(Operation *op, StringRef name, int64_t by) {
  if (by <= 0)
    return;
  op->setAttr(name, IntegerAttr::get(IntegerType::get(op->getContext(), 64),
                                     counterAttr(op, name) + by));
}

/// Memrefs whose SSA value identifies the storage: a local array or a
/// function argument. Two memref.get_global of one symbol are two values for
/// one memory, and a view or an iter_arg aliases its source: not tracked.
static bool isRootMemref(Value mem) {
  if (auto arg = dyn_cast<BlockArgument>(mem))
    return isa<func::FuncOp>(arg.getOwner()->getParentOp());
  return isa_and_present<memref::AllocaOp, memref::AllocOp>(
      mem.getDefiningOp());
}

void AffineToLoopSchedule::cleanupRedundantAccesses() {
  SmallVector<Block *> blocks;
  getOperation().walk([&](Block *buildPoint) { blocks.push_back(buildPoint); });

  DenseMap<Value, MemrefAliasInfo> aliasCache;
  auto aliasInfo = [&](Value mem) -> const MemrefAliasInfo & {
    auto it = aliasCache.find(mem);
    if (it == aliasCache.end())
      it = aliasCache.try_emplace(mem, collectMemrefAliases(mem)).first;
    return it->second;
  };

  unsigned merged = 0, forwarded = 0, removed = 0;
  for (Block *block : blocks) {
    DenseMap<Value, SmallVector<KnownValue, 8>> known;
    DenseMap<Value, Value> memberToRoot;
    auto forget = [&](Value mem) {
      auto it = memberToRoot.find(mem);
      if (it != memberToRoot.end())
        known.erase(it->second);
      known.erase(mem);
    };
    auto forgetOperands = [&](Operation *op) {
      for (Value valueHandle : op->getOperands())
        if (isa<BaseMemRefType>(valueHandle.getType()))
          forget(valueHandle);
    };

    auto trackable = [&](Value mem) -> bool {
      if (!isRootMemref(mem))
        return false;
      const MemrefAliasInfo &ai = aliasInfo(mem);
      if (ai.escaped)
        return false;
      if (!memberToRoot.count(mem))
        for (Value memoryOp : ai.members)
          memberToRoot[memoryOp] = mem;
      return true;
    };

    for (Operation &op : llvm::make_early_inc_range(*block)) {
      if (auto load = dyn_cast<AffineLoadOp>(op)) {
        Value mem = load.getMemRef();
        if (!trackable(mem)) {
          forget(mem);
          continue;
        }
        AccessAddr addr(load.getAffineMap(), load.getMapOperands());
        auto &vals = known[mem];
        KnownValue *same = nullptr;
        for (KnownValue &kv : vals) {
          AddrRelation rel = compareAddresses(addr, kv.addr);
          if (rel == AddrRelation::Same) {
            same = &kv;
            break;
          }
          if (rel == AddrRelation::MayAlias && kv.store)
            kv.readSince = true;
        }
        if (same && (same->store ? forwardStores : cseLoads)) {

          if (same->store) {
            addCounterAttr(same->store, "hls.forwarded_loads", 1);
            ++forwarded;
          } else {
            addCounterAttr(same->value.getDefiningOp(), "hls.merged_loads", 1);
            ++merged;
          }
          load.getResult().replaceAllUsesWith(same->value);
          load.erase();
          continue;
        }
        if (same) {
          if (same->store)
            same->readSince = true;
          continue;
        }
        vals.push_back({addr, load.getResult(), nullptr, false});
        continue;
      }
      if (auto store = dyn_cast<AffineStoreOp>(op)) {
        Value mem = store.getMemRef();
        if (!trackable(mem)) {
          forget(mem);
          continue;
        }
        AccessAddr addr(store.getAffineMap(), store.getMapOperands());
        auto &vals = known[mem];
        SmallVector<KnownValue, 8> kept;
        for (KnownValue &kv : vals) {
          AddrRelation rel = compareAddresses(addr, kv.addr);
          if (rel == AddrRelation::Disjoint) {
            kept.push_back(kv);
            continue;
          }
          if (rel == AddrRelation::Same && kv.store && !kv.readSince &&
              forwardStores) {

            addCounterAttr(&op, "hls.removed_stores",
                           1 + counterAttr(kv.store, "hls.removed_stores"));
            addCounterAttr(&op, "hls.forwarded_loads",
                           counterAttr(kv.store, "hls.forwarded_loads"));
            kv.store->erase();
            ++removed;
          }
        }
        vals = std::move(kept);
        vals.push_back(
            {addr, store.getValueToStore(), store.getOperation(), false});
        continue;
      }

      forgetOperands(&op);
      for (Region &region : op.getRegions())
        region.walk([&](Operation *inner) { forgetOperands(inner); });
    }
  }
  LLVM_DEBUG(llvm::dbgs() << "redundant-access cleanup: merged " << merged
                          << " loads, forwarded " << forwarded
                          << " loads from stores, removed " << removed
                          << " dead stores\n");
}

/// Returns true if `forOp` contains no loop of any kind anywhere in its body
/// (including inside ifs). MODIFIED (T3): an scf.for / scf.while inside an
/// affine.for used to make that affine.for "innermost" and sent it to the
/// scheduler, which has no operator type for the inner loop; such a loop is
/// sequential control around the inner loop, like an affine.for nest whose
/// inner loop is the pipelined one.
static bool isInnermostAffineFor(AffineForOp forOp) {
  bool hasNested = false;
  forOp.getBody()->walk([&](Operation *op) {
    if (!isa<LoopLikeOpInterface>(op))
      return WalkResult::advance();
    hasNested = true;
    return WalkResult::interrupt();
  });
  return !hasNested;
}

/// MODIFIED (T3): the pipeline terminator requires every yielded value to be
/// produced by a pipeline stage, and the stage plumbing only finds a value
/// yielded straight from a multicycle op (an fadd accumulator) when the
/// terminator happens to be scheduled when that op completes. Every yielded
/// value therefore goes through an identity `arith.select %true, %v, %v`
/// (a comb op, zero latency, scheduled once the value is ready): a loop that
/// yields one of its own iter_args or a value defined outside it (a shift
/// register: `affine.yield %new, %prev`) and the promoted `acc[k] +=`
/// accumulators of an unrolled body are both handled by that.
static void materializeYieldedValues(AffineForOp forOp) {
  auto yield = cast<AffineYieldOp>(forOp.getBody()->getTerminator());
  Value trueVal;
  OpBuilder buildPoint(yield);
  for (OpOperand &opd : yield->getOpOperands()) {
    Value valueHandle = opd.get();
    if (!trueVal) {
      OpBuilder ob(forOp);
      trueVal =
          arith::ConstantOp::create(ob, forOp.getLoc(), ob.getBoolAttr(true));
    }
    opd.set(arith::SelectOp::create(buildPoint, yield.getLoc(), trueVal,
                                    valueHandle, valueHandle));
  }
}

/// MODIFIED: Returns true if the perfect band has a rectangular iteration
/// space, i.e. every non-outermost loop's bounds are invariant with respect
/// to all enclosing IVs in the band. Flattening via coalesceLoops is only
/// valid in that case (trip count = product of per-loop trip counts);
/// affine::coalesceLoops does NOT reject non-rectangular nests gracefully -
/// it hoists the upper-bound product above the outermost loop, where an
/// outer-IV-dependent bound operand is undefined, and corrupts the IR
/// (null operands) instead of returning failure. So we must check here.
static bool isRectangularBand(ArrayRef<AffineForOp> band) {

  AffineForOp outermost = band.front();
  Region &outerRegion = outermost.getRegion();
  for (AffineForOp loop : band.drop_front()) {
    if (!areValuesDefinedAbove(loop.getLowerBoundOperands(), outerRegion) ||
        !areValuesDefinedAbove(loop.getUpperBoundOperands(), outerRegion))
      return false;
  }
  return true;
}

ModuloProblem AffineToLoopSchedule::getModuloProblem(CyclicProblem &prob) {
  ModuloProblem modProb(prob.getContainingOp());
  for (auto *op : prob.getOperations()) {
    auto opr = prob.getLinkedOperatorType(op);
    if (opr.has_value()) {
      modProb.setLinkedOperatorType(op, opr.value());
      auto latency = prob.getLatency(opr.value());
      if (latency.has_value())
        modProb.setLatency(opr.value(), latency.value());
    }
    auto rsrc = prob.getLinkedResourceTypes(op);
    if (rsrc.has_value())
      modProb.setLinkedResourceTypes(op, rsrc.value());
    modProb.insertOperation(op);
  }

  for (auto *op : prob.getOperations()) {
    for (auto dep : prob.getDependences(op)) {
      if (dep.isAuxiliary()) {
        auto depInserted = modProb.insertDependence(dep);
        assert(succeeded(depInserted));
        (void)depInserted;
      }
      auto distance = prob.getDistance(dep);
      if (distance.has_value())
        modProb.setDistance(dep, distance.value());
    }
  }

  return modProb;
}

/// MODIFIED: Flatten perfectly nested loop bands into single loops using
/// affine::coalesceLoops. This runs *before* dependence analysis so all
/// later analyses see the flattened IR.
///
/// coalesceLoops introduces delinearization of the flat IV via affine.apply
/// ops containing floordiv/mod; those are expanded to arith ops in
/// lowerAffineStructures and scheduled as multicycle/comb ops.
///
/// Bands that cannot be coalesced (e.g. inner bounds depending on outer
/// IVs) are simply left alone; their innermost loops are pipelined in place
/// later, with the outer loops remaining as sequential affine.for control.
void AffineToLoopSchedule::coalescePerfectNests() {

  SmallVector<SmallVector<AffineForOp>> bands;
  DenseSet<Operation *> visited;
  getOperation().walk<WalkOrder::PreOrder>([&](AffineForOp root) {
    if (visited.contains(root))
      return;
    SmallVector<AffineForOp> band;
    getPerfectlyNestedLoops(band, root);
    for (AffineForOp loop : band)
      visited.insert(loop);

    bool innerResults = llvm::any_of(
        ArrayRef<AffineForOp>(band).drop_front(),
        [](AffineForOp loop) { return loop.getNumResults() != 0; });
    if (band.size() > 1 && isInnermostAffineFor(band.back()) &&
        isRectangularBand(band) && !innerResults)
      bands.push_back(std::move(band));
  });

  for (auto &band : bands) {

    AffineForOp innermost = band.back();
    Attribute pipelineTag =
        innermost->getAttr(circt::hls_analysis::kLoopPipelineAttr);
    Attribute pipelineOff =
        innermost->getAttr(circt::hls_analysis::kLoopPipelineOffAttr);
    Attribute autoUnrolled =
        innermost->getAttr(circt::hls_analysis::kLoopAutoUnrolledAttr);
    Attribute unrollPartial =
        innermost->getAttr(circt::hls_analysis::kLoopUnrollPartialAttr);
    unsigned flattened = circt::hls_analysis::getFlattenedParents(innermost);
    unsigned levels = band.size() - 1;
    if (failed(coalesceLoops(MutableArrayRef<AffineForOp>(band)))) {
      LLVM_DEBUG(llvm::dbgs()
                 << "Could not coalesce perfect nest rooted at "
                 << *band.front()
                 << "; falling back to innermost-loop pipelining\n");
      continue;
    }
    AffineForOp outer = band.front();
    if (pipelineTag)
      outer->setAttr(circt::hls_analysis::kLoopPipelineAttr, pipelineTag);
    if (pipelineOff)
      outer->setAttr(circt::hls_analysis::kLoopPipelineOffAttr, pipelineOff);
    if (autoUnrolled)
      outer->setAttr(circt::hls_analysis::kLoopAutoUnrolledAttr, autoUnrolled);
    if (unrollPartial)
      outer->setAttr(circt::hls_analysis::kLoopUnrollPartialAttr,
                     unrollPartial);
    if (flattened > levels)
      outer->setAttr(circt::hls_analysis::kLoopFlattenedParentsAttr,
                     IntegerAttr::get(IntegerType::get(outer.getContext(), 64),
                                      flattened - levels));
    else
      outer->removeAttr(circt::hls_analysis::kLoopFlattenedParentsAttr);
  }
}

static void anchorUntrackedSideEffects(AffineForOp forOp,
                                       ModuloProblem &problem) {
  Operation *anchor = forOp.getBody()->getTerminator();

  SmallVector<Operation *> ops(problem.getOperations().begin(),
                               problem.getOperations().end());

  DenseSet<Operation *> hasSuccessor;
  for (Operation *op : ops)
    for (auto dep : problem.getDependences(op))
      if (Operation *src = dep.getSource())
        hasSuccessor.insert(src);

  for (Operation *op : ops) {
    if (op == anchor || hasSuccessor.contains(op))
      continue;
    Problem::Dependence dep(op, anchor);
    auto inserted = problem.insertDependence(dep);
    (void)inserted;
    assert(succeeded(inserted) && "failed to anchor sink");
  }
}

static void chainSharedCalleeInstances(AffineForOp forOp,
                                       ModuloProblem &problem) {
  auto parent = forOp->getParentOfType<func::FuncOp>();
  if (!parent)
    return;
  llvm::MapVector<Operation *, SmallVector<Operation *>> byCallee;
  forOp.getBody()->walk([&](CallOpInterface callSite) {
    if (!problem.hasOperation(callSite.getOperation()))
      return;
    if (func::FuncOp callee = resolveDefinedCallee(callSite))
      byCallee[callee.getOperation()].push_back(callSite.getOperation());
  });

  auto boundBySelf = [&](Operation *callSite) {
    auto occ = callSite->getAttrOfType<IntegerAttr>(
        circt::hls_analysis::kCallOccupancyAttr);
    if (!occ || occ.getInt() <= 1)
      return;
    Problem::Dependence self(callSite, callSite);
    if (succeeded(problem.insertDependence(self)))
      problem.setDistance(self, 1);
  };

  auto holdForDepth = [&](Operation *callSite) {
    unsigned depth = 0;
    if (auto dimensionIndex = callSite->getAttrOfType<IntegerAttr>(
            circt::hls_analysis::kCallDepthAttr))
      depth =
          static_cast<unsigned>(std::max<int64_t>(1, dimensionIndex.getInt()));
    else if (auto opr = problem.getLinkedOperatorType(callSite))
      depth = problem.getLatency(*opr).value_or(0) + 1;
    if (depth == 0)
      return;
    Problem::OperatorType held = problem.getOrInsertOperatorType(
        "call_kept_held_" + std::to_string(depth));
    problem.setLatency(held, depth);
    problem.setLinkedOperatorType(callSite, held);
  };
  for (auto &[calleeOp, sites] : byCallee) {
    if (sites.size() < 2) {
      boundBySelf(sites.front());
      continue;
    }
    auto callee = cast<func::FuncOp>(calleeOp);
    SmallVector<unsigned> group;
    groupConcurrentCalls(parent, sites, allocationLimit(parent, callee), group);
    llvm::MapVector<unsigned, SmallVector<Operation *>> chains;
    for (unsigned loopIndex = 0; loopIndex < sites.size(); ++loopIndex)
      chains[group[loopIndex]].push_back(sites[loopIndex]);
    for (auto &[globalOp, chain] : chains) {
      if (chain.size() < 2) {
        boundBySelf(chain.front());
        continue;
      }
      for (Operation *callSite : chain)
        holdForDepth(callSite);
      for (unsigned keyValue = 1; keyValue < chain.size(); ++keyValue)
        (void)problem.insertDependence(
            Problem::Dependence(chain[keyValue - 1], chain[keyValue]));
      Problem::Dependence back(chain.back(), chain.front());
      if (succeeded(problem.insertDependence(back)))
        problem.setDistance(back, 1);
    }
  }
}

static void anchorRegionCaptures(AffineForOp forOp, ModuloProblem &problem) {
  Block *body = forOp.getBody();
  for (Operation &regionOp : body->without_terminator()) {
    if (regionOp.getNumRegions() == 0 || !problem.hasOperation(&regionOp))
      continue;
    regionOp.walk([&](Operation *nested) {
      if (nested == &regionOp)
        return;
      for (Value valueHandle : nested->getOperands()) {
        Operation *def = valueHandle.getDefiningOp();
        if (!def || def == &regionOp || def->getBlock() != body ||
            !problem.hasOperation(def))
          continue;
        auto inserted =
            problem.insertDependence(Problem::Dependence(def, &regionOp));
        (void)inserted;
      }
    });
  }
}

/// MODIFIED: Fully unroll constant-trip innermost reduction loops so the
/// loop *above* them becomes the pipelineable innermost loop, matching
/// Vitis HLS behavior ("pipeline 2nd-level loop, unroll lower loop"). The
/// unrolled inner body exposes one memref.load per (bank, iteration) so the
/// partitioned arrays are actually read in parallel; otherwise the inner
/// reduction would serialize and the array_partition would be wasted.
///
/// Targets only innermost affine.for loops with a small constant trip count
/// that carry a reduction (iter_args)
void AffineToLoopSchedule::unrollInnerReductions() {
  SmallVector<AffineForOp> targets;

  unsigned kMaxUnrollTrip = 64;

  getOperation().walk([&](AffineForOp forOp) {
    if (!isInnermostAffineFor(forOp))
      return;

    if (forOp.getNumIterOperands() == 0)
      return;
    auto tc = getConstantTripCount(forOp);
    if (!tc || *tc == 0)
      return;

    if (*tc > kMaxUnrollTrip)
      return;
    targets.push_back(forOp);
  });

  for (AffineForOp forOp : targets) {
    if (failed(loopUnrollFull(forOp))) {
      LLVM_DEBUG(llvm::dbgs() << "could not fully unroll inner reduction: "
                              << *forOp << "\n");
    }
  }
}

namespace {

struct PureOpInfo : public llvm::DenseMapInfo<Operation *> {
  static unsigned getHashValue(const Operation *opC) {
    return OperationEquivalence::computeHash(
        const_cast<Operation *>(opC), OperationEquivalence::directHashValue,
        OperationEquivalence::ignoreHashValue,
        OperationEquivalence::IgnoreLocations);
  }
  static bool isEqual(const Operation *lhsC, const Operation *rhsC) {
    auto *lhs = const_cast<Operation *>(lhsC);
    auto *rhs = const_cast<Operation *>(rhsC);
    if (lhs == rhs)
      return true;

    if (lhs == getEmptyKey() || rhs == getEmptyKey())
      return false;
    return OperationEquivalence::isEquivalentTo(
        lhs, rhs, OperationEquivalence::IgnoreLocations);
  }
};
} // namespace

/// Merge every later duplicate of a side-effect-free, region-free,
/// non-terminator op into the first occurrence within the same block. Nested
/// blocks are processed with their own scope. Ops with memory effects (loads,
/// stores, store_enables) are never candidates, so the number and order of
/// memory accesses is preserved exactly. Returns the number of ops erased.
static unsigned cseBlockPureOps(Block &block) {
  unsigned merged = 0;
  DenseSet<Operation *, PureOpInfo> seen;
  for (Operation &op : llvm::make_early_inc_range(block)) {
    for (Region &region : op.getRegions())
      for (Block &nested : region)
        merged += cseBlockPureOps(nested);
    if (op.getNumRegions() != 0 || op.getNumResults() == 0 ||
        op.hasTrait<OpTrait::IsTerminator>() || !isMemoryEffectFree(&op))
      continue;
    auto [it, inserted] = seen.insert(&op);
    if (inserted)
      continue;
    op.replaceAllUsesWith(*it);
    op.erase();
    ++merged;
  }
  return merged;
}

namespace {
class FastModuloScheduler {
public:
  explicit FastModuloScheduler(ModuloProblem &prob) : prob(prob) {}

  /// Returns the number of operations linked to a resource with a limit.
  static unsigned countLimitedOps(ModuloProblem &prob);

  LogicalResult schedule(unsigned maxIIBumps);

private:
  struct Edge {
    unsigned src;
    unsigned latency;
    unsigned distance;
  };

  ModuloProblem &prob;
  SmallVector<Operation *> ops;
  SmallVector<unsigned> latency;
  SmallVector<SmallVector<Edge, 4>> preds;
  SmallVector<SmallVector<Problem::ResourceType, 1>> rsrcs;
  SmallVector<unsigned> topo;

  LogicalResult build();
  unsigned resMinII() const;
  /// Longest-path ASAP times at `ii`; false on a positive cycle.
  bool asapTimes(unsigned ii, SmallVectorImpl<int64_t> &asap) const;
  /// Smallest II >= lo without a positive cycle, or 0 if there is none.
  unsigned recMinII(unsigned lo) const;
  bool tryII(unsigned ii, SmallVectorImpl<unsigned> &start);
};
} // namespace

unsigned FastModuloScheduler::countLimitedOps(ModuloProblem &prob) {
  unsigned elementCount = 0;
  for (Operation *op : prob.getOperations()) {
    auto lr = prob.getLinkedResourceTypes(op);
    if (!lr)
      continue;
    if (llvm::any_of(*lr, [&](Problem::ResourceType resultValue) {
          return prob.getLimit(resultValue).value_or(0) > 0;
        }))
      ++elementCount;
  }
  return elementCount;
}

LogicalResult FastModuloScheduler::build() {
  DenseMap<Operation *, unsigned> index;
  for (Operation *op : prob.getOperations()) {
    index[op] = ops.size();
    ops.push_back(op);
  }
  unsigned elementCount = ops.size();
  latency.assign(elementCount, 0);
  preds.assign(elementCount, {});
  rsrcs.assign(elementCount, {});
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex) {
    auto opr = prob.getLinkedOperatorType(ops[loopIndex]);
    if (!opr)
      return failure();
    auto lat = prob.getLatency(*opr);
    if (!lat)
      return failure();
    latency[loopIndex] = *lat;
    if (auto lr = prob.getLinkedResourceTypes(ops[loopIndex]))
      for (Problem::ResourceType resultValue : *lr)
        if (prob.getLimit(resultValue).value_or(0) > 0)
          rsrcs[loopIndex].push_back(resultValue);
  }

  SmallVector<unsigned> indeg(elementCount, 0);
  SmallVector<SmallVector<unsigned, 4>> succ0(elementCount);
  for (unsigned innerIndex = 0; innerIndex < elementCount; ++innerIndex) {
    for (auto &dep : prob.getDependences(ops[innerIndex])) {
      auto it = index.find(dep.getSource());
      if (it == index.end())
        continue;
      unsigned loopIndex = it->second;
      unsigned dist = prob.getDistance(dep).value_or(0);
      preds[innerIndex].push_back({loopIndex, latency[loopIndex], dist});
      if (dist == 0) {
        succ0[loopIndex].push_back(innerIndex);
        ++indeg[innerIndex];
      }
    }
  }

  std::priority_queue<unsigned, std::vector<unsigned>, std::greater<unsigned>>
      ready;
  for (unsigned loopIndex = 0; loopIndex < elementCount; ++loopIndex)
    if (indeg[loopIndex] == 0)
      ready.push(loopIndex);
  while (!ready.empty()) {
    unsigned loopIndex = ready.top();
    ready.pop();
    topo.push_back(loopIndex);
    for (unsigned innerIndex : succ0[loopIndex])
      if (--indeg[innerIndex] == 0)
        ready.push(innerIndex);
  }

  return success(topo.size() == elementCount);
}

unsigned FastModuloScheduler::resMinII() const {
  DenseMap<Problem::ResourceType, unsigned> symbolUses;
  for (auto &rs : rsrcs)
    for (Problem::ResourceType resultValue : rs)
      ++symbolUses[resultValue];
  unsigned ii = 1;
  for (auto &[resultValue, count] : symbolUses) {
    unsigned limit = *prob.getLimit(resultValue);
    ii = std::max(ii, (count + limit - 1) / limit);
  }
  return ii;
}

bool FastModuloScheduler::asapTimes(unsigned ii,
                                    SmallVectorImpl<int64_t> &asap) const {
  unsigned elementCount = ops.size();
  asap.assign(elementCount, 0);
  bool changed = true;

  for (unsigned round = 0; changed && round <= elementCount; ++round) {
    changed = false;
    for (unsigned innerIndex : topo)
      for (const Edge &entryValue : preds[innerIndex]) {
        int64_t cand = asap[entryValue.src] +
                       static_cast<int64_t>(entryValue.latency) -
                       static_cast<int64_t>(entryValue.distance) * ii;
        if (cand > asap[innerIndex]) {
          asap[innerIndex] = cand;
          changed = true;
        }
      }
  }
  return !changed;
}

unsigned FastModuloScheduler::recMinII(unsigned lo) const {
  SmallVector<int64_t> asap;
  if (asapTimes(lo, asap))
    return lo;

  uint64_t bound = 0;
  for (unsigned lat : latency)
    bound += lat;
  bound = std::max<uint64_t>(bound, static_cast<uint64_t>(lo) + 1);

  uint64_t infeasible = lo, hi = lo;
  for (uint64_t step = 1;; step *= 2) {
    hi = std::min(static_cast<uint64_t>(lo) + step, bound);
    if (asapTimes(static_cast<unsigned>(hi), asap))
      break;
    if (hi >= bound)
      return 0;
    infeasible = hi;
  }

  while (hi - infeasible > 1) {
    uint64_t mid = infeasible + (hi - infeasible) / 2;
    if (asapTimes(static_cast<unsigned>(mid), asap))
      hi = mid;
    else
      infeasible = mid;
  }
  return static_cast<unsigned>(hi);
}

bool FastModuloScheduler::tryII(unsigned ii, SmallVectorImpl<unsigned> &start) {
  unsigned elementCount = ops.size();

  SmallVector<int64_t> asap;
  if (!asapTimes(ii, asap))
    return false;

  SmallVector<int64_t> st(elementCount, -1);
  DenseMap<Problem::ResourceType, SmallVector<unsigned>> mrt;
  for (unsigned innerIndex : topo) {
    int64_t est = asap[innerIndex];
    for (const Edge &entryValue : preds[innerIndex])
      if (st[entryValue.src] >= 0)
        est = std::max(est, st[entryValue.src] +
                                static_cast<int64_t>(entryValue.latency) -
                                static_cast<int64_t>(entryValue.distance) * ii);
    if (rsrcs[innerIndex].empty()) {
      st[innerIndex] = est;
      continue;
    }
    bool placed = false;
    for (unsigned keyValue = 0; keyValue < ii && !placed; ++keyValue) {
      int64_t typeValue = est + keyValue;
      unsigned slot = static_cast<unsigned>(typeValue % ii);
      bool free = true;
      for (Problem::ResourceType resultValue : rsrcs[innerIndex]) {
        auto &tab = mrt[resultValue];
        if (tab.empty())
          tab.assign(ii, 0);
        if (tab[slot] >= *prob.getLimit(resultValue)) {
          free = false;
          break;
        }
      }
      if (!free)
        continue;
      for (Problem::ResourceType resultValue : rsrcs[innerIndex])
        ++mrt[resultValue][slot];
      st[innerIndex] = typeValue;
      placed = true;
    }
    if (!placed)
      return false;
  }

  for (unsigned innerIndex = 0; innerIndex < elementCount; ++innerIndex)
    for (const Edge &entryValue : preds[innerIndex])
      if (st[entryValue.src] + static_cast<int64_t>(entryValue.latency) >
          st[innerIndex] + static_cast<int64_t>(entryValue.distance) * ii)
        return false;

  start.clear();
  for (int64_t typeValue : st)
    start.push_back(static_cast<unsigned>(typeValue));
  return true;
}

LogicalResult FastModuloScheduler::schedule(unsigned maxIIBumps) {
  if (failed(build()))
    return failure();
  unsigned resII = resMinII();
  unsigned ii = recMinII(resII);
  if (ii == 0)
    return failure();
  LLVM_DEBUG(llvm::dbgs() << "fast modulo scheduler: ResMinII = " << resII
                          << ", recurrence-feasible II = " << ii << "\n");
  SmallVector<unsigned> start;

  for (unsigned bumps = 0; bumps <= maxIIBumps; ++bumps, ++ii) {
    if (!tryII(ii, start))
      continue;
    prob.setInitiationInterval(ii);
    for (unsigned loopIndex = 0, elementCount = ops.size();
         loopIndex < elementCount; ++loopIndex)
      prob.setStartTime(ops[loopIndex], start[loopIndex]);
    LLVM_DEBUG(llvm::dbgs() << "fast modulo schedule: " << ops.size()
                            << " ops, II = " << ii << "\n");
    return success();
  }
  return failure();
}

void AffineToLoopSchedule::runOnOperation() {

  coalescePerfectNests();

  if (cseLoads || forwardStores)
    cleanupRedundantAccesses();
  if (hoistInvariant)
    hoistInvariantLoads();

  getOperation().walk([&](AffineForOp forOp) {
    if (isInnermostAffineFor(forOp))
      materializeYieldedValues(forOp);
  });

  {
    SmallVector<Operation *> dead;
    getOperation().walk([&](Operation *op) {
      if (isOpTriviallyDead(op))
        dead.push_back(op);
    });
    for (Operation *op : llvm::reverse(dead))
      op->erase();
  }

  auto dependenceAnalysis = getAnalysis<InnermostLoopDependenceAnalysis>();
  numDepPairs += dependenceAnalysis.getCounters().pairs;
  numDepTests += dependenceAnalysis.getCounters().tests;
  numDeps += dependenceAnalysis.getCounters().dependences;

  if (failed(lowerAffineStructures(dependenceAnalysis)))
    return signalPassFailure();

  if (cseBeforeSchedule) {
    unsigned merged = 0;
    for (Block &block : getOperation().getBody())
      merged += cseBlockPureOps(block);
    LLVM_DEBUG(llvm::dbgs() << "pre-schedule CSE merged " << merged
                            << " side-effect-free ops\n");
  }

  schedulingAnalysis = &getAnalysis<CyclicSchedulingAnalysis>();

  auto &bramClass = getAnalysis<BRAMClassification>();

  SmallVector<AffineForOp> innermostLoops;
  getOperation().walk([&](AffineForOp forOp) {
    if (forOp->hasAttr(circt::hls_analysis::kLoopCallBoundaryAttr))
      return;
    if (isInnermostAffineFor(forOp))
      innermostLoops.push_back(forOp);
  });

  scheduleCache.clear();
  for (AffineForOp loop : innermostLoops) {
    ModuloProblem moduloProblem =
        getModuloProblem(schedulingAnalysis->getProblem(loop));

    if (failed(populateOperatorTypes(loop, moduloProblem, bramClass)))
      continue;

    anchorRegionCaptures(loop, moduloProblem);
    chainSharedCalleeInstances(loop, moduloProblem);
    anchorUntrackedSideEffects(loop, moduloProblem);

    if (failed(solveSchedulingProblem(loop, moduloProblem)))
      return signalPassFailure();

    if (failed(createLoopSchedulePipeline(loop, moduloProblem)))
      return signalPassFailure();
  }
}

/// Apply the affine map from an 'affine.load' operation to its operands, and
/// feed the results to a newly created 'memref.load' operation (which replaces
/// the original 'affine.load').
/// The `hls.*` discardable attributes of an affine access (the counters the
/// redundant-access cleanup left on it) that its lowered form keeps, so that
/// --bram-debug can still report them.
static SmallVector<NamedAttribute> hlsAttrsOf(Operation *op) {
  SmallVector<NamedAttribute> out;
  for (NamedAttribute arrayValue : op->getDiscardableAttrs())
    if (arrayValue.getName().strref().starts_with("hls."))
      out.push_back(arrayValue);
  return out;
}

static void setAttrs(Operation *op, ArrayRef<NamedAttribute> attrs) {
  for (const NamedAttribute &arrayValue : attrs)
    op->setAttr(arrayValue.getName(), arrayValue.getValue());
}

/// Also replaces the affine load with the memref load in dependenceAnalysis.
/// TODO(mikeurbach): this is copied from AffineToStandard, see if we can reuse.
class AffineLoadLowering : public OpConversionPattern<AffineLoadOp> {
public:
  AffineLoadLowering(MLIRContext *context,
                     MemoryDependenceAnalysis &dependenceAnalysis)
      : OpConversionPattern(context), dependenceAnalysis(dependenceAnalysis) {}

  LogicalResult
  matchAndRewrite(AffineLoadOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {

    SmallVector<Value, 8> indices(op.getMapOperands());
    auto resultOperands =
        expandAffineMap(rewriter, op.getLoc(), op.getAffineMap(), indices);
    if (!resultOperands)
      return failure();

    SmallVector<NamedAttribute> hlsAttrs = hlsAttrsOf(op);
    auto memrefLoad = rewriter.replaceOpWithNewOp<memref::LoadOp>(
        op, op.getMemRef(), *resultOperands);
    setAttrs(memrefLoad, hlsAttrs);

    dependenceAnalysis.replaceOp(op, memrefLoad);

    return success();
  }

private:
  MemoryDependenceAnalysis &dependenceAnalysis;
};

/// Apply the affine map from an 'affine.store' operation to its operands, and
/// feed the results to a newly created 'memref.store' operation (which
/// replaces the original 'affine.store').
/// Also replaces the affine store with the memref store in dependenceAnalysis.
/// TODO(mikeurbach): this is copied from AffineToStandard, see if we can reuse.
class AffineStoreLowering : public OpConversionPattern<AffineStoreOp> {
public:
  AffineStoreLowering(MLIRContext *context,
                      MemoryDependenceAnalysis &dependenceAnalysis)
      : OpConversionPattern(context), dependenceAnalysis(dependenceAnalysis) {}

  LogicalResult
  matchAndRewrite(AffineStoreOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {

    SmallVector<Value, 8> indices(op.getMapOperands());
    auto maybeExpandedMap =
        expandAffineMap(rewriter, op.getLoc(), op.getAffineMap(), indices);
    if (!maybeExpandedMap)
      return failure();

    SmallVector<NamedAttribute> hlsAttrs = hlsAttrsOf(op);
    auto memrefStore = rewriter.replaceOpWithNewOp<memref::StoreOp>(
        op, op.getValueToStore(), op.getMemRef(), *maybeExpandedMap);
    setAttrs(memrefStore, hlsAttrs);

    dependenceAnalysis.replaceOp(op, memrefStore);

    return success();
  }

private:
  MemoryDependenceAnalysis &dependenceAnalysis;
};

static Value materializeIntegerSet(OpBuilder &buildPoint, Location loc,
                                   IntegerSet set, ValueRange setOperands) {
  if (set.getNumConstraints() == 0)
    return arith::ConstantIntOp::create(buildPoint, loc, 1, 1);

  Value zero = arith::ConstantIndexOp::create(buildPoint, loc, 0);
  Value acc;
  for (unsigned loopIndex = 0, entryValue = set.getNumConstraints();
       loopIndex < entryValue; ++loopIndex) {
    AffineExpr candidateValue = set.getConstraint(loopIndex);
    bool isEq = set.isEq(loopIndex);
    auto cMap =
        AffineMap::get(set.getNumDims(), set.getNumSymbols(), candidateValue);
    Value lhs = affine::AffineApplyOp::create(buildPoint, loc, cMap,
                                              llvm::to_vector(setOperands));
    Value cmp = arith::CmpIOp::create(
        buildPoint, loc,
        isEq ? arith::CmpIPredicate::eq : arith::CmpIPredicate::sge, lhs, zero);
    acc = acc ? arith::AndIOp::create(buildPoint, loc, acc, cmp).getResult()
              : cmp;
  }
  return acc;
}

struct AffineStoreEnableLowering
    : public OpConversionPattern<hls_analysis::AffineStoreEnableOp> {
  AffineStoreEnableLowering(MLIRContext *context, MemoryDependenceAnalysis &da)
      : OpConversionPattern(context), dependenceAnalysis(da) {}

  LogicalResult
  matchAndRewrite(AffineStoreEnableOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    Location loc = op.getLoc();

    Value en = materializeIntegerSet(rewriter, loc, op.getCondition(),
                                     adaptor.getSetOperands());
    if (!en)
      return rewriter.notifyMatchFailure(op, "could not materialize predicate");

    auto indexValue = expandAffineMap(
        rewriter, loc, op.getMap(), llvm::to_vector(adaptor.getMapOperands()));
    if (!indexValue)
      return rewriter.notifyMatchFailure(op, "could not expand access map");

    auto lowered = rewriter.replaceOpWithNewOp<hls_analysis::StoreEnableOp>(
        op, adaptor.getValue(), en, adaptor.getMemref(), *indexValue);

    dependenceAnalysis.replaceOp(op, lowered);
    return success();
  }

private:
  MemoryDependenceAnalysis &dependenceAnalysis;
};

/// Hoists computation out of scf::IfOp branches, turning the if into a
/// mux-like operation and exposing concurrent execution of its branches (was
/// the IfOpHoisting conversion pattern). Runs on the whole function after the
/// conversion: innermost ifs first (post-order), each branch's ops moved in
/// front of the if in order (then-branch, then else-branch), leaving the
/// yields.
/// MODIFIED (T6): a memory access moved out of an arm records it in
/// `hls.if_arms` (LoopPragmas.h), so that --bram-analysis still knows that the
/// two arms of one if never run together (Vitis predicates them and binds the
/// two to one port: sp_o_ifarms / sp_o_ifst, VITIS_NOTES.md N12). Read only by
/// the opt-in --bram-seq-dual-port; no estimate depends on it otherwise.
static void hoistIfBodies(Operation *root) {
  SmallVector<IfOp> ifs;
  root->walk<WalkOrder::PostOrder>([&](IfOp op) { ifs.push_back(op); });
  int64_t ifId = 0;
  for (IfOp op : ifs) {
    ++ifId;
    int64_t arm = -1;
    for (Block *blk : {op.thenBlock(), op.elseBlock()}) {
      ++arm;
      if (!blk)
        continue;
      for (Operation &inner :
           llvm::make_early_inc_range(blk->without_terminator())) {

        if (isa<memref::LoadOp, memref::StoreOp, hls_analysis::StoreEnableOp,
                CallOpInterface>(inner)) {
          SmallVector<int64_t> arms;
          if (auto prev = inner.getAttrOfType<DenseI64ArrayAttr>(
                  circt::hls_analysis::kIfArmsAttr))
            arms.append(prev.asArrayRef().begin(), prev.asArrayRef().end());
          arms.push_back(ifId);
          arms.push_back(arm);
          inner.setAttr(circt::hls_analysis::kIfArmsAttr,
                        DenseI64ArrayAttr::get(inner.getContext(), arms));
        }
        inner.moveBefore(op);
      }
    }
  }
}

/// Helper to mark AffineYieldOp legal, unless it is the terminator of a
/// partially converted scf::IfOp (an affine.if lowered to scf.if). MODIFIED
/// (T4): the immediate parent only - the yield of an affine.for nested in an
/// scf.if stays an affine.yield (it used to be converted to an scf.yield when
/// the if was not hoisted away first, which broke the loop).
static bool yieldOpLegalityCallback(AffineYieldOp op) {
  return !isa<IfOp>(op->getParentOp());
}

/// After analyzing memory dependences, and before creating the schedule, we
/// want to materialize affine operations with arithmetic, scf, and memref
/// operations, which make the condition computation of addresses, etc.
/// explicit. This is important so the schedule can consider potentially
/// complex computations in the condition of ifs, or the addresses of loads
/// and stores. The dependence analysis will be updated so the dependences
/// from the affine loads and stores are now on the memref loads and stores.
/// Folds the affine.apply ops that feed a bound of `forOp` into the bound map.
/// lowerAffineStructures expands every affine.apply into arith ops, and an
/// arith value computed inside a loop is no valid affine dimension or symbol,
/// so an affine.for left in place (a sequential loop) whose bound read such an
/// apply would no longer verify: polybench nussinov's `for (k = i + 1; k < j;
/// k++)`, whose `j` is an apply of the enclosing loops' counters ("operand
/// cannot be used as a dimension id", W8b). Loops whose bounds read no apply
/// are left untouched.
static void composeBoundApplies(AffineForOp forOp) {
  auto readsApply = [](ValueRange operands) {
    return llvm::any_of(operands, [](Value v) {
      return v.getDefiningOp<AffineApplyOp>() != nullptr;
    });
  };
  if (readsApply(forOp.getLowerBoundOperands())) {
    AffineMap map = forOp.getLowerBoundMap();
    SmallVector<Value> operands(forOp.getLowerBoundOperands());
    affine::fullyComposeAffineMapAndOperands(&map, &operands);
    affine::canonicalizeMapAndOperands(&map, &operands);
    forOp.setLowerBound(operands, map);
  }
  if (readsApply(forOp.getUpperBoundOperands())) {
    AffineMap map = forOp.getUpperBoundMap();
    SmallVector<Value> operands(forOp.getUpperBoundOperands());
    affine::fullyComposeAffineMapAndOperands(&map, &operands);
    affine::canonicalizeMapAndOperands(&map, &operands);
    forOp.setUpperBound(operands, map);
  }
}

LogicalResult AffineToLoopSchedule::lowerAffineStructures(
    MemoryDependenceAnalysis &dependenceAnalysis) {
  auto *context = &getContext();
  auto op = getOperation();
  op.walk([](AffineForOp forOp) { composeBoundApplies(forOp); });

  ConversionTarget target(*context);
  target.addLegalDialect<AffineDialect, ArithDialect, MemRefDialect, SCFDialect,
                         HLSDialect>();

  target.addIllegalOp<AffineApplyOp, AffineStoreEnableOp, AffineIfOp,
                      AffineLoadOp, AffineStoreOp>();
  target.addDynamicallyLegalOp<AffineYieldOp>(yieldOpLegalityCallback);

  RewritePatternSet patterns(context);
  populateAffineToStdConversionPatterns(patterns);
  patterns.add<AffineLoadLowering>(context, dependenceAnalysis);
  patterns.add<AffineStoreLowering>(context, dependenceAnalysis);
  patterns.add<AffineStoreEnableLowering>(context, dependenceAnalysis);

  if (failed(applyPartialConversion(op, target, std::move(patterns))))
    return failure();

  hoistIfBodies(op);
  return success();
}

static void linkMemoryResource(Operation *memOp, Value memRef, bool isLoad,
                               ModuloProblem &problem,
                               const BRAMClassification &bramClass) {
  auto key = std::to_string(hash_value(memRef));

  Problem::OperatorType memOpr = problem.getOrInsertOperatorType("mem_" + key);
  problem.setLatency(memOpr, 1);
  problem.setLinkedOperatorType(memOp, memOpr);

  using hls_analysis::StorageMode;
  const BankProfile *prof = bramClass.getProfile(memRef);

  SmallVector<Problem::ResourceType> rsrcs;

  StorageMode mode = prof ? prof->mode : StorageMode::TDP;
  Problem::ResourceType resultValue;

  switch (mode) {
  case StorageMode::OnePort:
  case StorageMode::TDP:
  case StorageMode::OneWriteNRead: {

    resultValue = problem.getOrInsertResourceType("mem_" + key + "_rsrc");
    problem.setLimit(resultValue, hls_analysis::storageModeSlots(mode));
    rsrcs.push_back(resultValue);
    break;
  }
  case StorageMode::SDP: {

    if (isLoad) {
      resultValue = problem.getOrInsertResourceType("mem_" + key + "_rd_rsrc");
      problem.setLimit(resultValue, 1);
    } else {
      resultValue = problem.getOrInsertResourceType("mem_" + key + "_wr_rsrc");
      problem.setLimit(resultValue, 1);
    }
    rsrcs.push_back(resultValue);
    break;
  }
  case StorageMode::Registers:
    break;
  }
  if (!rsrcs.empty())
    problem.setLinkedResourceTypes(memOp, rsrcs);

  LLVM_DEBUG(llvm::dbgs() << "linked " << (isLoad ? "load" : "store") << " to "
                          << stringifyStorageMode(mode) << " resource for "
                          << *memOp << "\n");
}

/// Populate the scheduling problem operator types for the dialect we are
/// targeting. Right now, we assume Calyx, which has a standard library with
/// well-defined operator latencies. Ultimately, we should move this to a
/// dialect interface in the Scheduling dialect.
///
/// MODIFIED: now takes a single innermost loop, and covers the full set of
/// arith ops produced by affine map expansion (including the floordiv/mod
/// delinearization introduced by loop coalescing): mul/div/rem are
/// multicycle, while select/sub/logical/shift/ext/trunc are combinational.
LogicalResult AffineToLoopSchedule::populateOperatorTypes(
    AffineForOp forOp, ModuloProblem &problem,
    const BRAMClassification &bramClass) {

  Problem::OperatorType combOpr = problem.getOrInsertOperatorType("comb");
  problem.setLatency(combOpr, 0);
  Problem::OperatorType seqOpr = problem.getOrInsertOperatorType("seq");
  problem.setLatency(seqOpr, 1);
  Problem::OperatorType mcOpr = problem.getOrInsertOperatorType("multicycle");
  problem.setLatency(mcOpr, 3);

  Problem::OperatorType fpMulOpr = problem.getOrInsertOperatorType("fpmul");
  problem.setLatency(fpMulOpr, 4);
  Problem::OperatorType fpAddOpr = problem.getOrInsertOperatorType("fpaddsub");
  problem.setLatency(fpAddOpr, 5);
  Problem::OperatorType fpDivOpr = problem.getOrInsertOperatorType("fpdiv");
  problem.setLatency(fpDivOpr, 12);

  Problem::OperatorType fpSqrtOpr = problem.getOrInsertOperatorType("fpsqrt");
  problem.setLatency(fpSqrtOpr, 16);
  Problem::OperatorType fpTransOpr = problem.getOrInsertOperatorType("fptrans");
  problem.setLatency(fpTransOpr, 20);

  Operation *unsupported;
  WalkResult result = forOp.getBody()->walk([&](Operation *op) {
    return TypeSwitch<Operation *, WalkResult>(op)

        .Case<IfOp, AffineYieldOp, arith::ConstantOp, CmpIOp, IndexCastOp,
              IndexCastUIOp, AllocaOp, AllocOp, YieldOp, AddIOp, SubIOp,
              SelectOp, AndIOp, OrIOp, XOrIOp, ShLIOp, ShRSIOp, ShRUIOp,
              TruncIOp, ExtSIOp, ExtUIOp, NegFOp, CmpFOp, ExtFOp, TruncFOp,
              SIToFPOp, UIToFPOp, FPToSIOp, FPToUIOp, BitcastOp>(
            [&](Operation *combOp) {
              problem.setLinkedOperatorType(combOp, combOpr);
              return WalkResult::advance();
            })

        .Case<AffineStoreOp, memref::StoreOp>([&](Operation *memOp) {
          Value memRef = isa<AffineStoreOp>(*memOp)
                             ? cast<AffineStoreOp>(*memOp).getMemRef()
                             : cast<memref::StoreOp>(*memOp).getMemRef();
          linkMemoryResource(memOp, memRef, false, problem, bramClass);
          return WalkResult::advance();
        })

        .Case<AffineLoadOp, memref::LoadOp>([&](Operation *memOp) {
          Value memRef = isa<AffineLoadOp>(*memOp)
                             ? cast<AffineLoadOp>(*memOp).getMemRef()
                             : cast<memref::LoadOp>(*memOp).getMemRef();
          linkMemoryResource(memOp, memRef, true, problem, bramClass);
          return WalkResult::advance();
        })
        .Case<StoreEnableOp>([&](Operation *memOp) {
          Value memRef = cast<StoreEnableOp>(*memOp).getMemref();
          linkMemoryResource(memOp, memRef, false, problem, bramClass);
          return WalkResult::advance();
        })
        .Case<MulIOp, DivSIOp, DivUIOp, RemSIOp, RemUIOp>([&](Operation *mcOp) {
          problem.setLinkedOperatorType(mcOp, mcOpr);
          return WalkResult::advance();
        })
        .Case<MulFOp>([&](Operation *fpOp) {
          problem.setLinkedOperatorType(fpOp, fpMulOpr);
          return WalkResult::advance();
        })
        .Case<AddFOp, SubFOp, MaximumFOp, MinimumFOp, MaxNumFOp, MinNumFOp>(
            [&](Operation *fpOp) {
              problem.setLinkedOperatorType(fpOp, fpAddOpr);
              return WalkResult::advance();
            })
        .Case<DivFOp, RemFOp>([&](Operation *fpOp) {
          problem.setLinkedOperatorType(fpOp, fpDivOpr);
          return WalkResult::advance();
        })
        .Case<math::SqrtOp, math::RsqrtOp>([&](Operation *fpOp) {
          problem.setLinkedOperatorType(fpOp, fpSqrtOpr);
          return WalkResult::advance();
        })
        .Case<math::ExpOp, math::Exp2Op, math::ExpM1Op, math::LogOp,
              math::Log2Op, math::Log10Op, math::Log1pOp, math::PowFOp,
              math::SinOp, math::CosOp, math::TanOp, math::TanhOp, math::ErfOp,
              math::AtanOp, math::Atan2Op>([&](Operation *fpOp) {
          problem.setLinkedOperatorType(fpOp, fpTransOpr);
          return WalkResult::advance();
        })
        .Case<math::FmaOp>([&](Operation *fpOp) {
          problem.setLinkedOperatorType(fpOp, fpAddOpr);
          return WalkResult::advance();
        })
        .Case<math::AbsFOp, math::CopySignOp, math::AbsIOp>(
            [&](Operation *combOp) {
              problem.setLinkedOperatorType(combOp, combOpr);
              return WalkResult::advance();
            })
        .Case<math::FloorOp, math::CeilOp, math::RoundOp, math::RoundEvenOp,
              math::TruncOp>([&](Operation *fpOp) {
          problem.setLinkedOperatorType(fpOp, fpAddOpr);
          return WalkResult::advance();
        })
        .Default([&](Operation *badOp) {
          if (auto callSite = dyn_cast<CallOpInterface>(badOp)) {

            if (loopScheduleKeptCallLatency >= 0 &&
                resolveDefinedCallee(callSite)) {

              unsigned latency =
                  static_cast<unsigned>(loopScheduleKeptCallLatency);
              if (auto occ = badOp->getAttrOfType<IntegerAttr>(
                      circt::hls_analysis::kCallOccupancyAttr))
                latency =
                    static_cast<unsigned>(std::max<int64_t>(1, occ.getInt()));
              Problem::OperatorType callOpr = problem.getOrInsertOperatorType(
                  "call_kept_" + std::to_string(latency));
              problem.setLatency(callOpr, latency);
              problem.setLinkedOperatorType(badOp, callOpr);
              return WalkResult::advance();
            }
            if (loopScheduleCallLatency >= 0 &&
                llvm::none_of(badOp->getOperandTypes(),
                              llvm::IsaPred<BaseMemRefType>) &&
                llvm::none_of(badOp->getResultTypes(),
                              llvm::IsaPred<BaseMemRefType>)) {
              Problem::OperatorType callOpr =
                  problem.getOrInsertOperatorType("call");
              problem.setLatency(
                  callOpr, static_cast<unsigned>(loopScheduleCallLatency));
              problem.setLinkedOperatorType(badOp, callOpr);
              return WalkResult::advance();
            }
          }
          unsupported = op;
          return WalkResult::interrupt();
        });
  });

  if (result.wasInterrupted()) {
    forOp.emitWarning("not pipelined (left as a sequential loop): "
                      "unsupported operation ")
        << *unsupported;
    return failure();
  }

  return success();
}

/// Solve the pre-computed scheduling problem.
LogicalResult
AffineToLoopSchedule::solveSchedulingProblem(AffineForOp forOp,
                                             ModuloProblem &problem) {

  LLVM_DEBUG(forOp.getBody()->walk<WalkOrder::PreOrder>([&](Operation *op) {
    llvm::dbgs() << "Scheduling inputs for " << *op;
    auto opr = problem.getLinkedOperatorType(op);
    llvm::dbgs() << "\n  opr = " << opr->getAttr();
    llvm::dbgs() << "\n  latency = " << problem.getLatency(*opr);
    for (auto dep : problem.getDependences(op))
      if (dep.isAuxiliary())
        llvm::dbgs() << "\n  dep = { distance = " << problem.getDistance(dep)
                     << ", source = " << *dep.getSource() << " }";
    llvm::dbgs() << "\n\n";
  }));

  if (failed(problem.check()))
    return failure();

  auto *anchor = forOp.getBody()->getTerminator();

  SmallVector<int64_t> signature;
  size_t signatureHash = 0;
  const CachedSchedule *reused = nullptr;
  if (reuseSchedules) {
    signature = scheduleSignature(problem, anchor);
    signatureHash =
        llvm::hash_combine_range(signature.begin(), signature.end());
    auto it = scheduleCache.find(signatureHash);
    if (it != scheduleCache.end())
      for (const CachedSchedule &candidateValue : it->second)
        if (candidateValue.signature == signature)
          reused = &candidateValue;
    DEBUG_WITH_TYPE("schedule-reuse", {
      llvm::dbgs() << "schedule signature " << forOp.getLoc() << " ops "
                   << problem.getOperations().size() << " hash "
                   << signatureHash << (reused ? " reused" : " new") << ":";
      for (int64_t exprValue : signature)
        llvm::dbgs() << " " << (exprValue > 1000000 ? 999 : exprValue);
      llvm::dbgs() << "\n";
    });
  }
  auto applyReused = [&]() {
    problem.setInitiationInterval(reused->ii);
    for (auto [op, typeValue] :
         llvm::zip(problem.getOperations(), reused->startTimes))
      problem.setStartTime(op, typeValue);
  };
  if (reused && !verifyScheduleReuse) {
    applyReused();
    if (succeeded(problem.verify())) {
      ++numSchedulesReused;
      forOp->setAttr(circt::hls_analysis::kLoopSchedulerAttr,
                     StringAttr::get(forOp.getContext(),
                                     reused->scheduler + " (reused from " +
                                         reused->loc + ")"));
      return success();
    }

    reused = nullptr;
  }

  unsigned limited = FastModuloScheduler::countLimitedOps(problem);
  bool scheduled = false, triedFast = false;

  StringRef scheduler;
  if (fastThreshold == 0 || limited > fastThreshold) {
    triedFast = true;
    FastModuloScheduler fast(problem);
    scheduled = succeeded(fast.schedule(4096));
    if (scheduled)
      scheduler = "greedy";
    LLVM_DEBUG(if (!scheduled) llvm::dbgs()
               << "fast modulo scheduler failed; falling back to simplex\n");
  }
  if (!scheduled) {
    scheduled = succeeded(scheduleSimplex(problem, anchor));
    if (scheduled)
      scheduler = triedFast ? "simplex (greedy failed)" : "simplex";
  }

  if (!scheduled && !triedFast) {
    LLVM_DEBUG(llvm::dbgs()
               << "simplex modulo scheduler failed; falling back to fast\n");
    FastModuloScheduler fast(problem);
    scheduled = succeeded(fast.schedule(4096));
    if (scheduled)
      scheduler = "greedy (simplex failed)";
  }
  if (!scheduled)
    return failure();

  if (failed(problem.verify()))
    return failure();
  ++numSchedulesSolved;
  forOp->setAttr(circt::hls_analysis::kLoopSchedulerAttr,
                 StringAttr::get(forOp.getContext(), scheduler));

  if (reuseSchedules) {
    SmallVector<unsigned> startTimes;
    for (Operation *op : problem.getOperations())
      startTimes.push_back(*problem.getStartTime(op));
    if (reused) {
      ++numSchedulesReused;
      if (reused->ii != *problem.getInitiationInterval() ||
          reused->startTimes != startTimes) {
        ++numReuseMismatches;
        forOp.emitWarning()
            << "schedule reuse mismatch: the identical loop at " << reused->loc
            << " has II " << reused->ii << ", this one solves to II "
            << *problem.getInitiationInterval();
      }
    } else {
      std::string loc;
      llvm::raw_string_ostream os(loc);
      if (auto fl = dyn_cast<FileLineColLoc>(forOp.getLoc()))
        os << fl.getFilename().getValue() << ":" << fl.getLine() << ":"
           << fl.getColumn();
      else
        forOp.getLoc().print(os);
      scheduleCache[signatureHash].push_back(
          {std::move(signature), *problem.getInitiationInterval(),
           std::move(startTimes), scheduler.str(), std::move(loc)});
    }
  }

  LLVM_DEBUG({
    llvm::dbgs() << "Scheduled initiation interval = "
                 << problem.getInitiationInterval() << "\n\n";
    forOp.getBody()->walk<WalkOrder::PreOrder>([&](Operation *op) {
      llvm::dbgs() << "Scheduling outputs for " << *op;
      llvm::dbgs() << "\n  start = " << problem.getStartTime(op);
      llvm::dbgs() << "\n\n";
    });
  });

  return success();
}

/// Create the loopschedule pipeline op for a single innermost loop.
///
/// MODIFIED: the pipeline is created *in place of* `forOp` rather than at
/// the root of a loop nest, and only `forOp` itself is erased. Any
/// enclosing affine.for loops survive and act as sequential control around
/// the pipeline. Because LoopSchedulePipelineOp is not IsolatedFromAbove,
/// cloned ops may keep references to outer induction variables and other
/// dominating values without extra plumbing.
LogicalResult
AffineToLoopSchedule::createLoopSchedulePipeline(AffineForOp forOp,
                                                 ModuloProblem &problem) {
  ImplicitLocOpBuilder passBuilder(forOp.getLoc(), forOp);

  Value lowerBound = lowerAffineLowerBound(forOp, passBuilder);
  Value upperBound = lowerAffineUpperBound(forOp, passBuilder);
  int64_t stepValue = forOp.getStep().getSExtValue();
  auto step = arith::ConstantOp::create(
      passBuilder, IntegerAttr::get(passBuilder.getIndexType(), stepValue));

  TypeRange resultTypes = forOp.getResultTypes();

  auto ii =
      passBuilder.getI64IntegerAttr(problem.getInitiationInterval().value());

  SmallVector<Value> iterArgs;
  iterArgs.push_back(lowerBound);
  iterArgs.append(forOp.getInits().begin(), forOp.getInits().end());

  std::optional<IntegerAttr> tripCountAttr;
  if (auto tripCount = getConstantTripCount(forOp))
    tripCountAttr = passBuilder.getI64IntegerAttr(*tripCount);

  auto pipeline = LoopSchedulePipelineOp::create(passBuilder, resultTypes, ii,
                                                 tripCountAttr, iterArgs);

  for (StringRef name : {circt::hls_analysis::kLoopPipelineAttr,
                         circt::hls_analysis::kLoopFlattenedParentsAttr,
                         circt::hls_analysis::kLoopAutoUnrolledAttr,
                         circt::hls_analysis::kLoopUnrollPartialAttr,
                         circt::hls_analysis::kLoopSchedulerAttr})
    if (Attribute arrayValue = forOp->getAttr(name))
      pipeline->setAttr(name, arrayValue);

  Block &condBlock = pipeline.getCondBlock();
  passBuilder.setInsertionPointToStart(&condBlock);
  auto cmpResult = arith::CmpIOp::create(passBuilder, passBuilder.getI1Type(),
                                         arith::CmpIPredicate::ult,
                                         condBlock.getArgument(0), upperBound);
  condBlock.getTerminator()->insertOperands(0, {cmpResult});

  DenseMap<unsigned, SmallVector<Operation *>> startGroups;
  for (auto *op : problem.getOperations()) {
    if (isa<AffineYieldOp, YieldOp>(op))
      continue;
    auto startTime = problem.getStartTime(op);
    startGroups[*startTime].push_back(op);
  }

  unsigned maxStartTime = 0;
  for (auto *op : problem.getOperations()) {
    if (isa<AffineYieldOp, YieldOp>(op))
      continue;
    maxStartTime = std::max(maxStartTime, *problem.getStartTime(op));
  }

  if (auto termStart = problem.getStartTime(forOp.getBody()->getTerminator());
      termStart && *termStart > 0)
    maxStartTime = std::max(maxStartTime, *termStart - 1);
  for (unsigned typeValue = 0; typeValue <= maxStartTime; ++typeValue)
    if (!startGroups.count(typeValue))
      startGroups.try_emplace(typeValue, SmallVector<Operation *>());

  IRMapping valueMap;
  assert(iterArgs.size() == forOp.getBody()->getNumArguments());
  for (size_t loopIndex = 0; loopIndex < iterArgs.size(); ++loopIndex)
    valueMap.map(forOp.getBody()->getArgument(loopIndex),
                 pipeline.getStagesBlock().getArgument(loopIndex));

  Block &stagesBlock = pipeline.getStagesBlock();
  passBuilder.setInsertionPointToStart(&stagesBlock);

  SmallVector<unsigned> startTimes;
  for (const auto &group : startGroups)
    startTimes.push_back(group.first);
  llvm::sort(startTimes);

  DominanceInfo dom(getOperation());

  SmallVector<SmallVector<Value>> registerValues;
  SmallVector<SmallVector<Type>> registerTypes;

  SmallVector<IRMapping> stageValueMaps;

  DenseMap<Operation *, std::pair<unsigned, unsigned>> pipeTimes;

  for (auto startTime : startTimes) {
    auto group = startGroups[startTime];

    auto isLoopTerminator = [forOp](Operation *op) {
      return isa<AffineYieldOp>(op) && op->getParentOp() == forOp;
    };

    for (unsigned loopIndex = registerValues.size(); loopIndex <= startTime;
         ++loopIndex)
      registerValues.emplace_back(SmallVector<Value>());

    for (auto *op : group) {
      if (op->getUsers().empty())
        continue;

      unsigned pipeEndTime = 0;
      for (auto *rawUser : op->getUsers()) {

        Operation *user = forOp.getBody()->findAncestorOpInBlock(*rawUser);
        if (!user)
          user = rawUser;
        unsigned userStartTime = *problem.getStartTime(user);
        if (*problem.getStartTime(user) > startTime)
          pipeEndTime = std::max(pipeEndTime, userStartTime);
        else if (isLoopTerminator(user))

          pipeEndTime = std::max(pipeEndTime, userStartTime + 1);
      }

      pipeTimes[op] = std::pair(startTime, pipeEndTime);

      for (unsigned loopIndex = registerValues.size(); loopIndex <= pipeEndTime;
           ++loopIndex)
        registerValues.push_back(SmallVector<Value>());

      for (auto result : op->getResults())
        registerValues[startTime].push_back(result);

      unsigned firstUse = std::max(
          startTime + 1,
          startTime + *problem.getLatency(*problem.getLinkedOperatorType(op)));
      for (unsigned loopIndex = firstUse; loopIndex < pipeEndTime;
           ++loopIndex) {
        for (auto result : op->getResults())
          registerValues[loopIndex].push_back(result);
      }
    }
  }

  for (unsigned loopIndex = 0; loopIndex < registerValues.size(); ++loopIndex) {
    SmallVector<mlir::Type> types;
    for (auto operandValue : registerValues[loopIndex])
      types.push_back(operandValue.getType());

    registerTypes.push_back(types);
    stageValueMaps.push_back(valueMap);
  }

  stageValueMaps.push_back(valueMap);

  for (auto startTime : startTimes) {
    auto group = startGroups[startTime];
    llvm::sort(group, [&](Operation *arrayValue, Operation *buildPoint) {
      return dom.properlyDominates(arrayValue, buildPoint);
    });
    auto stageTypes = registerTypes[startTime];

    if (group.empty() && stageTypes.empty() && startTime != 0)
      continue;

    if (startTime == 0)
      stageTypes.push_back(lowerBound.getType());

    passBuilder.setInsertionPoint(stagesBlock.getTerminator());
    auto startTimeAttr = passBuilder.getIntegerAttr(
        passBuilder.getIntegerType(64, true), startTime);
    auto stage = LoopSchedulePipelineStageOp::create(passBuilder, stageTypes,
                                                     startTimeAttr);
    auto &stageBlock = stage.getBodyBlock();
    auto *stageTerminator = stageBlock.getTerminator();
    passBuilder.setInsertionPointToStart(&stageBlock);

    for (auto *op : group) {
      auto *newOp = passBuilder.clone(*op, stageValueMaps[startTime]);

      for (auto result : op->getResults())
        stageValueMaps[startTime].map(
            result, newOp->getResult(result.getResultNumber()));
    }

    SmallVector<Value> stageOperands;
    unsigned resIndex = 0;
    for (auto passResult : registerValues[startTime]) {
      stageOperands.push_back(stageValueMaps[startTime].lookup(passResult));

      unsigned destTime = startTime + 1;
      unsigned latency = *problem.getLatency(
          *problem.getLinkedOperatorType(passResult.getDefiningOp()));

      if (*problem.getStartTime(passResult.getDefiningOp()) == startTime &&
          latency > 1)
        destTime = startTime + latency;
      destTime = std::min((unsigned)(stageValueMaps.size() - 1), destTime);
      stageValueMaps[destTime].map(passResult, stage.getResult(resIndex++));
    }

    stageTerminator->insertOperands(stageTerminator->getNumOperands(),
                                    stageOperands);

    if (startTime == 0) {
      auto incResult =
          arith::AddIOp::create(passBuilder, stagesBlock.getArgument(0), step);
      stageTerminator->insertOperands(stageTerminator->getNumOperands(),
                                      incResult->getResults());
    }
  }

  auto stagesTerminator =
      cast<LoopScheduleTerminatorOp>(stagesBlock.getTerminator());

  SmallVector<Value> termIterArgs;
  SmallVector<Value> termResults;
  termIterArgs.push_back(
      stagesBlock.front().getResult(stagesBlock.front().getNumResults() - 1));

  for (auto value : forOp.getBody()->getTerminator()->getOperands()) {
    unsigned lookupTime = std::min((unsigned)(stageValueMaps.size() - 1),
                                   pipeTimes[value.getDefiningOp()].second);

    termIterArgs.push_back(stageValueMaps[lookupTime].lookup(value));
    termResults.push_back(stageValueMaps[lookupTime].lookup(value));
  }

  stagesTerminator.getIterArgsMutable().append(termIterArgs);
  stagesTerminator.getResultsMutable().append(termResults);

  for (size_t loopIndex = 0; loopIndex < forOp.getNumResults(); ++loopIndex)
    forOp.getResult(loopIndex).replaceAllUsesWith(
        pipeline.getResult(loopIndex));

  forOp.walk([](Operation *op) {
    op->dropAllUses();
    op->dropAllDefinedValueUses();
    op->dropAllReferences();
    op->erase();
  });

  return success();
}
namespace circt::hls_analysis {

std::unique_ptr<mlir::Pass> createAffineToLoopSchedule() {
  return std::make_unique<AffineToLoopSchedule>();
}

void registerAffineToLoopScheduleAnalysisPass() {
  PassRegistration<AffineToLoopSchedule>();
}

} // namespace circt::hls_analysis
