/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

circt::ltl::SequenceType,
circt::ltl::PropertyType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(circt::ltl::SequenceType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::ltl::SequenceType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Case(circt::ltl::PropertyType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::ltl::PropertyType::get(parser.getContext());
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<circt::ltl::SequenceType>([&](auto t) {
      printer << circt::ltl::SequenceType::getMnemonic();
      return ::mlir::success();
    })
    .Case<circt::ltl::PropertyType>([&](auto t) {
      printer << circt::ltl::PropertyType::getMnemonic();
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::ltl {


} // namespace circt::ltl
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::ltl::SequenceType)
namespace circt::ltl {


} // namespace circt::ltl
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::ltl::PropertyType)
namespace circt::ltl {


/// Parse a type registered to this dialect.
::mlir::Type LTLDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void LTLDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::ltl

#endif // GET_TYPEDEF_CLASSES

