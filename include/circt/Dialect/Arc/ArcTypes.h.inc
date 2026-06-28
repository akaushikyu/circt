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
namespace circt::arc {

class StateType;
class MemoryType;
class StorageType;
class SimModelInstanceType;
/// Program counter of a coroutine
/// An opaque program counter value indicating where to resume execution of a
/// coroutine. The concrete size is determined by lowering.
class CoroutinePCType;
/// State persisted between re-entries into a coroutine
/// An opaque value representing the local state within a coroutine that
/// persists between re-entries into that coroutine. The concrete layout is
/// determined by lowering and is likely a union of structs, with each struct
/// corresponding to a unique resumption block in the coroutine.
class CoroutineStateType;
/// array reference
/// An array reference is a reference (pointer) to an array of values.
class ArrayRefType;
namespace detail {

struct StateTypeStorage;

} // namespace detail
class StateType : public ::mlir::Type::TypeBase<StateType, ::mlir::Type, detail::StateTypeStorage> {
public:
  using Base::Base;
  unsigned getBitWidth();
  unsigned getByteWidth() { return (getBitWidth() + 7) / 8; }
  static constexpr ::llvm::StringLiteral name = "arc.state";
  static constexpr ::llvm::StringLiteral dialectName = "arc";
  using Base::getChecked;
  static StateType get(::mlir::MLIRContext *context, ::mlir::Type type);
  static StateType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type type);
  static StateType get(::mlir::Type type);
  static StateType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type type);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"state"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getType() const;
};
namespace detail {

struct MemoryTypeStorage;

} // namespace detail
class MemoryType : public ::mlir::Type::TypeBase<MemoryType, ::mlir::Type, detail::MemoryTypeStorage> {
public:
  using Base::Base;
  unsigned getStride();
  static constexpr ::llvm::StringLiteral name = "arc.memory";
  static constexpr ::llvm::StringLiteral dialectName = "arc";
  static MemoryType get(::mlir::MLIRContext *context, unsigned numWords, ::mlir::IntegerType wordType, ::mlir::IntegerType addressType);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"memory"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getNumWords() const;
  ::mlir::IntegerType getWordType() const;
  ::mlir::IntegerType getAddressType() const;
};
namespace detail {

struct StorageTypeStorage;

} // namespace detail
class StorageType : public ::mlir::Type::TypeBase<StorageType, ::mlir::Type, detail::StorageTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "arc.storage";
  static constexpr ::llvm::StringLiteral dialectName = "arc";
  static StorageType get(::mlir::MLIRContext *context, unsigned size);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"storage"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  unsigned getSize() const;
};
namespace detail {

struct SimModelInstanceTypeStorage;

} // namespace detail
class SimModelInstanceType : public ::mlir::Type::TypeBase<SimModelInstanceType, ::mlir::Type, detail::SimModelInstanceTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "arc.sim.instance";
  static constexpr ::llvm::StringLiteral dialectName = "arc";
  static SimModelInstanceType get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr model);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"sim.instance"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::FlatSymbolRefAttr getModel() const;
};
namespace detail {

struct CoroutinePCTypeStorage;

} // namespace detail
class CoroutinePCType : public ::mlir::Type::TypeBase<CoroutinePCType, ::mlir::Type, detail::CoroutinePCTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "arc.coroutine_pc";
  static constexpr ::llvm::StringLiteral dialectName = "arc";
  static CoroutinePCType get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr coroutine);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"coroutine_pc"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::FlatSymbolRefAttr getCoroutine() const;
};
namespace detail {

struct CoroutineStateTypeStorage;

} // namespace detail
class CoroutineStateType : public ::mlir::Type::TypeBase<CoroutineStateType, ::mlir::Type, detail::CoroutineStateTypeStorage> {
public:
  using Base::Base;
  static constexpr ::llvm::StringLiteral name = "arc.coroutine_state";
  static constexpr ::llvm::StringLiteral dialectName = "arc";
  static CoroutineStateType get(::mlir::MLIRContext *context, mlir::FlatSymbolRefAttr coroutine);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"coroutine_state"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  mlir::FlatSymbolRefAttr getCoroutine() const;
};
namespace detail {

struct ArrayRefTypeStorage;

} // namespace detail
class ArrayRefType : public ::mlir::Type::TypeBase<ArrayRefType, ::mlir::Type, detail::ArrayRefTypeStorage, circt::hw::BitWidthTypeInterface::Trait, ::mlir::ShapedType::Trait> {
public:
  using Base::Base;
  size_t getNumElements() const;

  std::optional<size_t> getByteWidth() const {
    std::optional<size_t> bitWidth = getBitWidth();
    if (!bitWidth.has_value()) {
      return std::nullopt;
    }
    return (*bitWidth + 7) / 8;
  }
  static constexpr ::llvm::StringLiteral name = "arc.arrayref";
  static constexpr ::llvm::StringLiteral dialectName = "arc";
  using Base::getChecked;
  static ArrayRefType get(::mlir::MLIRContext *context, ::mlir::Type elementType, uint64_t size);
  static ArrayRefType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, ::mlir::Type elementType, uint64_t size);
  static ArrayRefType get(Type elementType, uint64_t size);
  static ArrayRefType getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, Type elementType, uint64_t size);
  static ::llvm::LogicalResult verify(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, uint64_t size);
  static ::llvm::LogicalResult verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::Type elementType, uint64_t size);
  static constexpr ::llvm::StringLiteral getMnemonic() {
    return {"arrayref"};
  }

  static ::mlir::Type parse(::mlir::AsmParser &odsParser);
  void print(::mlir::AsmPrinter &odsPrinter) const;
  ::mlir::Type getElementType() const;
  uint64_t getSize() const;
  std::optional<int64_t> getBitWidth() const;
  ::mlir::ShapedType cloneWith(::std::optional<::llvm::ArrayRef<int64_t>> shape, ::mlir::Type elementType) const;
  bool hasRank() const;
  ::llvm::ArrayRef<int64_t> getShape() const;
};

} // namespace circt::arc
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::StateType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::MemoryType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::StorageType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::SimModelInstanceType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutinePCType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::CoroutineStateType)
MLIR_DECLARE_EXPLICIT_TYPE_ID(circt::arc::ArrayRefType)

#endif // GET_TYPEDEF_CLASSES

