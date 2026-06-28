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
namespace circt::rtg {

/// handle to a sequence or sequence family
/// An SSA value of this type refers to a sequence if the list of element types
/// is empty or a sequence family if there are elements left to be substituted.
class SequenceType;
/// handle to a fully randomized sequence
/// Sequences can contain operations to randomize their content in various ways.
/// A sequence of this type is guaranteed to not have any such operations
/// anymore (transitively).
class RandomizedSequenceType;
/// a set of values
/// This type represents a standard set datastructure. It does not make any
/// assumptions about the underlying implementation. Thus a hash set, tree set,
/// etc. can be used in a backend.
class SetType;
/// a bag of values
/// This type represents a standard bag/multiset datastructure. It does not make
/// any assumptions about the underlying implementation.
class BagType;
/// a dictionary
/// This type is a dictionary with a static set of entries. This datatype does
/// not make any assumptions about how the values are stored (could be a struct,
/// a map, etc.). Furthermore, two values of this type should be considered
/// equivalent if they have the same set of entry names and types and the values
/// match for each entry, independent of the order.
class DictType;
/// an array type with dynamic size
/// Represents an array type with dynamic size. The array contains elements of
/// the specified type only.
class ArrayType;
/// a map from keys to values
/// This type represents a standard map/dictionary datastructure. It does not
/// make any assumptions about the underlying implementation. Thus a hash map,
/// tree map, etc. can be used in a backend. It does not guarentee deterministic
/// iteration.
class MapType;
/// a tuple of zero or more fields
/// This type represents a tuple of zero or more fields. The fields can be
/// of any type. The builtin tuple type is not used because it does not allow
/// zero fields.
class TupleType;
/// a string type
class StringType;
/// a reference to a label
/// This type represents a label. Payload dialects can add operations to cast
/// from this type to an immediate type they can use as an operand to an
/// instruction or allow an operand of this type directly.
class LabelType;
/// an ISA immediate
/// This type represents immediates of arbitrary but fixed bit-width.
/// The RTG dialect provides this type to avoid duplication in ISA payload
/// dialects.
class ImmediateType;
/// handle to a memory
/// This type is used to represent memory resources that are allocated from
/// memory blocks and can be accessed and manipulated by payload dialect
/// operations.
class MemoryType;
/// handle to a memory block
/// A memory block is representing a continuous region in a memory map with a
/// fixed size and base address. It can refer to actual memory or a memory
/// mapped device.
/// 
/// It is assumed that there is only a single address space.
class MemoryBlockType;
namespace detail {

struct SequenceTypeStorage;

} // namespace detail
class SequenceType : public ::mlir::Type::TypeBase<SequenceType, ::mlir::Type, detail::SequenceTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.sequence";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static SequenceType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<mlir::Type> elementTypes);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sequence"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<mlir::Type> getElementTypes() const;
};
class RandomizedSequenceType : public ::mlir::Type::TypeBase<RandomizedSequenceType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.randomized_sequence";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"randomized_sequence"};
  }

};
namespace detail {

struct SetTypeStorage;

} // namespace detail
class SetType : public ::mlir::Type::TypeBase<SetType, ::mlir::Type, detail::SetTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.set";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static SetType get(::mlir::MLIRContext *context, ::mlir::Type elementType);
  static SetType get(::mlir::Type elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"set"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
};
namespace detail {

struct BagTypeStorage;

} // namespace detail
class BagType : public ::mlir::Type::TypeBase<BagType, ::mlir::Type, detail::BagTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.bag";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static BagType get(::mlir::MLIRContext *context, ::mlir::Type elementType);
  static BagType get(::mlir::Type elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"bag"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
};
namespace detail {

struct DictTypeStorage;

} // namespace detail
class DictType : public ::mlir::Type::TypeBase<DictType, ::mlir::Type, detail::DictTypeStorage> {
public:
  using Base::Base;
  /// Checks if the types of the dictionary entries match the ones in the
  /// given type range. The dictionary entries are sorted by ascending names.
  bool entryTypesMatch(mlir::TypeRange types) const;
  static constexpr ::llvm::StringLiteral name = "rtg.dict";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  using Base::getChecked;
  static DictType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::rtg::DictEntry> entries);
  static DictType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<::circt::rtg::DictEntry> entries);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::rtg::DictEntry> entries);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<::circt::rtg::DictEntry> entries);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"dict"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<::circt::rtg::DictEntry> getEntries() const;
};
namespace detail {

struct ArrayTypeStorage;

} // namespace detail
class ArrayType : public ::mlir::Type::TypeBase<ArrayType, ::mlir::Type, detail::ArrayTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.array";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static ArrayType get(::mlir::MLIRContext *context, ::mlir::Type elementType);
  static ArrayType get(mlir::Type elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"array"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
};
namespace detail {

struct MapTypeStorage;

} // namespace detail
class MapType : public ::mlir::Type::TypeBase<MapType, ::mlir::Type, detail::MapTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.map";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static MapType get(::mlir::MLIRContext *context, ::mlir::Type keyType, ::mlir::Type valueType);
  static MapType get(::mlir::Type keyType, ::mlir::Type valueType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"map"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getKeyType() const;
  ::mlir::Type getValueType() const;
};
namespace detail {

struct TupleTypeStorage;

} // namespace detail
class TupleType : public ::mlir::Type::TypeBase<TupleType, ::mlir::Type, detail::TupleTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.tuple";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static TupleType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<::mlir::Type> fieldTypes);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"tuple"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<::mlir::Type> getFieldTypes() const;
};
class StringType : public ::mlir::Type::TypeBase<StringType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.string";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"string"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
};
class LabelType : public ::mlir::Type::TypeBase<LabelType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.isa.label";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"isa.label"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
};
namespace detail {

struct ImmediateTypeStorage;

} // namespace detail
class ImmediateType : public ::mlir::Type::TypeBase<ImmediateType, ::mlir::Type, detail::ImmediateTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.isa.immediate";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static ImmediateType get(::mlir::MLIRContext *context, uint32_t width);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"isa.immediate"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  uint32_t getWidth() const;
};
namespace detail {

struct MemoryTypeStorage;

} // namespace detail
class MemoryType : public ::mlir::Type::TypeBase<MemoryType, ::mlir::Type, detail::MemoryTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.isa.memory";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static MemoryType get(::mlir::MLIRContext *context, uint32_t addressWidth);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"isa.memory"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  uint32_t getAddressWidth() const;
};
namespace detail {

struct MemoryBlockTypeStorage;

} // namespace detail
class MemoryBlockType : public ::mlir::Type::TypeBase<MemoryBlockType, ::mlir::Type, detail::MemoryBlockTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "rtg.isa.memory_block";
  static constexpr ::llvm::StringLiteral dialectName = "rtg";
  static MemoryBlockType get(::mlir::MLIRContext *context, uint32_t addressWidth);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"isa.memory_block"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  uint32_t getAddressWidth() const;
};

} // namespace circt::rtg
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::SequenceType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::RandomizedSequenceType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::SetType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::BagType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::DictType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::ArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::MapType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::TupleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::StringType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::LabelType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::ImmediateType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::MemoryType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::rtg::MemoryBlockType)

#endif // GET_TYPEDEF_CLASSES

