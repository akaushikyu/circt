//===- AffineUnroll.h - affine loop unrolling without the yield bug -------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Wrappers around mlir::affine::loopUnrollFull / loopUnrollByFactor that are
// correct for a loop whose affine.yield returns one of the loop body's own
// block arguments (an iter_arg passed through, `yield %new, %a`, or the
// induction variable).
//
// Upstream `generateUnrolledLoop` (mlir/lib/Dialect/Affine/Utils/LoopUtils.cpp)
// advances the value a yielded operand denotes only when the operand is
// defined by an op of the body; a yielded block argument keeps the original
// block argument, so every later copy reads the loop's initial value
// (OPEN_ISSUES O207: `for (j < 3) { t = x + y; x = y; y = t; }` gave
// `out = in1` instead of `in0 + 2 in1`). The llvm submodule is not rebuilt, so
// the fix is here: each such operand is wrapped in a forwarding op of the body
// before the unroll (cloned and remapped like any body op) and the forwarding
// ops are removed again afterwards.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_AFFINEUNROLL_H
#define CIRCT_DIALECT_RESOURCE_PASSES_AFFINEUNROLL_H

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Support/LogicalResult.h"

#include <cstdint>

namespace circt::hls_analysis {

/// mlir::affine::loopUnrollFull, correct for yielded body block arguments.
mlir::LogicalResult hlsLoopUnrollFull(mlir::affine::AffineForOp loop);

/// mlir::affine::loopUnrollByFactor, correct for yielded body block arguments.
mlir::LogicalResult hlsLoopUnrollByFactor(mlir::affine::AffineForOp loop,
                                          uint64_t factor);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_AFFINEUNROLL_H
