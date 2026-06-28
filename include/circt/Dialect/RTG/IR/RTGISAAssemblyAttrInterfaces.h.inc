/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtg {

/// This interface should be implemented by attributes that represent
/// ISA registers. It is used for elaboration, register allocation, emission,
/// etc.
class RegisterAttrInterface;

} // namespace circt::rtg
namespace circt::rtg {

/// This interface should be implemented by attributes that represent
/// ISA registers. It is used for elaboration, register allocation, emission,
/// etc.
namespace detail {
struct RegisterAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    unsigned (*getClassIndex)(const Concept *impl, ::mlir::Attribute );
    llvm::StringLiteral (*getRegisterAssembly)(const Concept *impl, ::mlir::Attribute );
    /// The base classes of this interface.
    const ::mlir::TypedAttr::Concept *implTypedAttr = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implTypedAttr = interfaceMap.lookup<::mlir::TypedAttr>();
      assert(implTypedAttr && "`::circt::rtg::RegisterAttrInterface` expected its base interface `::mlir::TypedAttr` to be registered");
    }
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::circt::rtg::RegisterAttrInterface;
    Model() : Concept{getClassIndex, getRegisterAssembly} {}

    static inline unsigned getClassIndex(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline llvm::StringLiteral getRegisterAssembly(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::rtg::RegisterAttrInterface;
    FallbackModel() : Concept{getClassIndex, getRegisterAssembly} {}

    static inline unsigned getClassIndex(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
    static inline llvm::StringLiteral getRegisterAssembly(const Concept *impl, ::mlir::Attribute tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct RegisterAttrInterfaceTrait;

} // namespace detail
class RegisterAttrInterface : public ::mlir::AttributeInterface<RegisterAttrInterface, detail::RegisterAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<RegisterAttrInterface, detail::RegisterAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::RegisterAttrInterfaceTrait<ConcreteAttr> {};

  /// Returns the class specific index of the register. This translates from
  /// the flat internal representation to the architectural representation.
  unsigned getClassIndex() const;

  /// Returns a suitable string for use in assembly format.
  llvm::StringLiteral getRegisterAssembly() const;
  //===----------------------------------------------------------------===//
  // Inherited from ::mlir::TypedAttr
  //===----------------------------------------------------------------===//

  operator ::mlir::TypedAttr () const {
    if (!*this) return nullptr;
    return ::mlir::TypedAttr(*this, getImpl()->implTypedAttr);
  }


  /// Get the attribute's type
  ::mlir::Type getType() const;
};

} // namespace circt::rtg
namespace circt::rtg::detail {

  template <typename ConcreteAttr>
  struct RegisterAttrInterfaceTrait : public ::mlir::AttributeInterface<RegisterAttrInterface, detail::RegisterAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace circt::rtg::detail
namespace circt::rtg {

template<typename ConcreteAttr>
unsigned detail::RegisterAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getClassIndex(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getClassIndex();
}
template<typename ConcreteAttr>
llvm::StringLiteral detail::RegisterAttrInterfaceInterfaceTraits::Model<ConcreteAttr>::getRegisterAssembly(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return (::llvm::cast<ConcreteAttr>(tablegen_opaque_val)).getRegisterAssembly();
}
template<typename ConcreteAttr>
unsigned detail::RegisterAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getClassIndex(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getClassIndex(tablegen_opaque_val);
}
template<typename ConcreteAttr>
llvm::StringLiteral detail::RegisterAttrInterfaceInterfaceTraits::FallbackModel<ConcreteAttr>::getRegisterAssembly(const Concept *impl, ::mlir::Attribute tablegen_opaque_val) {
  return static_cast<const ConcreteAttr *>(impl)->getRegisterAssembly(tablegen_opaque_val);
}

} // namespace circt::rtg
