//===- ConstantCallEval.h - evaluate pure calls of constants ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Vitis evaluates a library call whose arguments are all constants at compile
// time (`hls::sqrt((data_t)4)` builds no core and its value narrows the width
// of the array the scaled data is stored in: VITIS_NOTES N130, kernels
// w9r17p_sq_*; forgebench attn_breakdown `scores_2`). This evaluates such
// calls by interpreting the callee (arith, scf, affine control flow and the
// calls it makes) and replaces each by its constant results.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTCALLEVAL_H
#define CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTCALLEVAL_H

#include "circt/Dialect/Resource/Plugins/PassPolicies.h"
#include "mlir/IR/BuiltinOps.h"
#include "llvm/ADT/SmallVector.h"

namespace circt::hls_analysis {

/// Replaces every `func.call` whose operands are all integer or float
/// constants, whose results are integers or floats, and whose callee is a
/// defined function without a user `inline off` (`hls.inline_off`) by the
/// constants the callee returns. The callee is interpreted: integer and
/// floating-point arith, scf.if / for / while, affine.for / if / apply /
/// min / max and nested calls of the same kind; any other operation (a
/// memory access, an external call), a division by zero, an undefined value
/// that reaches a decision or a result, or more than `maxSteps` executed
/// operations leaves the call as it is. Returns the number of calls
/// replaced; each is recorded in `notes` (rule `constant-call`).
unsigned foldConstantCalls(mlir::ModuleOp module, int64_t maxSteps,
                           llvm::SmallVectorImpl<circt::hlsest::FoldNote> &notes);

/// VITIS_NOTES N174: Vitis evaluates loops with constant trip counts that
/// fill local arrays from constants (LLVM's full unroll and SCCP), so a table
/// read at an index taken from such an array has a constant bank. In every
/// function, the operations of the entry block that store to local register
/// arrays (allocas completely partitioned on every dimension, of at most
/// `maxElements` integer or float elements, used only by loads and stores)
/// are interpreted in order, with the arrays' contents;
/// an array that only evaluated operations store to becomes a private
/// constant memref.global of its contents (rule `constant-fill-loops`),
/// the evaluated operations are removed (their results become constants),
/// and a table nothing reads is deleted. An operation that cannot be
/// evaluated (a run-time value, a call, an access of another memory) makes
/// the arrays it may store to unknown. Returns the arrays folded.
unsigned foldConstantFillPrefixes(
    mlir::ModuleOp module, int64_t maxSteps, int64_t maxElements,
    llvm::SmallVectorImpl<circt::hlsest::FoldNote> &notes);

} // namespace circt::hls_analysis

#endif // CIRCT_DIALECT_RESOURCE_PASSES_CONSTANTCALLEVAL_H
