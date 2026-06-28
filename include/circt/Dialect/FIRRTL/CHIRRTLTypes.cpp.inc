/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::chirrtl::CMemoryType,
::circt::chirrtl::CMemoryPortType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::chirrtl::CMemoryType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::chirrtl::CMemoryType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::chirrtl::CMemoryPortType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::chirrtl::CMemoryPortType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::chirrtl::CMemoryType>([&](auto t) {
      printer << ::circt::chirrtl::CMemoryType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::chirrtl::CMemoryPortType>([&](auto t) {
      printer << ::circt::chirrtl::CMemoryPortType::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::chirrtl {

namespace detail {

struct CMemoryTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<firrtl::FIRRTLBaseType, uint64_t>;
  CMemoryTypeStorage(firrtl::FIRRTLBaseType elementType, uint64_t numElements) : elementType(std::move(elementType)), numElements(std::move(numElements)) {}

  KeyTy getAsKey() const {
    return KeyTy(elementType, numElements);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (elementType == std::get<0>(tblgenKey)) && (numElements == std::get<1>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey), std::get<1>(tblgenKey));
  }

  static CMemoryTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto elementType = std::move(std::get<0>(tblgenKey));
    auto numElements = std::move(std::get<1>(tblgenKey));
    return new (allocator.allocate<CMemoryTypeStorage>()) CMemoryTypeStorage(std::move(elementType), std::move(numElements));
  }

  firrtl::FIRRTLBaseType elementType;
  uint64_t numElements;
};

} // namespace detail
CMemoryType CMemoryType::get(::mlir::MLIRContext *context, firrtl::FIRRTLBaseType elementType, uint64_t numElements) {
  return Base::get(context, std::move(elementType), std::move(numElements));
}

CMemoryType CMemoryType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, ::mlir::MLIRContext *context, firrtl::FIRRTLBaseType elementType, uint64_t numElements) {
  return Base::getChecked(emitError, context, std::move(elementType), std::move(numElements));
}

CMemoryType CMemoryType::get(firrtl::FIRRTLBaseType elementType, uint64_t numElements) {
  return Base::get(elementType.getContext(), elementType, numElements);
}

CMemoryType CMemoryType::getChecked(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, firrtl::FIRRTLBaseType elementType, uint64_t numElements) {
  return Base::getChecked(emitError, elementType.getContext(), elementType, numElements);
}

::llvm::LogicalResult CMemoryType::verifyInvariants(::llvm::function_ref<::mlir::InFlightDiagnostic()> emitError, firrtl::FIRRTLBaseType elementType, uint64_t numElements) {
  if (::mlir::failed(verify(emitError, elementType, numElements)))
    return ::mlir::failure();
  return ::mlir::success();
}

firrtl::FIRRTLBaseType CMemoryType::getElementType() const {
  return getImpl()->elementType;
}

uint64_t CMemoryType::getNumElements() const {
  return getImpl()->numElements;
}


} // namespace circt::chirrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::CMemoryType)
namespace circt::chirrtl {


} // namespace circt::chirrtl
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::chirrtl::CMemoryPortType)
namespace circt::chirrtl {


/// Parse a type registered to this dialect.
::mlir::Type CHIRRTLDialect::parseType(::mlir::DialectAsmParser &parser) const {
  ::llvm::SMLoc typeLoc = parser.getCurrentLocation();
  ::llvm::StringRef mnemonic;
  ::mlir::Type genType;
  auto parseResult = generatedTypeParser(parser, &mnemonic, genType);
  if (parseResult.has_value())
    return genType;
  
  parser.emitError(typeLoc) << "unknown  type `"
      << mnemonic << "` in dialect `" << getNamespace() << "`";
  return {};
}
/// Print a type registered to this dialect.
void CHIRRTLDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::chirrtl

#endif // GET_TYPEDEF_CLASSES

