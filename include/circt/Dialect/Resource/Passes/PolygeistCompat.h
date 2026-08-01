//===- PolygeistCompat.h - polygeist.subindex in cgeist output ------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// cgeist passes a row of a multi-dimensional array (`f(a[k])`, a reference to
// an element) as `"polygeist.subindex"(%a, %k) : (memref<NxMxT>, index) ->
// memref<MxT>`, an op of Polygeist's own dialect that hls-est could not parse
// (OPEN_ISSUES.md O25). This file gives hls-est a minimal `polygeist` dialect
// with that one op (a pure, view-like rank-reducing index into the leading
// dimension) and the pass `--lower-polygeist-subindex` that removes it:
//
//   - an affine / memref load or store through the view becomes an access of
//     the source array with the row prepended to its indices;
//   - a call that passes the view to a function defined in the module is
//     redirected to a clone of the callee whose parameter is replaced by the
//     whole array and the row index (the clone then indexes the row itself),
//     as Vitis clones a callee per array-argument form (VITIS_NOTES.md N14
//     R4: `work` and `work.1`). One clone per (callee, set of row
//     parameters, array types), shared by every call of that form.
//
// What stays (with a warning): a chained subindex, a same-rank subindex (a
// pointer offset into a memref<?x...>), a view passed to an external
// function or used by an op that is neither an access nor such a call.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_RESOURCE_PASSES_POLYGEISTCOMPAT_H
#define CIRCT_DIALECT_RESOURCE_PASSES_POLYGEISTCOMPAT_H

#include "mlir/IR/Dialect.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Interfaces/ViewLikeInterface.h"
#include "mlir/Pass/Pass.h"

#include <memory>

namespace circt::hls_analysis {

class PolygeistCompatDialect : public mlir::Dialect {
public:
  explicit PolygeistCompatDialect(mlir::MLIRContext *ctx);
  static llvm::StringRef getDialectNamespace() { return "polygeist"; }
};

/// `"polygeist.subindex"(%source, %index) : (memref<...>, index) ->
/// memref<...>`: the sub-array at `index` of the leading dimension of
/// `source` (rank reduced by one), or, when the ranks are equal, the source
/// offset by `index` elements of its leading dimension (Polygeist's pointer
/// arithmetic form). Pure; a view of its source.
class SubIndexOp
    : public mlir::Op<SubIndexOp, mlir::OpTrait::OneResult,
                      mlir::OpTrait::OneTypedResult<mlir::BaseMemRefType>::Impl,
                      mlir::OpTrait::NOperands<2>::Impl,
                      mlir::OpTrait::ZeroRegions, mlir::OpTrait::ZeroSuccessors,
                      mlir::MemoryEffectOpInterface::Trait,
                      mlir::ViewLikeOpInterface::Trait> {
public:
  using Op::Op;
  static llvm::StringRef getOperationName() { return "polygeist.subindex"; }
  static llvm::ArrayRef<llvm::StringRef> getAttributeNames() { return {}; }
  static void build(mlir::OpBuilder &builder, mlir::OperationState &state,
                    mlir::Type result, mlir::Value source, mlir::Value index);
  /// The `OpTy::create(builder, ...)` form TableGen ops have.
  static SubIndexOp create(mlir::OpBuilder &builder, mlir::Location loc,
                           mlir::Type result, mlir::Value source,
                           mlir::Value index) {
    mlir::OperationState state(loc, getOperationName());
    build(builder, state, result, source, index);
    return llvm::cast<SubIndexOp>(builder.create(state));
  }

  mlir::Value getSource() { return getOperand(0); }
  mlir::Value getIndex() { return getOperand(1); }
  mlir::Value getViewSource() { return getSource(); }
  void getEffects(
      llvm::SmallVectorImpl<mlir::SideEffects::EffectInstance<
          mlir::MemoryEffects::Effect>> &effects) {}
  mlir::LogicalResult verify();
  /// True iff the result has one dimension fewer than the source and the
  /// trailing dimensions agree (the row form this pass lowers).
  bool isRowSelect();
};

std::unique_ptr<mlir::Pass> createLowerSubIndexPass();
void registerLowerSubIndexPass();

} // namespace circt::hls_analysis

MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::hls_analysis::PolygeistCompatDialect)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::hls_analysis::SubIndexOp)

#endif // CIRCT_DIALECT_RESOURCE_PASSES_POLYGEISTCOMPAT_H
