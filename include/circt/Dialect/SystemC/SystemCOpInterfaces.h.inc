/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::systemc {

/// Provide common information for operations that declare a SystemC variable
/// name.
class SystemCNameDeclOpInterface;

} // namespace circt::systemc
namespace circt::systemc {

/// Provide common information for operations that declare a SystemC variable
/// name.
namespace detail {
struct SystemCNameDeclOpInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    ::llvm::StringRef (*getName)(const Concept *impl, ::mlir::Operation *);
    ::mlir::StringAttr (*getNameAttr)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::systemc::SystemCNameDeclOpInterface;
    Model() : Concept{getName, getNameAttr} {}

    static inline ::llvm::StringRef getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::StringAttr getNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::systemc::SystemCNameDeclOpInterface;
    FallbackModel() : Concept{getName, getNameAttr} {}

    static inline ::llvm::StringRef getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline ::mlir::StringAttr getNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
    ::llvm::StringRef getName(::mlir::Operation *tablegen_opaque_val) const;
    ::mlir::StringAttr getNameAttr(::mlir::Operation *tablegen_opaque_val) const;
  };
};
template <typename ConcreteOp>
struct SystemCNameDeclOpInterfaceTrait;

} // namespace detail
class SystemCNameDeclOpInterface : public ::mlir::OpInterface<SystemCNameDeclOpInterface, detail::SystemCNameDeclOpInterfaceInterfaceTraits> {
public:
  using ::mlir::OpInterface<SystemCNameDeclOpInterface, detail::SystemCNameDeclOpInterfaceInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::SystemCNameDeclOpInterfaceTrait<ConcreteOp> {};

  /// Get the declared name
  ::llvm::StringRef getName();

  /// Get the declared name
  ::mlir::StringAttr getNameAttr();
};

} // namespace circt::systemc
namespace circt::systemc::detail {

  template <typename ConcreteOp>
  struct SystemCNameDeclOpInterfaceTrait : public ::mlir::OpInterface<SystemCNameDeclOpInterface, detail::SystemCNameDeclOpInterfaceInterfaceTraits>::Trait<ConcreteOp> {

    /// Get the declared name
    ::llvm::StringRef getName() {
      return (*static_cast<ConcreteOp *>(this)).getName();
    }

    /// Get the declared name
    ::mlir::StringAttr getNameAttr() {
      return (*static_cast<ConcreteOp *>(this)).getNameAttr();
    }
    static ::llvm::LogicalResult verifyTrait(::mlir::Operation *op) {
      assert(op->hasAttrOfType<mlir::StringAttr>("name"));
    if (op->getAttrOfType<mlir::StringAttr>("name").getValue().empty())
      return op->emitOpError("'name' attribute must not be empty");
    return mlir::success();
    }
  };

} // namespace circt::systemc::detail
namespace circt::systemc {

template<typename ConcreteOp>
::llvm::StringRef detail::SystemCNameDeclOpInterfaceInterfaceTraits::Model<ConcreteOp>::getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getName();
}
template<typename ConcreteOp>
::mlir::StringAttr detail::SystemCNameDeclOpInterfaceInterfaceTraits::Model<ConcreteOp>::getNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameAttr();
}
template<typename ConcreteOp>
::llvm::StringRef detail::SystemCNameDeclOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getName(tablegen_opaque_val);
}
template<typename ConcreteOp>
::mlir::StringAttr detail::SystemCNameDeclOpInterfaceInterfaceTraits::FallbackModel<ConcreteOp>::getNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getNameAttr(tablegen_opaque_val);
}
template<typename ConcreteModel, typename ConcreteOp>
::llvm::StringRef detail::SystemCNameDeclOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getName(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getName();
}
template<typename ConcreteModel, typename ConcreteOp>
::mlir::StringAttr detail::SystemCNameDeclOpInterfaceInterfaceTraits::ExternalModel<ConcreteModel, ConcreteOp>::getNameAttr(::mlir::Operation *tablegen_opaque_val) const {
return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getNameAttr();
}

} // namespace circt::systemc
