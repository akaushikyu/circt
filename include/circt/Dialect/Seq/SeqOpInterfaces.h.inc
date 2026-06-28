/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::seq {

/// Trait for clocked elements
class Clocked;

} // namespace circt::seq
namespace circt::seq {

/// Trait for Resettable elements
class Resettable;

} // namespace circt::seq
namespace circt::seq {

/// Trait for clocked elements
namespace detail {
struct ClockedInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::Value (*getClk)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::seq::Clocked;
    Model() : Concept{getClk} {}

    static inline mlir::Value getClk(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::seq::Clocked;
    FallbackModel() : Concept{getClk} {}

    static inline mlir::Value getClk(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ClockedTrait;

} // namespace detail
class Clocked : public ::mlir::OpInterface<Clocked, detail::ClockedInterfaceTraits> {
public:
  using ::mlir::OpInterface<Clocked, detail::ClockedInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ClockedTrait<ConcreteOp> {};

  /// Get the clock signal
  mlir::Value getClk();
};

} // namespace circt::seq
namespace circt::seq {

/// Trait for Resettable elements
namespace detail {
struct ResettableInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::Value (*getReset)(const Concept *impl, ::mlir::Operation *);
    mlir::Value (*getResetValue)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::seq::Resettable;
    Model() : Concept{getReset, getResetValue} {}

    static inline mlir::Value getReset(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getResetValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::seq::Resettable;
    FallbackModel() : Concept{getReset, getResetValue} {}

    static inline mlir::Value getReset(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getResetValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ResettableTrait;

} // namespace detail
class Resettable : public ::mlir::OpInterface<Resettable, detail::ResettableInterfaceTraits> {
public:
  using ::mlir::OpInterface<Resettable, detail::ResettableInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ResettableTrait<ConcreteOp> {};

  /// Get the reset signal
  mlir::Value getReset();

  /// Get the reset value
  mlir::Value getResetValue();
};

} // namespace circt::seq
namespace circt::seq::detail {

  template <typename ConcreteOp>
  struct ClockedTrait : public ::mlir::OpInterface<Clocked, detail::ClockedInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::seq::detail
namespace circt::seq::detail {

  template <typename ConcreteOp>
  struct ResettableTrait : public ::mlir::OpInterface<Resettable, detail::ResettableInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::seq::detail
namespace circt::seq {

template<typename ConcreteOp>
mlir::Value detail::ClockedInterfaceTraits::Model<ConcreteOp>::getClk(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getClk();
}
template<typename ConcreteOp>
mlir::Value detail::ClockedInterfaceTraits::FallbackModel<ConcreteOp>::getClk(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getClk(tablegen_opaque_val);
}

} // namespace circt::seq
namespace circt::seq {

template<typename ConcreteOp>
mlir::Value detail::ResettableInterfaceTraits::Model<ConcreteOp>::getReset(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getReset();
}
template<typename ConcreteOp>
mlir::Value detail::ResettableInterfaceTraits::Model<ConcreteOp>::getResetValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResetValue();
}
template<typename ConcreteOp>
mlir::Value detail::ResettableInterfaceTraits::FallbackModel<ConcreteOp>::getReset(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getReset(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Value detail::ResettableInterfaceTraits::FallbackModel<ConcreteOp>::getResetValue(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getResetValue(tablegen_opaque_val);
}

} // namespace circt::seq
