/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* Interface Declarations                                                     *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

namespace circt::om {

/// Common functionality for class-like operations.
class ClassLike;

} // namespace circt::om
namespace circt::om {

/// Common interface for integer binary ops.
class IntegerBinaryOp;

} // namespace circt::om
namespace circt::om {

/// Common interface for binary property equality ops.
class BinaryEqualityOp;

} // namespace circt::om
namespace circt::om {

/// Common functionality for class-like operations.
namespace detail {
struct ClassLikeInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    llvm::StringRef (*getSymName)(const Concept *impl, ::mlir::Operation *);
    mlir::StringAttr (*getSymNameAttr)(const Concept *impl, ::mlir::Operation *);
    mlir::StringAttr (*getSymNameAttrName)(const Concept *impl, ::mlir::Operation *);
    mlir::ArrayAttr (*getFormalParamNames)(const Concept *impl, ::mlir::Operation *);
    mlir::StringAttr (*getFormalParamNamesAttrName)(const Concept *impl, ::mlir::Operation *);
    mlir::DictionaryAttr (*getFieldTypes)(const Concept *impl, ::mlir::Operation *);
    mlir::Region &(*getBody)(const Concept *impl, ::mlir::Operation *);
    mlir::Block *(*getBodyBlock)(const Concept *impl, ::mlir::Operation *);
    std::optional<mlir::Type> (*getFieldType)(const Concept *impl, ::mlir::Operation *, mlir::StringAttr);
    mlir::ArrayAttr (*getFieldNames)(const Concept *impl, ::mlir::Operation *);
    void (*replaceFieldTypes)(const Concept *impl, ::mlir::Operation *, mlir::AttrTypeReplacer);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::om::ClassLike;
    Model() : Concept{getSymName, getSymNameAttr, getSymNameAttrName, getFormalParamNames, getFormalParamNamesAttrName, getFieldTypes, getBody, getBodyBlock, getFieldType, getFieldNames, replaceFieldTypes} {}

    static inline llvm::StringRef getSymName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getSymNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getSymNameAttrName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::ArrayAttr getFormalParamNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getFormalParamNamesAttrName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::DictionaryAttr getFieldTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Region &getBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Block *getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline std::optional<mlir::Type> getFieldType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::StringAttr field);
    static inline mlir::ArrayAttr getFieldNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void replaceFieldTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::AttrTypeReplacer replacer);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::om::ClassLike;
    FallbackModel() : Concept{getSymName, getSymNameAttr, getSymNameAttrName, getFormalParamNames, getFormalParamNamesAttrName, getFieldTypes, getBody, getBodyBlock, getFieldType, getFieldNames, replaceFieldTypes} {}

    static inline llvm::StringRef getSymName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getSymNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getSymNameAttrName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::ArrayAttr getFormalParamNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::StringAttr getFormalParamNamesAttrName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::DictionaryAttr getFieldTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Region &getBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Block *getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline std::optional<mlir::Type> getFieldType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::StringAttr field);
    static inline mlir::ArrayAttr getFieldNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline void replaceFieldTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::AttrTypeReplacer replacer);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct ClassLikeTrait;

} // namespace detail
class ClassLike : public ::mlir::OpInterface<ClassLike, detail::ClassLikeInterfaceTraits> {
public:
  using ::mlir::OpInterface<ClassLike, detail::ClassLikeInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::ClassLikeTrait<ConcreteOp> {};

  /// Get the class-like symbol name
  llvm::StringRef getSymName();

  /// Get the class-like symbol name attribute
  mlir::StringAttr getSymNameAttr();

  /// Get the class-like symbol name attribute name
  mlir::StringAttr getSymNameAttrName();

  /// Get the class-like formal parameter names attribute
  mlir::ArrayAttr getFormalParamNames();

  /// Get the class-like formal parameter names attribute name
  mlir::StringAttr getFormalParamNamesAttrName();

  /// Get the class-like dictionary mapping field names to type
  mlir::DictionaryAttr getFieldTypes();

  /// Get the class-like body region
  mlir::Region &getBody();

  /// Get the class-like body block
  mlir::Block *getBodyBlock();

  /// Get the class-like field type
  std::optional<mlir::Type> getFieldType(mlir::StringAttr field);

  /// Get the class-like field names
  mlir::ArrayAttr getFieldNames();

  /// Replace field types dictionary attr
  void replaceFieldTypes(mlir::AttrTypeReplacer replacer);
};

} // namespace circt::om
namespace circt::om {

/// Common interface for integer binary ops.
namespace detail {
struct IntegerBinaryOpInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::Value (*getLhs)(const Concept *impl, ::mlir::Operation *);
    mlir::Value (*getRhs)(const Concept *impl, ::mlir::Operation *);
    mlir::Value (*getResult)(const Concept *impl, ::mlir::Operation *);
    mlir::FailureOr<llvm::APSInt> (*evaluateIntegerOperation)(const Concept *impl, ::mlir::Operation *, const llvm::APSInt &, const llvm::APSInt &);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::om::IntegerBinaryOp;
    Model() : Concept{getLhs, getRhs, getResult, evaluateIntegerOperation} {}

    static inline mlir::Value getLhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getRhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::FailureOr<llvm::APSInt> evaluateIntegerOperation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::APSInt & lhs, const llvm::APSInt & rhs);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::om::IntegerBinaryOp;
    FallbackModel() : Concept{getLhs, getRhs, getResult, evaluateIntegerOperation} {}

    static inline mlir::Value getLhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getRhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::FailureOr<llvm::APSInt> evaluateIntegerOperation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::APSInt & lhs, const llvm::APSInt & rhs);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct IntegerBinaryOpTrait;

} // namespace detail
class IntegerBinaryOp : public ::mlir::OpInterface<IntegerBinaryOp, detail::IntegerBinaryOpInterfaceTraits> {
public:
  using ::mlir::OpInterface<IntegerBinaryOp, detail::IntegerBinaryOpInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::IntegerBinaryOpTrait<ConcreteOp> {};

  /// Get the lhs Value
  mlir::Value getLhs();

  /// Get the rhs Value
  mlir::Value getRhs();

  /// Get the result Value
  mlir::Value getResult();

  /// Evaluate the integer binary operation
  mlir::FailureOr<llvm::APSInt> evaluateIntegerOperation(const llvm::APSInt & lhs, const llvm::APSInt & rhs);
};

} // namespace circt::om
namespace circt::om {

/// Common interface for binary property equality ops.
namespace detail {
struct BinaryEqualityOpInterfaceTraits {
  struct Concept {
    /// The methods defined by the interface.
    mlir::Value (*getLhs)(const Concept *impl, ::mlir::Operation *);
    mlir::Value (*getRhs)(const Concept *impl, ::mlir::Operation *);
    mlir::Value (*getResult)(const Concept *impl, ::mlir::Operation *);
    mlir::FailureOr<mlir::Attribute> (*evaluateBinaryEquality)(const Concept *impl, ::mlir::Operation *, mlir::Attribute, mlir::Attribute);
  };
  template<typename ConcreteOp>
  class Model : public Concept {
  public:
    using Interface = circt::om::BinaryEqualityOp;
    Model() : Concept{getLhs, getRhs, getResult, evaluateBinaryEquality} {}

    static inline mlir::Value getLhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getRhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::FailureOr<mlir::Attribute> evaluateBinaryEquality(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::Attribute lhs, mlir::Attribute rhs);
  };
  template<typename ConcreteOp>
  class FallbackModel : public Concept {
  public:
    using Interface = circt::om::BinaryEqualityOp;
    FallbackModel() : Concept{getLhs, getRhs, getResult, evaluateBinaryEquality} {}

    static inline mlir::Value getLhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getRhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::Value getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val);
    static inline mlir::FailureOr<mlir::Attribute> evaluateBinaryEquality(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::Attribute lhs, mlir::Attribute rhs);
  };
  template<typename ConcreteModel, typename ConcreteOp>
  class ExternalModel : public FallbackModel<ConcreteModel> {
  public:
    using ConcreteEntity = ConcreteOp;
  };
};
template <typename ConcreteOp>
struct BinaryEqualityOpTrait;

} // namespace detail
class BinaryEqualityOp : public ::mlir::OpInterface<BinaryEqualityOp, detail::BinaryEqualityOpInterfaceTraits> {
public:
  using ::mlir::OpInterface<BinaryEqualityOp, detail::BinaryEqualityOpInterfaceTraits>::OpInterface;
  template <typename ConcreteOp>
  struct Trait : public detail::BinaryEqualityOpTrait<ConcreteOp> {};

  /// Get the lhs Value
  mlir::Value getLhs();

  /// Get the rhs Value
  mlir::Value getRhs();

  /// Get the result Value
  mlir::Value getResult();

  /// Evaluate the binary equality operation
  mlir::FailureOr<mlir::Attribute> evaluateBinaryEquality(mlir::Attribute lhs, mlir::Attribute rhs);
};

} // namespace circt::om
namespace circt::om::detail {

  template <typename ConcreteOp>
  struct ClassLikeTrait : public ::mlir::OpInterface<ClassLike, detail::ClassLikeInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::om::detail
namespace circt::om::detail {

  template <typename ConcreteOp>
  struct IntegerBinaryOpTrait : public ::mlir::OpInterface<IntegerBinaryOp, detail::IntegerBinaryOpInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::om::detail
namespace circt::om::detail {

  template <typename ConcreteOp>
  struct BinaryEqualityOpTrait : public ::mlir::OpInterface<BinaryEqualityOp, detail::BinaryEqualityOpInterfaceTraits>::Trait<ConcreteOp> {
  };

} // namespace circt::om::detail
namespace circt::om {

template<typename ConcreteOp>
llvm::StringRef detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getSymName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSymName();
}
template<typename ConcreteOp>
mlir::StringAttr detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getSymNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSymNameAttr();
}
template<typename ConcreteOp>
mlir::StringAttr detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getSymNameAttrName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getSymNameAttrName();
}
template<typename ConcreteOp>
mlir::ArrayAttr detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getFormalParamNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getFormalParamNames();
}
template<typename ConcreteOp>
mlir::StringAttr detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getFormalParamNamesAttrName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getFormalParamNamesAttrName();
}
template<typename ConcreteOp>
mlir::DictionaryAttr detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getFieldTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getFieldTypes();
}
template<typename ConcreteOp>
mlir::Region &detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getBody();
}
template<typename ConcreteOp>
mlir::Block *detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getBodyBlock();
}
template<typename ConcreteOp>
std::optional<mlir::Type> detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getFieldType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::StringAttr field) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getFieldType(field);
}
template<typename ConcreteOp>
mlir::ArrayAttr detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::getFieldNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getFieldNames();
}
template<typename ConcreteOp>
void detail::ClassLikeInterfaceTraits::Model<ConcreteOp>::replaceFieldTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::AttrTypeReplacer replacer) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).replaceFieldTypes(replacer);
}
template<typename ConcreteOp>
llvm::StringRef detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getSymName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getSymName(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::StringAttr detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getSymNameAttr(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getSymNameAttr(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::StringAttr detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getSymNameAttrName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getSymNameAttrName(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::ArrayAttr detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getFormalParamNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getFormalParamNames(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::StringAttr detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getFormalParamNamesAttrName(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getFormalParamNamesAttrName(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::DictionaryAttr detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getFieldTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getFieldTypes(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Region &detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getBody(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getBody(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Block *detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getBodyBlock(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getBodyBlock(tablegen_opaque_val);
}
template<typename ConcreteOp>
std::optional<mlir::Type> detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getFieldType(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::StringAttr field) {
  return static_cast<const ConcreteOp *>(impl)->getFieldType(tablegen_opaque_val, field);
}
template<typename ConcreteOp>
mlir::ArrayAttr detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::getFieldNames(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getFieldNames(tablegen_opaque_val);
}
template<typename ConcreteOp>
void detail::ClassLikeInterfaceTraits::FallbackModel<ConcreteOp>::replaceFieldTypes(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::AttrTypeReplacer replacer) {
  return static_cast<const ConcreteOp *>(impl)->replaceFieldTypes(tablegen_opaque_val, replacer);
}

} // namespace circt::om
namespace circt::om {

template<typename ConcreteOp>
mlir::Value detail::IntegerBinaryOpInterfaceTraits::Model<ConcreteOp>::getLhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLhs();
}
template<typename ConcreteOp>
mlir::Value detail::IntegerBinaryOpInterfaceTraits::Model<ConcreteOp>::getRhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRhs();
}
template<typename ConcreteOp>
mlir::Value detail::IntegerBinaryOpInterfaceTraits::Model<ConcreteOp>::getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResult();
}
template<typename ConcreteOp>
mlir::FailureOr<llvm::APSInt> detail::IntegerBinaryOpInterfaceTraits::Model<ConcreteOp>::evaluateIntegerOperation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::APSInt & lhs, const llvm::APSInt & rhs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).evaluateIntegerOperation(lhs, rhs);
}
template<typename ConcreteOp>
mlir::Value detail::IntegerBinaryOpInterfaceTraits::FallbackModel<ConcreteOp>::getLhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLhs(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Value detail::IntegerBinaryOpInterfaceTraits::FallbackModel<ConcreteOp>::getRhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getRhs(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Value detail::IntegerBinaryOpInterfaceTraits::FallbackModel<ConcreteOp>::getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getResult(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::FailureOr<llvm::APSInt> detail::IntegerBinaryOpInterfaceTraits::FallbackModel<ConcreteOp>::evaluateIntegerOperation(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, const llvm::APSInt & lhs, const llvm::APSInt & rhs) {
  return static_cast<const ConcreteOp *>(impl)->evaluateIntegerOperation(tablegen_opaque_val, lhs, rhs);
}

} // namespace circt::om
namespace circt::om {

template<typename ConcreteOp>
mlir::Value detail::BinaryEqualityOpInterfaceTraits::Model<ConcreteOp>::getLhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getLhs();
}
template<typename ConcreteOp>
mlir::Value detail::BinaryEqualityOpInterfaceTraits::Model<ConcreteOp>::getRhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getRhs();
}
template<typename ConcreteOp>
mlir::Value detail::BinaryEqualityOpInterfaceTraits::Model<ConcreteOp>::getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).getResult();
}
template<typename ConcreteOp>
mlir::FailureOr<mlir::Attribute> detail::BinaryEqualityOpInterfaceTraits::Model<ConcreteOp>::evaluateBinaryEquality(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::Attribute lhs, mlir::Attribute rhs) {
  return (llvm::cast<ConcreteOp>(tablegen_opaque_val)).evaluateBinaryEquality(lhs, rhs);
}
template<typename ConcreteOp>
mlir::Value detail::BinaryEqualityOpInterfaceTraits::FallbackModel<ConcreteOp>::getLhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getLhs(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Value detail::BinaryEqualityOpInterfaceTraits::FallbackModel<ConcreteOp>::getRhs(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getRhs(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::Value detail::BinaryEqualityOpInterfaceTraits::FallbackModel<ConcreteOp>::getResult(const Concept *impl, ::mlir::Operation *tablegen_opaque_val) {
  return static_cast<const ConcreteOp *>(impl)->getResult(tablegen_opaque_val);
}
template<typename ConcreteOp>
mlir::FailureOr<mlir::Attribute> detail::BinaryEqualityOpInterfaceTraits::FallbackModel<ConcreteOp>::evaluateBinaryEquality(const Concept *impl, ::mlir::Operation *tablegen_opaque_val, mlir::Attribute lhs, mlir::Attribute rhs) {
  return static_cast<const ConcreteOp *>(impl)->evaluateBinaryEquality(tablegen_opaque_val, lhs, rhs);
}

} // namespace circt::om
