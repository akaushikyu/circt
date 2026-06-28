/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

circt::debug::ScopeType,
circt::debug::StructType,
circt::debug::ArrayType,
circt::debug::ValueType,
circt::debug::EnumType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(circt::debug::ScopeType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::debug::ScopeType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(circt::debug::StructType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::debug::StructType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(circt::debug::ArrayType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::debug::ArrayType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(circt::debug::ValueType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::debug::ValueType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(circt::debug::EnumType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::debug::EnumType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<circt::debug::ScopeType>([&](auto t) {
      printer << circt::debug::ScopeType::getMnemonic();
      return ::mlir::success();
    })
    .Case<circt::debug::StructType>([&](auto t) {
      printer << circt::debug::StructType::getMnemonic();
      return ::mlir::success();
    })
    .Case<circt::debug::ArrayType>([&](auto t) {
      printer << circt::debug::ArrayType::getMnemonic();
      return ::mlir::success();
    })
    .Case<circt::debug::ValueType>([&](auto t) {
      printer << circt::debug::ValueType::getMnemonic();
      return ::mlir::success();
    })
    .Case<circt::debug::EnumType>([&](auto t) {
      printer << circt::debug::EnumType::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::debug {


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::ScopeType)
namespace circt::debug {


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::StructType)
namespace circt::debug {


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::ArrayType)
namespace circt::debug {


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::ValueType)
namespace circt::debug {


} // namespace circt::debug
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::debug::EnumType)
namespace circt::debug {


/// Parse a type registered to this dialect.
::mlir::Type DebugDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void DebugDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::debug

#endif // GET_TYPEDEF_CLASSES

