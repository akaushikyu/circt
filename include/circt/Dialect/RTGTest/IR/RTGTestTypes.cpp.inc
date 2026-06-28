/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

::circt::rtgtest::CPUType,
::circt::rtgtest::IntegerRegisterType,
::circt::rtgtest::FloatRegisterType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(::circt::rtgtest::CPUType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::CPUType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::IntegerRegisterType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::IntegerRegisterType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(::circt::rtgtest::FloatRegisterType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = ::circt::rtgtest::FloatRegisterType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<::circt::rtgtest::CPUType>([&](auto t) {
      printer << ::circt::rtgtest::CPUType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::IntegerRegisterType>([&](auto t) {
      printer << ::circt::rtgtest::IntegerRegisterType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<::circt::rtgtest::FloatRegisterType>([&](auto t) {
      printer << ::circt::rtgtest::FloatRegisterType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::rtgtest {

::mlir::Type CPUType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return CPUType::get(odsParser.getContext());
}

void CPUType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::CPUType)
namespace circt::rtgtest {

::mlir::Type IntegerRegisterType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return IntegerRegisterType::get(odsParser.getContext());
}

void IntegerRegisterType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::IntegerRegisterType)
namespace circt::rtgtest {

::mlir::Type FloatRegisterType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return FloatRegisterType::get(odsParser.getContext());
}

void FloatRegisterType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace circt::rtgtest
MLIR_DEFINE_EXPLICIT_TYPE_ID(::circt::rtgtest::FloatRegisterType)
namespace circt::rtgtest {


/// Parse a type registered to this dialect.
::mlir::Type RTGTestDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void RTGTestDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::rtgtest

#endif // GET_TYPEDEF_CLASSES

