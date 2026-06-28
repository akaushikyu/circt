/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtg {

/// This interface should be implemented by operations that implicitly enforce
/// a constraint. This is used to automatically materialize constraints that
/// are not explicitly specified by the user.
class ImplicitConstraintOpInterface;

} // namespace circt::rtg
namespace circt::rtg {

/// This interface should be implemented by operations that implicitly enforce
/// a constraint. This is used to automatically materialize constraints that
/// are not explicitly specified by the user.
namespace detail {
struct ImplicitConstraintOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*isConstraintMaterialized)(const Concept *impl, ::mlir::Operation *);
    mlir::Operation *(*materializeConstraint)(const Concept *impl, ::mlir::Operation *, mlir::OpBuilder &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = ::circt::rtg::ImplicitConstraintOpInterface;
    Model() : Concept{isConstraintMaterialized, materializeConstraint} {}

    static inline bool isConstraintMaterialized(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Operation *materializeConstraint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::OpBuilder & builder);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::rtg::ImplicitConstraintOpInterface;
    FallbackModel() : Concept{isConstraintMaterialized, materializeConstraint} {}

    static inline bool isConstraintMaterialized(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Operation *materializeConstraint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::OpBuilder & builder);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ImplicitConstraintOpInterfaceTrait;

} // namespace detail
class ImplicitConstraintOpInterface : public ::mlir::OpInterface<ImplicitConstraintOpInterface, detail::ImplicitConstraintOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<ImplicitConstraintOpInterface, detail::ImplicitConstraintOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ImplicitConstraintOpInterfaceTrait<ConcreteOp> {};

  /// Returns whether the constraint enforced by this operation has already
  /// been materialized.
  bool isConstraintMaterialized();

  /// Materialize the constraint enforced by this operation. The operation
  /// itself may be modified in place (return itself) or a new operation may
  /// be returned to be replaced with this operation. Returning `nullptr` means
  /// the operation should be erased without being replaced (only valid for
  /// operations without results).
  mlir::Operation *materializeConstraint(mlir::OpBuilder & builder);
};

} // namespace circt::rtg
namespace circt::rtg::detail {

  template <typename ConcreteOp>
  struct ImplicitConstraintOpInterfaceTrait : public ::mlir::OpInterface<ImplicitConstraintOpInterface, detail::ImplicitConstraintOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::rtg::detail
namespace circt::rtg {

template<typename ConcreteOp>
bool detail::ImplicitConstraintOpInterfaceInterfaceTraits::Model<ConcreteOp>::isConstraintMaterialized(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).isConstraintMaterialized();
}
template<typename ConcreteOp>
mlir::Operation *detail::ImplicitConstraintOpInterfaceInterfaceTraits::Model<ConcreteOp>::materializeConstraint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::OpBuilder & builder) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).materializeConstraint(builder);
}
template<typename ConcreteOp>
bool detail::ImplicitConstraintOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::isConstraintMaterialized(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->isConstraintMaterialized(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Operation *detail::ImplicitConstraintOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::materializeConstraint(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::OpBuilder & builder) {
  return static_cast<const ConcreteOp *>(impl)->materializeConstraint(tablegen_opaque_val, builder);
}

} // namespace circt::rtg
