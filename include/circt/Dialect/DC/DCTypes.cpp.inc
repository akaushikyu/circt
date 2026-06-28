/*===- TableGen'erated file -------------------------------------*- C++ -*-===*\
|*                                                                            *|
|* TypeDef Definitions                                                        *|
|*                                                                            *|
|* Automatically generated file, do not edit!                                 *|
|*                                                                            *|
\*===----------------------------------------------------------------------===*/

#ifdef GET_TYPEDEF_LIST
#undef GET_TYPEDEF_LIST

circt::dc::TokenType,
circt::dc::ValueType

#endif // GET_TYPEDEF_LIST

#ifdef GET_TYPEDEF_CLASSES
#undef GET_TYPEDEF_CLASSES

static ::mlir::OptionalParseResult generatedTypeParser(::mlir::AsmParser &parser, ::llvm::StringRef *mnemonic, ::mlir::Type &value) {
  return ::mlir::AsmParser::KeywordSwitch<::mlir::OptionalParseResult>(parser)
    .Case(circt::dc::TokenType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::dc::TokenType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Case(circt::dc::ValueType::getMnemonic(), [&](llvm::StringRef, llvm::SMLoc) {
      value = circt::dc::ValueType::parse(parser);
      return ::mlir::success(!!value);
    })
    .Default([&](llvm::StringRef keyword, llvm::SMLoc) {
      *mnemonic = keyword;
      return std::nullopt;
    });
}

static ::llvm::LogicalResult generatedTypePrinter(::mlir::Type def, ::mlir::AsmPrinter &printer) {
  return ::llvm::TypeSwitch<::mlir::Type, ::llvm::LogicalResult>(def)    .Case<circt::dc::TokenType>([&](auto t) {
      printer << circt::dc::TokenType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Case<circt::dc::ValueType>([&](auto t) {
      printer << circt::dc::ValueType::getMnemonic();
t.print(printer);
      return ::mlir::success();
    })
    .Default([](auto) { return ::mlir::failure(); });
}

namespace circt::dc {

::mlir::Type TokenType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  return TokenType::get(odsParser.getContext());
}

void TokenType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
}


} // namespace circt::dc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::dc::TokenType)
namespace circt::dc {

namespace detail {

struct ValueTypeStorage : public ::mlir::TypeStorage {
  using KeyTy = std::tuple<Type>;
  ValueTypeStorage(Type innerType) : innerType(std::move(innerType)) {}

  KeyTy getAsKey() const {
    return KeyTy(innerType);
  }

  bool operator==(const KeyTy &tblgenKey) const {
    return (innerType == std::get<0>(tblgenKey));
  }

  static ::llvm::hash_code hashKey(const KeyTy &tblgenKey) {
    return ::llvm::hash_combine(std::get<0>(tblgenKey));
  }

  static ValueTypeStorage *construct(::mlir::TypeStorageAllocator &allocator, KeyTy &&tblgenKey) {
    auto innerType = std::move(std::get<0>(tblgenKey));
    return new (allocator.allocate<ValueTypeStorage>()) ValueTypeStorage(std::move(innerType));
  }

  Type innerType;
};

} // namespace detail
ValueType ValueType::get(::mlir::MLIRContext *context, Type innerType) {
  return Base::get(context, std::move(innerType));
}

::mlir::Type ValueType::parse(::mlir::AsmParser &odsParser) {
  ::mlir::Builder odsBuilder(odsParser.getContext());
  ::llvm::SMLoc odsLoc = odsParser.getCurrentLocation();
  (void) odsLoc;
  ::mlir::FailureOr<Type> _result_innerType;
  // Parse literal '<'
  if (odsParser.parseLess()) return {};

  // Parse variable 'innerType'
  _result_innerType = ::mlir::FieldParser<Type>::parse(odsParser);
  if (::mlir::failed(_result_innerType)) {
    odsParser.emitError(odsParser.getCurrentLocation(), "failed to parse ValueType parameter 'innerType' which is to be a `Type`");
    return {};
  }
  // Parse literal '>'
  if (odsParser.parseGreater()) return {};
  assert(::mlir::succeeded(_result_innerType));
  return ValueType::get(odsParser.getContext(),
      Type((*_result_innerType)));
}

void ValueType::print(::mlir::AsmPrinter &odsPrinter) const {
  ::mlir::Builder odsBuilder(getContext());
  odsPrinter << "<";
  odsPrinter.printStrippedAttrOrType(getInnerType());
  odsPrinter << ">";
}

Type ValueType::getInnerType() const {
  return getImpl()->innerType;
}


} // namespace circt::dc
MLIR_DEFINE_EXPLICIT_TYPE_ID(circt::dc::ValueType)
namespace circt::dc {


/// Parse a type registered to this dialect.
::mlir::Type DCDialect::parseType(::mlir::DialectAsmParser &parser) const {
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
void DCDialect::printType(::mlir::Type type,
                    ::mlir::DialectAsmPrinter &printer) const {
  if (::mlir::succeeded(generatedTypePrinter(type, printer)))
    return;
  
}

} // namespace circt::dc

#endif // GET_TYPEDEF_CLASSES

