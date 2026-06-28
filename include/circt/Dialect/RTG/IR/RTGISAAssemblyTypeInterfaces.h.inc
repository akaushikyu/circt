/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::rtg {

/// This interface should be implemented by types that represent
/// ISA registers. It is used for elaboration, register allocation, emission,
/// etc.
class RegisterTypeInterface;

} // namespace circt::rtg
namespace circt::rtg {

/// This interface should be implemented by types that represent
/// ISA registers. It is used for elaboration, register allocation, emission,
/// etc.
namespace detail {
struct RegisterTypeInterfaceInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    unsigned (*getRegisterClassSize)();
    ::circt::rtg::RegisterAttrInterface (*getRegisterAttrForClassIndex)(::mlir::MLIRContext *, unsigned);
  };
  template<typename ConcreteType>
  class Model : public Concept {
  public:
    using Interface = ::circt::rtg::RegisterTypeInterface;
    Model() : Concept{getRegisterClassSize, getRegisterAttrForClassIndex} {}

    static inline unsigned getRegisterClassSize();
    static inline ::circt::rtg::RegisterAttrInterface getRegisterAttrForClassIndex(::mlir::MLIRContext * ctx, unsigned index);
  };
  template<typename ConcreteType>
  class FallbackModel : public Concept {
  public:
    using Interface = ::circt::rtg::RegisterTypeInterface;
    FallbackModel() : Concept{getRegisterClassSize, getRegisterAttrForClassIndex} {}

    static inline unsigned getRegisterClassSize();
    static inline ::circt::rtg::RegisterAttrInterface getRegisterAttrForClassIndex(::mlir::MLIRContext * ctx, unsigned index);
  };
  template<typename ConcreteModel, typename ConcreteType>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteType;
  };
};
template <typename ConcreteType>
struct RegisterTypeInterfaceTrait;

} // namespace detail
class RegisterTypeInterface : public ::mlir::TypeInterface<RegisterTypeInterface, detail::RegisterTypeInterfaceInterfaceTraits> {
public:
  using ::mlir::TypeInterface<RegisterTypeInterface, detail::RegisterTypeInterfaceInterfaceTraits>::TypeInterface;
  template <typename ConcreteType>
  struct Trait : public detail::RegisterTypeInterfaceTrait<ConcreteType> {};

  /// Returns the number of registers in the class. Class indices are assumed
  /// to be a continuous range from 0 
  unsigned getRegisterClassSize() const;

  /// Returns the register attribute for the given class-specific index.
  /// Returns nullptr if the index is out of range.
  ::circt::rtg::RegisterAttrInterface getRegisterAttrForClassIndex(::mlir::MLIRContext * ctx, unsigned index) const;
};

} // namespace circt::rtg
namespace circt::rtg::detail {

  template <typename ConcreteType>
  struct RegisterTypeInterfaceTrait : public ::mlir::TypeInterface<RegisterTypeInterface, detail::RegisterTypeInterfaceInterfaceTraits>::Trait<ConcreteType> {
  };

} // namespace circt::rtg::detail
namespace circt::rtg {

template<typename ConcreteType>
unsigned detail::RegisterTypeInterfaceInterfaceTraits::Model<ConcreteType>::getRegisterClassSize() {
  return ConcreteType::getRegisterClassSize();
}
template<typename ConcreteType>
::circt::rtg::RegisterAttrInterface detail::RegisterTypeInterfaceInterfaceTraits::Model<ConcreteType>::getRegisterAttrForClassIndex(::mlir::MLIRContext * ctx, unsigned index) {
  return ConcreteType::getRegisterAttrForClassIndex(ctx, index);
}
template<typename ConcreteType>
unsigned detail::RegisterTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getRegisterClassSize() {
  return ConcreteType::getRegisterClassSize();
}
template<typename ConcreteType>
::circt::rtg::RegisterAttrInterface detail::RegisterTypeInterfaceInterfaceTraits::FallbackModel<ConcreteType>::getRegisterAttrForClassIndex(::mlir::MLIRContext * ctx, unsigned index) {
  return ConcreteType::getRegisterAttrForClassIndex(ctx, index);
}

} // namespace circt::rtg
