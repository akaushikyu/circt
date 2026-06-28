/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::sim {

/// An operation converting a value to a format fragment
class ValueFormatter;

} // namespace circt::sim
namespace circt::sim {

/// An operation converting a value to a format fragment
namespace detail {
struct ValueFormatterInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::mlir::StringAttr (*formatConstant)(const Concept *impl, ::mlir::Operation *, ::mlir::Attribute);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::sim::ValueFormatter;
    Model() : Concept{formatConstant} {}

    static inline ::mlir::StringAttr formatConstant(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Attribute constVal);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::sim::ValueFormatter;
    FallbackModel() : Concept{formatConstant} {}

    static inline ::mlir::StringAttr formatConstant(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Attribute constVal);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ValueFormatterTrait;

} // namespace detail
class ValueFormatter : public ::mlir::OpInterface<ValueFormatter, detail::ValueFormatterInterfaceTraits> {
public:
  using ::mlir::OpInterface<ValueFormatter, detail::ValueFormatterInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ValueFormatterTrait<ConcreteOp> {};

  /// Attempt to format an attribute as specified by this operation.
  ::mlir::StringAttr formatConstant(::mlir::Attribute constVal);
};

} // namespace circt::sim
namespace circt::sim::detail {

  template <typename ConcreteOp>
  struct ValueFormatterTrait : public ::mlir::OpInterface<ValueFormatter, detail::ValueFormatterInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::sim::detail
namespace circt::sim {

template<typename ConcreteOp>
::mlir::StringAttr detail::ValueFormatterInterfaceTraits::Model<ConcreteOp>::formatConstant(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Attribute constVal) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).formatConstant(constVal);
}
template<typename ConcreteOp>
::mlir::StringAttr detail::ValueFormatterInterfaceTraits::FallbackModel<ConcreteOp>::formatConstant(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, ::mlir::Attribute constVal) {
  return static_cast<const ConcreteOp *>(impl)->formatConstant(tablegen_opaque_val, constVal);
}

} // namespace circt::sim
