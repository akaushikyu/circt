//===- AutoPipelineUnroll.cpp - unroll small innermost affine loops -------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Automatically fully unrolls every innermost affine.for loop whose constant
// trip count is below a threshold T.
//
// Rule:
//
//   For each innermost loop L (an affine.for containing no nested affine.for):
//     - L has a known constant trip count TC(L), and
//     - TC(L) < THRESHOLD
//   -> fully unroll L.
//
//   THRESHOLD defaults to 64 and is controlled by the -threshold option.
//
// Loops with an unknown / dynamic trip count, or with TC(L) >= THRESHOLD, are
// left untouched so they can be pipelined in place downstream.
//
//===----------------------------------------------------------------------===//

#include "mlir/Dialect/Affine/Analysis/LoopAnalysis.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Pass/Pass.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "auto-pipeline-unroll"

using namespace mlir;
using namespace mlir::affine;

namespace {

/// True iff `forOp` is innermost, i.e. its body contains no nested affine.for.
static bool isInnermostLoop(AffineForOp forOp) {
  bool hasNestedLoop = false;
  forOp.getBody()->walk([&](AffineForOp nested) {
    hasNestedLoop = true;
    return WalkResult::interrupt();
  });
  return !hasNestedLoop;
}

struct AutoPipelineUnrollPass
    : public PassWrapper<AutoPipelineUnrollPass, OperationPass<func::FuncOp>> {
  MLIR_DEFINE_EXPLICIT_INTERNAL_INLINE_TYPE_ID(AutoPipelineUnrollPass)

  AutoPipelineUnrollPass() = default;
  AutoPipelineUnrollPass(const AutoPipelineUnrollPass &other)
      : PassWrapper(other) {}

  Option<unsigned> threshold{
      *this, "threshold",
      llvm::cl::desc("Fully unroll innermost affine loops whose constant trip "
                     "count is below this threshold (default 64)"),
      llvm::cl::init(32)};

  StringRef getArgument() const final { return "auto-pipeline-unroll"; }
  StringRef getDescription() const final {
    return "Fully unroll every innermost affine.for loop whose known trip "
           "count is below the threshold.";
  }

  void runOnOperation() override {
    func::FuncOp func = getOperation();

    // Collect innermost loops first; unrolling mutates the IR, so we must not
    // walk and mutate at the same time.
    SmallVector<AffineForOp> innermost;
    func.walk([&](AffineForOp forOp) {
      if (isInnermostLoop(forOp))
        innermost.push_back(forOp);
    });

    for (AffineForOp forOp : innermost) {
      std::optional<uint64_t> tripCount = getConstantTripCount(forOp);
      if (!tripCount || *tripCount == 0)
        continue; // Unknown / dynamic trip count -> leave in place.
      if (*tripCount <= threshold)
        continue; // Large loop -> pipeline in place downstream.
      LLVM_DEBUG(llvm::dbgs()
                 << "unrolling innermost loop (trip " << *tripCount << " < "
                 << threshold << ") @ " << forOp.getLoc() << "\n");
      if (failed(loopUnrollFull(forOp)))
        LLVM_DEBUG(llvm::dbgs() << "  loopUnrollFull failed\n");
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
