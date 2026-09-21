//===- FoldUnrolledGuards.h - drop affine.if arms that never run ----------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// After a loop is unrolled, each copy's affine.if guards take the copy's
// constant index as an operand: `if (k + j * N == 0)` becomes
// `affine.if (d0 == 0, d1 == 0)(%c3, %j)` in copy 3, a guard that can never
// hold. Vitis drops such a copy's accesses (VITIS_NOTES N89, kernel
// w9r11p_sa_cnd2: one stream read per iteration, II 1); --canonicalize does
// not fold a set whose operands are constants. cgeist emits a guard with a
// `%` or a non-affine shape as arith + scf.if (w9r11rev_fg_mod), decided the
// same way; an equality that fixes a variable makes it a constant in the
// guarded arm (w9r11rev_fg_unr, VITIS_NOTES N89 (b)).
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_FOLDUNROLLEDGUARDS_H
#define CIRCT_DIALECT_RESOURCE_PASSES_FOLDUNROLLEDGUARDS_H

#include "mlir/IR/Operation.h"
#include "llvm/ADT/StringRef.h"

namespace circt::hls_analysis {

/// What foldConstantAffineIfs did.
struct FoldedGuards {
  unsigned folded = 0;         ///< ifs replaced by one arm (or erased)
  unsigned scfIfs = 0;         ///< of those, scf.if
  unsigned pinnedOperands = 0; ///< operands fixed by an equality (N89 (b))
};

/// The counters on the nearest enclosing loop (--bram-debug pipelines[]).
constexpr llvm::StringLiteral kFoldedGuardsAttr = "hls.folded_guards";
constexpr llvm::StringLiteral kPinnedGuardOperandsAttr =
    "hls.pinned_guard_operands";

/// Substitute the constant operands of every affine.if under `root` into its
/// integer set; an if whose set is then empty is replaced by its else region
/// (or erased), one whose set is universal by its then region. An scf.if
/// whose condition is an affine comparison of loop induction variables
/// (arith add / sub / constant multiply / rem / div, C's normalised `%`,
/// and / or) is decided the same way. In the then arm of an affine.if left,
/// an operand an equality of the set fixes is replaced by that constant.
FoldedGuards foldConstantAffineIfs(mlir::Operation *root);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_FOLDUNROLLEDGUARDS_H
