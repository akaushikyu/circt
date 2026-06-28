/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::verif {

/// Common functionality for require-like operations.
class RequireLike;

} // namespace circt::verif
namespace circt::verif {

/// Common functionality for require-like operations.
namespace detail {
struct RequireLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    std::optional<llvm::StringRef> (*getLabel)(const Concept *impl, ::mlir::Operation *);
    mlir::StringAttr (*getLabelAttr)(const Concept *impl, ::mlir::Operation *);
    mlir::Value (*getProperty)(const Concept *impl, ::mlir::Operation *);
    mlir::Value (*getEnable)(const Concept *impl, ::mlir::Operation *);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::verif::RequireLike;
    Model() : Concept{getLabel, getLabelAttr, getProperty, getEnable} {}

    static inline std::optional<llvm::StringRef> getLabel(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getLabelAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getProperty(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getEnable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::verif::RequireLike;
    FallbackModel() : Concept{getLabel, getLabelAttr, getProperty, getEnable} {}

    static inline std::optional<llvm::StringRef> getLabel(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getLabelAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getProperty(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getEnable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct RequireLikeTrait;

} // namespace detail
class RequireLike : public ::mlir::OpInterface<RequireLike, detail::RequireLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<RequireLike, detail::RequireLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::RequireLikeTrait<ConcreteOp> {};

  /// Get the label
  std::optional<llvm::StringRef> getLabel();

  /// Get the label attribute
  mlir::StringAttr getLabelAttr();

  /// Get the property
  mlir::Value getProperty();

  /// Get the enable
  mlir::Value getEnable();
};

} // namespace circt::verif
namespace circt::verif::detail {

  template <typename ConcreteOp>
  struct RequireLikeTrait : public ::mlir::OpInterface<RequireLike, detail::RequireLikeInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::verif::detail
namespace circt::verif {

template<typename ConcreteOp>
std::optional<llvm::StringRef> detail::RequireLikeInterfaceTraits::Model<ConcreteOp>::getLabel(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLabel();
}
template<typename ConcreteOp>
mlir::StringAttr detail::RequireLikeInterfaceTraits::Model<ConcreteOp>::getLabelAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLabelAttr();
}
template<typename ConcreteOp>
mlir::Value detail::RequireLikeInterfaceTraits::Model<ConcreteOp>::getProperty(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getProperty();
}
template<typename ConcreteOp>
mlir::Value detail::RequireLikeInterfaceTraits::Model<ConcreteOp>::getEnable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getEnable();
}
template<typename ConcreteOp>
std::optional<llvm::StringRef> detail::RequireLikeInterfaceTraits::FallbackModel<ConcreteOp>::getLabel(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLabel(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::StringAttr detail::RequireLikeInterfaceTraits::FallbackModel<ConcreteOp>::getLabelAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLabelAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Value detail::RequireLikeInterfaceTraits::FallbackModel<ConcreteOp>::getProperty(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getProperty(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Value detail::RequireLikeInterfaceTraits::FallbackModel<ConcreteOp>::getEnable(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getEnable(tablegen_opaque_val);
}

} // namespace circt::verif
