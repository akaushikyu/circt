//===- DependenceAnalysis.cpp - memory dependence analyses ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements methods that perform analysis involving memory access
// dependences.
//
// MODIFIED for hls-est (performance; the recorded dependences are the same):
//   * accesses are grouped by memref before pairs are enumerated;
//   * pairs whose index along some dimension is a different constant skip the
//     dependence test (it can only report NoDependence for them);
//   * the dependence test is memoized on the facts it depends on, so the
//     thousands of identical accesses an unrolled body leaves (`acc[i][j] +=
//     ...` 64 times) cost one Fourier-Motzkin test instead of one per pair;
//   * only actual dependences are recorded (every consumer filters on
//     hasDependence());
//   * replaceOp() re-keys the destination properly and retargets sources
//     through an inverted index instead of rescanning every list;
// and adds a restricted scope (InnermostLoopDependenceAnalysis): only the
// pairs inside one innermost loop, at that loop's depth.
//
//===----------------------------------------------------------------------===//

#include "circt/Analysis/DependenceAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/AffineAnalysis.h"
#include "mlir/Dialect/Affine/Analysis/AffineStructures.h"
#include "mlir/Dialect/Affine/Analysis/Utils.h"
#include "mlir/Dialect/Affine/IR/AffineMemoryOpInterfaces.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/IR/AffineValueMap.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/IR/BuiltinOps.h"
#include "llvm/Support/ThreadPool.h"
#include "mlir/Interfaces/LoopLikeInterface.h"
#include "llvm/ADT/Hashing.h"
#include "llvm/ADT/MapVector.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"

#include <atomic>
#include <chrono>
#include <map>

#define DEBUG_TYPE "memory-dependence-analysis"

using namespace mlir;
using namespace mlir::affine;
using namespace circt::analysis;

namespace {

/// Threads the dependence tests of one analysis run use at most. Each
/// thread can hold one Fourier-Motzkin elimination of up to ~2 GB, so the
/// peak memory grows with it (W9r9 review D4: ResidualBlock opt4 7.85 GB with
/// 4 threads, 2.03 GB with 1; OPEN_ISSUES O103). Estimates never depend on
/// it; --mlir-disable-threading also forces 1.
llvm::cl::opt<unsigned> dependenceTestThreads(
    "hls-dependence-test-threads",
    llvm::cl::desc("Threads the memory dependence tests of one analysis run "
                   "use at most (1: sequential; peak memory grows with it)"),
    llvm::cl::init(4));

/// Everything the dependence test between two accesses depends on: their
/// composed access maps and operands, the blocks they live in (which fix the
/// iteration domains and the loops in common), the requested depth, and their
/// program order (which decides same-iteration dependences). Two pairs with
/// equal keys get equal results.
struct PairKey {
  Block *srcBlock = nullptr;
  Block *dstBlock = nullptr;
  // The access maps without the constant terms of their results, and the
  // source's constant terms minus the destination's: the dependence system
  // `src(x) + cs = dst(y) + cd` is `src(x) - dst(y) = cd - cs`, so pairs
  // that differ only by a common shift of their constants (the copies of a
  // fully unrolled body, `a[%i + 3]` / `a[%i + 5]` and `a[%i + 7]` /
  // `a[%i + 9]`) have one result.
  AffineMap srcMap, dstMap;
  SmallVector<int64_t, 4> constantDelta;
  SmallVector<Value, 4> srcOperands, dstOperands;
  unsigned depth = 0;
  bool srcBeforeDst = false;

  bool operator==(const PairKey &o) const {
    return srcBlock == o.srcBlock && dstBlock == o.dstBlock &&
           srcMap == o.srcMap && dstMap == o.dstMap &&
           constantDelta == o.constantDelta &&
           srcOperands == o.srcOperands && dstOperands == o.dstOperands &&
           depth == o.depth && srcBeforeDst == o.srcBeforeDst;
  }
};

struct PairKeyInfo {
  static PairKey getEmptyKey() {
    PairKey k;
    k.depth = ~0u;
    return k;
  }
  static PairKey getTombstoneKey() {
    PairKey k;
    k.depth = ~0u - 1;
    return k;
  }
  static unsigned getHashValue(const PairKey &k) {
    return llvm::hash_combine(
        k.srcBlock, k.dstBlock, k.srcMap.getAsOpaquePointer(),
        k.dstMap.getAsOpaquePointer(),
        llvm::hash_combine_range(k.constantDelta.begin(),
                                 k.constantDelta.end()),
        llvm::hash_combine_range(k.srcOperands.begin(), k.srcOperands.end()),
        llvm::hash_combine_range(k.dstOperands.begin(), k.dstOperands.end()),
        k.depth, k.srcBeforeDst);
  }
  static bool isEqual(const PairKey &a, const PairKey &b) { return a == b; }
};

/// The memoized outcome of one (source, destination, depth) test.
struct PairResult {
  bool skipped = false; // depth exceeds the loops the pair has in common
  DependenceResult::ResultEnum value = DependenceResult::NoDependence;
  SmallVector<DependenceComponent, 2> comps;
  bool sameElement = false; // the two accesses provably address one element
};

} // namespace

/// `map` with the constant term of every result removed (`d0 + 5` becomes
/// `d0`, `7` becomes `0`); the removed terms go to `constants`. Simplified
/// affine expressions keep the constant as the right operand of the
/// outermost addition.
static AffineMap stripConstantTerms(AffineMap map,
                                    SmallVectorImpl<int64_t> &constants) {
  SmallVector<AffineExpr, 4> parts;
  for (AffineExpr e : map.getResults()) {
    int64_t c = 0;
    if (auto ce = dyn_cast<AffineConstantExpr>(e)) {
      c = ce.getValue();
      e = getAffineConstantExpr(0, map.getContext());
    } else if (auto add = dyn_cast<AffineBinaryOpExpr>(e)) {
      if (add.getKind() == AffineExprKind::Add)
        if (auto ce = dyn_cast<AffineConstantExpr>(add.getRHS())) {
          c = ce.getValue();
          e = add.getLHS();
        }
    }
    parts.push_back(e);
    constants.push_back(c);
  }
  return AffineMap::get(map.getNumDims(), map.getNumSymbols(), parts,
                        map.getContext());
}

/// True if `a` comes before `b` in their lowest common block (what the
/// dependence test consults for same-iteration dependences).
static bool appearsBefore(Operation *a, Operation *b) {
  for (Operation *cur = a; cur; cur = cur->getParentOp()) {
    Block *block = cur->getBlock();
    if (!block)
      break;
    if (Operation *anc = block->findAncestorOpInBlock(*b))
      return cur != anc && cur->isBeforeInBlock(anc);
  }
  return false;
}

/// Two accesses whose index along some dimension is a different constant can
/// never touch the same element, so the dependence test would report
/// NoDependence for them. Unrolled, banked bodies consist largely of such
/// pairs (`bank[3][%i]` vs `bank[7][%i]`), and the full Fourier-Motzkin test
/// costs far more than this check.
static bool haveDisjointConstantIndex(const AffineValueMap &ma,
                                      const AffineValueMap &mb) {
  if (ma.getNumResults() != mb.getNumResults())
    return false;
  for (unsigned i = 0, e = ma.getNumResults(); i < e; ++i) {
    auto ca = dyn_cast<AffineConstantExpr>(ma.getAffineMap().getResult(i));
    auto cb = dyn_cast<AffineConstantExpr>(mb.getAffineMap().getResult(i));
    if (ca && cb && ca.getValue() != cb.getValue())
      return true;
  }
  return false;
}

/// The result dimensions that are constant in the access map of every
/// access in `ops` (all of one memref, so all of one rank).
static SmallVector<unsigned>
dimsConstantInAll(ArrayRef<Operation *> ops,
                  DenseMap<Operation *, AffineValueMap> &accessMaps) {
  SmallVector<unsigned> dims;
  if (ops.empty())
    return dims;
  unsigned rank = accessMaps[ops.front()].getNumResults();
  for (unsigned d = 0; d < rank; ++d) {
    bool allConstant = llvm::all_of(ops, [&](Operation *op) {
      AffineMap map = accessMaps[op].getAffineMap();
      return d < map.getNumResults() &&
             isa<AffineConstantExpr>(map.getResult(d));
    });
    if (allConstant)
      dims.push_back(d);
  }
  return dims;
}

unsigned MemoryDependenceAnalysis::slotFor(Operation *op) {
  auto [it, inserted] = slotOf.try_emplace(op, slots.size());
  if (inserted)
    slots.emplace_back();
  return it->second;
}

/// Helper to iterate through memory operation pairs and check for dependences
/// at a given loop nesting depth.
void MemoryDependenceAnalysis::checkMemrefDependence(
    SmallVectorImpl<Operation *> &memoryOps, unsigned depth) {
  // Every memory op gets a (possibly empty) dependence list, as before.
  for (auto *destination : memoryOps)
    slotFor(destination);

  // Accesses to different memrefs never depend on each other, so only pairs
  // within one memref's group are examined; program order is kept inside each
  // group, so the dependences are recorded in the same order as before.
  llvm::MapVector<Value, SmallVector<Operation *>> byMemref;
  DenseMap<Operation *, AffineValueMap> accessMaps;
  for (auto *op : memoryOps) {
    MemRefAccess access(op);
    byMemref[access.memref].push_back(op);
    // With constant operands folded into the map (`a[%i, %c3]` built by the
    // unroller is `(d0, d1) -> (d0, d1)` on a constant %c3): the constant
    // indices then show as such, for haveDisjointConstantIndex and the
    // buckets below. The folded map is the same access function, so the
    // memo key built from it still determines the test's result.
    AffineValueMap vm;
    access.getAccessMap(&vm);
    AffineMap map = vm.getAffineMap();
    SmallVector<Value, 8> operands(vm.getOperands());
    canonicalizeMapAndOperands(&map, &operands);
    accessMaps[op].reset(map, operands);
  }

  // The tests run in three phases with the same outcome as one serial loop:
  // (1) every pair, in program order, gets its memo entry, and each fresh
  // entry one job; (2) the jobs' dependence tests run in parallel (each a
  // pure function of the IR); (3) the pairs are visited again in the same
  // order and their results recorded. ResidualBlock opt4 spent 434 s in
  // 10,434 serial Fourier-Motzkin tests (OPEN_ISSUES O103).
  DenseMap<PairKey, unsigned, PairKeyInfo> memo; // key -> index in results
  SmallVector<PairResult> results;
  SmallVector<std::pair<Operation *, Operation *>> jobs; // per result
  constexpr unsigned kDisjoint = ~0u;
  std::vector<unsigned> pairResult; // per enumerated pair, in order
  uint64_t numPairs = 0, numTests = 0, numDeps = 0;
  [[maybe_unused]] uint64_t numDisjoint = 0, numHits = 0;

  struct GroupBuckets {
    DenseMap<Operation *, unsigned> bucketOf;
    SmallVector<SmallVector<Operation *>> buckets;
  };
  std::vector<GroupBuckets> groupBuckets;
  groupBuckets.reserve(byMemref.size());

  for (auto &group : byMemref) {
    SmallVectorImpl<Operation *> &ops = group.second;
    // A fully unrolled body holds thousands of accesses to one memref that
    // differ in a constant index (`a[%i][3]`, `a[%i][7]`, ...), and testing
    // every pair is quadratic. Two accesses whose constant indices differ
    // along a dimension that is constant in every access of the group are
    // disjoint (haveDisjointConstantIndex), so only accesses with equal
    // constants along those dimensions are paired. Pairs are still visited
    // in program order of the source, then of the destination.
    SmallVector<unsigned> constantDims =
        dimsConstantInAll(ops, accessMaps);
    GroupBuckets &gb = groupBuckets.emplace_back();
    DenseMap<Operation *, unsigned> &bucketOf = gb.bucketOf;
    SmallVector<SmallVector<Operation *>> &buckets = gb.buckets;
    {
      std::map<SmallVector<int64_t>, unsigned> bucketIds;
      for (auto *op : ops) {
        SmallVector<int64_t> constants;
        for (unsigned d : constantDims)
          constants.push_back(
              cast<AffineConstantExpr>(
                  accessMaps[op].getAffineMap().getResult(d))
                  .getValue());
        auto [it, fresh] = bucketIds.try_emplace(constants, buckets.size());
        if (fresh)
          buckets.emplace_back();
        buckets[it->second].push_back(op);
        bucketOf[op] = it->second;
      }
    }
    for (auto *source : ops) {
      const AffineValueMap &srcMap = accessMaps[source];
      for (auto *destination : buckets[bucketOf[source]]) {
        if (source == destination)
          continue;
        ++numPairs;
        const AffineValueMap &dstMap = accessMaps[destination];
        if (haveDisjointConstantIndex(srcMap, dstMap)) {
          ++numDisjoint;
          pairResult.push_back(kDisjoint);
          continue;
        }

        PairKey key;
        key.srcBlock = source->getBlock();
        key.dstBlock = destination->getBlock();
        SmallVector<int64_t, 4> srcConstants, dstConstants;
        key.srcMap = stripConstantTerms(srcMap.getAffineMap(), srcConstants);
        key.dstMap = stripConstantTerms(dstMap.getAffineMap(), dstConstants);
        for (auto [cs, cd] : llvm::zip(srcConstants, dstConstants))
          key.constantDelta.push_back(cs - cd);
        key.srcOperands.assign(srcMap.getOperands().begin(),
                               srcMap.getOperands().end());
        key.dstOperands.assign(dstMap.getOperands().begin(),
                               dstMap.getOperands().end());
        key.depth = depth;
        key.srcBeforeDst = appearsBefore(source, destination);

        auto [memoIt, fresh] =
            memo.try_emplace(key, static_cast<unsigned>(results.size()));
        if (fresh) {
          results.emplace_back();
          jobs.push_back({source, destination});
        } else {
          ++numHits;
        }
        pairResult.push_back(memoIt->second);
      }
    }
  }

  // (2) The block orders the tests compare are computed first, so that no
  // test writes to the IR (Operation::isBeforeInBlock recomputes them
  // lazily).
  {
    llvm::SmallPtrSet<Block *, 16> blocks;
    for (auto *op : memoryOps)
      for (Operation *cur = op; cur; cur = cur->getParentOp())
        if (Block *b = cur->getBlock(); b && blocks.insert(b).second)
          b->recomputeOpOrder();
  }
  auto runTest = [&](size_t i) {
    auto [source, destination] = jobs[i];
    PairResult &pr = results[i];
    // Requested depth might not be a valid comparison if they do not
    // belong to the same loop nest
    if (depth > getInnermostCommonLoopDepth({source, destination})) {
      pr.skipped = true;
      return;
    }
    MemRefAccess src(source), dst(destination);
    FlatAffineValueConstraints dependenceConstraints;
    DependenceResult result = checkMemrefAccessDependence(
        src, dst, depth, &dependenceConstraints, &pr.comps, true);
    pr.value = result.value;
    pr.sameElement = (src == dst);
  };
  // A few threads of its own, not the context's pool: one Fourier-Motzkin
  // test can hold hundreds of MB, and the harness runs designs side by side.
  unsigned threads = std::min<size_t>(
      std::max(1u, dependenceTestThreads.getValue()), jobs.size());
  if (threads > 1 && memoryOps.front()->getContext()->isMultithreadingEnabled()) {
    llvm::StdThreadPool pool(llvm::hardware_concurrency(threads));
    std::atomic<size_t> next{0};
    for (unsigned t = 0; t < threads; ++t)
      pool.async([&] {
        for (size_t i = next++; i < jobs.size(); i = next++)
          runTest(i);
      });
    pool.wait();
  } else {
    for (size_t i = 0; i < jobs.size(); ++i)
      runTest(i);
  }
  for (const PairResult &pr : results)
    if (!pr.skipped)
      ++numTests;

  // (3) Record, in phase 1's pair order.
  size_t pairNo = 0, groupNo = 0;
  for (auto &group : byMemref) {
    GroupBuckets &gb = groupBuckets[groupNo++];
    for (auto *source : group.second) {
      for (auto *destination : gb.buckets[gb.bucketOf[source]]) {
        if (source == destination)
          continue;
        unsigned r = pairResult[pairNo++];
        if (r == kDisjoint)
          continue;
        const PairResult &pr = results[r];
        if (pr.skipped)
          continue;

        // Only record actual dependences. Every consumer filters on
        // hasDependence(); keeping the NoDependence results made the result
        // map quadratic in the number of memory ops.
        if (hasDependence(pr.value)) {
          ++numDeps;
          record(source, destination, pr.value, pr.comps);
        }

        // Also consider intra-iteration dependences on the same memory
        // location. This currently does not consider aliasing.
        if (!pr.sameElement)
          continue;

        // Collect surrounding loops to use in dependence components. Only
        // proceed if we are in the innermost loop.
        SmallVector<AffineForOp> enclosingLoops;
        getAffineForIVs(*destination, &enclosingLoops);
        if (enclosingLoops.size() != depth)
          continue;

        // Look for the common parent that src and dst share. If there is
        // none, there is nothing more to do.
        SmallVector<Operation *> srcParents;
        getEnclosingAffineOps(*source, &srcParents);
        SmallVector<Operation *> dstParents;
        getEnclosingAffineOps(*destination, &dstParents);

        Operation *commonParent = nullptr;
        for (auto *srcParent : llvm::reverse(srcParents)) {
          for (auto *dstParent : llvm::reverse(dstParents)) {
            if (srcParent == dstParent)
              commonParent = srcParent;
            if (commonParent != nullptr)
              break;
          }
          if (commonParent != nullptr)
            break;
        }

        if (commonParent == nullptr)
          continue;

        // Check the common parent's regions.
        for (auto &commonRegion : commonParent->getRegions()) {
          if (commonRegion.empty())
            continue;

          // Only support structured constructs with single-block regions for
          // now.
          assert(commonRegion.hasOneBlock() &&
                 "only single-block regions are supported");

          Block &commonBlock = commonRegion.front();

          // Find the src and dst ancestor in the common block, if any.
          Operation *srcOrAncestor = commonBlock.findAncestorOpInBlock(*source);
          Operation *dstOrAncestor =
              commonBlock.findAncestorOpInBlock(*destination);
          if (srcOrAncestor == nullptr || dstOrAncestor == nullptr)
            continue;

          // Check if the src or its ancestor is before the dst or its
          // ancestor.
          if (srcOrAncestor->isBeforeInBlock(dstOrAncestor)) {
            // Build dependence components for each loop depth.
            SmallVector<DependenceComponent> intraDeps;
            for (size_t i = 0; i < depth; ++i) {
              DependenceComponent depComp;
              depComp.op = enclosingLoops[i];
              depComp.lb = 0;
              depComp.ub = 0;
              intraDeps.push_back(depComp);
            }

            ++numDeps;
            record(source, destination, DependenceResult::HasDependence,
                   intraDeps);
          }
        }
      }
    }
  }
  counters.pairs += numPairs;
  counters.tests += numTests;
  counters.dependences += numDeps;
  LLVM_DEBUG(llvm::dbgs() << "memory dependence analysis, depth " << depth
                          << ": " << memoryOps.size() << " accesses, "
                          << byMemref.size() << " memrefs, " << numPairs
                          << " same-memref pairs, " << numDisjoint
                          << " disjoint by constant index, " << numHits
                          << " memo hits, " << numTests
                          << " dependence tests, " << numDeps
                          << " dependences recorded\n");
}

void MemoryDependenceAnalysis::record(
    Operation *source, Operation *destination,
    DependenceResult::ResultEnum type,
    ArrayRef<DependenceComponent> components) {
  unsigned slot = slotFor(destination);
  slots[slot].emplace_back(source, type, components);
  SmallVector<unsigned> &holders = bySource[source];
  if (holders.empty() || holders.back() != slot)
    holders.push_back(slot);
}

/// MemoryDependenceAnalysis traverses any AffineForOps in the FuncOp body and
/// checks for memory access dependences. Results are captured in a
/// MemoryDependenceResult, which can by queried by Operation.
circt::analysis::MemoryDependenceAnalysis::MemoryDependenceAnalysis(
    Operation *op)
    : MemoryDependenceAnalysis(op, Scope::Function) {}

/// True if `forOp` has no loop (affine or not) in its body.
static bool hasNoNestedLoop(AffineForOp forOp) {
  return !forOp.getBody()
              ->walk([](LoopLikeOpInterface) { return WalkResult::interrupt(); })
              .wasInterrupted();
}

circt::analysis::MemoryDependenceAnalysis::MemoryDependenceAnalysis(
    Operation *op, Scope scope) {
  auto funcOp = cast<func::FuncOp>(op);
  [[maybe_unused]] auto t0 = std::chrono::steady_clock::now();

  if (scope == Scope::InnermostLoops) {
    // Group the accesses by their innermost enclosing affine.for and keep the
    // loops without a nested loop. checkMemrefDependence at the loop's depth D
    // examines exactly the pairs the function scope examines at depth D for
    // these destinations: a pair needs D common loops there, i.e. the same
    // innermost loop. Recording order per destination is kept (sources in
    // program order), so each list equals the function scope's list with its
    // entries of depths < D left out.
    llvm::MapVector<Operation *, SmallVector<Operation *>> byLoop;
    DenseMap<Operation *, unsigned> depthOf;
    DenseMap<Operation *, bool> isInnermost;
    funcOp.walk([&](Operation *op) {
      if (!isa<AffineReadOpInterface, AffineWriteOpInterface>(op))
        return;
      SmallVector<AffineForOp, 4> loops;
      getAffineForIVs(*op, &loops);
      if (loops.empty())
        return;
      Operation *loop = loops.back();
      auto [it, fresh] = isInnermost.try_emplace(loop, false);
      if (fresh)
        it->second = hasNoNestedLoop(loops.back());
      if (!it->second)
        return;
      byLoop[loop].push_back(op);
      depthOf[loop] = loops.size();
    });
    for (auto &[loop, ops] : byLoop)
      checkMemrefDependence(ops, depthOf[loop]);
    LLVM_DEBUG(llvm::dbgs()
               << "memory dependence analysis (" << byLoop.size()
               << " innermost loops) took "
               << std::chrono::duration<double>(
                      std::chrono::steady_clock::now() - t0)
                      .count()
               << " s\n");
    return;
  }

  // Collect affine loops grouped by nesting depth.
  std::vector<SmallVector<AffineForOp, 2>> depthToLoops;
  mlir::affine::gatherLoops(funcOp, depthToLoops);

  // Collect load and store operations to check.
  SmallVector<Operation *> memoryOps;
  funcOp.walk([&](Operation *op) {
    if (isa<AffineReadOpInterface, AffineWriteOpInterface>(op))
      memoryOps.push_back(op);
  });

  // For each depth, check memref accesses.
  for (unsigned depth = 1, e = depthToLoops.size(); depth <= e; ++depth)
    checkMemrefDependence(memoryOps, depth);
  LLVM_DEBUG(llvm::dbgs()
             << "memory dependence analysis took "
             << std::chrono::duration<double>(std::chrono::steady_clock::now() -
                                              t0)
                    .count()
             << " s\n");
}

/// Returns the dependences, if any, that the given Operation depends on.
ArrayRef<MemoryDependence>
circt::analysis::MemoryDependenceAnalysis::getDependences(Operation *op) {
  auto it = slotOf.find(op);
  if (it == slotOf.end())
    return {};
  return slots[it->second];
}

/// Replaces the dependences, if any, from the oldOp to the newOp.
void circt::analysis::MemoryDependenceAnalysis::replaceOp(Operation *oldOp,
                                                          Operation *newOp) {
  // Re-key the dependences *to* oldOp. (The original code assigned the new
  // key through the map iterator, which leaves the entry in the bucket of the
  // old key's hash, where a lookup by newOp cannot find it.)
  auto it = slotOf.find(oldOp);
  if (it != slotOf.end()) {
    unsigned slot = it->second;
    slotOf.erase(it);
    slotOf[newOp] = slot;
  }

  // Retarget the dependences *from* oldOp, using the inverted index instead
  // of a scan over every list.
  auto srcIt = bySource.find(oldOp);
  if (srcIt == bySource.end())
    return;
  SmallVector<unsigned> holders = std::move(srcIt->second);
  bySource.erase(srcIt);
  for (unsigned slot : holders)
    for (auto &dep : slots[slot])
      if (dep.source == oldOp)
        dep.source = newOp;
  bySource[newOp] = std::move(holders);
}
