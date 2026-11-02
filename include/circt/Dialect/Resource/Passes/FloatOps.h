//===- FloatOps.h - floating-point operator facts shared by passes --------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Facts about floating-point operators that the loop decision
// (--auto-pipeline-unroll) and the scheduler (--convert-affine-to-loopschedule)
// must agree on.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_FLOATOPS_H
#define CIRCT_DIALECT_RESOURCE_PASSES_FLOATOPS_H

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/Matchers.h"

namespace circt::hls_analysis {

/// Whether `op` is an arith.divf by a constant whose reciprocal is exact (a
/// finite, nonzero power of two, either sign). Vitis's LLVM front end
/// (InstCombine) rewrites such a divide into a multiply by the reciprocal,
/// so it is a multiplier, not a divider (W9r9 review D7: kernel
/// w9r9rev_e78_div2, `s / 2.0` is `fmul double %s, 5.0e-01` in a.o.3.ll,
/// II 11; VITIS_NOTES N79).
inline bool isExactReciprocalDivide(mlir::Operation *op) {
  auto div = mlir::dyn_cast<mlir::arith::DivFOp>(op);
  if (!div)
    return false;
  mlir::FloatAttr c;
  if (!mlir::matchPattern(div.getRhs(), mlir::m_Constant(&c)))
    return false;
  llvm::APFloat v = c.getValue();
  if (!v.isFiniteNonZero())
    return false;
  // getExactInverse succeeds exactly for powers of two whose reciprocal is
  // representable (the condition LLVM's fdiv -> fmul fold uses).
  return v.getExactInverse(nullptr);
}

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_FLOATOPS_H
