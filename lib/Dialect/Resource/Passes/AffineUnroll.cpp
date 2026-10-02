//===- AffineUnroll.cpp - affine loop unrolling without the yield bug -----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// See AffineUnroll.h (OPEN_ISSUES O207).
//
//===----------------------------------------------------------------------===//

#include "circt/Dialect/Resource/Passes/AffineUnroll.h"

#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/BuiltinOps.h"
#include "llvm/ADT/SmallVector.h"

using namespace mlir;
using namespace mlir::affine;

namespace circt::hls_analysis {
namespace {

/// Marks the forwarding casts this file inserts, so only they are removed.
constexpr llvm::StringLiteral kUnrollForwardAttr = "hls.unroll_forward";

/// Wraps every affine.yield operand of `loop` that is a block argument of its
/// own body in an identity cast placed before the yield. Returns false when
/// nothing needed wrapping (the common case: the IR is left untouched).
bool wrapYieldedBlockArguments(AffineForOp loop) {
  Block *body = loop.getBody();
  Operation *yield = body->getTerminator();
  bool wrapped = false;
  OpBuilder builder(yield);
  for (OpOperand &operand : yield->getOpOperands()) {
    auto arg = dyn_cast<BlockArgument>(operand.get());
    if (!arg || arg.getOwner() != body)
      continue;
    auto cast = builder.create<UnrealizedConversionCastOp>(
        yield->getLoc(), TypeRange{arg.getType()}, ValueRange{arg});
    cast->setAttr(kUnrollForwardAttr, builder.getUnitAttr());
    operand.set(cast.getResult(0));
    wrapped = true;
  }
  return wrapped;
}

/// Replaces every forwarding cast below `scope` by its operand.
void removeForwardingCasts(Operation *scope) {
  SmallVector<UnrealizedConversionCastOp> casts;
  scope->walk([&](UnrealizedConversionCastOp cast) {
    if (cast->hasAttr(kUnrollForwardAttr))
      casts.push_back(cast);
  });
  for (UnrealizedConversionCastOp cast : casts) {
    cast.getResult(0).replaceAllUsesWith(cast.getOperand(0));
    cast->erase();
  }
}

template <typename UnrollFn>
LogicalResult unrollWithForwarding(AffineForOp loop, UnrollFn unroll) {
  Operation *scope = loop->getParentOp();
  bool wrapped = wrapYieldedBlockArguments(loop);
  LogicalResult result = unroll(loop);
  if (wrapped)
    removeForwardingCasts(scope);
  return result;
}

} // namespace

LogicalResult hlsLoopUnrollFull(AffineForOp loop) {
  return unrollWithForwarding(loop,
                              [](AffineForOp l) { return loopUnrollFull(l); });
}

LogicalResult hlsLoopUnrollByFactor(AffineForOp loop, uint64_t factor) {
  return unrollWithForwarding(
      loop, [factor](AffineForOp l) { return loopUnrollByFactor(l, factor); });
}

} // namespace circt::hls_analysis
