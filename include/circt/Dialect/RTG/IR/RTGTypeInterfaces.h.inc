/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtg {

/// This interface should be implemented by types that represent context
/// resources. The `on_context` operation takes an operand of a type
/// implementing this interface or a set of such a type.
/// Any operation that creates a value of a type implementing this interface
/// must implement the `ContextResourceOpInterface` (does not apply to
/// operations that just forward a value of such type).
class ContextResourceTypeInterface;

} // namespace circt::rtg
namespace circt::rtg {

/// This interface should be implemented by types that are allowed to be used
/// as the type of the 'ref' operands of the 'rtg.validate' operation.
class ValidationTypeInterface;

} // namespace circt::rtg
namespace circt::rtg {

/// This interface should be implemented by types that represent context
/// resources. The `on_context` operation takes an operand of a type
/// implementing this interface or a set of such a type.
/// Any operation that creates a value of a type implementing this interface
/// must implement the `ContextResourceOpInterface` (does not apply to
/// operations that just forward a value of such type).
namespace detail {
struct ContextResourceTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::circt::rtg::ContextResourceTypeInterface;
    Model() : Concept{} {}

  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::rtg::ContextResourceTypeInterface;
    FallbackModel() : Concept{} {}

  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct ContextResourceTypeInterfaceTrait;

} // namespace detail
class ContextResourceTypeInterface : public ::mlir::TypeInterface<ContextResourceTypeInterface, detail::ContextResourceTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<ContextResourceTypeInterface, detail::ContextResourceTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::ContextResourceTypeInterfaceTrait<ConcreteType> {};
};

} // namespace circt::rtg
namespace circt::rtg {

/// This interface should be implemented by types that are allowed to be used
/// as the type of the 'ref' operands of the 'rtg.validate' operation.
namespace detail {
struct ValidationTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    bool (*isValidContentType)(const Concept *impl, ::mlir::Type , mlir::Type);
    mlir::TypedAttr (*parseContentValue)(const Concept *impl, ::mlir::Type , mlir::StringRef, mlir::Type);
    std::string (*getIntrinsicLabel)(const Concept *impl, ::mlir::Type , mlir::Attribute, mlir::StringRef);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::circt::rtg::ValidationTypeInterface;
    Model() : Concept{isValidContentType, parseContentValue, getIntrinsicLabel} {}

    static inline bool isValidContentType(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::Type contentType);
    static inline mlir::TypedAttr parseContentValue(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::StringRef valueString, mlir::Type contentType);
    static inline std::string getIntrinsicLabel(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::Attribute value, mlir::StringRef id);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::rtg::ValidationTypeInterface;
    FallbackModel() : Concept{isValidContentType, parseContentValue, getIntrinsicLabel} {}

    static inline bool isValidContentType(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::Type contentType);
    static inline mlir::TypedAttr parseContentValue(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::StringRef valueString, mlir::Type contentType);
    static inline std::string getIntrinsicLabel(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::Attribute value, mlir::StringRef id);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct ValidationTypeInterfaceTrait;

} // namespace detail
class ValidationTypeInterface : public ::mlir::TypeInterface<ValidationTypeInterface, detail::ValidationTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<ValidationTypeInterface, detail::ValidationTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::ValidationTypeInterfaceTrait<ConcreteType> {};

  /// Returns whether the specified type is a valid content type, e.g., if this
  /// type is an integer register it is a handle to a bit-vector stored in that
  /// register, thus an immediate of the width of the register is a valid
  /// content type.
  bool isValidContentType(mlir::Type contentType) const;

  /// Parses the given string as a value of the given content type and returns
  /// an Attribute representing the value for that type. A null attribute may be
  /// returned if the string cannot be parsed as a value of the given type.
  mlir::TypedAttr parseContentValue(mlir::StringRef valueString, mlir::Type contentType) const;

  /// Returns the name of the intrinsic label that the desired simulator
  /// understands to print the content of this ref value annotated with the
  /// given ID. The 'value' attribute represents the concrete value, e.g., the
  /// exact register to print the content of instead of. Note: this might be
  /// generalized to an SSA value argument in the future if needed.
  std::string getIntrinsicLabel(mlir::Attribute value, mlir::StringRef id) const;
};

} // namespace circt::rtg
namespace circt::rtg::detail {

  template <typename ConcreteType>
  struct ContextResourceTypeInterfaceTrait : public ::mlir::TypeInterface<ContextResourceTypeInterface, detail::ContextResourceTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace circt::rtg::detail
namespace circt::rtg::detail {

  template <typename ConcreteType>
  struct ValidationTypeInterfaceTrait : public ::mlir::TypeInterface<ValidationTypeInterface, detail::ValidationTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace circt::rtg::detail
namespace circt::rtg {


} // namespace circt::rtg
namespace circt::rtg {

template<typename ConcreteType>
bool detail::ValidationTypeInterfaceInterfaceTraits::Model<ConcreteType>::isValidContentType(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::Type contentType) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).isValidContentType(contentType);
}
template<typename ConcreteType>
mlir::TypedAttr detail::ValidationTypeInterfaceInterfaceTraits::Model<ConcreteType>::parseContentValue(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::StringRef valueString, mlir::Type contentType) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).parseContentValue(valueString, contentType);
}
template<typename ConcreteType>
std::string detail::ValidationTypeInterfaceInterfaceTraits::Model<ConcreteType>::getIntrinsicLabel(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::Attribute value, mlir::StringRef id) {
  return (::llvm::cast<ConcreteType>(tablegen_opaque_val)).getIntrinsicLabel(value, id);
}
template<typename ConcreteType>
bool detail::ValidationTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::isValidContentType(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::Type contentType) {
  return static_cast<const ConcreteType *>(impl)->isValidContentType(tablegen_opaque_val, contentType);
}
template<typename ConcreteType>
mlir::TypedAttr detail::ValidationTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::parseContentValue(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::StringRef valueString, mlir::Type contentType) {
  return static_cast<const ConcreteType *>(impl)->parseContentValue(tablegen_opaque_val, valueString, contentType);
}
template<typename ConcreteType>
std::string detail::ValidationTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getIntrinsicLabel(const Concept *impl, ::mlir::Type tablegen_opaque_val, mlir::Attribute value, mlir::StringRef id) {
  return static_cast<const ConcreteType *>(impl)->getIntrinsicLabel(tablegen_opaque_val, value, id);
}

} // namespace circt::rtg
