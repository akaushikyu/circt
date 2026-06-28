/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Definitions                                                      *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/


/// Returns whether the constraint enforced by this operation has already
/// been materialized.
bool circt::rtg::ImplicitConstraintOpInterface::isConstraintMaterialized() {
      return getImpl()->isConstraintMaterialized(getImpl(), getOperation());
  }

/// Materialize the constraint enforced by this operation. The operation
/// itself may be modified in place (return itself) or a new operation may
/// be returned to be replaced with this operation. Returning `nullptr` means
/// the operation should be erased without being replaced (only valid for
/// operations without results).
mlir::Operation *circt::rtg::ImplicitConstraintOpInterface::materializeConstraint(mlir::OpBuilder & builder) {
      return getImpl()->materializeConstraint(getImpl(), getOperation(), builder);
  }
