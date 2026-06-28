/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtg {

/// This interface should be implemented by attributes that represent context
/// resources.
/// Any attribute implementing this interface must be of a type implementing
/// the `ContextResourceTypeInterface`.
/// 
/// TODO: properly verify this; unfortunately, we don't have a 'verify' field
/// here like the 'OpInterface' has.
class ContextResourceAttrInterface;

} // namespace circt::rtg
namespace circt::rtg {

/// This interface should be implemented by attributes that represent context
/// resources.
/// Any attribute implementing this interface must be of a type implementing
/// the `ContextResourceTypeInterface`.
/// 
/// TODO: properly verify this; unfortunately, we don't have a 'verify' field
/// here like the 'OpInterface' has.
namespace detail {
struct ContextResourceAttrInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    /// The base classes of this interface.
    const ::mlir::TypedAttr::Concept *implTypedAttr = nullptr;

    void initializeInterfaceConcept(::mlir::detail::InterfaceMap &interfaceMap) {
      implTypedAttr = interfaceMap.lookup<::mlir::TypedAttr>();
      assert(implTypedAttr && "`::circt::rtg::ContextResourceAttrInterface` expected its base interface `::mlir::TypedAttr` to be registered");
    }
  };
  template<typename ConcreteAttr>
  class Model : public Concept {
  public:
    using Interface = ::circt::rtg::ContextResourceAttrInterface;
    Model() : Concept{} {}

  };
  template<typename ConcreteAttr>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::rtg::ContextResourceAttrInterface;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteAttr>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteAttr;
  };
};
template <typename ConcreteAttr>
struct ContextResourceAttrInterfaceTrait;

} // namespace detail
class ContextResourceAttrInterface : public ::mlir::AttributeInterface<ContextResourceAttrInterface, detail::ContextResourceAttrInterfaceInterfaceTraits> {
public:
  using ::mlir::AttributeInterface<ContextResourceAttrInterface, detail::ContextResourceAttrInterfaceInterfaceTraits>::AttributeInterface;
  template <typename ConcreteAttr>
  struct Trait : public detail::ContextResourceAttrInterfaceTrait<ConcreteAttr> {};
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
  struct ContextResourceAttrInterfaceTrait : public ::mlir::AttributeInterface<ContextResourceAttrInterface, detail::ContextResourceAttrInterfaceInterfaceTraits>::Trait<ConcreteAttr> {
  };

} // namespace circt::rtg::detail
namespace circt::rtg {


} // namespace circt::rtg
