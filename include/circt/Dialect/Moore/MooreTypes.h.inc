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
namespace circt::moore {

/// the SystemVerilog `void` type
class VoidType;
/// the SystemVerilog `string` type
class StringType;
/// the SystemVerilog `chandle` type
class ChandleType;
/// the SystemVerilog `event` type
class EventType;
/// A type that represents null literals for chandles, classhandles,
///   and virtual interfaces
class NullType;
/// Class object handle type, pointing to an object on the heap.
/// The `!moore.class<@C>` type represents a handle of a class instance of class `@C` living on the program's heap.
class ClassHandleType;
/// the SystemVerilog `time` and `realtime` type
/// The `!moore.time` type represents a time value. Internally, the value is
/// represented as femtoseconds in `i64`.
/// 
/// Time values are a problematic part of the SystemVerilog language, since they
/// are multiplied by a scaling factor given by the current scope's `timeunit`
/// and then mapped to an 64 bit four-valued integer for `time`, or a real for
/// `realtime`. This means that a time value flowing from one module with one
/// timeunit to another module with a different timeunit will read as two
/// distinct delay values in the two modules.
/// 
/// To work around these issues, the Moore dialect maps all time values to
/// femtoseconds and represents them as an integer value. This allows us to have
/// time values exchanged between modules correctly, while locally casting from
/// and to `integer` and `real` with the correct local scaling factor.
class TimeType;
/// a simple bit vector type
/// The `!moore.iN` and `!moore.lN` types represent a two-valued or four-valued
/// simple bit vector of width `N`. The predefined SystemVerilog integer types
/// map to this as follows:
/// 
/// | Verilog    | Moore Dialect |
/// |------------|---------------|
/// | `bit`      | `!moore.i1`   |
/// | `logic`    | `!moore.l1`   |
/// | `reg`      | `!moore.l1`   |
/// | `byte`     | `!moore.i8`   |
/// | `shortint` | `!moore.i16`  |
/// | `int`      | `!moore.i32`  |
/// | `integer`  | `!moore.l32`  |
/// | `longint`  | `!moore.i64`  |
/// | `time`     | `!moore.time` |
class IntType;
/// a SystemVerilog real type
/// This type represents the SystemVerilog real type. We coalesce the
/// `f32`, `f64`, and `realtime` types in the SystemVerilog standard to
/// this common `!moore.real` type. The standard specifies these types to be of
/// at least 32, 64, and 64 bits, respectively.
/// 
/// | Verilog     | Moore Dialect      |
/// |-------------|--------------------|
/// | `shortreal` | `!moore.f32`       |
/// | `real`      | `!moore.f64`       |
/// | `realtime`  | `!moore.time`      |
class RealType;
/// a packed array type
/// A packed array with a fixed number of elements. This type represents packed
/// range dimensions (`[a:b]`) in SystemVerilog.
/// 
/// | Verilog   | Moore Dialect         |
/// |-----------|-----------------------|
/// | `T [3:0]` | `!moore.array<4 x T>` |
/// | `T [2:4]` | `!moore.array<3 x T>` |
class ArrayType;
/// an unpacked array type
/// An unpacked array with a fixed number of elements. This type represents
/// unpacked range dimensions (`[a:b]`) and unpacked array dimensions (`[a]`) in
/// SystemVerilog.
/// 
/// | Verilog       | Moore Dialect          |
/// |---------------|------------------------|
/// | `T foo [3:0]` | `!moore.uarray<4 x T>` |
/// | `T foo [2:4]` | `!moore.uarray<3 x T>` |
/// | `T foo [2]`   | `!moore.uarray<2 x T>` |
class UnpackedArrayType;
/// an open packed array type
/// A packed array with an unspecified number of elements. This type represents
/// unsized/open packed arrays (`[]`) in SystemVerilog.
/// 
/// | Verilog | Moore Dialect          |
/// |---------|------------------------|
/// | `T []`  | `!moore.open_array<T>` |
class OpenArrayType;
/// an open unpacked array type
/// An unpacked array with an unspecified number of elements. This type
/// represents unsized/open unpacked arrays (`[]`) in SystemVerilog.
/// 
/// | Verilog    | Moore Dialect           |
/// |------------|-------------------------|
/// | `T foo []` | `!moore.open_uarray<T>` |
class OpenUnpackedArrayType;
/// an associative array type
/// An associative array. This type represents associative arrays (`[T]`) in
/// SystemVerilog.
/// 
/// | Verilog     | Moore Dialect              |
/// |-------------|----------------------------|
/// | `T foo [K]` | `!moore.assoc_array<T, K>` |
class AssocArrayType;
/// a queue type
/// A queue with an optional upper bound on the number of elements that it can
/// hold. This type represents queues (`[$]` and `[$:a]`) in SystemVerilog. A
/// `bound` of 0 indicates an unbounded queue.
/// 
/// | Verilog        | Moore Dialect         |
/// |----------------|-----------------------|
/// | `T foo [$]`    | `!moore.queue<T>`     |
/// | `T foo [$:42]` | `!moore.queue<T, 42>` |
class QueueType;
/// a packed struct type
/// A packed struct. All members are guaranteed to be packed as well.
class StructType;
/// an unpacked struct type
/// An unpacked struct.
class UnpackedStructType;
/// a packed union type
/// A packed union. All members are guaranteed to be packed as well.
class UnionType;
/// an unpacked union type
/// An unpacked union.
class UnpackedUnionType;
/// A wrapper is used to wrap any SystemVerilog type. It's aimed to work for
/// 'moore.variable', 'moore.blocking_assign', and 'moore.read', which are
/// related to memory, like alloca/write/read.
class RefType;
/// a format string type
/// An interpolated string produced by one of the string formatting operations.
/// It is used to parse format strings present in Verilog source text and
/// represent them as a sequence of IR operations that specify the formatting of
/// individual arguments.
class FormatStringType;
class VoidType : public ::mlir::Type::TypeBase<VoidType, moore::PackedType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.void";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"void"};
  }

};
class StringType : public ::mlir::Type::TypeBase<StringType, moore::UnpackedType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.string";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"string"};
  }

};
class ChandleType : public ::mlir::Type::TypeBase<ChandleType, moore::UnpackedType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.chandle";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"chandle"};
  }

};
class EventType : public ::mlir::Type::TypeBase<EventType, moore::UnpackedType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.event";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"event"};
  }

};
class NullType : public ::mlir::Type::TypeBase<NullType, moore::UnpackedType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.null";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"null"};
  }

};
namespace detail {

struct ClassHandleTypeStorage;

} // namespace detail
class ClassHandleType : public ::mlir::Type::TypeBase<ClassHandleType, moore::UnpackedType, detail::ClassHandleTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.class";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static ClassHandleType get(::mlir::MLIRContext *context, ::mlir::SymbolRefAttr classSym);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"class"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::SymbolRefAttr getClassSym() const;
};
class TimeType : public ::mlir::Type::TypeBase<TimeType, moore::PackedType, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.time";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"time"};
  }

};
namespace detail {

struct IntTypeStorage;

} // namespace detail
class IntType : public ::mlir::Type::TypeBase<IntType, moore::PackedType, detail::IntTypeStorage> {
public:
  using Base::Base;
  /// Create a signless `bit [width-1:0]` type.
  static IntType getInt(MLIRContext *context, unsigned width) {
    return get(context, width, Domain::TwoValued);
  }

  /// Create a signless `logic [width-1:0]` type.
  static IntType getLogic(MLIRContext *context, unsigned width) {
    return get(context, width, Domain::FourValued);
  }

  /// Get a two-valued version of this integer.
  IntType getTwoValued() {
    if (getDomain() == Domain::TwoValued)
      return *this;
    return getInt(getContext(), getWidth());
  }

  /// Get a four-valued version of this integer.
  IntType getFourValued() {
    if (getDomain() == Domain::FourValued)
      return *this;
    return getLogic(getContext(), getWidth());
  }
  static constexpr ::llvm::StringLiteral name = "moore.int";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static IntType get(::mlir::MLIRContext *context, unsigned width, Domain domain);
  unsigned getWidth() const;
  Domain getDomain() const;
};
namespace detail {

struct RealTypeStorage;

} // namespace detail
class RealType : public ::mlir::Type::TypeBase<RealType, moore::UnpackedType, detail::RealTypeStorage> {
public:
  using Base::Base;
  // Convenience helpers
  static RealType getShortReal(MLIRContext *ctx) { return get(ctx, RealWidth::f32); }
  static RealType getReal     (MLIRContext *ctx) { return get(ctx, RealWidth::f64); }
  static constexpr ::llvm::StringLiteral name = "moore.real";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static RealType get(::mlir::MLIRContext *context, RealWidth width);
  RealWidth getWidth() const;
};
namespace detail {

struct ArrayTypeStorage;

} // namespace detail
class ArrayType : public ::mlir::Type::TypeBase<ArrayType, moore::PackedType, detail::ArrayTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.array";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static ArrayType get(::mlir::MLIRContext *context, unsigned size, PackedType elementType);
  static ArrayType get(unsigned size, PackedType elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"array"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getSize() const;
  PackedType getElementType() const;
};
namespace detail {

struct UnpackedArrayTypeStorage;

} // namespace detail
class UnpackedArrayType : public ::mlir::Type::TypeBase<UnpackedArrayType, moore::UnpackedType, detail::UnpackedArrayTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.uarray";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static UnpackedArrayType get(::mlir::MLIRContext *context, unsigned size, UnpackedType elementType);
  static UnpackedArrayType get(unsigned size, UnpackedType elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"uarray"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getSize() const;
  UnpackedType getElementType() const;
};
namespace detail {

struct OpenArrayTypeStorage;

} // namespace detail
class OpenArrayType : public ::mlir::Type::TypeBase<OpenArrayType, moore::PackedType, detail::OpenArrayTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.open_array";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static OpenArrayType get(::mlir::MLIRContext *context, PackedType elementType);
  static OpenArrayType get(PackedType elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"open_array"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  PackedType getElementType() const;
};
namespace detail {

struct OpenUnpackedArrayTypeStorage;

} // namespace detail
class OpenUnpackedArrayType : public ::mlir::Type::TypeBase<OpenUnpackedArrayType, moore::UnpackedType, detail::OpenUnpackedArrayTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.open_uarray";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static OpenUnpackedArrayType get(::mlir::MLIRContext *context, UnpackedType elementType);
  static OpenUnpackedArrayType get(UnpackedType elementType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"open_uarray"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  UnpackedType getElementType() const;
};
namespace detail {

struct AssocArrayTypeStorage;

} // namespace detail
class AssocArrayType : public ::mlir::Type::TypeBase<AssocArrayType, moore::UnpackedType, detail::AssocArrayTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.assoc_array";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static AssocArrayType get(::mlir::MLIRContext *context, UnpackedType elementType, UnpackedType indexType);
  static AssocArrayType get(UnpackedType elementType, UnpackedType indexType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"assoc_array"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  UnpackedType getElementType() const;
  UnpackedType getIndexType() const;
};
namespace detail {

struct QueueTypeStorage;

} // namespace detail
class QueueType : public ::mlir::Type::TypeBase<QueueType, moore::UnpackedType, detail::QueueTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.queue";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static QueueType get(::mlir::MLIRContext *context, UnpackedType elementType, unsigned bound);
  static QueueType get(UnpackedType elementType, unsigned bound);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"queue"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  UnpackedType getElementType() const;
  unsigned getBound() const;
};
namespace detail {

struct StructTypeStorage;

} // namespace detail
class StructType : public ::mlir::Type::TypeBase<StructType, moore::PackedType, detail::StructTypeStorage, ::mlir::DestructurableTypeInterface::Trait> {
public:
  using Base::Base;
  std::optional<DenseMap<Attribute, Type>> getSubelementIndexMap();
  Type getTypeAtIndex(Attribute index);
  std::optional<uint32_t> getFieldIndex(StringAttr nameField);
  static constexpr ::llvm::StringLiteral name = "moore.struct";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  using Base::getChecked;
  static StructType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members);
  static StructType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<StructLikeMember> members);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<StructLikeMember> members);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"struct"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<StructLikeMember> getMembers() const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
};
namespace detail {

struct UnpackedStructTypeStorage;

} // namespace detail
class UnpackedStructType : public ::mlir::Type::TypeBase<UnpackedStructType, moore::UnpackedType, detail::UnpackedStructTypeStorage, ::mlir::DestructurableTypeInterface::Trait> {
public:
  using Base::Base;
  std::optional<DenseMap<Attribute, Type>> getSubelementIndexMap();
  Type getTypeAtIndex(Attribute index);
  std::optional<uint32_t> getFieldIndex(StringAttr nameField);
  static constexpr ::llvm::StringLiteral name = "moore.ustruct";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static UnpackedStructType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ustruct"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<StructLikeMember> getMembers() const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
};
namespace detail {

struct UnionTypeStorage;

} // namespace detail
class UnionType : public ::mlir::Type::TypeBase<UnionType, moore::PackedType, detail::UnionTypeStorage, ::mlir::DestructurableTypeInterface::Trait> {
public:
  using Base::Base;
  std::optional<DenseMap<Attribute, Type>> getSubelementIndexMap();
  Type getTypeAtIndex(Attribute index);
  std::optional<uint32_t> getFieldIndex(StringAttr nameField);
  static constexpr ::llvm::StringLiteral name = "moore.union";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  using Base::getChecked;
  static UnionType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members);
  static UnionType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<StructLikeMember> members);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::llvm::ArrayRef<StructLikeMember> members);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"union"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<StructLikeMember> getMembers() const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
};
namespace detail {

struct UnpackedUnionTypeStorage;

} // namespace detail
class UnpackedUnionType : public ::mlir::Type::TypeBase<UnpackedUnionType, moore::UnpackedType, detail::UnpackedUnionTypeStorage, ::mlir::DestructurableTypeInterface::Trait> {
public:
  using Base::Base;
  std::optional<DenseMap<Attribute, Type>> getSubelementIndexMap();
  Type getTypeAtIndex(Attribute index);
  std::optional<uint32_t> getFieldIndex(StringAttr nameField);
  static constexpr ::llvm::StringLiteral name = "moore.uunion";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static UnpackedUnionType get(::mlir::MLIRContext *context, ::llvm::ArrayRef<StructLikeMember> members);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"uunion"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::llvm::ArrayRef<StructLikeMember> getMembers() const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
};
namespace detail {

struct RefTypeStorage;

} // namespace detail
class RefType : public ::mlir::Type::TypeBase<RefType, moore::UnpackedType, detail::RefTypeStorage, ::mlir::DestructurableTypeInterface::Trait> {
public:
  using Base::Base;
  Domain getDomain() { return getNestedType().getDomain(); }
  std::optional<unsigned> getBitSize() {
    return getNestedType().getBitSize();
  };
  std::optional<DenseMap<Attribute, Type>> getSubelementIndexMap();
  Type getTypeAtIndex(Attribute index);
  std::optional<uint32_t> getFieldIndex(StringAttr nameField);
  static constexpr ::llvm::StringLiteral name = "moore.ref";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static RefType get(::mlir::MLIRContext *context, UnpackedType nestedType);
  static RefType get(UnpackedType nestedType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"ref"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  UnpackedType getNestedType() const;
  ::std::optional<::llvm::DenseMap<::mlir::Attribute, ::mlir::Type>> getSubelementIndexMap() const;
  ::mlir::Type getTypeAtIndex(::mlir::Attribute index) const;
};
class FormatStringType : public ::mlir::Type::TypeBase<FormatStringType, ::mlir::Type, ::mlir::TypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "moore.format_string";
  static constexpr ::llvm::StringLiteral dialectName = "moore";
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"format_string"};
  }

};

} // namespace circt::moore
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::VoidType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::StringType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::ChandleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::EventType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::NullType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::ClassHandleType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::TimeType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::IntType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::RealType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::ArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::UnpackedArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::OpenArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::OpenUnpackedArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::AssocArrayType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::QueueType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::StructType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::UnpackedStructType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::UnionType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::UnpackedUnionType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::RefType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(::circt::moore::FormatStringType)

#endif // GET_TYPEDEF_CLASSES

