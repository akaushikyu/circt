//===- SchedulingAnalysis.cpp - scheduling analyses -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements methods that perform analysis involving scheduling.
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/CyclicSchedulingAnalysisModified.h"
#include "circt/Dialect/Resource/Passes/LoopPragmas.h"
#include "circt/Analysis/DependenceAnalysis.h"
#include "circt/Scheduling/Problems.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
#include "mlir/Dialect/Utils/StaticValueUtils.h"
#include "mlir/Pass/AnalysisManager.h"
#include "llvm/ADT/MapVector.h"

using namespace mlir;
using namespace mlir::affine;
using namespace circt::scheduling;

namespace {
/// One load or store of a runtime-loop body, with the indices that are
/// constants (std::nullopt elsewhere).
struct BodyAccess {
  Operation *op;
  Value mem;
  bool isWrite;
  SmallVector<std::optional<int64_t>, 4> constIndex;
};
} // namespace

static std::optional<BodyAccess> getBodyAccess(Operation *op) {
  BodyAccess a{op, Value(), false, {}};
  auto constantsOf = [&](ValueRange indices) {
    for (Value v : indices)
      a.constIndex.push_back(getConstantIntValue(v));
  };
  auto affineConstantsOf = [&](AffineMap map, ValueRange operands) {
    SmallVector<Value, 4> ops(operands.begin(), operands.end());
    fullyComposeAffineMapAndOperands(&map, &ops);
    canonicalizeMapAndOperands(&map, &ops);
    for (AffineExpr e : map.getResults()) {
      if (auto c = dyn_cast<AffineConstantExpr>(e))
        a.constIndex.push_back(c.getValue());
      else
        a.constIndex.push_back(std::nullopt);
    }
  };
  if (auto l = dyn_cast<memref::LoadOp>(op)) {
    a.mem = l.getMemRef();
    constantsOf(l.getIndices());
  } else if (auto st = dyn_cast<memref::StoreOp>(op)) {
    a.mem = st.getMemRef();
    a.isWrite = true;
    constantsOf(st.getIndices());
  } else if (auto l = dyn_cast<AffineLoadOp>(op)) {
    a.mem = l.getMemRef();
    affineConstantsOf(l.getAffineMap(), l.getMapOperands());
  } else if (auto st = dyn_cast<AffineStoreOp>(op)) {
    a.mem = st.getMemRef();
    a.isWrite = true;
    affineConstantsOf(st.getAffineMap(), st.getMapOperands());
  } else {
    return std::nullopt;
  }
  return a;
}

/// Two accesses of one memory that differ in a constant index never meet.
static bool constantDisjoint(const BodyAccess &x, const BodyAccess &y) {
  if (x.constIndex.size() != y.constIndex.size())
    return false;
  for (auto [cx, cy] : llvm::zip(x.constIndex, y.constIndex))
    if (cx && cy && *cx != *cy)
      return true;
  return false;
}

/// The intra-iteration memory dependences of a pipelined runtime-trip loop
/// (VITIS_NOTES.md N53): InnermostLoopDependenceAnalysis covers affine
/// accesses in innermost affine.for loops only, so the body of an scf.for
/// gets no store -> load / load -> store / store -> store ordering from it.
/// Every pair of accesses of one memory, at least one a store, is ordered in
/// program order (distance 0) unless a constant index tells them apart, as
/// the affine analysis does for an equivalent affine body. Loop-carried
/// memory dependences are not added (O1: none reach the scheduler for affine
/// loops either).
static void insertRuntimeBodyDependences(Block *body, CyclicProblem &problem) {
  llvm::MapVector<Value, SmallVector<BodyAccess, 8>> byMemory;
  body->walk<WalkOrder::PreOrder>([&](Operation *op) {
    if (std::optional<BodyAccess> a = getBodyAccess(op))
      byMemory[a->mem].push_back(std::move(*a));
  });
  for (auto &[mem, accesses] : byMemory)
    for (size_t i = 0; i < accesses.size(); ++i)
      for (size_t j = i + 1; j < accesses.size(); ++j) {
        const BodyAccess &x = accesses[i], &y = accesses[j];
        if ((!x.isWrite && !y.isWrite) || constantDisjoint(x, y))
          continue;
        (void)problem.insertDependence(Problem::Dependence(x.op, y.op));
      }
}

/// CyclicSchedulingAnalysis constructs a CyclicProblem for each AffineForOp by
/// performing a memory dependence analysis and inserting dependences into the
/// problem. The client should retrieve the partially complete problem to add
/// and associate operator types.
circt::hls_analysis::CyclicSchedulingAnalysis::CyclicSchedulingAnalysis(
    Operation *op, AnalysisManager &am) {
  auto funcOp = cast<func::FuncOp>(op);

  // MODIFIED (T7): only the dependences inside innermost loops, the only
  // loops --convert-affine-to-loopschedule pipelines (analyzeForOp inserts
  // the dependences of the ops in a loop's body into that loop's problem).
  analysis::MemoryDependenceAnalysis &memoryAnalysis =
      am.getAnalysis<analysis::InnermostLoopDependenceAnalysis>();

  // Find the innermost loop of every perfectly nested band, regardless of
  // enclosing control flow (scf.if/scf.for, etc.). Walk pre-order and skip
  // loops already absorbed into a band we've processed, so each innermost
  // loop is analyzed exactly once.
  DenseSet<Operation *> visited;
  funcOp.walk<WalkOrder::PreOrder>([&](AffineForOp root) {
    if (visited.contains(root))
      return;
    SmallVector<AffineForOp> nestedLoops;
    getPerfectlyNestedLoops(nestedLoops, root);
    for (AffineForOp l : nestedLoops)
      visited.insert(l);
    analyzeForOp(nestedLoops.back(), memoryAnalysis);
  });
  // The pipelined runtime-trip scf.for loops (VITIS_NOTES.md N53). Their
  // accesses are outside every innermost affine.for, so the memory analysis
  // has no dependences for them; analyzeLoop orders them within an
  // iteration (insertRuntimeBodyDependences; none across iterations, O1).
  funcOp.walk([&](scf::ForOp forOp) {
    if (isScheduledRuntimeFor(forOp))
      analyzeLoop(forOp, forOp.getBody(), forOp.getRegionIterArgs(),
                  memoryAnalysis);
  });
}

// The analysis is taken by reference: the previous by-value parameter copied
// the whole dependence map once per innermost loop.
void circt::hls_analysis::CyclicSchedulingAnalysis::analyzeForOp(
    AffineForOp forOp, analysis::MemoryDependenceAnalysis &memoryAnalysis) {
  analyzeLoop(forOp, forOp.getBody(), forOp.getRegionIterArgs(),
              memoryAnalysis);
}

void circt::hls_analysis::CyclicSchedulingAnalysis::analyzeLoop(
    Operation *loop, Block *body, ValueRange regionIterArgs,
    analysis::MemoryDependenceAnalysis &memoryAnalysis) {
  // Create a cyclic scheduling problem.
  CyclicProblem problem(loop);

  // Insert memory dependences into the problem.
  body->walk([&](Operation *op) {
    // Insert every operation into the problem.
    problem.insertOperation(op);

    ArrayRef<analysis::MemoryDependence> dependences = memoryAnalysis.getDependences(op);
    if (dependences.empty())
      return;

    for (analysis::MemoryDependence memoryDep : dependences) {
      // Don't insert a dependence into the problem if there is no dependence.
      if (!hasDependence(memoryDep.dependenceType))
        continue;

      // Insert a dependence into the problem.
      Problem::Dependence dep(memoryDep.source, op);
      auto depInserted = problem.insertDependence(dep);
      assert(succeeded(depInserted));
      (void)depInserted;

      // Use the lower bound of the innermost loop for this dependence. This
      // assumes outer loops execute sequentially, i.e. one iteration of the
      // inner loop completes before the next iteration is initiated. With
      // proper analysis and lowerings, this can be relaxed.
      unsigned distance = *memoryDep.dependenceComponents.back().lb;
      if (distance > 0)
        problem.setDistance(dep, distance);
    }
  });

  if (!isa<AffineForOp>(loop))
    insertRuntimeBodyDependences(body, problem);

  // Insert conditional dependences into the problem.
  body->walk([&](Operation *op) {
    Block *thenBlock = nullptr;
    Block *elseBlock = nullptr;
    if (auto ifOp = dyn_cast<scf::IfOp>(op)) {
      thenBlock = ifOp.thenBlock();
      elseBlock = ifOp.elseBlock();
    } else if (auto ifOp = dyn_cast<AffineIfOp>(op)) {
      thenBlock = ifOp.getThenBlock();
      if (ifOp.hasElse())
        elseBlock = ifOp.getElseBlock();
    } else {
      return WalkResult::advance();
    }

    // No special handling required for control-only `if`s.
    if (op->getNumResults() == 0)
      return WalkResult::skip();

    // Model the implicit value flow from the `yield` to the `if`'s result(s).
    Problem::Dependence depThen(thenBlock->getTerminator(), op);
    auto depInserted = problem.insertDependence(depThen);
    assert(succeeded(depInserted));
    (void)depInserted;

    if (elseBlock) {
      Problem::Dependence depElse(elseBlock->getTerminator(), op);
      depInserted = problem.insertDependence(depElse);
      assert(succeeded(depInserted));
      (void)depInserted;
    }

    return WalkResult::advance();
  });

  // Set the anchor for scheduling. Insert dependences from all stores to the
  // terminator to ensure the problem schedules them before the terminator.
  auto *anchor = body->getTerminator();
  body->walk([&](Operation *op) {
    if (!isa<AffineStoreOp, memref::StoreOp>(op))
      return;
    Problem::Dependence dep(op, anchor);
    auto depInserted = problem.insertDependence(dep);
    assert(succeeded(depInserted));
    (void)depInserted;
  });

  // Handle explicitly computed loop-carried values, i.e. excluding the
  // induction variable. Insert inter-iteration dependences from the definers of
  // "iter_args" to their users.
  if (unsigned nIterArgs = anchor->getNumOperands(); nIterArgs > 0) {
    ValueRange iterArgs = regionIterArgs;
    for (unsigned i = 0; i < nIterArgs; ++i) {
      Operation *iterArgDefiner = anchor->getOperand(i).getDefiningOp();
      // If it's not an operation, we don't need to model the dependence.
      if (!iterArgDefiner)
        continue;

      for (Operation *iterArgUser : iterArgs[i].getUsers()) {
        Problem::Dependence dep(iterArgDefiner, iterArgUser);
        auto depInserted = problem.insertDependence(dep);
        assert(succeeded(depInserted));
        (void)depInserted;

        // Values always flow between subsequent iterations.
        problem.setDistance(dep, 1);
      }
    }
  }

  // Store the partially complete problem.
  problems.insert(std::pair<Operation *, CyclicProblem>(loop, problem));
}

CyclicProblem &
circt::hls_analysis::CyclicSchedulingAnalysis::getProblem(AffineForOp forOp) {
  return getProblem(forOp.getOperation());
}

CyclicProblem &
circt::hls_analysis::CyclicSchedulingAnalysis::getProblem(Operation *loop) {
  auto problem = problems.find(loop);
  assert(problem != problems.end() && "expected problem to exist");
  return problem->second;
}
