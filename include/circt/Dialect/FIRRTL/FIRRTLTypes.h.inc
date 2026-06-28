/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Declarations                                                       *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES


namespace mlir {
class AsmParser;
class AsmPrinter;
} // namespace mlir
namespace circt::firrtl {

/// A signed integer type, whose width may not be known.
class SIntType;
/// An unsigned integer type, whose width may not be known.
class UIntType;
/// Clock signal
class ClockType;
/// Reset Signal
class ResetType;
/// AsyncReset signal
class AsyncResetType;
/// Analog signal
class AnalogType;
/// a fixed size collection of elements, like an array.
class FVectorType;
/// a fixed size collection of elements, like an array.
class OpenVectorType;
/// an aggregate of named elements. This is effectively a struct.
class BundleType;
/// an aggregate of named elements. This is effectively a struct.
class OpenBundleType;
/// a sum type of named elements.
class FEnumType;
/// A reference to a signal elsewhere.
/// A reference type, such as `firrtl.probe<uint<1>>` or `firrtl.rwprobe<uint<2>>`.
/// 
/// Used for remote reads and writes of the wrapped base type.
/// 
/// Parameterized over the referenced base type, with flips removed.
/// 
/// Not a base type.
/// 
/// Values of this type are used to capture dataflow paths,
/// and do not represent a circuit element or entity.
/// 
/// Generally read-only (probe), optionally forceable (rwprobe).
class RefType;
/// A wrapper for LHS types.
/// A LHS type is a type usable for the destination of a strict connect
/// and for field indexing.  No other operations are valid.  Any passive,
/// strict-connectable types are valid inside LHS types.
class LHSType;
/// type alias for firrtl base types
class BaseTypeAliasType;
/// An instance of a class.
/// 
/// Example:
/// ```mlir
/// !firrtl.class<@Module(in p0: !firrtl.uint<8>, out p1: !firrtl.uint<8>)>
/// ```
class ClassType;
/// A reference to an instance of any class.
/// A reference of type AnyRef can be used in ports, property assignments, and
/// any other Property "plumbing" ops. But it is opaque, and references to
/// objects of AnyRef type cannot be "dereferenced". There is no information
/// about the referred to object's fields, so subfield access, etc. is illegal.
class AnyRefType;
/// An unlimited length string type. Not representable in hardware.
class StringType;
/// An unlimited length signed integer type.  Not representable in hardware.
class FIntegerType;
/// A typed property list of any length.  Not representable in hardware.
class ListType;
/// A path to a hardware entity.  Not representable in hardware.
class PathType;
/// A boolean property.  Not representable in hardware.
class BoolType;
/// A double property.  Not representable in hardware.
class DoubleType;
/// A format string type
class FStringType;
/// An instance of a domain.
/// 
/// Examples:
/// ```mlir
/// // Domain without fields
/// !firrtl.domain<@ClockDomain()>
/// 
/// // Domain with fields
/// !firrtl.domain<@PowerDomain(voltage: !firrtl.integer, frequency: !firrtl.integer)>
/// ```
class DomainType;
class SIntType : public ::mlir::Type::TypeBase<SIntType, ::circt::firrtl::IntType, detail::WidthTypeStorage, ::circt::firrtl::WidthQualifiedTypeTrait> {
public:
  using Base::Base;
  using WidthQualifiedTypeTrait<SIntType>::getWidth;
  using WidthQualifiedTypeTrait<SIntType>::hasWidth;
  int32_t getWidthOrSentinel() const;
  SIntType getConstType(bool isConst) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.sint";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static SIntType get(::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst);
  static SIntType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst);
  static SIntType get(::mlir::MLIRContext *context, std::optional<int32_t> width, bool isConst = false);
  static SIntType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, std::optional<int32_t> width, bool isConst = false);
  static SIntType get(::mlir::MLIRContext *context);
  static SIntType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst);
};
class UIntType : public ::mlir::Type::TypeBase<UIntType, ::circt::firrtl::IntType, detail::WidthTypeStorage, ::circt::firrtl::WidthQualifiedTypeTrait> {
public:
  using Base::Base;
  using WidthQualifiedTypeTrait<UIntType>::getWidth;
  using WidthQualifiedTypeTrait<UIntType>::hasWidth;
  int32_t getWidthOrSentinel() const;
  UIntType getConstType(bool isConst) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.uint";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static UIntType get(::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst);
  static UIntType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst);
  static UIntType get(::mlir::MLIRContext *context, std::optional<int32_t> width, bool isConst = false);
  static UIntType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, std::optional<int32_t> width, bool isConst = false);
  static UIntType get(::mlir::MLIRContext *context);
  static UIntType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst);
};
class ClockType : public ::mlir::Type::TypeBase<ClockType, ::circt::firrtl::FIRRTLBaseType, detail::FIRRTLBaseTypeStorage> {
public:
  using Base::Base;
  ClockType getConstType(bool isConst) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.clock";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static ClockType get(::mlir::MLIRContext *context, bool isConst);
  static ClockType get(::mlir::MLIRContext *context);
};
class ResetType : public ::mlir::Type::TypeBase<ResetType, ::circt::firrtl::FIRRTLBaseType, detail::FIRRTLBaseTypeStorage> {
public:
  using Base::Base;
  ResetType getConstType(bool isConst) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.reset";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static ResetType get(::mlir::MLIRContext *context, bool isConst);
  static ResetType get(::mlir::MLIRContext *context);
};
class AsyncResetType : public ::mlir::Type::TypeBase<AsyncResetType, ::circt::firrtl::FIRRTLBaseType, detail::FIRRTLBaseTypeStorage> {
public:
  using Base::Base;
  AsyncResetType getConstType(bool isConst) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.asyncreset";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static AsyncResetType get(::mlir::MLIRContext *context, bool isConst);
  static AsyncResetType get(::mlir::MLIRContext *context);
};
class AnalogType : public ::mlir::Type::TypeBase<AnalogType, ::circt::firrtl::FIRRTLBaseType, detail::WidthTypeStorage, ::circt::firrtl::WidthQualifiedTypeTrait> {
public:
  using Base::Base;
  int32_t getWidthOrSentinel() const;
  AnalogType getConstType(bool isConst) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.analog";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static AnalogType get(::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst);
  static AnalogType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, int32_t widthOrSentinel, bool isConst);
  static AnalogType get(::mlir::MLIRContext *context, std::optional<int32_t> width, bool isConst = false);
  static AnalogType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, std::optional<int32_t> width, bool isConst = false);
  static AnalogType get(::mlir::MLIRContext *context);
  static AnalogType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, int32_t widthOrSentinel, bool isConst);
};
class FVectorType : public ::mlir::Type::TypeBase<FVectorType, ::circt::firrtl::FIRRTLBaseType, detail::FVectorTypeStorage, circt::hw::FieldIDTypeInterface::Trait> {
public:
  using Base::Base;
  using ElementType = ::circt::firrtl::FIRRTLBaseType;

  ElementType getElementType() const;
  size_t getNumElements() const;

  /// Return the recursive properties of the type.
  RecursiveTypeProperties getRecursiveTypeProperties() const;

  /// Const support.
  bool isConst() const;
  ElementType getElementTypePreservingConst();

  /// Return a 'const' or non-'const' version of this type.
  FVectorType getConstType(bool isConst) const;


  /// Return this type with any flip types recursively removed from itself.
  FIRRTLBaseType getPassiveType();

  /// Return this type with a 'const' modifiers dropped
  FVectorType getAllConstDroppedType();

  /// Return this type with any type alias types recursively removed from itself.
  FIRRTLBaseType getAnonymousType();
  static constexpr ::llvm::StringLiteral name = "firrtl.vector";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static FVectorType get(::circt::firrtl::FIRRTLBaseType elementType, size_t numElements, bool isConst = false);
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
};
class OpenVectorType : public ::mlir::Type::TypeBase<OpenVectorType, ::circt::firrtl::FIRRTLType, detail::OpenVectorTypeStorage, circt::hw::FieldIDTypeInterface::Trait> {
public:
  using Base::Base;
  using ElementType = ::circt::firrtl::FIRRTLType;

  ElementType getElementType() const;
  size_t getNumElements() const;

  /// Return the recursive properties of the type.
  RecursiveTypeProperties getRecursiveTypeProperties() const;

  /// Const support.
  bool isConst() const;
  ElementType getElementTypePreservingConst();

  /// Return a 'const' or non-'const' version of this type.
  OpenVectorType getConstType(bool isConst) const;

  static constexpr ::llvm::StringLiteral name = "firrtl.openvector";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static OpenVectorType get(::circt::firrtl::FIRRTLType elementType, size_t numElements, bool isConst = false);
  static OpenVectorType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLType elementType, size_t numElements, bool isConst = false);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLType elementType, size_t numElements, bool isConst);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLType elementType, size_t numElements, bool isConst);
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
};
class BundleType : public ::mlir::Type::TypeBase<BundleType, ::circt::firrtl::FIRRTLBaseType, detail::BundleTypeStorage, circt::hw::FieldIDTypeInterface::Trait> {
public:
  using Base::Base;
  using ElementType = ::circt::firrtl::FIRRTLBaseType;

  /// Each element of a bundle, which is a name and type.
  struct BundleElement {
    StringAttr name;
    bool isFlip;
    ElementType type;

    BundleElement(StringAttr name, bool isFlip, ElementType type)
        : name(name), isFlip(isFlip), type(type) {}

    bool operator==(const BundleElement &rhs) const {
      return name == rhs.name && isFlip == rhs.isFlip && type == rhs.type;
    }
    bool operator!=(const BundleElement &rhs) const {
      return !operator==(rhs);
    }

    friend llvm::hash_code hash_value(const BundleElement &arg) {
      return llvm::hash_combine(arg.name, arg.isFlip, arg.type);
    }
  };

  ArrayRef<BundleElement> getElements() const;

  size_t getNumElements() const { return getElements().size(); }

  /// Look up an element's index by name.  This returns None on failure.
  std::optional<unsigned> getElementIndex(StringAttr name);
  std::optional<unsigned> getElementIndex(StringRef name);

  /// Look up an element's name by index. This asserts if index is invalid.
  StringAttr getElementNameAttr(size_t index);
  StringRef getElementName(size_t index);

  /// Look up an element by name.  This returns None on failure.
  std::optional<BundleElement> getElement(StringAttr name);
  std::optional<BundleElement> getElement(StringRef name);

  /// Look up an element by index.  This asserts if index is invalid.
  BundleElement getElement(size_t index);

  /// Look up an element type by name.
  ElementType getElementType(StringAttr name);
  ElementType getElementType(StringRef name);

  /// Look up an element type by index.
  ElementType getElementType(size_t index) const;

  /// Return the recursive properties of the type.
  RecursiveTypeProperties getRecursiveTypeProperties() const;

  using iterator = ArrayRef<BundleElement>::iterator;
  iterator begin() const { return getElements().begin(); }
  iterator end() const { return getElements().end(); }

  /// Const support.
  bool isConst() const;
  ElementType getElementTypePreservingConst(size_t index);

  /// Return a 'const' or non-'const' version of this type.
  BundleType getConstType(bool isConst) const;


  /// Return this type with any flip types recursively removed from itself.
  FIRRTLBaseType getPassiveType();

  /// Return this type with a 'const' modifiers dropped
  BundleType getAllConstDroppedType();

  /// Return this type with any type alias types recursively removed from itself.
  FIRRTLBaseType getAnonymousType();
  static constexpr ::llvm::StringLiteral name = "firrtl.bundle";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static BundleType get(::mlir::MLIRContext *context, ArrayRef<BundleElement> elements, bool isConst = false);
  static BundleType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ArrayRef<BundleElement> elements, bool isConst = false);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<BundleElement> elements, bool isConst);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<BundleElement> elements, bool isConst);
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
};
class OpenBundleType : public ::mlir::Type::TypeBase<OpenBundleType, ::circt::firrtl::FIRRTLType, detail::OpenBundleTypeStorage, circt::hw::FieldIDTypeInterface::Trait> {
public:
  using Base::Base;
  using ElementType = ::circt::firrtl::FIRRTLType;

  /// Each element of a bundle, which is a name and type.
  struct BundleElement {
    StringAttr name;
    bool isFlip;
    ElementType type;

    BundleElement(StringAttr name, bool isFlip, ElementType type)
        : name(name), isFlip(isFlip), type(type) {}

    bool operator==(const BundleElement &rhs) const {
      return name == rhs.name && isFlip == rhs.isFlip && type == rhs.type;
    }
    bool operator!=(const BundleElement &rhs) const {
      return !operator==(rhs);
    }

    friend llvm::hash_code hash_value(const BundleElement &arg) {
      return llvm::hash_combine(arg.name, arg.isFlip, arg.type);
    }
  };

  ArrayRef<BundleElement> getElements() const;

  size_t getNumElements() const { return getElements().size(); }

  /// Look up an element's index by name.  This returns None on failure.
  std::optional<unsigned> getElementIndex(StringAttr name);
  std::optional<unsigned> getElementIndex(StringRef name);

  /// Look up an element's name by index. This asserts if index is invalid.
  StringAttr getElementNameAttr(size_t index);
  StringRef getElementName(size_t index);

  /// Look up an element by name.  This returns None on failure.
  std::optional<BundleElement> getElement(StringAttr name);
  std::optional<BundleElement> getElement(StringRef name);

  /// Look up an element by index.  This asserts if index is invalid.
  BundleElement getElement(size_t index);

  /// Look up an element type by name.
  ElementType getElementType(StringAttr name);
  ElementType getElementType(StringRef name);

  /// Look up an element type by index.
  ElementType getElementType(size_t index) const;

  /// Return the recursive properties of the type.
  RecursiveTypeProperties getRecursiveTypeProperties() const;

  using iterator = ArrayRef<BundleElement>::iterator;
  iterator begin() const { return getElements().begin(); }
  iterator end() const { return getElements().end(); }

  /// Const support.
  bool isConst() const;
  ElementType getElementTypePreservingConst(size_t index);

  /// Return a 'const' or non-'const' version of this type.
  OpenBundleType getConstType(bool isConst) const;

  static constexpr ::llvm::StringLiteral name = "firrtl.openbundle";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static OpenBundleType get(::mlir::MLIRContext *context, ArrayRef<BundleElement> elements, bool isConst = false);
  static OpenBundleType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ArrayRef<BundleElement> elements, bool isConst = false);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<BundleElement> elements, bool isConst);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<BundleElement> elements, bool isConst);
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
};
class FEnumType : public ::mlir::Type::TypeBase<FEnumType, ::circt::firrtl::FIRRTLBaseType, detail::FEnumTypeStorage> {
public:
  using Base::Base;
  /// Each element of an enum, which is a name and type.
  struct EnumElement {
    StringAttr name;
    IntegerAttr value;
    FIRRTLBaseType type;

    EnumElement(StringAttr name, IntegerAttr value, FIRRTLBaseType type)
        : name(name), value(value), type(type) {}

    bool operator==(const EnumElement &rhs) const {
      return name == rhs.name && value == rhs.value && type == rhs.type;
    }
    bool operator!=(const EnumElement &rhs) const {
      return !operator==(rhs);
    }
    bool operator<(const EnumElement &rhs) const {
      return value.getValue().ult(rhs.value.getValue());
    }

    friend llvm::hash_code hash_value(const FEnumType::EnumElement &arg) {
      return mlir::hash_value(arg.name) ^ mlir::hash_value(arg.value) ^
             mlir::hash_value(arg.type);
    }
  };

  ArrayRef<EnumElement> getElements() const;

  size_t getNumElements() const { return getElements().size(); }

  FEnumType getConstType(bool isConst) const;

  /// Return this type with a 'const' modifiers dropped
  FEnumType getAllConstDroppedType();

  /// Return this type with any type alias types recursively removed from itself.
  FIRRTLBaseType getAnonymousType();

  /// Get the width of this
  size_t getBitWidth();

  /// Get the width of the data. Equal to the width of the largest element.
  size_t getDataWidth();

  /// Get the width of the the tag field.
  size_t getTagWidth();

  /// Look up an element's index by name.  This returns None on failure.
  std::optional<unsigned> getElementIndex(StringAttr name);
  std::optional<unsigned> getElementIndex(StringRef name);

  /// Look up an element's name by index. This asserts if index is invalid.
  StringAttr getElementNameAttr(size_t index);
  StringRef getElementName(size_t index);

  // Look up an element's value by index. This asserts if index is invalid.
  IntegerAttr getElementValueAttr(size_t index);
  APInt getElementValue(size_t index);

  // Look up an element's type by index. This asserts if index is invalid.
  FIRRTLBaseType getElementType(size_t index);

  /// Look up an element by name.  This returns None on failure.
  std::optional<EnumElement> getElement(StringAttr name);
  std::optional<EnumElement> getElement(StringRef name);

  /// Look up an element by index.  This asserts if index is invalid.
  EnumElement getElement(size_t index);

  /// Look up an element type by name.
  FIRRTLBaseType getElementType(StringAttr name);
  FIRRTLBaseType getElementType(StringRef name);

  /// Look up an element type by index.
  FIRRTLBaseType getElementType(size_t index) const;
  FIRRTLBaseType getElementTypePreservingConst(size_t index);

  /// Return the recursive properties of the type.
  RecursiveTypeProperties getRecursiveTypeProperties() const;

  using iterator = ArrayRef<EnumElement>::iterator;
  iterator begin() const { return getElements().begin(); }
  iterator end() const { return getElements().end(); }
  static constexpr ::llvm::StringLiteral name = "firrtl.enum";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static FEnumType get(::mlir::MLIRContext *context, ArrayRef<EnumElement> elements, bool isConst = false);
  static FEnumType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ArrayRef<EnumElement> elements, bool isConst = false);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<EnumElement> elements, bool isConst);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ArrayRef<EnumElement> elements, bool isConst);
};
namespace detail {

struct RefTypeStorage;

} // namespace detail
class RefType : public ::mlir::Type::TypeBase<RefType, ::circt::firrtl::FIRRTLType, detail::RefTypeStorage> {
public:
  using Base::Base;
  /// Return the recursive properties of the type.
  RecursiveTypeProperties getRecursiveTypeProperties() const;

  RefType removeLayer() const {
    if (getLayer() == nullptr)
      return *this;
    return get(getType(), getForceable());
  }
  static constexpr ::llvm::StringLiteral name = "firrtl.ref";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static RefType get(::circt::firrtl::FIRRTLBaseType type, bool forceable = false, ::mlir::SymbolRefAttr layer = {});
  static RefType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLBaseType type, bool forceable = false, ::mlir::SymbolRefAttr layer = {});
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLBaseType type, bool forceable, ::mlir::SymbolRefAttr layer);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLBaseType type, bool forceable, ::mlir::SymbolRefAttr layer);
  ::circt::firrtl::FIRRTLBaseType getType() const;
  bool getForceable() const;
  ::mlir::SymbolRefAttr getLayer() const;
};
namespace detail {

struct LHSTypeStorage;

} // namespace detail
class LHSType : public ::mlir::Type::TypeBase<LHSType, ::circt::firrtl::FIRRTLType, detail::LHSTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.lhs";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  using Base::getChecked;
  static LHSType get(::mlir::MLIRContext *context, FIRRTLBaseType type);
  static LHSType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, FIRRTLBaseType type);
  static LHSType get(::circt::firrtl::FIRRTLBaseType type);
  static LHSType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::circt::firrtl::FIRRTLBaseType type);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, FIRRTLBaseType type);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, FIRRTLBaseType type);
  FIRRTLBaseType getType() const;
};
class BaseTypeAliasType : public ::mlir::Type::TypeBase<BaseTypeAliasType, ::circt::firrtl::FIRRTLBaseType, detail::BaseTypeAliasStorage, circt::hw::FieldIDTypeInterface::Trait> {
public:
  using Base::Base;
  // FIRRTLBaseType utils.
  FIRRTLBaseType getAnonymousType();
  FIRRTLBaseType getPassiveType();
  FIRRTLBaseType getConstType(bool isConst) const;
  FIRRTLBaseType getAllConstDroppedType();

  /// Return the recursive properties of the type.
  RecursiveTypeProperties getRecursiveTypeProperties() const;

  // If a given `newInnerType` is identical to innerType, return `*this`
  // because we can reuse the type alias. Otherwise return `newInnerType`.
  FIRRTLBaseType getModifiedType(FIRRTLBaseType newInnerType) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.basetypealias";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static BaseTypeAliasType get(::mlir::StringAttr name, ::circt::firrtl::FIRRTLBaseType innerType);
  StringAttr getName() const;
  ::circt::firrtl::FIRRTLBaseType getInnerType() const;
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
};
class ClassType : public ::mlir::Type::TypeBase<ClassType, ::circt::firrtl::FIRRTLType, detail::ClassTypeStorage, circt::hw::FieldIDTypeInterface::Trait> {
public:
  using Base::Base;
  /// Helper to parse this type as a module interface.
  static ParseResult parseInterface(
    AsmParser &parser, ClassType &result);

  StringRef getName() const;
  FlatSymbolRefAttr getNameAttr() const;

  ArrayRef<ClassElement> getElements() const;
  size_t getNumElements() const { return getElements().size(); }
  const ClassElement &getElement(IntegerAttr index) const;
  const ClassElement &getElement(size_t index) const;
  std::optional<uint64_t> getElementIndex(StringRef fieldName) const;

  /// Helper to print this type as a module interface.
  /// Example:
  /// ```
  /// @MyClass(in %port: !firrtl.uint<8>, out o: !firrtl.uint<8>)
  /// ```
  void printInterface(AsmPrinter &p) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.propClass";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static ClassType get(::mlir::MLIRContext *context, FlatSymbolRefAttr name, ::llvm::ArrayRef<ClassElement> elements);
  static ClassType get(FlatSymbolRefAttr name, ArrayRef<ClassElement> elements);
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
};
class AnyRefType : public ::mlir::Type::TypeBase<AnyRefType, ::circt::firrtl::FIRRTLType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.propRef";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
};
class StringType : public ::mlir::Type::TypeBase<StringType, ::circt::firrtl::FIRRTLType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.propString";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
};
class FIntegerType : public ::mlir::Type::TypeBase<FIntegerType, ::circt::firrtl::FIRRTLType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.propInt";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
};
namespace detail {

struct ListTypeStorage;

} // namespace detail
class ListType : public ::mlir::Type::TypeBase<ListType, ::circt::firrtl::FIRRTLType, detail::ListTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.propList";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static ListType get(::mlir::MLIRContext *context, circt::firrtl::PropertyType elementType);
  circt::firrtl::PropertyType getElementType() const;
};
class PathType : public ::mlir::Type::TypeBase<PathType, ::circt::firrtl::FIRRTLType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.propPath";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
};
class BoolType : public ::mlir::Type::TypeBase<BoolType, ::circt::firrtl::FIRRTLType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.propBool";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
};
class DoubleType : public ::mlir::Type::TypeBase<DoubleType, ::circt::firrtl::FIRRTLType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.propDouble";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
};
class FStringType : public ::mlir::Type::TypeBase<FStringType, ::circt::firrtl::FIRRTLType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "firrtl.fstring";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
};
namespace detail {

struct DomainTypeStorage;

} // namespace detail
class DomainType : public ::mlir::Type::TypeBase<DomainType, ::circt::firrtl::FIRRTLType, detail::DomainTypeStorage, circt::hw::FieldIDTypeInterface::Trait> {
public:
  using Base::Base;
  /// Helper to parse this type as a domain interface.
  static ParseResult parseInterface(
    AsmParser &parser, DomainType &result);

  /// Construct a DomainType from a DomainOp definition.
  static DomainType getFromDomainOp(DomainOp domainOp);

  size_t getNumFields() const { return getFields().size(); }
  DomainFieldAttr getField(size_t index) const;
  std::optional<uint64_t> getFieldIndex(StringRef fieldName) const;

  /// Verify that this domain type matches the domain definition.
  LogicalResult verifySymbolUses(Operation *op,
                                 SymbolTableCollection &symbolTable) const;
  static constexpr ::llvm::StringLiteral name = "firrtl.domain";
  static constexpr ::llvm::StringLiteral dialectName = "firrtl";
  static DomainType get(::mlir::MLIRContext *context, FlatSymbolRefAttr name, ArrayAttr fields);
  static DomainType get(FlatSymbolRefAttr name, ArrayAttr fields);
  FlatSymbolRefAttr getName() const;
  ArrayAttr getFields() const;
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
};

} // namespace circt::firrtl
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::SIntType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::UIntType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::ClockType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::ResetType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::AsyncResetType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::AnalogType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::FVectorType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::OpenVectorType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::BundleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::OpenBundleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::FEnumType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::RefType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::LHSType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::BaseTypeAliasType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::ClassType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::AnyRefType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::StringType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::FIntegerType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::ListType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::PathType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::BoolType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::DoubleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::FStringType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::firrtl::DomainType)

#endif // GET_TYPEDEF_CLASSES

