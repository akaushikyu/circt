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
namespace circt::hw {

/// parameterized-width integer
/// Parameterized integer types are equivalent to the MLIR standard integer
/// type: it is signless, and may be any width integer.  This type represents
/// the case when the width is a parameter in the HW dialect sense.
class IntType;
/// fixed-sized array
/// Fixed sized HW arrays are roughly similar to C arrays. On the wire (vs.
/// in a memory), arrays are always packed. Memory layout is not defined as
/// it does not need to be since in silicon there is not implicit memory
/// sharing.
class ArrayType;
/// SystemVerilog 'unpacked' fixed-sized array
/// Unpacked arrays are a more flexible array representation than packed arrays,
/// and are typically used to model memories.  See SystemVerilog Spec 7.4.2.
class UnpackedArrayType;
/// inout type
/// InOut type is used for model operations and values that have "connection"
/// semantics, instead of typical dataflow behavior.  This is used for wires
/// and inout ports in Verilog.
class InOutType;
/// HW struct type
/// Represents a structure of name, value pairs.
/// ```mlir
/// !hw.struct<fieldName1: Type1, fieldName2: Type2>
/// ```
class StructType;
/// HW Enum type
/// Represents an enumeration of values. Enums are interpreted as integers with
/// a synthesis-defined encoding.
/// ```mlir
/// !hw.enum<field1, field2>
/// ```
class EnumType;
/// An untagged union of types
class UnionType;
/// An symbolic reference to a type declaration
/// A TypeAlias is parameterized by a SymbolRefAttr, which points to a
/// TypedeclOp. The root reference should refer to a TypeScope within the same
/// outer ModuleOp, and the leaf reference should refer to a type within that
/// TypeScope. A TypeAlias is further parameterized by the inner type, which is
/// needed to be known at the time the type is parsed.
/// 
/// Upon construction, a TypeAlias stores the symbol reference and type, and
/// canonicalizes the type to resolve any nested type aliases. The canonical
/// type is also cached to avoid recomputing it when needed.
class TypeAliasType;
/// Module Type
/// Module types have ports.
class ModuleType;
/// String type
/// Defines a string type for the hw-centric dialects
class StringType;
namespace detail {

struct IntTypeStorage;

} // namespace detail
class IntType : public ::mlir::Type::TypeBase<IntType, ::mlir::Type, detail::IntTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "hw.int";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static Type get(::mlir::TypedAttr width);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"int"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::TypedAttr getWidth() const;
};
namespace detail {

struct ArrayTypeStorage;

} // namespace detail
class ArrayType : public ::mlir::Type::TypeBase<ArrayType, ::mlir::Type, detail::ArrayTypeStorage, ::mlir::DestructurableTypeInterface::Trait, circt::hw::FieldIDTypeInterface::Trait, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  size_t getNumElements() const;
  static constexpr ::llvm::StringLiteral name = "hw.array";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  using Base::getChecked;
  static ArrayType get(::mlir::MLIRContext *context, ::mlir::Type elementType, ::mlir::Attribute sizeAttr);
  static ArrayType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type elementType, ::mlir::Attribute sizeAttr);
  static ArrayType get(Type elementType, size_t size);
  static ArrayType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, size_t size);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, ::mlir::Attribute sizeAttr);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, ::mlir::Attribute sizeAttr);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"array"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
  ::mlir::Attribute getSizeAttr() const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
  std::optional<int64_t> getBitWidth() const;
};
namespace detail {

struct UnpackedArrayTypeStorage;

} // namespace detail
class UnpackedArrayType : public ::mlir::Type::TypeBase<UnpackedArrayType, ::mlir::Type, detail::UnpackedArrayTypeStorage, circt::hw::FieldIDTypeInterface::Trait, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  size_t getNumElements() const;
  static constexpr ::llvm::StringLiteral name = "hw.uarray";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  using Base::getChecked;
  static UnpackedArrayType get(::mlir::MLIRContext *context, ::mlir::Type elementType, ::mlir::Attribute sizeAttr);
  static UnpackedArrayType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type elementType, ::mlir::Attribute sizeAttr);
  static UnpackedArrayType get(Type elementType, size_t size);
  static UnpackedArrayType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, size_t size);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, ::mlir::Attribute sizeAttr);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, ::mlir::Attribute sizeAttr);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"uarray"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
  ::mlir::Attribute getSizeAttr() const;
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
  std::optional<int64_t> getBitWidth() const;
};
namespace detail {

struct InOutTypeStorage;

} // namespace detail
class InOutType : public ::mlir::Type::TypeBase<InOutType, ::mlir::Type, detail::InOutTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "hw.inout";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  using Base::getChecked;
  static InOutType get(::mlir::MLIRContext *context, ::mlir::Type elementType);
  static InOutType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type elementType);
  static InOutType get(Type elementType);
  static InOutType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"inout"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
};
namespace detail {

struct StructTypeStorage;

} // namespace detail
class StructType : public ::mlir::Type::TypeBase<StructType, ::mlir::Type, detail::StructTypeStorage, ::mlir::DestructurableTypeInterface::Trait, circt::hw::FieldIDTypeInterface::Trait, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  using FieldInfo = ::circt::hw::detail::FieldInfo;
  mlir::Type getFieldType(mlir::StringRef fieldName);
  void getInnerTypes(mlir::SmallVectorImpl<mlir::Type>&);
  std::optional<uint32_t> getFieldIndex(mlir::StringRef fieldName);
  std::optional<uint32_t> getFieldIndex(mlir::StringAttr fieldName);
  static constexpr ::llvm::StringLiteral name = "hw.struct";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  using Base::getChecked;
  static StructType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements);
  static StructType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> elements);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"struct"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<::circt::hw::StructType::FieldInfo> getElements() const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
  uint64_t getMaxFieldID() const;
  std::pair<::mlir::Type, uint64_t> getSubTypeByFieldID(uint64_t fieldID) const;
  std::pair<uint64_t, bool> projectToChildFieldID(uint64_t fieldID, uint64_t index) const;
  uint64_t getIndexForFieldID(uint64_t fieldID) const;
  uint64_t getFieldID(uint64_t index) const;
  std::pair<uint64_t, uint64_t> getIndexAndSubfieldID(uint64_t fieldID) const;
  std::optional<int64_t> getBitWidth() const;
};
namespace detail {

struct EnumTypeStorage;

} // namespace detail
class EnumType : public ::mlir::Type::TypeBase<EnumType, ::mlir::Type, detail::EnumTypeStorage, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  /// Returns true if the requested field is part of this enum
  bool contains(mlir::StringRef field);

  /// Returns the index of the requested field, or a nullopt if the field is
  // not part of this enum.
  std::optional<size_t> indexOf(mlir::StringRef field);
  static constexpr ::llvm::StringLiteral name = "hw.enum";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static EnumType get(::mlir::MLIRContext *context, mlir::ArrayAttr fields);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"enum"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::ArrayAttr getFields() const;
  std::optional<int64_t> getBitWidth() const;
};
namespace detail {

struct UnionTypeStorage;

} // namespace detail
class UnionType : public ::mlir::Type::TypeBase<UnionType, ::mlir::Type, detail::UnionTypeStorage, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  using FieldInfo = ::circt::hw::detail::OffsetFieldInfo;

  FieldInfo getFieldInfo(::mlir::StringRef fieldName);

  ::mlir::Type getFieldType(::mlir::StringRef fieldName);
  std::optional<uint32_t> getFieldIndex(mlir::StringRef fieldName);
  std::optional<uint32_t> getFieldIndex(mlir::StringAttr fieldName);
  static constexpr ::llvm::StringLiteral name = "hw.union";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  using Base::getChecked;
  static UnionType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements);
  static UnionType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> elements);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"union"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<::circt::hw::UnionType::FieldInfo> getElements() const;
  std::optional<int64_t> getBitWidth() const;
};
namespace detail {

struct TypeAliasTypeStorage;

} // namespace detail
class TypeAliasType : public ::mlir::Type::TypeBase<TypeAliasType, ::mlir::Type, detail::TypeAliasTypeStorage, circt::hw::BitWidthTypeInterface::Trait> {
public:
  using Base::Base;
  /// Return the Typedecl referenced by this TypeAlias, given the module to
  /// look in.  This returns null when the IR is malformed.
  TypedeclOp getTypeDecl(const HWSymbolCache &cache);
  static constexpr ::llvm::StringLiteral name = "hw.typealias";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static TypeAliasType get(::mlir::MLIRContext *context, mlir::SymbolRefAttr ref, mlir::Type innerType, mlir::Type canonicalType);
  static TypeAliasType get(mlir::SymbolRefAttr ref, mlir::Type innerType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"typealias"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::SymbolRefAttr getRef() const;
  mlir::Type getInnerType() const;
  mlir::Type getCanonicalType() const;
  std::optional<int64_t> getBitWidth() const;
};
class ModuleType : public ::mlir::Type::TypeBase<ModuleType, ::mlir::Type, detail::ModuleTypeStorage> {
public:
  using Base::Base;
  // Many of these are transitional and will be removed when modules and instances
  // have moved over to this type.
  // *Input* are input indexed
  // *Output* are output indexed
  // *Port* are absolutely indexed
  size_t getNumPorts();
  size_t getNumInputs();
  size_t getNumOutputs();
  SmallVector<Type> getPortTypes();
  SmallVector<Type> getInputTypes();
  SmallVector<Type> getOutputTypes();
  Type getPortType(size_t);
  Type getInputType(size_t);
  Type getOutputType(size_t);
  SmallVector<Attribute> getPortNames();
  SmallVector<Attribute> getInputNames();
  SmallVector<Attribute> getOutputNames();
  StringAttr getPortNameAttr(size_t);
  StringRef getPortName(size_t);
  StringAttr getInputNameAttr(size_t);
  StringRef getInputName(size_t);
  StringAttr getOutputNameAttr(size_t);
  StringRef getOutputName(size_t);
  FunctionType getFuncType();
  bool isOutput(size_t);
  size_t getInputIdForPortId(size_t);
  size_t getOutputIdForPortId(size_t);
  size_t getPortIdForInputId(size_t);
  size_t getPortIdForOutputId(size_t);
  FailureOr<ModuleType> resolveParametricTypes(
    ArrayAttr parameters, LocationAttr loc, bool emitErrors);
  static constexpr ::llvm::StringLiteral name = "hw.modty";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  using Base::getChecked;
  static ModuleType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::ModulePort> ports);
  static ModuleType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::hw::ModulePort> ports);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::ModulePort> ports);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::hw::ModulePort> ports);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"modty"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<::circt::hw::ModulePort> getPorts() const;
};
class StringType : public ::mlir::Type::TypeBase<StringType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "hw.string";
  static constexpr ::llvm::StringLiteral dialectName = "hw";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"string"};
  }

};

} // namespace circt::hw
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::IntType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::UnpackedArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::InOutType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::StructType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::EnumType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::UnionType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::TypeAliasType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::ModuleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::hw::StringType)

#endif // GET_TYPEDEF_CLASSES

